"""One random valid fixture for Second Highest Salary.

usage: python3 generator.py [seed] [size]

The interesting cases are the ones with FEW DISTINCT values — a table of 500 unique salaries always
has a second highest, so it never tests the branch that matters. These draws deliberately produce
all-equal tables, two-value tables and heavy duplicate-at-the-top tables.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 5
rng = random.Random(seed)

n = max(0, min(2000, size))

shape = rng.choice(["few_distinct", "few_distinct", "all_equal", "two_values", "unique", "wide"])
if shape == "all_equal":
    v = rng.randint(-500, 500)
    salaries = [v] * max(1, n)
elif shape == "two_values":
    a, b = rng.sample(range(-500, 501), 2)
    salaries = [rng.choice([a, b]) for _ in range(max(1, n))]
elif shape == "few_distinct":
    pool = [rng.randint(-1000, 100000) for _ in range(rng.randint(1, 4))]
    salaries = [rng.choice(pool) for _ in range(max(1, n))]
elif shape == "wide":
    salaries = [rng.randint(-10 ** 6, 10 ** 6) for _ in range(max(1, n))]
else:
    salaries = rng.sample(range(-10 ** 6, 10 ** 6), max(1, min(n, 1500)))

if n == 0:
    salaries = []

print("CREATE TABLE employee (id INTEGER PRIMARY KEY, salary INTEGER NOT NULL);")
if salaries:
    vals = ", ".join("(%d, %d)" % (i + 1, s) for i, s in enumerate(salaries))
    print("INSERT INTO employee (id, salary) VALUES %s;" % vals)
