import sys
from collections import deque

def solve_campaign(n, edges, seed_costs, values, budget, d):
    # WRITE YOUR CODE HERE
    return [], 0, 0

def main():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    def ni():
        return int(next(it))
    try:
        n = ni()
    except StopIteration:
        return
    m = ni()
    edges = [(ni(), ni()) for _ in range(m)]
    s = ni()
    seed_costs = [(ni(), ni()) for _ in range(s)]
    values = [ni() for _ in range(n)]
    budget = ni()
    d = ni()
    chosen, total_value, total_cost = solve_campaign(n, edges, seed_costs, values, budget, d)
    out = ["[" + ",".join(map(str, chosen)) + "]", str(total_value), str(total_cost)]
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()
