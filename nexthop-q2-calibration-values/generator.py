"""One random valid input for Calibration Values.

usage: python3 generator.py [seed] [size]

Queries made of uniform random characters are almost useless here: a spelled word essentially never
appears by chance, so such a test only ever exercises the digit-character path and a solution that
ignores words entirely would pass. Every shape below therefore plants word occurrences on purpose,
and one of them plants nothing but the OVERLAPPING pairs ("oneight", "twone", ...) that a
replace-as-you-go solution gets wrong.

`size` is the number of queries; when that gets large the per-query length shrinks so the total
stays inside the 10^6 character budget.
"""
import random
import sys

WORDS = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
VALUE = {w: i + 1 for i, w in enumerate(WORDS)}
# Pairs that share letters: reading one of them must not hide the other.
GLUE = ["oneight", "twone", "threeight", "fiveight", "sevenine", "eightwo", "eighthree", "nineight"]
# Near misses — prefixes and suffixes that are NOT digits, to punish a loose substring check.
DECOY = ["on", "ne", "tw", "wo", "thre", "hree", "fou", "our", "fiv", "ive", "si", "ix",
         "seve", "even", "eigh", "ight", "nin", "ine", "eno", "owt", "xis", "evif"]
ALPHA = "abcdefghijklmnopqrstuvwxyz"
DIGITS = "0123456789"

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
rng = random.Random(seed)

n = max(1, min(200000, size))
maxlen = max(1, min(50, 1000000 // n))


def has_digit(s):
    """Exactly the problem's rule — used only to guarantee the constraint, never to solve."""
    for i, ch in enumerate(s):
        if ch in DIGITS:
            return True
        for w in WORDS:
            if s.startswith(w, i):
                return True
    return False


def build(shape, limit):
    parts = []
    total = 0

    def push(p):
        nonlocal total
        if total + len(p) <= limit:
            parts.append(p)
            total += len(p)
            return True
        return False

    if shape == "digits":
        while push(rng.choice(DIGITS)):
            if rng.random() < 0.15:
                break
    elif shape == "words":
        while push(rng.choice(WORDS)):
            if rng.random() < 0.25:
                break
    elif shape == "glued":
        while push(rng.choice(GLUE)):
            if rng.random() < 0.4:
                break
    elif shape == "decoy":
        # Near-miss fragments only, plus a single real digit somewhere inside.
        while push(rng.choice(DECOY)):
            if rng.random() < 0.3:
                break
        if parts:
            parts.insert(rng.randrange(len(parts) + 1), rng.choice(DIGITS))
    elif shape == "noise":
        while push(rng.choice(ALPHA)):
            if rng.random() < 0.1:
                break
        if parts:
            parts.insert(rng.randrange(len(parts) + 1), rng.choice(DIGITS))
    else:  # "mixed" — the general case: words, glue, digits and letters interleaved
        while True:
            r = rng.random()
            if r < 0.3:
                p = rng.choice(WORDS)
            elif r < 0.45:
                p = rng.choice(GLUE)
            elif r < 0.65:
                p = rng.choice(DIGITS)
            elif r < 0.8:
                p = rng.choice(DECOY)
            else:
                p = rng.choice(ALPHA)
            if not push(p):
                break
            if rng.random() < 0.2:
                break

    s = "".join(parts)[:limit]
    if not s:
        s = rng.choice(DIGITS)
    if not has_digit(s):
        # Constraint: every query has at least one digit. Overwrite the last character rather than
        # appending, so the length limit still holds.
        s = s[:-1] + rng.choice(DIGITS)
    return s


shapes = ["mixed", "mixed", "digits", "words", "glued", "glued", "decoy", "noise"]
# Sometimes the whole test is one shape, so a suite can contain an all-overlap case.
fixed = rng.choice(shapes) if rng.random() < 0.35 else None

out = [str(n)]
for _ in range(n):
    shape = fixed if fixed else rng.choice(shapes)
    limit = rng.randint(1, maxlen) if maxlen > 1 else 1
    out.append(build(shape, limit))

sys.stdout.write("\n".join(out) + "\n")
