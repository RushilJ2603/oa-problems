import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    n = size
    if n > 10000:
        n = 10000
    if n < 1:
        n = 1
        
    print(n)
    
    # ensure it hits bounds
    arr = []
    if size >= 10000:
        # max scale case
        for i in range(n):
            if random.random() < 0.1:
                arr.append(1023)
            elif random.random() < 0.1:
                arr.append(1)
            else:
                arr.append(random.randint(1, 1023))
    elif size >= 100:
        # medium values
        for _ in range(n):
            arr.append(random.randint(1, 1023))
    else:
        for _ in range(n):
            arr.append(random.randint(1, 20))
            
    for x in arr:
        print(x)

if __name__ == '__main__':
    main()
