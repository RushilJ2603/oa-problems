import sys

def get_distinct_score_values(n, arr):
    # WRITE YOUR CODE HERE
    return []

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    arr = [int(x) for x in input_data[1:n+1]]
    res = get_distinct_score_values(n, arr)
    for x in res:
        sys.stdout.write(f"{x}\n")

if __name__ == '__main__':
    main()
