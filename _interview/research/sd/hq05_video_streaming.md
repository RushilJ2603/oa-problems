# hq05 — Design Video Streaming (YouTube / Netflix)

**Interview relevance:** High — canonical 45-min HLD at FAANG + Indian product cos (Meta, Google, Amazon, Netflix, Uber, Flipkart); tests blob upload, async pipelines, CDN, and ABR more than novel algorithms.
**Type:** HLD-question
**Prereqs:** h01_networking, h02_load_balancing, h03_caching, h08_message_queues, h11_storage, h14_estimation

## Read / watch (curated, in order)
- [ ] [Design a Video Streaming Platform Like YouTube](https://www.hellointerview.com/learn/system-design/problem-breakdowns/youtube) — `Hello Interview` — best interview walk-through: requirements → presigned upload → segment+manifest ABR → DAG transcoding → CDN scale
- [ ] [System Design: Design YouTube](https://www.youtube.com/watch?v=jWRW2xGMqSw) — `ByteByteGo` — ~7 min visual of upload DAG, HLS/DASH manifests, CDN streaming (~51k+ views)
- [ ] [EP130: Design a System Like YouTube](https://blog.bytebytego.com/p/ep130-design-a-system-like-youtube) — `ByteByteGo` — 9-step upload → transcode → CDN diagram; pair with paid depth: [Design YouTube (SDI Vol)](https://bytebytego.com/courses/system-design-interview/design-youtube)
- [ ] [How NETFLIX onboards new content: Video Processing at scale](https://www.youtube.com/watch?v=x9Hrn0oNmJM) — `Gaurav Sen` — chunking, parallel encode, S3 origin, Open Connect ISP caches (~10 min)
- [ ] [Design a File Storage Service Like Dropbox](https://www.hellointerview.com/learn/system-design/problem-breakdowns/dropbox) — `Hello Interview` — same large-blob pattern: multipart + presigned URL (reuse for video upload)
- [ ] [system-design-primer — Content delivery network](https://github.com/donnemartin/system-design-primer#content-delivery-network) — `primer` — push vs pull CDN, TTL; pair with [CDN caching](https://github.com/donnemartin/system-design-primer#cdn-caching)
- [ ] [Caching for System Design Interviews](https://www.hellointerview.com/learn/system-design/core-concepts/caching) — `Hello Interview` — CDN as geo edge cache for media; when to introduce it in interviews
- [ ] [Why are Content Delivery Networks (CDN) so Popular?](https://bytebytego.com/guides/why-are-content-delivery-networks-cdn-so-popular/) — `ByteByteGo` — edge request flow; pair with [How CloudFront delivers content](https://docs.aws.amazon.com/AmazonCloudFront/latest/DeveloperGuide/HowCloudFrontWorks.html)
- [ ] [Adaptive bitrate streaming](https://en.wikipedia.org/wiki/Adaptive_bitrate_streaming) — `Wikipedia` — ABR vocabulary; then [HLS](https://en.wikipedia.org/wiki/HTTP_Live_Streaming) + [DASH](https://en.wikipedia.org/wiki/Dynamic_Adaptive_Streaming_over_HTTP)
- [ ] [Open Connect Overview (PDF)](https://openconnect.netflix.com/Open-Connect-Overview.pdf) — `Netflix` — why Netflix built its own CDN inside ISPs; site: [openconnect.netflix.com](https://openconnect.netflix.com/)
- [ ] [Distributing Content to Open Connect](https://netflixtechblog.com/distributing-content-to-open-connect-3e3e391d4dc9) — `Netflix TechBlog` — fill / placement at OCAs; optional: [Content Popularity for Open Connect](https://netflixtechblog.com/content-popularity-for-open-connect-b86d56f613b)
- [ ] [Uploading and copying objects using multipart upload](https://docs.aws.amazon.com/AmazonS3/latest/userguide/mpuoverview.html) — `AWS docs` — resumable multi-GB uploads (ETag / CompleteMultipartUpload)
- [ ] [YouTube Architecture](https://highscalability.com/youtube-architecture/) — `High Scalability` — classic early YouTube scale notes; pair with [YouTube scalability (talk)](https://www.youtube.com/watch?v=w5WVu624fY8)
- [ ] [InterviewReady system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` / Gaurav Sen link dump — browse CDN / storage / queues sections after the core walk-through

## Core concepts to master
- **Two planes:** upload/transcode (write-heavy, async, latency-tolerant) vs playback (read-heavy, sync, latency-critical). Never push video bytes through your API servers on the hot path.
- **Presigned / multipart upload:** client uploads chunks directly to object storage (S3/GCS); API only issues URLs + stores metadata. Enables resumability for 10s-of-GB files.
- **Transcoding DAG:** raw → split segments → parallel encode (bitrate ladder: 360p…4K, codecs H.264/VP9/AV1) → thumbnails / audio → package HLS/DASH → write manifests. Orchestrate with queue + workers (Kafka/SQS + FFmpeg fleet).
- **Manifests:** primary manifest lists renditions; media manifests list ~2–10s segments. Player fetches tiny index first, then segments by URL.
- **Adaptive bitrate (ABR):** client measures throughput / buffer health and switches quality per segment (aligned keyframes). Server just serves immutable HTTP objects.
- **CDN is the product:** 95%+ of segment traffic should hit edge (pull CDN or Netflix-style Open Connect inside ISPs). Origin shield / tiered cache protects blob storage from viral stampedes.
- **Metadata vs media:** titles, owners, status, manifest URL in DB + Redis; blobs in object storage. Point lookups by `videoId`; search/recs are optional below-the-line.
- **Hot video:** viral title → metadata cache + multi-replica; segments warm at edge (or pre-push first N seconds of popular rung).
- **YouTube vs Netflix nuance:** UGC + long-tail + pull CDN (YouTube) vs finite catalog + proactive fill to ISP appliances (Netflix Open Connect). Interview answer usually starts YouTube-shaped, then contrast.
- **Cost levers:** CDN egress dominates; codec efficiency, ladder width, cold-storage tiers, and “encode popular formats first” matter at staff depth.

## Practice — how it's asked & how to attack it
Prompt variants: “Design YouTube”, “Design Netflix”, “Design a video streaming service”. Scope with interviewer: VOD upload+watch in; live, ads, full recommendations usually out unless asked.

1. **Requirements & scale assumptions**
   - **Functional (in):** upload video; stream/watch with start in ~2–3s; resumable upload.
   - **Out / below line unless asked:** comments, search, recommendations, live, DRM, moderation.
   - **Non-functional:** high availability, global low-latency playback, multi-device / variable bandwidth, scale to ~1M uploads/day and ~100M watches/day (Hello Interview framing) or state your own numbers and stick to them.
   - Clarify YouTube-like UGC vs Netflix-like catalog; it changes CDN fill strategy.

2. **Back-of-envelope estimation**
   - Uploads: 1M/day ≈ 12/sec average; peak 10×. Avg raw size ~100–500 MB → tens of PB/year raw before encoding.
   - Storage multiplier: each title → many renditions × segments (often 5–10×+ raw depending on ladder).
   - Watch QPS: 100M watches/day ≈ ~1k starts/sec avg; concurrent viewers and bitrate (e.g. 3–5 Mbps) drive **egress Tbps**, not API QPS — hence CDN.
   - Transcode CPU: encode is the write-path bottleneck; size worker pool from upload rate × encode-minutes-per-video.

3. **API / interface**
   - `POST /videos` → create metadata (`processing`), return `videoId` + **presigned multipart** upload URLs (or `POST /videos/{id}/upload-urls`).
   - `PATCH /videos/{id}/parts` (optional) → mark parts uploaded / resume state.
   - `POST /videos/{id}/complete` → finalize multipart; enqueue transcode.
   - `GET /videos/{id}` → metadata + **manifest URL** (CDN), status (`processing` | `ready`).
   - Playback: player GETs manifest + segments **directly from CDN** (not through API). Optional: `POST /videos/{id}/views` async.

4. **Data model**
   - `User(user_id, …)`
   - `Video(video_id PK, uploader_id, title, description, status, duration_s, created_at, primary_manifest_url, thumbnail_url)`
   - `VideoRendition(video_id, codec, resolution, bitrate_kbps, media_manifest_url)` — or fold into manifests only.
   - `UploadPart(video_id, part_no, etag, status)` for resume tracking.
   - Counters (`views`) as separate write-heavy store / Redis buffer if in scope.
   - Blob keys: `raw/{video_id}/…`, `encoded/{video_id}/{rendition}/seg_00001.ts`, `manifests/{video_id}/master.m3u8`.
   - Metadata DB: Cassandra/Dynamo (partition `video_id`) or Postgres + cache; blobs: S3/GCS.

5. **High-level architecture / component breakdown**
   - **Client** → **API / LB** (auth, metadata, presign) → **Metadata DB + Redis**.
   - **Object storage (raw)** ← direct multipart upload.
   - **Queue** → **Transcode workers (DAG)** → **Object storage (encoded + manifests)** → update metadata `ready`.
   - **CDN (edge → optional regional / origin shield)** ← player segment fetches; origin = encoded bucket.
   - Optional: search indexer, notification on ready, view-count pipeline.
   - Draw **upload flow** and **streaming flow** as two diagrams.

6. **Deep dives & key tradeoffs (pick 2–3)**
   - **ABR vs single file:** segments + ladder enable mid-play quality switch and CDN caching; more storage/CPU vs smooth UX under flaky networks.
   - **DAG parallel encode vs sequential:** wall-clock minutes vs hours; need orchestrator, idempotent workers, temp storage by URL.
   - **Commercial CDN vs own (Open Connect):** buy until egress economics / ISP partnerships justify building; Netflix pre-positions catalog; YouTube pull-caches long tail.
   - **Eager vs lazy encode:** full ladder on upload (fast first play everywhere) vs popular-formats-first / on-demand rare rungs (save cost, slower long-tail quality).
   - **Exact vs approximate view counts:** Redis INCR + periodic flush vs CQRS; consistency vs write amplification.

7. **Bottlenecks / how you scale it**
   - **Egress / origin melt on viral video:** CDN hit ratio, origin shield, pre-warm first segments of hot titles.
   - **Transcode backlog:** autoscaling workers, priority queues (creators / trending), degrade ladder under load.
   - **Metadata hot key:** Redis cache, replicate popular rows, avoid single-partition overload.
   - **Upload failures:** multipart resume; idempotent complete; quarantine incomplete objects with TTL GC.
   - **Geo latency:** multi-region metadata + edge CDN; object storage region + cross-region replication for DR, not for every playback hop.

## Common follow-ups / gotchas
- Live streaming vs VOD: live needs low-latency ingest (chunks in real time), shorter segments, different packaging; don’t pretend your batch DAG is live.
- “Why not stream through app servers?” — bandwidth and cost; API stays control plane.
- DRM / signed URLs / token auth for paid Netflix-like content; public UGC often CDN-cached with softer controls.
- Thumbnail / preview generation and “processing” UX while encode runs.
- Cold start after publish: empty edge cache → origin spike; pre-push or origin shield.
- Codec/container confusion: codec = compression (H.264); container/protocol = HLS/DASH packaging for HTTP delivery.
- Recommendations / search are separate systems — acknowledge and park unless interviewer pulls you there.

## Where it appears
- **Campus / new-grad HLD:** very common “design YouTube”; expect upload + CDN + multi-quality; ABR/DAG depth differentiates.
- **Experienced (1–5+ YOE) / FAANG:** same prompt with probes on multipart resume, transcoding parallelism, CDN tiers, hot-video, cost; Netflix loops lean Open Connect + control vs data plane.
- **Frequency:** top-tier canonical HLD (with URL shortener, chat, news feed); Netflix/YouTube explicitly listed in ByteByteGo / Hello Interview / primer resource tables.
