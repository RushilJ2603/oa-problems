import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
size=int(sys.argv[2]) if len(sys.argv)>2 else 8
random.seed(seed)
n=random.randint(2,max(2,size))
k=random.randint(2,n)
print(n,k)
print(' '.join(str(random.randint(0,random.choice([10,100,1000000000]))) for _ in range(n)))
