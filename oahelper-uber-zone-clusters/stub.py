import sys

def solve(n, signature):
    # WRITE YOUR CODE HERE
    return [0] * n

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    signature = [int(data[i + 1]) for i in range(n)]
    ans = solve(n, signature)
    sys.stdout.write("\n".join(map(str, ans)) + "\n")

if __name__ == "__main__":
    main()
