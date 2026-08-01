# Relational Algebra and Joins

## Introduction to Relational Algebra

::: definition
**Relational Algebra** is a formal, procedural query language introduced by Edgar F. Codd in 1970. It is the mathematical foundation for relational databases.
:::

In relational algebra, queries are expressed as a sequence of operations. Because it is a *procedural* language, it specifies not only **what** data to retrieve, but also exactly **how** to get it by dictating the order of operations. 

A critical property of relational algebra is the **closure property**: every operator takes one or two relations as input and returns a new relation as output. This means operations can be seamlessly composed, with the output of one operator acting as the input to the next.

## Operators and Symbols

To build queries in relational algebra, specific operators are used. These operators are broadly categorized into basic and derived operators.

![Relational-algebra operators: basic (π, σ, ×, ∪, ρ, −) vs derived (⋈, ∩, ÷).](assets/ra_operators.jpg)

::: keypoint
**Basic (Fundamental) Operators**: These are the atomic building blocks of the language. They cannot be expressed in terms of any other operators. They include:

- Projection ($\pi$)
- Selection ($\sigma$)
- Cross product ($\times$)
- Union ($\cup$)
- Set difference ($-$)
- Rename ($\rho$)

**Derived Operators**: These are convenience operators that can be entirely expressed using combinations of the basic operators. They include:

- Join ($\bowtie$)
- Intersection ($\cap$)
- Division ($\div$)

For example, the intersection identity is given by: $X \cap Y = X - (X - Y)$.
:::

When writing relational algebra expressions, specific symbols denote these operations.

![Symbols for the relational-algebra operators.](assets/ra_symbols.jpg)

Here is a summary of the standard symbols:

- $\pi$ : Projection
- $\sigma$ : Selection
- $\rho$ : Rename
- $\cup$ : Union
- $\cap$ : Intersection
- $\leftarrow$ : Assignment
- $\times$ : Cartesian (Cross) product
- $\bowtie$ : Join
- `⟕` : Left outer join
- `⟖` : Right outer join
- `⟗` : Full outer join
- `⋉` : Semijoin

## Projection ($\pi$) and Selection ($\sigma$)

Projection and selection are fundamental unary operators (operators that act on a single relation).

::: definition
- **Projection ($\pi_{\text{cols}}(R)$)**: Picks specific COLUMNS from a relation (a vertical slice) and automatically removes any duplicate rows in the result.
- **Selection ($\sigma_{\text{condition}}(R)$)**: Picks specific ROWS from a relation (a horizontal slice) that satisfy the given condition.
:::

![Selection σ selects rows, projection π selects columns: π_Name(σ_Rollno=2(Student)).](assets/ra_selection.jpg)

::: trap
**Mnemonic**: 
**P**rojection = Columns. 
**S**election = Rows.
:::

### Composition Example
Because of the closure property, operators can be composed. Consider the query: $\pi_{\text{Name}}(\sigma_{\text{Rollno}=2}(\text{Student}))$.

Consider the `Student` relation, defined as `Student(Rollno, Name, Age)`:

| Rollno | Name | Age |
| :--- | :--- | :--- |
| 1 | A | 20 |
| 2 | B | 21 |
| 3 | A | 19 |

1. **Step 1 (Selection)**: Evaluating the inner expression $\sigma_{\text{Rollno}=2}(\text{Student})$ horizontally slices the table, picking only the row where `Rollno` is 2. The intermediate result is the full row: `(2, B, 21)`.
2. **Step 2 (Projection)**: Evaluating the outer expression $\pi_{\text{Name}}(\dots)$ vertically slices the intermediate result, keeping only the `Name` column.

The final result is simply `"B"`.

## Cross Product ($\times$)

The cross product (or Cartesian product) is a binary operator that combines two relations without any condition.

::: definition
**Cross Product ($R1 \times R2$)**: Pairs *every* tuple of $R1$ with *every* tuple of $R2$. If $R1$ has $m$ columns and $R2$ has $n$ columns, the result has $(m+n)$ columns. If $R1$ has $X$ rows and $R2$ has $Y$ rows, the result has $(X \times Y)$ rows.
:::

![Cross product R1×R2 has (m+n) columns and (m×n) rows.](assets/ra_cross.jpg)

Consider two relations:
`R1(A, B, C) = (1, 2, 3), (2, 1, 4)`
`R2(C, D, E) = (3, 4, 5), (2, 1, 2)`

| A | B | C |
| :--- | :--- | :--- |
| 1 | 2 | 3 |
| 2 | 1 | 4 |

| C | D | E |
| :--- | :--- | :--- |
| 3 | 4 | 5 |
| 2 | 1 | 2 |

Applying $R1 \times R2$ pairs each of the 2 rows in $R1$ with each of the 2 rows in $R2$.

- Number of columns: $3 + 3 = 6$ columns.
- Number of rows: $2 \times 2 = 4$ rows.

The cross product forms the mathematical basis for all join operations.

## Union ($\cup$) and Set Difference ($-$)

For standard set operations like Union ($\cup$), Intersection ($\cap$), and Set Difference ($-$) to make logical sense in a relational database, the participating relations must be **union-compatible**.

::: heavy
**Union-Compatibility**
Two relations are union-compatible if and only if they satisfy both of these strict requirements:

1. They have the exactly same number of columns (degree).
2. Each corresponding column (from left to right) has the same domain (data type).
:::

### Union

![Union of two union-compatible relations.](assets/ra_union.jpg)

Consider extracting all names from two different entities: `Student` and `Employee`.
`Student(Rollno, Name) = (1, A), (2, B), (3, C)`
`Employee(Emp_No, Name) = (7, E), (1, A)`

| Rollno | Name |
| :--- | :--- |
| 1 | A |
| 2 | B |
| 3 | C |

| Emp_No | Name |
| :--- | :--- |
| 7 | E |
| 1 | A |

To find everyone associated with the institution, Union is used: 
$\pi_{\text{Name}}(\text{Student}) \cup \pi_{\text{Name}}(\text{Employee})$. 

Because just the `Name` column is projected from both, the intermediate relations have 1 column with the same domain (text), making them union-compatible. 
The result is the set of distinct names: `{A, B, C, E}`.

### Set Difference

![Set difference on union-compatible relations: π_Name(Student) − π_Name(Employee).](assets/ra_setdiff.jpg)

Set difference returns tuples present in the first relation but absent in the second.

::: trap
**Order Matters**: Unlike intersection or union, set difference is not commutative. $A - B \neq B - A$. 
Mathematically, $A - B$ means the tuples in $A$ that are not in $B$, which can be written as $A \cap B'$.
:::

To find the "Name of a person who is a Student but not an Employee", set difference is applied:
$\pi_{\text{Name}}(\text{Student}) - \pi_{\text{Name}}(\text{Employee})$

Looking at the data, student "A" is also an employee, but "B" and "C" are not. The result is `{B, C}`.

## Division ($\div$)

Division is a derived operator typically used to answer queries involving the word "every" or "all".

![Division: the students enrolled in *every* course.](assets/ra_division.jpg)

::: definition
**Division ($A(x, y) \div B(y)$)**: Returns the $x$-values that appear in relation $A$ paired with *every* single $y$-value present in relation $B$.
:::

To find the "Sid of students enrolled in every course", it is formulated as:
$\text{Enrolled(Sid, Cid)} \div \text{Course(Cid)}$

## Rename ($\rho$)

![The rename operator ρ (a query-only alias).](assets/ra_rename.jpg)

The rename operator, denoted by $\rho$ (rho), provides a mechanism to give a relation a temporary alias for the duration of a query. 

::: definition
**Rename ($\rho(T, R)$)**: Gives relation $R$ the alias $T$. This is a query-only alias; the original data and schema on disk remain completely unchanged.
:::

Rename becomes strictly necessary when an operation requires referring to the same table multiple times in one query, such as computing a self cross-product: $R \times \rho(T, R)$. 

## A Worked Query

These concepts combine in a multi-step relational algebra query. 

![Worked query: female employees earning more than some male employee (self cross-product with ρ).](assets/ra_worked.jpg)

**Goal**: Find the emp id of female employees whose salary is more than some (at least one) male employee's salary.

Consider the following `Emp` relation, defined as `Emp(Eid, Salary, Gender)`:

| Eid | Salary | Gender |
| :--- | :--- | :--- |
| 1 | 10000 | M |
| 2 | 20000 | M |
| 3 | 30000 | F |
| 4 | 40000 | M |
| 5 | 50000 | F |

**Step 1: Self Cross-Product**
Because it requires comparing employees to other employees, a cross product of the table with itself is computed. The rename operator distinguishes the two instances.
Compute: $\text{Emp} \times \rho(\text{Emp1}, \text{Emp})$

This creates an intermediate table pairing every employee with every other employee.

**Step 2: Selection (Filtering)**
This combined table is filtered for specific conditions: the left employee must be female, the right (renamed) employee must be male, and the left's salary must be greater than the right's salary.
Select: $\sigma_{\text{Emp.Gender}='F' \land \text{Emp1.Gender}='M' \land \text{Emp.Salary} > \text{Emp1.Salary}}(\dots)$

Evaluating this:

- Eid 3 (Female, 30000) earns more than Eid 1 (Male, 10000) and Eid 2 (Male, 20000).
- Eid 5 (Female, 50000) earns more than Eid 1 (Male, 10000), Eid 2 (Male, 20000), and Eid 4 (Male, 40000).

**Step 3: Projection**
Finally, only the IDs of the qualifying females are extracted.
Project: $\pi_{\text{Emp.Eid}}(\dots)$

The final resulting set is: `{3, 5}`.

## Joins (The Relational Algebra View)

While a cross product pairs everything, a join restricts that pairing. Conceptually, a join is simply a cross product followed immediately by a selection condition. Note that the focus here is the relational algebra theory; full SQL syntax for joins is covered in Part V.

### Cross Join
A cross join is simply the plain cross product ($\times$) with no filtering condition.

### Natural Join ($\bowtie$)

![Natural join of Emp and Dept over the common attribute.](assets/join_natural.jpg)

A natural join automatically matches rows based on all common attributes between the two relations, and it drops the duplicate column in the final result.

Consider: `Emp(Eno, Ename, DepNo)` and `Dept(DepNo, Name, Eno)`.
To return employees whose DepNo matches a department:
`SELECT E_name FROM Emp NATURAL JOIN Dept` $\equiv$ `SELECT E_name FROM Emp,Dept WHERE Emp.Eno=Dept.Eno`

### Equi Join

![Equi join on an equality condition (address = location).](assets/join_equi.jpg)

An equi join is a specific type of theta join (a join with a condition) where the operator used in the condition is strictly equality (`=`).

Consider the query: "Emp whose department location = their address".
SQL equivalent: `... WHERE Emp.Eno=Dept.Eno AND Emp.Address=Dept.Location`

`Emp(Eno, Ename, Address)`:

| Eno | Ename | Address |
| :--- | :--- | :--- |
| 1 | Ram | Delhi |
| 2 | Varun | Chd |
| 3 | Ravi | Chd |
| 4 | Amrit | Delhi |

`Dept(DepNo, Location, Eno)`:

| DepNo | Location | Eno |
| :--- | :--- | :--- |
| D1 | Delhi | 1 |
| D2 | Pune | 2 |
| D3 | Patna | 4 |

The join condition requires matching `Eno` *and* matching `Address` to `Location`. Looking at the data, Eno 1 (Ram, Delhi) matches Dept D1 (Delhi, 1). The result isolates this pairing.

### Self Join

![Self join: students enrolled in at least two courses (Study aliased T1,T2).](assets/join_self.jpg)

A self join is a table joined to itself, which strictly requires using aliases to differentiate the two instances. 

Consider the query: "Student ids enrolled in $\ge 2$ courses".
`Study(S_id, C_id, Since)`:

| S_id | C_id | Since |
| :--- | :--- | :--- |
| S1 | C1 | 2016 |
| S2 | C2 | 2017 |
| S1 | C2 | 2017 |

To find students with multiple courses, the table is paired with itself, matching the student ID while ensuring the course IDs are different.
SQL equivalent: `SELECT T1.S_id FROM Study T1, Study T2 WHERE T1.S_id=T2.S_id AND T1.C_id<>T2.C_id`

### Outer Joins

Inner joins discard rows that do not find a match. Outer joins keep unmatched rows from one or both tables, padding the missing columns from the other side with `NULL`.

Consider these tables:
`Emp(Emp_no, E_name, Deptno)`:

| Emp_no | E_name | Deptno |
| :--- | :--- | :--- |
| E1 | Varun | D1 |
| E2 | Amrit | D2 |
| E3 | Ravi | D1 |
| E4 | Nitin | NULL |

`Dept(Dept_No, D_name, Loc)`:

| Dept_No | D_name | Loc |
| :--- | :--- | :--- |
| D1 | IT | Delhi |
| D2 | HR | Hyd |
| D3 | Finance | Pune |
| D4 | Testing | Noida |

![Left outer join: every left row, unmatched right columns become NULL.](assets/join_left.jpg)

- **LEFT OUTER JOIN**: Keeps all rows from the left table (`Emp`), plus any matches from the right. Here, employee E4 (Nitin) has a `NULL` department and will not match anything, but is still kept in the result, with the department columns padded as `NULL`.
`SELECT emp_no, e_name, d_name, loc FROM emp LEFT OUTER JOIN dept ON emp.deptno=dept.dept_no`

![Right outer join.](assets/join_right.jpg)

- **RIGHT OUTER JOIN**: Keeps all rows from the right table (`Dept`), plus any matches. Departments D3 (Finance) and D4 (Testing) have no employees, but are kept in the result, with employee columns padded as `NULL`.

- **FULL OUTER JOIN**: The union of a left outer join and a right outer join. It keeps all rows from both tables, padding with `NULL`s wherever there is no match.
