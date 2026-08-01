# Number Systems and Data Representation

This section is a compact recap of how data is represented at the hardware level and how C++ exposes these representations. 

## Bits, bytes, and positional systems

At the lowest level, computer memory is a vast sequence of switches that are either off (`0`) or on (`1`). 
- A **bit** (binary digit) is the smallest unit of data, holding a `0` or `1`. Computers use binary because distinguishing between two voltage levels in hardware is fast and reliable.
- A **nibble** is 4 bits.
- A **byte** is 8 bits. It is the smallest addressable unit of memory in C++.
- A **word** is the natural data size of the processor (e.g. 32 bits or 64 bits).

Humans count in base-10 (decimal). Computers count in base-2 (binary). Because binary strings are long and hard to read, programmers frequently group bits into threes (base-8, **octal**) or fours (base-16, **hexadecimal**).

- **Binary (Base-2)**: Digits 0-1.
- **Octal (Base-8)**: Digits 0-7.
- **Decimal (Base-10)**: Digits 0-9.
- **Hexadecimal (Base-16)**: Digits 0-9 and A-F.

To convert binary to hexadecimal, group bits into fours from right to left: `1010 1010` is `0xAA`.

## Integer literals in C++

C++ provides syntax for writing integer literals in all four common bases, as well as suffixes to specify their exact type and digit separators for readability.

```cpp
int dec = 42;             // Decimal (base 10)
int oct = 052;            // Octal (base 8): prefix with '0'
int hex = 0x2A;           // Hexadecimal (base 16): prefix with '0x' or '0X'
int bin = 0b101010;       // Binary (base 2): prefix with '0b' or '0B' (C++14)

// Digit separators (C++14) make long numbers readable:
long long wealth = 1'000'000'000;
int mask = 0b1100'0011'1010'0101;

// Suffixes force the type:
unsigned int u = 42u;           // 'u' or 'U' for unsigned
long l = 42l;                   // 'l' or 'L' for long
unsigned long long ull = 42ull; // Combinations are valid
```

::: keypoint
In Python, integers are arbitrary-precision and grow as large as memory allows. In C++, integers are strictly fixed-width (e.g. 32-bit or 64-bit); they have a hard maximum limit.
:::

## Signed integer representation: Two's complement

Unsigned integers simply use their bits to store the magnitude. But how do we store negative numbers? Early hardware tried **sign-magnitude** (reserving the top bit for the sign) and **one's complement** (flipping all bits to negate). Both suffered from having two representations for zero (`+0` and `-0`) and required complex circuitry for basic arithmetic.

Modern hardware universally uses **two's complement** for signed integers.

To negate a number in two's complement:
1. Invert all bits (the one's complement).
2. Add 1.

```cpp
// Assuming an 8-bit signed integer (int8_t):
//  5 is  0000 0101
// -5 is: 1111 1010 (invert)
//      +         1 (add 1)
//      = 1111 1011
```

Two's complement is elegant because addition hardware does not need to care whether the numbers are positive or negative — the same binary addition works for both. It has only one zero (`0000 0000`). Consequently, its range is asymmetric: an $n$-bit signed integer can represent values from $-2^{n-1}$ to $2^{n-1}-1$. For an 8-bit integer, the range is $[-128, 127]$.

::: interview
"Explain two's complement and why it is used." Mention the negation rule (invert and add 1), the fact that it has a single zero representation, and that it simplifies ALU hardware because signed and unsigned addition use the exact same logic circuitry.
:::

## Integer overflow

Because C++ integers are fixed-width, operations that exceed the maximum (or minimum) representable value cause an **overflow**.

For **unsigned** integers, overflow is well-defined: it wraps around using modulo $2^n$ arithmetic.

```cpp
#include <iostream>
#include <cstdint>

int main() {
    uint8_t u = 255; // Max 8-bit unsigned value
    u = u + 1;       // Wraps around to 0
    return 0;
}
```

For **signed** integers, overflow is **undefined behaviour (UB)**. The compiler is allowed to assume signed overflow never happens, which can lead to aggressive optimisations deleting your safety checks.

```cpp
int8_t s = 127;  // Max 8-bit signed value
s = s + 1;       // UNDEFINED BEHAVIOUR! (Might wrap to -128, might crash)
```

::: trap
Never check for signed overflow after it has happened (e.g. `if (a + b < a)`). Because signed overflow is UB, the compiler will often optimise the check away entirely. You must check *before* the operation: `if (b > INT_MAX - a)`.
:::

## Bitwise operators

C++ provides operators to manipulate integers at the bit level. These are crucial for systems programming and hardware interfacing.

```cpp
uint8_t a = 0b00001100; // 12
uint8_t b = 0b00001010; // 10

uint8_t and_res = a & b;  // 0b00001000 (Bitwise AND: 1 if both are 1)
uint8_t or_res  = a | b;  // 0b00001110 (Bitwise OR: 1 if either is 1)
uint8_t xor_res = a ^ b;  // 0b00000110 (Bitwise XOR: 1 if different)
uint8_t not_a   = ~a;     // 0b11110011 (Bitwise NOT: flips all bits)

uint8_t shl = a << 1;     // 0b00011000 (Shift left: multiplies by 2)
uint8_t shr = a >> 1;     // 0b00000110 (Shift right: divides by 2)
```

Common bit manipulation idioms using a bitmask (where `n` is the bit index, 0-based from the right):

```cpp
uint8_t flags = 0b00000000;
int n = 3;

// Set the nth bit to 1
flags |= (1 << n);

// Clear the nth bit to 0
flags &= ~(1 << n);

// Toggle the nth bit
flags ^= (1 << n);

// Read the nth bit (returns non-zero if set)
bool isSet = flags & (1 << n);
```

## Endianness

When an integer occupies more than one byte (e.g. a 32-bit `int` takes 4 bytes), the hardware must decide in what order to store those bytes in memory. This is called **endianness**.

Given the 32-bit hexadecimal value `0x1A2B3C4D`:
- **Big-endian** stores the most significant byte first: `1A 2B 3C 4D`.
- **Little-endian** stores the least significant byte first: `4D 3C 2B 1A`.

Most modern desktop processors (x86, ARM) are little-endian. Endianness generally only affects you when writing raw bytes to a file, sending data over a network, or interpreting a pointer cast to a `char*`.

::: interview
"What is endianness?" It is the byte-ordering of multi-byte data types in memory. Network protocols typically demand big-endian (often called "network byte order"), so you must convert little-endian host data before transmission.
:::

## Floating point representation

C++ represents fractional numbers using the **IEEE-754** standard. A floating-point number is stored in scientific notation in binary, divided into three fields:
1. **Sign bit**: `0` for positive, `1` for negative.
2. **Exponent**: The power of 2, stored with a bias.
3. **Mantissa (or significand)**: The fractional digits.

- `float` (single precision): 32 bits (1 sign, 8 exponent, 23 mantissa).
- `double` (double precision): 64 bits (1 sign, 11 exponent, 52 mantissa).

Because the mantissa is finite and based on powers of 2 (e.g. $1/2$, $1/4$, $1/8$), most decimal fractions cannot be represented exactly. For example, `0.1` in decimal is an infinitely repeating fraction in binary, much like `1/3` is `0.333...` in decimal.

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double a = 0.1;
    double b = 0.2;
    double c = 0.3;
    
    // Outputs: false (a + b might be 0.30000000000000004)
    std::cout << std::boolalpha << (a + b == c) << "\n";
    
    return 0;
}
```

::: trap
Never compare floating-point numbers for exact equality (`==`). Always check if the absolute difference is within a tiny tolerance (an **epsilon**).
:::

::: interview
"Why does `0.1 + 0.2 != 0.3`?" Explain that standard floating-point types use base-2 fractions. Just as `1/10` cannot be written finitely in base-2, it must be approximated. These slight rounding errors compound during arithmetic.
:::

IEEE-754 also defines special values:
- **Infinity** (`inf`): The result of dividing a non-zero number by `0.0`.
- **Not a Number** (`NaN`): The result of an undefined operation, like `0.0 / 0.0`. `NaN` is unique because it compares unequal to everything, including itself (`NaN == NaN` is false).

## Character encoding

Characters in C++ are fundamentally just integers mapped to visual glyphs.

- **ASCII**: Maps the numbers 0–127 to English characters and control codes. For example, `'A'` is 65, and `'a'` is 97. The standard `char` type is typically 1 byte, perfectly holding ASCII.
- **Unicode**: A universal standard assigning a unique number (a code point) to every character in every human language.
- **UTF-8**: A variable-length encoding of Unicode. ASCII characters take 1 byte, while complex symbols take up to 4 bytes. C++ uses `char` strings for UTF-8.
- C++ also provides `char16_t` and `char32_t` for UTF-16 and UTF-32 encodings, ensuring a fixed size per code unit.

```cpp
char ascii = 'A';           // Stored as integer 65
char16_t utf16 = u'ñ';      // 16-bit character
char32_t emoji = U'🚀';     // 32-bit character
```
