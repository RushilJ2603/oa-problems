#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import string
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Word length grows with size; at large size hit max length 35.
    # Keep letter alphabet small so brute (n!) stays feasible on random checks.
    if size >= 800:
        L = 35
        alphabet_n = 8
    elif size >= 400:
        L = 25
        alphabet_n = 7
    elif size >= 150:
        L = 15
        alphabet_n = 6
    elif size >= 40:
        L = max(3, min(12, size // 5 + 2))
        alphabet_n = 5
    else:
        L = max(1, min(8, size // 2 + 1))
        alphabet_n = max(2, min(5, size // 2 + 2))

    alphabet = list(string.ascii_uppercase[:alphabet_n])

    def make_word(length):
        # Prefer reuse so equation can be satisfiable sometimes; still random.
        return "".join(random.choice(alphabet) for _ in range(length))

    # Vary relative lengths: sum result often longer by 0 or 1
    mode = seed % 5
    if mode == 0:
        l1 = l2 = L
        l3 = min(35, L + 1)
    elif mode == 1:
        l1, l2, l3 = L, max(1, L - 1), L
    elif mode == 2:
        l1 = l2 = l3 = max(1, L // 2 + 1)
    elif mode == 3:
        l1, l2, l3 = 1, 1, 1  # leading-zero allowed on singles
    else:
        l1 = random.randint(1, L)
        l2 = random.randint(1, L)
        l3 = random.randint(1, min(35, max(l1, l2) + 1))

    # Occasional classic-style short puzzles with more letters
    if size < 40 and seed % 7 == 0:
        w1, w2, w3 = "SEND", "MORE", "MONEY"
    elif size < 40 and seed % 7 == 1:
        w1, w2, w3 = "GREEN", "BLUE", "BLACK"
    elif size < 40 and seed % 7 == 2:
        w1, w2, w3 = "A", "B", "C"
    else:
        w1, w2, w3 = make_word(l1), make_word(l2), make_word(l3)

    sys.stdout.write(f"{w1}\n{w2}\n{w3}\n")


if __name__ == "__main__":
    main()
