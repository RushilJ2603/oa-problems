# H15 — Core building blocks: consistent hashing, bloom filters, quorum, gossip, HLL, geohash

**Interview relevance:** High — these are the “name the primitive” follow-ups in almost every HLD round (distributed cache/DB, crawler, analytics, proximity/Uber-Yelp); campus + experienced; FAANG and Indian product cos.
**Type:** HLD-foundation
**Prereqs:** h02_load_balancing, h03_caching, h05_db_scaling, h06_consistency_cap; h07_consensus helpful for “quorum” vocabulary overlap

## Read / watch (curated, in order)
- [ ] [EP150: 12 Algorithms for System Design Interviews](https://blog.bytebytego.com/p/ep150-12-algorithms-for-system-design) — `ByteByteGo` — map of the six primitives (+ Merkle/Raft extras); use as a checklist of *when* each shows up
- [ ] [Consistent Hashing | Algorithms You Should Know #1](https://www.youtube.com/watch?v=UF9Iqmg94tk) — `ByteByteGo` — mod-N remapping storm → hash ring → virtual nodes; DynamoDB/Cassandra/CDN/LB uses (~10 min)
- [ ] [Consistent Hashing Explained](https://bytebytego.com/guides/consistent-hashing/) — `ByteByteGo` — same ideas in text/diagrams; pair with [What is CONSISTENT HASHING…](https://www.youtube.com/watch?v=zaRkONvyGr8) — `Gaurav Sen` — fault tolerance + scalability framing for interviews
- [ ] [Consistent Hashing (Hello Interview)](https://www.hellointerview.com/learn/system-design/core-concepts/consistent-hashing) — `Hello Interview` — vnodes, hot keys vs structural imbalance, when to deep-dive vs “Cassandra/Dynamo handles it”
- [ ] [system-design-primer — Sharding](https://github.com/donnemartin/system-design-primer#sharding) — `primer` — consistent hashing as the rebalance fix; classic explainer linked from primer: [The Simple Magic of Consistent Hashing](https://www.paperplanes.de/2011/12/9/the-magic-of-consistent-hashing.html)
- [ ] [Bloom Filters | Algorithms You Should Know #2](https://www.youtube.com/watch?v=V3pzxngeLqw) — `ByteByteGo` — bit vector + k hashes; false positives only; LSM/CDN/browser-style uses
- [ ] [How to avoid crawling duplicate URLs at Google scale](https://blog.bytebytego.com/p/how-to-avoid-crawling-duplicate-urls) — `ByteByteGo` — set vs DB vs Bloom for “seen URL?”; then [What are Bloom Filters?](https://www.youtube.com/watch?v=bgzUdBVr5tE) — `Gaurav Sen`
- [ ] [Redis — Bloom filter](https://redis.io/docs/latest/develop/data-types/probabilistic/bloom-filter/) — `Redis docs` — production API (`BF.ADD` / `BF.EXISTS`); size vs error-rate intuition
- [ ] *Designing Data-Intensive Applications* ch.3 (Storage and Retrieval) — `DDIA ch.3` — Bloom filters on LSM/SSTables to skip disk for missing keys ([book site](https://dataintensive.net/); [free notes](https://timilearning.com/posts/ddia/part-one/chapter-3/))
- [ ] *DDIA* ch.5 (Replication) — `DDIA ch.5` — leaderless **N/R/W** quorums, sloppy quorum + hinted handoff ([free notes](https://timilearning.com/posts/ddia/part-two/chapter-5/)); *DDIA* ch.6 (Partitioning) — hash partitioning / “consistent hashing” naming caveat ([free notes](https://timilearning.com/posts/ddia/part-two/chapter-6/))
- [ ] [Dynamo: Amazon’s Highly Available Key-value Store (PDF)](https://www.allthingsdistributed.com/files/amazon-dynamo-sosp2007.pdf) — `Dynamo paper` — **skim** consistent hashing + vnodes, preference lists, quorum R/W, gossip membership (the interview origin story for Cassandra/Riak-style stores)
- [ ] [Cassandra architecture — Dynamo](https://cassandra.apache.org/doc/latest/cassandra/architecture/dynamo.html) — `Cassandra docs` — gossip membership + Phi accrual failure detection + tunable consistency; pair [Internode communications (gossip)](https://docs.datastax.com/en/cassandra-oss/3.x/cassandra/architecture/archGossipAbout.html) — `DataStax` — every-second peer exchange, seeds for bootstrap
- [ ] [Cassandra Deep Dive (Hello Interview)](https://www.hellointerview.com/learn/system-design/deep-dives/cassandra) — `Hello Interview` — coordinator + gossip + quorum consistency levels in interview English
- [ ] [Redis — HyperLogLog](https://redis.io/docs/latest/develop/data-types/probabilistic/hyperloglogs/) — `Redis docs` — ~12 KB, ~0.81% error; `PFADD` / `PFCOUNT` / `PFMERGE`; then [Redis new data structure: the HyperLogLog](https://antirez.com/news/75) — `antirez` — leading-zeros intuition. Optional viz: [Redis HyperLogLog Explained](https://www.youtube.com/watch?v=MunL8nnwscQ). Optional primary paper (skim): [HyperLogLog (Flajolet et al. PDF)](https://algo.inria.fr/flajolet/Publications/FlFuGaMe07.pdf)
- [ ] [Proximity Search (Hello Interview)](https://www.hellointerview.com/learn/system-design/deep-dives/proximity-search) — `Hello Interview` — geohash / S2 / H3; **3×3 neighbor ring** + Haversine post-filter
- [ ] [Geohash (Wikipedia)](https://en.wikipedia.org/wiki/Geohash) — `Wikipedia` — base32 encoding, precision vs cell size table, edge/meridian caveats
- [ ] [Redis geospatial](https://redis.io/docs/latest/develop/data-types/geospatial/) — `Redis docs` — `GEOADD` / `GEOSEARCH` (geohash under the hood for nearby queries)
- [ ] [H3: Uber’s Hexagonal Hierarchical Spatial Index](https://www.uber.com/us/en/blog/h3/) — `Uber Eng` — why hex k-rings beat square geohash neighbors for marketplace / surge / dispatch

## Core concepts to master
- **Consistent hashing:** place nodes *and* keys on a ring; key → first node clockwise. Add/remove moves ~`K/N` keys, not almost all (`hash % N`). **Virtual nodes** (many ring positions per physical node) smooth load and spread failover. Used for caches, Dynamo/Cassandra partitions, sticky LBs — *not* a fix for celebrity hot keys (salt / replicate those).
- **Bloom filter:** probabilistic **set membership**. Answers “definitely not” or “probably yes” — **false positives OK, false negatives never**. Bit array + k hashes; cannot delete (unless counting Bloom). Interview uses: crawl “seen?” gate, cache negative lookups, LSM “key might be in this SSTable?” before disk.
- **Quorum (Dynamo-style):** with replication factor `N`, need `W` write acks and `R` read responses. Rule of thumb: **`R + W > N`** ⇒ read set overlaps a successful write (stronger recency). Typical `N=3, R=W=2`. Trade latency (wait for slowest of R/W) vs durability/freshness. **Sloppy quorum** + hinted handoff keeps writes available when “home” replicas are down (weaker overlap guarantee).
- **Gossip:** epidemic peer-to-peer state exchange (membership, tokens/schema, heartbeats). O(log n) rounds to converge; no central registry SPOF. Cassandra: ~1s gossip to a few peers + Phi accrual suspicion. Contrast with ZooKeeper/etcd consensus for *coordination* — gossip is for *membership dissemination*, not agreeing on one value.
- **HyperLogLog (HLL):** approximate **cardinality** (count distinct) in tiny fixed memory (~12 KB in Redis, ~0.81% std error). Hash → track max leading zeros across registers; mergeable (`PFMERGE`). Use for DAU, unique search queries, view-ish counts — **not** when you need exact billing or to enumerate members.
- **Geohash:** encode (lat, lon) → base32 string; shared prefix ⇒ same/nearby cell; longer string ⇒ smaller cell. Query pattern: prefix lookup on **center cell + 8 neighbors**, then exact distance filter. Alternatives: **H3** (hex k-ring, Uber) / **S2** (Google). Redis `GEO*` is the interview-ready shortcut.
- **How they compose:** Dynamo-family stack = consistent hashing (placement) + quorum (consistency knobs) + gossip (membership). Analytics path = Bloom (filter) + HLL (count). Location path = geohash/H3 index + post-filter. Pick the *right* probabilistic structure — Bloom ≠ HLL.

## Practice — how it's asked & how to attack it
Self-test drills (≤2 min aloud each):

1. **Ring vs mod-N:** Cache cluster grows 4→5 nodes. Why does `hash % N` thrash? Walk one key’s owner on a ring before/after adding a vnode-rich node. How many keys move roughly?
2. **Bloom sizing tradeoff:** Crawler bloom at 1% FPR vs 0.01%. What happens if you undersize the bit array? Can you ever get a false negative? Why can’t you “delete” a URL after un-blacklisting?
3. **Quorum math:** `N=3`. Compare `(R=1,W=1)`, `(R=2,W=2)`, `(R=3,W=1)`. Which survives one node down for writes? Which can return stale reads? When would you pick `W=N`?
4. **Gossip vs ZooKeeper:** Designing Cassandra-like KV vs Kafka controller election. Which uses gossip for membership, which needs consensus? What goes wrong if gossip is partitioned briefly (split view of UP/DOWN)?
5. **HLL product sense:** “Unique visitors today” dashboard. Why not a Redis `SET`? What error does the PM see at 10M uniques? Can you merge hourly HLLs into a daily number?
6. **Nearby restaurants:** User at a geohash cell edge. Why does querying only their cell miss a place 50 m away? Sketch 9-cell query + Haversine refine. When would you name H3 instead?

## Common follow-ups / gotchas
- Drawing a hash ring **without virtual nodes** — interviewer asks about load skew and “all traffic from dead node dumps onto one neighbor.”
- Treating Bloom “yes” as proof of existence — must hit the source of truth on positives; Bloom only saves work on negatives.
- Confusing **consensus quorum** (Raft majority for one log) with **Dynamo quorum** (R/W overlap for replica freshness) — say which you mean.
- Claiming gossip “guarantees strong consistency” — it eventually spreads membership; data consistency still needs R/W (or a consensus store).
- Using HLL for “exact distinct users for invoices” — wrong tool; HLL is approximate and does not store IDs.
- Forgetting geohash **boundary problem** (or poles/±180°) — always expand neighbors / use H3 k-ring, then exact distance.
- Saying “consistent hashing” when the system really uses **fixed hash slots** (Redis Cluster 16384) — principle is minimal remapping; implementation may differ (DDIA ch.6 warning).

## Where it appears
- **Campus / new-grad HLD:** consistent hashing on cache/URL shortener/chat; Bloom on crawler or “check username taken”; geohash on Yelp/Uber-lite; light quorum wording on Cassandra/Dynamo mentions.
- **Experienced (1–4+ YOE):** R+W>N tuning, sloppy quorum, gossip failure detection, HLL for analytics counters, H3 vs geohash tradeoffs — Meta, Google, Amazon, Uber, Flipkart, Atlassian infra loops.
- **Frequency:** high as **toolkit follow-ups** inside larger designs; rare as a standalone “design HyperLogLog” prompt — interviewers want correct tool choice and tradeoffs, not paper proofs.
