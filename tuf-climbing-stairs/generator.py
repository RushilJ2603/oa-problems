import sys, random
seed = int(sys.argv[1]) if len(sys.argv) > 1 else random.randrange(1 << 30)
random.seed(seed)
print(random.randint(1, 45))
