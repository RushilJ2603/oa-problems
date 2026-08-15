import sys

def solve(N: int, M: int, K: int, roads: list[list[int]], bridges: list[list[int]]) -> int:
    # WRITE YOUR CODE HERE
    pass

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    N = int(input_data[0])
    M = int(input_data[1])
    K = int(input_data[2])
    
    idx = 3
    roads = []
    for _ in range(M):
        roads.append([int(input_data[idx]), int(input_data[idx+1]), int(input_data[idx+2])])
        idx += 3
        
    bridges = []
    for _ in range(K):
        bridges.append([int(input_data[idx]), int(input_data[idx+1])])
        idx += 2
        
    print(solve(N, M, K, roads, bridges))

if __name__ == '__main__':
    main()
