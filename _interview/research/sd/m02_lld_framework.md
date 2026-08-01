# M02 — LLD interview framework & rubric

**Interview relevance:** High — the pacing + scoring model for every LLD / OOD / machine-coding round (campus + experienced); Flipkart, Uber, Swiggy, PhonePe, Atlassian, Amazon, Google, Meta grade the same axes: problem analysis → class design → code quality → extensibility → communication.
**Type:** resource-meta
**Prereqs:** OOP & SOLID (L01); do this before parking-lot / Splitwise-style LLD questions; patterns modules help once the pipeline is muscle memory

## Read / watch (curated, in order)
- [ ] [Low-Level Design in a Hurry — Introduction (Interview Assessment)](https://www.hellointerview.com/learn/low-level-design/in-a-hurry/introduction) — `Hello Interview` — what LLD vs HLD tests; official 5-axis rubric: Problem Analysis, Class Design, Code Quality, Extensibility/Maintainability, Communication
- [ ] [LLD Interview Delivery Framework](https://www.hellointerview.com/learn/low-level-design/in-a-hurry/delivery) — `Hello Interview` — timed ~35–45 min loop: Requirements → Entities → Class design → Implementation → Extensibility; boxes/arrows beat ceremony UML
- [ ] [How to Prepare for a Low-Level Design Interview](https://www.hellointerview.com/blog/how-to-prepare-lld) — `Hello Interview` — fundamentals + delivery framework + practice order; what interviewers actually evaluate; when *not* to force patterns
- [ ] [Design Principles (LLD)](https://www.hellointerview.com/learn/low-level-design/in-a-hurry/design-principles) — `Hello Interview` — KISS/YAGNI, SRP, composition-over-inheritance — the judgment bar behind the rubric
- [ ] [How to approach OOD Interviews](https://algomaster.io/learn/lld/ood-approach) — `AlgoMaster` / [awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) — canonical 5-step OOD loop (Stack Overflow example): clarify → entities → classes/interfaces → patterns → use-case walkthrough
- [ ] [How to Answer a LLD Interview Problem](https://blog.algomaster.io/p/how-to-answer-a-lld-interview-problem) — `AlgoMaster` newsletter — same framework in free blog form; central manager + interfaces + edge cases
- [ ] [Object-Oriented Design Interview: step-by-step Guide](https://www.systemdesignhandbook.com/guides/object-oriented-design-interview/) — `System Design Handbook` — requirements → classes → relationships → patterns → use cases → extensibility; composition-first mindset
- [ ] [What is a Machine Coding Round?](https://workat.tech/machine-coding/article/what-is-a-machine-coding-round-omfn1w54ojlg/) — `workat.tech` — Flipkart/Uber/Swiggy-style format + explicit judging criteria (working demo, correctness, modularity, SoC, extensibility, `Main` driver)
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — clarify → design 10–15 min → code → demo; mandatory > optional; timebox under 90–120 min
- [ ] [How to prepare for machine coding round?](https://workat.tech/machine-coding/article/how-to-prepare-for-machine-coding-round-naf2ih7a9e5l/) — `workat.tech` — models vs services vs driver; naming and separation of concerns under a timer
- [ ] [How to approach Machine Coding Interviews](https://algomaster.io/learn/lld/machine-coding-approach) — `AlgoMaster` — 5 phases: clarify → quick design (≤15–20% time) → skeleton → bottom-up impl → validate; MUST vs NICE
- [ ] [Machine Coding Round: Complete Prep Guide](https://www.lowleveldesignmastery.com/blog/machine-coding-round/) — `LLD Mastery` — company formats + weighted eval axes (design/structure, working functionality, SOLID/patterns, extensibility, edge cases)
- [ ] [Flipkart Machine Coding Round Experience (expectations list)](https://www.geeksforgeeks.org/interview-experiences/flipkart-machine-coding-round-experience/) — `GeeksforGeeks` — real Flipkart rubric language: working/demonstrable, functionally correct, abstraction/SoC, modular/readable, extensible, exception handling
- [ ] [Design Patterns catalog](https://refactoring.guru/design-patterns/catalog) — `Refactoring.Guru` — pick patterns *after* class design; start with Strategy / Observer / Factory Method / State / Facade
- [ ] [awesome-low-level-design (hub)](https://github.com/ashishps1/awesome-low-level-design) — `awesome-low-level-design` — approach links + problem list to drill this framework on
- [ ] [low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra question/solution index once the framework is muscle memory

## Core concepts to master
- **Two formats, one skill:** **OOD / LLD discussion** (45–60 min whiteboard/pseudocode — Hello Interview / AlgoMaster) vs **machine coding** (60–120 min runnable demo — Flipkart/Uber/Swiggy). Same modeling; different time split (design-heavy vs code-heavy).
- **Delivery pipeline (announce each phase):** Requirements & scope → entities/relationships → class APIs (state + behavior) → core methods / demo → extensibility follow-ups. Interviewers score *process*, not only the final diagram.
- **Rubric axes (what gets scored):** (1) **Problem analysis** — clarifying Qs, MUST vs NICE, explicit out-of-scope; (2) **Class design** — right entities, ownership, clean APIs; (3) **Code quality** — encapsulation, naming, SoC, composition over deep inheritance; (4) **Extensibility** — absorb “add X” without rewrite (OCP); (5) **Communication** — narrate tradeoffs, verify with a use-case trace.
- **Machine-coding bar (workat / Flipkart language):** working + demonstrable, functionally correct, modular/readable, separation of concerns, easy new requirements, `Main`/driver for demo, graceful exceptions — UI/DB usually out of scope.
- **Requirements first:** actors, ops, rules/state transitions, invalid inputs, concurrency if asked. Write 4–8 bullets; never invent a notification engine nobody requested.
- **Noun filter:** nouns → candidate classes (has state/rules = class; mere info = field/enum); verbs → methods. Aim ~4–7 core entities + one **orchestrator / Facade**.
- **Class design = requirements → state → behavior:** keep rules with the owner of the state (tell-don’t-ask). Formal UML optional — ask; boxes + method stubs usually win.
- **Patterns last:** Strategy / Factory / Observer / State only when something *varies*. 1–2 justified patterns beat five name-drops; over-engineering fails KISS/YAGNI on the rubric.
- **Close with verification:** walk one happy path + 2–3 edge cases (self-vote, full lot, illegal move). Many rubrics explicitly grade self-verification.
- **Mandatory > optional (machine coding):** ship working must-haves; leave NICE as TODOs with comments. Half-finished extensibility loses to a clean demo.

## Practice — how it's asked & how to attack it
1. **Requirements (3–5 min):** Prompt “Design Parking Lot / Tic-Tac-Toe / Stack Overflow.” Ask ops, actors, rules, errors, out-of-scope. Write MUST vs NICE; get sign-off.
2. **Entities (~3 min):** Noun-extract; filter fields vs classes; name the orchestrator; sketch ownership arrows (no ceremony UML unless asked).
3. **Class design (10–15 min OOD / ≤15–20% time MC):** Per entity — state tied to requirements, methods tied to use cases; extract 0–2 interfaces where behavior is shared (`Votable`, `PricingStrategy`).
4. **Implementation / demo:** OOD — implement 2–3 hot methods in pseudocode + edge cases. Machine coding — bottom-up (enums → models → service → `Main`); compile early; demo core flows.
5. **Verification & extensibility (last 5 min):** Trace a concrete scenario; then answer “add undo / new vehicle type / surge pricing” by pointing to the variation point — not rewriting.
6. **Timed dry run:** 45 min OOD (Hello/AlgoMaster phases) *or* 90 min machine coding (workat/AlgoMaster MC) on one [awesome-LLD problem](https://github.com/ashishps1/awesome-low-level-design); score yourself on the five rubric axes aloud.

## Common follow-ups / gotchas
- “Why no full UML?” — Communication > notation. Offer boxes/stubs; switch to formal diamonds if they insist.
- “Where do patterns fit?” — After entities/APIs. Forcing Singleton/Factory everywhere is a red-flag on the Code Quality axis.
- “You jumped to code” — Skipping requirements fails Problem Analysis; lock scope first.
- “God class / anemic models” — Orchestrator coordinates; domain objects own rules. Neither dump-everything-in-`Manager` nor getters-only bags.
- “Optional vs mandatory (machine coding)” — Working must-haves beat half-finished extensibility; say what you’d add next.
- “How would you extend this?” — Point to the interface/strategy you left open; “rewrite the whole thing” fails Extensibility.

## Where it appears
- **Campus / India product cos:** machine-coding often first onsite (Flipkart, Uber, Swiggy, PhonePe, Cred, Ola) — 90–120 min code + review against the workat/Flipkart expectation list.
- **FAANG / big-tech OOD–LLD:** Google, Amazon, Meta, Microsoft-style rounds lean discussion + class structure + extensibility (Hello Interview pacing); formal UML uncommon; patterns rewarded only when justified.
- **Frequency:** meta skill for **every** LLD question — parking lot, Splitwise, elevator, games, booking. Learn the framework + rubric once; reuse on all problem modules.
