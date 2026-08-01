# hq17 — Design an Ad Click Aggregator / Real-Time Analytics

**Interview relevance:** High — canonical “scaling writes + stream processing” HLD (Alex Xu Vol.2 ch.6 / Hello Interview); Meta, Google, Amazon, Uber, Netflix ads; probes Kafka/Flink, windowed aggregation, dedup/idempotency, Lambda vs Kappa, OLAP serving.
**Type:** HLD-question
**Prereqs:** h08_message_queues, h14_estimation, h05_db_scaling, h03_caching, h15_building_blocks (Bloom); helpful: h06_consistency_cap, h11_storage, h04_databases_indexing, h02_load_balancing

## Read / watch (curated, in order)
- [ ] [Design an Ad Click Aggregator](https://www.hellointerview.com/learn/system-design/problem-breakdowns/ad-click-aggregator) — `Hello Interview` — best free end-to-end interview breakdown: 302 redirect tracking, batch → stream, Flink windows, hot shards, reconciliation (Lambda), impression-ID dedup
- [ ] [Design an Ad Click Aggregator w/ a Ex-Meta Staff Engineer](https://www.youtube.com/watch?v=Zcv_899yqhI) — `Hello Interview` — ~62 min whiteboard of the same problem (Evan King); mid vs senior vs staff bar
- [ ] [Ad Click Event Aggregation (SDI course / Alex Xu Vol.2 ch.6)](https://bytebytego.com/courses/system-design-interview/ad-click-event-aggregation) — `ByteByteGo` — canonical book chapter (MapReduce → Flink, late events, OLAP); course may be gated
- [ ] [ByteByteGo — system_design_links_vol2 (Ch.6 refs)](https://github.com/alex-xu-system/bytebytego/blob/main/system_design_links_vol2.md) — `ByteByteGo` — CTR/OLAP/Flink/Pinot/Uber pointers that back the chapter
- [ ] [Metric monitoring](https://blog.bytebytego.com/p/metric-monitoring) — `ByteByteGo` — cousin pipeline: collectors → Kafka → Flink/Spark → TSDB/query/alert (same buffering mental model)
- [ ] [Kafka Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/kafka) — `Hello Interview` — durable partitioned log, consumer groups, replay; cites ad-click aggregation as the stream example
- [ ] [Flink Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/flink) — `Hello Interview` — why raw Kafka consumers fail for windowed state, watermarks, checkpoints
- [ ] [Scaling Writes pattern](https://www.hellointerview.com/learn/system-design/patterns/scaling-writes) — `Hello Interview` — queue buffer, shard/partition, hot-key salt, hierarchical aggregation (ad aggregator is a featured problem)
- [ ] [What is a MESSAGE QUEUE and Where is it used?](https://www.youtube.com/watch?v=oUJbuFMyBDk) — `Gaurav Sen` — why click intake never writes OLAP synchronously; buffer + async workers
- [ ] [What are Bloom Filters?](https://www.youtube.com/watch?v=bgzUdBVr5tE) — `Gaurav Sen` — space-cheap “seen?” for click/impression dedup (false positives only)
- [ ] [Redis — Bloom filter](https://redis.io/docs/latest/develop/data-types/probabilistic/bloom-filter/) — `Redis docs` — production `BF.ADD` / `BF.EXISTS` for hot-path dedupe
- [ ] [Lambda architecture](https://en.wikipedia.org/wiki/Lambda_architecture) — `Wikipedia` — speed + batch + serving; pair with [Databricks glossary](https://www.databricks.com/glossary/lambda-architecture)
- [ ] [What Is the Kappa Architecture?](https://hazelcast.com/glossary/kappa-architecture/) — `Hazelcast` — single streaming stack + replay vs dual codepaths
- [ ] [Real-Time Exactly-Once Ad Event Processing with Apache Flink, Kafka, and Pinot](https://www.uber.com/us/en/blog/real-time-exactly-once-ad-event-processing/) — `Uber Eng` — production ads: tumbling minutes, Flink 2PC + Kafka `read_committed`, Pinot upsert, Hive warehouse
- [ ] [End-to-end Exactly-once Aggregation Over Ad Streams | Yelp](https://www.youtube.com/watch?v=hzxytnPcAUM) — `Yelp` (ByteByteGo Ch.6 cite) — conference talk on exactly-once over ad streams
- [ ] [System Design Trackers from Netflix's Ad Tracking Launch](https://www.hellointerview.com/blog/system-design-trackers-from-netflix-ad-tracking-launch) — `Hello Interview` — interview lessons from Netflix ads; pairs with [Netflix TechBlog pipeline](https://netflixtechblog.com/behind-the-scenes-building-a-robust-ads-event-processing-pipeline-e4e86caf9249) (Kafka → Flink → Druid + offline correction)
- [ ] [Apache Flink](https://flink.apache.org/) — `Apache` — event-time, late data, exactly-once state; OLAP sinks: [Pinot](https://pinot.apache.org/), [Druid](https://druid.apache.org/), [ClickHouse](https://clickhouse.com/)
- [ ] [Clickthrough rate (CTR): Definition](https://support.google.com/google-ads/answer/2615875) — `Google Ads` — clicks ÷ impressions vocabulary; fraud context: [Ad Traffic Quality](https://www.google.com/ads/adtrafficquality/)
- [ ] [system-design-primer — Message queues](https://github.com/donnemartin/system-design-primer#message-queues) — `primer` — queue vocabulary for decoupling ingest from aggregation
- [ ] *Designing Data-Intensive Applications* ch.11 (Stream Processing) — `DDIA ch.11` — event time, windows, exactly-once; book site: [dataintensive.net](https://dataintensive.net/)
- [ ] [InterviewReady — system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` / Gaurav Sen — curated follow-on dump after the walkthrough; site: [interviewready.io](https://interviewready.io/)

## Core concepts to master
- **Write-heavy, read-light:** peak clicks (e.g. 10k/s) dwarf advertiser dashboard QPS → architecture is driven by **ingest durability + pre-aggregation**, not fancy read caches alone.
- **Track then redirect:** prefer **server-side 302** through `/click` (count then redirect) over client-only navigation that can skip tracking.
- **Never scan raw clicks for dashboards:** store raw events for audit/replay; serve **pre-aggregated** rows `(ad_id, minute, dims…) → counts` from an **OLAP** store (Pinot / Druid / ClickHouse / BigQuery-style), not `COUNT(*)` on OLTP.
- **Kafka (or Kinesis) as the buffer:** intake validates + appends → returns fast; stream processors consume asynchronously; retention enables **replay** after Flink bugs/outages.
- **Event time ≠ processing time:** bucket by click timestamp; use **watermarks** / allowed lateness so late mobile events land in the correct minute.
- **Windowed aggregation:** tumbling 1-minute windows are the interview default; flush partials early for fresher dashboards; roll up to hour/day for long-range queries.
- **Partition by `ad_id` (or campaign):** co-locates keys for aggregation; **hot ads** → salt key (`ad_id:0..N`) then merge on write/query.
- **Dedup / idempotency:** at-least-once delivery → duplicates. Prefer **signed impression_id** (per ad *instance*) + Redis/Bloom “seen” **before** counting; billing uses exact batch dedup. Don’t claim naked “exactly-once” without sink idempotency.
- **Lambda for money:** **speed layer** (Flink → near-real-time OLAP) for dashboards; **batch layer** (Spark over S3/lake raw log) reconciles exact counts for **billing**; never invoice from provisional stream counts alone unless product allows.
- **Kappa alternative:** one streaming codebase + log replay (Jay Kreps) — simpler ops, still need a correctness story for money.
- **Fraud is usually out of scope** unless asked — mention invalid traffic / bots, then park behind a filter service (Google Ad Traffic Quality mindset).
- **OLAP vs TSDB:** millions of ad IDs + multi-dimension slices favor columnar OLAP; plain TSDB only if cardinality and query shape stay tiny.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈45 min):

### 1. Requirements (functional + non-functional) & scale assumptions
**Functional (in scope):** record clicks (and often impressions); redirect user to advertiser URL; query aggregates by ad/campaign over time with **≥1-minute** granularity; optional slices (geo, device); near-real-time dashboard freshness.
**Out of scope (say so):** ad targeting / auction / RTB, creative CDN, full fraud ML, cross-device identity, conversion attribution (unless pulled — Uber-style).
**NFRs:** peak write throughput; no silent click loss after accept; low-latency analytics (sub-second reads on pre-agg); as fresh as possible (seconds–minutes); idempotent counting; billing accuracy stricter than dashboard freshness.
**Clarify:** clicks only vs impressions+clicks; dimensions; freshness SLA; billing vs dashboard; logged-in users only?

### 2. Back-of-envelope estimation
Align numbers with interviewer (Hello Interview baseline is fine):
- **10M active ads**, peak **~10k clicks/s** → if peak ≈ 10× average → ~1k/s avg → **~100M clicks/day**.
- Event size ~100–500 B → raw ingest tens of MB/s peak; retention (e.g. 7–30d Kafka + longer lake) dominates storage math more than OLAP rollups.
- Pre-agg shrinks data hard: 86400 minutes/day × ads × dims ≪ raw events if you only store non-zero buckets.
- Reads: thousands of advertisers polling dashboards ≪ write path — optimize writes first.

### 3. API / interface
- `GET /v1/click?ad_id=&impression_id=&sig=&…` → validate → enqueue → **`302`** to advertiser landing URL (tracking params optional).
- Alternate: beacon `POST /v1/events` `{ event_id, type: click|impression, ad_id, campaign_id, event_time, dims… }` → `202` (mobile SDKs).
- `GET /v1/ads/{ad_id}/metrics?from=&to=&granularity=1m|1h|1d&group_by=country,device`
- `GET /v1/campaigns/{id}/metrics…` for rollups.
- Auth: public/signed click URL; authenticated advertiser metrics; internal service auth for billing export.
- Optional: webhook/export for billing systems consuming **reconciled** aggregates only.

### 4. Data model
- **Impression / click event (raw):** `event_id` or `impression_id`, `ad_id`, `campaign_id`, `advertiser_id`, `user_id?`, `event_time`, `ingest_time`, `ip/ua` hashes, `country`, `device`, HMAC `sig`.
- **Dedup store:** Redis set / Bloom of `impression_id` (TTL ≈ attribution window, e.g. hours–days).
- **Aggregate fact (OLAP):** `(ad_id, window_start, granularity, country, device, …) → clicks, impressions, unique_approx?`
- **Rollup tables:** hourly/daily materializations for long-range charts.
- **Raw lake:** Parquet/ORC on S3/GCS (Kafka Connect / Firehose) — source of truth for batch recompute.
- **Billing snapshot:** immutable daily/hourly exact counts post-reconciliation (append corrections, don’t silently rewrite history without audit).

### 5. High-level architecture / component breakdown
1. **Ad Placement Service** (black box) serves creative + **signed impression_id** + click URL.
2. **Click / Event API** (LB → stateless fleet): verify HMAC, dedup check, append to **Kafka** (`clicks` topic, key=`ad_id` or salted), archive path to lake; then **302**.
3. **Stream processor (Flink):** event-time tumbling windows → emit minute aggregates → sink to **OLAP** (and/or aggregates topic).
4. **OLAP serving** (Pinot/Druid/ClickHouse/BigQuery): advertiser Query API / dashboards.
5. **Batch reconciler (Spark):** hourly/daily exact dedup + aggregate from lake → overwrite/correct OLAP + feed **billing**.
6. **Optional:** Redis hot counters for pacing/budget (Uber); separate fraud filter before count.

**Happy path:** User click → Click API (dedup) → Kafka → Flink 1-min window → OLAP → advertiser chart updates within ~window + checkpoint lag.

**Billing path:** same Kafka/lake → Spark exact `GROUP BY impression_id` → authoritative invoice numbers.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Batch vs stream (then Lambda):** batch alone is simple but stale under spikes; stream alone is fresh but harder to prove money-correct. **Speed for UX + batch for truth** is the senior answer; Kappa if you argue replay + one codebase.
2. **Dedup timing & key:** dedup **before** windowing (cross-minute duplicates). `user_id+ad_id` is wrong for retargeting — use **per-impression id**, signed so clients can’t invent IDs. Bloom false positives drop real clicks → prefer exact Redis for money-adjacent paths or accept FP only on non-billing dashboards.
3. **Exactly-once story:** Flink checkpoints + Kafka transactions + **idempotent sink** (Pinot upsert / UUID) as in Uber — “at-least-once + idempotent aggregate key” is the honest interview shorthand.
4. **Hot partitions:** viral ad → salt `ad_id`; merge with SUM upsert or query-time sum.
5. **Late events:** watermark + allowed lateness; after window closes, either side-output to correction stream or rely on batch reconcile.
6. **Query latency at long ranges:** pre-aggregate hour/day rollups (hierarchical aggregation) instead of summing millions of minute rows live.

### 7. Bottlenecks / how you scale it
- **Click API CPU/QPS** → horizontal scale + LB; keep handler lean (verify, dedup, produce, redirect).
- **Kafka partition throughput / hot keys** → more partitions; salt popular ads; monitor consumer lag.
- **Flink state / checkpoint duration** → keyed state by ad+window; tune checkpoint interval (Uber ~2 min for EOS) vs freshness.
- **Dedup Redis** → shard by impression_id; memory is small vs event volume if TTL’d; replica + persistence for failovers.
- **OLAP write amplification** → write **aggregates**, not every raw click; shard/tablet by advertiser for dashboard locality.
- **Batch job overrun** → lake partitioning by time; incremental windows; never block ingest on Spark.
- **Failure:** durable accept = Kafka ack before 302; replay from retained offsets; reconciliation heals stream drift; DLQ for poison events.
- **Multi-region:** dual-region produce + union/upsert (Uber) if dashboards are active-active.

## Common follow-ups / gotchas
- Aggregating in the **same OLTP DB** that stores raw clicks (`GROUP BY` at 10k/s) — instant fail.
- Counting with **processing time** so late mobile clicks bill the wrong minute.
- Claiming **exactly-once** without dedup/idempotent sink / checkpoint story.
- Deduping only **inside** a 1-minute Flink window (duplicates across boundaries double-count).
- Using **user_id + ad_id** forever as the idempotency key (breaks legitimate re-shows).
- **Billing off the real-time layer** without batch reconciliation.
- Ignoring **hot ad** partition imbalance after a celebrity campaign.
- Client-only redirect with **best-effort** beacon (lost clicks = lost revenue).
- Building custom stream-state on Kafka consumers instead of naming **Flink/Spark** tradeoffs when asked for seniority.
- Scope creep into full **fraud platform** without interviewer asking — mention, then park.

## Where it appears
- **Campus / intern / new-grad:** “design ad click aggregation / real-time analytics”; expect Kafka buffer, pre-agg, OLAP, basic dedup, and why not one SQL table.
- **Experienced (1–4+ YOE) / Meta–Google–Uber ads-flavored:** event-time windows, hot shards, Lambda reconcile vs Kappa, impression signing, estimation of peak write QPS, billing vs dashboard accuracy split.
- **Frequency:** top-tier HLD alongside metrics monitoring, Top-K / trending, notification pipelines. Depth = write scaling + stream correctness — not implementing an ad auction or fraud neural net unless explicitly asked.
