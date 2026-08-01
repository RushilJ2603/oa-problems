# The Preprocessor

Before the compiler even begins translating code into machine instructions, the source file is processed by the **preprocessor**. The preprocessor does not understand C++ syntax; it performs pure text substitution, manipulating the text of your source file before compilation begins.

## File inclusion: `#include`

The `#include` directive instructs the preprocessor to literally copy and paste the entire contents of another file into the current file at the exact point of the directive.

There are two syntaxes for inclusion, dictating where the preprocessor searches for the file:

```cpp
#include <iostream>  // Angle brackets: search the system's standard include paths
#include "my_math.h" // Quotes: search the local directory first, then system paths
```

## Macros: `#define` and `#undef`

The `#define` directive creates a **macro**, which tells the preprocessor to replace all subsequent occurrences of a specific identifier with a designated replacement text. The `#undef` directive removes a macro definition.

### Object-like macros

Object-like macros are typically used to define simple text replacements, such as constants.

```cpp
#define PI 3.14159
#define MAX_USERS 100

double area = PI * radius * radius; // Preprocessor replaces PI with 3.14159
#undef PI                           // PI is no longer defined after this line
```

### Function-like macros

Macros can also take arguments. The preprocessor substitutes the arguments into the replacement text without evaluating them first.

```cpp
#define SQ(x) ((x) * (x))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minimum = MIN(10, 20); // Replaced with: ((10) < (20) ? (10) : (20))
```

### Macro pitfalls

Because macros are dumb text substitution, they introduce severe bugs if not written carefully.

1. **Mandatory parentheses**: You must wrap every parameter and the entire macro body in parentheses to prevent operator precedence errors when complex expressions are passed.
2. **Argument re-evaluation**: If an argument contains side effects (like `i++`), it will be evaluated multiple times, which can lead to undefined behaviour.
3. **No type safety**: Macros do not respect types, leading to obscure compile errors or unexpected logic when given incompatible data.

```cpp
#define BAD_SQ(x) x * x
#define SQ(x) ((x) * (x))

int i = 5;
// TRAP: Precedence error. 5 + 1 * 5 + 1 evaluates to 5 + 5 + 1 = 11, not 36!
int result1 = BAD_SQ(i + 1); 

// TRAP: Double evaluation. i gets incremented twice!
// SQ(i++) expands to ((i++) * (i++)), causing undefined behaviour.
int result2 = SQ(i++); 
```

::: trap
A function-like macro without parentheses around its parameters and body will cause catastrophic operator precedence bugs. Passing arguments with side effects (like `i++`) to a macro causes double-evaluation bugs.
:::

## Conditional compilation

Conditional compilation directives allow you to include or exclude blocks of code based on whether macros are defined or what values they hold.

```cpp
#define DEBUG_MODE 1

#ifdef DEBUG_MODE
    // Included if DEBUG_MODE is defined
    std::cout << "Debug mode is ON\n";
#endif

#ifndef RELEASE_MODE
    // Included if RELEASE_MODE is NOT defined
    std::cout << "Release mode is OFF\n";
#endif

#if DEBUG_MODE == 1
    // Included if DEBUG_MODE evaluates to 1
#elif defined(BETA_MODE)
    // Included if BETA_MODE is defined (equivalent to #ifdef BETA_MODE)
#else
    // Included if none of the above are true
#endif
```

## Include guards versus `#pragma once`

Because headers often include other headers, a single header file might end up being included multiple times in the same source file. This causes compile errors due to multiple definitions of the same class or struct. We prevent this using **include guards** or `#pragma once`.

An include guard uses conditional compilation to ensure the file's contents are processed only once.

```cpp
// header.h
#ifndef HEADER_H     // If HEADER_H is not defined yet...
#define HEADER_H     // ...define it now.

class MyClass {
    // Class definition
};

#endif // HEADER_H
```

Alternatively, most modern compilers support `#pragma once`, which achieves the same result with a single line at the top of the file:

```cpp
// header.h
#pragma once

class MyClass {
    // Class definition
};
```

::: interview
"What do include guards prevent?" They prevent the One Definition Rule (ODR) from being violated by stopping a header file's contents (such as class definitions) from being pasted multiple times into the same compilation unit.
:::

## Predefined macros

The compiler automatically defines several object-like macros that provide information about the current compilation state.

```cpp
#include <iostream>

void printLog() {
    std::cout << "File: " << __FILE__ << "\n";
    std::cout << "Line: " << __LINE__ << "\n";
    std::cout << "Date: " << __DATE__ << "\n";
    std::cout << "Time: " << __TIME__ << "\n";
    std::cout << "Func: " << __func__ << "\n"; 
}
```

::: keypoint
`__func__` is actually a compiler-provided implicitly defined local variable (a static array of `char`), not a preprocessor macro, although it is often grouped with them conceptually.
:::

## The stringise (`#`) and token-paste (`##`) operators

The preprocessor provides two special operators for use within function-like macros:
- The **stringise** operator (`#`) converts a macro argument into a string literal.
- The **token-paste** operator (`##`) concatenates two tokens into a single token.

```cpp
#include <iostream>

// Stringise operator: turns 'var' into "var"
#define PRINT_VAR_NAME(var) std::cout << #var << " = " << var << "\n"

// Token-paste operator: combines 'name' and 'num' into 'name##num'
#define MAKE_VAR(name, num) int name##num = num

int main() {
    int x = 42;
    PRINT_VAR_NAME(x); // Replaced with: std::cout << "x" << " = " << x << "\n"

    MAKE_VAR(value, 10); // Replaced with: int value10 = 10;
    
    return 0;
}
```

## Why modern C++ prefers the language over the preprocessor

The preprocessor operates completely outside the type system and does not respect C++ namespaces or scope. For this reason, modern C++ heavily discourages using macros for everything except `#include` and conditional compilation. 

Instead, modern C++ provides safer, type-checked language features:

- **`const` and `constexpr` variables** instead of `#define` constants. These respect scoping and provide strict type safety.
- **`inline` functions and templates** instead of function-like macros. These evaluate arguments exactly once, enforce type checking, and can be easily debugged.
- **`enum` and `enum class`** instead of `#define` flags for grouping related named integer constants.

```cpp
// Legacy preprocessor approach
#define MAX_BUFFER 1024
#define CUBE(x) ((x) * (x) * (x))

// Modern C++ approach
constexpr int max_buffer = 1024;

template <typename T>
inline T cube(const T& x) {
    return x * x * x;
}
```

::: interview
"Why should you prefer `constexpr` or `inline` over macros?" Macros lack type safety, do not respect scope or namespaces, and are difficult to debug because the debugger sees the substituted text, not the macro name. Furthermore, function-like macros are prone to double-evaluation bugs.
:::
