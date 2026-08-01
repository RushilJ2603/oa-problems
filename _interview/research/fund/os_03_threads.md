# Threads and concurrency models

## Threads versus processes

A **thread** is the basic unit of CPU execution within a process — a single sequence of
instructions the scheduler can run independently. A process starts with one thread; giving it
several lets those threads run concurrently while sharing the process's memory. The key to
reasoning about threads is knowing exactly what they share and what they keep private:

| Shared by all threads (process-wide) | Private to each thread |
|---|---|
| Address space: text, data, heap | Stack (locals, call frames) |
| Open files / sockets (descriptor table) | Registers, including the stack pointer |
| Global and static variables | Program counter |
| Signal handlers, accounting, PID | Thread ID, scheduling state, thread-local storage |

The kernel tracks each thread with a **thread control block (TCB)** — TID, saved registers, PC,
stack pointer, state, and a pointer back to the process's PCB.

> **Key point.** Because threads share the heap and globals, they communicate simply by reading and
> writing shared variables — no IPC needed. That convenience is also the danger: shared writable
> state is exactly what creates race conditions, which is why synchronization (the next section)
> exists.

## Why threads, and their hazards

Threads buy **responsiveness** (one thread keeps working while another blocks — a UI thread stays
live while a worker loads data), **easy resource sharing**, **economy** (creating and switching
threads is far cheaper than processes — see the context-switch discussion under *Processes*), and
**scalability** across cores. The costs are the concurrency hazards: **data races**, **deadlocks**,
**oversubscription** (more runnable threads than cores → context-switch thrash), and **false
sharing** (independent variables sharing a cache line ping-ponging between cores).

## User-level versus kernel-level threads

Threads can be managed by a user-space library the kernel never sees, or by the kernel directly.

| | User-level threads | Kernel-level threads |
|---|---|---|
| Managed by | A user library | The OS kernel |
| Kernel awareness | Sees only the one process | Schedules each thread individually |
| Switch cost | Very cheap (no mode switch) | Higher (mode switch) |
| A blocking system call | **Blocks the whole process** (all its threads) | Blocks only that thread |
| Multicore | Cannot use multiple cores | Runs threads in parallel on many cores |

> **Trap.** The fatal flaw of pure user-level threads is the **blocking-syscall problem**: the
> kernel sees one process, so when any thread makes a blocking call, the kernel blocks the entire
> process and every other thread stalls with it.

## Multithreading models

These describe how user threads map onto kernel threads.

| Model | Mapping | Strengths | Weaknesses | Seen in |
|---|---|---|---|---|
| **Many-to-one** | Many user → 1 kernel thread | Very cheap switches | A blocking call freezes all; no true multicore | Early Java green threads (obsolete) |
| **One-to-one** | Each user → its own kernel thread | True parallelism; a block affects only one thread | Thread creation is a kernel operation; OS caps the count | Linux (NPTL), Windows, macOS — today's default |
| **Many-to-many** | Many user ↔ a smaller pool of kernel threads | Parallelism *and* bounded kernel overhead | Complex two-level scheduling | Go runtime, thread pools |
| **Two-level** | Many-to-many, but a thread may be *bound* 1:1 | Flexibility plus dedicated execution for critical threads | Most complex | Older Solaris, HP-UX |

## Concurrency versus parallelism

> **Definition.** **Concurrency** is *dealing with* many tasks at once — a matter of structure;
> interleaving tasks on one core by time-slicing is concurrent. **Parallelism** is *executing* many
> tasks at the same instant — it requires multiple cores.

One chef switching between dishes is concurrent; several chefs cooking simultaneously is parallel. A
single core can be fully concurrent (time-slicing) but never truly parallel.

**Amdahl's law** bounds the payoff of parallelism: if a fraction $P$ of the work is parallelizable
across $N$ processors,

$$\text{Speedup} = \frac{1}{(1-P) + P/N}.$$

> **Interview.** *Max speedup of a program that is 20% strictly sequential, on 1000 cores?* As
> $N\to\infty$ the speedup approaches $1/(1-P) = 1/0.2 = \mathbf{5\times}$. The serial fraction, not
> the core count, is the ceiling — the central lesson of Amdahl's law.

## Thread pools

Spawning a fresh thread per task is expensive and, if requests are unbounded, can exhaust the
system. A **thread pool** creates a fixed set of worker threads up front; they wait on a shared work
queue, and each picks up a task, runs it, and returns to wait. This **bounds concurrency** (no
thrashing from too many threads) and removes per-task creation latency. It is the many-to-many idea
applied at the application level.

## Thread safety, reentrancy, and thread-local storage

- **Thread-safe** — code behaves correctly when run by several threads at once (achieved by locks,
  atomics, or holding no shared mutable state).
- **Reentrant** — code that can be safely interrupted mid-execution and entered again before the
  first call finishes; it holds no static/global mutable state and returns no pointers to static
  data. **All reentrant code is thread-safe, but not all thread-safe code is reentrant** — a
  function that guards itself with a mutex is thread-safe, yet if a signal handler re-enters it, it
  self-deadlocks on that mutex.
- **Thread-local storage (TLS)** — data that looks global but has a private instance per thread
  (C's `errno`, Java's `ThreadLocal<T>`).

> **Interview.** *What happens if a thread in a multithreaded process calls `fork`?* The child gets
> **only the calling thread**, not the others. Any mutex the vanished threads held stays locked
> forever in the child — which is why after `fork` a child should generally only `exec` or call
> async-signal-safe functions.

## Lightweight threads: fibers, green threads, coroutines

Modern runtimes add threads *below* the kernel's radar, scheduled cooperatively in user space so
that millions can exist cheaply:

- **Go goroutines** — multiplexed many-to-many onto a small pool of OS threads; they yield at I/O
  and channel operations.
- **Java virtual threads (Project Loom)** — yield implicitly on blocking I/O, mapping vast numbers
  of virtual threads onto a few carrier OS threads.
- **Coroutines** — cooperatively scheduled, yielding at explicit `await`/`yield` points.

These trade preemption for scale: enormous concurrency at the cost of relying on tasks to yield.
