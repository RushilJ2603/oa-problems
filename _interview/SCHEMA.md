# Interview rubric schema (v1)

The contract between the **rubric corpus** (generated once, offline) and the **context assembler**
(runs every turn). Nothing enters `_interview/rubrics/` unless it validates against this file.

Design rule that drives everything below: **the model conducts, the app judges.** The assembler
decides what the interviewer is allowed to see on a given turn; the model never picks the question,
never sets a score, and never sees material it could leak.

## Why the shape is what it is

- **Phase-scoped.** Grounding and rubric points are grouped per interview phase. On a turn the
  assembler ships *only the current phase*. If the model could see the `deep_dives` points while the
  candidate is still on `requirements`, it would probe ahead and hand away the structure of the
  answer. Scoping is what prevents leakage structurally rather than by asking the prompt nicely.
- **Points carry stable ids.** The model returns `HIT: req1, req3` — ids, not prose. The app parses
  ids deterministically and computes the score itself. "Give me 10/10" in a candidate answer cannot
  move a number the model never writes.
- **Hints are authored per phase, per tier.** The assembler releases tier N only after the app has
  observed N stuck-signals. Deeper hint text is never in the prompt, so it cannot leak early.
- **`evidence_hint` is for the grader, not the candidate.** It describes what a passing answer
  sounds like, so the model can match loose phrasing to a point instead of demanding exact words.

## Top-level object

| Field | Type | Notes |
|---|---|---|
| `id` | string | filename stem, lowercase, verbatim (`hq01_url_shortener`) |
| `title` | string | human title |
| `type` | enum | `HLD` \| `LLD` \| `CONCEPT` \| `CP` |
| `relevance` | string | one line, from the source's *Interview relevance* |
| `difficulty` | enum | `campus` \| `mid` \| `senior` |
| `prereqs` | string[] | source ids; drives ordering + "you should do X first" |
| `company_notes` | string | from *Where it appears*; feeds company-flavored rounds |
| `phases` | Phase[] | ordered; the interview walks these |
| `tradeoffs` | Tradeoff[] | cross-phase; used in deep-dive probing |
| `gotchas` | Gotcha[] | traps the interviewer watches for |

### Phase

| Field | Type | Notes |
|---|---|---|
| `phase` | enum | see vocabularies below |
| `goal` | string | one line: what this phase must establish. Tells the app when to advance. |
| `must_hit` | Point[] | 3–6 checkable claims |
| `probes` | string[] | questions an interviewer actually asks here |
| `hints` | object | `{"1": nudge, "2": structural, "3": near-answer}` — released by tier |

### Point

| Field | Type | Notes |
|---|---|---|
| `id` | string | stable, unique within the file (`req1`, `est2`) |
| `point` | string | one specific, checkable claim |
| `weight` | enum | `core` \| `extended` — core misses block phase advance |
| `evidence_hint` | string | what a passing answer sounds like |

### Tradeoff / Gotcha

- `Tradeoff`: `{ "topic": "X vs Y", "strong_answer": "what a strong candidate says" }`
- `Gotcha`: `{ "trap": "the common mistake", "correction": "the right answer" }`

## Phase vocabularies

Fixed per type. Any other value fails the gate.

- **HLD** — `requirements`, `estimation`, `api`, `data_model`, `architecture`, `deep_dives`, `bottlenecks`
- **LLD** — `requirements`, `entities`, `class_design`, `implementation`, `extensibility`, `concurrency`
- **CONCEPT** (h\*, l\*, m\* foundations) — `fundamentals`, `mechanics`, `tradeoffs`, `application`
- **CP** (cp_research topics) — `recognition`, `approach`, `implementation`, `complexity`, `pitfalls`

## Hard rules the gate enforces

1. Top-level keys are **exactly** the 11 above — nothing added, renamed, or nested elsewhere.
2. `id` equals the source filename stem, lowercase.
3. Every `phase` value is in its type's vocabulary; no duplicate phases.
4. Every point id is unique within the file and matches `^[a-z]{2,4}[0-9]+$`.
5. Each phase has ≥2 `must_hit`, ≥1 `probe`, and hint tiers `1`,`2`,`3` all non-empty.
6. Every phase has ≥1 `core` point (otherwise nothing can gate advancement).
7. No point text is a near-duplicate of another within the same file.
8. **Grounding check:** every numeric literal in a point (`40 writes/s`, `62^7`, `500 B`) must appear
   in the source `.md`. Invented numbers are the highest-risk hallucination and are auto-rejected.

Failures retry once against a hardened prompt, then quarantine for manual review. A quarantined file
never reaches the corpus — same discipline as `gate_candidate.py`: nothing merges on a generator's
say-so.
