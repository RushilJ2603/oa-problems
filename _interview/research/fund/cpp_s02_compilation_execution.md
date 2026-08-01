# Compilation and the Program Execution Model

Before reasoning about language features it helps to know what actually happens between writing source code and seeing a result.

::: keypoint
A C++ program is not run directly from the text a programmer types; it passes through a fixed sequence of stages that transform human-readable source into a machine-executable image, which is then brought into memory and run.
:::

This part traces that pipeline and the memory layout the running program occupies.

## A sample program

The pipeline is easiest to follow against a concrete example: a small program with a `max` function that returns the larger of two integers, called from `main`.

```cpp
#include <iostream>

int max(int x, int y)
{
    if (x > y)
        return x;
    return y;
}

int main()
{
    int a = 10, b = 5, c;
    c = max(a, b);
    std::cout << c;
}
```

The source is written into a file — say `first.cpp` — and the goal of the pipeline is to turn that file into an executable image, `first.exe`.

## The five stages

A program reaches execution through five ordered stages.

1. **Editing.** The source is typed into an editor, usually inside an **Integrated Development Environment** (IDE) — a single tool that bundles the editor, compiler, and other utilities. Common examples include Turbo C++, Dev-C++, Xcode, Code::Blocks, and Eclipse.

2. **Compiling.** The compiler translates the source into machine code. Before translation proper, the **preprocessor** runs and expands directives such as `#include <iostream>`: the contents of the named header file are pulled into the source so that the names it declares (for instance the stream objects `cout` and `cin`) become known to the compiler.

   ::: definition
   A **header file** is exactly this — a file whose declarations are made available wherever it is included.
   :::

3. **Linking the library.** Declaring a name is not the same as providing its implementation.

   ::: definition
   Linking combines the compiled code with the library implementations it depends on — the standard library code behind `cout` and `cin`, for example — resolving every referenced symbol and producing the final executable (`first.cpp` becomes `first.exe`).
   :::

4. **Loading.** The finished executable lives on the hard disk (HDD). To run, it must first be loaded from disk into the computer's main memory.

5. **Execution.** Once loaded, the CPU executes the program's instructions.

## Where things live: disk, memory, and the CPU

Two distinct storage locations are involved. The hard disk holds the *files* — both the source `first.cpp` and the built `first.exe` — persistently. Main memory holds the program only while it runs.

When the executable is loaded, its address space is divided into regions, three of which are introduced here:

- the **code section**, which holds the program's instructions;
- the **stack**, used for function-call data;
- the **heap**, used for dynamically allocated data.

::: keypoint
The CPU drives execution: it reads instructions from the code section and operates on data held in the stack and heap. The division of run-time memory into stack, heap, and code section is the foundation for later topics such as how function calls and references behave in memory.
:::

![Steps for program development and execution.](assets/fig_20260614_program-dev-execution.png)
