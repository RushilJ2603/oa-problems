# Process synchronization

## Independent and cooperative processes

Processes fall into two categories by how they interact:

- **Independent processes** neither affect nor are affected by other processes; they share no
  state.
- **Cooperative processes** do interact, because they **share** something. Synchronization is
  concerned exclusively with this second category.

What cooperative processes can share:

| Shared item | Examples |
|---|---|
| Variables | a common counter or flag |
| Memory | a shared memory region |
| Code | re-entrant routines used by several processes |
| Resources | CPU, printer, scanner |

> **Key point.** Sharing is the prerequisite for a synchronization problem. If processes are
> truly independent, their interleaving is irrelevant; the moment they share writable state,
> the *order* of their operations starts to matter.

## The race condition

A **race condition** arises when the final result of shared data depends on the precise
interleaving of operations from several processes — an order the programmer does not control.

**Setup.** A shared variable is initialized on a uniprocessor:

```c
int shared = 5;
```

Two cooperative processes each read it, modify a private copy, sleep, then write back:

```c
// Process P1
int x = shared;   // x = 5
x = x + 1;        // x = 6
sleep(1);
shared = x;       // shared = 6
```

```c
// Process P2
int y = shared;   // y = 5
y = y - 1;        // y = 4
sleep(1);
shared = y;       // shared = 4
```

**The expected result** is that one increment and one decrement cancel, leaving
`shared == 5`. But with the interleaving above, **both** processes read `shared` as 5
*before* either writes back (the `sleep` makes this overlap concrete). Each then overwrites
the variable from its own stale copy:

- if P1 writes last, `shared` ends at **6**;
- if P2 writes last, `shared` ends at **4**.

The outcome is non-deterministic — it "races" — and is wrong in both cases.

> **Definition — Race condition.** A situation in which two or more processes access shared
> data concurrently and the final value depends on the timing/order of their execution. The
> root cause here is that read–modify–write is not performed as one indivisible (atomic)
> step; preventing it requires controlling access to the shared section of code.

## The producer–consumer (bounded-buffer) problem

The canonical illustration of a race is the **bounded buffer**. A producer deposits items into a
shared buffer of `n` slots; a consumer removes them. A shared counter `count` tracks how many
slots are filled, and `in`/`out` index the next slot to fill/empty.

```c
// shared
int count = 0;              // filled slots
item buffer[n];             // n = 8 in the worked example
int in = 0, out = 0;

// Producer
while (true) {
    produce_item(itemP);
    while (count == n);     // buffer full — busy wait
    buffer[in] = itemP;
    in = (in + 1) % n;
    count = count + 1;
}

// Consumer
while (true) {
    while (count == 0);     // buffer empty — busy wait
    itemC = buffer[out];
    out = (out + 1) % n;
    count = count - 1;
    consume_item(itemC);
}
```

The bug hides in `count = count + 1` and `count = count - 1`. Each is really three machine
operations — **load** `count` into a register, **increment/decrement** the register, **store** it
back:

```text
Producer:  load  Rp, count      Consumer:  load  Rc, count
           incr  Rp                        decr  Rc
           store count, Rp                 store count, Rc
```

If the two interleave — producer loads (say `count`=3), consumer loads the same 3, each modifies
its own register, and they store in turn — one update is lost: `count` ends at 2 or 4 instead of 3.
The read–modify–write on `count` is not atomic.

> **Key point.** The producer's and consumer's updates to `count` form a critical section. The
> whole apparatus of the following sections — locks, test-and-set, semaphores — exists to make
> that update indivisible.

## The printer–spooler problem

The same non-atomic-index bug appears in printing. A **spooler directory** `SD` holds queued
files, and a shared variable `in` marks the next free slot. Each process that wants to print does:

```text
1. load  Ri, in              // read the shared next-free index
2. store SD[Ri], "file-name" // place this file in that slot
3. incr  Ri
4. store in, Ri              // write the index back
```

If two processes both read `in` as 3, both write their file into slot 3 (the second overwrites the
first) and both store `in = 4`. One print job silently vanishes even though `in` advanced only once.

> **Trap.** These problems look different (a counter, a print queue) but are the *same* defect: an
> unprotected read–modify–write on a shared index. Recognizing that shared-state signature is the
> first step in any concurrency question.

## The critical-section problem

> **Definition — Critical section.** The part of a program where shared resources are accessed.
> The goal of synchronization is to ensure that when one process is executing in its critical
> section, no other process is allowed to execute in its own.

Each process is structured as **entry section → critical section → exit section → remainder**:

```text
while (true) {
    /* entry section  */   // acquire permission
    /* critical section*/   // touch shared state
    /* exit section   */    // release permission
    /* remainder      */    // non-critical work
}
```

A correct solution must satisfy four requirements. The first two are the **primary** requirements;
the last two are **secondary**:

1. **Mutual exclusion** *(primary)* — at most one process in the critical section at a time.
2. **Progress** *(primary)* — if no process is in the critical section, a process that wants to
   enter must not be blocked by one that has no interest in entering; the decision cannot be
   postponed indefinitely.
3. **Bounded waiting** *(secondary)* — there is a limit on how many times other processes can enter
   ahead of a waiting process, so no one is starved.
4. **No assumption about hardware** *(secondary)* — correctness must not depend on the relative
   speed of processors or the number of CPUs.

## Software and hardware solutions

### Lock variable

The most obvious idea — a shared `LOCK` that is 1 when the critical section is busy — does *not*
work:

```text
1. while (LOCK == 1);   // entry: spin until free
2. LOCK = 1;
3. // critical section
4. LOCK = 0;            // exit
```

Two processes can both execute step 1 while `LOCK` is still 0, both find it free, and both set it
to 1 and enter. The test (step 1) and the set (step 2) are separate, non-atomic operations, so the
lock variable **fails mutual exclusion**.

### Test-and-set instruction

Hardware fixes this by making test-and-set a single atomic instruction: it reads the old value and
writes `TRUE` in one indivisible step.

```c
boolean test_and_set(boolean *target) {
    boolean r = *target;
    *target = TRUE;
    return r;
}

// entry: spin until test_and_set returns FALSE (lock was free)
while (test_and_set(&lock));
// critical section
lock = FALSE;   // exit
```

Because the read and write happen atomically, only one process can observe `lock` as `FALSE` and
enter — this **guarantees mutual exclusion**. (Compare-and-swap is the more general modern form of
the same idea.)

### Turn variable (strict alternation)

A pure-software two-process attempt uses a shared `turn`:

```c
int turn = 0;
// Process P0                 // Process P1
while (turn != 0);           while (turn != 1);
// critical section          // critical section
turn = 1;                    turn = 0;
```

This provides mutual exclusion, but it **violates progress**: the two processes must strictly
alternate. If P0 finishes and sets `turn = 1`, P0 cannot re-enter until P1 has taken its turn — even
if P1 is busy in its remainder and does not want the critical section. A process is blocked by one
that has no interest in entering.

> **Key point — Peterson's solution.** The correct two-process software solution combines the turn
> variable with a `flag[]` array of intent: a process sets `flag[self] = true`, sets `turn` to the
> *other* process, and waits only while the other both wants in and it is the other's turn. This
> satisfies all four requirements and is the standard software answer, though in practice hardware
> primitives and semaphores are used.

## Semaphores

> **Definition — Semaphore.** An integer variable, accessed only through two atomic operations
> **down** (also `P`, or *wait*) and **up** (also `V`, or *signal*), used by concurrent cooperative
> processes to achieve synchronization. A process that cannot proceed is put to sleep on a
> **suspended list** rather than busy-waiting.

### Counting semaphore

A counting semaphore ranges over all integers and is used to guard a pool of identical resources:

```text
down(S):                       up(S):
    S.value = S.value - 1;         S.value = S.value + 1;
    if (S.value < 0) {             if (S.value <= 0) {
        // block this process          // select a process from the
        // add to suspended list        // suspended list
        sleep();                        wakeup();
    }                              }
```

A negative `S.value` counts exactly how many processes are asleep waiting on the semaphore.

### Binary semaphore

A binary semaphore holds only 0 or 1 and is the natural mutual-exclusion lock:

```text
down(S):                         up(S):
    if (S.value == 1)                if (suspended list is empty)
        S.value = 0;                     S.value = 1;
    else {                           else {
        // block this process            // select a process from the
        // add to suspended list          // suspended list
        sleep();                         wakeup();
    }                                }
```

> **Trap — semaphore vs mutex.** A semaphore is a *signalling* device with no notion of an owner:
> any process may `up` it. A mutex is a *lock* with ownership — only the locker may unlock. A binary
> semaphore can serve as a mutex, but a mutex cannot provide a semaphore's cross-process signalling.

### A worked question: maximum processes in the critical section

Suppose `n` processes each execute the same code with a semaphore `mutex` initialized to 1:

```text
down(mutex);
// critical section
up(mutex);
```

**How many processes can be inside the critical section at once?** With `mutex = 1`, exactly the
first `down` succeeds (setting the value to 0); every other process blocks. So **at most one**
process is in the critical section — mutual exclusion holds. If `mutex` were instead initialized to
`k` (a counting semaphore), up to **k** processes could be inside simultaneously.

## Classic synchronization problems

### Producer–consumer with semaphores

Semaphores make the bounded buffer correct. Two counting semaphores track slots and one binary
semaphore `S` guards the buffer:

```text
empty = n;   // number of empty slots
full  = 0;   // number of filled slots
S     = 1;   // binary semaphore (mutual exclusion)

// Producer                      // Consumer
produce_item(itemP);             down(full);
down(empty);                     down(S);
down(S);                             itemC = buffer[out];
    buffer[in] = itemP;              out = (out + 1) % n;
    in = (in + 1) % n;           up(S);
up(S);                           up(empty);
up(full);                        consume_item(itemC);
```

`down(empty)` blocks the producer when the buffer is full; `down(full)` blocks the consumer when it
is empty; `S` ensures only one of them touches the buffer at a time.

> **Trap — ordering matters.** The mutex `down(S)` must come *after* the counting semaphore
> (`down(empty)` / `down(full)`), never before. If a process took `S` first and then blocked on a
> full/empty buffer, it would sleep while holding the mutex — and the process that could wake it can
> never acquire `S`. That is a classic **deadlock**.

### Readers–writers

Many readers may share a database concurrently, but a writer needs exclusive access. The conflict
table: **read–write, write–read, write–write are problems; read–read is not.** A reader count `rc`
is guarded by `mutex`, and `db` locks the database:

```text
int rc = 0;
mutex = 1;   // protects rc
db    = 1;   // database lock

// Reader                          // Writer
while (true) {                     while (true) {
    down(mutex);                       down(db);
        rc = rc + 1;                       // write to DB
        if (rc == 1) down(db);         up(db);
    up(mutex);                     }
    // read the database
    down(mutex);
        rc = rc - 1;
        if (rc == 0) up(db);
    up(mutex);
}
```

The **first** reader to arrive locks `db` (shutting out writers); the **last** reader to leave
releases it. Writers simply take `db` exclusively.

> **Trap — writer starvation.** This "readers-preference" version lets a continuous stream of
> readers keep `db` locked forever, starving writers. Fair variants give waiting writers priority.

### Dining philosophers

Five philosophers sit around a table with five forks between them; each needs its **left and right
fork** to eat. Model each fork as a semaphore `S[i]` initialized to 1:

```text
S[i] = 1 for i in 0..4;   // five fork semaphores

void philosopher(int i) {
    while (true) {
        think();
        wait(S[i]);              // take left fork
        wait(S[(i+1) % N]);      // take right fork
        eat();
        signal(S[i]);            // put down left fork
        signal(S[(i+1) % N]);    // put down right fork
    }
}
```

> **Trap — deadlock.** If every philosopher picks up their **left** fork at the same instant, all
> five forks are held and each waits forever for a right fork that its neighbour holds — a circular
> wait, i.e. deadlock. The standard fixes: (1) allow **at most four** philosophers at the table at
> once; (2) an **asymmetric** rule — odd philosophers take left-then-right, even take
> right-then-left; or (3) pick up both forks only if **both** are free (guarded by a mutex).

## The concurrency toolkit in practice

The lecture problems are solved with semaphores; production code and coding interviews use a
broader vocabulary built on the same ideas.

**Locks — mutex vs spinlock.** A **mutex** puts a blocked waiter to *sleep* (no wasted CPU, but a
context-switch/wakeup latency of roughly a microsecond or more). A **spinlock** *busy-waits* on an
atomic flag — near-zero acquire latency but every spinning cycle is burned. Spin only when the
critical section is shorter than a context switch (a rule of thumb of a few microseconds) or in a
context that cannot sleep (an interrupt handler); otherwise use a mutex. In user space a spinlock is
dangerous: if the lock holder is preempted, every spinner wastes a full time slice.

**Monitors and condition variables.** A **monitor** bundles shared data with a mutex and one or
more **condition variables**, guaranteeing only one thread is active inside at a time. A condition
variable lets a thread sleep until a predicate holds:

```cpp
lock(m);
while (!predicate) cond.wait(m);   // always a loop, never a bare if
// ... use the shared state ...
unlock(m);
```

> **Trap.** Always re-check the predicate in a `while` loop, never an `if`. A thread can wake
> **spuriously** (with no matching signal) or find the condition already consumed by another
> thread. `wait` atomically releases the mutex and re-acquires it on wake, closing the lost-wakeup
> race.

**Atomics, compare-and-swap, and the ABA problem.** Lock-free code relies on atomic
read-modify-write hardware instructions, chiefly **compare-and-swap**: `CAS(addr, expected, new)`
sets `*addr = new` only if `*addr == expected`. Because CAS checks *value*, not *history*, it is
vulnerable to the **ABA problem** — a location changes A→B→A, so a stale CAS succeeds as if nothing
happened. Fixes tag the pointer with a version counter, use load-linked/store-conditional, or defer
memory reclamation (hazard pointers).

**Memory ordering.** CPUs and compilers reorder memory operations, so one thread's writes can become
visible to another out of order. A **memory barrier** forbids reorderings; the acquire/release
pairing (write data, then `release`-store a flag; `acquire`-load the flag, then read the data) is
how a lock or semaphore also *publishes* memory. Note that `volatile` in C/C++ prevents compiler
caching but provides **no** atomicity or cross-thread ordering — use `std::atomic` instead.

**False sharing.** Two threads updating independent variables that happen to share one 64-byte cache
line force the line to bounce between cores on every write, silently serializing them. Pad or align
hot per-thread data to its own cache line.

**Deadlock, livelock, starvation in code.** Deadlock in code is almost always a **circular lock
order** (T1 holds A wants B; T2 holds B wants A). The first-line defence is a **global lock
ordering** — always acquire locks in the same fixed order. **Livelock** is threads endlessly
reacting to each other without progress (fix: randomized backoff); **starvation** is a thread never
getting the resource (fix: fairness/aging); **priority inversion** — a low-priority thread holding a
lock a high-priority thread needs — is solved by **priority inheritance**.

---
