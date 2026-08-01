# Sets

> **Prerequisites Block:**
> * **Assumed Knowledge:** Lists, tuples, mutability.


## Introduction to Sets
A **set** is an unordered collection of items. Every set element is unique (no duplicates) and must be immutable (cannot be changed). 

However, a set itself is **mutable**. We can add or remove items from it.
Sets can also be used to perform mathematical set operations like union, intersection, symmetric difference, etc.

## Characteristics
- **Unordered**: Items have no index or specific order.
- **Mutable**: The set itself can be changed (items can be added or removed).
- **No Duplicates**: A set cannot contain duplicate elements.
- **Can't contain mutable data types**: Elements inside a set must be immutable (like integers, floats, strings, or tuples). You cannot have a list, dictionary, or another set inside a set.

## Creating Sets
You can create a set using curly braces `{}` or the `set()` function.
```python
# Empty set
# Note: s = {} creates an empty dictionary, not a set!
s = set()
print(type(s)) # Output: <class 'set'>

# 1D Set
s1 = {1, 2, 3}
print(s1)

# Homogeneous and Heterogeneous
s2 = {1, 'hello', 4.5, (1, 2, 3)} # Tuple is allowed (immutable)
print(s2) 
# Output: {1, 4.5, (1, 2, 3), 'hello'} (order may vary)

# Sets cannot contain mutable items like lists or other sets
# s3 = {1, 2, 3, [4, 5]} # TypeError: unhashable type: 'list'

# Duplicates are not allowed
# Python treats True as 1 and False as 0
s4 = {1, 'hello', 4.5, True}
print(s4) 
# Output: {1, 4.5, 'hello'} (True is considered a duplicate of 1 and ignored)

# Using type conversion (passing an iterable to set())
s5 = set([1, 2, 3, 3, 2, 1])
print(s5) # Output: {1, 2, 3}
```

## Accessing Items
Since sets are **unordered**, they do not support indexing or slicing.
```python
s = {1, 2, 3, 4}
# print(s[0]) # TypeError: 'set' object is not subscriptable
```
To access elements, you typically loop through the set or check for membership using the `in` keyword.

## Adding Items
You can add elements to a set using `add()` and `update()`.

### `add()`
Adds a single element to the set.
```python
s = {1, 2, 3, 4}
s.add(5)
print(s) # Output: {1, 2, 3, 4, 5}
```

### `update()`
Adds multiple elements (from an iterable like a list, tuple, or another set) to the set.
```python
s = {1, 2, 3, 4}
s.update([5, 6, 7])
print(s) # Output: {1, 2, 3, 4, 5, 6, 7}
```

## Deleting Items
There are several methods to remove items from a set:

### `discard(item)`
Removes the specified item. **Does not raise an error** if the item is not present.
```python
s = {1, 2, 3, 4, 5}
s.discard(50) # No error
```

### `remove(item)`
Removes the specified item. **Raises a KeyError** if the item is not present.
```python
# s.remove(50) # KeyError: 50
```

### `pop()`
Removes and returns an arbitrary item from the set.
```python
s = {1, 2, 3}
item = s.pop() # Removes a random item
```

### `clear()`
Empties the set completely.
```python
s.clear()
print(s) # Output: set()
```

### `del`
Deletes the set object from memory entirely.
```python
del s
```

## Set Operations
Sets are highly useful because they support mathematical set operations.

```python
s1 = {1, 2, 3, 4, 5}
s2 = {4, 5, 6, 7, 8}

# Union (|): All items from both sets
print(s1 | s2) # {1, 2, 3, 4, 5, 6, 7, 8}

# Intersection (&): Common items in both sets
print(s1 & s2) # {4, 5}

# Difference (-): Items in s1 but not in s2
print(s1 - s2) # {1, 2, 3}
print(s2 - s1) # {6, 7, 8}

# Symmetric Difference (^): Items in either set, but NOT in both
print(s1 ^ s2) # {1, 2, 3, 6, 7, 8}
```

## Membership Test
You can test if an item exists in a set using `in` or `not in`. (This is much faster in sets than in lists!).
```python
s = {1, 2, 3, 4, 5}
print(1 in s)     # True
print(10 not in s) # True
```

## Iteration
You can loop through a set using a `for` loop.
```python
for i in {1, 2, 3}:
    print(i)
```

## Set Functions
Similar to lists and tuples, sets support built-in functions:
- `len(s)`: Returns the number of items.
- `sum(s)`: Returns the sum of items.
- `min(s)` / `max(s)`: Returns the minimum/maximum item.
- `sorted(s)`: Returns a **sorted list** of the set's items.
```python
s = {3, 1, 4, 5, 2, 7}
print(sorted(s)) # Output: [1, 2, 3, 4, 5, 7]
print(sorted(s, reverse=True)) # Output: [7, 5, 4, 3, 2, 1]
```

## Other Set Methods
Sets have several built-in methods that are equivalent to the mathematical operators:

### `union()` and `update()`
`s1.union(s2)` returns a new set with all items from both sets.
`s1.update(s2)` modifies `s1` in-place, adding all items from `s2`.

### `intersection()` and `intersection_update()`
`s1.intersection(s2)` returns a new set with common items.
`s1.intersection_update(s2)` modifies `s1` in-place to keep only common items.

### `difference()` and `difference_update()`
`s1.difference(s2)` returns a new set with items in `s1` but not in `s2`.
`s1.difference_update(s2)` modifies `s1` in-place, removing items found in `s2`.

### `symmetric_difference()` and `symmetric_difference_update()`
`s1.symmetric_difference(s2)` returns a new set with items in either set but not both.
`s1.symmetric_difference_update(s2)` modifies `s1` in-place.

### Checking Set Relations
```python
s1 = {1, 2, 3, 4}
s2 = {7, 8, 5, 6}

# isdisjoint(): Returns True if two sets have a null intersection
print(s1.isdisjoint(s2)) # True

s1 = {1, 2, 3, 4, 5}
s2 = {3, 4, 5}

# issuperset(): Returns True if s1 contains all items of s2
print(s1.issuperset(s2)) # True

# issubset(): Returns True if all items of s2 are in s1
print(s2.issubset(s1)) # True
```

### `copy()`
Returns a shallow copy of the set.
```python
s1 = {1, 2, 3}
s2 = s1.copy()
```

## Frozenset
A **frozenset** is just an **immutable version** of a Python set object. While elements of a set can be modified at any time, elements of the frozenset remain the same after creation.

Due to this, frozensets can be used as keys in Dictionary or as elements of another set.

### Creating Frozenset
```python
fs = frozenset([1, 2, 3])
print(fs) # frozenset({1, 2, 3})
```

### What works and what does not
- **Works**: All read operations (union, intersection, difference, membership, length, iteration, etc.).
- **Doesn't work**: All write operations (add, remove, update, clear, pop, discard, etc.).

### When to use Frozenset?
Since sets cannot contain mutable items, you cannot create a 2D set (a set of sets):
```python
# s = {{1, 2}, {3, 4}} # TypeError: unhashable type: 'set'
```
However, you **can** create a set of frozensets because frozensets are immutable (and therefore hashable):
```python
s = {frozenset([1, 2]), frozenset([3, 4])}
print(s) # Output: {frozenset({1, 2}), frozenset({3, 4})}
```

## Set Comprehension
Just like lists, sets also support comprehensions for concise creation.
```python
# Create a set of numbers greater than 5
s = {i for i in range(1, 11) if i > 5}
print(s) # Output: {6, 7, 8, 9, 10}

# Create a set of squares
squares = {i**2 for i in range(1, 6)}
print(squares) # Output: {1, 4, 9, 16, 25}
```
