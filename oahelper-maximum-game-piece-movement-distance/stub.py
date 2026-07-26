import sys


def solve(n, board):
    # WRITE YOUR CODE HERE
    return 0


def read_board():
    raw = sys.stdin.read()
    if "[" in raw:
        return [int(ch) for ch in raw if ch in "01"]
    nums = list(map(int, raw.split()))
    if not nums:
        return []
    n = nums[0]
    return nums[1 : 1 + n]


def main():
    board = read_board()
    print(solve(len(board), board))


if __name__ == "__main__":
    main()
