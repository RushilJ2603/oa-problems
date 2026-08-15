import sys

def recoverDeadPods(pods: int, connections: list[list[int]], queries: list[list[int]]) -> list[int]:
    # WRITE YOUR CODE HERE
    return []

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    pods = int(next(iterator))
    n = int(next(iterator))
    _ = int(next(iterator)) # dummy 2
    
    connections = []
    for _ in range(n):
        u = int(next(iterator))
        v = int(next(iterator))
        connections.append([u, v])
        
    q = int(next(iterator))
    _ = int(next(iterator)) # dummy 2
    
    queries = []
    for _ in range(q):
        t = int(next(iterator))
        p = int(next(iterator))
        queries.append([t, p])
        
    result = recoverDeadPods(pods, connections, queries)
    if result:
        sys.stdout.write("\n".join(map(str, result)) + "\n")

if __name__ == "__main__":
    solve()
