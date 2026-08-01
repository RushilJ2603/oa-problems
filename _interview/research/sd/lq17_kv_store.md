# LQ17 — Design an In-Memory Key-Value Store

**Interview relevance:** High — systems-flavored LLD / machine-coding staple (campus + experienced); Lyft, Uber, Coinbase, Anchorage, Amazon, Google, Meta, Atlassian, and Flipkart-style loops probe `get`/`set`/`delete`, TTL, nested or MULTI-style transactions, CAS, eviction Strategy, and concurrency. Distinct from LRU/LFU cache LLD (`lq13_cache_lld`) and distributed cache / Dynamo HLD (`hq14_distributed_cache`, ByteByteGo “Design a Key-Value Store”).
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Factory), l03_patterns_structural (Facade), l04_patterns_behavioral (Strategy / Command), l05_concurrency_lld; warm-up sibling: `lq13_cache_lld` (eviction); HLD stretch: `hq14_distributed_cache`, `h03_caching`

## Read / watch (curated, in order)
- [ ] [Design an in-memory database to handle transactions (Hello Interview)](https://www.hellointerview.com/community/questions/memory-database-transactions/cm6uaoy1y00003b6la4jojd7s) — `Hello Interview` — **start here for the transaction variant:** `get`/`set`/`unset` + nested `begin`/`commit`/`abort`; delta stack (not full DB copy); asked at Lyft / Uber / Coinbase / Anchorage
- [ ] [System Design: InMemory Key-Value Store With Transaction](https://medium.com/@rickymondal/system-design-inmemory-key-value-with-transaction-0a6df97ccce1) — `Medium / Ricky Mondal` — LLD with optimistic concurrency: `VersionedValue`, `ThreadLocal` txn, `readSet`/`writeSet`/`deleteSet`, validate-on-commit (Redis WATCH-shaped)
- [ ] [Design an InMemory Database library](https://nikhilgupta1.medium.com/design-an-inmemory-database-library-082739088710) — `Medium / Nikhil Gupta` — Strategy for `Storage` + `EvictionPolicy`, `InMemoryDb` facade, `ReentrantReadWriteLock`; OCP for LRU/LFU/FIFO
- [ ] [Designing a LRU Cache (problem + UML + multi-lang code)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/lru-cache.md) — `awesome-low-level-design` — **closest awesome-lld sibling** (no dedicated `key-value-store.md`): capacity + O(1) get/put + thread-safety; [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/lrucache-class-diagram.png); hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Java lrucache solution](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/lrucache) — `awesome-low-level-design` — runnable HashMap + DLL with `synchronized` get/put (reuse as eviction Strategy behind the KV facade)
- [ ] [Scenario: Design a caching layer](https://codefarm0.medium.com/scenario-design-a-caching-layer-what-patterns-and-considerations-would-you-use-0a5c4afd6fe5) — `Medium` — TTL entry + `ConcurrentHashMap` sketch, eviction Strategy framing, distributed follow-ups
- [ ] [Design a Cache with Expiry](https://officialcto.com/interview-section/lld/cache-with-expiry) — `Official CTO` — compact TTL LLD: `CacheEntry` + lazy/periodic eviction + `ReentrantReadWriteLock`; Strategy for eviction
- [ ] [abhi-824/thread-safe-cache](https://github.com/abhi-824/thread-safe-cache) — `GitHub` — concurrency deep dive: immutable `CacheEntry`, lazy + eager expiry, **conditional** `map.remove(key, entry)` races called out
- [ ] [Building a Redis Clone from Scratch – Part 1: In-Memory KV Store with TCP](https://sushantdhiman.substack.com/p/building-a-redis-clone-from-scratch) — `Substack` — minimal `KVStore` on `ConcurrentHashMap` + TCP command loop (machine-coding shape)
- [ ] [mohosy/kv-store-engine](https://github.com/mohosy/kv-store-engine) — `GitHub` — from-scratch hash table + lazy/active TTL + RDB-style snapshot (good “beyond `HashMap`” stretch)
- [ ] [ThatDeparted2061/mini-redis-go](https://github.com/ThatDeparted2061/mini-redis-go) — `GitHub` — Redis-compatible clone notes: typed values, lazy + active sampling expiry (25% heuristic), AOF stretch
- [ ] [SET](https://redis.io/docs/latest/commands/set/) / [GET](https://redis.io/docs/latest/commands/get/) / [DEL](https://redis.io/docs/latest/commands/del/) / [SETEX](https://redis.io/docs/latest/commands/setex/) / [EXPIRE](https://redis.io/docs/latest/commands/expire/) — `Redis docs` — canonical API + **passive + active** expiry algorithm (sample ~20 keys; repeat if >25% expired)
- [ ] [Transactions (MULTI / EXEC / DISCARD / WATCH)](https://redis.io/docs/latest/develop/using-commands/transactions/) — `Redis docs` — queue-then-atomic-exec; optimistic CAS via [WATCH](https://redis.io/docs/latest/commands/watch/); [MULTI](https://redis.io/docs/latest/commands/multi/) / [EXEC](https://redis.io/docs/latest/commands/exec/) / [DISCARD](https://redis.io/docs/latest/commands/discard/); Redis does **not** rollback mid-EXEC failures
- [ ] [Redis key eviction](https://redis.io/docs/latest/develop/reference/eviction/) — `Redis docs` — `maxmemory` + `allkeys-lru` / `allkeys-lfu` / `volatile-*` / `noeviction` when the store is capacity-bounded
- [ ] [ConcurrentHashMap (Java SE 17)](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/concurrent/ConcurrentHashMap.html) — `Oracle JDK` — default interview store: concurrent gets, segmented/CAS updates; pair with `compute` / `computeIfAbsent` / `remove(k,v)` for atomic check-and-set
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) / [Facade](https://refactoring.guru/design-patterns/facade) / [Command](https://refactoring.guru/design-patterns/command) / [Singleton](https://refactoring.guru/design-patterns/singleton) — `Refactoring.Guru` — eviction/storage policies, create policy from config, `KeyValueStore` API surface, queued txn ops / undo, optional single process store (prefer DI)
- [ ] [Key–value database](https://en.wikipedia.org/wiki/Key%E2%80%93value_database) — `Wikipedia` — model vocabulary before UML
- [ ] [ben-manes/caffeine](https://github.com/ben-manes/caffeine) — `Caffeine` — production in-process KV/cache after you hand-roll (size + expireAfterWrite); contrast with interview HashMap+DLL
- [ ] [Design a Key-Value Store (ByteByteGo / Alex Xu Vol.1)](https://bytebytego.com/courses/system-design-interview/design-a-key-value-store) — `ByteByteGo` — **HLD companion only** (partition, replication, quorum, LSM); don’t build Dynamo mid-LLD unless asked
- [ ] [Design a Key Value Store: A Complete Guide](https://www.systemdesignhandbook.com/guides/design-a-key-value-store/) — `System Design Handbook` — free written Dynamo-shaped stretch after the in-memory LLD works
- [ ] [How to Answer a LLD Interview Problem](https://blog.algomaster.io/p/how-to-answer-a-lld-interview-problem) — `AlgoMaster` — clarify → entities → relationships → code skeleton pacing
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after the happy path
- [ ] [AlgoMaster LLD hub](https://algomaster.io/learn/lld) — `AlgoMaster` — sheet hub that also indexes the awesome-lld problems

## Core concepts to master
- **Clarify before coding:** single-process in-memory vs distributed? string-only values or typed (string/list/hash)? TTL? capacity + eviction? nested transactions vs Redis MULTI queue? CAS / `compareAndSet`? persistence (AOF/snapshot)? concurrency model (locks vs event-loop)?
- **LLD vs HLD split:** LLD = classes, map + entry metadata, TTL, txn stack / optimistic versions, Strategy for eviction, thread-safety. HLD = sharding, replication, quorum, LSM — mention as stretch (`hq14` / ByteByteGo KV chapter), don’t draw Dynamo mid-round unless asked.
- **Core entities:** `KeyValueStore` / `InMemoryDB` (facade) → `Storage` (map) → `Entry` / `VersionedValue` (value + version + `expireAt`); optional `Transaction` / `TransactionManager`; optional `EvictionPolicy` Strategy; optional `Clock`, `ExpirySweeper`.
- **Patterns that earn points:** **Facade** (`get`/`set`/`delete`/`expire`), **Strategy** (LRU/LFU/FIFO/TTL-only eviction; HashMap vs custom table storage), **Factory** (build store from config: capacity, policy, TTL defaults), **Command** (queue MULTI ops / undo on abort), **DIP** (inject `Storage` + `EvictionPolicy` + `Clock`). Avoid cargo-cult Singleton.
- **Default data plane:** `ConcurrentHashMap<K, Entry>` for O(1) average get/set/delete. Entry holds value + optional absolute expiry + optional version. Capacity-bounded stores compose with LRU/LFU structures from `lq13`.
- **TTL (must verbalize Redis-style):** **lazy/passive** — on access, if `now >= expireAt`, delete and return miss; **active** — background sampler deletes expired keys so cold keys don’t leak memory. Prefer absolute deadline on the entry (or side expire map) over sleeping per key.
- **Transactions — two interview shapes:**
  1. **Nested delta stack** (Hello Interview): `begin` pushes a change-log; ops record previous values; `abort` restores; nested `commit` merges into parent; top-level commit drops the log (or applies buffered writes). Space = O(keys touched), not O(DB size).
  2. **Optimistic / Redis WATCH:** buffer writes in txn; track versions in `readSet`; on `commit`/`EXEC`, abort if any watched/read version changed; else apply atomically.
- **CAS:** `compareAndSet(key, expected, new)` or version check — foundational for counters / “set only if unchanged” without holding a global lock.
- **Concurrency (the senior probe):** single-key ops → `ConcurrentHashMap` methods / per-key lock. Compound ops (read-modify-write, txn apply, “evict then put”) need one critical section or CAS retry — never check-then-act on the map without atomicity. Prefer striped / per-key locks over one global `synchronized` on the facade under load. Redis production model = single-threaded command loop (mention as alternative).
- **SOLID signal:** OCP = new eviction/storage = new class + Factory branch; SRP = store orchestrates, entry owns metadata, policy owns victim selection, txn manager owns isolation; DIP = depend on `Storage` / `EvictionPolicy` / `Clock`.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~30–40 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** `get(key)`, `set(key, value)`, `delete(key)` with O(1) average; miss returns null / optional empty.
- **FR (common extensions — ask):** per-key TTL (`set(key, value, ttlMs)` / `expire`); capacity + eviction; nested transactions OR MULTI/EXEC/DISCARD; `compareAndSet`; `exists` / `ttl`; typed values.
- **NFR:** thread-safe under concurrent clients; no stale reads of expired keys; extensible eviction/storage; deterministic tests (injectable `Clock`); bounded memory if capacity set.
- **Assumptions to state:** single JVM / process in-memory unless told otherwise; string keys/values OK for demo; wall-clock OK in interview, mention monotonic/`Clock` for production; no disk durability unless asked.
- **Use cases:** session store (`SET sessionId … EX 3600`); feature-flag map; cart/counter with CAS; multi-step transfer with `begin`/`commit`/`abort`; local cache in front of a DB (then point to `lq13` / `hq14`).

### 2. Back-of-envelope estimation (usually light for LLD)
- Millions of keys × (key + value + 16–32 B metadata) → RAM budget; reject or evict when over `maxMemory` / capacity.
- Hot path must stay **O(1)** average; don’t scan the whole map on every `get`.
- Active expiry: sample a few keys periodically (Redis: ~20 keys, 10×/s; repeat if >25% expired) — O(sample), not O(n) full sweep unless tiny.

### 3. API / interface
```
get(key) → value | null
set(key, value) → void
set(key, value, ttlMs) → void
delete(key) → boolean
exists(key) → boolean
ttl(key) → msRemaining | -1 (no expire) | -2 (missing)
compareAndSet(key, expected, newValue) → boolean

// Nested-txn shape (Hello Interview)
begin() / commit() / abort()
// Redis-shaped
multi() / exec() → results | null / discard() / watch(keys…)
```
Optional CLI for machine coding: `SET k v [EX sec]`, `GET k`, `DEL k`, `BEGIN`, `COMMIT`, `ABORT`.

### 4. Data model / class diagram
```
KeyValueStore (Facade)
  ├── Storage<<interface>> → HashMapStorage | ConcurrentMapStorage
  ├── EvictionPolicy<<interface>> → LRU | LFU | FIFO | NoEviction   // optional
  ├── TransactionManager (optional)
  ├── ExpirySweeper / ScheduledExecutor (optional active TTL)
  └── Clock

Entry / VersionedValue
  - value
  - version (long)                 // for optimistic txn / CAS
  - expireAtMs (Long / 0 = none)

Transaction
  - writeSet / deleteSet
  - readSet: Map<key, version>     // optimistic
  // OR nested stack frame: Map<key, (newVal, oldVal)>

EvictionPolicy
  + onAccess(key) / onPut(key) / onRemove(key)
  + evictCandidate() → key?
```
Canonical related UML: [lrucache-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/lrucache-class-diagram.png) (eviction subsystem). Transaction narratives: [Hello Interview](https://www.hellointerview.com/community/questions/memory-database-transactions/cm6uaoy1y00003b6la4jojd7s), [Mondal optimistic design](https://medium.com/@rickymondal/system-design-inmemory-key-value-with-transaction-0a6df97ccce1).

### 5. High-level architecture / component breakdown
- **KeyValueStore (Facade):** validates args → lazy-expire check → delegate to `Storage` → notify `EvictionPolicy` → optionally enforce capacity.
- **Storage:** `ConcurrentHashMap` of `Entry`; exposes get/put/remove/CAS helpers.
- **TransactionManager:** owns stack or `ThreadLocal` txn context; on commit validates versions (optimistic) or merges deltas (nested); on abort restores / drops buffers.
- **ExpirySweeper:** daemon samples keys with TTL; uses conditional remove so it never deletes a fresher entry that replaced an expired one.
- **EvictionPolicy:** updated on access/put; returns victim when `Storage` is full (see `lq13` for O(1) LRU/LFU).
- **Concurrency layer:** map atomics for single-key; lock or single-threaded apply path for multi-key txn commit.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Full snapshot vs delta stack for transactions:** copying the whole map per `begin` is simple but O(n) memory; delta log is O(keys touched) and is the expected answer (Hello Interview).
2. **Lazy-only vs lazy+active TTL:** lazy alone leaks memory on write-heavy never-read keys; active sampling fixes it without a huge timer heap (Redis model). Min-heap of expiries is exact but costlier to maintain under churn.
3. **Global lock vs ConcurrentHashMap / per-key lock:** global `synchronized` is correct for demos; seniors want map atomics + narrow critical sections for compound ops / txn apply.
4. **Optimistic vs pessimistic txn:** optimistic (versions/WATCH) maximizes concurrency, retries on conflict; pessimistic locks keys for the txn duration — simpler reasoning, worse under contention.
5. **In-memory LLD vs distributed KV (stretch):** partitioning + replication + quorum is HLD (`hq14` / ByteByteGo); say so and stay on classes unless prompted.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot key → same map bucket / same lock; mention key sharding (striped maps) if pressed.
- Memory → capacity + eviction Strategy; estimate entry overhead; optional value size limits.
- Expiry storm → bound work per active tick; don’t block the request path on a full-table sweep.
- Multi-key txn → lock keys in sorted order to avoid deadlock, or use optimistic validation + retry.
- Product stretch only if asked: AOF/snapshot persistence, RESP protocol, replica sync — out of core LLD scope.

**Timed drill:** implement `get`/`set`/`delete` + per-key TTL (lazy + optional sweeper) + either nested `begin`/`commit`/`abort` **or** optimistic `begin`/`commit` with versions, on `ConcurrentHashMap`, in 60–75 min; unit-test with a fake `Clock`.

## Common follow-ups / gotchas
- “Nested transaction abort should only undo the inner level” — merge child deltas into parent on inner commit; restore previous values only for the popped frame on abort.
- “Two threads, one CAS — both succeed?” — show version check or `replace(key, oldEntry, newEntry)` / `compareAndSet`.
- “Expired key still in memory forever” — need active expiry; lazy alone is insufficient.
- “Sweeper deleted a key that was just refreshed” — use conditional `remove(key, expectedEntry)` / CAS, not blind `remove(key)`.
- “Add LFU eviction tomorrow” — new `EvictionPolicy` class + Factory; zero edits to call sites of `get`/`set` (OCP); detail in `lq13`.
- “Make it durable” — append-only log of mutations + periodic snapshot; replay on boot (Redis AOF/RDB talking point).
- “Make it multi-node” — consistent hashing / Redis Cluster slots + replication — hand off to `hq14` / ByteByteGo KV chapter.
- Gotcha: treating this round as pure LeetCode LRU — draw the store facade, TTL, and concurrency story; reuse LRU as a Strategy, don’t stop at DLL surgery.
- Gotcha: Redis MULTI is **not** SQL rollback — queued commands run atomically; failed command mid-EXEC doesn’t undo siblings; WATCH provides optimistic abort before EXEC.

## Where it appears
- **Campus / new-grad:** common machine-coding / LLD round when they want concurrency + data-structure design without a huge domain model; often “HashMap store + TTL” or “KV + nested transactions.”
- **Experienced / SDE-2+:** same surface, harder probes — optimistic vs nested txn, conditional remove races, striped locks, capacity eviction Strategy, injectable clock, persistence stretch (Lyft/Uber/Coinbase-style txn DB; Amazon/Meta/Google systems LLD).
- **Sibling rounds:** `lq13_cache_lld` (LRU/LFU eviction detail), `hq14_distributed_cache` / ByteByteGo “Design a Key-Value Store” (distributed Redis/Dynamo HLD), `h03_caching` foundations.
- **Frequency:** high among systems-flavored LLD problems — treat alongside rate limiter, logger, and LRU cache as the “infra OOP” set. awesome-lld indexes the eviction half via [lru-cache.md](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/lru-cache.md); pair it with Hello Interview’s transaction DB for the full KV brief.
