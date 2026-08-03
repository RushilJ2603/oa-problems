#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size <= 5:
        n = random.randint(1, 3)
    elif size <= 20:
        n = random.randint(3, 6)
    elif size <= 80:
        n = random.randint(6, 10)
    elif size <= 200:
        n = random.randint(10, 14)
    else:
        n = 18  # MAX-SCALE

    k = random.randint(1, n)
    # Mix cost regimes so wrong algorithms (direct edges only, undirected, etc.) diverge.
    mode = random.choice(["uniform", "asymmetric", "triangle_break", "sparse_cheap"])
    mat = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if i == j:
                continue
            if mode == "uniform":
                mat[i][j] = random.randint(0, 1000)
            elif mode == "asymmetric":
                mat[i][j] = random.randint(0, 10**5)
            elif mode == "triangle_break":
                # Often cheaper via an intermediate than the direct edge.
                mat[i][j] = random.randint(500, 10**5)
            else:
                mat[i][j] = random.randint(1, 10**5) if random.random() < 0.7 else random.randint(0, 20)

    if mode == "triangle_break" and n >= 3:
        # Plant a cheap 2-hop that beats the direct edge.
        a, b, c = 0, 1, 2
        mat[a][b] = random.randint(1, 10)
        mat[b][c] = random.randint(1, 10)
        mat[a][c] = mat[a][b] + mat[b][c] + random.randint(50, 500)

    print(n, k)
    for row in mat:
        print(" ".join(map(str, row)))

if __name__ == "__main__":
    main()
