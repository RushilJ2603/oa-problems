import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
random.seed(seed)
nc=random.randint(1,20)
fd=random.randint(0,20);ld=fd+random.randint(0,20)
print(nc,fd,ld)
