# Binary Palindromic Numbers

## Counting before coding

The instinct is to walk outward from `N` — check `N`, then `N-1` and `N+1`, then `N-2` and `N+2` —
until something is a palindrome. It is correct, and at `N <= 2·10^9` with `T` up to `10^5` it is far
too slow: the widest gap between neighbouring binary palindromes below `2·10^9` puts the worst `N`
**24,576** steps from the nearest one (that `N` is `536895489`, and it is `tests/edge/04.in`). At
`10^5` queries that is billions of palindrome checks.

The fix comes from counting how many palindromes there even are. A binary palindrome of length `L`
is completely determined by its leading `ceil(L/2)` bits, and its leading bit must be `1` (no leading
zeros are allowed). So there are exactly `2^(ceil(L/2) - 1)` palindromes of length `L`, and summing
over `L <= 34` gives **262,142** of them in total.

That is a small list. Build it once, sort it, and every query becomes a binary search for the two
neighbours of `N`:

```
answer = min( first palindrome >= N  -  N ,  N - last palindrome <= N )
```

Total cost `O(P log P + T log P)` with `P ≈ 2.6·10^5`. The max-scale tests run in 0.07s.

## Building the list correctly

Mirror the leading half onto the trailing half, and be careful that **odd lengths do not duplicate
the middle bit**. With `half = (L + 1) / 2`, the palindrome is the half followed by `L - half`
mirrored bits — for odd `L` that is one fewer than `half`, which is exactly what stops the centre
bit being written twice.

Two boundary details that quietly break implementations:

- **Iterate `h` from `2^(half-1)`, not from `0`.** Starting at zero generates numbers with leading
  zeros, which the problem forbids, and which would let `10` claim to be the palindrome `0101`.
- **Build past the input ceiling.** `N` can be `2·10^9`, and the nearest palindrome *above* it may be
  larger than `2^31`. Capping generation at the input limit removes the upper neighbour and produces
  a wrong answer for the largest inputs. The reference builds to `2^34` for headroom.

## The constructive alternative

You do not have to store the list. For each length `L`, the palindrome's value is monotonically
increasing in its leading half `h`, so the nearest one of that length comes from taking `N`'s own
leading bits as `h`, clamping into `[2^(half-1), 2^half - 1]`, and testing `h-1`, `h`, `h+1`. Thirty-
four lengths times three candidates is about a hundred constructions per query and no memory at all.

That is what `brute.py` does — deliberately, so the cross-check does not share the enumeration it is
supposed to be checking. Both agree across a full sweep of `1..200000` and 20,000 random values.

## Complexity

| Approach | Time | Verdict |
|---|---|---|
| Walk outward from `N` | up to `24576` checks per query | TLE at `T = 10^5` |
| **Enumerate + binary search** | **`O(P log P + T log P)`** | **intended** |
| Construct per length | `O(T · 34 · 3)` | equally good, no memory |
