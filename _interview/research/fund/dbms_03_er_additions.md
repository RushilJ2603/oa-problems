## Degree of Relationship (Cardinality)

In entity-relationship modeling, the concept of cardinality determines the quantitative nature of an association between entity sets. Think of cardinality as the "allowable connections" between items in two different buckets. For instance, can one item in a bucket connect to many in another bucket, or is it strictly a one-to-one pairing? The formal term for this is the degree of relationship.

::: definition
**Cardinality (Degree of Relationship)**: The number of entity instances that can associate across a relationship.
:::

There are four primary types of cardinality ratios: **1:1**, **1:M**, **M:1**, and **M:N (M-M)**.

To illustrate these concepts, consider a relationship where an `Employee` works for a `Department`. The `Works` relationship connects the two entity sets.

![Degree of relationship (cardinality) and the one-to-one mapping: an Employee–Works–Department example where the merged table's primary key may be either Eid or Did.](assets/er_cardinality.jpg)

Consider the following sample entity instances:

**Employee(Eid, Ename, age)**

| Eid | Ename | age |
|---|---|---|
| E1 | A | 20 |
| E2 | B | 25 |
| E3 | C | 28 |
| E4 | A | 24 |
| E5 | B | 25 |

**Department(Did, Dname, Loc)**

| Did | Dname | Loc |
|---|---|---|
| D1 | IT | Bang |
| D2 | Bhopal | Delhi |
| D3 | HR | Delhi |

In some relationships, properties do not belong exclusively to either entity set but instead characterize the relationship itself.

::: definition
**Descriptive Attribute**: An attribute on the relationship diamond itself. It records a property of the association, such as the `Date` an order was placed, which belongs neither strictly to the customer nor to the order, but to the event of giving the order.
:::

## ER-to-Relational Mapping Rules

Once an ER diagram is constructed, it must be translated into tables (relations). This is the true payoff of the design process. The overarching goal of this mapping is to minimize the total number of tables required without losing information.

::: heavy
**The Golden Rule of ER Mapping**
The placement of foreign keys and the absorption of relationship tables depends entirely on the cardinality. The fundamental objective is to reduce the number of resulting tables whenever mathematically sound.
:::

### 1:1 Mapping

In a 1:1 relationship, each entity on one side connects to at most one entity on the other. 

**Rule**: Combine into ONE table (or keep two and add the other's key as a foreign key on either side). 
**Primary Key**: If merged into a single table, the primary key can be **either Eid or Did**. 
Because 1:1 relationships offer maximal flexibility, the minimum tables question is straightforward: you often can merge them to reduce the count.

### 1:M Mapping

Consider a customer placing multiple orders: `Customer(1)`–`Give`–`Order(M)`.

**Rule**: Put the foreign key (which is the primary key of the "1" side) onto the "**many**" side. The relationship table itself is **absorbed** to reduce the overall number of tables.

![Mapping a one-to-many relationship (Customer–Give–Order) to tables: the foreign key is placed on the 'many' side and the relationship table is absorbed.](assets/er_one_many.jpg)

Given the following sample data:

**Customer(ID, Name, City)**

| ID | Name | City |
|---|---|---|
| C1 | A | Tal |
| C2 | B | Delhi |
| C3 | C | Mum |
| C4 | A | Mum |

**Order(O_no, item_name, Cost)**

| O_no | item_name | Cost |
|---|---|---|
| O1 | Bucket | 1000 |
| | Shoes | 2000 |
| O3 | Shirt | 1500 |
| O4 | Jeans | 2000 |

If the relationship `Give(ID, O_no, Date)` includes `Date` as a descriptive attribute, the mapping absorbs `Give` into the `Order` table. The foreign key `Customer.ID` migrates into `Order` along with the `Date` attribute. 

**Resulting Tables**: **2 tables**.
The primary key of the absorbed table is the primary key of the "many" side: **PK = O_no**.

### M:N Mapping

Consider students taking multiple courses, and courses having multiple students: `Student(M)`–`Study`–`Course(N)`.

::: trap
**The "Absorb M:N" Fallacy**
Attempting to absorb an M:N relationship into either participating table will result in massive data redundancy and insert anomalies. M:N relationships **cannot reduce**.
:::

**Rule**: You MUST create a separate relationship (junction) table holding both keys. The primary key of this new table is a **composite {both keys}**. The overarching principle is: "PK sits in the Referencing table / Relationship."

![Mapping a many-to-many relationship (Student–Study–Course): a separate relationship table is required, with a composite primary key {Rollno, C_id}.](assets/er_many_many.jpg)

Given the following sample data:

**Student(Rollno, name, age)**

| Rollno | name | age |
|---|---|---|
| 1 | A | 16 |
| 2 | B | 17 |
| 3 | A | 16 |
| 4 | D | 17 |
| 5 | - | 15 |

**Course(C_id, name, Credit)**

| C_id | name | Credit |
|---|---|---|
| C1 | Maths | 4 |
| C2 | Phy | 4 |
| C3 | Chem | 4 |
| C4 | Hindi | 4 |

The relationship `Study(Rollno, C_id)` contains the following pairings:
`1 C1, 2 C2, 1 C2, 2 C3, 3 C1`

Because this is an M:N relationship, no reduction is possible ("M-N = No Reduction"). 
**Composite Key**: **Rollno + C_id**.

## Weak Entity Sets

In database design, an entity must typically possess a unique identifier. However, some entities exist only in relation to another entity and lack a sufficient identifier of their own. For example, a company might track employee dependents, but dependent names are only unique within a specific employee's family.

![Weak entity set: properties (no key of its own, existence dependency, total participation, partial key).](assets/er_weak_def.jpg)

::: definition
**Weak Entity**: An entity that has **no primary key of its own**. It cannot be identified independently and **depends on an owner (strong) entity**.
:::

Key characteristics of a weak entity set include:

1. **Total Participation**: Also known as existence dependency, a weak entity must participate totally in its **identifying relationship** with the owner. It cannot exist without the owner.
2. **Partial Key**: Also known as a discriminator, this is a set of attributes that distinguish the weak entity's tuples *within* one owner.

![Weak-entity notation: double rectangle (weak entity), double diamond (identifying relationship), dashed underline (partial key).](assets/er_weak_notation.jpg)

**Notation**:

- Weak entity = **double rectangle**
- Identifying relationship = **double diamond**
- Partial key attribute = **dashed/dotted underline (dashed ellipse)**
- Total participation = **double line**

![Weak entity Dependent identified through the owner Employee via the identifying relationship Has, with total participation.](assets/er_weak_example.jpg)

Consider the example `Employee` —(`Has`)— `Dependent`. 

- `Employee` is the owner (strong entity) with `E_Id` (key) and `Address`. 
- `Dependent` is the weak entity with `Name` and `Age`. 
- `Has` is the identifying relationship (double diamond). 
- `Dependent` participates totally (TP).

Sample `Dependent` tuples, identified per owner:
`E1,A,16; E1,B,17; E2,A,18`

**Mapping a weak entity to a table**:
To represent a weak entity in a relational schema, the weak-entity table equals the **owner's PK (e.g. EID) + partial key (e.g. Name) + its own attributes**. 
The resulting table has a **composite PK = {owner PK, partial key}**. 
Thus, the mapped table becomes `Dependent(EID, Name, age)`.

## Worked Problems

### Minimum-Tables Question
A classic Lec-22 and competition-exam favourite tests the understanding of ER mapping reductions.

**Setup**: Consider entities $E_1$, $E_2$ (and $A$, $B$ as their key/attribute ellipses), and relationships $R_1$ (between them, cardinalities $M$ and $N$ or $1$ and $M$ as drawn) and $R_2$. 

**Question**: "What is the minimum number of tables required to represent this E-R model into the Relational Model? a) 2 b) 3 c) 4 d) 5."

![Minimum-tables question: the E-R model reduces to three relations (T1=E1, T2=R1·E2, T3=R2).](assets/er_min_tables.jpg)

**Answer**: **(b) 3**

**Reduction Reasoning**: 

- A strong entity always requires its own table ($T_1 = E_1$).
- A 1:M relationship folds the many side and the relationship together. Therefore, $E_2$ and $R_1$ combine to form the second table ($T_2 = R_1 \cdot E_2$).
- A many-to-many relationship cannot be absorbed and requires a separate table ($T_3 = R_2$).

### GATE-2018 ER Reasoning Question
This Lec-23 problem tests the logical consequences of cardinality constraints and total participation.

**Question**: "In an ER model, suppose $R$ is a **many-to-one** relationship from entity set $E_1$ to entity set $E_2$. Assume $E_1$ and $E_2$ **participate totally** in $R$ and that the **cardinality of $E_1$ is greater than the cardinality of $E_2$**. Which one is true about $R$?"

**Options**:
(A) Every entity in $E_1$ is associated with exactly one entity in $E_2$.
(B) Some entity in $E_1$ is associated with more than one entity in $E_2$.
(C) Every entity in $E_2$ is associated with exactly one entity in $E_1$.
(D) Every entity in $E_2$ is associated with at most one entity in $E_1$.

![GATE-2018: a many-to-one, totally participating relationship R from E1 to E2.](assets/er_gate2018.jpg)

**Answer**: **(A)**

**Reasoning**: 

- The relationship is many-to-one from $E_1$ to $E_2$, which strictly implies each $E_1$ entity maps to exactly one $E_2$ entity. This confirms option (A) and contradicts (B).
- The total participation of $E_1$ guarantees that every $E_1$ entity participates. 
- Because $|E_1| > |E_2|$, some $E_2$ entities must take several $E_1$ entities, rendering options (C) and (D) false.
