import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
size=int(sys.argv[2]) if len(sys.argv)>2 else 7
random.seed(seed)
n=random.randint(1,max(1,size))
m=random.randint(1,n+1)
print(n,m)
print(' '.join(str(random.randint(1,100)) for _ in range(n)))
