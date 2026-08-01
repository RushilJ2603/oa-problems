# Introduction to Database Systems


## Data, databases, and the DBMS

A **database system** is best understood as two cooperating parts: the
*database* — the data itself — and the *database management system* (DBMS) — the
software that operates on that data. The two are routinely conflated in casual
speech, but separating them clarifies almost everything that follows.

A **database** is an organised collection of *related* data. The relatedness
matters: a database is not a heap of arbitrary files but a structured body of
information about some domain — a railway reservation system, a university's
records, and so on. The data a system manages ranges from highly **structured**
data (the rows and columns of a railway booking system such as IRCTC, or a
university's student records) through **unstructured** data to raw **web pages**.
A relational database management system (**RDBMS**) is the variety specialised
for structured, tabular data.

A **DBMS** is the software layer that performs **operations** on the database —
storing, retrieving, updating and protecting the data, and mediating access to
it. Widely used systems include Oracle (in its 9i, 11g and 12c releases),
Microsoft SQL Server, MySQL and IBM DB2.

![A database system divides into the *database* — a collection of related data, ranging from structured records to unstructured content and web pages — and the *DBMS*, the software that performs operations on it.](assets/fig01.png)

::: {.definition}
**Definition.** A *database* is an organised collection of related data. A *DBMS*
is the software that stores, manipulates and controls access to that data.
Together they constitute a *database system*.
:::

## File systems versus a DBMS

Before databases, data lived in ordinary files managed by the operating system's
file system. A DBMS earns its place by improving on the file-system approach
along several axes, each of which is also a classic disadvantage of relying on
bare files.

**Volume and scale.** A flat file is comfortable for small amounts of data —
think of a few kilobytes — but degrades badly as data grows. A DBMS is built to
organise and query very large volumes (gigabytes and far beyond) efficiently.

**Structure and attributes.** A DBMS stores data with an explicit structure —
named attributes (columns) of defined types — so that the meaning of each field
is known to the system. A file system imposes no such structure on the bytes it
holds.

**Concurrency.** Real systems are accessed by many users at once. The DBMS must
coordinate the four kinds of overlapping access between two transactions —
read–read (RR), read–write (RW), write–read (WR) and write–write (WW) — so that
simultaneous use does not corrupt the data. File systems offer no such
concurrency control.

**Security.** A DBMS enforces fine-grained, **role-based access control**:
different roles see and may touch only the data appropriate to them. The same
underlying data may be exposed differently to a *student*, a *faculty* member and
a *dean*; the system decides who can access what. Bare files cannot express this.

**Redundancy.** Keeping data in scattered files invites duplication — the same
fact stored in several places, drifting out of agreement over time. A DBMS
reduces such redundancy and the inconsistencies it breeds.

![File system versus DBMS. A DBMS wins on scale (kilobytes versus gigabytes), on imposing attributes/structure, on controlling concurrent access (RR, RW, WR, WW), and on role-based access control under which a *student*, *faculty* and *dean* each see only their slice of the data.](assets/fig02.png)

::: {.keypoint}
**Key point.** The advantages of a DBMS over a file system are, in one breath:
scale, enforced structure, concurrency control, security through role-based
access, and reduced redundancy.
:::

## Data models

A **data model** is the abstract framework that determines how data is
structured and related. Several families have been used historically; the course
names five:

- **Network model** — records linked into a graph of owner–member sets.
- **Hierarchical model** — records arranged in a parent–child tree.
- **Relational model** — data held in tables (relations) of rows and columns;
  the dominant model and the one underlying everything in these notes.
- **Entity–Relationship (ER) model** — a high-level *design* model of entities
  and the relationships between them (treated in detail in Section 3).
- **Object-oriented model** — data represented as objects, as in object-oriented
  programming.
