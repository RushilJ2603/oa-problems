# 5. Arrays, Strings & the Array–Pointer Relationship

C does not have a native "list" data structure, nor does it have an intelligent "string" object. Instead, C provides raw, contiguous blocks of memory called arrays. The relationship between arrays and pointers in C is one of the most famous—and frequently misunderstood—design choices in programming history.

## 5.1. Arrays: Contiguous Blocks of Memory

An array is a collection of identical variables allocated sequentially in memory. 

```{=typst}
#definition[
```
**Array**: A fixed-size, contiguous sequence of elements of the same type.
```{=typst}
]
```

When you declare `int scores[5];`, you are asking the compiler to set aside exactly enough adjacent bytes to hold 5 integers. Because the storage is contiguous (unbroken), the program can instantly calculate the exact memory address of any element simply by knowing where the array starts and how big each element is.

### Declaration and Initialization

An array must have its size known at compile time (historically), and it uses zero-based indexing.

```c
int scores[5];           // Uninitialized; contains garbage values
int evens[3] = {2, 4, 6}; // Initialized with exact elements
int zeroes[100] = {0};   // Partial initialization; the rest are set to 0
```

In C99, **designated initializers** allow you to initialize specific elements by index:
```c
int sparse[5] = {[2] = 42, [4] = 99}; // Yields {0, 0, 42, 0, 99}
```

![A memory diagram of a contiguous array](assets/s05_array_memory.png)

Because arrays are raw memory blocks, C does not store their length at runtime, nor does it perform bounds checking. Asking for `scores[10]` simply reads whatever data happens to reside at that address, leading to undefined behavior.

## 5.2. Array-to-Pointer Decay

```{=typst}
#heavy[
```
Dense — slow down: The array–pointer relationship is the most frequent source of beginner confusion in C. An array is **not** a pointer, but in most situations, it will masquerade as one.
```{=typst}
]
```

**(A) Analogy**  
Imagine an array is a physical house, holding several rooms (elements). A pointer is just a piece of paper with a street address written on it. "Array decay" is a compiler trick: whenever an expression asks for the house itself, the compiler intercepts the request, grabs a piece of paper, scribbles down the street address of the front door, and hands you the paper instead.

**(D) Diagram**  
Look again at the memory diagram above. The variable `a` encompasses the whole block, but when evaluated, it yields the location of `a[0]`.

**(E) Example First**  
```c
int a[3] = {10, 20, 30};
int *p = a;  // 'a' magically turns into a pointer to its first element
```

**(P) Plain English**  
When you write the name of an array in almost any expression, C silently and automatically converts it into a pointer to its first element. This process is called **decay**. You don't write `&a[0]`; you just write `a`, and the compiler does the rest.

**(T) Technical Statement**  
Except when it is the operand of the `sizeof` operator, or the unary `&` (address-of) operator, or is a string literal used to initialize an array, an expression that has type "array of type" is converted to an expression with type "pointer to type" that points to the initial element of the array object [1].

This explains the famous equivalence of subscripting. The array indexing operator `a[i]` is defined by the standard to be exactly equivalent to `*(a + i)` [2]. Because addition is commutative, `*(a + i)` is the same as `*(i + a)`. Therefore, the bizarre expression `i[a]` is perfectly valid C!

```{=typst}
#trap[
```
**"An array is just a pointer."**  
This is false. They are fundamentally different types. You can prove this using the `sizeof` exception. If `int a[5];` was a pointer, `sizeof(a)` would yield 8 (on a 64-bit machine). Instead, it yields 20 (5 elements × 4 bytes). The array *is* the block of memory; it only *evaluates to* a pointer when you use it.
```{=typst}
]
```

## 5.3. Passing Arrays to Functions

Because arrays decay into pointers in expressions, they also decay when passed as arguments to functions.

```c
void print_scores(int arr[]) {
    // arr is just an int* here!
}

int main(void) {
    int scores[5] = {1, 2, 3, 4, 5};
    print_scores(scores); 
}
```

When `print_scores(scores)` is called, the array `scores` decays into an `int*`. The function parameter `int arr[]` is secretly rewritten by the compiler to `int *arr`. The callee receives a copy of the address, not a copy of the array.

This creates a significant boundary: **the function loses the length of the array**.

```{=typst}
#trap[
```
**Using sizeof to find length inside a function.**  
```c
void bad_print(int arr[5]) {
    size_t len = sizeof(arr) / sizeof(arr[0]); // FAILS!
}
```
Because `arr` decayed to an `int*`, `sizeof(arr)` is the size of a pointer (e.g., 8 bytes), not the size of the array. The formula evaluates to $8 / 4 = 2$. You must **always** pass the length as a separate parameter: `void good_print(int *arr, size_t length)`.
```{=typst}
]
```

## 5.4. Strings: Null-Terminated `char` Arrays

C does not have a distinct string type. A string is simply an array of characters, with a strict convention: the string ends at the first null character `'\0'` (byte value 0).

![A char array holding "Hello" and a null terminator](assets/s05_string.png)

```{=typst}
#keypoint[
```
A string's memory must always be at least one byte larger than the visible text to hold the `'\0'` terminator.
```{=typst}
]
```

There are two ways to declare a string, and they behave very differently in memory [3]:

```c
// 1. Initializing an array (Read-Write)
char s[] = "hello"; 
// The compiler allocates a 6-byte array on the stack and copies "hello\0" into it.
// s[0] = 'H'; is perfectly valid.

// 2. Initializing a pointer (Read-Only)
char *p = "hello";
// The string literal "hello\0" is stored in a read-only data segment of the binary.
// p is a pointer directed at that read-only memory.
```

```{=typst}
#interview[
```
**Interviewer:** "Why does `char *s = "x"; s[0] = 'Y';` crash the program?"  
**Answer:** "The string literal `"x"` is stored in the read-only data segment. `s` is a pointer pointing there. Attempting to write to read-only memory causes a segmentation fault. To make it modifiable, it must be declared as an array: `char s[] = "x";`, which copies the literal onto the stack."
```{=typst}
]
```

## 5.5. The `<string.h>` Library

Because arrays cannot be assigned with `=` or compared with `==`, the C standard library provides `<string.h>` for string manipulation [4]. 

- **`strlen(s)`**: Counts characters until `'\0'`. Returns `size_t`. Does *not* include the terminator.
- **`strcpy(dest, src)`**: Copies `src` to `dest`, including `'\0'`.
- **`strcmp(s1, s2)`**: Compares strings alphabetically. Returns `0` if exactly equal.
- **`memcpy(dest, src, n)`**: Copies exactly `n` raw bytes.
- **`memmove(dest, src, n)`**: Safely copies `n` bytes even if `dest` and `src` overlap.
- **`memset(dest, val, n)`**: Fills `n` bytes of memory with the byte `val`.

```{=typst}
#trap[
```
**Buffer Overflows & `memcpy` Overlap**  
`strcpy` has no idea how large `dest` is. If `src` is longer than `dest`, it will blindly overwrite adjacent memory (a buffer overflow).  
Furthermore, `memcpy` assumes the source and destination blocks do not overlap. If they do, the behavior is undefined. Always use `memmove` if the blocks might overlap.
```{=typst}
]
```

## 5.6. Multi-dimensional Arrays

```{=typst}
#heavy[
```
Dense — slow down: A 2D array in C is physically 1D in memory. Distinguishing true 2D arrays from arrays of pointers is a critical skill.
```{=typst}
]
```

**(A) Analogy**  
Think of a calendar. It looks like a 2D grid of weeks and days. But time is actually 1D—a continuous, unbroken timeline. C stores 2D arrays the same way: as one continuous strip, placing one row immediately after another.

**(D) Diagram**  
![Diagram array-of-pointers vs a true 2D block](assets/s05_2d_vs_ptrarray.png)

**(E) Example First**  
```c
int grid[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
// Memory layout: 1, 2, 3, 4, 5, 6 (Row-Major Order)
```

**(P) Plain English**  
A 2D array is literally an "array of arrays". Because elements are contiguous, `grid` is just 6 integers back-to-back. To find `grid[row][col]`, the compiler does math: $address = base + (row \times width + col) \times size$. 

**(T) Technical Statement**  
Because `grid` is an array of 3-element integer arrays, it decays into a **pointer to an array**: `int (*p)[3]`.

This leads to the most important type distinction in C pointer syntax:

1. **`int (*p)[3]`**: A pointer to an array of 3 integers. This is what `grid` decays to.
2. **`int *p[3]`**: An array of 3 pointers to integers. This is what you use when you have distinct strings of different lengths.
3. **`int **p`**: A pointer to a pointer. It points to a single memory address holding another address.

```{=typst}
#interview[
```
**Interviewer:** "How do you map a 2D coordinate `(r, c)` into a 1D array of `WIDTH` columns?"  
**Answer:** "The 1D index is $r \times WIDTH + c$. We skip $r$ full rows of size $WIDTH$, then step forward by $c$ elements."
```{=typst}
]
```

## 5.7. Variable-Length Arrays (VLAs)

Introduced in C99, Variable-Length Arrays allow you to declare an array size using a runtime variable:

```c
void process(int n) {
    int temp[n]; // Size evaluated at runtime
}
```

While convenient, VLAs are dangerous. They allocate memory on the call stack, which is tightly limited. If `n` is suspiciously large (e.g., provided by user input), the VLA will instantly blow the stack, crashing the program (Stack Overflow). 

Because of these security hazards, C11 made VLAs optional. In C23, VLA *types* are mandatory (useful for pointer arithmetic on multi-dimensional bounds), but creating VLA *objects* on the stack remains an optional feature compilers do not have to support [5].

## 5.8. Worked Examples

### Traced: Array Decay in Action
```c
int a[5] = {10, 20, 30, 40, 50};
```
- `a`: Decays to `&a[0]`. Prints the memory address of the first element.
- `&a[0]`: Exactly the same as `a`.
- `a + 1`: Pointer arithmetic scales by the size of the element. Points to `20`.
- `*(a + 2)`: Dereferences the pointer offset by 2 elements. Evaluates to `30`. Equivalent to `a[2]`.
- `sizeof(a)`: Exception to decay! Evaluates to `20` (assuming 4-byte `int`).
- `sizeof(a + 0)`: The `+` operator forces decay. Evaluates to the size of an `int*` (e.g., `8`).

### Worked: In-Place String Reversal
Reversing a string in place requires two pointers (or indices) moving toward the center, swapping characters until they meet.

```c
#include <string.h>

void reverse_string(char s[]) {
    if (s == NULL) return;
    
    size_t len = strlen(s);
    if (len <= 1) return;
    
    size_t left = 0;
    size_t right = len - 1; // Start before the '\0'
    
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}
```

### Faded: Implementing `my_strlen`
Complete the loop condition to stop when it hits the null terminator.

```c
size_t my_strlen(const char *s) {
    size_t count = 0;
    // Walk the pointer forward until it hits the terminator.
    // Notice how we don't need to know the length to find the end!
    while (_________________) {
        count++;
        s++;
    }
    return count;
}
```
*(Hint: Dereference the pointer `*s` and check if it equals `'\0'`.)*

### References
[1] ISO/IEC 9899:2011 (C11) §6.3.2.1 — Lvalues, arrays, and function designators — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[2] ISO/IEC 9899:2011 (C11) §6.5.2.1 — Array subscripting — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[3] ISO/IEC 9899:2011 (C11) §6.4.5 — String literals — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[4] ISO/IEC 9899:2011 (C11) §7.24 — String handling <string.h> — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[5] C23 Working Draft N3096 §6.7.6.2 — Array declarators — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf
