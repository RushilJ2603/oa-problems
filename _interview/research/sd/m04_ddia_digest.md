# M04 — DDIA chapter-by-chapter digest (interview lens)

**Interview relevance:** High — the tradeoff vocabulary interviewers expect in HLD deep dives (replication lag, isolation, partitioning, consistency); FAANG + Indian product cos (Atlassian, Uber, Flipkart, etc.). Not a substitute for timed design practice.
**Type:** resource-meta
**Prereqs:** HLD framework (M01). Read selectively while doing foundations H01–H16 and `hq*` designs — do **not** finish all 12 chapters before practicing. Pair: ch.5↔H05/H06, ch.6↔H05, ch.7↔H04/payments, ch.8–9↔H07/H16, ch.11↔H08.

## Read / watch (curated, in order)
- [ ] [DDIA — book home](https://dataintensive.net/) — `DDIA` — official hub; buy links + what the book is for (tradeoffs, not tool tutorials)
- [ ] [Where to buy DDIA](https://dataintensive.net/buy.html) — `DDIA` — print/ebook retailers (incl. Amazon.in / Flipkart for India)
- [ ] [Amazon — DDIA (print, ISBN 1449373321)](https://www.amazon.com/Designing-Data-Intensive-Applications-Reliable-Maintainable/dp/1449373321) — `O'Reilly` / Kleppmann — 1st ed. is what most free chapter notes follow; a 2nd ed. exists (cloud/AI storage updates) — buy via [dataintensive.net/buy](https://dataintensive.net/buy.html)
- [ ] [DDIA study guide — interview chapter priorities](https://sd.dosibridge.com/resources/designing-data-intensive-apps/) — `resource` — focus **ch.5–9** for interviews; skim Part I; Part III as needed for queues/ETL
- [ ] [Chapter-by-chapter summary (backend / SD lens)](https://quyennv.com/blog/designing-data-intensive-applications-summary/) — `notes` — full Part I–III digest before or alongside the book
- [ ] [Learning diary index (free notes, ch.1–9)](https://timilearning.com/posts/ddia/notes/) — `timilearning` — best free chapter notes used across this sheet; Part III not covered here
- [ ] [Ch.1 — Reliable, Scalable, Maintainable](https://timilearning.com/posts/ddia/part-one/chapter-1/) — `DDIA ch.1` — reliability vs scalability vs maintainability; **load parameters**; **p50/p95/p99** (not averages); Twitter fan-out case
- [ ] [Ch.2 — Data Models and Query Languages](https://timilearning.com/posts/ddia/part-one/chapter-2/) — `DDIA ch.2` — relational vs document vs graph; declarative SQL vs MapReduce-style; pick model for access patterns
- [ ] [Ch.3 — Storage and Retrieval](https://timilearning.com/posts/ddia/part-one/chapter-3/) — `DDIA ch.3` — LSM/SSTables vs B-trees; OLTP vs OLAP; column stores — why write-heavy vs read-heavy DBs differ ([alt notes](https://notes.shichao.io/dda/ch3/))
- [ ] [Ch.4 — Encoding and Evolution](https://timilearning.com/posts/ddia/part-one/chapter-4/) — `DDIA ch.4` — JSON vs Avro/Protobuf/Thrift; backward/forward compat; REST vs RPC; schemas as contracts
- [ ] [Ch.5 — Replication](https://timilearning.com/posts/ddia/part-two/chapter-5/) — `DDIA ch.5` — **interview core:** single-/multi-leader / leaderless; sync vs async; read-your-writes, monotonic reads, prefix; quorums N/R/W
- [ ] [Ch.6 — Partitioning](https://timilearning.com/posts/ddia/part-two/chapter-6/) — `DDIA ch.6` — **interview core:** key-range vs hash; hot spots; local vs global secondary indexes; rebalancing; “consistent hashing” naming caveat
- [ ] [Ch.7 — Transactions](https://timilearning.com/posts/ddia/part-two/chapter-7/) — `DDIA ch.7` — ACID (C is app invariant); isolation levels; lost update / write skew / phantoms; 2PL vs SSI — money & booking deep dives
- [ ] [Ch.8 — The Trouble with Distributed Systems](https://timilearning.com/posts/ddia/part-two/chapter-8/) — `DDIA ch.8` — partial failure; timeouts ≠ certainty; clocks drift; GC pauses; fencing tokens
- [ ] [Ch.9 — Consistency and Consensus (1/2)](https://timilearning.com/posts/ddia/part-two/chapter-9-1/) — `DDIA ch.9` — linearizability vs weaker models; CAP misuse; when you actually need strong consistency
- [ ] [Ch.9 — Consistency and Consensus (2/2)](https://timilearning.com/posts/ddia/part-two/chapter-9-2/) — `DDIA ch.9` — total-order broadcast; 2PC pain; Raft/Paxos at interview depth; ZooKeeper/etcd as coordination
- [ ] [Book notes (dense, all 12 chapters)](https://danlebrero.com/2021/09/01/designing-data-intensive-applications-summary/) — `notes` — Part III (batch/stream/future) + punchy ch.5–9 callouts when timilearning stops
- [ ] [GitHub notes — all chapters (incl. 10–12)](https://github.com/ahmedhammad97/Designing-Data-Intensive-Applications-Notes) — `notes` — one-page lookup for batch, streams, derived-data / unbundling DB
- [ ] [Please stop calling databases CP or AP](https://martin.kleppmann.com/2015/05/11/please-stop-calling-databases-cp-or-ap.html) — `DDIA author` — classic CAP follow-up trap; reason per operation / failure mode
- [ ] [How to do distributed locking](https://martin.kleppmann.com/2016/02/08/how-to-do-distributed-locking.html) — `DDIA author` — Redlock critique; **fencing tokens**; DB/conditional write as truth (booking / seats)
- [ ] [Distributed Systems lecture series (YouTube)](https://www.youtube.com/playlist?list=PLeKd45zvjcDFUEv_ohr_HdUFe97RItdiB) — `DDIA author` / Cambridge — free companion (~7h); start [1.1 Introduction](https://www.youtube.com/watch?v=UEAMfLPZZhE); Raft deep dive [6.2](https://www.youtube.com/watch?v=uXEYuDwm7e4)
- [ ] [Course materials + lecture notes (PDF)](https://www.cl.cam.ac.uk/teaching/2122/ConcDisSys/materials.html) — `Cambridge` — slides + [dist-sys notes PDF](https://www.cl.cam.ac.uk/teaching/2122/ConcDisSys/dist-sys-notes.pdf); author announcement: [blog post](https://martin.kleppmann.com/2020/11/18/distributed-systems-and-elliptic-curves.html)
- [ ] [DDIA chapter maps poster](https://dataintensive.net/poster.html) — `DDIA` — visual TOC of approaches per chapter (free JPG for personal use)
- [ ] [system-design-primer](https://github.com/donnemartin/system-design-primer) — `primer` — after DDIA concepts, drill building blocks + worked designs so theory turns into diagrams

## Core concepts to master
- **Ch.1 — NFR language:** reliability (fault ≠ failure), scalability (name **load parameters**), maintainability (operability / simplicity / evolvability). Quote **percentiles**, never “average latency”.
- **Ch.2 — Model fits access pattern:** relational (joins / many-to-many), document (locality / hierarchy), graph (highly connected). Wrong model ⇒ you fight the DB forever.
- **Ch.3 — Storage engines drive perf stories:** LSM (write-optimized, compaction, bloom filters) vs B-tree (read-friendly pages + WAL). OLTP row store vs OLAP column store.
- **Ch.4 — Evolution / APIs:** backward + forward compatibility; rolling deploys need schema contracts (Avro/Protobuf > ad-hoc JSON for cross-service evolution).
- **Ch.5 — Replication tradeoffs (say these aloud):** single-leader (simple, lag anomalies) vs multi-leader (conflicts) vs leaderless (quorum `R+W>N`, sloppy quorum / hinted handoff). Know read-your-writes / monotonic / consistent-prefix.
- **Ch.6 — Partitioning:** hash vs range; hot keys (celebrity / timestamp); secondary indexes = local scatter-gather vs global async index; avoid naïve `hash mod N` rebalancing.
- **Ch.7 — Isolation is not “ACID or nothing”:** read committed vs snapshot vs serializable; lost updates, write skew, phantoms — name the anomaly your design prevents (payments, seats, inventory).
- **Ch.8 — Distributed reality:** network is unreliable; timeout ⇒ unknown; clocks lie; process pauses break “locks” without fencing.
- **Ch.9 — Consistency ladder:** linearizability (expensive) vs eventual; total-order log / Raft for **coordination** (leader, config, unique ID), not every user read; 2PC across microservices is a smell.
- **Ch.10–11 — Derived data:** batch (immutable inputs, recompute) vs streams (Kafka-style log, CDC, event time vs processing time, idempotence). Dual-writes without a log race and lose data.
- **Interview rule:** DDIA teaches *why* Redis/Kafka/Postgres — naming tools without a tradeoff from these chapters scores weak.

## Practice — how it's asked & how to attack it
Self-test drills (map chapters → interview talk track):
1. **Drill — ch.1 load params (3 min):** For “Design Twitter/Instagram feed,” name 2–3 load parameters and which percentile you’d put on an SLO. Say what would make you skip early estimation.
2. **Drill — ch.5 lag anomalies:** “Reads go to replicas.” Explain one anomaly (stale profile after edit) + the fix (read-your-writes / sticky replica / read leader for own data).
3. **Drill — ch.6 shard key:** For URL shortener vs chat messages, pick hash vs range (or compound) and name the hot-spot risk + mitigation (salt / random suffix / separate celebrity path).
4. **Drill — ch.7 isolation:** “Two users book the last seat.” Walk lost-update vs write-skew; say which isolation / constraint (unique row, `SELECT FOR UPDATE`, serializable) you want and why.
5. **Drill — ch.8–9 fencing:** “Use Redis lock for inventory.” Argue why TTL lock alone fails under GC pause; add fencing token or DB conditional write (Kleppmann blog).
6. **Drill — ch.11 dual-write:** “Write DB then Kafka.” Name the failure mode; propose CDC/outbox as the DDIA-shaped fix. Optional: skim Raft lecture 6.2 only if interviewer probes consensus.

## Common follow-ups / gotchas
- “Is Cassandra AP and Mongo CP?” — Refuse the one-letter label; cite Kleppmann CAP post and discuss *this* read/write under *this* partition.
- “Just use consistent hashing.” — DDIA ch.6: many DBs say it but mean hash partitioning + fixed slots; say minimal remapping, not the CDN paper blindly.
- “Eventual consistency is fine.” — Ask *which* client guarantee you still need (read-your-writes on profile? inventory?).
- “We need distributed transactions.” — Prefer single-partition transactions + idempotent async; 2PC blocks on coordinator failure (ch.9).
- “Redis lock = safe.” — Without fencing, a paused holder still writes; DB/epoch check is the fence (ch.8 + locking essay).
- “I read all of DDIA.” — Interviewers care that you apply ch.5–7 on the whiteboard; finishing ch.12 without timed designs doesn’t help campus loops.

## Where it appears
- **Campus / early-career India product cos:** rarely “explain Raft”; often *implicit* DDIA: replica lag, sharding key, “what if node dies,” cache vs DB truth. Flipkart/Uber/Atlassian HLD probes map to ch.5–6–8.
- **FAANG / big-tech mid+ HLD:** explicit tradeoff language from ch.5–9; senior loops may touch consensus/coordination (ch.9) and stream/CDC (ch.11). New-grad depth varies — prefer applied ch.5–7 over formal proofs.
- **Frequency:** **meta resource** — cite chapter ideas inside every HLD foundation and `hq*` deep dive; re-read the matching chapter the night before that topic, don’t binge-read cover-to-cover first.
