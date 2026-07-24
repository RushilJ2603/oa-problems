import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
size=int(sys.argv[2]) if len(sys.argv)>2 else 8
random.seed(seed)
n=random.randint(1,max(1,size))
names=['a','b','c','d']
tasks=[random.choice(names) for _ in range(n)]
ts=random.sample(range(1,10*n+5),n)
lim=[random.randint(1,6) for _ in range(n)]
print(n)
print(' '.join(tasks));print(' '.join(map(str,ts)));print(' '.join(map(str,lim)))
