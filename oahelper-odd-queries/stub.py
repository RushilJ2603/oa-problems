import sys

def solve(N, Q, Arr, queries):
    # WRITE YOUR CODE HERE
    return []

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    T = int(input_data[0])
    idx = 1
    
    out = []
    for _ in range(T):
        N = int(input_data[idx])
        Q = int(input_data[idx+1])
        idx += 2
        
        Arr = []
        for _ in range(N):
            Arr.append(int(input_data[idx]))
            idx += 1
            
        queries = []
        for _ in range(Q):
            queries.append([int(input_data[idx]), int(input_data[idx+1]), int(input_data[idx+2])])
            idx += 3
            
        res = solve(N, Q, Arr, queries)
        out.append(" ".join(map(str, res)))
        
    for row in out:
        sys.stdout.write(f"{row}\n")

if __name__ == '__main__':
    main()
