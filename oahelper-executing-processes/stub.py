import sys

def solve(n, priorities):
    # WRITE YOUR CODE HERE
    return [0] * n

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    priorities = [int(x) for x in input_data[1:]]
    ans = solve(n, priorities)
    print(" ".join(map(str, ans)))

if __name__ == '__main__':
    main()
