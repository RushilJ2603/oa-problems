# 6. Advanced Class Mechanics

> **Prerequisites Block:**
> * **Assumed Knowledge:** Classes, instances, decorators (`@`).

As you build more complex systems, you'll encounter scenarios where standard instance methods aren't quite the right fit, or where the boilerplate of writing `__init__` becomes tedious.

## `@classmethod` vs. `@staticmethod`

Standard methods inside a class are **instance methods**: they take `self` as their first parameter, giving them access to modify the specific object they were called on. Python provides two alternative method types via decorators.

### Class Methods
A **class method** takes the class itself as its first parameter (by convention, named `cls` instead of `self`) [1]. It can read and modify class-level state, but not instance-level state.

> **Heavy:** Why would you need a method that modifies the class rather than the instance?

**Analogy:** If instances are cookies and the class is the cookie cutter, a class method is an action that modifies the cookie cutter itself, or uses the cookie cutter to stamp out cookies in a specialized way.

**Instance:** A common use case is creating "Alternative Constructors" [1].
```python
class Date:
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

    @classmethod
    def from_string(cls, date_str):
        # cls refers to the Date class itself
        year, month, day = map(int, date_str.split('-'))
        # Returns a new instance of the class
        return cls(year, month, day)

# Standard creation
d1 = Date(2023, 10, 15)
# Alternative creation via class method
d2 = Date.from_string("2023-10-15")
```

**Definition:** The `@classmethod` decorator binds a method to the class rather than the instance. It receives the class (`cls`) as the implicit first argument.

*Why it matters here:* Using `cls()` instead of hardcoding `Date()` inside the method ensures that if `Date` is subclassed, the alternative constructor will correctly create instances of the subclass, not the parent.

### Static Methods
A **static method** takes neither `self` nor `cls` as an implicit first argument. It behaves exactly like a normal function, but it lives inside the class's namespace because it makes logical sense for it to be there [1].

```python
class MathUtils:
    @staticmethod
    def add(a, b):
        return a + b

print(MathUtils.add(5, 10))
```
Use `@staticmethod` for utility functions that don't need access to class or instance data but conceptually belong with the class.

> **Trap:** Overusing `@staticmethod`. In Python, if a function doesn't need a class, it is perfectly acceptable (and often preferred) to just define it as a standalone function at the module level. Don't force functions into classes just to mimic Java.

## Introduction to Dataclasses

Python 3.7 introduced **Dataclasses**, a major quality-of-life feature for classes that primarily exist to store data [2].

Writing a standard class to hold data requires repetitive boilerplate:
```python
class Book:
    def __init__(self, title, author):
        self.title = title
        self.author = author
        
    def __repr__(self):
        return f"Book(title='{self.title}', author='{self.author}')"
```

> **First-use gloss:** A **Dataclass** is a class decorated with `@dataclass` that automatically generates tedious boilerplate methods like `__init__`, `__repr__`, and `__eq__` behind the scenes [2].

```python
from dataclasses import dataclass

@dataclass
class Book:
    title: str
    author: str

# __init__ is automatically generated!
my_book = Book("Python Tricks", "Dan Bader")

# __repr__ is automatically generated, making printing pretty!
print(my_book)
# Output: Book(title='Python Tricks', author='Dan Bader')
```

Dataclasses require type hints (like `: str`), though Python does not strictly enforce them at runtime. They vastly simplify the creation of data-heavy models.

**A question to sit with:** If a dataclass generates `__init__` for you, how do you execute custom setup logic (like calculating a derived field) immediately after the object is created? (Hint: look up `__post_init__`).

### References
[1] "Python `@classmethod` and `@staticmethod` for Beginners." realpython.com. https://realpython.com/instance-class-and-static-methods-demystified/
[2] "Data Classes in Python 3.7+." realpython.com. https://realpython.com/python-data-classes/


## Worked & Faded Example
**Worked:** A dataclass representing a Coordinate.
```python
from dataclasses import dataclass
@dataclass
class Coordinate:
    lat: float
    lon: float
```
**Faded:** Create a dataclass for a `Product` with `name` and `price`.
```python
from dataclasses import ____
@____
class Product:
    ____: str
    price: ____
```

## Failure Case
> Dataclasses break (or rather, are inappropriate) when your class is primarily logic-heavy rather than data-heavy, or when you need complex validation during initialization.

## Connections
This concludes the core masterclass on Python OOP. You can now build robust, maintainable data models and systems using classes, properties, and inheritance.
