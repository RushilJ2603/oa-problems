# 18. RTOS & Real-Time Concepts

A *real-time system* is one where correctness depends not just on producing the logically correct result, but on producing it *before a strict deadline*. It prioritizes *determinism* (predictable timing) over raw throughput. A system calculating pi to a million digits quickly is fast, but not real-time. An engine controller that calculates injection timing in 10ms instead of 5ms is a catastrophic failure.

- **Hard real-time**: Missing a deadline is a total system failure (e.g., flight control, airbags).
- **Firm real-time**: Missing a deadline makes the result useless, but doesn't destroy the system (e.g., video frame decoding—late frames are dropped).
- **Soft real-time**: Missing a deadline degrades performance but is tolerated (e.g., UI updates).

## Superloop vs. RTOS

In a bare-metal *superloop* (cooperative multitasking), the `main` function runs an infinite `while(1)` loop, calling handlers sequentially.

```c
int main(void) {
    while (1) {
        read_sensors();
        update_display(); // If this takes 50ms...
        control_motor();  // ...this is delayed by 50ms!
    }
}
```

This model breaks down when one slow operation starves critical ones. A *Real-Time Operating System (RTOS)* introduces *preemptive multitasking*. The RTOS can forcefully interrupt a low-priority task to run a high-priority one, guaranteeing response times. You genuinely need an RTOS when timing dependencies between independent events become too complex for a linear loop.

## Tasks & Scheduling

```{=typst}
#heavy[
```

Dense — slow down: We are moving from a single linear execution thread to multiple concurrent virtual threads sharing one CPU core.

```{=typst}
]
```

Think of a busy chef (the CPU core) cooking multiple meals (tasks) at once. When a steak needs turning (a high-priority event), the chef instantly drops the salad prep, perfectly remembers their place (saves context), turns the steak, and later resumes the salad exactly where they left off.

![The lifecycle of a task in an RTOS. Only one task can be in the Running state per CPU core.](assets/s18_task_states.png)

Consider a drone firmware with a `FlightControlTask` (Priority 5, high) and a `LogToSDCardTask` (Priority 1, low). If logging is currently running and the IMU interrupt fires indicating new gyro data is ready, the RTOS pauses logging instantly, runs flight control, and then resumes logging.

In an RTOS, your program is split into independent **tasks** (or threads). Each task is written as an infinite loop and thinks it has the CPU entirely to itself. To create this illusion, the RTOS assigns each task its own private **stack** and tracks its **context** (the exact state of all CPU registers, just as we saw in §16). 

A hardware timer generates a periodic interrupt called the **system tick** (e.g., every 1ms). At every tick, or whenever a task yields, the RTOS scheduler looks at all tasks and picks the one with the highest priority to run next.

A task exists in one of several states:
- **Running**: Currently executing on the CPU (only one task per core).
- **Ready**: Able to execute, but waiting because a higher or equal priority task is currently Running.
- **Blocked**: Waiting for an event (a timer to expire, a message to arrive, a lock to release).
- **Suspended**: Explicitly paused by the programmer.

When the scheduler switches from Task A to Task B, it performs a **context switch**: it pushes Task A's CPU registers onto Task A's stack, saves the stack pointer, loads Task B's stack pointer, and pops Task B's registers into the CPU. This mechanism is *preemptive priority-based scheduling*.

```{=typst}
#trap[
```
A beginner assumes a blocked task (e.g., calling `vTaskDelay(10)`) spins in a `while` loop burning CPU cycles. It does not. The scheduler marks it Blocked, swaps it out, and does not schedule it again until the 10 ticks elapse, giving 100% of the CPU to other tasks.
```{=typst}
]
```

*This breaks when...* you have two tasks of the exact same highest priority that never block. They will typically *time-slice* (round-robin) every tick, wasting CPU cycles on constant context switching.

## Inter-Task Communication

When tasks share data, the concurrency hazards from §16 return. An RTOS provides thread-safe primitives to solve this:
- **Mutex (Mutual Exclusion)**: A token used to protect shared resources. A task "takes" the mutex, uses the resource, and "gives" it back. Only the owner can give it back.
- **Semaphore**: A signaling mechanism. A *binary semaphore* is like a flag (1 or 0) often used to synchronize a task with an interrupt. A *counting semaphore* tracks available resources (e.g., 5 empty slots in a buffer). Unlike a mutex, a semaphore has no "owner".
- **Message Queues**: A thread-safe FIFO buffer (like the ring buffer of §12) to pass data safely between tasks by copying the data, avoiding shared memory entirely.
- **Event Flags**: Lightweight bitmasks to signal tasks (e.g., "Bit 0 means DMA complete").

## Priority Inversion & Deadlock

```{=typst}
#heavy[
```

Dense — slow down: The interaction of priorities and locks creates catastrophic hidden dependencies that can crash a mission.

```{=typst}
]
```

Imagine a VIP (High priority task) who wants to enter a private room. A Janitor (Low priority) is currently inside cleaning, holding the only key (a mutex). Normally, the VIP just waits. But a regular customer (Medium priority) stops the Janitor in the hallway to chat. Because Medium outranks Low, the Janitor is preempted and cannot finish cleaning. The VIP is now stuck waiting indefinitely for the Medium customer to finish talking. 

![A timeline of priority inversion, followed by the priority inheritance fix.](assets/s18_priority_inversion.png)

This exact bug paralyzed the Mars Pathfinder in 1997 [2]. A low-priority meteorological task held a mutex on an information bus. A high-priority bus management task blocked on the mutex. A medium-priority communications task preempted the low-priority task. The high-priority task missed its deadline, triggering a watchdog reset.

**Priority Inversion** happens when a high-priority task is forced to wait for a low-priority task, and that low-priority task is preempted by a medium-priority task. The high-priority task is effectively running at the priority of the lowest task.

The solution is **Priority Inheritance** (or Priority Ceiling). When a high-priority task blocks on a mutex held by a low-priority task, the RTOS temporarily *elevates* the low-priority task to the high priority. This prevents medium-priority tasks from preempting it. Once the low-priority task releases the mutex, its priority drops back to normal.

```{=typst}
#interview[
```
**Q:** Why use a mutex instead of a binary semaphore to protect a shared resource?
**A:** A binary semaphore lacks *ownership*. Because the RTOS does not know who "owns" the semaphore, it cannot apply priority inheritance. Mutexes have ownership and thus prevent unbounded priority inversion.
```{=typst}
]
```

A related hazard is **Deadlock**, where tasks wait forever on each other. Deadlock strictly requires four *Coffman conditions* [3]:
1. **Mutual exclusion**: Resources cannot be shared.
2. **Hold and wait**: A task holds one lock while waiting for another.
3. **No preemption**: Locks cannot be forcibly taken away.
4. **Circular wait**: Task A waits on a lock held by B, while B waits on a lock held by A.

*This breaks when...* you acquire locks in inconsistent orders. Always acquiring Lock X before Lock Y across all tasks breaks the circular wait condition, guaranteeing deadlock cannot occur.

## ISRs under an RTOS

Interrupt Service Routines (ISRs) execute outside the RTOS scheduler's awareness and preempt *everything*. Therefore, ISRs must be incredibly short. You should never process data in an ISR. 

Instead, defer the work: the ISR clears the hardware flag, wakes a task (by giving a semaphore or sending to a queue), and exits. This wakes a high-priority "handler" task to do the heavy lifting.

![A typical RTOS architecture. Hardware triggers an ISR, which defers processing to a high-priority task via a semaphore. Tasks pass data via queues.](assets/s18_rtos_arch.png)

Most RTOS APIs have specific, safe functions for ISRs (e.g., `xQueueSendFromISR`). Never call a standard blocking RTOS function inside an interrupt.

Two critical latencies define system responsiveness:
- **Interrupt Latency**: Time from the hardware trigger to the first instruction of the ISR.
- **Scheduling Latency**: Time from the ISR making a task Ready, to that task actually Running on the CPU.

## Timing Analysis & Schedulability

To guarantee hard real-time deadlines, you must calculate the **Worst-Case Execution Time (WCET)** for tasks. You must also account for **jitter**—the variance in timing (e.g., a task meant to run exactly every 10ms sometimes runs at 10.1ms).

**Rate-Monotonic Scheduling (RMS)** is a foundational algorithm by Liu and Layland [1] for assigning priorities. The rule is simple: assign the highest priorities to tasks that run the most frequently (shortest periods). If total CPU utilization remains below roughly 69%, RMS mathematically guarantees all independent tasks will meet their deadlines.

## Memory in an RTOS

In a bare-metal system, you manage one stack. In an RTOS, *every* task needs its own stack. Overestimating stack size wastes precious SRAM; underestimating causes a **stack overflow**, which usually silently overwrites the memory (often the Task Control Block) of an adjacent task, causing bizarre, un-debuggable crashes.

Dynamic allocation (`malloc`/`free`) is highly discouraged in real-time systems. It is non-deterministic (takes variable time to execute) and risks heap fragmentation (§7/§17). Modern high-reliability systems statically allocate all task stacks and queues at compile time.

## The Landscape

- **FreeRTOS**: The undisputed standard for lightweight microcontrollers.
- **Zephyr**: A modern, feature-rich RTOS hosted by the Linux Foundation, providing a Linux-like device tree.
- **Watchdog Timer (WDT)**: A hardware timer that must be periodically "kicked" (reset) by software. If tasks deadlock or a superloop hangs, the timer expires and resets the whole CPU, saving the system from a permanent freeze.

## Worked Examples

### Task Communication (Producer / Consumer)

This pseudo-C example (using FreeRTOS-style naming) demonstrates two tasks safely passing data through a queue.

```c
// A queue holding up to 10 integers
QueueHandle_t dataQueue;

void ProducerTask(void *pvParameters) {
    int counter = 0;
    while (1) {
        counter++;
        // Send data to the back of the queue. Block for up to 10 ticks if full.
        xQueueSend(dataQueue, &counter, 10);
        
        // Block this task for 100 ticks, yielding CPU to others
        vTaskDelay(100); 
    }
}

void ConsumerTask(void *pvParameters) {
    int receivedValue;
    while (1) {
        // Attempt to receive data. portMAX_DELAY means block forever if empty.
        // The scheduler puts this task in the Blocked state until data arrives.
        if (xQueueReceive(dataQueue, &receivedValue, portMAX_DELAY)) {
            process_data(receivedValue);
        }
    }
}
```

### Tracing Priority Inheritance

Watch the timeline of a priority inversion fix:
1. `LowTask` (Priority 1) takes `MutexA`.
2. `HighTask` (Priority 3) preempts `LowTask` and tries to take `MutexA`.
3. `HighTask` blocks. The RTOS immediately raises `LowTask` to Priority 3 (Inheritance).
4. `MediumTask` (Priority 2) becomes Ready, but *cannot* preempt `LowTask` (because `LowTask` is currently acting as Priority 3).
5. `LowTask` finishes and gives `MutexA`.
6. `LowTask` drops back to Priority 1. `HighTask` acquires `MutexA` and resumes.

### Faded Example: Deferred Interrupt Processing

Here is an ISR that defers work by giving a binary semaphore. Fill in the missing call to wake the handler task safely from the interrupt context.

```c
SemaphoreHandle_t dmaSemaphore;

void DMA_IRQHandler(void) {
    // 1. Clear the hardware interrupt flag
    clear_dma_interrupt_flag();
    
    // 2. Wake the handler task. 
    // We CANNOT use standard xSemaphoreGive() here!
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    
    xSemaphoreGiveFromISR(dmaSemaphore, &higherPriorityTaskWoken);
    
    // 3. Force a context switch if waking the task made it the highest priority
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
}

void DmaHandlerTask(void *pvParameters) {
    while (1) {
        // Block forever waiting for the ISR to give the semaphore
        xSemaphoreTake(dmaSemaphore, portMAX_DELAY);
        process_dma_buffer();
    }
}
```

### References

[1] Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment — Journal of the ACM — https://dl.acm.org/doi/10.1145/321738.321743
[2] What Really Happened on Mars? — Mike Jones — https://www.cs.cornell.edu/courses/cs614/1999sp/papers/pathfinder.html
[3] System Deadlocks — ACM Computing Surveys — https://dl.acm.org/doi/10.1145/356586.356588
