import sys

def getAssignedCluster(clusters: int, m: int, connections: list[list[int]], q: int, queries: list[list[int]]) -> list[int]:
    # WRITE YOUR CODE HERE
    return []

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    clusters = int(input_data[0])
    m = int(input_data[1])
    
    idx = 2
    connections = []
    for _ in range(m):
        connections.append([int(input_data[idx]), int(input_data[idx+1])])
        idx += 2
        
    q = int(input_data[idx])
    idx += 1
    queries = []
    for _ in range(q):
        queries.append([int(input_data[idx]), int(input_data[idx+1])])
        idx += 2
        
    result = getAssignedCluster(clusters, m, connections, q, queries)
    for ans in result:
        print(ans)

if __name__ == '__main__':
    main()
