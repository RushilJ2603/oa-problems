"""Independent solution.

reference.cpp walks the string index by index and asks "does a digit start here?". This one never
walks the string at all: it hands the whole query to a single regular expression whose alternatives
sit inside a ZERO-WIDTH LOOKAHEAD

    (?=(\\d|one|two|...|nine))

so the regex engine consumes nothing as it scans. Every match position is reported, including
positions inside a word that already matched — which is the overlap rule ("eightwothree" -> 8,2,3)
expressed as a property of the pattern instead of as a hand-written "i += 1".

A plain re.findall WITHOUT the lookahead consumes each match and would silently miss the second
digit of every overlapping pair, so the two solutions disagree exactly where the interesting bug is.
"""
import re
import sys

WORDS = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
VALUE = {w: i + 1 for i, w in enumerate(WORDS)}
PAT = re.compile(r"(?=(\d|" + "|".join(WORDS) + r"))")


def main() -> None:
    data = sys.stdin.buffer.read().decode().split()
    n = int(data[0])
    total = 0
    for q in data[1:1 + n]:
        hits = PAT.findall(q)
        if not hits:
            continue
        digits = [VALUE[h] if h in VALUE else int(h) for h in hits]
        total += 10 * digits[0] + digits[-1]
    print(total)


main()
