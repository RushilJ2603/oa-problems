import sys

def solve(n: int) -> int:
    # WRITE YOUR CODE HERE
    return 0

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    print(solve(n))

if __name__ == '__main__':
    main()
