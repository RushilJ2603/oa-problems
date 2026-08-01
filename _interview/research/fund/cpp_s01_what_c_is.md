# 1. What C Is & How It Runs

## 1.1 The C Philosophy

C is a small, fast, close-to-the-hardware systems language. It was designed in the early 1970s by Dennis Ritchie at Bell Labs to write the Unix operating system [2]. C provides minimal abstraction over the underlying machine architecture, trusting the programmer completely. Today, C still dominates where performance, determinism, and direct memory access are paramount: operating system kernels, embedded firmware, language interpreters, and hardware drivers.

## 1.2 The C Standards

C has evolved through a series of formal standards, starting from the informal "K&R C" to ANSI C (C89/C90), and then C99, C11, C17, and recently C23 [1]. 

```{=typst}
#interview[
```

**Interviewer:** "What standard of C do you typically target, and why does it matter?"

**Answer:** "I target C11 or C17 for broad compatibility, but leverage C99 as the baseline since it introduced `stdint.h` and inline declarations. It matters because newer standards introduce features (like variable-length arrays in C99, made optional in C11) that may not be supported by legacy or specialized embedded compilers."

```{=typst}
]
```

When you compile C, you can specify the standard version using a compiler flag like `-std=c17` or `-std=c23`. This dictates which language features and library functions are available to your program.

## 1.3 The Translation Pipeline

```{=typst}
#heavy[
```

Dense — slow down: The steps from readable text to a runnable program involve multiple hidden tools acting in sequence.

```{=typst}
]
```

To understand C, you must understand how your source code becomes an executable. Think of this process like an assembly line in a factory. Each station takes an intermediate product, transforms it, and hands it to the next station.

![The C translation pipeline: from text to an executable binary.](assets/s01_pipeline.png)

First, let's look at an example. When you run a single command like `gcc main.c -o myprogram`, GCC acts as a "driver" that silently orchestrates four distinct stages:

1. **Preprocessing**: The preprocessor acts as a naive text-replacement tool. It strips comments, expands macros (`#define`), and literally pastes the contents of header files (`#include`) into your source file.
2. **Compilation**: The compiler translates the expanded C code into assembly language, which is a human-readable text representation of machine instructions specific to your CPU architecture.
3. **Assembly**: The assembler converts the assembly text into raw binary machine code, producing an *object file*.
4. **Linking**: The linker takes one or more object files, stitches them together, resolves references to external functions (like `printf` from the C standard library), and produces the final executable binary.

```{=typst}
#definition[
```

A **Translation Unit** is the ultimate input to the compiler: a single `.c` source file *after* the preprocessor has expanded all macros and pasted in all `#include` headers.

```{=typst}
]
```

```{=typst}
#definition[
```

An **Object File** (typically `.o` or `.obj`) contains compiled binary machine code for a single translation unit, but it is not yet executable because it may reference functions defined elsewhere that the linker hasn't connected yet.

```{=typst}
]
```

```{=typst}
#trap[
```

A common beginner mistake is assuming `#include` is like importing a module in Python. It is not. It is literal text inclusion. If you `#include` a massive header, the compiler processes all of it every time that file is compiled.

```{=typst}
]
```

If any stage fails, the pipeline halts. Syntax errors break compilation. Missing function definitions (like forgetting to compile a `.c` file that contains a function you called) break linking.

*This breaks when:* You declare a function but forget to define it. The code will compile fine, but the *linker* will fail with an "undefined reference" error.
*Question to sit with:* Why split compilation and linking into two separate steps instead of compiling everything directly to an executable at once?

## 1.4 A First Program: Tokens and Meaning

Let's dissect the canonical first program:

```c
#include <stdio.h>

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
```

- `#include <stdio.h>`: An instruction to the preprocessor to paste the "Standard Input/Output" header here, which tells the compiler what `printf` looks like.
- `int main(void)`: The entry point of every hosted C program. It takes no arguments (`void`) and returns an integer (`int`).
- `printf(...)`: A call to the standard library function to print formatted text to *standard output* (stdout).
- `return 0;`: Terminates the program. The `0` is passed back to the operating system as the *process exit status*. By convention, `0` means success.

By default, every C program has access to three standard streams: `stdin` (input), `stdout` (normal output), and `stderr` (error messages).

## 1.5 Compiling and Running in Practice

In practice, you invoke a compiler like `gcc` or `clang` from the terminal. A robust baseline command looks like this [3]:

```bash
gcc -std=c17 -Wall -Wextra -O2 -g main.c -o myprogram
```

- `-std=c17`: Selects the C17 standard.
- `-Wall -Wextra`: Enables a comprehensive set of warnings. Always use these; the compiler will catch many bugs for you.
- `-O2`: Enables moderate optimization for performance.
- `-g`: Embeds debugging information into the binary, allowing tools to map machine code back to your C source lines.

You can instruct the compiler to stop at specific pipeline stages to inspect the intermediate artifacts:
- `-E`: Stop after preprocessing (prints expanded text to the terminal).
- `-S`: Stop after compilation (produces an assembly file, usually `main.s`).
- `-c`: Stop after assembly (produces an object file, `main.o`).

## 1.6 Compiled vs Interpreted and the ABI

Unlike Python or JavaScript, C is compiled to *native code*. This means the compiler produces raw machine instructions that the CPU executes directly, without any software intermediary. This buys maximum performance and minimal overhead, but costs portability.

When you compile a C program, the resulting binary is tightly bound to the target CPU architecture (e.g., x86_64, ARM) and the operating system (e.g., Linux, Windows).

```{=typst}
#definition[
```

An **Application Binary Interface (ABI)** is the low-level contract between a binary and the operating system/hardware. It dictates things like how data is laid out in memory and in which CPU registers function arguments are passed.

```{=typst}
]
```

To run your program on a different architecture (like building Raspberry Pi code on your Windows laptop), you must *cross-compile*, using a toolchain specifically built to generate machine code for the target ABI.

## 1.7 The Abstract Machine and Behavior Categories

```{=typst}
#heavy[
```

Dense — slow down: C defines a theoretical "abstract machine." Your code's behavior must match what the standard dictates for this machine.

```{=typst}
]
```

The C standard does not describe exactly what a CPU must do. Instead, it describes an *Abstract Machine*. Think of this as a perfect, idealized computer that operates strictly by the rules of the C standard. 

![The four categories of behavior in C.](assets/s01_behavior.png)

Let's look at a concrete example. If you write `int a = 2 + 2;`, the compiler ensures `a` is 4. But what if you write `int x = 2147483647 + 1;` (overflowing a standard 32-bit signed integer)? The C compiler's job is to translate your code so that the actual CPU's observable behavior matches the abstract machine's requirements.

The standard categorizes program behavior into four distinct buckets [1]:

1. **Well-defined behavior**: The standard prescribes exactly what must happen (e.g., `int a = 2 + 2;`).
2. **Implementation-defined behavior**: The standard allows a few options, and the compiler *must* choose one and document it (e.g., the exact size in bytes of an `int`).
3. **Unspecified behavior**: The compiler can choose an option, but does not have to document it, and can change its mind (e.g., in `foo() + bar()`, which function is called first).
4. **Undefined behavior (UB)**: You have violated the rules of the abstract machine. The standard imposes *no requirements whatsoever* on what the compiler does next.

```{=typst}
#trap[
```

Beginners often think Undefined Behavior means "it crashes" or "it returns garbage." No. UB means the compiler is allowed to assume the invalid code *never happens*. It might delete the code entirely, format your hard drive, or time-travel to break earlier code. Never rely on UB.

```{=typst}
]
```

*This breaks when:* You write code that triggers Undefined Behavior, like dividing by zero or accessing an array out of bounds. The compiler might optimize the check away entirely, assuming you wouldn't write broken code.
*Question to sit with:* Why does the C standard allow Implementation-Defined behavior instead of forcing all compilers to do exactly the same thing?

We will cover the profound implications of Undefined Behavior in Section 19.

## 1.8 From Source to a Running Process

When you run your compiled binary, the operating system's loader reads the file into memory and creates a process. This process has distinct memory regions:
- **Code (Text)**: The executable machine instructions.
- **Data/BSS**: Global and static variables.
- **Stack**: Memory for local variables and function call bookkeeping.
- **Heap**: Memory you request dynamically at runtime.

We will explore this layout rigorously in Section 6 (Memory Model).

## 1.9 The Toolchain Ecosystem

C is supported by a massive ecosystem. The "Big Three" compilers are GCC (GNU Compiler Collection), Clang (based on LLVM), and MSVC (Microsoft Visual C++). To manage compiling multiple files, projects use build systems like `make`, `CMake`, or `Ninja`. For debugging, `gdb` (GNU Debugger) and `lldb` are standard tools.

In the embedded world, C is the lingua franca. Hardware vendors (like ARM or STM32) provide specialized cross-toolchains to compile C into raw binaries that can be flashed directly onto microcontrollers, bypassing the need for an operating system entirely.

---

## 1.10 Worked Examples

### Walkthrough: Inspecting the Pipeline

Let's walk through compiling a simple `hello.c` and inspecting the pipeline.

```c
#include <stdio.h>
int main(void) {
    puts("Hello pipeline");
    return 0;
}
```

1) **Preprocess**: Run `gcc -E hello.c > hello.i`. If you open `hello.i`, you will see thousands of lines of code. This is because `<stdio.h>` and all its dependencies have been fully expanded. Your `main` function sits at the very bottom.
2) **Assemble**: Run `gcc -S hello.c`. This produces `hello.s`. Open it, and you'll see assembly language (e.g., `call puts` or `mov eax, 0`), bridging C and the machine.
3) **Compile to Object**: Run `gcc -c hello.c`. This produces `hello.o`. If you try to read it with a text editor, it will look like gibberish—it is raw binary machine code.
4) **Link**: Run `gcc hello.o -o hello`. The linker connects `hello.o` with the system's C library (where `puts` actually lives) to produce the final executable `hello`.

### Faded Example

Consider the following program, saved as `math.c`:

```c
#define MULTIPLIER 5
int scale(int input) { return input * MULTIPLIER; }
```

You run three different commands. Identify what the resulting artifact contains:

1) **Command**: `gcc -E math.c`
   **Result**: Outputs the C source code, but with `MULTIPLIER` replaced by `5`.
2) **Command**: `gcc -S math.c`
   **Result**: Outputs `math.s`, containing human-readable assembly instructions (like an `imul` multiply instruction).
3) **Command**: `gcc -c math.c`
   **Result**: ________

*(Self-check: The third command outputs `math.o`, a binary object file containing the machine code for the `scale` function, ready to be linked.)*

---

### References
[1] ISO/IEC 9899:2024 (C23 standard draft N3220) — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf
[2] History of C — en.cppreference.com — https://en.cppreference.com/w/c/language/history
[3] GCC Command Options — gcc.gnu.org — https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
