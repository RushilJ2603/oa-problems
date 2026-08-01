# 2. Classes and Instances

> **First-use gloss:** A **Class** is a user-defined blueprint or prototype from which objects are created. An **Instance** (or object) is a specific realization of any object created from that blueprint [1].

## Defining a Class

Classes are defined using the `class` keyword, conventionally followed by a capitalized name (CamelCase).

![Class vs Instance](assets/class_vs_instance.png)
*Figure 1: The `Dog` class acts as a single blueprint to instantiate multiple distinct instances (Buddy, Lucy) with their own state.*

```python
class Dog:
    pass
```
Here, `pass` is a placeholder indicating an empty block. Even though it is empty, `Dog` is now a valid class.

## Creating an Instance

To create an object from this blueprint, we "call" the class as if it were a function. This process is known as **instantiation**.

```python
my_dog = Dog()
print(type(my_dog))
# Output: <class '__main__.Dog'>
```

`my_dog` is now an instance of the `Dog` class.

## State and Behavior: Attributes and Methods

A class bundles two things:
1. **State (Attributes):** The data or variables that belong to the object.
2. **Behavior (Methods):** The functions that belong to the object and typically operate on its state.

> **First-use gloss:** **Methods** are simply functions that are defined inside a class body [1].

```python
class Dog:
    species = "Canis familiaris"  # Class attribute

    def bark(self):               # Method
        print("Woof!")
```

## The Constructor: `__init__` and `self`

> **Heavy:** How does an object get its initial state when it is created?

**Analogy:** Think of a class as a factory form for ordering a customized car. The form itself (the class) just says a car needs a color and an engine type. The `__init__` method is the factory worker who reads your specific order (e.g., "Red", "V8") and paints that specific car. `self` is the worker pointing at the exact car currently on the assembly line, ensuring they don't paint the car next to it by mistake.

**Instance:**
```python
class Dog:
    def __init__(self, name, age):
        self.name = name  # Instance attribute
        self.age = age    # Instance attribute

buddy = Dog("Buddy", 3)
print(buddy.name)  # Output: Buddy
```

**Definition:** 
- The `__init__()` method is a special method automatically invoked whenever a new instance of a class is created [1]. It is used to initialize the object's initial state (its **instance attributes**).
- The `self` parameter refers to the specific instance of the class that is currently being operated upon [2]. When you write `self.name = name`, you are storing the value inside that specific object's memory space.

*Why it matters here:* Without `self`, variables inside `__init__` would just be temporary local variables that disappear when the method finishes. `self` is what attaches the data to the object permanently.

> **Trap:** Forgetting to include `self` as the first parameter in an instance method. If you define `def bark():` instead of `def bark(self):`, calling `buddy.bark()` will throw a `TypeError` because Python automatically passes the instance itself as the first invisible argument behind the scenes.

**A question to sit with:** Since Python automatically passes the instance to the method, what happens if we call the method directly on the class itself, like `Dog.bark(buddy)`? (Try it—it works exactly the same way!)

### Worked Example: Building a Basic Class

Let's put it together to model a bank account.

```python
class BankAccount:
    # __init__ sets up the initial state of the specific account
    def __init__(self, owner, starting_balance=0):
        self.owner = owner
        self.balance = starting_balance
        
    # A method that modifies the state
    def deposit(self, amount):
        if amount > 0:
            self.balance += amount
            print(f"Deposited {amount}. New balance: {self.balance}")
```

We can now instantiate multiple independent accounts:

```python
alice_account = BankAccount("Alice", 100)
bob_account = BankAccount("Bob")

alice_account.deposit(50)
# Output: Deposited 50. New balance: 150

print(bob_account.balance)
# Output: 0
```
Notice how `alice_account` and `bob_account` maintain completely separate `balance` states, thanks to `self`.

### References
[1] "Python Tutorial: Classes." docs.python.org. https://docs.python.org/3/tutorial/classes.html
[2] "Object-Oriented Programming (OOP) in Python 3." realpython.com. https://realpython.com/python3-object-oriented-programming/


## Worked & Faded Example
**Worked:** 
```python
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
```
**Faded:** Complete the initialization for a `Rectangle` with width and height.
```python
class Rectangle:
    def __init__(____, width, ____):
        self.width = ____
        self.height = ____
```

## Failure Case
> Classes break when you use them simply to group standalone functions that don't share any state. (Just use a module for that!).

## Connections
Now that we can create stateful objects, we need to protect that state from being invalid, which leads us to **Encapsulation**.
