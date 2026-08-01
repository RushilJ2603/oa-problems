# H06 — Consistency models, CAP, PACELC, ACID vs BASE, transactions, isolation levels

**Interview relevance:** High — almost every HLD "design X" round probes C vs A tradeoffs, when to use strong vs eventual consistency, and ACID/isolation for money/inventory paths (campus + experienced; FAANG and Indian product cos).
**Type:** HLD-foundation
**Prereqs:** h01_networking, h02_load_balancing; databases / replication foundations (earlier HLD DB modules in this sheet)

## Read / watch (curated, in order)
- [ ] [system-design-primer — CAP theorem](https://github.com/donnemartin/system-design-primer#cap-theorem) — `primer` — C/A/P definitions; CP vs AP under partition; then [Consistency patterns](https://github.com/donnemartin/system-design-primer#consistency-patterns) (weak / eventual / strong) and [ACID](https://github.com/donnemartin/system-design-primer#acid) / [BASE](https://github.com/donnemartin/system-design-primer#base)
- [ ] [CAP Theorem Simplified](https://www.youtube.com/watch?v=BHqjEjzAicA) — `ByteByteGo` — ~5 min: partition forces C vs A; why “pick 2 of 3” is messy; tees up PACELC (latency vs consistency when healthy)
- [ ] [CAP Theorem: One of the Most Misunderstood Terms](https://bytebytego.com/guides/cap-theorem-one-of-the-most-misunderstood-terms/) — `ByteByteGo` — same ideas in text; warns against labeling a DB “CP/AP” as the whole story
- [ ] [CAP Theorem (Hello Interview)](https://www.hellointerview.com/learn/system-design/core-concepts/cap-theorem) — `Hello Interview` — interview framing: pick C vs A per *feature*; strong / causal / read-your-writes / eventual spectrum with booking vs social examples
- [ ] [Data Consistency and Tradeoffs in Distributed Systems](https://www.youtube.com/watch?v=m4q7VkgDWrM) — `Gaurav Sen` — sync vs eventual consistency, acknowledgements / 2PC cost, why many systems choose eventual
- [ ] [CAP Twelve Years Later: How the "Rules" Have Changed](https://www.infoq.com/articles/cap-twelve-years-later-how-the-rules-have-changed/) — `Brewer (InfoQ)` — partitions are rare but real; latency and “partial” C/A matter more than cartoon CAP triangles
- [ ] [Please stop calling databases CP or AP](https://martin.kleppmann.com/2015/05/11/please-stop-calling-databases-cp-or-ap.html) — `DDIA` author — why shoehorning Mongo/Cassandra/ZooKeeper into one CAP letter is wrong; reason per operation / failure mode
- [ ] [PACELC (Abadi)](https://www.cs.umd.edu/~abadi/papers/abadi-pacelc.pdf) — `Abadi` — if Partition → A vs C; Else → Latency vs Consistency; the tradeoff that shows up *most of the time*
- [ ] [What does ACID mean?](https://bytebytego.com/guides/what-does-acid-mean) — `ByteByteGo` — A/C/I/D for transactions; explicitly separates ACID “C” (invariants) from CAP “C” (linearizable recency). Pair with [ACID Properties in Databases With Examples](https://www.youtube.com/watch?v=GAe5oB742dw)
- [ ] [What are database isolation levels (Episode 8)](https://blog.bytebytego.com/p/what-are-database-isolation-levels) — `ByteByteGo` — Read Uncommitted → Serializable; dirty / non-repeatable / phantom; MVCC sketch
- [ ] [PostgreSQL — Transaction Isolation](https://www.postgresql.org/docs/current/transaction-iso.html) — `PostgreSQL docs` — what Read Committed / Repeatable Read / Serializable actually mean in a real engine (defaults + SSI)
- [ ] *Designing Data-Intensive Applications* ch.7 (Transactions) — `DDIA ch.7` — ACID, weak isolation, snapshot isolation, write skew, serializability ([book site](https://dataintensive.net/); [free notes](https://timilearning.com/posts/ddia/part-two/chapter-7/))
- [ ] *DDIA* ch.9 (Consistency and Consensus) — `DDIA ch.9` — linearizability vs serializability, causal consistency, 2PC ([free notes part 1](https://timilearning.com/posts/ddia/part-two/chapter-9-1/) / [part 2](https://timilearning.com/posts/ddia/part-two/chapter-9-2/)); skim only — not Raft proofs
- [ ] [Jepsen — Consistency models](https://jepsen.io/consistency) — `Jepsen` — visual map of models (linearizability, serializability, etc.); use as a glossary, not a deep-dive
- [ ] [Introduction to NoSQL databases](https://www.youtube.com/watch?v=xQnIN9bW0og) — `Gaurav Sen` — why NoSQL often picks availability / BASE-style eventual consistency
- [ ] [CAP, PACELC, ACID, BASE — Essential Concepts](https://blog.bytebytego.com/p/cap-pacelc-acid-base-essential-concepts) — `ByteByteGo` — single recap article tying all four acronyms (newsletter; may be paywalled — skip if blocked)

## Core concepts to master
- **CAP (interview form):** in a distributed store, network **partitions happen**; under a partition you must choose **Consistency** (every read sees latest write or errors) vs **Availability** (every non-failed node answers, maybe stale). “CA without P” is not a real distributed design.
- **CAP “C” ≠ ACID “C”:** CAP consistency ≈ **linearizability / single-copy** recency. ACID consistency = **preserve application invariants** (constraints, balances ≥ 0). Never conflate them in an interview.
- **Don’t label whole DBs “CP/AP”:** real systems mix modes (strong write path, stale secondary reads, per-table settings). Prefer: “for *this API*, under *this failure*, we choose …”.
- **PACELC:** if **P**artition → **A** vs **C**; **E**lse (normal) → **L**atency vs **C**. Most of the time there is no partition — sync replication buys stronger C at higher latency.
- **Consistency spectrum (replicas):** **strong / linearizable** (read always latest) → **causal** (cause before effect) → **read-your-writes / session** → **eventual** (replicas converge if writes stop). Pick per data item / API, not per company slogan.
- **ACID transactions:** **Atomic** all-or-nothing; **Consistent** invariants; **Isolated** concurrent txns; **Durable** after commit. Needed for money moves, inventory decrement, seat booking.
- **BASE (contrast, not a theorem):** Basically Available, Soft state, Eventually consistent — favors availability / scale; app must tolerate temporary divergence and design compensating logic.
- **Isolation levels (weak → strong):** Read Uncommitted → Read Committed → Repeatable Read / Snapshot → Serializable. Phenomena: dirty read, non-repeatable read, phantom, **write skew** (classic SI hole — two doctors both go off-call).
- **Linearizability vs serializability:** linearizability = single-object real-time order; serializability = multi-object txn order *as if* one-at-a-time. You can have one without the other; **strict serializability** is both.
- **2PC / distributed txns:** atomic commit across nodes; coordinator failure can block. Interview default: prefer **single-partition ACID** or **saga / outbox** over cross-shard 2PC unless you truly need it.
- **Design rule of thumb:** money / inventory / unique booking → strong C + careful isolation; feeds, counts, profiles, CDN/DNS-like data → availability + eventual (plus read-your-writes where UX demands it).

## Practice — how it's asked & how to attack it
Self-test drills (≤2 min aloud each):

1. **CAP pick per feature:** For a ticket marketplace, classify {browse event page, reserve seat, pay, “popularity” counter} as CP-leaning vs AP-leaning. What does the user see on partition for each?
2. **PACELC normal path:** Primary–replica Postgres with async replicas vs sync quorum. Under *no* partition, what did you trade (L vs C)? When would a stale read replica be wrong for checkout?
3. **ACID “C” vs CAP “C”:** Transfer ₹100 A→B. Explain Atomicity and Durability; explain which “consistency” is invariants vs replica recency; what fails if isolation is only Read Committed?
4. **Isolation anomalies:** Sketch dirty read, non-repeatable read, phantom, write skew with concrete rows. Which level (or SSI) stops write skew? What does Postgres default give you?
5. **Consistency spectrum:** Instagram-like profile pic update — argue for read-your-writes for the writer, eventual for others. When would causal consistency matter for comments-on-posts?
6. **Distributed money without 2PC:** Two services (wallet, ledger). Outline saga / outbox + idempotency instead of XA/2PC; name one failure mode you must handle (at-least-once duplicate).

## Common follow-ups / gotchas
- “Is Cassandra AP and Postgres CP?” — too coarse; ask which operation, which consistency setting, which failure (node vs datacenter partition).
- Eventual consistency ≠ “incorrect forever” — it means replicas **converge**; you still need conflict resolution (LWW, version vectors, app merges).
- Strong consistency has a **latency tax** even when the network is healthy (PACELC’s ELC) — sync replication / quorum R+W>N.
- Default isolation is often **not** Serializable (Postgres Read Committed; MySQL InnoDB often Repeatable Read) — race bugs hide until load.
- Read replicas are **eventually consistent** by default — never serve checkout/balance from a lagging replica without sticky/primary reads.
- CAP does not say you can’t be “mostly consistent and mostly available”; it forbids *perfect* C and *perfect* A during a partition.

## Where it appears
- **Campus / new-grad HLD:** explicit “CAP?” or “strong vs eventual?” on URL shortener, news feed, chat, e-commerce — expected vocabulary; depth on isolation separates strong candidates.
- **Experienced / mid-level (1–4+ YOE):** per-API consistency, PACELC latency tradeoffs, isolation anomalies (lost update / write skew), saga vs 2PC — common at Amazon, Google, Meta, Uber, Atlassian, Flipkart, payments-heavy loops.
- **Frequency:** near-universal foundation; every design that replicates or takes money/inventory will probe these tradeoffs.
