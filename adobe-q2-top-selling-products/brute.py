"""Independent solution: no JOIN, no GROUP BY, no HAVING.

Load the fixture, pull the two tables out as plain rows, and do the grouping in Python with a dict.
Money is accumulated in INTEGER CENTS rather than floats, so this side of the comparison cannot
inherit a rounding artefact from the same double arithmetic the query uses — if reference.sql's
ROUND ever landed on the wrong side of a half-cent, this would disagree with it.

Self-contained: the gate stages the package into a temp directory, so nothing here may import from
the repo.
"""
import sqlite3
import sys
from collections import defaultdict


def main() -> None:
    con = sqlite3.connect(":memory:")
    con.executescript(sys.stdin.read())

    # Price is DECIMAL(10,2) stored as REAL; round to whole cents to get back the exact decimal.
    price_cents = {}
    name = {}
    for pid, pname, price in con.execute("SELECT ProductID, ProductName, Price FROM Products"):
        price_cents[pid] = int(round(float(price) * 100))
        name[pid] = pname

    qty = defaultdict(int)
    cents = defaultdict(int)
    for pid, q in con.execute("SELECT ProductID, QuantitySold FROM Sales"):
        if pid not in price_cents:
            continue                      # a sale of a product that does not exist cannot be named
        qty[pid] += q
        cents[pid] += q * price_cents[pid]

    rows = [(name[pid], cents[pid]) for pid in qty if qty[pid] > 100]
    rows.sort(key=lambda r: -r[1])

    for pname, c in rows:
        print("%s\t%.2f" % (pname, c / 100.0))


main()
