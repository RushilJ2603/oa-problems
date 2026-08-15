import sys

def solve(n: int, m: int, maxTime: int, fee: list[int], edges: list[list[int]], src: int, dest: int) -> int:
    # WRITE YOUR CODE HERE
    return 0

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    m = int(input_data[1])
    maxTime = int(input_data[2])
    
    fee = []
    idx = 3
    for _ in range(n):
        fee.append(int(input_data[idx]))
        idx += 1
        
    edges = []
    for _ in range(m):
        u = int(input_data[idx])
        v = int(input_data[idx+1])
        t = int(input_data[idx+2])
        edges.append([u, v, t])
        idx += 3
        
    src = int(input_data[idx])
    dest = int(input_data[idx+1])
    
    res = solve(n, m, maxTime, fee, edges, src, dest)
    print(res)

if __name__ == '__main__':
    main()
