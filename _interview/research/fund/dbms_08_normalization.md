# Normalization and Normal Forms

## Why Normalize: Redundancy and Anomalies

Storing everything in one single, wide table often causes massive data redundancy and introduces anomalies that corrupt the integrity of a database. 

Consider a monolithic `Student–Course–Faculty` table structure that stores `SID`, `Sname`, `Age`, `Cid`, `Cname`, `FID`, `Fname`, and `Salary` all in one place.

| SID | Sname | Age | Cid | Cname | FID | Fname | Salary |
|---|---|---|---|---|---|---|---|
| 1 | RAM | 20 | C1 | DBMS | F1 | John | 30000 |
| 2 | Ravi | - | C2 | JAVA | F2 | Bob | 40000 |
| 3 | Nitin | - | C1 | DBMS | F1 | John | 30000 |
| 4 | Amrit | - | C1 | DBMS | F1 | John | 30000 |

::: definition
**Normalization** is the process of decomposing a table into multiple related tables to remove redundancy while ensuring the decomposition is lossless.
:::

An unnormalised design suffers from three primary anomalies:

- **Insertion anomaly**: Data cannot be added without the presence of other unrelated data. For example, you cannot add a new faculty member or a new course to the system unless a student is actively enrolled in it.
- **Deletion anomaly**: Deleting a row causes unintended loss of other independent facts. Deleting the last student enrolled in a course will unintentionally lose all information about that course and its faculty.
- **Updation anomaly**: Modifying a duplicated value requires updating multiple rows. If the faculty member "John" gets a salary increase, his salary of `30000` repeated across multiple rows must be changed everywhere. Failure to do so creates inconsistent data.

![Insertion, deletion and updation anomalies in an unnormalised Student–Course–Faculty table.](assets/nf_anomalies.jpg)


## First Normal Form (1NF)

::: definition
**First Normal Form (1NF)** (defined by E.F. Codd) requires that a table must not contain any multivalued or composite attributes. Every cell must be atomic, holding exactly one single value.
:::

When attributes contain lists or sets of values, the relational model cannot process them efficiently using standard operations.

![First normal form: a table must not contain a multivalued attribute (Course = C/C++).](assets/nf_1nf.jpg)

A table not in 1NF:

| Rollno | Name | Course |
|---|---|---|
| 1 | Sai | C/C++ |
| 2 | Harsh | Java |
| 3 | Ontario | C/DBMS |

Notice that `Sai` has the value `"C/C++"` and `Ontario` has `"C/DBMS"` in the `Course` attribute. To fix this and satisfy 1NF, we split the composite strings so that there is exactly one atomic value per row:

| Rollno | Name | Course |
|---|---|---|
| 1 | Sai | C |
| 1 | Sai | C++ |
| 2 | Harsh | Java |
| 3 | Ontario | C |
| 3 | Ontario | DBMS |


## Second Normal Form (2NF)

::: definition
**Second Normal Form (2NF)** requires that the table is in 1NF AND there is no **partial dependency**. This means no non-prime attribute depends on a *proper subset* of a candidate key. Every non-prime attribute must be *fully* functionally dependent on the whole candidate key (CK).
:::

### Conceptual Example

Consider a `Customer(CustomerID, StoreID, Location)` table tracking where customers shop.

| CustomerID | StoreID | Location |
|---|---|---|
| 1 | 1 | Delhi |
| 1 | 3 | Mumbai |
| 2 | 1 | Delhi |
| 3 | 2 | Banglore |
| 4 | 3 | Mumbai |

- **Candidate Key (CK)** = `{CustomerID, StoreID}`
- **Prime attributes** = `{CustomerID, StoreID}`
- **Non-prime attributes** = `{Location}`

We can observe the functional dependency (FD) `StoreID` $\rightarrow$ `Location` (each store is located in one specific city). However, `StoreID` is only a *proper subset* of the entire candidate key `{CustomerID, StoreID}`. This creates a partial dependency. Because a non-prime attribute (`Location`) depends on just part of the candidate key, it violates 2NF. 

To fix this, we decompose the table and split `Location` into a separate `Store(StoreID, Location)` table.

![Second normal form: the partial dependency StoreID→Location in a {CustomerID,StoreID} key.](assets/nf_2nf.jpg)

### Formal Check

Let's test 2NF on relation $R(A, B, C, D, E, F)$ with the functional dependencies $FD = \{CD \rightarrow F, E \rightarrow A, EC \rightarrow D, A \rightarrow B\}$.

![2NF check on R(ABCDEF), FD{CD→F,E→A,EC→D,A→B}, CK={EC}.](assets/nf_2nf_example.jpg)

1. Find the candidate keys. We check the closure of $EC$:
   $EC^+ = E, C, F, A, D, B$ (which includes all attributes).
   Thus, $CK = \{EC\}$.
2. Identify attribute types:
   **Prime attributes** = $\{E, C\}$
   **Non-prime attributes** = $\{A, B, D, F\}$
3. Check for partial dependencies. The candidate key has subsets $\{E\}$ and $\{C\}$. We look for any FD where the left-hand side (LHS) is one of these proper subsets. 
   We find $E \rightarrow A$. Since $E \subsetneq CK$ and $A$ is a non-prime attribute, this is a partial dependency. The relation violates 2NF.


## Third Normal Form (3NF)

::: definition
**Third Normal Form (3NF)** requires that the relation is in 2NF AND there is no **transitive dependency** of a non-prime attribute on the candidate key. An equivalent test is that for every functional dependency $X \rightarrow Y$, $X$ is a superkey OR $Y$ is a prime attribute.
:::

A transitive dependency occurs when a non-prime attribute functionally determines another non-prime attribute, indirectly tying it back to the candidate key.

Consider a table with `Rollno`, `State`, and `City`:

| Rollno | State | City |
|---|---|---|
| 1 | Punjab | Mohali |
| 2 | Haryana | Ambala |
| 3 | Punjab | Mohali |
| 4 | Haryana | Ambala |
| 5 | Bihar | Patna |

- **Candidate Key (CK)** = `{Rollno}`
- **Prime attribute (PA)** = `{Rollno}`
- **Non-prime attributes (NPA)** = `{State, City}`

The functional dependencies are `Rollno` $\rightarrow$ `State` and `State` $\rightarrow$ `City`. This creates a transitive dependency: `Rollno` $\rightarrow$ `State` $\rightarrow$ `City`. 

Let's apply the equivalent 3NF test to the FD `State` $\rightarrow$ `City`:

1. Is `State` a superkey? No.
2. Is `City` a prime attribute? No.
Since both conditions fail, the transitive dependency is confirmed, and the table violates 3NF.

![Third normal form: the transitive dependency Rollno→State→City.](assets/nf_3nf.jpg)


## Boyce-Codd Normal Form (BCNF)

::: definition
**Boyce-Codd Normal Form (BCNF)** is a stricter version of 3NF. It dictates that for EVERY non-trivial functional dependency $X \rightarrow Y$, $X$ must be a superkey. In other words, the left-hand side (LHS) of every FD must be a candidate or super key.
:::

![BCNF: every FD's LHS is a candidate/super key (Student with Rollno,VoterID both keys).](assets/nf_bcnf.jpg)

Consider a `Student(Rollno, Name, VoterID, age)` relation:

| Rollno | Name | VoterID | age |
|---|---|---|---|
| 1 | Ravi | K0123 | 20 |
| 2 | Varun | M034 | 21 |
| 3 | Ravi | K786 | 23 |
| 4 | Rahul | D256 | 21 |

The FDs are: `Rollno` $\rightarrow$ `Name`, `Rollno` $\rightarrow$ `VoterID`, `VoterID` $\rightarrow$ `age`, and `VoterID` $\rightarrow$ `Rollno`.
Because `VoterID` $\rightarrow$ `Rollno` and `Rollno` $\rightarrow$ `VoterID`, both `Rollno` and `VoterID` uniquely identify the row.
The candidate keys are $CK = \{Rollno\}, \{VoterID\}$. Since every FD's LHS is one of these candidate keys, the relation is perfectly in BCNF.

::: keypoint
Because BCNF is strictly more restrictive, any relation in BCNF is automatically in 3NF, 2NF, and 1NF. The hierarchy forms a strict containment: BCNF $\subset$ 3NF $\subset$ 2NF $\subset$ 1NF.
:::

![The strict containment BCNF ⊂ 3NF ⊂ 2NF ⊂ 1NF.](assets/nf_nesting.jpg)

### The Classic "3NF but not BCNF" Trap

::: trap
It is possible for a relation to pass the 3NF test but fail BCNF. This happens when overlapping candidate keys exist.
:::

Take $R(A, B, C, D)$ with $FD = \{AB \rightarrow CD, D \rightarrow A\}$.

First, let's find the candidate keys:

- $AB^+ = A, B, C, D$
- $BD^+ = B, D, A, C$
Therefore, $CK = \{AB, BD\}$.
The prime attributes (PA) are $\{A, B, D\}$, and the non-prime attribute (NPA) is $\{C\}$.

Now evaluate the FD $D \rightarrow A$:

- Does it pass 3NF? Yes, because $D$ is not a superkey, but $A$ IS a prime attribute.
- Does it pass BCNF? No, because BCNF mandates that the LHS ($D$) MUST be a superkey. BCNF ignores whether the right side is prime.

![3NF-but-not-BCNF: R(ABCD), AB→CD, D→A.](assets/nf_3nf_not_bcnf.jpg)


## Decomposition: Lossless and Dependency-Preserving

::: heavy
When normalizing by splitting a table $R$ into fragments $R_1$ and $R_2$, two critical properties must be checked:

1. **Lossless-join**: We must not generate spurious tuples when recombining the data.
2. **Dependency-preserving**: We must not lose our ability to enforce functional constraints.
:::

### Lossless-Join Decomposition

Decomposing $R$ into $R_1$ and $R_2$ is lossless if and only if the common attribute(s) $R_1 \cap R_2$ form a superkey of $R_1$ OR of $R_2$. Otherwise, the natural join produces spurious, fake tuples, meaning the decomposition is lossy.

For example, given $R(A, B, C)$:

| A | B | C |
|---|---|---|
| 1 | 2 | 1 |
| 2 | 1 | 2 |
| 3 | 2 | 3 |

If we split this into $R_1(AB)$ and $R_2(BC)$, the common attribute is $B$. Since $B$ contains duplicate values (like `2`) and does not uniquely identify rows in either fragment, it is not a key. Consequently, $R_1 \bowtie R_2$ yields extra tuples that never existed in the original dataset.

![Lossless vs lossy decomposition: the common attribute must be a key of R1 or R2.](assets/nf_lossless.jpg)

### Dependency-Preserving Decomposition

A decomposition is dependency-preserving if the union of the projected FDs on the resulting fragments implies all the original FDs ($F_1 \cup F_2 \cup \dots = F^+$).

Consider $R(A, B, C, D)$ with $FD = \{A \rightarrow B, B \rightarrow C, C \rightarrow D, D \rightarrow B\}$.
If we decompose this into $R_1(AB)$, $R_2(BC)$, and $R_3(BD)$:
To check what dependencies survive, compute the closures over the fragments:

- $B^+ = B, C, D$
- $C^+ = C, D, B$

The fragments give us $A \rightarrow B$, $B \rightarrow C$, $C \rightarrow B$, $B \rightarrow D$, and $D \rightarrow B$. By taking the union $F_1 \cup F_2$, we see this equals $F^+$. The original constraints are fully preserved.

![Dependency-preserving decomposition of R(ABCD), FD{A→B,B→C,C→D,D→B}.](assets/nf_dep_preserve.jpg)

### The BCNF vs 3NF Guarantee

A mathematically guaranteed fact in database design:

- A **3NF decomposition** can ALWAYS be both lossless AND dependency-preserving.
- A **BCNF decomposition** is always lossless but may NOT be dependency-preserving.

Returning to the classic example $R(A, B, C, D)$ with $AB \rightarrow CD$ and $D \rightarrow A$: 
If we decompose it into BCNF fragments (e.g., separating out $DA$ and leaving a $BCD$-type fragment), we physically separate $A$ and $B$, making it impossible to evaluate and preserve the $AB \rightarrow C$ dependency within a single fragment.

![BCNF need not preserve dependencies (the classic AB→CD, D→A example).](assets/nf_bcnf_not_dp.jpg)


## Fourth Normal Form (4NF) and Multivalued Dependencies

::: definition
**Fourth Normal Form (4NF)** mandates that the table is in BCNF AND contains no non-trivial **multivalued dependency (MVD)**.
:::

A multivalued dependency $A \rightarrow\rightarrow B$ occurs when, for a single value of $A$, multiple independent values of $B$ exist. A true MVD requires:

1. $\ge 3$ columns in the table.
2. The dependency $A \rightarrow\rightarrow B$ exists.
3. The attributes $B$ and $C$ are independent of each other.

![Multivalued dependency A→→B requires ≥3 columns with B and C independent.](assets/nf_mvd.jpg)

Consider an `Enrolment(s_id, course, hobby)` table:

| s_id | course | hobby |
|---|---|---|
| 1 | Science | Cricket |
| 1 | Maths | Hockey |
| 1 | Science | Hockey |
| 1 | Maths | Cricket |

Here, the choice of `course` and `hobby` are completely independent. This means $s\_id \rightarrow\rightarrow course$ and $s\_id \rightarrow\rightarrow hobby$. The combination of independent multi-valued facts causes an explosive Cartesian product effect inside a single table. This is a BAD DESIGN and a 4NF violation.

![4NF violation: the Enrolment(s_id,course,hobby) table with independent course/hobby.](assets/nf_mvd_table.jpg)

The fix is to decompose the independent facts into their own two-column tables: `CourseOpted(s_id, course)` and `Hobbies(s_id, hobby)` (and hypothetically `Address(s_id, address)` if a third independent MVD existed).

![4NF decomposition into CourseOpted + Hobbies + Address.](assets/nf_4nf_decomp.jpg)


## Fifth Normal Form (5NF) and Join Dependencies

::: definition
**Fifth Normal Form (5NF)**, also known as Project-Join Normal Form (PJNF), dictates that the relation is in 4NF AND contains no non-trivial **join dependency**. The relation cannot be decomposed into smaller relations and rejoined without generating spurious tuples; we decompose only if the projections rejoin losslessly.
:::

A join dependency occurs when a complex ternary (three-way) relationship is irreducible. 

![A ternary Supplier–Product–Customer relationship and its three binary projections.](assets/nf_5nf_binary.jpg)

Consider a ternary `Supplier–Product–Customer` relation tracking three binary facts: {Supplier–Customer, Customer–Product, Product–Supplier}.
`SPC(supplier, product, customer)` = `(ACME, 72X SW, FORD)`.

Suppose the business rules state: 

- `ACME` sells `72X SW`
- `FORD` uses `72X SW`
- `ACME` supplies to `FORD`
which jointly implies that `ACME` sells `72X SW` to `FORD`.

If we tried to decompose this into three binary tables: `SUPP_PRO(ACME, 72X SW)`, `SUPP_CUST(ACME, FORD)`, and `CUST_PRO(FORD, 72X SW)`, and later tried rejoining these three, we might generate spurious tuples.

![Join dependency: the SPC table decomposed into SUPP_PRO, SUPP_CUST, CUST_PRO.](assets/nf_5nf_spc.jpg)

If rejoining these yields exactly the original dataset (no spurious tuple), the table is NOT in 5NF and should be decomposed. However, the shown `SPC` table "does satisfy 5NF" when a spurious tuple would otherwise appear upon trying to force it into smaller pieces.

![A relation already in 5th normal form (further decomposition would lose information).](assets/nf_5nf_satisfies.jpg)


## Summary of Normal Forms

- **1NF**: Atomic values (no multivalued attributes).
- **2NF**: 1NF + no partial dependency.
- **3NF**: 2NF + no transitive dependency ($X \rightarrow Y \Rightarrow X$ superkey or $Y$ prime).
- **BCNF**: 3NF + LHS of every FD is a superkey.
- **4NF**: BCNF + no MVD.
- **5NF**: 4NF + no lossy join dependency (lossless decomposition).

![Summary of normal-form conditions from 1NF to 5NF.](assets/nf_summary.jpg)


## Worked Problems: Highest Normal Form

To analyze an arbitrary schema and determine its highest normal form, you iteratively verify conditions starting from the strongest. 

### Arbitrary Schema Calculation

Given $R(A, B, C, D, E, F)$ with $FD = \{AB \rightarrow C, C \rightarrow D, C \rightarrow E, E \rightarrow F, F \rightarrow A\}$.

1. **Find all CKs and prime attributes**: Using closures, map out the decomposition tree (e.g., $R_1(ABCEF)$, $R_2(CD)$). 
2. **Check properties**: Test for partial and transitive dependencies.
   - For 2NF: LHS must not be a proper subset of a CK.
   - For 3NF: RHS must be a prime attribute if LHS is not a SK.
   - For BCNF: LHS must be a CK/SK.

The result typically fails BCNF and sits at a lower normal form depending on which rule breaks first.

![Finding the highest normal form of R(ABCDEF), FD{AB→C,C→D,C→E,E→F,F→A}.](assets/nf_highest.jpg)

### Schema Variants (GATE-2018)

Consider finding the highest normal form for four variants of a `Registration` schema (worth 2 marks in the GATE-2018 exam):

1. **S1: `Registration(rollno, courseid)`**
   No non-trivial dependencies exist besides the composite key itself. This is perfectly in **BCNF**.
2. **S2: `Registration(rollno, courseid, email)`, `email` $\rightarrow$ `rollno`**
   Because `email` $\rightarrow$ `rollno`, `email` acts as a candidate key (alongside the original key). Every determinant is a key. This is in **BCNF**.
3. **S3: `Registration(rollno, courseid, marks, grade)`, `marks` $\rightarrow$ `grade`**
   `marks` is a non-prime attribute determining another non-prime attribute (`grade`). This is a transitive dependency. Thus, it fails 3NF and is only in **2NF**.
4. **S4: `Registration(rollno, courseid, credit)`, `courseid` $\rightarrow$ `credit`**
   `courseid` is a proper subset of the candidate key `{rollno, courseid}` determining a non-prime attribute. This is a partial dependency. Thus, it fails 2NF and is only in **1NF**.

![GATE-2018: highest normal form of four Registration schema variants.](assets/nf_schemas_gate.jpg)
