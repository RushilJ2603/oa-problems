# hq13_unique_id — Design a Distributed Unique ID Generator (Snowflake)

**Interview relevance:** High — Alex Xu Vol.1 Ch.7 staple; shows up standalone and as a building block inside URL shortener, chat, news feed, booking; FAANG + Indian product cos probe Snowflake vs UUID vs ticket server.
**Type:** HLD-question
**Prereqs:** h01_networking, h04_databases_indexing, h05_db_scaling, h06_consistency_cap, h07_consensus, h10_api_design, h14_estimation; pairs with hq01_url_shortener, hq03_chat_whatsapp, hq04_news_feed

## Read / watch (curated, in order)
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — 45-min skeleton (FRs → NFRs → entities → API → HLD → deep dives) reused on every design Q
- [ ] [Design a Unique ID Generator In Distributed Systems (ByteByteGo / Alex Xu Vol.1 Ch.7)](https://bytebytego.com/courses/system-design-interview/design-a-unique-id-generator-in-distributed-systems) — `ByteByteGo` — canonical interview chapter: multi-master, UUID, ticket server, Snowflake bit layout (course may be gated); free notes mirror: [SDI Vol.1 Ch.7 notes (Noah Tigner)](https://noahtigner.com/articles/system-design-interview-volume-1-chapter-7/)
- [ ] [Explaining 5 Unique ID Generators](https://bytebytego.com/guides/explaining-5-unique-id-generators-in-distributed-systems/) — `ByteByteGo` — UUID / Snowflake / DB auto-incr / DB segment / Redis at a glance; also in [EP82](https://blog.bytebytego.com/p/ep82-open-sourcing-over-100-byte)
- [ ] [Unique ID Generator (requirements diagram)](https://bytebytego.com/guides/unique-id-generator/) — `ByteByteGo` — interview constraints: 64-bit, numerical, time-sortable, high QPS
- [ ] [Snowflake ID Generation by Twitter](https://www.youtube.com/watch?v=2O1wur4m8DE) — `Gaurav Sen` — 60s visual of timestamp + machine + sequence; playlist: [System Design (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX)
- [ ] [twitter-archive/snowflake (snowflake-2010)](https://github.com/twitter-archive/snowflake/tree/snowflake-2010) — `Twitter / X` — original open-source layout + NTP / clock-backwards notes; repo: [twitter-archive/snowflake](https://github.com/twitter-archive/snowflake)
- [ ] [Announcing Snowflake (Twitter Engineering, 2010 — Wayback)](https://web.archive.org/web/20210508000000/https://blog.twitter.com/engineering/en_us/a/2010/announcing-snowflake.html) — `Twitter blog` — why uncoordinated 64-bit k-sortable IDs; live blog often 403 — archive is the working copy
- [ ] [Snowflake ID](https://en.wikipedia.org/wiki/Snowflake_ID) — `Wikipedia` — bit layout cheat sheet + Discord / Instagram / Mastodon variants
- [ ] [Ticket Servers: Distributed Unique Primary Keys on the Cheap](https://code.flickr.net/2010/02/08/ticket-servers-distributed-unique-primary-keys-on-the-cheap/) — `Flickr` — central `REPLACE INTO` ticket DB + odd/even HA; the interview alternative Snowflake beats on SPOF
- [ ] [Sharding & IDs at Instagram](https://medium.com/instagram-engineering/sharding-ids-at-instagram-1cf5a71e5a5c) — `Instagram Engineering` — in-Postgres Snowflake variant (41 + 13 shard + 10 seq) without a separate ID service
- [ ] [Discord API Reference — Snowflakes](https://docs.discord.com/developers/reference) — `Discord` — production Snowflake (42-bit ts / 5 worker / 5 process / 12 incr) + string serialization for JSON
- [ ] [Design a Unique Identifier System for Customers](https://www.hellointerview.com/community/questions/customer-id-system/cm8ezj1h1024fkosmqoo87oqv) — `Hello Interview` — Netflix/Microsoft-flavored prompt (multi-DC signup IDs ≈ Snowflake)
- [ ] [DynamoDB Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/dynamodb) — `Hello Interview` — why sortable IDs (Snowflake / UUID v7 / ULID) beat raw timestamps as sort keys
- [ ] [RFC 9562 — UUID Version 7](https://www.rfc-editor.org/rfc/rfc9562.html) — `IETF` — time-ordered 128-bit alternative when 64-bit is not required; overview: [UUID (Wikipedia)](https://en.wikipedia.org/wiki/Universally_unique_identifier)

## Core concepts to master
- **Requirements triad (Alex Xu default):** globally **unique**, **64-bit numeric**, **roughly time-sortable**, ≥ **10k IDs/s**, low latency, high availability — then defend why UUID v4 fails (128-bit, not ordered) and ticket server fails (SPOF / bottleneck).
- **Snowflake bit layout (classic):** `1` unused/sign + `41` ms timestamp (custom epoch → ~69 years) + `10` machine (often `5` DC + `5` worker) + `12` sequence → **4096 IDs/ms/worker** ≈ **4M IDs/s/worker**, no per-ID network hop.
- **Uniqueness without coordination:** once each worker has a unique machine ID, generation is local (clock + counter + bit-pack). Coordination is **only at startup** (ZooKeeper/etcd/config/IP/ordinal), not on every ID.
- **k-ordering:** IDs are roughly time-ordered (Twitter aimed ~1s); same-ms IDs sort by machine then sequence — good enough for feeds / cursors, not a global Lamport clock.
- **Clock skew is the hard problem:** NTP can step clocks **backward** → duplicate risk. Production pattern: refuse / wait until `now > lastTimestamp`; prefer NTP that slews forward-only; optionally track last ID time.
- **Sequence overflow:** if sequence hits `4095` in the same ms → spin/`tilNextMillis` until the next millisecond.
- **Alternatives map:** multi-master auto-incr (odd/even / incr-by-N) — simple but not time-sortable across nodes, painful on add/remove; **Flickr ticket server** — sequential, SPOF unless odd/even pair; **DB segment / range allocator** — batch ranges to apps (good mid answer); **Redis INCR** — fast but centralized; **UUID v4** — no coord, bad indexes; **UUID v7 / ULID** — sortable 128-bit, no machine-ID ops.
- **Instagram variant:** generate inside Postgres shard (`41` ts + `13` shard + `10` seq) — same idea, fewer moving parts than a Thrift Snowflake fleet.
- **Why 64-bit matters:** fits `BIGINT` / JS `Number` carefully (Discord returns **strings**), half of UUID storage, B-tree-friendly when time-leading bits keep inserts roughly append-only.
- **Tuning bits is an interview move:** shrink DC bits, grow worker or sequence if topology is known (e.g. 8 DCs × 512 workers × 1024/ms).

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈40–45 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR:** `nextId()` → globally unique ID; optional batch `nextIds(n)`; optional decode (extract timestamp / worker).
- **Clarify:** must be 64-bit? numeric only? strictly monotonic globally or roughly time-ordered? multi-region? must hide business volume (no pure sequential)?
- **NFR:** uniqueness (hard), availability ≈ dependent services, p99 ≪ 1–2 ms local / few ms if networked, ≥ 10k–100k+/s, no single writer SPOF.
- **Out of scope unless asked:** cryptographic unguessability, secondary indexes, mapping ID → object store.

### 2. Back-of-envelope estimation
State assumptions out loud (swap for interviewer numbers):
- Target **10k IDs/s** cluster-wide (Alex Xu baseline) → one Snowflake worker is overkill (4M/s theoretical).
- Social / chat peak: **100k–1M IDs/s** → still fine with tens of workers.
- Capacity check: `41`-bit ms → `2^41 / (1000×86400×365) ≈ 69` years from custom epoch.
- Per-worker ceiling: `2^12 × 1000 = 4,096,000` IDs/s; cluster ceiling ≈ workers × that.
- Implication: **CPU/clock**, not DB, is the bottleneck if generation is local; network only if you expose a remote ID service.

### 3. API / interface
- Library (preferred at scale): `long nextId()` / `List<Long> nextIds(int n)` in-process or sidecar.
- Optional RPC: `POST /v1/ids` `{ "count": 1 }` → `{ "ids": [1935847…] }`; batch to amortize RTT.
- Optional: `GET /v1/ids/{id}/meta` → `{ "timestamp_ms", "datacenter_id", "worker_id", "sequence" }` (debug / pagination helpers).
- Auth / rate-limit the network service; library calls stay internal.

### 4. Data model / class diagram
Not a heavy DB design — state is tiny and mostly local:

```
IdWorker
  - workerId: 0..31
  - datacenterId: 0..31
  - sequence: 0..4095
  - lastTimestamp: long
  + nextId(): long
  + tilNextMillis(last): long
  + timeGen(): long   // System.currentTimeMillis() or monotonic wrapper

MachineIdAssigner
  - assign() via ZooKeeper/etcd ephemeral / static config / StatefulSet ordinal / IP bits
```

Bit pack (classic Twitter split of 10 machine bits):
```
id = ((now - epoch) << 22)
   | (datacenterId << 17)
   | (workerId << 12)
   | sequence
```
Persist only **assignment leases** (ZK/etcd paths) if using dynamic worker IDs — not every generated ID.

### 5. High-level architecture
```
App servers ──(local)──► Snowflake library / sidecar
                              │
                              ├─ clock (NTP-synced)
                              ├─ sequence (in-memory, mutex/atomic)
                              └─ workerId (assigned once)

Startup path (optional):
  Worker → ZooKeeper/etcd → unique workerId lease → ready

Compare paths you discard out loud:
  Client → Ticket Server (MySQL/Redis INCR) → SPOF / latency
  Client → UUID v4 local → fails 64-bit + sort requirements
```
- Prefer **embed library** or **localhost sidecar** over a multi-hop ID microservice unless polyglot clients force it.
- Multi-DC: encode `datacenterId`; keep NTP healthy per region.

### 6. Deep dives & the 2–3 key tradeoffs interviewers probe
1. **Snowflake vs ticket server vs UUID:** Snowflake wins when you need 64-bit + time order + no per-ID coord; ticket server wins for strict global sequence / simplicity at low QPS; UUID v7/ULID when 128-bit is OK and you want zero machine-ID ops.
2. **Clock skew:** how do you detect backward time? wait vs throw vs use a logical clock offset? What if skew > sequence window across workers? (IDs can interleave across machines within the same ms — usually acceptable.)
3. **Worker ID lifecycle:** static config (simple, ops burden) vs ZK ephemeral (auto reclaim, need care on long GC / network blips so two live nodes never share an ID) vs Instagram-style shard ID baked into DB.
4. **Bit-budget tuning:** trade timestamp years vs #workers vs per-ms burst; show you can reallocate 10+12 bits to the topology.

### 7. Bottlenecks / how you scale it
- **Horizontal:** add workers with new IDs — generation QPS scales linearly until you exhaust the 10-bit (or tuned) machine space.
- **Hot worker:** one process >4k IDs/ms → wait for next ms or split into more processes (Discord-style process bits) / widen sequence bits.
- **Remote ID service:** batch IDs, client-side cache of prefetched ranges, avoid sync RPC per insert.
- **Failure:** worker death is fine (IDs not reused for that timestamp); **do not** reassign a workerId while its clock window could still collide — wait out lease / max clock skew.
- **Multi-region:** independent generators; accept cross-region k-ordering only within NTP + network skew bounds.
- **DB impact:** time-leading IDs ≈ sequential inserts → good B-tree locality vs random UUID v4 page splits.

## Common follow-ups / gotchas
- "Clock moved backwards — what do you do?" → refuse or sleep until catch-up; never emit a duplicate `(timestamp, worker, seq)` tuple; cite NTP slew vs step.
- "Are IDs strictly monotonic across the whole fleet?" → No — only roughly; same-ms ordering is by worker/seq. Say **k-sorted**.
- "Why not UUID?" → size (128), random v4 hurts indexes; if allowed, prefer **UUID v7** (RFC 9562) over v4.
- "How does Discord/Instagram differ?" → Discord: JSON **strings**, custom epoch 2015, process bits; Instagram: **in-DB** shard bits, no separate Snowflake service.
- "WorkerId collision after restart?" → ephemeral ZK without fencing, or recycling IDs too fast after crash = duplicates; hold leases past max skew.
- "Can users guess volume from IDs?" → timestamp leaks rough create time; sequence within ms is not a global counter — better than auto-incr for hiding totals, not privacy-preserving.
- "JS / JSON number precision?" → IDs > `2^53-1` need **string** transport (Discord pattern).

## Where it appears
- **Campus / new-grad HLD:** common as a **short deep-dive** inside URL shortener / feed / chat, or a full 45-min when they want distributed-systems fundamentals without a huge product surface.
- **Experienced (1–4 YOE):** standalone "design Snowflake" or "ID service for multi-DC"; probes clock skew, ZK assignment, bit tuning, UUID v7 tradeoff.
- **Companies:** Twitter/X origin story; asked widely at Meta, Amazon, Microsoft, Uber, Atlassian, Flipkart, etc., whenever primary keys or message ordering come up.
- **Frequency:** **high** as a building-block question — mandatory alongside URL shortener; know the 64-bit diagram cold.
