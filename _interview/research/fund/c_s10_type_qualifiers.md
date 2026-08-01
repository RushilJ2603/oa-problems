# 10. Type Qualifiers & Specifiers

Type qualifiers and specifiers are metadata you attach to C declarations. They do not typically change how data is fundamentally represented in memory; instead, they change the *contract* between you and the compiler. They dictate what the compiler is allowed to do—and what it is forbidden from doing—when it optimizes your code. 

## The `const` Qualifier: Promises and Placement

The `const` qualifier declares that an object's value will not be modified after initialization. It is the foundation of *const-correctness*, a discipline where functions explicitly advertise whether they modify the data you pass them.

### Const-Correctness as a Contract

When a function takes a pointer to `const` data, it makes a binding promise to the caller: "I will read from this pointer, but I will not write to it." 

```c
// Promises not to modify the string 'src'
size_t strlen(const char *src);

// Promises not to modify 'src', but will modify 'dest'
char *strcpy(char * restrict dest, const char * restrict src);
```

If you attempt to write to `src` inside `strlen`, the compiler will emit an error. This prevents accidental mutations and allows callers to safely pass read-only data.

### The Four Pointer Combinations

As covered in Section 4, reading C declarations with pointers requires the "right-left rule" (read from the identifier, look right, then look left). The position of `const` relative to the asterisk `*` completely changes its meaning [1].

1. **Pointer to mutable data:** `int *p;` (Both pointer and data can change).
2. **Pointer to constant data:** `const int *p;` or `int const *p;` (The pointer can point elsewhere, but the integer it points to cannot be changed through `p`).
3. **Constant pointer to mutable data:** `int * const p;` (The pointer is locked to one address, but the integer there can be changed).
4. **Constant pointer to constant data:** `const int * const p;` (Neither the address nor the data can change).

### Where `const` Data Lives

If you declare a global or `static` variable as `const`, the compiler and linker will typically place it in a read-only memory segment of the executable (often called `.rodata` in ELF binaries). 

```{=typst}
#trap[
```

Casting away `const` is a dangerous game. If an object was *originally defined* as `const` (like a string literal or a `const` global), and you use a cast to remove the `const` qualifier and modify it, the behavior is undefined (UB) [2]. The program might crash with a segmentation fault because the operating system enforces the read-only memory protection.

```{=typst}
]
```

## `volatile`: The "Do Not Optimize" Qualifier

```{=typst}
#heavy[
```

Dense — slow down: The C compiler's optimizer assumes it is the only entity interacting with memory. `volatile` breaks this assumption, requiring you to think about external hardware and asynchronous events.

```{=typst}
]
```

To understand `volatile`, you first have to understand what the compiler normally does. Modern compilers aggressively optimize code. If you read a variable in a loop, the compiler will fetch it from memory *once*, store it in a fast CPU register, and just read the register repeatedly. If you write to a variable and immediately write to it again, the compiler will delete the first write.

This is perfect for normal variables. But what if the memory isn't normal? 

**Analogy:** Imagine you are a clerk (the CPU) tasked with checking a thermometer reading written on a whiteboard in the next room (memory). If you check it once and it says 72°, and you know *you* haven't changed it, you might just sit at your desk and assume it's still 72° (caching in a register). But what if a weather sensor (hardware) is constantly updating that whiteboard? You *must* walk to the room and read the board every single time you are asked. 

![Compiler caching vs Volatile memory access](assets/s10_volatile.png)

```c
// Example: Polling a memory-mapped hardware status register
volatile uint32_t *timer = (volatile uint32_t *)0x40001000;

// The compiler MUST emit a fresh read instruction for every loop iteration
while (*timer == 0) {
    // Wait for the hardware to change the value
}
```

By marking the pointer's target as `volatile`, you are explicitly stating: **"This object can be modified by something outside the known flow of control. Do not cache it, do not elide reads, and do not reorder accesses to it."** 

Formally, the C standard guarantees that every read and write to a `volatile` object in the abstract machine corresponds to a physical read or write in the actual execution environment. It forces the compiler to respect the exact sequence of memory accesses written in your code.

### When `volatile` is Required

1.  **Memory-Mapped Hardware Registers:** In embedded systems (§15), hardware peripherals (like UARTs or GPIO pins) are controlled by reading and writing to specific memory addresses. A status register might change independently of the CPU.
2.  **Variables Modified by an Interrupt Service Routine (ISR):** If an interrupt fires (§16), suspends the main loop, changes a global variable, and returns, the main loop won't see the change unless the variable is `volatile`.
3.  **Signal Handlers:** Variables of type `sig_atomic_t` modified in a signal handler must also be `volatile` [3].

```{=typst}
#trap[
```

**The Concurrency Myth.** `volatile` is NOT atomic, and it is NOT a memory barrier. It does not prevent multiple threads from simultaneously writing to the same variable (a data race), nor does it prevent the CPU hardware itself from reordering instructions. Do not use `volatile` for thread synchronization; use `_Atomic` or mutexes.

```{=typst}
]
```

### Combining `const` and `volatile`

Can something be both `const` and `volatile`? Yes! It sounds contradictory until you consider a hardware status register (like a button state or a timer counter). 

- `volatile`: The hardware changes it, so the compiler must re-read it every time.
- `const`: The C program is not allowed to write to it (it is a read-only hardware register).

```c
// Pointer to a hardware register that the CPU can only read, 
// but the hardware can change at any time.
const volatile uint32_t *timer_register = (const volatile uint32_t *)0x40001000;
```

## `restrict`: The Anti-Aliasing Promise

```{=typst}
#heavy[
```

Dense — slow down: `restrict` is a bold promise you make to the optimizer about pointers. If you lie, the compiler will confidently generate broken code.

```{=typst}
]
```

Introduced in C99, `restrict` is an optimization hint. Two pointers are said to *alias* if they point to overlapping regions of memory. Aliasing is the optimizer's worst enemy.

**Analogy:** Imagine you hire two editors to proofread two different chapters of a book. If you give them separate chapters, they can work simultaneously (optimized). But if you accidentally give them overlapping pages (aliasing), one editor might overwrite the other's corrections. To be safe, they have to coordinate every single change (unoptimized).

![Aliased pointers vs Restricted pointers](assets/s10_restrict.png)

```c
// Example: The standard library copy functions
// Promises that 'dest' and 'src' do not overlap.
// Can use highly optimized vector instructions.
void *memcpy(void * restrict dest, const void * restrict src, size_t n);

// Makes no restrict promise. Safe for overlapping memory, 
// but potentially slower.
void *memmove(void *dest, const void *src, size_t n);
```

If a function takes two pointers, the compiler must pessimistically assume they *might* alias. Therefore, it has to write intermediate results back to memory constantly, just in case the other pointer needs to read them.

By adding `restrict` to a pointer declaration, you promise: **"For the lifetime of this pointer, the memory it points to will be accessed *only* through this pointer (or pointers derived from it)."** 

Formally, during the block in which the `restrict` pointer is declared, if the object it points to is modified in any way, then all accesses to that object must occur through that `restrict` pointer. If you pass overlapping buffers to `memcpy` (breaking the promise), it results in undefined behavior [4]. The compiler might have vectorized the loop assuming non-overlapping memory, leading to data corruption.

## `_Atomic` vs `volatile` (C11)

C11 introduced the `_Atomic` type specifier. It is crucial to understand how it differs from `volatile`.
- `volatile` guarantees **visibility** to the hardware/ISRs by preventing compiler caching. It does *not* prevent a thread from being preempted halfway through an update.
- `_Atomic` guarantees **atomicity** and memory ordering for multi-threading. An `_Atomic` operation completes entirely or not at all, safely coordinating between CPU cores. 

If you are communicating with hardware or an interrupt, use `volatile`. If you are communicating between OS threads (§18), use `_Atomic` [5].

## Other Specifiers (A Brief Survey)

-   `inline`: A hint (not a command) to the compiler to substitute the function's body directly at the call site, avoiding the overhead of a function call.
-   `_Noreturn` (C11): Indicates a function will never return to its caller (e.g., `exit()` or an infinite loop). 
-   `register`: A legacy hint suggesting a variable be kept in a CPU register. Modern compilers ignore this for optimization but will enforce that you cannot take the address (`&`) of a `register` variable.
-   `_Alignas` (C11): Forces a variable or type to have a specific memory alignment boundary (e.g., aligning a buffer to 32 bytes for SIMD instructions).
-   `static` in array parameters (C99): Writing `void foo(int arr[static 10])` promises the compiler that `arr` points to at least 10 integers and is not NULL.
-   `typedef`: Technically classified as a storage-class specifier, it creates an alias for an existing type, not a new type.

```{=typst}
#interview[
```

**Q: What does `volatile` do, and is it enough to protect data shared between threads?**  
A: `volatile` tells the compiler not to optimize away or reorder memory accesses to a variable, ensuring every read/write hits actual memory. It is required for memory-mapped I/O and ISRs. However, it is *not* enough for threads because it provides no hardware atomicity (a read-modify-write can still be interrupted) and no memory barrier against CPU reordering. Thread sharing requires mutexes or atomics.

```{=typst}
]
```

## Worked Examples

### 1. Traced: The Polling Loop (Why `volatile` matters)

Consider a program waiting for a hardware flag to become `1`.

**Without `volatile`:**
```c
int hardware_flag = 0; // Not volatile!

void wait_for_hardware(void) {
    // Optimizer looks at this loop: "hardware_flag is 0. 
    // Nothing in this loop changes it. Therefore, it will always be 0."
    while (hardware_flag == 0) {
        // ... do nothing
    }
}
```
*Trace:* The compiler hoists the read out of the loop. It generates assembly equivalent to: `if (hardware_flag == 0) { while(1) {} }`. It becomes an infinite loop, completely ignoring the hardware.

**With `volatile`:**
```c
volatile int hardware_flag = 0;

void wait_for_hardware(void) {
    // Optimizer is forced to emit a load instruction 
    // on every single loop iteration.
    while (hardware_flag == 0) {
        // ... do nothing
    }
}
```
*Trace:* The CPU reads the physical memory address of `hardware_flag` every cycle. When the hardware changes it to 1, the loop terminates immediately.

### 2. A `const`-correct string search

```c
// 1. Returns a pointer to char, but cannot modify the 'haystack' data.
// 2. The 'needle' parameter is also read-only.
const char *find_substring(const char *haystack, const char *needle) {
    // Implementation can safely read both strings.
    // Returning a const char* ensures the caller can't accidentally 
    // modify the original haystack through the returned pointer.
    return haystack;
}
```

### 3. Faded Example: Memory-Mapped Register

Declare a pointer named `uart_rx` to an 8-bit memory-mapped receive register at address `0x4000C000`. The CPU can read received bytes from this register, but cannot write to it. The hardware updates it asynchronously.

```c
// Fill in the missing qualifiers
_____ _____ uint8_t *uart_rx = (const volatile uint8_t *)0x4000C000;
```

*(Solution: `const volatile` — `const` prevents C from writing, `volatile` forces C to read fresh.)*

### References

[1] ISO/IEC 9899:2011 (C11 Standard), Section 6.7.3 — N1570 Committee Draft — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[2] ISO/IEC 9899:2011 (C11 Standard), Section 6.7.3 (6) — N1570 Committee Draft — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[3] Defining Signal Handlers — GNU C Library Reference Manual — https://www.gnu.org/software/libc/manual/html_node/Defining-Handlers.html
[4] ISO/IEC 9899:2011 (C11 Standard), Section 7.24.2.1 — N1570 Committee Draft — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[5] Atomic operations library — Cppreference — https://en.cppreference.com/w/c/atomic
