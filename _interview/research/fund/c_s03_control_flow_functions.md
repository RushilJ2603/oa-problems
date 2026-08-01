# 3. Control Flow & Functions

Control flow directs the execution path of a program, while functions organize that logic into reusable blocks. 

## Conditionals

Conditionals allow a program to branch its execution based on runtime values, which is essential for making decisions.

### `if` and `else`

An `if` statement evaluates an expression and executes a block if the result is non-zero (true); the `else` clause provides the fallback. This matters because it is the fundamental building block of all program logic.

```c
if (score >= 90) {
    puts("A");
} else if (score >= 80) {
    puts("B");
} else {
    puts("C");
}
```

```{=typst}
#trap[
```

A common mistake is using `=` (assignment) instead of `==` (equality) in a condition: `if (x = 5)`. This assigns 5 to `x` and evaluates to 5 (true), always executing the block. Modern compilers warn about this if you enable `-Wall`.

```{=typst}
]
```

This breaks when you need to match against dozens of distinct constant values; a massive `if`-chain becomes an unreadable, slow $O(N)$ bottleneck.

### `switch` Statements

A `switch` statement evaluates an integer expression and jumps directly to a matching `case` label [1]. This matters because it provides a cleaner, faster alternative to long `if`-chains when comparing against discrete constants.

```c
switch (status_code) {
    case 200:
        puts("OK");
        break;
    case 404:
        puts("Not Found");
        break;
    default:
        puts("Unknown error");
        break;
}
```

When `case` labels are dense (contiguous or close in value), compilers like GCC and Clang generate a **jump table**. A jump table is an array of memory addresses mapping to code blocks. Instead of evaluating conditions one by one, the program uses the `switch` expression as an index to jump directly to the correct block in $O(1)$ time. 

```{=typst}
#trap[
```

**Fallthrough:** Unlike many languages, C does not automatically exit a `switch` block after a `case` finishes. If you omit the `break;`, execution *falls through* to the next case. 

```{=typst}
]
```

This breaks when you need to match strings, floating-point numbers, or dynamic ranges; `switch` strictly requires compile-time integer constants.

## Loops

Loops repeatedly execute a block of code, which is vital for processing arrays, reading files, or waiting for events.

### `while` and `do-while`

A `while` loop checks a condition before each iteration, meaning it might never run. A `do-while` loop evaluates the condition after the iteration, guaranteeing at least one execution. This matters when deciding if an initial state check is necessary.

```c
while (bytes_read > 0) {
    process(buffer);
}

do {
    prompt_user();
} while (input_invalid);
```

This breaks when the loop condition relies on an external hardware register without the `volatile` keyword, leading the compiler to optimize the check away and loop infinitely.

### `for` Loops

A `for` loop consolidates initialization, condition testing, and advancement into a single line. This matters because it tightly groups all loop control logic, making it ideal for counting and array traversal.

```c
for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
}
```

```{=typst}
#trap[
```

**Off-by-one errors:** Looping `i <= 10` instead of `i < 10` when processing an array of size 10 reads out of bounds, invoking undefined behavior. Valid zero-based indices are 0 through 9.

```{=typst}
]
```

**The Comma Operator:** You can pack multiple initializations or advancements into a `for` loop using the comma operator, which evaluates its left operand, discards the result, and evaluates the right.

```c
for (int i = 0, j = 10; i < j; i++, j--) {
    // Both i and j update each iteration
}
```

**Infinite Loops:** The standard idiom for a deliberate infinite loop (e.g., in event servers) is `for (;;)` or `while (1)`.

This breaks when you manipulate the loop counter `i` unexpectedly inside the loop body, causing skipped elements or infinite cycles.

### `break` and `continue`

The `break` keyword instantly terminates the innermost enclosing loop or `switch`, while `continue` skips the rest of the loop body and jumps straight to the next iteration's evaluation. This matters for cleanly exiting early without convoluted nested `if`s. 

This breaks when you assume `break` will exit multiple nested loops; it only ever escapes the single deepest enclosing loop.

## `goto` and Labels

The `goto` statement jumps unconditionally to a named label within the same function. While universally discouraged for general logic, it remains a standard, legitimate C idiom for centralized error cleanup and unwinding, especially since C lacks exceptions.

```c
    FILE *f1 = fopen("a.txt", "r");
    if (!f1) goto error_f1;

    FILE *f2 = fopen("b.txt", "r");
    if (!f2) goto error_f2;

    // ... work ...

    fclose(f2);
    fclose(f1);
    return 0;

error_f2:
    fclose(f1);
error_f1:
    return -1;
```

This breaks when used to jump backward or across complex control structures, quickly degrading the program into impossible-to-follow spaghetti code.

## Functions

Functions encapsulate logic into named, callable units. A function **prototype** (declaration) announces the function's name, return type, and parameters to the compiler, while the **definition** provides the actual code. This matters because it allows modular code and separate compilation. A return type of `void` means nothing is returned, and `(void)` means no parameters are accepted.

```{=typst}
#heavy[
```

Dense — slow down: C exclusively uses pass-by-value for function arguments.

```{=typst}
]
```

Think of a function call like emailing a coworker a document. If you email them a copy, any edits they make do not affect your original file. If you want them to modify your document, you must send them a link to the shared file (a pointer).

![Pass-by-value vs Pointers](assets/s03_byvalue.png)

Let's look at an attempt to swap two variables before diving into the rules:

```c
void broken_swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}
```

When you call `broken_swap(x, y)`, C copies the *values* of `x` and `y` into the function's own isolated containers `a` and `b`. The function successfully swaps its own containers, but the original variables `x` and `y` in the caller remain completely unchanged.

In C, **everything is passed by value** [2]. A function parameter is simply a new local variable initialized with a copy of the caller's argument expression. C has no built-in "pass-by-reference" feature like C++ references.

```{=typst}
#trap[
```

A beginner's mental model is often that passing `x` to a parameter named `x` links them together. They are completely separate variables that happen to share a name and an initial value.

```{=typst}
]
```

To simulate "pass-by-reference" and mutate a caller's variable, you must pass a pointer (a memory address). The address itself is copied (passed by value), but the callee can use that copied address to reach back and modify the original data. 

This breaks when you forget the pointer syntax and accidentally pass the value—the compiler might complain, or you might just silently mutate a discarded copy.

Question to sit with: If a function only receives copies of its arguments, how does `scanf` manage to modify the variables you pass to it?

```{=typst}
#interview[
```

**Interviewer:** "Does C support pass-by-reference?"
**Answer:** "No, C is strictly pass-by-value. To modify a variable in a caller's scope, we simulate pass-by-reference by passing a pointer to the variable by value."

```{=typst}
]
```

## The Call Stack

When a function is called, the program suspends the caller and allocates a new block of memory called a **stack frame** to support the callee. This matters because it is the fundamental mechanism that allows functions to pause, call other functions, and resume exactly where they left off.

![The Call Stack](assets/s03_callstack.png)

A stack frame contains:
1. **Parameters:** The copied argument values.
2. **Local Variables:** Variables declared inside the function.
3. **Return Address:** Where execution should resume once the function finishes.

When the function returns, its stack frame is popped off the stack and destroyed, ending the **automatic lifetime** of its local variables.

```{=typst}
#trap[
```

**Dangling Pointers:** Never return a pointer to a local variable. Once the function returns, its stack frame is destroyed. The returned pointer now points to invalid, reclaimed memory (it is dangling). Dereferencing it is undefined behavior.

```{=typst}
]
```

This breaks when you allocate massive arrays as local variables, overflowing the limited stack memory and crashing the program.

## Recursion

A function can call itself, a technique known as recursion. Every recursive function requires a base case to halt, and a recursive step that moves toward that base case. This matters because it provides an elegant way to traverse tree-like data structures.

Because each function call pushes a new stack frame, deep recursion rapidly consumes stack space. While iterative solutions (loops) use less memory, recursive logic is often cleaner. Some compilers optimize **tail recursion** (where the recursive call is the absolute final operation) into a loop to save frames, but C does not guarantee this.

This breaks when the recursion goes too deep without hitting a base case, exhausting the call stack and causing a stack overflow crash.

## `main` Signatures

The `main` function is the mandated entry point of a C program. It commonly has two standard signatures: `int main(void)` when ignoring command-line arguments, and `int main(int argc, char **argv)` when accepting them. `argc` is the argument count, and `argv` is an array of string pointers where `argv[0]` is the program name. This matters because it bridges the operating system shell and your C code.

This breaks when you declare `main` with a `void` return type; the returned integer acts as the exit status (0 for success, non-zero for failure) handed back to the OS.

## Variadic Functions

Functions like `printf` can accept a variable number of arguments by using an ellipsis (`...`) and the `<stdarg.h>` library (`va_list`, `va_start`, `va_arg`, `va_end`). This matters for creating flexible formatting and logging utilities.

```c
#include <stdarg.h>
#include <stdio.h>

void print_ints(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        printf("%d ", va_arg(args, int));
    }
    va_end(args);
}
```

This breaks when you pass fewer arguments than the function expects, or of the wrong type. Variadic functions in C are completely **type-unsafe** [3]; `va_arg` blindly interprets the next chunk of memory as the requested type, leading to undefined behavior if mismatched.

## `inline` Functions

The `inline` keyword is a request to the compiler to inject the function's body directly into the caller's code to avoid the overhead of a function call. This matters for tiny, performance-critical, frequently called functions, offering macro-like speed with true function type-checking.

This breaks when the function relies on complex loops or recursion, or is too large, in which case the compiler will silently ignore the `inline` request and emit a normal function call.

## Function Pointers

Because functions reside in memory, a function pointer can store the address of a function. This matters because it allows you to pass functions as arguments to other functions, enabling dynamic callbacks (like a custom sorting comparator).

```c
#include <stdio.h>

void greet(void) { puts("Hello!"); }

int main(void) {
    void (*func_ptr)(void) = greet;
    func_ptr(); // Calls greet()
    return 0;
}
```

This breaks when the function pointer signature does not perfectly match the function being assigned to it, invoking undefined behavior upon execution.

## Worked Examples

### Traced Recursive Call: Factorial

Let's trace the execution of `factorial(3)` to see the stack in action.

```c
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

1. `factorial(3)` is called. A frame is pushed. It evaluates `n <= 1` (false). It needs to return `3 * factorial(2)`.
2. `factorial(2)` is called. A frame is pushed. It needs to return `2 * factorial(1)`.
3. `factorial(1)` is called. A frame is pushed. The base case `n <= 1` is true. It returns `1`.
4. `factorial(1)`'s frame pops. `factorial(2)` receives `1`, computes `2 * 1`, and returns `2`.
5. `factorial(2)`'s frame pops. `factorial(3)` receives `2`, computes `3 * 2`, and returns `6`.
6. `factorial(3)`'s frame pops. The final result is `6`.

### Faded Example: Fixing the Swap Function

Earlier, we saw that `broken_swap` failed because it only swapped its own local copies. Here is the framework to fix it by passing pointers. Complete the missing dereference in the final step.

```c
void swap(int *a, int *b) {
    // 1. Read the value at address 'a' into a temporary variable.
    int temp = *a;
    
    // 2. Write the value at address 'b' into the location at address 'a'.
    *a = *b;
    
    // 3. Write the temporary value into the location at address 'b'.
    // <Fill in the blank>
}

int main(void) {
    int x = 5, y = 10;
    swap(&x, &y); // Pass addresses instead of values
    return 0;
}
```

*Solution: The missing line is `*b = temp;`*

### References

[1] ISO/IEC 9899:2011 (C11) §6.8.4.2 — The `switch` statement semantics. — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[2] ISO/IEC 9899:2011 (C11) §6.5.2.2 — Function calls inherently evaluate and copy argument values. — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[3] ISO/IEC 9899:2011 (C11) §7.16 — Variable arguments lack native type safety. — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
