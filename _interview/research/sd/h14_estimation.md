# H14 — Back-of-envelope estimation & capacity planning (QPS, storage, bandwidth)

**Interview relevance:** High — expected early in almost every HLD round (campus + experienced); FAANG and Indian product cos (Atlassian, Uber, Flipkart, etc.) use it to see if your architecture class matches the load.
**Type:** HLD-foundation
**Prereqs:** None — learn early; apply in every HLD design question. Bandwidth/RTT intuition pairs with h01_networking; storage sizing pairs with h04/h05/h11

## Read / watch (curated, in order)
- [ ] [Back-of-the-envelope calculations (primer)](https://github.com/donnemartin/system-design-primer#back-of-the-envelope-calculations) — `primer` — interview entry point: when you're asked to estimate by hand; points to powers-of-two + latency tables
- [ ] [Powers of two table](https://github.com/donnemartin/system-design-primer#powers-of-two-table) — `primer` — bytes → KB/MB/GB/TB/PB mental conversions (2^10 ≈ 10^3); [Power of two (Wikipedia)](https://en.wikipedia.org/wiki/Power_of_two) for the math
- [ ] [Latency numbers every programmer should know (primer)](https://github.com/donnemartin/system-design-primer#latency-numbers-every-programmer-should-know) — `primer` — L1 → RAM → SSD → disk → DC RTT → cross-continent; order-of-magnitude intuition
- [ ] [Latency numbers (jboner gist)](https://gist.github.com/jboner/2841832) — `Jeff Dean / community gist` — canonical printable table (also [visual / human-scale gist](https://gist.github.com/hellerbarde/2843375))
- [ ] [Google Pro Tip: Use Back-of-the-envelope Calculations](https://highscalability.com/google-pro-tip-use-back-of-the-envelope-calculations-to-choo/) — `High Scalability` (Jeff Dean) — why estimates choose designs; serial vs parallel thumbnail example
- [ ] [Jeff Dean latency numbers (table)](https://brenocon.com/dean_perf.html) — `Jeff Dean` — compact “Numbers Everyone Should Know” reference
- [ ] [Interactive latency numbers by year](https://colin-scott.github.io/personal_website/research/interactive_latency.html) — `Colin Scott` — hardware moves; ratios matter more than exact ns ([repo](https://github.com/colin-scott/interactive_latencies))
- [ ] [Computers Are Fast](https://computers-are-fast.github.io/) — practice game — calibrate “how much work fits in 1 second” (order of magnitude, not precision)
- [ ] [Back-of-the-Envelope Estimation (ByteByteGo / Alex Xu Vol.1 Ch.2)](https://bytebytego.com/courses/system-design-interview/back-of-the-envelope-estimation) — `ByteByteGo` — powers of two, latency, availability “nines,” QPS/storage drill; TOC context in [Vol 1 vs Vol 2](https://blog.bytebytego.com/p/system-design-interview-books-volume)
- [ ] [Capacity Planning (ByteByteGo newsletter)](https://blog.bytebytego.com/p/capacity-planning) — `ByteByteGo` — DAU → avg QPS → peak QPS; request sizing; ingress/egress bandwidth with worked social-feed math
- [ ] [Mastering Estimation](https://www.hellointerview.com/blog/mastering-estimation) — `Hello Interview` — Fermi-style approach: estimate the *crux*, dimensional analysis, round numbers, what interviewers grade
- [ ] [System Design Delivery Framework — Capacity Estimation](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — just-in-time math (skip ritual QPS if it won’t change the design); when estimates *do* matter
- [ ] [Capacity Planning and Estimation: How much data does YouTube store daily?](https://www.youtube.com/watch?v=0myM0k1mjZw) — `Gaurav Sen` — storage + replication + encoding + cache node count; narrate assumptions out loud
- [ ] [Pastebin design — Calculate usage](https://github.com/donnemartin/system-design-primer/blob/master/solutions/system_design/pastebin/README.md) — `primer` — worked QPS + storage + “2.5M seconds/month” conversion cheat sheet
- [ ] [DDIA Ch.1 — Reliable, Scalable, Maintainable Applications](https://dataintensive.net/) — `DDIA ch.1` — load parameters, throughput vs latency, **percentiles (p95/p99)** not averages ([free notes](https://timilearning.com/posts/ddia/part-one/chapter-1/))
- [ ] [System Design playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — listen for where capacity math drives architecture in full designs
- [ ] [system-design-resources (InterviewReady / Gaurav Sen)](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` — curated further reading dump after you have the core pipeline down

## Core concepts to master
- **Goal ≠ precision:** order of magnitude (10×) is enough to pick architecture class (1 box vs sharded fleet vs multi-region). Narrate assumptions; round aggressively (86,400 s/day → **10^5**).
- **Four numbers every design needs:** **avg QPS**, **peak QPS**, **storage (growth + retention)**, **bandwidth (ingress + egress)**. Optional fifth: **cache/memory working set**.
- **QPS pipeline:** `avg QPS ≈ (DAU × actions/user/day) / 10^5`. Split **read vs write**. **Peak ≈ 2–5× avg** (consumer); higher for event spikes or business-hours B2B. Design for **peak**, not average.
- **Handy conversions:** ~2.5×10^6 s/month → 1 RPS ≈ 2.5M req/month; 400 RPS ≈ 1B/month (primer Pastebin sheet).
- **Storage:** `bytes/item × items/day × retention_days × replication (often 3×) × index overhead (~1.2–2×)`. Don’t forget encodings/variants (e.g. multi-res video) and backups.
- **Bandwidth:** `QPS × avg payload` separately for **ingress** (writes/uploads) and **egress** (reads/feeds). Watch **bits vs bytes** (8× trap). CDN/cache cut egress at origin.
- **Latency hierarchy (orders of magnitude):** L1 ~1 ns → RAM ~100 ns → SSD ~100 μs → same-DC RTT ~0.5 ms → disk seek ~10 ms → cross-continent ~100–150 ms. Memory ≫ disk; same-DC ≫ WAN — this drives cache/CDN/co-location choices.
- **Servers from QPS:** `servers ≈ peak_QPS / QPS_per_instance` (or Little’s Law: concurrency ≈ QPS × latency). Add headroom for deploys/failures (~20–50%).
- **Estimate → architecture:** if peak write QPS ≫ one primary DB → replicas/shards/queues; if hot reads ≫ DB → cache/CDN; if storage ≫ one disk → object store/sharding. A number without a design implication is wasted.
- **Availability “nines”:** 99.9% ≈ 8.7 h downtime/year; 99.99% ≈ 52 min. SLA targets constrain redundancy cost — mention when NFRs ask for high availability.
- **DDIA framing:** define **load parameters** first; measure user-facing latency with **percentiles**, not means — capacity that only hits average QPS still fails p99.

## Practice — how it's asked & how to attack it
Self-test drills (speak answers in ≤3 min; state assumptions first):

1. **QPS drill — URL shortener:** 100M DAU, 2 creates + 20 redirects per user/day. Compute avg write QPS, avg read QPS, and peak (×3). What architecture class does peak read imply?
2. **Storage drill — tweets:** 200M DAU, 2 tweets/user/day, 300 bytes/tweet metadata, 5-year retention, 3× replication. Ballpark total storage. Does it fit on one machine?
3. **Bandwidth drill — news feed:** 50k avg QPS, each response ~200 KB of post payloads. Origin egress? How do CDN + thumbnails + pagination change the number?
4. **Latency hierarchy drill:** For each of {serve profile from Redis, random row from HDD, call EU from US}, give ~latency and say whether it’s on the critical path for a 100 ms SLO.
5. **YouTube-lite (Gaurav Sen style):** 1M hours uploaded/day, ~1 GB/hour encoded primary, + ladder of lower res, 3× copies. Daily PB written? Rough cache-fleet size if 1% of catalog is hot in RAM.
6. **Just-in-time vs ritual:** Design Top-K trending. Which *one* estimate changes the design (in-memory heap vs sharded)? Which estimates can you skip? (Hint: Hello Interview delivery + Top-K breakdown.)

## Common follow-ups / gotchas
- Designing for **average** QPS then melting at peak / launch day — always state peak multiplier.
- **Bits vs bytes** or KB vs KiB confusion — label units every line.
- Precise calculator theater (17,341.2 QPS) with **no design conclusion** — interviewer wants architecture implications.
- Forgetting **replication, indexes, encodings, retention** in storage → undercount by 3–10×.
- Using ancient “disk seek = everything is slow” to ban SSDs — update intuition (SSD/NVMe changed the economics; ratios still matter).
- Estimating everything up front when only one bottleneck is load-bearing — prefer **crux-first / just-in-time** math.
- Ignoring **read:write skew** (often 10:1–100:1) and sizing write path like the read path.

## Where it appears
- **Campus / new-grad HLD:** nearly every “design X” — 2–5 minutes after requirements; Pastebin/URL shortener/Twitter-lite scale assumptions are common.
- **Experienced / mid-level:** same math, but interviewers push peak vs average, cache hit-rate needed to spare the DB, multi-region bandwidth, and cost/SLA nines.
- **Frequency:** foundational in essentially all product-company HLD rounds; weak or missing estimates are a common fail signal even when the box diagram looks fine.
