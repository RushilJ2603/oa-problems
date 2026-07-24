import sys, random
seed = int(sys.argv[1]) if len(sys.argv) > 1 else random.randrange(1 << 30)
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
random.seed(seed)
n = random.randint(1, max(1, size))
m = random.randint(0, max(1, size))
hi = random.choice([5, 20, 1000, 2147483647])
print(n)
print(' '.join(str(random.randint(1, hi)) for _ in range(n)))
print(m)
print(' '.join(str(random.randint(1, hi)) for _ in range(m)))
