import sys

def solve(min_length, max_length, one_group, zero_group):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if len(data) < 4:
        return
    min_length, max_length, one_group, zero_group = map(int, data[:4])
    print(solve(min_length, max_length, one_group, zero_group))

if __name__ == "__main__":
    main()
