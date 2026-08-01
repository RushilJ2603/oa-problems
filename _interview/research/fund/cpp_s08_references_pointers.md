# References, the Address-of and Dereference Operators, and Pointers

This part builds the tools for working with memory directly: the idea of a reference as an alias, the subtler cases of binding references to constants and to temporaries, taking the address of an object, dereferencing an address to reach the object it names, and finally pointers, which store addresses as values.

## A reference is an alias

::: definition
An **lvalue reference** is essentially an **alias**: a second name for an object that already exists.
:::

Declaring a reference — `&` after the type — and initialising it from an existing variable makes both names refer to the very same storage:

```cpp
int main()
{
    int x = 10;
    int& y = x;   // y is an alias for x — the SAME object, not a copy
}
```

After this, `x` and `y` name one and the same memory cell — say the one at address `200/201`. There is no second object; `y` is simply another label on `x`'s box. Consequently a change made through either name is visible through the other:

```cpp
x++;             // affects the single shared object
y++;             // affects the same object again
std::cout << x;  // 12
std::cout << y;  // 12
```

Both print `12`, because both names denote the same value, now incremented twice.

![Reference: y is an alias for x — both names share one object at one address.](assets/fig_20260615_reference-alias.png)

Two properties follow directly from "a reference is just another name":

- **A reference must be initialised when it is declared.** There is no reference that names nothing — `int& y;` is a compile error ("declaration of reference variable 'y' requires an initializer"). A name must be a name *for something*.
- **A reference occupies no separate storage of its own.** Being an alias rather than an independent object, it gets no box in memory; it shares the address of what it refers to. Taking the address of either name yields the same address, so `&x == &y`.

## Address versus data: the two sides of an assignment

The alias idea is sharpened by a complementary observation about what a variable name *means* depending on where it appears in an assignment:

```cpp
int a;
a = x;    // RIGHT-hand side: x is read for its DATA       (used as an rvalue)
x = 25;   // LEFT-hand side:  x designates its ADDRESS      (used as an lvalue)
```

On the right of `=`, a variable contributes its stored value — its *data*; on the left, it designates the location — its *address* — into which a value is written. This is the same lvalue/rvalue distinction developed earlier for expressions, now restated as address versus data. It is also why a reference, bound directly to an address, can stand in for its object on either side of an assignment.

## Binding a const lvalue reference to a modifiable lvalue

An lvalue reference to `const` can bind not only to `const` objects but also to **modifiable** lvalues. When it does, the object is treated as `const` *when accessed through that reference*, even though the underlying object is itself non-`const`.

```cpp
#include <iostream>

int main()
{
    int x { 5 };          // x is a modifiable lvalue
    const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue

    std::cout << ref << '\n'; // okay: we can access the object through our const reference
    ref = 7;                  // error: we cannot modify an object through a const reference

    x = 6; // okay: x is a modifiable lvalue, we can still modify it through the original identifier

    return 0;
}
```

Here the `const` reference `ref` is bound to the modifiable lvalue `x`. Access through `ref` is allowed, but assignment through `ref` is forbidden because `ref` is `const`. The original object can still be changed through its own identifier `x`. An earlier variant of the same idea binds a `const` reference to a `const` object:

```cpp
const int& ref { x }; // okay: ref is an lvalue reference to a const value

std::cout << ref << '\n'; // okay: we can access the const object
ref = 6;                  // error: we cannot modify an object through a const reference
```

::: keypoint
Favour lvalue references to `const` over lvalue references to non-`const` unless you need to modify the object being referenced.
:::

## Binding a const reference to an rvalue: hidden temporary materialisation

A `const` lvalue reference may also bind to an rvalue — for example `const int& ref = 5;`. This raises a puzzle: a reference must be backed by a physical memory address, but `5` is a pure value with no address. To resolve this, the compiler silently rewrites the code into something equivalent to:

```cpp
int __hidden_temporary = 5;            // 1. Allocates real stack memory
const int& ref = __hidden_temporary;   // 2. Binds your reference to it
```

What this means for the mental model:

1. You did not actually get the address of the "pure" rvalue `5`.
2. The compiler was forced to *materialise* that rvalue into a real, physical, unnamed variable on the stack.
3. Your `const` reference is bound to that hidden stack variable, and the compiler guarantees that the hidden variable stays alive exactly as long as `ref` stays alive.

**Can you access its address?** Yes. Writing `&ref` compiles and prints a valid memory address — the address of the compiler's hidden temporary. But because it is a `const` reference, the compiler physically blocks you from writing to that address: you can read the data, but you cannot change it.

This is the same materialisation principle seen earlier with post-increment temporaries — rvalues that need to persist are given a real, if invisible, home in memory.

## The address-of operator (`&`)

The **address-of operator** returns the memory address of its operand. For objects that occupy more than one byte of memory, address-of returns the address of the *first* byte used by the object.

The `&` symbol is a frequent source of confusion because its meaning depends on context:

- When following a type name, `&` denotes an **lvalue reference**: `int& ref`.
- When used in a **unary** context in an expression, `&` is the **address-of** operator: `std::cout << &x`.
- When used in a **binary** context in an expression, `&` is the **bitwise AND** operator: `std::cout << x & y`.

## The dereference operator (`*`)

Knowing the address of a variable is not by itself very useful. The most useful thing one can do with an address is to access the value stored at that address. The **dereference operator** `*` (also called the **indirection operator**) returns the value at a given memory address as an lvalue.

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    std::cout << x << '\n';   // print the value of variable x
    std::cout << &x << '\n';  // print the memory address of variable x

    std::cout << *(&x) << '\n'; // print the value at the memory address of variable x
                                // (parentheses not required, but make it easier to read)

    return 0;
}
```

::: keypoint
Given a memory address, the dereference operator `*` gives the value at that address (as an lvalue). The address-of operator `&` and the dereference operator `*` are opposites: address-of takes an object and gives its address; dereference takes an address and gives the object at it.
:::

::: trap
Although the dereference operator looks like the multiplication operator, the two are distinguishable because **dereference is unary** whereas **multiplication is binary**.
:::

Note that taking the address of a variable and then immediately dereferencing it (as in `*(&x)`) is not itself useful — if you already have the variable, you can just use it. The value of these operators comes once they are combined with pointers.

## Pointers

::: definition
A **pointer** is an object that holds a *memory address* (typically of another variable) as its value.
:::

This allows the address of some other object to be stored and used later. In modern C++, the pointers described here are sometimes called "raw pointers" or "dumb pointers", to distinguish them from "smart pointers", which were introduced into the language more recently.

A type that specifies a pointer (for example, `int*`) is called a **pointer type**. Much as reference types are declared with an ampersand (`&`), pointer types are declared with an asterisk (`*`):

```cpp
int;   // a normal int
int&;  // an lvalue reference to an int value

int*;  // a pointer to an int value (holds the address of an integer value)
```

To create a pointer variable, simply define a variable with a pointer type:

```cpp
int main()
{
    int x { 5 };    // normal variable
    int& ref { x }; // a reference to an integer (bound to x)

    int* ptr;       // a pointer to an integer

    return 0;
}
```

### Initialising pointers

::: trap
A pointer that is not initialised holds a garbage address, and dereferencing such a **wild pointer** results in undefined behaviour. Always initialise your pointers to a known value.
:::

```cpp
int main()
{
    int x { 5 };

    int* ptr;        // an uninitialized pointer (holds a garbage address)
    int* ptr2{};     // a null pointer (discussed in the next lesson)
    int* ptr3{ &x }; // a pointer initialized with the address of variable x

    return 0;
}
```

Because pointers hold addresses, the value used to initialise or assign to a pointer must itself be an address — and addresses are obtained with the address-of operator (`&`). Once a pointer holds the address of another object, the dereference operator (`*`) can be used to access the value at that address:

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    std::cout << x << '\n'; // print the value of variable x

    int* ptr{ &x };          // ptr holds the address of x
    std::cout << *ptr << '\n'; // use dereference operator to print the value at the address
                               // that ptr is holding (which is x's address)

    return 0;
}
```

This is where address-of and dereference become genuinely useful: a pointer stores an address obtained with `&`, and `*` reaches through the stored address to read or write the object it names.

### A worked picture: a pointer, its target, and their addresses

A small example ties the three symbols — `&`, `*`, and the pointer variable itself — to concrete numbers. Suppose an integer `x` holding `10` lives at address `200`, and a pointer `p` set to `&x` lives at its own address `300`:

```cpp
int x = 10;   // x lives at address 200, holds 10
int* p;       // p is a pointer to int
p = &x;       // p now holds 200 (the address of x)

std::cout << x;    // 10   — the value of x
std::cout << &x;   // 200  — the address of x
std::cout << p;    // 200  — p's value, which IS the address of x
std::cout << &p;   // 300  — the address of p itself
std::cout << *p;   // 10   — dereference: the value living at the address p holds
```

Reading the list line by line fixes the mental model. Printing `x` gives its value, `10`. Printing `&x` gives where `x` lives, `200`. The pointer `p` *stores* that same address, so printing `p` also gives `200`. But `p` is itself an object with its own location, so `&p` gives a different address, `300`. Finally, `*p` *follows* the address stored in `p` back to `x` and yields `10` again. Dereferencing is exactly this act of "accessing the data that `p` is pointing to."

![Pointers: a variable, its address, and a pointer that holds that address.](assets/fig_20260614_pointers-worked-example.png)

### The three operations: declaration, initialisation, dereferencing

Pointers are easier to keep straight once their use is separated into three distinct steps, each with its own syntax:

| Step | Syntax | What it does |
| --- | --- | --- |
| **Declaration** | `int* p;` | creates a pointer that can hold the address of an `int` |
| **Initialisation** | `p = &x;` | stores an actual address (here, `x`'s) into the pointer |
| **Dereferencing** | `std::cout << *p;` | follows the stored address to reach the pointed-to value |

Declaration sets up the pointer's type; initialisation gives it something real to point at; dereferencing uses it. Confusion usually comes from blurring these three together — kept apart, each is simple.

### A pointer's own size

A pointer stores an address, and an address is the same size regardless of what it points at. So `sizeof` applied to a pointer does **not** depend on its pointee type — `int*`, `double*`, and `char*` are all the same size:

```cpp
int*    p;
double* q;
sizeof(p) == sizeof(q);   // true: each merely holds an address
```

On a typical modern 64-bit compiler that size is **8 bytes** for every pointer. (The worked examples in this and the following sections use a 2-byte address purely to keep the address arithmetic small and readable.)

### Copying a pointer versus referencing it

Assigning one pointer to another **copies the address**, producing two independent pointers that merely happen to hold the same value:

```cpp
int  x  = 5;
int* p1 = &x;
int* p2 = p1;   // p2 is a SEPARATE pointer holding the same address
```

`p1` and `p2` are two distinct pointer variables; later making `p2` point elsewhere leaves `p1` untouched. This differs from a **reference to a pointer**, written `int*&`, which is an alias for the pointer itself:

```cpp
int*& p3 = p1;  // p3 is another name for p1, not a copy of it
```

Through `p3`, changing where the pointer points also changes `p1`, because they are the same pointer. It is the familiar copy-versus-alias distinction, applied one level up: `int* p2 = p1` copies the pointer, whereas `int*& p3 = p1` aliases it.

## Why pointers exist: reaching the heap

Pointers can feel like an unnecessary detour — why store an address when the variable is right there? The reason becomes clear from how a running program is allowed to touch memory. Recall the process memory model with its three regions: the **code section**, the **stack**, and the **heap**. A program may access the code section and its own stack directly: when `main` runs, its local variables sit in `main`'s activation record on the stack, and the program reaches them by name without ceremony.

The **heap** is different. The program is not permitted to reach into heap memory directly by name — there is no name to use, because heap memory is requested at runtime rather than declared in the source. The only way to use a block of heap memory is to hold its **address** and reach it indirectly. That is precisely what a pointer is for: a pointer variable, living on the stack, stores the address of a block on the heap, and dereferencing it reaches across into that block.

![Why pointers: the program reaches heap memory indirectly, through a pointer held on the stack.](assets/fig_20260614_why-pointers-heap.png)

So the heap is the home of memory whose size or lifetime is not known until the program runs — exactly the memory a `std::vector` asks for as it grows. Such memory is unreachable except through a pointer, which makes pointers the indispensable bridge between the program's named, stack-bound world and the anonymous, dynamically allocated heap.
