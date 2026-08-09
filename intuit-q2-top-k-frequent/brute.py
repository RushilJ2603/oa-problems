"""Independent slow solution: build the frequency table by scanning the whole list once per distinct
tag (O(n * distinct)) and pick the winner k times by a linear max-scan. Deliberately shares no code
path with reference.cpp — no hash counting, no sort, no comparator."""
import sys


def main() -> None:
    data = sys.stdin.read().split()
    n = int(data[0])
    tags = data[1:1 + n]
    k = int(data[1 + n])

    distinct = []
    seen = set()
    for t in tags:
        if t not in seen:
            seen.add(t)
            distinct.append(t)

    counts = []
    for d in distinct:
        c = 0
        for t in tags:
            if t == d:
                c += 1
        counts.append([d, c])

    out = []
    for _ in range(k):
        best = None
        for pair in counts:
            if pair[1] < 0:
                continue
            if best is None or pair[1] > best[1] or (pair[1] == best[1] and pair[0] < best[0]):
                best = pair
        if best is None:
            break
        out.append(best[0])
        best[1] = -1

    print(" ".join(out))


main()
