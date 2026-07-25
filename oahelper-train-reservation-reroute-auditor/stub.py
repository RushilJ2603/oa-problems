import sys


def solve(M, N, T, events):
    # WRITE YOUR CODE HERE
    # events[i] = ("BOOK", l, r, p) or ("QUERY", l, r)
    # return list of query answers followed by the threshold-event index
    return []


def main():
    raw = sys.stdin.read().replace("\\n", "\n")
    data = raw.split()
    if not data:
        return
    it = iter(data)
    M = int(next(it))
    N = int(next(it))
    T = int(next(it))
    events = []
    for _ in range(N):
        op = next(it)
        if op == "BOOK":
            l = int(next(it))
            r = int(next(it))
            p = int(next(it))
            events.append(("BOOK", l, r, p))
        else:
            l = int(next(it))
            r = int(next(it))
            events.append(("QUERY", l, r))
    for x in solve(M, N, T, events):
        print(x)


if __name__ == "__main__":
    main()
