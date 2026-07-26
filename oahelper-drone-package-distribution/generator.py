#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size to N; at large size hit the constraint bound.
    if size >= 400:
        N = 100000
    elif size >= 150:
        N = 5000
    elif size >= 40:
        N = 200
    elif size >= 10:
        N = 30
    else:
        N = max(1, size)

    totalZones = random.randint(1, min(100000, max(1, N)))
    # Vary capacities: sometimes tight, sometimes loose.
    mode = seed % 5
    if mode == 0:
        maxPackages = 1
        maxWeight = random.randint(1, 10)
    elif mode == 1:
        maxPackages = random.randint(1, min(10, N))
        maxWeight = random.randint(1, 20)
    elif mode == 2:
        maxPackages = min(N, 100000)
        maxWeight = 100000
    elif mode == 3:
        maxPackages = random.randint(2, min(50, max(2, N)))
        maxWeight = random.randint(5, 100)
    else:
        maxPackages = random.randint(1, min(1000, N))
        maxWeight = random.randint(1, 1000)

    print(N)
    for i in range(N):
        if mode == 2:
            zone = 1 + (i % max(1, min(totalZones, 5)))
        elif mode == 0:
            zone = random.randint(1, totalZones)
        else:
            # clustered zones with occasional switches
            if i == 0 or random.random() < 0.3:
                zone = random.randint(1, totalZones)
            else:
                zone = prev
        prev = zone
        weight = random.randint(1, maxWeight)
        print(zone, weight)
    print(totalZones)
    print(maxPackages)
    print(maxWeight)

if __name__ == "__main__":
    main()
