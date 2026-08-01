# 41 — Contest strategy & speed-solving meta

**Placement value:** High — timed OAs are the same game as Div2: rank easy work first, ship correct code fast, and do not bleed attempts; CF/AtCoder rating is almost entirely this meta plus upsolving.
**Prereq topics:** Full Striver A2Z pattern set (LC-style), basic CF contest UI / multi-test I/O, ability to code greedy / BS-on-answer / prefix / simple DP without looking them up
**Pattern in one paragraph:** Contest skill is a loop — **skim → rank → solve → verify → submit → (later) upsolve** — under a clock and a wrong-attempt tax. Recognize the meta from time pressure, score decay / ICPC penalty, multi-test traps, and “A looks hard / D looks easy” inversions. Workflow: (1) 2–4 min skim of all statements + constraints to tag *speed-impl / observation / known template / skip*, (2) clear A–B (and easy C) before deep thinking, (3) local-check samples + `n=1` / empty / max before every submit, (4) hard cut-timers when stuck, (5) within 24h upsolve the easiest unsolved with editorial only after a real attempt.

## Ladder (easy -> hard, 28 problems)

- [ ] [Factory Machines](https://cses.fi/problemset/task/1620) — `CSES` `Sorting and Searching` — BS-on-answer under a timer — **(core)** classic “constraints scream binary search”; drill spotting + coding BS in ≤15 min (OA timed section staple)
- [ ] [GeT AC](https://atcoder.jp/contests/abc122/tasks/abc122_c) — `AtCoder` `ABC122 C` — prefix counts, query speed — ABC-C pace drill: read → prefix → answer Q; trains not re-scanning the string per query
- [ ] [K-th Beautiful String](https://codeforces.com/problemset/problem/1328/B) — `Codeforces` `1300` — count-from-the-end construction — **(core)** do not generate strings; combinatorial ranking under Div2-B clock
- [ ] [Product of Three Numbers](https://codeforces.com/problemset/problem/1294/C) — `Codeforces` `1300` — factor hunt + impossible case — verify `n` too small / prime powers before submit; penalty drill on “almost correct” math
- [ ] [Coin Rows](https://codeforces.com/problemset/problem/1555/C) — `Codeforces` `1300` — prefix/suffix skim-classify — **(core)** looks like DP, is prefix sums; 60-second pattern tag practice
- [ ] [Chat Ban](https://codeforces.com/problemset/problem/1612/C) — `Codeforces` `1300` — BS on monotonic answer — “how many messages until ban” → binary search template; must fire in <5 min once seen
- [ ] [3SUM Closure](https://codeforces.com/problemset/problem/1698/C) — `Codeforces` `1300` — observation kills code — **(core)** if too many positives/negatives → NO; teaches “think 3 min before coding O(n²)” (rating-builder + anti-TLE)
- [ ] [Trouble Sort](https://codeforces.com/problemset/problem/1365/B) — `Codeforces` `1300` — careful statement read — **(core)** 0/1 types: when is any permutation reachable?; misread → free WA (penalty mgmt)
- [ ] [Pokémon Army (easy version)](https://codeforces.com/problemset/problem/1420/C1) — `Codeforces` `1300` — take easy version first — contest ranking: bank C1 points / learn the peak-valley idea before C2
- [ ] [Switches](https://atcoder.jp/contests/abc128/tasks/abc128_c) — `AtCoder` `ABC128 C` — constraints → brute — **(core)** `n≤10` ⇒ try all 2ⁿ; ranking by constraints, not by letter
- [ ] [Element Extermination](https://codeforces.com/problemset/problem/1375/C) — `Codeforces` `1400` — anti-overthink one-liner — **(core)** YES iff `a[1] < a[n]`; if you invent a stack/segment tree here, you failed the meta
- [ ] [Number Game](https://codeforces.com/problemset/problem/1370/C) — `Codeforces` `1400` — casework + skip timer — **(core)** ~5 cases on prime/odd factors; no idea in 10–12 min → park and read D (ranking drill)
- [ ] [Subsequence Hate](https://codeforces.com/problemset/problem/1363/B) — `Codeforces` `1400` — enumerate candidates — try all split/target patterns instead of hunting a clever closed form; speed > elegance on B/C
- [ ] [The Delivery Dilemma](https://codeforces.com/problemset/problem/1443/C) — `Codeforces` `1400` — sort + BS / greedy pick — modern Div2-C shape; decide courier vs self-pickup under a time budget
- [ ] [I Hate 1111](https://codeforces.com/problemset/problem/1526/B) — `Codeforces` `1400` — math observation over DP — **(core)** `111…` residue trick; if you start digit-DP in contest, you mis-ranked the problem
- [ ] [Schedule Management](https://codeforces.com/problemset/problem/1701/C) — `Codeforces` `1400` — BS on hours — worker load binary search; OA-flavored “finish by time T?” recognition
- [ ] [Two Substrings](https://codeforces.com/problemset/problem/550/A) — `Codeforces` `1500` — pretest / order trap — **(core)** check AB-then-BA and BA-then-AB (non-overlap); classic “one sample passes, systest fails” penalty lesson
- [ ] [Mortal Kombat Tower](https://codeforces.com/problemset/problem/1418/C) — `Codeforces` `1500` — short DP under pressure — **(core)** 2-state “who kills next”; when you tag DP, code the tiny transition — don’t redesign mid-contest
- [ ] [Non-zero Segments](https://codeforces.com/problemset/problem/1426/D) — `Codeforces` `1500` — prefix-sum set — insert 0 cuts when prefix repeats; Div2-C staple, reward for clean first AC
- [ ] [Min Max Sort](https://codeforces.com/problemset/problem/1792/C) — `Codeforces` `1500` — consecutive-block observation — longest already-consecutive run; skip if you start coding heavy data structures
- [ ] [Chat in a Circle](https://atcoder.jp/contests/abc173/tasks/abc173_d) — `AtCoder` `ABC173 D (400)` — greedy contribution — sort + “each edge used twice except ends”; ABC-D pace / observation under 100-min contest
- [ ] [Potions (Hard Version)](https://codeforces.com/problemset/problem/1526/C2) — `Codeforces` `1600` — greedy + priority queue — **(core)** drink while health ≥0, undo worst; upsolve target if you only cleared C1 in-contest
- [ ] [Set or Decrease](https://codeforces.com/problemset/problem/1622/C) — `Codeforces` `1600` — BS + greedy ops — two-move toolkit; practice choosing *this* C/D when solve counts favor it
- [ ] [Remove the Substring (hard version)](https://codeforces.com/problemset/problem/1203/D2) — `Codeforces` `1700` — two pointers / farthest match — **(stretch)** famous upsolve: L/R match arrays then max window
- [ ] [Solve The Maze](https://codeforces.com/problemset/problem/1365/D) — `Codeforces` `1700` — block then BFS — **(stretch)** rush-submit WA factory (block G-adjacent, then path check); verify both parts before submit
- [ ] [New Year's Problem](https://codeforces.com/problemset/problem/1619/D) — `Codeforces` `1800` — BS + “two shops share” — **(stretch)** hard BS-on-answer; contest ranking when D has more solves than C
- [ ] [Skyscrapers (hard version)](https://codeforces.com/problemset/problem/1313/C2) — `Codeforces` `1900` — stack unimodal construction — **(stretch)** upsolve after C1; teaches finishing the *hard* twin post-contest
- [ ] [Pokémon Army (hard version)](https://codeforces.com/problemset/problem/1420/C2) — `Codeforces` `2100` — online peak-valley updates — **(stretch)** same idea as C1 + point updates; Candidate-Master pace / editorial upsolve milestone

## Must-internalize checklist (5-10 bullets)

- **Open routine:** skim every statement + constraints in the first ~5–8 min; tag each as *speed / observation / template / skip*; do not dig into #1 only because it is letter A.
- **Speed band:** aim A+B (CF Div2) or ABC A–C in ~20–25 min with clean first AC; score decay makes early minutes the most expensive.
- **Stuck timers:** ~5–8 min on A/B with no plan → reread (you misread); ~12–15 min on C with no plan → park, open D/E, return later.
- **Penalty hygiene:** before submit — re-trace samples by hand, `n=1` / empty / all-equal / MAX, and reset *all* multi-test state; one avoided WA beats 5 minutes of “clever” coding.
- **Constraint → algorithm:** `n≤20` brute/subsets, `n≤400` O(n²)/O(n³), `n≤2e5` O(n log n); letter order is a hint, constraints are the truth.
- **Anti-overthink:** if a short observation (parity, `a[1]<a[n]`, residue, “too many ±”) fits samples, code it; do not invent heavy DS on 1400s.
- **Scoring rules:** CF score decay → early easy solves; ICPC/CF ICPC-mode → maximize solves first, then minimize penalty (`time + 10×WA` on solved only — unsolved WA is free).
- **Upsolve rule:** within 24h, solve the *easiest unsolved* with a real solo attempt, then editorial + re-implement from scratch; virtual any missed rated round.

## Where it appears in OAs / interviews

- Timed OA (HackerRank/HackerEarth 60–90 min, 2–4 tasks): same as Div2 — clear the implementation/greedy first, leave the “trick” task for last; wrong attempts can lock or burn score on some platforms.
- “Finish as many as you can” campus assessments: ICPC-style ranking — one more AC always beats polishing penalty on an already-solved easy.
- Take-home / multi-section tests: upsolving meta = after the clock, redo the one you almost had; interviewers often reuse that near-miss as a follow-up.
- Live coding screens with a hard stop: stuck-timer + local edge checks map directly — talk constraints first, ship a correct simple solution before optimizing.
