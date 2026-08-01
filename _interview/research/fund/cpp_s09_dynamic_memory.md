# Dynamic Memory Allocation on the Heap

The previous section established that the heap is reachable only through a pointer. This section shows how a program actually obtains and releases heap memory. The defining property of the heap is that its memory is allocated **dynamically**: the amount of memory is decided at *run time*, not at compile time. This is exactly what lets a program ask for precisely as much storage as it discovers it needs while running, rather than committing to a fixed size in the source.

## Stack allocation versus heap allocation

Contrast an ordinary array with a dynamically allocated one. A built-in array lives in the function's stack frame, and its size is fixed when the program is compiled:

```cpp
int A[5] = {1, 2, 3, 4, 5};   // on the STACK: size fixed at compile time
```

Heap allocation is requested explicitly with the `new` operator, and the resulting address is stored in a pointer:

```cpp
int* p;
p = new int[5];               // on the HEAP: a block of 5 ints, allocated at run time

// declaration and allocation can be combined into one line:
int* p = new int[5];
```

`new int[5]` asks the heap for a block large enough for five integers and hands back the address of that block, which is kept in the pointer `p`. The array `A` sits in `main`'s stack frame; the `new[]` block sits on the heap; and `p`, itself a stack variable, holds the heap block's address. This is the same stack-points-to-heap picture from the previous section, now created deliberately by the programmer.

## Lifetime: heap memory is not reclaimed automatically

Stack memory is managed automatically — a function's locals vanish when the function returns. Heap memory is not. 

::: keypoint
A block obtained with `new` **persists for as long as the program runs** unless the program explicitly gives it back. The responsibility for releasing it rests entirely with the programmer.
:::

::: definition
If a heap block is finished with but never released, the memory stays reserved and unusable for the rest of the program's life. This waste is called a **memory leak**: memory that is allocated, no longer reachable or needed, yet never returned.
:::

## Releasing memory and the null pointer

A heap block is returned to the system with the `delete` operator. Because the block was allocated as an array with `new[]`, it must be released with the matching array form `delete[]`:

```cpp
delete[] p;   // returns the heap block to the system
p = NULL;     // p now points nowhere
```

After `delete[]`, the pointer `p` still holds its old address, but that address is no longer valid. Assigning `NULL` marks the pointer as pointing nowhere. 

::: definition
A pointer that is not pointing at anything is called a **null pointer** — a deliberate, recognisable "points to nothing" state, as opposed to a stale address left dangling after a delete.
:::

![Heap: dynamic allocation of an array with new, released with delete and reset to null.](assets/fig_20260614_heap-dynamic-allocation.png)

The complete cycle, then, is: request memory with `new[]`, use it through the pointer, return it with `delete[]`, and set the pointer to `NULL`. 

::: trap
Skipping the `delete[]` leaks the memory; using the pointer after `delete[]` without resetting it reaches into memory the program no longer owns.
:::

## Indexing a heap array through the pointer

A pointer to a heap array is indexed exactly like an ordinary array. Given a stack array `A` and a heap array reached through `p`, the two element assignments look identical:

```cpp
int A[5] = {1, 2, 3, 4, 5};   // array on the stack
int* p = new int[5];          // array on the heap, reached through p

A[2] = 15;   // writes element 2 of the stack array
p[2] = 15;   // writes element 2 of the heap array, via the pointer
```

The subscript `p[2]` works because indexing is defined in terms of the pointer: it advances two elements past the address `p` holds and accesses the value there. So although the heap block has no name of its own, `p` gives every element of it the same convenient `p[i]` access an ordinary array enjoys.

## A runtime-sized array: the point of dynamic allocation

The real payoff of `new[]` is that the size may be a value computed *while the program runs* — something a stack array cannot do. A typical pattern reads the size from the user and then allocates exactly that many elements:

```cpp
int size;
std::cout << "Enter number of elements";
std::cin >> size;
int* p = new int[size];   // size is known only at run time

// to resize later, allocate a fresh block of the new size:
std::cout << "Enter new size";
std::cin >> size;
p = new int[size];
```

Because `size` is not known until the user supplies it, the array could not have been declared on the stack with a compile-time bound; the heap is the only region that can satisfy a request whose size is discovered at run time. 

::: trap
Note that the second `new[]` replaces the pointer with a brand-new block; in a complete program the first block must be released with `delete[]` before reassigning, or it is leaked — a pitfall taken up in a later section.
:::
