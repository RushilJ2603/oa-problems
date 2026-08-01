# 7. Dynamic Memory Management

Up to this point, our variables have lived either in the data segment (static duration) or on the stack (automatic duration). The stack is fast, but it imposes three severe constraints:
1. **Size must be known (mostly):** While Variable-Length Arrays (VLAs) exist, they are often dangerous or unsupported. Generally, array sizes must be known at compile time.
2. **Lifetimes are rigid:** When a function returns, its stack frame is destroyed. You cannot return a pointer to a local variable.
3. **Space is strictly limited:** The stack is typically small (often 1 to 8 megabytes). Allocating a massive array on the stack will cause a stack overflow and crash your program.

Dynamic memory allocation breaks these constraints. It allows you to ask the operating system for memory at *runtime*, from a vast pool called the **heap**. You decide exactly when this memory is requested and exactly when it is released. The cost of this freedom is responsibility: if you do not explicitly return the memory, it is lost forever.

## 7.1 The Core API: `malloc`, `calloc`, `realloc`, and `free`

```{=typst}
#heavy[
```

Dense — slow down: The heap relies on manual management through raw memory addresses, governed by exactly four functions. Managing them safely is one of the steepest learning curves in C.

```{=typst}
]
```

**Analogy:** Think of dynamic allocation like renting a storage unit. `malloc` is the rental agreement where you ask for a specific number of square feet. The manager gives you the keys (a pointer) to a unit of that size. `free` is returning the keys and terminating the lease.

![The lifecycle of a heap block](assets/s07_heap_lifecycle.png)

**Example First:**
```c
#include <stdlib.h> // Required for memory functions

// 1) Allocate space for 10 integers
int *scores = malloc(10 * sizeof(*scores));

// 2) Check for failure
if (scores == NULL) {
    // Handle error (e.g., return, exit)
}

// 3) Use the memory (it acts just like an array)
scores[0] = 42;

// 4) Return the memory when done
free(scores);
scores = NULL; // Defuse the pointer
```

**Plain-English:**
When you call `malloc`, you tell it how many bytes you need. It searches the heap for a contiguous block of free memory that large, reserves it, and hands you back a pointer to the first byte. If it can't find enough space (an Out-Of-Memory or OOM condition), it hands you back a `NULL` pointer. Once you are done with the memory, you pass that exact same pointer to `free`, which marks the block as available again.

**Technical Statement:**
The memory management functions are defined in `<stdlib.h>`.

- `void *malloc(size_t size);`
  Allocates `size` bytes of uninitialized memory. Returns a pointer to the allocated memory, or `NULL` if the request fails [1].
- `void *calloc(size_t nmemb, size_t size);`
  Allocates memory for an array of `nmemb` elements of `size` bytes each. Unlike `malloc`, it **initializes all bytes to zero** [1].
- `void free(void *ptr);`
  Deallocates the space previously allocated by `malloc`, `calloc`, or `realloc`. If `ptr` is a null pointer, no action occurs [1].

**Why here:** We use dynamic allocation when we need memory whose size isn't known until runtime, or memory that must outlive the function that created it.
**Alternative rejected:** Why not just use Variable-Length Arrays (VLAs)? Because VLAs are stack-bound. They will crash your program if they grow too large, and they vanish the moment the function returns.

**The `sizeof(*p)` Idiom:**
Notice our example used `malloc(10 * sizeof(*scores))`. This is the safest way to allocate arrays. Rather than calculating `10 * sizeof(int)`, we use the pointer itself. If the type of `scores` ever changes from `int *` to `long *` or `double *`, the `malloc` call automatically scales the byte count correctly.

```{=typst}
#keypoint[
```

**Do not cast `malloc` in C.**
In C++, you must cast the `void *` returned by `malloc`. In C, `void *` is automatically and safely promoted to any other pointer type. Writing `int *p = (int *)malloc(...)` is unnecessary clutter, and in older versions of C (C89), it could dangerously mask a missing `#include <stdlib.h>` bug [2].

```{=typst}
]
```

**Question to sit with:** If `free(scores)` doesn't erase the underlying data bytes, what happens if another part of the system or a malicious program reads that address immediately after?

**This breaks when:** You forget to `#include <stdlib.h>`. In older C standards (C89), functions without declarations were assumed to return `int`. The compiler would silently truncate the 64-bit pointer returned by `malloc` into a 32-bit integer, guaranteeing a segmentation fault when you try to use it.

## 7.2 The Memory Contract

The fundamental contract of dynamic memory is: **Every successful allocation must be paired with exactly one `free`.**

When you call `free(p)`, you are surrendering ownership of the memory block `p` points to. However, `free` only tells the memory allocator that the block is available. It does **not** erase the data inside the block, nor does it set your pointer `p` to `NULL`.

```{=typst}
#trap[
```

**The Dangling Pointer**
After calling `free(p)`, `p` becomes a *dangling pointer*. It still holds the address of the now-freed memory. If you try to read from or write to `p` after freeing it, you invoke undefined behavior. Always set `p = NULL;` immediately after `free(p)` to defuse it.

```{=typst}
]
```

## 7.3 The Big Bugs (The UB Minefield)

Because the compiler cannot enforce the memory contract, breaking it leads to catastrophic runtime bugs.

1.  **Memory Leak:** You allocate memory but lose all pointers to it before calling `free` (e.g., by reassigning the pointer). The memory remains reserved but unreachable. In a long-running program, leaks eventually exhaust system memory.
2.  **Double Free:** Calling `free` twice on the same pointer. The heap allocator tracks metadata about free and used blocks; a double free corrupts this internal metadata, usually resulting in an immediate, spectacular crash.
3.  **Use-After-Free:** Accessing memory after it has been passed to `free`. Because the allocator might have immediately reassigned that block to a different part of your program, writing to a dangling pointer will silently corrupt completely unrelated data.
4.  **Freeing a Non-Heap / Mid-Block Pointer:** You can only pass pointers to `free` that were directly returned by `malloc`, `calloc`, or `realloc`. Passing a pointer to a stack variable, or a pointer to the *middle* of an allocated block (e.g., `free(p + 1)`), destroys the heap.

## 7.4 The Subtleties of `realloc`

```{=typst}
#heavy[
```

Dense — slow down: `realloc` is powerful because it resizes existing memory, but its failure mode is a famous trap that requires a specific, non-intuitive coding pattern to use safely.

```{=typst}
]
```

**Analogy:** You realize your rented storage unit is too small. You ask the manager for a larger one. If the units next to yours are empty, the manager simply knocks down a wall, keeping your stuff in place. But if your neighbors are occupying the adjacent units, the manager must assign you a completely new, larger unit across the hall, move all your boxes for you, and then put your old unit back on the market.

![How realloc handles growth](assets/s07_realloc_behavior.png)

**Example First:**
```c
size_t old_cap = 10;
size_t new_cap = 20;
int *arr = malloc(old_cap * sizeof(*arr));

// ... later, we need more space ...

// CORRECT realloc pattern:
int *temp = realloc(arr, new_cap * sizeof(*temp));
if (temp == NULL) {
    // Handling OOM. 'arr' is STILL VALID and holds the original 10 elements.
    free(arr);
    return -1; 
}
arr = temp; // Only reassign once we know it succeeded
```

**Plain-English:**
`realloc` attempts to resize a previously allocated block of memory. If it can expand the block in place, it does so and returns the original pointer. If there isn't enough contiguous space, it allocates an entirely new block, copies your existing data over, frees the old block, and returns the pointer to the *new* block. 

**Technical Statement:**
- `void *realloc(void *ptr, size_t size);`
  Changes the size of the memory block pointed to by `ptr` to `size` bytes. If `ptr` is `NULL`, it behaves exactly like `malloc(size)`. If it returns a new pointer, the old `ptr` is automatically freed. If it fails, it returns `NULL` and the original memory block is left untouched [1].

**Why here:** We use `realloc` when we are reading stream data of unknown length (like a file or network packet) and need an array to dynamically grow as more data arrives.
**Alternative rejected:** Why not just `malloc` a new block, manually `memcpy` the old data over, and `free` the old block? Because `realloc` can often expand the block *in place* without moving any data, which is drastically faster.

```{=typst}
#trap[
```

**The `p = realloc(p, ...)` Leak**
If you write `p = realloc(p, new_size);` and the allocation fails, `realloc` returns `NULL`. You just overwrote your only pointer `p` with `NULL`. The original memory block still exists, but you lost the address—an instant, unrecoverable memory leak. Always use a temporary pointer.

```{=typst}
]
```

**Question to sit with:** If `realloc` decides to move your data to a new block, what happens to other pointers in your program that were pointing to the middle of the old block? (Answer: they instantly become dangling pointers.)

**This breaks when:** You assume the old pointer remains valid after `realloc` succeeds. You must always use the new pointer returned by `realloc`.

## 7.5 Patterns and Practices

### Multidimensional Arrays (2-D)

There are two primary ways to dynamically allocate a 2-D array (a matrix), each with distinct trade-offs.

![Two approaches to 2-D dynamic allocation](assets/s07_2d_alloc.png)

**Pattern 1: Array of Pointers (N+1 Allocations)**
You allocate an array of row pointers, then allocate each row individually.
```c
int rows = 3, cols = 4;
int **matrix = malloc(rows * sizeof(*matrix));
for (int i = 0; i < rows; i++) {
    matrix[i] = malloc(cols * sizeof(*matrix[i]));
}
// Usage: matrix[row][col] = 5;
```
*Trade-off:* Allows ragged arrays (rows of different lengths) and natural `matrix[r][c]` syntax. However, it requires a loop to allocate and a loop to free. The rows are scattered across the heap, which ruins cache locality (terrible for performance).

**Pattern 2: Contiguous Block (1 Allocation)**
You allocate a single, flat 1-D array large enough to hold all elements, and use index math to simulate 2-D access.
```c
int rows = 3, cols = 4;
int *matrix = malloc(rows * cols * sizeof(*matrix));
// Usage: matrix[row * cols + col] = 5;
```
*Trade-off:* Requires only one `malloc` and one `free`. All data is contiguous in memory, which is exceptionally fast for the CPU cache. The downside is that you must perform the `row * cols + col` math yourself.

### Detection and Discipline

Memory bugs are notoriously difficult to track down because they often crash the program far away from where the actual bug occurred. 

1.  **Ownership Rules:** Always explicitly define who "owns" a block of memory. A function that returns a `malloc`ed string transfers ownership to the caller. The documentation must clearly state: *"The caller is responsible for freeing the returned pointer."*
2.  **Tooling:** Use `valgrind` (on Linux) or compile with AddressSanitizer (`gcc -fsanitize=address -g`) to detect leaks, double-frees, and out-of-bounds heap accesses during testing [3].

## 7.6 Under the Hood: Fragmentation and Alignment

The heap isn't magic; it's a large data structure (often a linked list or trees of free blocks) managed by the C library. As a long-running program repeatedly allocates and frees chunks of different sizes, the heap becomes **fragmented**. It turns into Swiss cheese: you might have 10 MB of free memory in total, but if it consists of millions of tiny 10-byte gaps, a request for a contiguous 1 MB block will fail. 

The standard guarantees that any pointer returned by `malloc` is suitably aligned for any built-in type. You don't need to worry about alignment faults when putting an 8-byte `double` into a block returned by `malloc` [1].

## 7.7 The Embedded Reality

```{=typst}
#interview[
```

**Interviewer:** "Why is dynamic allocation often strictly banned in real-time embedded systems or aerospace software?"

**Answer:** Non-determinism, fragmentation, and safety. `malloc` has variable execution time—it might find a block instantly, or it might spend milliseconds traversing the heap searching for space. In a real-time system, a deadline miss is a system failure. Furthermore, heap fragmentation can cause an unpredictable Out-Of-Memory failure months after deployment. Finally, embedded systems often lack virtual memory or an OS to handle OOM gracefully; an allocation failure means a catastrophic crash. The solution is to use statically allocated global buffers or custom fixed-size memory pools.

```{=typst}
]
```

## 7.8 Worked Examples

### Traced: Safe Array Resize
We allocate an array, fill it, safely resize it, and release it.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 1) Initial allocation
    size_t cap = 2;
    int *arr = malloc(cap * sizeof(*arr));
    if (!arr) return 1;

    arr[0] = 10;
    arr[1] = 20;

    // 2) We need more space. Use a temp pointer!
    size_t new_cap = 5;
    int *temp = realloc(arr, new_cap * sizeof(*temp));
    
    if (temp == NULL) {
        printf("Failed to grow array.\n");
        free(arr); // Clean up the original
        return 1;
    }
    
    // 3) Success. Update the main pointer.
    arr = temp;
    arr[2] = 30; // Use the new space

    // 4) Final cleanup
    free(arr);
    return 0;
}
```

### Worked: Growable String Buffer
A common pattern for building strings of unknown length (like reading a file).

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuffer;

StringBuffer* create_buffer(size_t initial_cap) {
    StringBuffer *buf = malloc(sizeof(*buf));
    if (!buf) return NULL;
    
    buf->data = malloc(initial_cap);
    if (!buf->data) {
        free(buf); // Trap averted: free the struct if inner alloc fails
        return NULL;
    }
    
    buf->data[0] = '\0';
    buf->length = 0;
    buf->capacity = initial_cap;
    return buf;
}

int append_buffer(StringBuffer *buf, const char *str) {
    size_t str_len = strlen(str);
    
    // Check if we need to grow
    if (buf->length + str_len + 1 > buf->capacity) {
        size_t new_cap = buf->capacity == 0 ? 8 : buf->capacity * 2;
        // Keep doubling until it fits
        while (buf->length + str_len + 1 > new_cap) {
            new_cap *= 2;
        }
        
        char *temp = realloc(buf->data, new_cap);
        if (!temp) return -1; // OOM, but old data remains safe
        
        buf->data = temp;
        buf->capacity = new_cap;
    }
    
    // Append and update length
    strcpy(buf->data + buf->length, str);
    buf->length += str_len;
    return 0;
}

void destroy_buffer(StringBuffer *buf) {
    if (buf) {
        free(buf->data); // Free the inner payload first
        free(buf);       // Free the struct container
    }
}
```

### Faded: Error Path Cleanup
When an allocation succeeds but a subsequent operation fails, you must clean up before returning the error code.

```c
int process_file(const char *filename) {
    char *buffer = malloc(1024);
    if (!buffer) return -1;
    
    FILE *f = fopen(filename, "r");
    if (!f) {
        // ERROR PATH: The file failed to open.
        // What must you do before returning?
        
        // ??? (Answer: free(buffer); )
        return -2;
    }
    
    // ... process file ...
    
    fclose(f);
    free(buffer);
    return 0;
}
```

### References

- [1] ISO/IEC 9899:2011 (C11 Standard Draft N1570) — Open-Std — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
- [2] Do I cast the result of malloc? — C FAQ — https://c-faq.com/malloc/mallocnocast.html
- [3] AddressSanitizer — Google/Clang Documentation — https://clang.llvm.org/docs/AddressSanitizer.html
