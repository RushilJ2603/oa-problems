import sys

def solve(n, m, edges):
    # WRITE YOUR CODE HERE
    return 0

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    m = int(input_data[1])
    edges = []
    idx = 2
    for _ in range(m):
        edges.append([int(input_data[idx]), int(input_data[idx+1])])
        idx += 2
    print(solve(n, m, edges))

if __name__ == '__main__':
    main()
