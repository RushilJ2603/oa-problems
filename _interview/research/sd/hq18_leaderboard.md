# hq18_leaderboard — Design a Gaming Leaderboard

**Interview relevance:** High — Alex Xu *System Design Interview* Vol.2 Ch.10 classic; common at Meta / Google / PayPal / Amazon gaming & social rounds; tests Redis sorted sets, atomic increments, sharding, and real-time vs eventual consistency.
**Type:** HLD-question
**Prereqs:** h03_caching (Redis), h04_databases_indexing, h05_db_scaling, h14_estimation, h10_api_design; helpful: h06_consistency_cap, h08_message_queues, h02_load_balancing; cousin problem: Hello Interview Top-K

## Read / watch (curated, in order)
- [ ] [Real-time Gaming Leaderboard (ByteByteGo / Alex Xu Vol.2 Ch.10)](https://bytebytego.com/courses/system-design-interview/real-time-gaming-leaderboard) — `ByteByteGo` — canonical interview walk-through: scope → SQL fails → Redis ZSET → fixed vs hash sharding → NoSQL alt (course may be gated); TOC proof: [Vol.1 vs Vol.2 chapter list](https://blog.bytebytego.com/p/system-design-interview-books-volume)
- [ ] [Real-time Gaming Leaderboard Design | Chapter 10 (Vol.2)](https://www.youtube.com/watch?v=fPz75ALyDvo) — `ByteByteGo` — free visual narration of the same chapter (ZSET ops, skip list intuition, scale to 500M DAU)
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — the 45-min skeleton (FRs → NFRs → entities → API → HLD → deep dives) you reuse on every design question
- [ ] [Design an Online Game Leaderboard](https://www.hellointerview.com/community/questions/realtime-game-leaderboard/cm4t0qbr9004988ilmum8jm06) — `Hello Interview` — prompt framing (asked at Meta / Google / PayPal): global top, near-me, friends board
- [ ] [Redis Deep Dive (leaderboards section)](https://www.hellointerview.com/learn/system-design/deep-dives/redis) — `Hello Interview` — why ZSET beats SQL for ranking; `ZADD` / `ZREMRANGEBYRANK` patterns
- [ ] [Design YouTube's Top K Videos Feature](https://www.hellointerview.com/learn/system-design/problem-breakdowns/top-k) — `Hello Interview` — related Top-K variant (tumbling windows, approximate vs exact) — useful follow-up vocabulary when interviewer pivots from exact ranks to trending
- [ ] [Redis leaderboard use case](https://redis.io/docs/latest/develop/use-cases/leaderboard/) — `Redis docs` — official product framing: ZSET + Hash metadata, `ZINCRBY`, windowed keys + `EXPIRE`
- [ ] [Redis sorted sets](https://redis.io/docs/latest/develop/data-types/sorted-sets/) — `Redis docs` — skip list + hash table, O(log N) ops; leaderboards called out as the primary use case
- [ ] [How to build a Real-Time Leaderboard with Redis](https://redis.io/tutorials/howtos/leaderboard/) — `Redis docs` — hands-on `ZADD` / `ZREVRANGE` / `ZREVRANK` / `ZINCRBY` demo
- [ ] [Build a real-time gaming leaderboard with Amazon ElastiCache for Redis](https://aws.amazon.com/blogs/database/building-a-real-time-gaming-leaderboard-with-amazon-elasticache-for-redis/) — `AWS` — production-shaped Redis vs MySQL comparison (rank query ~350 ms vs ~9.5 s at 22M rows in their demo); Lambda + API Gateway path
- [ ] [System Design Playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — foundations (scale, cache, DB) you will name inside this design; no dedicated leaderboard episode — use ByteByteGo Ch.10 for the problem itself; channel primer: [System Design Primer](https://www.youtube.com/watch?v=SqcXvc3ZmRU)
- [ ] [InterviewReady — system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` / Gaurav Sen org — curated further-reading dump; companion prep list: [coding-parrot/system_design](https://github.com/coding-parrot/system_design)
- [ ] [Caching for System Design Interviews](https://www.hellointerview.com/learn/system-design/core-concepts/caching) — `Hello Interview` — where Redis sits vs DB; pair with [primer — Cache](https://github.com/donnemartin/system-design-primer#cache)

## Core concepts to master
- **Product shape:** after each match / score event, maintain a ranked list. Core queries: **top-K**, **my rank + score**, optional **K neighbors around me**, optional **friends / regional / time-windowed** boards.
- **Why SQL fails at interview scale:** `ORDER BY score DESC` (or nested `COUNT(*)` for rank) is O(N) / worse under continuous updates; ranks cannot be cheaply cached when every write invalidates order. Redis ZSET keeps order on write.
- **Redis sorted set (ZSET):** member = `user_id`, score = points. Internals = **hash table** (member → score, O(1) `ZSCORE`) + **skip list** (ordered by score). Insert / update / rank / range are **O(log N)** (range + M for the window size).
- **Canonical commands:** `ZINCRBY` (atomic increment — prefer over read-modify-write), `ZADD` (set absolute score), `ZREVRANGE key 0 K-1 WITHSCORES` (top-K), `ZREVRANK` (0-indexed rank from top; +1 for 1-indexed), neighborhood = `ZREVRANGE` around known rank.
- **Server-authoritative scores:** client must **never** write scores directly — game service validates the match result, then leaderboard service updates. Stops MITM / cheat proxies.
- **Durability split:** Redis = hot ranking projection; **RDBMS / event log** = source of truth (point history, rebuild ZSET on Redis loss). Replica + failover for Redis; accept brief lag if you buffer via Kafka.
- **Time windows:** separate keys per window (`lb:global:2026-07`, `lb:weekly:2026-W30`) + `EXPIRE` on daily/weekly; monthly tournament reset = new key (ByteByteGo default).
- **Ties:** product choice — same rank (competition ranking) vs unique rank (lexicographic member tie-break in Redis) vs composite score (points + inverted timestamp). Say which you pick.
- **Sharding tradeoff (the senior probe):** **score-range (fixed) partition** → top-K hits one shard, but players migrate shards on score change; **hash / Redis Cluster** → easy writes, top-K needs **scatter-gather merge** from every shard. Exact global rank on hash shards is expensive — often approximate or maintain a secondary aggregator.
- **Friends board:** don't maintain a ZSET per user; intersect friend IDs with scores (pipeline `ZSCORE` / small local sort) or maintain small per-clique boards if graph is hot.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈40–45 min). Default to ByteByteGo scope unless the interviewer says otherwise.

### 1. Requirements (functional + non-functional) & scale assumptions
**Clarify first:** how is score computed (wins = +1 vs XP)? Real-time or batch OK? Only top-10 or any player's rank? Monthly reset? Tie-break? Friends / regional boards? Anti-cheat?

**Functional (typical Alex Xu / ByteByteGo scope):**
- Display **top 10** (or top K) on the leaderboard.
- Return a **specific user's rank + score**.
- Bonus: **±4 neighbors** around a user.
- Score updates when a player wins a match (server-side).

**Non-functional:**
- **Near-real-time** rank visibility (not nightly batch).
- Low latency reads (top-K and rank ≪ 100 ms p99).
- Scalable / available / durable enough to rebuild after Redis loss.
- Scale class: **~5M DAU / ~25M MAU** unless told otherwise.

**Out of scope (draw the line):** matchmaking ELO math, anti-cheat ML, full social graph — unless asked.

### 2. Back-of-envelope estimation
Alex Xu–style numbers (say them out loud; adjust if interviewer disagrees):

| Assumption | Example |
|---|---|
| DAU / MAU | **5M / 25M** |
| Matches / user / day | **10** |
| Avg concurrent users | 5M / 10⁵ s ≈ **~50/s**; peak **~5×** → **~250/s** |
| Score-update QPS | 50 × 10 ≈ **~500/s** avg; peak **~2.5k/s** |
| Top-10 fetch QPS | ~once per open/day → **~50/s** (reads are cheap vs writes here) |
| ZSET memory | ~26 B/member × 25M ≈ **~650 MB** (+ skip-list overhead ≈ **~1–2 GB**) — **one Redis node** at this scale |

Implication: at 5M DAU a **single Redis ZSET** is enough; sharding is the **100× scale** deep dive (500M DAU → ~65 GB, ~250k QPS).

### 3. API / interface
Internal write (game servers only — not public clients):

```
POST /v1/scores
body: { "user_id": "...", "points": 1 }
→ 200 OK | 400
```

Public / player reads:

```
GET /v1/scores                     → top 10 [{user_id, user_name, rank, score}, ...]
GET /v1/scores/{user_id}           → {user_id, score, rank}
GET /v1/scores/{user_id}/neighbors?k=4  → players rank-4 … rank+4  (optional)
```

Optional later: `GET /v1/scores?window=weekly`, `GET /v1/scores/friends`.

### 4. Data model
**Redis (hot path):**
- Key `leaderboard:{yyyy_mm}` → ZSET of `user_id` → `score`
- Optional Hash `user:{id}` → `{name, avatar, …}` or cache only top-K profiles

**Durable store (MySQL/Postgres or similar):**
```
users(user_id PK, display_name, ...)
points(user_id, delta, created_at, match_id?)   -- audit / rebuild source
```
Rebuild: replay `points` (or latest score snapshot) into a new ZSET on failover.

**Windowed keys:** `lb:daily:{date}`, `lb:weekly:{iso_week}`, `lb:alltime` — write amplifies across active windows.

### 5. High-level architecture / component breakdown
```
Client → Game Service (authoritative match result)
            → Leaderboard Service → Redis ZSET (ZINCRBY)
                                 → durable DB (async or dual-write)

Client → Leaderboard Service → Redis (ZREVRANGE / ZREVRANK)
                             → User DB / profile cache (names, avatars)
```

Optional: Kafka between game and leaderboard if analytics / push / multiple consumers need the same score event.

```
[Match end] → Game svc validate → (optional Queue) → Leaderboard svc
                                                      ├─ ZINCRBY lb:{window}
                                                      └─ append points row
[Read top-K / rank] → Leaderboard svc → Redis → enrich from user store
```

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **SQL ORDER BY vs Redis ZSET:** sorting on read vs maintaining order on write. Nested rank SQL is the trap — reject it for real-time millions of players.
2. **Atomic updates:** `ZINCRBY` (or Lua) vs get-score → add → set. Concurrent match completions must not lose increments.
3. **Fixed score-range shards vs Redis Cluster hash slots:** top-K locality vs write simplicity; explain scatter-gather merge and why exact global `ZREVRANK` across hash shards is hard.
4. **Consistency:** Redis primary for live ranks (eventual vs replica lag); DB for durability. "How fresh?" — seconds of lag usually OK for games unless prize payouts need strong consistency.
5. **Exact vs approximate Top-K:** for trending / huge write fan-in, Count-Min Sketch / heavy-hitters (Hello Interview Top-K) — different problem than exact gaming ranks; know when to switch.

### 7. Bottlenecks / how you scale it
- **Single-node ceiling:** memory (~tens of GB comfortable) and write QPS; past that, shard.
- **Hot top-K reads:** cache serialized top-10 JSON with short TTL / pub-sub invalidate; profile enrichment for top players only.
- **Hash-shard top-K:** parallel `ZREVRANGE 0 K-1` per shard → merge-sort in app (K × num_shards is small).
- **Hash-shard exact rank:** local rank + count of higher-scoring members on other shards (expensive) — or accept approximate percentile for deep ranks.
- **Score-range shards:** maintain user→score map so updates know current shard; on boundary cross, `ZREM` old + `ZADD` new.
- **Redis HA:** primary + replica; AOF/RDB; rebuild from DB if both lost.
- **Write bursts (tournament finals):** queue + batch consumers; shed non-critical neighbor queries.
- **Multi-window write amp:** limit active windows; expire old daily keys.
- **Cheat / abuse:** only trusted game servers call `POST /scores`; idempotent `match_id` to prevent double-count.

## Common follow-ups / gotchas
- "Two players, same score — same rank or not?" → state competition vs dense vs unique ranking; Redis default unique order is lexicographic on member id.
- "Client updates the score?" → never; server-authoritative path only.
- "Redis dies — ranks gone?" → durable point log / DB snapshot + rebuild job; don't treat Redis as sole source of truth.
- "How do friend leaderboards work?" → don't N-way fan-out ZSETs; score-lookup + sort friends, or small clique boards.
- "Daily / weekly / all-time?" → one ZSET key per window; `EXPIRE` on ephemeral keys; write to all active windows.
- "500M DAU?" → must shard; walk fixed-range vs Cluster hash and the scatter-gather tax on global top-K.
- Confusing this with **approximate Top-K / trending** — gaming ranks usually need **exact** positions for the player; trending can be fuzzy.

## Where it appears
- **Campus / new-grad HLD:** common as a "pick the right data structure" question once Redis is in your toolkit; often shorter than feed/chat.
- **Experienced (1–4+ YOE):** Meta / Google / PayPal / Amazon (gaming, social, fantasy sports) — depth on sharding, durability, friends boards, anti-cheat.
- **Frequency:** **high** among Vol.2-style questions; treat as mandatory after caching foundations and before heavier designs (payments, stock exchange).
