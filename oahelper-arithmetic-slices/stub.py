import sys
import ast

def solve(n: int, latencies: list[int]) -> int:
    # WRITE YOUR CODE HERE
    return 0

def main():
    input_str = sys.stdin.read().strip()
    if not input_str:
        return
    try:
        nums = ast.literal_eval(input_str)
    except:
        nums = [int(x) for x in input_str.replace('[', '').replace(']', '').replace(',', ' ').split()]
    print(solve(len(nums), nums))

if __name__ == '__main__':
    main()
