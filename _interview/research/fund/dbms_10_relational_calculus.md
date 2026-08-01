# Relational Calculus

## Introduction to Tuple Relational Calculus

Unlike relational algebra, which functions as a procedural query language dictating the sequence of operations, Tuple Relational Calculus (TRC) is a non-procedural, or declarative, query language. It specifies what data to retrieve without defining how to execute the retrieval.

::: definition
**Tuple Relational Calculus (TRC)**
A declarative query language where queries are expressed as predicate formulas. A TRC expression takes the form $\{t \mid P(t)\}$, representing the set of all tuples $t$ for which the predicate $P(t)$ evaluates to true.
:::

![Tuple relational calculus: predicate formulas with ∃ and ∀ quantifiers.](assets/trc_intro.jpg)

In TRC, the predicate $P$ is constructed from atomic formulas that compare attributes and constants. These atomic formulas are combined using logical connectives:

- **OR** ($\lor$)
- **AND** ($\land$)
- **NOT** ($\neg$)

TRC also relies on quantifiers to express conditions over entire relations:

- $\exists t \in r (Q(t))$: The existential quantifier states that "there exists a tuple $t$ in relation $r$ such that $Q(t)$ is true."
- $\forall t \in r (Q(t))$: The universal quantifier states that "$Q(t)$ is true for all tuples $t$ in relation $r$."

::: keypoint
Although they utilize completely different paradigms, Tuple Relational Calculus and Relational Algebra have the exact same expressive power. Any query formulated in one language can be translated into the other.
:::

## Safety in Relational Calculus

A fundamental requirement for evaluating declarative queries is ensuring they yield finite results. Because TRC allows arbitrary logical predicates, it introduces the risk of generating infinite sets.

::: trap
**Unsafe Expressions**
An expression is considered unsafe if it can produce an infinite relation. For example, the query $\{s.\text{name} \mid \neg \text{Supplier}(s)\}$ attempts to retrieve all names of entities that are not suppliers. Because the theoretical domain of names is infinite, this predicate yields an infinitely large result set that a database system cannot compute.
:::

To ensure computability, database systems restrict queries to safe expressions. A safe expression guarantees that its results are drawn exclusively from the database domain—the finite set of constants present in the database relations or in the query itself.

## TRC Query Formulation: Worked Examples

To demonstrate TRC query formulation, consider a database schema managing suppliers, parts, and a catalog:

- `Supplier(S)`
- `Parts(P)`
- `Catalog(C)` (The `Catalog` relation links a supplier to a part).

![TRC practice queries over Supplier / Parts / Catalog.](assets/trc_examples.jpg)

### Basic Retrieval Queries

**Q1: Sname of suppliers**
The query defines a result containing the name attribute drawn from the `Supplier` relation.
$$ \{S.\text{name} \mid \text{Supplier}(S)\} $$

**Q2: Pname of parts whose colour is Red**
This query applies a logical AND connective to enforce an equality condition on the color attribute of the `Parts` relation.
$$ \{P.\text{name} \mid \text{Parts}(P) \land P.\text{color} = \text{'Red'}\} $$

**Q3: SID of suppliers named 'Varun' at 'Chandigarh'**
Multiple attribute conditions are evaluated simultaneously.
$$ \{S.\text{Sid} \mid \text{Supplier}(S) \land S.\text{name} = \text{'Varun'} \land S.\text{address} = \text{'Chandigarh'}\} $$

### Queries with Existential Quantifiers

When a query spans multiple relations, existential quantifiers ($\exists$) are used to assert the existence of related tuples in linking tables.

::: heavy
**Q4/Q5: Suppliers who supplied some part**
To find suppliers present in the `Catalog`, the query checks for the existence of a matching catalog tuple linked by the supplier ID (`Sid`). 
$$ \{S.\text{Sid} \mid \text{Supplier}(S) \land \exists c(\text{Catalog}(c) \land c.\text{Sid} = S.\text{Sid})\} $$
A variant of this query returning the `Sname` simply modifies the projection attribute before the vertical bar.
:::

![A TRC expression for suppliers who supply some red part.](assets/trc_formula.jpg)

**Q6: Sname of suppliers who supplied some RED part**
This query requires navigating from the supplier, through the catalog, to the parts relation. It nests existential quantifiers to locate a catalog entry bridging the supplier and a part, and then verifies the part is 'Red'.
$$ \{S.\text{name} \mid \text{Supplier}(S) \land \exists c(\text{Catalog}(c) \land c.\text{Sid} = S.\text{Sid} \land \exists p(\text{Parts}(p) \land p.\text{pid} = c.\text{pid} \land p.\text{color} = \text{'Red'}))\} $$

### Domain Relational Calculus

Domain Relational Calculus serves as the variable-per-attribute cousin to Tuple Relational Calculus. Rather than binding variables to entire tuples, Domain Relational Calculus binds variables to single attributes or domains. It is important to note that Domain Relational Calculus shares the exact same expressive power as both Tuple Relational Calculus and Relational Algebra.
