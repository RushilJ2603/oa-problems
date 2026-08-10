"""One random valid input for Escape Room Capacity.

usage: python3 generator.py [seed] [size]

The answer is a single bit, so a careless generator is worse than useless here: draw the capacity
independently of the shows and nearly every instance comes out False (any decent overlap blows past
a random capacity), and a suite of 200 tests that all answer False is passed by `return false`.

So this generator builds the shows first, measures their true peak occupancy, and then sets the
capacity RELATIVE to that peak — at it, one below it, or somewhere above. That keeps True and False
roughly balanced and, more importantly, puts most instances exactly on the `peak <= capacity`
boundary, where an off-by-one or a `>=`/`>` slip is the difference between the two answers.

`size` is the number of shows; the time axis and the attendee counts scale with it too, so a large
size reaches the 10^14 running total that needs 64 bits.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
rng = random.Random(seed)

n = max(1, min(100000, size))
# Small time span -> heavy overlap; large span -> mostly disjoint. Both matter.
span = rng.choice([2, 5, 20, max(2, n), max(2, 4 * n), 10 ** 9])
big = rng.random() < 0.3          # push attendees to the 10^9 end to force a 64-bit accumulator
amax = 10 ** 9 if big else rng.choice([0, 1, 5, 100, 10 ** 6])

shape = rng.choice(["random", "random", "nested", "chain", "same_start", "point", "spread"])

shows = []
if shape == "nested":
    lo, hi = 0, min(10 ** 9, span)
    for _ in range(n):
        if hi - lo >= 2:
            lo += rng.randint(0, 1)
            hi -= rng.randint(0, 1)
        shows.append((lo, max(lo, hi), rng.randint(0, amax)))
elif shape == "chain":
    # Back to back: each show ends exactly where the next begins, so nothing ever overlaps and the
    # peak is the largest single show. A solution that lets an ending and a starting show coexist
    # gets these wrong and only these.
    t = rng.randint(0, 10)
    for _ in range(n):
        d = rng.randint(0, 3)
        shows.append((t, t + d, rng.randint(0, amax)))
        t += d
elif shape == "same_start":
    t = rng.randint(0, max(0, min(10 ** 9 - 1, span)))
    for _ in range(n):
        shows.append((t, t + rng.randint(1, 3), rng.randint(0, amax)))
elif shape == "point":
    # Zero-length shows occupy the room for no time and must never count.
    for _ in range(n):
        t = rng.randint(0, min(10 ** 9, span))
        if rng.random() < 0.6:
            shows.append((t, t, rng.randint(0, amax)))
        else:
            shows.append((t, min(10 ** 9, t + rng.randint(1, 4)), rng.randint(0, amax)))
elif shape == "spread":
    for _ in range(n):
        s = rng.randint(0, 10 ** 9 - 1)
        shows.append((s, min(10 ** 9, s + rng.randint(0, 2)), rng.randint(0, amax)))
else:
    for _ in range(n):
        s = rng.randint(0, min(10 ** 9, span))
        e = min(10 ** 9, s + rng.randint(0, max(1, span // 2)))
        shows.append((s, e, rng.randint(0, amax)))

# True peak occupancy, so the capacity can be placed on the boundary rather than at random.
delta = {}
for s, e, a in shows:
    delta[s] = delta.get(s, 0) + a
    delta[e] = delta.get(e, 0) - a
peak = 0
run = 0
for t in sorted(delta):
    run += delta[t]
    peak = max(peak, run)

choice = rng.random()
if choice < 0.35:
    capacity = peak                                   # exactly enough -> True
elif choice < 0.7:
    capacity = max(0, peak - 1)                       # one short -> False (unless peak was 0)
elif choice < 0.85:
    capacity = min(10 ** 9, peak + rng.randint(1, 5))  # a little slack -> True
else:
    capacity = rng.randint(0, 10 ** 9)                # unrelated

print(capacity)
print(n)
out = []
for s, e, a in shows:
    out.append("%d %d %d" % (s, e, a))
sys.stdout.write("\n".join(out) + "\n")
