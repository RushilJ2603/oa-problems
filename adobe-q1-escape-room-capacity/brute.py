"""Independent solution.

reference.cpp collapses the timeline into +/- deltas and sweeps a running sum. This one does not
sweep anything and never builds an event list: it goes back to the DEFINITION and, for each candidate
instant t, counts everyone whose interval covers t by re-scanning all N shows.

The candidate instants are the start times, and only those. Occupancy is constant between
consecutive events and only ever RISES at a start, so if the room is ever over capacity it is over
capacity at some show's start_time. A show with start == end covers nothing, since `s <= t < e` is
false for every t when s == e — the half-open rule falls out of the comparison instead of out of the
way two deltas happen to cancel.

O(N^2), so above a few thousand shows it switches to an explicit sorted merge of arrivals and
departures — still a different mechanism from the reference's ordered map.
"""
import sys


def by_definition(capacity, shows):
    for t, _, _ in shows:
        inside = 0
        for s, e, a in shows:
            if s <= t < e:
                inside += a
        if inside > capacity:
            return False
    return True


def by_merge(capacity, shows):
    arrivals = sorted((s, a) for s, e, a in shows if s < e)
    departures = sorted((e, a) for s, e, a in shows if s < e)
    i = j = 0
    inside = 0
    while i < len(arrivals):
        # Everyone who leaves at or before the next arrival is out of the room first.
        while j < len(departures) and departures[j][0] <= arrivals[i][0]:
            inside -= departures[j][1]
            j += 1
        t = arrivals[i][0]
        while i < len(arrivals) and arrivals[i][0] == t:
            inside += arrivals[i][1]
            i += 1
        if inside > capacity:
            return False
    return True


def main() -> None:
    data = sys.stdin.buffer.read().split()
    capacity = int(data[0])
    n = int(data[1])
    shows = []
    for i in range(n):
        s, e, a = (int(x) for x in data[2 + 3 * i:5 + 3 * i])
        shows.append((s, e, a))
    ok = by_definition(capacity, shows) if n <= 3000 else by_merge(capacity, shows)
    print("True" if ok else "False")


main()
