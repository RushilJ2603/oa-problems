import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
size=int(sys.argv[2]) if len(sys.argv)>2 else 8
random.seed(seed)
n=random.randint(1,max(1,size))
print(n)
print(' '.join(str(random.randint(-20,20)) for _ in range(n)))
