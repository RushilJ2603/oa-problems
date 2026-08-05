import sys


def min_transform_cost(machine_count, final_machine_count, shifting_cost):
    # WRITE YOUR CODE HERE
    return 0


def main() -> None:
    data = sys.stdin.read().split()
    n = int(data[0])
    machine_count = [int(x) for x in data[1:1 + n]]
    final_machine_count = [int(x) for x in data[1 + n:4 + n]]
    shifting_cost = int(data[4 + n])
    print(min_transform_cost(machine_count, final_machine_count, shifting_cost))


if __name__ == "__main__":
    main()
