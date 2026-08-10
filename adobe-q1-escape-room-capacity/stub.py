import sys


def can_schedule(capacity: int, shows: list) -> bool:
    # shows is a list of (start_time, end_time, attendees) tuples
    # WRITE YOUR CODE HERE
    return True


def main() -> None:
    data = sys.stdin.buffer.read().split()
    capacity = int(data[0])
    n = int(data[1])
    shows = []
    for i in range(n):
        s, e, a = (int(x) for x in data[2 + 3 * i:5 + 3 * i])
        shows.append((s, e, a))
    print("True" if can_schedule(capacity, shows) else "False")


main()
