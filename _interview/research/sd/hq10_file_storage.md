# hq10 — Design File Storage & Sync (Google Drive / Dropbox)

**Interview relevance:** High — canonical 45-min HLD at FAANG + Indian product cos (Google, Meta, Amazon, Microsoft/OneDrive, Dropbox, Uber, Flipkart); tests metadata vs blob split, chunking/delta sync, conflict copies, and notification fan-out.
**Type:** HLD-question
**Prereqs:** h11_storage, h01_networking, h02_load_balancing, h03_caching, h04_databases_indexing, h05_db_scaling, h08_message_queues, h14_estimation; helpful: h06_consistency_cap

## Read / watch (curated, in order)
- [ ] [Design a File Storage Service Like Dropbox](https://www.hellointerview.com/learn/system-design/problem-breakdowns/dropbox) — `Hello Interview` — best free junior-friendly walkthrough (upload → presigned blob → share → sync cursor); pair with the video [Design Dropbox or Google Drive (Ex-Meta Staff)](https://www.youtube.com/watch?v=_UZ1ngy-kOI)
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — the 45-min skeleton (FRs → NFRs → entities → API → HLD → deep dives) you reuse on every design question
- [ ] [Handling Large Blobs](https://www.hellointerview.com/learn/system-design/patterns/large-blobs) — `Hello Interview` — why not DB BLOBs; **presigned URLs**, multipart/resumable upload, CDN download — required vocabulary before drawing Dropbox boxes
- [ ] [Design Google Drive (ByteByteGo / Alex Xu Vol.1 Ch.15)](https://bytebytego.com/courses/system-design-interview/design-google-drive) — `ByteByteGo` — canonical book/course chapter: block servers, delta sync, metadata DB, notifications; free notes mirror: [SDI Vol.1 Ch.15 notes (Noah Tigner)](https://noahtigner.com/articles/system-design-interview-volume-1-chapter-15/)
- [ ] [S3-like storage system](https://blog.bytebytego.com/p/design-a-s3-like-storage-system) — `ByteByteGo` — metadata store vs data store upload flow (the blob plane under Drive/Dropbox)
- [ ] [The Internal Architecture of Amazon S3](https://www.youtube.com/watch?v=M2jYafYJovo) — `Gaurav Sen` — multipart, checksums, erasure coding vs 3× replication, 11 nines — what you mean when you say "S3/Magic Pocket"
- [ ] [System Design playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — scale / load-balance / cache foundations you name inside this design; channel: [Gaurav Sen](https://www.youtube.com/@gkcs)
- [ ] [Dropbox system design | Google drive system design](https://www.youtube.com/watch?v=U0xTu6E2CT8) — `Tech Dummies` — Indian-interview staple full walkthrough: watcher/chunker/indexer client, metadata vs block servers (~45 min)
- [ ] [Design Dropbox (GeeksforGeeks)](https://www.geeksforgeeks.org/system-design/design-dropbox-a-system-design-interview-question/) — `GfG` — compact written recap of client components + metadata/block split
- [ ] [Dropbox System Design (Grokking / Educative)](https://www.educative.io/courses/grokking-the-system-design-interview/dropbox-system-design) — `Grokking / Educative` — estimation framing + chunk/hash upload + sync/conflict chapter
- [ ] [Inside the Magic Pocket](https://dropbox.tech/infrastructure/inside-the-magic-pocket) — `Dropbox Eng` — production immutable blob store (≤4 MB blocks); pair with [Broccoli: Syncing faster by syncing less](https://dropbox.tech/infrastructure/-broccoli--syncing-faster-by-syncing-less) (metadata sync vs block sync, PutBlock/GetBlock by hash)
- [ ] [Rewriting the heart of our sync engine](https://dropbox.tech/infrastructure/rewriting-the-heart-of-our-sync-engine) — `Dropbox Eng` — Nucleus client sync rewrite (optional depth after the interview skeleton)
- [ ] [How We've Scaled Dropbox](https://www.youtube.com/watch?v=PE4gwstWhmc) — `Dropbox` (via `primer` list) — real scale talk; primer landing: [donnemartin/system-design-primer](https://github.com/donnemartin/system-design-primer)
- [ ] [Upload with a presigned URL](https://docs.aws.amazon.com/AmazonS3/latest/userguide/PresignedUrlUploadObject.html) / [Multipart upload overview](https://docs.aws.amazon.com/AmazonS3/latest/userguide/mpuoverview.html) — `AWS docs` — direct client→blob path + resumable multi-GB uploads
- [ ] [Rabin fingerprint](https://en.wikipedia.org/wiki/Rabin_fingerprint) — `Wikipedia` — rolling hash behind **content-defined chunking** (shift-resistant blocks; LBFS note on the page); pair with [Rsync Algorithm (GfG)](https://www.geeksforgeeks.org/system-design/rsync-algorithm-system-design/) for delta-transfer intuition
- [ ] [Design Dropbox File Sync (Sujeet Jaiswal)](https://sujeet.pro/articles/design-dropbox-file-sync) — optional deep dive — CAS blocks, 4 MiB reality vs CDC interview answer, Magic Pocket economics
- [ ] [InterviewReady system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` / Gaurav Sen link dump — further reading after the core path; book site: [dataintensive.net](https://dataintensive.net/) (`DDIA` — replication / durability framing)

## Core concepts to master
- **Two planes:** **metadata** (file tree, versions, ACLs, ordered block-hash manifests — hot, strongly consistent per user/namespace) vs **blocks/blobs** (immutable content-addressed chunks in S3/GCS/Magic Pocket). Never push GB through API servers on the hot path.
- **Presigned / direct upload:** API issues short-lived URLs (or session tokens); client PUTs chunks straight to object storage; metadata commit happens **after** blocks are durable. Same pattern as video upload.
- **Chunking (~4 MB interview default):** enables (1) **delta sync** (upload only changed chunks), (2) **resumable** transfers, (3) **parallel** upload/download, (4) **dedup** via content hash (SHA-256).
- **Fixed-size vs content-defined chunking (CDC):** fixed is simple; insert-1-byte at start **shifts all** fixed boundaries. CDC (Rabin rolling hash breakpoints) keeps most boundaries stable — better delta/dedup after edits. Real Dropbox often cites fixed ≤4 MB blocks; say CDC as the “better delta” upgrade if probed.
- **Content-addressable storage (CAS):** chunk key = hash(content). Identical chunks across files/users stored once (global dedup) — privacy/cross-tenant policy may force **per-user** dedup instead; call the tradeoff.
- **Sync protocol:** client keeps a **cursor** / `since` revision; long-poll / WebSocket / push notifies “something changed” → client pulls metadata delta → downloads missing chunks. Polling alone is too expensive at scale.
- **Conflict resolution (binary files):** offline concurrent edits → **conflict copy** (`file (conflicted copy — Device — Date)`) rather than silent last-writer-wins. Real-time collab (Docs) is **out of scope** — OT/CRDT, not file sync.
- **Version history:** each commit = new version pointing at a new ordered hash list; old blocks GC’d when no version references them (refcounts). Cap retention (e.g. 30/180 days) for cost.
- **Sharing / ACLs:** share link or collaborator list on file/folder namespace; permission check on metadata path before issuing download URLs. Folder share = shared namespace mounted into multiple users’ trees (shard carefully).
- **Availability vs consistency:** brief sync lag across devices is OK (AP-friendly notify); **metadata commit** for a single user’s file tree needs careful consistency so you don’t lose versions / double-apply cursors.
- **Client local engine:** watcher (FS events) → chunker → indexer/local DB of hashes → sync with cloud. Server is not the only “system.”

## Practice — how it's asked & how to attack it
Prompt variants: “Design Dropbox”, “Design Google Drive”, “Design a file storage & sync service”. Scope early: **file sync in**; Google Docs collab, full search, virus scan, custom object-store internals **out** unless asked.

Interview walk-through skeleton (≈40–45 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (core):** upload / download files; sync across a user’s devices near-real-time; list folder tree.
- **FR (ask / optional):** share file/folder with ACLs; version history / restore; resumable large files (≤50 GB typical interview cap).
- **Out / below line:** real-time co-editing, full-text search, malware scanning, per-user quota UI.
- **NFR:** high durability (don’t lose bytes); upload/download low latency; support multi-GB files; availability over strict cross-device immediate consistency; secure (authz before every URL grant).
- **Clarify:** #users, avg storage/user, peak file size, sync SLA (seconds?), sharing in-scope?, regions?

### 2. Back-of-envelope estimation
State assumptions out loud (replace with interviewer's numbers):
- **100M users**, **10 GB** avg stored → **1 EB** logical; after ~30% dedup still **~700 PB** physical — storage **cost** dominates.
- Active sync: **10M** DAU × **10** file events/day → **~1k metadata writes/s** avg; peaks 5–10×. Block traffic >> metadata QPS.
- Block size **4 MB** → a **1 GB** file ≈ **256** chunks; 1% edit ≈ few chunks re-uploaded (delta).
- Implication: **metadata DB** is QPS/consistency-sensitive; **blob store** is capacity/bandwidth/durability-sensitive — scale them independently.

### 3. API / interface
Control plane (REST; auth via token header — never trust `userId` in body):
- `POST /files/upload-session` body: `{ "name", "parent_id", "size", "chunk_hashes[]" }` → `{ "file_id", "upload": [{ "hash", "presigned_url" }, ...] }` — only **missing** hashes get URLs
- `POST /files/{fileId}/complete` → commit new version once all chunks ACK’d in blob store
- `GET /files/{fileId}` → metadata + download URLs for needed chunks (or CDN)
- `GET /files?parent_id=` → list children
- `POST /files/{fileId}/share` body: `{ "user_ids[]", "role" }` or `{ "link", "role" }`
- `GET /sync/changes?cursor=` → `{ "events[]", "next_cursor" }` (long-poll / WS notify wake)
- Optional: `GET /files/{fileId}/versions`, `POST /files/{fileId}/restore`

### 4. Data model
```
users(user_id PK, ...)
files(
  file_id PK,
  parent_id,          -- folder tree (NULL = root)
  owner_id,
  name,
  is_folder BOOL,
  current_version_id,
  created_at, updated_at
)
file_versions(
  version_id PK,
  file_id,
  size,
  created_by_device,
  created_at,
  parent_version_id   -- for conflict detection
)
version_blocks(
  version_id,
  block_seq,          -- order in file
  block_hash,         -- SHA-256
  PRIMARY KEY (version_id, block_seq)
)
blocks(               -- optional global index
  block_hash PK,
  size,
  ref_count,
  storage_key         -- object-store location
)
shares(file_or_folder_id, grantee_user_id, role)
devices(device_id, user_id, sync_cursor)
```
- Shard metadata by `owner_id` / namespace_id; shared folders need a dedicated namespace strategy (denormalize, shared shard, or globally consistent store).
- Blob objects keyed by `block_hash` (immutable).

### 5. High-level architecture
```
Desktop/Mobile Client
  Watcher → Chunker (hash) → local index
        │
        ▼
   API Gateway / LB
        ├─ Metadata Service  → SQL/NoSQL (file tree, versions, ACLs, cursors)
        ├─ Block / Upload Service → check missing hashes → presigned URLs
        │         └─ Object Store (S3 / GCS / Magic Pocket)  [CAS chunks]
        ├─ Sync / Notification Service → long-poll / WebSocket / APNs/FCM
        │         └─ Queue / PubSub (change events)
        └─ CDN (optional) for hot public/shared downloads
```
- **Upload flow:** hash chunks locally → ask metadata which hashes are new → PUT only new chunks to blob → `complete` creates `file_versions` + `version_blocks` → publish change → other devices wake and pull.
- **Download/sync flow:** receive notify → `GET /sync/changes` → for each file, diff hash lists → GET missing chunks → reassemble.
- Stateless app tier; sticky not required if sync state lives in DB + pub/sub.

### 6. Deep dives & the 2–3 key tradeoffs interviewers probe
1. **Proxy bytes through API vs presigned direct-to-blob:** proxy is simple/secure-looking but melts servers on 50 GB files. Prefer **presigned** (or equivalent) + auth on the *grant*; mention multipart for resume.
2. **Fixed 4 MB chunks vs CDC (Rabin):** fixed = simpler metadata, worse shift behavior; CDC = better delta after inserts, more variable chunk sizes / CPU. Interview default: start fixed 4 MB, offer CDC when they say “edit middle of 1 GB file.”
3. **Global vs per-tenant dedup:** global saves most storage but cross-user side channels / compliance risk; per-user safer. Mention encryption: client-side encryption breaks server-side dedup.
4. **Conflict copies vs LWW vs OT:** for opaque binaries, **conflict copy** (no silent data loss). LWW only if product accepts loss. OT/CRDT = Docs — explicitly defer.
5. **Strong metadata vs eventual notify:** commit version with compare-and-swap on `parent_version_id` (detect concurrent commits); devices may lag seconds via async notify — defend AP for sync lag, strong-ish for single-file version lineage.

### 7. Bottlenecks / how you scale it
- **Metadata hot path:** shard by user/namespace; cache folder listings; avoid huge folders (paginate); shared-folder fan-out is the hard shard problem.
- **Block upload bandwidth:** parallel chunk PUTs; client-side compression; only missing hashes; CDN / edge for popular shared downloads.
- **Notification fan-out:** one change → many devices (and shared-folder members). Pub/sub per user/device; batch events; mobile uses push (APNs/FCM) instead of always-on WS.
- **Storage cost:** dedup + cold tier (IA/Glacier-like) + version TTL + GC of unreferenced blocks (refcount or mark-and-sweep).
- **Large shared folders:** don’t nest all members’ metadata on one owner shard without a plan — shared namespace ID + ACL table.
- **Failure:** incomplete upload → abort session / TTL orphan multipart parts; blob up, metadata down → no commit (safe); metadata up, notify down → clients catch up via cursor poll.
- **Integrity:** verify hash on upload; checksum scrub in blob store; client re-hash on download if paranoid.

## Common follow-ups / gotchas
- “Is this Google Docs?” → No. File sync ≠ character-level collab. Conflict copies for binaries; OT/CRDT only if they expand scope.
- “Why not store files in MySQL?” → backups/replication/query death; blobs belong in object storage; DB holds pointers + manifests.
- “Upload failed at 99%?” → chunk/multipart resume; only retry missing parts; don’t rewrite successful hashes.
- “Two devices edit offline — who wins?” → neither silently; keep both as conflicted copies (or version fork) and surface to user.
- “How does dedup interact with encryption?” → server-side dedup needs server-visible plaintext (or convergent encryption — advanced); client-side E2EE ≈ little/no cross-user dedup.
- Drawing S3 but skipping **chunk manifest + sync cursor + conflict policy** — interviewers treat those three as the actual Dropbox question.

## Where it appears
- **Campus / intern / new-grad HLD:** common full-round or “large blob” deep dive inside Instagram/YouTube/chat; expect metadata vs S3 + presigned upload even if sync is light.
- **Experienced (1–4 YOE):** full Dropbox/Drive design; depth on CDC vs fixed chunks, shared-folder sharding, dedup/encryption, notification fan-out, GC of versions — frequent at Google, Meta, Amazon, Microsoft, Dropbox, and storage-heavy loops.
- **Frequency:** among the **top-tier** HLD design questions (alongside URL shortener, chat, feed, video) — treat as mandatory after `h11_storage`.
