# 3. Encapsulation and Access Control

> **Prerequisites Block:**
> * **Assumed Knowledge:** Classes, instances, attributes.

> **First-use gloss:** **Encapsulation** is the principle of bundling data (attributes) and the methods that operate on that data into a single unit (a class), and restricting direct access to some of the object's components [1].

In many programming languages (like Java or C++), encapsulation is strictly enforced by the compiler using keywords like `public`, `private`, and `protected`. Python does not have these keywords. Instead, it relies on conventions and trust: "we are all consenting adults here" [2].

## Access Control Conventions

Python uses underscores to signal how an attribute or method should be accessed.

### Public Members
By default, all attributes and methods in a Python class are public. They can be accessed from anywhere.
```python
class Car:
    def __init__(self):
        self.color = "Red"  # Public attribute
```

### Protected Members (`_`)
Prefixing a name with a single underscore (e.g., `_model`) is a strong convention indicating that the attribute is intended for internal use only [1]. 

> **Heavy:** A single underscore does not actually prevent access.

**Analogy:** A single underscore is like putting a "Staff Only" sign on an unlocked door. Anyone *can* walk in, but they are warned that they shouldn't, and if they break something, it's their own fault.

**Instance:**
```python
class Car:
    def __init__(self):
        self._engine_temp = 90  # Protected by convention

my_car = Car()
# You CAN do this, but you SHOULD NOT:
print(my_car._engine_temp) 
```

**Definition:** The single underscore prefix `_` is a signal to other programmers. It tells them: "This is an internal implementation detail. Do not rely on it, as it may change without notice." Python itself does nothing to restrict access to it.

*Why it matters here:* This convention keeps the public API clean while allowing developers to inspect internal state during debugging without jumping through hoops.

### Private Members and Name Mangling (`__`)
Prefixing a name with double underscores (e.g., `__serial_number`) invokes a specific Python mechanism called **name mangling**.

> **First-use gloss:** **Name mangling** is a process where Python automatically rewrites the attribute name internally to include the class name, making it harder to access from outside [1].

```python
class Car:
    def __init__(self):
        self.__serial_number = "12345ABC"

my_car = Car()
# print(my_car.__serial_number)  # Raises AttributeError!
```

> **Trap:** Believing that name mangling makes an attribute truly secure. It doesn't. Python renames `__serial_number` to `_Car__serial_number`. If you know the class name, you can still access it: `print(my_car._Car__serial_number)`. The primary purpose of name mangling is not security, but to avoid name collisions when classes are inherited [2].

## The `@property` Decorator

If Python relies on conventions, how do you protect data from invalid values (e.g., setting a temperature to absolute zero)? 

In Java, you would write `get_temperature()` and `set_temperature(value)` methods. In Python, this is considered unpythonic. Instead, we use the `@property` decorator to make a method act like an attribute [3].

```python
class Thermometer:
    def __init__(self):
        self._temp_c = 0  # Internal storage

    @property
    def temperature(self):
        """The getter."""
        return self._temp_c

    @temperature.setter
    def temperature(self, value):
        """The setter with validation logic."""
        if value < -273.15:
            raise ValueError("Temperature cannot be below absolute zero!")
        self._temp_c = value

t = Thermometer()
t.temperature = 25       # Calls the setter
print(t.temperature)     # Calls the getter
# t.temperature = -300   # Raises ValueError
```

**A question to sit with:** If you start a project using public attributes (e.g., `t.temperature`), and later realize you need validation, how does the `@property` decorator save you from having to rewrite all the code that uses your class?

### References
[1] "Python Tutorial: Classes." docs.python.org. https://docs.python.org/3/tutorial/classes.html
[2] "Object-Oriented Programming (OOP) in Python 3." realpython.com. https://realpython.com/python3-object-oriented-programming/
[3] "Encapsulation in Python." codesignal.com. https://codesignal.com/blog/python/encapsulation-in-python/


## Worked & Faded Example
**Worked:** Using `@property` to ensure age is positive.
```python
class User:
    def __init__(self): self._age = 0
    @property
    def age(self): return self._age
    @age.setter
    def age(self, val):
        if val < 0: raise ValueError()
        self._age = val
```
**Faded:** Create a `password` setter that enforces a minimum length of 8.
```python
    @password.____
    def password(self, val):
        if len(val) < ____:
            raise ____('Too short')
        self._password = val
```

## Failure Case
> The `@property` decorator breaks (causes infinite recursion) if you accidentally assign to `self.temperature` inside the setter instead of the internal `self._temp_c`.

## Connections
Encapsulation protects a single object. Next, we'll see how objects can share behavior and build on each other using **Inheritance**.
