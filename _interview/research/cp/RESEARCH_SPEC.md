# CP Sheet — Research Spec (read before writing your topic file)

We are building a **curated competitive-programming sheet** — the CP analogue of NeetCode 150 / Striver's SDE
sheet. It lives as a checklist (links only, not a judge). Audience: a strong student who wants **(1) every
placement OA / DSA interview to be a breeze — TOP priority — and (2) to climb Codeforces/CodeChef rating** as
the stretch goal.

## The band that matters (ceiling = Candidate Master, CF ~2100)
- **Placement core (MAIN weight, ~60-70% of your list):** Codeforces ~**800–1600** (Div 2 A/B/C, occasional D),
  AtCoder ABC A–E, CSES, LeetCode Medium/Hard. This is ~90% of real OAs. The ladder must be solid here.
- **Rating stretch (~30-40%, clearly marked `(stretch)`):** up to CF ~**2100 (Candidate Master)**. This tail
  MAY include the advanced material — lazy segment trees, LCA / binary lifting, sqrt decomposition, Tarjan/
  Kosaraju SCC, DSU-on-tree, basic max-flow, string suffix structures, matrix expo, CHT/DP-opt — **only where
  it's the natural continuation of your topic**, and always marked `(stretch)`. Keep it a minority tail; do
  NOT let advanced problems crowd out the placement core.
- **Still avoid** the truly esoteric (persistent/treap-heavy DS, FFT/NTT unless trivially motivated, Möbius,
  heavy computational geometry, Aho-Corasick/suffix-automaton unless canonical for your topic) — one or two at
  most, only if they're famous milestone problems.

## AUDIENCE: post-Striver, but LC-style not CF-style (READ THIS)
The reader has **finished Striver's A2Z sheet** — so they know the ALGORITHMS/patterns (arrays, all binary
search incl. BS-on-answer, trees/BST, graphs incl. Dijkstra/Bellman-Ford/Floyd/MST/DSU/topo/SCC/bridges, the
classic-DP catalog, tries, KMP/Z/Rabin-Karp) — **but only through LeetCode-style problems. They have NOT done
Codeforces-style problems on these topics.** CF-style = observation/ad-hoc heavy, tighter constraints, "find
the trick", contest time pressure — a different skill from applying a known template.

So for a topic that OVERLAPS Striver: **keep the topic, but pick CF/AtCoder/CSES contest problems, NEVER the
LeetCode problems Striver already used.** The point is to re-train the same pattern in *contest* form.
- Difficulty floor ~**CF 1300** (skip 800-1100 warmups — they're past those). Core band 1300-1700; stretch
  1700-2100 (up to Candidate Master).
- For genuinely NEW CP topics Striver never covers (segment tree + lazy, Fenwick, sparse table, 0-1 BFS,
  LCA/binary-lifting, bitmask/digit DP, string hashing, sqrt/Mo, game theory, matrix expo, meet-in-middle,
  ternary search, competitive number theory & combinatorics): teach from the ground up within the CP context.

## Your job
Curate the **highest-value, most canonical problems** for YOUR assigned topic — the ones that recur in OAs and
teach the pattern with maximum transfer. Quality over quantity. Prefer problems that are "famous" / repeatedly
recommended across CP-31 (TLE Eliminators), CSES, A2OJ/ITMO ladders, AtCoder DP contest, Codeforces EDU,
USACO Guide, and the placement-overlap of NeetCode / Striver.

## Hard rules on links
- Every problem MUST have a **real, working, canonical URL** (Codeforces problem page, CSES, AtCoder, or
  LeetCode). Prefer Codeforces + CSES + AtCoder. Use LeetCode only when it's the canonical home of that pattern.
- Do NOT invent problem IDs or URLs. If unsure a link is real, drop the problem. Broken links are worse than
  fewer problems.
- Include the CF rating (or CSES section / AtCoder difficulty / LC difficulty) for each.

## Output file — write EXACTLY this structure to your assigned filename
```
# <NN> — <Topic Name>

**Placement value:** High | Medium (one line why)
**Prereq topics:** <list>
**Pattern in one paragraph:** what the core idea is and how to recognize it in a problem statement.

## Ladder (easy -> hard, ~18-28 problems)
For EACH problem, one line:
- [ ] [Problem Title](URL) — `platform` `rating/difficulty` — pattern tag — WHY it's high value / where it shows up (OA-classic vs rating-builder)

Order strictly by difficulty within the topic. Mark the ~8-12 must-do "core" ones with **(core)** and the
harder rating-stretch ones with **(stretch)**.

## Must-internalize checklist (5-10 bullets)
The sub-skills / templates one must be able to write from memory after finishing this topic.

## Where it appears in OAs / interviews
2-4 concrete examples of how this topic is disguised in real assessments (company-style if you know them).
```

## Quality bar
- ~18-28 problems, laddered, no duplicates, every link real.
- Bias to problems that are **reused across multiple famous sheets** (high consensus = high value).
- Terse. This is a reference, not an essay.
