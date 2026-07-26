import sys


def add_one(number):
    # `number` is a digit string; return the digit string of (number + 1).
    # WRITE YOUR CODE HERE
    return number


def main():
    data = sys.stdin.read().split()
    if not data:
        return
    print(add_one(data[0]))


if __name__ == "__main__":
    main()
