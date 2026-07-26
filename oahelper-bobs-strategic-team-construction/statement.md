# Bob's Strategic Team Construction

Bob is hiring for a new venture. There are `N` candidates. Candidate `i` asks for salary `salary[i]` and would contribute earnings `earning[i]` to Bob's business.

Bob's total salary budget is at most `M`. He may also strategically influence up to `K` candidates: for each influenced candidate he hires, he pays only `⌊salary[i] / 2⌋` instead of the full salary. Each candidate may be hired at most once (either at full price, at half price using one influence token, or not at all).

Compute the maximum total earnings Bob can achieve without exceeding budget `M`. If he cannot hire anyone, the answer is `0`.

## Input Format

- Line 1: integer `N` — number of candidates
- Line 2: integer `M` — budget
- Line 3: integer `K` — maximum number of half-price hires
- Line 4: `N` space-separated integers `salary[1..N]`
- Line 5: `N` space-separated integers `earning[1..N]`

## Output Format

Print a single integer — the maximum achievable earnings.

## Constraints

- `1 ≤ N, M ≤ 1000`
- `1 ≤ K ≤ 5`
- `1 ≤ salary[i] ≤ 2000`
- `0 ≤ earning[i] ≤ 10^9`

## Examples

### Example 1

**Input**
```
5
15
1
10 10 10 10 10
100 200 300 400 500
```

**Output**
```
900
```

**Explanation**

Influence the last candidate (pay `⌊10/2⌋ = 5`) and hire the fourth at full price (`10`). Total cost `15`, earnings `500 + 400 = 900`.

### Example 2

**Input**
```
1
1
1
2
100
```

**Output**
```
100
```

**Explanation**

With one influence token the candidate costs `⌊2/2⌋ = 1`, which fits the budget.
