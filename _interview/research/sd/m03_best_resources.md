# M03 — Best SD resources ranked (courses / books / playlists)

**Interview relevance:** High — meta module for every campus + off-campus HLD/LLD prep path; pick 1–2 primaries, don’t collect 10 courses.
**Type:** resource-meta
**Prereqs:** none (start here before h01 / l01); pairs with this sheet’s HLD + LLD modules

## Read / watch (curated, in order)
Ranked for a strong DSA student prepping placements — **learning sequence**, not “prestige.” Prefer free first; buy only what closes a clear gap.

- [ ] [system-design-primer (donnemartin)](https://github.com/donnemartin/system-design-primer) — `primer` — **best free syllabus / map.** Building blocks (LB, cache, DB, queues), performance numbers, Anki decks, and sample HLD/OOD solutions. Skim the outline once; return per topic — don’t “read the README cover-to-cover” as a substitute for designing.
- [ ] [System Design in a Hurry — Introduction](https://www.hellointerview.com/learn/system-design/in-a-hurry/introduction) — `Hello Interview` — **best free modern interview guide.** Built backwards from what FAANG interviewers score. Then: [How to Prepare](https://www.hellointerview.com/learn/system-design/in-a-hurry/how-to-prepare) + [Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — the 45-min skeleton you reuse on every “design X.”
- [ ] [System Design Playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — **best free video intuition** for scale, microservices, LB, cache, DB tradeoffs (esp. Indian campus / product-cos language). Channel: [Gaurav Sen](https://www.youtube.com/channel/UCRPMAqdtSgd0Ipeef7iFsKw). Companion dump: [InterviewReady/system-design-resources](https://github.com/InterviewReady/system-design-resources). Paid deepen: [InterviewReady](https://interviewready.io/) (System Design Simplified + LLD).
- [ ] [*System Design Interview – An Insider’s Guide* Vol. 1 (Alex Xu)](https://www.amazon.com/System-Design-Interview-insiders-Second/dp/B08CMF2CQF) — `ByteByteGo` — **best interview playbook for canonical HLD.** 4-step framework + ~16 classic designs (rate limiter, URL shortener, news feed, chat, YouTube, Drive…). Digests: [bytebytego.com](https://bytebytego.com/), free visuals on [ByteByteGo YouTube](https://www.youtube.com/@ByteByteGo) / [channel ID](https://www.youtube.com/channel/UCZgt6AzoyjslHTC9dz0UoTw), newsletter [blog.bytebytego.com](https://blog.bytebytego.com/). Book refs: [alex-xu-system/bytebytego](https://github.com/alex-xu-system/bytebytego).
- [ ] [Grokking the System Design Interview (DesignGurus — original)](https://www.designgurus.io/course/grokking-the-system-design-interview) — `Grokking` — **best structured paid course walkthroughs** of the classic problem set (requirements → API → design). Alternate interactive text track (independently maintained): [Educative — Grokking Modern System Design Interview](https://www.educative.io/courses/grokking-the-system-design-interview). Use **one** Grokking path, not both.
- [ ] [*System Design Interview* Vol. 2 (Alex Xu & Sahn Lam)](https://www.amazon.com/System-Design-Interview-Insiders-Guide/dp/1736049119) — `ByteByteGo` — **best next book after Vol. 1** for harder designs (proximity, Maps, message queue, payments, object storage, leaderboard…). Vol.1-vs-2 map: [Volume 1 vs Volume 2](https://blog.bytebytego.com/p/system-design-interview-books-volume). Kindle: [Vol. 2 ebook](https://www.amazon.com/System-Design-Interview-Insiders-Guide-ebook/dp/B0CR977BQH).
- [ ] [*Designing Data-Intensive Applications* (DDIA) — Kleppmann](https://dataintensive.net/) — `DDIA` — **best depth book for tradeoff vocabulary** (replication, partitioning, transactions, streams) — *not* an interview script. Buy: [Amazon](https://www.amazon.com/Designing-Data-Intensive-Applications-Reliable-Maintainable/dp/1449373321) · [buy.html](https://dataintensive.net/buy.html). Prep use: **selective chapters** tied to this sheet (e.g. storage/retrieval, replication, partitioning, consistency) — skip formal consensus proofs.
- [ ] [coding-parrot/system_design](https://github.com/coding-parrot/system_design) + [coding-parrot/Low-Level-Design](https://github.com/coding-parrot/Low-Level-Design) — `Gaurav Sen / InterviewReady` — light link dumps for HLD + LLD; use as bookmarks after the cores above, not as a primary curriculum.

**Suggested stack (placements, ~4–8 weeks):** primer map → Hello Interview framework → Gaurav Sen playlist for intuition → Vol.1 (or Grokking) for 10–15 designs → Vol.2 / DDIA chapters only where interviewers probe depth. Add InterviewReady if you want video+LLD in one paid package.

## Core concepts to master
- **Role of each resource:** primer = glossary/map; Hello Interview = how to run 45 min; Gaurav Sen = spoken intuition; Vol.1 / Grokking = practice designs; Vol.2 = harder designs; DDIA = *why* tradeoffs; InterviewReady = paid HLD+LLD depth.
- **HLD interview bar ≠ research DS:** you must discuss LB, cache, DB choice, sharding, queues, consistency, estimation — not implement Raft/Paxos.
- **One delivery framework:** requirements → estimation → API → data model → high-level diagram → 2–3 deep dives → bottlenecks. Hello Interview + Alex Xu 4-step are the same idea.
- **Canonical problem set (~15–20):** URL shortener, rate limiter, chat, news feed, video, drive, autocomplete, crawler, notification, ride-hailing, booking, etc. — Vol.1 / Grokking / this sheet’s `hq*` modules.
- **LLD is a separate track:** OOP/SOLID + patterns + concurrency + parking lot / Splitwise / elevator — don’t expect Vol.1 to teach machine coding; use this sheet’s `l*` / `lq*` + LLD primers.
- **Buy vs free:** free path (primer + Hello Interview + Gaurav Sen + ByteByteGo YT) is enough for many campus rounds; pay for Vol.1/Grokking/InterviewReady when you need structured solutions or mocks.
- **Anti-pattern:** finishing DDIA or 3 paid courses before ever whiteboard-timing a design. Practice > consumption.
- **Depth on demand:** open DDIA / Vol.2 when a follow-up (quorum, partitioning, exactly-once, geo) keeps failing — not as week-1 reading.

## Practice — how it's asked & how to attack it
Self-test drills:

1. **Pick a 3-resource stack** for a 4-week campus prep and justify *why* (one map, one framework, one practice source). Drop anything redundant.
2. **Map five `hq*` questions** in this sheet to the chapter/lesson in Vol.1 *or* Grokking *or* Hello Interview problem breakdowns — prove you know where to drill each.
3. **Timebox one design (45 min)** using only Hello Interview Delivery Framework — no notes from a solution chapter until after.
4. **DDIA triage:** name 3 chapters you’d skim for “design a chat / news feed / distributed cache” and what interview phrase each unlocks (e.g. leaderless quorum, log-structured storage).
5. **LLD gap check:** if your stack is HLD-only, list which LLD resource you’ll add (this sheet’s `l01`+`lq*`, InterviewReady LLD, or `coding-parrot/Low-Level-Design`) before product-cos machine-coding rounds.
6. **Budget drill:** given ₹0 vs ~book+course budget, rewrite the stack — what stays free, what you buy first and why.

## Common follow-ups / gotchas
- “I watched 40 hours of SD YouTube but freeze in the room” — missing timed delivery framework + solo whiteboard reps.
- Buying **both** DesignGurus Grokking **and** Educative “Grokking Modern…” — overlapping; pick one.
- Reading **all of DDIA** before any design practice — classic stall; interviewers reward applied tradeoffs, not chapter recall.
- Treating Vol.1 diagrams as the only “correct” architecture — interviewers poke alternatives; defend tradeoffs.
- Ignoring LLD until the night before an Atlassian/Flipkart machine-coding round — separate skill from HLD playbooks.
- Chasing every newsletter/video instead of finishing ~15 designs end-to-end with estimation + one deep dive each.

## Where it appears
- **Campus (product cos / some FAANG new-grad):** light HLD or “design TinyURL”-style; free stack (primer + Hello Interview + Gaurav Sen + a few Vol.1 chapters) is usually enough.
- **Off-campus SDE-1/2 / experienced hire:** full HLD round; Vol.1 or Grokking practice set + Hello Interview framework expected; Vol.2 / DDIA chapters for senior-ish probing.
- **Indian product cos (Atlassian, Uber, Flipkart, etc.):** often HLD *and* LLD/machine coding — don’t stop at Alex Xu alone.
- **Frequency:** this meta choice is made once at the start of prep; revisit only when a mock exposes a gap (framework vs content vs LLD).
