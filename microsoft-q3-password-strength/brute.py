#!/usr/bin/env python3
# Independent implementation using set-subset checks (not the reference's per-char flags).
# NOTE: deliberately does NOT use str.isupper()/isdigit(), whose semantics ("all *cased*
# chars are upper", "all chars are digits & nonempty") differ from the rule that EVERY
# character must be an uppercase/lowercase letter or a digit.
import sys

DIG = set("0123456789")
UP = set("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
LO = set("abcdefghijklmnopqrstuvwxyz")


def weak(pw, commons):
    if len(pw) < 6:
        return True
    chars = set(pw)
    if chars <= DIG or chars <= UP or chars <= LO:
        return True
    return any(w in pw for w in commons)


def main():
    data = sys.stdin.read().split("\n")
    pos = 0
    n = int(data[pos]); pos += 1
    passwords = data[pos:pos + n]; pos += n
    c = int(data[pos]); pos += 1
    commons = data[pos:pos + c]; pos += c
    print("\n".join("weak" if weak(p, commons) else "strong" for p in passwords))


main()
