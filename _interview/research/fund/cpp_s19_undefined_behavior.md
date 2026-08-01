# 19. Undefined Behavior & C's Sharp Edges

In C, the compiler is not your babysitter; it is your business partner. It assumes you know exactly what you are doing, and in return, it gives you raw, unbridled speed. But this pact is forged on a razor's edge.

## 19.1 The Four Categories of Behavior

When you write a C program, the ISO C standard categorizes how that code behaves into four distinct buckets.

* **Well-defined behavior**: The standard dictates exactly what must happen. `int x = 5 + 3;` reliably results in `8`.
* **Implementation-defined behavior**: The standard requires the compiler to choose a behavior from a set of valid options and document it. For example, the size of an `int` can be 16, 32, or 64 bits, but the compiler manual must state which it is.
* **Unspecified behavior**: The compiler must choose a valid behavior, but it does not have to document it, and it can change from one compilation to the next. For example, in `f(g(), h())`, the standard leaves it unspecified whether `g()` or `h()` is evaluated first.

```{=typst}
#definition[
```

**Undefined Behavior (UB)** is a state where the C standard imposes absolutely no requirements on the host environment or compiler [1]. If your code triggers UB, the entire program's execution is instantly invalidated.

```{=typst}
]
```

## 19.2 What UB REALLY Means

```{=typst}
#heavy[
```

Dense — slow down: Undefined Behavior does not mean your program crashes predictably. It means the compiler is legally permitted to mathematically prove that your code will never execute UB, and aggressively delete safety checks based on that assumption.

```{=typst}
]
```

**Analogy**: Imagine making a wish to a magical genie. If you follow the strict rules of wishing, you get exactly what you want. If you break a rule, the genie doesn't just deny the wish—the genie is allowed to rewrite history, steal your house, or do literally anything else.

![How a compiler optimizes away a null check by assuming Undefined Behavior (NULL dereference) never happens.](assets/s19_optimized_check.png)

**Example**:
```c
#include <stddef.h>

int process(int *ptr) {
    int value = *ptr;        // 1. Dereference
    if (ptr == NULL) {       // 2. Check
        return -1;
    }
    return value * 2;
}
```

**Plain English**: You might think passing `NULL` to this function crashes on line 1, or perhaps survives and safely returns `-1`. In reality, reading from a `NULL` pointer is Undefined Behavior. The compiler looks at line 1 and thinks, "Because this program is valid C, `ptr` *cannot* be `NULL` here." It then looks at line 2 and deduces, "Since `ptr` is definitely not `NULL`, this `if` statement is always false." The compiler deletes your safety check entirely. The UB on line 1 "time-travels" backward to break the logic on line 2.

**Technical Statement**: The C Standard states that when a program invokes undefined behavior, "this International Standard imposes no requirements" [1]. This absolute freedom is the origin of the "nasal demons" joke from early compiler newsgroups: a C compiler is strictly conforming even if UB causes demons to fly out of your nose.

**Why here?** The C language was designed for operating systems and embedded hardware where checking boundaries costs precious CPU cycles. C assumes the programmer is infallible.
**Alternative rejected:** Mandating runtime trapping (crashing predictably with an exception) like Java or Python does. 

```{=typst}
#trap[
```

The "works on my machine" fallacy. A beginner observes that accessing an array out of bounds simply prints a nearby variable's value and assumes UB just means "unpredictable memory." No. It means the compiler can unravel your program's logic entirely based on the assumption you wouldn't write UB.

```{=typst}
]
```

*Question to sit with*: If UB can silently manifest as working code today, how can you ever trust a test suite that only checks outputs?

*This breaks when*: You change compiler versions or optimization levels. Code that "worked fine" for ten years on `-O0` will instantly break on a modern compiler with `-O3`.

## 19.3 The Catalog of Common UB

UB lurks behind seemingly innocent syntax. Here is a definitive catalog of the traps.

![Taxonomy of common Undefined Behavior sources in C.](assets/s19_ub_taxonomy.png)

* **Signed integer overflow**: `int a = INT_MAX; a += 1;`
  Unlike unsigned integers which predictably wrap around, signed overflow is UB. Hardware differs on how signed numbers are represented, so C left it undefined. **To avoid:** Check limits *before* arithmetic.
* **Out-of-bounds array/pointer access**: `int arr[5]; arr[5] = 1;`
  Reading or writing past the allocated boundary destroys memory integrity. **To avoid:** Always pass explicit length bounds alongside arrays.
* **Use-after-free, double-free, and dangling pointers**: `free(p); *p = 5;`
  Writing to memory returned to the allocator corrupts heap structures. **To avoid:** Immediately set pointers to `NULL` after freeing.
* **NULL dereference**: `int *p = NULL; *p = 5;`
  Attempting to read or write address 0. **To avoid:** Validate pointers before use.
* **Reading an uninitialized variable**: `int x; printf("%d", x);`
  Local variables with automatic storage duration contain indeterminate values. Reading them is often immediate UB (e.g., if their address is never taken or they form a trap representation). **To avoid:** Initialize at declaration (`int x = 0;`).
* **Strict aliasing violations / Bad type punning**: `float f = 3.14f; int i = *(int*)&f;`
  Accessing a `float` as if it were an `int` through a pointer cast violates strict aliasing. **To avoid:** Use `memcpy` or a `union`.
* **Data races**: Two threads modifying the same memory location without synchronization. **To avoid:** Use mutexes or `<stdatomic.h>`.
* **Unsequenced modification**: `i = i++;` or `arr[i] = i++;`
  The standard states the side effect on `i` is unsequenced relative to its value computation [3]. The behavior is undefined. **To avoid:** Place exactly one modification of a variable per statement.
* **Invalid bitwise shifting**: `1 << 32` (on a 32-bit `int`) or `1 << -1`.
  Shifting by a negative amount, or by an amount greater than or equal to the bit-width of the type, is UB. **To avoid:** Mask shift amounts.
* **Division by zero and `INT_MIN / -1`**:
  Dividing by zero is obviously fatal, but `INT_MIN / -1` is also UB because `INT_MAX` is exactly one less than the absolute value of `INT_MIN` in two's complement, causing an overflow. **To avoid:** Check divisor limits.
* **Out-of-bounds pointer arithmetic**: `int *p = arr + 10;` (if `arr` has 5 elements).
  Even if you never dereference `p`, simply *calculating* a pointer more than one element past the end of an array is UB. **To avoid:** Calculate sizes carefully.
* **Misaligned access**: Casting a `char *` on an odd address to an `int *` and dereferencing it. Some CPUs crash immediately on misaligned loads. **To avoid:** Use `memcpy`.
* **Modifying a string literal**: `char *s = "hello"; s[0] = 'H';`
  String literals are often placed in read-only memory (ROM or `.rodata`). **To avoid:** Use an array: `char s[] = "hello";`.
* **Calling through an incompatible function pointer**: `void (*f)(int) = (void(*)(int))some_float_func; f(5);`
  The Calling Convention dictates how registers are set up. Mismatched signatures corrupt the stack. **To avoid:** Match signatures exactly.

## 19.4 How Compilers EXPLOIT UB

```{=typst}
#heavy[
```

Dense — slow down: Modern compilers are not just translators; they are mathematical proof engines. When the C Standard says "X is UB", the compiler introduces a rigorous algebraic axiom: "X is mathematically impossible." It then solves for the fastest assembly that satisfies this reality.

```{=typst}
]
```

**Analogy**: Think of a GPS navigator that assumes you will never drive off a cliff. If a certain road inevitably leads to a cliff, the GPS immediately prunes that entire route from its search space to calculate your path faster.

![How the compiler exploits restrict and UB to vectorize loops, replacing scalar operations with SIMD instructions.](assets/s19_vectorize.png)

**Example**:
```c
void process_array(int * restrict dest, int * restrict src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i] * 2;
    }
}
```

**Plain English**: The `restrict` keyword promises the compiler that `dest` and `src` will never overlap (violating this is UB). Because the compiler assumes you never invoke UB, it drops all internal checks about memory overlap. Furthermore, it knows `i` is a signed `int`. Since signed overflow is UB, it assumes `i` will strictly count up to `n` without wrapping. Armed with these proofs, it vectorizes the loop, safely processing 4 or 8 integers simultaneously using SIMD instructions.

**Technical Statement**: Compilers exploit UB for optimizations like Value Range Propagation (VRP) and Alias Analysis [2]. If an operation would cause UB for certain variable states, the compiler mathematically intersects the variable's possible range with the "safe" range, allowing it to prove branches unreachable and eliminate dead code.

**Why here?** Extreme execution speed.
**Alternative rejected:** Disabling aggressive optimizations to preserve the programmer's explicit bounds checks.

```{=typst}
#trap[
```

Thinking the compiler is "malicious." The compiler does not know what you intended; it only knows the algebraic rules you gave it. When it deletes a check, it is genuinely trying to make your code run faster by removing a branch it proved impossible.

```{=typst}
]
```

*Question to sit with*: Is a language truly "safe" if its optimizer actively exploits your mistakes?

*This breaks when*: You write safety checks *after* an operation that might cause UB.

## 19.5 Implementation-Defined & Unspecified Behavior

While UB invalidates your program, implementation-defined and unspecified behaviors just hurt portability. 

* **`int` size**: Could be 16-bit, 32-bit, or 64-bit.
* **`char` signedness**: `char c = 200;` might be positive or negative depending on the compiler's default.
* **Struct padding**: The compiler inserts hidden bytes between struct members for alignment.
* **Right-shift of negatives**: `(-4) >> 1` might preserve the sign bit (arithmetic shift) or fill with zero (logical shift).

**Portable-code discipline**: Never rely on these behaviors. Use `<stdint.h>` types (like `int32_t` and `uint8_t`) to guarantee size, always use `sizeof()` instead of hardcoding padding offsets, and use `unsigned` types for bitwise operations.

## 19.6 Catching UB

Because the compiler won't stop you from writing UB, you must rely on tooling:

1. **Sanitizers**: Compile with `-fsanitize=undefined` (UBSan) and `-fsanitize=address` (ASan). These inject runtime checks into your binary. They are the single most powerful tool for a C programmer.
2. **Valgrind**: A heavy-duty memory debugger that catches use-after-free and leaks without recompiling, though it runs slowly.
3. **Compiler Warnings**: Always compile with `-Wall -Wextra -Wpedantic`. 
4. **Static Analyzers**: Tools like `clang-tidy` and `cppcheck` read your source code to mathematically prove the presence of UB before you even compile.
5. **Defensive Idioms**: Use `assert()` liberally to document your assumptions, and always compute limits safely.

## 19.7 Worked-Example Zone

### Worked Example: The Optimized-Away Check

**The Bug:**
```c
int check_distance(int dist) {
    // Intended to check for overflow
    if (dist + 100 < dist) { 
        return -1;
    }
    return 1;
}
```

**The Trace:**
1. The programmer wants to ensure adding `100` to `dist` doesn't wrap around.
2. The compiler sees `dist + 100 < dist`.
3. Mathematically, $x + 100 < x$ is true *only* if an overflow occurs.
4. Signed integer overflow is Undefined Behavior.
5. The compiler explicitly assumes UB never happens, meaning `dist + 100` cannot overflow.
6. Therefore, the compiler deduces `dist + 100 < dist` must logically be `false`.
7. The compiler deletes the entire `if` block, optimizing the function to a single unconditional `return 1;`.

**The Fix:**
Check the limit *before* doing the arithmetic using subtraction:
```c
#include <limits.h>

int check_distance(int dist) {
    if (dist > INT_MAX - 100) { 
        return -1;
    }
    return 1;
}
```

### Worked Example: Strict Aliasing Bug

**The Bug:**
```c
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void demo_aliasing_bug(void) {
    float f = 3.14159f;
    uint32_t *bits = (uint32_t *)&f;
    printf("%" PRIx32 "\n", *bits);
}
```
Reading a `float` through a `uint32_t` pointer violates strict aliasing [4]. The optimizer is allowed to assume that an integer pointer and a float pointer never touch the same memory, potentially reordering reads and writes maliciously.

```{=typst}
#interview[
```

**Q:** How do you safely interpret the raw bits of a float as an integer in C?

**A:** Never use pointer casting (`*(int*)&f`), as it violates strict aliasing. Instead, use `memcpy` to copy the bytes into an integer variable, or use a `union` (valid in C99 and later). Modern compilers recognize the `memcpy` idiom and optimize it into a direct register move with zero overhead.

```{=typst}
]
```

**The Fix:**
```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

void demo_aliasing_fix(void) {
    float f = 3.14159f;
    uint32_t bits;
    memcpy(&bits, &f, sizeof(bits)); // The compiler optimizes this perfectly
    printf("%" PRIx32 "\n", bits);
}
```

### Faded Example: Safe Bounds Checking

We want to check if a requested slice of memory (`base + len`) fits safely within our buffer size `LIMIT`. We are using `unsigned int`, which is well-defined to wrap around, but we still want to prevent the wrap to ensure bounds safety.

```c
#include <stdbool.h>

bool is_valid_range(unsigned int base, unsigned int len, unsigned int LIMIT) {
    // We cannot do: if (base + len > LIMIT) because base + len might wrap to 0.
    
    // Step 1: Ensure the requested length itself isn't completely bogus.
    if (len > LIMIT) {
        return false;
    }
    
    // Step 2: Rearrange the check to use subtraction.
    // Because of Step 1, we know (LIMIT - len) will not underflow.
    if (base > /* ??? (Fill in the missing check) */) {
        return false;
    }
    
    return true;
}
```

### References

* [1] ISO/IEC 9899:2011 (C11 Standard), §3.4.3 — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
* [2] What Every C Programmer Should Know About Undefined Behavior — LLVM Blog — https://blog.llvm.org/2011/05/what-every-c-programmer-should-know.html
* [3] ISO/IEC 9899:2011 (C11 Standard), §6.5 Expressions — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
* [4] Understanding Strict Aliasing — CellPerformance — https://web.archive.org/web/20060718024925/http://cellperformance.beyond3d.com/articles/2006/06/understanding-strict-aliasing.html
