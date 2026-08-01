# 8. Structures, Unions, Enums & Bit-fields

When primitive types like `int` and `float` are insufficient to model complex data, C provides composite types. Structures group heterogeneous data sequentially, unions overlap them in the same space, enumerations map names to integers, and bit-fields carve up sub-byte boundaries.

## 8.1 Structures: Grouping Data

A `struct` aggregates multiple variables (members) under a single namespace. 

```{=typst}
#definition[
```

A *structure* is a contiguous block of memory containing a sequence of named members of potentially different types.

```{=typst}
]
```

### 8.1.1 Declaration and the `typedef` Idiom

Structures require a tag or a `typedef`. A struct tag alone mandates the `struct` keyword for every declaration.

```c
struct Point {
    int x;
    int y;
};

struct Point p1; // 'struct' is mandatory
```

To omit the `struct` keyword, wrap the declaration in a `typedef`. This creates an alias for the type.

```c
typedef struct {
    int x;
    int y;
} Point;

Point p2; // Cleaner syntax
```

### 8.1.2 Initialization and Member Access

Members are accessed via the dot operator (`.`). Historically, structures were initialized positionally, which breaks if member order changes. Modern C (C99) favors *designated initializers*, which map values by name [5].

```c
// Positional (brittle)
Point p_old = {10, 20}; 

// C99 Designated (robust)
Point p_new = { .y = 20, .x = 10 }; 
```

Unspecified members in a designated initializer are zero-initialized.

### 8.1.3 Nested and Anonymous Structures

Structures can be nested. Since C11, a nested structure or union can be *anonymous* (unnamed), projecting its members directly into the enclosing structure's scope [1].

```c
typedef struct {
    int entity_id;
    struct {         // Anonymous struct (C11)
        float x;
        float y;
    };
} Player;

Player p = { .entity_id = 1, .x = 5.5f, .y = 10.0f };
// p.x is valid; no intermediate name needed
```

## 8.2 Memory Layout: Alignment and Padding

```{=typst}
#heavy[
```

Dense — slow down: A struct's size in memory is rarely the exact sum of its members' sizes. The compiler injects invisible gaps.

```{=typst}
]
```

Think of a cargo ship holding differently sized shipping containers. If a heavy 40-foot container is mandated to only sit on main load-bearing beams spaced 40 feet apart, placing a 10-foot box first means you must leave 30 feet of empty space before the 40-foot container can be safely loaded.

![Struct padding byte layout](assets/s08_padding.png)

Consider this structure:

```c
struct bad_layout {
    char a;  // 1 byte
    int b;   // 4 bytes
    char c;  // 1 byte
};
```

One might expect `sizeof(struct bad_layout)` to be 6 bytes. It is typically 12 bytes.

The CPU fetches memory in aligned chunks (words). Reading an `int` (4 bytes) from an address not divisible by 4 requires multiple memory fetches or triggers a hardware alignment fault (especially on ARM architectures). To guarantee fast, fault-free access, the compiler enforces *alignment requirements*, queried via `_Alignof(type)` (C11).

To satisfy this, the compiler injects *padding bytes* after `a` so `b` starts on a 4-byte boundary. It also adds *trailing padding* after `c` so that in an array of this struct, the next element's `a` and `b` maintain correct alignment. 

The rule is absolute: a structure's overall alignment requirement is the largest alignment requirement of any of its members. The structure's total size must be a multiple of this overall alignment.

```{=typst}
#trap[
```

Assuming you can read/write structs directly to disk or network sockets as raw byte streams. Padding bytes contain garbage memory, and layout varies by compiler and architecture.

```{=typst}
]
```

### 8.2.1 Shrinking Structs: Reordering

To minimize wasted padding, order members from largest alignment requirement to smallest.

```c
struct good_layout {
    int b;   // 4 bytes
    char a;  // 1 byte
    char c;  // 1 byte
};
```

Here, `sizeof(struct good_layout)` is 8 bytes (4 for `b`, 2 for `a` and `c`, plus 2 bytes of trailing padding to reach a multiple of 4).

### 8.2.2 Packed Structures

When communicating with hardware or parsing network packets, padding is unacceptable. You can force the compiler to drop padding using compiler-specific extensions like `__attribute__((packed))` in GCC/Clang [2] or `#pragma pack` in MSVC.

```c
struct __attribute__((packed)) network_header {
    char type;
    int payload_length;
}; // Size is exactly 5 bytes
```

*Trade-off*: Packed structures save memory but incur severe performance penalties on architectures that do not support unaligned loads. The compiler must emit slower, byte-by-byte shifting instructions to read the `int`.

## 8.3 Pointers to Structures and `->`

Structures are passed by value by default. Passing a large struct to a function copies every byte, which is expensive. 

```{=typst}
#keypoint[
```

Always pass structures by pointer to avoid copy overhead, using the `const` qualifier if the function should not modify it.

```{=typst}
]
```

When holding a pointer to a struct, the `.` operator cannot be used directly without dereferencing (`(*ptr).member`). C provides the arrow operator `->` as syntactic sugar.

```c
void move(Point *p, int dx, int dy) {
    p->x += dx;  // Equivalent to (*p).x += dx
    p->y += dy;
}
```

Functions can return structures by value. Modern compilers optimize this using Return Value Optimization (RVO), allocating the space in the caller's stack frame, but returning via an out-pointer remains a common C idiom for explicitness.

## 8.4 Self-Referential Structures

A structure cannot contain an instance of itself (its size would be infinite). It can, however, contain a *pointer* to its own type, because pointers have a fixed, known size. This is the foundation of linked lists and trees.

```c
struct Node {
    int data;
    struct Node *next; // Valid: pointer to incomplete type
};
```

This requires using the `struct` tag approach; a `typedef` alias is not fully defined until the closing brace, so it cannot be used inside the definition.

## 8.5 Unions: Overlapping Storage

```{=typst}
#heavy[
```

Dense — slow down: Unions look like structs, but their members do not exist side-by-side. They fight for the same physical memory.

```{=typst}
]
```

Think of a single hotel safe. You can store your laptop in it, or you can store your passport in it. If you put your laptop in, the passport must come out. They share the same capacity.

![Union members overlapping in memory](assets/s08_union.png)

```c
#include <stdint.h>

union Data {
    uint32_t raw;
    float f;
    char str[4];
};

union Data u;
```

A `union` allocates exactly enough memory to hold its *largest* member. In `union Data`, all three members start at the exact same memory address (offset 0). Writing to `u.f` overwrites whatever was in `u.raw`.

### 8.5.1 Type Punning (The C Way)

If you write to the `float` member and read from the `uint32_t` member, what happens? You are reading the raw IEEE-754 floating-point bits as an integer.

This is called *type punning*. The C standard (C99 and C11) explicitly guarantees that reading from a different union member than the one last written is valid and yields the object representation of the overlapping bytes [3].

```{=typst}
#trap[
```

C++ differs dramatically here. In C++, reading an inactive union member is Undefined Behavior (Strict Aliasing violation). In C, it is a legally sanctioned workaround for strict aliasing.

```{=typst}
]
```

### 8.5.2 Tagged Unions (Variant Types)

Because a union cannot know which member is currently "active", they are almost always paired with a state indicator, creating a *tagged union*.

```c
typedef enum { TYPE_INT, TYPE_FLOAT } DataType;

typedef struct {
    DataType type;        // The "tag"
    union {               // Anonymous union
        int i;
        float f;
    };
} Variant;
```

## 8.6 Enumerations (Enums)

Enums assign names to integer constants. 

```c
typedef enum {
    STATE_IDLE,       // 0
    STATE_RUNNING,    // 1
    STATE_ERROR = -1  // Explicit value
} ProcessState;
```

By default, the first enumerator is `0` and subsequent ones increment by 1. 

```{=typst}
#keypoint[
```

In C, `enum` constants leak into the surrounding scope. You cannot have two enums in the same scope that both define an `IDLE` state. This is why C enums are usually prefixed (e.g., `STATE_IDLE`).

```{=typst}
]
```

The underlying type of an enum is implementation-defined; the compiler chooses an integer type capable of representing all values (often just `int`) [4]. 

## 8.7 Bit-fields

When mapping hardware registers or packing data intensely, standard types are too granular. Bit-fields allow you to specify the exact number of bits a member occupies within an integer word [1].

![Bit-field mapping](assets/s08_bitfield.png)

```c
#include <stdint.h>

struct Register {
    uint16_t enable    : 1;  // Bit 0: EN
    uint16_t interrupt : 1;  // Bit 1: INT
    uint16_t mode      : 3;  // Bits 2-4: MODE
    uint16_t reserved  : 10; // Bits 5-14: RESERVED
    uint16_t ready     : 1;  // Bit 15: READY
};
```

This packs all five variables into a single 16-bit word.

```{=typst}
#trap[
```

Bit-field ordering is implementation-defined. GCC on x86 typically packs them from Least Significant Bit (LSB) to Most Significant Bit (MSB), while others might pack MSB to LSB. Never use bit-fields to map exact hardware registers if portability is required; use bitwise operations instead.

```{=typst}
]
```

## 8.8 Flexible Array Members (FAMs)

Historically, programmers used the "struct hack" (an array of size 1 at the end of a struct) to allocate variable-length data. C99 formalized this with the Flexible Array Member [1].

```c
#include <stdlib.h>

typedef struct {
    int capacity;
    int data[]; // Must be the last member, incomplete size
} Vector;

// Allocate the struct PLUS room for 100 ints
Vector *vec = malloc(sizeof(Vector) + 100 * sizeof(int));
```

The `sizeof(Vector)` excludes the `data` array entirely. 

## 8.9 Worked Examples

### Traced: Struct Padding and Reordering

**Goal:** Analyze memory layout on a 64-bit system (where pointers are 8 bytes).

```c
struct Trace {
    char a;      // size: 1, align: 1. Offset: 0
    // padding: 7 bytes to align ptr
    double *ptr; // size: 8, align: 8. Offset: 8
    int b;       // size: 4, align: 4. Offset: 16
    // padding: 4 bytes to align total size to 8 (max alignment)
};
```
Total size: `1 + 7(pad) + 8 + 4 + 4(pad) = 24 bytes`.

*Reordered for space:*
```c
struct TraceOptimized {
    double *ptr; // size: 8. Offset: 0
    int b;       // size: 4. Offset: 8
    char a;      // size: 1. Offset: 12
    // padding: 3 bytes to reach 16 (multiple of 8)
};
```
Total size: `8 + 4 + 1 + 3(pad) = 16 bytes`. We saved 8 bytes per instance.

```{=typst}
#interview[
```

**Q:** How do you find the byte offset of a member inside a struct without creating an instance?
**A:** Use the `offsetof(type, member)` macro from `<stddef.h>`. It casts a null pointer to the struct type and retrieves the address of the member, resolving at compile-time.

```{=typst}
]
```

### Worked: Tagged Union Variant

**Goal:** Safely handle dynamic data types.

```c
#include <stdio.h>

typedef enum { INT_VAL, FLOAT_VAL } ValType;

typedef struct {
    ValType type;
    union {
        int i;
        float f;
    };
} Value;

void print_value(const Value *v) {
    switch (v->type) {
        case INT_VAL:   printf("Int: %d\n", v->i); break;
        case FLOAT_VAL: printf("Float: %f\n", v->f); break;
    }
}
```

### Faded: Self-Referential Tree Node

Complete the `right` child pointer declaration for this binary tree node.

```c
struct TreeNode {
    int payload;
    struct TreeNode *left;
    // 1. Declare the right child pointer
    // ___ ___ ___
};
```

## References

- [1] ISO/IEC 9899:2011 (C11) §6.7.2.1 Structure and union specifiers — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
- [2] GCC Manual: Type Attributes (packed) — gcc.gnu.org — https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html
- [3] ISO/IEC 9899:2011 (C11) §6.5.2.3 Structure and union members (Type punning) — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
- [4] ISO/IEC 9899:2011 (C11) §6.7.2.2 Enumeration specifiers — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
- [5] ISO/IEC 9899:2011 (C11) §6.7.9 Initialization — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
