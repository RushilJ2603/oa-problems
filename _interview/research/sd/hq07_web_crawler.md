# hq07 — Design a Web Crawler

**Interview relevance:** High — canonical 45-min HLD (Alex Xu Vol.1 ch.9); FAANG + Indian product cos (Google, Meta, Amazon, Microsoft); probes pipelines, politeness, dedup, and scheduling more than a public REST API.
**Type:** HLD-question
**Prereqs:** h01_networking, h08_message_queues, h09_rate_limiting, h03_caching, h11_storage, h14_estimation, h15_building_blocks (Bloom); helpful: h12_search (downstream of crawl)

## Read / watch (curated, in order)
- [ ] [Design a Web Crawler](https://www.hellointerview.com/learn/system-design/problem-breakdowns/web-crawler) — `Hello Interview` — best interview walk-through: seed → frontier → fetch/parse pipeline → robots.txt politeness → scale to ~10B pages; LLM-corpus framing
- [ ] [Design a Web Crawler System Design Interview w/ a Ex-Meta Staff Engineer](https://www.youtube.com/watch?v=krsuaUp__pM) — `Hello Interview` — ~65 min whiteboard of the same breakdown (Evan King)
- [ ] [Design a Web Crawler: FAANG Interview Question](https://www.youtube.com/watch?v=6u25GckPhLU) — `ByteByteGo` — ~6 min visual: frontier, per-host politeness queues, URL-seen + content-seen, parser loop
- [ ] [Design a Web Crawler (ByteByteGo course / Alex Xu Vol.1 ch.9)](https://bytebytego.com/courses/system-design-interview/design-a-web-crawler) — `ByteByteGo` — full chapter depth: URL frontier, HTML downloader, content extractor, duplicate detection (course may be gated)
- [ ] [How to avoid crawling duplicate URLs at Google scale](https://blog.bytebytego.com/p/how-to-avoid-crawling-duplicate-urls) — `ByteByteGo` — set vs DB vs **Bloom filter** for “URL seen?”; false positives only
- [ ] [What are Bloom Filters?](https://www.youtube.com/watch?v=bgzUdBVr5tE) — `Gaurav Sen` — bit vector + k hashes; why crawlers use it for seen-URL / seen-content checks (~27 min)
- [ ] [EP104: How do Search Engines Work?](https://blog.bytebytego.com/p/ep104-how-do-search-engines-work) — `ByteByteGo` — crawl → index → rank → query; places the crawler in the search stack (park indexing unless asked)
- [ ] [system-design-primer — Design a web crawler](https://github.com/donnemartin/system-design-primer/blob/master/solutions/system_design/web_crawler/README.md) — `primer` — estimation, `links_to_crawl` / signatures, cycle avoidance, freshness, DNS bottleneck notes
- [ ] [The URL frontier (Stanford IR book)](https://nlp.stanford.edu/IR-book/html/htmledition/the-url-frontier-1.html) — `Stanford IR` — Mercator-style **front queues (priority) + back queues (politeness)**; pair with [Crawling](https://nlp.stanford.edu/IR-book/html/htmledition/crawling-1.html)
- [ ] [Mercator: A Scalable, Extensible Web Crawler (PDF)](https://www.cs.ucr.edu/~vagelis/classes/CS242/publications/scalable-crawler.pdf) — `classic paper` — component list + why DNS/custom resolvers mattered; interview origin for the two-tier frontier
- [ ] [RFC 9309 — Robots Exclusion Protocol](https://datatracker.ietf.org/doc/html/rfc9309) — `IETF` — canonical robots.txt rules; pair with [Robots exclusion protocol](https://en.wikipedia.org/wiki/Robots_exclusion_protocol)
- [ ] [Redis — Bloom filter](https://redis.io/docs/latest/develop/data-types/probabilistic/bloom-filter/) — `Redis docs` — `BF.ADD` / `BF.EXISTS` production API for seen-set checks
- [ ] [System Design Interview Vol.1 Ch.9 notes](https://noahtigner.com/articles/system-design-interview-volume-1-chapter-9/) — `Alex Xu companion` — free notes bridging ByteByteGo ch.9 ↔ Hello Interview topology
- [ ] [InterviewReady — system-design-resources](https://github.com/InterviewReady/system-design-resources) — `Gaurav Sen` / InterviewReady — queues / Redis / batch sections after the core walk-through; site: [interviewready.io](https://interviewready.io/)
- [ ] [Web crawler (Wikipedia)](https://en.wikipedia.org/wiki/Web_crawler) — `Wikipedia` — vocabulary cheat sheet; optional near-dup: [SimHash](https://en.wikipedia.org/wiki/SimHash); real-world corpus: [Common Crawl](https://commoncrawl.org/overview)

## Core concepts to master
- **Closed crawl loop:** seed URLs → **URL frontier** → DNS → fetch HTML → (optional) content-seen → parse text + links → URL filter/canonicalize → URL-seen → re-enqueue survivors. Output is usually **blob store + metadata**, not a user-facing search UI.
- **URL frontier is the heart:** must balance **priority** (important / fresh pages first) with **politeness** (don’t hammer one host). Naive single FIFO/BFS fails both.
- **Mercator two-tier queues:** front queues by priority → map host → **back queues per host (or host-hash)** → scheduler releases next URL only when that host’s delay allows. Often ~1 in-flight request/host + crawl-delay.
- **Politeness + robots.txt:** cache `robots.txt` per host; honor `Disallow`; treat `Crawl-delay` as courtesy (not always enforced by Googlebot, but interviewers expect you to mention it). Per-host rate limit (e.g. ≤1 req/s) across the whole fleet.
- **URL vs content dedup:** canonicalize (`http`/`https`, `www`, trailing `/`, fragment strip) + **URL-seen** (Bloom / DB) so you don’t refetch; **content hash** (exact hash or SimHash near-dup) so mirrors don’t waste parse/storage.
- **Pipeline the stages:** split fetch vs parse (queues between stages) so fetch failures/retries don’t lose parse progress; don’t put raw HTML in the queue — put IDs / blob keys.
- **DNS is a real bottleneck:** at high QPS, cache resolutions (and/or multi-provider / custom resolver); Mercator famously found DNS dominated thread time without caching.
- **Freshness / re-crawl:** continuous crawlers schedule by change rate + importance (news more often than static docs); one-shot LLM corpus crawls may skip this unless asked.
- **Crawler traps:** infinite calendars / generated paths — enforce **max hop depth**, per-host page budget, URL pattern filters, timeouts.
- **Shard by hostname:** consistent-hash hosts onto frontier shards so politeness stays **local** (all URLs for `nytimes.com` on one owner). Aggregate throughput = millions of hosts × low per-host QPS.
- **Out of scope unless pulled:** full inverted index / PageRank, JS rendering (headless Chrome), login walls, media crawl — acknowledge and park.

## Practice — how it's asked & how to attack it
Prompt variants: “Design a web crawler”, “Design Googlebot”, “Crawl the web for search / LLM training data”. Scope with interviewer: crawl + store in; indexing/ranking usually out.

1. **Requirements & scale assumptions**
   - **Functional (in):** start from seed URLs; fetch HTML; extract text (+ links); store content; discover new URLs; respect robots.txt; avoid duplicate URL work.
   - **Out / below line unless asked:** training the LLM / building search ranker; images/video; JS-rendered SPAs; authenticated pages.
   - **Non-functional:** politeness, fault tolerance (resume without losing frontier), scalability (billions of pages), robustness (bad HTML, traps, timeouts).
   - Pick a framing and stick to it — e.g. Hello Interview: ~**10B pages**, ~**2 MB/page** transfer planning, finish in ~**5 days**; or primer: ~1B links, weekly refresh. State assumptions out loud.

2. **Back-of-envelope estimation**
   - Throughput: 10B pages / 5 days ≈ **~23k pages/s** average (order-of-magnitude; peak higher).
   - Bandwidth: 23k × 2 MB ≈ tens of **GB/s** aggregate — drives fleet size and NIC class, not API QPS.
   - Storage: 10B × (HTML or extracted text) → multi-PB; compression + content dedup matter.
   - Insight to say: per-host ~1 req/s still yields huge global QPS because you crawl **many hosts in parallel**.

3. **API / interface**
   - Crawler is mostly an **internal pipeline**, not a public product API. Sketch control-plane ops:
   - `POST /seeds` — submit seed URL list (priority, max_depth).
   - `GET /urls/{id}` or `GET /status` — crawl status / counts (crawled, queued, failed).
   - `POST /urls/{id}/recrawl` (optional) — force refresh.
   - Workers: pull next URL from frontier (or consume queue), write blobs, ack on success; DLQ after N fetch failures.

4. **Data model**
   - `Url(url_id, canonical_url, host, status[queued|fetched|parsed|skipped|failed], depth, priority, content_hash, html_blob_key, text_blob_key, last_crawled_at, next_fetch_at, http_status)`
   - `Host(host, robots_txt, crawl_delay_s, last_fetch_at, robots_fetched_at)` — politeness + robots cache.
   - `SeenUrl` / Bloom of canonical URL hashes; optional `SeenContent` / Bloom or indexed content hashes.
   - Blob keys: `raw/{url_id}.html.gz`, `text/{url_id}.txt.gz` in S3/GCS.
   - Metadata: Dynamo/Cassandra/Postgres sharded by `url_id` or host; frontier: Redis / SQS / Kafka + per-host scheduling state.

5. **High-level architecture / component breakdown**
   - **Seed injector** → **URL frontier** (priority + per-host back queues).
   - **Fetcher workers** → DNS cache → robots check → HTTP GET → write raw HTML to **object storage** → update metadata → enqueue parse.
   - **Parser workers** → extract text + links → content-seen → store text → canonicalize/filter links → URL-seen → push new URLs to frontier.
   - **Queues** between stages (SQS visibility timeout + DLQ, or Kafka offsets) for retries and independent scale-out.
   - Optional continuous mode: **re-crawl scheduler** scans `next_fetch_at` and re-enqueues.
   - Draw the **closed loop**; call out system boundary vs external web servers.

6. **Deep dives & key tradeoffs (pick 2–3)**
   - **Politeness vs throughput:** stricter per-host delay protects sites / avoids bans but stretches wall-clock; win by parallelizing across hosts, not by raising per-host QPS.
   - **Two-tier frontier vs single priority queue + Redis host locks:** Mercator queues localize politeness; shared queue + locks is simpler ops but hotter coordination — name both.
   - **Bloom vs exact DB for URL-seen:** Bloom = tiny memory, false positives skip some new URLs (usually OK); exact store = no false skip, heavier. Content-seen similarly.
   - **Monolithic crawler vs pipelined fetch/parse:** pipeline isolates I/O failures and lets you re-parse without re-fetch; more moving parts.
   - **BFS vs priority crawl:** BFS is simple; production mixes importance (PageRank-like / seed distance) + freshness deficit.
   - **Host-hash sharding:** local politeness = global politeness; cross-shard priority is approximate unless you add coordination.

7. **Bottlenecks / how you scale it**
   - **DNS:** cache aggressively; multi-provider; don’t block the fleet on uncached lookups.
   - **Frontier hotspot / single queue:** shard by host; keep per-host state with the shard owner.
   - **Fetcher failures / flaky hosts:** retries with exponential backoff + jitter; DLQ; don’t block other hosts.
   - **Parser lag:** autoscale parsers off queue depth; keep HTML in blob store so fetch isn’t blocked.
   - **Dedup store size:** Bloom + periodic rebuild / exact DB for authoritative metadata.
   - **Bandwidth & sockets:** high concurrency (many hosts), connection pooling, timeouts, max page size (HEAD / Content-Length guard).
   - **Traps & spam:** depth/budget caps, URL regex denylist, per-host page caps.

## Common follow-ups / gotchas
- How do you enforce **global** politeness with many fetcher machines? → shard frontier by **hostname** (or distributed per-host lock); never let two shards own the same host.
- URL-seen isn’t enough — same article on two hosts → **content hash / SimHash**.
- JS-heavy SPAs: HTML fetch misses body → headless browser path (expensive; usually out of scope).
- Continuous crawl freshness: adaptive `next_fetch_at` from observed change rate, not fixed weekly for all pages.
- “Where is the API?” — clarify it’s a **data pipeline**; seeds/status are control plane only.
- robots.txt freshness and Crawl-delay nuances; Don’t invent Googlebot-specific myths — stick to Disallow + courtesy delay.
- Bloom false positive means you **skip a never-seen URL** (safe-ish for crawl completeness tradeoff); false negatives don’t happen on membership.
- Indexing / ranking / PageRank are a **separate system** consuming your store — park unless interviewer pulls you there.

## Where it appears
- **Campus / new-grad HLD:** common “design a crawler / search backend piece”; expect seed→frontier→fetch→parse, robots + basic dedup; Bloom and Mercator queues differentiate.
- **Experienced (1–5+ YOE) / FAANG:** same prompt with deep probes on two-tier frontier, host sharding, DNS, retry/DLQ, content dedup, trap handling, re-crawl scheduling.
- **Frequency:** top-tier canonical HLD (with URL shortener, rate limiter, chat, news feed, YouTube); listed explicitly in ByteByteGo Vol.1, Hello Interview problem set, and system-design-primer solutions.
)