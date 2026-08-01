# Templates

::: heavy
Dense section — slow down. This introduces compile-time code generation, the engine behind the C++ Standard Template Library.
:::

## Compile-time code generation

Imagine a cookie cutter. The cutter itself is not a cookie; it is a shape used to stamp out cookies from different types of dough (chocolate, ginger, vanilla). A **template** in C++ is a stencil. It is not runnable code on its own.

![One template is stamped into a separate concrete function for each type it is instantiated with.](assets/s38_template_instantiation.png)

```cpp
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    maximum(10, 20);       // Stamps out maximum(int, int)
    maximum(5.5, 3.2);     // Stamps out maximum(double, double)
    return 0;
}
```

The plain-English rule is: when you call a template, the compiler looks at the types you provided and automatically generates a brand-new, ordinary function for those specific types at compile time.

Technically, a template is a blueprint for generating classes or functions. When the compiler encounters an instantiation of a template, it substitutes the template arguments into the template parameters and compiles the resulting concrete code. If you instantiate a template with `int` and `double`, the compiler generates two completely separate functions in the final binary.

::: keypoint
In Python, variables are duck-typed and evaluated at runtime, so a single function can accept any object that supports the `>` operator without needing templates. C++ requires strict static typing, so it uses templates to generate distinct typed functions at compile time.
:::

## Function templates

Function templates allow you to write generic functions that work with any data type.

### `typename` versus `class`

You declare a template using the `template` keyword followed by a template parameter list in angle brackets. You can use either `typename` or `class`. They mean exactly the same thing in this context.

```cpp
// These two declarations are entirely equivalent
template <typename T> void print(T value);
template <class T>    void print(T value);
```

Conventionally, `typename` is preferred for generic types, but you will frequently see `class` in older codebases.

### Template argument deduction and explicit arguments

When you call a function template, the compiler usually deduces the template type `T` from the arguments you pass.

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    int x = add(5, 10);       // Deduces T as int
    // double y = add(5.5, 10); // ERROR: T deduced as double and int, conflict!
    
    // Explicitly specifying the type resolves conflicts
    double z = add<double>(5.5, 10); // T is forced to double, 10 is implicitly converted
    return 0;
}
```

### Overloading function templates

Function templates can be overloaded with ordinary, non-template functions. When resolving a call, the compiler prefers an ordinary function if it is a perfect match. If no ordinary function matches, it falls back to generating a function from the template.

```cpp
#include <iostream>

void display(int x) {
    std::cout << "Ordinary function: " << x << "\n";
}

template <typename T>
void display(T x) {
    std::cout << "Template function: " << x << "\n";
}

int main() {
    display(42);       // Calls ordinary function (perfect match)
    display(3.14);     // Stamps out and calls template function for double
    display<>(42);     // Forces the compiler to use the template
    return 0;
}
```

### The `typename` keyword for dependent types

While `typename` and `class` are interchangeable in the parameter list, `typename` is **required** when you want to refer to a nested type (like an `iterator`) inside a type that depends on a template parameter. 

```cpp
#include <vector>
#include <iostream>

template <typename Container>
void printFirst(const Container& c) {
    // Container::const_iterator depends on the template parameter 'Container'.
    // We MUST use 'typename' to tell the compiler this is a type, not a static variable.
    typename Container::const_iterator it = c.begin();
    if (it != c.end()) {
        std::cout << *it << "\n";
    }
}
```

## Class templates

You can also use templates to create generic classes, which is how standard containers like `std::vector` are implemented.

```cpp
template <typename T>
class Box {
private:
    T content;
public:
    Box(T val) : content(val) {}
    T getContent() const;
};
```

### Defining member functions outside the class

If you define a class template's member function outside the class body, you must prefix it with the `template` declaration and use the full type name (`Box<T>`) to specify the scope.

```cpp
template <typename T>
T Box<T>::getContent() const {
    return content;
}

int main() {
    Box<int> intBox(100);             // Instantiates Box for int
    Box<std::string> strBox("Hello"); // Instantiates Box for std::string
    return 0;
}
```

## Non-type template parameters

Template parameters do not have to be types. They can also be constant values known at compile time, such as integers.

```cpp
#include <cstddef>

template <typename T, std::size_t N>
class FixedArray {
private:
    T data[N]; // N is a compile-time constant
public:
    std::size_t size() const { return N; }
};

int main() {
    FixedArray<int, 5> arr1;      // Generates an array class of 5 ints
    FixedArray<double, 10> arr2;  // Generates an array class of 10 doubles
    return 0;
}
```

## Default template arguments

Just like function arguments, template parameters can have default values.

```cpp
#include <cstddef>

template <typename T = int, std::size_t N = 10>
class Buffer {
    T data[N];
};

int main() {
    Buffer<> defaultBuf;         // Equivalent to Buffer<int, 10>
    Buffer<double> doubleBuf;    // Equivalent to Buffer<double, 10>
    Buffer<char, 256> charBuf;   // Overrides both defaults
    return 0;
}
```

## Template specialisation

Sometimes a generic template does not work (or is sub-optimal) for a specific data type. You can override the compiler's stencil for specific types using **specialisation**.

### Full (explicit) specialisation

Full specialisation provides a completely custom implementation for a specific type. You leave the template parameter list empty `template <>` and specify the target type after the template name.

```cpp
#include <iostream>

// Primary template
template <typename T>
class Printer {
public:
    void print(const T& val) { std::cout << val << "\n"; }
};

// Full specialisation for bool
template <>
class Printer<bool> {
public:
    void print(const bool& val) {
        std::cout << (val ? "true" : "false") << "\n";
    }
};

int main() {
    Printer<int> p1;
    p1.print(1);    // Uses primary template, outputs: 1
    
    Printer<bool> p2;
    p2.print(true); // Uses specialised template, outputs: true
    return 0;
}
```

### Partial specialisation

Partial specialisation allows you to specialise a template while still leaving some parameters generic (for example, specialising for all pointer types `T*`). 

::: keypoint
Partial specialisation is only allowed for **class templates**, not function templates (which rely on function overloading instead).
:::

```cpp
#include <iostream>

// Primary template
template <typename T>
class PointerPrinter {
public:
    void print(T val) { std::cout << "Value: " << val << "\n"; }
};

// Partial specialisation for ANY pointer type T*
template <typename T>
class PointerPrinter<T*> {
public:
    void print(T* ptr) {
        if (ptr) std::cout << "Pointer to: " << *ptr << "\n";
        else std::cout << "Null pointer\n";
    }
};

int main() {
    int x = 42;
    PointerPrinter<int> valPrinter;
    valPrinter.print(x);     // Outputs: Value: 42
    
    PointerPrinter<int*> ptrPrinter;
    ptrPrinter.print(&x);    // Outputs: Pointer to: 42
    return 0;
}
```

## Variadic templates

Introduced in C++11, **variadic templates** can accept an arbitrary number of template arguments using a **parameter pack** (indicated by an ellipsis `...`).

### Recursive expansion

Historically, parameter packs were unpacked using recursive function calls. You provide a base case, and a recursive template that peels off one argument at a time.

```cpp
#include <iostream>

// Base case: called when the parameter pack is empty
void printAll() {
    std::cout << "\n";
}

// Recursive case: peels off 'first', leaving the rest in 'args'
template <typename T, typename... Args>
void printAll(T first, Args... args) {
    std::cout << first << " ";
    
    // Determine number of remaining arguments at compile time
    std::size_t remaining = sizeof...(args); 
    
    printAll(args...); // Recursively unpacks the remaining arguments
}

int main() {
    printAll(1, 2.5, "Hello"); // Outputs: 1 2.5 Hello 
    return 0;
}
```

### Fold expressions (C++17)

C++17 introduced **fold expressions**, which elegantly reduce a parameter pack over a binary operator, eliminating the need for boilerplate recursive functions.

```cpp
template <typename... Args>
auto sumAll(Args... args) {
    // Fold expression: expands to (arg1 + (arg2 + (arg3 + ...)))
    return (... + args);
}

int main() {
    int total = sumAll(1, 2, 3, 4, 5); // total is 15
    return 0;
}
```

## Template definitions and headers

::: trap
Template code is not fully checked by the compiler until it is actually instantiated. Furthermore, placing template definitions in a `.cpp` file while declaring them in a header will result in linker errors.
:::

Because templates are stencils, the compiler needs to see the *entire definition* of the template at the exact moment you instantiate it (the separate-compilation model). If the definition is hidden in a separately compiled `.cpp` file, the compiler cannot stamp out the type-specific code when compiling your `main.cpp`, and the linker will eventually fail to find the instantiated symbols.

For this reason, template declarations and definitions must be placed together in header files (`.h` or `.hpp`).

## SFINAE and Concepts

When substituting types into templates, if the substitution results in invalid code, the compiler silently discards that template rather than throwing a hard error — a principle known as **SFINAE** (Substitution Failure Is Not An Error).

While SFINAE was historically used to loosely constrain templates (e.g. "only instantiate this template if T is an integer"), C++20 introduced **Concepts**, providing a modern, readable, and robust language feature for directly specifying template constraints.

::: interview
Templates are a central C++ topic. Be prepared to explain that they are compile-time code generators, not runtime constructs. Ensure you can articulate the difference between full and partial specialisation, and clearly explain why template definitions must be placed in headers rather than `.cpp` files.
:::
