#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Cap |plan| for non-max sizes so the exponential set-enumeration brute
    # finishes on gate random cross-checks (sizes up to 120). Large size => MAX.
    if size <= 5:
        m = random.randint(1, 4)
        n = random.randint(1, 4)
    elif size <= 20:
        m = random.randint(3, 8)
        n = random.randint(2, 8)
    elif size <= 80:
        m = random.randint(6, 10)
        n = random.randint(4, 15)
    elif size <= 200:
        m = random.randint(8, 12)
        n = random.randint(8, 30)
    else:
        m = 1000   # MAX-SCALE |plan|
        n = 2500   # MAX-SCALE upper bound

    plan = "".join(random.choice("lr") for _ in range(m))
    start = random.randint(0, n)
    end = random.randint(0, n)
    print(plan)
    print(n)
    print(start)
    print(end)

if __name__ == "__main__":
    main()
