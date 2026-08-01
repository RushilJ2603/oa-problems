# Deadlocks

## What a deadlock is

> **Definition — Deadlock.** A situation in which a set of processes is permanently blocked, each
> waiting for a resource that another process in the set holds. Because the awaited event (a
> resource release) can never happen, none of them can ever proceed.

A deadlock requires **four conditions to hold simultaneously** (the Coffman conditions). All four
are necessary; breaking any one makes deadlock impossible.

1. **Mutual exclusion** — at least one resource is held in a non-shareable mode; only one process
   can use it at a time.
2. **Hold and wait** — a process holds at least one resource while waiting to acquire others.
3. **No preemption** — a resource cannot be forcibly taken from a process; it must be released
   voluntarily.
4. **Circular wait** — there is a cycle of processes $P_0, P_1, \ldots, P_n, P_0$ in which each
   waits for a resource held by the next.

> **Trap.** Deadlock, starvation, and livelock are different. *Deadlock* is a permanent circular
> block. *Starvation* is a process that could run being indefinitely denied a resource (e.g. a
> low-priority job under a stream of high-priority ones). *Livelock* is processes actively changing
> state in response to each other yet making no progress.

## Resource-allocation graphs

A **resource-allocation graph (RAG)** models the system as a directed graph. Processes are drawn as
circles and resource types as boxes (with a dot per instance). A **request edge** runs from a
process to a resource; an **assignment edge** runs from a resource instance to a process.

### Single-instance resources

When every resource type has exactly one instance, the graph tells the whole story:

> **Key point.** With single-instance resources, **a cycle in the RAG is both necessary and
> sufficient for deadlock** — a cycle means deadlock, no cycle means no deadlock.

For example, if $P_1$ holds $R_1$ and requests $R_2$, while $P_2$ holds $R_2$ and requests $R_1$,
the two request/assignment edges form a cycle $P_1 \to R_2 \to P_2 \to R_1 \to P_1$: a deadlock.

### Multiple-instance resources

When a resource type has several instances, a cycle is only a *warning*:

> **Key point.** With multiple-instance resources, **a cycle is necessary but not sufficient**. A
> cycle *may* be a deadlock, or another process holding an instance of a resource in the cycle may
> release it and break the wait. To decide, you must run the detection/safety algorithm on the
> allocation and request matrices — the graph alone is inconclusive.

## Handling deadlocks

There are four strategies, from doing nothing to full detection:

- **Deadlock ignorance (the Ostrich algorithm)** — pretend deadlocks never happen; if the system
  hangs, reboot. Because deadlocks are rare, this is what most general-purpose operating systems
  (Linux, Windows) actually do — the cost of prevention is not worth paying continuously.
- **Deadlock prevention** — design the system so that one of the four necessary conditions can
  never hold.
- **Deadlock avoidance** — allow the conditions but never grant a request that could lead to
  deadlock, using advance knowledge of maximum needs (the Banker's algorithm).
- **Deadlock detection and recovery** — let deadlocks happen, detect them, then recover.

## Deadlock prevention

Prevention attacks the four conditions directly:

| Condition | How to break it | Cost |
|---|---|---|
| Mutual exclusion | Make resources shareable (e.g. read-only, or spooling) where possible | Not all resources can be shared |
| Hold and wait | Require a process to request *all* resources at once, up front | Low utilization; starvation |
| No preemption | Allow the OS to preempt a resource (take it back) | Only works for saveable state (CPU, memory), not printers |
| Circular wait | Impose a **global ordering** on resource types; a process may only request resources in increasing order | The most practical rule — used in real lock-ordering disciplines |

> **Key point.** Breaking **circular wait** with a global resource ordering is the technique that
> carries straight into code: always acquire locks in the same fixed order and a cyclic wait — and
> thus deadlock — becomes impossible.

## Deadlock avoidance: the Banker's algorithm

Avoidance keeps the system in a **safe state**: one for which there exists an ordering of all
processes — a **safe sequence** — such that each can obtain its maximum needs, run, and release,
using only the resources currently available plus those freed by earlier processes in the sequence.
A request is granted only if the resulting state is still safe. An **unsafe** state is not
necessarily deadlocked, but it *may* lead to deadlock, so avoidance refuses to enter it.

Each process declares its **maximum** claim in advance. The **remaining need** is
$\text{Need} = \text{Max} - \text{Allocation}$.

**Worked example.** Three resource types with totals $A=10,\ B=5,\ C=7$:

| Process | Allocation (A B C) | Max (A B C) | Need = Max − Alloc (A B C) |
|---|---|---|---|
| P1 | 0 1 0 | 7 5 3 | 7 4 3 |
| P2 | 2 0 0 | 3 2 2 | 1 2 2 |
| P3 | 3 0 2 | 9 0 2 | 6 0 0 |
| P4 | 2 1 1 | 4 2 2 | 2 1 1 |
| P5 | 0 0 2 | 5 3 3 | 5 3 1 |

Total allocated is $\langle 7,2,5\rangle$, so the currently **Available** vector is
$\langle 10,5,7\rangle - \langle 7,2,5\rangle = \langle 3,3,2\rangle$.

**The safety algorithm.** Repeatedly find a process whose `Need ≤ Available`; "run" it (it can
finish), then return its allocation to `Available`. If all processes can be finished this way, the
state is safe.

| Step | Process run (Need ≤ Available?) | Available after it releases |
|---|---|---|
| start | — | 3 3 2 |
| 1 | P2 (1 2 2 ≤ 3 3 2 ✓) | 3 3 2 + 2 0 0 = **5 3 2** |
| 2 | P4 (2 1 1 ≤ 5 3 2 ✓) | 5 3 2 + 2 1 1 = **7 4 3** |
| 3 | P5 (5 3 1 ≤ 7 4 3 ✓) | 7 4 3 + 0 0 2 = **7 4 5** |
| 4 | P1 (7 4 3 ≤ 7 4 5 ✓) | 7 4 5 + 0 1 0 = **7 5 5** |
| 5 | P3 (6 0 0 ≤ 7 5 5 ✓) | 7 5 5 + 3 0 2 = **10 5 7** |

Every process finished, so the state is **safe**, with **safe sequence
$\langle P_2, P_4, P_5, P_1, P_3\rangle$**. (Other safe sequences may also exist.)

### Checking whether a given ordering is safe

Assessments often ask the inverse: *"which of these orderings is **not** a safe sequence?"* The
method is the same simulation, applied to the given order — walk it left to right, and at each
process check `Need ≤ current Available`; if it holds, add that process's allocation back and
continue. The ordering is **unsafe the moment some process's Need exceeds the Available** at its
turn.

In the example above, any sequence that **starts with P1** is not safe: P1's need $\langle
7,4,3\rangle$ already exceeds the initial Available $\langle 3,3,2\rangle$, so P1 cannot begin, and
nothing has yet been released to help it.

> **Trap.** "Is X a safe sequence?" is a **simulation**, not a formula — run the Available vector
> forward through the ordering. If a fresh request is granted first (as in the Cisco template where
> a process's request is granted before testing), subtract it from Available and add it to that
> process's allocation *before* you start walking.

## Detection and recovery

If a system neither prevents nor avoids deadlock, it can run a **detection** algorithm (essentially
the safety algorithm using current requests instead of maximum needs) periodically or when
utilization drops. On finding a deadlock it **recovers** by either:

- **Process termination** — abort all deadlocked processes, or abort them one at a time until the
  cycle breaks (choosing victims by priority, progress, or resources held); or
- **Resource preemption** — take a resource from a process and give it to another, rolling the
  victim back to a safe checkpoint (raising the risk of starvation if the same process is always
  chosen).

## How many resources guarantee no deadlock

A classic exam template asks for the resource count that makes deadlock impossible. Suppose there
are $n$ processes $P_1,\ldots,P_n$ competing for a single resource type, where $P_i$ needs a maximum
of $d_i$ units. The worst case just short of everyone finishing is each process holding one less
than it needs, i.e. $d_i - 1$ units — a total of $\sum (d_i - 1)$ units all tied up. One more unit
then lets some process reach its maximum, finish, and release. Hence:

$$\text{Deadlock is possible} \iff R \le \sum_{i=1}^{n} d_i - n, \qquad
\text{Deadlock-free} \iff R \ge \sum_{i=1}^{n}(d_i - 1) + 1 = \sum_{i=1}^{n} d_i - n + 1.$$

When every process needs the same maximum $k$, this reduces to the well-known form
$R \ge n(k-1) + 1$.

**Worked checks.**

- *Three processes, each needing 2 units — minimum units of $R$ so no deadlock can occur?* Here
  $n=3,\ d_i=2$: deadlock-free needs $R \ge 3(2-1)+1 = 4$. So **4** units suffice (with 3, each
  could hold 1 and wait forever).
- *A system has 4 instances shared by 3 processes; the largest maximum request $k$ that always
  avoids deadlock?* Solve $4 \ge 3(k-1)+1 \Rightarrow k-1 \le 1 \Rightarrow k \le 2$. So the largest
  safe value is **$k = 2$**.

---
