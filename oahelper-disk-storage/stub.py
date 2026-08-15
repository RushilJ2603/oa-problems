import sys

def palindromePaths(tree_nodes: int, tree_from: list[int], tree_to: list[int], arr: list[str], queries: list[int]) -> list[int]:
    # WRITE YOUR CODE HERE
    pass

def main():
    lines = sys.stdin.read().split()
    if not lines:
        return
    idx = 0
    n = int(lines[idx])
    idx += 1
    e = int(lines[idx])
    idx += 1
    tree_from = []
    tree_to = []
    for _ in range(e):
        tree_from.append(int(lines[idx]))
        idx += 1
        tree_to.append(int(lines[idx]))
        idx += 1
    
    c = int(lines[idx])
    idx += 1
    arr = []
    for _ in range(c):
        arr.append(lines[idx])
        idx += 1
        
    m = int(lines[idx])
    idx += 1
    queries = []
    for _ in range(m):
        queries.append(int(lines[idx]))
        idx += 1
        
    res = palindromePaths(n, tree_from, tree_to, arr, queries)
    for x in res:
        print(x)

if __name__ == '__main__':
    main()
