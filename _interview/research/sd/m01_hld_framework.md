# M01 — HLD interview framework & rubric

**Interview relevance:** High — the pacing/structure and scoring lens for every 45-min “design X” HLD round (campus + experienced); FAANG and Indian product cos (Atlassian, Uber, Flipkart, etc.) grade how you run requirements → architecture → deep dives → tradeoffs, not a memorized diagram alone.
**Type:** resource-meta
**Prereqs:** None — learn this first; reuse on every HLD-question module. Pair with estimation (H14) when math changes the design; foundations (H01–H16) feed deep dives.

## Read / watch (curated, in order)
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — canonical 45-min pacing: Requirements (~5) → Core Entities (~2) → API (~5) → optional Data Flow → High-Level Design (~10–15) → Deep Dives (~10); just-in-time capacity math
- [ ] [System Design in a Hurry — Introduction](https://www.hellointerview.com/learn/system-design/in-a-hurry/introduction) — `Hello Interview` — why structure beats trivia; what to skim when time-starved (delivery + core concepts)
- [ ] [System Design Requirements Gathering](https://www.hellointerview.com/blog/system-design-requirements) — `Hello Interview` — #1 mid-level failure mode: skip/overdo/undistill FRs+NFRs; 5–7 min box; mark out-of-scope
- [ ] [Mastering Estimation](https://www.hellointerview.com/blog/mastering-estimation) — `Hello Interview` — estimate the *crux* only; what interviewers grade vs ritual QPS theater
- [ ] [System Design Interview: A Step-By-Step Guide](https://www.youtube.com/watch?v=i7twT3x5yv8) — `ByteByteGo` — Alex Xu 4-step: scope → HLD + buy-in → deep dive → wrap-up (~5 / ~20 / ~15 / ~5 in a 45-min block)
- [ ] [EP46: Step-by-step guide on System Design Interview](https://blog.bytebytego.com/p/ep46-step-by-step-guide-on-system) — `ByteByteGo` — free newsletter companion to the 4-step video
- [ ] [A Framework for System Design Interviews](https://bytebytego.com/courses/system-design-interview/a-framework-for-system-design-interviews) — `ByteByteGo` / Vol.1 Ch.1 — dos/don’ts, collaboration, time allocation detail
- [ ] [EP141: How to Ace System Design Interviews](https://blog.bytebytego.com/p/ep141-how-to-ace-system-design-interviews) — `ByteByteGo` — 7-step checklist: clarify → estimate → HLD → DB → interfaces → scale/perf → reliability
- [ ] [How to approach a system design interview question](https://github.com/donnemartin/system-design-primer#how-to-approach-a-system-design-interview-question) — `primer` — lead the open-ended convo: use cases/constraints → HLD → core components → scale + tradeoffs
- [ ] [system-design-primer (hub)](https://github.com/donnemartin/system-design-primer) — `primer` — building-block index + worked solutions to drill the approach on
- [ ] [Rubric for System Design Interviews](https://www.tryexponent.com/courses/system-design-interviews/system-design-interview-rubric) — `Exponent` — what interviewers score: requirements, design+tradeoffs, scalability, fault tolerance, communication (weak → very strong)
- [ ] [System Design Interview Prep Guide (2026)](https://www.tryexponent.com/blog/system-design-interview-guide) — `Exponent` — bar shift: cost, failure modes, ops/monitoring unprompted; level expectations
- [ ] [10 System Design Interview Mistakes That Cost You the Offer](https://www.designgurus.io/blog/system-design-interview-mistakes) — `DesignGurus` — jump-to-diagram, no tradeoffs, time sink on one box, ritual estimation, Google-scale by default
- [ ] [Common Mistakes to Avoid in a System Design Interview](https://www.geeksforgeeks.org/system-design/common-mistakes-to-avoid-in-a-system-design-interview/) — `GeeksforGeeks` — clarify-first + estimate load early; MVP before feature sprawl
- [ ] [System design interview guide](https://www.techinterviewhandbook.org/system-design/) — `Tech Interview Handbook` — when HLD shows up (mid/senior), formats (distributed vs API vs OOD), resource map
- [ ] [System Design Primer (video)](https://www.youtube.com/watch?v=SqcXvc3ZmRU) — `Gaurav Sen` — HLD vs LLD mental model; scaling / LB / decoupling intuition before frameworks
- [ ] [System Design playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — full designs; listen for where capacity + tradeoffs drive architecture
- [ ] [system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` / Gaurav Sen — curated further-reading dump after the framework is muscle memory
- [ ] [DDIA — book home](https://dataintensive.net/) — `DDIA` — reliable / scalable / maintainable vocabulary interviewers expect in deep dives (not proofs)

## Core concepts to master
- **You lead a 45-min design conversation.** Interviewer grades process + judgment under time, not a unique “correct” diagram. Announce phases so they can pace/redirect with you.
- **Merged 45-min skeleton (use this):** (1) FR + NFR + explicit out-of-scope (~5) → (2) core entities (~2) → (3) API/interface (~5) → (4) simple HLD that satisfies FRs (~10–15) → (5) deep dives on NFRs/bottlenecks (~10) → (6) wrap: bottlenecks, failures, what you’d do next (~3–5). Optional early estimation only if numbers change the design (Hello); otherwise estimate in the deep dive when needed.
- **Functional vs non-functional:** FRs = “users can…” (top 3 features). NFRs = quantified qualities (“feed p99 < 200ms”, “prefer availability over consistency on timeline”). Vague “highly available / fast / secure” scores weak.
- **Working system first, complexity later.** Draw a complete path for core APIs before caches, queues, shards. Note “add cache here later” and move on — unfinished HLD is the #1 mid-level fail (Hello).
- **Deep dive = seniority signal.** Junior: follow interviewer probes. Senior+: pick 1–2 hard spots yourself (hot read path, write fan-out, consistency edge, SPOF) and drive tradeoffs.
- **What interviewers score (Exponent rubric):** (1) problem understanding / requirements, (2) technical design + justified tradeoffs, (3) scalability & performance (incl. sensible numbers), (4) fault tolerance & reliability, (5) communication & collaboration. Ratings typically weak → very strong map to no-hire / hire / strong-hire advocacy.
- **Tradeoff language wins.** Name alternatives you rejected (SQL vs NoSQL, fan-out-on-write vs read, sync vs async) and *why for this NFR*. Naming Kafka/Redis without a reason is a red flag.
- **Ops/cost are no longer optional bonus points.** Mention failure modes + mitigation, monitoring/alerts, and rough cost/right-sizing when relevant (Exponent 2026 bar).
- **Collaborate, don’t monologue.** Check in after HLD (“buy-in?”); leave room for probes in deep dives; absorb hints. Talking over the interviewer burns the communication signal.

## Practice — how it's asked & how to attack it
Self-test drills (framework muscle memory before problem modules):
1. **Drill — 5-min requirements script:** Prompt “Design Instagram.” Ask FRs, NFRs (latency/consistency/scale), out-of-scope. Write ≤3 FRs + ≤4 quantified NFRs; stop when you’d ask the interviewer to confirm.
2. **Drill — estimation gate:** For the same prompt, list which one number (QPS, storage, or fan-out fan-in) would *change* architecture. If none, say aloud you’d skip upfront math — then do one crux estimate in ≤2 min.
3. **Drill — API from FRs:** Map each FR to 1–2 REST endpoints (or events). No HLD until the contract is on the board.
4. **Drill — HLD-only timer (12 min):** Boxes/arrows only for the happy path of those APIs. Forbidden: Redis/Kafka/sharding until every FR has a path. Narrate data + state changes.
5. **Drill — deep-dive picker:** From your HLD, name the two weakest NFR spots and one SPOF; for each, state option A vs B + tradeoff in ≤3 sentences.
6. **Drill — full timed dry run (45 min):** Run Hello or ByteByteGo pacing on a primer question (e.g. URL shortener / Pastebin). End with a 60-sec wrap: design summary, top tradeoffs, what you’d improve with more time.

## Common follow-ups / gotchas
- “Why didn’t you estimate first?” — Numbers only when they pick architecture class; ritual DAU→QPS with “so… it’s a lot” wastes signal (Hello). Do math when sharding/cache/replication decisions depend on it.
- “You jumped to microservices / Kafka.” — Over-engineering before a working monolith-style HLD. Simple path first; async/cache as deep-dive upgrades tied to NFRs.
- “What are the tradeoffs?” — Every major choice needs an alternative you considered. Silence here tanks the technical-design rubric bucket.
- “What if this component dies?” — Expect SPOF, redundancy, retries/backoff, degraded mode. Saying “it’s replicated” without user impact + mitigation is weak fault-tolerance signal.
- “You’re out of time / still on schema.” — Time-box requirements (~5) and HLD; leave ≥10 min for deep dives. Schema fields that don’t drive design are noise.
- “How do you know this scales?” — Tie to peak QPS, read/write ratio, and a concrete lever (replicas, shard key, cache, CDN, queue). Blind “NoSQL scales better” is a classic fail.

## Where it appears
- **Campus / early-career India product cos:** often one HLD-style round or a lighter “design at scale” discussion after coding; Flipkart, Uber, Atlassian, etc. still expect clarify → diagram → bottlenecks even if less formal than FAANG.
- **FAANG / big-tech SDE:** standard 45–60 min HLD for mid+; new-grad loops vary (some skip or shorten). Meta/Amazon/Google-style rounds use delivery + tradeoff depth heavily (Hello / Exponent framing).
- **Frequency:** **meta for every HLD question** — URL shortener, chat, feed, rides, video, rate limiter, etc. Master this once; apply unchanged on all later `hq*` modules.
