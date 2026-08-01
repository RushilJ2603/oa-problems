# 2. Data Types, Variables & Operators

C is statically typed: every variable and expression has a type known at compile time. The type dictates how many bytes are used and how those bytes are interpreted.

## The Scalar Type System

A *scalar type* is a single, indivisible value, representing a single number or pointer (as opposed to structures or arrays which hold multiple values).

C guarantees minimum ranges for integer types, not exact byte sizes [1]. The actual size is chosen by the compiler to best fit the target hardware.

| Type | Signedness | Minimum Guaranteed Range | Typical Size (bytes) |
|---|---|---|---|
| `char` | Implementation-defined | $0$ to $255$ (or $-127$ to $127$) | $1$ |
| `short` | Signed | $-32,767$ to $32,767$ | $2$ |
| `int` | Signed | $-32,767$ to $32,767$ | $4$ |
| `long` | Signed | $-2,147,483,647$ to $2,147,483,647$ | $4$ or $8$ |
| `long long`| Signed | $-(2^{63} - 1)$ to $2^{63} - 1$ | $8$ |

*Note: The C standard requires `int` to be at least 16 bits, but it is 32 bits on almost all modern systems.*

- `signed` and `unsigned`: Integer types (except `char`) are signed by default. Prefixing with `unsigned` shifts the range to start at $0$, doubling the maximum positive value. `char` is uniquely strange: whether a plain `char` is signed or unsigned is left entirely up to the compiler. If you need a specific behavior for math, explicitly use `signed char` or `unsigned char`.
- `float`, `double`, `long double`: Floating-point types. `float` typically maps to IEEE 754 single-precision (32-bit), `double` to double-precision (64-bit).
- `_Bool` (or `bool` via `<stdbool.h>`): A boolean type that can only hold $0$ or $1$.
- `void`: An incomplete type meaning "no value" or "no type". You cannot create a variable of type `void`.

```{=typst}
#keypoint[
```

You can query the size of a type in bytes using the `sizeof` operator (e.g., `sizeof(int)`). To find the actual min/max limits on your exact system, include `<limits.h>` (for `INT_MAX`, `UINT_MAX`, etc.) or `<float.h>` [2].

```{=typst}
]
```

## Fixed-Width Integer Types

Because `int` might be 16 bits on a microcontroller and 32 bits on a PC desktop, relying on standard types for exact byte layouts (like network protocols or hardware registers) breaks portability.

To solve this, `<stdint.h>` provides types that guarantee exact bit widths [3]:

- `int8_t`, `uint16_t`, `int32_t`, `uint64_t`: Exact-width types. A `uint32_t` is exactly 32 bits, unsigned, everywhere.
- `int_fast16_t`: The fastest integer type with at least 16 bits.
- `int_least16_t`: The smallest integer type with at least 16 bits.
- `intptr_t`, `uintptr_t`: Integers guaranteed to be large enough to safely hold a pointer address.

Additionally, `<stddef.h>` provides two critical alias types:
- `size_t`: An unsigned integer returned by the `sizeof` operator. It is guaranteed to be large enough to hold the size of the largest possible object on the system in bytes. Always use this for array indices and memory sizes.
- `ptrdiff_t`: A signed integer that results from subtracting two pointers, able to represent the distance between elements in a massive array.

```{=typst}
#interview[
```

**Q: When should I use `int` versus `int32_t` versus `size_t`?**

Use `int` for generic counters or values where exact size doesn't matter (the compiler will pick the most efficient native size). Use `<stdint.h>` types like `int32_t` when modeling exact hardware, network packets, or file formats. Use `size_t` for anything representing memory size, byte counts, or array indexing.

```{=typst}
]
```

## Literals: Values in Source Code

A *literal* is a raw value written directly in source code. Every literal has a fixed type determined by its syntax.

- **Integer Literals**: Written in decimal (`42`), octal (`052` — prefixed with `0`), hexadecimal (`0x2A` — prefixed with `0x`), or binary (C23: `0b101010` — prefixed with `0b`).
  - An integer literal is a signed `int` by default, but automatically takes a larger type (like `long`) if the value is too large.
  - Append suffixes to change the type: `U` (unsigned), `L` (long), `LL` (long long). Example: `42UL` has type `unsigned long`.
- **Character Literals**: Enclosed in single quotes, e.g., `'A'`. Trap: In C (unlike C++), a character literal has type `int`, not `char`.
- **Floating-Point Literals**: Must have a decimal point (`3.14`) or an exponent (`1e-4`). They are `double` by default. Suffix with `f` or `F` for `float` (e.g., `3.14f`).
- **String Literals**: Enclosed in double quotes, e.g., `"Hello"`. They include a hidden null terminator (`\0`) appended at the end. Their type is an array of `char`.

Escape sequences allow representing unprintable characters: `\n` (newline), `\t` (tab), `\0` (null terminator), `\\` (literal backslash).

## Variables, Scope, and Initialization

A *variable* is a named region of memory.

**Declaration vs. Definition**:
- A *declaration* introduces the name and type to the compiler without necessarily allocating memory, promising it exists: `extern int x;`.
- A *definition* both declares the variable and allocates memory for it: `int x;`.

**Initialization**:
You can assign an initial value when defining a variable: `int count = 0;`.

```{=typst}
#trap[
```

Local variables are not zeroed out by default! An uninitialized local variable contains garbage (whatever bytes previously occupied that memory). Reading it before explicitly writing to it is undefined behavior.

```{=typst}
]
```

**Scope and Lifetime**:
A variable declared inside braces `{ ... }` has *block scope*—it is invisible to code outside those braces. By default, it has *automatic lifetime*, meaning its memory is allocated when execution enters the block and is automatically reclaimed when the block ends [4]. (We cover static and dynamic lifetimes in §6).

## Operators

C provides a rich set of operators.

- **Arithmetic**: `+`, `-`, `*`, `/`, `%` (modulo, which returns the remainder of integer division).
- **Relational**: `==` (equal), `!=` (not equal), `<`, `>`, `<=`, `>=`. They return `1` for true or `0` for false.
- **Logical**: `&&` (AND), `||` (OR), `!` (NOT).
  - *Short-circuiting*: `&&` evaluates its right side ONLY if the left side evaluates to true. `||` evaluates its right side ONLY if the left side evaluates to false. This is critical for safe guards: `if (ptr != NULL && ptr->value > 0)`.
- **Bitwise**: `&` (AND), `|` (OR), `^` (XOR), `~` (NOT), `<<` (left shift), `>>` (right shift).
- **Assignment**: `=` assigns the right side's value to the left side's memory. The expression itself evaluates to the assigned value, allowing chaining: `a = b = 0;`.
  - Compound assignment: `+=`, `-=`, `<<=`, etc. `x += 5;` is functionally equivalent to `x = x + 5;`.
- **Increment/Decrement**: `++`, `--`.
  - Pre-increment (`++x`): Increment `x`, then evaluate the expression as the new value.
  - Post-increment (`x++`): Evaluate the expression as the *current* value of `x`, then increment `x` in the background.
- **Ternary**: `condition ? true_expr : false_expr`. Evaluates to `true_expr` if the condition is non-zero, else `false_expr`.
- **Comma**: `expr1, expr2`. Evaluates `expr1`, completely discards the result, evaluates `expr2`, and returns that. Rarely used outside `for` loop headers.
- **sizeof**: Returns the size of a type or variable in bytes. It is evaluated at compile time (except for variable-length arrays).
- **Cast**: `(type)expr`. Forces conversion of `expr` to the specified `type`.

### Precedence and Associativity

Precedence dictates which operators bind tightest. Associativity dictates the evaluation order when operators have the same precedence.

| Precedence | Operator | Associativity |
|---|---|---|
| Highest | `()` `[]` `->` `.` post-`++` post-`--` | Left to Right |
| | pre-`++` pre-`--` `+` `-` `!` `~` `*` (deref) `&` (address) `sizeof` `(type)` | Right to Left |
| | `*` (mult) `/` `%` | Left to Right |
| | `+` (add) `-` (sub) | Left to Right |
| | `<<` `>>` | Left to Right |
| | `<` `<=` `>` `>=` | Left to Right |
| | `==` `!=` | Left to Right |
| | `&` (bitwise AND) | Left to Right |
| | `^` (bitwise XOR) | Left to Right |
| | `&#124;` (bitwise OR) | Left to Right |
| | `&&` | Left to Right |
| | `&#124;&#124;` | Left to Right |
| | `?:` | Right to Left |
| | `=` `+=` `-=` etc. | Right to Left |
| Lowest | `,` | Left to Right |

```{=typst}
#trap[
```

**The Bitwise Precedence Trap:** The bitwise operators `&`, `^`, and `|` have lower precedence than the equality operator `==`.

The statement `if (flags & MASK == 0)` actually evaluates as `if (flags & (MASK == 0))`, which is almost never what you want. Always parenthesize bitwise operations: `if ((flags & MASK) == 0)`.

```{=typst}
]
```

## Conversions

```{=typst}
#heavy[
```

Dense — slow down: The compiler silently rewrites your types before applying operators. This hidden behavior can invert your program's logic entirely if signed and unsigned types mix unexpectedly.

```{=typst}
]
```

Imagine a math problem where one number is measured in inches and another in feet. Before you can add them together, you must convert them to a common unit. In C, binary operators demand matching types. When they don't match, the compiler silently injects implicit conversions to make the units align [5].

![Usual Arithmetic Conversions Flowchart](assets/s02_conversions.png)

Let us examine an example first:

```c
int a = -1;
unsigned int b = 0;
if (a > b) {
    // This block WILL execute!
}
```

Wait, is $-1$ really greater than $0$? According to C, yes.

When an operator like `>` sees a signed integer on one side and an unsigned integer on the other, it applies a rigid set of rules to find a common type. It generally prefers to promote the smaller type to the larger one to preserve data. However, when mixing a signed and an unsigned type of the exact same size, the compiler converts the signed value into an unsigned value. 

Here is the exact technical mechanism. The compiler applies two phases to binary operators:

1. **Integer Promotions**: Before any math happens, small types (`char`, `short`) are promoted to `int`. If an `int` somehow cannot hold all original values, they are promoted to `unsigned int`.
2. **Usual Arithmetic Conversions**: If the operands still have different types after promotion, the compiler resolves them by rank:
   - If one is floating-point, both become the largest floating-point type present.
   - If both are integers and have different signedness:
     - If the unsigned type has a higher or equal rank (size) to the signed type, the signed operand is cast to the unsigned type.
     - If the signed type is larger and can represent all values of the unsigned type, the unsigned operand is cast to the signed type.

In our example, `a > b` mixes an `int` and an `unsigned int`. They have the same rank. By rule, the signed operand (`-1`) is cast to `unsigned int`. In memory, $-1$ is represented as all binary 1s (two's complement). When interpreted as an unsigned integer, all 1s is the maximum possible value (`UINT_MAX`, typically $4,294,967,295$). Therefore, $4,294,967,295 > 0$ evaluates to true.

This breaks when you write loops like `for (int i = 0; i < my_vector.size(); i++)` where a size function returns `size_t` (unsigned). If `i` goes negative inside the loop body, evaluating `i < size()` converts `i` to unsigned, causing a massive positive underflow value, and the loop continues incorrectly.

### Explicit Conversions (Casts)

You can force a conversion manually using a cast: `(type)expr`.

Casts are generally safe when *widening* (e.g., casting `int` to `long long`). They are highly dangerous when *narrowing* (e.g., casting `long` to `short`) because the high-order bytes are truncated, permanently altering the value if it exceeds the smaller type's capacity. Casting a `float` to an `int` simply truncates the fractional part.

## Evaluation Order & Sequence Points

What is the exact value of `i` after executing `i = i++`? What about `a[i] = i++`?

In C, the order in which the operands of an operator are evaluated is mostly unspecified by the standard. A *sequence point* is a boundary in the execution flow where the compiler guarantees that all previous side effects (like the increment in `++`) are fully complete, and no future side effects have started [6].

Modifying the same scalar variable twice without an intervening sequence point is strictly **Undefined Behavior (UB)**. Therefore, `i = i++` is UB. The compiler is legally allowed to do anything—including silently producing garbage logic or crashing. (We will cover UB and sequence points exhaustively in §19).

## Constants

You can define constant values in two primary ways (excluding `enum`s, covered in §8):

1. `#define MAX_USERS 100`: A preprocessor macro. The compiler literally performs a text replacement of `MAX_USERS` with `100` before compiling. It has no type safety and respects no scope blocks.
2. `const int max_users = 100;`: A `const`-qualified variable. It has a strict type and respects block scope. The compiler enforces that you cannot modify it after initialization.

### Worked Examples

**Traced Example: The usual arithmetic conversions**
```c
int32_t a = -5;
uint32_t b = 10;
uint64_t c = 2;

// Evaluate: (a + b) < c
```
*Trace:*
1. `a + b`: Operands are `int32_t` (signed) and `uint32_t` (unsigned). Integer promotions do nothing as they are already 32-bit.
2. Usual arithmetic conversions: Ranks are equal, but signs differ. The signed operand `a` is converted to `uint32_t`.
3. $-5$ as a 32-bit unsigned integer underflows to $4,294,967,291$.
4. $4,294,967,291 + 10$ wraps around to $5$. The result type of the addition is `uint32_t`.
5. `5 < c`: Operands are `uint32_t` and `uint64_t`. The lower rank is converted to the higher rank type. $5$ becomes a `uint64_t`.
6. $5 < 2$ evaluates to $0$ (false).

**Faded Example**
Predict the final type and value of `x`:
```c
unsigned char c1 = 200;
unsigned char c2 = 100;
// What is the type and value of x?
auto x = c1 + c2; // (Using conceptual 'auto' for the resulting type)
```
1. `c1` and `c2` are smaller than `int`.
2. Integer promotions apply first: both operands are promoted to `int` (since a standard 32-bit `int` can easily hold $200$ and $100$).
3. The addition is performed strictly as `int + int`.
4. *Your turn:* What is the final value and type of `x`? Does it overflow the 8-bit limit?
*(Answer: `x` is of type `int` with a value of $300$. It does not overflow an 8-bit unsigned char limit during the addition because the values were promoted to a wider type first).*

### References
[1] ISO/IEC 9899:2011 (C11), §5.2.4.2.1 Sizes of integer types `<limits.h>` — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[2] cppreference, "Arithmetic types" — cppreference.com — https://en.cppreference.com/w/c/language/arithmetic_types
[3] ISO/IEC 9899:2011 (C11), §7.20 Integer types `<stdint.h>` — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[4] cppreference, "Storage-class specifiers" — cppreference.com — https://en.cppreference.com/w/c/language/storage_duration
[5] cppreference, "Usual arithmetic conversions" — cppreference.com — https://en.cppreference.com/w/c/language/conversion#Usual_arithmetic_conversions
[6] cppreference, "Order of evaluation" — cppreference.com — https://en.cppreference.com/w/c/language/eval_order
