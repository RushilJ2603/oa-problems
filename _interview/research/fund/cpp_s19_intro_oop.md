# Introduction to Object-Oriented Programming

An earlier section traced the path from monolithic code through to procedural style. **Object-oriented programming** (OOP) is the next step, and it becomes essential as systems grow large and complex.

## Procedural versus object-oriented style

In a **procedural style**, a program is organised as a flat collection of functions operating on passive, shared data. 

```cpp
// Procedural C++
struct Account {
    int balance;
};

void deposit(Account& acc, int amount) {
    acc.balance += amount;
}
```

This is workable for small programs. However, as the system grows, functions and data become disconnected. Any function might modify any piece of data, making the system difficult to reason about and fragile to change.

Object-oriented programming instead groups related data together with the functions that act upon it into self-contained units, and lets a large system be decomposed into cooperating parts. The analogy is a government divided into departments — Electricity, Water, Transport — each an independent unit with its own responsibilities and internal workings, together making a large organisation manageable.

```cpp
// Object-oriented C++
class Account {
private:
    int balance;
public:
    void deposit(int amount) {
        balance += amount;
    }
};
```

## Classes and objects

::: definition
A **class** is a user-defined type that acts as a blueprint, grouping data and functions together. An **object** is a concrete instance of that class created in memory.
:::

A class does not occupy memory itself (beyond the compiler's internal tracking), much like the blueprint of a house is not a house. The object is the actual entity you create and manipulate.

```cpp
// 'Account' is the class (the blueprint)
class Account {
public:
    int balance = 0;
};

int main() {
    // 'acc1' and 'acc2' are objects (instances of Account)
    Account acc1;
    Account acc2;
    return 0;
}
```

::: keypoint
In Python, you also define classes using the `class` keyword, but you instantiate them with `acc = Account()`. In C++, an object declaration like `Account acc;` instantiates the object directly on the stack — no `new` keyword is used unless you specifically want heap allocation.
:::

## A minimal complete class example

Here is a simple but complete class representing a rectangle, showing how data and functions are bundled:

```cpp
#include <iostream>

class Rectangle {
private:
    // Data members (state)
    int length = 0;
    int breadth = 0;

public:
    // Member functions (behaviour)
    void setDimensions(int l, int b) {
        if (l >= 0 && b >= 0) {
            length = l;
            breadth = b;
        }
    }

    int getArea() {
        return length * breadth;
    }
};

int main() {
    Rectangle rect;                  // Instantiate an object
    rect.setDimensions(10, 5);       // Call a member function
    std::cout << rect.getArea();     // Outputs 50
    return 0;
}
```

## The four pillars of OOP

OOP rests on four foundational principles. We introduce them briefly here; the mechanics of each are covered deeply in later sections.

### 1. Encapsulation

**Encapsulation** is bundling data and the functions that operate on it into a single unit (the class), and controlling access to that data. This enables **data hiding**, preventing external code from bypassing validation or putting the object into an invalid state.

```cpp
class Bank {
private: // Hidden from outside
    int vaultCash;
public:  // Accessible interface
    void deposit(int amount) { vaultCash += amount; }
};
```

::: interview
Encapsulation is frequently tested conceptually. Be precise: *encapsulation* is the mechanism of bundling data and methods, while *data hiding* is the security benefit achieved by using access modifiers (`private`/`public`) within that bundle.
:::

### 2. Abstraction

**Abstraction** means exposing only the essential features of an entity while hiding the complex background details. You can drive a car by using the steering wheel and pedals without understanding the engine's combustion mechanics.

```cpp
class CoffeeMachine {
public:
    void brewEspresso(); // The simple interface exposed to the user
private:
    void grindBeans();   // Hidden complex implementation details
    void heatWater();
};
```

### 3. Inheritance

**Inheritance** is the ability to derive a new class from an existing one, so that shared structure and behaviour are written once and reused. The new class inherits the properties of the base class and can add its own specifics.

```cpp
class Animal {
public:
    void eat();
};

// Dog inherits from Animal
class Dog : public Animal {
public:
    void bark(); 
};
```

### 4. Polymorphism

**Polymorphism** (meaning "many forms") allows code to treat objects of different types through the same interface, letting the same operation behave appropriately for the specific type of object being acted upon.

```cpp
class Shape {
public:
    virtual void draw() = 0; // Common interface
};

class Circle : public Shape {
public:
    void draw() override { /* draw circle */ }
};

class Square : public Shape {
public:
    void draw() override { /* draw square */ }
};
```
