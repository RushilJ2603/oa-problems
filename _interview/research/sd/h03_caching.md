# h03_caching — Caching (cache-aside / write-through / write-back, eviction, Redis/Memcached, CDN, invalidation)

**Interview relevance:** High — almost every HLD "design X" round; FAANG and Indian product cos expect you to place a cache, pick a write strategy, name eviction + invalidation, and discuss stampede / stale-read tradeoffs when the DB or origin is the bottleneck.
**Type:** HLD-foundation
**Prereqs:** h01_networking, h02_load_balancing

## Read / watch (curated, in order)
- [ ] [system-design-primer — Cache](https://github.com/donnemartin/system-design-primer#cache) — `primer` — where to cache (client / CDN / app / DB); then drill [Cache-aside](https://github.com/donnemartin/system-design-primer#cache-aside), [Write-through](https://github.com/donnemartin/system-design-primer#write-through), [Write-behind (write-back)](https://github.com/donnemartin/system-design-primer#write-behind-write-back), [Refresh-ahead](https://github.com/donnemartin/system-design-primer#refresh-ahead)
- [ ] [What are Distributed CACHES and how do they manage DATA CONSISTENCY?](https://www.youtube.com/watch?v=U3RkDLtS7uY) — `Gaurav Sen` — why cache, placement, LRU, write-through vs write-back tradeoffs (~13 min)
- [ ] [Caching in distributed systems: A friendly introduction](https://www.youtube.com/watch?v=zw7VwIlkPPc) — `Gaurav Sen` — hit/miss, staleness / eventual consistency, local vs global vs DB cache (~11 min)
- [ ] [Cache Systems Every Developer Should Know](https://www.youtube.com/watch?v=dGAgxozNWFE) — `ByteByteGo` — cache layers end-to-end (browser → CDN → Redis → DB); pair with [EP 38: Where do we cache data?](https://blog.bytebytego.com/p/ep-38-where-do-we-cache-data)
- [ ] [Top caching strategies](https://blog.bytebytego.com/p/top-caching-strategies) — `ByteByteGo` — cache-aside / read-through / write-around / write-through / write-back in one diagram
- [ ] [Cache Eviction Policies](https://bytebytego.com/guides/most-popular-cache-eviction/) — `ByteByteGo` — TTL, LRU, LFU, MRU, SLRU; when each fits
- [ ] [Caching for System Design Interviews](https://www.hellointerview.com/learn/system-design/core-concepts/caching) — `Hello Interview` — interview framing: when to introduce cache, patterns, TTL, stampede, failure modes
- [ ] [Cache-Aside Pattern (Azure Architecture Center)](https://learn.microsoft.com/en-us/azure/architecture/patterns/cache-aside) — `Microsoft Learn` — lazy load + invalidate-on-write; why update DB *before* deleting the cache key
- [ ] [Redis key eviction](https://redis.io/docs/latest/develop/reference/eviction/) — `Redis docs` — `maxmemory` + `allkeys-lru` / `allkeys-lfu` / `volatile-*` / `noeviction`; pair with [Redis](https://redis.io/) and [Caching with Redis](https://redis.io/solutions/caching/)
- [ ] [Comparing Valkey, Memcached, and Redis OSS (ElastiCache)](https://docs.aws.amazon.com/AmazonElastiCache/latest/dg/SelectEngine.html) — `AWS docs` — Redis/Valkey (structures, replication, persistence) vs Memcached (simple, multi-threaded); skim [memcached.org](https://memcached.org/)
- [ ] [Why are Content Delivery Networks (CDN) so Popular?](https://bytebytego.com/guides/why-are-content-delivery-networks-cdn-so-popular/) — `ByteByteGo` — edge cache request flow; pair with [How CloudFront delivers content](https://docs.aws.amazon.com/AmazonCloudFront/latest/DeveloperGuide/HowCloudFrontWorks.html) — POP → regional edge → origin
- [ ] [Cache consistency strategies](https://redis.io/blog/cache-consistency-strategies/) — `Redis` — drift windows (TTL, write races, multi-instance fills); when to add event/CDC invalidation on top of TTL
- [ ] [Cache made consistent (Meta Engineering)](https://engineering.fb.com/2022/06/08/core-infra/cache-made-consistent) — `Meta` — why invalidation is hard; optional depth: [Scaling Memcache at Facebook (USENIX NSDI'13 PDF)](https://www.usenix.org/system/files/conference/nsdi13/nsdi13-final170_update.pdf)
- [ ] [Cache replacement policies](https://en.wikipedia.org/wiki/Cache_replacement_policies) — `Wikipedia` — LRU/LFU vocabulary cheat sheet; InterviewReady link dump: [system-design-resources — Caching](https://github.com/InterviewReady/system-design-resources#caching)
- [ ] *Designing Data-Intensive Applications* ch.5 (Replication) — read-your-writes / replication lag as the same mental model as cache staleness — `DDIA ch.5` — book site: [dataintensive.net](https://dataintensive.net/)

## Core concepts to master
- **Why cache:** store a hot subset in fast memory to cut latency and shield the DB/origin. Goal metric = **hit ratio**; miss cost = full DB/origin round-trip (+ possible stampede).
- **Where:** browser / client → **CDN** (static & media near users) → reverse proxy → **app local (in-process)** → **distributed cache (Redis/Memcached)** → DB buffer pool. Don't cache everything — prefer read-heavy, slowly changing, expensive-to-compute data.
- **Cache-aside (lazy loading):** app checks cache → miss → read DB → populate cache. Default for interviews. Flexible; app owns consistency; first request after miss/expiry is slow.
- **Read-through:** app talks only to cache; cache loads from DB on miss. Simpler app code; less control over what gets cached.
- **Write-through:** every write hits cache *and* DB synchronously → stronger freshness / read-your-writes, slower writes, can pollute cache with rarely-read keys.
- **Write-back (write-behind):** write cache first, flush DB async → fast writes; **data loss** if cache dies before flush. Fit for counters/analytics, not money/passwords.
- **Write-around:** write DB only, skip cache; next read populates. Avoids write-churn on cold keys; reads after write may miss.
- **Invalidation:** on DB update, **delete** (or update) the key so the next read refills. Prefer **delete-after-DB-write** (idempotent) over set-new-value races. TTL is a **backstop**, not a substitute for explicit invalidation when freshness matters.
- **Eviction:** when memory is full — **LRU** (default interview answer), **LFU** (skewed hot sets), **TTL**, random. Redis: set `maxmemory` + policy (`allkeys-lru` for pure caches).
- **Redis vs Memcached:** Memcached = simple string/object cache, multi-threaded, no rich types/persistence. Redis = data structures (hashes, sets, sorted sets), optional persistence, replication/cluster, pub/sub, scripting — default pick unless you only need dumb GET/SET at extreme throughput.
- **CDN:** geo edge caches for static (and some dynamic) content; origin pull on miss; purge/invalidate on deploy. Complements app Redis — different layer (bytes near users vs objects near services).
- **Failure modes:** **stampede/thundering herd** (hot key expires → N DB loads); **cache penetration** (repeated misses for missing keys — cache negative/null with short TTL); **hot key** (one key hammers one shard); whole-cache outage → every request hits DB (need degrade path / circuit breaker / small local fallback).

## Practice — how it's asked & how to attack it
Self-test drills (say answers out loud in ≤2 min each):

1. **Pattern pick:** Product catalog (read-heavy, minutes-old OK) vs wallet balance (read-your-writes) vs view counters (write-heavy, loss OK). Map each to cache-aside+TTL, write-through, or write-back — and say what breaks if you pick wrong.
2. **Invalidate vs TTL:** User updates profile. Sketch: write DB → `DEL user:{id}` → next GET refills. Why delete-before-DB-write can reintroduce stale data? When is TTL-only acceptable?
3. **Stampede drill:** Celebrity profile TTL hits zero at peak QPS. Mitigations: single-flight / lock (`SETNX`), probabilistic early refresh, slightly jittered TTLs, serve stale while one request refills.
4. **Redis vs Memcached:** Interviewer: "Why Redis?" Answer with structures (sessions, rate limits, leaderboards), HA/persistence needs — and when Memcached's simplicity still wins.
5. **CDN vs app cache:** Design Instagram-like feed. What goes on CDN (images/video segments) vs Redis (feed fanout metadata, session, counters)? How do you purge CDN after a media replace?
6. **Cache dies:** Redis cluster is down. Do you fail open to DB (with shedding), fail closed, or serve last-known local? How do you avoid melting Postgres?

## Common follow-ups / gotchas
- "Cache invalidation is the hard problem" — races between fill and invalidate; multi-writer apps; updates that bypass your app (batch jobs) need TTL or CDC/event invalidation.
- Caching mutable, user-specific, or security-sensitive data without short TTL / auth scoping → wrong user sees wrong data.
- Drawing Redis but never saying **key design**, **TTL**, or **eviction policy** — interviewers probe all three.
- Updating cache *before* DB commit → crash leaves phantom cache values; classic fix is DB-first then invalidate.
- Ignoring stampede on the hottest keys — high hit ratio overall still dies on one viral key expiry.
- Treating CDN purge as instant everywhere — edges can lag; versioned URLs (`asset.v3.js`) often beat emergency purge.
- Assuming write-back is "always faster and fine" — interviewer will ask about crash before flush.

## Where it appears
- **Campus / intern / new-grad HLD:** expected box in URL shortener, news feed, e-commerce, chat, TikTok/YouTube — "add Redis + CDN" is table stakes; depth on aside vs through and invalidation differentiates.
- **Experienced / mid-level (1–4 YOE):** stampedes, hot keys, Redis vs Memcached, write-back risk, CDN purge vs versioned assets — common at Amazon, Meta, Google, Uber, Atlassian, Flipkart, etc.
- **Frequency:** near-universal building block in HLD; occasionally a deeper "how would you keep cache consistent?" follow-up; full "design Memcached" is rarer outside infra-heavy loops (Facebook paper is bonus, not required).
