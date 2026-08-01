# Foreign Keys and Referential Integrity


## Foreign keys: referenced and referencing relations

A **foreign key** is an attribute — or set of attributes — in one relation that
**references the primary key** of the same relation or another relation. Its job
is to maintain **referential integrity**: to guarantee that a reference always
points at something that exists.

Two roles appear whenever a foreign key is present. The **referenced** relation
(also called the *base* or *parent* table) is the one whose primary key is being
pointed at; the **referencing** relation (the *child* table) is the one that
holds the foreign key. A foreign key may even reference its own table.

Take a *Student* table whose primary key is *Rollno*, and a *Course* table whose
*Rollno* column is a foreign key onto it:

| Student | | |
|:------:|:--|:--|
| **Rollno** (PK) | **name** | **address** |
| 1 | A | Delhi  |
| 2 | B | Mumbai |
| 3 | A | Chd    |

| Course | | |
|:--|:--|:------:|
| **Cuid** | **Cuname** | **Rollno** (FK) |
| C1 | DBMS    | 1 |
| C2 | Network | 2 |

Here *Student* is the referenced (parent) relation and *Course* the referencing
(child) relation. A *Course* row may only carry a *Rollno* that actually exists
in *Student*; a value such as `10`, absent from *Student*, would violate
referential integrity.

![Foreign keys. *Student.Rollno* is the primary key of the referenced (base) table; *Course.Rollno* is a foreign key in the referencing table. The constraint may be declared inside `CREATE TABLE` or added later with `ALTER TABLE ... ADD CONSTRAINT`.](assets/fig07.png)

## Declaring a foreign key

A foreign key can be declared as part of the table definition:

```sql
create table Course (
    Cuid    varchar(10),
    Cuname  varchar(20),
    Rollno  int references Student(Rollno)
);
```

or added to an existing table afterwards:

```sql
alter table Course
    add constraint fk foreign key (Rollno) references Student(Rollno);
```

## Which operations can violate referential integrity

A foreign key links two tables, so an operation on *either* table may threaten
the link. Whether a given operation can cause a violation depends on which table
it touches.

**On the referenced (parent) table:**

- **Insert** — *never* violates. Adding a new parent row leaves every existing
  reference valid.
- **Delete** — *may* violate, because child rows might still point at the deleted
  parent. This case is governed by the referential actions below.
- **Update** of the referenced key — *may* violate, for the same reason as
  delete.

**On the referencing (child) table:**

- **Insert** — *may* violate, if the new foreign-key value has no matching parent
  row.
- **Delete** — *never* violates. Removing a child row breaks no reference.
- **Update** — *may* violate, if the foreign key is changed to a value with no
  matching parent.

![The operations that can violate referential integrity. On the referencing table, *insert* and *update* may violate while *delete* cannot; on the referenced table, *delete* (and update of the key) may violate while *insert* cannot — handled via `ON DELETE CASCADE / SET NULL / NO ACTION`.](assets/fig08.png)

::: {.keypoint}
**Key point.** Danger lies in two places: **inserting/updating the child** (the
reference may point nowhere) and **deleting/updating the parent** (existing
references may be orphaned). Inserting a parent and deleting a child are always
safe.
:::

## Referential actions on delete

When a delete (or key update) on the referenced table would orphan child rows,
the foreign-key declaration specifies what to do:

- **`ON DELETE CASCADE`** — delete the dependent child rows as well.
- **`ON DELETE SET NULL`** — set the children's foreign-key value to null.
- **`ON DELETE NO ACTION`** — reject the operation (the default behaviour).

## Worked example: a referential-integrity question

A standard examination question (UGC NET, July 2018) tests exactly this
asymmetry.

> Let $R_1(a, b, c)$ and $R_2(x, y, z)$ be two relations in which $a$ is a
> foreign key in $R_1$ that refers to the primary key of $R_2$. Consider the four
> operations: (a) insert into $R_1$, (b) insert into $R_2$, (c) delete from
> $R_1$, (d) delete from $R_2$. Which operations can cause a violation of
> referential integrity?

Here $R_1$ is the referencing relation and $R_2$ the referenced one. Applying the
rules above: inserting into the referencing relation $R_1$ — operation (a) — may
violate, since $a$ might name a key absent from $R_2$; and deleting from the
referenced relation $R_2$ — operation (d) — may violate, since rows of $R_1$ may
still reference the deleted key. Inserting into the referenced $R_2$ (b) and
deleting from the referencing $R_1$ (c) are always safe. The operations that can
cause a violation are therefore **(a) and (d)**.

![The UGC NET (July 2018) question. With $a$ a foreign key in $R_1$ referencing the primary key $x$ of $R_2$, the violating operations are *insert into $R_1$* (the referencing relation) and *delete from $R_2$* (the referenced relation) — options (a) and (d).](assets/fig09.png)

## In practice: `ON DELETE CASCADE` and the `ORA-02291` error

The same rules show up directly at the SQL prompt. A child table can be created
with a cascading foreign key onto an `emp` table:

```sql
create table salary_detail (
    id     int references emp(id) on delete cascade,
    salary int
);
```

```sql
create table dependent (
    id              int references emp(id) on delete cascade,
    dependent_name  char(10)
);
```

Both `salary_detail.id` and `dependent.id` reference `emp(id)`; thanks to
`ON DELETE CASCADE`, deleting an employee automatically removes that employee's
salary and dependent rows.

Inserting a child row whose foreign key has no matching parent is the violating
case from Section 6.3. Attempting

```sql
insert into salary_detail values (10, 10000);
```

when no employee with `id = 10` exists is rejected by Oracle with

```text
ORA-02291: integrity constraint (...) violated - parent key not found
```

— the database refusing an insert into the referencing table that would dangle.

::: {.trap}
**Trap.** `ON DELETE CASCADE` makes a delete on the *parent* succeed by removing
children; it does nothing for the *insert-into-child* case, which still fails
with `ORA-02291` whenever the referenced parent key is missing.
:::
