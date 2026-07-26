import sys

def solve(operations):
    # WRITE YOUR CODE HERE
    return ""

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    idx = 0
    n = int(data[idx]); idx += 1
    operations = []
    for _ in range(n):
        t = int(data[idx]); idx += 1
        if t == 1:
            x = int(data[idx]); idx += 1
            operations.append([t, x])
        else:
            x = int(data[idx]); idx += 1
            size = int(data[idx]); idx += 1
            operations.append([t, x, size])
    print(solve(operations))

if __name__ == "__main__":
    main()
