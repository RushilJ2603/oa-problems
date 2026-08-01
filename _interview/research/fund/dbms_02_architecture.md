# Database Architecture


## The three-schema (ANSI/SPARC) architecture

The **three-schema architecture** organises a database into three *levels of
abstraction*. Its purpose is **data independence**: insulating each level from
changes in the one beneath it, so that, for instance, altering how data is
physically stored need not break the applications that use it.

**External (view) level.** This is what individual users see. There may be many
**external schemas**, each a tailored view of the database for a particular kind
of user. A *student*, a *faculty* member and a *dean* may each be presented with
a different view of the same database; in a corporate setting, HR might see
salaries while IT sees passwords.

**Conceptual (logical) level.** The single **conceptual schema** is the logical
map of the *whole* database — its tables, the relationships among them, and the
rules they obey. It is the level at which the ER and relational models operate.

**Internal (physical) level.** The **physical schema** describes how the data is
actually stored on disk: the files, the byte layout, and the access structures
such as indexes and B-trees. Beneath it lies the database itself, on the disk.

![The three-schema architecture. Many external schemas (one per class of user) sit at the view level; a single conceptual schema captures the logical structure (tables, relationships — the ER/relational design) at the logical level; the physical schema describes on-disk storage at the internal level; the database resides on the disk below.](assets/fig04.png)

::: {.definition}
**Definition.** A *schema* is the **description** — the logical representation —
of a database's structure, fixed at design time; for example
`Student(Rollno, name, age, address)`. The data values that populate the schema
at a given moment are its *instance*.
:::

## Data independence

The pay-off of separating the three levels is **data independence**, which comes
in two grades.

**Logical data independence** is the capacity to change the *conceptual* schema —
adding a table, splitting a relation — without disturbing the external schemas
and the applications built on them. It is realised chiefly through **views**, and
is the harder of the two to achieve in practice because applications depend so
directly on the logical structure.

**Physical data independence** is the capacity to change the *physical* schema
without touching the conceptual schema. Typical such changes are reorganising the
**storage structure**, switching the underlying **data structure**, and adding or
dropping an **index**. None of these should require the logical design — or the
applications — to change.

![Data independence. *Logical* data independence (via views) shields the external/view level from changes to the conceptual schema; *physical* data independence shields the conceptual schema from changes to physical storage — storage structure, data-structure changes, and indexing.](assets/fig05.png)

## Two-tier and three-tier architecture

Where the three-schema architecture concerns how data is *organised*, the
**tiered architectures** concern where software *runs* — how an application's
parts are distributed.

In a **two-tier** architecture, client machines — the interface or client
application — talk **directly** to the database server. There are only two
layers: the clients and the database.

In a **three-tier** architecture a middle layer is interposed:

- **Client (presentation) layer** — the client applications, the user interface.
- **Application (business) layer** — an application server that holds the
  business logic.
- **Data layer** — the data source: the database server.

Clients send requests to the application server, which in turn talks to the data
source. The extra tier separates user interface, business logic and data
storage, which aids scalability and keeps concerns from tangling together.

![Two-tier versus three-tier. Left: clients connect straight to the database server. Right: a client (presentation) layer talks to an application server (business layer), which talks to the data source (data layer).](assets/fig03.png)

## Three-schema versus three-tier: a common confusion

The two architectures sound alike and are constantly muddled, yet they describe
different things. The three-schema architecture is about **how data is hidden and
organised** inside a DBMS; the three-tier architecture is about **where software
code actually runs**. The cleanest way to hold them together is this: the entire
three-schema architecture lives *inside the data tier* of the three-tier
architecture.

**Three-schema architecture (ANSI/SPARC)** is a framework strictly for database
systems, and its goal is data independence — ensuring that changing how data is
physically stored does not break the application.

- *External level* — different views for different users (HR sees salaries, IT
  sees passwords).
- *Conceptual level* — the logical map of the whole database (tables,
  relationships, rules).
- *Internal level* — the actual physical storage on disk (indexes, bytes,
  B-trees).

**Three-tier architecture** is a framework for software engineering and
deployment, and its goal is separation of concerns and scalability — keeping the
user interface, the business logic and the database from being tangled together
on one server.

- *Presentation tier* — the user interface (a website or mobile app).
- *Application (logic) tier* — the backend server handling the computation and
  rules (Node.js, Python, Java).
- *Data tier* — the database server where information is kept (PostgreSQL,
  MongoDB).

The two interact continuously. When a user taps "View Profile" on a phone (the
presentation tier), the phone sends a request to the backend server (the
application tier), which asks the database (the data tier) for the user's
information. *Inside* the data tier, the three-schema architecture takes over:
the query addresses a specific view or API (the external schema), the database
translates that view into the overall table structure (the conceptual schema),
and it then retrieves the actual bytes from disk (the internal schema). The data
is handed back up the chain to the user's screen.

::: {.keypoint}
**Key point.** Three-schema is a DBMS concept about *data organisation and
independence*; three-tier is a deployment concept about *where code runs*. The
whole three-schema stack sits within the three-tier *data tier*.
:::
