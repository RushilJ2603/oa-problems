# Dictionaries

> **Prerequisites Block:**
> * **Assumed Knowledge:** Sets, keys, mutability.


## Introduction to Dictionaries
Dictionary in Python is a collection of key-value pairs, used to store data values like a map. Unlike other data types that hold only a single value as an element, a dictionary stores two paired values.

In some languages, this is known as a **map** or **associative array**.

```python
d = {'name': 'nitish', 'age': 33, 'gender': 'male'}
print(d)
```

## Characteristics
- **Mutable**: Dictionaries can be modified (items added, removed, or changed) after creation.
- **Indexing has no meaning**: Values are accessed via their keys, not by numerical index positions.
## Creating a Dictionary

You can create dictionaries in multiple ways:

```python
# 1. Empty dictionary
d = {}
# or 
d = dict()

# 2. 1D dictionary
d1 = {'name': 'nitish', 'gender': 'male'}

# 3. With mixed keys (keys can be any immutable type)
d2 = {(1, 2, 3): 1, 'hello': 'world'}

# 4. 2D dictionary (nested dictionary, like JSON)
d3 = {
    'name': 'nitish',
    'college': 'bit',
    'sem': 4,
    'subjects': {
        'dsa': 50,
        'maths': 67,
        'english': 34
    }
}

# 5. Using dict() function with a sequence of tuples
d4 = dict([('name', 'nitish'), ('age', 32), (3, 3)])
# Output: {'name': 'nitish', 'age': 32, 3: 3}

# Duplicate keys (the later value overwrites the earlier one)
d5 = {'name': 'nitish', 'name': 'rahul'}
print(d5) # Output: {'name': 'rahul'}

# Using a mutable type as a key raises a TypeError
# d6 = {'name': 'nitish', [1, 2, 3]: 2} # TypeError: unhashable type: 'list'
```

## Accessing Items

You can access the values of a dictionary using the key inside square brackets `[]`, or using the `get()` method.

```python
my_dict = {'name': 'Jack', 'age': 26}

# Using square brackets
print(my_dict['age']) # Output: 26
# print(my_dict['address']) # Raises KeyError

# Using get() method
print(my_dict.get('age')) # Output: 26
print(my_dict.get('address')) # Output: None (does not raise error)

# Accessing items in a 2D dictionary
d3 = {'subjects': {'maths': 67, 'english': 34}}
print(d3['subjects']['maths']) # Output: 67
```

## Adding Key-Value Pair

You can add a new key-value pair by simply assigning a value to a new key.
```python
d = {'name': 'nitish', 'age': 32, 3: 3}
d['gender'] = 'male'
d['weight'] = 72
print(d) 
# Output: {'name': 'nitish', 'age': 32, 3: 3, 'gender': 'male', 'weight': 72}
```

## Editing Key-Value Pair

If the key already exists, assigning a value to it updates the existing value.
```python
d = {'name': 'nitish', 'sem': 4}
d['sem'] = 5
print(d) # Output: {'name': 'nitish', 'sem': 5}
```

## Removing Key-Value Pair

Dictionaries offer several methods to remove items:

1. **`pop(key)`**: Removes the item with the specified key and returns its value.
2. **`popitem()`**: Removes the last inserted key-value pair (in Python 3.7+) and returns it as a tuple.
3. **`del`**: Removes the item with the specified key, or deletes the entire dictionary.
4. **`clear()`**: Empties the dictionary.

```python
d = {'name': 'nitish', 'age': 32, 3: 3, 'gender': 'male', 'weight': 72}

# pop()
d.pop(3) # Removes the key 3
print(d) # {'name': 'nitish', 'age': 32, 'gender': 'male', 'weight': 72}

# popitem()
d.popitem() # Removes ('weight', 72)
print(d) # {'name': 'nitish', 'age': 32, 'gender': 'male'}

# del
del d['age']
print(d) # {'name': 'nitish', 'gender': 'male'}
# del d # Deletes the dictionary entirely

# clear()
d.clear()
print(d) # {}
```

## Dictionary Operations

### Membership

The `in` and `not in` operators can check if a **key** exists in the dictionary. Membership tests are only for keys, not for values.

```python
s = {'name': 'nitish', 'college': 'bit', 'sem': 5}

print('name' in s) # Output: True
print('nitish' in s) # Output: False ('nitish' is a value, not a key)
```

### Iteration

You can loop through a dictionary using a `for` loop. By default, it iterates over the keys.

```python
d = {'name': 'nitish', 'gender': 'male', 'age': 33}

for i in d:
    print(i, d[i]) 
# Output:
# name nitish
# gender male
# age 33
```

## Dictionary Functions

### `len()`
Returns the number of key-value pairs in the dictionary.
```python
print(len(d)) # Output: 3
```

### `sorted()`
Returns a list of all the **keys** in sorted order.
```python
print(sorted(d)) # Output: ['age', 'gender', 'name']
```

### `max()` / `min()`
Returns the maximum or minimum **key** in the dictionary.

### `items()`, `keys()`, `values()`

These methods return view objects that provide a dynamic view of the dictionary's entries.

- **`keys()`**: Returns a view object displaying a list of all the keys.
- **`values()`**: Returns a view object displaying a list of all the values.
- **`items()`**: Returns a view object displaying a list of dictionary's (key, value) tuple pairs.

```python
print(d.keys())   # Output: dict_keys(['name', 'gender', 'age'])
print(d.values()) # Output: dict_values(['nitish', 'male', 33])
print(d.items())  # Output: dict_items([('name', 'nitish'), ('gender', 'male'), ('age', 33)])
```

## Dictionary Comprehension

Similar to list and set comprehensions, you can create dictionaries using comprehension.

**Syntax**: `{key: value for vars in iterable}`

```python
# Print 1st 10 numbers and their squares
squares = {i: i**2 for i in range(1, 11)}
print(squares) 
# Output: {1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100}

# Using an existing dictionary
distances = {'delhi': 1000, 'mumbai': 2000, 'bangalore': 3000}
distances_miles = {key: value * 0.62 for (key, value) in distances.items()}
print(distances_miles) 
# Output: {'delhi': 620.0, 'mumbai': 1240.0, 'bangalore': 1860.0}

# Using zip
days = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
temp_C = [30.5, 32.6, 31.8, 33.4, 29.8, 30.2, 29.9]
temperatures = {i: j for (i, j) in zip(days, temp_C)}
print(temperatures)
# Output: {'Sunday': 30.5, 'Monday': 32.6, ...}

# Using if condition
products = {'phone': 10, 'laptop': 0, 'charger': 32, 'tablet': 0}
in_stock = {key: value for (key, value) in products.items() if value > 0}
print(in_stock)
# Output: {'phone': 10, 'charger': 32}

# Nested Comprehension
# Print tables of numbers from 2 to 4
tables = {i: {j: i * j for j in range(1, 11)} for i in range(2, 5)}
print(tables)
# Output: 
# {
#   2: {1: 2, 2: 4, 3: 6, ... 10: 20},
#   3: {1: 3, 2: 6, 3: 9, ... 10: 30},
#   4: {1: 4, 2: 8, 3: 12, ... 10: 40}
# }
```
