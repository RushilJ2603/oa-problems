# HQ04 — News feed / Twitter timeline (fan-out)

**Interview relevance:** High — canonical "design Twitter / Instagram / Facebook News Feed" HLD round at FAANG, Meta PA, and Indian product cos (Flipkart, Uber, Atlassian, etc.); the celebrity / hybrid fan-out tradeoff is the probe that separates mid from senior.
**Type:** HLD-question
**Prereqs:** h03_caching, h05_db_scaling, h08_message_queues, h14_estimation; helpful: h04_databases_indexing, h06_consistency_cap, h02_load_balancing

## Read / watch (curated, in order)
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — interview skeleton using Twitter as the running example (requirements → entities → API → HLD → fan-out deep dive)
- [ ] [Designing INSTAGRAM: System Design of News Feed](https://www.youtube.com/watch?v=QmX2NPkJTKg) — `Gaurav Sen` — ER → services → feed service; push timelines into followers' queues/caches (~24 min)
- [ ] [Design a News Feed System Overview | Chapter 11](https://www.youtube.com/watch?v=1FtPdvoNnBQ) — `ByteByteGo` / Alex Xu Vol.1 — publishing vs retrieval flows; hybrid fan-out overview
- [ ] [Design a News Feed System](https://bytebytego.com/courses/system-design-interview/design-a-news-feed-system) — `ByteByteGo` — full Ch.11: APIs, fanout service + MQ workers, ID-only feed cache, hydration, 5-layer cache
- [ ] [Design Facebook's News Feed](https://www.hellointerview.com/learn/system-design/problem-breakdowns/fb-news-feed) — `Hello Interview` — follow graph + posts GSI → precomputed feed; when push becomes necessary
- [ ] [Interview question: Design Twitter (Episode 5)](https://blog.bytebytego.com/p/interview-question-design-twitter) — `ByteByteGo` — write API → fanout → Redis → Timeline service; Earlybird / Blender for search (2013 talk summary)
- [ ] [system-design-primer — Design the Twitter timeline and search](https://github.com/donnemartin/system-design-primer/tree/master/solutions/system_design/twitter) — `primer` — home vs user timeline, fanout bottleneck, search cluster sketch
- [ ] [The Architecture Twitter Uses… (150M users, 300K QPS)](https://highscalability.com/the-architecture-twitter-uses-to-deal-with-150m-active-users/) — `High Scalability` — Raffi Krikorian talk gloss: write fanout, Redis ≤800 IDs, hybrid pull for celebrities, race with @replies
- [ ] [Timelines at Scale (InfoQ)](https://www.infoq.com/presentations/Twitter-Timeline-Scalability/) — `InfoQ` — original talk; watch after the High Scalability notes
- [ ] [How Twitter Uses Redis to Scale](https://highscalability.com/how-twitter-uses-redis-to-scale-105tb-ram-39mm-qps-10000-ins/) — `High Scalability` — Timeline as Redis lists / hybrid lists; why RAM + replication dominate the feed store
- [ ] [Design Decisions for Scaling Your High Traffic Feeds](https://highscalability.com/design-decisions-for-scaling-your-high-traffic-feeds/) — `High Scalability` — Postgres → Redis push → selective fanout; cites Twitter / Yahoo Feeding Frenzy
- [ ] [Feeding Frenzy: Selectively Materializing Users' Event Feeds (VLDB)](https://www.vldb.org/pvldb/vol4/p1055-silberstein.pdf) — `Yahoo Research` — when to push vs pull scientifically (selective materialization)
- [ ] [twitter-archive/snowflake](https://github.com/twitter-archive/snowflake) — `Twitter` — time-sortable 64-bit IDs (timeline sort without a separate created_at index)
- [ ] [Capacity Planning](https://blog.bytebytego.com/p/capacity-planning) — `ByteByteGo` — social news-feed QPS / bandwidth worked example
- [ ] [How News Feed Works (Facebook Help)](https://www.facebook.com/help/327131014036297/) — `Facebook` — product definition cited by Alex Xu (what "feed" means to users)
- [ ] *Designing Data-Intensive Applications* ch.11 (Stream Processing) + ch.5 (Replication) — `DDIA` — MQ/log backbone for fanout workers; read-your-writes vs eventual delivery lag — [dataintensive.net](https://dataintensive.net/)
- [ ] [InterviewReady — system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` / Gaurav Sen — link dump; pair with [System Design playlist](https://www.youtube.com/playlist?list=PLLcTitwD4tE3RiFws0bYAj9LFbATrSYMS)

## Core concepts to master
- **Home timeline vs user timeline:** home = merge of people you follow; user = one author's posts (profile). Home is the hard fan-out problem; user timeline is a simpler append + read-by-author.
- **Read-heavy product:** timeline reads ≫ tweet writes (often ~50:1+). Optimize the read path (precompute / cache IDs) even if writes get expensive.
- **Fan-out-on-write (push):** on post, write `tweet_id` into each follower's precomputed home timeline (Redis list/ZSET). Reads ≈ O(1); write cost ≈ O(followers).
- **Fan-out-on-read (pull):** on feed load, query recent posts of everyone you follow and merge. Cheap writes; expensive/slow reads as follow count grows.
- **Hybrid (the expected answer):** push for normal accounts; **skip push for celebrities** (follower count above a threshold); at read time merge precomputed timeline + recent celebrity tweets. Threshold is tunable (~10K–100K historically discussed).
- **Store IDs, hydrate later:** timeline cache holds `(tweet_id[, author_id])` only (~800 recent). Content hydration from tweet/user caches (or DB) after ID fetch — keeps RAM bounded.
- **Async fan-out:** API persists tweet → enqueue (Kafka/MQ) → fan-out workers. User gets fast 200/201; delivery is eventually consistent (seconds, p99 can be worse for huge fanouts).
- **Social graph service:** need both "who do I follow?" (read path / celebrity merge) and "who follows me?" (write fan-out). Graph store / dual indexes; hot celebrity follower lists are themselves a bottleneck.
- **Snowflake-style IDs:** roughly time-ordered unique IDs → chronological sort without relying on clocks at merge time; helps pagination cursors.
- **Inactive users:** skip push to cold followers (waste); rebuild/reconstruct timeline on return (graph + disk tweets → Redis).
- **Deletes / visibility:** delete/unpublish must remove IDs from many timelines or filter at hydrate; mute/block applied on fan-out filter or read merge.
- **Ranking is optional in interviews:** start reverse-chronological; mention candidate generation → light/heavy ranker only if asked (modern "For You").

## Practice — how it's asked & how to attack it
Walk this skeleton on the whiteboard (~45 min). Scope: **post + follow + home timeline** (defer DMs, Trends, ads unless asked).

### 1. Requirements & scale assumptions
**Functional**
- Post tweet (text; optional media URL)
- Follow / unfollow (uni-directional)
- Home timeline: tweets from followees, reverse chronological, paginated
- User timeline: tweets by one user

**Non-functional (say out loud)**
- High availability over strong consistency for feed freshness (eventual OK for a few seconds)
- Home timeline p99 latency target ~100–200 ms after hydrate
- Scale: e.g. 100–300M DAU; read:write ≫ 1; power-law followers (celebrities)

**Out of scope (explicitly cut):** full-text search, Trends, DMs, algorithmic For You — unless interviewer pulls them in.

### 2. Back-of-envelope estimation
Pick round numbers and state assumptions:
- 200M DAU; avg 2 tweets/user/day → ~400M tweets/day ≈ ~5K writes/s avg (10–20K peak)
- Timeline reads: each user opens feed ~10×/day → ~20B reads/day ≈ ~200K+ QPS avg; peak higher
- Avg ~200 followers; celebrity outliers 10M–100M → pure push write amplification is the cliff
- Home cache: 800 × 16–24 B ≈ ~15–20 KB/user; active users in Redis → multi-TB RAM cluster (why IDs only)

Use estimates to **justify** hybrid fan-out + Redis timelines — not to flex arithmetic.

### 3. API / interface
REST default; auth from token (never trust `user_id` in body for "me"):

```
POST   /v1/tweets                  { "text": "...", "media_ids": [] } → Tweet
GET    /v1/tweets/{tweet_id}       → Tweet
DELETE /v1/tweets/{tweet_id}

POST   /v1/follows                 { "followee_id": "..." }
DELETE /v1/follows/{followee_id}

GET    /v1/users/{user_id}/tweets?cursor=&limit=   → user timeline
GET    /v1/feed?cursor=&limit=                     → home timeline (Tweet[])
```

Cursor = last `tweet_id` (Snowflake) or timestamp — not fragile offsets.

### 4. Data model
**Entities:** User, Tweet, Follow, (HomeTimeline entry = cached IDs).

| Store | Shape | Notes |
| --- | --- | --- |
| Tweet DB | `tweet_id` PK, `author_id`, text, media refs, created_at | Shard by `tweet_id` or `author_id` (user timeline locality) |
| User timeline | list/table by `author_id` + time/`tweet_id` | Profile page; also celebrity pull source |
| Follow graph | edges `(follower_id → followee_id)` + reverse index | Fan-out needs followers-of(author); feed merge needs followees-of(me) |
| Home timeline cache | Redis list/ZSET `home:{user_id}` → tweet IDs, cap ~800 | Push target; LTRIM/ZREMRANGEBYRANK |
| Tweet / user object cache | `tweet:{id}`, `user:{id}` | Hydration; CDN for media blobs |

### 5. High-level architecture
**Write path:** Client → LB → API → Tweet Service (persist + user timeline) → emit `tweet.created` to MQ → Fan-out workers → Graph Service (followers) → if not celebrity, `LPUSH`/`ZADD` into each active follower's Redis home timeline → Notification service (optional).

**Read path:** Client → LB → API → Timeline/Feed Service → read Redis home IDs → fetch celebrity followees' recent tweets (user timelines) → merge/sort by id/time → hydrate tweet+user objects from cache/DB → return page.

**Boxes:** API tier (stateless), Tweet service, Graph service, Fan-out workers, Timeline service, Redis timeline cluster, Tweet/User DB + caches, Object storage + CDN (media), MQ (Kafka).

### 6. Deep dives & key tradeoffs (interviewers probe these)
1. **Push vs pull vs hybrid** — push = fast reads, celebrity write storm + inactive waste; pull = slow reads at follow-scale; hybrid = complexity (two paths + merge) but is the production answer. Name the threshold and that it's operationally tuned.
2. **Sync fan-out vs MQ workers** — never block the post HTTP on millions of Redis writes; at-least-once workers need idempotent timeline inserts (dedupe by tweet_id).
3. **Cache content vs IDs** — IDs keep RAM feasible and let one tweet object update (edits/counts) without rewriting millions of timelines; hydration adds a batch get stage (watch N+1).
4. **Celebrity / hot partition** — huge follower list fetch + fan-out lag; replies can arrive before the original (race). Mitigate: pull celebrities, prioritize active followers, reorder by Snowflake id at serve time.
5. **Consistency** — feed is eventually consistent; discuss read-your-writes for the author (show own tweet immediately from user timeline / optimistic UI).

### 7. Bottlenecks / how you scale
- **Fan-out workers / MQ lag** — scale consumer groups; shard work by author or follower ranges; backpressure + lag alerts; DLQ for poison tweets
- **Redis timeline cluster** — shard by `user_id`; replicate; reconstruct on miss from graph + tweet store; don't keep inactive homes forever
- **Graph service** — cache follower lists; paginate huge celebrity follower sets; consider not materializing full push for them at all
- **Hydration / tweet store** — batch multi-get; tweet cache; CDN for media; avoid joining in one giant SQL at request time
- **Hot celebrities tweeting each other** — hybrid pull; rate-limit fan-out priority; accept higher p99 delivery
- **Further scale knobs:** skip inactive, cap home length, multi-DC with local Redis + async replicate, search as a separate inverted-index path (Earlybird-style) if asked

## Common follow-ups / gotchas
- **"What about Justin Bieber / Lady Gaga?"** — if you only drew pure push, you fail the probe; switch those accounts to pull + merge.
- **Reply before original** — long fan-out queues reorder UX; sort by id and/or delay reply fan-out until parent is visible.
- **Unfollow / mute / block / delete tweet** — push copies are stale; filter at read or issue async removals; deletes are fan-out's ugly twin.
- **Inactive user returns** — empty/missing Redis home → reconstruction job; don't push to them while cold.
- **"Just query SQL JOIN followers × tweets every refresh"** — dies at read QPS; use it only to motivate precompute.
- **Pagination with OFFSET** — breaks under inserts; use cursor on `tweet_id`/time.
- **Storing full tweet text in every home timeline** — RAM explosion + painful edits; IDs + hydrate.
- **Search / Trends conflated with home timeline** — different path (index on write, scatter-gather on read); mention only if asked.

## Where it appears
- **Campus / new-grad HLD:** extremely common as "Design Twitter / Instagram / News Feed"; expected signal is hybrid fan-out + Redis ID timelines + async workers — not Manhattan internals.
- **Experienced / Meta PA / mid-level:** same prompt with deeper probes — celebrity threshold, reconstruction, delete/fan-in, ranking candidates, multi-DC, graph hotspots.
- **Frequency:** among the top 5 product HLD questions; sister prompts are notification fan-out and "design Facebook News Feed" (same core tradeoff).
