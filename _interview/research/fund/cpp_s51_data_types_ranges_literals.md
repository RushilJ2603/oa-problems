# Fundamental Data Types, Ranges, and Literals

C++ provides a rich set of built-in fundamental data types. Because C++ maps directly to the underlying hardware, these types are designed for performance and tight memory control rather than mathematical purity.

::: keypoint
In Python, there is one unbounded `int` type and one `float` type, unlike C++'s many hardware-mapped, fixed-size types.
:::

## The fundamental types

### Boolean, void, and null
- `bool`: Holds `true` or `false`.
- `void`: Represents the absence of a type, used mainly for functions that do not return a value, or generic pointers (`void*`).
- `std::nullptr_t`: The type of the null pointer literal `nullptr`.

```cpp
bool isReady = true;
void doNothing() {}
std::nullptr_t nullPtr = nullptr;
```

### Character types
Character types are integral types optimised for text representation.
- `char`: The default character type. Whether it is signed or unsigned is **implementation-defined**.
- `signed char` and `unsigned char`: Explicitly signed or unsigned 1-byte integers.
- `wchar_t`: A wide character, large enough to contain the largest character set supported by the implementation's locale.
- `char8_t` (C++20), `char16_t`, `char32_t`: Explicit types for UTF-8, UTF-16, and UTF-32 code units.

```cpp
char c = 'A';
char16_t utf16_c = u'\u20AC'; // Euro sign
```

### Integer types
C++ provides four standard signed integer types, each with a corresponding `unsigned` variant.
- `short` (or `short int`)
- `int`
- `long` (or `long int`)
- `long long` (or `long long int`)

```cpp
int counter = -10;
unsigned long long bigCount = 42;
```

### Floating-point types
For fractional values, C++ provides three types of increasing precision.
- `float`: Single precision.
- `double`: Double precision (the default choice).
- `long double`: Extended precision.

```cpp
double pi = 3.1415926535;
```

## Size guarantees

The C++ standard does **not** mandate exact absolute sizes in bytes for the fundamental integer types (except `char`). Instead, it fixes minimum sizes and a strict relative ordering:

`1 == sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)`

By definition, `sizeof(char)` is exactly 1 byte. (Note that a C++ "byte" is at least 8 bits; on some exotic hardware it could be more, though it is universally 8 bits in modern desktop usage).

::: trap
Assuming `sizeof(int)` is exactly 4 bytes (32 bits) is a classic mistake. While true on most modern desktop platforms, it is implementation-defined.
:::

::: interview
**Is the size of `int` fixed in C++?** No. The standard only guarantees that `int` is at least 16 bits and at least as large as `short`. Its actual size depends on the compiler and the target architecture's data model (e.g., LP64 vs LLP64).
:::

## Fixed-width integer types (`<cstdint>`)

When you need exact bit-width guarantees (e.g. for binary file formats, cryptography, or networking), you must use the fixed-width types from `<cstdint>`.

```cpp
#include <cstdint>

// Exact-width integer types
int8_t   i8  = -10;
uint16_t u16 = 65000;
int32_t  i32 = 0;
uint64_t u64 = 123456789;

// Minimum-width (at least N bits)
int_least32_t least32 = 42;

// Fastest minimum-width (the fastest type of at least N bits for the architecture)
int_fast16_t fast16 = 42;

// Pointer-sized integers (guaranteed to be large enough to hold a pointer)
intptr_t  iptr = 0;
uintptr_t uptr = 0;
```

### Crucial standard library types

Two standard type aliases appear everywhere in C++ codebases:
- `std::size_t`: An unsigned integer type returned by the `sizeof` operator. It is guaranteed to be large enough to hold the size in bytes of any object the system can allocate.
- `std::ptrdiff_t`: A signed integer type used to represent the distance between two pointers.

::: interview
**What is `size_t` and when should you use it?** `size_t` is the unsigned integer type returned by `sizeof`. You should use it whenever representing the size of an object, a count of elements, or an index into standard containers like `std::vector`, rather than using a plain `int`.
:::

## Signed versus unsigned: ranges and traps

An `unsigned` integer uses the bit normally reserved for the sign to represent larger positive numbers, effectively doubling its maximum positive range compared to its `signed` counterpart.

You can inspect these ranges using the `<limits>` header:

```cpp
#include <iostream>
#include <limits>

int main() {
    std::cout << "int max: " << std::numeric_limits<int>::max() << "\n";
    std::cout << "uint max: " << std::numeric_limits<unsigned int>::max() << "\n";
    std::cout << "int digits (bits): " << std::numeric_limits<int>::digits << "\n";
    return 0;
}
```

### The signed/unsigned comparison trap

Comparing or mixing signed and unsigned integers is a dangerous source of subtle bugs.

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v; // empty, so v.size() is 0
    int index = -1;
    
    // TRAP: index is promoted to an unsigned size_t for the comparison.
    // -1 underflows to the maximum unsigned value (e.g. 18446744073709551615).
    if (index < v.size()) {
        std::cout << "This will NOT print!\n";
    }
    
    return 0;
}
```

::: trap
When comparing a signed and unsigned integer, the signed integer is implicitly converted to unsigned. A negative value wraps around to a massive positive number, silently breaking the logic.
:::

### Unsigned subtraction wraparound

::: trap
Unsigned integers can never be negative. Subtracting past zero wraps around to the maximum possible value.
:::

```cpp
unsigned int count = 5;
// Infinite loop! When count drops below 0, it wraps to UINT_MAX.
while (count >= 0) { 
    --count; 
}
```

::: interview
**When should you use unsigned integers?** Use them primarily for bit manipulation, masks, or when interacting with standard library APIs that require them (like container indices). Do not use them simply to enforce a "must be positive" domain constraint, as the wraparound traps make arithmetic dangerous.
:::

### Integer promotions and usual arithmetic conversions

When you perform arithmetic on types smaller than `int` (like `char` or `short`), C++ implicitly promotes them to `int` before the operation. This is called **integer promotion**.

When an operation involves two different types (e.g., `int` and `double`), the compiler applies the **usual arithmetic conversions** to find a common type. Generally, the "smaller" or "less precise" type is promoted to the "larger" type (e.g., the `int` becomes a `double`).

## Literals in full

A **literal** is a hardcoded value directly written into the source code.

### Integer literals

You can write integers in decimal, octal, hexadecimal, or binary forms. Since C++14, you can use the single quote (`'`) as a digit separator to improve readability.

```cpp
int dec = 42;
int oct = 052;        // Octal (prefix 0)
int hex = 0x2A;       // Hexadecimal (prefix 0x or 0X)
int bin = 0b101010;   // Binary (prefix 0b or 0B)

long billion = 1'000'000'000; // Digit separators (C++14)
```

Suffixes dictate the literal's exact type. Without a suffix, an integer literal is the smallest type that can hold it (usually `int`).
- `u` or `U`: Unsigned
- `l` or `L`: Long
- `ll` or `LL`: Long long

```cpp
auto u1 = 42U;    // unsigned int
auto l1 = 42L;    // long
auto ul1 = 42ULL; // unsigned long long
```

### Floating-point literals

Floating-point literals are of type `double` by default. Use suffixes to change this.

```cpp
double d = 3.14159;
double sci = 1.23e-4; // Scientific notation (0.000123)

float f = 3.14f;      // 'f' or 'F' suffix for float
long double ld = 2.7L; // 'l' or 'L' suffix for long double
```

### Character literals and escape sequences

Character literals are enclosed in single quotes. Escape sequences allow you to express unprintable characters.

```cpp
char a = 'a';
char newline = '\n';
char tab = '\t';
char nullChar = '\0';
```

Encoding prefixes enforce specific character types:

```cpp
wchar_t wide_c = L'A';
char8_t utf8_c = u8'A'; // C++20
char16_t utf16_c = u'A';
char32_t utf32_c = U'A';
```

### String literals

String literals are enclosed in double quotes. Adjacent string literals are automatically concatenated by the compiler.

```cpp
const char* msg = "Hello, world!";
const char* joined = "This is " "one string."; 
```

Like character literals, string literals accept encoding prefixes (`L"..."`, `u8"..."`, `u"..."`, `U"..."`).

#### Raw string literals

A **raw string literal** ignores all escape sequences. It is enclosed in `R"( ... )"`. This is invaluable for regular expressions, Windows file paths, or multi-line strings.

```cpp
// Without raw strings, backslashes must be escaped
const char* path1 = "C:\\Windows\\System32";

// With raw strings
const char* path2 = R"(C:\Windows\System32)";
```

### Boolean and pointer literals

```cpp
bool flag = true; // or false
int* ptr = nullptr; // Always prefer nullptr over NULL or 0
```

### User-defined literals

C++ allows developers to define custom suffixes to create user-defined literals. 

```cpp
// One-line example showing a custom literal in use:
auto distance = 10.5_km; // Assumes an operator""_km has been defined
```

### `auto` with literals

When using the `auto` keyword, the suffix of the literal is what tells the compiler which type to deduce.

```cpp
auto w = 42;      // deduced as int
auto x = 42U;     // deduced as unsigned int
auto y = 3.14;    // deduced as double
auto z = 3.14f;   // deduced as float
auto s = "Hello"; // deduced as const char*
```
