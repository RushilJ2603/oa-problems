# The STL Container Zoo

The C++ Standard Template Library (STL) provides a collection of generic data structures, known as containers, alongside iterators and algorithms. Containers are broadly divided into:
- **Sequence containers:** Data is stored linearly (e.g., `vector`, `deque`, `list`).
- **Container adaptors:** Wrappers providing specialized interfaces (e.g., `stack`, `queue`, `priority_queue`).
- **Ordered associative containers:** Data is stored in sorted order via trees (e.g., `set`, `map`).
- **Unordered associative containers:** Data is stored via hash tables for $O(1)$ access (e.g., `unordered_set`, `unordered_map`).
- **Bitsets & Strings:** Specialized structures for bit manipulation and character sequences.

::: keypoint
**Which container when:** Start with a `vector` for sequence data. If you need a LIFO/FIFO interface, use `stack` or `queue`. For priority-based retrieval, use `priority_queue`. If you need fast lookups of unique elements or key-value pairs, use `unordered_map` or `unordered_set`. Only switch to `map` or `set` when you specifically require sorted order or order-statistics operations like `lower_bound`.
:::

## Sequence Containers

### `std::array<T, N>`
A fixed-size array wrapper. Its **underlying data structure** is a standard contiguous C-style array. It provides the same performance as a raw array but adds standard container interfaces (like `.size()` and iterators) and optional bounds checking (via `.at()`).

| Operation | Complexity |
| --- | --- |
| Access | $O(1)$ |
| Size | $O(1)$ |

```cpp
#include <array>
#include <iostream>

void array_demo() {
    std::array<int, 3> arr = {1, 2, 3};
    arr.front() = 10;
    arr.back() = 30;
    arr[1] = 20; // No bounds checking
    
    for (int x : arr) {
        std::cout << x << " ";
    }
}
```
**When to use:** When you need a small, stack-allocated, fixed-size array that interacts smoothly with STL algorithms, preferring it over raw C-arrays for safety.

### `std::vector`
A dynamic array. Its **underlying data structure** is a dynamically allocated contiguous memory block. When its capacity is exhausted, it allocates a new larger block (typically double the size), copies elements over, and deletes the old block.

| Operation | Complexity |
| --- | --- |
| Access | $O(1)$ |
| Push/Pop Back | $O(1)$ amortized |
| Insert/Erase (middle) | $O(n)$ |

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

void vector_demo() {
    std::vector<int> v;
    v.reserve(10); // Preallocate to avoid reallocations

    // Insertion
    v.push_back(1);
    v.emplace_back(2); // Constructs element in-place
    v.insert(v.begin() + 1, 99); // Insert 99 at index 1

    // Access
    int a = v.front();
    int b = v.back();
    int c = v[0]; // No bounds check
    int d = v.at(0); // Throws std::out_of_range if invalid

    // Size & Capacity
    bool is_empty = v.empty();
    size_t s = v.size();
    size_t cap = v.capacity();
    v.resize(20, 0); // Change size to 20, fill new elements with 0
    v.shrink_to_fit(); // Frees unused allocated memory
    
    // Deletion
    v.pop_back();
    v.erase(v.begin()); // Erase first element
    v.clear(); // Removes all elements

    // 2-D Vector Initialization (e.g., grid of n x m initialized to 0)
    int n = 5, m = 10;
    std::vector<std::vector<int>> grid(n, std::vector<int>(m, 0));

    // The Erase-Remove Idiom (remove all instances of 2)
    std::vector<int> v2 = {1, 2, 3, 2, 4};
    v2.erase(std::remove(v2.begin(), v2.end(), 2), v2.end());

    // Assign new contents
    v2.assign(5, 10); // v2 becomes {10, 10, 10, 10, 10}
}
```
**When to use:** This is the default container. Use it for almost everything unless you explicitly need fast $O(1)$ insertions at the front or middle.

::: trap
**Iterator Invalidation:** Reallocating a vector (e.g., pushing elements when `size == capacity`) invalidates all iterators, pointers, and references to its elements. Always return indices, not references or iterators, if the vector might grow.
:::

::: trap
**The `vector<bool>` Proxy:** `std::vector<bool>` is uniquely specialized to use 1 bit per element. Thus, `v[i]` does not return a `bool&` but a temporary proxy object. This breaks generic code expecting a reference. Prefer `std::vector<char>` or `std::deque<bool>` if standard reference behavior is needed.
:::

### `std::deque`
A double-ended queue. Its **underlying data structure** is a block-map (an array of pointers to fixed-size memory chunks). This avoids large contiguous memory reallocations while providing random access.

| Operation | Complexity |
| --- | --- |
| Access | $O(1)$ |
| Push/Pop (both ends) | $O(1)$ |
| Insert/Erase (middle) | $O(n)$ |

```cpp
#include <deque>

void deque_demo() {
    std::deque<int> dq;
    dq.push_back(1);
    dq.push_front(2); // O(1) front insertion
    int first = dq.front();
    int last = dq.back();
    dq.pop_front();
    dq.pop_back();
}
```
**When to use:** Use when you need to frequently push/pop from both the front and back of the sequence (e.g., sliding window algorithms).

### `std::list` & `std::forward_list`
Their **underlying data structures** are a doubly linked list (`std::list`) and a singly linked list (`std::forward_list`). Memory is non-contiguous, meaning elements are scattered as separate nodes in the heap.

| Operation | Complexity |
| --- | --- |
| Access | $O(n)$ |
| Push/Pop (front/back) | $O(1)$ |
| Insert/Erase (given iterator) | $O(1)$ |

```cpp
#include <list>
#include <forward_list>

void list_demo() {
    std::list<int> l = {1, 2, 3};
    l.push_front(0);
    l.push_back(4);
    
    std::list<int> l2 = {10, 20};
    // Splice: move all elements of l2 into l right before l.begin() in O(1) time
    l.splice(l.begin(), l2);
}
```
**When to use:** Only when you absolutely need $O(1)$ insertions and deletions anywhere in the sequence (provided you already have the iterator), or when you need the $O(1)$ `splice` operation.

### Raw Arrays + `memset` vs `fill`
Raw C-arrays are sometimes used in competitive programming for minor speed gains in global memory, but they require careful initialization.

```cpp
#include <cstring>
#include <algorithm>

void array_init_demo() {
    int arr[100];
    
    // std::fill works for ANY value and ANY type
    std::fill(arr, arr + 100, 5); 
    
    // memset works by setting BYTES. 
    memset(arr, 0, sizeof(arr));  // Initializes to 0
    memset(arr, -1, sizeof(arr)); // Initializes to -1
    memset(arr, 0x3f, sizeof(arr)); // Standard CP trick for "Infinity" (~10^9)
}
```

::: trap
**The `memset` Gotcha:** `memset` sets each byte individually. Doing `memset(arr, 1, sizeof(arr))` sets each byte to `00000001`, resulting in the 32-bit integer `16843009`, not `1`! Use `std::fill` for values other than `0`, `-1`, or `0x3f`.
:::

## Container Adaptors

### `std::stack` and `std::queue`
Adaptors wrap an existing sequence container. `std::stack` wraps `std::deque` by default and enforces LIFO (Last-In-First-Out). `std::queue` wraps `std::deque` and enforces FIFO (First-In-First-Out).

| Operation | Complexity |
| --- | --- |
| Push/Pop | $O(1)$ |
| Top/Front/Back | $O(1)$ |

```cpp
#include <stack>
#include <queue>

void stack_queue_demo() {
    std::stack<int> s;
    s.push(1);
    int top = s.top();
    s.pop();
    bool se = s.empty();
    size_t sz = s.size();
    
    std::queue<int> q;
    q.push(1);
    int first = q.front();
    int last = q.back();
    q.pop();
}
```
**When to use:** Depth-First Search (DFS) uses a `stack`. Breadth-First Search (BFS) uses a `queue`.

### `std::priority_queue`
A binary heap adaptor. Its **underlying data structure** is a complete binary tree laid out in a sequence (usually a `std::vector`), maintaining the heap-order property. By default, it is a **max-heap**.

| Operation | Complexity |
| --- | --- |
| Push/Pop | $O(\log n)$ |
| Top | $O(1)$ |

```cpp
#include <queue>
#include <vector>
#include <functional>
#include <tuple>

// 3. Custom struct for PQ elements
struct Task {
    int id;
    int priority;
    // Operator overloads can also define sorting
    bool operator<(const Task& other) const {
        return priority < other.priority; 
    }
};

void pq_demo() {
    // 1. Max-heap (default)
    std::priority_queue<int> max_pq;
    max_pq.push(10);
    int top_val = max_pq.top(); // 10
    max_pq.pop();
    bool is_emp = max_pq.empty();
    size_t sz = max_pq.size();
    
    // 2. Min-heap (using std::greater)
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    
    // 3. Custom Comparator via Struct Functor
    struct CustomComp {
        bool operator()(const int& a, const int& b) const {
            return a > b; // Returns true if 'a' has LOWER priority than 'b'
        }
    };
    std::priority_queue<int, std::vector<int>, CustomComp> custom_pq;
    
    // 4. Custom Comparator via Lambda
    auto cmp = [](const int& a, const int& b) { return a > b; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> lambda_pq(cmp);
    
    // PQ of pairs/tuples (sorts lexicographically by first element, then second)
    std::priority_queue<std::pair<int, int>> pq_pair;
    
    // PQ of custom structs
    std::priority_queue<Task> task_pq;
}
```
**When to use:** Finding the top $k$ elements, Dijkstra's algorithm, maintaining a running median, or repeatedly extracting minimum/maximum values.

::: trap
**Reversed Comparator:** In sorting, a comparator returning `a < b` sorts in ascending order. In a `std::priority_queue`, the comparator returns `true` if `a` has **lower priority** than `b` (meaning `a` will sink lower in the heap). Thus, `a > b` generates a **min-heap**.
:::

## Ordered Associative Containers

::: heavy
The **underlying data structure** for `set` and `map` is a self-balancing Red-Black Binary Search Tree. Elements are kept strictly ordered. The height of the tree is bounded to $O(\log n)$, guaranteeing that searches, insertions, and deletions take $O(\log n)$ worst-case time.
:::

### `std::set` and `std::multiset`
A collection of keys. `std::set` stores unique keys, while `std::multiset` allows duplicates.

| Operation | Complexity |
| --- | --- |
| Insert/Erase/Find/Count | $O(\log n)$ |
| lower_bound / upper_bound | $O(\log n)$ |
| Size | $O(1)$ |

```cpp
#include <set>
#include <iostream>

void set_demo() {
    std::set<int> s = {3, 1, 4, 1, 5}; // stores {1, 3, 4, 5}
    
    // Insertion & Deletion
    s.insert(2);
    s.erase(3);
    
    // Search
    if (s.find(4) != s.end()) { /* Found */ }
    int cnt = s.count(4); // 1 if present, 0 if not
    
    // Ordered Traversal
    for (int x : s) std::cout << x << " "; // 1 2 4 5
    
    // Min/Max elements
    int min_val = *s.begin();
    int max_val = *s.rbegin();
    
    // Bounds (use members, NOT std::lower_bound)
    auto it1 = s.lower_bound(2); // First element >= 2
    auto it2 = s.upper_bound(4); // First element > 4
    
    // Multiset
    std::multiset<int> ms = {1, 1, 1, 2};
    // ERASING in multiset
    ms.erase(1); // TRAP: Removes ALL copies of 1
    ms.erase(ms.find(1)); // CORRECT: Removes only ONE copy
}
```
**When to use:** Deduplication when order matters, or when you need to efficiently find the closest elements to a value using `lower_bound`/`upper_bound`.

::: trap
**Multiset Erase:** Calling `multiset.erase(val)` removes **all** occurrences of `val`! To remove just one occurrence, use `multiset.erase(multiset.find(val))`.
:::

### `std::map` and `std::multimap`
A collection of key-value pairs sorted by unique keys (`map`) or non-unique keys (`multimap`).

| Operation | Complexity |
| --- | --- |
| Insert/Erase/Find | $O(\log n)$ |
| Access via `[]` | $O(\log n)$ |

```cpp
#include <map>
#include <string>
#include <iostream>

void map_demo() {
    std::map<std::string, int> mp;
    
    mp["apple"] = 1; // Inserts "apple" with value 1
    mp["banana"] = 2;
    
    // Search
    if (mp.find("cherry") == mp.end()) { /* Not found */ }
    
    // Structured binding loop
    for (auto const& [key, val] : mp) {
        std::cout << key << ": " << val << "\n";
    }
    
    // Deletion
    mp.erase("apple");
    
    // Bounds
    auto it = mp.lower_bound("b"); // Iterator to pair
    
    // Custom Comparator (sort keys descending)
    std::map<int, int, std::greater<int>> desc_map;
}
```
**When to use:** When you need key-value associations and care about the sorted order of keys or need bound operations.

::: trap
**The `operator[]` Default Insertion:** Executing `mp["cherry"]` searches for "cherry". If it doesn't exist, it **inserts** "cherry" with a default-constructed value (e.g., `0`) and returns a reference to it. If you only want to check existence, use `.find()` or `.count()` to avoid accidentally polluting the map.
:::

## Unordered Associative Containers

::: heavy
The **underlying data structure** is a hash table (an array of buckets with chaining for collisions). The elements are placed into buckets based on the hash of their key. This provides fast $O(1)$ operations on average, but elements are not ordered.
:::

### `std::unordered_set` and `std::unordered_map`

| Operation | Complexity |
| --- | --- |
| Insert/Erase/Find | $O(1)$ average, $O(n)$ worst-case |

```cpp
#include <unordered_set>
#include <unordered_map>
#include <string>

void unordered_demo() {
    std::unordered_map<int, std::string> ump;
    ump.reserve(1024); // Preallocate buckets to avoid rehashing
    ump.max_load_factor(0.25); // Trade memory for speed (fewer collisions)
    
    ump[1] = "one";
    ump.erase(1);
    
    std::unordered_set<int> us = {1, 2, 3};
    us.insert(4);
}
```

**Custom Hashing for Pair / Tuple:**
Standard Library provides no default hash for `std::pair` or `std::tuple`, meaning `std::unordered_set<std::pair<int,int>>` will not compile. You must supply a custom hash function:
```cpp
#include <unordered_set>
#include <utility>

struct PairHash {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Simple bitwise combination
    }
};

void pair_hash_demo() {
    std::unordered_set<std::pair<int, int>, PairHash> pair_set;
    pair_set.insert({1, 2});
}
```
**When to use:** Use unordered variants anytime you just need exact key lookups and frequencies. Switch to `map` or `set` only when you need iteration in sorted order or `lower_bound`/`upper_bound`.

::: interview
Interviewers will frequently ask why you might use a `map` over an `unordered_map` despite the $O(\log n)$ versus $O(1)$ time complexity. Be prepared to discuss worst-case hash collisions and the necessity of ordered keys for operations like `lower_bound`.
:::

::: trap
**Anti-Hash Adversarial TLE:** Because hash tables have a worst-case $O(n)$ access time on heavy collisions, platforms like Codeforces have test cases intentionally designed to collide standard `std::hash`, causing Time Limit Exceeded (TLE). Fix this by writing a randomized custom hash, or simply falling back to `std::map`.
:::

## Bitset & String as Containers

### `std::bitset<N>`
A highly optimized fixed-size array of bits. 

| Operation | Complexity |
| --- | --- |
| Access bit/flip/test | $O(1)$ |
| Bitwise Ops (&, &#124;, ^) | $O(N / 64)$ |

```cpp
#include <bitset>
#include <iostream>
#include <string>

void bitset_demo() {
    std::bitset<10> b("1010"); // binary string init
    
    b.set(1); // Set bit 1 to true
    b.reset(2); // Set bit 2 to false
    b.flip(); // Invert all bits
    
    bool bit = b.test(3); // Bounds checked access
    int ones = b.count(); // Number of 1s
    
    bool has_any = b.any();
    bool all_ones = b.all();
    bool all_zeros = b.none();
    
    int first_set = b._Find_first(); // Index of first set bit
    
    std::string s = b.to_string();
    unsigned long ul = b.to_ulong();
}
```
**When to use:** Subset sums, DP speedups, and graph reachability where parallel bitwise operations yield a $64 \times$ performance boost.

### `std::string`
Acts heavily like `std::vector<char>` but comes with specialized string matching routines.

| Operation | Complexity |
| --- | --- |
| Access / append char | $O(1)$ |
| Substring / find | $O(n)$ or $O(n \cdot m)$ |

```cpp
#include <string>
#include <cctype>

void string_demo() {
    std::string s(5, 'a'); // "aaaaa"
    s += "bcd"; // Append
    s.push_back('e');
    
    // Substring
    std::string sub = s.substr(1, 3); // Starts at index 1, length 3
    
    // Searching
    size_t pos = s.find("bc");
    if (pos != std::string::npos) { /* Found */ }
    size_t rpos = s.rfind("a"); // Search from right
    
    // Conversions
    int num = std::stoi("123");
    long long llnum = std::stoll("123456789");
    double d = std::stod("3.14");
    std::string text = std::to_string(42);
    
    // Comparison & Char Arithmetic
    bool is_equal = (s == "aaaaabcde");
    char next_char = s[0] + 1; // 'b'
    
    // cctype functions
    bool is_alpha = std::isalpha('A');
    bool is_digit = std::isdigit('9');
    char lower = std::tolower('A');
    char upper = std::toupper('a');
}
```

## Iterators & Ranges

Iterators abstract the process of navigating a container. They come in 5 categories (increasing capability): Input, Output, Forward, Bidirectional (`list`, `set`, `map`), and Random-Access (`vector`, `deque`, `array`, raw pointers).

### Iterator Navigation
```cpp
#include <vector>
#include <iterator>

void iter_demo() {
    std::vector<int> v = {10, 20, 30, 40};
    auto it = v.begin(); // points to 10
    auto end_it = v.end(); // points JUST PAST 40
    
    auto rit = v.rbegin(); // points to 40
    auto rend_it = v.rend(); // points JUST BEFORE 10
    
    auto cit = v.cbegin(); // const iterator (read-only)
    
    std::advance(it, 2); // Moves iterator safely by 2 (points to 30)
    auto nxt = std::next(it); // Returns iterator 1 ahead
    auto prv = std::prev(it); // Returns iterator 1 behind
    int dist = std::distance(v.begin(), it); // Number of hops
    
    std::vector<int> target;
    // back_inserter automatically calls push_back on target during algorithm copies
    std::copy(v.begin(), v.end(), std::back_inserter(target));
}
```

### Invalidation Rules & Erase-in-loop Pattern

When containers are mutated, pointers, references, and iterators may be permanently invalidated and unsafe to use.

| Container | Insertion Invalidation | Deletion Invalidation |
| --- | --- | --- |
| `vector`, `string` | All, if capacity is exceeded | Elements at and after point of deletion |
| `deque` | All iterators | Elements at point of deletion (sometimes all) |
| `list` | None | Only the erased element |
| `set`, `map` | None | Only the erased element |
| `unordered_map` | All (if rehashed) | Only the erased element |

A common mistake is erasing an element in a loop and invalidating the active iterator.
```cpp
#include <vector>

void erase_loop_demo() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    for (auto it = v.begin(); it != v.end(); ) {
        if (*it % 2 == 0) {
            it = v.erase(it); // erase returns the VALID next iterator
        } else {
            ++it; // Only manually increment if no erasure occurred
        }
    }
}
```

## Summary

### Master Complexity Table

| Container | Insertion (Back) | Insertion (Front) | Insertion (Middle) | Deletion (Key/Iter) | Access (Index) | Search |
| --- | --- | --- | --- | --- | --- | --- |
| `vector` | $O(1)$ amortized | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(n)$ |
| `deque` | $O(1)$ | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ | $O(n)$ |
| `list` | $O(1)$ | $O(1)$ | $O(1)$ given iter | $O(1)$ given iter | $O(n)$ | $O(n)$ |
| `priority_queue` | $O(\log n)$ | - | - | $O(\log n)$ (top) | $O(1)$ (top) | - |
| `set` / `map` | - | - | $O(\log n)$ | $O(\log n)$ | - | $O(\log n)$ |
| `unordered_map` | - | - | $O(1)$ avg | $O(1)$ avg | - | $O(1)$ avg |

::: keypoint
**Decision List: Which Container When?**
1. Default for sequences: `vector`.
2. Push/Pop both ends (Sliding Window): `deque`.
3. Finding Top-K / Minimum / Maximum tracking: `priority_queue`.
4. Storing distinct elements or $O(1)$ key lookups: `unordered_set` / `unordered_map`.
5. Sorted order required, or `lower_bound`/`upper_bound` needed: `set` / `map`.
6. Bits with parallel logic / fast DP: `bitset`.
7. Middle splicing $O(1)$: `list`.
:::
