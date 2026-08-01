# Operating-system fundamentals and structure

## What an operating system is

An **operating system (OS)** is the software that sits between hardware and applications and does
two jobs at once. As a **resource manager** it decides how the CPU, memory, disk, and network are
shared among competing programs, fairly and safely. As an **abstraction layer** it hides the
messy particulars of hardware behind clean, uniform interfaces, so that a program writes to a file
without knowing whether the disk is spinning rust or flash, and opens a socket without driving the
network card directly.

> **Definition — Kernel.** The core of the operating system: the part that is always resident in
> memory and runs with full hardware privilege. It performs scheduling, memory management, and
> hardware communication. The *OS* is the larger package — kernel plus system libraries, shells,
> and utilities; the *kernel* is only its privileged heart.

> **Trap.** A shell (`bash`), a compiler, or `ls` is **not** part of the kernel. These are ordinary
> user-space programs that ask the kernel for services through system calls. Likewise the C
> library (`libc`) is user-space; it *wraps* kernel calls, it is not inside the kernel.

## User mode and kernel mode

If any program could execute any instruction and touch any memory, one buggy or malicious process
could halt the machine or read another's data. To prevent this, the CPU supports **dual-mode
operation**, governed by a hardware **mode bit**.

- **User mode** — the unprivileged mode ordinary applications run in. Code cannot execute
  privileged instructions or reach memory outside what the OS has granted it.
- **Kernel mode** (also *supervisor* or *ring 0*) — the privileged mode. Code may execute any
  instruction and access any address.

**Privileged instructions** — disabling interrupts, halting the CPU, loading the page-table base
register, issuing raw I/O — are legal only in kernel mode. If a user-mode program attempts one, the
hardware traps to the OS, which typically kills the offending process.

> **Key point.** A **mode switch** is not a **context switch**. Crossing the user/kernel boundary
> (to service a system call, say) is a mode switch *within the same process*. A context switch
> changes which process is running; it involves mode switches but also saves and restores whole
> process state, and is far more expensive.

| | User mode | Kernel mode |
|---|---|---|
| Privilege | Restricted | Unrestricted |
| Direct hardware access | No | Yes |
| A fatal bug here | Crashes one process | Crashes the system (kernel panic / BSOD) |
| Mode bit (typical) | 1 | 0 |

## System calls

A user program cannot simply *call* a kernel function the way it calls its own — that would let
arbitrary code run with full privilege. Instead it enters the kernel through exactly one guarded
gate: a **system call**.

> **Definition — System call.** The mechanism by which a user-space program requests a service
> from the kernel, crossing from user mode to kernel mode through a controlled trap.

The mechanism, step by step:

1. The program places the arguments in registers and loads a **system-call number** into a
   designated register (for example `rax` on x86-64).
2. It executes a special instruction (`syscall`, `sysenter`, or the older `int 0x80`), which
   raises a **software interrupt (trap)**.
3. The hardware saves minimal state, flips the mode bit to kernel mode, and jumps to a fixed
   kernel entry point.
4. The kernel uses the system-call number to index the **system-call table** and dispatch to the
   right routine (e.g. `sys_read`).
5. The routine runs, the return value is placed in a register, the mode bit flips back, and an
   interrupt-return resumes the user program at the next instruction.

Because arguments travel in registers rather than on the stack (the user and kernel stacks are
separate), and because large data is passed by a pointer the kernel must validate, a system call is
much costlier than a plain function call — it flushes pipelines and pollutes caches.

| | Library call | System call |
|---|---|---|
| Runs in | User mode | Kernel mode (after a mode switch) |
| Cost | Cheap | Expensive (trap + mode switch) |
| Portability | High (e.g. the POSIX C library) | Tied to the specific kernel |
| Examples | `printf`, `strlen`, `malloc` | `read`, `write`, `open`, `fork`, `brk` |

> **Trap.** A standard-library function is not automatically a system call. `printf` formats in
> user space and *then* calls the `write` system call; `malloc` manages a user-space heap and only
> drops into `brk`/`mmap` when it needs more pages. Know which is the wrapper and which is the
> syscall.

> **Interview.** *Why can't a program call kernel functions directly?* Because a direct call does
> not change privilege level. The kernel must keep a hard boundary so user code can enter only
> through the trap handler, in a controlled way, with its arguments checked.

## Interrupts, traps, exceptions, and faults

The CPU must react to events it did not plan for. These come in two flavours by *timing*:
**asynchronous** (arriving independently of what the CPU is executing) and **synchronous**
(produced by the current instruction).

- **Interrupt** — an *asynchronous* hardware signal (timer tick, disk-I/O completion, network
  packet, keystroke). The CPU finishes the current instruction, saves the program counter and
  status, looks up the handler in the **interrupt vector table**, and runs the **interrupt service
  routine (ISR)**. A *maskable* interrupt can be temporarily deferred; a *non-maskable* interrupt
  (e.g. an unrecoverable hardware error) cannot.
- **Trap** — a *synchronous*, *intentional* exception raised by an instruction, used to implement
  system calls and debugger breakpoints. Execution resumes at the following instruction.
- **Fault** — a *synchronous*, *unintentional* but often *recoverable* condition, such as a page
  fault or divide-by-zero. If the OS can fix it (e.g. by paging data in), execution retries the
  *faulting* instruction.
- **Abort** — an unrecoverable error.

| Type | Source | Timing | Intentional? | Example |
|---|---|---|---|---|
| Interrupt | Hardware | Asynchronous | No | Timer, disk done, keystroke |
| Trap | Software | Synchronous | Yes | System call, breakpoint |
| Fault | Software | Synchronous | No | Page fault, divide by zero |

> **Key point.** A **page fault is not an error.** It is the normal signal that a referenced page
> is not currently in RAM; the OS fetches it from disk and retries. Demand paging is built on it.

> **Trap.** An ISR generally must not sleep or block — it runs in a restricted context, often with
> interrupts disabled. It should do the minimum and defer heavy work (this deferral is exactly the
> idea behind the interrupt-then-poll designs discussed under I/O).

## Operating-system structure

Kernels are organized along a spectrum trading **performance** against **fault isolation**.

- **Monolithic kernel** — scheduling, memory management, file systems, and drivers all run
  together in one kernel address space. Components talk by direct function call, so it is fast; but
  a bug anywhere (a bad driver) can crash the whole system. *Linux, classic Unix.*
- **Microkernel** — only the bare minimum (IPC, basic scheduling, basic memory) runs in kernel
  mode; drivers and file systems run as separate user-space server processes. A crashed driver can
  be restarted without taking down the OS, so it is reliable and modular — but every service
  interaction becomes IPC across the user/kernel boundary, which costs performance. *QNX, MINIX,
  L4, Mach.*
- **Hybrid kernel** — mostly monolithic for speed, with some subsystems structured as separate
  modules. *Windows NT; macOS (XNU) is commonly described this way.*
- **Modular / layered** — a monolithic kernel that loads drivers dynamically as **loadable kernel
  modules**. This is logical modularity, not a microkernel: once loaded, a Linux module runs with
  full kernel privilege.

| | Monolithic | Microkernel |
|---|---|---|
| Kernel size | Large | Minimal |
| Speed | High (function calls) | Lower (IPC + mode switches) |
| Fault isolation | Weak (one bug crashes all) | Strong (a server can restart) |
| Example | Linux | QNX |

> **Interview.** *Why is a microkernel slower than a monolithic kernel?* In a monolithic kernel the
> file system reaches the disk driver by a direct function call. In a microkernel they are separate
> user processes, so the same interaction becomes message passing through the kernel — multiple
> mode switches and IPC copies per request.

> **Trap.** Linux's loadable modules do **not** make it a microkernel. A loaded module executes in
> kernel space with full privilege; the isolation of a microkernel is exactly what it lacks.

## The boot process

The path from power-on to a usable system is a hand-off through progressively more capable
software:

1. **Power-on and POST.** The CPU begins executing firmware (BIOS or UEFI) from a fixed ROM
   address; the firmware runs a **power-on self-test** to check hardware.
2. **Firmware to bootloader.** The firmware locates a bootable device and loads the bootloader —
   BIOS from the disk's master boot record, UEFI from an `.efi` file on a system partition.
3. **Bootloader (e.g. GRUB).** It loads the **kernel image** and an initial RAM filesystem into
   memory and jumps to the kernel's entry point; it may offer a menu of kernels/OSes.
4. **Kernel initialization.** The kernel sets up memory management and paging, initializes the
   scheduler and devices, and mounts the root filesystem.
5. **First user process.** The kernel starts **`init` / `systemd` as PID 1**, the ancestor of all
   later processes.
6. **Services and login.** `init` starts daemons and networking and brings up the login prompt or
   graphical session.

> **Interview.** *What is PID 1?* The first user-space process the kernel starts. It is the root of
> the process tree and adopts (and reaps) orphaned processes. *BIOS vs UEFI?* BIOS is the legacy
> 16-bit firmware that boots from an MBR (with a ~2 TB disk limit); UEFI is the modern replacement
> with GPT support, faster boot, a richer environment, and Secure Boot.

## Where services live

Knowing which components run privileged and which do not explains many design and security
questions.

- **Kernel space** — the process scheduler, memory manager, IPC primitives, file systems (and the
  virtual-filesystem layer), the network stack, and device drivers.
- **User space** — the windowing system, system libraries (`glibc`, `pthreads`), shells, daemons
  (`sshd`, `cron`, `systemd`), and all applications.

> **Interview.** *Why has a graphics-driver bug historically been able to blue-screen a machine?*
> Because drivers usually run in kernel space for speed, so a stray pointer there is a kernel fault,
> not a mere application crash. This is precisely the fragility microkernels trade performance to
> avoid.
