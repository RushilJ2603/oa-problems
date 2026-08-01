# HQ16 — Design Google Maps / nearby-places (geospatial, quadtree)

**Interview relevance:** High — canonical geo HLD (campus + experienced) at Google, Meta, Amazon, Uber, Flipkart/Swiggy-style product cos; probes spatial indexes (geohash / quadtree / S2) + read-heavy LBS. Twin of HQ06 (static POIs vs moving drivers).
**Type:** HLD-question
**Prereqs:** h14_estimation, h15_building_blocks (geohash/quadtree/S2/H3), h03_caching, h04_databases_indexing / h05_db_scaling, h10_api_design; helpful: h02_load_balancing, h08_message_queues; pair with hq06_ride_hailing (same geo toolkit, dynamic writes)

## Read / watch (curated, in order)
- [ ] [Proximity Search deep dive](https://www.hellointerview.com/learn/system-design/deep-dives/proximity-search) — `Hello Interview` — **start here**: spatial trees vs encoded keys (geohash / S2 / H3); neighbor-ring + exact distance; when Redis GEO vs PostGIS
- [ ] [Proximity-Based Services (patterns)](https://www.hellointerview.com/learn/system-design/in-a-hurry/patterns) — `Hello Interview` — when geo indexes matter vs “just scan”; local-shard intuition
- [ ] [Redis Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/redis) — `Hello Interview` — `GEOADD` / `GEOSEARCH` as interview-ready hot path (geohash under the hood)
- [ ] [Proximity service (newsletter)](https://blog.bytebytego.com/p/proximity-service) — `ByteByteGo` — Alex Xu geohash intuition for Yelp / Google Maps “nearby”
- [ ] [Design Google maps (newsletter)](https://blog.bytebytego.com/p/design-google-maps) — `ByteByteGo` — alternate prompt: location firehose + **map tiles (CDN)** + navigation/ETA; mirror: [bytebytego.com guide](https://bytebytego.com/guides/design-google-maps/)
- [ ] *System Design Interview* Vol 2 — Ch.1 Proximity Service + Ch.3 Google Maps (Alex Xu) — `ByteByteGo` — full geohash/quadtree/S2 + tiles/routing treatment; [Vol 1 vs Vol 2 TOC](https://blog.bytebytego.com/p/system-design-interview-books-volume)
- [ ] [EP150: 12 Algorithms for System Design Interviews](https://blog.bytebytego.com/p/ep150-12-algorithms-for-system-design) — `ByteByteGo` — checklist that **Geohash + QuadTree** show up for LBS
- [ ] [Designing a location database: QuadTrees and Hilbert Curves](https://www.youtube.com/watch?v=OcUKFIjhKu0) — `Gaurav Sen` — spatial trees + locality-preserving curves (the vocabulary interviewers expect)
- [ ] [System Design Playlist](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — broader HLD framing; channel: [Gaurav Sen](https://www.youtube.com/channel/UCRPMAqdtSgd0Ipeef7iFsKw); pair with [system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady`
- [ ] [Announcing the S2 Library](https://opensource.googleblog.com/2017/12/announcing-s2-library-geometry-on-sphere.html) — `Google OSS` — why Google indexes geography on a **sphere**; docs: [s2geometry.io](https://s2geometry.io/), code: [google/s2geometry](https://github.com/google/s2geometry)
- [ ] [H3: Uber’s Hexagonal Hierarchical Spatial Index](https://www.uber.com/us/en/blog/h3/) — `Uber Eng` — hex k-rings vs square geohash (contrast when interviewer asks “why not H3?”); docs: [h3geo.org](https://h3geo.org/), code: [uber/h3](https://github.com/uber/h3)
- [ ] [Redis geospatial](https://redis.io/docs/latest/develop/data-types/geospatial/) — `Redis docs` — `GEOADD` / [`GEOSEARCH`](https://redis.io/docs/latest/commands/geosearch/); production-shaped shortcut for nearby POIs
- [ ] [PostGIS `ST_DWithin`](https://postgis.net/docs/ST_DWithin.html) — `PostGIS` — R-tree / GiST path for radius queries; overview: [postgis.net/documentation](https://postgis.net/documentation/)
- [ ] [Nearby Search (New) — Places API](https://developers.google.com/maps/documentation/places/web-service/nearby-search) — `Google Maps Platform` — real product API shape (`searchNearby`, circle restriction, types)
- [ ] [Geohash](https://en.wikipedia.org/wiki/Geohash) / [Quadtree](https://en.wikipedia.org/wiki/Quadtree) / [Haversine formula](https://en.wikipedia.org/wiki/Haversine_formula) — `Wikipedia` — precision vs cell size; boundary problem; exact-distance refine
- [ ] [Tiles (OpenStreetMap Wiki)](https://wiki.openstreetmap.org/wiki/Tiles) — `OSM` — zoom levels + tile grid intuition for the “Design Google Maps” rendering path
- [ ] [Design Google Maps](https://sujeet.pro/articles/design-google-maps) — senior reference — tiles + CH/A* routing + traffic overlays assembled end-to-end (read after ByteByteGo Maps chapter)
- [ ] [system-design-primer](https://github.com/donnemartin/system-design-primer) — `primer` — estimation / scaling vocabulary; [dataintensive.net](https://dataintensive.net/) (`DDIA`) for load params / percentiles framing

## Core concepts to master
- **Two interview prompts, one geo core:** (A) **Nearby places / Yelp / Places** → static POIs, read-heavy, geohash/quadtree/S2. (B) **Full Google Maps** → (A) plus **map tiles (CDN)** + **routing/ETA** + user location firehose. Scope aloud first.
- **Why B-trees fail alone:** `ORDER BY haversine(lat,lng)` or separate lat/lng range indexes still scan huge candidate sets; you need a **2D spatial index** or a **1D encoding** that preserves locality.
- **Geohash pattern:** encode (lat, lng) → base32 string; shared prefix ⇒ same/nearby cell; pick precision from radius (~6 ≈ 0.6 km, ~5 ≈ 2.4 km). Query **center cell + 8 neighbors**, then **Haversine** (or Redis distance) to refine. Never return raw cell contents as “within radius.”
- **Boundary / edge problem:** two points meters apart can sit in different cells (or across equator/antimeridian) with short shared prefixes — neighbor ring (or S2 coverings) is mandatory; stating this unprompted is a strong signal.
- **Quadtree:** recursively split plane into 4 until leaf capacity (e.g. ≤N POIs). **Density-adaptive** (downtown deep, ocean shallow); great in-memory index for static/near-static data; **painful under heavy moves** (rebalance). Interview line: “Google Maps–style serving often keeps quadtree segments in memory per region.”
- **S2 (Google) vs H3 (Uber) vs geohash:** S2 = sphere + Hilbert curve, uniform-ish cells, region coverings — Google’s geography DB story. H3 = hex k-rings (cleaner neighbors) — dispatch/surge. Geohash = simplest / what Redis GEO uses. Pick one and know the tradeoff.
- **Static vs dynamic geo:** POIs update rarely → DB + **Redis result cache** keyed by `geohash:category:radius`. Drivers/users move every few seconds → in-memory GEO / cell sets, short TTL, no multi-minute nearby cache (see hq06).
- **Two-phase retrieval:** (1) cheap candidate generation via cells/GEO; (2) exact filter + rank (distance, rating, open-now, personalization). Ranking is a separate deep dive — don’t invent ML; say “features → ranker.”
- **Read/write split:** LBS search QPS ≫ business CRUD; primary-replica / cache-first on read path; eventual consistency on “hours open” is usually OK; assignment/booking is not this problem.
- **Maps rendering (if asked):** world map → **tiles** at zoom levels; static tiles → object store + **CDN**; pan/zoom loads precomputed neighbors — not one giant image.
- **Navigation (if asked):** geocode address → road graph shortest path (A* / contraction hierarchies) → ETA with traffic overlay; crow-flies ≠ drive time.
- **Shard by geography:** geohash/S2 prefix or city/region so a NYC nearby query hits 1–2 shards, not the globe.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈45 min). Default scope: **nearby places / proximity service**. If interviewer says “Design Google Maps,” add tiles + routing as separate components after the geo index.

### 1. Requirements (functional + non-functional) & scale assumptions
**Functional (top 3–4):**
- Search places near `(lat, lng)` within radius `R` (or return top-K nearest)
- Filter by category / type (restaurant, gas, ATM); optional min rating / open-now
- View place details (name, address, hours, photos metadata)
- Admin: add / update / soft-delete a place (can be eventually visible)

**Out of scope (unless probed):** full turn-by-turn navigation, map tile pipeline, reviews/UGC, payments, ads.

**If “Design Google Maps”:** also location pings, tile serving, A→B routes + ETA.

**Non-functional:**
- Search latency: **&lt;100–200 ms p99** typical interview target
- Extremely **read-heavy** (often cited ~100:1+)
- Global scale, but queries are **local**
- Slight staleness on place metadata OK; don’t invent strong consistency needs

**Assumptions to state aloud:** ~100–200M places globally; discrete radii (500m / 1km / 5km / 20km); return top 20; one region first, then geo-shard.

### 2. Back-of-envelope estimation
Narrate assumptions; round aggressively (see h14).

Example framing (tune with interviewer):
- 200M places × ~500 B metadata ≈ **~100 GB** raw (fits sharded SQL/doc easily; index + replicas larger)
- 100M DAU × 10 nearby searches/day ≈ **~10k QPS average**; peak **5–10×** → design for **~50–100k QPS** reads
- Writes (business updates): orders of magnitude lower — **hundreds–low thousands QPS**
- Hot path working set: popular cells’ place-ID lists + place cards in **Redis** (GBs–tens of GBs per region), not full photo blobs
- Quadtree for 200M points: Vol 2–style claim — index often **fits in memory on a handful of region servers** once built

Implication: optimize **read path + cache**; geo index must shrink candidates before Haversine.

### 3. API / interface
Keep auth on admin writes; never trust client-sent ranking scores.

```
GET /v1/places/nearby
  ?lat=&lng=&radius_m=&category=&min_rating=&limit=&cursor=
  → { places: [{ placeId, name, lat, lng, distance_m, rating, categories[] }], nextCursor? }

GET /v1/places/:placeId
  → { placeId, name, address, lat, lng, hours, rating, attributes… }

POST /v1/places
  body: { name, lat, lng, categories[], … }
  → { placeId }

PATCH /v1/places/:placeId
  body: { …fields }
  → { placeId }

# Optional “full Maps” extras
GET /v1/maps/tiles/:z/:x/:y.png     // CDN-facing
POST /v1/directions
  body: { origin, destination, mode?, avoid? }
  → { routes: [{ polyline, eta_s, distance_m }] }
```

Product analogy: [Places Nearby Search](https://developers.google.com/maps/documentation/places/web-service/nearby-search).

### 4. Data model / class diagram
**Entities (logical):**
- `Place` (placeId, name, address, lat, lng, geohash/s2CellId, categories[], rating, hours, status, updatedAt)
- `PlaceMedia` (optional, separate store — not on search hot path)
- `GeoCell` / index side: `cellId → [placeId…]` (Redis SET / SQL secondary index)

**Tables / stores:**
- **Primary DB** (Postgres + optional PostGIS, or MySQL + geohash column + B-tree): source of truth for Place
- **Redis:** (a) `nearby:{precision}:{geohash}:{category}:{radius}` → ranked place IDs (TTL minutes); (b) `place:{id}` → JSON card; optionally Redis GEO for live demos
- **Object store + CDN:** tiles / photos (Maps prompt)

**Index shapes to draw:**
- Geohash string column + prefix / IN-list of 9 cells
- *or* in-memory **quadtree** per region rebuilt on deploy / async refresh
- *or* S2 cell ID ranges covering the search circle

### 5. High-level architecture / component breakdown
```
Mobile / Web ── API Gateway ── Place Search (LBS) ── Redis (nearby cache + place cards)
                                    │
                                    ├── Geo Index (geohash/S2/quadtree / Redis GEO / PostGIS)
                                    └── Place Service ── Primary DB (replicas)
                                              │
                                              └── (async) cache invalidation / index updater

# If “Design Google Maps” also:
Client ── CDN ◄── Tile Store (S3)
      └── Navigation ── Geocoder + Route Planner (graph tiles) + Traffic / ETA
      └── Location Service ── NoSQL (high-write pings) ──► traffic / map freshness
```

**Flows to narrate:**
1. **Nearby read:** compute cell(s) for `(lat,lng,R)` → cache lookup → on miss, query geo index (9 geohashes or S2 covering or quadtree leaves) → fetch place cards → Haversine filter → rank → cache → return
2. **Write:** Place Service upserts DB → update geo membership (old cell → new cell) → invalidate `nearby:*` keys for affected cells (or short TTL)
3. **Maps tile:** client requests `z/x/y` → CDN hit; miss loads pre-rendered tile from object store
4. **Directions:** geocode → load routing subgraph / tiles → shortest path → apply traffic → ETA → return polyline

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
**A. Geohash vs quadtree vs S2**
- **Geohash:** simple, DB-friendly prefix scans, Redis-native; fixed grid → uneven load; boundary ring required
- **Quadtree:** adapts to density; natural for in-memory static indexes; updates / rebalance harder; harder to shard as a string key
- **S2:** spherical, Hilbert locality, region coverings — Google’s answer for global geography; more API surface than geohash

**B. Redis GEO / cache vs PostGIS alone**
- **Redis GEO / cell cache:** sub-ms candidate fetch; win for high QPS read path
- **PostGIS `ST_DWithin`:** correct GIS semantics, polygons, complex filters; may need read replicas + still cache for Maps-scale QPS
- Interview default: **geohash (or Redis GEO) + Haversine refine + Redis result cache**; name PostGIS/S2 as upgrades

**C. Cache key design**
- Bucket radius to discrete values; key includes precision + cell + category — continuous free-form radius → ~0 hit rate
- Invalidate on write (pub/sub / Kafka) vs short TTL; for static POIs TTL of 1–5 min is often enough

**D. Full Maps only — preprocessing vs query latency**
- Tile pyramid + contraction hierarchies / preprocessed routing buy **ms** queries at cost of offline builds; traffic as overlay multipliers, not full graph rebuild every minute

### 7. Bottlenecks / how you scale it
- **Hot downtown cells:** finer precision, split GEO keys / shards by child cells, more LBS replicas on that region; don’t one-size precision globally
- **Read amplification:** cache place cards; paginate; avoid joining photos on search path
- **Sparse areas:** expanding-ring search (widen precision / k-ring) until `limit` met or max radius
- **Write → index lag:** async updater; accept brief stale nearby lists; for closures, push invalidation
- **Shard routing:** first 2–3 geohash / S2 parent chars → region; cross-boundary queries fan out to ≤2 shards
- **Tile / photo bandwidth:** CDN + HTTP cache headers; separate from LBS cluster autoscaling
- **Multi-region:** serve LBS from nearest region with local replica of that geography; GDPR/residency as follow-up, not day-one design

## Common follow-ups / gotchas
- “Why not `SELECT * WHERE distance < R`?” — full scan / can’t index the expression; show cell filter first.
- “User on a cell edge misses a restaurant 10 m away?” — **9-cell / neighbor ring** (or S2 covering); classic trap.
- “Geohash vs quadtree — which do you ship?” — geohash for DB/Redis simplicity; quadtree if density skew + mostly static in-memory index; S2 if interviewer steers Google-shaped.
- “Same design as Uber?” — no: POIs are **static/read-heavy + cacheable**; drivers are **write-heavy + consistency on assignment** (hq06).
- “How do map tiles work?” — zoom pyramid, `z/x/y`, CDN; not one bitmap of Earth.
- “ETA = Haversine?” — only for candidate sort tie-break; navigation uses **road graph + traffic**.
- Forgetting to **remove deleted/moved** places from old cells → ghosts in nearby results.
- Caching with unbounded continuous `radius` query params → useless cache; bucket it.

## Where it appears
- **Campus / new-grad:** “Design Yelp / nearby restaurants / Google Maps nearby”; expect geohash + 9 neighbors + Redis cache, light estimation.
- **Experienced (1–4+ YOE):** geohash vs quadtree vs S2/H3, hot-cell sharding, cache invalidation, PostGIS vs Redis GEO; full “Design Google Maps” adds tiles + routing/ETA (Google, Meta, Amazon geo loops; Maps/Flipkart logistics flavor).
- **Frequency:** among the highest-signal classic HLD prompts; **static twin** of ride-hailing proximity — interviewers often reuse the same geo toolkit across both.
