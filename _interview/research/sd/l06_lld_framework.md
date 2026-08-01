# L06 — LLD interview framework & UML basics

**Interview relevance:** High — the pacing/structure for every LLD / OOD / machine-coding round (campus + experienced); Flipkart, Uber, Swiggy, PhonePe, Atlassian, Amazon, Google, Meta all grade how you go requirements → entities → class diagram → patterns → code, not pattern name-dropping alone.
**Type:** LLD-fundamental
**Prereqs:** OOP & SOLID (L01); creational patterns (L02) helpful before the “apply patterns” step; structural/behavioral pattern modules next

## Read / watch (curated, in order)
- [ ] [How to approach OOD Interviews](https://algomaster.io/learn/lld/ood-approach) — `AlgoMaster` / [awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) — canonical 5-step OOD loop: clarify → entities → classes/interfaces → patterns → use-case walkthrough (Stack Overflow running example)
- [ ] [How to Answer a LLD Interview Problem](https://blog.algomaster.io/p/how-to-answer-a-lld-interview-problem) — `AlgoMaster` newsletter — same framework in free blog form; UML optional; central manager + interfaces + edge cases
- [ ] [LLD Interview Delivery Framework](https://www.hellointerview.com/learn/low-level-design/in-a-hurry/delivery) — `Hello Interview` — timed 35–45 min pacing: requirements → entities → class design → implementation → extensibility; boxes/arrows > ceremony UML
- [ ] [How to Prepare for a Low-Level Design Interview](https://www.hellointerview.com/blog/how-to-prepare-lld) — `Hello Interview` — fundamentals + delivery framework + practice order; when *not* to force patterns
- [ ] [How to approach Machine Coding Interviews](https://algomaster.io/learn/lld/machine-coding-approach) — `AlgoMaster` — Flipkart/Uber/Swiggy-style: must-have vs nice-to-have, quick design (15–20% time), bottom-up impl, demo `Main`
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — clarify → design 10–15 min → code → demo; mandatory > optional; optional UML sketch
- [ ] [How to prepare for machine coding round?](https://workat.tech/machine-coding/article/how-to-prepare-for-machine-coding-round-naf2ih7a9e5l/) — `workat.tech` — models vs services vs driver; naming, separation of concerns under a timer
- [ ] [UML Class Diagram Explained with Examples](https://blog.algomaster.io/p/uml-class-diagram-explained-with-examples) — `AlgoMaster` — class box (name / attrs / ops), `+ - # ~`, association / aggregation / composition / inheritance / realization / dependency + multiplicity
- [ ] [Class diagram (Wikipedia)](https://en.wikipedia.org/wiki/Class_diagram) — `reference` — UML compartments, visibility, association vs aggregation vs composition, generalization, realization, multiplicity table
- [ ] [UML Association vs Aggregation vs Composition](https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-aggregation-vs-composition/) — `Visual Paradigm` — lifecycle ownership: Student/Class (aggregation) vs Room/House (composition)
- [ ] [UML Class Diagram Relationships](https://creately.com/guides/class-diagram-relationships/) — `Creately` — quick visual cheat-sheet for association, multiplicity, aggregation, composition, inheritance, realization
- [ ] [UML Class Diagram Tutorial (Lucid)](https://lucid.co/diagram/uml/class-diagram-tutorial) — `Lucidchart` — three-compartment class, visibility markers, inheritance/association walkthrough + short [YouTube](https://www.youtube.com/watch?v=6XrL5jXmTwM)
- [ ] [Sequence diagram (Wikipedia)](https://en.wikipedia.org/wiki/Sequence_diagram) — `reference` — optional interview add-on: objects × time for one critical flow (park car, place order, ask question)
- [ ] [Design Patterns catalog](https://refactoring.guru/design-patterns/catalog) — `Refactoring.Guru` — pick patterns *after* the class diagram; start with [Strategy](https://refactoring.guru/design-patterns/strategy), [Observer](https://refactoring.guru/design-patterns/observer), [Factory Method](https://refactoring.guru/design-patterns/factory-method), [Facade](https://refactoring.guru/design-patterns/facade), [State](https://refactoring.guru/design-patterns/state)
- [ ] [Dive Into Design Patterns — free demo PDF](https://refactoring.guru/files/design-patterns-en-demo.pdf) — `Refactoring.Guru` — OOP + UML primer before the GoF catalog ([full book](https://refactoring.guru/design-patterns/book))
- [ ] [awesome-low-level-design (hub)](https://github.com/ashishps1/awesome-low-level-design) — `awesome-low-level-design` — approach links + problem list to drill this framework on
- [ ] [low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra question/solution index once the framework is muscle memory

## Core concepts to master
- **Repeatable pipeline:** requirements & use cases → nouns/entities → class diagram (state + APIs + relationships) → 0–2 justified patterns → code / walkthrough. Announce each phase so the interviewer can pace with you.
- **Requirements first:** functional (what ops?), actors, rules/state transitions, errors, and explicit **out of scope** (UI, DB, network). Write 4–8 bullets on the board; never invent a notification engine nobody asked for.
- **Noun / verb extraction:** nouns → candidate classes (filter: has state/rules = class; mere info = field/enum); verbs → methods. Aim for ~4–7 core entities + one **orchestrator / Facade** (`ParkingLot`, `Game`, `StackOverflow`).
- **Class design = state + behavior tied to requirements:** for each entity, list fields that enforce rules and methods that map to use cases; put rules with the owner of the state (encapsulation / tell-don’t-ask).
- **UML basics (interview-enough):** class = name | attributes | operations; visibility `+ public` / `- private` / `# protected` / `~ package`. Relationships: **association** (uses), **aggregation** ○ (has-a, part can live alone), **composition** ● (owns lifecycle), **generalization** ▵ (is-a), **realization** dashed ▵ (implements interface), **dependency** dashed → (uses momentarily). Multiplicity: `1`, `0..1`, `*`, `1..*`.
- **Formal UML is optional:** many FAANG/Hello-Interview style rounds accept boxes + arrows or skeleton code; Indian machine-coding often likes a quick UML sketch — **ask** what they want.
- **Patterns last, not first:** Strategy (varying pricing/reputation), Factory (varying product types), Observer (notifications), State (open/closed/vending), Facade (manager). Name the problem, then the pattern — never the reverse.
- **OOD vs machine coding:** OOD = discussion + class diagram / stubs (45–60 min). Machine coding = working demo; design ≤15–20% of time; models → services → `Main`; must-haves before nice-to-haves.
- **Close with a use-case trace:** walk one happy path + 2–3 edge cases (self-vote, full lot, invalid move) so classes prove they collaborate; sequence diagram only if it clarifies a hot path.

## Practice — how it's asked & how to attack it
1. **Drill — 5-min requirements script:** Prompt “Design Parking Lot.” Ask ops, vehicle types, floors/gates, payment, concurrency, out-of-scope. Write MUST vs NICE bullets; stop when interviewer confirms.
2. **Drill — noun filter:** From “Users ask tagged questions, answer, comment, and vote,” list entities; drop attributes (`title`) and external inputs; keep `User`, `Question`, `Answer`, `Comment`, `Tag`, `Vote` + manager.
3. **Drill — UML relationship quiz:** For each pair, pick association / aggregation / composition / inheritance / realization: ParkingLot–Floor, Floor–Spot, Vehicle–Car, Question–Tag, `Question`–`Votable`, House–Room, Department–Professor.
4. **Drill — class API from requirements:** Take Tic-Tac-Toe requirements; derive `Game` state (`board`, `currentPlayer`, `state`) and methods (`makeMove`, `getWinner`) without inventing undo/AI.
5. **Drill — pattern gate:** On a finished class sketch, ask “what varies?” If nothing, ship without a pattern. If pricing/reputation/notifications/state machine varies, add exactly one pattern and say why.
6. **Drill — timed dry run:** 45 min OOD (AlgoMaster/Hello framework) *or* 90 min machine coding (workat.tech/AlgoMaster MC phases) on one [awesome-LLD problem](https://github.com/ashishps1/awesome-low-level-design); end with a verbal use-case walkthrough.

## Common follow-ups / gotchas
- “Why didn’t you draw full UML?” — Communication > notation. Offer simplified boxes; switch to formal diamonds/arrows if they insist.
- “Where do patterns fit?” — After entities/APIs. Forcing Singleton/Factory everywhere is a red flag; 1–2 justified patterns beat five unused names.
- “You jumped to code” — Skipping requirements signals poor product sense; always lock scope and write bullets first.
- “God class / anemic models” — Orchestrator coordinates; domain objects own their rules. Don’t dump all logic in `Manager` *or* leave empty getters-only models if behavior belongs there.
- “Optional vs mandatory (machine coding)” — Working must-haves beat half-finished extensibility; say aloud what you’d add next.
- “How do classes collaborate?” — Trace one end-to-end use case (or a short sequence diagram); missing this is how broken designs survive until the interviewer probes.

## Where it appears
- **Campus / new-grad (India product cos):** machine-coding rounds at Flipkart, Uber, Swiggy, PhonePe, Cred, etc. expect this exact clarify → design → code → demo loop; UML sketch often welcome.
- **FAANG / big-tech LLD–OOD:** Google, Amazon, Meta, Microsoft-style rounds lean discussion + class structure + extensibility (Hello Interview pacing); formal UML less common than clear APIs and tradeoffs.
- **Frequency:** foundational for **every** LLD question — parking lot, Splitwise, elevator, Stack Overflow, games, booking systems. Master this once; reuse on all later problem modules.
