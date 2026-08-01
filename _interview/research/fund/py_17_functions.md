# Functions

> **Prerequisites Block:**
> * **Assumed Knowledge:** Loops, variables, data structures.

> **First-use gloss:** A **function** is a reusable block of code that performs a specific task.


## Introduction to Functions

A function is a block of organized, reusable code that is used to perform a single, related action. Functions provide better modularity for your application and a high degree of code reusing.

```python
# Syntax
def function_name(parameters):
    """docstring"""
    # body
    return expression
```

**Example:**
```python
def is_even(i):
    """
    Input: i, a positive int
    Returns True if i is even, otherwise False
    """
    print("inside is_even")
    return i % 2 == 0
```
- **`def`**: Keyword used to declare a function.
- **`is_even`**: The name of the function.
- **`(i)`**: Parameters or arguments passed to the function.
- **`""" """`**: Docstring, which provides documentation for the function.
- **Body**: The block of code inside the function.

You call the function later in the code using its name and passing the required arguments.

## Types of Arguments

When calling a function, you can pass arguments in different ways:

1. **Default Argument**
2. **Positional Argument**
3. **Keyword Argument**

```python
def power(a=1, b=1):
    return a**b

# Default arguments used (a=1, b=1)
print(power()) # Output: 1

# Positional arguments (a=2, b=3)
print(power(2, 3)) # Output: 8

# Keyword arguments (order doesn't matter)
print(power(b=3, a=2)) # Output: 8
```

## `*args` and `**kwargs`

`*args` and `**kwargs` are special Python keywords that are used to pass a variable length of arguments to a function.

### `*args`

`*args` allows us to pass a variable number of **non-keyword arguments** (positional arguments) to a function. Inside the function, the arguments are collected into a tuple.

```python
def multiply(*args):
    product = 1
    
    # args is a tuple of all passed arguments
    print(args)
    for i in args:
        product = product * i
        
    return product

print(multiply(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12))
# Output:
# (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12)
# 43545600
```
*Note: `args` is just a naming convention. You can use any name, like `*salman` or `*numbers`, as long as it starts with an asterisk `*`.*

### `**kwargs`

`**kwargs` allows us to pass any number of **keyword arguments**. Inside the function, these arguments are collected into a dictionary.

```python
def display(**kwargs):
    # kwargs is a dictionary
    for (key, value) in kwargs.items():
        print(key, '->', value)

display(india='delhi', srilanka='colombo', nepal='kathmandu', pakistan='islamabad')
# Output:
# india -> delhi
# srilanka -> colombo
# nepal -> kathmandu
# pakistan -> islamabad
```

## Accessing Docstrings

You can access the docstring of a function using the `__doc__` attribute.

```python
def is_even(i):
    """
    This function returns if a given number is odd or even
    input - any valid integer
    output - odd/even
    created on - 16th Nov 2022
    """
    return i % 2 == 0

print(is_even.__doc__)
```
### Points to remember while using `*args` and `**kwargs`

- **Order of arguments matters:** `normal -> *args -> **kwargs`
- The words `args` and `kwargs` are only a convention; you can use any name of your choice as long as they are preceded by `*` and `**` respectively.

## How Functions are Executed in Memory

When a function is called, the execution is managed using frames in memory:

1. **Global Frame:** When a function is defined, it is created and stored in the global frame.
2. **Local Frame:** When the function is called, a separate local frame is created for that specific function call.
3. **Variable Assignment:** Variables passed to the function are stored in the local frame.
4. **Return and Destruction:** Once the function finishes execution and returns a value, the local frame is destroyed, and control returns to the global frame.

**Example:**
```python
def is_even(num):
    if num % 2 == 0:
        return 'even'
    else:
        return 'odd'

print(is_even(7))
```
- The function `is_even` is stored in the global frame.
- When `is_even(7)` is called, a local frame is created for `is_even`, and `num` is set to `7`.
- The function evaluates to `'odd'` and returns it.
- The local frame for `is_even(7)` is destroyed.
## Functions Without a Return Statement

If a function does not explicitly return a value using the `return` keyword, it implicitly returns `None`.

```python
def is_even(num):
    if num % 2 == 0:
        print('even')
    else:
        print('odd')

# Prints 'odd', then prints 'None' because is_even returns None
print(is_even(7))
```

This behavior is common with many built-in list methods that mutate the list in place instead of returning a new list:
```python
L = [1, 2, 3]
print(L.append(4)) # Output: None
print(L)           # Output: [1, 2, 3, 4]
```

## Variable Scope

Variables in Python have different scopes which determine where they can be accessed.

### Global vs. Local Variables

Variables defined outside of a function are **global** and can be accessed anywhere. Variables defined inside a function are **local** to that function.

```python
def g(y):
    # Can read the global variable x
    print(x)     # 5
    print(x + 1) # 6

x = 5
g(x)
print(x)         # 5
```

If you assign a value to a variable inside a function, it creates a new local variable, shadowing the global one:
```python
def f(y):
    x = 1        # Local variable x
    x += 1
    print(x)     # 2

x = 5            # Global variable x
f(x)
print(x)         # 5
```

### UnboundLocalError

If you try to modify a global variable inside a function without declaring it as global, Python assumes it's a local variable. This leads to an error if the variable hasn't been assigned yet.

```python
def h(y):
    # Tries to access local 'x' before it is assigned
    x += 1

x = 5
h(x)
# UnboundLocalError: local variable 'x' referenced before assignment
```

### The `global` Keyword

To modify a global variable inside a function, you must explicitly declare it using the `global` keyword.

```python
x = 5

def h():
    global x
    x += 1

h()
print(x) # 6
```

### Modifying Mutable Global Objects

If your global variable is a mutable object (like a list, dictionary, or set), you **do not** need the `global` keyword to change its contents. This is because you are modifying the existing object in memory, not pointing the variable to a completely new object.

```python
inventory = ["sword", "shield"]

def add_item(item):
    # No 'global' keyword needed
    inventory.append(item)

add_item("potion")
print(inventory) # ['sword', 'shield', 'potion']
```

**The Golden Rule:** If you need to use the equals sign (`=`) to assign a completely new value to a global variable name, use `global`. If you are just using methods to mutate an existing object in place, you don't need it.

### The "Sticky Note" Rule (Immutability)

In Python, variables are not buckets that hold data; they are just sticky notes (labels) attached to objects in memory.

When you create an integer, Python builds an integer object in memory and slaps your variable name on it like a sticky note. Because integers are **immutable**, their core value can never be changed.

```python
x = 5
x = 6
```

When you do this, you didn't change the `5` into a `6`. Instead, Python:
1. Created an immutable object `5` in memory.
2. Put the sticky note `x` on the `5`.
3. Created a brand-new immutable object `6` in memory.
4. Ripped the sticky note `x` off the `5` and stuck it onto the `6`.

The original `5` was never altered. You can prove this using Python's built-in `id()` function, which reveals the exact memory address of an object.

## Nested Functions

Python allows you to define functions inside other functions. The inner function is only accessible from within the outer function (unless returned).

```python
def f():
    def g():
        print('inside function g')
    g()
    print('inside function f')

f()
# Output:
# inside function g
# inside function f
```

## Functions as First-Class Citizens

In Python, functions are "first-class citizens" (also known as first-class objects). This means that functions support all the operations generally available to other entities like integers, strings, and lists.

You can perform typical operations on functions such as:
1. Finding their type and memory address.
2. Reassigning them to new variables.
3. Deleting them.
4. Storing them in data structures (like lists or dictionaries).
5. Passing them as arguments to other functions.
6. Returning them from other functions.

**1. Type and ID**
```python
def square(num):
    return num**2

**2. Reassigning**
```python
x = square
print(id(x)) # Same as id(square)
print(x(3))  # 9
```

**3. Deleting**
```python
del square
square(3) # NameError: name 'square' is not defined
```

**4. Storing**
```python
def square(num): return num**2
L = [1, 2, 3, 4, square]
print(L[-1](3)) # 9

s = {square}
print(s) # {<function __main__.square(num)>}
```

**5. Returning a function**
```python
def f():
    def x(a, b):
        return a + b
    return x

val = f()(3, 4)
print(val) # 7
```

**6. Passing a function as an argument**
```python
def func_a():
    print('inside func_a')

def func_b(z):
    print('inside func_c')
    return z()

print(func_b(func_a))
# Output:
# inside func_c
# inside func_a
# None
```

## Lambda Functions

> **Heavy.** Syntactically compressed anonymous functions.

**Analogy:** A lambda is like a disposable sticky note. While a normal `def` function is a formal, named recipe written in your permanent cookbook, a lambda is a quick calculation you scribble on a scrap of paper, use once, and throw away.

**Example FIRST:**
```python
# x, y -> x+y
a = lambda x, y: x + y
print(a(5, 2)) # 7
```

**Plain-English:**
A lambda function allows you to write a small, nameless function in a single line. It implicitly returns the result of its single expression without needing the `return` keyword. 

**Technical Definition:**
A lambda function is an anonymous inline function consisting of a single expression. Evaluating a lambda expression yields a function object.
**Syntax:** `lambda arguments: expression`
- The colon (`:`) separates the arguments from the expression.

**Why here / The Trap:**
Why use them? They are primarily used as "throwaway" arguments for Higher-Order Functions (HOF). 
> **Trap.** Because they have no name and no `return` keyword, attempting to write multi-line logic or complex statements inside a lambda will fail. They must remain a single expression.

## Higher Order Functions (HOF)

> **Heavy.** Functions that treat other functions as data.

**Analogy:** If a normal function is a machine that processes raw materials (data) into products, a Higher-Order Function is a factory manager that takes in *other machines* (functions) and orchestrates them. 

**Example FIRST:**
```python
# Square the items of a list
L = [1, 2, 3, 4, 5]
list(map(lambda x: x**2, L))
# [1, 4, 9, 16, 25]
```

**Plain-English:**
A Higher-Order Function is any function that either accepts another function as an argument, or returns a function as its result. They allow you to apply a generic behavior (like transforming or filtering) using a specific rule (the passed-in function).

**Technical Definition:**
A higher-order function takes one or more function objects as arguments or returns a function object.

### 1. `map()`

**Plain-English:** It applies a given function to every item in an iterable, returning a map object (an iterator) with the transformed items.
**Syntax:** `map(function, iterable)`

**Examples:**
```python
# Odd/even labelling of list items
L = [1, 2, 3, 4, 5]
list(map(lambda x: 'even' if x % 2 == 0 else 'odd', L))
# ['odd', 'even', 'odd', 'even', 'odd']

# Fetch names from a list of dictionaries
users = [
    {'name': 'Rahul', 'age': 45, 'gender': 'male'},
    {'name': 'Nitish', 'age': 33, 'gender': 'male'},
    {'name': 'Ankita', 'age': 50, 'gender': 'female'}
]
list(map(lambda user: user['name'], users))
# ['Rahul', 'Nitish', 'Ankita']
```

### 2. `filter()`

**Plain-English:** It returns an iterator containing only the items from the original iterable that return `True` when passed into the given function.
**Syntax:** `filter(function, iterable)`

**Examples:**
```python
# Numbers greater than 5
L = [3, 4, 5, 6, 7]
list(filter(lambda x: x > 5, L))
# [6, 7]

# Fetch fruits starting with 'a'
fruits = ['apple', 'guava', 'cherry']
list(filter(lambda x: x.startswith('a'), fruits))
# ['apple']
```

### 3. `reduce()`

**Plain-English:** It applies a rolling computation to sequential pairs of values in an iterable, reducing the entire collection down to a single aggregate value.
**Syntax:** `functools.reduce(function, iterable)`

**Example:**
```python
import functools

# Sum of all items
L = [1, 2, 3, 4, 5]
functools.reduce(lambda x, y: x + y, L)
# 15
```
*(Failure case: `reduce` requires `import functools` in Python 3; forgetting this will raise a `NameError`.)*

