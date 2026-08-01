# The Competitive-Programming and DSA Toolkit

::: heavy
Dense catalogue — this is the niche C++ that competitive programming and advanced DSA lean on every contest. Containers and algorithms basics live in Part V; here the focus is the power tools, their complexities, and the traps that silently WA or TLE a solution.
:::

Part V already covers vectors, maps, sets, and the core of `<algorithm>`. This section gathers the **competitive-programming toolkit**: the idioms, builtins, and libraries that turn correct solutions into *fast* ones, and that make advanced DSA (order statistics, bitmask DP, coordinate compression) practical in C++.

## Fast I/O (recap)

On large inputs ($10^5$–$10^7$ tokens), default C++ streams are often the bottleneck. The usual contest boilerplate disables C syncing and unties `cin` from `cout`. The mechanism and the buffering story are in s54; the one-liner you paste at the top of `main` is:

```cpp
#include <bits/stdc++.h>  // GCC/Clang contest header; or include what you use
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cout << n << '\n';  // never endl in a hot loop
}
```

::: trap
`std::endl` flushes the stream. In a loop of $10^6$ lines that is a flood of syscalls. Prefer `'\n'`; flush only when you truly need interactive I/O.
:::

## Integer discipline

DSA arithmetic overflows silently in C++. A classic failure mode is writing `int ans = n * n` when $n$ is $10^5$: the product $10^{10}$ does not fit in a 32-bit `int`, wraps around (undefined behaviour for signed overflow), and the rest of the solution is garbage.

### Prefer `long long` for products and sums

On typical contest platforms, `int` is 32-bit and **`long long`** is 64-bit. Reach for `long long` whenever you multiply two values that may each exceed about $2^{15}$, or when summing an array whose total may exceed $2^{31}-1$.

```cpp
#include <climits>
#include <vector>

long long sum = 0;
for (int x : a) sum += x;          // init and accumulator are long long

long long n = a.size();
long long pairs = n * (n - 1) / 2; // cast/widen before multiply

long long prod = 1LL * a[i] * a[j]; // promote early
```

Useful limits from `<climits>` / `<limits>`:

| Symbol | Typical value |
| :--- | :--- |
| `INT_MAX` | $2^{31}-1 = 2147483647$ |
| `INT_MIN` | $-2^{31}$ |
| `LLONG_MAX` | $2^{63}-1$ |
| `LLONG_MIN` | $-2^{63}$ |

::: trap
Signed overflow is **undefined behaviour**. Do not "rely on wraparound" for `int`. Compute in a wider type (`long long`, or `__int128` for products of two 64-bit values), then cast or take modulo.
:::

### When `unsigned` bites

Unsigned wraparound *is* defined (modulo $2^w$), but mixing signed and unsigned in comparisons and loops is a minefield: `i < v.size() - 1` with an empty vector underflows `size_t`, and `int` vs `size_t` comparisons promote incorrectly. In CP, prefer signed `int` / `long long` indices unless you have a deliberate bit-mask reason for unsigned.

### `__int128` for big products

GCC/Clang provide **`__int128`** (not in the ISO standard, but ubiquitous on contest judges). Use it when multiplying two `long long` values that may exceed $2^{63}-1$, then print carefully:

```cpp
__int128 mul = (__int128)a * b;  // a, b are long long

// printing helper (no iostream overload for __int128)
void print_int128(__int128 x) {
    if (x < 0) { putchar('-'); x = -x; }
    if (x > 9) print_int128(x / 10);
    putchar(char('0' + int(x % 10)));
}
```

### Modular arithmetic pattern

Under a prime **`MOD`** (commonly $10^9+7$), every intermediate result must stay in $[0, MOD)$. Subtraction and negative intermediates need normalisation:

```cpp
const long long MOD = 1'000'000'007;

long long add(long long a, long long b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

long long sub(long long a, long long b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

long long mul(long long a, long long b) {
    return (__int128)a * b % MOD;  // or (a % MOD) * (b % MOD) % MOD if both fit
}

// Why (a % m + m) % m ?
// C++11 onward, a % m for negative a has the sign of a (implementation-defined
// before C++11). Adding m then reducing maps negatives into [0, m).
long long norm(long long a) {
    return (a % MOD + MOD) % MOD;
}
```

::: keypoint
Always widen *before* the multiply that might overflow, then reduce: `((a % MOD) * (b % MOD)) % MOD` is safe only if that product still fits in the type you multiply in. Prefer `__int128` or a dedicated `mul` helper for 64-bit residues.
:::

::: interview
Classic WA: `int` sum of an array of size $n \le 10^5$ with values up to $10^9$, or `n * n` for $n = 10^5$. Interviewers and contest authors both expect you to name the overflow and fix it with `long long` (or modular reduction).
:::

## Bit manipulation

Bitwise operators treat an integer as a bag of independent flags. In CP they encode subsets, visited masks, and parity tricks far more cheaply than a `vector<bool>`.

### Operators and masks (recap)

| Op | Meaning |
| :--- | :--- |
| `&` `|` `^` `~` | and, or, xor, not |
| `<<` `>>` | shift left / right |
| `1 << k` | mask with only bit $k$ set (careful: `1` is `int`) |

Prefer `1LL << k` when $k$ may reach 31 or more on a signed 32-bit `int`.

```cpp
int x = 0b1101;  // 13

bool bit_on = (x >> k) & 1;   // test bit k
x |=  (1 << k);               // set
x &= ~(1 << k);               // clear
x ^=  (1 << k);               // toggle

int low = x & -x;             // lowest set bit (two's complement)
bool pow2 = x && !(x & (x - 1)); // power of two (and x != 0)
```

### Iterate all submasks of a mask

Given a bitmask `m`, every `s` with `s ⊆ m` (as bit sets) can be enumerated in $O(3^{n/2})$-style loops for SOS DP, or simply:

```cpp
// All non-empty submasks of m, then s == 0
for (int s = m; s; s = (s - 1) & m) {
    // use s
}
// Include empty submask separately if needed: s = 0
```

![Enumerating every submask of a bitmask with the `s = (s-1) & m` walk.](assets/s55_submask.png)

**Bitmask DP** intuition: if the state space is "a subset of $n$ items" with $n \le 20$, store `dp[1 << n]` (or `dp[mask][v]`). Transition by trying each bit (item) you can add, or by iterating submasks. Complexity is typically $O(2^n \cdot n)$ or $O(3^n)$ for subset convolution / SOS-style passes — feasible only for small $n$.

### GCC builtins

These are compiler intrinsics (GCC/Clang); they compile to single CPU instructions (`popcnt`, `bsr`/`lzcnt`, `bsf`/`tzcnt`):

| Builtin | Meaning |
| :--- | :--- |
| `__builtin_popcount(x)` / `popcountll` | number of set bits |
| `__builtin_clz(x)` / `clzll` | count leading zeros |
| `__builtin_ctz(x)` / `ctzll` | count trailing zeros |
| `__builtin_parity(x)` / `parityll` | set-bit count mod 2 |
| `__lg(x)` | floor($\log_2 x$) for `x > 0` (libstdc++ / GCC) |

```cpp
unsigned x = 0b1011000;
int bits = __builtin_popcount(x);       // 3
int trail = __builtin_ctz(x);           // 3  (x != 0!)
int lead  = __builtin_clz(x);           // depends on width of unsigned
int msb   = 31 - __builtin_clz(x);      // index of highest set bit
int lg    = __lg(x);                    // same idea for positive x
```

::: trap
`__builtin_clz(0)`, `__builtin_ctz(0)`, and `__lg(0)` are **undefined behaviour**. Always guard with `x != 0` (or use a wider known-nonzero expression).
:::

::: interview
"How do you count set bits?" — mention `__builtin_popcount` / `popcountll`, and Kernighan's loop `while (x) { x &= x - 1; ++c; }`. "How do you find the lowest set bit?" — `x & -x`.
:::

## `std::bitset` in full

**`std::bitset<N>`** (`<bitset>`) is a fixed-size pack of $N$ bits, stored densely and SIMD-friendly for shifts and bitwise ops. Prefer it over `vector<bool>` when $N$ is a compile-time constant and you need fast bitset algebra (sieve segments, reachability, subset DP with OR-convolution).

```cpp
#include <bitset>
#include <string>
#include <iostream>

int main() {
    std::bitset<8> a;              // all zeros
    std::bitset<8> b(42);          // from unsigned long
    std::bitset<8> c(std::string("1101")); // low bits on the right: ...1101

    a.set(3);                      // set bit 3
    a.reset(3);                    // clear bit 3
    a.flip(3);                     // toggle
    a.set();                       // all ones
    a.reset();                     // all zeros

    bool on = a.test(3);           // true if bit 3 set (throws if out of range)
    bool any = a.any(), none = a.none(), all = a.all();
    std::size_t ones = a.count();

    a <<= 2;  a >>= 1;
    auto d = a & b;  auto e = a | b;  auto f = a ^ b;  auto g = ~a;

    unsigned long ul = a.to_ulong();       // throws std::overflow_error if too wide
    // unsigned long long ull = a.to_ullong(); // C++11
    std::string s = a.to_string();

    // libstdc++ extensions: walk set bits (GCC)
    std::bitset<128> bs;
    bs.set(5); bs.set(40);
    for (std::size_t i = bs._Find_first(); i < bs.size(); i = bs._Find_next(i)) {
        // i is a set bit index
    }
}
```

**Speed vs `vector<bool>`:** `vector<bool>` is bit-packed but has proxy-reference weirdness and no bulk `&`/`|`/`<<` between two vectors. `bitset` gives word-parallel ops; for $N \approx 10^4$–$10^5$ compile-time sizes it is often dramatically faster for sieve / Floyd–Warshall-on-bits / subset DP.

::: keypoint
`bitset` size is a template argument — fixed at compile time. For runtime-sized bitsets use `vector<uint64_t>` manually, or Boost `dynamic_bitset` (rarely available on judges).
:::

## Permutations and partial ordering

These live in `<algorithm>` and are CP staples for "enumerate orders", "median", and "top $k$".

### `next_permutation` / `prev_permutation`

Transforms the range into the next (previous) lexicographical permutation. Returns `false` when wrapping past the last (first). **Sort ascending first** to enumerate all permutations:

```cpp
#include <algorithm>
#include <vector>

std::vector<int> a = {1, 2, 3};
std::sort(a.begin(), a.end());
do {
    // process current permutation of a
} while (std::next_permutation(a.begin(), a.end()));
// O(n · n!) total for distinct elements
```

### `nth_element` — $O(n)$ selection

Rearranges so that the iterator `nth` points to the element that *would* be there after a full sort. Elements before are $\le$ it, after are $\ge$ it (order within sides unspecified). Average / expected linear time — use for median or "k-th smallest" without fully sorting.

```cpp
std::vector<int> v = {9, 1, 5, 3, 7};
std::nth_element(v.begin(), v.begin() + 2, v.end());
// v[2] is the median (0-based); left half ≤ median ≤ right half
```

### `partial_sort`, `is_sorted`, `minmax_element`, `clamp`

```cpp
#include <algorithm>

std::partial_sort(v.begin(), v.begin() + k, v.end()); // smallest k sorted at front
bool ok = std::is_sorted(v.begin(), v.end());

auto [lo, hi] = std::minmax_element(v.begin(), v.end()); // C++11 pair; C++17 structured bind

int x = std::clamp(score, 0, 100); // C++17: x in [0, 100]
```

| Tool | Complexity (typical) | Reach for when |
| :--- | :--- | :--- |
| `sort` | $O(n \log n)$ | need full order |
| `partial_sort` | $O(n \log k)$ | need the smallest $k$ *sorted* |
| `nth_element` | $O(n)$ | need only the $k$-th / partition around it |
| `next_permutation` | $O(n)$ per step | enumerate permutations |

## `<numeric>` for CP

```cpp
#include <numeric>
#include <vector>

std::vector<int> a = {1, 2, 3, 4};

// TRAP: init type decides the accumulator type
long long sum = std::accumulate(a.begin(), a.end(), 0LL); // not 0

std::vector<int> idx(n);
std::iota(idx.begin(), idx.end(), 0); // 0,1,2,...,n-1 — great for argsort

std::vector<long long> pref(n);
std::partial_sum(a.begin(), a.end(), pref.begin(),
                 [](long long x, int y) { return x + y; }); // prefix sums

std::vector<int> diff(n);
std::adjacent_difference(a.begin(), a.end(), diff.begin());
// diff[0] == a[0]; diff[i] == a[i]-a[i-1] for i > 0

long long dot = std::inner_product(a.begin(), a.end(), b.begin(), 0LL);
```

**GCD / LCM:** C++17 adds `std::gcd` / `std::lcm` in `<numeric>`. Older code and many templates still use `__gcd` from libstdc++ (`<algorithm>` historically):

```cpp
#include <numeric>
long long g = std::gcd(a, b);           // C++17
long long l = std::lcm(a, b);           // watch overflow: a / gcd * b
// long long g2 = __gcd(a, b);          // GCC extension
```

::: trap
`std::accumulate(v.begin(), v.end(), 0)` sums in `int` even if `v` holds large values. Always pass `0LL` (or a `long long` zero) when the sum may overflow 32 bits.
:::

## Ordered map/set idioms and coordinate compression

### Binary search on a sorted `vector` (the CP workhorse)

For static data, a sorted `vector` plus `lower_bound` / `upper_bound` is usually faster and leaner than `std::set`:

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {1, 3, 3, 7, 9}; // must be sorted
auto lb = std::lower_bound(v.begin(), v.end(), 3); // first ≥ 3
auto ub = std::upper_bound(v.begin(), v.end(), 3); // first > 3
auto [L, R] = std::equal_range(v.begin(), v.end(), 3); // [lb, ub)

bool found = lb != v.end() && *lb == 3;
int idx = int(lb - v.begin()); // insertion point / rank among unique keys
```

### Member vs free-function on `set` / `map`

`std::set` and `std::map` provide **member** `lower_bound` / `upper_bound` / `equal_range` that use the tree and run in $O(\log n)$. The free `std::lower_bound` on `set::iterator` is only bidirectional — it may degrade to linear. Prefer the members:

```cpp
std::set<int> s = {1, 3, 5, 7};
auto it = s.lower_bound(4); // O(log n) — points to 5
// auto bad = std::lower_bound(s.begin(), s.end(), 4); // avoid on set
```

Custom ordering of keys is the same strict-weak-ordering story as sorting; see s48 for comparator forms and the `<=` trap.

### Coordinate compression

Map large or sparse values into a dense $0 \ldots k-1$ rank space (Fenwick/segment trees, counting sorts):

```cpp
std::vector<int> vals = /* all coordinates that appear */;
std::sort(vals.begin(), vals.end());
vals.erase(std::unique(vals.begin(), vals.end()), vals.end());

auto id = [&](int x) {
    return int(std::lower_bound(vals.begin(), vals.end(), x) - vals.begin());
};
// id(x) in [0, vals.size()) for x that appeared in vals
```

## Policy-based data structures (ordered statistics)

GCC's **`__gnu_pbds`** library exposes a tree that supports **order statistics**: find the $k$-th smallest element and the rank of a key in $O(\log n)$. This is not ISO C++, but it is available on virtually every Codeforces / AtCoder GCC judge.

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag,
                         tree_order_statistics_node_update>;

// ordered_set<int> s;
// s.insert(10); s.insert(20); s.insert(30);
// *s.find_by_order(0);   // 10 — 0-based k-th smallest
//  s.order_of_key(25);   // 2  — count of elements strictly < 25
```

| Method | Meaning | Complexity |
| :--- | :--- | :--- |
| `find_by_order(k)` | iterator to 0-based $k$-th smallest | $O(\log n)$ |
| `order_of_key(x)` | number of elements strictly less than $x` | $O(\log n)$ |

**Multiset via `pair`:** `tree` stores unique keys under `less<T>`. For duplicates, store `pair<T, int>` with a unique id (index) as the second field, and use `less<pair<T,int>>`.

::: trap
PBDS is **GCC-only** (libstdc++). It will not compile under MSVC's STL. Prefer it in contests that guarantee g++; avoid it in portable production code unless you vendor an equivalent.
:::

::: interview
"How do you find the k-th element in a dynamic set in $O(\log n)$?" — balanced BST with subtree sizes (PBDS `find_by_order`), or a Fenwick/segment tree over compressed coordinates. Mention both.
:::

## Custom hashing (defeat anti-hash tests)

libstdc++'s default `std::hash` for integers is effectively identity-like. Adversarial test cases can force **`unordered_map`** / **`unordered_set`** into long collision chains and $O(n^2)$ behaviour (famous Codeforces "anti-hash" hacks).

Fix: a strong 64-bit mix with a **random seed** fixed once per run:

```cpp
#include <chrono>
#include <unordered_map>

struct SplitmixHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// Also works for other integer keys via casting
std::unordered_map<long long, int, SplitmixHash> mp;
std::unordered_set<long long, SplitmixHash> st;
```

For `pair` keys, hash both halves and mix (e.g. `splitmix64(a + FIXED) ^ (splitmix64(b + FIXED + 1) << 1)`).

::: trap
Default `unordered_map` is fine for interviews and most LeetCode tests, but on Codeforces-style adversarial data it can TLE. Either use a custom hash as above, or fall back to `std::map` ($O(n \log n)$ worst-case guaranteed).
:::

## Randomness with `<random>`

Contest solutions need **controlled randomness**: shuffle a permutation so adversarial tests cannot force a worst-case pivot order, break anti-hash attacks with a per-run seed, or sample a random neighbour in a randomised algorithm. C++11's `<random>` is the right toolkit; the old C `rand()` / `srand()` pair is not.

### Why `rand()` is bad

`rand()` from `<cstdlib>` returns an `int` in $[0, RAND\_MAX]$. On many platforms `RAND_MAX` is only $2^{15}-1 = 32767$ — far too small to sample uniformly from a range of size $10^9$, and too coarse for hashing seeds. The underlying LCG (or similar) has short period and poor statistical quality: consecutive values are correlated, and low bits are especially weak. Calling `srand(time(0))` once per second still leaves the stream predictable to an adversary who knows the contest clock.

::: trap
`rand() % n` is **biased** whenever $n$ does not divide $RAND\_MAX+1$ evenly: some residues appear more often than others. Prefer `std::uniform_int_distribution` with a Mersenne Twister engine (below), never `rand() % n`.
:::

### Engines: `std::mt19937` and `std::mt19937_64`

A **random-number engine** produces a stream of unsigned integers. The contest workhorse is **`std::mt19937`** (32-bit Mersenne Twister) or **`std::mt19937_64`** (64-bit). Pair the engine with a **distribution** that maps engine output into the exact range and type you want.

```cpp
#include <chrono>
#include <random>

// 32-bit engine — fine for shuffle / pivots / most CP sampling
std::mt19937 rng(42);  // fixed seed: reproducible local debugging

// 64-bit engine — prefer when you need wide seeds or 64-bit samples
std::mt19937_64 rng64(42);
```

### Seeding: `steady_clock` and `random_device`

A fixed seed (`42`) is perfect for local debugging (same shuffle every run). On the judge you usually want a **non-guessable** seed so an adversary cannot craft a test that defeats your randomised pivot or hash:

```cpp
#include <chrono>
#include <random>

// Common CP idiom — high-resolution clock tick as seed
std::mt19937 rng(
    std::chrono::steady_clock::now().time_since_epoch().count());

// Stronger entropy when available (may be slow or deterministic on some judges)
std::random_device rd;
std::mt19937 rng2(rd());

// Mix both if you like a belt-and-braces seed
std::mt19937 rng3(rd() ^
    (unsigned)std::chrono::steady_clock::now().time_since_epoch().count());
```

::: keypoint
**Seed randomness so it is not hackable.** A fixed seed lets an opponent re-run your binary and craft anti-hash or anti-quicksort tests. Seed from `steady_clock` (and/or `random_device`) once at startup; keep the engine as a global or function-local `static` so every call draws from the same stream.
:::

This is exactly the idea behind `FIXED_RANDOM` in the `SplitmixHash` above: one clock-based constant per process, mixed into every hash. You can also seed the hash from an `mt19937_64`:

```cpp
std::mt19937_64 seeder(
    std::chrono::steady_clock::now().time_since_epoch().count());
static const uint64_t FIXED_RANDOM = seeder();
// then: return splitmix64(x + FIXED_RANDOM);
```

### Distributions: integers and reals

**`std::uniform_int_distribution<T>`** draws uniformly from a closed integer interval $[L, R]$. **`std::uniform_real_distribution<T>`** draws from a half-open real interval $[a, b)$.

```cpp
#include <chrono>
#include <random>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

std::uniform_int_distribution<int> coin(0, 1);
int bit = coin(rng);                    // 0 or 1

std::uniform_int_distribution<int> pick(0, n - 1);
int i = pick(rng);                      // index in [0, n)

std::uniform_int_distribution<long long> big(1LL, 1'000'000'000LL);
long long x = big(rng);

std::uniform_real_distribution<double> unit(0.0, 1.0);
double p = unit(rng);                   // in [0.0, 1.0)
```

Reuse one engine; create distributions as needed (or keep them if the range is fixed). Prefer `long long` distributions when the endpoints themselves are 64-bit.

### Practical CP uses

**1. Shuffle a range** — fair random permutation; beats hand-rolled Fisher–Yates with `rand()`:

```cpp
#include <algorithm>
#include <random>
#include <vector>

std::vector<int> v = {1, 2, 3, 4, 5};
std::shuffle(v.begin(), v.end(), rng);  // C++11; uses rng, not rand()
// Prefer std::shuffle over the deprecated std::random_shuffle
```

**2. Random pivot / random rotation** — defeat anti-quicksort and pathological orderings. Before a handmade partition, swap a random element into the pivot slot; or rotate the array by a random offset so a sorted (or adversarial) input is no longer worst-case:

```cpp
// Random pivot for a [lo, hi] inclusive partition
std::uniform_int_distribution<int> piv(lo, hi);
std::swap(a[lo], a[piv(rng)]);

// Random rotation of a vector (same multiset, different starting point)
std::uniform_int_distribution<int> rot(0, (int)a.size() - 1);
std::rotate(a.begin(), a.begin() + rot(rng), a.end());
```

The same idea appears in randomised quickselect / treaps: draw priorities or pivots from `rng` so expected complexity holds against adversarial input.

**3. Seed a custom hash** — tie-back to `SplitmixHash` earlier in this section. Mixing `FIXED_RANDOM` from the clock (or from `mt19937_64`) into `splitmix64` is what makes per-run bucket layouts unpredictable. Without that seed, a public identity-like `std::hash` is hackable; with it, anti-hash tests lose their bite.

```cpp
// Minimal sketch — same structure as SplitmixHash above
size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
}
```

::: interview
"Why not `rand()`?" — small `RAND_MAX`, poor quality, `rand()%n` bias. Name `mt19937` + `uniform_int_distribution` + `std::shuffle`, and mention seeding hashes / pivots so adversarial tests cannot force $O(n^2)$.
:::

## Handy multi-value and container idioms

### `pair`, `tuple`, `tie`, structured bindings

```cpp
#include <tuple>
#include <utility>

auto p = std::make_pair(1, 2.5);          // pair<int, double>
std::pair<int, int> q = {3, 4};           // CTAD / brace init

std::tuple<int, int, int> t = {1, 2, 3};
auto [x, y, z] = t;                       // C++17 structured bindings

int a, b, c;
std::tie(a, b, c) = t;                    // pre-C++17 unpack
std::tie(a, b) = std::minmax(10, 3);      // a=3, b=10

// Sorting by multiple keys: pair/tuple compare lexicographically
std::vector<std::pair<int, int>> edges;
std::sort(edges.begin(), edges.end());    // by .first, then .second
```

### `array` vs `vector`; 2D grids; `reserve`; `emplace_back`

```cpp
#include <array>
#include <vector>

std::array<int, 4> fixed = {1, 2, 3, 4};  // stack, size in type, no heap

int r = 100, c = 200;
std::vector<std::vector<int>> g(r, std::vector<int>(c, 0)); // r×c zeros

std::vector<int> v;
v.reserve(n);              // avoid geometric realloc in a known-size loop
v.emplace_back(x);         // construct in place (matters for heavy types / pairs)
v.push_back({u, w});       // fine for pair<int,int>; emplace_back(u, w) also works
```

::: keypoint
Use `std::array` (or C arrays) for tiny fixed sizes and compile-time dimensions; `vector` for everything dynamic. Always `reserve` when you know $n$ before a tight `push_back` loop.
:::

## Multidimensional containers

Grids, DP tables, and adjacency tensors show up constantly in DSA. Nested `vector`s are the readable default; a **flat** buffer is often the faster one. Fixed compile-time dimensions belong in `std::array`.

### 2D grids with nested `vector`

The idiomatic $R \times C$ zero-initialised grid:

```cpp
#include <vector>

int R = 100, C = 200;
std::vector<std::vector<int>> grid(R, std::vector<int>(C, 0));
// grid[r][c] — row r, column c
grid[0][0] = 1;
```

Each inner `vector<int>(C, 0)` is an independent row of length $C$. The outer constructor makes $R$ **copies** of that prototype row, so you get $R$ separate allocations (plus the outer vector's buffer of row objects).

### Flat `vector` — contiguity and cache

A nested grid stores $R$ separate heap buffers. Walking column-by-column (or even row-by-row across many small rows) jumps between allocations and thrashes the cache. A **flat** `vector<int>` of size $R \cdot C` keeps every cell in one contiguous block:

```cpp
std::vector<int> g(R * C, 0);
auto at = [&](int r, int c) -> int& { return g[r * C + c]; };
// or simply: g[r * C + c]

at(2, 5) = 42;
int v = g[2 * C + 5];
```

Indexing is $O(1)$ either way; the win is **spatial locality** — sequential scans, BFS distance arrays, and DP recurrences that touch neighbours stay in cache. For large grids ($10^6$–$10^7$ cells) the flat form is routinely faster and uses slightly less overhead (one allocation, no per-row capacity words).

![Two ways to store a grid: scattered nested vectors versus one contiguous flat buffer.](assets/s55_2d.png)

::: keypoint
Prefer `vector<int>(R * C)` with `g[r * C + c]` in hot inner loops; keep `vector<vector<int>>` when clarity matters more than a few percent, or when rows genuinely have different lengths (ragged grids).
:::

### `std::array` for fixed dimensions

When $R$ and $C$ are compile-time constants (small DP, board games, convolution kernels), **`std::array`** lives on the stack (or inside another object) with no heap traffic:

```cpp
#include <array>

constexpr int N = 8, M = 8;
std::array<std::array<int, M>, N> board{};  // 8×8 zeros

// Fully flat fixed buffer
std::array<int, N * M> flat{};
flat[r * M + c] = 1;
```

Same rule as elsewhere: `array` for fixed sizes known at compile time; `vector` when dimensions come from input.

### 3D nesting

Bitmask DP or volumetric grids need three indices. Nesting works; flat with strides is again the performance choice:

```cpp
int X = 50, Y = 50, Z = 50;

// Nested — clear, three allocations deep
std::vector<std::vector<std::vector<int>>> cub(
    X, std::vector<std::vector<int>>(Y, std::vector<int>(Z, 0)));
cub[x][y][z] = 1;

// Flat — one buffer, manual strides
std::vector<int> flat3(X * Y * Z, 0);
auto id3 = [&](int x, int y, int z) { return (x * Y + y) * Z + z; };
flat3[id3(1, 2, 3)] = 1;
```

For DP shaped `[n+1][1<<k][k]` with small compile-time `k`, a mix is common: outer `vector` over $n$, inner `array` or flat block over the mask dimension.

### Trap: sharing one row when you meant copies

There are two related mistakes.

**1. Building rows that alias one shared vector** (classic with pointers / references, or careless fill loops):

```cpp
std::vector<int> row(C, 0);
std::vector<std::vector<int>> bad(R, row); // OK: copies row R times

// DANGER — if you instead store pointers/references to one row:
std::vector<std::vector<int>*> worse(R, &row); // every entry aliases row
row[0] = 99;  // "all rows" appear to change
```

The constructor `vector<vector<int>>(R, row)` **does** copy `row` $R$ times — that form is fine. The trap is storing addresses of one buffer, or resizing/filling in a way that reuses the same inner vector object.

**2. Accidental copies of huge grids** — passing `vector<vector<int>>` by value duplicates every row:

```cpp
void flood(std::vector<std::vector<int>> g);      // copies entire grid
void flood_ref(std::vector<std::vector<int>>& g); // in-place
void flood_view(const std::vector<std::vector<int>>& g); // read-only
```

Also watch assignment: `auto h = g;` deep-copies all cells. Prefer `reserve` + `assign`, or flat buffers, when you repeatedly allocate scratch grids in a tight loop.

::: trap
`vector<vector<int>>(R, row)` copies `row` — that part is safe. The real sharing bugs are pointer/reference aliases to one row, and silent **by-value** copies of whole grids into functions. Pass large grids by reference (or use a flat `vector<int>`).
:::

::: interview
"Nested `vector` vs flat array for a grid?" — nested is clear; flat `g[r*C+c]` is contiguous and cache-friendlier. Mention fixed `std::array` when dims are compile-time, and never pass huge grids by value.
:::

## When to reach for what

| Need | Tool |
| :--- | :--- |
| Fast token I/O | `ios::sync_with_stdio(false); cin.tie(nullptr);` + `'\n'` (see s54) |
| Safe products / sums | `long long`, `__int128`, modular helpers |
| Subsets of $n \le 20$ | bitmasks + `__builtin_popcount`; `bitset` for dense Boolean algebra |
| Count / scan bits | `__builtin_popcount(ll)`, `ctz` / `clz` (guard zero!) |
| All permutations | `sort` + `do … while (next_permutation)` |
| k-th / median, unsorted | `nth_element` |
| Top $k$ sorted | `partial_sort` or heap |
| Prefix sums / argsort idx | `partial_sum`, `iota` |
| Static binary search | sorted `vector` + `lower_bound` / `upper_bound` |
| Dynamic order statistics | PBDS `ordered_set` (`find_by_order` / `order_of_key`) |
| Compress coordinates | `sort` + `unique` + `lower_bound` |
| Hash map under attack | `unordered_map` + `SplitmixHash`, or `map` |
| Random shuffle / pivot / sample | `mt19937` + `uniform_int_distribution`; `std::shuffle` — never `rand() % n` |
| Unpredictable hash / RNG seed | `steady_clock` and/or `random_device` once at startup |
| Multi-key sort / unpack | `pair`/`tuple`, structured bindings / `tie` |
| Fixed small table | `array` or `bitset<N>`; else `vector` + `reserve` |
| $R \times C$ grid (hot loop) | flat `vector<int>(R*C)` with `g[r*C+c]`; nested `vector` for clarity / ragged rows |
| 3D / tensor DP | nested `vector`s or flat with strides `(x*Y+y)*Z+z` |

::: interview
A strong CP/DSA C++ interview loop: overflow discipline (`long long` / modular), bitmask + builtins, `lower_bound` on a sorted vector vs `set`, `nth_element` vs `sort`, why `unordered_map` can degrade without a custom hash, why `rand()` is replaced by `mt19937` + distributions, and nested vs flat grids. Name complexities and one concrete snippet for each.
:::
