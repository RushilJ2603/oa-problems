"""Independent solution.

reference.cpp never restarts: one right pointer sweeps the queue once and the count of distinct
talents is repaired incrementally as the left end moves. That is an argument about monotonicity, and
if the argument is wrong the sweep is wrong everywhere at once.

This one makes no such argument. For every start i it walks forward from scratch, dropping talents
into a fresh set and stopping the moment the set is full — the definition read literally, with no
state shared between one start and the next. O(n^2), which is exactly why it only runs on small
inputs.

Above a few thousand students it switches to a third mechanism rather than timing out: NEXT
OCCURRENCES, scanned right to left. Starting at i, the group has to reach the farthest of the
talents' next occurrences, so ans[i] = max(next[t]) - i + 1 once every talent still has one. The
running maximum comes off a lazy heap. No window, no left pointer, nothing in common with either of
the others.
"""
import heapq
import sys


def by_definition(n, k, talent):
    ans = []
    for i in range(n):
        have = set()
        length = -1
        for j in range(i, n):
            have.add(talent[j])
            if len(have) == k:
                length = j - i + 1
                break
        ans.append(length)
    return ans


def by_next_occurrence(n, k, talent):
    nxt = [-1] * (k + 1)       # nxt[t] = smallest index >= i holding talent t, -1 if none
    missing = k                # talents with no occurrence at or after i
    ans = [-1] * n
    heap = []                  # (-index, talent); stale entries are discarded on inspection
    for i in range(n - 1, -1, -1):
        t = talent[i]
        if nxt[t] == -1:
            missing -= 1
        nxt[t] = i
        heapq.heappush(heap, (-i, t))
        if missing == 0:
            while nxt[heap[0][1]] != -heap[0][0]:
                heapq.heappop(heap)
            ans[i] = -heap[0][0] - i + 1
    return ans


def main() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    k = int(data[1])
    talent = [int(x) for x in data[2:2 + n]]
    ans = by_definition(n, k, talent) if n <= 3000 else by_next_occurrence(n, k, talent)
    sys.stdout.write(" ".join(str(x) for x in ans) + "\n")


main()
