# 6. Memory Model & Storage Classes

Before we write code that manages memory dynamically, we must understand the physical and virtual reality our code lives in. At the hardware level, the Central Processing Unit (CPU) executes instructions, and Random Access Memory (RAM) acts as the workspace for both those instructions and the data they manipulate. Every byte in RAM has a unique numeric address. Modern operating systems provide each running program (process) with an illusion called *virtual memory*—a seamless, isolated address space where it appears to own all the memory, from address zero up to the architectural maximum.

But a C program does not simply dump its bytes randomly into this space. It organizes them meticulously.

## 6.1 The Process Memory Layout

```{=typst}
#heavy[
```

Dense — slow down: The abstract C standard avoids dictating physical layouts, but practically every desktop and embedded operating system maps C's conceptual memory onto a rigid physical blueprint. Understanding this blueprint is non-negotiable for debugging and reasoning about program state.

```{=typst}
]
```

Think of a process's memory as a heavily structured office building. You have the library for reference manuals (read-only), a lobby for public notices (globals), private desks for current tasks (locals), and a warehouse for custom-sized boxes (dynamic memory). Mixing them up—like putting a private task on the public notice board—causes chaos.

![Process Address Space](assets/s06_memory_map.png)

Let's look at a concrete example of how C data segregates into these regions:

```c
#include <stdio.h>
#include <stdlib.h>

int public_count = 100;      // Initialized data segment
int pending_flags;           // BSS segment (zero-initialized)

int main(void) {
    int local_temp = 5;      // Stack segment
    int *dynamic_arr = malloc(10 * sizeof(int)); // Heap segment
    
    // ...
    free(dynamic_arr);
    return 0;
}
```

When your operating system loads a compiled C executable, it typically partitions the virtual address space into five distinct segments:

1. **Text (Code) Segment**: This is where the compiled machine instructions live. It is typically marked **read-only** by the OS so a program cannot accidentally overwrite its own logic.
2. **Initialized Data Segment**: Often just called the "Data segment", this holds global and static variables that have an explicit, non-zero initial value in the source code (like `public_count`).
3. **BSS (Block Started by Symbol) Segment**: This historically named segment holds global and static variables that are uninitialized or explicitly initialized to zero (like `pending_flags`). Instead of storing thousands of zeroes in the executable file on disk, the system just records how much space is needed and zeroes it out in RAM when the program starts.
4. **The Heap**: A large pool of memory used for dynamic allocation. The heap typically starts above the BSS and grows *upward* toward higher memory addresses as you request more space.
5. **The Stack**: A scratchpad memory used for function calls and local variables (like `local_temp`). The stack typically starts at a high memory address and grows *downward* toward the heap.

Technically, the C standard never mentions "stack" or "heap". It only specifies *storage duration* [1]. However, every major compiler implements C's automatic variables using the hardware stack, and allocated variables using the heap.

```{=typst}
#trap[
```

String literals like `"Hello"` do not live on the stack or the heap. They are stored in read-only memory, typically within or adjacent to the Text segment. Attempting to modify a string literal (e.g., `char *s = "Hi"; s[0] = 'h';`) is Undefined Behavior and usually triggers a segmentation fault.

```{=typst}
]
```

**Question to sit with:** Why do the stack and heap grow towards each other from opposite ends of the available memory, rather than both growing upwards from the bottom?

## 6.2 Storage Duration and Lifetime

A variable's **lifetime** (or storage duration) dictates *when* a variable is created and when it is destroyed. The C standard defines four storage durations [1]:

1. **Automatic**: The object exists only within the block (`{ ... }`) it was declared in. It is created when execution enters the block and destroyed when it exits. Local variables default to automatic duration.
2. **Static**: The object exists for the *entire execution* of the program. It is initialized exactly once, before program startup (`main()`) begins.
3. **Allocated**: The object is created and destroyed on demand by calling library functions (`malloc()` and `free()`). You have complete manual control over its lifetime.
4. **Thread**: Introduced in C11 (`_Thread_local`), the object exists for the lifetime of a specific execution thread.

## 6.3 Storage-Class Specifiers

C uses keywords called *storage-class specifiers* to alter a variable's default duration or linkage.

- `auto`: Explicitly marks a variable as having automatic duration. Since this is the default for local variables, `auto` is redundant and almost never written in modern C.
- `register`: A hint to the compiler to store the variable in a CPU register for speed rather than in RAM. Today, optimizing compilers are vastly better at register allocation than humans, making this keyword mostly obsolete. You cannot take the address (using `&`) of a `register` variable.
- `static`: Changes either the lifetime or the linkage, depending on where it is used (see Section 6.4).
- `extern`: Declares that a variable is defined *elsewhere* (usually in another file). It tells the compiler, "Trust me, this exists, let the linker find it later."

## 6.4 The Dual Meaning of `static`

```{=typst}
#heavy[
```

Dense — slow down: The `static` keyword in C is notoriously overloaded. It performs two completely different jobs depending on whether you place it outside a function or inside a function.

```{=typst}
]
```

Imagine a locked safe. If you put the safe in a public lobby, anyone in the building can see it, but they need a key to open it (Internal Linkage). If you put the safe in your private office, only you know it exists, and whatever you leave in there today will still be there tomorrow (Static Lifetime).

![Block-scope static variable persisting across calls](assets/s06_static_local.png)

Let's look at this behavior in code:

```c
#include <stdio.h>

static int global_hidden = 100; // File-scope static (internal linkage)

void counter(void) {
    // Initialized ONCE. Retains its value across calls.
    static int calls = 0; 
    
    // Initialized EVERY time the function is called.
    int local = 0;        
    
    calls++;
    local++;
    printf("calls: %d, local: %d\n", calls, local);
}
```

What is happening here? The `static` keyword is performing two completely different tasks based on where it is placed.

**1. File-Scope `static` (Internal Linkage)**
When used on a global variable or function *outside* of any function block (like `global_hidden`), `static` means **internal linkage** [2]. It hides the variable or function from the rest of the program, making it strictly private to the `.c` file (translation unit) it is defined in.

**2. Block-Scope `static` (Static Lifetime)**
When used on a local variable *inside* a function (like `calls`), `static` changes its storage duration from automatic to **static**. The variable still has local *scope* (it can only be accessed by name inside that function), but its *lifetime* becomes the entire run of the program. It is initialized only once, and it retains its value between function calls.

```{=typst}
#trap[
```

A common trap is assuming `static` inside a function means "constant" or "unchangeable." It does not. It means "persistent." The variable can be freely modified, but its memory cell outlives the function return.

```{=typst}
]
```

*This breaks when...* you write multithreaded code. A block-scope `static` variable is shared among all threads calling that function, creating dangerous race conditions if not protected by a mutex.

## 6.5 Linkage and the One-Definition Rule

**Linkage** determines whether a name (identifier) declared in different scopes or different files refers to the *same* underlying object or function [2].

- **No Linkage**: The name belongs strictly to the block it is in. Local variables have no linkage.
- **Internal Linkage**: The name refers to the same object everywhere within a single `.c` file (translation unit), but is completely hidden from other files. Achieved using `static` at file scope.
- **External Linkage**: The name refers to the exact same object across the *entire program*. Global variables and normal functions have external linkage by default.

This brings us to the **One-Definition Rule (ODR)** concept. In C, you can *declare* a variable as many times as you want across multiple files, but you must *define* it exactly once.
- **Declaration**: Tells the compiler the type and name. (`extern int g;`)
- **Definition**: Tells the compiler to actually allocate memory. (`int g = 5;`)

To share a global variable across multiple translation units cleanly:
1. Put an `extern` declaration in a header file (`.h`).
2. Include that header everywhere you need the variable.
3. Put the actual definition (without `extern`) in exactly ONE `.c` file.

## 6.6 Scope vs. Lifetime

It is critical to untangle Scope from Lifetime:
- **Scope** is a spatial and lexical concept. It answers: *Where in the source code am I allowed to type this variable's name?*
- **Lifetime** is a temporal and execution concept. It answers: *During what period of the program's runtime does the memory for this variable exist?*

C has four types of scope [1]:
1. **Block Scope**: Variables declared inside `{ }`. Visible only until the closing `}`.
2. **File Scope**: Variables declared outside any function. Visible from the line of declaration to the end of the file.
3. **Function Scope**: Exclusively for `goto` labels, which are visible anywhere within the function they are defined.
4. **Function Prototype Scope**: Parameter names in a function declaration (e.g., the `x` in `void foo(int x);`). Visible only to the end of the prototype.

```{=typst}
#keypoint[
```

A variable can have local scope but static lifetime (like our block-scope `static` example), meaning the memory exists forever, but you can only refer to it by name while inside its corresponding function.

```{=typst}
]
```

## 6.7 Initialization Rules

The C standard dictates strict default initialization rules based on storage duration [3]:

- **Static and Thread duration objects**: If you do not provide an explicit initializer, they are automatically initialized to zero (or `NULL` for pointers).
- **Automatic and Allocated objects**: If you do not provide an explicit initializer, their value is **indeterminate**.

```{=typst}
#trap[
```

Reading an uninitialized automatic variable is UB-adjacent. If the variable's type could have a "trap representation" (an invalid bit pattern for that type), merely reading it is Undefined Behavior. Even if it does not trap, it holds garbage data left over on the stack from previous function calls. *Always* initialize your locals.

```{=typst}
]
```

## 6.8 Stack vs. Heap: Trade-offs

Choosing where to store your data is a core engineering decision.

**The Stack:**
- **Cost**: Extremely fast. Allocating memory is just moving a CPU register (the stack pointer) by a few bytes.
- **Lifetime**: Strictly bound to the function scope. Cleaned up automatically.
- **Limits**: Very small (often limited to 1MB to 8MB by the OS).
- **Failure Mode**: Allocating too much (e.g., massive arrays, infinite recursion) causes a **Stack Overflow**, immediately crashing the program.

**The Heap:**
- **Cost**: Slower. Requires calling `malloc()`, which involves internal bookkeeping and occasionally asking the OS for more pages.
- **Lifetime**: Manual. Persists indefinitely until you explicitly call `free()`.
- **Limits**: Massive. Limited only by available system RAM and virtual memory.
- **Failure Mode**: Forgetting to free causes a memory leak. Accessing memory after freeing it causes Undefined Behavior.

```{=typst}
#interview[
```

**Q:** Why is returning a pointer to a local variable a critical bug?

**A:** Because the variable lives on the stack. When the function returns, its stack frame is "popped" and invalidated. The returned pointer becomes a *dangling pointer*. The memory it points to will be overwritten by the very next function call the program makes. Reading from or writing to it is Undefined Behavior.

```{=typst}
]
```

---

## Worked Examples

### Traced Example: The Persistent Local
Let's trace a function with a block-scope `static` variable over three consecutive calls.

```c
#include <stdio.h>

void generate_id(void) {
    static int next_id = 100; // Initialization happens BEFORE main() runs
    int temp = 0;             // Initialization happens EVERY call
    
    printf("ID: %d (temp was %d)\n", next_id, temp);
    next_id++;
    temp++;
}

int main(void) {
    generate_id(); // Call 1
    generate_id(); // Call 2
    generate_id(); // Call 3
    return 0;
}
```

**Walkthrough:**
1. Before `main` even starts, the system allocates space for `next_id` in the Data segment and sets it to `100`.
2. **Call 1**: `temp` is created on the stack and set to `0`. The function prints `ID: 100 (temp was 0)`. `next_id` is incremented to `101`. The function returns, and `temp` is destroyed. `next_id` survives.
3. **Call 2**: `temp` is created anew on the stack and set to `0`. The function prints `ID: 101 (temp was 0)`. `next_id` is incremented to `102`. The function returns.
4. **Call 3**: `temp` is created again. The function prints `ID: 102 (temp was 0)`. The persistent state of `next_id` allows it to act as a stateful generator without exposing it globally.

### Two-File Example: Extern Linkage
How to share a variable across files cleanly without violating the One-Definition Rule.

`config.h` (The Declaration)
```c
#ifndef CONFIG_H
#define CONFIG_H

// DECLARATION: tells the compiler 'system_mode' exists elsewhere.
extern int system_mode; 

#endif
```

`config.c` (The Definition)
```c
#include "config.h"

// DEFINITION: actually allocates the memory. Present in exactly ONE .c file!
int system_mode = 1; 
```

`main.c` (The Usage)
```c
#include <stdio.h>
#include "config.h" // Includes the extern declaration

int main(void) {
    // Uses the global defined in config.c, linked later by the linker.
    printf("Mode: %d\n", system_mode); 
    return 0;
}
```

### Faded Example: Storage Classification
Classify the following variables based on their Scope, Storage Duration, and Linkage. Think through the first four, and complete the final classification yourself.

```c
#include <stdlib.h>

int alpha = 1;          // (1)
static int beta = 2;    // (2)

void func(void) {
    int gamma = 3;      // (3)
    static int delta = 4; // (4)
    int *epsilon = malloc(sizeof(int)); // (5)
}
```

- **(1) `alpha`**: File scope, Static duration, External linkage.
- **(2) `beta`**: File scope, Static duration, Internal linkage.
- **(3) `gamma`**: Block scope, Automatic duration, No linkage.
- **(4) `delta`**: Block scope, Static duration, No linkage.
- **(5) The allocated memory pointed to by `epsilon`**: ? 
  *(Answer: No scope—it has no name and can only be accessed via pointers; Allocated duration; No linkage)*

---

### References
[1] ISO/IEC 9899:2011 (C11 Standard) — §6.2.4 Storage durations of objects, §6.2.1 Scopes of identifiers — https://port70.net/~nsz/c/c11/n1570.html#6.2
[2] ISO/IEC 9899:2011 (C11 Standard) — §6.2.2 Linkages of identifiers — https://port70.net/~nsz/c/c11/n1570.html#6.2.2
[3] ISO/IEC 9899:2011 (C11 Standard) — §6.7.9 Initialization — https://port70.net/~nsz/c/c11/n1570.html#6.7.9
