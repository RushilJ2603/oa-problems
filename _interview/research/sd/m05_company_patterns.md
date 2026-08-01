# M05 — Company-specific SD/LLD interview patterns (FAANG + Indian product cos)

**Interview relevance:** High — same HLD/LLD skeleton, different scoring weights and formats; knowing “what *this* company probes” is the 10% that moves meet-bar → strong-hire (campus + experienced).
**Type:** resource-meta
**Prereqs:** M01 (HLD framework), L06 (LLD framework); foundations H01–H16 and L01–L05 before drilling company prompts.

## Read / watch (curated, in order)
- [ ] [System Design Interview Prep & Questions (2026 Guide)](https://www.tryexponent.com/blog/system-design-interview-guide) — `Exponent` — cross-company map: Google vs Meta vs Amazon formats, level bars, recent prompt themes
- [ ] [Company-Specific Interview Flavors (Amazon, Google, Meta, Netflix)](https://hld.handbook.academy/curriculum/interview-framework/company-specific-flavors/) — `HLD Handbook` — same prompt, four rubric weightings; what to emphasize per flavor
- [ ] [What to Expect in Google's System Design Interview (2026)](https://www.tryexponent.com/blog/google-system-design-interview) — `Exponent` — first-principles depth; build components, don’t name managed services; L3–L4 light / L5+ heavy
- [ ] [Google L5 Interview Guides & Questions](https://www.hellointerview.com/guides/google/l5) — `Hello Interview` — loop shape + where design sits for senior Google
- [ ] [Meta System Design Interview (2026 Guide)](https://www.tryexponent.com/blog/meta-system-design-interview) — `Exponent` — Meta-scale products, 45-min pace, proactive sharding/caching
- [ ] [Understanding Meta Product Architecture vs System Design](https://www.hellointerview.com/blog/meta-system-vs-product-design) — `Hello Interview` — SWE-Product vs SWE-Infra tracks; same prompt, different focus (API/UX vs infra)
- [ ] [Meta E5 Interview Guides & Questions](https://www.hellointerview.com/guides/meta/e5) — `Hello Interview` — E5 loop weighting; design + behavioral level signal
- [ ] [Amazon System Design Interview (2026 Guide)](https://www.tryexponent.com/blog/amazon-system-design-interview) — `Exponent` — resiliency > raw scale; LPs inside the design round; HLD vs LLD by level; reverse system design
- [ ] [Amazon L5 Interview Guides & Questions](https://www.hellointerview.com/guides/amazon/l5) — `Hello Interview` — L5 expects both HLD and OOD competence
- [ ] [Microsoft System Design Interview (2026 Guide)](https://www.tryexponent.com/blog/microsoft-system-design-interview) — `Exponent` — team-written prompts; ask HLD vs LLD up front; security/compliance unprompted
- [ ] [Uber Software Engineer Interview Guide](https://www.tryexponent.com/guides/uber-software-engineer-interview) — `Exponent` — classic HLD round; clarify → simple HLD → deep dive → bottlenecks
- [ ] [System Design Interviews at Google, Amazon, and Meta](https://www.designgurus.io/blog/system-design-interviews-at-google-meta-amazon) — `DesignGurus` — shared top prompts (URL shortener, feed, chat, …) + per-company structure table
- [ ] [Atlassian Engineering Interview Guide](https://www.atlassian.com/company/careers/resources/interviewing/engineering) — `Atlassian (official)` — 60-min systems design; laddering follow-ups; explore reliability/cost, not “one right diagram”
- [ ] [Atlassian System Design Interview: What the Bar Actually Tests](https://spacecomplexity.ai/blog/atlassian-system-design-interview) — `SpaceComplexity` — collab-product prompts, multi-tenancy, code-design (LLD) separate from HLD
- [ ] [Atlassian's Interview Process (2026)](https://www.techprep.app/blog/atlassian-interview-process) — `TechPrep` — Craft/LLD + HLD + Values; production-quality code in Craft
- [ ] [HLD Interview Bible — SDE1→SDE2 (Indian Product Companies)](https://pspatilx.medium.com/hld-interview-bible-sde1-sde2-indian-product-companies-ddf23e2bab85) — `Medium` — Flipkart/Swiggy/Razorpay/Atlassian/etc. top designs + India pacing tips
- [ ] [Top 15 System Design Questions for Indian Tech Companies (2026)](https://www.tusharagrawal.in/blog/system-design-interview-questions-india-2026) — `Tushar Agrawal` — India landscape table + Flipkart/fintech-flavored prompts
- [ ] [System Design Interview Prep for Indian Engineers](https://techtipsindia.com/blog/system-design-interview-prep) — `Tech Tips India` — India-scale constraints (sales spikes, UPI, vernacular) mapped to company question themes
- [ ] [HLD vs LLD: System Design Interview Guide](https://ikshitij.com/learn/hld-lld-interview/) — `ikshitij` — when Indian loops separate HLD vs LLD; prep order by company type
- [ ] [Microsoft / Uber / Google / Amazon / Atlassian Interview Experiences](https://shubham-jain.medium.com/microsoft-uber-google-amazon-atlassian-dunzo-interview-experiences-with-questions-6129ca89a20a) — `Medium` — real loop shapes: machine coding vs LLD whiteboard vs HLD
- [ ] [How to Prepare for a Low-Level Design Interview](https://www.hellointerview.com/blog/how-to-prepare-lld) — `Hello Interview` — LLD delivery (requirements → entities → classes → impl → verify); Amazon/Atlassian/India Craft prep
- [ ] [Low Level Design in a Hurry — Introduction](https://www.hellointerview.com/learn/low-level-design/in-a-hurry/introduction) — `Hello Interview` — what LLD scores (decompose, boundaries, extensibility)
- [ ] [awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) — `ashishps1` — practice catalog for parking lot / Splitwise / machine-coding style rounds
- [ ] [low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `prasadgujar` — LLD problem index + approach notes
- [ ] [How I Cracked the Object Oriented Design Interview at Amazon](https://www.davidseek.com/object-oriented-design-amazon) — `davidseek` — Amazon OOD cadence: clarify → API → classes → extensibility
- [ ] [System design interview guide](https://www.techinterviewhandbook.org/system-design/) — `Tech Interview Handbook` — when HLD appears by level; distributed vs API vs OOD formats
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — reusable 45-min pacing underneath every company flavor
- [ ] [system-design-primer](https://github.com/donnemartin/system-design-primer) — `primer` — building blocks + worked designs to re-skin per company emphasis

## Core concepts to master
- **Framework is shared; flavor is the delta.** Requirements → API/entities → HLD or class design → deep dives → tradeoffs stays constant (M01/L06). Companies re-weight: Google depth, Meta product+scale, Amazon resiliency+LPs, Microsoft domain+security, Atlassian laddering+multi-tenancy, Indian product cos LLD/machine-coding + practical India scale.
- **Google:** Vague one-liner; *you* set scope. Prefer mechanisms over AWS/GCP product names — if you say “queue,” expect “build the queue.” Standalone design mainly L5+; L3/L4 often folds scaling into coding.
- **Meta:** Design products Meta ships (feed, Messenger, storage, CDN). Track split: **System Design** (infra / zoomed-in backend) vs **Product Architecture** (user-facing; APIs + UX flows). Same four competencies; Excalidraw-style whiteboard; drive Meta-scale (sharding, fan-out, caches) *proactively*.
- **Amazon:** Resiliency first (circuit breakers, isolation, degradation). LPs scored *inside* design (Ownership, Customer Obsession, one-way vs two-way doors). Junior loops often **OOD/LLD** (parking lot, chess, coupons); senior = HLD + sometimes reverse design of *your* past system. Bar Raiser calibrates level.
- **Microsoft:** Hiring *team* writes the prompt — Azure / M365 / gaming flavor. Explicitly ask: **HLD whiteboard or coded LLD?** Raise auth, privacy, compliance early. Round is a level-setter; thin domain depth → downlevel risk.
- **Uber (and similar marketplace cos):** Classic 45–60 min HLD; intermediate prompts often generic (not only “design Uber”). Real-time / geo / matching vocabulary helps if the prompt drifts there.
- **Atlassian:** Official 60-min systems design with **laddering** (requirements layered mid-round). Separate **code design / Craft (LLD)** with working extensible code. Product-shaped prompts (boards, workflows, notifications, job schedulers) + multi-tenancy. Values round can veto a strong technical packet.
- **Indian product cos (Flipkart, Swiggy, Zomato, PhonePe, Razorpay, Cred, Walmart GT, etc.):** Expect **both** HLD and LLD — often a **machine-coding** round (working code + tests in ~90–120 min or take-home) *plus* a diagram HLD. Themes: flash sales / inventory, payments idempotency, dispatch/geo, search/catalog, chat, URL shortener, rate limiter. Cost and realistic India-scale matter more than “design for 1B MAU by default.”
- **DE Shaw:** Still coding / CS-fundamentals / systems-depth first; experienced loops may add LLD (modular backend, patterns) and HLD with crisp CAP/partition/failure reasoning — not Flipkart-style machine-coding volume. Don’t skip DSA for SD-only prep.
- **LLD vs HLD company lean:** Heavy LLD/machine-coding — Amazon junior, Atlassian Craft, Flipkart/Swiggy/PhonePe/Cred-class India loops. Heavy HLD — Meta, Google L5+, Uber HLD round. Mixed/ambiguous — Microsoft (ask), Amazon L5+, Atlassian (both rounds).

## Practice — how it's asked & how to attack it
Self-test drills (company-flavor muscle memory):
1. **Drill — flavor cheat sheet (15 min):** For each target company, write 5 lines: (a) HLD vs LLD vs both, (b) time box, (c) #1 scored signal, (d) 3 likely prompts, (e) one phrase you’ll say unprompted (e.g. Meta: sharding; Amazon: circuit breaker; Atlassian: tenant isolation; Razorpay: idempotency).
2. **Drill — same prompt, three companies:** Take “Design a notification system.” Run 20 min as Meta (fan-out at billions), 20 min as Amazon (failure isolation + LP language), 20 min as Flipkart/Atlassian (multi-tenant / cost / extensibility). Diff your deep-dive picks.
3. **Drill — Google “build it” pushback:** In any HLD, when you name Redis/Kafka/queue, spend 5 min explaining *internals* (data structure, consistency, failure) as if the interviewer banned the product name.
4. **Drill — Amazon reverse design:** Pick a past project; narrate architecture → SPOF → circuit breaker / retry / degradation → “who is on-call.” Time-box 25 min.
5. **Drill — Microsoft format gate:** Open every mock with “Do you want high-level architecture or object-oriented classes I’ll code?” Then practice *both* on the same prompt (e.g. file system).
6. **Drill — India machine coding:** From `awesome-low-level-design`, pick parking lot / Splitwise / rate limiter. 90 min: requirements → classes → working code → 3 edge-case tests. Then spend 30 min converting the same problem into an HLD diagram for a separate Flipkart-style HLD round.
7. **Drill — Atlassian laddering:** Start “design a task board.” At 20 min inject “10k orgs, custom fields, Forge plugin CPU spike.” Adapt without redrawing from scratch; narrate multi-tenancy options.

## Common follow-ups / gotchas
- “Why Kafka/Redis here?” — At Google: explain the mechanism. At Amazon: tie to failure blast radius. At Meta: tie to QPS / fan-out. Product-name drops without tradeoffs fail everywhere.
- “You prepared the wrong Meta track.” — Product Architecture ≠ Design Memcached. Confirm SWE-Product vs SWE-Infra; still cover APIs *and* scale for either.
- “Junior Amazon with only HLD prep.” — Many SDE I/II loops want OOD classes, not distributed boxes. Practice parking lot / chess / coupons.
- “Microsoft ‘design’ meant code.” — Candidates who assume endpoints/DBs stall when told “code the file system.” Ask format first.
- “India loop: only Alex Xu / Grokking.” — Leaves machine-coding / LLD under-prepped for Flipkart-class companies; US FAANG guides underweight Craft rounds.
- “Atlassian: strong HLD, weak Values/Craft.” — Laddering + clean extensible code + values stories are first-class; tech-only prep is incomplete.
- “I always design for Google-scale.” — Overkill (and wrong cost signal) at many India product cos; ask traffic assumptions; design for stated NFRs.

## Where it appears
- **Campus / early-career India:** Coding + often **one LLD or machine-coding**; HLD lighter or merged into “design discussion.” Flipkart / Swiggy / PhonePe / Atlassian Bengaluru still expect clarify → structure → bottlenecks.
- **Experienced SDE-2 / senior (India product + FAANG India):** Usually **separate LLD and HLD** (or Craft + systems design at Atlassian); Meta/Google/Amazon India follow parent-company flavors with India logistics.
- **FAANG (global):** Meta & Google — HLD-centric (Meta may split Product Architecture); Amazon — HLD + LLD by level + LPs; Microsoft — team-domain HLD *or* coded LLD; Uber — standard HLD.
- **Frequency:** **Meta module** — consult before every company-targeted mock; re-read the 1-page flavor notes the night before each loop. Pair with M01/L06 for delivery; use `hq*` / `lq*` modules for prompt practice.
