"""Independent solution.

reference.cpp walks the bits one at a time and branches on c_i. This one never looks at an
individual bit — it derives the same number as a closed form over whole words:

    answer = popcount(c ^ (a | b))  +  popcount(a & b & ~c)

The first term is "every bit where the OR currently disagrees with c", which charges exactly one
flip to each disagreeing bit. That is already right everywhere except one place: a bit where
c_i = 0 and BOTH a_i and b_i are 1 needs two flips, not one. The second term is precisely the set
of those bits, so it adds the missing second flip.

Two different derivations landing on the same number is the point — a case the per-bit branch got
wrong would show up here as a disagreement rather than being reproduced identically.
"""
import sys

MASK = (1 << 63) - 1


def main() -> None:
    a, b, c = (int(x) for x in sys.stdin.buffer.read().split()[:3])
    disagree = (c ^ (a | b)) & MASK
    both_set_but_wanted_clear = (a & b & ~c) & MASK
    print(bin(disagree).count("1") + bin(both_set_but_wanted_clear).count("1"))


main()
