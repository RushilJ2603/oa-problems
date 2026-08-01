# hq14_distributed_cache — Design a distributed cache (Redis / Memcached)

**Interview relevance:** High — classic infra HLD prompt ("design Redis/Memcached") and the deep-dive that follows almost every read-heavy product design; campus + experienced; FAANG and Indian product cos.
**Type:** HLD-question
**Prereqs:** h03_caching, h15_building_blocks (consistent hashing), h02_load_balancing, h14_estimation; helpful: h05_db_scaling, h06_consistency_cap

## Read / watch (curated, in order)
- [ ] [Design a Distributed Cache Like Redis](https://www.hellointerview.com/learn/system-design/problem-breakdowns/distributed-cache) — `Hello Interview` — best interview skeleton: GET/SET/DELETE + TTL + LRU; 1TB / 100k QPS framing; HA, sharding, hot keys
- [ ] [System Design Interview — Distributed Cache](https://www.youtube.com/watch?v=iuqZvajTOyA) — `System Design Interview` (YouTube) — full whiteboard: local LRU → dedicated cluster → consistent hashing → replication + config service (~Memcached/Redis shape)
- [ ] [What are Distributed CACHES and how do they manage DATA CONSISTENCY?](https://www.youtube.com/watch?v=U3RkDLtS7uY) — `Gaurav Sen` — why cache, placement, LRU, write-through vs write-back (~13 min)
- [ ] [Caching in distributed systems: A friendly introduction](https://www.youtube.com/watch?v=zw7VwIlkPPc) — `Gaurav Sen` — hit/miss, staleness, local vs shared cache (~11 min)
- [ ] [A Crash Course in Caching — Part 1](https://blog.bytebytego.com/p/a-crash-course-in-caching-part-1) — `ByteByteGo` — what a cache is, hit ratio, layers (browser → CDN → Redis/Memcached); newsletter may be paywalled past the fold
- [ ] [A Crash Course in Caching — Part 2](https://blog.bytebytego.com/p/a-crash-course-in-caching-part-2) — `ByteByteGo` — distributed cache sharding (mod / range / **consistent hashing**) + read/write strategies
- [ ] [Cache Systems Every Developer Should Know](https://www.youtube.com/watch?v=dGAgxozNWFE) — `ByteByteGo` — end-to-end cache layers in one visual
- [ ] [Consistent Hashing | Algorithms You Should Know #1](https://www.youtube.com/watch?v=UF9Iqmg94tk) — `ByteByteGo` — ring + vnodes; pair with [Consistent Hashing Explained](https://bytebytego.com/guides/consistent-hashing/)
- [ ] [What is CONSISTENT HASHING and Where is it used?](https://www.youtube.com/watch?v=zaRkONvyGr8) — `Gaurav Sen` — interview framing of the same primitive
- [ ] [Consistent Hashing (Hello Interview)](https://www.hellointerview.com/learn/system-design/core-concepts/consistent-hashing) — `Hello Interview` — vnodes, hot keys vs structural imbalance
- [ ] [Caching for System Design Interviews](https://www.hellointerview.com/learn/system-design/core-concepts/caching) — `Hello Interview` — when to introduce cache, TTL, stampede, failure modes (foundation for this design)
- [ ] [Cache Eviction Policies](https://bytebytego.com/guides/most-popular-cache-eviction/) — `ByteByteGo` — TTL / LRU / LFU cheat sheet
- [ ] [Design a Key-Value Store (ByteByteGo / Alex Xu Vol.1)](https://bytebytego.com/courses/system-design-interview/design-a-key-value-store) — `ByteByteGo` — sibling chapter: data partition, replication, consistency (course may be gated)
- [ ] [Design a Distributed Cache (Grokking)](https://www.educative.io/courses/grokking-the-system-design-interview/design-a-distributed-cache) — `Grokking / Educative` — alternate written walkthrough (may be gated)
- [ ] [system-design-primer — Cache](https://github.com/donnemartin/system-design-primer#cache) — `primer` — cache-aside / write-through / write-behind; pair with [Consistent hashing](https://github.com/donnemartin/system-design-primer#consistent-hashing) + [The Simple Magic of Consistent Hashing](https://www.paperplanes.de/2011/12/9/the-magic-of-consistent-hashing.html)
- [ ] [Redis Cluster scaling (hash slots)](https://redis.io/docs/latest/operate/oss_and_stack/management/scaling/) — `Redis docs` — **16384 slots**, `CRC16(key) mod 16384` (not a classic consistent-hash ring); pair with [Cluster specification](https://redis.io/docs/latest/operate/oss_and_stack/reference/cluster-spec/)
- [ ] [Redis key eviction](https://redis.io/docs/latest/develop/reference/eviction/) — `Redis docs` — `maxmemory` + `allkeys-lru` / `allkeys-lfu` / `volatile-*` / `noeviction`
- [ ] [Understanding distributed caching](https://redis.io/glossary/distributed-caching/) — `Redis` — short product-shaped overview of distributed caching
- [ ] [Redis Sentinel](https://redis.io/docs/latest/operate/oss_and_stack/management/sentinel/) — `Redis docs` — HA for a single primary (failover) vs Cluster (sharding + HA)
- [ ] [Comparing Valkey, Memcached, and Redis OSS (ElastiCache)](https://docs.aws.amazon.com/AmazonElastiCache/latest/dg/SelectEngine.html) — `AWS docs` — Redis/Valkey (structures, replication, persistence) vs Memcached (simple, multi-threaded); skim [memcached.org](https://memcached.org/)
- [ ] [Cache-Aside Pattern](https://learn.microsoft.com/en-us/azure/architecture/patterns/cache-aside) — `Microsoft Learn` — lazy load + invalidate-on-write; DB-first then delete key
- [ ] [Scaling Memcache at Facebook (USENIX NSDI'13 PDF)](https://www.usenix.org/system/files/conference/nsdi13/nsdi13-final170_update.pdf) — `Meta / USENIX` — production gold: client-side consistent hashing, lease/thundering herd, multi-cluster; optional depth: [mcrouter announcement](https://engineering.fb.com/2014/09/15/web/introducing-mcrouter-a-memcached-protocol-router-for-scaling-memcached-deployments/) + [facebook/mcrouter](https://github.com/facebook/mcrouter)
- [ ] [Cache made consistent (Meta Engineering)](https://engineering.fb.com/2022/06/08/core-infra/cache-made-consistent) — `Meta` — why invalidation is hard at scale
- [ ] [Design of a Modern Cache](http://highscalability.com/blog/2016/1/25/design-of-a-modern-cache.html) — `High Scalability` — Caffeine-style modern eviction (Window TinyLFU); code: [ben-manes/caffeine](https://github.com/ben-manes/caffeine)
- [ ] [coding-parrot / distributed-cache (LLD code)](https://github.com/coding-parrot/Low-Level-Design/tree/master/distributed-cache) — `Gaurav Sen` — machine-coding companion (LRU + distributed pieces); resource dump: [InterviewReady — Caching](https://github.com/InterviewReady/system-design-resources#caching)
- [ ] [Design a Distributed Cache (System Design School)](https://systemdesignschool.io/problems/distributed-cache/solution) — `System Design School` — strong written deep dives on routing, working-set sizing, hot keys, invalidation races
- [ ] *Designing Data-Intensive Applications* ch.5–6 — `DDIA` — replication lag / read-your-writes as cache staleness; partitioning & “consistent hashing” naming caveat — book: [dataintensive.net](https://dataintensive.net/); free notes: [ch.6](https://timilearning.com/posts/ddia/part-two/chapter-6/)
- [ ] [Consistent hashing (Wikipedia)](https://en.wikipedia.org/wiki/Consistent_hashing) — `Wikipedia` — quick ring + vnode vocabulary

## Core concepts to master
- **What you're building:** an in-memory **key-value** layer across many machines — not a durable DB. Source of truth is usually the database; cache is a **lossy accelerator**. Goal metric = **hit ratio** (and p99 latency on hits).
- **APIs:** `GET` / `SET` (optional TTL) / `DELETE`. Interview default eviction = **LRU** (+ TTL as backstop). Out of scope unless asked: rich query, strong durability, multi-key transactions.
- **Why distribute:** working set exceeds one box's RAM, or single-node QPS/CPU isn't enough → **shard** keys across nodes.
- **Partitioning:** `hash % N` remaps almost everything on scale-out → **consistent hashing** (ring + **virtual nodes**) so only ~`1/N` keys move. Production note: **Redis Cluster** uses fixed **16384 hash slots**, not a classic ring — same goal (minimal remapping), different mechanism.
- **Routing:** (a) **client-side** hashing (Memcached / Facebook style — lowest latency, smart clients); (b) **proxy** (mcrouter / Twemproxy — dumb clients, extra hop); (c) **server redirects** (Redis Cluster `MOVED`/`ASK`). Pick one and name the tradeoff.
- **Replication / HA:** primary + async replicas per shard; promote on failure via Sentinel / Cluster / config service. Cache can lose unreplicated writes → become a miss and refill from DB. Prefer **availability + eventual consistency** over strong durability unless interviewer insists.
- **Eviction:** memory full → **LRU** (default), **LFU** (skewed popularity), TTL expiry. Redis: set `maxmemory` + policy (`allkeys-lru` for pure caches).
- **App integration (usually separate from "design Redis"):** **cache-aside** + **delete-on-write** + TTL; stampede (single-flight / lease / jittered TTL); hot-key (local L1, replicate hot keys, split keys).
- **Redis vs Memcached:** Memcached = simple GET/SET, multi-threaded, no rich types. Redis = structures, scripting, optional persistence, Sentinel/Cluster — default interview pick unless they want dumb high-QPS cache.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (~45 min). Clarify whether they want **the cache product** (Redis-like) or **app + cache** (cache-aside in front of Postgres). Default below = **design the cache cluster**; mention cache-aside as the client pattern.

### 1. Requirements (functional + non-functional) & scale assumptions
**Clarify first:** KV only? TTL? Eviction policy? Durability needed? Strong consistency or eventual OK? Read/write ratio? Client library smart enough to hash?

**Functional (typical — Hello Interview):**
- `GET(key)` → value or miss.
- `SET(key, value, ttl?)` → store with optional expiry.
- `DELETE(key)` → remove (invalidation path).
- Evict by **LRU** when memory is full.

**Non-functional (typical):**
- Low latency hits (**< ~1–10 ms** in-region; Hello Interview often uses **< 10 ms**).
- High availability; **eventual consistency** OK across replicas.
- Horizontal scale for memory + QPS.
- **Out of scope (draw the line):** disk durability as primary store; SQL; cross-DC strong consistency; multi-key ACID.

**Scale prompt to ask for:** e.g. **~1 TB** cached data, **~100k–1M ops/s**, read-heavy.

### 2. Back-of-envelope estimation
Use working-set math (size for **hot keys**, not the full DB):

| Assumption | Example |
|---|---|
| Dataset / keys | 1B keys × ~1 KB ≈ **1 TB** on disk DB |
| Working set | ~**10%** keys serve ~90% traffic → **~100 GB** to keep in RAM for high hit rate |
| Peak QPS | **100k–1M** ops/s (pick with interviewer) |
| Per-node RAM | e.g. **16–64 GB** usable → **~2–10+** shards for 100 GB (+ headroom for overhead/replicas) |
| Per-node QPS | one Redis primary often **50k–100k+** simple ops/s (order-of-magnitude) → shard for QPS *and* memory |
| Miss tax | at 99% hit + 1M QPS → **10k** DB reads/s steady; **one dead shard** doubles miss load for its keys — size DB for the cold case |

Say out loud: *hit rate is an economics problem* — a few points of miss rate can melt the DB when a shard dies.

### 3. API / interface
Cache protocol (not a public REST product) — sketch:

```
GET    key            -> HIT value | MISS
SET    key value [EX seconds]
DELETE key
```

Optional admin / cluster: add/remove node, rebalance slots, stats (`INFO`, hit ratio, memory).

If interviewer wants the **application** API instead, show cache-aside around a domain call:

```
getUser(id):
  v = cache.GET("user:"+id)
  if v: return v
  v = db.load(id)
  cache.SET("user:"+id, v, ttl=300)
  return v

updateUser(id, patch):
  db.save(id, patch)
  cache.DELETE("user:"+id)   # invalidate; next read refills
```

### 4. Data model / class diagram
**Per entry (in memory):**

| Field | Notes |
|---|---|
| `key` | string / bytes; namespace prefixes (`user:123`) |
| `value` | opaque bytes (or Redis type) |
| `expire_at` | absolute time; lazy + active expiry |
| `lru_node` | pointer into LRU list / approximated LRU sample |

**Node-local structures (whiteboard):**
- Hash map: `key → entry`
- Doubly linked list (or Redis approximated LRU) for eviction order
- Optional TTL min-heap / timing wheel

**Cluster metadata:** node list / slot map (or consistent-hash ring + vnodes); primary–replica membership.

### 5. High-level architecture / component breakdown
**Default interview design:**

```
App servers  ──(client lib: hash(key) / slot map)──►  Cache shard primaries
                                                         ├─ async replicate ─► replicas
Config / membership (ZK, Consul, Redis Cluster bus, Sentinel)
DB (source of truth on miss / after invalidate)
```

- **Cache nodes:** in-memory KV + LRU + TTL; one **primary** owns a key range/slots.
- **Replicas:** HA + optional read scaling (stale OK).
- **Routing:** prefer **client-side** consistent hashing / slot map for fewer hops; mention **proxy** (mcrouter) when many languages / ops need central policy.
- **Config service:** publish membership so clients don't hammer dead nodes.
- **Alternatives to name:** co-located cache process on app hosts (Facebook early pattern) vs dedicated cache fleet (isolation, shared across services).

### 6. Deep dives & the 2–3 key tradeoffs interviewers probe
**A. Sharding: mod hash vs consistent hashing vs Redis slots**
- `hash % N` is fine until you add a node → mass miss storm.
- Consistent hashing + **vnodes** → even load, ~`1/N` remapped.
- Redis Cluster: **16384 slots** moved between nodes — same interview story, say the real mechanism if they ask "how does Redis do it?"

**B. Consistency & invalidation**
- Cache is allowed to be **stale within TTL / invalidate contract**.
- Prefer **DB write then DELETE key** (idempotent) over updating cache in place (fill/invalidate races).
- Async replication → brief stale reads after failover; acceptable for most caches.

**C. Client routing vs proxy**
- Client hash: +1 RTT saved, harder client upgrades.
- Proxy (mcrouter): central routing, pooling, shadow/warmup — +latency, ops complexity.

**D. Hot keys & stampedes** (almost always asked)
- Hot **read** key: L1 in-process cache, replicate that key to N nodes, split into subkeys, or mcrouter-style pools.
- Stampede on expiry: **lease / single-flight** (Facebook memcache lease), probabilistic early refresh, jittered TTLs, serve-stale-while-revalidate.
- Hot **write** key: harder — often redesign key (shard counters) or accept primary bottleneck.

### 7. Bottlenecks / how you scale it
- **Memory:** add shards; rebalance slots/ring; size for working set + replica copies.
- **QPS / CPU on one primary:** more shards; for hot keys use replication or L1 — sharding alone won't help one viral key.
- **Network fan-out:** one page may touch hundreds of keys (Facebook paper) → **batch/multiget**, connection pooling, avoid thundering incast.
- **Node failure:** promote replica; clients refresh map; expect temporary miss spike — **DB must absorb** `~traffic/N` extra.
- **Cold cluster / deploy:** warmup, shadow traffic (mcrouter), or accept miss storm with shedding.
- **Multi-region:** usually **per-region cache** + invalidate or TTL; global exact cache coherence is rarely worth it.

**30-second closing line:** “In-memory sharded KV with client-side consistent hashing (or Redis 16384 slots), LRU+TTL, primary/replica HA, cache-aside delete-on-write at the app, and explicit hot-key + stampede mitigations so a miss storm doesn't take down the DB.”

## Common follow-ups / gotchas
- “Just use `hash % N`” — probe what happens when you add a cache node (mass remapping / miss storm).
- Consistent hashing without **vnodes** → uneven arcs and hot nodes.
- Saying Redis uses a consistent-hash **ring** — interviewers who know Redis may expect **hash slots**.
- Updating cache **before** DB commit → crash leaves phantom values; fix = DB-first + invalidate.
- Ignoring **thundering herd** on popular key TTL expiry.
- Treating cache as durable store (write-back without acknowledging loss risk).
- Hot key: more shards don't help if one key maps to one shard — need L1 / replication / key split.
- Redis down: fail-open to DB with **load shedding**, small local fallback, or circuit breaker — don't silently melt Postgres.
- Redis vs Memcached: justify with structures/HA needs vs multi-threaded simple GET/SET.

## Where it appears
- **Campus / intern / new-grad HLD:** frequent as “add Redis” inside URL shortener, feed, e-commerce; standalone “design a distributed cache” appears at stronger campuses and infra-leaning loops.
- **Experienced (1–4+ YOE):** consistent hashing/slots, replication failover, hot keys, stampede, client vs proxy, Facebook memcache paper depth — Meta, Amazon, Google, Uber, LinkedIn, Atlassian, Flipkart, etc.
- **Frequency:** very high as a building block; high as a standalone design at companies that run large cache fleets. Pair with **h03_caching** + **h15** before mock interviews.
