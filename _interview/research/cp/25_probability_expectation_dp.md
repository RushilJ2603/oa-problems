# 25 — Probability & Expectation DP

**Placement value:** Medium (simple probability / “expected count via indicators” shows up in harder OAs; full expectation-DP with self-loops is mainly a CF ~1600–2100 rating skill Striver never covers)
**Prereq topics:** Intro / linear DP, basic probability (independence, conditional), fractions & modular inverse (for `p·q⁻¹ mod M` answers), bitmasks (for subset-alive states), trees DFS (for path / depth expectation)

**Pattern in one paragraph:** Probability DP pushes forward: `dp[state] = Prob(reach state)`, transitions multiply edge probabilities. Expectation DP usually pulls backward from a terminal: `E[s] = 1 + Σ p(s→t)·E[t]` (or rearrange when `t=s` is possible — “geometric wait” / self-loop). Linearity of expectation `E[Σ Xᵢ] = Σ E[Xᵢ]` (no independence needed) turns many “expected count” problems into summing indicator probabilities, often without any DP. Spot it when the statement asks for a probability / expected value under random draws, random walks, random survivors, or “until all done,” and the state space is small (counts, masks, remaining HP, dish multiplicities).

## Ladder (easy -> hard, 24 problems)
- [ ] [Dreamoon and WiFi](https://codeforces.com/problemset/problem/476/B) — `Codeforces` `1300` — count outcomes → probability — Enumerate `?` masks / binomial ways; lightest CF bridge from combinatorics to Prob. **(core)**
- [ ] [Journey](https://atcoder.jp/contests/abc194/tasks/abc194_d) — `AtCoder` `ABC D` — coupon / geometric expectation — Expected steps until all vertices visited via `N/(N−k)` waits; closed-form expectation drill before DP.
- [ ] [Journey](https://codeforces.com/problemset/problem/839/C) — `Codeforces` `1500` — expected path length on tree — DFS: at a node, average child-subtree expectations equally; *the* CF tree-expectation intro. **(core)**
- [ ] [Little Pony and Expected Maximum](https://codeforces.com/problemset/problem/453/A) — `Codeforces` `1600` — E[max of n dice] — Closed form `Σ (iⁿ − (i−1)ⁿ)/mⁿ · i`; teaches CDF → expectation for discrete max. **(core)**
- [ ] [Candy Lottery](https://cses.fi/problemset/task/1727) — `CSES` `Mathematics` — expected maximum — CSES twin of 453A: `E[max] = Σ x·(P(max≤x) − P(max≤x−1))`.
- [ ] [Inversion Probability](https://cses.fi/problemset/task/1728) — `CSES` `Mathematics` — linearity of expectation — **(core)** Sum `P(aᵢ>aⱼ)` over pairs; no DP needed — *the* indicator template.
- [ ] [Dice Probability](https://cses.fi/problemset/task/1725) — `CSES` `Mathematics` — sum-distribution DP — **(core)** `dp[throws][sum]` with fair d6; placement-flavored probability DP.
- [ ] [increment of coins](https://atcoder.jp/contests/abc184/tasks/abc184_d) — `AtCoder` `ABC D` — 3-count expectation DP — **(core)** `E(x,y,z)` until some color hits 100; memoized recursion on coin counts.
- [ ] [Critical Hit](https://atcoder.jp/contests/abc280/tasks/abc280_e) — `AtCoder` `ABC E` — HP expectation + mod inverse — `E[h]` with −1/−2 damage; answer as `P·Q⁻¹ mod 998244353`.
- [ ] [Coins](https://atcoder.jp/contests/dp/tasks/dp_i) — `AtCoder` `Educational DP` — heads-count probability DP — **(core)** AtCoder DP Contest I / USACO-adjacent; `dp[i][j]` = Prob exactly `j` heads after `i` coins.
- [ ] [Ilya and Escalator](https://codeforces.com/problemset/problem/518/D) — `Codeforces` `1700` — queue / Bernoulli DP — **(core)** `dp[t][k]` = Prob `k` people on escalator at time `t`; classic time×count probability DP.
- [ ] [Throwing the Die](https://atcoder.jp/contests/abc266/tasks/abc266_e) — `AtCoder` `ABC E` — optimal-stopping expectation — Decide keep vs reroll to max `E[score]`; expectation + greedy threshold.
- [ ] [Sushi](https://atcoder.jp/contests/dp/tasks/dp_j) — `AtCoder` `Educational DP` — expectation DP with self-loop — **(core)** AtCoder DP Contest J; `E[i][j][k]` on dish multiplicities — rearrange `E = 1 + p₀E + …` to isolate `E`. *The* expectation-DP milestone.
- [ ] [Bag of mice](https://codeforces.com/problemset/problem/148/D) — `Codeforces` `1800` — turn-based draw probability DP — **(core)** OI Wiki classic; `dp[w][b]` = Prob princess wins with `w` white / `b` black left.
- [ ] [Moving Robots](https://cses.fi/problemset/task/1726) — `CSES` `Mathematics` — linearity + walk DP — Per-robot position probs after `k` steps; `E[empty] = Σ P(cell empty)` via independence product.
- [ ] [Fish](https://codeforces.com/problemset/problem/16/E) — `Codeforces` `1900` — bitmask probability DP — **(core)** `dp[mask]` = Prob subset `mask` still alive; pair fights inside the mask.
- [ ] [Bad Luck Island](https://codeforces.com/problemset/problem/540/D) — `Codeforces` `1900` — 3-species probability DP — **(core)** `dp[r][s][p]` survival probs; rock–scissors–paper extinction classic.
- [ ] [Let's Play Osu!](https://codeforces.com/problemset/problem/235/B) — `Codeforces` `2000` — consecutive-ones expectation — Maintain `E[len]` / `E[len²]` under random 0/1 string; contribution of segments. **(stretch)**
- [ ] [Wish I Knew How to Sort](https://codeforces.com/problemset/problem/1753/C) — `Codeforces` `2000` — expected swaps to sort — Random adjacent useful swaps; expectation DP / closed form on inversion structure. **(stretch)**
- [ ] [Beautiful Mirrors](https://codeforces.com/problemset/problem/1265/E) — `Codeforces` `2100` — expected retries + mod inverse — Geometric waits chained through mirrors; elegant `Eᵢ` recurrence mod `998244353`. **(stretch)**
- [ ] [Game on Tree](https://codeforces.com/problemset/problem/280/C) — `Codeforces` `2200` — linearity on tree depths — Famous milestone: `E[ops] = Σ 1/depth(v)`; no heavy DP — pure indicators. **(stretch)**
- [ ] [New Year and Arbitrary Arrangement](https://codeforces.com/problemset/problem/908/D) — `Codeforces` `2200` — expected string build DP — Stop when `ab`-count hits `k`; `dp[a_count][ab_count]` with infinite-process cut. **(stretch)**
- [ ] [Another Sith Tournament](https://codeforces.com/problemset/problem/678/E) — `Codeforces` `2200` — bitmask + probability — Choose fight order / who stays; `dp[mask]` win Prob for subset of Sith. **(stretch)**
- [ ] [Makoto and a Blackboard](https://codeforces.com/problemset/problem/1097/D) — `Codeforces` `2200` — prime-power expectation DP — Factor `n`, independent per prime power; `dp[steps][exp]` expected value after `k` replacements. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- Probability DP (forward): `dp[v] += dp[u] * P(u→v)`; answer is a sum of `dp[terminal]` (or Prob of a property).
- Expectation DP (backward): `E[term]=0`; `E[s] = cost(s) + Σ P(s→t)·E[t]`. If `t=s` allowed, move self-term: `E[s] = (cost + Σ_{t≠s} P·E[t]) / (1−P_self)`.
- Geometric wait: success Prob `p` each trial ⇒ expected trials `1/p` (Sushi empty-dish / coupon phases).
- Linearity / indicators: `E[count] = Σ P(eventᵢ)` even when events are dependent — first tool before writing DP (inversions, empty cells, “node removed directly”).
- Discrete `E[X] = Σ P(X≥k)` (positive integer) and `E[max] = Σ (F(x)ⁿ − F(x−1)ⁿ)·x`.
- Float vs modular: print doubles with `setprecision` + absolute/relative `1e-6…1e-9`; or output `P·Q⁻¹ mod 998244353` / `1e9+7`.
- Bitmask probability: state = alive set / chosen subset; transition enumerates pairs or challengers inside the mask (`n≤20`).
- Always define *whose turn / what remains* in the state; draw boundary cases (`0` of a type, empty bag, already sorted) explicitly.

## Where it appears in OAs / interviews
- “Each of `n` kids rolls `1..k` uniformly; expected maximum candy count” → Candy Lottery / Little Pony Expected Maximum.
- “Array entries uniform in ranges; expected number of inversions / equal pairs” → indicator sum (Inversion Probability style) — common “clever OA math” disguise.
- “Monster HP `n`, each hit deals 1 or 2 with given Prob; expected hits (mod prime)” → Critical Hit–style linear expectation DP.
- “Keep tossing / drawing until every type collected or every plate empty; expected steps” → coupon / Sushi expectation DP with self-loops.
