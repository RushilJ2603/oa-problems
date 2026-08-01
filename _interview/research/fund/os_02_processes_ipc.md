# Processes and inter-process communication

## From program to process

A **program** is passive: an executable file on disk (an ELF binary, say) holding machine code and
initial data. A **process** is that program *in execution* — an active entity with its own memory,
registers, and operating-system bookkeeping. Running the same program twice creates two distinct
processes. The process, not the program, is the unit to which the OS allocates resources.

Getting from source to a running process passes through a fixed toolchain:

$$\text{HLL source} \xrightarrow{\text{compiler}} \text{assembly / object files} \xrightarrow{\text{linker}} \text{executable} \xrightarrow{\text{loader}} \text{process in memory}$$

The **compiler** translates high-level source into object files; the **linker** stitches object
files and libraries into one executable, resolving cross-references; the **loader** (invoked by
`exec`) maps that executable into a fresh address space and starts it. An object/executable file is
itself structured — a **header**, a **text** (code) section, a **data** section, a **BSS** section,
a **symbol table**, **relocation information**, and **debugging information** — and the loader uses
these to lay out the process image.

## The process address space

When the loader builds a process, its memory is divided into regions with distinct purposes:

| Region | Holds | Notes |
|---|---|---|
| **Text (code)** | Machine instructions | Read-only and shareable between processes running the same program |
| **Data** | Initialized globals/statics | |
| **BSS** | Uninitialized globals/statics | Zero-filled by the OS before `main` |
| **Heap** | Dynamic allocation (`malloc`/`new`) | **Grows upward** toward higher addresses |
| **Memory-mapped region** | Shared libraries, `mmap`ed files | Between heap and stack |
| **Stack** | Locals, arguments, return addresses | **Grows downward** toward lower addresses |
| **Args/env** | `argv`, environment strings | Highest addresses |

> **Trap — stack vs heap.** The **stack** is fast (allocation is just moving the stack pointer),
> automatically freed on return, but small and fixed-limit; a runaway recursion causes a **stack
> overflow**. The **heap** is large and flexible but slower, manually managed, and prone to
> fragmentation and leaks. The two grow toward each other; a collision is fatal.

## Process states

A process moves through a lifecycle. The full **seven-state model** (the two "suspend" states
appear once swapping to disk is considered):

- **New** — the PCB is being created; not yet admitted to memory.
- **Ready** — in memory, waiting for the CPU.
- **Running** — executing on a CPU.
- **Waiting / Blocked** — cannot proceed until an event occurs (I/O completion, a lock, a signal).
- **Terminated** — finished or killed; the PCB lingers until the parent reaps it.
- **Suspend-Ready** — was ready, but its memory has been swapped out to disk to relieve memory
  pressure; must be swapped back before running.
- **Suspend-Blocked** — was blocked *and* swapped out; when its event fires it becomes
  Suspend-Ready.

> **Key point.** A thread has a simpler life — essentially **Running, Ready, Blocked** — because it
> is a unit of execution within a process and does not independently own memory to be swapped.

## The process control block (PCB)

> **Definition — PCB.** The kernel data structure that represents a process (in Linux, the
> `task_struct`). It lives in **kernel memory**, out of reach of user code.

A PCB records everything the OS needs to manage and resume the process:

- **Identification** — PID, parent PID, user/group IDs.
- **State** — its current lifecycle state.
- **Program counter** — the address of the next instruction.
- **CPU registers** — the saved register context when the process is not running.
- **Memory-management info** — page/segment tables, base/limit registers.
- **Accounting** — CPU time used, priority, limits.
- **I/O status** — allocated devices and the **open-file table**.

## Context switches

> **Definition — Context switch.** Saving the state of the running process into its PCB and loading
> another process's state, so the CPU can switch which process it runs.

The scheduler triggers a switch on a **timer interrupt** (a time slice expired — preemption), when
a process **blocks** in a system call (e.g. `read`), or when an interrupt wakes a higher-priority
process. What is saved and restored: the CPU registers (including PC and stack pointer) to/from the
PCBs, plus pointing the MMU at the new process's page tables.

A context switch does **no useful application work — it is pure overhead**. Its cost is more than
the visible register copying:

- **Direct** — cycles to save/restore registers, switch page tables, run the scheduler.
- **Indirect (the real cost)** — switching address spaces **flushes the TLB**, and the new
  process's data is cold in the CPU caches, so the first many memory accesses are slow.

> **Interview.** *Why is a thread switch cheaper than a process switch?* Threads of one process
> share an address space, so a thread switch swaps only registers — the page tables are unchanged,
> so the **TLB is not flushed** and caches stay warm. A process switch changes the address space,
> paying the full TLB/cache penalty.

## Creating processes: `fork`, `exec`, `wait`

Unix creates processes with a deliberately split, two-call design.

- **`fork()`** duplicates the calling process. It is called once but **returns twice**: in the
  parent it returns the child's PID, in the child it returns `0` (and `-1` on failure). The child
  receives an independent copy of the parent's address space and a *duplicate* of its open file
  descriptors.

```c
pid_t pid = fork();
if (pid == 0) {          // child
    /* ... */
} else if (pid > 0) {    // parent, pid = child's PID
    /* ... */
}
```

- **`exec()`** (the `execl`/`execvp` family) **replaces** the current process image with a new
  program loaded from disk. On success it **never returns** (there is nothing to return to); it
  keeps the same PID and, by default, the open file descriptors.
- **`wait()` / `waitpid()`** blocks the parent until a child terminates, delivering the child's
  exit status and letting the OS free the child's remaining resources (**reaping**).

> **Key point — why split `fork` and `exec`?** The gap between them is where the child, still a copy
> of the parent, rewires itself: redirecting stdin/stdout, wiring up pipes, dropping privileges, or
> closing descriptors — *before* the new program takes over. This is exactly how a shell builds a
> pipeline such as `ls | grep foo`.

> **Trap — descriptor inheritance.** Open descriptors survive `fork` **and** `exec` by default. A
> server that forks and execs a helper can leak its listening socket into the child. Mark sensitive
> descriptors `FD_CLOEXEC` (close-on-exec).

## Copy-on-write

Copying a parent's entire address space on every `fork` would be wasteful — especially since the
child often immediately `exec`s a different program. **Copy-on-write (COW)** avoids it.

On `fork`, the OS does not copy pages. It points the child's page table at the **same physical
pages** as the parent, marks all of them **read-only**, and bumps each page's reference count. The
processes share memory harmlessly as long as they only read. The instant either one **writes**, the
MMU raises a protection **page fault**; the OS allocates a fresh frame, copies that one page into
it, remaps the writer's page as read-write, and lets the write proceed. Only pages that are
actually modified are ever copied.

> **Key point.** COW makes `fork` cheap and is why the `fork`-then-`exec` idiom is efficient: almost
> nothing is copied before `exec` throws the address space away.

## Zombies and orphans

> **Definition — Zombie.** A process that has terminated but whose parent has not yet `wait`ed for
> it. The kernel must keep its exit status (a small PCB entry) until the parent collects it, so a
> zombie holds **no memory or CPU — only a PID**.

> **Definition — Orphan.** A process whose parent terminated while it is still running. The OS
> **reparents** orphans to `init`/`systemd` (PID 1), which periodically `wait`s and reaps them.

> **Trap.** You cannot `kill -9` a zombie — it is already dead; the signal has no one to act on. The
> cure is for the parent to `wait`, or to kill the *parent*, after which PID 1 adopts and reaps the
> zombie. A process that spawns many children and never reaps them (no `wait`, no `SIGCHLD` handler)
> leaks PIDs until the system cannot fork — a common daemon bug.

## Inter-process communication

Because each process has a private address space, cooperating processes need explicit **IPC**.
Everything reduces to two paradigms:

- **Message passing** — processes exchange messages through the kernel; the kernel moves the data
  and provides implicit synchronization. Simple and safe, but every message is copied
  user→kernel→user. (Pipes, message queues, sockets.)
- **Shared memory** — the kernel maps one physical region into several address spaces; processes
  then read/write it directly. **Fastest**, because after setup there is no kernel involvement and
  no copying — but the processes must synchronize access **themselves** (with semaphores/mutexes
  placed *inside* the shared region).

### Pipes

A **pipe** is a one-way byte stream. An **anonymous pipe** (`pipe()`) yields a read end `fd[0]` and
a write end `fd[1]` and is used between related processes (typically parent/child after `fork`). A
**named pipe / FIFO** (`mkfifo`) is a special file in the filesystem, so *unrelated* processes can
use it. Pipes have a finite kernel buffer: `write` blocks when it is full, `read` blocks when it is
empty. Writing to a pipe whose read end is fully closed raises **`SIGPIPE`** (default: terminate).

### Shared memory

The OS maps the same physical frames into multiple processes' page tables (`shm_open`+`mmap`, System
V `shmget`/`shmat`, or anonymous `mmap`). Transfer is then pure user-space memory access — no
syscalls, no copies. The kernel provides **no synchronization**, so a mutex or semaphore (kept in
the shared region itself) is mandatory to avoid races.

### Message queues

Kernel-maintained lists of discrete messages. Unlike a pipe's raw byte stream, a queue **preserves
message boundaries** (one read returns exactly one message) and supports **types/priorities**, so a
consumer can pull the highest-priority message first. Queues persist in the kernel until deleted.

### Signals

A **signal** is an asynchronous notification — a software interrupt — that an event occurred. A
process can catch it with a handler, ignore it, or take the default action. Common ones: `SIGINT`
(Ctrl-C), `SIGKILL` (9, uncatchable), `SIGTERM` (15, catchable graceful stop), `SIGSEGV` (bad
memory access), `SIGCHLD` (a child stopped/terminated), `SIGPIPE` (broken pipe).

> **Trap.** Signals carry essentially no payload — just the number — so they are for *notification*,
> not data transfer. And handlers must be **async-signal-safe**: calling `malloc` or `printf` from a
> handler can corrupt state if the signal interrupted the same function mid-update.

### Sockets

**Sockets** give bidirectional communication. **Unix-domain sockets** (`AF_UNIX`) connect processes
on one machine through the kernel without touching the network stack (used by, e.g., a local
database server). **Network sockets** (`AF_INET`) reach across machines: **TCP** is a reliable,
ordered stream; **UDP** is unreliable, unordered datagrams.

### Choosing a mechanism

| Mechanism | Direction | Speed | Synchronization | Cross-machine | Typical use |
|---|---|---|---|---|---|
| Anonymous pipe | One-way | Medium | Implicit (blocking) | No | `stdin`/`stdout` chaining (`ls \| grep`) |
| Named pipe (FIFO) | One-way | Medium | Implicit | No | Stream between unrelated processes |
| Shared memory | Two-way | **Highest** (zero-copy) | **Manual** (semaphores) | No | Large / high-frequency data |
| Message queue | Two-way | Medium | Implicit | No | Discrete, prioritized messages |
| Signals | One-way | Tiny payload | — | No | Async alerts, graceful shutdown |
| Unix socket | Two-way | Medium | Implicit | No | Local client–server |
| Network socket | Two-way | Slowest | Implicit | **Yes** | Distributed systems |

### Producer–consumer through IPC

The bounded-buffer producer–consumer problem (treated in full under synchronization) shows the
paradigm trade-off concretely:

- **Shared memory + semaphores** — the buffer lives in shared memory guarded by a `mutex` plus an
  `empty` semaphore (initialized to the buffer size, counts free slots) and a `full` semaphore
  (initialized to 0, counts filled slots). Fastest, but every synchronization detail is the
  programmer's responsibility.
- **Message queue** — the producer `msgsnd`s and the consumer `msgrcv`s; the kernel blocks a
  producer on a full queue and a consumer on an empty one, so **no user-space synchronization is
  needed**. Simpler and robust, at the cost of kernel copying.

> **Interview.** *Why is shared memory the fastest IPC?* After the one-time page mapping, the
> processes read and write RAM directly — no system calls and no user→kernel→user copying, unlike
> pipes, queues, and sockets. The price is that you must synchronize it yourself.
