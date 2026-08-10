"""One random valid fixture for Department Top Earners.

usage: python3 generator.py [seed] [size]

Salaries are drawn from a SMALL pool on purpose. Ties are the entire difficulty of this problem —
they are what separates DENSE_RANK from RANK and from LIMIT 3 — and a fixture of distinct salaries
never exercises any of it. Departments with fewer than three distinct salaries appear too, since
"top 3" must then mean "all of them".
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 6
rng = random.Random(seed)

n_emp = max(1, min(600, size))
n_dept = max(1, min(n_emp, rng.choice([1, 1, 2, 3, max(1, n_emp // 4)])))
NAMES = ["Ann", "Bo", "Cy", "Di", "Ed", "Fi", "Gil", "Hu", "Ida", "Jo",
         "Kim", "Lu", "Moe", "Nia", "Oz", "Pia", "Ray", "Sid", "Tom", "Uma"]

pool_size = rng.choice([1, 2, 3, 4, 8, 40])
pool = [rng.randrange(0, 200000, 500) for _ in range(pool_size)]

print("CREATE TABLE departments (id INTEGER PRIMARY KEY, name TEXT NOT NULL);")
print("CREATE TABLE employees (id INTEGER PRIMARY KEY, name TEXT NOT NULL,"
      " salary INTEGER NOT NULL, department_id INTEGER);")
print("INSERT INTO departments (id, name) VALUES %s;"
      % ", ".join("(%d,'D%02d')" % (i + 1, i + 1) for i in range(n_dept)))
emps = []
for i in range(n_emp):
    nm = rng.choice(NAMES) + (str(i) if rng.random() < 0.6 else "")
    sal = rng.choice(pool)
    did = rng.randint(1, n_dept)
    emps.append("(%d,'%s',%d,%d)" % (i + 1, nm, sal, did))
print("INSERT INTO employees (id, name, salary, department_id) VALUES %s;" % ", ".join(emps))
