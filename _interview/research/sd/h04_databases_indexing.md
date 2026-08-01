# H04 — Databases & indexing (SQL vs NoSQL, B-tree vs LSM, indexes, query planning)

**Interview relevance:** High — almost every HLD round picks a store and justifies indexes for access patterns; FAANG + Indian product cos (Atlassian, Uber, Flipkart, DE Shaw) probe SQL vs NoSQL and B-tree vs LSM tradeoffs on write-heavy designs.
**Type:** HLD-foundation
**Prereqs:** None — foundational storage module; pair later with caching, replication, and sharding

## Read / watch (curated, in order)
- [ ] [system-design-primer — Database](https://github.com/donnemartin/system-design-primer#database) / [SQL or NoSQL](https://github.com/donnemartin/system-design-primer#sql-or-nosql) / [NoSQL types](https://github.com/donnemartin/system-design-primer#nosql) — `primer` — when SQL wins (joins, ACID, structured) vs NoSQL (flexible schema, high IOPS); KV / document / wide-column / graph
- [ ] [Types of Databases](https://bytebytego.com/guides/types-of-databases/) — `ByteByteGo` — relational, OLAP, and NoSQL flavors (graph, KV, document, column) in one diagram-friendly pass
- [ ] [How to Choose the Right Database](https://bytebytego.com/guides/how-to-choose-the-right-database/) — `ByteByteGo` — pick by access pattern, consistency, and scale; pair with [How To Choose The Right Database?](https://www.youtube.com/watch?v=kkeFE6iRfMM) (~video walkthrough)
- [ ] [Introduction to NoSQL databases](https://www.youtube.com/watch?v=xQnIN9bW0og) — `Gaurav Sen` — Cassandra-shaped NoSQL: partition, quorum, memtable → SSTable, compaction
- [ ] [Data Modeling](https://www.hellointerview.com/learn/system-design/core-concepts/data-modeling) — `Hello Interview` — SQL vs NoSQL for interviews; index columns to API access patterns
- [ ] [DDIA Ch.2 — Data Models and Query Languages](https://dataintensive.net/) — `DDIA ch.2` — relational vs document vs graph; declarative SQL enables the optimizer ([free notes](https://timilearning.com/posts/ddia/part-one/chapter-2/))
- [ ] [Database Indexing](https://www.hellointerview.com/learn/system-design/core-concepts/db-indexing) — `Hello Interview` — why indexes exist; B-tree default; composite / covering; write+space cost
- [ ] [Anatomy of an SQL Index](https://use-the-index-luke.com/sql/anatomy) — `Use the Index, Luke` — index = redundant sorted structure; then [The B-Tree](https://use-the-index-luke.com/sql/anatomy/the-tree) and [The Where Clause](https://use-the-index-luke.com/sql/where-clause) (leftmost prefix / composite keys)
- [ ] [8 Data Structures That Power Your Databases](https://bytebytego.com/guides/8-data-structures-that-power-your-databases/) — `ByteByteGo` — hash, SSTable, LSM, B-tree, inverted index map to real systems
- [ ] [B-Tree vs. LSM-Tree](https://bytebytego.com/guides/b-tree-vs/) — `ByteByteGo` — B-tree = faster reads; LSM = faster writes + compaction
- [ ] [DDIA Ch.3 — Storage and Retrieval](https://dataintensive.net/) — `DDIA ch.3` — LSM (memtable → SSTables → compaction + bloom filters) vs B-trees (pages, in-place updates, WAL) ([free notes](https://timilearning.com/posts/ddia/part-one/chapter-3/); also [Shichao notes](https://notes.shichao.io/dda/ch3/))
- [ ] [Relational database index vs. NoSQL index](https://www.youtube.com/watch?v=mTNkqMDCasI) — `Gaurav Sen` — RDBMS secondary indexes vs NoSQL partition/sort keys and GSIs
- [ ] [SQL Statement Execution in Database](https://bytebytego.com/guides/how-is-a-sql-statement-executed-in-the-database/) — `ByteByteGo` — parse → **optimizer/plan** → executor → access methods / buffer; pair with [SQL execution order](https://www.youtube.com/watch?v=BHwzDmr6d7s)
- [ ] [PostgreSQL — Using EXPLAIN](https://www.postgresql.org/docs/current/using-explain.html) — `PostgreSQL docs` — Seq Scan vs Index Scan; cost model; `EXPLAIN ANALYZE`; skim [Indexes](https://www.postgresql.org/docs/current/indexes.html), [Index types](https://www.postgresql.org/docs/current/indexes-types.html), [Multicolumn](https://www.postgresql.org/docs/current/indexes-multicolumn.html), [Covering / index-only](https://www.postgresql.org/docs/current/indexes-index-only-scans.html), [Planner/Optimizer](https://www.postgresql.org/docs/current/planner-optimizer.html)
- [ ] [Reading Database Execution Plans](https://use-the-index-luke.com/sql/explain-plan) — `Use the Index, Luke` — how to read plans across vendors after you know Postgres EXPLAIN
- [ ] [Cassandra Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/cassandra) — `Hello Interview` — LSM/SSTable path at interview depth (optional after B-tree vs LSM)
- [ ] [PostgreSQL Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/postgres) — `Hello Interview` — B-tree indexes + when the planner ignores your index (optional)

## Core concepts to master
- **SQL (relational):** tables + schema, joins, strong consistency / ACID transactions; great for multi-entity integrity and ad-hoc queries; horizontal scale is harder (replica / shard / denormalize).
- **NoSQL families:** key-value, document, wide-column, graph — optimize for known access patterns; often schema-flexible and easier to shard; joins usually in the app; consistency often tunable / eventual.
- **Choose by access pattern + consistency + scale**, not fashion: payments / inventory → SQL; session/KV, social graphs, write-heavy time-series / messaging → specialized NoSQL; polyglot is normal.
- **Index = redundant structure** derived from the table: speeds lookups/sorts/joins; **every write updates data + indexes**; unused indexes waste space and slow writes.
- **B-tree / B+ tree (default RDBMS index):** balanced tree of disk pages; O(log n) point + range queries (`=`, `<`, `BETWEEN`, `ORDER BY`); Postgres/MySQL InnoDB default.
- **LSM-tree (Cassandra, RocksDB, LevelDB, …):** write to memtable → flush immutable **SSTables** → background **compaction**; sequential writes → high write throughput; reads may touch memtable + several SSTables (bloom filters help); compaction causes write amp and latency variance.
- **Interview mnemonic:** B-tree ≈ read-friendly / predictable lookups; LSM ≈ write-friendly / append + compact. Workload (read:write, p99) picks the engine more than “SQL vs NoSQL” branding.
- **Composite indexes follow leftmost prefix:** `(user_id, created_at)` helps `user_id` and `user_id + created_at`, not `created_at` alone; column order = query order.
- **Covering / index-only scan:** if the index holds all needed columns, skip the heap — fewer I/Os; don’t over-INCLUDE wide columns.
- **Query planning:** declarative SQL → parser → **cost-based optimizer** picks scan/join order using stats + available indexes; `EXPLAIN` shows Seq Scan vs Index Scan; planner may correctly prefer a seq scan on small/hot tables.
- **NoSQL “indexing” ≠ free secondary indexes:** often you design **partition key + sort key** (and optional GSI) for the query; wrong key = full partition scan or fan-out.

## Practice — how it's asked & how to attack it
1. **Drill — SQL vs NoSQL picker:** For each of {payments ledger, Instagram-like feed, shopping cart, friend-graph recommendations, IoT metrics ingest}, pick store type and one consistency/query tradeoff.
2. **Drill — B-tree vs LSM:** Narrate a point lookup and a write on each; name write amplification, read amplification, and when compaction hurts p99.
3. **Drill — index the API:** Given `GET /users/{id}/posts?limit=20` sorted by time, design table + composite index; state what breaks if you only index `created_at`.
4. **Drill — leftmost prefix:** Index `(a, b, c)`. Which of `WHERE a=?`, `WHERE b=?`, `WHERE a=? AND c=?`, `WHERE a=? AND b=?` can use it efficiently? Why?
5. **Drill — EXPLAIN literacy:** For `SELECT * FROM orders WHERE user_id = ?`, sketch when you’d see Index Scan vs Seq Scan; what does `EXPLAIN ANALYZE` add over `EXPLAIN`?
6. **Drill — over-indexing:** List three indexes you’d *not* add on a write-heavy logs table and why; when is “no secondary index” the right answer?

## Common follow-ups / gotchas
- “Why not index every column?” — write amplification, storage, and the planner ignoring low-selectivity indexes anyway.
- “Is NoSQL always more scalable?” — No; many products scale Postgres far; NoSQL wins when the *data model + partitioning* match the queries, not from magic.
- “Does LSM always beat B-tree on writes?” — usually higher sustained write throughput, but compaction / tombstones / read amp can erase the win; measure for the workload.
- “Hash index vs B-tree?” — hash = equality only; B-tree also does ranges and ordering — default to B-tree unless you know you need hash.
- “Secondary indexes on sharded NoSQL?” — global secondary indexes are another distributed store (lag, cost, failure mode); prefer query-driven primary keys.
- “Why did EXPLAIN ignore my index?” — stale stats, low selectivity, wrong column order, function on the column (`WHERE LOWER(email)=…`), or table small enough that seq scan is cheaper.

## Where it appears
- **Campus / new-grad HLD:** SQL vs NoSQL choice on nearly every design; “what do you index?” on user/feed/order tables is extremely common at Indian product cos and FAANG-adjacent rounds.
- **Experienced / mid-level HLD:** B-tree vs LSM, composite/covering indexes, and reading a plan separate strong answers on write-heavy (chat, metrics, logs) and read-heavy OLTP designs.
- **Frequency:** foundational in every storage deep dive; expect explicit follow-ups whenever you draw a database box or claim “we’ll just shard NoSQL.”
