# Passing Arguments: by Value, by Pointer, by Reference

How a function receives its arguments decides whether it can change the caller's variables. Three mechanisms — **by value**, **by pointer**, and **by reference** — differ in exactly that. A swap function makes the difference vivid: each version tries to exchange two variables `x` and `y`.

## Call by value: the function works on copies

::: definition
By default, arguments are passed by value: the function receives *copies* of the caller's data in its own parameters.
:::

::: trap
Changes to those copies never reach the originals.
:::

```cpp
void swap(int a, int b)   // a, b are copies
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x = 10, y = 20;
    swap(x, y);
    cout << x << " " << y;   // 10 20 — UNCHANGED
}
```

Inside `swap`'s own activation record `a` and `b` are exchanged, but `x` and `y` in `main` are untouched, so the output is still `10 20`. The work was done on copies that vanish when `swap` returns.

## Call by pointer: passing addresses

To let a function modify the caller's variables, pass their addresses and operate through the pointers, dereferencing to reach the originals:

```cpp
void swap(int* a, int* b)   // a, b hold addresses
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int x = 10, y = 20;
    swap(&x, &y);            // pass addresses
    cout << x << " " << y;   // 20 10 — swapped
}
```

Now `a` and `b` hold the addresses of `x` and `y` (say `200` and `210`); `*a` and `*b` reach back into `main`'s memory, so the exchange affects the real variables.

## Call by reference: aliases for the caller's variables

::: definition
The most elegant form passes the parameters by reference. The parameters become *aliases* for the caller's `x` and `y` — not copies, and not addresses to dereference, but the same objects under new names:
:::

```cpp
void swap(int& a, int& b)   // a, b are aliases for the arguments
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x = 10, y = 20;
    swap(x, y);             // ordinary call syntax
    cout << x << " " << y;  // 20 10 — swapped
}
```

The call syntax is identical to call by value — `swap(x, y)` — but because `a` and `b` *are* `x` and `y`, the exchange happens directly on the originals. 

::: keypoint
No copies are made: the reference parameters share `main`'s storage (`x`/`a` and `y`/`b` name the same cells). This unites the clean syntax of value passing with the power to modify the caller's data, which is why reference parameters are the idiomatic C++ choice.
:::

## A note on inlining

A call-by-reference function can additionally be made an **inline** function. 

::: definition
Inlining is a compiler optimisation about *how a call is executed*, independent of how arguments are passed.
:::

Normally, calling a function makes the CPU jump to the function's single block of machine code, run it, and return; that machine code lives once, in the `.text` section of the executable, and every call site jumps to it.

When a function is inlined, the compiler instead pastes the function's machine code *directly* into each call site, removing the jump-and-return. This trades space for speed:

- **Not inlined (normal):** the code exists once — a smaller executable — but each call pays for a jump to it and a return.
- **Inlined:** each call runs the code in place — faster, no jump — but the body is duplicated at every call site, enlarging the executable.

::: interview
In modern C++ the `inline` keyword is only a *suggestion*; aggressive compilers (GCC, Clang, MSVC) decide for themselves whether inlining a given function is worthwhile, weighing the speed gain against the code-size cost.
:::
