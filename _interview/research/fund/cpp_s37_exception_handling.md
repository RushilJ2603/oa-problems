# Exception Handling

Errors occur in all non-trivial programs. C++ provides a structured mechanism for error handling: exceptions. **Exception handling** allows a program to signal that an anomalous situation has occurred and transfer control directly to a designated error-handling block, completely separating the normal flow from error management.

## The `try`, `throw`, and `catch` syntax

The core of exception handling involves three keywords:
1. **`throw`**: Signals that an error has occurred.
2. **`try`**: Encloses a block of code where exceptions might be thrown.
3. **`catch`**: Defines a block of code to handle a specific type of exception.

```cpp
#include <iostream>

double divide(int numerator, int denominator) {
    if (denominator == 0) {
        throw "Division by zero!"; // Throws a const char*
    }
    return static_cast<double>(numerator) / denominator;
}

int main() {
    try {
        std::cout << divide(10, 2) << "\n"; // Outputs: 5
        std::cout << divide(10, 0) << "\n"; // Throws an exception
        std::cout << "This line will not execute.\n";
    } 
    catch (const char* errorMsg) {
        std::cerr << "Error: " << errorMsg << "\n";
    }
    return 0;
}
```

When a `throw` statement executes, the normal flow of the program immediately halts. The program searches up the call stack for the nearest enclosing `try` block that has a matching `catch` handler.

## Catching by reference and the object idiom

In C++, you can `throw` an expression of *any* type — an `int`, a `const char*`, or a custom object. However, the standard idiom is to throw **exception objects** and catch them by **`const` reference**. 

Catching by value, much like passing by value in function calls, invokes the copy constructor and triggers **object slicing** if a derived exception is caught by a base class handler. Catching by `const` reference (`const std::exception& e`) avoids the copy overhead and preserves the dynamic type of polymorphic exceptions.

```cpp
#include <stdexcept>
#include <iostream>

void process() {
    throw std::runtime_error("File not found");
}

int main() {
    try {
        process();
    }
    catch (const std::runtime_error& e) { // Best practice: catch by const reference
        std::cerr << "Caught: " << e.what() << "\n";
    }
    return 0;
}
```

## The standard exception hierarchy

The `<stdexcept>` header defines a comprehensive class hierarchy for exceptions, all inheriting from `std::exception`. The base class provides a virtual `what()` member function that returns a `const char*` describing the error.

The two main branches derived from `std::exception` are:
1. **`std::logic_error`**: Errors that are theoretically preventable by the programmer (e.g., passing invalid arguments). Children include `std::invalid_argument`, `std::out_of_range`, and `std::length_error`.
2. **`std::runtime_error`**: Errors that cannot be easily predicted or prevented before the program runs (e.g., hardware failures or missing files). Children include `std::overflow_error` and `std::underflow_error`.

Other notable standard exceptions include `std::bad_alloc` (thrown by `new` when memory allocation fails) and `std::bad_cast` (thrown by a failed `dynamic_cast` on references).

## Multiple `catch` blocks and ordering

A single `try` block can be followed by multiple `catch` handlers to process different types of exceptions.

::: trap
Catch blocks are evaluated strictly in the order they appear. You must always place the most-derived exception handlers first and the base class handlers last. If a base class is caught first, it will intercept all derived exceptions, rendering subsequent blocks unreachable.
:::

```cpp
#include <stdexcept>
#include <iostream>

int main() {
    try {
        // Code that might throw various exceptions
    }
    catch (const std::out_of_range& e) {
        // Most-derived class first
        std::cerr << "Out of range: " << e.what() << "\n";
    }
    catch (const std::logic_error& e) {
        // Base class of out_of_range, goes second
        std::cerr << "Logic error: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        // Base class of all standard exceptions, goes last
        std::cerr << "Standard exception: " << e.what() << "\n";
    }
    return 0;
}
```

## The catch-all block and rethrowing

Sometimes, you need to intercept an exception without knowing its type, perhaps to perform local cleanup or logging, before passing the error up the chain. The **catch-all handler**, written as `catch (...)`, catches any exception regardless of its type.

To propagate an exception from within a catch block to a higher-level handler, you use a bare `throw;` statement. This is called **rethrowing**.

```cpp
try {
    // Risky operation
} 
catch (...) { // Catch absolutely anything
    std::cerr << "An unknown error occurred. Logging and aborting...\n";
    throw; // Rethrows the EXACT same exception object
}
```

Using `throw;` preserves the original exception's type and state. Do not use `throw e;` if you caught `e`, as that would slice the object and throw a new copy based on the static type of `e`.

::: keypoint
In Python, you use `try` / `except` / `finally`, where the `finally` block runs cleanup code regardless of success or failure, and `raise` to throw or rethrow. C++ has no `finally` keyword; instead, it relies entirely on RAII (Resource Acquisition Is Initialisation) to guarantee cleanup.
:::

::: heavy
The following section deals with the internal mechanics of how exceptions travel through the call stack and how objects are destroyed along the way.
:::

## Stack unwinding and RAII

When an exception is thrown, the program searches for a matching `catch` block by climbing back up the call stack. This process of popping function frames off the stack to find a handler is called **stack unwinding**.

Imagine a fire alarm going off in an office building. The occupants do not just vanish instantly; they follow the evacuation route, closing doors and shutting off machinery as they leave. 

![Stack unwinding: a thrown exception destroys each frame’s locals on its way up to the matching `catch`.](assets/s37_stack_unwinding.png)

```cpp
#include <iostream>
#include <string>
#include <stdexcept>

class FileHandler {
public:
    FileHandler(const std::string& name) { std::cout << "Opening " << name << "\n"; }
    ~FileHandler() { std::cout << "Closing file\n"; }
};

void readFile() {
    FileHandler file("data.txt"); // Constructor runs
    throw std::runtime_error("Disk read error"); 
    // Destructor runs automatically during unwinding before the exception escapes
}

int main() {
    try {
        readFile();
    } catch (const std::exception& e) {
        std::cerr << "Caught: " << e.what() << "\n";
    }
    return 0;
}
```

The plain-English rule is: as an exception propagates up the stack, C++ guarantees that the destructors of all fully-constructed automatic (local) objects in the abandoned scopes will be executed in reverse order of creation.

Technically, this is exactly why the RAII idiom (tying resource management to object lifetime) makes C++ code exceptionally robust. Since stack unwinding calls destructors automatically, any dynamically allocated memory, file handles, or mutex locks encapsulated within RAII objects (like `std::unique_ptr` or `std::lock_guard`) are safely released, preventing resource leaks even when errors occur.

## Throwing from constructors

Constructors are the correct place to throw exceptions if an object cannot be initialised into a valid state. Because constructors do not have a return type, throwing an exception is the only way to signal failure.

When an exception is thrown from a constructor, the object is considered "never fully built." Consequently, the destructor for that specific object **will not be called**. However, any members or base classes that were fully constructed *before* the exception was thrown will have their destructors executed. This is another reason to prefer RAII members: raw pointers allocated in a constructor will leak if the constructor later throws, but smart pointers will clean themselves up automatically.

## Throwing from destructors

::: trap
Never let an exception escape from a destructor. Doing so during stack unwinding will immediately terminate the program.
:::

If an exception is thrown and stack unwinding begins, the program is actively executing destructors. If one of those destructors throws a *new* exception while the first exception is still looking for a handler, C++ finds itself in an unresolvable situation with two simultaneous active exceptions. By rule, the runtime immediately calls `std::terminate()`, crashing the program. Any operations in a destructor that might throw must be wrapped in a local `try` / `catch` block that swallows the error.

## The `noexcept` specifier and operator

C++11 introduced the `noexcept` specifier to declare that a function is guaranteed not to throw an exception. This allows the compiler to heavily optimise the function, as it does not need to generate stack-unwinding scaffolding.

```cpp
void safeFunction() noexcept {
    // This function guarantees it will never throw
}
```

If a function marked `noexcept` violates its promise and attempts to throw an exception out of its scope, the program immediately calls `std::terminate()`. By default, destructors are implicitly `noexcept`.

The `noexcept(...)` **operator** is a compile-time check that returns `true` if the expression inside it is guaranteed not to throw. This is useful in template metaprogramming to conditionally apply the `noexcept` specifier based on template parameters.

```cpp
// The noexcept operator evaluates at compile time
constexpr bool isSafe = noexcept(safeFunction()); // Evaluates to true
```

## Exception-safety guarantees

When designing robust C++ libraries, functions are classified by the level of **exception safety** they provide if an exception is thrown during their execution:

1. **Nothrow (or No-fail) guarantee**: The function promises to never throw an exception. This is required for destructors and swap functions.
2. **Strong guarantee**: The "commit or rollback" semantics. If the function fails and throws, the state of the program is completely unchanged, exactly as if the function was never called.
3. **Basic guarantee**: If the function throws, no resources are leaked, and the program remains in a valid (but possibly unpredictable) state. All class invariants are preserved.
4. **No guarantee**: If an exception occurs, the program may leak memory or be left in a corrupted state. This is unacceptable in modern C++.

## Writing a custom exception class

You can create custom exception types to provide specific, domain-relevant error information. The standard practice is to inherit from `std::runtime_error` (or another appropriate standard exception) and override the constructor to accept your custom message.

```cpp
#include <stdexcept>
#include <string>

class NetworkError : public std::runtime_error {
private:
    int errorCode;
public:
    // Pass the message to the base class constructor
    NetworkError(const std::string& msg, int code) 
        : std::runtime_error(msg), errorCode(code) {}

    int getErrorCode() const { return errorCode; }
};

// Usage
void connect() {
    throw NetworkError("Connection timed out", 404);
}
```

::: interview
Be prepared to explain the exception-safety guarantees (Nothrow, Strong, Basic) and the mechanism of stack unwinding. A classic trap question asks why we catch by `const` reference (to avoid object slicing and copying) and what happens if a destructor throws (it risks `std::terminate()`). Knowing when and why to use `noexcept` is also a frequent topic.
:::
