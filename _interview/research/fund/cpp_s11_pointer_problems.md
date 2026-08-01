# Common Pointer Problems

Pointers are powerful precisely because they manipulate memory directly, and that same directness makes them easy to misuse. Three classic problems account for most pointer bugs: the **uninitialised pointer**, the **memory leak**, and the **dangling pointer**.

## Uninitialised (wild) pointers

::: definition
A pointer that is declared but never given a valid address holds whatever garbage already occupied its memory. Dereferencing such a **wild pointer** reads or writes an unpredictable location.
:::

The remedy is to give every pointer a definite value before use — the address of a real object, or an explicit null:

```cpp
int x = 10;
int* p;              // uninitialised: holds garbage

p = &x;              // (1) point it at a real object
p = (int*) 0x5638;   // (2) a specific, hard-coded address — rarely appropriate
p = new int(5);      // (3) point it at a freshly allocated heap object
```

Each assignment gives `p` a defined meaning; the danger lies only in using it before any of them has run. (Note that `new int(5)` allocates a *single* `int` initialised to 5, whereas `new int[5]` would allocate an array of five.)

## Memory leaks

Heap memory obtained with `new` stays reserved until it is explicitly released with `delete`.

::: definition
If the last pointer to a block is lost — reassigned to something else, or going out of scope — without a matching `delete`, that block can never be reclaimed: a memory leak.
:::

::: keypoint
The discipline is to pair every `new` with a `delete`, and after releasing, to reset the pointer so it no longer names freed memory:
:::

```cpp
int* p = new int[5];
// ... use p ...

delete[] p;     // release the block
p = nullptr;    // (equivalently p = NULL; or p = 0;) p now points at nothing
```

Nulling the pointer after deletion is also what guards against the third problem.

## Dangling pointers

::: definition
A dangling pointer still holds the address of memory that has already been freed.
:::

::: trap
Dereferencing it is **undefined behaviour** — the memory may have been handed to something else entirely. The trap is especially easy to fall into when a pointer is shared across functions:
:::

```cpp
void fun(int* q)
{
    // ...
    delete[] q;        // frees the block
}

void main()
{
    int* p = new int[5];
    fun(p);            // fun deletes the block that p still points to

    std::cout << *p;   // DANGLING: p now refers to freed memory — undefined behaviour
}
```

Here `main` and `fun` hold two pointers, `p` and `q`, to the *same* heap block. When `fun` deletes through `q`, the block is gone, yet `main`'s `p` still holds its old address. Using `*p` afterwards reaches into memory the program no longer owns. The remedy combines the null-after-delete habit with clear ownership — deciding which part of the code is responsible for releasing a block — exactly the kind of check careful programmers verify before shipping.

![Common pointer problems: once a block is freed, any other pointer still holding its address is left dangling.](assets/fig_20260615_pointer-problems.png)
