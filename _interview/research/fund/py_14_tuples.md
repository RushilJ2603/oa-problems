# Tuples

> **Prerequisites Block:**
> * **Assumed Knowledge:** Lists, immutability.


A tuple in Python is similar to a list. The difference between the two is that we cannot change the elements of a tuple once it is assigned, whereas we can change the elements of a list. In short, a tuple is an **immutable list**. A tuple cannot be changed in any way once it is created.

## Characteristics of Tuples
- **Ordered**: Elements have a defined order that will not change.
- **Unchangeable (Immutable)**: You cannot add, remove, or modify elements after creation.
- **Allows Duplicates**: Like lists, tuples can contain duplicate values.

## Plan of Attack
- Creating a Tuple
- Accessing Items
- Editing Items
- Adding Items
- Deleting Items
- Operations on Tuples
- Tuple Functions

## Creating Tuples
```python
# Empty tuple
t1 = ()

# Create a tuple with a single item
# Without a trailing comma, Python treats it as a string
t2 = ('hello') 
print(type(t2)) # Output: <class 'str'>

# With a trailing comma, it becomes a tuple
t2 = ('hello',)
print(type(t2)) # Output: <class 'tuple'>

# Homogeneous tuple
t3 = (1, 2, 3, 4)

# Heterogeneous tuple
t4 = (1, 2.5, True, [1, 2, 3])

# Nested tuple
t5 = (1, 2, 3, (4, 5))

# Using type conversion
t6 = tuple('hello')
print(t6) # Output: ('h', 'e', 'l', 'l', 'o')
```

## Accessing Items
Accessing items in a tuple works exactly the same as in a list.
- **Indexing**: `t[0]`, `t[-1]`
- **Slicing**: `t[1:4]`
- **Nested Indexing**: `t5[-1][0]`

## Editing Items
You **cannot** edit items in a tuple. Like strings, tuples are immutable.
```python
t3 = (1, 2, 3, 4)
t3[0] = 100 
# TypeError: 'tuple' object does not support item assignment
```

## Adding Items
Since tuples are immutable, you **cannot** add new items (no `append`, `extend`, or `insert` equivalent exists for tuples).

## Deleting Items
You **cannot** delete individual items from a tuple.
```python
t5 = (1, 2, 3, (4, 5))
del t5[-1] 
# TypeError: 'tuple' object doesn't support item deletion
```
However, you can delete the entire tuple using the `del` keyword.
```python
del t5
```

## Operations on Tuples
Like strings and lists, tuples support basic operations.

- **Concatenation (`+`)**: Joins tuples together.
  ```python
  t1 = (1, 2, 3, 4)
  t2 = (5, 6, 7, 8)
  print(t1 + t2) # Output: (1, 2, 3, 4, 5, 6, 7, 8)
  ```
- **Repetition (`*`)**: Repeats the tuple.
  ```python
  print(t1 * 3) # Output: (1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4)
  ```
- **Membership**: `in` and `not in`.
- **Iteration**: Using `for` loops.
## Tuple Functions
Like lists, tuples support many built-in functions:
- **`len(t)`**: Returns the number of items.
- **`sum(t)`**: Returns the sum of all items.
- **`min(t)` / `max(t)`**: Returns the minimum/maximum item.
- **`sorted(t)`**: Returns a **list** of sorted items (does not modify the tuple, as it's immutable).
- **`t.count(x)`**: Returns the number of times `x` occurs in the tuple.
- **`t.index(x)`**: Returns the index of the first occurrence of `x`.

## Difference between Lists and Tuples
- **Syntax**: Lists use `[]`, tuples use `()`.
- **Mutability**: Lists are mutable, tuples are immutable.
- **Speed**: Tuples are generally faster to iterate over and create than lists.
- **Memory**: Tuples consume less memory.
  ```python
  import sys
  L = list(range(1000))
  T = tuple(range(1000))
  print('List size', sys.getsizeof(L))   # e.g., 9120
  print('Tuple size', sys.getsizeof(T))  # e.g., 8056
  ```
- **Built-in functionality**: Lists have more built-in methods (like `append`, `remove`) than tuples.
- **Error Prone**: Lists are more prone to errors due to mutability (e.g., aliasing issues). Tuples are safer.
- **Usability**: Tuples are typically used for heterogeneous data types, while lists are often used for homogeneous data.

## Immutability and Aliasing
Because tuples are immutable, they do not suffer from aliasing side-effects like lists do.
```python
# With Lists (Mutable)
a = [1, 2, 3]
b = a
a.append(4)
print(a) # Output: [1, 2, 3, 4]
print(b) # Output: [1, 2, 3, 4]

# With Tuples (Immutable)
a = (1, 2, 3)
b = a
a = a + (4,)
print(a) # Output: (1, 2, 3, 4)
print(b) # Output: (1, 2, 3)
```

## Special Syntax
### Tuple Unpacking
You can unpack the elements of a tuple into multiple variables. The number of variables must match the number of items in the tuple.
```python
a, b, c = (1, 2, 3)
print(a, b, c) # Output: 1 2 3

# Error if variables do not match items
# a, b = (1, 2, 3)
# ValueError: too many values to unpack (expected 2)
```

You can use tuple unpacking for swapping variables intuitively:
```python
a = 1
b = 2
a, b = b, a
print(a, b) # Output: 2 1
```

You can use the `*` operator to gather remaining items into a list:
```python
a, b, *others = (1, 2, 3, 4)
print(a, b)     # Output: 1 2
print(others)   # Output: [3, 4]
```

### Zipping Tuples
You can zip two tuples together using the `zip()` function, which creates an iterator of tuples pairing items from each iterable.
```python
a = (1, 2, 3, 4)
b = (5, 6, 7, 8)

# Convert the zip object to a list to view it
print(list(zip(a, b))) 
# Output: [(1, 5), (2, 6), (3, 7), (4, 8)]
```
