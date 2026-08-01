# C++ Essentials for DSA

This section covers the practical subset of C++ necessary for competitive programming and data structures and algorithms. It strips away the language's full object-oriented capabilities and design patterns to focus exclusively on fast execution, memory safety, and concise syntax. For deep object-oriented design or language theory, consult a dedicated software engineering reference.

## Fast I/O

In competitive programming, the default input/output operations in C++ can be a bottleneck, causing Time Limit Exceeded (TLE) errors on problems with massive test data.

### Synchronized I/O and `cin.tie`

By default, C++ synchronizes its standard streams (`cin`, `cout`) with C's standard streams (`stdin`, `stdout`) so they can be mixed safely. It also ties `cin` to `cout` so that any read from `cin` automatically flushes `cout` first.

```cpp
#include <iostream>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}
```

Disabling synchronization removes the overhead of keeping C and C++ streams in sync, drastically speeding up I/O. Untying `cin` from `cout` removes the automatic flushing.

::: trap
Do not mix `scanf`/`printf` with `cin`/`cout` after calling `ios_base::sync_with_stdio(false)`. The streams will no longer be synchronized, leading to scrambled output.
:::

### The `endl` Flush Trap

`std::endl` inserts a newline character and then forces a flush of the output buffer.

::: trap
Using `std::endl` in a loop over thousands of items will cause a Time Limit Exceeded (TLE). Always use `'\n'` instead, which simply inserts a newline character and allows the system to flush the buffer optimally.
:::

```cpp
#include <iostream>
#include <vector>

void print_fast(const std::vector<int>& arr) {
    for (int x : arr) {
        std::cout << x << '\n'; // Fast
    }
}
```

### Reading Patterns

Problems typically present input as either a stream until the end-of-file (EOF), or as a count $n$ followed by $n$ items.

```cpp
#include <iostream>
#include <vector>

void read_patterns() {
    int x;
    // Pattern 1: Read until EOF
    while (std::cin >> x) {
        // Process x
    }

    // Pattern 2: Read n, then n elements
    int n;
    if (std::cin >> n) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
    }
}
```

When an entire line needs to be captured, including spaces, use `std::getline`.

::: trap
**The Leftover Newline Trap**: `std::cin >> x` leaves the trailing newline character in the input buffer. An immediate call to `std::getline(std::cin, str)` will consume that newline and read an empty string. You must consume the leftover newline first using `std::cin.ignore()` or a dummy `getline`.
:::

```cpp
#include <iostream>
#include <string>

void read_line_trap() {
    int n;
    std::cin >> n;
    
    std::string s;
    // Consume the leftover newline from 'cin >> n'
    std::cin.ignore(256, '\n'); 
    
    std::getline(std::cin, s);
}
```

### Stringstreams

`std::stringstream` (from `<sstream>`) treats a string like an input/output stream. It is the cleanest way to tokenize a space-separated string or convert between integers and strings.

```cpp
#include <string>
#include <sstream>
#include <vector>

void stringstream_demo() {
    std::string line = "10 20 30";
    std::stringstream ss(line);
    
    int val;
    std::vector<int> tokens;
    while (ss >> val) {
        tokens.push_back(val);
    }
    // tokens now holds {10, 20, 30}
}
```

### `printf`, `scanf`, and Floating Point Precision

C-style `scanf` and `printf` (from `<cstdio>`) are inherently fast and do not require `sync_with_stdio(false)`. When outputting floating-point numbers with C++ streams, use `<iomanip>` to avoid scientific notation and set precise decimal places.

```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>

void precision_demo() {
    double pi = 3.1415926535;
    // C++ way:
    std::cout << std::fixed << std::setprecision(5) << pi << '\n'; 
    // C way:
    printf("%.5f\n", pi);
}
```

## Types, Ranges, and Overflow

Choosing the correct integer type prevents silent wrap-around errors that fail hidden test cases.

| Type | Size | Min/Max Range (approximate) | Constant Limits (`<climits>`) |
| :--- | :--- | :--- | :--- |
| `int` | 32-bit | $-2 \times 10^{9}$ to $2 \times 10^{9}$ | `INT_MIN` to `INT_MAX` |
| `unsigned int` | 32-bit | $0$ to $4 \times 10^{9}$ | `0` to `UINT_MAX` |
| `long long` | 64-bit | $-9 \times 10^{18}$ to $9 \times 10^{18}$ | `LLONG_MIN` to `LLONG_MAX` |
| `__int128` | 128-bit | $\approx \pm 10^{38}$ | None (compiler intrinsic) |

`long long` is mandatory when summing $10^{5}$ values that can each be $10^{9}$, or when multiplying two $10^{9}$ integers. `__int128` is a GCC extension useful for intermediate multiplications exceeding 64-bit limits, but it cannot be directly read or printed via `cin`/`cout`.

### Overflow Traps

When mixing 32-bit and 64-bit integers, the evaluation happens at the wider type. However, if the operation is solely between 32-bit integers, the overflow occurs *before* assignment.

::: trap
The `1LL << k` trap: Shifting a 32-bit literal `1 << 40` invokes undefined behavior. Always cast the literal to a 64-bit integer first by using the `LL` suffix: `1LL << 40`.
:::

```cpp
void overflow_demo() {
    int a = 1e9;
    int b = 1e9;
    // OVERFLOW: a + b exceeds INT_MAX before assignment
    long long bad_sum = a + b; 
    // CORRECT: Cast one operand to force 64-bit addition
    long long good_sum = (long long)a + b; 
}
```

::: keypoint
The safe way to compute a midpoint in binary search without integer overflow is `int mid = l + (r - l) / 2;`. Doing `(l + r) / 2` will overflow if $l + r > 2^{31}-1$.
:::

### Floating Point Comparisons

`double` offers 53 bits of precision (about 15-17 decimal digits), while `long double` provides 80-bit or 128-bit precision depending on the platform.

::: trap
Never use `==` to compare two floating-point numbers due to representation inaccuracies. Always compare their absolute difference against a small epsilon.
:::

```cpp
#include <cmath>

bool are_equal(double a, double b) {
    const double EPSILON = 1e-9;
    return std::abs(a - b) < EPSILON;
}
```

### Unsigned Underflow

The `size_t` type (returned by `.size()` on containers) is unsigned. Subtracting from `0` wraps around to the maximum possible value.

::: trap
`for (size_t i = 0; i < arr.size() - 1; ++i)` will loop infinitely (or cause a segfault) if `arr.size()` is $0$, because $0 - 1$ underflows to a massive positive number. Cast to `int` or check `.empty()` first.
:::

## Core Language for DSA

### `auto`, `const`, and Pass-by-Reference

`auto` infers the type at compile time. `const` prevents modification, and `constexpr` evaluates a constant at compile time.

::: keypoint
Never pass containers (like `std::vector` or `std::string`) by value unless you explicitly want a copy. Passing by value takes $O(n)$ time. Always pass by `const&` (read-only) or `&` (mutable) for $O(1)$ overhead.
:::

```cpp
#include <vector>

// O(1) pass, cannot modify
void process(const std::vector<int>& arr) { } 

// O(1) pass, can modify
void modify(std::vector<int>& arr) { } 
```

### Range-based `for` and Structured Bindings

The range-based `for` loop provides a clean syntax for iterating over containers. Structured bindings (C++17) unpack pairs and tuples directly into named variables.

```cpp
#include <vector>
#include <map>
#include <iostream>

void iteration_demo() {
    std::vector<int> nums = {1, 2, 3};
    for (int& x : nums) {
        x *= 2; // modify in place
    }
    for (const int& x : nums) {
        // read-only
    }

    std::map<int, int> freq = {{1, 10}, {2, 20}};
    // C++17 structured bindings
    for (const auto& [key, val] : freq) {
        std::cout << key << ": " << val << '\n';
    }
}
```

### Pairs and Tuples

`std::pair` (from `<utility>`) bundles two elements. `std::tuple` (from `<tuple>`) bundles three or more. Both automatically define lexicographical comparison operations (`<`, `==`), making them natural choices for sorting multidimensional data or representing graph edges.

```cpp
#include <utility>
#include <tuple>

void pair_tuple_demo() {
    std::pair<int, int> p = std::make_pair(1, 2);
    // access via p.first, p.second
    
    std::tuple<int, int, int> t = std::make_tuple(1, 2, 3);
    // access via std::get<0>(t)
    
    // Unpacking with structured bindings
    auto [x, y] = p;
    auto [a, b, c] = t;
}
```

### Lambdas and Custom Comparators

Lambdas are anonymous inline functions. They are the standard way to provide custom logic to sorting algorithms or standard library tools.

- `[&]` captures all local variables by reference.
- `[=]` captures all local variables by value.
- `[this]` captures the enclosing class instance.
- `[x]` captures only `x` by value, `[&x]` by reference.
- `mutable` allows a lambda to modify value-captured variables.
- `-> type` defines a trailing return type (often inferred, but useful for clarity).
- Generic lambdas use `auto` parameters.

```cpp
#include <vector>
#include <algorithm>

void lambda_demo() {
    std::vector<int> arr = {5, 2, 8, 1};
    int limit = 4;
    
    // Sort descending using a generic lambda
    std::sort(arr.begin(), arr.end(), [](auto a, auto b) {
        return a > b;
    });

    // Count elements greater than limit
    int count = std::count_if(arr.begin(), arr.end(), [&](int x) {
        return x > limit;
    });
}
```

To write a recursive lambda, `std::function` is traditionally used to explicitly define the function signature, breaking the circular dependency of type inference. C++23 introduces `auto self`, but in C++17, passing the lambda to itself or using `std::function` is required.

```cpp
#include <functional>

void recursive_lambda() {
    // Using std::function to allow recursion
    std::function<int(int)> fib = [&](int n) -> int {
        if (n <= 1) return n;
        return fib(n - 1) + fib(n - 2);
    };
    
    // Using auto auto-deduction trick (passing lambda to itself)
    auto dfs = [&](auto& self, int node) -> void {
        if (node == 0) return;
        self(self, node - 1);
    };
    dfs(dfs, 5);
}
```

Functors (structs overloading `operator()`) are an older but still relevant pattern, strictly required when a type name is expected rather than an instance (such as the third template parameter of `std::priority_queue`).

```cpp
struct CustomCompare {
    bool operator()(const int& a, const int& b) const {
        return a > b; 
    }
};
// Used as: std::priority_queue<int, std::vector<int>, CustomCompare> pq;
```

### Utility Functions: Swap, Move, Max, Min

- `std::swap(a, b)` swaps two elements in $O(1)$ time for fundamental types and standard containers.
- `std::move(a)` casts an object to an rvalue, transferring its underlying resources rather than copying them.
- `std::tie(a, b) = some_pair` assigns tuple/pair values to existing variables.
- `std::max` and `std::min` handle two values natively. For three or more, use an initializer list. `std::clamp` enforces lower and upper bounds.

```cpp
#include <algorithm>
#include <utility>
#include <tuple>
#include <vector>

void util_demo() {
    int a = 1, b = 2, c = 3;
    std::swap(a, b);
    
    int mx = std::max({a, b, c}); // Requires initializer list {...}
    int bounded = std::clamp(a, 10, 20); // If a < 10 returns 10, if a > 20 returns 20
    
    std::pair<int, int> p = {100, 200};
    std::tie(a, b) = p; // a=100, b=200
    
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = std::move(v1); // v1 is now empty, v2 has the data (O(1))
}
```

### Macros and Typedefs

Competitive programmers often use macros and type aliases to shorten code.

```cpp
#include <vector>
#include <algorithm>

#define all(x) (x).begin(), (x).end()
using ll = long long;

void macro_demo() {
    std::vector<int> arr = {3, 1, 2};
    // Replaces std::sort(arr.begin(), arr.end());
    std::sort(all(arr)); 
}
```

While acceptable in isolated algorithmic contexts, aggressive macro usage (`#define rep(i, a, b) ...`) harms readability, breaks scoping rules, and makes debugging difficult. Use them sparingly.

::: keypoint
**C++ DSA Quick Checklist**
- Add `ios_base::sync_with_stdio(false); cin.tie(nullptr);` to `main()`.
- Never use `std::endl`; always use `'\n'`.
- Pass vectors and strings by `const&` unless a copy is needed.
- Use `long long` when sums or products can exceed $2 \times 10^{9}$.
- Prevent integer overflow in binary search with `l + (r - l) / 2`.
:::
