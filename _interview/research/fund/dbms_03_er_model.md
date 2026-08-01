# The Entity–Relationship Model


## Entities, attributes and relationships

The **entity–relationship (ER) model** is a high-level model for *designing* a
database. It describes a domain in terms of **entities**, their **attributes**,
and the **relationships** between entities. Because it captures the logical
design without committing to storage details, it is the natural language of the
conceptual schema.

An **entity** is an object of interest — a particular *Student*, for example. The
**entity type** (its schema) fixes the structure shared by all such entities:
`Student(Rollno, age, address)`. A **relationship** is an association between
entities; a *Student* **studies** a *Course* is a relationship between the
*Student* and *Course* entities.

ER diagrams use a small, fixed vocabulary of shapes:

- a **rectangle** denotes an **entity**;
- an **ellipse** (oval) denotes an **attribute**;
- a **diamond** denotes a **relationship**.

Lines connect attributes to their entity, and entities to the relationships they
participate in.

![ER notation. An entity is drawn as a rectangle (here *Student* and *Course*), an attribute as an ellipse, and a relationship as a diamond linking entities (*Student* — studies — *Course*). The entity type `Student(Rollno, age, address)` gives the structure shared by all student entities.](assets/fig10.png)

## Types of attributes

Attributes are classified along several independent dimensions; an attribute can
sit on either side of each.

1. **Single-valued versus multivalued.** A single-valued attribute holds exactly
   one value per entity (an *age*). A **multivalued** attribute may hold several
   (a *mobile number*, since one person may have many). It is drawn as a
   **double ellipse**.
2. **Simple versus composite.** A simple (atomic) attribute cannot be subdivided.
   A **composite** attribute decomposes into meaningful parts — a *student name*
   into first, middle and last name.
3. **Stored versus derived.** A stored attribute is kept as-is (*date of
   birth*). A **derived** attribute is computed from others (*age*, obtained from
   the date of birth) and is drawn as a **dashed ellipse**.
4. **Key versus non-key.** A **key** attribute uniquely identifies the entity
   (*roll number*) and is shown **underlined**; a non-key attribute does not.
5. **Required versus optional.** A required attribute must always carry a value;
   an optional one may be left empty.
6. **Complex.** A **complex** attribute is the combination of *composite* and
   *multivalued* — for instance, a set of addresses each of which itself has
   parts.

![Types of attributes on a *Student* entity: a multivalued *mobile number* (double ellipse), a composite *student name* (first/middle/last), a stored *date of birth* from which *age* is derived (dashed ellipse), and the key *roll number* (underlined).](assets/fig11.png)

::: {.keypoint}
**Key point.** The six attribute dimensions: single-valued/multivalued,
simple/composite, stored/derived, key/non-key, required/optional, and the
*complex* attribute (composite **and** multivalued together).
:::
