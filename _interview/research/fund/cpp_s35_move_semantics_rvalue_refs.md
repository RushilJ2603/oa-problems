# Move Semantics and Rvalue References

::: heavy
Dense section — slow down. This introduces value categories, rvalue references, and the mechanics of stealing resources from temporary objects.
:::

## Value categories: lvalues and rvalues

Before we can move anything, we must understand *what* is safe to move from. C++ classifies every expression into a value category. The two fundamental categories are **lvalues** and **rvalues**.

::: definition
An **lvalue** (locator value) is an expression that refers to a persistent memory location. It has a name or an identifiable address. An **rvalue** is a temporary value that does not persist beyond the expression that uses it.
:::

```cpp
int x = 10;
// 'x' is an lvalue (it has a name and address).
// '10' is an rvalue (it is a temporary literal).

x = 20; // OK: lvalue on the left, rvalue on the right.
// 20 = x; // ERROR: cannot assign to an rvalue.
```

If a function returns by value, the returned object is a temporary rvalue:

```cpp
#include <string>

std::string getName() { return "Alice"; }

int main() {
    std::string name = getName(); 
    // 'name' is an lvalue. 'getName()' evaluates to a temporary rvalue.
    return 0;
}
```

## Rvalue references (`T&&`)

Historically, C++ only had **lvalue references** (written as `T&`), which bind only to lvalues (with the exception of `const T&`, which can bind to temporaries). 

C++11 introduced the **rvalue reference**, written as `T&&`. An rvalue reference is designed specifically to bind *only* to rvalues (temporaries).

![Value categories and reference binding: lvalues bind to `T&` and `const T&`; rvalues bind to `const T&` and `T&&`.](assets/s35_lvalue_rvalue.png)

```cpp
int x = 10;
int& lref = x;        // OK: lvalue reference binds to lvalue
// int& lref2 = 20;   // ERROR: lvalue reference cannot bind to rvalue

int&& rref = 20;      // OK: rvalue reference binds to rvalue
// int&& rref2 = x;   // ERROR: rvalue reference cannot bind to lvalue
```

Because an rvalue reference binds to a temporary that is about to be destroyed, it gives you a powerful guarantee: *you are the only one who has access to this object*. You can safely modify it or strip it of its resources without affecting the rest of the program.

## The problem: wasteful copies of temporaries

Consider a class that owns a large heap-allocated buffer. Without move semantics, initialising a new object from a temporary object forces a deep copy.

```cpp
#include <cstddef>

class IntArray {
private:
    size_t size;
    int* data;
public:
    // Constructor allocates a large buffer
    IntArray(size_t s) : size(s), data(new int[s]) {}
    
    // Copy constructor performs a deep, expensive copy
    IntArray(const IntArray& other) : size(other.size), data(new int[other.size]) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    
    ~IntArray() { delete[] data; }
};

IntArray createArray() {
    IntArray temp(1000000);
    return temp; // Returns by value
}

int main() {
    IntArray arr = createArray(); // Triggers an expensive deep copy (prior to C++11)
    return 0;
}
```

When `createArray()` returns, it produces a temporary `IntArray` (an rvalue). The copy constructor allocates a new million-element array and copies every integer. Immediately afterwards, the temporary object is destroyed, and its million-element array is deleted. This is incredibly wasteful.

## Move semantics: stealing the guts

Imagine someone is handing you a heavy box of books, and they are about to throw their identical box into an incinerator. Instead of laboriously photocopying every page into your own empty box, you simply take their box from them and hand them your empty one. You have "moved" the contents without doing the heavy lifting.

![Copy duplicates the owned heap block; move steals the pointer and leaves the source empty.](assets/s35_copy_vs_move.png)

```cpp
class IntArray {
private:
    size_t size;
    int* data;
public:
    // Standard constructor
    IntArray(size_t s) : size(s), data(new int[s]) {}

    // Copy constructor: deep copy (slow)
    IntArray(const IntArray& other) : size(other.size), data(new int[other.size]) {
        for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
    }
    
    // Move constructor: steal the guts (fast)
    IntArray(IntArray&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr; // Null out the source
    }
    
    // Move assignment operator
    IntArray& operator=(IntArray&& other) noexcept {
        if (this != &other) {
            delete[] data;       // 1. Clean up own existing resources
            
            size = other.size;   // 2. Steal the state
            data = other.data;
            
            other.size = 0;      // 3. Null out the source
            other.data = nullptr;
        }
        return *this;
    }

    ~IntArray() { delete[] data; } // Safe to delete nullptr
};
```

The plain-English rule is: to move an object, you steal its pointers and handles, and then immediately null out the source object so its destructor does not clean up the resources you just stole.

Technically, the **move constructor** (`T(T&& other) noexcept`) and **move assignment operator** (`T& operator=(T&& other) noexcept`) take an rvalue reference to a non-const object. Because the parameter binds to a temporary, you are guaranteed safe, exclusive access to its internals. When you null out the pointers, the source object is left in a **valid but unspecified state**. When the temporary's destructor inevitably runs, calling `delete[] nullptr` is a safe no-op.

## `std::move`: an unconditional cast

Sometimes you have an lvalue (a named object), but you *know* you are done using it and want to move from it. 

::: trap
`std::move` does not actually move anything. It is merely an unconditional cast that converts its argument into an rvalue reference, making it eligible to be moved from.
:::

```cpp
#include <utility>
#include <string>

int main() {
    std::string s1 = "Hello, world! This is a long string.";
    // std::string s2 = s1;            // This would trigger the copy constructor
    std::string s2 = std::move(s1);    // This triggers the move constructor
    
    // s1 is now in a valid but unspecified state (typically empty).
    // DO NOT use s1 after this point, other than to assign to it or destroy it.
    return 0;
}
```

By calling `std::move(s1)`, we tell the compiler, "Treat `s1` as an rvalue." This forces the initialisation to use `std::string`'s move constructor instead of its copy constructor.

## The Rule of 0, 3, and 5

Managing resources manually dictates how you must define your special member functions.

- **The Rule of 3**: If your class defines *any* of a destructor, copy constructor, or copy assignment operator, it likely manages a raw resource manually, and you generally must define all three.
- **The Rule of 5**: In modern C++, if you define the Rule of 3, you should also define the move constructor and move assignment operator to ensure performance.
- **The Rule of 0**: Prefer to design your classes so they manage no raw resources directly (use `std::string`, `std::vector`, `std::unique_ptr` instead). The compiler will automatically generate all five special member functions correctly, allowing you to write none of them.

## Implicit move generation and suppression

The compiler will automatically generate the move constructor and move assignment operator for you, *unless* you suppress them.

::: keypoint
If you declare a custom destructor, copy constructor, or copy assignment operator, the compiler **suppresses** the automatic generation of move operations. The class will fall back to copying.
:::

```cpp
class Widget {
public:
    ~Widget() {} // Custom destructor suppresses implicit move operations!
    // If you return a Widget by value now, it will be copied, not moved.
};
```

If you want the default move operations alongside a custom destructor, explicitly request them:

```cpp
class Widget {
public:
    ~Widget() {}
    Widget(const Widget&) = default;
    Widget& operator=(const Widget&) = default;
    Widget(Widget&&) = default;
    Widget& operator=(Widget&&) = default;
};
```

## Perfect forwarding and `std::forward`

When writing generic templates, you often want to pass an argument through to another function exactly as it was received, preserving whether it was an lvalue or an rvalue. 

In a template context where the type is deduced, `T&&` is not strictly an rvalue reference; it is a **forwarding reference** (or universal reference). It can bind to both lvalues and rvalues, relying on **reference collapsing rules**.

If a template takes `T&&` and you pass an lvalue of type `int`, `T` deduces to `int&`. The signature conceptually becomes `int& &&`. C++ collapses these references:

- `& &` collapses to `&`
- `& &&` collapses to `&`
- `&& &` collapses to `&`
- `&& &&` collapses to `&&`

Thus, an lvalue yields an lvalue reference, and an rvalue yields an rvalue reference.

```cpp
#include <utility>
#include <iostream>

void process(int& x)  { std::cout << "lvalue\n"; }
void process(int&& x) { std::cout << "rvalue\n"; }

template <typename T>
void wrapper(T&& arg) {
    // std::forward restores the original value category of arg
    process(std::forward<T>(arg)); 
}

int main() {
    int a = 5;
    wrapper(a);       // Outputs: lvalue (a is an lvalue)
    wrapper(10);      // Outputs: rvalue (10 is an rvalue)
    return 0;
}
```

Unlike `std::move` (which unconditionally casts to an rvalue), **`std::forward<T>`** is a conditional cast. It casts the argument to an rvalue *only* if the original argument was passed to the template as an rvalue. This preserves the exact value category through multiple layers of function calls.

## Copy elision and return value optimisation (RVO)

Before C++11, returning a large object by value was slow. Move semantics made it fast. However, C++ has an even better mechanism: **Copy Elision**.

```cpp
#include <string>

std::string makeString() {
    std::string local = "Very long string...";
    return local; 
}
```

Under **return value optimisation (RVO)**, the compiler constructs the `local` object directly in the memory location of the caller's variable. No copy is made. No move is made. Both are entirely elided.

::: trap
Do not write `return std::move(local);`. This actually *prevents* the compiler from performing RVO, forcing it to use the move constructor. Just write `return local;`.
:::

::: keypoint
In Python, variables are simply references to objects on the heap. Assigning a variable or passing it to a function just copies the reference. Therefore, there is no copy/move distinction to manage at the language level.
:::

::: interview
**What does `std::move` actually do?** It does not move anything; it is simply an unconditional cast to an rvalue reference (`T&&`), making the object eligible to be moved from.

**Why must a move constructor be `noexcept`?** Standard library containers like `std::vector` offer the strong exception guarantee. If a vector reallocates its buffer, it will only use your move constructor if it is marked `noexcept`. If it might throw, the vector safely falls back to copying the elements.

**What is the Rule of 5?** If a class defines a destructor, copy constructor, or copy assignment operator, it manages a resource and must define all five (adding the move constructor and move assignment operator) to be both safe and efficient.
:::
