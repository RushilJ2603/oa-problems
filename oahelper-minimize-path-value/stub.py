import sys

def solve(n: int, m: int, u: list[int], v: list[int], w: list[int], src: int, dest: int) -> int:
    # WRITE YOUR CODE HERE
    return 0

def main():
    input_data = sys.stdin.read().split()
    if not input_data: return
    n = int(input_data[0])
    m = int(input_data[1])
    u, v, w = [0]*m, [0]*m, [0]*m
    idx = 2
    for i in range(m):
        u[i] = int(input_data[idx])
        v[i] = int(input_data[idx+1])
        w[i] = int(input_data[idx+2])
        idx += 3
    src = int(input_data[idx])
    dest = int(input_data[idx+1])
    print(solve(n, m, u, v, w, src, dest))

if __name__ == '__main__':
    main()
