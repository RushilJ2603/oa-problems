import sys

def solve(R: int, C: int, mat: list[list[int]]) -> list[int]:
    # WRITE YOUR CODE HERE
    return []

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    r = int(input_data[0])
    c = int(input_data[1])
    mat = []
    idx = 2
    for _ in range(r):
        row = []
        for _ in range(c):
            row.append(int(input_data[idx]))
            idx += 1
        mat.append(row)
    res = solve(r, c, mat)
    print(*(res))

if __name__ == '__main__':
    main()
