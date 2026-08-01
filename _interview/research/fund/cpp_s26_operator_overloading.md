# Operator Overloading

Built-in operators such as `+`, `*`, and `<<` work natively on the language's built-in types. **Operator overloading** allows you to redefine how these operators work for *user-defined* types (classes and structs), enabling intuitive syntax like `a + b` instead of `a.add(b)`.

::: definition
**Operator overloading** is the mechanism of providing custom implementations for standard C++ operators when applied to user-defined types. It is syntactic sugar for a function call.
:::

## What can and cannot be overloaded

Most C++ operators can be overloaded, including arithmetic (`+`, `-`), assignment (`=`, `+=`), comparison (`==`, `<`), and even memory allocation (`new`, `delete`). 

However, a few specific operators **cannot** be overloaded because doing so would fundamentally alter the language's evaluation rules:
- `.` (member access)
- `.*` (pointer-to-member access)
- `::` (scope resolution)
- `?:` (ternary conditional)
- `sizeof`, `typeid`, `alignof`

::: trap
You cannot invent new operators (like `**` for exponentiation), nor can you change an operator's precedence, associativity, or the number of operands it takes.
:::

## Member vs non-member operators

An operator can be implemented as a **member function** of a class, or as a **non-member (free) function** (often a `friend`).

### Member functions
When overloaded as a member function, the left-hand operand is the object the function is called on (`*this`). The right-hand operand (if binary) is passed as the argument.

```cpp
class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Member: Left operand is 'this', right operand is 'rhs'
    Complex operator+(const Complex& rhs) const {
        return Complex(real + rhs.real, imag + rhs.imag);
    }
};
// Usage: c1 + c2  =>  c1.operator+(c2)
```

### Non-member (friend) functions
When overloaded as a non-member function, all operands are passed as explicit arguments. It is often declared as a `friend` inside the class to grant access to private data.

```cpp
class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Friend: Symmetric operands
    friend Complex operator+(const Complex& lhs, const Complex& rhs);
};

// Non-member implementation
Complex operator+(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.real + rhs.real, lhs.imag + rhs.imag);
}
// Usage: c1 + c2  =>  operator+(c1, c2)
```

### How to choose

::: keypoint
**Rule of thumb for choosing:**
1. Must it be a member? (`=`, `[]`, `()`, `->` *must* be members).
2. Is the left-hand side a different type that you don't own? (e.g. `std::ostream` in `cout << obj`). Use a non-member.
3. Do you want symmetry? If implicit conversions should apply to *both* the left and right operands equally (e.g. `1.5 + c` and `c + 1.5`), use a non-member.
4. Otherwise, prefer a member function.
:::

## Canonical signatures

Proper const-correctness and return types are critical when overloading operators to match the behaviour of built-in types.

### Arithmetic and compound assignment (+, +=)

Compound assignment modifies the existing object and returns a reference to `*this`. Arithmetic operators return a new object by value. 

```cpp
class Vector2D {
public:
    double x, y;
    Vector2D(double x, double y) : x(x), y(y) {}

    // Compound assignment modifies *this, returns reference
    Vector2D& operator+=(const Vector2D& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};

// Arithmetic operators are typically non-members implemented via compound assignment
Vector2D operator+(Vector2D lhs, const Vector2D& rhs) {
    lhs += rhs; // reuse +=
    return lhs; // Return by value
}
```

::: trap
Never return a reference to a local variable created inside the operator function. When returning a new object (like in `operator+`), return by value. Returning a reference to a local variable leads to undefined behaviour as the object is destroyed when the function exits.
:::

### Comparison (==, <)

Comparison operators should return `bool` and take operands by `const` reference.

```cpp
bool operator==(const Vector2D& lhs, const Vector2D& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
```

::: keypoint
**C++20 spaceship operator (`<=>`)**: In modern C++, you can default the three-way comparison operator. The compiler will automatically generate all six comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`) for you, performing member-wise comparison.
```cpp
auto operator<=>(const Vector2D&) const = default;
```
:::

### Stream insertion and extraction (<<, >>)

Because the left operand is an `ostream` (like `std::cout`) or `istream` (like `std::cin`), these **must** be non-member functions. They take the stream by reference and return the stream by reference to allow chaining (`cout << a << b`).

```cpp
#include <iostream>
#include <string>

class Person {
    std::string name;
    int age;
public:
    Person(std::string n, int a) : name(n), age(a) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << " (" << p.age << ")";
        return os; // Enables chaining
    }
    
    friend std::istream& operator>>(std::istream& is, Person& p) {
        is >> p.name >> p.age;
        return is;
    }
};
```

### The assignment operator (=)

The copy assignment operator replaces the contents of an existing object. It is a special member function generated automatically, but if your class manages raw resources (like heap memory), you must overload it to perform a **deep copy**.

```cpp
#include <cstring>

class String {
    char* data;
public:
    // ... constructors and destructors omitted ...

    String& operator=(const String& rhs) {
        if (this == &rhs) {
            return *this; // Self-assignment check
        }
        
        delete[] data; // Clean up old resource
        
        // Deep copy new resource
        data = new char[std::strlen(rhs.data) + 1];
        std::strcpy(data, rhs.data);
        
        return *this; // Return reference to allow a = b = c
    }
};
```

::: interview
A classic interview trap is forgetting the **self-assignment check** (`if (this == &rhs)`). Without it, assigning an object to itself (`str = str;`) will first delete its own data, and then attempt to copy from the now-deleted data, causing a crash.
:::

### Subscript operator []

The subscript operator must be a member function. It is typically overloaded in pairs: a non-const version that returns a reference (allowing modification), and a `const` version that returns a `const` reference (for read-only access).

```cpp
class IntArray {
    int* array;
    int size;
public:
    // Non-const version: enables writing, e.g. arr[0] = 5;
    int& operator[](int index) {
        return array[index]; // Bounds checking omitted for brevity
    }

    // Const version: enables reading from const objects
    const int& operator[](int index) const {
        return array[index];
    }
};
```

### Function call operator ()

Overloading `operator()` allows an object to be invoked as if it were a function. Such objects are called **functors** (or function objects). They are heavily used in C++ standard algorithms to maintain state across calls.

```cpp
class Multiplier {
    int factor;
public:
    Multiplier(int f) : factor(f) {}

    int operator()(int value) const {
        return value * factor;
    }
};

int main() {
    Multiplier timesFive(5);
    int result = timesFive(10); // Calls operator()(10), returns 50
    return 0;
}
```

### Increment and decrement (++, --)

To distinguish between prefix (`++x`) and postfix (`x++`) forms, the postfix version takes a dummy `int` parameter. Prefix modifies and returns the object itself, while postfix must save the old state, modify the object, and return the old state by value.

```cpp
class Counter {
    int count;
public:
    Counter(int c = 0) : count(c) {}

    // Prefix (++c): Return reference to self
    Counter& operator++() {
        ++count;
        return *this;
    }

    // Postfix (c++): Dummy int parameter. Return old value by value.
    Counter operator++(int) {
        Counter temp = *this; // Save old state
        ++count;              // Modify self
        return temp;          // Return old state
    }
};
```
