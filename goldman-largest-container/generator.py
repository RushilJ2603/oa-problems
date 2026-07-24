import sys, random
seed = int(sys.argv[1]) if len(sys.argv) > 1 else random.randrange(1 << 30)
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
random.seed(seed)
n = random.randint(1, min(8, max(1, size)))
print(n)
print(' '.join(str(random.randint(1, 9)) for _ in range(n)))
m = random.randint(0, min(8, n + 3))
print(m)
fp = [random.randint(0, n - 1) for _ in range(m)]
sp = [random.randint(0, n - 1) for _ in range(m)]
sl = [random.randint(0, 2 * n) for _ in range(m)]
print(' '.join(map(str, fp))); print(' '.join(map(str, sp))); print(' '.join(map(str, sl)))
