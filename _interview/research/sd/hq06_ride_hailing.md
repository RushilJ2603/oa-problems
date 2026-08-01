# HQ06 — Design ride-hailing (Uber/Lyft) with geospatial matching

**Interview relevance:** High — flagship HLD question (campus + experienced) at Uber, Lyft, Ola, Grab, FAANG, Flipkart/Swiggy-style product cos; probes real-time geo index + matching consistency.
**Type:** HLD-question
**Prereqs:** h14_estimation, h15_building_blocks (geohash/H3), h03_caching, h08_message_queues, h04_databases_indexing / h05_db_scaling, h10_api_design; h01_networking helpful for WebSocket/push

## Read / watch (curated, in order)
- [ ] [Design a Ride-Sharing Service Like Uber (answer key)](https://www.hellointerview.com/learn/system-design/answer-keys/uber) — `Hello Interview` — primary interview skeleton: requirements → API → services → Redis GEO deep dives (lock TTL, queues)
- [ ] [Uber problem breakdown](https://www.hellointerview.com/learn/system-design/problem-breakdowns/uber) — `Hello Interview` — same prompt as practice; use if you want the “try first” framing
- [ ] [Proximity Search deep dive](https://www.hellointerview.com/learn/system-design/deep-dives/proximity-search) — `Hello Interview` — geohash / S2 / H3; when Redis GEO vs cell index; neighbor-ring + exact distance
- [ ] [Redis Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/redis) — `Hello Interview` — GEO + distributed locks (the Uber “don’t double-assign” follow-up)
- [ ] [Proximity service (newsletter)](https://blog.bytebytego.com/p/proximity-service) — `ByteByteGo` — Alex Xu geohash intuition (static “nearby places”); map the same index idea onto *moving* drivers
- [ ] [EP150: 12 Algorithms for System Design Interviews](https://blog.bytebytego.com/p/ep150-12-algorithms-for-system-design) — `ByteByteGo` — checklist that geospatial indexing shows up in Uber/Yelp-class designs
- [ ] *System Design Interview* Vol 2 — Proximity Service chapter (Alex Xu) — `ByteByteGo` — full geohash/quadtree/S2 treatment; [Vol 1 vs Vol 2 TOC](https://blog.bytebytego.com/p/system-design-interview-books-volume)
- [ ] [Designing a location database: QuadTrees and Hilbert Curves](https://www.youtube.com/watch?v=OcUKFIjhKu0) — `Gaurav Sen` — spatial trees + locality-preserving curves for “nearby” queries (prerequisite vocabulary)
- [ ] [System Design Playlist](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — broader HLD framing; pair with [system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady`
- [ ] [H3: Uber’s Hexagonal Hierarchical Spatial Index](https://www.uber.com/us/en/blog/h3/) — `Uber Eng` — why hex k-rings beat square geohash neighbors for dispatch / surge; docs: [h3geo.org](https://h3geo.org/), code: [uber/h3](https://github.com/uber/h3)
- [ ] [How does Uber match riders with drivers?](https://www.uber.com/us/en/marketplace/matching/) — `Uber Marketplace` — **batched** matching vs greedy “closest”; product-level tradeoff interviewers love
- [ ] [DeepETA: How Uber Predicts Arrival Times](https://www.uber.com/us/en/blog/deepeta-how-uber-predicts-arrival-times/) — `Uber Eng` — routing engine + ML residual; ETA ≠ Haversine
- [ ] [Redis geospatial](https://redis.io/docs/latest/develop/data-types/geospatial/) — `Redis docs` — `GEOADD` / [`GEOSEARCH`](https://redis.io/docs/latest/commands/geosearch/); interview-ready hot path
- [ ] [Geohash (Wikipedia)](https://en.wikipedia.org/wiki/Geohash) — `Wikipedia` — precision vs cell size; boundary problem
- [ ] [8.9 Design a ride-sharing service (Uber / Lyft)](https://www.systemdesigninterview.com/guides/system-design-interview-handbook/89-design-a-ridesharing-service-uber-lyft) — handbook walk-through — location firehose vs trip ACID split
- [ ] [Design Uber-Style Ride Hailing](https://sujeet.pro/articles/design-uber-ride-hailing) — senior reference — H3 + batch dispatch + DeepETA assembled end-to-end (read after Hello Interview)
- [ ] [system-design-primer](https://github.com/donnemartin/system-design-primer) — `primer` — estimation / scaling vocabulary you apply here (no Uber solution chapter)

## Core concepts to master
- **Two workloads, two stores:** GPS pings = high-write, ephemeral, spatially queried → **in-memory geo index** (Redis GEO or H3→Redis sets). Trips/money = low-write, strongly consistent state machine → **SQL/DocStore** with conditional updates.
- **Geospatial matching pattern:** snap point → cell (geohash / H3) → query **center + neighbors** (geohash 3×3 or H3 `gridDisk`/`k-ring`) → **refine** with distance or road-network ETA. Never scan the global fleet.
- **H3 vs geohash (interview answer):** hexes have **uniform neighbor distance** and near-equal area → cleaner rings for dispatch + surge; geohash is simpler / what Redis GEO uses under the hood. Quadtrees adapt to density but mutate under heavy writes.
- **Greedy nearest vs batch matching:** “closest available” is easy; Uber’s marketplace story is **batch** open requests + drivers every few seconds and optimize system ETA (not one pair in isolation).
- **Offer lock:** prevent double-dispatch with **atomic reserve** (`UPDATE … WHERE status='AVAILABLE'` or Redis lock + **TTL** ≈ accept window). Decline/timeout → cascade to next candidate.
- **Trip state machine:** `REQUESTED → OFFERED → ACCEPTED → ARRIVED → IN_TRIP → COMPLETED` (+ cancel paths). Illegal transitions must be impossible.
- **ETA ≠ crow-flies:** Haversine for candidate filter; ranking uses **routing + traffic** (mention DeepETA as residual ML on top of a routing engine — don’t invent model details).
- **Surge as geo counters:** supply/demand per cell (often H3), cached multipliers; neighbor blending avoids cliff prices at cell edges.
- **Realtime fan-out:** driver→location service (WebSocket/gRPC stream); match→driver **push** (FCM/APNs or persistent socket); rider map updates via push, not polling every second.
- **Shard by city/region:** matching is almost always **local**; partition geo index + match workers by metro so hot cities don’t sink the globe.
- **Consistency split:** location can be **eventually consistent / slightly stale** (seconds); assignment must be **linearizable on the driver**.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈45 min). Scope tightly: matching + location; payments/ratings/pool as “below the line” unless asked.

### 1. Requirements (functional + non-functional) & scale assumptions
**Functional (top 3–4):**
- Fare estimate given pickup + destination
- Request ride → match nearby available driver
- Driver accept/decline; navigate pickup → dropoff
- Continuous driver location updates; rider sees ETA / approaching car

**Out of scope (unless probed):** payments, ratings, scheduled rides, multi-hop pool, fraud.

**Non-functional:**
- Match latency: seconds (often “< ~30–60s to match or fail”), not minutes
- **Strong consistency on assignment** (one driver ↔ one active trip)
- Survive city-scale spikes (concert / rain) without dropping requests
- Location freshness on the order of a few seconds

**Assumptions to state aloud:** one metro first; global = many independent city shards; vehicle types later.

### 2. Back-of-envelope estimation
Narrate assumptions; round aggressively (see h14).

Example framing (tune numbers with interviewer):
- ~1–5M concurrent online drivers globally; **city shard** might be 50k–200k online
- Ping every **3–5 s** → city write QPS ≈ `drivers / 4` (e.g. 100k drivers → **~25k GEO writes/s**)
- Ride requests: much smaller (hundreds–low thousands RPS peak per large city); nearby/map queries **5–10×** requests
- Hot path storage = **working set in Redis** (current lat/lng + status), not years of GPS history
- Historical pings (analytics) → Kafka → cold store; don’t put that on the match path

Implication: OLTP DB cannot be the geo index; Redis/H3 cell maps can.

### 3. API / interface
Keep auth identity in JWT/session — never trust client-sent `driverId` / fare amount.

```
POST /fares
  body: { pickup: {lat,lng}, destination: {lat,lng}, product? }
  → { fareId, estimate, eta, currency }

POST /rides
  body: { fareId }
  → { rideId, status: REQUESTED }   // matching async

POST /drivers/location
  body: { lat, lng, heading?, speed?, ts? }
  → 204

PATCH /rides/:rideId
  body: { action: ACCEPT | DECLINE }
  → { rideId, status, pickup }

GET /rides/:rideId          // status / assigned driver (or WebSocket push)
GET /drivers/nearby         // map pins; return fuzzed positions
```

Push channels: offer to driver; location + status to rider.

### 4. Data model / class diagram
**Entities (logical):**
- `Rider`, `Driver` (profile, vehicle, rating)
- `DriverLocation` (driverId, lat, lng, cellId, updatedAt, status) — **hot**, Redis
- `Fare` (estimate snapshot: route metrics, price, surge, expiresAt)
- `Ride` (rideId, riderId, driverId?, fareId, status, pickup, dest, timestamps)
- Optional: `Offer` (rideId, driverId, expiresAt) for audit

**Ride status:** `REQUESTED | OFFERED | ACCEPTED | EN_ROUTE | IN_TRIP | COMPLETED | CANCELLED`

**Geo index shapes:**
- Redis GEO key per city: member=`driverId`, score=geohash encoding of (lng,lat)
- *or* Redis `SET drivers:h3:{cellId}` + hash `driver:{id}` → metadata

SQL holds rides/fares/users; Redis holds “who is free where *now*”.

### 5. High-level architecture / component breakdown
```
Rider App ──┐
            ├── API Gateway ── Ride Service ── (SQL: Fare/Ride)
Driver App ─┤                      │
            │                      ├── Matching / Dispatch Service
            │                      │         │
            │                      │         ├── Geo Index (Redis GEO or H3 cells)
            │                      │         ├── ETA / Routing (Maps + traffic)
            │                      │         └── Lock (Redis TTL) / CAS on Driver
            │                      └── Notification / Push (FCM, APNs, WS)
            │
            └── Location Service ◄── high-QPS GPS ──► Redis (+ Kafka for analytics)
```

**Flows to narrate:**
1. **Ping loop:** Driver → Location Service → `GEOADD` / cell membership update (+ TTL / last-seen)
2. **Request:** Ride Service creates `REQUESTED` row → enqueue match job (Kafka/SQS), ack rider
3. **Match:** candidates from geo query → filter status/vehicle → rank by ETA → lock driver → push offer → wait accept window → cascade or fail
4. **Trip:** status transitions in SQL; location stream continues for map UX

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
**A. Geo index choice**
- **Redis GEO:** fastest interview answer; geohash under the hood; great for “nearby drivers”
- **H3 cell sets:** same API shape Uber talks about; better for surge analytics + uniform rings
- **PostGIS/quadtree alone:** fine for static POIs; painful as sole store at ~10^4–10^5 writes/s

**B. Greedy offer vs batch dispatch**
- Greedy: low latency, easy cascade, can be locally suboptimal
- Batch (marketplace): wait 2–5s, bipartite optimize ETAs — better network efficiency; harder ops

**C. Consistency / double-booking**
- Must show **atomic reserve** + **TTL unlock** on no-response
- Location staleness OK; **assignment** not OK to be wrong

**D. ETA**
- Filter with geo; rank with routing; optionally name DeepETA as production refinement

### 7. Bottlenecks / how you scale it
- **GPS write firehose:** shard Redis by city / H3 parent; adaptive ping rate (slow when parked); don’t persist every ping on match path
- **Hot downtown cells:** finer H3 resolution or split GEO keys; more match workers on that city’s queue partition
- **Match storms (stadium exit):** queue + autoscale matchers; expand k-ring / radius; surge to rebalance supply; degrade to longer ETA honestly
- **Offer timeouts:** delay queue or durable workflow (Temporal/Cadence — Uber origin story) so crashes don’t lose `REQUESTED` rides
- **Multi-region:** active city affinity; riders match only to local supply; global user DB separate from city dispatch
- **Map read amplification:** fuzz + throttle nearby queries; push location to matched rider only after accept

## Common follow-ups / gotchas
- “Why not Postgres `ORDER BY distance`?” — full scan / bad multi-dim B-tree; geo index first.
- “Two riders grab the same driver?” — show CAS/lock + what the loser does next.
- “Driver never responds?” — TTL unlock + cascade; don’t block the rider forever.
- “Closest driver stuck across a river?” — ETA/routing beats Haversine; talk barriers.
- “Surge fairness / cell edges?” — H3 rings + neighbor blending; don’t cliff at geohash borders.
- “Where do historical GPS trails go?” — Kafka → analytics/OLAP; Redis is *current* only.
- Forgetting to **remove offline drivers** (TTL / last-seen sweeper) → ghost cars on the map.
- Passing `fareAmount` or `driverId` from the client — security smell; server owns both.

## Where it appears
- **Campus / new-grad:** Uber/Ola/Swiggy HLD rounds and FAANG “design Uber/nearby drivers”; expect Redis GEO + basic matching, light estimation.
- **Experienced (1–4+ YOE):** H3 vs geohash, batch vs greedy, lock TTL, city sharding, ETA/surge, queue durability — Uber, Lyft, Grab, Meta/Google geo-flavored loops, Flipkart logistics.
- **Frequency:** among the highest-signal classic HLD prompts; often paired with proximity/Yelp as the *static* twin of the same geo toolkit.
