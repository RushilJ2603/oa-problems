# Data Structures and their STL Mapping

This section is a capstone recap linking abstract data structures to their concrete Standard Template Library (STL) implementations in C++. It summarises the fundamental time complexities (Big-O) for core operations and details the syntax required to instantiate and manipulate each container. This is a mapping and syntax reference, rather than a tutorial on algorithmic internals.

The deeper member-by-member treatments of sequence containers, adaptors, and associative containers live in the dedicated Part V sections (s44–s46). Here the goal is different: given an *abstract* structure (dynamic array, heap, hash table, …), name the STL type that implements it, recall the Big-O of the operations that matter, and decide *when* to pick it. Sorting, graph algorithms, and other DSA procedures are out of scope — only containers and their costs.

::: keypoint
In Python, the built-in `list`, `dict`, and `set` broadly map onto C++'s `std::vector`, `std::unordered_map`, and `std::unordered_set` respectively.
:::

::: keypoint
**Amortised vs worst-case.** Several STL operations are quoted as *amortised* O(1) — notably `vector::push_back` and end-insertions on `deque` / `string`. Amortised means the *average* cost over a long sequence of operations is O(1), even though a single call may be O(n) when a reallocation (or block allocation) occurs. Guaranteed worst-case bounds (e.g. `map` insert O(log n), `list` splice O(1)) never surprise you with a linear spike; amortised bounds do. In interviews and latency-sensitive code, say which kind you mean.
:::

::: interview
Classic prompt: *"What is the complexity of `vector::push_back`?"* Answer carefully: amortised O(1), worst-case O(n) on reallocation. If they ask for a hard real-time guarantee, prefer a structure with true O(1) worst-case (or pre-`reserve`).
:::

## How to read this mapping

For each abstract structure below you get: the STL type that implements it, the key operations with Big-O, a short realistic snippet, and the traps that trip interviews and contests. Use the **Summary Table** and the **Choosing a container** guide when you only need a decision; dive into the subsections when you need signatures.

<!-- FIG s49: abstract DS icons mapped to STL type names (vector, array, list, stack, queue, deque, priority_queue, unordered_map, set/map, bitset) -->

## Contiguous memory versus node-based containers

A **contiguous** container (`vector`, `array`, `string`, and to a lesser extent `deque`'s blocks) stores elements in adjacent memory. A **node-based** container (`list`, `forward_list`, `set`/`map`, `unordered_*`) stores each element in its own heap node linked by pointers.

::: definition
**Cache locality** means successive elements live close in memory, so a CPU cache line fetch pulls many useful neighbours at once. Contiguous layouts exploit this; pointer-chasing through scattered nodes does not.
:::

Why `vector` usually beats `list` in practice despite Big-O:

- Middle insert into a `vector` is O(n) *element moves*, but those moves are a tight `memmove` over contiguous bytes — extremely fast per element.
- Middle insert into a `list` is O(1) *pointer rewiring* **if you already hold an iterator**, but finding that position is O(n), and each node is a separate heap allocation with poor locality. Traversing *n* list nodes routinely loses to scanning *n* vector elements.
- Heap allocators add constant overhead per node; a million-node `list` pays for a million allocations, while a `vector` of a million ints is one (or a handful of) allocations.

![Contiguous storage is cache-friendly; scattered list nodes cost a cache miss per hop.](assets/s49_cache.png)

::: keypoint
Big-O counts *operations*, not wall-clock time. Prefer `vector` unless you have a measured need for stable iterators under middle insert/erase *and* you already hold the iterator (splice-heavy workloads, LRU with intrusive lists, etc.).
:::

::: trap
Do not choose `std::list` solely because "insert is O(1)". Without a pre-existing iterator to the splice point, you still pay O(n) to *find* the spot — the same asymptotic cost as `vector::insert`, with worse constants.
:::

## Sequence Containers

Sequence containers store data in a linear arrangement. 

### Dynamic Array -> `std::vector`
A resizable array contiguous in memory. This is the default container you should reach for in C++ because its cache locality provides unbeatable constant-factor performance.
- **Access (index)**: O(1)
- **Insert/Delete at end**: Amortised O(1)
- **Insert/Delete in middle**: O(n)

**When to pick:** default sequence; random access; append-heavy workloads; need a contiguous buffer for C APIs (`data()`).

```cpp
#include <vector>

// Instantiation forms
std::vector<int> v1;                     // Empty vector
std::vector<int> v2(10);                 // 10 elements, default-initialised (0)
std::vector<int> v3(5, 42);              // 5 elements, all initialised to 42
std::vector<int> v4 = {1, 2, 3};         // Initialiser list

// Core operations and signatures
v4.push_back(4);                         // void push_back(const T& value);
v4.emplace_back(5);                      // template<class... Args> reference emplace_back(Args&&... args);
v4.pop_back();                           // void pop_back();
int a = v4[0];                           // reference operator[](size_type pos); // Unchecked
int b = v4.at(1);                        // reference at(size_type pos);         // Bounds-checked
v4.insert(v4.begin() + 1, 99);           // iterator insert(const_iterator pos, const T& value);
v4.erase(v4.begin() + 1);                // iterator erase(const_iterator pos);
size_t sz = v4.size();                   // size_type size() const;
v4.clear();                              // void clear();
```

Additional members you will use constantly:

```cpp
#include <vector>

std::vector<int> v = {1, 2, 3};
v.reserve(100);                          // void reserve(size_type new_cap); // capacity >= 100, size unchanged
v.resize(5);                             // void resize(size_type count);   // grow/shrink size
size_t cap = v.capacity();               // size_type capacity() const;
bool e = v.empty();                      // bool empty() const;
int* p = v.data();                       // T* data() noexcept;             // contiguous pointer
v.front(); v.back();                     // reference front(); reference back();
```

Realistic pattern — build then freeze size:

```cpp
#include <vector>

std::vector<int> scores;
scores.reserve(1000);                    // avoid repeated reallocations in a hot loop
for (int i = 0; i < 1000; ++i)
    scores.push_back(i * i);
```

::: trap
`push_back` / `insert` / `reserve` that triggers reallocation **invalidates all iterators, references, and pointers** into the vector. `erase` invalidates iterators at/after the erase point. Hold indices, or re-get iterators after growth.
:::

::: interview
*"Why is `vector` the default container?"* Contiguous storage → cache-friendly traversal, O(1) index, amortised O(1) append, interoperates with C via `data()`. Reach for something else only when a specific requirement (stable middle iterators, both-end ops without contiguous guarantee, sorted keys, …) forces it.
:::

### Fixed Array -> `std::array`
A thin wrapper around a raw array. Its size is fixed at compile time and it allocates directly on the stack (or inline in its enclosing object).
- **Access**: O(1)

**When to pick:** size known at compile time; want value-semantic arrays that know their length; avoid decay-to-pointer surprises of C arrays.

```cpp
#include <array>

// Instantiation forms
std::array<int, 5> arr = {1, 2, 3, 4, 5};

// Core operations and signatures
int a = arr[0];                          // reference operator[](size_type pos);
int b = arr.at(1);                       // reference at(size_type pos);
int f = arr.front();                     // reference front();
int bk = arr.back();                     // reference back();
size_t sz = arr.size();                  // constexpr size_type size() const; // Always 5
```

```cpp
#include <array>
#include <algorithm>

std::array<int, 4> a = {4, 1, 3, 2};
std::sort(a.begin(), a.end());           // works with <algorithm> like any contiguous range
int* raw = a.data();                     // T* data() noexcept;
a.fill(0);                               // void fill(const T& value);
```

::: trap
`std::array<T, N>` is *not* a dynamic container — `N` is part of the type. You cannot `push_back`. Passing `array<int, 5>` and `array<int, 6>` are different types.
:::

### String -> `std::string`
Conceptually a dynamic array of characters with added string-manipulation utilities.
- **Access**: O(1)
- **Insert/Delete**: Amortised O(1) at the end, O(n) in the middle.

**When to pick:** text; need search/substr/concat; treat as the `char` specialisation of a dynamic array with SSO (small-string optimisation) on typical implementations.

```cpp
#include <string>

// Instantiation forms
std::string s1 = "hello";                // From string literal
std::string s2(5, 'a');                  // Fill constructor: "aaaaa"
std::string s3(s1, 1, 3);                // Substring: "ell" (starts at index 1, length 3)

// Core operations and signatures
s1.push_back('!');                       // void push_back(char c);
s1.append(" world");                     // string& append(const char* s);
s1 += "!";                               // string& operator+=(const char* s);
char c = s1[0];                          // reference operator[](size_type pos);
std::string sub = s1.substr(1, 4);       // string substr(size_type pos = 0, size_type count = npos) const;
size_t pos = s1.find("world");           // size_type find(const char* s, size_type pos = 0) const;
```

```cpp
#include <string>

std::string path = "/usr";
path += "/local";                        // append in place
path.append("/bin");
if (path.find("local") != std::string::npos)
    path.replace(path.find("local"), 5, "opt"); // string& replace(...);
```

::: trap
`find` returns `std::string::npos` (usually `size_t(-1)`) on failure — never compare the result to `-1` as a signed int without care; compare to `npos`.
:::

### Singly Linked List -> `std::forward_list`
A forward-linked list. It has zero memory overhead beyond a basic pointer-linked list, which is why it conspicuously lacks a `size()` function (maintaining a count would add overhead or make `size()` O(n)).
- **Insert/Delete**: O(1) with an iterator (specifically, the iterator to the position *before* the insertion point).

**When to pick:** rare — need singly-linked semantics, forward-only traversal, and minimal per-node overhead. Prefer `list` or `vector` unless you have a measured reason.

```cpp
#include <forward_list>

// Instantiation forms
std::forward_list<int> fl = {1, 2, 3};

// Core operations and signatures
fl.push_front(0);                        // void push_front(const T& value); 
fl.pop_front();                          // void pop_front();                
fl.insert_after(fl.begin(), 99);         // iterator insert_after(const_iterator pos, const T& value);
fl.erase_after(fl.begin());              // iterator erase_after(const_iterator pos);                  
```

`insert_after(begin(), …)` inserts *after* the first element. To insert at the front without `push_front`, use `before_begin()`:

```cpp
#include <forward_list>

std::forward_list<int> fl2 = {1, 2, 3};
fl2.insert_after(fl2.begin(), 99);         // {1, 99, 2, 3}
fl2.insert_after(fl2.before_begin(), 0);   // {0, 1, 99, 2, 3}
```

::: trap
`forward_list` has no `size()`, no `push_back`, and no iterator arithmetic. `insert_after` / `erase_after` need the iterator *before* the victim — off-by-one relative to `list::insert`.
:::

### Doubly Linked List -> `std::list`
A doubly linked list. Nodes maintain pointers to both the next and previous elements.
- **Insert/Delete**: O(1) with an iterator.

**When to pick:** you already hold iterators to splice/erase points; need stable iterators under insert/erase elsewhere; heavy `splice` between lists. Not for random access or cache-sensitive scans.

```cpp
#include <list>

// Instantiation forms
std::list<int> lst = {1, 2, 3};

// Core operations and signatures
lst.push_back(4);                        // void push_back(const T& value);
lst.push_front(0);                       // void push_front(const T& value);
lst.pop_back();                          // void pop_back();
lst.pop_front();                         // void pop_front();
lst.insert(lst.begin(), 99);             // iterator insert(const_iterator pos, const T& value);
lst.erase(lst.begin());                  // iterator erase(const_iterator pos);
size_t sz = lst.size();                  // size_type size() const;
```

```cpp
#include <list>

std::list<int> a = {1, 2, 3};
std::list<int> b = {10, 20};
a.splice(a.end(), b);                    // void splice(const_iterator pos, list& other);
                                         // O(1) move of nodes; b is now empty; a is {1,2,3,10,20}
```

::: trap
`list` iterators stay valid across insert/erase of *other* elements, but an erased element's iterator is invalidated. There is still no `operator[]` — access by index is O(n).
:::

::: interview
*"When would you use `std::list` over `std::vector`?"* Only when you need O(1) insert/erase *given an iterator*, iterator stability under mutations elsewhere, or O(1) `splice`. If the answer starts with "because insert is O(1)" without mentioning the iterator requirement, dig deeper.
:::

### Double-ended Queue -> `std::deque`
A segmented array structure allowing fast insertions and deletions at *both* ends. It lacks the strict contiguous memory guarantee of `std::vector`, but maintains constant-time indexed access.
- **Access**: O(1)
- **Insert/Delete at ends**: Amortised O(1)
- **Insert/Delete in middle**: O(n)

**When to pick:** need fast push/pop at *both* ends *and* occasional random access; default underlying container for `stack` / `queue`. Prefer `vector` if you only grow at the back.

```cpp
#include <deque>

// Instantiation forms
std::deque<int> dq = {1, 2, 3};

// Core operations and signatures
dq.push_back(4);                         // void push_back(const T& value);
dq.push_front(0);                        // void push_front(const T& value);
dq.pop_back();                           // void pop_back();
dq.pop_front();                          // void pop_front();
int a = dq[0];                           // reference operator[](size_type pos);
```

```cpp
#include <deque>

std::deque<int> window;
window.push_back(10);
window.push_front(5);                    // {5, 10}
int mid = window[1];                     // O(1) index — unlike list
window.pop_front();                      // sliding-window style
```

::: trap
`deque` is *not* guaranteed contiguous — do not pass `&dq[0]` to a C API expecting one block (use `vector`). Middle insert still shifts elements (O(n)); only the ends are cheap.
:::

## Container Adaptors

Adaptors are not new data structures; they wrap existing sequence containers (like `deque` or `vector`) to provide a restricted interface.

### Stack (LIFO) -> `std::stack`
Last-In, First-Out. Defaults to wrapping a `std::deque`.
- **Push/Pop/Top**: O(1)

**When to pick:** strict LIFO interface (DFS explicit stack, undo buffers, bracket matching). Restricts the API so you cannot accidentally index the middle.

```cpp
#include <stack>

std::stack<int> st;

// Core operations and signatures
st.push(1);                              // void push(const T& value); 
st.pop();                                // void pop();                
int top = st.top();                      // reference top();           
bool empty = st.empty();                 // bool empty() const;
```

```cpp
#include <stack>
#include <vector>

// Explicit underlying container (often vector for cache locality)
std::stack<int, std::vector<int>> st_v;
st_v.push(3);
st_v.push(1);
// top == 1; pop yields LIFO order
```

::: trap
`pop()` returns `void` — it does **not** return the removed element. Call `top()` first, then `pop()`. Same trap applies to `queue` and `priority_queue`.
:::

### Queue (FIFO) -> `std::queue`
First-In, First-Out. Defaults to wrapping a `std::deque`.
- **Push/Pop/Front/Back**: O(1)

**When to pick:** BFS layers, producer–consumer buffers, any strict FIFO. Do not use when you need priority ordering — that is `priority_queue`.

```cpp
#include <queue>

std::queue<int> q;

// Core operations and signatures
q.push(1);                               // void push(const T& value); 
q.pop();                                 // void pop();                
int f = q.front();                       // reference front();         
int b = q.back();                        // reference back();          
```

```cpp
#include <queue>

std::queue<int> bfs;
bfs.push(0);
while (!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    // process u, push neighbours…
}
```

::: interview
*"Implement a queue with two stacks"* / *"stack with two queues"* are classic interface questions. Know that STL `queue` is an adaptor (default `deque`), not a linked-list invent-your-own unless asked.
:::

### Binary Heap / Priority Queue -> `std::priority_queue`
Defaults to wrapping a `std::vector` and acting as a max-heap (largest element is yielded first).
- **Push/Pop**: O(log n)
- **Top**: O(1)

**When to pick:** repeatedly need the current min or max; Dijkstra / Huffman / scheduling style workloads. Not for arbitrary delete-by-value or decrease-key (no STL support — simulate with lazy deletion or roll your own heap).

```cpp
#include <queue>
#include <vector>
#include <functional> // For std::greater

// Max-heap by default
std::priority_queue<int> max_pq;

// Min-heap requires explicitly stating the underlying container and comparator
std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;

// Core operations and signatures
max_pq.push(10);                         // void push(const T& value); 
max_pq.pop();                            // void pop();                
int top = max_pq.top();                  // const_reference top() const; 
```

```cpp
#include <queue>
#include <vector>
#include <functional>

std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
min_pq.push(5);
min_pq.push(1);
min_pq.push(3);
// min_pq.top() == 1
```

::: trap
`priority_queue` has **no iterators** and no find/erase-by-value. Default is a **max**-heap — forgetting `std::greater` is a common Dijkstra bug. `top()` returns `const` — you cannot mutate the priority in place.
:::

::: interview
*"Max-heap or min-heap?"* State the default (`less<T>` → largest on top) and show the three-template-argument min-heap form. Mention that true decrease-key is not available on `std::priority_queue`.
:::

## Associative Containers

Associative containers optimise for retrieval by key.

### Balanced BST (Ordered) -> `std::set` / `std::map`
Implemented as self-balancing binary search trees (typically Red-Black trees). They keep elements sorted.
- **Search/Insert/Delete**: O(log n)
- **Iteration**: Yields elements in sorted order.

**When to pick:** need keys in sorted order; need lower/upper bound; need guaranteed O(log n) worst-case (adversarial keys / no good hash); ordered unique keys (`set`/`map`) or ordered duplicates (`multiset`/`multimap`).

```cpp
#include <set>
#include <map>
#include <string>

// Instantiation
std::set<int> s = {3, 1, 4};
std::map<std::string, int> m = {{"apple", 1}};

// Core operations and signatures
s.insert(2);                             // std::pair<iterator, bool> insert(const T& value); 
s.erase(1);                              // size_type erase(const T& value);                  
auto sit = s.find(3);                    // iterator find(const T& value);                    

m.insert({"banana", 2});                 // std::pair<iterator, bool> insert(const value_type& value); 
m["cherry"] = 3;                         // T& operator[](const Key& key); // Inserts if not found                          
m.erase("apple");                        // size_type erase(const Key& key);                           
auto mit = m.find("banana");             // iterator find(const Key& key);                             
```

Ordered lookups beyond exact match:

```cpp
#include <set>

std::set<int> s = {1, 3, 5, 7};
auto lb = s.lower_bound(4);              // iterator to first element >= 4 → 5
auto ub = s.upper_bound(5);              // iterator to first element > 5  → 7
```

`multiset` / `multimap` allow duplicate keys with the same O(log n) costs; `equal_range` returns the half-open iterator span of equivalents.

```cpp
#include <set>

std::multiset<int> ms = {1, 1, 2};
ms.insert(1);                            // now three 1s
auto range = ms.equal_range(1);          // pair<iterator,iterator> covering all 1s
```

::: trap
`map::operator[]` **default-inserts** if the key is missing — disastrous when you meant read-only lookup. Use `find` / `at` / `contains` (C++20) for pure queries. `at` throws if absent.
:::

::: keypoint
**Ordered map/set** here means `std::map` / `std::set` (tree-based, sorted). **Unordered** means `std::unordered_map` / `std::unordered_set` (hash-based, no order). Say "ordered" in interviews when you need sorted iteration or `lower_bound`.
:::

### Hash Table -> `std::unordered_set` / `std::unordered_map`
Implemented using hash tables. They do not maintain any order.
- **Search/Insert/Delete**: Average O(1), Worst O(n) (on severe hash collisions).

**When to pick:** fast average lookup/insert by key; order does not matter; keys are hashable. Prefer ordered `map`/`set` when you need sorted order, range queries, or hard O(log n) worst-case.

```cpp
#include <unordered_set>
#include <unordered_map>
#include <string>

// Instantiation
std::unordered_set<int> us = {3, 1, 4};
std::unordered_map<std::string, int> um = {{"apple", 1}};

// Operations use identical signatures to set/map, but differ in complexity
us.insert(2);                            // Average O(1), Worst O(n)
us.erase(1);                             
auto uit = us.find(3);                   

um["cherry"] = 3;                        
um.erase("apple");                       
auto umit = um.find("cherry");           
```

```cpp
#include <unordered_map>
#include <string>

std::unordered_map<std::string, int> freq;
freq["alpha"]++;                         // create-or-increment idiom
freq.reserve(1000);                      // void reserve(size_type count); // reduce rehashes
```

::: trap
Custom types need a hash and equality. Worst-case O(n) under collisions is real — for adversarial or pathological keys, prefer `std::map`. Iteration order is unspecified and unstable across rehashes.
:::

::: interview
*"map vs unordered_map?"* Average O(1) vs guaranteed O(log n); sorted iteration and `lower_bound` only on the tree; hash requirements and collision risk only on the unordered side. Pick based on *order needed?* and *worst-case needed?*.
:::

## Bit set -> `std::bitset`

A **bitset** is a fixed-size pack of bits (compile-time `N`), not a general container of arbitrary objects. It implements the abstract "array of bits / bit vector" structure with word-parallel bitwise algebra.

- **Access / set / test one bit**: O(1)
- **Bitwise `&` `|` `^` / shifts on the whole set**: O(N / word-size) — effectively linear in number of words
- **Count of set bits (`count`)**: O(N / word-size) typically

**When to pick:** fixed `N` known at compile time; need dense flags or bitset DP / sieve segments. For contest-grade detail (vs `vector<bool>`, bulk ops, runtime-sized alternatives), see **s55 — The Competitive-Programming and DSA Toolkit**. Policy-based ordered-statistic trees (`__gnu_pbds`) are also covered there — do not reinvent them here.

```cpp
#include <bitset>

std::bitset<32> flags;
flags.set(3);                            // reference set(size_t pos, bool val = true);
flags.reset(3);                          // reset bit
flags.flip(0);                           // toggle
bool on = flags.test(0);                 // bool test(size_t pos) const;
std::size_t n = flags.count();           // number of bits set to 1
```

::: trap
Prefer `std::bitset<N>` (or a manual `vector<uint64_t>`) over `std::vector<bool>` — the latter is a specialisation with proxy references and no proper container semantics. `N` is fixed at compile time.
:::

## Heterogeneous Aggregates

### Pair and Tuple -> `std::pair` / `std::tuple`
Used to bundle disparate, heterogeneous values together without writing a custom `struct`.

```cpp
#include <utility>
#include <tuple>
#include <string>

// Pair
std::pair<int, std::string> p = {1, "one"};
std::pair<int, std::string> p2 = std::make_pair(2, "two");

int k = p.first;                         // Direct member access
std::string v = p.second;

// Tuple
std::tuple<int, double, char> t = {1, 3.14, 'a'};
std::tuple<int, double, char> t2 = std::make_tuple(2, 2.71, 'b');

int i = std::get<0>(t);                  // template<std::size_t I, class... Types> constexpr std::tuple_element_t<I, std::tuple<Types...>>& get(std::tuple<Types...>& t);
double d = std::get<1>(t);
```

```cpp
#include <map>
#include <string>
#include <tuple>

// map nodes are pair<const Key, T>
std::map<std::string, int> m;
m.insert(std::pair<const std::string, int>{"x", 1});

auto [a, b, c] = std::tuple{1, 2.0, 'z'}; // C++17 structured bindings
```

::: keypoint
`pair` / `tuple` are *aggregates*, not sequence containers — no push/pop, no iterators over "elements" in the container sense (beyond `std::apply` / structured bindings). Use them as map value types, return bundles, and heap nodes.
:::

## Summary Table

| Data structure | STL container | access | search | insert | delete | ordered? | notes |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Dynamic array** | `std::vector` | O(1) | O(n) | Amortised O(1)* | Amortised O(1)* | No | *At the end. O(n) in the middle. Default choice. |
| **Fixed array** | `std::array` | O(1) | O(n) | N/A | N/A | No | Stack-allocated, fixed size at compile time. |
| **String** | `std::string` | O(1) | O(n) | Amortised O(1)* | Amortised O(1)* | No | *At the end. Conceptually a `vector<char>`. |
| **Singly linked list** | `std::forward_list` | O(n) | O(n) | O(1)** | O(1)** | No | **When provided an iterator to the position. |
| **Doubly linked list** | `std::list` | O(n) | O(n) | O(1)** | O(1)** | No | **When provided an iterator to the position. |
| **Double-ended queue** | `std::deque` | O(1) | O(n) | Amortised O(1)***| Amortised O(1)***| No | ***At both ends. |
| **Stack (LIFO)** | `std::stack` | O(1) top | O(n) | O(1) | O(1) | No | Adaptor wrapping a sequence container. |
| **Queue (FIFO)** | `std::queue` | O(1) ends | O(n) | O(1) | O(1) | No | Adaptor wrapping a sequence container. |
| **Binary heap** | `std::priority_queue`| O(1) top | O(n) | O(log n) | O(log n) | Partial | Max-heap by default. |
| **Balanced BST** | `std::set` / `map` | O(log n) | O(log n) | O(log n) | O(log n) | Yes | Yields elements in sorted order. |
| **Ordered map/set** | `std::map` / `std::set` (also `multi*`) | O(log n) | O(log n) | O(log n) | O(log n) | Yes | Same trees; `multi*` allows duplicate keys. |
| **Hash table** | `std::unordered_set` / `map` | O(1) avg | O(1) avg | O(1) avg | O(1) avg | No | Worst-case O(n) upon hash collision. |
| **Bitset** | `std::bitset<N>` | O(1) bit | O(N/w) scan | O(1) set bit | O(1) reset | No | Fixed `N`; see s55 for CP detail. |

### Complete pick-guide mapping

Same rows, emphasising *when to pick* rather than repeating every complexity cell:

| Abstract structure | STL type | Key ops (Big-O) | When to pick |
| :--- | :--- | :--- | :--- |
| Dynamic array | `std::vector<T>` | `[]` O(1); `push_back` amortised O(1); middle insert O(n) | **Default.** Index + append + cache-friendly scan. |
| Static / fixed array | `std::array<T,N>` | `[]` O(1); no grow | Compile-time size; stack/inline storage; known `N`. |
| Singly linked list | `std::forward_list<T>` | `insert_after`/`erase_after` O(1) with prior iterator; no `size()` | Minimal node overhead; forward-only; rare. |
| Doubly linked list | `std::list<T>` | insert/erase O(1) with iterator; `splice` O(1); no `[]` | Stable iterators; splice-heavy; already hold position. |
| Stack | `std::stack<T>` | `push`/`pop`/`top` O(1) | Strict LIFO API. |
| Queue | `std::queue<T>` | `push`/`pop`/`front`/`back` O(1) | Strict FIFO (BFS). |
| Deque | `std::deque<T>` | ends amortised O(1); `[]` O(1); middle O(n) | Fast both ends **and** indexing; not contiguous. |
| Priority queue / binary heap | `std::priority_queue<T>` | `push`/`pop` O(log n); `top` O(1) | Repeated min/max; no arbitrary delete. |
| Hash table | `std::unordered_map` / `unordered_set` | average O(1) lookup/insert/erase; worst O(n) | Fast average key ops; order irrelevant. |
| Balanced BST | `std::set` / `map` | all key ops O(log n) | Sorted order; `lower_bound`; hard worst-case. |
| Ordered map/set (unique or multi) | `map`/`set`/`multimap`/`multiset` | O(log n) | Ordered keys; duplicates → `multi*`. |
| Bitset | `std::bitset<N>` | bit get/set O(1); word-parallel `&`/`|` | Fixed-width flags / bit algebra; see s55. |

## Choosing a container

Walk the questions in order; stop at the first decisive answer.

<!-- FIG s49: decision flowchart — order? duplicates? index? middle insert? both ends? min/max? bits? → STL type -->

1. **Need an array of bits / bit algebra with fixed width?** → `std::bitset<N>` (details in s55). Runtime-sized bit packs → `vector<uint64_t>` (s55), not `vector<bool>`.
2. **Need only LIFO or only FIFO?** → `stack` or `queue` (adaptors). Need **current min/max repeatedly**? → `priority_queue`.
3. **Need lookup by key?**
   - Sorted order or `lower_bound` / guaranteed O(log n)? → `map` / `set` (or `multi*` if duplicates).
   - Average O(1) and no order? → `unordered_map` / `unordered_set`.
4. **Need random-access index (`[]`)?**
   - Size fixed at compile time? → `array`.
   - Grow at the back only? → `vector` (default).
   - Grow/shrink at **both** ends? → `deque`.
5. **Need fast insert/erase in the middle?**
   - Already hold an iterator / need `splice` / need iterator stability? → `list` (or `forward_list` if singly linked is enough).
   - Otherwise still prefer `vector` and pay O(n) moves — usually faster in practice (see contiguous-vs-node above).
6. **Need duplicates in a sorted key collection?** → `multiset` / `multimap`. Unordered duplicates-by-key → `unordered_multiset` / `unordered_multimap`.
7. **Unsure?** → `std::vector`. Justify anything else.

::: keypoint
Decision axes that matter in interviews: **order?** (sorted / insertion / none), **duplicates?**, **index?**, **where you insert** (end / both ends / middle with iterator), **worst-case vs amortised**, **cache locality**.
:::

::: interview
*"Which container and why?"* drills — practise answering with one requirement → one type:

- Stream of integers, frequent append, occasional index → **`vector`**.
- Sliding window needing push back and pop front → **`deque`** (or `queue` if no indexing).
- Dictionary with sorted keys for predecessor queries → **`map`** / **`set`**.
- Frequency count of words, no ordering → **`unordered_map`**.
- Process jobs by highest priority → **`priority_queue`**.
- Undo stack of edits → **`stack`**.
- Fixed 256 privilege flags → **`bitset<256>`**.
- O(1) erase of a known node in an LRU list → **`list`** (+ map from key to iterator).
:::

## Building Missing Data Structures

The STL does not provide every classical data structure out of the box. You must construct the rest from primitives:

### Graph
There is no built-in graph container. The standard approach is to build an **adjacency list**.
```cpp
// Adjacency list using a vector of vectors (for consecutive integer node IDs)
std::vector<std::vector<int>> adjList(numNodes);

// Adjacency list for non-sequential or string node IDs
std::unordered_map<std::string, std::vector<std::string>> adjMap;
```

### General Tree
There is no built-in tree. Build it by defining a node `struct` that holds its value and a container of children.
```cpp
struct TreeNode {
    int val;
    std::vector<TreeNode*> children;
};
```

### Trie (Prefix Tree)
Implement a node containing a mapping to its children. You can use an array (if the alphabet is small and fixed) or an associative container.
```cpp
struct TrieNode {
    std::map<char, TrieNode*> children; // Or std::array<TrieNode*, 26>
    bool isWord = false;
};
```

### Disjoint-Set / Union-Find
Model the parent relationships using a simple `std::vector`. The index represents the element, and the value at that index represents its parent.
```cpp
std::vector<int> parent(numElements);
// Initialise each element to be its own parent
for (int i = 0; i < numElements; ++i) {
    parent[i] = i; 
}
```

### Bit Sets
If you need an array of booleans tightly packed into bits, do not use `std::vector<bool>` (which is famously non-standard). If the size is known at compile time, use `std::bitset`.
```cpp
#include <bitset>

std::bitset<32> bits; // 32 bits, all initialised to 0
bits.set(0);          // Set the 0th bit to 1
bool isSet = bits.test(0);
```

For full `bitset` algebra, speed notes versus `vector<bool>`, and runtime-sized bit packs, see **s55**. For **policy-based data structures** (GCC `__gnu_pbds` ordered-statistic trees — find *k*-th / rank in O(log n)), also see **s55**; they are not ISO STL and are out of scope for this mapping section.

::: interview
**Interview focus**: Be prepared to justify your container choice.
- **Which container to use**: Default to `std::vector` because contiguous memory gives superior cache locality. Use `std::list` only if you require O(1) insertions/deletions in the middle *and* you will already have a valid iterator to that position.
- **std::map vs std::unordered_map**: `std::unordered_map` is faster for general use (average O(1) access/insert/delete), but has a worst-case of O(n) on hash collisions. `std::map` gives guaranteed O(log n) worst-case performance and allows iterating over keys in sorted order.
- **Graph representation**: If asked how to represent a graph in C++, state that C++ has no built-in graph container and you will build an adjacency list using `std::vector<std::vector<int>>`.
:::

::: interview
Extra "which container and why" prompts to rehearse aloud:
- Why is middle-insert Big-O on `list` misleading in practice?
- When is amortised O(1) unacceptable?
- Why might `deque` be wrong for a C-style buffer API?
- How do you get a min-heap from `priority_queue`?
- `set` vs `unordered_set` for "report keys in sorted order".
:::
