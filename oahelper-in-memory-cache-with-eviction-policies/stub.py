import sys

def run_cache_operations(capacity, policy, operations):
    # WRITE YOUR CODE HERE
    return []

def main():
    lines = sys.stdin.read().splitlines()
    if not lines: return
    capacity = int(lines[0].strip())
    policy = lines[1].strip()
    n = int(lines[2].strip())
    ops = [lines[3+i].strip() for i in range(n)]
    res = run_cache_operations(capacity, policy, ops)
    for s in res: print(s)

if __name__ == '__main__':
    main()
