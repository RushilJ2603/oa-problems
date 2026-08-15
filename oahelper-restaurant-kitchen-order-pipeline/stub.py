import sys

def solve(N, S, station, duration, adj, indegree):
    # WRITE YOUR CODE HERE
    return [0] * (N + 1)

def main():
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return
    idx = 0
    N = data[idx]; idx += 1
    S = data[idx]; idx += 1
    
    station = [0] * (N + 1)
    duration = [0] * (N + 1)
    for i in range(1, N + 1):
        station[i] = data[idx]; idx += 1
        duration[i] = data[idx]; idx += 1
        
    M = data[idx]; idx += 1
    adj = [[] for _ in range(N + 1)]
    indegree = [0] * (N + 1)
    for _ in range(M):
        u = data[idx]; idx += 1
        v = data[idx]; idx += 1
        adj[u].append(v)
        indegree[v] += 1
        
    finish = solve(N, S, station, duration, adj, indegree)
    
    makespan = 0
    ans = []
    for i in range(1, N + 1):
        ans.append(str(finish[i]))
        if finish[i] > makespan:
            makespan = finish[i]
            
    print(" ".join(ans))
    print(makespan)

if __name__ == '__main__':
    main()
