# Member Functions: Categories, Definition, and Scope Resolution

A class's behaviour is defined by its **member functions** (often called methods in other languages). This section covers how they are categorised, where they are defined, how they pass and return objects, and the critical `const` qualifier.

## Categories of member functions

Member functions generally fall into four standard categories based on their role in managing the object's state. These are conventions, not distinct language features.

| Category | Role | Example |
| :--- | :--- | :--- |
| **Manager** | Initialise, copy, move, or clean up the object. | `Rectangle()`, `~Rectangle()` |
| **Accessor** (Getter) | Read a data member without modifying the object. | `int getLength() const;` |
| **Mutator** (Setter) | Change a data member, often enforcing invariants. | `void setLength(int l);` |
| **Utility** (Facilitator) | Compute values or perform operations using the state. | `int calculateArea() const;` |

*(Note: **Static member functions** operate on the class as a whole rather than a specific object; they are covered fully in a dedicated section.)*

## Defining functions: inside vs outside

A member function can be defined **inside** the class body, or merely declared there and **defined outside** using the **scope resolution operator** (`::`). 

### Inside the class (implicitly inline)

Defining a function directly inside the class body is convenient for short functions like getters and setters.

```cpp
class Rectangle {
private:
    int length = 0;
    int breadth = 0;

public:
    // Defined inside: implicitly inline
    int getArea() {
        return length * breadth; 
    }
};
```

Any function defined *inside* the class body is implicitly marked as `inline`, meaning the compiler is encouraged to substitute the function call with the actual code to avoid function-call overhead. 

::: keypoint
Inside a class, the order of member function definitions does not matter. The compiler parses the class declarations in a first pass, and then the function bodies in a second pass. A function near the top can call one declared near the bottom.
:::

### Outside the class (using `::`)

For longer or more complex functions, the best practice is to *declare* the function inside the class (typically in a header file) and *define* it outside (typically in a `.cpp` file). 

To define a member function outside its class, you must prefix its name with the class name and the **scope resolution operator** (`::`), so the compiler knows which class the function belongs to.

```cpp
class Rectangle {
private:
    int length;
    int breadth;

public:
    // Declaration only
    void setDimensions(int l, int b);
};

// Definition outside using scope resolution
void Rectangle::setDimensions(int l, int b) {
    if (l >= 0 && b >= 0) {
        length = l;
        breadth = b;
    }
}
```

The syntax `void Rectangle::setDimensions` reads as "the `setDimensions` function returning `void` that belongs to the `Rectangle` class". 

If you define a function outside the class but still want it to be inline (for example, if you are defining it outside the class but still within the same header file), you must explicitly use the **`inline` keyword**:

```cpp
inline void Rectangle::setDimensions(int l, int b) {
    // ...
}
```

## Passing and returning objects

Member functions frequently take objects as parameters or return them. Because objects can be large, you must choose how to pass them carefully to avoid expensive copying.

### Passing objects

When an object is passed **by value**, the entire object is copied. This invokes the copy constructor and is generally inefficient for class types. Instead, objects should almost always be passed **by reference** (`&`) to avoid the copy, or **by const reference** (`const &`) if the function should not modify the argument.

```cpp
class Vector2D {
public:
    double x, y;

    // Pass by const reference: avoids copying, prevents modification
    void add(const Vector2D& other) {
        this->x += other.x;
        this->y += other.y;
    }
};
```

### Returning objects

Functions can return objects by value or by reference. Returning **by value** is standard when creating a *new* object, as modern C++ compilers optimise away the copy (Return Value Optimization or RVO). Returning **by reference** is used when returning an existing object (like `*this` for chaining).

```cpp
class Vector2D {
public:
    double x, y;

    // Return by value: returning a brand new object
    Vector2D add(const Vector2D& other) const {
        return Vector2D{this->x + other.x, this->y + other.y};
    }
    
    // Return by reference: returning the current object for chaining
    Vector2D& scale(double factor) {
        x *= factor;
        y *= factor;
        return *this;
    }
};
```

::: trap
Never return a reference to a local variable created inside the function. The local variable will be destroyed when the function ends, leaving a dangling reference. Always return by value when generating new objects.
:::

## Const member functions

A **const member function** guarantees that it will not modify the state of the object it is called on. You declare a function as const by placing the `const` keyword at the end of the declaration, after the parameter list (and before the body, if defining it).

```cpp
class BankAccount {
private:
    int balance;

public:
    BankAccount(int initial) : balance(initial) {}

    // const member function: guarantees it won't change data members
    int getBalance() const {
        // balance += 10; // ERROR: assignment of member in read-only object
        return balance;
    }
    
    void deposit(int amount) {
        balance += amount; // allowed, not a const function
    }
};
```

### Why `const` is critical

If you pass an object to a function by `const` reference, the compiler treats that object as read-only. Consequently, **you can only call `const` member functions on a `const` object**. 

```cpp
void printAccount(const BankAccount& acc) {
    // std::cout << acc.deposit(50); // ERROR: deposit() is not const
    std::cout << acc.getBalance();   // OK: getBalance() is const
}
```

::: interview
A classic interview question is "What is `const` correctness?". It is the practice of consistently marking member functions as `const` when they do not modify state, and passing objects by `const Type&` when you don't intend to modify them. If you fail to mark an accessor as `const`, users of your class will be unable to read data from `const` instances of it!
:::

### The `mutable` keyword

Sometimes, a `const` member function needs to modify a specific data member that does not affect the object's logically observable state. Common examples are mutexes for thread safety or cached values. 

The **`mutable` keyword** is applied to a data member to exempt it from `const` enforcement. This allows "logical constness" even if the bitwise state of the object changes.

```cpp
class ExpensiveCalculator {
private:
    int data;
    mutable int cachedResult = 0;
    mutable bool isCached = false;

public:
    ExpensiveCalculator(int d) : data(d) {}

    // Logically const: the answer doesn't change, but we cache it internally
    int compute() const {
        if (!isCached) {
            cachedResult = data * 42; // Expensive computation here
            isCached = true;          // Modifying mutable members is allowed
        }
        return cachedResult;
    }
};
```

## Ref-qualified member functions (C++11)

Just as a function can be marked `const` to indicate it should be called on a `const` object, C++11 introduced **ref-qualified member functions**. By appending `&` or `&&` to the function signature, you restrict whether the function can be called on an lvalue (a persistent object) or an rvalue (a temporary object).

```cpp
class DataBuffer {
public:
    // Called only on lvalues (named, persistent objects)
    void process() & {
        // ...
    }

    // Called only on rvalues (temporary objects)
    void process() && {
        // ...
    }
};

int main() {
    DataBuffer buf;
    buf.process();            // Calls process() &
    
    DataBuffer().process();   // Calls process() &&
}
```

This is an advanced feature primarily used to optimise return types or prevent dangerous operations on temporary objects.
