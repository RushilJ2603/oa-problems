# System Design (HLD + LLD) Sheet — Research Spec

We are building a **curated System Design sheet** for **placement / SDE interviews** — the SD analogue of a
NeetCode/Striver sheet. It is **sheet-only**: resources to read/watch + questions to practice + a repeatable
framework, so a student who "doesn't know where to start" gets structure. Audience: strong DSA student (has
done Striver) prepping for **campus + off-campus SDE interviews at product companies** (FAANG + Indian product
cos like Atlassian, Uber, Flipkart, DE Shaw, etc.).

## Scope = ONLY what placement interviews actually test
- **HLD (High-Level Design):** the 45-min "design X" round — foundations (networking, DB, caching, queues,
  consistency, scaling) + ~15-20 canonical design questions.
- **LLD (Low-Level Design / OOD):** the "design classes for Y" round — OOP/SOLID, the interview-relevant design
  patterns, concurrency, + ~15-20 canonical LLD problems (parking lot, Splitwise, elevator, etc.).
- **Do NOT** go into research-grade distributed-systems theory (formal Paxos proofs, exotic CRDTs) beyond what
  an interviewer expects. Depth = "can discuss tradeoffs confidently", not "can implement Raft".

## Curated resources to draw from (cite the BEST, link directly)
Gaurav Sen (YouTube playlist + `System-Design` GitHub), ByteByteGo (Alex Xu — *System Design Interview* Vol 1 & 2,
newsletter, YouTube), `donnemartin/system-design-primer` (GitHub), *Designing Data-Intensive Applications* (DDIA,
by chapter), Grokking the System Design Interview (topic list), Hello Interview, InterviewReady, `ashishps1/
awesome-low-level-design` (GitHub) and `prasadgujar/low-level-design-primer` for LLD, Refactoring.Guru (design
patterns). Prefer free + canonical. Every link MUST be real and working — verify, never invent URLs; drop
anything you're unsure of.

## Output file — write EXACTLY this structure to your assigned filename
```
# <ID> — <Title>

**Interview relevance:** High | Medium (which rounds / companies) — one line
**Type:** HLD-foundation | HLD-question | LLD-fundamental | LLD-question | resource-meta
**Prereqs:** <other modules in this sheet>

## Read / watch (curated, in order)
- [ ] [Resource title](URL) — `source` (Gaurav Sen / ByteByteGo / DDIA ch.N / primer / Refactoring.Guru) — why / what it teaches

## Core concepts to master
5-12 crisp bullets — the ideas/tradeoffs you must be able to discuss.

## Practice — how it's asked & how to attack it
For a DESIGN QUESTION (HLD or LLD): give the interview walk-through skeleton —
  1. Requirements (functional + non-functional) & scale assumptions
  2. Back-of-envelope estimation (for HLD)
  3. API / interface
  4. Data model / class diagram
  5. High-level architecture / component breakdown
  6. Deep dives & the 2-3 key tradeoffs an interviewer probes
  7. Bottlenecks / how you scale it
For a FOUNDATION/FUNDAMENTAL: give 3-6 concrete sub-questions or drills to test yourself.

## Common follow-ups / gotchas
3-6 bullets — the follow-up questions interviewers actually ask.

## Where it appears
Which companies / which round (campus vs experienced), how frequently.
```

## Quality bar
Terse, high-signal, real links, ordered by learning sequence. This is a reference a student follows top-to-bottom.
