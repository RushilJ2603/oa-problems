"""Independent solution.

reference.cpp answers the question as asked: try every placement, measure the worst plot, keep the
best worst. It never asks "is d achievable?" — it computes the answer directly and the minimum falls
out of the enumeration.

This one inverts the problem into a DECISION and searches differently. For d = 0, 1, 2, … it asks
"can n offices put every plot within d?" — which is set cover. Each plot gets a bitmask of the plots
it would serve at radius d, and the search always branches on the FIRST plot still uncovered, trying
only the offices that would cover it. The first d that succeeds is the answer, because coverage is
monotone in d.

Nothing is shared with the reference: different question, different search order, different pruning,
and the answer arrives from below rather than from above.
"""
import sys


def solve(h, w, n):
    cells = h * w
    full = (1 << cells) - 1
    coords = [(c // w, c % w) for c in range(cells)]

    for d in range(h + w):          # h-1 + w-1 is the largest distance in the grid
        serves = []
        for r0, c0 in coords:
            m = 0
            for idx, (r1, c1) in enumerate(coords):
                if abs(r0 - r1) + abs(c0 - c1) <= d:
                    m |= 1 << idx
            serves.append(m)

        def cover(covered, left):
            if covered == full:
                return True
            if left == 0:
                return False
            # Branch on the first plot nobody serves yet: some office must be within d of it, so
            # only those placements are worth trying.
            missing = (~covered) & full
            first = (missing & -missing).bit_length() - 1
            for cand in range(cells):
                if serves[cand] >> first & 1:
                    if cover(covered | serves[cand], left - 1):
                        return True
            return False

        if cover(0, n):
            return d
    return h + w                     # unreachable: d = h+w-2 always covers everything


def main() -> None:
    h, w, n = (int(x) for x in sys.stdin.read().split()[:3])
    print(solve(h, w, n))


main()
