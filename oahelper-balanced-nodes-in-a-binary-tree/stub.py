import sys

def solve(n: int, root_val: int, edges: list) -> int:
    # WRITE YOUR CODE HERE
    return 0

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    root_val = int(input_data[1])
    edges = []
    idx = 2
    for _ in range(n - 1):
        if idx >= len(input_data):
            break
        path = input_data[idx]
        val = int(input_data[idx+1])
        edges.append((path, val))
        idx += 2
        
    res = solve(n, root_val, edges)
    print(res)

if __name__ == '__main__':
    main()
