# 4. Inheritance

> **Prerequisites Block:**
> * **Assumed Knowledge:** Classes, initialization, attributes.

> **First-use gloss:** **Inheritance** is a mechanism where a new class (the child or subclass) derives properties and behaviors from an existing class (the parent or base class) [1].

Inheritance promotes code reuse. Instead of rewriting the same logic, a subclass inherits it for free, and can then add new logic or override existing logic.

## Single Inheritance

In single inheritance, a child class inherits from exactly one parent class. The parent class is passed as an argument in the class definition.

```python
class Animal:
    def eat(self):
        print("Consuming calories.")

class Dog(Animal):  # Dog inherits from Animal
    def bark(self):
        print("Woof!")

buddy = Dog()
buddy.eat()   # Inherited from Animal
buddy.bark()  # Specific to Dog
```

## Method Overriding and `super()`

Often, a child class needs to change how a parent's method works. This is called **overriding**.

If you override the `__init__` method, the child's `__init__` completely replaces the parent's. But what if you still need the parent's initialization logic? You use `super()`.

> **First-use gloss:** `super()` is a built-in function that returns a temporary object of the superclass, allowing you to call its methods [2].

```python
class Animal:
    def __init__(self, name):
        self.name = name

class Dog(Animal):
    def __init__(self, name, breed):
        # Call the parent's __init__ to handle the name
        super().__init__(name)
        # Handle the Dog-specific attribute
        self.breed = breed

buddy = Dog("Buddy", "Golden Retriever")
print(buddy.name, buddy.breed)
```

## Multiple Inheritance

Python allows a class to inherit from multiple parents at once.

```python
class Swimmer:
    def swim(self):
        print("Swimming in water.")

class Flyer:
    def fly(self):
        print("Flying in the sky.")

class Duck(Swimmer, Flyer):
    pass

donald = Duck()
donald.swim()
donald.fly()
```

## Method Resolution Order (MRO)

> **Heavy:** When inheriting from multiple classes, what happens if both parents have a method with the exact same name?

**Analogy:** Imagine asking your parents for permission. If your mom says "yes" and your dad says "no," whose rule do you follow? You need a strict hierarchy—an order of operations—to resolve the conflict.

![MRO Diamond Inheritance](assets/mro_diamond.png)
*Figure 2: A visual representation of the "Diamond Problem" where `class D` inherits from both `B` and `C`, which both inherit from `A`.*

**Instance:**
```python
class A:
    def say(self): print("A")

class B(A):
    def say(self): print("B")

class C(A):
    def say(self): print("C")

class D(B, C):
    pass

d_obj = D()
d_obj.say()  # Prints "B"
```

**Definition:** The **Method Resolution Order (MRO)** is the strict sequence in which Python searches for methods and attributes within a class hierarchy [3]. Python uses an algorithm called **C3 Linearization** to compute this order [4]. 

The C3 algorithm ensures two critical properties:
1. Children precede their parents (e.g., `D` is checked before `B` and `C`).
2. The order of parents listed in the class definition is preserved (`B` is listed before `C`, so `B` is checked before `C`).

You can view the exact order Python calculated by checking the `__mro__` attribute or calling `.mro()`:

```python
print(D.mro())
# [<class '__main__.D'>, <class '__main__.B'>, <class '__main__.C'>, <class '__main__.A'>, <class 'object'>]
```

*Why it matters here:* Multiple inheritance can quickly create confusing "diamond problems" where tracing execution paths becomes a nightmare. MRO provides a predictable, unambiguous path through the inheritance tree.

> **Trap:** Using multiple inheritance casually. Because MRO and state management (e.g., calling multiple `super().__init__()`) can get incredibly complex, modern software design favors composition (having objects as attributes) over deep or wide inheritance trees [2].

**A question to sit with:** Based on the MRO output above, every class eventually traces back to `<class 'object'>`. What is `object`, and what does it provide?

### References
[1] "Python Tutorial: Classes." docs.python.org. https://docs.python.org/3/tutorial/classes.html
[2] "Object-Oriented Programming (OOP) in Python 3." realpython.com. https://realpython.com/python3-object-oriented-programming/
[3] "Method Resolution Order (MRO) in Python." geeksforgeeks.org. https://www.geeksforgeeks.org/method-resolution-order-in-python-inheritance/
[4] "The Python 2.3 Method Resolution Order." python.org. https://www.python.org/download/releases/2.3/mro/


## Worked & Faded Example
**Worked:**
```python
class Bird:
    def fly(self): print('Flying')
class Penguin(Bird):
    def fly(self): print('Cannot fly')
```
**Faded:** Override the `make_sound` method for a `Cat`.
```python
class Animal:
    def make_sound(self): print('Generic sound')
class Cat(____):
    def make_sound(____):
        print(____)
```

## Failure Case
> Multiple inheritance breaks down (becomes an unmaintainable tangled mess) when parents have complex overlapping state initializations. Favor composition!

## Connections
Inheritance allows objects to share methods. But what if we want different objects to use the same method names differently? We explore this in **Polymorphism**.
