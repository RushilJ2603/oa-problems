#!/usr/bin/env python3
# Independent parser: pull quoted tokens with a regex (vs the reference's manual scan),
# pair them key,value,key,value,..., then diff the two dicts.
import re
import sys


def parse(s):
    toks = re.findall(r'"([^"]*)"', s)
    return {toks[i]: toks[i + 1] for i in range(0, len(toks) - 1, 2)}


def main():
    lines = sys.stdin.read().split("\n")
    a = lines[0] if len(lines) > 0 else ""
    b = lines[1] if len(lines) > 1 else ""
    da, db = parse(a), parse(b)
    res = sorted(k for k in da if k in db and da[k] != db[k])
    sys.stdout.write("".join(k + "\n" for k in res))


main()
