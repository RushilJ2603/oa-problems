# h09_rate_limiting — Rate limiting & throttling: token bucket, leaky bucket, sliding window, distributed limits

**Interview relevance:** High — standalone "design a rate limiter" is a common HLD question; also probed as a building block in URL shortener, chat, ticketing, payment, and API-platform designs (campus + experienced; FAANG and Indian product cos).
**Type:** HLD-foundation
**Prereqs:** h01_networking, h02_load_balancing, h03_caching

## Read / watch (curated, in order)
- [ ] [system-design-primer — Design an API rate limiter](https://github.com/donnemartin/system-design-primer#additional-system-design-interview-questions) — `primer` — lists the classic interview prompt; pairs directly with Stripe's production write-up below
- [ ] [Rate Limiter System Design: Token Bucket, Leaky Bucket, Scaling](https://www.youtube.com/watch?v=YXkOdWBwqaA) — `ByteByteGo` — ~8 min: why rate limit, fixed-window boundary spike, token bucket as industry default, middleware + Redis sketch for multi-node
- [ ] [Rate Limiting Fundamentals](https://blog.bytebytego.com/p/rate-limiting-fundamentals) — `ByteByteGo` — limit / window / identifier; block vs throttle vs shape; fixed window, sliding log, sliding counter, token bucket, leaky bucket (newsletter; may be paywalled past the fold)
- [ ] [Design a Rate Limiter (ByteByteGo course ch.)](https://bytebytego.com/courses/system-design-interview/design-a-rate-limiter) — `ByteByteGo` / Alex Xu Vol.1 ch.4 — interview walk-through: placement (client / server / gateway), algorithms, Redis sync, race conditions, multi-DC (course may be gated)
- [ ] [Design a Distributed Rate Limiter](https://www.hellointerview.com/learn/system-design/problem-breakdowns/distributed-rate-limiter) — `Hello Interview` — gateway placement, identity (user / IP / API key), token bucket + Redis, HTTP 429 headers, sharding, fail-open vs fail-closed; pair with [YouTube breakdown](https://www.youtube.com/watch?v=MIJFyUPG4Z4)
- [ ] [Scaling your API with rate limiters](https://stripe.com/blog/rate-limiters) — `Stripe` — production stack: request rate limiter + concurrent-request limiter + fleet/worker load shedders; token bucket on Redis; fail-open, dark-launch, kill switches
- [ ] [How we built rate limiting capable of scaling to millions of domains](https://blog.cloudflare.com/counting-things-a-lot-of-different-things/) — `Cloudflare` — why fixed window + sliding log fail at edge scale; sliding-window *counter* (two integers + weighted estimate); async increment + local deny cache under L7 attack
- [ ] [Scaling a High-traffic Rate Limiting Stack with Redis Cluster](https://www.brandur.org/redis-cluster) — `Brandur (Stripe)` — single hot Redis → Cluster; Lua/`EVAL` atomicity; hash tags so multi-key scripts stay on one slot
- [ ] [Module ngx_http_limit_req_module](https://nginx.org/en/docs/http/ngx_http_limit_req_module.html) — `nginx.org` — leaky-bucket-style limiting in practice (`rate`, `burst`, `nodelay`); IP-keyed zones at the reverse proxy
- [ ] [Throttle requests to your REST APIs (API Gateway)](https://docs.aws.amazon.com/apigateway/latest/developerguide/api-gateway-request-throttling.html) — `AWS docs` — token bucket with steady-state rate + burst; account/stage/method limits → `429`
- [ ] [Rate limits for the REST API](https://docs.github.com/en/rest/using-the-rest-api/rate-limits-for-the-rest-api) — `GitHub docs` — consumer-facing pattern: `x-ratelimit-limit` / `remaining` / `reset`, primary vs secondary limits, backoff on `403`/`429`
- [ ] [429 Too Many Requests](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/429) — `MDN` — status semantics + `Retry-After`
- [ ] [Token bucket](https://en.wikipedia.org/wiki/Token_bucket) / [Leaky bucket](https://en.wikipedia.org/wiki/Leaky_bucket) — `Wikipedia` — formal definitions; when token bucket ≈ leaky-as-meter vs leaky-as-queue (smooth, no burst out)
- [ ] [Redis INCR](https://redis.io/docs/latest/commands/incr/) + [Lua / EVAL intro](https://redis.io/docs/latest/develop/programmability/eval-intro/) — `Redis docs` — atomic counters and scripting for check-and-decrement without race conditions

## Core concepts to master
- **Why:** protect backends from overload/abuse, enforce fairness / tiered quotas, control cost (esp. paid outbound APIs), reserve capacity for critical paths (load shedding ≠ per-user rate limit).
- **Placement:** client-side is advisory only; prefer **API gateway / middleware** (central policy, drop early) or per-service when limits are domain-specific. Sticky sessions to pin clients to one limiter is a bad distributed fix.
- **Identity key:** user ID / API key for authenticated traffic; IP for anonymous — but NAT/mobile shared IPs cause false positives; often combine (per-user + per-IP + per-endpoint).
- **Fixed window counter:** simple (`INCR` + TTL) but **boundary burst** — 2× limit across the window edge (N at 0:59 + N at 1:00).
- **Sliding window log:** store every timestamp; accurate, memory-heavy — poor at high QPS / long windows.
- **Sliding window counter:** hybrid — previous + current window, weighted estimate (Cloudflare); ~O(1) memory, small approximation error; kills most boundary exploits.
- **Token bucket:** tokens refill at rate *r*, capacity *b*; request needs a token. Allows **controlled bursts** up to *b*, then sustained *r*. Default for most public APIs (Stripe, AWS API Gateway).
- **Leaky bucket:** smooths to a constant drain rate (queue/shaper) or meters like an inverted token bucket; nginx `limit_req` is leaky-style. Prefer when downstream **cannot** tolerate bursts.
- **Distributed state:** local in-memory counters undercount across N nodes → use shared Redis (or equivalent). Race on get→check→set → use **atomic Lua/`EVAL`** (or single `INCR` for simple counters).
- **Scale Redis:** shard by identity (consistent hashing / Redis Cluster); multi-key scripts need **hash tags** `{userId}:…` so keys share a slot (Brandur).
- **Response contract:** HTTP **429** (sometimes 503 for shedder/overload); headers `Retry-After`, `X-RateLimit-Limit` / `Remaining` / `Reset` (GitHub-style) so clients back off with jitter.
- **Failure mode:** **fail-open** (allow if Redis down) prioritizes availability — Stripe default for request limiter; **fail-closed** prioritizes hard quotas / cost / security. Dark-launch and feature-flag kill switches before enforcing.

## Practice — how it's asked & how to attack it
Self-test drills (say answers out loud in ≤2 min each):

1. **Algorithm pick:** "100 req/min per user, mobile clients burst after reconnect." Token bucket vs fixed window vs sliding counter — which, and what parameters (*r*, *b*) would you set? When would you refuse bursts (leaky)?
2. **Boundary exploit:** Draw a fixed 60s window at limit 100. Show how a client sends ~200 near the boundary. Fix it with sliding log vs sliding counter — memory and accuracy tradeoffs.
3. **Distributed race:** Two gateway pods hit Redis for the same user with 1 token left. Why naive GET/SET overshoots? Sketch a Lua script that refills (token bucket) and decrements atomically.
4. **Placement + identity:** Design limits for `/login` (brute force) vs `/feed` (read) vs premium vs free. Gateway vs service-local? User ID vs IP vs API key — NAT and shared office Wi-Fi failure modes.
5. **Fail-open debate:** Payments quota vs public blog API. Redis blips for 2s — fail-open or fail-closed? How do Stripe-style concurrent limiters and load shedders differ from a plain request rate limiter?
6. **Headers & client behavior:** Return a correct 429 with remaining/reset. What must the client do (honor `Retry-After`, exponential backoff + jitter)? What goes wrong if clients retry immediately?

## Common follow-ups / gotchas
- "Local counters on each app server" — under-enforces by roughly the replica count; interviewer expects Redis (or similar) shared state.
- Fixed window is fine for a whiteboard start — then they ask about the **double-limit at the window edge**.
- Token bucket ≠ unlimited burst: capacity *b* caps the spike; refill rate caps the long-term average.
- Rate limit vs load shed: rate limit is usually **per identity**; load shed looks at **fleet health** and drops low-priority traffic (Stripe's fleet/worker shedders).
- Redis down: saying nothing is a miss — pick fail-open vs fail-closed and justify.
- Multi-region / anycast: global exact counts are hard/high-latency; often enforce per-region or at edge PoP (Cloudflare model) and accept slight over-allow.
- IP-only limits punish users behind CGNAT; identity should prefer authenticated keys when available.

## Where it appears
- **Campus / intern / new-grad HLD:** "Design a rate limiter" is a frequent standalone prompt; also expected as a box in API, social, ticketing, and auth designs ("how do you stop abuse?").
- **Experienced / mid-level (1–4 YOE):** deeper probes on algorithm tradeoffs, Redis Lua races, sharding/hot keys, fail-open, multi-DC, and distinguishing rate limiting from load shedding — common at Amazon, Google, Meta, Uber, Stripe-like API cos, Atlassian, Flipkart, etc.
- **Frequency:** high — both as its own question (Alex Xu Vol.1 ch.4 classic) and as a follow-up inside almost any public-API or write-heavy design.
