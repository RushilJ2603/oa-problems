# H12 — Search (inverted index, Elasticsearch, ranking, autocomplete indexing)

**Interview relevance:** High — keyword/product/tweet search and typeahead appear constantly in HLD rounds; FAANG + Indian product cos (Flipkart, Uber, Atlassian) expect inverted index + ranking, and often a separate autocomplete design.
**Type:** HLD-foundation
**Prereqs:** h04_databases_indexing (indexes / LSM-shaped segments); helpful: h03_caching, h08_message_queues (async index updates)

## Read / watch (curated, in order)
- [ ] [Design Twitter — search use case](https://github.com/donnemartin/system-design-primer/blob/master/solutions/system_design/twitter/README.md) — `primer` — tokenize → Lucene/search cluster → scatter-gather → merge/rank; search as a separate index path from timelines
- [ ] [Inverted index](https://en.wikipedia.org/wiki/Inverted_index) — `Wikipedia` — term → postings (doc IDs; optionally positions); why it beats scanning a forward index
- [ ] [8 Data Structures That Power Your Databases](https://bytebytego.com/guides/8-data-structures-that-power-your-databases/) — `ByteByteGo` — inverted index called out as the document-search structure (Lucene)
- [ ] [Inverted Index - The Data Structure Behind Search Engines](https://www.youtube.com/watch?v=iHHqnyThrqE) — `Arpit Bhayani` — build/tokenize/stem, posting lists (tf + positions), sorted lists + delta encoding (~15 min)
- [ ] [System Design Key Technologies — Search Optimized Database](https://www.hellointerview.com/learn/system-design/in-a-hurry/key-technologies) — `Hello Interview` — inverted index framing; when Elasticsearch vs Postgres FTS; interview depth expectations
- [ ] [Elasticsearch Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/elasticsearch) — `Hello Interview` — Lucene segments, inverted index + doc values, shards/replicas, coordinating node, not-a-primary-DB tradeoffs
- [ ] [Elasticsearch from the Bottom Up, Part 1](https://www.elastic.co/blog/found-elasticsearch-from-the-bottom-up) — `Elastic` — inverted index → analyzers → immutable segments → merges → shard = Lucene index
- [ ] [DDIA Ch.3 — Storage and Retrieval](https://dataintensive.net/) — `DDIA ch.3` — Lucene term dictionary / postings as SSTable-like files; fuzzy/edit-distance indexes ([free notes](https://timilearning.com/posts/ddia/part-one/chapter-3/); also [Shichao notes](https://notes.shichao.io/dda/ch3/))
- [ ] [How do we learn ElasticSearch?](https://blog.bytebytego.com/p/ep36-types-of-databases-and-use-cases) — `ByteByteGo` — ES as distributed Lucene: product search, autocomplete, logs; term dictionary / LSM-shaped segments
- [ ] [Text analysis](https://www.elastic.co/docs/manage-data/data-store/text-analysis) — `Elasticsearch docs` — analyzers (char filter → tokenizer → token filters) define what becomes searchable terms
- [ ] [Practical BM25 — Part 2](https://www.elastic.co/blog/practical-bm25-part-2-the-bm25-algorithm-and-its-variables) — `Elastic` — TF saturation (`k1`), length norm (`b`); default Lucene/ES scorer ([Okapi BM25](https://en.wikipedia.org/wiki/Okapi_BM25); [similarity module](https://www.elastic.co/docs/reference/elasticsearch/index-settings/similarity))
- [ ] [Design Facebook's Post Search](https://www.hellointerview.com/learn/system-design/problem-breakdowns/fb-post-search) — `Hello Interview` — build a keyword inverted index yourself (tokenization, Redis postings, ranking by recency/likes) without naming ES
- [ ] [System Design Interview Vol.1 Ch.13 notes — Search Autocomplete](https://noahtigner.com/articles/system-design-interview-volume-1-chapter-13/) — `ByteByteGo / Alex Xu` companion — trie + precomputed top-K, offline aggregation, hot-prefix cache, <100ms budget
- [ ] [Typeahead Suggestion Design Deep Dive](https://www.youtube.com/watch?v=1moO3rn42uk) — `Jordan has no life` — interview walkthrough of typeahead (trie, sharding, update path)
- [ ] [Suggesters (completion)](https://www.elastic.co/docs/reference/elasticsearch/rest-apis/search-suggesters) — `Elasticsearch docs` — in-memory FST completion suggester for autocomplete; pair with [search-as-you-type](https://www.elastic.co/docs/reference/elasticsearch/mapping-reference/search-as-you-type) and [edge_ngram tokenizer](https://www.elastic.co/docs/reference/text-analysis/analysis-edgengram-tokenizer) / [Elasticsearch Labs autocomplete overview](https://www.elastic.co/search-labs/blog/elasticsearch-autocomplete-search)
- [ ] [Visualizing Lucene's segment merges](https://blog.mikemccandless.com/2011/02/visualizing-lucenes-segment-merges.html) — `Michael McCandless` — why segment count / merges affect search latency and deletes (optional depth)
- [ ] [Apache Lucene](https://lucene.apache.org/) — `Lucene` — library under Elasticsearch / OpenSearch / Solr (skim; don't implement)

## Core concepts to master
- **Inverted index:** map `term → postings list` (doc IDs, often tf + positions). Query = look up terms, **intersect/union** postings, then **rank**. Forward index (doc → terms) is for display/snippets, not retrieval.
- **Analysis / tokenization:** lowercase, stop words, stemming/lemmatization, synonyms — index-time and query-time analyzers must agree or you get silent misses. Positions enable **phrase** / proximity queries.
- **Lucene segment model:** buffer → flush **immutable segments** → background **merge**; deletes are soft until merge. Same LSM intuition as DDIA ch.3 / RocksDB — write amp vs read amp.
- **Elasticsearch layout:** cluster → **index** → **primary shards** (+ replicas); each shard is a Lucene index. Query fans out (scatter-gather); p99 ≈ slowest shard. Prefer **document-partitioned** shards over term-sharding for multi-term queries.
- **Near-real-time indexing:** refresh makes new segments searchable (default ~1s); bulk reindex / high write load → raise `refresh_interval`. Source of truth is usually OLTP DB + **async** index via queue/CDC — ES is a **derived** search store, not the system of record.
- **Ranking (BM25):** default relevance = term rarity (IDF) + saturated TF + doc-length normalization. Interview add-ons: freshness, popularity/CTR, personalization, business boosts — often a **multi-stage** cascade (cheap retrieval → heavier re-rank).
- **Autocomplete ≠ full-text search:** latency budget is brutal (often <100ms). Canonical pattern = **prefix structure** (trie / FST) with **precomputed top-K** at each prefix; online path is a lookup, not a subtree scan + sort.
- **Autocomplete update path:** log queries → aggregate frequencies (batch/stream) → rebuild suggestion index → **atomic swap**. Trending = short-window overlay (e.g. Redis) merged at serve time; don't mutate the hot trie on every search.
- **ES autocomplete options:** **completion suggester** (fast, in-memory FST, prefix-oriented); **search_as_you_type** / **edge n-grams** (more flexible matching, larger index). Interview answer: trie/top-K for custom typeahead; ES suggester if you already run ES.
- **When not to use ES:** strong transactional source of truth, heavy point updates of single fields, or tiny corpora where Postgres FTS / simple inverted map in Redis is enough.

## Practice — how it's asked & how to attack it
1. **Drill — draw an inverted index:** For docs `{1: "red fox", 2: "fox jumps", 3: "red car"}`, build term → postings; execute `red AND fox` by intersection; say what positions would add for `"red fox"` phrase.
2. **Drill — why not SQL `LIKE '%foo%'`?** Explain full scan / leading-wildcard pain vs inverted index; when Postgres `tsvector` / GIN is "good enough" vs dedicated search.
3. **Drill — BM25 intuition:** Two docs both contain "elastic"; one is 20 tokens, one is 2000. Which ranks higher for query `elastic` and why (`b`)? What does raising `k1` change?
4. **Drill — index pipeline:** User creates a product/tweet. Sketch write path: primary DB commit → queue → indexer → ES. Name freshness lag, dual-write failure, and how you'd reindex.
5. **Drill — autocomplete top-K:** Prefix `"app"`. Explain why storing top-5 completions **on the trie node** beats DFS+sort at query time; how often you rebuild; how "breaking news" trends appear before the next full rebuild.
6. **Drill — shard fan-out:** 64 shards, query must touch all. What dominates latency? Name one mitigation (replicas, hedged requests, time-based indices, routing by user).

## Common follow-ups / gotchas
- "Is Elasticsearch a database?" — No for money/orders; yes as a **search/analytics secondary index**. Plan rebuild + lag + inconsistency with the primary.
- "Update one field in a big document?" — Lucene updates ≈ delete + reindex whole doc → write amplification; denormalize carefully.
- "Deep pagination (`from`/`size` large)?" — expensive; prefer `search_after` / cursor-style pagination.
- "How do you get phrases / typo tolerance?" — positions for phrases; fuzziness / n-grams / suggesters for typos (costly — gate by prefix length).
- "Trie vs Elasticsearch for typeahead?" — custom trie/FST + cache for ultra-low latency & simple popularity ranking; ES completion/search-as-you-type when ops simplicity and fuzzy/infix matter more.
- "Hot terms / stop words?" — huge postings; stop-word removal, champion lists, or don't rank on ultra-common terms alone.

## Where it appears
- **Campus / new-grad HLD:** "Design Twitter/YouTube/e-commerce search" and **"design autocomplete/typeahead"** are staples; expecting inverted index + basic ranking + cache is enough.
- **Experienced / mid-level:** ES/Lucene internals (segments, shards, BM25), async indexing consistency, and autocomplete precompute vs freshness tradeoffs separate strong answers.
- **Frequency:** high whenever the product has a search box; autocomplete is its own frequent standalone question (Google/Amazon/Meta-style).
