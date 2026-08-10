"""One random valid fixture for Customers Who Never Ordered.

usage: python3 generator.py [seed] [size]

Two properties are deliberate. Orders frequently carry a NULL customer_id (an unassigned order),
because that single value is what makes the NOT IN solution collapse to an empty result — a fixture
without it lets the wrong answer pass. And orders sometimes reference a customer id that does not
exist, so a solution that assumes referential integrity is exercised too.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 5
rng = random.Random(seed)

n = max(1, min(800, size))
NAMES = ["Ana", "Bob", "Cyd", "Dan", "Eve", "Fay", "Gus", "Hal", "Ivy", "Jon",
         "Kay", "Lee", "Mia", "Ned", "Oli", "Pat", "Quin", "Rex", "Sam", "Tia"]

customers = [(i + 1, rng.choice(NAMES) + (str(i) if rng.random() < 0.5 else ""))
             for i in range(n)]

n_orders = rng.randint(0, max(1, n * 2))
orders = []
null_rate = rng.choice([0.0, 0.05, 0.2, 0.5])       # 0.0 included so the NOT IN bug is not ALWAYS caught
for j in range(n_orders):
    if rng.random() < null_rate:
        cid = None
    elif rng.random() < 0.1:
        cid = n + rng.randint(1, 5)                  # orphan: no such customer
    else:
        cid = rng.randint(1, n)
    orders.append((j + 1, cid))

print("CREATE TABLE customers (id INTEGER PRIMARY KEY, name TEXT NOT NULL);")
print("CREATE TABLE orders (id INTEGER PRIMARY KEY, customer_id INTEGER);")
print("INSERT INTO customers (id, name) VALUES %s;"
      % ", ".join("(%d, '%s')" % (i, nm.replace("'", "''")) for i, nm in customers))
if orders:
    print("INSERT INTO orders (id, customer_id) VALUES %s;"
          % ", ".join("(%d, %s)" % (i, "NULL" if c is None else c) for i, c in orders))
