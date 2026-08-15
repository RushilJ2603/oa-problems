import sys

def solve(N: int, m: int, nums: list[int]) -> int:
    # WRITE YOUR CODE HERE
    return 0

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    N = int(input_data[0])
    m = int(input_data[1])
    nums = [int(x) for x in input_data[2:2+m]]
    
    print(solve(N, m, nums))

if __name__ == '__main__':
    main()
