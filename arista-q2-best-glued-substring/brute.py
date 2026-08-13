"""Independent solution.

reference.cpp never measures a single overlap directly. It decomposes: the seam on the left depends
only on where the piece STARTS, the seam on the right only on where it ENDS, and each is capped by
the piece's length — so two Z-functions give every overlap at once and the answer falls out of an
O(n^2) scan over (start, end). That decomposition is the whole idea, and if it is wrong it is wrong
silently.

This one does not believe it. For every substring it slides the two strings together character by
character and asks the literal question — "do these k characters match?" — with no arrays shared
between one substring and the next, and it compares candidates with plain Python string comparison
instead of a precomputed LCP table. O(n^3)-ish, so it only runs on small inputs.

Above a couple of hundred characters it would take minutes, so it falls back to per-position overlap
arrays built with str.endswith / str.startswith. That shares the decomposition with the reference
and is therefore a weaker check — it exists so the large random cases are covered at all, not to
validate the idea. The idea is validated by the small cases, which are the ones the generator
produces in bulk.
"""
import sys


def overlap(x, y):
    """Longest k such that the last k characters of x equal the first k characters of y."""
    for k in range(min(len(x), len(y)), 0, -1):
        if x[len(x) - k:] == y[:k]:
            return k
    return 0


def by_definition(s, p, q):
    best_score, best = -1, None
    for i in range(len(s)):
        for j in range(i + 1, len(s) + 1):
            t = s[i:j]
            sc = overlap(p, t) + overlap(t, q)
            if sc > best_score or (sc == best_score and t < best):
                best_score, best = sc, t
    return best


def by_arrays(s, p, q):
    """Same answer, reached without enumerating every substring's overlap from scratch.

    Note what is NOT done here: no capping. `valid_p[i]` is the SET of overlap lengths that work at
    start i, and the score for a piece of length L is the largest member that is <= L. The largest
    member overall, capped at L, is a different and wrong number — k-1 valid does not follow from k
    valid.
    """
    n, np_, nq = len(s), len(p), len(q)
    valid_p = [set() for _ in range(n)]
    for i in range(n):
        for k in range(1, min(np_, n - i) + 1):
            if p.endswith(s[i:i + k]):
                valid_p[i].add(k)
    valid_q = [set() for _ in range(n + 1)]
    for j in range(1, n + 1):
        for k in range(1, min(nq, j) + 1):
            if q.startswith(s[j - k:j]):
                valid_q[j].add(k)
    best_score, best = -1, None
    for i in range(n):
        pfx = 0
        for j in range(i + 1, n + 1):
            L = j - i
            if L in valid_p[i]:
                pfx = L
            sfx = max((k for k in valid_q[j] if k <= L), default=0)
            sc = pfx + sfx
            t = s[i:j]
            if sc > best_score or (sc == best_score and t < best):
                best_score, best = sc, t
    return best


def main() -> None:
    data = sys.stdin.read().split()
    s, p, q = data[0], data[1], data[2]
    print(by_definition(s, p, q) if len(s) <= 200 else by_arrays(s, p, q))


main()
