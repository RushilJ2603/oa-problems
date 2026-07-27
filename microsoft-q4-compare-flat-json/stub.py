import sys


def diff_keys(json1, json2):
    # Return the keys present in BOTH objects with different values, sorted ascending.
    # WRITE YOUR CODE HERE
    return []


def main():
    lines = sys.stdin.read().split("\n")
    a = lines[0] if len(lines) > 0 else ""
    b = lines[1] if len(lines) > 1 else ""
    sys.stdout.write("".join(k + "\n" for k in diff_keys(a, b)))


main()
