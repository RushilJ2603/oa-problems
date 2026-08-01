# HQ15 — Design Instagram (photo-sharing)

**Interview relevance:** High — canonical 45-min "Design Instagram / photo-sharing" HLD at Meta PA, FAANG, Snap/Pinterest cousins, and Indian product cos; probes **media pipeline (presign → object store → CDN)** plus **hybrid feed fan-out** (same celebrity cliff as Twitter/News Feed).
**Type:** HLD-question
**Prereqs:** h03_caching, h05_db_scaling, h08_message_queues, h11_storage, h14_estimation; helpful: hq04_news_feed, h02_load_balancing, h06_consistency_cap, h01_networking

## Read / watch (curated, in order)
- [ ] [Design a Photo Sharing App Like Instagram](https://www.hellointerview.com/learn/system-design/problem-breakdowns/instagram) — `Hello Interview` — best interview skeleton for this prompt (post + follow + chronological feed; 500M DAU / 100M posts framing; deep dives: feed latency, large media, scale)
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — 45-min structure (FRs → NFRs → entities → API → HLD → deep dives) reused on every design Q
- [ ] [Handling Large Blobs](https://www.hellointerview.com/learn/system-design/patterns/large-blobs) — `Hello Interview` — **presigned upload**, never push photo bytes through API servers; CDN download path
- [ ] [Designing INSTAGRAM: System Design of News Feed](https://www.youtube.com/watch?v=QmX2NPkJTKg) — `Gaurav Sen` — ER → services → push timelines + celebrity fan-out (~24 min); playlist: [System Design](https://www.youtube.com/playlist?list=PLLcTitwD4tE3RiFws0bYAj9LFbATrSYMS)
- [ ] [Design a News Feed System Overview | Chapter 11](https://www.youtube.com/watch?v=1FtPdvoNnBQ) — `ByteByteGo` / Alex Xu Vol.1 — publishing vs retrieval; hybrid fan-out overview (same core as Instagram home)
- [ ] [Design a News Feed System](https://bytebytego.com/courses/system-design-interview/design-a-news-feed-system) — `ByteByteGo` — full Ch.11: APIs, fanout + MQ, ID-only feed cache, hydration, CDN for media; explicitly maps to Instagram/Twitter-style feeds
- [ ] [Design Facebook's News Feed](https://www.hellointerview.com/learn/system-design/problem-breakdowns/fb-news-feed) — `Hello Interview` — follow graph + precomputed feed; when push becomes necessary (sister problem)
- [ ] [Design of Instagram (Grokking / Educative)](https://www.educative.io/courses/grokking-the-system-design-interview/design-of-instagram) — `Grokking` — API + storage schema + push/pull/hybrid timeline chapter
- [ ] [8.6 Design a photo/video sharing platform (Instagram)](https://www.systemdesigninterview.com/guides/system-design-interview-handbook/86-design-a-photovideo-sharing-platform-instagram) — `System Design Interview` handbook — scoped FRs (upload + home feed + follow/like/comment); hybrid fan-out writeup
- [ ] [Instagram Architecture: 14M users, Terabytes of Photos…](https://highscalability.com/instagram-architecture-14-million-users-terabytes-of-photos/) — `High Scalability` — gloss of early IG stack (Django, Postgres, Redis feeds, S3, CloudFront, Gearman fan-out)
- [ ] [What Powers Instagram: Hundreds of Instances…](https://web.archive.org/web/20120731051222/http://instagram-engineering.tumblr.com/post/13649370142/what-powers-instagram-hundreds-of-instances) — `Instagram Eng` (Wayback) — canonical early production write-up the High Scalability notes summarize
- [ ] [Instagram Architecture Update: What’s new with Instagram?](https://highscalability.com/instagram-architecture-update-whats-new-with-instagram/) — `High Scalability` — Krieger talk notes: Redis feed lists of media IDs, memcached hydrate, logical Postgres sharding
- [ ] [Sharding & IDs at Instagram (clip)](https://jaytaylor.com/notes/node/1354039963000.html) — `Instagram Eng` (archived clip) — 64-bit time+shard+seq IDs; pair with [Sharding @ Instagram (SFPUG PDF)](https://media.postgresql.org/sfpug/instagram_sfpug.pdf) — Mike Krieger slides
- [ ] [Designing Instagram](https://highscalability.com/designing-instagram/) — `High Scalability` — interview-style walkthrough: async fan-out for non-celebrities, pull merge for whales
- [ ] [Interview question: Design Twitter (Episode 5)](https://blog.bytebytego.com/p/interview-question-design-twitter) — `ByteByteGo` — write → fanout → Redis timeline service (same celebrity merge pattern)
- [ ] [system-design-primer — Design the Twitter timeline and search](https://github.com/donnemartin/system-design-primer/tree/master/solutions/system_design/twitter) — `primer` — home vs user timeline, fanout bottleneck sketch; primer also lists Instagram under photo-sharing exercises: [donnemartin/system-design-primer](https://github.com/donnemartin/system-design-primer)
- [ ] [The Architecture Twitter Uses… (150M users, 300K QPS)](https://highscalability.com/the-architecture-twitter-uses-to-deal-with-150m-active-users/) — `High Scalability` — hybrid pull for celebrities; Redis ≤800 IDs
- [ ] [Feeding Frenzy: Selectively Materializing Users' Event Feeds (VLDB)](https://www.vldb.org/pvldb/vol4/p1055-silberstein.pdf) — `Yahoo Research` — when push vs pull is scientifically worth it
- [ ] [twitter-archive/snowflake](https://github.com/twitter-archive/snowflake) — `Twitter` — time-sortable 64-bit IDs (cousin of Instagram’s ID layout; timeline sort / cursors)
- [ ] [Capacity Planning](https://blog.bytebytego.com/p/capacity-planning) — `ByteByteGo` — social feed QPS / bandwidth worked example
- [ ] [Upload with a presigned URL](https://docs.aws.amazon.com/AmazonS3/latest/userguide/PresignedUrlUploadObject.html) / [Multipart upload overview](https://docs.aws.amazon.com/AmazonS3/latest/userguide/mpuoverview.html) — `AWS docs` — direct client→blob path + resumable uploads
- [ ] [Why are Content Delivery Networks (CDN) so Popular?](https://bytebytego.com/guides/why-are-content-delivery-networks-cdn-so-popular/) — `ByteByteGo` — edge cache for immutable media URLs
- [ ] [Caching for System Design Interviews](https://www.hellointerview.com/learn/system-design/core-concepts/caching) — `Hello Interview` — multi-layer cache vocabulary (feed IDs, post objects, CDN)
- [ ] [How to Design a System like Instagram? (Alex Xu)](https://www.linkedin.com/posts/alexxubyte_systemdesign-coding-interviewtips-activity-7305252479397482496-gYrN) — `ByteByteGo` — short visual checklist (Postgres metadata, Cassandra hot writes, object store + CDN, async workers)
- [ ] [InterviewReady — system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` / Gaurav Sen — link dump after the core path; book site: [dataintensive.net](https://dataintensive.net/) (`DDIA` ch.5 replication / ch.11 streams for fan-out workers)

## Core concepts to master
- **Two products glued together:** (1) **media plane** — upload, resize/variants, object storage, CDN; (2) **social/feed plane** — follow graph, post metadata, home timeline fan-out. Don’t design one without the other.
- **Never put photo bytes on the API hot path:** API issues **presigned** (or session) upload URLs → client PUTs to S3/GCS → async workers create thumbnails/WebP/AVIF variants → metadata flips to `ready` → CDN serves immutable URLs.
- **Metadata vs blobs:** caption, author, status, CDN URLs live in DB/cache; bytes live in object storage. Feed stores **post/media IDs**, not image binaries.
- **Home feed vs profile grid:** home = merge of followees (hard fan-out); profile = one author’s posts (append + read-by-author / shard by `user_id`).
- **Read-heavy:** feed opens and image views ≫ uploads. Optimize read path (precomputed ID timelines + CDN); accept expensive async writes.
- **Fan-out-on-write (push):** on publish, push `post_id` into each follower’s Redis list/ZSET. Fast reads; write cost ≈ O(followers).
- **Fan-out-on-read (pull):** on feed load, fetch recent posts of followees and merge. Cheap writes; slow at high follow counts.
- **Hybrid (expected answer):** push for normal accounts; **skip push for celebrities** above a follower threshold; at read time merge precomputed timeline + recent celebrity posts. Threshold is operational (~10K–1M discussed; tune to fan-out lag).
- **IDs only in feed cache:** ~hundreds of recent `(post_id)` per user; hydrate post+user objects in a batch get. Keeps RAM feasible and edits/counts consistent.
- **Async everything after upload ACK:** image processing, fan-out, notifications via MQ/workers (Kafka/SQS/Gearman-class). Post HTTP returns fast; delivery is eventually consistent.
- **Time-sortable IDs:** Instagram-style 64-bit (time | shard | seq) or Snowflake — chronological feed sort + cursor pagination without fragile `OFFSET`.
- **CDN is the media product:** 95%+ media hits should be edge; origin shield / immutable content-hash URLs avoid stampede + purge hell.
- **Ranking optional:** start reverse-chronological; mention light ranking / “For You” only if asked.

## Practice — how it's asked & how to attack it
Walk this skeleton on the whiteboard (~45 min). Prompt variants: “Design Instagram”, “Design a photo-sharing service”, “Design Pinterest” (same media+feed core). Scope: **upload photo + follow + home feed** in; Stories, Reels, DMs, Explore/ML, Live usually out unless asked.

### 1. Requirements & scale assumptions
**Functional (in)**
- Upload photo (optional short video) + caption → publish to followers
- Follow / unfollow (uni-directional)
- Home feed: posts from followees, reverse chronological, paginated
- Profile: user’s own posts grid

**Non-functional (say out loud)**
- Feed p99 latency target ~200–500 ms after hydrate (Hello Interview: <500 ms)
- Media: photos up to ~8 MB (interview framing); global low-latency image delivery via CDN
- Availability over strong consistency for feed freshness (few seconds lag OK)
- Scale example: **500M DAU, ~100M posts/day** (Hello Interview) — or state your own and stick to them

**Out of scope (cut explicitly):** likes/comments (mention as counters if asked), hashtag search, Stories TTL, Reels ABR, ads, full ranking.

### 2. Back-of-envelope estimation
Pick round numbers and use them to **justify** architecture:
- 100M posts/day ≈ ~1.2K writes/s avg (5–10× peak)
- Avg photo ~200–500 KB raw → tens of TB/day before variants; 3–5 resized variants multiply storage
- Feed reads: each DAU opens home ~10×/day → billions of reads/day → **100K+ QPS** class; image GETs are even higher → **CDN**, not API
- Avg ~200–500 followers; celebrities 10M–100M → pure push write amplification is the cliff
- Home cache: 800 × ~16–24 B IDs ≈ ~15–20 KB/user; active users in Redis → multi-TB RAM (why IDs only)

### 3. API / interface
REST default; auth from token (never trust `user_id` in body for “me”):

```
POST   /v1/posts/upload-session     → { post_id, presigned_urls[], expires_at }
POST   /v1/posts/{post_id}/complete { "caption": "..." }  → mark uploaded; enqueue process
GET    /v1/posts/{post_id}          → Post (CDN media URLs when ready)
DELETE /v1/posts/{post_id}

POST   /v1/follows                  { "followee_id": "..." }
DELETE /v1/follows/{followee_id}

GET    /v1/users/{user_id}/posts?cursor=&limit=   → profile grid
GET    /v1/feed?cursor=&limit=                    → home feed (Post[])
```

Cursor = last `post_id` (time-sortable) — not `OFFSET`. Client fetches image bytes **directly from CDN**, not through API.

### 4. Data model
**Entities:** User, Post/Media, Follow, (HomeTimeline = cached IDs).

| Store | Shape | Notes |
| --- | --- | --- |
| Post / metadata DB | `post_id` PK, `author_id`, caption, status (`uploading`/`processing`/`ready`), media CDN URLs, created_at | Shard by `post_id` or `author_id` (profile locality) |
| User timeline / profile | list by `author_id` + time/`post_id` | Profile grid; celebrity pull source |
| Follow graph | `(follower_id → followee_id)` + reverse index | Fan-out needs followers-of(author); merge needs followees-of(me) |
| Home timeline cache | Redis list/ZSET `home:{user_id}` → post IDs, cap ~800 | Push target; LTRIM/ZREMRANGEBYRANK |
| Post / user object cache | `post:{id}`, `user:{id}` | Hydration after ID fetch |
| Object storage + CDN | `raw/{post_id}`, `var/{post_id}/{size}.webp` | Immutable keys; CDN origin = processed bucket |

Early Instagram reality check (interview color, not requirement): Postgres metadata + Redis feeds + S3 + CloudFront + async workers.

### 5. High-level architecture
**Upload / publish path:** Client → LB → API (create post metadata `uploading` + presign) → client uploads to object storage → `complete` → MQ → **Media workers** (resize/encode variants, write CDN-ready objects) → status `ready` → emit `post.published` → **Fan-out workers** → Graph Service (followers) → if not celebrity, `LPUSH`/`ZADD` into active followers’ Redis homes → optional Notification service.

**Read / feed path:** Client → LB → Feed Service → read Redis home IDs → pull recent posts from celebrity followees’ user timelines → merge/sort by id/time → hydrate post+user from cache/DB → return page with **CDN URLs**. Client renders images from CDN.

**Boxes:** API tier (stateless), Media processing workers, Post/User service, Graph service, Fan-out workers, Feed/Timeline service, Redis timeline cluster, Metadata DB + caches, Object storage, CDN, MQ (Kafka).

### 6. Deep dives & key tradeoffs (interviewers probe these)
1. **Push vs pull vs hybrid** — push = fast scroll, celebrity write storm + inactive waste; pull = slow reads; hybrid = two paths + merge but is the production answer. Name a threshold and that ops tunes it.
2. **Presigned direct upload vs proxy through API** — proxy simplifies auth but melts app servers / bandwidth; direct upload + short-lived URLs is the expected pattern for multi-MB photos.
3. **Eager vs lazy image variants** — generate common sizes on upload (fast first paint everywhere, more CPU/storage) vs on-demand rare sizes (cheaper, worse cold latency). Interviews usually eager 2–4 sizes.
4. **Sync fan-out vs MQ workers** — never block publish HTTP on millions of Redis writes; at-least-once workers need idempotent timeline inserts (dedupe by `post_id`).
5. **Consistency** — feed eventually consistent; **read-your-writes** for author via profile timeline / optimistic UI; media not visible in feed until `ready`.

### 7. Bottlenecks / how you scale
- **CDN / origin** — viral post stampede: edge TTL + origin shield; immutable URLs; don’t invalidate whole trees on caption edits
- **Fan-out workers / MQ lag** — scale consumer groups; skip inactive users; prioritize active followers; alert on lag; DLQ poison posts
- **Celebrity / hot partition** — skip push; paginate huge follower lists; rate-limit fan-out priority for near-threshold accounts
- **Redis timeline cluster** — shard by `user_id`; reconstruct on miss from graph + post store; cap length; don’t keep cold homes forever
- **Graph service** — cache hot follower lists; dual indexes (followers / following)
- **Hydration / metadata store** — batch multi-get; post cache; shard by author for profile; avoid giant SQL JOINs per refresh
- **Media workers** — autoscale on queue depth; idempotent processing; quarantine failed encodes without blocking metadata
- **Further knobs:** multi-DC local Redis + async replicate, separate search/Explore index if asked, Stories as TTL’d side cache if asked

## Common follow-ups / gotchas
- **"What about a celebrity with 100M followers?"** — if you only drew pure push, you fail; switch those accounts to pull + merge at read.
- **Uploading through the app server** — classic trap; move to presigned/direct-to-blob and keep API on metadata.
- **Storing full images or captions in every home timeline** — RAM explosion + painful edits; IDs + hydrate + CDN URLs.
- **Delete / unfollow / mute / private account** — push copies go stale; filter at hydrate or async remove; privacy checks before serving.
- **Inactive user returns** — missing Redis home → reconstruction job; don’t fan-out to cold users forever.
- **Pagination with OFFSET** — breaks under inserts; cursor on time-sortable `post_id`.
- **"Just SQL JOIN followers × posts every refresh"** — dies at read QPS; use it only to motivate precompute.
- **Stories / Reels / Explore conflated with home feed** — different TTLs, ABR, or ML retrieval; mention only if asked.
- **Exactly-once fan-out** — say at-least-once + idempotent ZADD/dedupe; don’t invent exactly-once MQ magic.

## Where it appears
- **Campus / new-grad HLD:** extremely common as “Design Instagram”; expected signal is **presigned media + CDN** and **hybrid fan-out + Redis ID timelines + async workers** — not Meta’s full ranking stack.
- **Experienced / Meta PA / mid-level:** same prompt with deeper probes — celebrity threshold, media variant ladder, reconstruction, delete/privacy, multi-DC, graph hotspots, light ranking.
- **Frequency:** top-tier product HLD; sister prompts are News Feed / Twitter timeline (hq04), Dropbox-style large blobs, and YouTube (heavier video/ABR).
