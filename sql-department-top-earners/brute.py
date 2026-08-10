"""Independent solution: no window function, no SQL ranking.

Load the fixture, group employees by department in Python, take the top three DISTINCT salary values
per department with a plain sorted set, then keep every employee at one of those salaries and sort
the output by hand. reference.sql's correctness rests on DENSE_RANK semantics; this rederives the
same answer without ever using them.

Self-contained: the gate stages the package into a temp directory.
"""
import sqlite3
import sys
from collections import defaultdict


def main() -> None:
    con = sqlite3.connect(":memory:")
    con.executescript(sys.stdin.read())
    depts = dict(con.execute("SELECT id, name FROM departments"))
    by_dept = defaultdict(list)
    for name, salary, did in con.execute("SELECT name, salary, department_id FROM employees"):
        by_dept[did].append((name, salary))

    rows = []
    for did, people in by_dept.items():
        if did not in depts:
            continue                                    # employee in a department that does not exist
        top3 = sorted({s for _, s in people}, reverse=True)[:3]
        keep = set(top3)
        for name, salary in people:
            if salary in keep:
                rows.append((depts[did], name, salary))

    rows.sort(key=lambda r: (r[0], -r[2], r[1]))
    for d, n, s in rows:
        print("%s\t%s\t%s" % (d, n, s))


main()
