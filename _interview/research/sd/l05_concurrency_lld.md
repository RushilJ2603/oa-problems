# L05 — Concurrency in LLD: thread-safety, locks, producer-consumer, thread-safe singleton

**Interview relevance:** High — LLD / machine-coding follow-ups and senior LLD rounds (parking lot double-book, logging, inventory, bounded queue, connection pool); Flipkart/Uber/Swiggy machine coding + FAANG/experienced “make it thread-safe”
**Type:** LLD-fundamental
**Prereqs:** L01 (OOP & SOLID), L02 (creational — especially Singleton); helpful after structural wrappers (L03) when Proxy/logging enters concurrent territory

## Read / watch (curated, in order)
- [ ] [Introduction to Concurrency (Hello Interview LLD)](https://www.hellointerview.com/learn/low-level-design/concurrency/intro) — `Hello Interview` — interview framing: correctness vs coordination vs scarcity; toolbox (locks, atomics, semaphores, blocking queues)
- [ ] [Concurrency in LLD Interviews (video)](https://www.youtube.com/watch?v=d8rmosXttTE) — `Hello Interview` — same three-category framework walked through with staff-engineer examples
- [ ] [Concurrency (Oracle Java Tutorials)](https://docs.oracle.com/javase/tutorial/essential/concurrency/) — `Oracle` — processes/threads → sync → high-level `java.util.concurrent`; language-truth baseline
- [ ] [Memory Consistency Errors](https://docs.oracle.com/javase/tutorial/essential/concurrency/memconsist.html) — `Oracle` — visibility (happens-before), not just mutual exclusion
- [ ] [Race Conditions and Critical Sections](https://algomaster.io/learn/concurrency-interview/race-conditions-and-critical-sections) — `AlgoMaster` / [awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) — check-then-act / read-modify-write in interview voice
- [ ] [Intrinsic Locks and Synchronization](https://docs.oracle.com/javase/tutorial/essential/concurrency/locksync.html) — `Oracle` — monitors, synchronized methods/blocks, fine-grained lock objects
- [ ] [Mutex (Mutual Exclusion)](https://algomaster.io/learn/concurrency-interview/mutex) — `AlgoMaster` — lock ownership, critical sections, why “check outside lock” fails
- [ ] [Lock Objects (`ReentrantLock`)](https://docs.oracle.com/javase/tutorial/essential/concurrency/newlocks.html) — `Oracle` — tryLock / interruptible acquire vs intrinsic locks
- [ ] [Synchronized vs ReentrantLock](https://algomaster.io/learn/concurrency-interview/java-synchronized-vs-reentrantlock) — `AlgoMaster` — when to leave `synchronized` for explicit locks + try-finally unlock
- [ ] [Coarse-grained vs Fine-grained Locking](https://algomaster.io/learn/concurrency-interview/coarse-vs-fine-grained-locking) — `AlgoMaster` — throughput vs deadlock risk; maps to Hello Interview “Correctness”
- [ ] [Correctness (Hello Interview)](https://www.hellointerview.com/learn/low-level-design/concurrency/correctness) — `Hello Interview` — seat-booking / inventory races; coarse vs fine locks, atomics, thread confinement
- [ ] [Guarded Blocks (wait/notify)](https://docs.oracle.com/javase/tutorial/essential/concurrency/guardmeth.html) — `Oracle` — condition waiting; always re-check in a `while` loop
- [ ] [Condition Variables](https://algomaster.io/learn/concurrency-interview/condition-variables) — `AlgoMaster` — wait/signal building block behind blocking queues
- [ ] [Producer-Consumer Pattern](https://algomaster.io/learn/concurrency-interview/producer-consumer-pattern) — `AlgoMaster` / awesome-LLD — classic handoff; bounded buffer + backpressure
- [ ] [Coordination (Hello Interview)](https://www.hellointerview.com/learn/low-level-design/concurrency/coordination) — `Hello Interview` — producer → queue → workers; efficient wait + backpressure vs OOM
- [ ] [Concurrent Collections / BlockingQueue](https://docs.oracle.com/javase/tutorial/essential/concurrency/collections.html) — `Oracle` — prefer `BlockingQueue` over hand-rolled wait/notify for P-C
- [ ] [BlockingQueue (Java SE API)](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/concurrent/BlockingQueue.html) — `JDK` — `put`/`take` contract; multi-producer / multi-consumer safe
- [ ] [Producer-Consumer Problem (Baeldung)](https://www.baeldung.com/java-producer-consumer-problem) — `Baeldung` — wait/notify version then simplify with `BlockingQueue`
- [ ] [Guide to BlockingQueue (Baeldung)](https://www.baeldung.com/java-blocking-queue) — `Baeldung` — capacity, poison-pill shutdown, producer/consumer wiring
- [ ] [Design Thread-Safe Blocking Queue](https://algomaster.io/learn/concurrency-interview/design-thread-safe-blocking-queue) — `AlgoMaster` — drill: implement bounded queue yourself (locks + conditions)
- [ ] [Deadlock](https://docs.oracle.com/javase/tutorial/essential/concurrency/deadlock.html) — `Oracle` — circular wait; pair with [AlgoMaster deadlock](https://algomaster.io/learn/concurrency-interview/deadlock)
- [ ] [Atomic Variables](https://docs.oracle.com/javase/tutorial/essential/concurrency/atomicvars.html) — `Oracle` — `AtomicInteger` / CAS for single-variable RMW without coarse locks
- [ ] [Scarcity (Hello Interview)](https://www.hellointerview.com/learn/low-level-design/concurrency/scarcity) — `Hello Interview` — connection pools, semaphores, “what when N resources run out”
- [ ] [Semaphores](https://algomaster.io/learn/concurrency-interview/semaphores) — `AlgoMaster` — permits for rate/concurrency limits (scarce resource)
- [ ] [Thread Pool Pattern](https://algomaster.io/learn/concurrency-interview/thread-pool-pattern) — `AlgoMaster` — reuse workers; bounded queue + rejection as backpressure
- [ ] [Singleton (Refactoring.Guru)](https://refactoring.guru/design-patterns/singleton) — `Refactoring.Guru` — intent + multithreaded double-check sketch; cons (SRP, testability)
- [ ] [Thread-safe Singleton (Java example)](https://refactoring.guru/design-patterns/singleton/java/example) — `Refactoring.Guru` — volatile + DCL with local `result`; links [Java DCL caveat](https://refactoring.guru/java-dcl-issue)
- [ ] [Singleton (AlgoMaster LLD)](https://algomaster.io/learn/lld/singleton) — `AlgoMaster` / awesome-LLD — lazy → synchronized → DCL → eager → Bill Pugh holder → **enum**
- [ ] [Thread-Safe Singleton in Java (Baeldung)](https://www.baeldung.com/java-implement-thread-safe-singleton) — `Baeldung` — compare synchronized accessor, DCL+`volatile`, holder, enum
- [ ] [Java Singleton Best Practices (DigitalOcean)](https://www.digitalocean.com/community/tutorials/java-singleton-design-pattern-best-practices-examples) — `DigitalOcean` — holder vs enum recommendation; when synchronized is “good enough”
- [ ] [“Double-Checked Locking is Broken” (historical)](https://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html) — `reference` — why pre-Java-5 DCL failed; today: `volatile` or prefer holder/enum
- [ ] [Logging Framework (thread-safe LLD problem)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/logging-framework.md) — `awesome-low-level-design` — Singleton logger + concurrent writers as applied drill
- [ ] [awesome-low-level-design — Concurrency hub](https://github.com/ashishps1/awesome-low-level-design) — `awesome-low-level-design` — full concurrency concept + problem list (FooBar, H2O, ConcurrentHashMap, …)
- [ ] [Master Concurrency Interviews (AlgoMaster index)](https://algomaster.io/learn/concurrency-interview) — `AlgoMaster` — course index once fundamentals stick
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra LLD/MC problem index to re-ask “where are the races?”

## Core concepts to master
- **Thread-safety** = correct results under concurrent access: no lost updates, no torn reads, and **visibility** of writes across threads (happens-before), not only “I used a lock somewhere.”
- **Race / critical section:** shared mutable state + overlapping read-modify-write or check-then-act (two threads both see “spot free” / “qty=1” and both commit). Fix by making the check+act **atomic** under one lock (or one atomic op).
- **Locks (mutex / synchronized / ReentrantLock):** mutual exclusion for multi-field invariants. Prefer **smallest** critical section that still keeps the invariant; coarse lock = simpler + less parallelism; fine-grained = more throughput + deadlock risk.
- **Condition waiting:** `wait`/`notify` or `Condition.await`/`signal` — always wait in a **`while` (not `if`)** re-checking the predicate (spurious wakeups / lost notify). Prefer `BlockingQueue` over hand-rolling for producer-consumer.
- **Producer-consumer:** producers put work into a buffer; consumers take. **Bounded** queue gives **backpressure** (producer blocks when full) and prevents unbounded memory growth; empty → consumer blocks efficiently (no busy-spin).
- **`BlockingQueue`:** interview default for coordination (`put`/`take`). Multi-producer/multi-consumer is supported; shut down with poison pills or interrupt + `shutdownNow`.
- **Deadlock:** circular wait on locks — prevent with consistent lock order, tryLock+backoff, or fewer locks. Know starvation/livelock as “progress” cousins.
- **Atomics / CAS:** good for single counters/flags; **not** enough when two fields must change together (need a lock or redesign).
- **Thread-safe Singleton (Java checklist):** naive lazy (broken) → `synchronized getInstance` → DCL + **`volatile`** → Bill Pugh static holder → **enum Singleton** (serialization/reflection-safe). Eager init is fine if always needed. Prefer DI/shared instance unless truly process-global.
- **Interview map (Hello Interview):** diagnose first — **Correctness** (locks/atomics) → **Coordination** (blocking queue / P-C) → **Scarcity** (semaphore / pool). Don’t reach for a thread pool before the shared-state race is fixed.

## Practice — how it's asked & how to attack it
1. **Drill — name the failure:** For each snippet, say correctness / coordination / scarcity and the primitive you’d use: (a) two parkers grab one spot, (b) API threads hand jobs to workers, (c) at most 5 DB connections.
2. **Drill — check-then-act fix:** Write `park(vehicle)` that findSpot + occupy under one lock (or CAS on spot state). Explain why synchronizing only `findSpot` still races.
3. **Drill — bounded producer-consumer:** Implement a fixed-capacity buffer with `ReentrantLock` + two `Condition`s (`notFull`/`notEmpty`), then rewrite using `ArrayBlockingQueue`. State what changes for N producers / M consumers.
4. **Drill — thread-safe Singleton whiteboard:** Sketch broken lazy → synchronized → DCL+`volatile` → Bill Pugh → enum. State one testing downside of Singleton and the DI alternative.
5. **Drill — logging / cache:** Take [Logging Framework](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/logging-framework.md) or “thread-safe cache with TTL”: where is the lock? Can you use `ConcurrentHashMap`? What must stay atomic (record write vs map put)?
6. **Drill — deadlock hunt:** Two accounts `transfer(A→B)` locking both accounts; show reverse-order deadlock; fix with ordered lock IDs or tryLock timeout.

## Common follow-ups / gotchas
- “Is `volatile` enough?” — Gives **visibility** for a single field, not atomic check-then-act on compound state. DCL needs `volatile` so you don’t publish a half-constructed Singleton.
- “Why `while` not `if` around `wait`?” — Spurious wakeups and multiple waiters; always re-test the condition after waking.
- “Synchronize the whole class?” — Works but kills concurrency; interviewers want you to lock the **shared resource** (spot map, inventory row), not every unrelated method.
- “Unbounded queue OK?” — Coordination without backpressure → memory blow-up under burst; prefer capacity + block/reject.
- “Is Singleton automatically thread-safe?” — Only the **instance creation** story; methods that mutate shared fields still need their own synchronization.
- “Can ConcurrentHashMap replace all locks?” — Great for independent key ops; **multi-key** invariants (transfer between two keys, check-then-put-if-absent across structures) still need external coordination.

## Where it appears
- **Campus / machine coding (India product cos):** often optional until the happy path works — then “make parking / booking / logging thread-safe”; Flipkart, Uber, Swiggy, Amazon loops commonly add this as a follow-up.
- **Experienced / SDE-2+ LLD:** concurrency is in-scope from the start (rate limiter, connection pool, scheduler, bounded queue, concurrent cache); Hello Interview–style correctness/coordination/scarcity language scores well.
- **Frequency:** nearly every shared-mutable LLD design gets a concurrency probe at mid-level; explicit “design a blocking queue / thread pool” prompts are common at product cos and FAANG-adjacent loops once OOP/patterns are assumed.
