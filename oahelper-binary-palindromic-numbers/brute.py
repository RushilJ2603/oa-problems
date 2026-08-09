"""Independent solution.

reference.cpp enumerates EVERY binary palindrome once and binary-searches the sorted list. This one
never builds the list: for each bit length it CONSTRUCTS the nearest palindrome of that length
directly, by taking the leading half of n, mirroring it, and nudging the half by +-1. Different
method, so a bug in the enumeration (a missing length, a mis-mirrored odd length, a bad limit) shows
up as a disagreement.

For a fixed length L, the palindrome value increases monotonically with its leading half h, so the
closest one of that length is at h = clamp(n's leading bits) or one either side of it.
"""
import sys


def build(h, L):
    """The length-L palindrome whose leading (L+1)//2 bits are h."""
    half = (L + 1) // 2
    v = h
    for i in range(L - half - 1, -1, -1):
        v = (v << 1) | ((h >> (half - 1 - i)) & 1)
    return v


def nearest_ops(n):
    best = None
    nb = n.bit_length()
    for L in range(1, 35):
        half = (L + 1) // 2
        lo_h = 1 << (half - 1)
        hi_h = (1 << half) - 1
        if L <= nb:
            ideal = n >> (L - half)
        else:
            ideal = lo_h                       # this length is entirely above n
        for h in (ideal - 1, ideal, ideal + 1):
            if h < lo_h or h > hi_h:
                continue
            v = build(h, L)
            if v < 1:
                continue
            d = v - n if v > n else n - v
            if best is None or d < best:
                best = d
    return best


def main() -> None:
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    out = []
    for i in range(1, t + 1):
        out.append(str(nearest_ops(int(data[i]))))
    print("\n".join(out))


main()
