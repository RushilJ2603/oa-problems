# Data Types

Python ships with a set of built-in types. The snippets below print one literal
of each so its display form is visible.

## Numeric types

### Integer (`int`)

Python integers have **arbitrary precision** — they are limited only by
available memory, not by a fixed width.

```python
# Integer
print(8)
# 1*10**308
print(1e309)
```

```text
8
inf
```

The second line is instructive. `1e309` is written as a *float* literal, and
`10**309` exceeds the range a floating-point number can represent, so Python
yields the special floating-point value `inf` (infinity) rather than a number.
This overflow behaviour belongs to floats; the unbounded `int` type would have
held the exact value had it been written as an integer expression.

### Float

Decimal numbers are of type `float`. They are demonstrated further under
[Literals](#literals).

### Boolean (`bool`)

`True` and `False`. Booleans are a subtype of integers in Python, a fact that
surfaces directly under [Type Conversion](#type-conversion).

### Complex

Numbers with a real and imaginary part, written with a `j` suffix on the
imaginary component (see [Literals](#literals)).

## Collection types

### List — an ordered, mutable sequence

```python
# List -> C -> Array
print([1, 2, 3, 4, 5])
```

```text
[1, 2, 3, 4, 5]
```

A list is Python's closest analogue to the array of a language like C, but it
is dynamic and may hold mixed types.

### Tuple — an ordered, immutable sequence

```python
# Tuple
print((1, 2, 3, 4, 5))
```

```text
(1, 2, 3, 4, 5)
```

A tuple looks like a list but uses parentheses and cannot be changed after
creation.

### Set — an unordered collection of unique elements

```python
# Sets
print({1, 2, 3, 4, 5})
```

A set is written with braces and stores no duplicates and no order.

### Dictionary — key–value pairs

```python
# Dictionary
print({'name': 'Nitish', 'gender': 'Male', 'weight': 70})
```

```text
{'name': 'Nitish', 'gender': 'Male', 'weight': 70}
```

A dictionary maps keys to values, also written with braces but using
`key: value` pairs.

> **First-use gloss:** *List* `[ ]` — an ordered, changeable collection of items.
> **First-use gloss:** *Tuple* `( )` — an ordered, fixed collection of items.
> **First-use gloss:** *Set* `{ }` — an unordered collection of unique items.
> **First-use gloss:** *Dictionary* `{k: v}` — a collection of keyed lookups. Braces serve both sets and dictionaries; the presence of `key: value` pairs distinguishes a dictionary.
