# hq02_rate_limiter — Design a distributed rate limiter

**Interview relevance:** High — classic standalone HLD prompt (Alex Xu Vol.1 ch.4); also a building-block follow-up inside API, social, payments, and gateway designs (campus + experienced; FAANG and Indian product cos).
**Type:** HLD-question
**Prereqs:** h09_rate_limiting, h01_networking, h02_load_balancing, h03_caching, h14_estimation

## Read / watch (curated, in order)
- [ ] [Rate Limiter System Design: Token Bucket, Leaky Bucket, Scaling](https://www.youtube.com/watch?v=YXkOdWBwqaA) — `ByteByteGo` — ~8 min overview: why rate limit, fixed-window boundary spike, token bucket default, middleware + Redis sketch
- [ ] [Rate Limiting Fundamentals](https://blog.bytebytego.com/p/rate-limiting-fundamentals) — `ByteByteGo` — limit / window / identifier; block vs throttle; fixed window, sliding log/counter, token bucket, leaky bucket (newsletter; may be paywalled past the fold)
- [ ] [Design a Rate Limiter (ByteByteGo course / Alex Xu Vol.1 ch.4)](https://bytebytego.com/courses/system-design-interview/design-a-rate-limiter) — `ByteByteGo` — full interview walk-through: placement, algorithms, Redis sync, race conditions, multi-DC (course may be gated)
- [ ] [Design a Distributed Rate Limiter](https://www.hellointerview.com/learn/system-design/problem-breakdowns/distributed-rate-limiter) — `Hello Interview` — gateway placement, identity keys, token bucket + Redis Lua, 429 headers, sharding, fail-open vs fail-closed
- [ ] [Design a Distributed Rate Limiter (YouTube walkthrough)](https://www.youtube.com/watch?v=MIJFyUPG4Z4) — `Hello Interview` — ex-Meta staff engineer whiteboard of the same breakdown
- [ ] [InterviewReady — system-design-resources (Rate Limiting)](https://github.com/InterviewReady/system-design-resources#rate-limiting) — `Gaurav Sen` / InterviewReady — curated pointers (circuit breaker + Uber leaky-bucket lib); pairs with paid InterviewReady module “Design a distributed rate limiter” on [interviewready.io](https://interviewready.io/)
- [ ] [uber-go/ratelimit](https://github.com/uber-go/ratelimit) — `Uber` (via Gaurav Sen list) — production-style **blocking leaky bucket** (GCRA-style) for in-process throttling; contrast with Redis-backed distributed quotas
- [ ] [Scaling your API with rate limiters](https://stripe.com/blog/rate-limiters) — `Stripe` — request limiter + concurrent limiter + fleet/worker load shedders; token bucket on Redis; fail-open, dark-launch, kill switches
- [ ] [How we built rate limiting capable of scaling to millions of domains](https://blog.cloudflare.com/counting-things-a-lot-of-different-things/) — `Cloudflare` — why fixed window + sliding log fail at edge; sliding-window **counter** (two ints + weighted estimate)
- [ ] [Scaling a High-traffic Rate Limiting Stack with Redis Cluster](https://www.brandur.org/redis-cluster) — `Brandur (Stripe)` — hot single Redis → Cluster; Lua/`EVAL` atomicity; **hash tags** so multi-key scripts stay on one slot
- [ ] [Redis rate limiter use case](https://redis.io/docs/latest/develop/use-cases/rate-limiter/) + [Lua / EVAL intro](https://redis.io/docs/latest/develop/programmability/eval-intro/) — `Redis docs` — why shared store + atomic scripts for check-and-consume
- [ ] [system-design-primer — Design an API rate limiter](https://github.com/donnemartin/system-design-primer#additional-system-design-interview-questions) — `primer` — classic prompt in the interview-questions list
- [ ] [429 Too Many Requests](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/429) — `MDN` — status + `Retry-After`
- [ ] [Rate limits for the REST API](https://docs.github.com/en/rest/using-the-rest-api/rate-limits-for-the-rest-api) — `GitHub docs` — consumer-facing `X-RateLimit-*` header pattern

## Core concepts to master
- **Why:** protect backends, enforce fairness / tiered quotas, control cost (paid outbound APIs), stop abuse — distinct from **load shedding** (fleet health, not per-user quota).
- **Placement:** client-side = advisory only; prefer **API gateway / middleware** (drop early, one policy) or a dedicated rate-limit service when rules need rich app context. Sticky sessions are a bad distributed fix.
- **Identity key:** user ID / API key (auth); IP (anonymous) — NAT/CGNAT false positives; often **layer** per-user + per-IP + per-endpoint and take the most restrictive.
- **Algorithms:** fixed window (simple, **2× boundary burst**); sliding log (accurate, memory-heavy); sliding counter (Cloudflare hybrid, ~O(1)); **token bucket** (burst *b*, sustained *r* — Stripe/AWS default); leaky bucket (smooth output, no burst).
- **Distributed state:** local counters under-enforce by ~replica count → shared **Redis** (or equivalent). Race on get→check→set → **atomic Lua/`EVAL`** (not just `MULTI` around writes after a separate read).
- **Response contract:** HTTP **429** (+ sometimes 503 for shedders); headers `Retry-After`, `X-RateLimit-Limit` / `Remaining` / `Reset` so clients back off with jitter.
- **Failure mode:** **fail-open** (availability — Stripe request limiter) vs **fail-closed** (hard quotas / cost / security). Dark-launch + kill switches before enforcing.
- **Scale:** shard by identity (consistent hashing / Redis Cluster); hot keys (abusers / mega-clients) need special handling; multi-region exact global counts are hard — often per-region / edge with slight over-allow.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (~45 min). Say assumptions out loud; pick one default path and name the tradeoffs.

### 1. Requirements (functional + non-functional) & scale assumptions
**Clarify first:** server-side API limiter? Per-user / IP / API key? Soft throttle vs hard reject? Exact vs approximate OK?

**Functional (typical):**
- Identify client (user ID, IP, API key — often layered).
- Enforce configurable rules (e.g. 100 req/min/user; different tiers / endpoints).
- On exceed → **429** + helpful headers (`Limit` / `Remaining` / `Reset`, `Retry-After`).

**Non-functional (typical):**
- Low overhead on the hot path (aim **< ~5–10 ms** added latency).
- High availability; slight over/under-count across nodes often acceptable.
- Distributed across many gateway / app replicas.
- Rules changeable without full redeploy (config store / cache).

**Out of scope (draw the line):** analytics warehouse on every deny; strong global consistency across continents; billing-grade exact metering unless asked.

### 2. Back-of-envelope estimation
Pick a scale with the interviewer (Hello Interview-style example works well):

| Assumption | Example |
|---|---|
| Peak QPS | **1M req/s** through the gateway |
| DAU / distinct keys | **100M** users (huge key space, sparse active set) |
| Per-check Redis cost | Lua script ≈ few ops; budget **~50k–100k checks/s per Redis primary** (pessimistic) |
| Shards needed | ~**10–20+** Redis primaries (or Redis Cluster) for 1M checks/s |
| Memory | token bucket ≈ 2 numbers + TTL per active key; sliding **log** blows up with timestamps |

Storage is ephemeral (TTL / idle expiry). Disk DBs are too slow for the request path — in-memory store is mandatory.

### 3. API / interface
Gateway-internal check (middleware), not a public REST product:

```
isAllowed(clientId, ruleId) -> { allowed: bool, remaining: int, resetAt: timestamp, retryAfterSec?: int }
```

On deny, HTTP response shape clients expect:

```
HTTP/1.1 429 Too Many Requests
X-RateLimit-Limit: 100
X-RateLimit-Remaining: 0
X-RateLimit-Reset: 1640995200
Retry-After: 60
```

Optional admin/config: CRUD rules (limit, window, burst, scope = user|ip|key|endpoint|tier) loaded into gateway memory via push / poll.

### 4. Data model
**Rules** (config, relatively static): `ruleId`, scope, limit / refill rate, burst capacity, window, endpoints, tier.

**Counters / buckets** (Redis, hot path) — pick one algorithm and stick to it:

| Algorithm | Key sketch | Value |
|---|---|---|
| Fixed window | `rl:{client}:{windowStart}` | counter + TTL |
| Token bucket | `rl:{client}:{rule}` hash | `tokens`, `last_refill` + TTL |
| Sliding counter | `rl:{client}:{currWin}`, `…:{prevWin}` | two counters |
| Sliding log | sorted set of timestamps | memory-heavy — usually reject at this scale |

Use Redis Cluster **hash tags** when a Lua script touches multiple keys for one client: `{user123}:tokens`, `{user123}:meta` (Brandur).

### 5. High-level architecture / component breakdown
**Default interview design (most common “great” path):**

```
Client → LB / API Gateway (rate-limit middleware)
              ↓ Lua/atomic check
         Redis Cluster (sharded by client id)
              ↓ allow
         API / service tier
```

- **Gateway middleware:** extract identity → load applicable rules → call Redis → allow forward or 429.
- **Redis Cluster:** source of truth for counters/buckets; shard by `hash(clientId)`.
- **Rule config:** disk / DB → workers / push → in-memory cache on gateways (Stripe-style).
- **Alternatives to name:** (a) in-process only — under-enforces; (b) dedicated rate-limit microservice — richer context, +1 RTT; (c) edge PoP (Cloudflare model) — low latency, approximate global.

### 6. Deep dives & the 2–3 key tradeoffs interviewers probe
**A. Algorithm choice**
- Token bucket: allow **controlled bursts**, good DX for mobile/batch — **default**.
- Fixed window: fine as a whiteboard start — they will ask about **boundary 2×**.
- Sliding counter: when you need near-sliding accuracy with O(1) memory (Cloudflare).
- Leaky / blocking (Uber lib): when you want **smooth** outbound to a fragile dependency.

**B. Correctness under concurrency**
- Separate HMGET then HSET/`MULTI` still races — two gateways both see 1 token.
- Fix: entire refill + consume in one **Lua `EVAL`/`EVALSHA`**.

**C. Fail-open vs fail-closed**
- Social / blog API under Redis blip → usually **fail-open** (availability) + alerts.
- Payments / LLM cost / security quotas → **fail-closed**.
- Stripe: fail-open on request limiter; separate **load shedders** for fleet emergencies.

**D. Accuracy vs latency vs ops**
- Exact global multi-DC counts = high RTT / complexity; often **per-region** limits + accept slight over-allow.
- Local cache of “already denied” can help under attack (Cloudflare) but risks stale allows — call out carefully.

### 7. Bottlenecks / how you scale it
- **Redis CPU / QPS** is the usual ceiling → shard by client id; Redis Cluster; connection pools on gateways.
- **Hot key** (one abuser / scraper IP) saturates one shard → local deny cache, stricter IP rules, challenge / ban, isolate heavy tenants on dedicated limits.
- **Gateway CPU** for Lua round-trips → pool connections; co-locate Redis in-region; avoid sticky-session “solutions.”
- **Config fan-out** → push rules; feature-flag / kill switch to disable enforcement if a bad rule ships.
- **Observability:** rate of 429s by rule, Redis latency/errors, fail-open events; dark-launch before enforce (Stripe).

**30-second closing line:** “Gateway middleware, token bucket in Redis with Lua atomicity, shard by client id, 429 + headers, fail-open/closed chosen by risk, Redis Cluster + hot-key and multi-region caveats.”

## Common follow-ups / gotchas
- “Just put a counter in each app server” — under-enforces by ~N replicas; expect shared Redis (or similar).
- Fixed window → probe **double-limit at the window edge**; fix with sliding counter/log or token bucket.
- Token bucket ≠ unlimited burst: capacity *b* caps the spike; refill rate caps long-term average.
- Race condition: `MULTI` after a non-atomic read is not enough — need **Lua** (or single `INCR` for simple windows).
- Redis down: silence is a miss — pick **fail-open vs fail-closed** and justify.
- Rate limit vs load shed: per-identity quota vs fleet-health dropping low-priority traffic (Stripe).
- IP-only limits punish CGNAT / office Wi-Fi; prefer authenticated identity when available.
- Multi-region: exact global counters are expensive; per-region / edge is the pragmatic answer.

## Where it appears
- **Campus / intern / new-grad HLD:** frequent standalone “Design a rate limiter”; also the abuse box in URL shortener, Twitter, ticket booking, auth.
- **Experienced (1–4+ YOE):** deeper Redis Lua races, Cluster/hash tags, hot keys, fail-open, multi-DC, rate limit vs load shedding — Amazon, Google, Meta, Uber, Stripe-like API cos, Atlassian, Flipkart, etc.
- **Frequency:** very high — Alex Xu Vol.1 ch.4 classic and a near-universal follow-up on any public API design.
