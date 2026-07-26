import sys


def total_bits_at_sinks(n, edges):
    # n nodes (0..n-1); node 0 is the producer. edges is a list of (u, v) directed links.
    # Return the total bits received by all sink nodes (no outgoing edge).
    # WRITE YOUR CODE HERE
    return 0


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    idx = 0
    n = int(data[idx]); idx += 1
    m = int(data[idx]); idx += 1
    edges = []
    for _ in range(m):
        u = int(data[idx]); v = int(data[idx + 1]); idx += 2
        edges.append((u, v))
    print(total_bits_at_sinks(n, edges))


if __name__ == "__main__":
    main()
