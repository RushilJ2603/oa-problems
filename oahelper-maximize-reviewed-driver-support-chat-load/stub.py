import sys

MOD = 10**9 + 7

def solve(n, chat_load, k, review_minutes):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    n = int(data[p]); p += 1
    chat = [int(data[p + i]) for i in range(n)]; p += n
    k = int(data[p]); p += 1
    rev = [int(data[p + i]) for i in range(k)]
    print(solve(n, chat, k, rev))

if __name__ == "__main__":
    main()
