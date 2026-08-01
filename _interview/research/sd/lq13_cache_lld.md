# LQ13 — Design an LRU / LFU Cache

**Interview relevance:** High — the bridge LLD + DSA design problem (coding screens + OOD rounds); Amazon, Google, Meta, Microsoft, Uber, Flipkart, Atlassian, and most product cos probe HashMap+DLL composition, Strategy for eviction, and concurrency.
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Factory), l03_patterns_structural (Proxy/Decorator); Strategy / Observer from behavioral patterns; comfort with HashMap + doubly linked list (or Refactoring.Guru + LeetCode 146 first)

## Read / watch (curated, in order)
- [ ] [Designing a LRU Cache (problem + UML + multi-lang code)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/lru-cache.md) — `awesome-low-level-design` — **start here:** requirements (O(1) get/put, capacity, thread-safety), [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/lrucache-class-diagram.png); hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Java lrucache solution](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/lrucache) — `awesome-low-level-design` — runnable `Node` + `LRUCache` with `synchronized` get/put; also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/lrucache) / [C++](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/cpp/lrucache) / [Go](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/golang/lrucache)
- [ ] [Design LRU Cache | LLD (AlgoMaster)](https://algomaster.io/learn/lld/design-lru-cache) — `AlgoMaster` — clean entity split: `Node` / `DoublyLinkedList` / `LRUCache`, SOLID notes, synchronized API
- [ ] [LRU and LFU Cache (LLD-flavoured)](https://ikshitij.com/learn/lld-object-oriented/lru-lfu-cache/) — `ikshitij` — **both policies in one page:** class diagrams, O(1) recipes, thread-safety table, TTL, stats, production libs (Caffeine / Redis)
- [ ] [LRU Cache - Twitch Interview Question - Leetcode 146 (NeetCode)](https://www.youtube.com/watch?v=7ABFKPK2hD4) — `YouTube / NeetCode` — visual HashMap + DLL walkthrough; pair with written [NeetCode LRU solution](https://neetcode.io/solutions/lru-cache)
- [ ] [146. LRU Cache (problem + HashMap+DLL solution)](https://github.com/doocs/leetcode/blob/main/solution/0100-0199/0146.LRU%20Cache/README_EN.md) — `doocs/leetcode` — free mirror of the canonical coding prompt (same as [leetcode.com/problems/lru-cache](https://leetcode.com/problems/lru-cache/))
- [ ] [Leetcode 146. LRU Cache (Hello Interview)](https://www.hellointerview.com/community/questions/lru-cache/cm5eh7nrh04r2838os7lk8nwf) — `Hello Interview` — why HashMap alone fails + sentinel head/tail framing
- [ ] [LFU Cache Implementation (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/least-frequently-used-lfu-cache-implementation/) — `GeeksforGeeks` — LFU semantics + tie-break by LRU; then code O(1) yourself
- [ ] [460. LFU Cache (Doocs wiki)](https://leetcode.doocs.org/en/lc/460/) / [NeetCode LFU explanation](https://neetcode.io/solutions/lfu-cache) — `doocs` / `NeetCode` — Hard follow-up: freq → DLL buckets + `minFreq`; problem hub: [leetcode.com/problems/lfu-cache](https://leetcode.com/problems/lfu-cache/)
- [ ] [Leetcode 460. LFU Cache (Hello Interview)](https://www.hellointerview.com/community/questions/lfu-cache/cm5eguhab02d6838o87irm4sz) — `Hello Interview` — eviction = tail of `minFreq` list; reset `minFreq = 1` on new insert
- [ ] [LFU cache and Java implementation](https://phamduyhieu.com/lfu-cache-and-java-implementation) — `phamduyhieu` — interview-shaped Java: custom DLL vs `LinkedList`, capacity-0 edge case
- [ ] [LLD Case Study: Thread-Safe LRU Cache (CalibreOS)](https://www.calibreos.com/learn/lld-lru-cache) — `CalibreOS` — senior bar: invariants, `ReadWriteLock` vs global sync, striped segments, TTL, singleflight
- [ ] [Design Thread-Safe Cache with TTL (AlgoMaster concurrency)](https://algomaster.io/learn/concurrency-interview/design-thread-safe-cache-with-ttl) — `AlgoMaster` — concurrency drill: TTL + safe concurrent access
- [ ] [Implementing a Thread-Safe LRU Cache with High Concurrency (CodeSignal)](https://codesignal.com/learn/courses/advanced-real-life-concurrency-challenges/lessons/implementing-a-thread-safe-lru-cache-with-high-concurrency) — `CodeSignal` — `ConcurrentHashMap` + order structure + `ReentrantLock` sketch
- [ ] [LinkedHashMap (Java SE 21) — `removeEldestEntry`](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/LinkedHashMap.html) — `Oracle JDK` — language shortcut for access-order LRU (not thread-safe; know when interviewers allow it)
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) / [Proxy](https://refactoring.guru/design-patterns/proxy) / [Decorator](https://refactoring.guru/design-patterns/decorator) / [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — eviction policy swap, `CacheFactory`, caching proxy in front of a store, stats/eviction listeners
- [ ] [Cache replacement policies](https://en.wikipedia.org/wiki/Cache_replacement_policies) / [Least frequently used](https://en.wikipedia.org/wiki/Least_frequently_used) / [Page replacement algorithm](https://en.wikipedia.org/wiki/Page_replacement_algorithm) — `Wikipedia` — LRU vs LFU vs FIFO/ARC vocabulary for follow-ups
- [ ] [CacheBuilder (Guava)](https://guava.dev/releases/33.4.7-jre/api/docs/com/google/common/cache/CacheBuilder.html) — `Guava` — production API shape: `maximumSize`, `expireAfterWrite`/`Access`, `RemovalListener`, stats
- [ ] [ben-manes/caffeine](https://github.com/ben-manes/caffeine) + [Design wiki](https://github.com/ben-manes/caffeine/wiki/Design) + [Efficiency (W-TinyLFU)](https://github.com/ben-manes/caffeine/wiki/Efficiency) — `Caffeine` — what “real” JVM caches do after the whiteboard LRU; overview: [Design of a Modern Cache](https://highscalability.com/design-of-a-modern-cache/)
- [ ] [TinyLFU: A Highly Efficient Cache Admission Policy (arXiv)](https://arxiv.org/abs/1512.00727) — `arXiv` — optional stretch: frequency sketch admission filter behind Caffeine’s W-TinyLFU
- [ ] [Redis key eviction](https://redis.io/docs/latest/develop/reference/eviction/) / [LFU vs LRU (Redis blog)](https://redis.io/blog/lfu-vs-lru-how-to-choose-the-right-cache-eviction-policy/) — `Redis` — approximated sampled LRU/LFU at distributed-cache scale (HLD bridge)
- [ ] [LRU cache (DSA Handbook)](https://dsa.handbook.academy/curriculum/design-the-data-structure/lru-cache/) / [LFU cache (DSA Handbook)](https://dsa.handbook.academy/curriculum/design-the-data-structure/lfu-cache/) — `DSA Handbook` — design framing + concurrency/TTL stretch after you can code O(1)
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after the happy path

## Core concepts to master
- **Clarify before coding:** capacity fixed? generic `K,V`? return sentinel vs throw on miss? does `get` count as “use” (yes for LRU/LFU)? LFU tie-break = LRU within same frequency? TTL? thread-safety? pluggable policy?
- **O(1) contract forces two structures:** HashMap alone cannot evict in O(1); a list/heap alone cannot look up by key in O(1). Compose them.
- **LRU recipe:** `Map<K, Node>` + doubly linked list (MRU at head, LRU at tail) + sentinel head/tail. On get/put hit → unlink + move to head; on capacity put → remove `tail.prev` from list *and* map (node must store `key`).
- **LFU recipe:** `Map<K, Node>` + `Map<freq, DoublyLinkedList>` + `minFreq`. On access: remove from freq list → `freq++` → add to new list; if old list empty and `freq == minFreq`, bump `minFreq`. New inserts start at freq 1 and set `minFreq = 1`. Evict = remove LRU (tail) of `minFreq` list.
- **Patterns that earn points:** **Strategy** (`EvictionPolicy` / `LRU` vs `LFU`), **Factory** (`CacheFactory.create(policy, capacity)`), **Proxy/Decorator** (cache in front of `DataStore`), **Observer** (`RemovalListener` / stats on eviction). Don’t force Singleton.
- **Class responsibilities:** `Cache` (API facade) owns capacity + map; `Node` holds key/value/(freq)/prev/next; `DoublyLinkedList` owns pointer surgery; policy owns “who to evict.”
- **LinkedHashMap shortcut (Java):** access-order + override `removeEldestEntry` → quick LRU demo; say you’d hand-roll DLL in OOD rounds and for portability / LFU / concurrency control.
- **Concurrency:** coarse `synchronized`/`ReentrantLock` on get+put is correct but serializes; senior answers mention striped/segmented locks, `ReadWriteLock` (careful: both get and put mutate order), or library designs (Caffeine read buffers + async maintenance).
- **TTL:** store absolute `expiresAt`; lazy expire on get + optional background sweeper; TTL eviction is orthogonal to LRU/LFU capacity eviction.
- **LRU vs LFU product choice:** LRU adapts fast to shifting working sets; LFU keeps long-term hot keys but can be polluted by one-time spikes (mention TinyLFU / Redis approximated LFU as production fixes).
- **SOLID signal:** OCP = new eviction policy without editing `Cache` callers; SRP = list vs map vs policy; DIP = depend on `Cache` / `EvictionPolicy` interfaces.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~30–40 min, coding ~20–45 min for LRU, +15–25 min for LFU / concurrency):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** fixed capacity; `get(key) → value | miss`; `put(key, value)` insert/update; on overflow evict by policy (LRU or LFU); both ops **O(1)** average.
- **FR (common extensions — ask):** LFU with LRU tie-break; TTL / expireAfterWrite; `invalidate` / `clear`; hit/miss/eviction stats; loading cache (`get(key, loader)`); pluggable policy at construct time.
- **NFR:** thread-safe under concurrent get/put; no unbounded memory; predictable latency; extensible policies.
- **Assumptions to state:** in-memory single process (distributed cache is HLD sibling); capacity ≥ 1 unless told capacity 0 is allowed; miss returns `-1`/`null` as agreed.
- **Use cases:** App reads key → cache hit returns value / miss loads store then `put`; write updates value and refreshes recency/freq; capacity full → evict victim then insert; optional TTL expiry independently removes stale entries.

### 2. Back-of-envelope estimation (usually light for LLD)
- Capacity often **hundreds–millions** of entries; per-entry overhead = value + pointers + (LFU) freq counters — mention memory, not just big-O.
- If “scale” is pushed: shard into N independent caches by `hash(key) % N` to cut lock contention; or jump to Redis/Memcached (approx eviction) for multi-node.

### 3. API / interface
```
Cache(capacity) / Cache(capacity, EvictionPolicy)
V get(K key)                  // miss → null | -1
void put(K key, V value)
void invalidate(K key)        // optional
CacheStats stats()            // hits, misses, evictions

// LFU-specific invariant (state, not API):
// minFreq tracks lowest frequency present
```
OOD method surface:
```
Cache.get / put
DoublyLinkedList.addFront / remove / removeLast
EvictionPolicy.onAccess(node) / selectVictim() → Node
LRUCache.moveToHead / evictLRU
LFUCache.incrementFreq / evictLFU
```

### 4. Data model / class diagram
```
Cache <<interface>>
  + get(K): V
  + put(K, V)

Cache <|.. LRUCache
Cache <|.. LFUCache
         (or one Cache + EvictionPolicy Strategy)

Node (key, value, prev, next [, freq])
DoublyLinkedList (head, tail sentinels)
  + addFront(n) / remove(n) / removeLast(): Node

LRUCache
  - capacity
  - map: Map<K, Node>
  - list: DoublyLinkedList   // head=MRU, tail=LRU

LFUCache
  - capacity, minFreq
  - keyToNode: Map<K, Node>
  - freqToList: Map<int, DoublyLinkedList>

EvictionPolicy <<interface>> → LRUPolicy | LFUPolicy   (optional Strategy)
CacheFactory.create(type, capacity)                   (optional Factory)
DataStore <<interface>> ← CachingProxy / Decorator    (optional)
RemovalListener / CacheStats ── Observer              (optional)
```
Canonical LRU diagram: [lrucache-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/lrucache-class-diagram.png). Combined LRU+LFU sketch: [ikshitij LRU/LFU](https://ikshitij.com/learn/lld-object-oriented/lru-lfu-cache/).

### 5. High-level architecture / component breakdown
```
Client
  │
  ▼
Cache (Facade / API)  ──uses──►  EvictionPolicy (Strategy)
  │                                │
  ├── Map<K, Node>                 ├── LRU: one DLL by recency
  └── DoublyLinkedList(s)          └── LFU: freq → DLL + minFreq

Optional: CachingProxy → DataStore (DB/API)
Optional: RemovalListener, Stats, TTL sweeper
```
- **Cache:** public API only; coordinates map + list(s); no policy `if/else` soup if Strategy is expected.
- **Node + DLL helpers:** all pointer arithmetic in one place (`remove` / `addFront`) — get/put stay short.
- **Concurrency layer:** one lock around map+list mutations, or per-segment caches.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Hand-rolled DLL vs `LinkedHashMap`:** LinkedHashMap is faster to ship for Java-only LRU; hand-rolled shows you understand O(1) splicing and ports to LFU / other languages — prefer hand-rolled in LLD.
2. **Separate `LRUCache`/`LFUCache` classes vs Strategy:** two classes is clearer for LeetCode; Strategy/`EvictionPolicy` wins when the prompt says “support both / switch policies.”
3. **Global lock vs striped locks:** `synchronized get/put` is the safe interview default; mention striping or Caffeine-style async maintenance when asked about throughput.
4. **Exact LFU vs approximate (Redis/Caffeine):** whiteboard = exact O(1) structures; production often samples or uses TinyLFU sketches for memory/CPU — name the tradeoff, don’t implement sketches unless asked.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = **lock held across map + list reorder** → keep critical section tiny; don’t hold lock while calling a slow loader (singleflight / load outside lock, then `put`).
- LFU `minFreq` bugs and empty-bucket cleanup are the usual correctness bottlenecks — test: insert, access to raise freq, fill capacity, verify correct victim.
- TTL + capacity: expire-on-read alone leaks memory for unread keys → add periodic sweep or timer wheel (Caffeine).
- Product stretch (only if asked): write-through/write-back, distributed cache (Redis `allkeys-lru` / `allkeys-lfu`), W-TinyLFU — keep as talking points.

**Timed drill:** implement LRU (sentinels + map) in 25–35 min; then either add `synchronized` + a unit trace, or extend to LFU freq buckets in another 20 min.

## Common follow-ups / gotchas
- “Does `get` update recency/frequency?” — **yes** for both LRU and LFU; forgetting this is the #1 eviction bug.
- “LFU tie when frequencies equal?” — evict **least recently used** within that frequency bucket (list tail).
- “Capacity 0 / capacity 1?” — capacity 0 → every put is no-op or immediate evict; capacity 1 → thrash correctly on alternating keys.
- “Update existing key when full?” — update value + bump recency/freq; **do not** evict (size unchanged).
- “Make it thread-safe?” — start with one lock on get/put; discuss races on read-then-evict-then-insert; escalate to striping if probed.
- “Add TTL?” — lazy check on get + background cleanup; expired entry is a miss even if still in the list (remove from both structures).
- “Why not a heap for LFU?” — `O(log n)` on access; interviewers want `O(1)` via freq → DLL.
- Gotcha: DLL node without storing `key` → cannot delete map entry on eviction in O(1).
- Gotcha: after LFU promote, forgetting to delete empty freq list / update `minFreq` → wrong victim forever.

## Where it appears
- **Campus / new-grad coding:** extremely common as **LeetCode 146** (Medium) on phone screens; LFU (**460**, Hard) for stronger loops.
- **LLD / machine-coding (India product cos + FAANG OOD):** “design a cache” with class diagram, Strategy for LRU/LFU, and concurrency notes — often 45–90 min with a working demo.
- **Experienced / SDE-2+:** same core plus TTL, striped locks, stats, loading-cache / thundering-herd, and bridge to Redis/Caffeine / TinyLFU.
- **Frequency:** among the **most asked** design-the-data-structure problems — treat LRU as mandatory and LFU as the differentiator follow-up.
