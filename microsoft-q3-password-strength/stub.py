import sys


def is_weak(pw, commons):
    # Return True if the password is weak, False if strong.
    # WRITE YOUR CODE HERE
    return False


def main():
    data = sys.stdin.read().split("\n")
    pos = 0
    n = int(data[pos]); pos += 1
    passwords = data[pos:pos + n]; pos += n
    c = int(data[pos]); pos += 1
    commons = data[pos:pos + c]; pos += c
    print("\n".join("weak" if is_weak(p, commons) else "strong" for p in passwords))


main()
