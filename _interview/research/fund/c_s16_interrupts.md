# 16. Interrupts & Concurrency in Embedded C

Embedded systems interact with a chaotic physical world. While your `main()` loop executes linearly, hardware events—a button press, an incoming network packet, or a timer expiring—cannot wait. They require immediate attention.

## Hardware Preemption: The Interrupt

An **interrupt** is a hardware mechanism that asynchronously preempts the CPU's current execution to run a dedicated function called an **Interrupt Service Routine (ISR)** [3]. 

When an **Interrupt Request (IRQ)** is asserted by a peripheral, the CPU completes its current instruction and immediately pauses. It saves its state (pushing registers and the program counter to the stack) and looks up the address of the corresponding ISR in a hardware-defined array called the **vector table** [3]. The CPU then jumps to that address, executes the ISR, restores the saved context, and resumes the exact instruction in `main()` it was about to execute.

![Hardware interrupt preemption flow, showing context saving and vector table resolution.](assets/s16_interrupt_flow.png)

**Interrupt latency** is the time measured from the physical hardware event asserting the IRQ to the execution of the first instruction inside the ISR. Minimizing this latency is critical for real-time systems.

## Writing an ISR in C

An ISR is a normal C function, but it is never called explicitly by your code—it is invoked directly by the CPU hardware. Because an ISR steals time from the main application, the golden rule of ISR design is: **keep it short and non-blocking**.

A well-designed ISR does exactly three things:
1. Clears the peripheral's interrupt hardware flag (acknowledging the event).
2. Performs the bare minimum immediate work (e.g., reading a received byte from a hardware data register).
3. Sets a flag or pushes data to a buffer, deferring the heavy processing to `main()`.

```{=typst}
#interview[
```

**Q:** Why can't you call `printf` or `malloc` inside an Interrupt Service Routine?

**A:** Because they are blocking and non-reentrant. `malloc` uses internal locks to protect the heap's linked list. If `main()` is inside `malloc` holding the lock, and an interrupt fires, the ISR calling `malloc` will attempt to acquire that same lock. The ISR blocks indefinitely waiting for `main()`, but `main()` cannot resume until the ISR finishes. The system is deadlocked.

```{=typst}
]
```

## Shared Data & Concurrency Hazards

```{=typst}
#heavy[
```

Dense — slow down: Data shared between asynchronous contexts is fundamentally broken unless explicitly synchronized.

```{=typst}
]
```

Imagine you are tallying cash. You look at a pile of 5 coins, mentally add 1, and reach for a pen to write "6". Suddenly, someone freezes time, drops 10 coins on the pile, crosses out the sheet, writes "15", and unfreezes you. You, unaware of the frozen moment, proceed to write "6". The 10 coins added during the pause are permanently lost from the record.

This is exactly what happens when `main()` and an ISR share a global variable. Let's look at a simple counter:

```c
// Shared global state
volatile int event_count = 0; 
```

`event_count++` appears to be a single action in C. However, the CPU executes it as a **Read-Modify-Write (RMW)** sequence:
1. **Read**: Load `event_count` from RAM into a CPU register.
2. **Modify**: Increment the register value.
3. **Write**: Store the new value back to RAM.

If an interrupt fires *after* the read step, the ISR might execute, read the old value, increment it, and write it back. When the ISR returns, `main()` blindly proceeds to step 2, incrementing its stale, cached value, and writes it back, completely erasing the ISR's update [1].

![A Read-Modify-Write torn by an interrupt, resulting in a lost update.](assets/s16_race.png)

```{=typst}
#trap[
```

Assuming `volatile` makes an operation atomic. It does not. `volatile` merely provides *visibility* (ensuring the compiler won't cache the variable in a register forever, forcing actual memory reads/writes). A multi-instruction read-modify-write on a `volatile` variable can still be torn by an interrupt.

```{=typst}
]
```

To fix this, we must protect the shared data. A **critical section** is a block of code where interrupts are temporarily disabled, ensuring the read-modify-write cycle completes entirely without preemption:

```c
// Fixing the race condition with a critical section
disable_interrupts(); // Assembly instruction (e.g., __disable_irq() on ARM)
event_count++;        // Now guaranteed to execute atomically
enable_interrupts();  // Restore preemption
```

*Question to sit with*: If critical sections solve the problem, why not wrap the entire `main()` loop in one? (Answer: Doing so would destroy your interrupt latency, defeating the whole purpose of hardware preemption).

This mechanism breaks if your critical section takes too long, causing the system to miss subsequent interrupts. 

Alternatively, C provides the `sig_atomic_t` type [2]. It is guaranteed to be readable and writable as a single atomic unit (meaning the CPU instruction cannot be torn midway). However, `sig_atomic_t` only guarantees atomicity for simple loads and stores, not for operations like `++` (which remain multi-instruction RMW sequences). For full atomic RMW operations without disabling interrupts, embedded systems increasingly rely on C11 `<stdatomic.h>`.

## Reentrancy

A function is **reentrant** if it can be safely interrupted in the middle of its execution and then called again from the ISR, before the first invocation has finished.

Functions become non-reentrant when they rely on shared, hidden state. For example, if a function modifies a static variable, writes to a global error code like `errno`, or dynamically allocates memory, it is unsafe to re-enter. To write reentrant code, pass all necessary state in via pointer arguments (stack variables) rather than relying on globals.

## Atomicity on the Target

An operation is **atomic** if it is indivisible; from the perspective of the rest of the system, it either has not started or has completely finished, with no observable intermediate state.

On most modern microcontrollers, an aligned word load or store (e.g., writing a 32-bit integer on a 32-bit ARM Cortex-M) is naturally atomic [3]. The CPU updates the memory in a single bus cycle. However, a 64-bit operation on a 32-bit MCU requires two 32-bit instructions, meaning an interrupt could occur between them, resulting in torn data where half the variable is old and half is new.

Furthermore, advanced architectures with instruction pipelines or multiple cores might perform operations out of order. **Memory barriers** (or fences) are explicit CPU instructions that force all pending memory reads and writes to complete before execution continues, ensuring that context boundaries see consistent memory states.

## Lock-Free Single-Producer/Single-Consumer Ring Buffer

```{=typst}
#heavy[
```

Dense — slow down: The shared data hazard can be bypassed entirely by carefully dividing ownership of memory.

```{=typst}
]
```

Imagine a restaurant order wheel. The waiter (Producer) clips tickets onto the incoming side of the wheel. The chef (Consumer) pulls tickets off the outgoing side. They never reach for the exact same physical clip at the same time.

In embedded C, passing a stream of data from an ISR to `main()` is typically done with a **lock-free single-producer/single-consumer (SPSC) ring buffer** (building on the buffer from §12). 

```c
#define BUF_SIZE 64

volatile uint8_t buffer[BUF_SIZE];
volatile uint32_t head = 0; // Written ONLY by ISR
volatile uint32_t tail = 0; // Written ONLY by main()
```

By splitting ownership, we eliminate the need for critical sections. The ISR *only* writes to the `head` index; `main()` *only* writes to the `tail` index. 

1. The ISR pushes a byte, then updates `head = (head + 1) % BUF_SIZE`.
2. `main()` sees that `head != tail`, reads the byte, and updates `tail = (tail + 1) % BUF_SIZE`.

![Single-producer, single-consumer ring buffer demonstrating separated index ownership.](assets/s16_spsc_ring.png)

This relies entirely on the architecture's guarantee that a simple store to a 32-bit index is word-atomic. When the ISR updates `head`, `main()` will either see the completely old `head` or the completely new `head`—never a corrupted, half-written value.

```{=typst}
#keypoint[
```

The data array itself doesn't need to be atomic because of strict sequencing: the ISR writes the payload to `buffer[head]` *before* it publishes the new `head` value. `main()` will not attempt to read that slot until it sees the updated `head`.

```{=typst}
]
```

This design breaks immediately if you introduce a second producer (e.g., two different ISRs pushing to the same buffer), because both ISRs would attempt a read-modify-write on the shared `head` index, causing a race condition.

## Polling vs Interrupt-Driven I/O

When designing hardware interactions, you must choose between polling and interrupts:
- **Polling (Busy-Waiting)**: `main()` continually checks a hardware register (`while (!(UART->STATUS & RX_READY));`). This is deterministic and simple, but costs 100% CPU utilization and prevents the processor from sleeping or doing other work.
- **Interrupt-Driven**: The CPU sleeps or performs background tasks until the hardware signals readiness. This dramatically reduces CPU waste and power consumption, but introduces preemption latency and concurrency hazards.

## Bridge to RTOS

As systems grow complex, manually managing flags and critical sections becomes brittle. A Real-Time Operating System (RTOS) solves this by providing abstract concurrency primitives. Instead of setting a raw `volatile` flag, an ISR will "give a semaphore" or "write to an RTOS queue". The RTOS kernel then preempts `main()`, automatically waking the exact thread waiting for that data (see §18).

This introduces new traps, such as **priority inversion**, where a low-priority thread holding a mutex blocks a high-priority thread from executing—a topic we will untangle when we introduce RTOS scheduling.

## Worked Examples

### 1. The Torn Counter & The Critical Section Fix

**The Bug:**
```c
volatile uint32_t system_ticks = 0;

// Hardware Timer ISR (Fires every 1ms)
void Timer_ISR(void) {
    system_ticks++; // Safe: only modified here
}

int main(void) {
    while(1) {
        // DANGER: system_ticks is 32-bit. On an 8-bit AVR, 
        // reading a 32-bit var takes 4 instructions!
        // An interrupt here will tear the read.
        if (system_ticks > 1000) { 
            do_something();
            system_ticks = 0; // DANGER: Torn write!
        }
    }
}
```

**The Fix:**
```c
int main(void) {
    uint32_t local_ticks;
    while(1) {
        // Enter Critical Section
        __disable_irq(); 
        local_ticks = system_ticks; 
        if (local_ticks > 1000) {
            system_ticks = 0; 
        }
        // Exit Critical Section
        __enable_irq(); 

        // Do slow work outside the critical section
        if (local_ticks > 1000) {
            do_something();
        }
    }
}
```

### 2. Lock-Free UART-RX Ring Buffer

```c
#define BUF_SIZE 64
volatile uint8_t rx_buf[BUF_SIZE];
volatile uint32_t rx_head = 0;
volatile uint32_t rx_tail = 0;

// Executed asynchronously by hardware
void UART_RX_ISR(void) {
    // 1. Read hardware register (clears interrupt flag)
    uint8_t data = UART0->DATA; 
    
    // 2. Calculate next index
    uint32_t next_head = (rx_head + 1) % BUF_SIZE;
    
    // 3. Prevent overflow: if full, discard byte
    if (next_head != rx_tail) {
        rx_buf[rx_head] = data; // Write payload
        rx_head = next_head;    // Publish atomic update
    }
}

// Executed continuously by main loop
int main(void) {
    while (1) {
        if (rx_head != rx_tail) {
            // Consumer reads data
            uint8_t byte = rx_buf[rx_tail];
            
            // Advance tail atomically
            rx_tail = (rx_tail + 1) % BUF_SIZE;
            
            process_byte(byte);
        }
    }
}
```

### 3. Faded Example: ISR Handshake

We want to trigger an expensive data processing function in `main()` whenever a GPIO button is pressed. Complete the code by adding the missing qualifier to ensure the compiler doesn't optimize away the flag check.

```c
// FIXME: What must qualify this variable so main() actually 
// re-reads it from RAM on every loop iteration?
______ bool button_pressed = false;

void GPIO_ISR(void) {
    // Acknowledge hardware
    GPIO->INT_CLEAR = BUTTON_PIN; 
    
    // Defer work to main
    button_pressed = true; 
}

int main(void) {
    while (1) {
        if (button_pressed) {
            button_pressed = false;
            expensive_processing();
        }
    }
}
```
*(Solution: The flag must be declared as `volatile bool button_pressed = false;`)*

### References

[1] ISO/IEC 9899:2011 (C11 Standard) — 5.1.2.3 Program execution — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[2] ISO/IEC 9899:2011 (C11 Standard) — 7.14.1.1 The signal function (volatile sig_atomic_t) — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[3] ARM Cortex-M4 Devices Generic User Guide — Exception Model — https://developer.arm.com/documentation/dui0553/a/
