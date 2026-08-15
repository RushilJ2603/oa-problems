import sys

def get_valid_configurations(n: int, coordination_threshold: list) -> int:
    # WRITE YOUR CODE HERE
    return 0

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    coordination_threshold = [int(x) for x in input_data[1:n+1]]
    print(get_valid_configurations(n, coordination_threshold))

if __name__ == '__main__':
    main()
