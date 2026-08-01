# Sequence Containers

Sequence containers store data in a linear arrangement. You choose between them based on how you need to access elements (randomly or sequentially) and where you need to insert or remove them (at the ends or in the middle).

::: keypoint
In Python, the built-in `list` is actually a dynamic array (equivalent to `std::vector`), while `collections.deque` is a double-ended queue (equivalent to `std::deque`). C++ provides these as distinct types to give you strict control over memory layout and performance characteristics.
:::

::: definition
A **sequence container** stores elements in a definite linear order: each element has a predecessor and a successor (except at the ends). Position is part of the meaning — unlike associative containers, where keys decide placement.
:::

The five sequence containers in the Standard Library are:

| Container | Header | Storage model | Best for |
| :--- | :--- | :--- | :--- |
| `std::vector<T>` | `<vector>` | One contiguous heap block | Default choice; random access; append-heavy work |
| `std::array<T,N>` | `<array>` | Inline fixed buffer of size `N` | Compile-time size; stack/embedded storage |
| `std::deque<T>` | `<deque>` | Map of fixed-size chunks | Fast push/pop at *both* ends + random access |
| `std::list<T>` | `<list>` | Doubly-linked heap nodes | Stable iterators; O(1) splice/insert given an iterator |
| `std::forward_list<T>` | `<forward_list>` | Singly-linked heap nodes | Minimal node overhead; forward-only algorithms |

::: interview
"Which sequence container do you reach for by default, and why?" — Answer `std::vector` unless you have a measured reason not to. Interviewers want cache-locality reasoning, not a textbook list of big-O cases.
:::

## `std::vector` (Dynamic Array)

A **`std::vector`** is a dynamic array that can grow in size. It is the default, go-to container in C++ for almost all use cases because it stores elements contiguously in memory, making it incredibly cache-friendly and fast for traversal.

### Construction and initialisation

A `std::vector` manages its own heap memory and offers several constructors to populate it initially.

```cpp
#include <vector>

// 1. Default construction (empty, no heap allocation yet)
std::vector<int> v1;

// 2. Count and value
std::vector<int> v2(5, 10); // {10, 10, 10, 10, 10}

// 3. Initialiser list
std::vector<int> v3 = {1, 2, 3, 4, 5};

// 4. From iterator range (copies elements from another container)
std::vector<int> v4(v3.begin(), v3.begin() + 3); // {1, 2, 3}

// 5. Copy construction (deep copy)
std::vector<int> v5(v3);

// 6. Move construction (steals memory from a temporary, O(1))
std::vector<int> v6(std::move(v5)); 
```

Full construction / assign API (typical signatures; `Allocator` omitted for clarity):

| Member | Signature (sketch) | Complexity | Notes |
| :--- | :--- | :--- | :--- |
| Default ctor | `vector()` | $O(1)$ | Empty; capacity often 0 |
| Count ctor | `vector(n)` / `vector(n, value)` | $O(n)$ | Value-initialises or copies `value` |
| Range ctor | `vector(first, last)` | $O(n)$ | Copies `[first, last)` |
| Initialiser-list | `vector(std::initializer_list<T>)` | $O(n)$ | Prefer for literals |
| Copy / move | `vector(const vector&)` / `vector(vector&&)` | $O(n)$ / $O(1)$ | Move steals the buffer |
| `operator=` | copy / move / init-list assign | $O(n)$ | May reuse capacity |
| `assign` | `assign(n, value)` / `assign(first, last)` / `assign(il)` | $O(n)$ | Replaces *all* contents |
| `assign_range` | C++23: `assign_range(rg)` | $O(n)$ | Range-based assign |

```cpp
#include <vector>

std::vector<int> v = {1, 2, 3};
v.assign(4, 7);              // {7, 7, 7, 7}
v.assign({9, 8, 7});         // {9, 8, 7}
std::vector<int> src = {1, 2};
v.assign(src.begin(), src.end()); // {1, 2}
```

### Size versus capacity

A vector tracks two distinct integer values to manage its growth efficiently:
- **Size**: The number of elements currently stored in the vector.
- **Capacity**: The total number of elements the vector *could* store in its currently allocated heap block before it needs to request more memory.

```cpp
std::vector<int> v;
v.reserve(100); // Allocates memory for 100 elements, but size is still 0

v.push_back(1);
v.push_back(2);

// v.size() is 2
// v.capacity() is at least 100

v.shrink_to_fit(); // Politely asks to reduce capacity to match size (2)
```

#### Capacity members

| Member | Signature | Complexity | What it does |
| :--- | :--- | :--- | :--- |
| `size` | `size_type size() const noexcept` | $O(1)$ | Number of live elements |
| `empty` | `bool empty() const noexcept` | $O(1)$ | Equivalent to `size() == 0` |
| `max_size` | `size_type max_size() const noexcept` | $O(1)$ | Theoretical upper bound (allocator limit) |
| `capacity` | `size_type capacity() const noexcept` | $O(1)$ | Allocated slots (may exceed `size`) |
| `reserve` | `void reserve(size_type n)` | $O(n)$ if realloc | Ensures `capacity() >= n`; does **not** change `size` |
| `shrink_to_fit` | `void shrink_to_fit()` | $O(n)$ if realloc | Non-binding request to drop spare capacity |

::: keypoint
**`reserve` vs `resize`**: `reserve(n)` only grows the *buffer* so future `push_back`s avoid reallocation — size stays the same and new slots are uninitialised storage. `resize(n)` changes the *logical* size: if growing, it default-/value-constructs new elements; if shrinking, it destroys the tail. Prefer `reserve` when you know how many `push_back`s are coming; use `resize` when you need `n` constructed elements you can index immediately.
:::

```cpp
#include <vector>
#include <iostream>

std::vector<int> a;
a.reserve(5);   // size == 0, capacity >= 5 — a[0] is undefined behaviour
a.resize(5);    // size == 5, capacity >= 5 — a[0]..a[4] exist (0-initialised for int)
a.resize(2);    // destroys a[2], a[3], a[4]; capacity usually unchanged
a.resize(4, 99); // appends two 99s → size 4
```

::: trap
`v[i]` after `reserve` but before the element exists is undefined behaviour. `reserve` does not create elements — only `resize`, `push_back`/`emplace_back`, `insert`, or construction does.
:::

### Element access

Because a vector is contiguous, it provides $O(1)$ random access to any element.

```cpp
std::vector<int> v = {10, 20, 30};

// operator[]: Unchecked access (fastest, undefined behaviour if out of bounds)
int a = v[1]; // 20

// .at(): Bounds-checked access (throws std::out_of_range if out of bounds)
int b = v.at(5); // Exception!

// Front and back access
int first = v.front(); // 10
int last = v.back();   // 30

// Raw pointer access to the underlying contiguous array
int* rawPtr = v.data();
```

| Member | Signature | Complexity | Notes |
| :--- | :--- | :--- | :--- |
| `operator[]` | `T& operator[](size_type i)` | $O(1)$ | No bounds check |
| `at` | `T& at(size_type i)` | $O(1)$ | Throws `std::out_of_range` |
| `front` | `T& front()` | $O(1)$ | UB if empty |
| `back` | `T& back()` | $O(1)$ | UB if empty |
| `data` | `T* data() noexcept` | $O(1)$ | Pointer to element 0 (or unspecified if empty) |

::: trap
Calling `front()`, `back()`, or `pop_back()` on an empty vector is undefined behaviour. Check `empty()` first in defensive code.
:::

### Iterators

| Member | Signature | Complexity | Notes |
| :--- | :--- | :--- | :--- |
| `begin` / `end` | `iterator begin()/end()` | $O(1)$ | Half-open `[begin, end)` |
| `cbegin` / `cend` | const iterators | $O(1)$ | Always const |
| `rbegin` / `rend` | reverse iterators | $O(1)$ | Reverse view |
| `crbegin` / `crend` | const reverse | $O(1)$ | |

```cpp
#include <vector>
#include <iostream>

std::vector<int> v = {1, 2, 3};
for (auto it = v.begin(); it != v.end(); ++it)
    std::cout << *it << ' ';
for (auto it = v.rbegin(); it != v.rend(); ++it)
    std::cout << *it << ' '; // 3 2 1
```

`std::vector` iterators are **contiguous iterators** (C++17 concept): pointer arithmetic and `&v[i] == v.data() + i` hold.

### Modifiers

Adding or removing elements at the end of a vector is fast, but inserting or erasing in the middle requires shifting all subsequent elements, costing $O(n)$ time.

```cpp
#include <vector>
#include <string>

std::vector<std::string> words = {"apple", "banana"};

// push_back copies or moves an existing object into the vector
words.push_back("cherry");

// emplace_back constructs the object in-place directly in the vector's memory, 
// avoiding temporary copies. It takes constructor arguments for the element type.
words.emplace_back(5, 'A'); // "AAAAA"

// Remove the last element
words.pop_back();

// insert and emplace (requires an iterator, shifts following elements right)
auto it = words.insert(words.begin(), "start");
words.emplace(it + 1, "second"); // Constructs directly in place

// erase (requires an iterator, shifts following elements left)
words.erase(words.begin()); // removes "start"

// Other modifiers
words.resize(10);        // Changes size to 10 (padding with empty strings)
words.assign(3, "x");    // Replaces entire contents with {"x", "x", "x"}
words.clear();           // Sets size to 0, but leaves capacity unchanged

std::vector<std::string> other;
words.swap(other);       // Swaps internal pointers in O(1) time
```

| Member | Signature (sketch) | Typical complexity | Effect |
| :--- | :--- | :--- | :--- |
| `clear` | `void clear() noexcept` | $O(n)$ destroy | Size → 0; capacity unchanged |
| `insert` | `insert(pos, value/count/range/il)` | $O(n)$ + possible realloc | Shifts `[pos, end)` right |
| `emplace` | `emplace(pos, args...)` | $O(n)$ + possible realloc | In-place construct at `pos` |
| `erase` | `erase(pos)` / `erase(first, last)` | $O(n)$ | Shifts following elements left |
| `push_back` | `void push_back(const T&)` / `T&&` | Amortised $O(1)$ | Append; may reallocate |
| `emplace_back` | `reference emplace_back(Args&&...)` | Amortised $O(1)$ | Construct at end |
| `pop_back` | `void pop_back()` | $O(1)$ | Destroy last; no capacity shrink |
| `resize` | `void resize(n)` / `resize(n, value)` | $O(\|n - size\|)$ + possible realloc | Grow/shrink logical size |
| `swap` | `void swap(vector&)` | $O(1)$ | Exchange buffers |

```cpp
#include <vector>

std::vector<int> v = {10, 20, 30, 40};
v.insert(v.begin() + 1, 15);           // {10, 15, 20, 30, 40}
v.insert(v.end(), 2, 99);              // append two 99s
v.erase(v.begin() + 2);                // erase one
v.erase(v.begin(), v.begin() + 2);     // erase a prefix
```

::: heavy
The vector memory model combines the speed of contiguous arrays with dynamic sizing. This introduces the concepts of geometric growth and iterator invalidation.
:::

### Amortised growth and iterator invalidation

*Analogy*: Imagine you are filling a bookshelf. Because books must sit contiguously, when the shelf is full, you cannot just nail a single plank to the side. You must buy a completely new, wider bookshelf, physically move all the books over one by one, and throw away the old shelf. Anyone who wrote down the physical address of the old shelf now has an invalid address.

![Vector growth: allocate a larger contiguous block, move the elements across, then free the old block.](assets/s44_vector_growth.png)

```cpp
std::vector<int> v = {1, 2, 3}; // capacity might be exactly 3
int* ptr = &v[0];               // pointing to the first element's memory

v.push_back(4); // Vector is full! Reallocation triggered.
// 'ptr' is now dangling. Dereferencing it is undefined behaviour.
```

**Plain-English rule**: Vectors guarantee elements sit right next to each other in memory. When they run out of space, they must find a new, larger piece of memory and move everything there.

**Technical precise statement**: To maintain an amortised $O(1)$ time complexity for `push_back`, `std::vector` grows geometrically (typically doubling its `capacity`) when reallocation is required. Reallocation invalidates all iterators, pointers, and references to elements within the vector. Furthermore, `insert` and `erase` operations invalidate iterators from the point of modification to the end of the vector due to $O(n)$ memory shifting.

::: trap
Any operation that might cause a vector to exceed its `capacity` (such as `push_back`, `insert`, or `resize`) threatens to reallocate the underlying array, immediately invalidating all iterators and pointers to its elements.
:::

#### Iterator / reference invalidation (`std::vector`)

| Operation | Invalidates |
| :--- | :--- |
| `push_back` / `emplace_back` if `size() == capacity()` | **All** iterators, pointers, references |
| `push_back` / `emplace_back` if spare capacity | None (end iterators may be affected in the formal sense; references to existing elements stay valid) |
| `insert` / `emplace` / `resize` larger, if realloc | **All** |
| `insert` / `emplace` without realloc | All at/after insertion point; before stay valid |
| `erase` | Erased element and all after it; before stay valid |
| `pop_back` | Only references/iterators to the removed last element |
| `clear` | All (to elements); capacity usually kept |
| `reserve` larger than current capacity | **All** (reallocates) |
| `shrink_to_fit` (if it reallocates) | **All** |
| `swap` | Iterators still refer to elements in the *other* container (C++11+); treat with care across containers |

```cpp
#include <vector>

std::vector<int> v = {1, 2, 3, 4, 5};
v.reserve(100); // no realloc on next few inserts if capacity was smaller
auto it = v.begin() + 2; // -> 3
v.insert(v.begin(), 0);  // no realloc (spare capacity): it is invalidated (shifted)
// After insert without realloc, iterators at/after the insert point are invalid.
```

### The `vector<bool>` proxy gotcha

::: trap
`std::vector<bool>` is a **space-optimised specialisation** that packs bits. `operator[]` does **not** return `bool&` — it returns a **proxy object**. Taking the address of an element, binding a `bool&` to `v[i]`, or assuming contiguous `bool` storage is wrong and breaks template code that expects a real container of `bool`.
:::

```cpp
#include <vector>
#include <algorithm>

std::vector<bool> bits = {true, false, true};
// bool& ref = bits[0];          // ERROR: cannot bind bool& to proxy
auto proxy = bits[0];            // vector<bool>::reference
proxy = false;                   // modifies the packed bit

// Prefer for real bool semantics:
std::vector<char> flags(3, 0);   // or std::deque<bool>, or bitset / dynamic_bitset
```

::: interview
Classic trap question: "What's wrong with `std::vector<bool>`?" — Mention the proxy reference, broken `&v[i]`, incompatibility with algorithms expecting `T*`, and recommend `vector<char>` / `deque<bool>` / a bitset when you need genuine `bool` objects.
:::

### Under the hood: `std::vector`

::: heavy
Under the hood — slow down. Contiguous storage plus geometric growth is why vector dominates real workloads.
:::

Internally a vector is essentially three values controlling **one contiguous heap block**:

- a pointer to the start of the allocated array,
- **size** (how many `T` objects are alive),
- **capacity** (how many `T`-sized slots the block can hold).

When `size == capacity` and you `push_back`, the implementation:

1. allocates a new block, typically ~$2\times$ (or ~$1.5\times$) the old capacity,
2. move-constructs (or copies) every existing element into the new block,
3. destroys the old elements and frees the old block,
4. appends the new element.

That is why growth is **amortised** $O(1)$: most pushes are cheap; occasional reallocations cost $O(n)$ but happen rarely enough that the average stays constant. Prefer `reserve` when you know the final size to avoid those moves entirely.

::: keypoint
**Why `vector` usually beats `list` in practice**: even when big-O says list insert is $O(1)$ and vector insert is $O(n)$, modern CPUs load whole cache lines. Contiguous `vector` scans stream through memory; `list` chases pointers across the heap (**pointer chasing**), thrashing the cache. Measured insert-in-the-middle workloads often still favour `vector` until $n$ is huge *and* you already hold a stable iterator.
:::

::: interview
Explain amortised `push_back`: geometric growth means total cost of $n$ pushes is $O(n)$, so average per push is $O(1)$. Also state what reallocation invalidates (everything).
:::

## `std::array` (Fixed-Size Array)

A **`std::array`** is a fixed-size container that wraps a built-in array. Its size is fixed at compile time, and its memory is allocated exactly where the array itself is declared (on the stack, or inside an object), completely avoiding the heap.

```cpp
#include <array>

// Aggregate initialisation; size is part of the type signature
std::array<int, 5> arr = {1, 2, 3, 4, 5};

arr.fill(0); // Sets all elements to 0

// Element access is identical to std::vector
size_t s = arr.size(); // Always 5
arr[0] = 10;
arr.at(1) = 20; // bounds-checked
int first = arr.front();
int last = arr.back();
int* ptr = arr.data();

// Tuple-like access (evaluated at compile time)
int val = std::get<0>(arr); 
```

Because the size is fixed, `std::array` lacks `push_back`, `insert`, or `reserve`.

### Construction, assign, and fixed size

`std::array<T, N>` embeds `T[N]` (or equivalent). **`N` is part of the type**: `array<int,3>` and `array<int,4>` are unrelated types.

| Member / operation | Signature (sketch) | Complexity | Notes |
| :--- | :--- | :--- | :--- |
| Aggregate init | `array<T,N> a = {…};` | $O(N)$ | No custom ctor required |
| Copy / move | implicit | $O(N)$ | Element-wise |
| `operator=` | copy / move assign | $O(N)$ | |
| `fill` | `void fill(const T& value)` | $O(N)$ | Assigns every element |
| `swap` | `void swap(array&)` | $O(N)$ | Swaps elements (not pointers) |

```cpp
#include <array>
#include <algorithm>

std::array<int, 4> a{};          // all zeros
std::array<int, 4> b = {1, 2};   // {1, 2, 0, 0}
a.fill(7);                       // {7, 7, 7, 7}
a.swap(b);
std::sort(a.begin(), a.end());   // works — random-access, contiguous
```

### Element access and iterators

Same shape as `vector`: `operator[]`, `at`, `front`, `back`, `data`, and bidirectional/contiguous iterators via `begin`/`end`/`rbegin`/`rend` and const variants. All access is $O(1)$. `size()`, `empty()`, `max_size()` are `constexpr`-friendly; `size()` is always `N`.

```cpp
#include <array>

std::array<double, 3> pts = {0.0, 1.0, 2.0};
double* p = pts.data();     // &pts[0]
constexpr std::size_t n = std::array<int, 8>{}.size(); // 8
```

### Capacity (fixed — no growth API)

| Member | Complexity | Notes |
| :--- | :--- | :--- |
| `size` / `max_size` | $O(1)$ | Both equal `N` |
| `empty` | $O(1)$ | `N == 0` only for `array<T,0>` |

There is **no** `reserve`, `capacity`, `resize`, `clear`-that-shrinks, `push_back`, `pop_back`, `insert`, or `erase`. Size never changes.

### Iterator invalidation (`std::array`)

| Operation | Invalidates |
| :--- | :--- |
| Element assignment / `fill` / `swap` | Nothing about *identity* of storage — iterators still refer to the same slots (values change) |
| Moving the `array` object itself | Iterators/pointers into the old object are invalid (storage moved with the object) |
| Insert / erase | N/A — not supported |

### Under the hood: `std::array`

`std::array` is **inline storage**: the `T` elements live inside the `array` object, wherever that object lives (automatic storage, static storage, or as a data member). No heap allocation, no allocator, no indirection. That makes it ideal for small fixed buffers, embedded/real-time code, and `constexpr` data.

::: keypoint
Prefer `std::array` over a raw `T[N]` when you want STL iterators, `size()`, bounds-checked `at()`, and the ability to pass/return the array by value without decaying to a pointer.
:::

::: interview
"`std::array` vs C array vs `std::vector`?" — Fixed compile-time size and no heap → `array`. Runtime size / growth → `vector`. Raw arrays decay to pointers and do not carry size.
:::

## `std::deque` (Double-Ended Queue)

A **`std::deque`** (pronounced "deck") allows fast $O(1)$ insertion and deletion at *both* the front and the back. 

Unlike a vector, a deque is not strictly contiguous. It is typically implemented as a collection of fixed-size memory chunks (an array of pointers to arrays). Because it is not a single contiguous block, `std::deque` does not have a `reserve()` or `capacity()` method, and pointer arithmetic between arbitrary elements is not valid.

```cpp
#include <deque>

std::deque<int> d = {2, 3, 4};

d.push_front(1); // O(1) time, unlike vector where this is O(n)
d.push_back(5);  // O(1) time
// d is now {1, 2, 3, 4, 5}

d.pop_front();
d.pop_back();

// Indexed access is still O(1)
int val = d[1];
```

### Construction and assign

| Member | Signature (sketch) | Complexity |
| :--- | :--- | :--- |
| Ctors | default / count / count+value / range / init-list / copy / move | $O(1)$ or $O(n)$ |
| `operator=` | copy / move / init-list | $O(n)$ |
| `assign` | count+value / range / init-list | $O(n)$ |

```cpp
#include <deque>

std::deque<int> d1;
std::deque<int> d2(5, 42);          // five 42s
std::deque<int> d3 = {1, 2, 3};
d1.assign(d3.begin(), d3.end());
```

### Element access

| Member | Signature | Complexity | Notes |
| :--- | :--- | :--- | :--- |
| `operator[]` | `T& operator[](size_type)` | $O(1)$ | Unchecked |
| `at` | `T& at(size_type)` | $O(1)$ | Throws if out of range |
| `front` / `back` | `T& front()` / `T& back()` | $O(1)$ | UB if empty |
| `data` | — | — | **Not provided** (not one contiguous block) |

```cpp
#include <deque>

std::deque<int> d = {10, 20, 30};
int x = d.at(1);   // 20
int y = d.front(); // 10
// int* p = d.data(); // ERROR — no data()
```

### Iterators

`begin`/`end`/`rbegin`/`rend` and const variants — **random-access iterators**, but they are *fatter* than raw pointers: typically they store a pointer into a chunk plus enough state to walk the block map. Prefer them over storing raw `T*` into a deque.

### Capacity

| Member | Complexity | Notes |
| :--- | :--- | :--- |
| `size` / `empty` / `max_size` | $O(1)$ | |
| `resize` | $O(\|Δn\|)$ | Grow/shrink at the **back** |
| `shrink_to_fit` | non-binding | May compact unused chunks |
| `reserve` / `capacity` | — | **Absent** — chunked layout has no single capacity |

### Modifiers

| Member | Complexity | Notes |
| :--- | :--- | :--- |
| `push_back` / `emplace_back` | Amortised $O(1)$ | May allocate a new back chunk |
| `push_front` / `emplace_front` | Amortised $O(1)$ | May allocate a new front chunk |
| `pop_back` / `pop_front` | $O(1)$ | May free an empty end chunk |
| `insert` / `emplace` | $O(n)$ | Shifts toward nearer end (implementation) |
| `erase` | $O(n)$ | Same |
| `clear` | $O(n)$ | Destroys elements |
| `swap` | $O(1)$ | Swaps maps/chunks |

```cpp
#include <deque>
#include <string>

std::deque<std::string> q;
q.emplace_front("first");
q.push_back("last");
q.insert(std::next(q.begin()), "middle"); // {first, middle, last}
q.pop_front();
q.erase(q.begin()); // remove current front
```

### Iterator invalidation (`std::deque`)

| Operation | Iterators | Pointers / references to elements |
| :--- | :--- | :--- |
| `push_back` / `push_front` / `emplace_*` at ends | **May invalidate all iterators** | Typically **remain valid** (elements do not move between chunks on end insert) |
| `pop_back` / `pop_front` | Invalidate only to the erased element (and past-the-end as needed) | Same for erased; others stay |
| `insert` / `erase` in the middle | **All iterators** invalidated | References may also be invalidated (elements can be moved between chunks) |
| `clear` | All invalidated | All invalidated |

::: trap
On `deque`, **end insertions can keep element pointers/references valid while invalidating iterators**. Never assume "if the pointer is fine, my iterator is fine." Store indices or re-get iterators after mutating.
:::

### Under the hood: `std::deque`

![A deque is a map of pointers to fixed-size blocks — O(1) at both ends, but not one contiguous array.](assets/s44_deque.png)

*Analogy*: A deque is less like one long shelf and more like a **library catalogue** (the map) pointing at many short shelves (chunks). You can add a new short shelf on the left or the right without rebuilding the whole library.

**Technical model**: a **map** (dynamic array of pointers) addresses fixed-size **chunks/blocks** of elements. Indexing computes `chunk_index` and `offset` in $O(1)$. Growing at either end allocates a new chunk and, occasionally, grows the map itself — still amortised $O(1)$ at the ends, without relocating existing elements into one giant contiguous buffer.

Consequences:

- $O(1)$ `push_front` **and** `push_back` without shifting the whole sequence (unlike `vector`).
- Random access stays $O(1)$, but each step may cross a chunk boundary — iterators are heavier and more fragile than `vector`'s pointer-like iterators.
- `&d[i] + 1 == &d[i+1]` is **not** guaranteed (not contiguous as a whole).
- No `data()`; do not pass a deque to APIs expecting a single `T*`.

::: interview
"How can `deque` do $O(1)$ push front *and* random access?" — Chunk map: new chunk at the front for push_front; index arithmetic for `operator[]`. Contrast with `vector` (push_front is $O(n)$) and `list` (no `operator[]`).
:::

## `std::list` (Doubly-Linked List)

A **`std::list`** is a doubly-linked list. Every element is stored in its own heap node, containing the value and pointers to the next and previous nodes.

Because nodes are scattered across the heap, you cannot use an index to jump to an element. However, once you have an iterator pointing to a specific location, inserting or erasing a node is an $O(1)$ operation that simply wires up pointers.

```cpp
#include <list>
#include <iterator>

std::list<int> l = {4, 2, 5, 1, 3};

// auto val = l[2]; // ERROR: std::list has no operator[]

// Insertion requires an iterator traversal first (O(n))
auto it = l.begin();
std::advance(it, 2); 
l.insert(it, 99); // O(1) insertion at the found location
```

::: trap
Because `std::list` nodes are scattered in memory, it defeats the CPU cache. Iterating over a `std::list` is significantly slower than iterating over a `std::vector`, even if the asymptotic $O(n)$ complexity is the same. Furthermore, `std::list` has no `operator[]`.
:::

### Construction and assign

| Member | Signature (sketch) | Complexity |
| :--- | :--- | :--- |
| Ctors | default / count / value / range / init-list / copy / move | $O(1)$ or $O(n)$ |
| `assign` / `operator=` | as usual | $O(n)$ |

### Element access

| Member | Complexity | Notes |
| :--- | :--- | :--- |
| `front` / `back` | $O(1)$ | No `operator[]`, no `at`, no `data` |
| Iterators | bidirectional | `++` / `--` only — not random access |

```cpp
#include <list>

std::list<int> l = {1, 2, 3};
int a = l.front(); // 1
int b = l.back();  // 3
```

### Iterators and capacity

| Member | Complexity | Notes |
| :--- | :--- | :--- |
| `begin`/`end`/`rbegin`/`rend` (+ const) | $O(1)$ | Bidirectional |
| `size` / `empty` / `max_size` | $O(1)$ (C++11+) | Size is stored |
| `resize` | $O(\|Δn\|)$ | Add/remove at back |
| `reserve` / `capacity` | — | None — each node is separate |

### Modifiers

| Member | Complexity | Notes |
| :--- | :--- | :--- |
| `push_back` / `emplace_back` | $O(1)$ | |
| `push_front` / `emplace_front` | $O(1)$ | |
| `pop_back` / `pop_front` | $O(1)$ | |
| `insert` / `emplace` | $O(1)$ per element *given the iterator* | Finding the spot is still $O(n)$ |
| `erase` | $O(1)$ per element *given the iterator* | Only the erased iterators invalidate |
| `clear` | $O(n)$ | |
| `swap` | $O(1)$ | |

```cpp
#include <list>
#include <string>

std::list<std::string> names;
names.emplace_front("Ada");
names.push_back("Grace");
names.insert(std::next(names.begin()), "Edsger"); // after first
names.pop_front();
```

### Member algorithms

Generic algorithms like `std::sort` require random access iterators, which `std::list` does not provide. Therefore, `std::list` implements its own member functions for these operations, efficiently modifying the node pointers instead of copying values.

```cpp
l.sort();    // O(N log N) sorting using node pointers
l.reverse(); // O(N) pointer reversal
l.unique();  // Removes consecutive duplicates
l.remove(99); // Removes all elements equal to 99
l.remove_if([](int n) { return n % 2 == 0; }); // Removes even numbers

std::list<int> l2 = {10, 20};
l.sort();
l2.sort();
l.merge(l2); // Merges two sorted lists in O(N); l2 becomes empty

std::list<int> l3 = {100, 200};
// splice transfers nodes from l3 into l without reallocation or copying
l.splice(l.begin(), l3); // l3 is now empty
```

#### Special list operations (detailed)

| Member | Signature (sketch) | Complexity | What it does |
| :--- | :--- | :--- | :--- |
| `splice` | `splice(pos, other)` / `splice(pos, other, it)` / `splice(pos, other, first, last)` | $O(1)$ or $O(distance)$ for sized range in some forms | **Transfers nodes** — no element copy/alloc |
| `merge` | `merge(other)` / `merge(other, comp)` | $O(n)$ | Requires both lists sorted; empties `other` |
| `remove` | `remove(const T&)` | $O(n)$ | Erase all `== value` |
| `remove_if` | `remove_if(pred)` | $O(n)$ | Erase when predicate true |
| `unique` | `unique()` / `unique(pred)` | $O(n)$ | Erase *consecutive* duplicates |
| `sort` | `sort()` / `sort(comp)` | $O(n \log n)$ | Relinks pointers; stable |
| `reverse` | `reverse()` | $O(n)$ | Swaps next/prev links |

::: definition
**`splice`** moves nodes between lists (or within one list) by rewiring pointers. Element constructors do not run — ownership of the node transfers. Iterators to spliced elements **remain valid** and now belong to the destination list.
:::

```cpp
#include <list>

std::list<int> a = {1, 2, 3};
std::list<int> b = {10, 20};
auto it = std::next(a.begin()); // -> 2
a.splice(it, b);                // a: 1,10,20,2,3  b: empty
// 'it' still points to 2
```

::: keypoint
**Why `list` has its own `sort`**: `std::sort` needs random-access iterators (typically introsort / QuickSort-style partitioning). `list::sort` is usually a merge sort on node links — $O(n \log n)$ comparisons, no random access, and it does not move `T` if splicing nodes is enough.
:::

::: trap
`unique` only removes **consecutive** duplicates. Sort first if you want global uniqueness: `l.sort(); l.unique();`.
:::

### Iterator invalidation (`std::list`)

| Operation | Invalidates |
| :--- | :--- |
| `insert` / `emplace` / `push_*` / `splice` in | **Nothing** to existing elements (new iterators for new nodes) |
| `erase` / `pop_*` / `remove` / `remove_if` | **Only** iterators/references to erased element(s) |
| `clear` / full assign destroying elements | All to destroyed elements |
| `merge` / `sort` / `reverse` / `unique` | Do not invalidate iterators to remaining elements (values may change order) |

### Under the hood: `std::list`

![A doubly-linked list: each node is a separate heap allocation linked by prev and next pointers.](assets/s44_dll.png)

Each element lives in a separately heap-allocated **node**: `{ prev*, next*, T value }` (plus allocator bookkeeping). Insert/erase at a known iterator rewires a constant number of pointers — true $O(1)$ *once you are there*. There is no random access: advancing $k$ steps costs $O(k)$.

Cache behaviour is the tax: walking the list jumps around the heap. Prefer `list` when you need **iterator stability**, **O(1) splice**, or frequent insert/erase in the middle *with an iterator already in hand* — not as a general `vector` replacement.

::: interview
When is `list` justified over `vector`? Stable iterators across inserts, splicing whole ranges in $O(1)$, or algorithms that relink nodes. Otherwise default to `vector`.
:::

## `std::forward_list` (Singly-Linked List)

A **`std::forward_list`** is a singly-linked list. It has an absolute minimal memory footprint—just one pointer per node (pointing to the next element). Because nodes do not point backward, you can only iterate forward, and operations like insert and erase must happen *after* a given node.

Historically, `std::forward_list` did not even track its own `size()` because maintaining that counter would add overhead to every list instance.

```cpp
#include <forward_list>

std::forward_list<int> fl = {1, 2, 3};

// fl.size(); // ERROR: deliberately omitted to save space

// Operations happen *after* the iterator
auto it = fl.before_begin(); // Special iterator to an imaginary element before the first
fl.insert_after(it, 0);      // {0, 1, 2, 3}
fl.erase_after(fl.begin());  // Removes the element following the first
```

### Construction and assign

Same family of constructors and `assign` / `operator=` as other sequences (count, range, init-list, copy, move). Complexity $O(n)$ when elements are created.

### Element access and iterators

| Member | Complexity | Notes |
| :--- | :--- | :--- |
| `front` | $O(1)$ | No `back`, no `operator[]`, no `at`, no `data` |
| `begin` / `end` | $O(1)$ | Forward iterators only |
| `before_begin` / `cbefore_begin` | $O(1)$ | Past-the-front sentinel for `*_after` APIs |
| `size` | — | **Not provided** (use `std::distance` → $O(n)$) |
| `empty` / `max_size` | $O(1)$ | |

```cpp
#include <forward_list>
#include <iterator>

std::forward_list<int> fl = {10, 20, 30};
int f = fl.front(); // 10
auto n = std::distance(fl.begin(), fl.end()); // 3, O(n)
```

### Capacity and modifiers (after-oriented)

There is no `push_back` / `pop_back` / `back`. Growth at the front uses `push_front` / `emplace_front` / `pop_front`. Middle updates use the `*_after` family:

| Member | Signature (sketch) | Complexity | Notes |
| :--- | :--- | :--- | :--- |
| `push_front` / `emplace_front` | as usual | $O(1)$ | |
| `pop_front` | `void pop_front()` | $O(1)$ | |
| `insert_after` | `insert_after(pos, value/count/range/il)` | $O(k)$ for $k$ inserts | Insert **after** `pos` |
| `emplace_after` | `emplace_after(pos, args...)` | $O(1)$ | Construct after `pos` |
| `erase_after` | `erase_after(pos)` / `erase_after(first, last)` | $O(1)$ / $O(range)$ | Erase **after** `pos` |
| `clear` | `void clear()` | $O(n)$ | |
| `resize` | `void resize(n)` / `resize(n, value)` | $O(n)$ | |
| `swap` | `void swap(forward_list&)` | $O(1)$ | |

```cpp
#include <forward_list>
#include <iterator>

std::forward_list<int> fl = {1, 3, 4};
auto prev = fl.before_begin();
fl.insert_after(prev, 0);    // {0, 1, 3, 4} — insert after before_begin = push front

// Insert 2 between 1 and 3: hold the predecessor (the node with value 1)
auto cur = fl.begin();       // -> 0
++cur;                       // -> 1
fl.insert_after(cur, 2);     // {0, 1, 2, 3, 4}
fl.emplace_after(fl.begin(), 99); // {0, 99, 1, 2, 3, 4}
fl.erase_after(fl.begin());  // erase element after first → removes 99
```

::: trap
With `forward_list` you almost always keep the iterator to the **predecessor**. There is no `erase(it)` that removes `*it` in one shot — you need `erase_after(pred)`. Losing the previous iterator means restarting from `before_begin()`.
:::

### Special forward_list operations

Same spirit as `list`, but forward-only and often `*_after`:

| Member | Complexity | Notes |
| :--- | :--- | :--- |
| `splice_after` | $O(1)$ or $O(range)$ | Transfer nodes after a position |
| `merge` | $O(n)$ | Both must be sorted |
| `remove` / `remove_if` | $O(n)$ | |
| `unique` | $O(n)$ | Consecutive duplicates |
| `sort` | $O(n \log n)$ | Member sort — no random access |
| `reverse` | $O(n)$ | |

```cpp
#include <forward_list>

std::forward_list<int> a = {3, 1, 2};
std::forward_list<int> b = {0, 4};
a.sort();
b.sort();
a.merge(b);          // a: 0,1,2,3,4  b: empty
a.unique();
a.reverse();
a.remove_if([](int x) { return x % 2 == 0; });
```

### Iterator invalidation (`std::forward_list`)

| Operation | Invalidates |
| :--- | :--- |
| `insert_after` / `emplace_after` / `push_front` / `splice_after` | Existing iterators remain valid |
| `erase_after` / `pop_front` / `remove*` | Only iterators to erased elements |
| `before_begin()` | Remains valid across inserts/erases of elements (it never points at an element) |

### Under the hood: `std::forward_list`

A **singly-linked** node holds `{ next*, T value }` — no `prev`. That saves a pointer per node versus `list`, but forces the `before_begin` / `insert_after` / `erase_after` API: to change a link you must hold the node that *points to* the target. Use it for forward-only passes with minimal memory, or when API symmetry with intrusive singly-linked structures matters. For general bidirectional editing, prefer `list` or (usually) `vector`.

::: interview
"Why `before_begin`?" — Singly-linked lists insert/erase by updating the *previous* node's `next`. `before_begin` is the fake predecessor of `front`, so you can `insert_after`/`erase_after` at the head without a special case.
:::

## Container Comparison Summary

| Container | Underlying Structure | Random Access? | Insert/Erase (middle) | Contiguous? | Iterator Invalidation (on insert/erase) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `std::vector` | Dynamic Array | Yes ($O(1)$) | $O(n)$ | Yes | If reallocated: **All**. Otherwise: **From point to end**. |
| `std::array` | Static Array | Yes ($O(1)$) | N/A | Yes | N/A (cannot insert/erase) |
| `std::deque` | Array of Arrays | Yes ($O(1)$) | $O(n)$ | No | **All** (pointers/references may survive in some cases) |
| `std::list` | Doubly-Linked List | No | $O(1)$ | No | **Only the erased element** |
| `std::forward_list`| Singly-Linked List | No | $O(1)$ | No | **Only the erased element** |

### Choosing quickly

| Need | Prefer |
| :--- | :--- |
| Default sequential storage | `vector` |
| Fixed `N`, no heap | `array<T,N>` |
| Heavy push/pop at **both** ends + indexing | `deque` |
| Stable iterators / splice / middle edit with known iterator | `list` |
| Absolute minimum node size, forward-only | `forward_list` |
| Binary buffer for C APIs (`T*`) | `vector` or `array` (`data()`) — never `deque`/`list` |

::: interview
Be ready to justify container choices:
1. **`std::vector` vs `std::list`**: Always default to `std::vector`. The contiguous memory of `vector` makes it vastly superior for cache performance, beating `std::list` even for insertions unless the container is massive and you already hold an iterator.
2. **When to use `std::deque`**: When you need queue semantics (push/pop at both ends) but still require indexed access, or when vector reallocations cause unacceptable latency spikes.
3. **Vector capacity growth**: Explain the amortised $O(1)$ complexity. When full, a vector allocates a geometrically larger block (e.g. $1.5\times$ or $2\times$) and moves elements, making growth incredibly efficient over time.
4. **Why `std::list` has its own `sort()`**: Generic `std::sort` requires random-access iterators (e.g. for QuickSort). `std::list` provides a member `sort()` that efficiently relinks pointers without needing random access.
:::

::: keypoint
Memorise one invalidation slogan per container: **vector** — realloc kills all, else from edit point; **deque** — iterators fragile on end insert, pointers often OK; **list** / **forward_list** — only erased nodes die; **array** — storage is the object itself.
:::
