# hq09 — Design search autocomplete / typeahead

**Interview relevance:** High — Alex Xu Vol.1 ch.13 classic; asked standalone and as the suggestion box inside Search / e-commerce / Maps designs (campus + experienced; Google, Meta, Amazon, LinkedIn, Uber, Flipkart, Databricks).
**Type:** HLD-question
**Prereqs:** h03_caching, h08_message_queues, h14_estimation; DSA trie/prefix trees; helpful: h02_load_balancing, h05_db_scaling

## Read / watch (curated, in order)
- [ ] [Design A Search Autocomplete System (ByteByteGo course / Alex Xu Vol.1 ch.13)](https://bytebytego.com/courses/system-design-interview/design-a-search-autocomplete-system) — `ByteByteGo` — canonical interview walk-through: scope, trie + top-K, data gathering, caching, scale (course may be gated); TOC proof: [Vol.1 vs Vol.2 chapter list](https://blog.bytebytego.com/p/system-design-interview-books-volume)
- [ ] [Design A Search Autocomplete System (free notes)](https://www.gauravaryal.com/system-design/design-a-search-autocomplete-system/) — `Alex Xu notes` — free restatement of ch.13 numbers (10M DAU → ~24k/48k QPS) + trie deep dive; pair with [Noah Tigner ch.13 notes](https://noahtigner.com/articles/system-design-interview-volume-1-chapter-13/)
- [ ] [Design Typeahead Search](https://www.hellointerview.com/community/questions/typeahead-search-system/cm7l2wazy00t7105qdvnemtwy) — `Hello Interview` — prompt framing (asked at Meta / Databricks / Expedia / …); non-personalized suggestions focus
- [ ] [Trie Overview](https://www.hellointerview.com/learn/code/trie/overview) — `Hello Interview` — prefix-tree ops before the HLD; pair with coding drill [LC 642 Design Search Autocomplete System](https://www.hellointerview.com/community/questions/design-search-autocomplete-system/67257ab0-683b-481d-bfd2-f7e63258056e)
- [ ] [Typeahead Suggestion Design Deep Dive with Google SWE](https://www.youtube.com/watch?v=1moO3rn42uk) — `Jordan has no life` — long-form whiteboard: API, trie, async aggregation, cache, partition
- [ ] [Search Autocomplete - System Design](https://www.youtube.com/watch?v=LLBrV5qRT3o) — `Code with Lucian` — shorter visual pass of the same dual-path design
- [ ] [Typeahead / Autocomplete System Design](https://systemdesignschool.io/problems/typeahead/solution) — `System Design School` — crisp “rank offline, lookup online” principle + top-K-at-node
- [ ] [Design Search Autocomplete (Typeahead Suggestions)](https://hld.handbook.academy/curriculum/case-studies/search-autocomplete/) — `HLD Handbook` — CDN + immutable trie + streaming trending overlay (lambda hybrid); precompute vs freshness
- [ ] [8.14 Design an autocomplete/typeahead system](https://www.systemdesigninterview.com/guides/system-design-interview-handbook/814-design-an-autocompletetypeahead-system) — `System Design Interview Handbook` — hot path vs cold path; top-K stored on every trie node
- [ ] [Design Search Autocomplete: Prefix Matching at Scale](https://sujeet.pro/articles/design-search-autocomplete) — `Sujeet Jaiswal` — production-shaped Path A (in-memory trie) vs Path B (Elasticsearch completion / FST)
- [ ] [The Life of a Typeahead Query](https://engineering.fb.com/2010/05/17/web/the-life-of-a-typeahead-query/) — `Meta Eng` — **>100 ms → stutter**; aggregator + leaf services; browser bootstrap cache (latency folklore interviewers expect)
- [ ] [You Complete Me](https://www.elastic.co/blog/you-complete-me) — `Elastic` — why a dedicated completion suggester (in-memory FST) beats full search for typeahead; pair with docs: [Completion suggester](https://www.elastic.co/guide/en/elasticsearch/reference/8.19/search-suggesters.html)
- [ ] [Trie](https://en.wikipedia.org/wiki/Trie) — `Wikipedia` — prefix-tree vocabulary if rusty
- [ ] [Caching for System Design Interviews](https://www.hellointerview.com/learn/system-design/core-concepts/caching) — `Hello Interview` — where CDN / Redis / in-process cache sit on a keystroke path; pair with [primer — Cache](https://github.com/donnemartin/system-design-primer#cache)
- [ ] [EP104: How do Search Engines Work](https://blog.bytebytego.com/p/ep104-how-do-search-engines-work) — `ByteByteGo` — optional context: autocomplete ≠ full search (crawler / inverted index); keep typeahead scoped
- [ ] [System Design Playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — foundations (caching, queues, estimation) used in this design; no dedicated autocomplete episode — use ByteByteGo ch.13 for the problem itself
- [ ] [InterviewReady — system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` / Gaurav Sen org — curated dump (search / Elastic pointers); browse after the walk-through

## Core concepts to master
- **Product:** given prefix `p`, return **top-K** (usually 5–10) completions ranked by popularity (frequency ± recency). Prefix match at start only unless interviewer asks mid-string / fuzzy.
- **Latency SLO:** end-to-end **< ~100 ms** or the UI “stutters” (Meta Eng). Backend budget often **tens of ms**; client debounce (~100–300 ms) cuts QPS.
- **Two timelines:** **online read path** (keystroke → suggestions) vs **offline/async write path** (logs → aggregate → rebuild index). Never mutate a shared trie on every search under read load.
- **Trie (prefix tree) + top-K at each node:** walk O(|prefix|), then **return precomputed list** — no subtree DFS / sort on the hot path. Without top-K cache, short prefixes explode.
- **Alternative store:** `prefix → [top-K]` in Redis / Cassandra / KV (still precomputed). Elasticsearch **completion suggester** (in-memory FST) is the managed Path-B.
- **Ranking signals:** historical frequency (default), recency / trending overlay, locale, optional personalization (re-rank top-30 → top-10 offline of the critical path).
- **Caching layers:** browser / CDN for power-law popular prefixes → Redis → in-memory trie shard. Eventual staleness (minutes–hours) is OK for suggestions.
- **Freshness:** nightly/hourly **batch rebuild** of immutable trie + optional **streaming overlay** (Kafka → Flink → Redis) for breaking trends — classic precompute vs freshness tradeoff.
- **Scale:** shard trie / prefix map by **prefix range** (or first chars); replicate shards; hot short prefixes (“a”, “the”) need cache / dedicated handling.
- **Abuse / quality:** rate-limit clients; filter NSFW / injection; trending needs velocity / uniqueness checks so poisoning doesn’t dominate.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (~45 min). Clarify Google-bar query suggestions (not full search results page, not Maps place autocomplete) unless told otherwise.

### 1. Requirements (functional + non-functional) & scale assumptions
**Clarify first:** prefix-only vs infix? K=? Rank by frequency only? Typo / spellcheck? Personalization? Languages? Case / charset?

**Functional (typical Alex Xu scope):**
- As user types, return **top 5** queries that **start with** the prefix.
- Rank by **historical search frequency**.
- English lowercase letters only (extend later).
- No spellcheck in MVP.

**Non-functional (typical):**
- **p99 < 100 ms** perceived; high availability.
- Eventual consistency OK (suggestions can lag hours).
- Scale: **~10M DAU** class unless interviewer gives other numbers.

**Out of scope (draw the line):** full web search ranking, ads, rich entity cards, Maps geocode — unless asked.

### 2. Back-of-envelope estimation
Alex Xu–style numbers (say them out loud; adjust if interviewer disagrees):

| Assumption | Example |
|---|---|
| DAU | **10M** |
| Searches / user / day | **10** |
| Avg chars / query (requests if no debounce) | **~20** → ~**20 AJAX calls / search** |
| Avg QPS | 10M × 10 × 20 / 86400 ≈ **~24k QPS** |
| Peak QPS | ~**2×** → **~48k QPS** |
| New unique query storage / day | ~20% new × 10M × 10 × ~20 B ≈ **~0.4 GB/day** raw strings |

With client **debounce**, QPS drops a lot — mention it; still design for tens of kQPS. Storage of the **serving** index is dominated by trie / prefix→top-K, not raw logs (logs live in warehouse / object store).

### 3. API / interface
Public suggestion API (REST or similar):

```
GET /v1/suggest?prefix=din&limit=5&locale=en_US
→ 200 {
  "prefix": "din",
  "suggestions": [
    {"query": "dinner ideas", "score": 0.92},
    {"query": "dinosaur", "score": 0.81}
  ]
}
```

Optional: `Authorization` / `session` for personalized re-rank; `If-None-Match` / short `Cache-Control` for CDN.

Analytics (async, not on suggest path): search submit / click-through events → log pipeline.

Admin / offline: rebuild job trigger, blocklist CRUD — not the interview focus.

### 4. Data model
**Query log event** (append-only): `{query, user_id?, locale, ts, session_id?}`.

**Frequency table** (aggregated): `{normalized_query, count_window, locale}` — warehouse / Cassandra / KV after batch or stream aggregate.

**Serving index** (choose one and stick to it):
- **Trie node:** `children[char]`, `topK: [(query, score)]` (size ≤ K) computed at build time.
- **Or KV:** key = `prefix` (or `locale:prefix`), value = ordered top-K JSON / protobuf.

**Versioning:** `index_version` / snapshot id; atomic pointer flip so servers never serve a half-built trie.

Optional: `trending:{prefix}` Redis ZSET for speed-layer overlay; `user_recent_queries` for personalization.

### 5. High-level architecture / component breakdown
**Default interview design (most common “great” path):**

```
[Client debounce] → CDN / edge cache
                         ↓ miss
                   Suggest API / LB
                         ↓
              Trie / prefix servers (RAM, sharded by prefix)
                         ↓ miss hot path only
                   Redis (hot prefixes)

Write / cold path:
Search submit → Kafka → aggregator (Spark/Flink batch ± stream)
  → frequency table → Trie builder → object storage snapshot
  → push / pull → atomic swap on suggest servers
  (+ optional Redis trending overlay)
```

- **Client:** debounce; cancel in-flight requests; local filter of last response as user types more chars.
- **Suggest service:** normalize prefix → cache → trie walk → merge trending → optional light re-rank → return K.
- **Data pipeline:** never blocks keystrokes; rebuild hourly/daily; stream overlay for news-scale freshness.
- **Name alternatives:** Elasticsearch completion suggester instead of custom trie (ops simpler, slightly higher latency).

### 6. Deep dives & the 2–3 key tradeoffs interviewers probe
**A. Query-time traversal vs precomputed top-K**
- Naive: DFS subtree + heap on every keystroke → blows p99 on short prefixes.
- Interview answer: **store top-K on every node** (or materialize `prefix → top-K`) at build time; read path is walk + return.

**B. Freshness vs latency (batch vs realtime)**
- Update trie on every search → write contention, hard to scale.
- Batch rebuild → stale trends (election / viral meme).
- Hybrid: immutable trie for >99% + **streaming trending overlay** merge at query time (handbook / production pattern).

**C. Personalization**
- Global top-K is cacheable and CDN-friendly.
- Personalized results **fragment caches** — fetch global top-N, re-rank with user history in ~few ms, or personalize only after cache miss / logged-in path.

**D. Custom trie vs Elasticsearch / FST**
- Custom trie: lowest latency, full control, you own sharding + deploy.
- ES completion: faster to ship, fuzzy/context options, FST in heap — good Path-B if cluster already exists.

### 7. Bottlenecks / how you scale it
- **QPS:** debounce + CDN/Redis for head prefixes (power law); horizontally scale stateless suggest tier.
- **Hot prefixes** (1–2 chars): almost always cached; optionally require min prefix length (e.g. 2–3) before hitting origin.
- **Memory:** full English query trie can be tens of GB → **shard by prefix**; each host holds a range; replicate for HA.
- **Rebuild deploy:** blue/green or versioned snapshot + atomic flip; rolling reload so not all hosts GC at once.
- **Pipeline lag / poison trends:** windowed counts + uniqueness checks; kill switch to disable overlay.
- **Multi-region:** serve from nearest region’s replica of the snapshot; global exact ranking not required.

**30-second closing line:** “Debounced suggest API, in-memory trie with top-K precomputed per node, offline Kafka→aggregate→atomic trie swap, CDN/Redis for hot prefixes, optional trending overlay for freshness, shard by prefix — keep p99 under 100 ms.”

## Common follow-ups / gotchas
- “Just `SELECT … LIKE 'pre%'`” — too slow / not ranked; needs prefix index + precomputed top-K.
- Forgetting **top-K on nodes** — interviewer will ask about complexity under prefix `"a"`.
- Updating the trie **synchronously** on every search — couples write amplification to the latency path; prefer async rebuild / overlay.
- **No debounce** → 5–10× QPS; clients must debounce and abort stale responses.
- Personalization vs CDN — personalized responses rarely edge-cached; separate global vs personalized path.
- Typos / fuzzy — out of MVP; add edit-distance / separate spell service or ES fuzzy completion if asked.
- Analytics poisoning — bots inflating counts; need rate limits + trusted-session filters on the ranking pipeline.
- AJAX waterfall vs WebSocket — REST/HTTP fine; WS rarely needed for suggest.

## Where it appears
- **Campus / intern / new-grad HLD:** very common as “Design autocomplete / typeahead / Google search suggestions”; also the suggestion box inside Amazon / Flipkart / YouTube designs.
- **Experienced (1–4+ YOE):** deeper on sharding, atomic index swap, trending overlay, personalization vs cache, ES/FST vs custom trie, multi-locale — Meta, Google, Amazon, LinkedIn, Uber, Databricks.
- **Frequency:** high — Alex Xu Vol.1 ch.13 staple and a standard “top-K + prefix index” probe.
