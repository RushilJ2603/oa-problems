# h11_storage — Object/blob storage & file systems (S3-style, chunking, replication, durability)

**Interview relevance:** High — almost every media/file HLD (Instagram, YouTube, Dropbox, Pastebin, chat attachments) expects S3/blob + metadata DB + CDN/presigned uploads; Amazon and infra-heavy loops also probe "design S3" durability/chunking.
**Type:** HLD-foundation
**Prereqs:** h01_networking, h03_caching (CDN), h04_databases_indexing; pair with h06_consistency_cap for read-after-write vs eventual listing

## Read / watch (curated, in order)
- [ ] [Storage systems overview](https://blog.bytebytego.com/p/storage-systems-overview) — `ByteByteGo` — block vs file vs object in one mental model: when each wins (DB/VM volumes vs NFS/SMB vs S3-style blobs)
- [ ] [system-design-primer — Latency numbers](https://github.com/donnemartin/system-design-primer#latency-numbers-every-programmer-should-know) — `primer` — memory vs SSD vs disk vs network; why blobs leave the DB and why CDN matters
- [ ] [Pastebin design (Object Store)](https://github.com/donnemartin/system-design-primer/blob/master/solutions/system_design/pastebin/README.md) — `primer` — metadata in SQL + body in managed object store; classic interview split
- [ ] [Handling Large Blobs](https://www.hellointerview.com/learn/system-design/patterns/large-blobs) — `Hello Interview` — why not DB BLOBs; **presigned URLs**, multipart/resumable upload, CDN download — the pattern you drop into every media design
- [ ] [Design Dropbox](https://www.hellointerview.com/learn/system-design/problem-breakdowns/dropbox) — `Hello Interview` — file sync design that forces chunking, metadata service, blob store, and direct client↔S3 path
- [ ] [S3-like storage system](https://blog.bytebytego.com/p/design-a-s3-like-storage-system) — `ByteByteGo` — bucket/object API, IAM gate, **metadata store vs data store** upload walkthrough
- [ ] [How Amazon S3 Stores 350 Trillion Objects with 11 Nines of Durability](https://blog.bytebytego.com/p/how-amazon-s3-stores-350-trillion) — `ByteByteGo` — microservices split, indexing, erasure coding / multi-AZ placement, prefix partitioning
- [ ] [The Internal Architecture of Amazon S3](https://www.youtube.com/watch?v=M2jYafYJovo) — `Gaurav Sen` — short: multipart upload, checksums, shuffle sharding, ECC (~1.8×) vs naive 3× replication, 11 nines
- [ ] [Amazon S3 — What is Amazon S3?](https://docs.aws.amazon.com/AmazonS3/latest/userguide/Welcome.html) — `AWS docs` — bucket / key / object / region vocabulary; pair with [Using objects](https://docs.aws.amazon.com/AmazonS3/latest/userguide/UsingObjects.html)
- [ ] [Data protection / durability](https://docs.aws.amazon.com/AmazonS3/latest/userguide/DataDurability.html) — `AWS docs` — designed **11 nines** durability, multi-AZ redundancy, checksum scrubbing; skim [storage classes](https://aws.amazon.com/s3/storage-classes/) (Standard → IA → Glacier tiers)
- [ ] [Multipart upload overview](https://docs.aws.amazon.com/AmazonS3/latest/userguide/mpuoverview.html) — `AWS docs` — split large objects into parts, parallel + retry-per-part; best practice ≥100 MB
- [ ] [Amazon S3 strong consistency](https://aws.amazon.com/s3/consistency/) — `AWS docs` — strong read-after-write for PUT/overwrite/DELETE; background: [2020 strong consistency announcement](https://aws.amazon.com/blogs/aws/amazon-s3-update-strong-read-after-write-consistency/)
- [ ] [Share an object with a presigned URL](https://docs.aws.amazon.com/AmazonS3/latest/userguide/ShareObjectPreSignedURL.html) / [Upload with a presigned URL](https://docs.aws.amazon.com/AmazonS3/latest/userguide/PresignedUrlUploadObject.html) — `AWS docs` — time-limited signed access without proxying bytes through app servers
- [ ] [Building and operating a pretty big storage system called S3](https://www.allthingsdistributed.com/2023/07/building-and-operating-a-pretty-big-storage-system.html) — `AWS (Andy Warfield / All Things Distributed)` — real S3 org/architecture lens: front-end, namespace, disk fleet, background repair — interview-grade depth without implementing Raft
- [ ] [Inside the Magic Pocket](https://dropbox.tech/infrastructure/inside-the-magic-pocket) — `Dropbox Eng` — exabyte blob store: chunk/block storage, metadata, durability at production scale (pairs with Dropbox interview)
- [ ] [The Google File System (GFS) paper](https://static.googleusercontent.com/media/research.google.com/en//archive/gfs-sosp2003.pdf) — `GFS` — classic chunkserver + master; large chunks, replication, append-heavy design (landing: [research.google.com/archive/gfs.html](https://research.google.com/archive/gfs.html))
- [ ] [Object storage (Wikipedia)](https://en.wikipedia.org/wiki/Object_storage) / [Erasure code](https://en.wikipedia.org/wiki/Erasure_code) — vocabulary cheat sheet; optional: [Distributed file system](https://en.wikipedia.org/wiki/Distributed_file_system)
- [ ] [Blob Storage Design](https://sujeet.pro/articles/blob-storage-design) — deep optional — metadata/data planes, replication vs erasure coding tradeoffs, lifecycle/GC at interview+ depth
- [ ] *Designing Data-Intensive Applications* ch.3 (Storage and Retrieval) + ch.5 (Replication) — `DDIA ch.3 / ch.5` — on-disk structures + why copies buy durability/availability ([book site](https://dataintensive.net/); [ch.3 free notes](https://timilearning.com/posts/ddia/part-one/chapter-3/))
- [ ] [system-design-resources — Storage](https://github.com/InterviewReady/system-design-resources#storage) — `InterviewReady` — link dump for further rabbit holes; GCS/Azure intros: [GCS introduction](https://cloud.google.com/storage/docs/introduction), [Azure Blob intro](https://learn.microsoft.com/en-us/azure/storage/blobs/storage-blobs-introduction)

## Core concepts to master
- **Block vs file vs object:** **Block** = raw volumes (EBS/disk) for DBs/VMs — low latency, mutable. **File** = hierarchical dirs over NFS/SMB — shared POSIX-ish semantics. **Object** = flat bucket+key, HTTP API, immutable whole-object writes — cheap, durable, near-infinite scale for unstructured blobs (images, video, backups, logs).
- **S3 mental model:** `bucket` + `key` → object = bytes + metadata. "Folders" are just key prefixes. App DB stores pointers/URLs/metadata; **never** shove multi-MB blobs into Postgres/MySQL as the primary store.
- **Two planes:** **metadata plane** (hot, sharded KV/DB: key → size, etag, chunk map, ACLs) vs **data plane** (cold(er), many disk nodes holding chunks). Scale and fail independently.
- **Chunking / multipart:** large files split into parts/chunks (fixed size or CDC). Multipart upload = initiate → upload parts (parallel, retry one part) → complete (server assembles). Enables resume, throughput, and bounded retry cost.
- **Durability ≠ availability:** durability = "bytes not lost forever"; availability = "can read *now*." S3 markets **11 nines (99.999999999%)** durability via redundancy across devices/AZs + continuous integrity checks — not the same as 100% uptime.
- **Replication vs erasure coding (ECC):** 3× replication = simple, fast repair, ~3× storage. ECC (e.g. Reed–Solomon / LRC) = reconstruct from data+parity shards with ~1.2–1.8× overhead — cheaper at cold/warm scale, costlier CPU/network on repair. Interview answer: "replication for hot/small; ECC for bulk durability."
- **Placement:** spread chunks across disks → racks → **AZs** (and optionally regions via CRR). Survive disk and AZ loss without user-visible data loss; geo-replication is a separate product decision (latency, cost, compliance).
- **Consistency:** modern S3 = **strong read-after-write** for new/overwrite/delete of objects. Historically LIST could lag; don't assume every object store behaves the same — state your assumption in the interview.
- **Client path:** prefer **presigned URL** (or CDN) so clients upload/download **directly** to blob store — app servers stay control-plane (auth, metadata). Proxying GB through app servers is a common fail.
- **Serving:** pair object store with **CDN** for public/hot media; use versioned keys or cache-busting URLs on replace. Lifecycle policies move cold data to cheaper classes (IA/Glacier) or expire.
- **Integrity:** per-part/object checksums (CRC/MD5/SHA), scrubbing, bit-rot detection; versioning / object lock for accidental delete and ransomware-ish recovery.
- **Hot prefixes / throughput:** partition load by key prefix; avoid one sequential prefix absorbing all writes (or rely on the store's auto-sharding — still design keys with fan-out in mind for DIY systems).

## Practice — how it's asked & how to attack it
Self-test drills (say answers out loud in ≤2 min each):

1. **Where do bytes live?** Design Instagram photo upload. Sketch: client → presigned PUT to S3 → notification/callback → metadata row in DB → CDN URL for reads. Why not store JPEG in MySQL? Why not stream every download through the API tier?
2. **Multipart drill:** 8 GB video over flaky mobile network. Walk initiate / upload parts / complete / abort. What retries? What happens to orphaned parts if the client dies mid-upload?
3. **Durability math talk:** Interviewer: "How do you get 11 nines?" Answer with multi-AZ placement + replication *or* ECC + checksum repair — and distinguish durability from availability SLA.
4. **Replication vs ECC:** Pick storage for (a) hot profile thumbnails, (b) 100 PB cold backups. Justify overhead, repair cost, and latency.
5. **Design S3 (lite):** Requirements → estimate objects/QPS → API (PUT/GET/DELETE/LIST) → metadata service + chunk servers → durability strategy → multipart → one deep dive (hot prefix **or** consistency **or** GC of deleted objects).
6. **Dropbox chunking:** File edit changes 1%. Do you re-upload the whole file? Explain block/chunk hashing, metadata that maps file → chunk IDs, and dedupe across users (high level only).

## Common follow-ups / gotchas
- Putting large blobs in the primary DB — backups, replicas, and queries all melt; fix = object store + thin metadata.
- Proxying uploads through app servers "for security" — use short-lived **presigned** URLs / STS instead; still enforce auth on the *grant*.
- Confusing **durability** (won't lose data) with **availability** (always reachable) or with **consistency** (read sees latest write).
- Drawing folders as real directories in S3 — they're prefixes; LIST and permissions behave differently than a POSIX FS.
- Ignoring multipart for multi-GB objects — single PUT timeouts and full restarts under network loss.
- Forgetting CDN (or Range requests) on read path for public media — origin S3 alone is wrong geo latency story.
- Assuming every cloud blob store is eventually consistent forever — S3 is strongly consistent now; say what *your* design guarantees.
- Naive 3× replication of everything at EB scale — interviewer expects ECC / tiering cost awareness.

## Where it appears
- **Campus / intern / new-grad HLD:** expected box in URL shortener (paste body), news feed, Instagram/YouTube, chat, e-commerce images — "S3 + CDN + metadata DB" is table stakes; depth on presigned upload and multipart differentiates.
- **Experienced / mid-level (1–4 YOE):** design Dropbox / YouTube / "design S3"; probes on chunking, ECC vs replication, hot prefixes, consistency, lifecycle — common at Amazon, Meta, Google, Uber, Flipkart, and storage-heavy cos (Cohesity, Databricks, etc.).
- **Frequency:** near-universal building block whenever media or files appear; full "build an object store" is less common than "use S3 correctly," but Amazon and infra loops love the deeper version.
