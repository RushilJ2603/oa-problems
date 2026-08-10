"""One random valid fixture for Top Selling Products.

usage: python3 generator.py [seed] [size]

The whole problem lives at one number, so the fixture is built AROUND that number rather than around
it. Random quantities put almost every product far from 100 units, where "> 100", ">= 100" and
"COUNT(*) > 100" all agree and the test proves nothing; here a large share of products is steered to
land on exactly 100 or exactly 101 total units, and one shape fills the table with quantity-ZERO
sales so a product can have 150 transactions and still sell nothing.

The generator also enforces the statement's guarantee that no two REPORTED products share a
TotalSalesAmount, by nudging a quantity upward until every reported total is distinct — otherwise
"ordered by TotalSalesAmount descending" would not determine the output.
"""
import random
import sys
from collections import defaultdict

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
rng = random.Random(seed)

WORDS = ["Widget", "Gadget", "Sprocket", "Cog", "Bolt", "Lever", "Panel", "Valve", "Cable", "Gear"]

n_sales = max(0, min(1000, size))
n_prod = max(1, min(200, rng.choice([1, 2, 3, max(1, n_sales // 4), max(1, n_sales // 20), 200])))

# Keep every TotalSalesAmount inside DECIMAL(10,2) even in the worst case where one product takes
# every sale at the maximum quantity.
price_cap = max(1, min(99999, 10 ** 10 // (n_sales * 500 + 1000)))

shape = rng.choice(["random", "random", "boundary", "boundary", "zeroqty", "wide", "heavy"])


def qt(s):
    return "'" + s.replace("'", "''") + "'"


names = set()
products = []
for i in range(n_prod):
    while True:
        nm = "%s %s%d" % (rng.choice(WORDS), rng.choice(["", "", "O'", "Mk-", "Pro "]), i)
        if nm not in names:
            names.add(nm)
            break
    products.append((i + 1, nm, rng.randint(1, price_cap)))

# --- sales -------------------------------------------------------------------------------------
sales = []          # (product_id, quantity)
if shape == "boundary":
    # Split the sales budget between products and aim each product's TOTAL at a value near 100.
    per = max(1, n_sales // max(1, n_prod))
    for pid, _, _ in products:
        if len(sales) >= n_sales:
            break
        target = rng.choice([0, 1, 99, 100, 100, 101, 101, 102, 150, 500])
        k = rng.randint(1, min(per, 8))
        left = target
        for j in range(k):
            if len(sales) >= n_sales:
                break
            take = left if j == k - 1 else rng.randint(0, left)
            sales.append((pid, min(1000, take)))
            left -= take
elif shape == "zeroqty":
    # Many transactions, no units: COUNT(*) says yes, SUM(QuantitySold) says no.
    for _ in range(n_sales):
        pid = rng.randint(1, n_prod)
        sales.append((pid, 0 if rng.random() < 0.8 else rng.randint(0, 120)))
elif shape == "wide":
    # One sale per product, so almost nothing qualifies and the empty-ish result is exercised.
    for i in range(n_sales):
        sales.append((rng.randint(1, n_prod), rng.choice([0, 1, 50, 100, 101, 500])))
elif shape == "heavy":
    # Everything piled onto one or two products.
    hot = [rng.randint(1, n_prod) for _ in range(min(2, n_prod))]
    for _ in range(n_sales):
        pid = rng.choice(hot) if rng.random() < 0.9 else rng.randint(1, n_prod)
        sales.append((pid, rng.randint(0, 500)))
else:
    for _ in range(n_sales):
        sales.append((rng.randint(1, n_prod), rng.randint(0, 500)))

price_of = {pid: pc for pid, _, pc in products}

# --- enforce "no two reported products share a TotalSalesAmount" --------------------------------
first_sale_of = {}
for idx, (pid, _) in enumerate(sales):
    first_sale_of.setdefault(pid, idx)


def totals():
    q = defaultdict(int)
    c = defaultdict(int)
    for p, quantity in sales:
        q[p] += quantity
        c[p] += quantity * price_of[p]
    return q, c


qty, cents = totals()
used = set()
for pid in sorted(p for p in qty if qty[p] > 100):
    guard = 0
    while cents[pid] in used and guard <= len(products) + 2:
        i = first_sale_of[pid]
        p, quantity = sales[i]
        sales[i] = (p, min(1000, quantity + 1))
        cents[pid] += price_of[pid]
        qty[pid] += 1
        guard += 1
    used.add(cents[pid])

# --- emit ---------------------------------------------------------------------------------------
print("CREATE TABLE Products (ProductID INTEGER PRIMARY KEY, ProductName TEXT NOT NULL,"
      " Price REAL NOT NULL);")
print("CREATE TABLE Sales (SaleID INTEGER PRIMARY KEY, ProductID INTEGER NOT NULL,"
      " QuantitySold INTEGER NOT NULL, SaleDate TEXT NOT NULL);")
print("INSERT INTO Products (ProductID, ProductName, Price) VALUES %s;"
      % ", ".join("(%d,%s,%.2f)" % (pid, qt(nm), pc / 100.0) for pid, nm, pc in products))
if sales:
    rows = []
    for i, (pid, quantity) in enumerate(sales):
        d = "2024-%02d-%02d" % (rng.randint(1, 12), rng.randint(1, 28))
        rows.append("(%d,%d,%d,'%s')" % (i + 1, pid, quantity, d))
    print("INSERT INTO Sales (SaleID, ProductID, QuantitySold, SaleDate) VALUES %s;"
          % ", ".join(rows))
