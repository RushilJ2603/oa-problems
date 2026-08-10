# Minimum Flips to Make a OR b Equal to c

## The observation that makes it easy

Flipping bit `i` of `a` changes bit `i` of `a | b` **and nothing else**. There is no carry, no
borrow, no interaction between positions. So the problem is not one problem over 60-bit numbers —
it is 60 completely independent one-bit problems, and the answer is their sum. Once you see that,
there is nothing left to search.

For a single bit position there are exactly two situations:

| `c_i` | requirement | cost |
|---|---|---|
| `1` | `a_i \| b_i` must be `1` | `0` if either bit is already set, else `1` (turn **one** of them on) |
| `0` | `a_i \| b_i` must be `0`, i.e. **both** must be `0` | `a_i + b_i` — so `0`, `1`, or `2` |

That table *is* the solution:

```cpp
while (a || b || c) {                  // stop when nothing is left in ANY of the three
    int ai = a & 1, bi = b & 1, ci = c & 1;
    if (ci) { if (!ai && !bi) flips += 1; }
    else    { flips += ai + bi; }
    a >>= 1; b >>= 1; c >>= 1;
}
```

`O(60)` time, `O(1)` space. Consuming the low bit and shifting is worth preferring over
`for (int i = 0; i < 60; i++)`: the loop bound stops being a magic number you have to keep in sync
with the constraints, and the `||` is a real condition — `while (a && b && c)` stops the moment any
one of them runs out and silently drops the rest, which a fixed bound would have hidden.

## The three traps

**1. Charging one flip when `c_i = 0` and both bits are set.** This is the only position that costs
**two**, and it is the single most common wrong answer. It is easy to write the loop as "count the
positions where the OR disagrees with `c`" — which is one flip per disagreeing bit — and that
undercounts precisely here. `edge/09` (`1 1 0`, answer `2`) is the minimal instance; `edge/03`
(`2^60-1, 2^60-1, 0`) is the same bug amplified to a 60× gap: `120` versus `60`.

**2. Flipping both bits when `c_i = 1` and neither is set.** The mirror mistake. The OR only needs
*one* of the two to be on, so turning both on wastes a flip. Overcounting here is caught by
`edge/04` (`0 0, 2^60-1`, answer `60`, not `120`).

**3. Using `int`.** `a`, `b` and `c` go up to `2^60 - 1`. Reading them into a 32-bit `int`, or
writing `1 << i` instead of `1LL << i` when `i >= 31`, is undefined behaviour and typically returns
garbage for the high bits while looking perfectly fine on the samples. `edge/06`
(`2147483648 2147483648 0`) is bit 31 alone and `edge/07` straddles the 32/33-bit boundary; both
exist to fail a 32-bit solution that passes everything smaller.

## A closed form (what `brute.py` uses)

The per-bit table collapses into two population counts, with no loop over bits at all:

```
answer = popcount(c ^ (a | b))  +  popcount(a & b & ~c)
```

The first term charges one flip to every bit where the OR currently disagrees with `c`. That is
correct everywhere **except** trap 1 — the bits where `c_i = 0` and both `a_i` and `b_i` are set,
which need a second flip. `a & b & ~c` is exactly that set of bits, so the second term supplies the
missing flip. The two terms are the two traps, written down.

It is worth deriving both forms: the loop is what you write in an interview, and the identity is
the proof that the loop's branch is complete.

## Complexity

- Time `O(1)` — 60 bit positions, or two `popcount` instructions.
- Space `O(1)`.
