import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
size=int(sys.argv[2]) if len(sys.argv)>2 else 8
random.seed(seed)
n=random.randint(1,max(1,size));k=random.randint(0,12)
print(n);print(k)
hi=random.choice([5,1000000000])
print(' '.join(str(random.randint(-hi,hi)) for _ in range(n)))
