"""Independent solution.

reference.sql answers with one SQL statement (DISTINCT + ORDER BY + LIMIT/OFFSET inside a scalar
subquery). This one uses SQL only to LOAD the fixture, then computes the answer in plain Python over
the raw rows — so the ranking, the de-duplication and the "no second salary" case are all derived a
second time, by different means.

Self-contained on purpose: gate_candidate.py copies the package into an isolated staging directory,
so a brute that reaches back into the repo (say, to import the app's row formatter) fails there and
not here. Print the one value it needs directly.
"""
import sqlite3
import sys


def main() -> None:
    con = sqlite3.connect(":memory:")
    con.executescript(sys.stdin.read())
    salaries = [r[0] for r in con.execute("SELECT salary FROM employee")]

    distinct = sorted(set(salaries), reverse=True)
    answer = distinct[1] if len(distinct) >= 2 else None
    print("NULL" if answer is None else str(answer))


main()
