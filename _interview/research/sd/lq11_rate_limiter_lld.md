# LQ11 — Design a Rate Limiter

**Interview relevance:** High — the canonical **Strategy + concurrency** LLD / machine-coding problem (campus + experienced); Uber, Stripe, Amazon, Google, Meta, Atlassian, Flipkart, and API-platform loops use it to probe algorithm choice, OCP, per-key locking, and the bridge to distributed Redis. Distinct from the HLD variant (`hq02_rate_limiter` / `h09_rate_limiting`).
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Factory), l04_patterns_behavioral (Strategy), l05_concurrency_lld; algorithm intuition: h09_rate_limiting; distributed stretch: hq02_rate_limiter

## Read / watch (curated, in order)
- [ ] [Rate Limiter (Hello Interview LLD)](https://www.hellointerview.com/learn/low-level-design/problem-breakdowns/rate-limiter) — `Hello Interview` — **start here:** clarifying questions, in-memory gateway framing, `(clientId, endpoint)` → `(allowed, remaining, retryAfterMs)`, Strategy + Factory class list, thread-safety / memory / new-algo extensibility probes
- [ ] [Rate Limiter Low Level Design — Token Bucket, Sliding Window](https://lldhub.in/blog/rate-limiter-lld-design) — `lldhub` — free end-to-end LLD: entities, text class diagram, Java Token Bucket / Fixed Window / Sliding Window Log + algorithm comparison + distributed follow-ups
- [ ] [Java rate_limiting implementations](https://github.com/ashishps1/awesome-system-design-resources/tree/main/implementations/java/rate_limiting) — `ashishps1` — runnable reference: [TokenBucket](https://github.com/ashishps1/awesome-system-design-resources/blob/main/implementations/java/rate_limiting/TokenBucket.java) / [LeakyBucket](https://github.com/ashishps1/awesome-system-design-resources/blob/main/implementations/java/rate_limiting/LeakyBucket.java) / [FixedWindowCounter](https://github.com/ashishps1/awesome-system-design-resources/blob/main/implementations/java/rate_limiting/FixedWindowCounter.java) / [SlidingWindowLog](https://github.com/ashishps1/awesome-system-design-resources/blob/main/implementations/java/rate_limiting/SlidingWindowLog.java) / [SlidingWindowCounter](https://github.com/ashishps1/awesome-system-design-resources/blob/main/implementations/java/rate_limiting/SlidingWindowCounter.java) (lazy refill + `synchronized`); Python twin: [implementations/python/rate_limiting](https://github.com/ashishps1/awesome-system-design-resources/tree/main/implementations/python/rate_limiting). Hub: [awesome-system-design-resources](https://github.com/ashishps1/awesome-system-design-resources). *(Note: [awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) is the sheet’s LLD hub for OOP/patterns; rate-limiter code lives in the sibling SD repo for now.)*
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) — `Refactoring.Guru` — **the two patterns this problem exists to test** (swap TokenBucket ↔ SlidingWindow without editing the facade; create limiter from config string)
- [ ] [LLD Case Study: Extensible Rate Limiter](https://www.calibreos.com/learn/lld-rate-limiter) — `CalibreOS` — Strategy + DI of `Clock`/`Store`; E4→E6 bar (global lock vs per-key lock vs Redis Lua); read-modify-write race called out explicitly
- [ ] [Rate Limiter LLD · LLD-flavoured](https://ikshitij.com/learn/lld-object-oriented/rate-limiter-lld/) — `ikshitij` — class diagrams (`RateLimiter` + pluggable `Storage` + CAS); Redis Lua token-bucket sketch; Guava / Bucket4j pointers
- [ ] [[LLD-5] Rate Limiter: Low Level Design](https://blog.stackademic.com/lld-5-rate-limiter-low-level-design-df3106250899) — `Stackademic` — compact Token Bucket walkthrough: `RateLimitStore` (`ConcurrentHashMap`) → `TokenRateLimiter` → facade `RateLimiter`
- [ ] [Low level design: Rate Limiting System](https://levelup.gitconnected.com/low-level-design-rate-limiting-system-a815eac97fea) — `Level Up Coding` — enterprise-shaped class hierarchy: Strategy + Factory + `QuotaManager` / tiers + Redis stub as DIP store
- [ ] [Designing a Rate Limiter — Token Bucket deep dive](https://www.onenoughtone.com/learn/rate-limiter/2) — `OneNoughtOne` — capacity vs rate math, lazy refill, concurrent race on naive read-then-write (pairs with coding Token Bucket cleanly)
- [ ] [RateLimiter (Guava)](https://guava.dev/releases/33.4.7-jre/api/docs/com/google/common/util/concurrent/RateLimiter.html) + [source](https://github.com/google/guava/blob/master/guava/src/com/google/common/util/concurrent/RateLimiter.java) — `Google Guava` — production **local** token-bucket: `acquire` / `tryAcquire`, thread-safe, warmup variant; contrast with per-user map of buckets
- [ ] [Bucket4j](https://bucket4j.com/) ([GitHub](https://github.com/bucket4j/bucket4j)) — `Bucket4j` — Java token-bucket library used in real gateways; good “what production looks like” after you hand-roll
- [ ] [uber-go/ratelimit](https://github.com/uber-go/ratelimit) — `Uber` — GCRA / leaky-bucket-style **blocking** in-process limiter; contrast bursty token bucket vs smooth drain
- [ ] [Token bucket](https://en.wikipedia.org/wiki/Token_bucket) / [Leaky bucket](https://en.wikipedia.org/wiki/Leaky_bucket) — `Wikipedia` — formal defs before you draw UML
- [ ] [Rate Limiting Fundamentals](https://blog.bytebytego.com/p/rate-limiting-fundamentals) — `ByteByteGo` — algorithm cheat-sheet (fixed / sliding log / sliding counter / token / leaky) before class design; pair with short [YouTube overview](https://www.youtube.com/watch?v=YXkOdWBwqaA)
- [ ] [Scaling your API with rate limiters](https://stripe.com/blog/rate-limiters) — `Stripe` — production follow-up after LLD: token bucket on Redis, fail-open, dark-launch (HLD bridge)
- [ ] [Redis rate limiter use case](https://redis.io/docs/latest/develop/use-cases/rate-limiter/) + [INCR rate-limiter pattern](https://redis.io/docs/latest/commands/incr/) + [Lua / EVAL intro](https://redis.io/docs/latest/develop/programmability/eval-intro/) — `Redis docs` — when interviewer asks “make it multi-instance”: shared store + atomic script
- [ ] [429 Too Many Requests](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/429) — `MDN` — status + `Retry-After`; pair with [GitHub `X-RateLimit-*` headers](https://docs.github.com/en/rest/using-the-rest-api/rate-limits-for-the-rest-api)
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after you can code the happy path

## Core concepts to master
- **Clarify before coding:** in-memory single process vs distributed? key = user / IP / API key / `(clientId, endpoint)`? hard reject vs queue/throttle? return bool only or `(allowed, remaining, retryAfter)`? which algorithms mandatory? config at startup or hot-reload?
- **LLD vs HLD split:** LLD = classes, Strategy, per-key state, thread-safety, Factory from config. HLD = gateway placement, Redis sharding, fail-open, multi-DC — mention as stretch, don’t build Redis mid-round unless asked.
- **Core entities:** `RateLimiter` (facade) → `RateLimitAlgorithm` / `RateLimitStrategy` (interface) → concrete algos; `RateLimitConfig` / `RateLimitRule` (limit, window/rate, capacity); `RateLimitResult`; per-key state store (`ConcurrentHashMap` or `Storage` interface); optional `LimiterFactory`, `Clock`, `LimitResolver` (tiered quotas).
- **Patterns that earn points:** **Strategy** (swap Token Bucket / Fixed Window / Sliding Log / Sliding Counter / Leaky Bucket without editing callers), **Factory** (config `algorithm` string → concrete limiter), **DIP** (inject `Clock` + `Store` for tests / Redis later). Facade on `RateLimiter.allow(...)`. Avoid cargo-cult Singleton.
- **Algorithm cheat-sheet (must verbalize):**
  - **Fixed window:** counter + window id; simple; **2× burst at boundary**.
  - **Sliding window log:** deque of timestamps; accurate; **O(n) memory**.
  - **Sliding window counter:** weighted prev+curr windows; ~O(1); approximate (Cloudflare-style).
  - **Token bucket:** capacity *b*, refill *r*; **controlled bursts**; O(1); industry default (Stripe / AWS / Guava).
  - **Leaky bucket:** constant drain / no burst out; smooth downstream (nginx / Uber GCRA-style).
- **Lazy refill (critical):** on each request compute `tokens += elapsed * rate` capped at capacity — **no background refill thread**.
- **Concurrency (the senior probe):** check-then-consume is a race. Prefer **per-key lock** (or `synchronized` on the bucket object) / `AtomicReference`+CAS — never one global lock on the whole map under load. `ConcurrentHashMap.computeIfAbsent` for cold keys; lock the bucket, not the map.
- **Keying:** composite key `"userId:endpoint"` (or API key) so policies differ per route; default config when endpoint unknown (Hello Interview).
- **Result contract:** `allowed`, `remaining`, `retryAfterMs` (null if allowed) — maps cleanly to HTTP 429 + `Retry-After` / `X-RateLimit-*`.
- **SOLID signal:** OCP = new algorithm = new class + Factory branch; SRP = strategy owns math, store owns persistence, facade owns orchestration; DIP = depend on `RateLimitAlgorithm` / `Storage` / `Clock`.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~30–40 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** given identity key (+ often endpoint), decide allow/deny under a configured rule; support ≥2 algorithms behind one interface; return remaining quota (+ retry hint on deny).
- **FR (common extensions — ask):** per-tier limits (free/pro); multi-permit cost (GraphQL complexity); default rule for unknown endpoints; admin update rules.
- **NFR:** correct under concurrent checks; low latency (µs–ms in-process); extensible algorithms & storage; deterministic tests (injectable clock).
- **Assumptions to state:** single JVM in-memory unless told otherwise; wall-clock OK for interview, mention monotonic/`Clock` for production; fail-open/closed only if distributed.
- **Use cases:** API gateway middleware checks each request; login endpoint uses stricter fixed/sliding limit; search allows token-bucket bursts; denied client backs off using `retryAfterMs`.

### 2. Back-of-envelope estimation (usually light for LLD)
- Active keys: thousands–millions sparse; state ≈ a few numbers per key (token bucket) or up to *limit* timestamps (sliding log).
- Hot path must be **O(1)** for token/fixed/sliding-counter; avoid scanning all keys.
- If “scale” probe: global lock → throughput cliff; per-key lock or striped locks; distributed → Redis Lua (see hq02).

### 3. API / interface
```
allow(clientId, endpoint) → RateLimitResult { allowed, remaining, retryAfterMs }
// or
tryAcquire(key, permits=1) → boolean
```
Factory / config shape (Hello Interview-style):
```
{ "endpoint": "/search", "algorithm": "TokenBucket",
  "algoConfig": { "capacity": 1000, "refillRatePerSecond": 10 } }
```
HTTP mapping (when asked): `429` + `Retry-After` + `X-RateLimit-Limit|Remaining|Reset`.

### 4. Data model / class diagram
```
RateLimiter (facade)
  ├── uses → LimiterFactory
  ├── Map<endpoint, RateLimitConfig>
  └── Map<(clientId, endpoint), RateLimitAlgorithm>   // or shared strategy + Map of state

RateLimitAlgorithm <<interface>>
  + allow(key, config) → RateLimitResult
  <|-- TokenBucketAlgorithm
  <|-- FixedWindowAlgorithm
  <|-- SlidingWindowLogAlgorithm
  <|-- SlidingWindowCounterAlgorithm
  <|-- LeakyBucketAlgorithm

RateLimitConfig (limit / windowMs / capacity / refillRate / algorithmType)
RateLimitResult (allowed, remaining, retryAfterMs)

Storage <<interface>>  (optional DIP)
  + get / cas / put(ttl)
  <|-- InMemoryStore (ConcurrentHashMap)
  <|-- RedisStore                    // stretch

Clock <<interface>> → SystemClock | FakeClock
```
Canonical narrative diagrams: [lldhub class sketch](https://lldhub.in/blog/rate-limiter-lld-design), [ikshitij Mermaid](https://ikshitij.com/learn/lld-object-oriented/rate-limiter-lld/).

### 5. High-level architecture / component breakdown
- **RateLimiter (Facade):** resolve config for endpoint → get/create per-key algorithm state → delegate `allow` → return `RateLimitResult`.
- **LimiterFactory:** maps algorithm enum/string + `algoConfig` → concrete strategy instance (or prototype).
- **Strategies:** pure rate math + own/borrow per-key state; Token Bucket holds `(tokens, lastRefill)`.
- **Store:** `ConcurrentHashMap` keyed by identity; optional TTL/eviction for idle clients (memory follow-up).
- **Clock:** injectable for unit tests (advance time → tokens refill without `Thread.sleep`).
- **Concurrency layer:** synchronize / lock **per bucket**; CAS retry loop if lock-free.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Strategy vs giant switch:** switch compiles faster in a timebox; Strategy + Factory is the expected OCP answer for “add Sliding Window Counter tomorrow.”
2. **Token Bucket vs Sliding Log:** TB = burst OK, O(1) mem; log = exact, memory grows with request rate — pick consciously.
3. **Global lock vs per-key lock:** `synchronized allow()` on the facade is correct but serializes unrelated users; lock the per-key bucket (or CAS) — senior signal.
4. **Lazy refill vs timer thread:** timers add complexity and races; lazy refill on request is the interview default.
5. **In-memory vs Redis (stretch):** local under-enforces by replica count; Redis + Lua for atomic check-and-consume; fail-open vs fail-closed is a product call (Stripe often fail-open for request limiter).

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = **one key’s allow()** — keep O(1); don’t hold the map lock while doing math.
- Memory: idle-key eviction / TTL; prefer token bucket or sliding counter over sliding log at high QPS.
- Many endpoints × many clients → store state only for **seen** keys (`computeIfAbsent`).
- Optional product stretch: Redis Cluster + hash tags, local token cache / borrow batches — only if asked (HLD territory).

**Timed drill:** implement Token Bucket + Fixed Window behind `RateLimitAlgorithm` with `ConcurrentHashMap` + per-bucket `synchronized` in 60–75 min; add Factory from JSON config; unit-test with a fake clock.

## Common follow-ups / gotchas
- “Two threads, one token left — both allowed?” — race on read-modify-write; show per-key lock or CAS / Redis Lua.
- “Add a new algorithm” — new class implementing Strategy + one Factory branch; zero edits to `RateLimiter` call sites.
- “Fixed window boundary spike” — draw 2× burst; fix with sliding counter/log or switch to token bucket.
- “Distributed across N pods” — shared Redis; atomic Lua for token bucket; mention fail-open/closed.
- “Memory grows forever” — TTL/idle eviction on keys; sliding log is the worst offender.
- “Tiered limits (free vs pro)” — `LimitResolver` / config per plan; don’t hardcode rates in the strategy.
- Gotcha: background refill thread + sleep in tests — prefer lazy refill + injected `Clock`.
- Gotcha: locking the entire `ConcurrentHashMap` / facade — correct but fails the concurrency follow-up.
- Gotcha: shipping only HLD Redis boxes when the round is **LLD** — draw classes and a working `allow()` first.

## Where it appears
- **Campus / new-grad:** increasingly common machine-coding / LLD round in India and FAANG-style loops when they want Strategy + concurrency without a huge domain model; often “implement Token Bucket + one other algo.”
- **Experienced / SDE-2+:** same OOP surface, harder probes — per-key locking, injectable clock/store, Redis Lua stretch, fail-open, header contract, algorithm selection by traffic shape (Stripe/Uber/Amazon/Meta/Google, API gateway teams).
- **Sibling rounds:** HLD “design a rate limiter” (`hq02`) and foundation `h09_rate_limiting` — reuse algorithm vocabulary; this card is the **class-design** version.
- **Frequency:** high among LLD concurrency/Strategy problems — treat alongside LRU cache and logger as the “systems-flavored” LLD set.
