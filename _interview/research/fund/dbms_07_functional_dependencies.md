# Functional Dependencies

## Functional Dependency Basics

::: definition
A **functional dependency** (FD), denoted as $X \rightarrow Y$, means that a set of attributes $X$ (the **determinant**) uniquely determines another set of attributes $Y$ (the **dependent**). Formally, if two tuples agree on the values of $X$, they must necessarily agree on the values of $Y$.
:::

In practical database design, a functional dependency expresses a constraint on the real-world entities modeled by the relation. If the same value for $X$ always yields the exact same value for $Y$ across all possible valid rows in the table, the functional dependency $X \rightarrow Y$ holds.

Functional dependencies can be classified into two primary categories:

- **Trivial FD**: A functional dependency $X \rightarrow Y$ is trivial if $Y \subseteq X$. For example, an attribute always determines itself. 
- **Non-trivial FD**: A functional dependency $X \rightarrow Y$ is non-trivial if the intersection of $X$ and $Y$ is empty, meaning $X \cap Y = \emptyset$.

To observe valid versus invalid functional dependencies in practice, consider a table of student information. A student ID mapping to a student name is a standard expectation. 

| Sid | Sname |
|-----|-------|
| 1   | Ranjit |
| 2   | Ranjit |
| 3   | Varun |

- **Valid FD**: `Sid` $\rightarrow$ `Sname` is valid because each `Sid` maps to exactly one `Sname`. (Both `Sid` 1 and 2 map to "Ranjit", which is perfectly valid; two different students can share a name).
- **Invalid FD**: `Sname` $\rightarrow$ `Sid` is invalid when two students share a name. The name "Ranjit" appears for `Sid` 1 and `Sid` 2. Because the same determinant value ("Ranjit") produces different dependent values (1 and 2), the functional dependency fails. Furthermore, if a second student named "Varun" were inserted into the table with a new ID, "Varun" would also map to multiple IDs.

::: trap
A common misconception is that if $X \rightarrow Y$ is valid, the reverse $Y \rightarrow X$ must also be valid. As seen with the `Sid` and `Sname` example, functional dependencies are directional and do not automatically imply their inverse.
:::

## Armstrong's Axioms

![The functional dependency X→Y (X determinant, Y dependent) and Armstrong's axioms.](assets/fd_armstrong.jpg)

When analyzing relational schemas, a database system must infer new functional dependencies from a given set of established ones. **Armstrong's axioms** provide the formal inference rules used to derive all valid functional dependencies. The rules are both sound (they never derive an incorrect dependency) and complete (they can derive every valid dependency).

The primary axioms form the foundation:

- **Reflexivity**: If $Y \subseteq X$, then $X \rightarrow Y$.
- **Augmentation**: If $X \rightarrow Y$, then $XZ \rightarrow YZ$ for any set of attributes $Z$.
- **Transitivity**: If $X \rightarrow Y$ and $Y \rightarrow Z$, then $X \rightarrow Z$.

Using the primary axioms, several additional rules can be derived to simplify computations:

- **Union**: If $X \rightarrow Y$ and $X \rightarrow Z$, then $X \rightarrow YZ$.
- **Decomposition**: If $X \rightarrow YZ$, then $X \rightarrow Y$ and $X \rightarrow Z$.
- **Pseudo-transitivity**: If $X \rightarrow Y$ and $WY \rightarrow Z$, then $WX \rightarrow Z$.
- **Composition**: If $X \rightarrow Y$ and $Z \rightarrow W$, then $XZ \rightarrow YW$.

::: keypoint
The decomposition rule allows splitting the right-hand side of a functional dependency into single attributes. However, the left-hand side can never be decomposed. If $AB \rightarrow C$, it does not imply $A \rightarrow C$ or $B \rightarrow C$.
:::

## Attribute Closure and Candidate Keys

::: heavy
**Attribute Closure**
The attribute closure of a set of attributes $X$, denoted as $X^{+}$, is the complete set of all attributes that can be functionally determined by $X$ under a specific set of functional dependencies. Computing the closure is a fundamental algorithmic step in determining candidate keys.
:::

A **candidate key** is defined as the minimal set of attributes whose closure contains all attributes of the relation. "Minimal" signifies that no proper subset of the candidate key can determine all attributes. 

Attributes are formally classified based on their membership in candidate keys:

- **Prime attribute**: An attribute that is a member of some candidate key.
- **Non-prime attribute**: An attribute that is not part of any candidate key.

### Linear FD Set Example

![Attribute-closure method for finding candidate keys: R(ABCD), FD{A→B,B→C,C→D}, CK={A}.](assets/fd_closure.jpg)

Consider a relation $R(A, B, C, D)$ with the functional dependency set $FD = \{A \rightarrow B, B \rightarrow C, C \rightarrow D\}$. 

Calculating closures systematically:

- $A^{+} = \{A, B, C, D\}$. The attribute $A$ determines $B$, $B$ determines $C$, and $C$ determines $D$.
- $B^{+} = \{B, C, D\}$.
- $C^{+} = \{C, D\}$.
- $D^{+} = \{D\}$.

Since $A^{+}$ contains all attributes of $R$, and $A$ is a single attribute (thus trivially minimal), the candidate key is $\{A\}$.

### Cyclic FD Set Example

![A cyclic FD set makes every attribute prime: R(ABCD), FD{A→B,B→C,C→D,D→A}.](assets/fd_closure_cyclic.jpg)

Consider a relation $R(A, B, C, D)$ with a cyclic functional dependency set $FD = \{A \rightarrow B, B \rightarrow C, C \rightarrow D, D \rightarrow A\}$.

Calculating closures:

- $A^{+} = \{A, B, C, D\}$
- $B^{+} = \{B, C, D, A\} = \{A, B, C, D\}$
- $C^{+} = \{C, D, A, B\} = \{A, B, C, D\}$
- $D^{+} = \{D, A, B, C\} = \{A, B, C, D\}$

Every single attribute's closure evaluates to all attributes. Therefore, the candidate keys are $\{A\}$, $\{B\}$, $\{C\}$, and $\{D\}$. In this schema, the prime attributes are $\{A, B, C, D\}$ and the non-prime attribute set is $\emptyset$.

### Multi-Attribute Keys Example

![Finding all candidate keys of R(ABCDE), FD{A→B,BC→D,E→C,D→A}: CK={AE,BE,CE,DE}.](assets/fd_candidate_keys.jpg)

Consider a relation $R(A, B, C, D, E)$ with the functional dependency set $FD = \{A \rightarrow B, BC \rightarrow D, E \rightarrow C, D \rightarrow A\}$. 

To find all candidate keys, begin by identifying any attribute that does not appear on the right-hand side of any FD. Here, $E$ never appears on the right-hand side. Consequently, no combination of other attributes can ever determine $E$. The attribute $E$ must therefore be part of every candidate key.

Test the closure of $E$:

- $E^{+} = \{E, C\}$. This is not all attributes.

Now test combinations of $E$ with other attributes:

- $AE^{+} = \{A, B, E, C, D\} = \text{all}$. (Using $A \rightarrow B$, $E \rightarrow C$, and $BC \rightarrow D$).
- $BE^{+} = \{B, E, C, D, A\} = \text{all}$. (Using $E \rightarrow C$, $BC \rightarrow D$, and $D \rightarrow A$).
- $CE^{+} = \text{all}$. 
- $DE^{+} = \{D, E, A, B, C\} = \text{all}$. (Using $D \rightarrow A$, $A \rightarrow B$, and $E \rightarrow C$).

The candidate keys are therefore $\{AE, BE, CE, DE\}$. The prime attributes are $\{A, B, C, D, E\}$, leaving the non-prime attribute set as $\emptyset$.

## Minimal (Canonical) Cover

![Computing a minimal (canonical) cover of {A→B,C→B,D→ABC,AC→D}.](assets/fd_minimal_cover.jpg)

::: heavy
**Minimal Cover**
The minimal (or canonical) cover of a functional dependency set is an equivalent set of FDs that has been reduced to its simplest possible form. Two sets are equivalent if they have the exact same attribute closures.
:::

A minimal cover must satisfy three strict conditions:

1. Every functional dependency must have a single attribute on its right-hand side.
2. There must be no redundant attributes on the left-hand side of any functional dependency.
3. There must be no redundant functional dependencies in the set.

**Worked Calculation:**
Compute the minimal cover of the set $\{A \rightarrow B, C \rightarrow B, D \rightarrow ABC, AC \rightarrow D\}$.

**Step 1: Split Right-Hand Sides**
Apply the decomposition rule so all right-hand sides are single attributes.

- $A \rightarrow B$
- $C \rightarrow B$
- $D \rightarrow A$
- $D \rightarrow B$
- $D \rightarrow C$
- $AC \rightarrow D$

**Step 2: Remove Redundant Left-Hand Side Attributes**
Analyze FDs with multiple attributes on the left-hand side. The only candidate is $AC \rightarrow D$. To test if $A$ or $C$ is redundant, calculate their closures using the other FDs.

- Is it $A \rightarrow D$ or $C \rightarrow D$? 
- Calculate $A^{+}$ without $AC \rightarrow D$: $A^{+} = \{A, B\}$. Since it does not contain $D$, $C$ is not redundant.
- Calculate $C^{+}$ without $AC \rightarrow D$: $C^{+} = \{C, B\}$. Since it does not contain $D$, $A$ is not redundant.
- Conclusion: Keep $AC \rightarrow D$.

**Step 3: Remove Redundant Functional Dependencies**
Test each single-attribute FD to see if it can be derived from the others.

- Is $D \rightarrow B$ redundant? Calculate $D^{+}$ without $D \rightarrow B$.
- Using the remaining FDs: $D \rightarrow A$ (so $D$ gives $A$) and $D \rightarrow C$ (so $D$ gives $C$). We now have $\{A, C, D\}$. Since $A \rightarrow B$ exists, $\{A, C, D\}$ gives $B$.
- Since $D^{+}$ still includes $B$ via the path $D \rightarrow A \rightarrow B$ (or $D \rightarrow C \rightarrow B$), the FD $D \rightarrow B$ is redundant and can be removed.

The resulting minimal cover is $\{A \rightarrow B, C \rightarrow B, D \rightarrow A, D \rightarrow C, AC \rightarrow D\}$.

## Equivalence of Functional Dependency Sets

![Testing equivalence of two FD sets via mutual cover (X covers Y and Y covers X).](assets/fd_equivalence.jpg)

Two sets of functional dependencies, $X$ and $Y$, are logically equivalent (denoted $X \equiv Y$) if and only if $X$ covers $Y$ and $Y$ covers $X$. A set covers another if every functional dependency in the second set can be derivable using the closures defined by the first set.

**Worked Calculation:**
Test the equivalence of the following two FD sets:

- $X = \{AB \rightarrow CD, B \rightarrow C, C \rightarrow D\}$
- $Y = \{AB \rightarrow C, AB \rightarrow D, C \rightarrow D\}$

To determine if $Y$ covers $X$, attempt to derive every FD in $X$ using the rules of $Y$.

- Take the FD $B \rightarrow C$ from set $X$.
- Compute the closure of $B$ under the rules of set $Y$.
- Under $Y$, $B^{+} = \{B\}$. No rules in $Y$ have a left-hand side that can be satisfied by just $B$.
- Because $B^{+}$ under $Y$ does not include $C$, the dependency $B \rightarrow C$ is NOT derivable.

Since $Y$ fails to derive $B \rightarrow C$, $Y$ does not cover $X$. Therefore, the sets $X$ and $Y$ are NOT equivalent.
