# Classes and Objects

The class is the central construct of object-oriented C++. It is the mechanism by which data and the functions that act on that data are bundled into a single user-defined type.

## Defining a class

::: definition
A **class** is a user-defined type that acts as a blueprint, describing the properties and behaviours its instances will have. An **object** is a concrete instance built from that blueprint.
:::

A class lists its **data members** (properties or state) and **member functions** (behaviours or methods). By default, everything inside a `class` is private; the `public` access modifier must be explicitly specified to allow outside code to use the members.

```cpp
class Account {
    // By default, members here are private
    int internalId; // Private: inaccessible from outside

public: // Access modifier
    // Public: accessible from anywhere
    int balance;

    void deposit(int amount) {
        balance += amount;
    }
}; // CRITICAL: A class definition must end with a semicolon
```

::: trap
Forgetting the semicolon at the end of a class definition is a classic compilation error. The compiler will often report the error on the *next* line or even in a different file.
:::

## Creating and using objects

Objects can be created in memory just like primitive types, either on the stack or dynamically on the heap.

### Stack allocation (the dot operator)

When an object is declared as a normal local variable, it is created on the stack. Its members are accessed using the **dot operator** (`.`).

```cpp
#include <iostream>

int main() {
    Account acc1;          // Object created on the stack
    Account acc2;          // A second, distinct object
    
    acc1.balance = 1000;   // Accessing a data member
    acc1.deposit(500);     // Calling a member function
    
    acc2.balance = 0;      
    
    std::cout << acc1.balance << "\n"; // Outputs 1000
    std::cout << acc2.balance << "\n"; // Outputs 0
    
    return 0;
}
```

Each object holds its own independent copy of the data members (`acc1` and `acc2` have their own `balance`).

::: keypoint
In Python, all objects are instantiated on the heap and accessed via references, using syntax like `acc1 = Account()`. In C++, a declaration like `Account acc1;` instantiates the object directly on the stack without the `new` keyword.
:::

### Heap allocation (the arrow operator)

Objects can also be dynamically allocated on the heap using the `new` keyword, which returns a pointer to the object. When accessing members through a pointer, use the **arrow operator** (`->`), which acts as shorthand for dereferencing the pointer and then applying the dot operator.

```cpp
int main() {
    // Dynamically allocate an object on the heap
    Account* pAcc = new Account();
    
    // Accessing members via a pointer
    pAcc->balance = 1000;       // Equivalent to (*pAcc).balance = 1000;
    pAcc->deposit(500);         // Equivalent to (*pAcc).deposit(500);
    
    // Heap-allocated objects must be manually destroyed to prevent memory leaks
    delete pAcc;
    
    return 0;
}
```

## Member functions: inline versus out-of-line

A member function can be declared and defined fully inside the class body, as shown above. Alternatively, to keep the class definition clean, a function can be *declared* inside the class but *defined* outside of it.

When defining a member function outside the class, you must prefix the function name with the class name and the **scope resolution operator** (`::`). This tells the compiler that the function belongs to the class.

```cpp
class Rectangle {
public:
    int length;
    int breadth;

    // Inside the class: only the declaration (prototype)
    int area();
};

// Outside the class: the full definition using ClassName::
int Rectangle::area() {
    return length * breadth; // Operates on the object's data members
}
```

## Object size in memory

Because each object needs its own distinct state, every time an object is created, memory is allocated for its data members. 

However, member functions are *not* duplicated per object. The compiled code for a member function is stored exactly once in the program's executable text segment. When you call a member function on an object, the compiler seamlessly passes the memory address of that specific object to the function so it operates on the correct data.

![Objects hold separate data members but share one copy of the member-function code.](assets/s20_object_size.png)

```cpp
#include <iostream>

class Point {
public:
    int x; // 4 bytes
    int y; // 4 bytes
    
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
};

int main() {
    std::cout << sizeof(Point); // Outputs 8
    return 0;
}
```

::: interview
"What is the size of an object in C++?" The size of an object is determined solely by the sum of its non-static data members (plus possible padding for alignment). Member functions do not increase the size of an object. (Note: an empty class has a size of 1 byte, not 0, so every object has a unique memory address.)
:::

## Forward declaration

Sometimes you need to refer to a class before its full definition is available. A **forward declaration** introduces the name of a class to the compiler without defining its contents.

```cpp
class Employee; // Forward declaration announces the class exists

class Department {
public:
    // We can use pointers or references to the incomplete type
    Employee* manager; 
};

// Full definition of Employee provided later
class Employee {
public:
    int id;
};
```

You can only use a forward-declared class in ways that do not require the compiler to know its size or layout (e.g., declaring pointers or references). You cannot declare an object by value (`Employee emp;`) until the full class is defined.
