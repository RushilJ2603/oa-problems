# Memory and the Execution Model: Stack, Heap, and Storage

When a C++ program runs, every variable, every function call, and every dynamically allocated object occupies a concrete place in the process's address space. Interviews and competitive programming both assume you know *where* data lives, *how long* it lives, and *what happens* when those rules are broken. This section is the coherent map of that territory.

::: heavy
Dense section — slow down. The stack, heap, and storage-duration rules are mentioned everywhere but rarely explained as one mechanism. Read the layout first, then the call-stack walk-through, before the overflow and heap material.
:::

## The program in memory

When the operating system loads your executable, it does not dump a shapeless blob into RAM. It lays out a **process address space** — a virtual map of regions, each with a distinct job. Think of a warehouse with labelled zones: one locked room for the blueprints (code), one shelf for pre-filled boxes (initialised data), one aisle of empty boxes that must start at zero (BSS), a growing free-store yard (heap), and a rapidly used scratch desk that shrinks and grows from the other end (stack).

![The memory layout of a running process: code and static data low, the heap growing up, the stack growing down.](assets/s53_memory_layout.png)

On a typical Linux/Unix-like layout (high addresses at the top, low at the bottom), the picture is roughly:

| Region (high → low) | What lives there |
|---|---|
| Command line / environment | `argv`, `envp`, and related strings the OS places for the process |
| **Stack** (grows *downward*) | Function frames: return addresses, locals, parameters, saved registers |
| (unused gap) | Guard / free virtual space between stack and heap |
| **Heap** (grows *upward*) | Dynamically allocated blocks from `new` / `malloc` |
| **BSS** | Uninitialised (or zero-initialised) globals and statics |
| **Data** (initialised) | Globals/statics with explicit non-zero initialisers; string literals often nearby in read-only data |
| **Text / code** | Machine instructions of your functions; typically read-only and executable |

### Text (code) segment

The **text segment** holds the compiled machine code. Function bodies live here as instructions, not as "variables". On modern systems this region is usually marked read-only and executable so accidental writes cannot overwrite code.

```cpp
void greet() {
    // The *instructions* for greet live in the text segment.
    // Its local variables, when called, live on the stack.
}
```

### Initialised data segment

Globals and `static` objects that have an explicit non-zero initialiser are placed in the **data segment**. Their values are baked into the executable and loaded into memory when the process starts.

```cpp
int g_counter = 42;           // data segment (initialised)
static double pi = 3.14159;   // data segment (internal linkage, still static storage)
const char* msg = "hello";    // pointer may be in data; "hello" often in read-only data (.rodata)
```

### BSS (Block Started by Symbol)

The **BSS** segment holds globals and statics that are zero-initialised (or left without an explicit initialiser, which for static storage means zero-init). The executable need not store a run of zeros on disk; the loader simply reserves a zeroed region of the right size.

```cpp
int g_zeros;                  // BSS: zero-initialised
static int table[1000];       // BSS: 1000 ints, all zero — cheap in the binary
```

::: keypoint
BSS exists so large zeroed arrays and globals cost almost nothing in the executable file size. The OS maps zero-filled pages at load time.
:::

### Heap

The **heap** (also called the free store in C++ terminology) is a large pool of memory the program may request at run time. It typically grows toward higher addresses as more blocks are allocated. You reach it only through pointers (or references bound to heap objects) — never by naming a heap block directly.

### Stack

The **stack** holds **activation records** (stack frames) for active function calls. On nearly all mainstream ABIs it grows toward *lower* addresses: each new call pushes a frame "downward". When the function returns, the frame is popped and that storage is gone.

### Command line and environment

Above the stack (or in a dedicated high region, depending on the OS), the process receives `argc`/`argv` and the environment strings. You read them in `main`; you do not allocate them yourself.

```cpp
#include <iostream>

int main(int argc, char* argv[]) {
    // argv points into OS-provided memory for the process image —
    // not something you new/delete.
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }
}
```

::: interview
"Describe the memory layout of a running C++ process." Walk high-to-low (or low-to-high consistently): text, data, BSS, heap growing up, stack growing down, plus argv/env. Name one example of what lives in each region.
:::

## Storage duration and how it maps to the segments

C++ does not ask you to pick "stack" or "heap" as keywords. Instead it defines **storage duration** — which means *how long an object's storage lasts*. The compiler and run-time then map that policy onto the segments above.

::: definition
**Storage duration** is the rule that decides when an object's memory is obtained and when it is released. C++ has four: automatic, static, dynamic, and thread.
:::

### Automatic storage duration → stack

Locals inside a function or block (unless marked `static` or `thread_local`) have **automatic storage duration**. Their storage is allocated when the block is entered and released when the block is exited — implemented as slots inside the current stack frame.

```cpp
void f() {
    int x = 10;           // automatic: lives in f's stack frame
    int arr[100];         // automatic: 100 ints on the stack
    {
        double y = 1.5;   // automatic: nested block; gone at closing brace
    }
    // y no longer exists
} // x and arr destroyed here
```

**Lifetime**: constructors run when the declaration is reached; destructors run in reverse order of construction when the scope ends.

### Static storage duration → data / BSS

Globals, namespace-scope variables, and anything declared `static` (including `static` locals) have **static storage duration**. They exist for the entire run of the program. Non-zero initialised ones → data segment; zero-initialised → BSS.

```cpp
int g = 1;                // static storage, data segment

void counter() {
    static int n = 0;     // static storage; initialised *once*
    ++n;                  // retains value across calls
}
```

::: keypoint
A **static local** is initialised the first time control passes through its declaration (for non-`constexpr` locals this is typically on the first call). After that, the initialiser is skipped. The object still has function-local *name visibility*, but program-long *lifetime*.
:::

```cpp
#include <iostream>

void once_demo() {
    static int n = 0;   // runs only on the first call
    std::cout << ++n << '\n';
}

int main() {
    once_demo(); // 1
    once_demo(); // 2
    once_demo(); // 3
}
```

For function-local `static` objects of non-trivial type, C++11 also guarantees that concurrent first-entry initialisation is thread-safe on conforming implementations (the "magic static" / concurrent init guard). Prefer not to rely on subtle ordering between *different* static objects across translation units — that is the **static initialisation order fiasco**.

### Dynamic storage duration → heap

Objects created with `new` (or C's `malloc`) have **dynamic storage duration**. They live until you explicitly destroy/release them with `delete` / `free` (or until a smart pointer does so for you).

```cpp
#include <new>

int* p = new int(42);     // dynamic: object on the heap; p itself is automatic
delete p;                 // ends the int's lifetime; storage returned to the allocator
```

### Thread storage duration → per-thread static-like storage

`thread_local` gives each thread its own instance. Lifetime spans the thread; storage is neither the shared data/BSS picture nor a single process-wide static.

```cpp
thread_local int tls_id = 0;  // one copy per thread
```

### Quick mapping

| Storage duration | Typical declaration | Where it lives | Lifetime |
|---|---|---|---|
| Automatic | local / parameter | stack frame | enclosing block |
| Static | global / `static` | data or BSS | whole program |
| Dynamic | `new` / `malloc` | heap | until `delete` / `free` |
| Thread | `thread_local` | per-thread storage | that thread's life |

::: interview
"What is the difference between scope and lifetime?" Scope is about *name visibility* (where you may write the identifier). Lifetime / storage duration is about *when the object exists in memory*. A static local has narrow scope but long lifetime.
:::

## The call stack in depth

Imagine a cafeteria tray stack. Each function call places a new tray on top; when the function finishes, that tray is removed. You can only work with the top tray — the current function. That tray is the **stack frame** (also called an **activation record**).

![The call stack: each call pushes a frame; the stack grows downward and unwinds on return.](assets/s53_call_frames.png)

### Anatomy of a stack frame

Exact layout is ABI-specific (System V AMD64, Microsoft x64, ARM AAPCS, …), but the *contents* of a frame are the same idea everywhere:

- **Return address** — where execution resumes in the caller after this function returns.
- **Saved registers** — callee-saved registers the function must restore before returning (so the caller sees its values intact).
- **Parameters / arguments** — some in registers, overflow on the stack (calling convention dependent).
- **Local variables** — automatic objects for this invocation.
- **Frame pointer** (optional) — a stable base to address locals/parameters while the stack pointer moves (many optimised builds omit a dedicated frame pointer).

The **stack pointer** (e.g. `rsp` on x86-64) always refers to the current top of the stack. A call typically decreases it (stack grows down) to make room for the new frame; a return increases it, reclaiming the frame.

### Call pushes a frame; return pops it

```cpp
#include <iostream>

int add(int a, int b) {
    int sum = a + b;   // local in add's frame
    return sum;
}

int main() {
    int x = 3;         // local in main's frame
    int y = add(x, 4); // call: push add's frame; return: pop it
    std::cout << y << '\n';
}
```

Mechanically, ignoring ABI micro-detail:

1. `main` is running; its frame holds `x`, `y`, …
2. The call to `add` saves a return address and allocates `add`'s frame (`a`, `b`, `sum`, …). The stack pointer moves downward.
3. `add` computes and places the return value where the calling convention requires (often a register such as `eax`/`rax`).
4. `add` returns: its frame is released, the stack pointer moves back up, and control jumps to the saved return address in `main`.
5. `y` receives the returned value. `sum` no longer exists.

### Why locals vanish after return

When the frame is popped, the memory that held those locals is simply reusable stack space. The *bits* may still sit there until overwritten, but the object's **lifetime has ended**. Holding a pointer or reference to that storage is undefined behaviour — the classic dangling-return-of-local trap.

```cpp
int* bad() {
    int local = 42;
    return &local;    // BUG: address of automatic storage
}

int& also_bad() {
    int local = 7;
    return local;     // BUG: reference to automatic storage
}

int main() {
    int* p = bad();   // p is dangling
    // *p  → undefined behaviour
}
```

::: trap
Returning a pointer or reference to a function-local (automatic) variable is always wrong. The callee's frame is gone; the caller holds a dangling address. Return by value, or return a pointer/reference to something with longer lifetime (static, caller-owned, or heap via smart pointer).
:::

Returning a *value* is fine — the result is copied or moved into the caller's context (or constructed straight into the caller's object via RVO/NRVO):

```cpp
#include <string>

std::string fine() {
    std::string s = "ok";
    return s;   // OK: by value (often elided)
}
```

### Recursion and nested frames

Each recursive call gets its **own** frame. Deep recursion means a tall tower of frames; that is why recursion consumes stack space proportional to depth.

```cpp
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);  // each call: another frame
}
```

::: interview
"Why does returning a local pointer break?" Because automatic storage is tied to the stack frame. After `return`, that frame is popped, the object's lifetime ends, and any pointer into it dangles. Contrast with returning the address of a `static` local (lifetime OK, but usually poor design) or a heap object (lifetime until `delete`).
:::

## Stack overflow

The stack is **fast** and **small**. Typical default sizes are on the order of **1–8 MB** per thread (OS and linker dependent — Windows defaults are often 1 MB; many Linux setups are 8 MB). That ceiling is fixed for the thread unless you raise it explicitly.

::: definition
A **stack overflow** occurs when the call stack grows beyond the reserved stack region — usually from unbounded recursion or enormous automatic objects — and the process crashes (segfault / stack overflow exception).
:::

### Cause 1: deep or infinite recursion

```cpp
void infinite() {
    infinite();   // each call pushes a frame until the stack is exhausted
}
```

Even *finite* but deep recursion can blow the stack. In competitive programming, recursive DFS on a graph of $10^5$ nodes, or recursion depth proportional to $n$ for $n \sim 10^6$, is a common silent killer on platforms with small stacks.

### Cause 2: huge locals

```cpp
void boom() {
    int a[10'000'000];  // ~40 MB if sizeof(int)==4 — often larger than the whole stack
    a[0] = 1;
}
```

A large automatic array is allocated *in the frame* when the function is entered. There is no `new`, so this is not a heap allocation — it competes for the same few megabytes as every other frame.

::: trap
`int a[10000000];` inside a function is a stack allocation, not a heap one. Prefer `std::vector<int> a(10'000'000);` (heap-backed) or a static/global buffer when sizes are huge. In CP, a global `static int a[N];` in BSS is a frequent pattern for large scratch arrays.
:::

### Why CP recursion depth is limited — and how to mitigate

| Mitigation | Idea |
|---|---|
| Iterative rewrite | Explicit `std::stack` / loop instead of call recursion; frames move to the heap-backed container |
| Heap allocation | Large buffers via `std::vector` / `new`, not VLAs or giant locals |
| Larger stack | Raise stack size (`ulimit -s`, linker `/STACK`, `pthread_attr_setstacksize`) when the environment allows |
| Tail-call hopes | Do **not** rely on tail-call optimisation in C++; it is not guaranteed |

Contrast: the heap is typically limited by available virtual memory / RAM (gigabytes), not by a few megabytes. A million-node structure almost always belongs on the heap (or in static BSS), not as nested automatic frames.

::: interview
"What causes a stack overflow?" Two staples: (1) recursion deeper than the stack can hold, (2) very large automatic objects. Fix by reducing depth, switching to iteration, or moving big data to the heap/static storage.
:::

## The heap in depth

If the stack is a fixed-size tray tower, the heap is a large yard where you rent plots of any size, for as long as you need, and must return them when finished.

### Allocation and deallocation mechanics

C++ obtains dynamic objects with `new` / `new[]` and releases them with `delete` / `delete[]`. C-style `malloc` / `free` (from `<cstdlib>`) allocate raw untyped storage without constructors/destructors.

```cpp
#include <cstdlib>
#include <new>

// C++ free store
int* p = new int(5);          // allocate + construct
delete p;                     // destroy + deallocate

int* arr = new int[100]();    // value-initialised array
delete[] arr;                 // must match new[]

// C allocator (no constructors)
void* raw = std::malloc(100 * sizeof(int));
std::free(raw);
```

::: trap
`new` pairs with `delete`; `new[]` pairs with `delete[]`. Mixing them is undefined behaviour. Never `free` memory from `new`, or `delete` memory from `malloc`.
:::

### Allocator intuition: free lists and bookkeeping

At a high level, the heap **allocator** (the library behind `new`/`malloc`) maintains metadata about which regions are in use and which are free — often as **free lists** or more sophisticated segregated/bins structures (as in modern `malloc` implementations). A request walks or indexes that metadata, carves out a block (possibly splitting a larger free chunk), and returns a pointer to usable storage. A free operation marks the block reusable, sometimes coalescing adjacent free neighbours to fight fragmentation.

You do not see this bookkeeping in the pointer value you hold; it usually sits *beside* or *before* your block in allocator-owned headers. That is one reason heap traffic has overhead the stack does not: every allocation may lock, search, split, and update metadata.

### Fragmentation

**Fragmentation** is the heap analogue of a full parking lot with no two adjacent spaces: total free bytes may be enough for a request, yet no *contiguous* free region is large enough. External fragmentation (scattered holes) and internal fragmentation (over-allocation / alignment padding inside a block) both waste capacity and can make large allocations fail even when "plenty of memory" appears free in aggregate.

### Why the heap is slower than the stack

| Stack allocation | Heap allocation |
|---|---|
| Adjust stack pointer (a few instructions) | Call into allocator; search/update free structures |
| LIFO order — perfect locality of frames | Blocks scattered; poorer cache behaviour |
| No per-block metadata in your code | Metadata, possible locks, syscalls when growing the arena (`brk`/`mmap`) |
| Fixed small budget | Large budget, higher constant factors |

Stack allocation is essentially free in steady state; heap allocation is a library algorithm plus possible kernel involvement when the arena must grow.

### Leaks and dangling pointers (recap)

- **Memory leak**: you allocate and lose the last pointer without `delete` — the block stays reserved until process exit.
- **Dangling pointer**: you `delete` (or leave a scope) but still hold an address into freed or ended storage — dereference is UB.
- **Double free**: `delete` twice on the same address — UB; often corrupts allocator metadata.

```cpp
int* p = new int(1);
delete p;
// delete p;   // double free — UB
p = nullptr;   // defensive: do not leave a dangling non-null pointer
```

### RAII and smart pointers — the modern answer

Manual `new`/`delete` pairing fails under early returns and exceptions. **RAII** (Resource Acquisition Is Initialisation) ties resource lifetime to object lifetime: acquire in the constructor, release in the destructor. Modern C++ encodes this for memory with smart pointers in `<memory>` — covered in depth in **s41**.

```cpp
#include <memory>

void safe() {
    auto p = std::make_unique<int[]>(1'000'000);  // heap data, automatic cleanup
    // no delete — unique_ptr destructor frees on scope exit
}
```

::: keypoint
Prefer `std::unique_ptr` / `std::shared_ptr` (and `std::vector` for dynamic arrays) over raw `new`/`delete` in application code. Raw owning pointers remain an interview topic; they should be rare in new designs.
:::

## Stack versus heap: the decision table

| Criterion | Stack | Heap |
|---|---|---|
| Speed | Extremely fast (pointer bump) | Slower (allocator + metadata) |
| Size budget | Small (~1–8 MB typical) | Large (RAM / virtual address space) |
| Lifetime | Tied to function/block | Until explicit free / smart-pointer release |
| Who manages it? | Compiler / ABI automatically | Programmer (or RAII wrapper) |
| Allocation syntax | Ordinary locals, parameters | `new` / `malloc` / containers |
| Failure mode | Stack overflow | `std::bad_alloc` / `nullptr` from `malloc` |
| Fragmentation | Not applicable (LIFO) | Possible |
| Typical use | Scalars, small arrays, control flow | Large or long-lived data, shared objects |

### Pointers and references: a memory recap

A **pointer** is an object that stores an address. The pointer variable itself has a storage duration (often automatic — on the stack) while the pointed-to object may live elsewhere (heap, static, or another stack frame that must still be alive).

A **reference** is an alias for an existing object; it is not an independently reseatable address object in the language model (even if implemented as a pointer under the hood). Binding a reference to an object does not move that object between segments.

```cpp
int stack_v = 1;
int* heap_v = new int(2);

int* p1 = &stack_v;  // pointer on stack → object on stack
int* p2 = heap_v;    // pointer on stack → object on heap
int& r  = *heap_v;   // reference aliases the heap int

delete heap_v;
```

::: interview
"Stack vs heap — explain." Lead with lifetime and who manages memory, then size and speed. Give one concrete example of each (local `int` vs `new int` / `std::vector`). Mention stack overflow vs leaks as the characteristic failure modes.
:::

## Object memory: size, alignment, and where members live

### `sizeof`, alignment, and padding

`sizeof(T)` is the number of bytes an object of type `T` occupies, including any **padding** the compiler inserts so members satisfy **alignment** constraints (e.g. a `double` often wants an 8-byte-aligned address). Padding exists so the CPU can load fields efficiently; it can make `sizeof` larger than the sum of member sizes.

```cpp
#include <iostream>

struct A {
    char c;    // 1 byte
    // 3 or 7 bytes padding (typical)
    int i;     // 4 bytes
};

struct B {
    int i;
    char c;
    // trailing padding so arrays of B keep int aligned
};

int main() {
    std::cout << sizeof(A) << ' ' << sizeof(B) << '\n';
    // Often 8 and 8 on LP64 — order matters for padding
}
```

::: keypoint
Reordering members by decreasing alignment often shrinks `sizeof`. Interviews love asking why two structs with the same members can have different sizes.
:::

### Heap object, stack pointer

When you `new` a class instance, the *object representation* (all members, padding, vptr if any) lives in one contiguous heap block. The pointer variable you use to reach it is usually an automatic object on the stack.

```cpp
struct Node {
    int value;
    Node* next;
};

void example() {
    Node* head = new Node{42, nullptr};
    // head: pointer in this stack frame
    // *head: Node object on the heap (value and next live there)
    delete head;
}
```

Members are not "on the stack" merely because you access them through a stack pointer. Their storage is wherever the enclosing object lives. If `Node` itself is automatic, its members are inside that stack frame; if `Node` is dynamic, its members are inside the heap block.

```cpp
Node local{};           // entire Node on the stack
Node* dyn = new Node{}; // Node on the heap; dyn on the stack
delete dyn;
```

In competitive programming, large `struct` arrays as *locals* can overflow the stack; the same arrays as globals/`static` land in data/BSS, and `std::vector` of structs lands payload on the heap — three different segment choices for the "same" logical data.

::: interview
"If I have `MyClass* p = new MyClass();`, where are the members?" Inside the heap-allocated `MyClass` object. The pointer `p` is typically on the stack. Knowing this distinction is the difference between "I memorised stack vs heap" and actually reading a memory diagram in an interview.
:::
