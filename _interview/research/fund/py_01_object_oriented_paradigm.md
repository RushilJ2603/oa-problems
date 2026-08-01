# 1. The Object-Oriented Paradigm

> **First-use gloss:** **Object-Oriented Programming (OOP)** is a programming paradigm based on the concept of "objects," which can contain data and code: data in the form of fields (often known as attributes), and code in the form of procedures (often known as methods) [1].

## Procedural vs. OOP Approach

Historically, programs were written as a sequence of steps or functions that act upon data. This is known as procedural programming. In procedural programming, data and functions are completely separate entities. 

While this works well for simple scripts, managing global state in large applications can become unwieldy. When hundreds of functions manipulate shared data, modifying one piece of data can cause unpredictable bugs elsewhere.

OOP solves this by bundling the data and the functions that operate on that data into a single unit called an object [2]. Instead of having a function `drive(car)` that operates on a separate `car` data structure, you have a `car` object that knows how to `drive()` itself. This modularity makes complex systems easier to design, scale, and maintain.

## The Four Pillars: High-Level Overview

The OOP paradigm is traditionally supported by four foundational principles [3]. We will explore these deeply in later sections, but it is useful to know their names upfront:

1. **Encapsulation:** Grouping related data and functions together, and restricting outside access to internal state to prevent accidental interference.
2. **Inheritance:** Creating new classes based on existing ones, promoting code reuse.
3. **Polymorphism:** The ability of different types of objects to respond to the same method call in their own specific way.
4. **Abstraction:** Hiding complex implementation details behind a simple interface.

## Everything is an Object in Python

> **Heavy:** Python takes the OOP paradigm further than many other languages.

**Analogy:** In some languages, numbers and letters are like raw materials (wood, metal), while complex data structures are like manufactured products (a car, a house). In Python, *everything* you interact with is already a fully manufactured product with built-in features, even the simplest numbers.

**Instance:**
```python
x = 5
print(type(x))
# Output: <class 'int'>
```
Notice that `5` isn't just a raw mathematical value; it is an instance of the `int` class.

**Definition:** In Python, every piece of data—numbers, strings, functions, and even classes themselves—is an object [4]. This means that every value has a type (which is a class), and every value possesses attributes and methods that dictate its behavior. This uniform design means you can pass a function into another function exactly the same way you pass an integer.

*Why it matters here:* Because everything is an object, the rules of OOP apply universally across the language, making Python's behavior highly consistent.

> **Trap:** Believing that basic data types like integers and booleans are "primitives" without methods. In Python, there are no primitive types in the Java or C sense; you can literally call methods on a number, such as `(5).bit_length()`.

**A question to sit with:** If a class defines how an object behaves, and a class is itself an object, what defines how a class behaves? (We will answer this when we reach Metaclasses).

### References
[1] "Python Tutorial: Classes." docs.python.org. https://docs.python.org/3/tutorial/classes.html
[2] "Object-Oriented Programming (OOP) in Python 3." realpython.com. https://realpython.com/python3-object-oriented-programming/
[3] "Differences between Procedural and Object Oriented Programming." geeksforgeeks.org. https://www.geeksforgeeks.org/differences-between-procedural-and-object-oriented-programming/
[4] "Data model." docs.python.org. https://docs.python.org/3/reference/datamodel.html


## Worked & Faded Example
**Worked:** Designing a system procedural vs OOP.
*Procedural:* `def calculate_salary(base, bonus): return base + bonus`
*OOP:* `class Employee: def get_salary(self): return self.base + self.bonus`
**Faded:** Try to design a `Bank` system. What data goes into the `Account` object? What methods does it need? (e.g. `deposit`, `____`)

## Failure Case
> This paradigm breaks when you need hyper-optimized, cache-friendly data processing (Data-Oriented Design is often better there) or purely mathematical transformations (Functional Programming is better).

## Connections
This lays the theoretical foundation. Next, we will see how Python specifically creates these objects using **Classes and Instances**.
