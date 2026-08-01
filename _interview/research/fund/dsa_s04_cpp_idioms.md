# C++ Idioms, Gotchas & the CP Toolkit

## Utilities, Randomness, and Misc

### `emplace` vs `insert`
When adding elements to a container, `insert` and `push_back` take an object of the element type, which often requires constructing a temporary object and moving or copying it into the container. `emplace` and `emplace_back` construct the element *in-place* directly inside the container's memory, bypassing the temporary object creation.

```cpp
#include <vector>
#include <string>

struct Node {
    int id;
    std::string name;
    Node(int i, std::string n) : id(i), name(std::move(n)) {}
};

int main() {
    std::vector<Node> v;
    
    // Creates a temporary Node, then moves it into the vector
    v.push_back(Node(1, "Alice"));
    
    // Constructs the Node directly in the vector's memory
    v.emplace_back(2, "Bob");
    return 0;
}
```

::: keypoint
Use `emplace` or `emplace_back` when inserting complex objects (like custom structs or `std::string`) to avoid unnecessary copies or moves. For primitive types like `int`, the performance difference is negligible.
:::

### `std::greater<>`, `std::less<>`, and Transparent Comparators
The standard library provides functor objects like `std::less<T>` and `std::greater<T>` in `<functional>`. By default, containers like `std::priority_queue` use `std::less<T>`, yielding a max-heap. To create a min-heap, use `std::greater<T>`.

Since C++14, these comparators can be "transparent" by omitting the template type: `std::less<>`. This allows heterogeneous comparisons (e.g., comparing a `std::string` to a `const char*` without constructing a temporary `std::string`).

```cpp
#include <set>
#include <string>
#include <functional>

int main() {
    // Transparent comparator allows lookup with string literals
    std::set<std::string, std::less<>> s = {"apple", "banana"};
    
    // No temporary std::string is constructed here
    auto it = s.find("apple"); 
    return 0;
}
```

### Randomness: `mt19937` and `shuffle`
The legacy `rand()` function is predictably flawed and produces low-quality randomness. C++11 introduced `<random>`, which provides the Mersenne Twister engine. Use `std::mt19937` for 32-bit integers and `std::mt19937_64` for 64-bit integers.

Randomness is critical for avoiding worst-case behavior in randomized algorithms (like QuickSort) or for generating robust hashes to defeat adversarial test cases.

```cpp
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

int main() {
    // Seed the random number generator using high-resolution time
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    
    // Generate a random integer in [10, 100]
    std::uniform_int_distribution<int> dist(10, 100);
    int random_val = dist(rng);
    
    // Shuffle a vector securely
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::shuffle(v.begin(), v.end(), rng);
    
    return 0;
}
```

### `assert`, Printing `__int128`, and `std::tie`
**Assertions:** Use `assert(condition)` from `<cassert>` to catch logic errors during development. If the condition is false, the program terminates immediately.

**`__int128`:** The compiler extension `__int128` provides 128-bit integers, which is useful for preventing overflow during intermediate multiplications of 64-bit integers. However, it lacks standard I/O overloads, requiring custom print functions.

**`std::tie`:** Useful for unpacking `std::pair` or `std::tuple` before C++17 structured bindings, and for establishing lexicographical comparisons across multiple variables.

```cpp
#include <iostream>
#include <tuple>
#include <cassert>

// Custom print for __int128
void print128(__int128 n) {
    if (n < 0) { std::cout << '-'; n = -n; }
    if (n > 9) print128(n / 10);
    std::cout << (int)(n % 10);
}

int main() {
    int a = 5, b = 10;
    assert(a < b); // Validates assumption
    
    int x = 1, y = 2, z = 3;
    int u = 1, v = 3, w = 1;
    
    // Lexicographical comparison using std::tie
    if (std::tie(x, y, z) < std::tie(u, v, w)) {
        std::cout << "First tuple is smaller\n";
    }
    
    return 0;
}
```

## The Gotchas That Cause Real Bugs

::: trap
**`map`/`set` `operator[]` inserts a default silently.**
Accessing an absent key via `m[key]` in a `std::map` or `std::unordered_map` silently inserts a default-constructed value. This bloats the map and can turn an $O(1)$ check into an accidental modification. Use `.count(key)`, `.find(key)`, or `.at(key)` for read-only checks.
```cpp
#include <map>
#include <iostream>

int main() {
    std::map<int, int> m;
    if (m[5] == 0) { } // TRAP: 5 is now in the map with value 0
    if (m.count(6)) { } // CORRECT: Checks existence without insertion
    return 0;
}
```
:::

::: trap
**`multiset.erase(val)` deletes ALL equal elements.**
Calling `erase(val)` on a `std::multiset` removes every instance of `val`. If the goal is to remove only a single occurrence, pass an iterator instead.
```cpp
#include <set>

int main() {
    std::multiset<int> ms = {1, 2, 2, 2, 3};
    ms.erase(2); // TRAP: ms is now {1, 3}
    
    std::multiset<int> ms2 = {1, 2, 2, 2, 3};
    ms2.erase(ms2.find(2)); // CORRECT: ms2 is now {1, 2, 2, 3}
    return 0;
}
```
:::

::: trap
**A comparator must be a strict weak ordering.**
A custom sorting comparator must return `false` when comparing two equal elements. Using `<=` instead of `<` violates the strict weak ordering requirement, resulting in undefined behavior (often a segmentation fault or an infinite loop).
```cpp
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5};
    // TRAP: Using <= causes undefined behavior
    // std::sort(v.begin(), v.end(), [](int a, int b) { return a <= b; });
    
    // CORRECT: Use < for strict weak ordering
    std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });
    return 0;
}
```
:::

::: trap
**Integer overflow in midpoint calculation and bit shifts.**
Writing `mid = (l + r) / 2` overflows if `l + r` exceeds the maximum value of the integer type. Writing `1 << k` overflows if `k \ge 31` because integer literals are 32-bit `int` by default.
```cpp
int main() {
    int l = 2000000000, r = 2000000000;
    // int mid = (l + r) / 2; // TRAP: l + r overflows
    int mid = l + (r - l) / 2; // CORRECT: prevents overflow
    
    int k = 40;
    // long long val = 1 << k; // TRAP: 1 is a 32-bit int, shifts past 31 overflow
    long long val = 1LL << k; // CORRECT: 1LL is a 64-bit integer
    return 0;
}
```
:::

::: trap
**`unordered_map` adversarial TLE.**
`std::unordered_map` uses a deterministic polynomial hash function. Adverserals test cases can exploit this to cause massive collisions, degrading performance from $O(1)$ to $O(n)$ per operation, leading to Time Limit Exceeded (TLE). Fix this by using a custom hash with a randomized seed, or simply fall back to `std::map` ($O(\log n)$).
```cpp
#include <chrono>
#include <unordered_map>

// Custom hash to prevent adversarial TLE
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    std::unordered_map<long long, int, custom_hash> safe_map;
    return 0;
}
```
:::

::: trap
**`std::endl` flushes the output stream.**
`std::endl` inserts a newline character and then flushes the buffer. Flushing is a slow I/O operation. In problems with massive output, flushing on every line guarantees a TLE. Always use `'\n'` instead.
```cpp
#include <iostream>

int main() {
    // TRAP: flushes buffer 10^5 times -> TLE
    // for (int i = 0; i < 100000; ++i) std::cout << i << std::endl;
    
    // CORRECT: fast I/O
    for (int i = 0; i < 100000; ++i) std::cout << i << '\n';
    return 0;
}
```
:::

::: trap
**`vector<bool>` is a bit-proxy, not a real `bool`.**
To save space, `std::vector<bool>` packs boolean values into bits. As a result, its elements are not standard `bool` types, and you cannot take a reference or a pointer to them.
```cpp
#include <vector>

int main() {
    std::vector<bool> v(10, false);
    // bool& ref = v[0]; // TRAP: Compilation error
    auto proxy = v[0]; // proxy is std::vector<bool>::reference
    return 0;
}
```
If actual references are required, use `std::vector<char>` or `std::vector<int>` instead.
:::

::: trap
**Dangling references after vector reallocation.**
Adding elements to a `std::vector` may exceed its capacity, causing it to allocate a new memory block and move its elements. Any references or pointers to elements inside the vector become immediately invalidated (dangling).
```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3};
    int& ref = v[0];
    v.push_back(4); // May reallocate
    // std::cout << ref << '\n'; // TRAP: ref might now be dangling (UB)
    return 0;
}
```
:::

::: trap
**Iterator invalidation during loops.**
Erasing an element from a container invalidates iterators pointing to that element. In a `std::vector`, it invalidates all iterators after the erased element as well. When erasing inside a loop, the iterator must be explicitly updated using the return value of `erase()`.
```cpp
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    for (auto it = v.begin(); it != v.end(); ) {
        if (*it % 2 == 0) {
            // it = v.erase(it); // CORRECT: erase returns the next valid iterator
            it = v.erase(it);
        } else {
            ++it;
        }
    }
    return 0;
}
```
:::

::: trap
**Mixing `cin >>` and `getline`.**
Formatted input (`cin >> x`) leaves the trailing newline character `\n` in the input stream. A subsequent `std::getline` reads until the next newline, which means it immediately consumes the leftover newline and reads an empty string.
```cpp
#include <iostream>
#include <string>

int main() {
    int n;
    std::string s;
    // cin >> n;
    // getline(cin, s); // TRAP: reads empty string immediately
    
    // CORRECT: Consume the trailing whitespace/newline first
    // cin >> n >> std::ws;
    // getline(cin, s);
    return 0;
}
```
:::

## The Consolidated CP Toolkit

### Competitive Programming Template
A standardized template minimizes boilerplate during contests. It typically includes fast I/O setup and macros for common operations.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Common typedefs
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

// Macros for brevity
#define all(x) (x).begin(), (x).end()
#define pb push_back

void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (int& x : a) cin >> x;
    
    sort(all(a)); // Uses the all() macro
}

int main() {
    // Fast I/O: disables C/C++ I/O synchronization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

::: keypoint
Use macros like `all(x)` judiciously. While they save keystrokes in timed competitions, excessive macros destroy readability and make debugging harder. Fast I/O is mandatory for problems with over $10^5$ input/output operations.
:::

### Fast Matrix and Adjacency List Reading
Graphs and grids form the basis of many problems. Sizing the containers correctly ahead of time is faster than relying on dynamic resizing (`push_back`).

```cpp
#include <iostream>
#include <vector>

using namespace std;

void read_graph_and_matrix() {
    int n, m;
    cin >> n >> m;
    
    // Matrix reading (pre-allocated)
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }
    
    // Adjacency list reading
    int nodes, edges;
    cin >> nodes >> edges;
    vector<vector<int>> adj(nodes + 1); // 1-indexed
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Remove for directed graph
    }
}
```

### The $10^8$ Operations Rule
A modern CPU performs roughly $10^8$ basic operations per second. This forms a reliable mental model for deducing the required algorithm complexity from the problem constraints.
- If $N \le 10$, $O(N!)$ or $O(2^N)$ is acceptable (backtracking).
- If $N \le 20$, $O(2^N)$ is acceptable.
- If $N \le 10^4$, $O(N^2)$ is acceptable.
- If $N \le 10^5$, $O(N \log N)$ or $O(N)$ is required.
- If $N \le 10^9$, $O(\log N)$ or $O(1)$ is required.

(For a complete treatment of deducing complexity, refer to the Complexity Analysis section).

## Gotchas at a Glance

| Symptom | Cause | Fix |
| :--- | :--- | :--- |
| `std::map` size balloons unexpectedly | `operator[]` inserts default values on read | Use `map.count(key)` or `map.at(key)` |
| `multiset` deletes multiple occurrences | `ms.erase(val)` removes all copies | Use `ms.erase(ms.find(val))` |
| Segmentation fault / UB during `std::sort` | Comparator uses `<=` instead of `<` | Enforce strict weak ordering with `<` |
| Variable overflow causing negative logic | `(l + r) / 2` or `1 << 40` overflows 32-bit `int` | Use `l + (r - l) / 2` and `1LL << k` |
| TLE on `std::unordered_map` | Hash collisions from adversarial inputs | Use custom hash with `mt19937` or use `std::map` |
| TLE on massive string output | `std::endl` forces a stream flush | Use `'\n'` |
| Compilation error taking `vector<bool>` reference | `vector<bool>` returns proxy objects, not `bool&` | Pass by value, or use `vector<char>` |
| Unexpected garbage values from vector ref | Vector reallocated memory, dangling the reference | Avoid caching references, access via `v[i]` |
| Loop skips elements or crashes after `erase` | Iterator invalidation inside a loop | Use `it = c.erase(it)` |
| String is inexplicably empty | `getline` consumed the `\n` left by `cin >>` | Use `cin >> ws` before `getline` |
