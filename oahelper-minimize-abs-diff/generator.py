import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
size=int(sys.argv[2]) if len(sys.argv)>2 else 10
random.seed(seed)
n=random.randint(2,max(2,size));k=random.randint(1,n-1)
print(n,k)
hi=random.choice([5,1000,1000000000])
print(' '.join(str(random.randint(-hi,hi)) for _ in range(n)))
