#!/usr/bin/env python3
"""Generate one random valid input for Dr. Jang's Probabilistic Walk.
CLI: python3 generator.py <seed> <size>
At large size, emits a MAX-SCALE instance (N=100, T=1000).
"""
import random
import sys


def emit_case(N, E_target, T):
    # Build a valid Markov graph: each non-sink has outgoing probs summing to 1.
    # Keep a fraction of nodes as sinks (no out-edges) so "leave work" is tested.
    sink_prob = 0.15
    is_sink = [False] * (N + 1)
    for u in range(1, N + 1):
        if u == 1:
            continue  # start node always has exits so the walk can begin
        if random.random() < sink_prob:
            is_sink[u] = True

    edges = []
    for u in range(1, N + 1):
        if is_sink[u]:
            continue
        # 1..k outgoing targets (at most N), probs sum to 1
        k = random.randint(1, min(4, N) if N > 1 else 1)
        # Prefer distinct targets; allow self-loops
        targets = []
        for _ in range(k):
            targets.append(random.randint(1, N))
        # Normalize random positive weights
        w = [random.random() + 0.01 for _ in targets]
        s = sum(w)
        for t, wi in zip(targets, w):
            edges.append((u, t, wi / s))

    # Cap / trim to roughly E_target by merging if somehow huge (shouldn't be)
    if len(edges) > max(E_target, 1) and E_target > 0:
        # Keep all — E is derived from construction; E_target is a hint only
        pass

    print(N, len(edges), T)
    flat = []
    for u, v, p in edges:
        flat.append(f"{u} {v} {p:.10f}")
    print(" ".join(flat))


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> (N, T). Large size hits constraint bounds.
    if size >= 100:
        N = 100
        T = 1000
    elif size >= 40:
        N = min(50, max(5, size // 2))
        T = min(500, size * 5)
    elif size >= 10:
        N = min(20, max(3, size))
        T = min(100, size * 3)
    else:
        N = max(2, min(8, size + 1))
        T = random.randint(0, max(20, size * 10))

    # Keep steps modest for small sizes so the exponential brute stays fast
    if size < 25:
        T = min(T, 30)  # at most 3 moves
        N = min(N, 6)

    E_hint = N * 3
    emit_case(N, E_hint, T)


if __name__ == "__main__":
    main()
