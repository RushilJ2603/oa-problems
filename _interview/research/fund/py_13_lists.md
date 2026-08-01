# Lists in Python

> **Prerequisites Block:**
> * **Assumed Knowledge:** Variables, loops, basic types.


## What are Lists?
A List is a data type where you can store multiple items under one name. More technically, lists act like **dynamic arrays**, which means you can add more items on the fly.

```python
L = [20, 'Jessa', 35.75, [30, 60, 90]]
```
Lists can contain heterogeneous data types, including other lists.

## Array vs. Lists

| Feature | Arrays | Lists |
| :--- | :--- | :--- |
| **Size** | Fixed size | Dynamic size |
| **Data Types** | Homogeneous (same data type) | Heterogeneous (mixed data types) |
| **Speed of Execution** | Faster | Slower |
| **Memory** | Contiguous memory allocation | Referential arrays |

## How Lists are Stored in Memory

> **Heavy.** Python lists are not traditional arrays; they are implemented as Referential Arrays.

**Analogy:** Think of a traditional C array as a row of lockers where the actual items (like books) are stuffed directly inside the lockers. A Python list, however, is a row of lockers that only contains **maps** (memory addresses) pointing to where the books are actually stored across a giant library. 

**Concrete Example FIRST:**
When you create a list `L = [1, 2, 3]`, Python creates objects in memory for the integers `1`, `2`, and `3`. The list `L` itself is an array of references (pointers) to those memory locations.

```python
L = [1, 2, 3]
print(id(L[0]) == id(1))
```

```text
True
```

**Plain-English:** Because Python caches small integers, the memory address of the first element in the list `id(L[0])` is exactly the same as the memory address of the integer `1` itself. The list doesn't "contain" the number `1`; it contains the address of `1`.

**Technical Definition:** In languages like C or Java, arrays are stored in contiguous memory locations. For example, an array of 3 integers will occupy 12 bytes consecutively. In Python, lists are implemented as **Referential Arrays**. The items in the list hold the memory addresses of the objects, not the values directly. This design is what allows lists to contain heterogeneous data types—since the list only stores memory addresses (which have a fixed size), it doesn't matter if one address points to an integer and another points to a massive string.

### How Dynamic Arrays Work
When a list (which is a dynamic array) runs out of space to store new items, Python does the following:
1. It allocates a new, larger block of memory (usually double the size of the current array).
2. It copies all the existing items (references) from the old array to the new array.
3. It adds the new item.
4. The old array is deleted.

## Characteristics of a List

1. **Ordered**: Lists maintain the order of elements as they were inserted. `[1, 2, 3]` is not the same as `[3, 2, 1]`.
2. **Changeable/Mutable**: You can modify, add, or remove elements after the list has been created.
3. **Heterogeneous**: Lists can contain elements of different data types (e.g., integers, strings, other lists).
4. **Can have duplicates**: Lists can contain multiple identical values.
5. **Dynamic**: Lists automatically resize themselves when elements are added or removed.
6. **Can be nested**: A list can contain another list as an item.
7. **Items can be accessed**: Elements can be accessed via indexing and slicing.
8. **Can contain any kind of object**: Any Python object can be stored in a list.

## Creating a List
Lists can be created in several ways, and they can hold different numbers of dimensions or types of data.

```python
# Empty List
print([])

# 1D List -> Homogeneous
print([1, 2, 3, 4, 5])

# 2D List
print([1, 2, 3, [4, 5]])

# 3D List
print([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])

# Heterogeneous List
print([1, True, 5.6, 5+6j, 'Hello'])

# Using Type conversion (list() function)
print(list('hello')) # Output: ['h', 'e', 'l', 'l', 'o']
```

## Accessing Items from a List
You can access items using index positions (0-based indexing) or slicing.

```python
# Indexing
L = [[[1, 2], [3, 4]], [[5, 6], [7, 8]]]
# Accessing '2'
print(L[0][0][1])

## Adding Items to a List
There are three main ways to add items to a list:

1. **`append()`**: Adds a single item to the end of the list. If you pass a list, it gets added as a single nested list.
2. **`extend()`**: Adds multiple items (from an iterable) to the end of the list individually.
3. **`insert()`**: Adds a single item at a specific index.

```python
L = [1, 2, 3, 4, 5]

# Using append()
L.append([6, 7, 8])
print(L) # Output: [1, 2, 3, 4, 5, [6, 7, 8]]

# Using extend()
L = [1, 2, 3, 4, 5]
L.extend([6, 7, 8])
print(L) # Output: [1, 2, 3, 4, 5, 6, 7, 8]

# extend() with a string adds individual characters
L.extend('delhi')
print(L) # Output: [..., 'd', 'e', 'l', 'h', 'i']

# Using insert(index, item)
L = [1, 2, 3, 4, 5]
L.insert(1, 100) # Inserts 100 at index 1
print(L) # Output: [1, 100, 2, 3, 4, 5]
```

## Editing Items in a List
Lists are mutable, meaning their contents can be changed by assigning new values to specific indexes or slices.

```python
L = [1, 2, 3, 4, 5]

# Editing a single item via indexing
L[-1] = 500
print(L) # Output: [1, 2, 3, 4, 500]

# Editing multiple items via slicing
L[1:4] = [200, 300, 400]
print(L) # Output: [1, 200, 300, 400, 500]
```

## Deleting Items from a List
There are several methods/keywords to remove items from a list.

1. **`del` keyword**: Can delete a single item by index, a slice, or the entire list variable.
2. **`remove()`**: Removes the first occurrence of a specific value.
3. **`pop()`**: Removes the item at the specified index (or the last item if no index is given) and returns it.
4. **`clear()`**: Empties the list, leaving an empty list `[]`.

```python
L = [1, 2, 3, 4, 5]

# Using del
del L[-1]     # Deletes the last item
del L[1:3]    # Deletes items from index 1 to 2
# del L       # Deletes the entire list variable from memory

# Using remove()
L = [1, 2, 3, 4, 5]
## Operations on Lists
Lists support various operations like arithmetic, membership, and looping.

### Arithmetic Operations
- **Concatenation (`+`)**: Merges two lists together.
- **Repetition (`*`)**: Repeats the items in a list a specified number of times.

```python
L1 = [1, 2, 3, 4]
L2 = [5, 6, 7, 8]

# Concatenation
print(L1 + L2) # Output: [1, 2, 3, 4, 5, 6, 7, 8]

# Repetition
print(L1 * 3)  # Output: [1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4]
```

### Membership Operations
You can use `in` and `not in` operators to check if an item exists within a list.

```python
L1 = [1, 2, 3, 4, 5]
L2 = [1, 2, 3, 4, [5, 6]]

print(5 not in L1)     # Output: False
print([5, 6] in L2)    # Output: True
print(5 in L2)         # Output: False (5 is inside a nested list)
```

### Loops
You can iterate through a list using a `for` loop.

```python
L1 = [1, 2, 3, 4, 5]
for i in L1:
    print(i)

# Looping over nested lists
## Built-in Functions with Lists

Python provides several built-in functions to work with lists:

- **`len()`**: Returns the number of items in the list.
- **`min()`**: Returns the smallest item.
- **`max()`**: Returns the largest item.
- **`sorted()`**: Returns a new sorted list (does not modify original).

```python
L = [2, 1, 5, 7, 0]
print(len(L))    # Output: 5
print(min(L))    # Output: 0
print(max(L))    # Output: 7
print(sorted(L)) # Output: [0, 1, 2, 5, 7]
```

## List Methods
In addition to the adding and deleting methods, lists have:

- **`count()`**: Returns the number of times a value appears.
- **`index()`**: Returns the index of the first occurrence of a value.
- **`reverse()`**: Reverses the list *in place*.
- **`sort()`**: Sorts the list *in place* (modifies original).
- **`copy()`**: Returns a shallow copy of the list.

```python
L = [1, 2, 1, 3, 4, 1, 5]
print(L.count(1)) # Output: 3
print(L.index(3)) # Output: 3

L = [2, 1, 5, 7, 0]
L.reverse()
print(L)          # Output: [0, 7, 5, 1, 2]

L.sort()
print(L)          # Output: [0, 1, 2, 5, 7]

L1 = L.copy()     # Creates a shallow copy
```

## List Comprehension

> **Heavy.** A syntactically compressed loop for generating lists.

**Analogy:** List comprehension is like placing a bulk order at a restaurant. Instead of going to the counter 10 times to say "I want a burger" (a `for` loop), you hand them a single piece of paper saying "I want 10 burgers, but only if they have cheese" (list comprehension). It does the exact same work but much faster and in one statement.

**Concrete Example FIRST:**
**Example: Add numbers 1 to 10 to a list**
Using a traditional loop:
```python
L = []
for i in range(1, 11):
    L.append(i)
print(L) # Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
```
Using list comprehension:
```python
L = [i for i in range(1, 11)]
print(L) # Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
```

**Plain-English:** List comprehensions allow you to create a new list by looping over an existing iterable and applying an expression or filter to it, all squeezed into a single line surrounded by brackets. It replaces the common pattern of creating an empty list and calling `.append()` inside a `for` loop.

**Technical Definition:** List comprehension provides a concise way to create lists based on existing iterables. It is more time-efficient and space-efficient than loops because it is optimized at the C-level in Python's implementation.

**Syntax**:
```python
newlist = [expression for item in iterable if condition == True]
```

**Advantages**:
- More time-efficient and space-efficient than loops.
- Requires fewer lines of code.
**Example 1: Add numbers 1 to 10 to a list**
Using a loop:
```python
L = []
for i in range(1, 11):
    L.append(i)
print(L) # Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
```
Using list comprehension:
**Example 2: Scalar multiplication on a vector**
```python
v = [2, 3, 4]
s = -3
print([s * i for i in v]) # Output: [-6, -9, -12]
```

**Example 3: Add squares**
```python
L = [1, 2, 3, 4, 5]
print([i**2 for i in L]) # Output: [1, 4, 9, 16, 25]
```

**Example 4: Print all numbers divisible by 5 (1 to 50)**
```python
print([i for i in range(1, 51) if i % 5 == 0]) 
# Output: [5, 10, 15, 20, 25, 30, 35, 40, 45, 50]
```

**Example 5: Find words starting with a specific letter**
```python
languages = ['java', 'python', 'php', 'c', 'javascript']
print([lang for lang in languages if lang.startswith('p')])
**Example 6: Nested `if` with List Comprehension**
```python
basket = ['apple', 'guava', 'cherry', 'banana']
my_fruits = ['apple', 'kiwi', 'grapes', 'banana']

# Add fruit from my_fruits if it exists in basket AND starts with 'a'
print([fruit for fruit in my_fruits if fruit in basket if fruit.startswith('a')])
# Output: ['apple']
```

**Example 7: Print a (3, 3) matrix using Nested List Comprehension**
```python
matrix = [[i * j for i in range(1, 4)] for j in range(1, 4)]
print(matrix)
**Example 8: Cartesian Products using List Comprehension**
```python
L1 = [1, 2, 3, 4]
L2 = [5, 6, 7, 8]
print([i * j for i in L1 for j in L2])
```

## Traversing a List
There are two main ways to traverse a list:
1. **Itemwise**: Iterate directly over the items.
   ```python
   L = [1, 2, 3, 4]
   for i in L:
       print(i)
   ```
2. **Indexwise**: Iterate using the range of indices.
   ```python
   L = [1, 2, 3, 4]
   for i in range(len(L)):
       print(L[i])
   ```

## Zip Function
The `zip()` function takes iterables, aggregates them in a tuple, and returns an iterator. It's useful for operating on multiple lists simultaneously.

```python
L1 = [1, 2, 3, 4]
L2 = [-1, -2, -3, -4]

# Add items of 2 lists indexwise
print([i + j for i, j in zip(L1, L2)]) 
# Output: [0, 0, 0, 0]
```

## Disadvantages of Python Lists
While highly flexible, Python lists come with trade-offs:
- **Slow execution**: Operations like arbitrary insertion/deletion are $O(n)$.
- **Risky usage**: Lists are mutable, which can lead to unintended side-effects if not careful due to aliasing.
  ```python
  a = [1, 2, 3]
  b = a           # 'b' points to the same list as 'a'
  a.append(4)
  print(a)        # Output: [1, 2, 3, 4]
  print(b)        # Output: [1, 2, 3, 4] (b changed too!)
  ```
- **Eats up more memory**: Lists allocate extra space to allow for fast appends, and store references to objects rather than the raw data itself.

Note: Lists can even contain functions and classes!
```python
L = [1, 2, print, type, input]
print(L) 
# Output: [1, 2, <built-in function print>, <class 'type'>, ...]
```
