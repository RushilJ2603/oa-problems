# The Relational Model: Tables and Keys


## Relations, schema and tables

In the relational model a **schema** is the *logical representation* of the
data, and data is held in **tables** (relations) of rows and columns. SQL's
**data-definition language (DDL)** is the sub-language used to declare these
tables. Two small schemas recur as running examples:

| Student | | |
|:--|:--|:--|
| **Rollno** | **name** | **address** |

| Course | | |
|:--|:--|:--|
| **Cid** | **Name** | **Definition** |

Each table fixes a set of named columns; each row is one record conforming to
that structure.

## Keys and candidate keys

A **key** is an attribute — or set of attributes — whose purpose is to
**uniquely identify** a row (tuple) of a table. The idea mirrors the way a person
can be pinned down by any one of several real-world identifiers: an Aadhaar card
number, a roll number, a registration number, a driving-licence number, a voter
ID, a phone number or an email address. Each of these can single out one
individual, so each is a candidate to serve as the table's key — a **candidate
key**.

Consider a *Student* table:

| Rollno | Sname | City      | Age |
|:------:|:------|:----------|:---:|
| 1      | Reddy | Hyderabad | 20  |
| 2      | Pragna| Kurnool   | 21  |
| 3      | Reddy | Hyderabad | 20  |

The values of *Sname*, *City* and *Age* repeat — rows 1 and 3 share `Reddy`,
`Hyderabad`, `20` — so none of those columns can reliably distinguish a row.
*Rollno*, however, is unique to each student and so qualifies as a candidate key.

::: {.definition}
**Definition.** A *candidate key* is a minimal set of attributes that can
uniquely identify every tuple of a relation. A relation may have several
candidate keys.
:::

## Super keys and how to count them

A **super key** is any combination of attributes that can uniquely identify the
tuples of a table. Equivalently, **any superset of a candidate key is a super
key**: once a set of columns is enough to identify a row, adding further columns
keeps it sufficient.

Suppose a relation $R(A_1, A_2, A_3, \ldots, A_n)$ has $n$ attributes, and take
the candidate key to be the single attribute $A_1$ (for instance, *Rollno* in a
relation with attributes *Rollno*, *name*, *age*). Every super key is then a
subset of the attributes that **contains $A_1$**. The number of such subsets is
obtained by freely choosing whether to include each of the remaining $n-1$
attributes:

$$ \#\,\text{super keys} = 2^{\,n-1}. $$

With the three attributes *Rollno*, *name*, *age* and candidate key *Rollno*,
this gives $2^{3-1} = 4$ super keys, exactly those listed:
$\{\text{Rollno}\}$, $\{\text{Rollno}, \text{name}\}$,
$\{\text{Rollno}, \text{age}\}$ and $\{\text{Rollno}, \text{name}, \text{age}\}$.

When a relation has **more than one** candidate key, the super keys are counted
by inclusion–exclusion over the candidate keys. If $A_1$ and $A_2$ are *both*
(single-attribute) candidate keys, then a super key is any subset that contains
$A_1$ **or** $A_2$:

$$ \#\,\text{super keys} = 2^{\,n-1} + 2^{\,n-1} - 2^{\,n-2}, $$

where the two $2^{\,n-1}$ terms count the subsets containing $A_1$ and those
containing $A_2$, and the $2^{\,n-2}$ term removes the subsets counted twice —
those containing **both** $A_1$ and $A_2$.

The same reasoning extends to *composite* candidate keys. If the two candidate
keys are the pairs $\{A_1, A_2\}$ and $\{A_3, A_4\}$ (disjoint, two attributes
each), then

$$ \#\,\text{super keys} = 2^{\,n-2} + 2^{\,n-2} - 2^{\,n-4}, $$

the subsets containing $\{A_1,A_2\}$ plus those containing $\{A_3,A_4\}$, less
the subsets containing all four.

::: {.keypoint}
**Key point.** Count super keys by counting attribute subsets that contain *at
least one whole candidate key*. One single-attribute candidate key gives
$2^{\,n-1}$; for several candidate keys, apply inclusion–exclusion.
:::

## Primary keys and alternate keys

Among the candidate keys, the designer selects **one** to serve as the
**primary key**; the candidate keys not chosen become **alternate** (alternative)
keys. The defining property of the primary key is compact:

$$ \textbf{Primary key} = \text{Unique} + \text{Not Null}. $$

It must be **unique** — no two rows may share its value — and **not null** —
every row must have a value for it. (Each candidate key already satisfies "unique
and not null"; the primary key is simply the one promoted to identify the
relation.) This yields the key hierarchy: every primary key is a candidate key,
and every candidate key is a super key.

::: {.trap}
**Trap.** A super key need not be minimal — `{Rollno, name}` is a super key but
not a candidate key, because *Rollno* alone already suffices. A candidate key is
a *minimal* super key; the primary key is the *chosen* candidate key.
:::
