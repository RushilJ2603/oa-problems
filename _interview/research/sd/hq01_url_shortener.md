# hq01_url_shortener — Design a URL Shortener (TinyURL / Bitly)

**Interview relevance:** High — the classic first "design X" HLD question at campus + FAANG / Indian product cos; tests estimation, unique ID generation, Base62, read-heavy caching, and 301 vs 302.
**Type:** HLD-question
**Prereqs:** h01_networking, h02_load_balancing, h03_caching, h04_databases_indexing, h05_db_scaling, h10_api_design, h14_estimation; helpful: h06_consistency_cap, h08_message_queues, h09_rate_limiting

## Read / watch (curated, in order)
- [ ] [Design a URL Shortener Like Bitly](https://www.hellointerview.com/learn/system-design/problem-breakdowns/bitly) — `Hello Interview` — best free junior-friendly walkthrough (requirements → API → uniqueness → cache → scale); pair with the video [Beginner System Design Interview: Design Bitly](https://www.youtube.com/watch?v=iUU4O1sWtJA)
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — the 45-min skeleton (FRs → NFRs → entities → API → HLD → deep dives) you reuse on every design question
- [ ] [Design a URL Shortener (ByteByteGo / Alex Xu Vol.1 Ch.8)](https://bytebytego.com/courses/system-design-interview/design-a-url-shortener) — `ByteByteGo` — canonical book/course chapter: API, hash vs Base62, cache-aside redirect path
- [ ] [How Does a URL Shortener Work?](https://www.youtube.com/watch?v=HHUi8F_qAXM) — `ByteByteGo` — short free visual of the create + redirect flows
- [ ] [TinyURL System Design (codeKarle)](https://www.youtube.com/watch?v=AVztRY77xxA) — `codeKarle` — Indian-interview staple: range/token service, Base62, Cassandra, async analytics; notes: [TinyURL System Design](https://www.codekarle.com/system-design/TinyUrl-system-design.html)
- [ ] [Snowflake ID Generation by Twitter](https://www.youtube.com/watch?v=2O1wur4m8DE) — `Gaurav Sen` — distributed unique IDs (timestamp + worker + sequence) used before Base62; code/archive: [twitter-archive/snowflake](https://github.com/twitter-archive/snowflake)
- [ ] [System Design playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — foundations (scale, cache, DB) you will name inside this design; channel: [Gaurav Sen](https://www.youtube.com/channel/UCRPMAqdtSgd0Ipeef7iFsKw)
- [ ] [Design Pastebin.com (or Bit.ly)](https://github.com/donnemartin/system-design-primer/blob/master/solutions/system_design/pastebin/README.md) — `primer` — close cousin (Bit.ly called out): MD5/Base62, schema, cache, capacity math
- [ ] [Designing TinyURL (Grokking the System Design Interview)](https://www.educative.io/courses/grokking-the-system-design-interview/system-design-tinyurl) — `Grokking / Educative` — classic Key Generation Service (KGS) + unused/used key DBs framing
- [ ] [How to Design a TinyURL / URL Shortener](https://www.geeksforgeeks.org/system-design/how-to-design-a-tiny-url-or-url-shortener/) — `GfG` — compact written recap of hash vs counter + Base62
- [ ] [URL shortener system design (Tech Dummies)](https://www.youtube.com/watch?v=JQDHz72OA3c) — `Tech Dummies` — alternate full walkthrough if you want a second narration
- [ ] [Design a URL Shortener (Bitly) — NeetCodeIO](https://www.youtube.com/watch?v=qSJAvd5Mgio) — `NeetCodeIO` — optional mock-style pass after Hello Interview / ByteByteGo
- [ ] [301 Moved Permanently](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/301) / [302 Found](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/302) — `MDN` — redirect caching semantics (the analytics tradeoff)
- [ ] [Base62](https://en.wikipedia.org/wiki/Base62) / [URL shortening](https://en.wikipedia.org/wiki/URL_shortening) — `Wikipedia` — alphabet + product context cheat sheet
- [ ] [Caching for System Design Interviews](https://www.hellointerview.com/learn/system-design/core-concepts/caching) — `Hello Interview` — cache-aside / TTL / stampede vocabulary for the redirect hot path
- [ ] [system-design-resources (InterviewReady)](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` — further-reading dump after the core path; book site: [dataintensive.net](https://dataintensive.net/) (`DDIA` — load parameters / percentiles framing)

## Core concepts to master
- **Two paths only:** **write** = shorten (`POST` → unique short code → persist mapping); **read** = redirect (`GET /{code}` → lookup → `Location` header). Optimize the **read** path first — typical **read:write ≈ 100:1 to 1000:1**.
- **Short-code length math:** alphabet = Base62 (`0-9a-zA-Z`) → `62^n` codes. `62^7 ≈ 3.5×10^12` — interview default length **7**. Pick `n` from lifetime URL count, not vibes.
- **ID generation options (tradeoffs):** (1) **hash long URL + truncate + Base62** — deterministic/dedup-friendly, needs collision retry; (2) **global counter / range allocator + Base62** — collision-free, predictable (enumerable); (3) **Snowflake / distributed ID + Base62** — no central counter SPOF, time-sortable; (4) **pre-generated Key Generation Service (KGS)** — Grokking-style unused/used key pools.
- **Prefer counter/Snowflake over naive hash** at interview scale unless interviewer wants dedup of identical long URLs — hash truncation forces DB uniqueness checks + retries.
- **Data model:** primary key = `short_code` → `long_url`, `created_at`, optional `expires_at`, `user_id`, `custom_alias`. Index/PK on `short_code` for O(log n)/O(1) redirect lookup.
- **Cache-aside on redirect:** Redis/Memcached holds hot `code → long_url`; miss → DB → populate. Viral links make cache the real capacity story.
- **301 vs 302:** **301** = browsers may cache forever → fewer hits to you, weak analytics / hard revoke; **302** (or 301 + short `Cache-Control`) = every click hits you → analytics + update/expire control. Default interview answer: **302 if you need click tracking**.
- **Custom aliases:** separate namespace or reserved prefix so user aliases never collide with auto-generated codes; enforce uniqueness with DB constraint / conditional write.
- **Availability > strong consistency for redirects:** AP-friendly store (or SQL + replicas) is fine once a mapping is written; custom-alias uniqueness needs a strong uniqueness check on create.
- **Analytics off the hot path:** enqueue click events (Kafka/queue) async — never block redirect on analytics write.
- **Abuse / rate limit:** create endpoint authenticated + rate-limited; redirects public. Malicious URL scanning is usually "below the line" unless asked.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈40–45 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (core):** shorten long URL → short URL; open short URL → redirect to long URL.
- **FR (optional / ask):** custom alias, TTL/expiry, click analytics, user accounts, delete/update destination.
- **NFR:** unique codes; redirect p99 ≪ 100 ms; high availability (redirect never fails if mapping exists); durable mappings; read-heavy.
- **Clarify:** expected URLs/day, retention (e.g. 5–10 years), custom aliases?, analytics required?, multi-region?

### 2. Back-of-envelope estimation
State assumptions out loud (example set — replace with interviewer's numbers):
- **100M new URLs / month** ≈ **40 writes/s** avg; peak ~2–5×.
- **100:1 reads** → **~4k redirects/s** avg; peak tens of thousands.
- **Record ~500 B** (code + URL + metadata) → 100M/mo ≈ **50 GB/mo** raw; × retention × replication.
- **Code space:** need `62^n ≥` lifetime URLs → usually **n = 7**.
- Implication: writes fit one primary DB early; **reads need cache/CDN**, not a bigger primary.

### 3. API / interface
- `POST /urls` (or `/api/v1/shorten`) body: `{ "long_url", "custom_alias?", "expires_at?" }` → `{ "short_url": "https://short.ly/{code}" }`
- `GET /{code}` → **302** (or 301) with `Location: <long_url>`; **404** unknown; **410** expired
- Optional: `DELETE /urls/{code}`, `GET /urls/{code}/stats` (analytics — below the line unless scoped in)

### 4. Data model
```
url_mapping(
  short_code  PK  VARCHAR(8),   -- Base62
  long_url        TEXT NOT NULL,
  user_id         BIGINT NULL,
  created_at      TIMESTAMP,
  expires_at      TIMESTAMP NULL,
  is_custom       BOOL
)
```
- Optional reverse index / hash of `long_url` if dedup is required.
- Analytics tables (clicks) live elsewhere — not on the redirect critical path.

### 5. High-level architecture
```
Client → LB / API Gateway
         ├─ Write service  → ID gen (counter range / Snowflake / KGS) → Base62 → DB
         └─ Redirect service → Cache (Redis) → DB (on miss) → 302 Location
                              └─ async click event → Queue → analytics store
```
- Stateless app servers; scale **redirect** fleet >> **write** fleet.
- DB: Postgres/MySQL OK at interview scale with PK on `short_code`; Cassandra/Dynamo if interviewer pushes massive write/partition story.
- Cache-aside + LRU/TTL; CDN/edge optional for viral codes.

### 6. Deep dives & the 2–3 key tradeoffs interviewers probe
1. **Hash+truncate vs counter/Snowflake+Base62:** collisions + retries vs coordination + predictability. Pick one and defend; mention XOR/permutation if sequential codes worry them.
2. **301 vs 302:** browser caching / lower origin load vs analytics + revoke/update. Tie choice to whether clicks must be counted.
3. **Single Redis INCR vs range allocator / Snowflake:** SPOF + hot counter vs unused ranges on crash vs clock skew — CodeKarle/Hello Interview range story is the expected mid-level answer.
4. **Custom alias uniqueness:** strong check on write (`UNIQUE` / conditional put); never let aliases eat the auto-ID namespace.

### 7. Bottlenecks / how you scale it
- **Redirect QPS:** cache hit rate dominates; add Redis cluster, local LRU for ultra-hot keys, CDN for viral links; singleflight to prevent stampede on expiry.
- **DB:** shard by `short_code` hash only if storage/QPS exceeds one primary; read replicas for rare cache-miss storms.
- **ID generator:** pre-allocate ranges so app servers don't hit a global counter every write; Snowflake if multi-region writes.
- **Writes:** still low vs reads — rate-limit creates; validate URL; optional async persistence only if interviewer accepts brief create lag.
- **Expiry cleanup:** TTL in cache ≤ `expires_at`; periodic DB sweeper or lazy 410 on read.
- **Failure:** cache down → degrade to DB with shedding; DB primary down → fail creates, serve redirects from replicas/cache.

## Common follow-ups / gotchas
- "Same long URL shortened twice — same short code or new?" → product choice: hash/dedup vs always-new (campaigns need distinct codes + analytics).
- "How do you stop people enumerating sequential codes?" → randomize/permute IDs, longer codes, auth on sensitive targets, rate-limit redirects — short links are often public by design.
- "Why not UUID in the URL?" → too long; defeats shortening. Encode a compact ID instead.
- "Where do analytics live?" → never on the redirect path; buffer + Kafka/ClickHouse (or similar). Losing some click events is usually OK.
- "Custom alias taken / race?" → DB unique constraint + retry/error; conditional write in NoSQL.
- Drawing Redis but skipping **TTL, eviction, and hot-key stampede** — interviewers poke all three on this question.

## Where it appears
- **Campus / intern / new-grad HLD:** extremely common warm-up or full round (Amazon, Google, Microsoft, Meta, Uber, Atlassian, Flipkart, etc.).
- **Experienced (1–4 YOE):** still asked; depth shifts to ID allocation at multi-region scale, 301/302 + CDN, cache stampedes, abuse.
- **Frequency:** among the **most frequent** HLD design questions — treat as mandatory practice before harder designs (feed, chat, video).
