"""Independent solution: load the fixture, then do the anti-join in plain Python with a set of
customer ids that appear in orders. No SQL join, no NULL semantics to get wrong — which is the point,
because reference.sql's whole correctness argument is about how NULL behaves in a join.

Self-contained: gate_candidate.py stages the package into a temp dir, so nothing here may import
from the repo.
"""
import sqlite3
import sys


def main() -> None:
    con = sqlite3.connect(":memory:")
    con.executescript(sys.stdin.read())
    customers = list(con.execute("SELECT id, name FROM customers"))
    ordered = {r[0] for r in con.execute("SELECT customer_id FROM orders") if r[0] is not None}
    for cid, name in customers:
        if cid not in ordered:
            print(name)


main()
