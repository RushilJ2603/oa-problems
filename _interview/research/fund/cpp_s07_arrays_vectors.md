# Arrays and Vectors: Static and Dynamic Storage

Before turning to pointers and the **heap**, it is worth contrasting the two everyday ways C++ stores a sequence of elements: the built-in **array** and the standard-library **vector** (`std::vector`). The fundamental difference comes down to *flexibility versus rigidity*.

::: definition
An array is a fixed-size block of memory; a vector is a dynamic, resizable array that can grow or shrink at runtime.
:::

That single distinction — fixed versus growable — explains every other difference between them, including where each one lives in memory.

## Quick reference comparison

| Feature | Array | Vector (`std::vector`) |
| --- | --- | --- |
| **Sizing** | Fixed (cannot be changed) | Dynamic (grows automatically) |
| **Memory location** | Usually the stack | Always the heap |
| **Size known at** | Compile time | Runtime |
| **Performance** | Extremely fast (zero overhead) | Fast (slight overhead for resizing) |
| **Memory efficiency** | Perfect (uses exactly what it needs) | Over-allocates to allow for growth |
| **Syntax** | `int arr[5];` | `std::vector<int> vec;` |

## Arrays: the rigid speedsters

When an array is created its size is locked in for good. The compiler must be told exactly how many elements it will hold before the program even compiles.

Because the compiler knows the exact size in advance, it can safely place the array on the **stack**. Stack memory is extremely fast and is managed automatically.

::: trap
If an array is declared with room for ten items but the program later needs an eleventh, there is no recourse — writing past the end overflows the array's storage.
:::

::: keypoint
Prefer not to use raw C-style arrays (`int arr[]`). The standard-library wrapper `std::array<int, 5> arr` has the same performance but adds bounds checking and other safety features.
:::

## Vectors: the dynamic workhorses

A `std::vector` is designed to be completely flexible. One can start with an empty vector and keep pushing items into it indefinitely; the vector handles the memory management.

Because a vector does not know in advance how large it will eventually grow, it cannot live on the stack. Instead it requests memory from the operating system on the heap.

::: interview
A vector does not actually grow one element at a time. Internally it holds a fixed **capacity**, and when an insertion would exceed that capacity it performs a comparatively heavy operation:
1. it requests a brand-new, larger block of memory from the heap (typically **double** the current size);
2. it copies every existing element across to the new block;
3. it releases the old block.
:::

This reallocation costs time and processing power. But because the capacity *doubles* each time it is exhausted, reallocations occur exponentially less often as the vector grows — so the cost, averaged over many insertions, stays small.

## Which should you use?

::: keypoint
**Default to `std::vector` for almost everything.** The cost of heap allocation is negligible for the overwhelming majority of programs, and the flexibility removes a whole class of out-of-bounds errors.
:::

Reach for `std::array` only when the number of elements is genuinely known in advance — for instance, holding the three coordinates of a point — where a fixed, stack-resident block is both sufficient and maximally efficient.
