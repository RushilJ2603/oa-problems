# 5. Polymorphism and Abstraction

> **Prerequisites Block:**
> * **Assumed Knowledge:** Inheritance, basic methods.

> **First-use gloss:** **Polymorphism** means "many forms." In programming, it refers to the ability of different types of objects to respond to the same method call in their own specific way [1].

If inheritance is about *sharing* behavior, polymorphism is about *customizing* behavior under a shared name.

## Duck Typing in Python

Python is a dynamically typed language. It does not force you to declare what type a variable is. This design philosophy leads directly to **Duck Typing**.

> **Heavy:** "If it walks like a duck and quacks like a duck, then it must be a duck." [2]

**Analogy:** If a manager asks three employees (an engineer, an accountant, and a designer) to "Do your job," the manager doesn't need to know exactly how each person does their job. The manager just knows that all three respond to the command "Do your job," but the actual work produced is entirely different.

**Instance:**
```python
class Dog:
    def speak(self): return "Woof!"

class Cat:
    def speak(self): return "Meow!"

class Robot:
    def speak(self): return "Beep boop!"

# A function that expects ANY object with a .speak() method
def animal_sound(entity):
    print(entity.speak())

animal_sound(Dog())   # Output: Woof!
animal_sound(Cat())   # Output: Meow!
animal_sound(Robot()) # Output: Beep boop!
```

**Definition:** In Duck Typing, Python doesn't check if the `entity` is strictly an instance of an `Animal` class. It only checks if the `entity` has a `speak()` method at the moment it is called [2]. If the method exists, it works.

*Why it matters here:* This makes Python incredibly flexible. You can design loosely coupled systems where components can be swapped out easily, as long as they implement the expected interface.

> **Trap:** The downside of Duck Typing is that if you pass an object that *doesn't* have the `speak()` method, Python will throw an `AttributeError` at runtime, potentially crashing your program. 

## Magic / Dunder Methods (Operator Overloading)

Python allows you to define how standard operators (`+`, `-`, `==`, `str()`) behave with your custom objects using "magic" or "dunder" (double underscore) methods.

```python
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    def __add__(self, other):
        # Defines behavior for the '+' operator
        return Point(self.x + other.x, self.y + other.y)
        
    def __str__(self):
        # Defines behavior for print() and str()
        return f"({self.x}, {self.y})"

p1 = Point(1, 2)
p2 = Point(3, 4)
p3 = p1 + p2  # Calls p1.__add__(p2)

print(p3)     # Output: (4, 6)
```

## Abstraction and Abstract Base Classes (ABCs)

While Duck Typing is flexible, sometimes you *need* to enforce a strict contract. If you are building a large system, you might want to guarantee that every "PaymentProcessor" class absolutely has a `process_payment()` method before the program even runs.

> **First-use gloss:** **Abstraction** is the concept of hiding complex implementation details behind a simple interface. An **Abstract Base Class (ABC)** is a blueprint that cannot be instantiated itself, but forces its subclasses to implement specific methods [3].

To create an ABC in Python, we import from the `abc` module.

```python
from abc import ABC, abstractmethod

# 1. Inherit from ABC
class PaymentProcessor(ABC):
    
    # 2. Use the @abstractmethod decorator
    @abstractmethod
    def process_payment(self, amount):
        pass

class CreditCardProcessor(PaymentProcessor):
    # If we forget to write process_payment(), Python will crash when we instantiate this.
    def process_payment(self, amount):
        print(f"Processing ${amount} via Credit Card.")

# p = PaymentProcessor()  # TypeError: Can't instantiate abstract class
processor = CreditCardProcessor()
processor.process_payment(100)
```

**A question to sit with:** Duck Typing assumes "we are all consenting adults" and relies on trust. ABCs enforce contracts strictly. In what types of projects would you prefer one over the other?

### References
[1] "Python Tutorial: Classes." docs.python.org. https://docs.python.org/3/tutorial/classes.html
[2] "Duck Typing in Python." realpython.com. https://realpython.com/python-duck-typing/
[3] "Abstract Base Classes." docs.python.org. https://docs.python.org/3/library/abc.html


## Worked & Faded Example
**Worked:** Adding two `Vector` objects via `__add__`.
```python
class Vector:
    def __init__(self, x): self.x = x
    def __add__(self, other): return Vector(self.x + other.x)
```
**Faded:** Implement the `__eq__` (equals) dunder method for `Vector`.
```python
    def __eq__(self, ____):
        return self.x == ____.x
```

## Failure Case
> Duck typing breaks catastrophically at runtime if the object passed does not implement the expected method, throwing an AttributeError.

## Connections
With polymorphism and ABCs, we have strict contracts. Finally, we will look at how to optimize class creation itself in **Advanced Class Mechanics**.
