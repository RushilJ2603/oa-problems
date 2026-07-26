import sys

def solve(n, vulnerability, k):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    vulnerability = list(map(int, data[1:n + 1]))
    k = int(data[n + 1])
    print(solve(n, vulnerability, k))

if __name__ == "__main__":
    main()
