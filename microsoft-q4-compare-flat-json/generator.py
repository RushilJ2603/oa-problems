#!/usr/bin/env python3
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
random.seed(seed)

KEY = "abcdefghijk"          # small pool -> keys overlap between the two objects
VAL = "abcABC012:,{}"        # values may include : , { } but never " (stresses the scanner)


def rstr(maxlen, alphabet):
    return ''.join(random.choice(alphabet) for _ in range(random.randint(1, maxlen)))


def build(n):
    d = {}
    guard = 0
    while len(d) < n and guard < n * 50:
        d[rstr(3, KEY)] = rstr(4, VAL)
        guard += 1
    return d


def dump(d):
    return '{' + ','.join(f'"{k}":"{v}"' for k, v in d.items()) + '}'


n1 = random.randint(1, max(1, size))
n2 = random.randint(1, max(1, size))
print(dump(build(n1)))
print(dump(build(n2)))
