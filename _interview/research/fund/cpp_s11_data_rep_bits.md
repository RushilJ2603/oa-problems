# 11. Data Representation & Bit Manipulation

Before we can manipulate hardware registers or optimize memory usage, we must understand exactly how C programs map abstract numbers into physical bits [1].

## 11.1 Binary, Hexadecimal, and the Byte

Modern computers store data in binary (base-2). A single binary digit is a **bit** (0 or 1). 
- A **nibble** is 4 bits. It can represent $2^{4} = 16$ distinct values (0 to 15).
- A **byte** is 8 bits (two nibbles). It is the smallest addressable unit of memory in C.
- A **word** is the natural data size of the processor (e.g., 32 bits or 64 bits).

Binary is too verbose for humans, so we use **hexadecimal** (base-16), prefixing values with `0x`. Because $16 = 2^{4}$, exactly one hex digit maps to one nibble. The hex digits are `0-9` and `A-F` (representing 10-15).

```{=typst}
#keypoint[
```

Memorize this mapping: `0x0` is `0000`, `0xF` is `1111`. To read `0xA5`, translate each nibble: `A` (10) is `1010`, `5` is `0101`. Thus, `0xA5` is `1010 0101`.

```{=typst}
]
```

## 11.2 Integer Representation: Two's Complement

Unsigned integers simply use straight binary positional notation. But how do we represent negative numbers? Modern systems universally use **two's complement**.

```{=typst}
#heavy[
```

Dense — slow down: In two's complement, the most significant bit carries a negative weight, completely changing the math at the boundaries.

```{=typst}
]
```

**Analogy:** Imagine a mechanical car odometer at `0000`. If you drive backward one mile, the odometer rolls under to `9999`. We can agree that `9999` represents -1, `9998` represents -2, and so on. Two's complement is exactly this "roll under" arithmetic applied to binary.

![Two's Complement Wheel](assets/s11_twos_complement.png)

**Example First:** Consider an 8-bit unsigned number: `1111 1111` is 255. If we add 1, it overflows and wraps back to `0000 0000`. Now consider two's complement. We declare that `1111 1111` is -1. If we add 1 to it: `1111 1111 + 0000 0001 = 0000 0000`. The binary addition hardware doesn't need to know if the numbers are signed or unsigned—it just performs standard addition, and the bit pattern naturally wraps to 0.

**Plain-English:** Two's complement represents signed integers by assigning a negative value to the most significant bit (the sign bit). The remaining bits have their normal positive values. To negate a number, flip all its bits and add 1.

**Technical:** For an $N$-bit two's complement integer, the value of the bits $b_{N-1} b_{N-2} \dots b_{0}$ is:
$$-b_{N-1} 2^{N-1} + \sum_{i=0}^{N-2} b_{i} 2^{i}$$
The range is asymmetrical: $[-2^{N-1}, 2^{N-1}-1]$. For 8 bits, this is -128 to +127. There is one unique zero (`0000 0000`).

```{=typst}
#trap[
```

**The Overflow Trap**: Beginners assume a signed integer will simply wrap around to a negative value when it gets too large, just like unsigned integers wrap to zero. In C, unsigned arithmetic is *defined* to wrap modulo $2^{N}$. Signed overflow, however, is **Undefined Behavior (UB)** [2]. The compiler assumes signed overflow never happens and will aggressively optimize your checks away if they rely on wrapping.

```{=typst}
]
```

This breaks when converting between types. If you widen a signed type (e.g., 8-bit `char` to 32-bit `int`), the compiler performs **sign extension**: it fills the new upper bits with copies of the sign bit to preserve the negative value. A common pitfall is that the signedness of the plain `char` type is implementation-defined (it might be signed, it might be unsigned) [1].

## 11.3 Endianness: Byte Order in Memory

When we store an 8-bit `uint8_t`, it takes one byte. But how does the hardware store a 32-bit `uint32_t` (4 bytes) in memory?

```{=typst}
#heavy[
```

Dense — slow down: The order of bytes across multiple memory addresses depends entirely on the CPU architecture, not the C standard.

```{=typst}
]
```

**Analogy:** If you write down the date "January 2, 2024", Americans write "01-02-2024" (Month-Day-Year), while Europeans write "02-01-2024" (Day-Month-Year). The underlying information is identical, but the sequence of the parts differs.

![Endianness Layout](assets/s11_endianness.png)

**Example First:** We have a 32-bit integer `0x11223344`. We want to store it starting at memory address `0x1000`.
- In a **Big-Endian** system, the most significant byte (`0x11`) goes into the lowest address (`0x1000`), followed by `0x22`, `0x33`, and `0x44`.
- In a **Little-Endian** system, the least significant byte (`0x44`) goes into the lowest address (`0x1000`), followed by `0x33`, `0x22`, and `0x11`.

**Plain-English:** Endianness describes how a multi-byte data type is arranged in consecutive memory bytes. Big-endian puts the "big end" first. Little-endian puts the "little end" first. Most modern consumer CPUs (x86, ARM by default) are little-endian.

**Technical:** C does not dictate endianness. When transmitting data over a network or writing binary files, endianness must be strictly managed [3]. Internet protocols use big-endian, historically called "network byte order". C provides `<arpa/inet.h>` functions like `htonl()` (host-to-network long) and `ntohl()` to safely serialize multi-byte integers regardless of the host's native endianness.

This breaks when casting a pointer to a multi-byte integer into a `char *` to read individual bytes, or when reading a raw binary file created on a machine with a different architecture.

## 11.4 Bitwise Operators & Shifts

C provides direct bit-level manipulation operators. These operate on integer types bit-by-bit.

- `&` (Bitwise AND): 1 if both bits are 1, else 0.
- `|` (Bitwise OR): 1 if either bit is 1, else 0.
- `^` (Bitwise XOR): 1 if bits are different, else 0.
- `~` (Bitwise NOT): Flips all bits (0 becomes 1, 1 becomes 0).

**Shifts:** `<<` shifts bits left, `>>` shifts bits right.
Shifting left by $N$ (`x << N`) is equivalent to multiplying by $2^{N}$.
Right shifting (`x >> N`) is equivalent to dividing by $2^{N}$, but with a critical distinction based on signedness:
- **Logical Shift:** Shifts in `0`s from the left. Usually applied to unsigned types.
- **Arithmetic Shift:** Shifts in copies of the sign bit from the left, preserving the number's sign. Applied to signed types on most compilers (though implementation-defined).

```{=typst}
#trap[
```

**The Shift UB Trap**: Shifting by a negative amount, or by an amount greater than or equal to the bit-width of the type, is Undefined Behavior. `1 << 32` on a 32-bit integer is UB, not 0.

```{=typst}
]
```

## 11.5 The Interview Core: Bit Manipulation Idioms

You are expected to recognize and write these idioms flawlessly from memory. They frequently appear in embedded systems (hardware registers) and algorithmic interviews.

This direct bit manipulation is the foundation of the **read-modify-write** pattern used universally to safely update hardware registers (forward §15).

```{=typst}
#interview[
```

**Q:** How do you set, clear, and toggle the $n$-th bit of an integer `x` without altering other bits?

**A:** You construct a **mask** by shifting a literal `1` left by $n$, then apply `|`, `& ~`, or `^`.

```c
// Always cast 1 to the target unsigned type to avoid signed overflow UB and size mismatches
uint32_t mask = (uint32_t)1 << n; 

x |= mask;       // SET bit n: 0 OR 1 = 1, 1 OR 1 = 1 (forces bit to 1)
x &= ~mask;      // CLEAR bit n: x AND 0 at bit n forces 0. Other bits AND 1 remain unchanged.
x ^= mask;       // TOGGLE bit n: x XOR 1 flips the bit. Other bits XOR 0 remain unchanged.
```

```{=typst}
]
```

![Bitwise operations mask](assets/s11_bit_ops.png)

### Essential Idioms

**Test a bit:**
```c
bool is_set = (x >> n) & 1u; // Shift bit to the LSB, then mask everything else out
```

**Extract a bit-field (e.g., 3 bits starting at bit 4):**
```c
uint32_t field = (x >> 4) & 0x07; // 0x07 is binary 0111 (3 bits of 1s)
```

**Test if a number is a power of two:**
Powers of two have exactly one bit set. Subtracting 1 from a power of two flips all bits up to the set bit (e.g., `0100 - 1 = 0011`).
```c
bool is_pow2 = x && !(x & (x - 1)); // The x && checks that x is not 0
```

**Isolate the lowest set bit:**
Because `-x` is `~x + 1`, this expression leaves only the lowest 1-bit intact.
```c
uint32_t lowest_set = x & -x;
```

**Count set bits (Popcount):**
Brian Kernighan's algorithm clears the lowest set bit in a loop.
```c
int count = 0;
while (x) {
    x &= (x - 1); // Clears the lowest set bit
    count++;
}
```

**Swap two variables without a temporary (XOR Swap):**
```c
a ^= b;
b ^= a;
a ^= b;
```
*(Trap: If you are swapping via pointers and both point to the exact same memory location, `*a ^= *b` resolves to `*a ^= *a`, which zeroes out the value entirely. In practice, just use a temporary variable!)*

## 11.6 Floating-Point (IEEE-754) Basics

C uses the IEEE-754 standard for `float` (32-bit single precision) and `double` (64-bit double precision) [4].
A floating-point number is stored in three fields:
1. **Sign bit:** 0 for positive, 1 for negative.
2. **Exponent:** The power of 2 (biased).
3. **Mantissa (or Significand):** The fractional digits.

```{=typst}
#trap[
```

**Equality Trap**: Floating-point math introduces rounding errors. `0.1 + 0.2` may equal `0.30000000000000004` due to binary fraction limits. Never use `==` to compare floats. Instead, check if the absolute difference is less than a tiny threshold (an *epsilon*).

```{=typst}
]
```

IEEE-754 also defines special values:
- `+Inf` and `-Inf` (Infinity, resulting from dividing a non-zero float by 0.0).
- `NaN` (Not a Number, resulting from invalid operations like `sqrt(-1.0)` or `0.0 / 0.0`). A `NaN` is unique because `NaN == NaN` always evaluates to false.

## 11.7 Worked Examples

### Traced: Two's Complement Conversion and Addition

**Goal:** Convert `-5` to an 8-bit two's complement binary, then add it to `7`.

1. **Find positive 5 in binary:** `0000 0101`
2. **Invert all bits (`~5`):** `1111 1010`
3. **Add 1:** `1111 1011`
So, `-5` is `1111 1011`.

Now, add to `7` (`0000 0111`):
```text
  1111 1011 (-5)
+ 0000 0111 (7)
-----------
 10000 0010 (The 9th bit '1' overflows and is discarded)
```
The result is `0000 0010`, which is `2`. The wrap naturally produces the correct math.

### Worked: Manipulating Bit 3

**Goal:** Set, clear, and test bit 3 of an 8-bit unsigned integer initialized to `0100 0000` (64).

1. **Initial state:** `x = 0100 0000`
2. **Set bit 3:** `x |= (1u << 3)`
   - `1u << 3` is `0000 1000`
   - `0100 0000 | 0000 1000 = 0100 1000`
3. **Clear bit 3:** `x &= ~(1u << 3)`
   - `~(0000 1000)` is `1111 0111`
   - `0100 1000 & 1111 0111 = 0100 0000`
4. **Test bit 3:** `(x >> 3) & 1u`
   - `0100 0000 >> 3` is `0000 1000`
   - `0000 1000 & 0000 0001 = 0000 0000` (false)

### Worked: Endianness Check

**Goal:** Write a function to determine if the host CPU is little-endian or big-endian.

```c
#include <stdbool.h>
#include <stdint.h>

bool is_little_endian(void) {
    uint16_t test = 0x0001;
    // Cast the address of the multi-byte integer to a pointer to a single byte
    uint8_t *ptr = (uint8_t *)&test;
    // If the lowest address (ptr[0]) contains the least significant byte (0x01),
    // then the architecture is little-endian.
    return (*ptr == 0x01);
}
```

### Faded Example: Clear the Low Nibble

**Goal:** Clear the lowest 4 bits (the low nibble) of an 8-bit integer `x`.

```c
#include <stdint.h>

uint8_t clear_low_nibble(uint8_t x) {
    // We want to keep the upper 4 bits and force the lower 4 bits to 0.
    // The mask needs 1s in the upper half, 0s in the lower half.
    uint8_t mask = _______; // Try to write the hex value here (Answer: 0xF0)
    return x & mask;
}
```

### References

[1] ISO/IEC 9899:2023 (C23 standard draft n3220) — WG14 — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf
[2] Understanding Integer Overflow in C/C++ — Dietz et al., ICSE 2012 — https://users.cs.utah.edu/~regehr/papers/overflow12.pdf
[3] Byte Order Fallacy — Rob Pike — https://commandcenter.blogspot.com/2012/04/byte-order-fallacy.html
[4] IEEE Standard for Floating-Point Arithmetic (IEEE 754-2019) — IEEE — https://ieeexplore.ieee.org/document/8766229
