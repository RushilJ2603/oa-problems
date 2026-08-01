# 20. Interview Craft & Classic Gotcha Questions

This section synthesizes the core concepts covered across the preceding chapters into the sharp, defensive posture required for technical interviews. The questions below represent the classic "gotchas" and conceptual probes used by both software and hardware teams. The goal here is not to learn new concepts, but to recognize how the foundational rules interact when pushed to their edges.

## Method and Meta: Driving the C Interview

A C interview differs from a general algorithmic interview. While you may still write a sorting algorithm or a graph traversal, the interviewer is equally interested in *how* you write it: whether you check for `NULL`, whether you leak memory, and if you understand the underlying bytes.

The software interviewer looks for memory safety, undefined behavior awareness, and robust API design. The hardware/embedded interviewer looks for interrupt-safety, bitwise fluency, and an understanding of volatile state and hardware boundaries.

**The Drive Strategy:**
1. **Clarify Constraints:** Ask about integer sizes (e.g., "Are we assuming a 32-bit `int`?"). Ask if standard library functions like `string.h` are allowed.
2. **Brute Force First:** Write the simple, safe version.
3. **Optimize & Refine:** Move to the clever bitwise or pointer-arithmetic solution only after securing a working baseline.
4. **Test Edge Cases:** Explicitly walk through empty arrays, `NULL` pointers, and maximum integer values.
5. **Call Out Undefined Behavior:** If a proposed shortcut relies on signed overflow or strict aliasing violations, name it and explain why you are rejecting it.

![The C interview topic taxonomy.](assets/s20_question_map.png)

## Software Interview Q&A

### Pointers and Arrays

```{=typst}
#interview[
```

**Q:** What is the difference between `*p++`, `(*p)++`, and `*(p++)`?

**A:**
- `*p++` (same as `*(p++)`): Dereferences the pointer `p` yielding the value it currently points to, and then increments the pointer itself to the next element. The post-increment `++` binds more tightly than the dereference `*`.
- `(*p)++`: Dereferences the pointer `p`, and then increments the *value* stored at that location.

**Trap:** Assuming `*p++` increments the value. This causes out-of-bounds reads instead of modifying the target.

```{=typst}
]
```

```{=typst}
#interview[
```

**Q:** How do you read the declarations `int *p[10]` and `int (*p)[10]`?

**A:** Use the "spiral rule" or precedence: `[]` binds tighter than `*`.
- `int *p[10]`: `p` is an array of 10 pointers to `int`.
- `int (*p)[10]`: The parentheses force `*` to bind first. `p` is a pointer to an array of 10 `int`s.

**Trap:** Treating a pointer to an array identically to a double pointer (`int **`). They have different pointer arithmetic scales.

```{=typst}
]
```

### Memory Management

```{=typst}
#interview[
```

**Q:** What is the difference between a dangling pointer and a memory leak?

**A:** A dangling pointer points to memory that has already been freed (or to a local variable that has gone out of scope). Using it is undefined behavior. A memory leak occurs when dynamically allocated memory is never freed, but the pointers to it are lost, making it impossible to reclaim until the process dies.

**Trap:** Thinking that `free(p)` sets `p` to `NULL`. It only returns the memory to the allocator; the pointer retains the stale address.

```{=typst}
]
```

```{=typst}
#interview[
```

**Q:** Why is returning a pointer to a local variable disastrous?

**A:** Local variables are allocated on the stack and destroyed when the function returns. Returning its address means giving the caller a pointer to stack memory that is now invalid and will be overwritten by the next function call.

**Trap:** Thinking it "sometimes works" because the memory hasn't been overwritten *yet*. It is always undefined behavior.

```{=typst}
]
```

### Strings

```{=typst}
#interview[
```

**Q:** What is the difference between `char *s = "hello"` and `char s[] = "hello"`?

**A:**
- `char *s = "hello";` allocates a read-only string literal in the data segment (typically `.rodata`) and points `s` to it. Attempting to modify it (`s[0] = 'H'`) causes a segmentation fault.
- `char s[] = "hello";` allocates a mutable array on the stack (or globally) and *copies* the string literal into it. It is perfectly safe to modify.

**Trap:** Passing `char *s = "hello"` to a string reversal function and crashing.

```{=typst}
]
```

```{=typst}
#interview[
```

**Q:** How do `strlen(s)` and `sizeof(s)` differ for `char s[10] = "hi";`?

**A:** `strlen(s)` counts characters up to (but not including) the null terminator, returning 2. `sizeof(s)` evaluates at compile time to the total allocated size of the array, returning 10.

**Trap:** Using `sizeof` on a decayed pointer inside a function (`void foo(char s[]) { ... sizeof(s) ... }`) expecting the string length or array size; it returns the size of the pointer itself.

```{=typst}
]
```

### Storage and Qualifiers

```{=typst}
#interview[
```

**Q:** What are the two distinct meanings of the `static` keyword?

**A:**
1. **Inside a function:** It changes the variable's *lifetime* to the duration of the program, preserving its value between calls, while keeping its scope local to the function.
2. **Outside a function (global level):** It changes the variable's or function's *linkage* to internal, restricting its visibility to the translation unit (the current file) and preventing naming collisions.

**Trap:** Confusing scope and lifetime, or forgetting the linkage aspect.

```{=typst}
]
```

```{=typst}
#interview[
```

**Q:** When should you use `const` vs `#define` vs `enum` for constants?

**A:**
- `const`: When you need a typed variable that cannot be modified, useful for function parameters (e.g., `const char *`) or scoped constants. It still occupies memory (usually).
- `#define`: For preprocessor textual substitution. It has no type and no scope (it ignores block boundaries).
- `enum`: For grouping related, named integer constants. They have type and scope, making them superior to `#define` for state machines.

**Trap:** Trying to use a `const int` as the size of a static array in older C standards (C89), where it is not considered a constant expression, whereas `#define` or `enum` work.

```{=typst}
]
```

### The Preprocessor

```{=typst}
#interview[
```

**Q:** What is the pitfall of `#define SQUARE(x) x * x`?

**A:** Textual substitution ignores order of operations. `SQUARE(1 + 2)` expands to `1 + 2 * 1 + 2`, which evaluates to `1 + 2 + 2 = 5`, not 9. The fix is aggressive parenthesization: `#define SQUARE(x) ((x) * (x))`. Furthermore, macros evaluate their arguments multiple times, so `SQUARE(i++)` expands to `((i++) * (i++))`, causing undefined behavior.

**Trap:** Thinking macros behave like function calls. Inline functions are vastly preferred for logic.

```{=typst}
]
```

### Representation and Bits

```{=typst}
#interview[
```

**Q:** How do you test if a non-zero unsigned integer is a power of two?

**A:** `(x & (x - 1)) == 0`. A power of two has exactly one bit set. Subtracting 1 flips that set bit and all bits to the right of it. Bitwise ANDing them together leaves 0.

**Trap:** Writing a loop that repeatedly divides by 2, showing a lack of bitwise intuition.

```{=typst}
]
```

```{=typst}
#interview[
```

**Q:** How can you detect endianness at runtime?

**A:** Treat an integer as an array of bytes.
```c
int num = 1;
char *byte = (char *)&num;
if (*byte == 1) { /* Little-endian */ }
```

**Trap:** Confusing bit-order with byte-order. Endianness only affects the layout of *bytes* in memory.

```{=typst}
]
```

### Structs and Unions

```{=typst}
#interview[
```

**Q:** Why might `sizeof(struct { char a; int b; })` be 8 instead of 5?

**A:** Padding. The compiler inserts 3 invisible padding bytes after `a` so that `b` sits on a 4-byte aligned memory address, which hardware requires for efficient (or even valid) access.

**Trap:** Assuming structs pack perfectly, leading to errors when serializing structs directly to a network socket or file.

```{=typst}
]
```

### Undefined Behavior

```{=typst}
#interview[
```

**Q:** Name three common examples of Undefined Behavior (UB).

**A:**
1. Dereferencing a NULL or uninitialized pointer.
2. Accessing an array out of bounds.
3. Signed integer overflow.

**Trap:** Believing UB just means "it crashes" or "it wraps around." UB means the compiler is allowed to assume the event never happens, aggressively optimizing away checks and generating entirely unpredictable code.

```{=typst}
]
```

## Hardware & Embedded Interview Q&A

This section represents the gauntlet for firmware, embedded systems, and OS kernel roles.

```{=typst}
#interview[
```

**Q:** What exactly does `volatile` do, and when is it required?

**A:** `volatile` tells the compiler that a variable's value may change at any time outside the knowledge of the current execution thread. It forbids the compiler from optimizing out reads (e.g., caching the value in a register) or writes. It is required for:
1. Memory-mapped hardware registers.
2. Global variables modified by an Interrupt Service Routine (ISR) and read by the main loop.

**Trap:** Using `volatile` to synchronize threads. It does *not* guarantee atomicity or prevent CPU cache reordering; it only stops compiler optimizations [1].

```{=typst}
]
```

```{=typst}
#interview[
```

**Q:** What is the read-modify-write atomicity hazard?

**A:** When modifying a shared variable (or register), an operation like `x |= 0x01` is actually three steps at the assembly level: Load into register, OR the bit, Store back to memory. If an interrupt fires between the Load and Store, and modifies `x`, the subsequent Store from the main loop will blindly overwrite the ISR's changes.

**Trap:** Assuming `x++` or bitwise operators are atomic on a 32-bit MCU. They almost never are. The fix is temporarily disabling interrupts around the access, or using atomic instructions.

```{=typst}
]
```

```{=typst}
#interview[
```

**Q:** Why can't you call `malloc` or `printf` inside an Interrupt Service Routine (ISR)?

**A:** Both are typically non-deterministic and heavily reliant on locks (mutexes). An ISR must be fast and deterministic. If the main loop was executing `printf` (holding its internal lock) when the interrupt fired, calling `printf` again in the ISR will cause a deadlock.

**Trap:** Using standard library I/O or dynamic allocation in real-time interrupt contexts.

```{=typst}
]
```

## Output-Prediction Puzzles

These are classic "what does this print?" snippets designed to test your mental model of the C abstract machine.

**Dense — slow down:** Multiple rules of evaluation order, promotion, and UB overlap in these snippets.

### Puzzle 1: The Size of a String

```c
#include <stdio.h>
void print_size(char arr[]) {
    printf("%zu\n", sizeof(arr));
}
int main(void) {
    char str[] = "Antigravity";
    print_size(str);
    return 0;
}
```

**Step-by-Step Trace:**
1. In `main`, `str` is an array of 12 chars (11 letters + `\0`).
2. We pass `str` to `print_size`.
3. Arrays passed to functions decay into pointers. The parameter `char arr[]` is perfectly synonymous with `char *arr`.
4. `sizeof(arr)` evaluates the size of a pointer (usually 8 bytes on a 64-bit system), not the original array.
**Answer:** It prints 8 (or 4 on a 32-bit system).

### Puzzle 2: Integer Promotion and Signs

```c
#include <stdio.h>
int main(void) {
    unsigned int a = 10;
    int b = -20;
    if (a + b > 10) {
        printf("Greater\n");
    } else {
        printf("Lesser\n");
    }
    return 0;
}
```

**Step-by-Step Trace:**
1. We are evaluating `a + b`. `a` is `unsigned int`, `b` is `int`.
2. The *usual arithmetic conversions* dictate that if an operation mixes signed and unsigned types of the same rank, the signed operand is implicitly cast to unsigned.
3. `-20` cast to `unsigned int` becomes a massive positive number (e.g., `4294967276` on 32-bit systems).
4. `10 + 4294967276` evaluates to `4294967286`, which is certainly far greater than 10.
**Answer:** It prints `Greater`.

### Puzzle 3: The Strict Aliasing Trap

```c
#include <stdio.h>
int main(void) {
    float f = 1.0f;
    unsigned int *p = (unsigned int *)&f;
    *p = 0x4048F5C3; 
    printf("%f\n", f);
    return 0;
}
```

**Step-by-Step Trace:**
1. We take the address of a `float` and cast it to an `unsigned int *`.
2. We dereference the `unsigned int *` to write a bit pattern.
3. We then read the `float` `f`.
4. This violates the *strict aliasing rule*, which states that you cannot access an object of one type through a pointer to a fundamentally different type (with the exception of `char *`).
**Answer:** Undefined Behavior. The compiler is allowed to assume `f` was never modified by `*p` and might print `1.000000` (optimizing away the write) or output the new float value. It is invalid C. To do this safely, use `memcpy` or a `union` (in C99+).

### Faded Puzzle: Predict the Output

Read the following snippet and predict the output. Identify the specific rule that governs this behavior [2].

```c
#include <stdio.h>
int main(void) {
    int i = 5;
    i = i++ + 1;
    printf("%d\n", i);
    return 0;
}
```

*Self-check:* The output is not predictable. Modifying a variable (`i++`) and then modifying it again (`i = ...`) without an intervening sequence point is Undefined Behavior.

## References

[1] ISO/IEC 9899:2011 (C11) — §6.7.3 Type qualifiers, semantics of volatile — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[2] "Deep C (and C++)" — Olve Maudal and Jon Jagger — https://www.slideshare.net/olvemaudal/deep-c
