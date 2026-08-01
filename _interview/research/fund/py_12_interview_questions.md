# Interview Questions

### 1. What is Python? What are the benefits of using Python?

Python is a high-level, interpreted, general-purpose programming language. Being a general-purpose language, it can be used to build almost any type of application with the right tools/libraries. Additionally, python supports objects, modules, threads, exception-handling, and automatic memory management which help in modelling real-world problems and building applications to solve these problems.

**Benefits of using Python:**
- Python is a general-purpose programming language that has a simple, easy-to-learn syntax that emphasizes readability and therefore reduces the cost of program maintenance. Moreover, the language is capable of scripting, is completely open-source, and supports third-party packages encouraging modularity and code reuse.
- Its high-level data structures, combined with dynamic typing and dynamic binding, attract a huge community of developers for Rapid Application Development and deployment.

### 2. What is a dynamically typed language?

Before we understand a dynamically typed language, we should learn about what typing is. Typing refers to type-checking in programming languages. In a **strongly-typed** language, such as Python, `"1" + 2` will result in a type error since these languages don't allow for "type-coercion" (implicit conversion of data types). On the other hand, a **weakly-typed** language, such as Javascript, will simply output `"12"` as result.

Type-checking can be done at two stages:
- **Static** - Data Types are checked before execution.
- **Dynamic** - Data Types are checked during execution. Python is an interpreted language, executes each statement line by line and thus type-checking is done on the fly, during execution. Hence, Python is a Dynamically Typed Language.

### 3. What is an Interpreted language?

An Interpreted language executes its statements line by line. Languages such as Python, Javascript, R, PHP, and Ruby are prime examples of Interpreted languages. Programs written in an interpreted language runs directly from the source code, with no intermediary compilation step.

### 4. What is PEP 8 and why is it important?

PEP stands for **Python Enhancement Proposal**. A PEP is an official design document providing information to the Python community, or describing a new feature for Python or its processes. PEP 8 is especially important since it documents the style guidelines for Python Code. Apparently contributing to the Python open-source community requires you to follow these style guidelines sincerely and strictly.

### 5. What are the common built-in data types in Python?

There are several built-in data types in Python. Although, Python doesn't require data types to be defined explicitly during variable declarations type errors are likely to occur if the knowledge of data types and their compatibility with each other are neglected. Python provides `type()` and `isinstance()` functions to check the type of these variables. These data types can be grouped into the following categories:

1. **None Type**: None keyword represents the null values in Python. Boolean equality operation can be performed using these NoneType objects.
2. **Numeric Type**: There are three distinct numeric types - integers, floating-point numbers and complex numbers. Additionally, booleans are a sub-type of integers.
3. **Sequence Types**: According to Python Docs, there are three basic Sequence Types - lists, tuples, and range objects. Sequence types have the in and not in operators defined for their traversing their elements. These operators share the same priority as the comparison operations.
4. **Mapping Types**: A mapping object can map hashable values to random objects in Python. Mappings objects are mutable and there is currently only one standard mapping type, the dictionary.
5. **Set Types**: Currently, Python has two built-in set types - set and frozenset. set type is mutable and supports methods like `add()` and `remove()`. frozenset type is immutable and can't be modified after creation.
6. **Callable Types**: Callable types are the types to which function call can be applied. They can be user-defined functions, instance methods, generator functions, and some other built-in functions, methods and classes.

### 6. Operator Precedence

The operator precedence in Python is listed in the following table (descending order, upper group has higher precedence):

| Operators | Meaning |
| :--- | :--- |
| `()` | Parentheses |
| `**` | Exponent |
| `+x`, `-x`, `~x` | Unary plus, Unary minus, Bitwise NOT |
| `*`, `/`, `//`, `%` | Multiplication, Division, Floor division, Modulus |
| `+`, `-` | Addition, Subtraction |
| `<<`, `>>` | Bitwise shift operators |
| `&` | Bitwise AND |
| `^` | Bitwise XOR |
| `\|` | Bitwise OR |
| `==`, `!=`, `>`, `>=`, `<`, `<=`, `is`, `is not`, `in`, `not in` | Comparisons, Identity, Membership operators |
| `not` | Logical NOT |
| `and` | Logical AND |
| `or` | Logical OR |

### 7. Explain the ternary operator in Python.

Unlike C++, we don't have `?:` in Python, but we have this:
`[on true] if [expression] else [on false]`

If the expression is True, the statement under `[on true]` is executed. Else, that under `[on false]` is executed.
Below is how you would use it:

```python
a, b = 2, 3
min = a if a < b else b
print(min)
```
Above will print `2`.

### 8. What Does the 'is' Operator Do?

Identity operators in Python, `is` and `is not`, are used to check if two values are located on the same part of the memory. Two variables that are equal does not imply that they are identical. `==` checks for equality, while `is` checks for identity (memory address).

For example:
```python
a = 257
b = 257
print(a is b) # False
print(a == b) # True
```
Python caches small integers in the range `-5` to `256`, so if `a = 256` and `b = 256`, `a is b` would be `True`.

### 9. Disadvantages of Python.

Python has several disadvantages:
- **Speed**: Python is an interpreted language and is slow compared to C/C++ or Java. It is a high-level language and execution takes place with the help of an interpreter instead of a compiler.
- **Mobile Development**: Python is strong in desktop and server platforms, but it is considered a weak language for mobile development. Very few mobile applications are built in it.
- **Memory Consumption**: For memory-intensive tasks, Python is not a good choice. Its memory consumption is high due to the flexibility of the data types.
- **Database Access**: Python's database access layer is underdeveloped and primitive compared to popular technologies like JDBC and ODBC. This acts as a major barrier for big enterprises.
- **Runtime Errors**: Python is dynamically typed, so it has errors that only show up at runtime. It requires more testing.
- **Difficulty in Using Other Languages**: Python lovers become so accustomed to its features and extensive libraries that they face problems learning or working on other programming languages.

### 10. How strings are stored in Python?

Strings in Python are arrays of bytes representing Unicode characters. Python does not have a character data type; a single character is simply a string with a length of 1. Strings are immutable, meaning they cannot be changed after they are created.

### 11. What is the Zen of Python?

The Zen of Python is a collection of 19 "guiding principles" for writing computer programs that influence the design of the Python programming language.
Some of the key principles include:
- Beautiful is better than ugly.
- Explicit is better than implicit.
- Simple is better than complex.
- Complex is better than complicated.
- Flat is better than nested.
- Sparse is better than dense.
- Readability counts.
- Special cases aren't special enough to break the rules.

### 12. Identity operator (`is`) vs Equality operator (`==`)?

- **Identity operators**: The `is` and `is not` keywords are called identity operators that compare objects based on their identity (their memory location).
- **Equality operators**: The `==` and `!=` are called equality operators that compare objects based on their values.

### 13. Modules vs Packages vs Library in Python

Python uses some terms that you may not be familiar with if you are coming from a different language:
- **Module**: A module is a Python file intended to be imported into scripts or other modules. It often defines classes, functions, and variables.
- **Package**: A package is a collection of related modules that work together to provide certain functionality. These modules are contained within a folder and can be imported. This folder will often contain a special `__init__.py` file.
- **Library**: A library is an umbrella term that loosely means "a bundle of code." Libraries can have tens or hundreds of individual modules. The Python Standard Library contains hundreds of modules bundled with Python.

### 14. Why `0.3 - 0.2` is not equal to `0.1` in Python?

The reason behind it is called "precision," and it's due to the fact that computers do not compute in Decimal, but in Binary. Computers use a base-2 system (Binary code) to store floating-point numbers, which cannot represent numbers like `0.1` perfectly, leading to minor floating-point inaccuracies.

### 15. What are Python Docstrings?

Python docstrings are the string literals that appear right after the definition of a function, method, class, or module. They are used to document the code and explain its purpose and usage. They can be accessed using the `__doc__` attribute of the object.
