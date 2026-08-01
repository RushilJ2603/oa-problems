# 9. The Preprocessor & Macros

The C compiler does not read the raw `.c` file you write. Before the compiler ever sees your code, the text is rewritten by a program called the **preprocessor**. This is a pure text-substitution engine. It knows nothing about C data types, variables, loops, or scope rules. It simply reads text, looks for specific directives starting with `#`, and outputs modified text. The result is a single, self-contained file called a *translation unit* (which means the fully expanded source file ready for compilation), which is then handed to the actual C compiler.

```{=typst}
#keypoint[
```

The preprocessor operates exclusively on text tokens, not on C semantics. A macro error is a text replacement error, not a type error.

```{=typst}
]
```

## 9.1 File Inclusion: `#include`

The `#include` directive instructs the preprocessor to take the entire contents of another file and paste it directly into the current file at the exact line where the directive appears.

There are two forms of `#include`, which differ only in where they search for the file:
- `#include <filename.h>`: The preprocessor searches in system-defined standard directories. Use this for standard library headers like `<stdio.h>` or third-party libraries.
- `#include "filename.h"`: The preprocessor first searches in the same directory as the current source file. If it fails, it falls back to the system directories. Use this for your own project's header files.

![Source to translation unit pipeline](assets/s09_preprocess_flow.png)

### The Header Guard

Because `#include` is a blind text paste, a single source file might end up including the same header multiple times (for example, `a.h` includes `c.h`, and `b.h` also includes `c.h`; then `main.c` includes both `a.h` and `b.h`). If `c.h` defines a `struct`, the compiler will see the `struct` defined twice in the final translation unit, causing a compilation error.

To prevent this, we use a **header guard**. A header guard uses conditional compilation directives to ensure the file's contents are only pasted once per translation unit.

```c
#ifndef MY_HEADER_H
#define MY_HEADER_H

// Declarations go here
struct Point { int x; int y; };
void do_something(void);

#endif
```

When this file is included the first time, `MY_HEADER_H` is not defined. The preprocessor enters the `#ifndef` block, defines `MY_HEADER_H`, and pastes the contents. The second time the file is included, `MY_HEADER_H` is already defined, so the preprocessor skips the entire block until the `#endif`.

An alternative, widely supported extension is `#pragma once` at the very top of the header. It serves the exact same purpose, is less prone to naming collisions, and can compile slightly faster [1].

![Include guard preventing double inclusion](assets/s09_header_guard.png)

```{=typst}
#trap[
```

Placing function or variable *definitions* (the actual code or memory allocation) in a header file will cause linker errors if that header is included by multiple `.c` files. Each `.c` file gets its own copy of the definition, resulting in a "multiple definition" error at link time. Headers must contain only *declarations* (signatures, macros, structs, types).

```{=typst}
]
```

## 9.2 Text Substitution: `#define`

The `#define` directive creates a **macro**, mapping an identifier to a replacement text. When the preprocessor encounters that identifier later in the source code, it blindly substitutes the replacement text.

### Object-like Macros

An object-like macro replaces an identifier with a fixed sequence of tokens. It is typically used for manifest constants.

```c
#define MAX_BUFFER_SIZE 1024
#define PI 3.14159
```

### Function-like Macros

```{=typst}
#heavy[
```

Dense — slow down: Function-like macros look exactly like C functions when invoked, but their purely textual nature makes them extremely fragile and a prime source of hidden bugs.

```{=typst}
]
```

Function-like macros take arguments, similar to a function call. However, they do not pass values; they substitute the exact text of the arguments into the macro body.

**(A) Analogy:** A function call evaluates its arguments and passes the computed *values* in a sealed envelope to the function. A function-like macro is like "find and replace" in a text editor: it takes the exact keystrokes you typed as the argument and pastes them into the formula before any math or logic happens.

**(D) Diagram:** (See Traced Example in Worked Examples for the text expansion visualization).

**(E) Example First:** Let's look at a macro intended to multiply a number by 2.

```c
#define DOUBLE_BAD(x) x * 2

int a = DOUBLE_BAD(3 + 4);
```

You might expect `a` to be `14`. But the preprocessor substitutes the exact text `3 + 4` for `x`. The expanded code becomes:

```c
int a = 3 + 4 * 2;
```

Due to C operator precedence, `4 * 2` is evaluated first, making `a = 11`.

**(P) Plain-English:** Because macros are text substitution, they inherit the operator precedence of whatever expression they are dropped into, and the expressions passed into them can be split apart if they contain lower-precedence operators. To fix this, you must aggressively wrap parentheses around *every* use of a parameter inside the macro, and around the *entire* macro body itself.

**(T) Technical Statement:** A robust function-like macro must enclose all parameter tokens in parentheses to prevent internal operator precedence issues, and enclose the entire replacement list in parentheses to prevent external context precedence issues.

```c
#define DOUBLE_SAFE(x) ((x) * 2)
```

Now, `DOUBLE_SAFE(3 + 4)` expands to `((3 + 4) * 2)`, properly yielding `14`.

This breaks when an argument is evaluated multiple times. Even with perfect parentheses, a macro evaluates the *text* of its arguments as many times as the parameter appears in the replacement list.

```{=typst}
#trap[
```

**Multiple Evaluation (The Double-Eval Trap).** If you pass an expression with side effects (like `a++` or a function call) to a macro that uses its parameter more than once, that side effect will occur multiple times. This is undefined behavior or unintended logic [2].

```{=typst}
]
```

### Statement Macros and `do { ... } while (0)`

Sometimes a macro needs to execute multiple statements.

```c
#define LOG_ERROR(msg) \
    printf("Error: %s\n", msg); \
    exit(1);
```

This looks fine until it is used in an `if` statement without braces:

```c
if (fatal)
    LOG_ERROR("Crash!");
```

This expands to:

```c
if (fatal)
    printf("Error: %s\n", "Crash!");
    exit(1); // ALWAYS EXECUTES!
```

To safely bundle multiple statements into a macro that behaves syntactically like a single C statement (requiring a semicolon at the end, safely embeddable in single-line `if`/`else`), the standard idiom is to wrap the block in a `do { ... } while (0)` loop [3].

```c
#define LOG_ERROR(msg) do { \
    printf("Error: %s\n", msg); \
    exit(1); \
} while (0)
```

The loop condition `0` means it executes exactly once. The `do-while` syntax specifically demands a trailing semicolon, making it a drop-in replacement for a standard statement.

## 9.3 Advanced Token Manipulation

The preprocessor provides two special operators that only exist within macro definitions: stringizing (`#`) and token-pasting (`##`).

### Stringizing (`#`)
The `#` operator converts a macro parameter into a string literal. The preprocessor puts double quotes around the exact text passed to the parameter.

```c
#define PRINT_INT(var) printf(#var " = %d\n", var)

int x = 5;
PRINT_INT(x); // Expands to: printf("x" " = %d\n", x)
```

Adjacent string literals in C are automatically concatenated by the compiler, so this effectively becomes `printf("x = %d\n", x)`.

### Token-pasting (`##`)
The `##` operator takes two separate tokens and glues them together to form a single, valid C token (typically an identifier).

```c
#define DECLARE_STRUCT(name) struct name##_data { int id; }

DECLARE_STRUCT(user); // Expands to: struct user_data { int id; }
```

### Variadic Macros (`__VA_ARGS__`)
Macros can accept a variable number of arguments using `...` in the parameter list. The special identifier `__VA_ARGS__` in the replacement list expands to all the arguments passed in place of the `...`, including the commas separating them [4].

```c
#define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)

DEBUG_PRINT("x is %d and y is %d\n", x, y);
```

## 9.4 Conditional Compilation

The preprocessor can selectively include or exclude blocks of text using conditional directives: `#if`, `#ifdef` (if defined), `#ifndef` (if not defined), `#elif`, `#else`, and `#endif`.

This is heavily used for:
- **Platform Guards:** Including Windows-specific headers on Windows, and POSIX headers on Linux.
- **Feature Flags:** Compiling in experimental features only if a specific macro is defined at compile time.
- **Debug vs Release:** Removing expensive assertions or logging from the final release build.

```c
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
```

You can define these macros directly in the code using `#define FEATURE_X 1`, or pass them via the compiler's command line using `-D` flags (e.g., `gcc -DFEATURE_X=1 main.c`), which is how build systems configure the software. The `#undef` directive can be used to remove a macro definition.

## 9.5 Predefined Macros and Directives

The C standard mandates several predefined macros that the compiler automatically populates [5]:
- `__FILE__`: A string literal representing the current filename.
- `__LINE__`: An integer representing the current line number in the source file.
- `__DATE__` / `__TIME__`: String literals with the compilation timestamp.

*(Note: `__func__`, which provides the current function name, is often grouped with these, but it is technically a predefined identifier, not a macro).*

Other useful directives include:
- `#error "message"`: Forces the compilation to immediately fail and prints the message. Useful for enforcing compiler versions or missing configurations.
- `#pragma`: Issues compiler-specific commands. Behavior is implementation-defined.
- `#line`: Changes the compiler's internal concept of the current line number and filename, mostly used by code generators.

The `assert(condition)` macro (from `<assert.h>`) uses `__FILE__` and `__LINE__` to print the exact location where a program's invariant failed. If the macro `NDEBUG` is defined before including `<assert.h>`, all `assert()` calls compile to nothing.

## 9.6 Real-world Idioms

The preprocessor enables several powerful idioms heavily used in systems programming.

### `ARRAY_SIZE`
Returns the number of elements in a statically allocated array.

```c
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
```

### `container_of`
A staple of the Linux kernel. Given a pointer to a struct member, it calculates the pointer to the struct containing it. This enables generic, intrusive data structures.

```c
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))
```

### X-Macros (Advanced)
A technique where a list of data is defined in one macro, and then expanded multiple times with different definitions of an "X" macro. This allows you to generate enums, string arrays, and switch statements from a single source of truth.

```{=typst}
#interview[
```

**Q: When should you use a macro versus `inline`, `const`, or `enum`?**

**A:** Modern C strongly prefers native language features over macros whenever possible, because they provide type safety, scope, and are visible to debuggers.
- Use `const` variables or `enum` constants instead of object-like macros for values.
- Use `inline` functions instead of function-like macros to avoid the multiple evaluation trap and enforce parameter type checking.
- **Use macros ONLY when you must manipulate text:** for stringizing (`#`), token-pasting (`##`), capturing file/line numbers (`__FILE__`), manipulating control flow (`do { ... } while(0)`), conditional compilation, or generic type-agnostic operations (`container_of`) that cannot be expressed as standard C functions.

```{=typst}
]
```

---

## Worked Examples

### Traced: Expanding a Buggy Macro

Let's trace the expansion of a naïve macro `SQUARE(x)`.

```c
#define SQUARE(x) x * x
```

**Scenario 1: Precedence Failure**
Code: `int y = SQUARE(2 + 3);`
Text substitution: `int y = 2 + 3 * 2 + 3;`
Evaluation (by compiler): `3 * 2` is `6`. `2 + 6 + 3` is `11`. (Expected `25`).
Fix: Wrap parameter and body. `#define SQUARE(x) ((x) * (x))`

**Scenario 2: The Double-Eval Trap (Undefined Behavior)**
Code:

```c
#define SQUARE_SAFE(x) ((x) * (x))
int i = 5;
int z = SQUARE_SAFE(i++);
```

Text substitution: `int z = ((i++) * (i++));`
Evaluation: Modifying `i` twice without an intervening sequence point is undefined behavior in C. The result is unpredictable. The compiler might produce `25`, `30`, or crash.
Fix: There is no standard C macro fix for this. Use an `inline` function instead.

### Worked: A Syntactically Safe Macro and `do-while(0)`

A generic macro to swap two integers using XOR (no temporary variable), safely bundled syntactically.

```c
#define SWAP_INT(a, b) do { \
    (a) ^= (b); \
    (b) ^= (a); \
    (a) ^= (b); \
} while (0)
```

Notice how every use of `a` and `b` is heavily parenthesized to protect against the caller passing an expression like `*ptr`. The block is wrapped in `do { ... } while (0)` so it acts as a single statement. However, because it evaluates its arguments three times, it is still vulnerable to the multiple evaluation trap if called with side-effecting expressions like `SWAP_INT(i++, j++)`!

### Faded: Compute Array Capacity

Write the `ARRAY_SIZE` macro to compute how many elements a statically allocated array `a` holds. The total byte size is divided by the byte size of...

```c
// Calculate total size of the array, divided by the size of its first element
#define ARRAY_SIZE(a) (sizeof(a) / ________)
```

---

### References
[1] "GCC 13.2 Manual: Pragmas" — GNU Project — https://gcc.gnu.org/onlinedocs/gcc/Pragmas.html
[2] "ISO/IEC 9899:2011 (C11), Section 6.10.3 Macro replacement" — ISO — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[3] "CERT C Coding Standard: PRE10-C. Wrap multistatement macros in a do-while loop" — SEI CERT — https://wiki.sei.cmu.edu/confluence/display/c/PRE10-C.+Wrap+multistatement+macros+in+a+do-while+loop
[4] "Variadic Macros" — cppreference.com — https://en.cppreference.com/w/c/preprocessor/replace
[5] "Predefined Macros" — cppreference.com — https://en.cppreference.com/w/c/preprocessor/replace
