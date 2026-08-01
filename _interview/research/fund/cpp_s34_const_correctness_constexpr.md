# Const Correctness and constexpr

The `const` keyword is a fundamental tool in C++ for enforcing immutability. By marking variables, parameters, and member functions as `const`, you create a contract that the compiler enforces, preventing accidental modifications and enabling optimisations.

## The `const` qualifier and the right-to-left reading rule

At its simplest, `const` applies to a variable to make it immutable. A `const` variable must be initialised when it is declared because it can never be assigned to later.

```cpp
const int maxUsers = 100; // Must be initialised
// maxUsers = 150;        // ERROR: assignment of read-only variable
```

When combining `const` with pointers, the syntax can become confusing. The most reliable way to understand complex declarations is the **right-to-left reading rule**: read the declaration from the variable name backwards to the type.

![Reading a `const` pointer declaration right-to-left, so each `const` and `*` binds to the token on its right.](assets/s34_const_read_rtl.png)

### Pointer flavours

There are three distinct ways `const` interacts with pointers, each forbidding different kinds of mutation:

1. **Pointer-to-const** (`const int*` or `int const*`): The pointer can change to point elsewhere, but the value it points to cannot be modified through this pointer.

```cpp
int x = 10;
int y = 20;

// Read right-to-left: p1 is a pointer to an int that is const
const int* p1 = &x; 
// int const* p1 = &x; // Exactly equivalent

p1 = &y;     // OK: the pointer itself can change
// *p1 = 30; // ERROR: the integer pointed to is read-only
```

::: trap
A common mistake is assuming `const int*` and `int* const` are identical. They are fundamentally different. `const int*` protects the data; `int* const` protects the pointer address.
:::

2. **Const-pointer** (`int* const`): The pointer's address is fixed and must be initialised, but the value it points to can be modified.

```cpp
int x = 10;
int y = 20;

// Read right-to-left: p2 is a const pointer to an int
int* const p2 = &x;

*p2 = 30;    // OK: the integer pointed to can change
// p2 = &y;  // ERROR: the pointer itself is read-only
```

3. **Const-pointer-to-const** (`const int* const`): Neither the pointer address nor the value it points to can be modified.

```cpp
int x = 10;

// Read right-to-left: p3 is a const pointer to an int that is const
const int* const p3 = &x;

// *p3 = 30; // ERROR: cannot modify the value
// p3 = &y;  // ERROR: cannot modify the pointer
```

## Const references

A **const reference** (`const T&`) allows you to alias a variable without copying it, whilst guaranteeing you will not modify it. This is the standard, efficient idiom for passing large objects (like strings or custom classes) to functions — it provides the performance of pass-by-reference with the safety of pass-by-value.

```cpp
#include <iostream>
#include <string>

// Cheap to pass (no copy), safe to use (cannot modify)
void printMessage(const std::string& msg) {
    std::cout << msg << "\n";
    // msg += "!"; // ERROR: cannot modify a const reference
}
```

::: keypoint
In Python, there is no language-level `const` keyword. Immutability is either a property of the type (like `tuple` or `str`), or enforced by convention (like naming constants in `ALL_CAPS` or using type hints like `Final`).
:::

## Const member functions and `mutable`

As recapped from an earlier section, a **const member function** is one that promises not to modify any member variables of the class. It is denoted by placing `const` at the end of the function signature. You can only call const member functions on `const` objects.

```cpp
class Account {
private:
    int balance = 0;
    mutable int accessCount = 0;

public:
    // The 'const' at the end promises this function won't change the object
    int getBalance() const {
        accessCount++; // OK: 'mutable' allows modification even in const functions
        return balance;
    }
};
```

The **`mutable`** keyword is an escape hatch. It allows a specific member variable to be modified even within a const member function, typically used for internal bookkeeping (like caching or thread mutexes) that does not alter the logical, externally-visible state of the object.

::: interview
"What does `const` after a member function mean?" It means the function does not modify the object's observable state, and the compiler enforces this. The hidden `this` pointer inside the function becomes `const ClassName* const`.
:::

## Const parameters and return values

Beyond references, function parameters passed by value can also be marked `const`. This simply prevents the function from modifying its own local copy, which is a useful implementation detail but does not affect the caller.

```cpp
void process(const int value) {
    // value = 5; // ERROR: local copy is immutable
}
```

Returning a `const` value (e.g., `const int getValue()`) is generally obsolete in modern C++ and inhibits move semantics. However, returning a **const reference** (`const T&`) is extremely common for exposing internal class data cheaply without allowing the caller to modify it.

```cpp
#include <string>

class Config {
private:
    std::string name = "App";
public:
    const std::string& getName() const {
        return name; // Avoids copying a large string
    }
};
```

*(Note: In the Standard Template Library, container iteration provides `const_iterator` to traverse elements read-only — this detail is deferred to the STL sections.)*

## Const-correctness as a discipline

**Const-correctness** is the discipline of marking everything `const` that should not change. This practice must propagate outward: if you have a `const` object, you can only pass it to functions taking `const` parameters or call its `const` member functions.

Const-correctness serves two primary purposes:
1. **API Contracts**: It clearly communicates intent. A function taking `const Widget&` signals to the caller "I will only read your widget."
2. **Compiler Optimisation**: When the compiler is certain a value will not change, it can aggressively optimise register usage and memory accesses.

## Compile-time evaluation: `constexpr`

While `const` means "I promise not to change this at run time," **`constexpr`** means "this value is known at compile time."

### constexpr variables

A `constexpr` variable is a true compile-time constant. It must be initialised with a constant expression.

```cpp
constexpr int maxRetries = 5;            // OK: literal is a constant expression
constexpr int total = maxRetries * 2;    // OK: computed at compile time

// int x;
// std::cin >> x;
// constexpr int limit = x; // ERROR: 'x' is not known at compile time
```

### constexpr functions

A **`constexpr` function** is a function that *can* be evaluated at compile time if all its arguments are constant expressions.

```cpp
constexpr int square(int x) {
    return x * x;
}

int main() {
    constexpr int a = square(5); // Evaluated at compile time
    
    int y = 10;
    int b = square(y);           // Evaluated at run time because 'y' is not constant
    return 0;
}
```

The plain-English rule is: a `constexpr` function runs at compile time when given compile-time inputs, but gracefully falls back to running at run time if given run-time inputs.

### `constexpr` versus `inline` constants

Historically, `inline` was used to prevent multiple definition errors for variables in header files. Since C++17, `constexpr` variables are implicitly `inline`, meaning you can define them directly in header files safely.

```cpp
// In a header file:
constexpr int globalMax = 100; // Implicitly inline, safe to include in multiple translation units
```

### Advanced compile-time features (C++17 and C++20)

Modern C++ has expanded compile-time capabilities significantly:
- **`if constexpr` (C++17)**: A conditional statement where the branch is evaluated and discarded at compile time, primarily used in template metaprogramming.
- **`consteval` (C++20)**: Creates an *immediate function* that **must** be evaluated at compile time (unlike `constexpr` which *can* be).
- **`constinit` (C++20)**: Ensures a variable has static or thread storage duration and is initialised at compile time, avoiding the "static initialisation order fiasco" without making the variable immutable.

```cpp
// Syntax examples:
consteval int mandatoryCompileTime(int x) { return x * 2; }
// int a = 5; int b = mandatoryCompileTime(a); // ERROR: 'a' is not a compile-time constant

constinit int runTimeMutableButCompileTimeInit = 42; 
```

::: interview
"What is the difference between `const` and `constexpr`?" `const` means an object's state cannot be modified after initialisation (runtime immutability), whereas `constexpr` means the value must be fully evaluable during compilation (compile-time constant). All `constexpr` variables are implicitly `const`, but not all `const` variables are `constexpr`.
:::
