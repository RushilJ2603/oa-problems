# Memory and Object References

> **Prerequisites Block:**
> * **Assumed Knowledge:** Basic data types (lists, tuples, strings), variables and binding.
> * **Recap:** Variables in Python are sticky name tags bound to objects in memory, not fixed buckets.

## Memory Models

When a variable is assigned a value, Python creates an object in memory and binds the variable name to that object's memory address. 
For example, with `a = 5`, an integer object `5` is created at some memory address, and `a` points to it.

## Aliasing

> **First-use gloss:** **Aliasing** occurs when multiple variable names refer to the exact same object in memory.

If we write:
```python
a = [1, 2, 3]
b = a
```
Here, `b` is not a new copy of the list. Instead, `b` becomes an alias for `a`; both names point to the very same list object. Modifying the list through `b` (e.g., `b.append(4)`) will reflect in `a` because there is only one underlying object.

## Garbage Collection

> **First-use gloss:** **Garbage Collection** is Python's automatic memory management process that frees up memory occupied by objects that are no longer referenced by any variable.

Python uses reference counting. If an object's reference count drops to zero (meaning no variables point to it), the garbage collector reclaims that memory.

## Mutability and Its Dangers

> **First-use gloss:** **Mutability** refers to whether an object's internal state can be modified after creation. Lists and dictionaries are mutable; tuples, strings, and integers are immutable.

Mutability is powerful but dangerous in scenarios involving aliasing or when passing mutable objects to functions. Unintended side-effects occur if multiple parts of a program share a reference to a mutable object and one part modifies it, unexpectedly affecting the other parts.

## Cloning (Shallow vs Deep Copies)

To avoid the dangers of aliasing with mutable objects, we can clone them.

### Shallow Copy
Using `b = a[:]` or `b = a.copy()` creates a shallow copy. It creates a new list object, but inserts references to the *same* child objects found in the original list.
* For a flat list like `[1, 2, 3]`, this is perfectly sufficient. Modifying `b` will not affect `a`.
* For a nested list like `[1, 2, [3, 4]]`, a shallow copy only copies the outer list. The inner list `[3, 4]` is still shared between `a` and `b`.

### Deep Copy
Using `import copy; copy.deepcopy(a)` creates a fully independent clone of the original object and all its nested objects recursively. Modifying deeply nested structures in the deep copy will not affect the original.

## Memory Layout of Types

### Nested Lists
A nested list like `[1, 2, [3, 4]]` is stored as an array of references. The first two elements point to integer objects `1` and `2`. The third element points to another list object, which in turn contains references to integer objects `3` and `4`.

### Strings
Python strings are arrays of references to character objects. Like tuples, they are contiguous in memory.

### Tuples vs. Lists in Memory
> **Heavy:** Why do tuples take less memory than lists?

**Analogy:** A list is like a moving box with extra room left inside just in case you buy more stuff. A tuple is like shrink-wrapping the exact items you have.

**Technical Definition:** 
* **Lists** use dynamic arrays. When a list is created, Python over-allocates memory (reserves extra space) to allow for efficient future `append()` operations without needing to reallocate the whole array every time.
* **Tuples** are static arrays. Because they are immutable, Python allocates exactly the amount of memory needed for the elements, with zero over-allocation. This makes tuples more memory-efficient than lists.

### Sets and Dictionaries
> **Heavy:** Why are mutable types not allowed as elements in Sets or keys in Dictionaries?

Sets and Dictionaries rely on hash tables for fast `O(1)` lookups. The index of an item in the hash table is decided by calculating the **hash value** of the item.
If mutable types (like lists) were allowed as keys, their content could change after insertion. If the content changes, the hash value would change, meaning the object would now be in the "wrong" bucket in the hash table, breaking the data structure and making it impossible to find the item again. Therefore, only immutable (hashable) types are permitted.
