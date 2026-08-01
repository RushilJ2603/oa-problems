# h05_db_scaling — DB scaling: replication, sharding, partitioning, federation, read replicas, hot-key

**Interview relevance:** High — the usual deep-dive after you draw a single Postgres/MySQL box in any HLD "design X" round (campus + experienced); FAANG and Indian product cos probe read replicas vs sharding, shard-key choice, and hot-key mitigations.
**Type:** HLD-foundation
**Prereqs:** h01_networking, h02_load_balancing

## Read / watch (curated, in order)
- [ ] [system-design-primer — RDBMS scaling](https://github.com/donnemartin/system-design-primer#relational-database-management-system-rdbms) — `primer` — the interview ladder in one place: [master-slave](https://github.com/donnemartin/system-design-primer#master-slave-replication) / [master-master](https://github.com/donnemartin/system-design-primer#master-master-replication) → [federation](https://github.com/donnemartin/system-design-primer#federation) → [sharding](https://github.com/donnemartin/system-design-primer#sharding); note [replication disadvantages](https://github.com/donnemartin/system-design-primer#disadvantages-replication) (lag, more hardware)
- [ ] [7 Must-know Strategies to Scale Your Database](https://www.youtube.com/watch?v=_1IKwnbscQU) — `ByteByteGo` — vertical scale, indexing, caching, replication (sync vs async), partitioning/sharding, federation — when each buys you headroom
- [ ] [What is DATABASE SHARDING?](https://www.youtube.com/watch?v=5faMjKuB9bc) — `Gaurav Sen` — horizontal split by shard key, cross-shard joins, consistent hashing / rebalancing pain
- [ ] [A Crash Course on Database Sharding](https://bytebytego.com/guides/a-crash-course-in-database-sharding/) — `ByteByteGo` — hash / range / directory sharding; app-level vs middleware vs DB-native; pair with [newsletter write-up](https://blog.bytebytego.com/p/a-crash-course-in-database-sharding) if you want diagrams in text form
- [ ] [Sharding (Hello Interview)](https://www.hellointerview.com/learn/system-design/core-concepts/sharding) — `Hello Interview` — partition vs shard wording, when *not* to shard, shard-key rules, hot spots, resharding; skim the [quick reference](https://www.hellointerview.com/learn/system-design/core-concepts/sharding/quick-reference)
- [ ] [Data Replication: A Key Component for Building Large-Scale Distributed Systems](https://blog.bytebytego.com/p/data-replication-a-key-component) — `ByteByteGo` — leader-follower / multi-leader / leaderless; then [How to Choose a Replication Strategy](https://blog.bytebytego.com/p/how-to-choose-a-replication-strategy) for multi-leader + quorum tradeoffs
- [ ] *Designing Data-Intensive Applications* ch.5 (Replication) — `DDIA ch.5` — book: [dataintensive.net](https://dataintensive.net/); free notes: [Chapter 5 - Replication](https://timilearning.com/posts/ddia/part-two/chapter-5/) — single-leader, sync/async lag anomalies (read-your-writes), multi-leader conflicts, leaderless quorums
- [ ] *Designing Data-Intensive Applications* ch.6 (Partitioning) — `DDIA ch.6` — free notes: [Chapter 6 - Partitioning](https://timilearning.com/posts/ddia/part-two/chapter-6/) — key-range vs hash, skewed workloads / hot spots, secondary indexes, rebalancing, request routing
- [ ] [PostgreSQL — Table Partitioning](https://www.postgresql.org/docs/current/ddl-partitioning.html) — `PostgreSQL docs` — in-instance range/list/hash partitions (maintenance, pruning) ≠ sharding across machines
- [ ] [Working with DB instance read replicas (AWS RDS)](https://docs.aws.amazon.com/AmazonRDS/latest/UserGuide/USER_ReadRepl.html) — `AWS docs` — async read replicas, promote-on-failover; Postgres specifics: [RDS PostgreSQL read replicas](https://docs.aws.amazon.com/AmazonRDS/latest/UserGuide/USER_PostgreSQL.Replication.ReadReplicas.html)
- [ ] [What is Vitess?](https://vitess.io/docs/overview/) + [Shard concept](https://vitess.io/docs/concepts/shard/) — `Vitess` — how YouTube-scale MySQL sharding actually looks (VTGate routing); optional narrative: [How YouTube Supports Billions of Users with MySQL and Vitess](https://blog.bytebytego.com/p/how-youtube-supports-billions-of)
- [ ] [Leader and Followers](https://martinfowler.com/articles/patterns-of-distributed-systems/leader-follower.html) — `Martin Fowler` — crisp primary/replica mental model; pair with [Key-Range Partitions](https://martinfowler.com/articles/patterns-of-distributed-systems/key-range-partitions.html) / [Fixed Partitions](https://martinfowler.com/articles/patterns-of-distributed-systems/fixed-partitions.html) if you want pattern names for the whiteboard

## Core concepts to master
- **Scaling ladder (say it in interviews):** vertical scale + indexes → caching → **read replicas** → **federation** (split by service/domain) → **sharding** (split rows across machines). Don't jump to shards at 10K QPS / 100GB without capacity math.
- **Replication:** keep copies for durability, failover, and **read scale**. Default interview model = **single-leader** (primary takes writes; replicas serve reads). Multi-leader = multi-region write locality + conflict resolution. Leaderless = quorum (W/R) à la Cassandra/Dynamo-style.
- **Sync vs async:** sync = follower ack before commit (stronger durability, higher write latency; one slow replica stalls you). Async = primary returns fast, **replication lag** → stale reads. Semi-sync = ack from ≥1 replica.
- **Read replicas:** offload read-heavy traffic; **do not** fix write throughput or storage size. Route "must see my write" to primary (read-your-writes); tolerate lag on feeds/analytics.
- **Partitioning vs sharding:** partitioning often means splitting a table **inside one DB** (Postgres declarative partitions — prune scans, drop old data). Sharding = horizontal split **across machines/instances**. Interviewers use the words loosely — say which you mean.
- **Federation (functional partitioning):** separate DBs by domain (`users` / `orders` / `payments`) so each scales and fails independently. Joins become app-level or are avoided; schema coupling is the tax.
- **Shard key:** high cardinality, even distribution, present in most queries so you hit **one** shard. Good: `user_id`, `tenant_id`. Bad: `is_premium` (2 buckets), `country` if skewed, **`created_at` alone** (all writes → "today" shard).
- **Placement strategies:** **hash** (even load, weak range scans); **range** (great range queries, hotspot risk); **directory** (flexible mapping, lookup SPOF/latency). Prefer **hash(user_id)** unless you need ranges.
- **Hot key / hot partition:** one key or shard eats disproportionate traffic (celebrity account, flash-sale SKU, time-bucket writes). Mitigations: cache the hot read, **key salting / write sharding** (`id#0…N` + aggregate on read), isolate celebs on dedicated shards, avoid time-only shard keys, hybrid fan-out for social feeds.
- **Cross-shard pain:** joins, transactions, unique constraints, and global secondary indexes get hard. Prefer denormalization / co-locate related rows on one shard; accept scatter-gather for rare global queries.
- **Rebalancing:** `hash % N` reshuffles almost everything on scale-out → use **consistent hashing** / fixed many virtual partitions mapped to nodes. Plan online reshard (Vitess-style) as an ops problem, not a one-liner.
- **Combine patterns:** each shard usually has its **own primary + replicas**. Replication ≠ partitioning; you almost always want both at scale.

## Practice — how it's asked & how to attack it
Self-test drills (say answers out loud in ≤2 min each):

1. **Ladder pick:** "URL shortener at 50K reads/s, 5K writes/s, 200GB." Do you shard? Justify replicas + cache first; name the metric that would force a shard (storage ceiling, write QPS, single-primary CPU).
2. **Read-your-writes:** User updates profile then immediately GETs it; replicas lag 800ms. Where do you send the GET? How do session stickiness, "primary for N seconds after write," or synchronous replica change the design?
3. **Shard-key debate:** Instagram-like app — shard by `user_id` vs `post_id` vs time. Which queries become single-shard vs fan-out? What breaks for "global trending"?
4. **Federation vs sharding:** E-commerce with `users`, `catalog`, `orders`. When is functional split enough? When do `orders` still need horizontal shards by `customer_id`?
5. **Hot-key incident:** Taylor Swift's shard is at 95% CPU; others idle. List 3 mitigations (cache, salt writes, dedicated shard) and the read-path cost of each.
6. **Range vs hash:** Time-series metrics store — why range-by-time feels natural and why it creates a hot write shard; what hybrid key (`hash(metric_id) + time`) buys you.

## Common follow-ups / gotchas
- "Read replicas fix writes" — they don't; writes still serialize on the primary (unless you multi-leader/shard).
- Premature sharding — huge operational tax; interviewers reward "I'd shard when X metric hits Y," not default sharding boxes.
- Stale replica reads after write — classic gotcha; call out read-your-writes explicitly.
- Bad shard key (`created_at`, low-cardinality status) → permanent hot partition; more nodes won't help that key.
- Cross-shard transactions / joins — either avoid (denormalize, saga) or admit 2PC/app merge cost.
- Forgetting per-shard HA — a shard without replicas is a bigger blast radius than one big primary with replicas.
- Confusing Postgres **table partitions** with **shards** — one machine vs many; both can coexist.

## Where it appears
- **Campus / intern / new-grad HLD:** expected vocabulary in URL shortener, Twitter/Instagram, chat, e-commerce, ticket booking — "add read replicas" is table stakes; shard-key + hot-key talk differentiates.
- **Experienced / mid-level (1–4 YOE):** deeper probes on lag SLAs, resharding, federation boundaries, Vitess/Citus-style routing, and celebrity/hot-key designs — common at Amazon, Google, Meta, Uber, Flipkart, Atlassian, etc.
- **Frequency:** near-universal whenever the design is data-heavy; rarely "design a sharded database product" as the whole prompt, but these knobs show up in almost every scale discussion after the first architecture sketch.
