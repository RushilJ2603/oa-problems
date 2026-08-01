# 4. Pointers — Deep Dive

At the hardware level, memory is a vast sequence of cells, each capable of holding a single byte of data. Every cell is identified by a unique numeric index called its *address* [1]. 

## 4.1 What a Pointer Is

```{=typst}
#heavy[
```

Dense — slow down: A pointer requires you to distinguish between a container, its location, and the data inside it.

```{=typst}
]
```

Think of computer memory like a long street of houses. A variable's value is the family living inside the house. The variable's address is the house number painted on the curb. A **pointer** is a piece of paper on which you have written down that house number. You can hand this paper to someone else, and they can use it to find the house and interact with the family inside.

![A pointer holding the address of another variable.](assets/s04_pointer_basic.png)

```c
int x = 42;
int *p = &x;
```

In this snippet, `x` is the house holding the value `42`. `p` is a pointer variable. We initialize `p` not with a standard number, but with the memory address of `x`. The `*` in the declaration flags `p` as a pointer, and the `&` operator fetches the address of `x`.

A pointer, therefore, is a distinct variable whose value is a memory address. Crucially in C, a pointer is not just a raw address; it is an *address strongly bound to a specific data type*, known as the **pointee type** [1]. The type `int *` means "an address where an `int` can be found." This breaks when you attempt to treat a pointer merely as an integer; they are distinct concepts in the C memory model.

```{=typst}
#trap[
```

**Trap: "A pointer is a memory address."**
A pointer *holds* a memory address, but it also carries type information. The compiler uses this type to know how many bytes to read when you visit the address, and how to interpret those bytes. A `char *` reads 1 byte; a `double *` reads 8 bytes.

```{=typst}
]
```

## 4.2 Syntax and the Right-Left Rule

C uses specific operators to manage indirection.
- **Address-of (`&`)**: Given a variable `x`, `&x` yields the memory address where `x` resides.
- **Dereference (`*`)**: Given a pointer `p`, `*p` follows the address to the actual memory cell, allowing you to read or write the pointee's value. 

When declarations become complex, reading them linearly from left to right fails. Use the **Right-Left Rule** (often called the spiral rule) [3]. Start at the variable name, look right, then look left, and keep expanding outward:
1. `int *p;` → Start at `p`. Look right: nothing. Look left: `*` (pointer to). Look left: `int`. "p is a pointer to an int."
2. `int *(*f)(int);` → Start at `f`. Look right: `)` (bound by parens, bounce back). Look left: `*` (pointer to). Look right (outside parens): `(int)` (function taking an int). Look left: `*` (pointer to). Look left: `int`. "f is a pointer to a function taking an int and returning a pointer to an int."

## 4.3 The Null Pointer

A pointer must point to valid memory before it is dereferenced. C defines a special macro, `NULL` (typically defined as `0` or `(void*)0`), to represent a pointer that points nowhere [4]. It is the universal sentinel value indicating "no valid object." Dereferencing a null pointer triggers **undefined behavior (UB)**, typically causing the operating system to forcefully terminate the program (a segmentation fault). Always check pointers for `NULL` before dereferencing if their origin is uncertain (e.g., returned from an allocation function).

## 4.4 Pointer Arithmetic

```{=typst}
#heavy[
```

Dense — slow down: Pointer arithmetic does not behave like standard integer math. It is strictly tied to the pointee's type size.

```{=typst}
]
```

Imagine standing on a tiled floor where each tile is an `int`. If you step forward by "one tile," your physical displacement depends on how wide the tile is. 

![Pointer arithmetic scales by the size of the pointee type.](assets/s04_ptr_arithmetic.png)

```c
int arr[4] = {10, 20, 30, 40};
int *p = &arr[0];
p = p + 1;
```

When you add `1` to `p`, C does not add `1` to the raw memory address. It adds `1 * sizeof(int)`. If an `int` is 4 bytes and `p` starts at address `0x1000`, `p + 1` evaluates to `0x1004` [2]. This ensures that arithmetic on a pointer always advances it to the next valid object of that type in a sequence.

The valid arithmetic operations are:
1. **Addition/Subtraction of an integer (`p + n`, `p - n`)**: Steps forward or backward by $n$ elements.
2. **Pointer difference (`p2 - p1`)**: Yields the number of *elements* (not bytes) between two pointers, as a signed integer type `ptrdiff_t`.
3. **Relational comparisons (`p1 < p2`)**: Evaluates which pointer points to an earlier element.

This breaks when applied arbitrarily. Pointer arithmetic and comparison are *only* well-defined when both pointers point to elements within the *same array*, or one past the last element of that array [2]. Comparing or subtracting pointers from entirely different, unrelated variables is undefined behavior.

## 4.5 Pointers and `const`

```{=typst}
#heavy[
```

Dense — slow down: The `const` keyword can apply to the pointer itself, to the data it points to, or to both.

```{=typst}
]
```

A door can be locked, or the room behind it can be locked, or both. `const` works the same way with pointers. Apply the right-left rule to read these correctly.

![Diagram showing what const locks in different pointer declarations.](assets/s04_const_ptr.png)

1. `const int *p;` (or `int const *p;`)
   Start at `p`. Look left: `*` (pointer to). Look left: `const int`. "p is a pointer to a const int."
   You can change `p` to point to a different address, but you cannot use `*p` to modify the value it points to.
2. `int *const p;`
   Start at `p`. Look left: `const`. Look left: `*` (pointer to). Look left: `int`. "p is a const pointer to an int."
   The pointer is locked to its initial address. You cannot reassign `p`, but you can use `*p` to modify the integer.
3. `const int *const p;`
   "p is a const pointer to a const int." Neither the pointer's address nor the pointee's value can be changed.

```{=typst}
#trap[
```

**Trap: "Passing a pointer guarantees modification."**
Just because a function accepts a pointer doesn't mean it intends to modify the caller's data. A signature like `size_t strlen(const char *str);` uses a pointer merely to avoid copying a massive string, using `const` to promise it will not mutate the original data.

```{=typst}
]
```

## 4.6 Generic Pointers: `void *`

A `void *` is a raw address stripped of its pointee type. It represents "a pointer to some block of memory." Because the compiler does not know the type, you cannot dereference a `void *` (it doesn't know how many bytes to read) and you cannot perform pointer arithmetic on it (it doesn't know the scale factor). 

Any object pointer can be implicitly converted to and from a `void *` without casting [4]. This is why dynamic memory functions like `malloc` return `void *`—they supply raw memory that you assign to a typed pointer, which automatically contextualizes it.

## 4.7 Pointers to Pointers

```{=typst}
#heavy[
```

Dense — slow down: To modify a variable inside a function, you must pass a pointer to that variable. If the variable you want to modify is *itself* a pointer, you must pass a pointer to a pointer.

```{=typst}
]
```

Think of a variable as a safety deposit box, and a pointer as the physical key to that box. If you want a locksmith (a function) to change the contents of your box, you give them the key (`int *`). But what if the box *contains* another key, and you want the locksmith to swap out that inner key for a new one? You must give them the key to the first box so they can open it and replace the key inside. That first key is a pointer to a pointer (`char **`).

If you want a function to change an `int` in the caller's scope, you pass an `int *`. If you want a function to change a `char *` (perhaps redirecting it to newly allocated memory), you must pass a `char **`.

![A double pointer holds the address of a pointer.](assets/s04_double_ptr.png)

```c
#include <stdlib.h>

void allocate_buffer(char **buf) {
    *buf = malloc(1024); // Modifies the caller's pointer
}

int main(void) {
    char *my_buf = NULL;
    allocate_buffer(&my_buf); // Pass the address of the pointer
    free(my_buf); // Good practice
    return 0;
}
```

By passing `&my_buf` (which has type `char **`), the function receives the address where the pointer `my_buf` lives. Dereferencing `buf` (`*buf`) reaches back to the original `my_buf` in `main` and updates its address. 

Another common use is arrays of strings. Because a string is a `char *`, an array of strings is an array of pointers, which degrades to a `char **` when passed to functions (e.g., `int main(int argc, char **argv)`).

## 4.8 Function Pointers

```{=typst}
#heavy[
```

Dense — slow down: Code resides in memory just like data. A function pointer holds the address of executable instructions, allowing you to pass functions as arguments.

```{=typst}
]
```

Think of a function like a specialized kitchen appliance, such as a blender, that sits at a fixed location on your counter. A function pointer is a label with the exact counter number where the appliance is plugged in. Instead of hardcoding "always use the blender here," you can pass the label to a chef (another function), allowing the chef to walk over and use whatever appliance is at that location.

Code resides in memory just like data. A function pointer holds the address of executable instructions, allowing you to pass functions as arguments.

![A function pointer holds the address of a block of executable code.](assets/s04_func_ptr.png)

When compiling, a function's machine code is placed at a specific memory address. You can take the address of a function and invoke it indirectly. This enables **callbacks**: passing logic into another function to customize its behavior.

```c
int ascending(int a, int b) { return a - b; }

// 'cmp' is a pointer to a function returning int and taking two ints
void sort_array(int *arr, int len, int (*cmp)(int, int)) {
    // Invoke the function pointer
    if (len >= 2 && cmp(arr[0], arr[1]) > 0) { 
        int temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
    }
}

int main(void) {
    int my_arr[10] = {0};
    sort_array(my_arr, 10, ascending); // Pass function address
    return 0;
}
```

The syntax for declaring a function pointer is notoriously ugly: `int (*cmp)(int, int)`. The parentheses around `*cmp` are mandatory; without them, the compiler parses it as a function returning an `int *`. To maintain sanity, use `typedef` to alias the signature:

```c
typedef int (*Comparator)(int, int);
void sort_array(int *arr, int len, Comparator cmp);
```

This breaks if the signature of the passed function does not strictly match the expected function pointer type. The compiler will complain, and overriding it with a cast leads to severe undefined behavior.

## 4.9 Pointers, Arrays, and Hazards

Arrays and pointers are intimately linked but fundamentally distinct. An array is a block of contiguous memory. However, in almost all expressions, an array's name **decays** into a pointer to its first element. 

If `int a[5];`, the expression `a` yields the address `&a[0]` as an `int *`. The array subscript operator `[]` is actually defined in terms of pointers: `a[i]` is identical to `*(a + i)` [2]. 

With this immense power come significant hazards:
1. **Uninitialized (Wild) Pointers**: Declaring `int *p;` without initialization leaves `p` holding random garbage. Dereferencing it will corrupt arbitrary memory.
2. **Dangling Pointers**: Pointing to memory that has been deallocated (either by calling `free()` or returning the address of a local variable from a function).
3. **Strict Aliasing Violations**: Accessing an object through a pointer of an incompatible type (type-punning). The compiler optimizes assuming different types don't overlap in memory; violating this silently corrupts data.

```{=typst}
#definition[
```

**Dangling Pointer**: A pointer whose pointee has ended its lifetime. The address remains in the pointer variable, but the memory it maps to is no longer legally yours to touch.

```{=typst}
]
```

## 4.10 Interview Deep Cuts

```{=typst}
#interview[
```

**Q: What is the difference between `*p++`, `(*p)++`, and `*(p++)`?**
- `*p++` (standard idiom): Post-increment binds tighter than dereference, but post-increment evaluates to the *old* pointer value. Thus, it dereferences the *current* address, then advances the pointer. 
- `(*p)++`: Dereferences `p` to get the value, then increments the *value*. The pointer's address does not change.
- `*(p++)`: Identical to `*p++`. The parentheses are redundant.

```{=typst}
]
```

```{=typst}
#interview[
```

**Q: How do `sizeof(array)` and `sizeof(pointer)` differ?**
When `sizeof` is applied directly to an array name (e.g., `int arr[10]`), it does *not* decay. It yields the total byte size of the entire array (40 bytes). If applied to a pointer (e.g., `int *p = arr`), it yields the size of the pointer itself (typically 8 bytes on a 64-bit system).

```{=typst}
]
```

## 4.11 Worked Examples

### Traced: Array Arithmetic

```c
#include <stddef.h>

int a[4] = {10, 20, 30, 40};
int *p = a;          // p holds address of a[0], e.g., 0x1000. *p is 10.
int val = *(p + 2);  // p + 2 evaluates to 0x1008. Dereferences to 30.
p++;                 // p is updated to 0x1004. *p is now 20.

int *q = &a[3];      // q holds 0x100C.
ptrdiff_t diff = q - p; // (0x100C - 0x1004) / sizeof(int) = 8 / 4 = 2.
```
*Watch it happen:* The subtraction yields `2` because there are exactly two elements between `a[1]` and `a[3]`.

### Callback Integration

```c
#include <stdio.h>
#include <stdlib.h>

// A comparator for qsort. Returns <0 if a goes before b.
int compare_desc(const void *a, const void *b) {
    // Cast void pointers to int pointers, then dereference
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return arg2 - arg1; // Descending order
}

int main(void) {
    int arr[] = {3, 1, 4, 1, 5};
    qsort(arr, 5, sizeof(int), compare_desc); // Pass function pointer
    return 0;
}
```

### Faded Examples

**Objective 1: Swap two values via pointers.**

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    // Step left open: complete the swap
    // _____________;
}
```

**Objective 2: Allocate and initialize via double pointer.**

```c
#include <stdlib.h>

void alloc_and_set(int **ptr, int val) {
    *ptr = malloc(sizeof(int));
    if (*ptr != NULL) {
        // Step left open: assign 'val' into the newly allocated memory
        // _____________;
    }
}
```

### References

- [1] ISO/IEC 9899:2011 (C11) §6.2.5 Types — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
- [2] ISO/IEC 9899:2011 (C11) §6.5.6 Additive operators — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
- [3] The Right-Left Rule — c-faq.com — http://c-faq.com/decl/spiral.anderson.html
- [4] ISO/IEC 9899:2011 (C11) §6.3.2.3 Pointers — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
