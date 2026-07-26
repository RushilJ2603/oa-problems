#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 3:
        n = random.randint(1, 5)
    elif size <= 10:
        n = random.randint(6, 20)
    elif size <= 40:
        n = random.randint(21, 80)
    elif size <= 150:
        n = random.randint(100, 500)
    elif size <= 400:
        n = random.randint(1000, 5000)
    else:
        n = 100000

    mode = seed % 6
    used = set()
    used_list = []
    ops = []
    next_seq = 0

    def fresh_coord():
        nonlocal next_seq
        if n >= 10000:
            # dense unique coords without collision retries
            x = next_seq
            next_seq += 1
            if mode == 1:
                x = -10**9 + x
            elif mode == 2:
                x = 10**9 - n + x
            elif mode == 4:
                x = -n // 2 + x
            return x
        for _ in range(64):
            if mode == 0:
                x = random.randint(-10**6, 10**6)
            elif mode == 1:
                x = random.randint(-10**9, -10**9 + 10**6)
            elif mode == 2:
                x = random.randint(10**9 - 10**6, 10**9)
            elif mode == 3:
                x = random.randint(-1000, 1000)
            elif mode == 4:
                x = random.randint(-10**9, 10**9)
            else:
                x = random.randint(-10**5, 10**5)
            if x not in used:
                return x
        base = random.randint(-10**9, 10**9 - n - 1)
        x = base
        while x in used:
            x += 1
        return x

    for i in range(n):
        if not used:
            want_query = (random.random() < 0.25)
        else:
            want_query = random.random() < (0.55 if mode % 2 == 0 else 0.45)

        if want_query:
            if used_list and mode in (1, 2, 3):
                pivot = used_list[random.randrange(len(used_list))]
                size_v = random.randint(1, 10**6) if n < 10000 else random.randint(1, 1000)
                x = pivot + random.randint(0, min(size_v, 100))
            else:
                if n >= 10000 and used_list:
                    pivot = used_list[random.randrange(len(used_list))]
                    x = pivot + random.randint(1, 50)
                    size_v = random.randint(1, 100)
                else:
                    x = random.randint(-10**9, 10**9)
                    if mode == 3:
                        size_v = random.randint(1, 2000)
                    elif mode == 5:
                        size_v = random.choice([1, 2, 10, 10**9])
                    else:
                        size_v = random.randint(1, 10**9)
            ops.append((2, x, size_v))
        else:
            x = fresh_coord()
            used.add(x)
            used_list.append(x)
            ops.append((1, x))

    if not any(op[0] == 2 for op in ops):
        x = random.randint(-10**9, 10**9)
        ops[-1] = (2, x, random.randint(1, 10**9))

    out_lines = [str(n)]
    for op in ops:
        if op[0] == 1:
            out_lines.append(f"1 {op[1]}")
        else:
            out_lines.append(f"2 {op[1]} {op[2]}")
    sys.stdout.write("\n".join(out_lines) + "\n")

if __name__ == "__main__":
    main()
