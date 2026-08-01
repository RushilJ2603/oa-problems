# Vocabulary and Utility Types: pair, tuple, optional, variant, any, string_view

The Standard Library's small general-purpose types — **`std::pair`**, **`std::tuple`**, **`std::optional`**, **`std::variant`**, **`std::any`**, and **`std::string_view`** — appear constantly in DSA, competitive programming, and interviews. They are not containers in the Part V sense; they are vocabulary types: shared names for "two things", "several things", "maybe a thing", "one of these things", "some erased thing", and "a view of characters". Master the API and the traps; the rest of the library assumes you have.

::: heavy
Dense catalogue — each type is small, but the wrong choice (especially `optional` empty dereference, `variant` wrong `get`, and dangling `string_view`) is undefined behaviour or a silent bug. Read each type's construction and access rules before its worked example.
:::

## `std::pair<A, B>` — two values, one name

### What it is and why it exists

A **`std::pair<T1, T2>`** (header `<utility>`) is a simple aggregate-like struct holding two members, **`first`** and **`second`**. It exists so the library (and your code) can name "a key with a value", "two return values", or "an edge $(u,v)$" without inventing a one-off struct every time. Associative containers use it as their element type: `std::map<K,V>::value_type` is `std::pair<const K, V>`.

::: definition
A **`std::pair<T1, T2>`** is a class template with public data members `T1 first` and `T2 second`, plus lexicographic comparison operators so pairs sort and compare naturally.
:::

### Construction and initialisation

```cpp
#include <utility>
#include <string>

// 1. Direct / brace initialisation
std::pair<int, double> p1(1, 2.5);
std::pair<int, double> p2{1, 2.5};
std::pair<int, double> p3 = {1, 2.5};

// 2. make_pair — deduces types (pre-C++17 helper; still useful)
auto p4 = std::make_pair(1, 2.5);           // pair<int, double>
auto p5 = std::make_pair(42, std::string{"hi"});

// 3. C++17 class template argument deduction (CTAD)
std::pair p6{3, 4};                         // pair<int, int>
std::pair p7{1, std::string{"x"}};          // pair<int, string>

// 4. piecewise / converting construction (when members need args)
std::pair<std::string, std::string> p8{"hello", "world"};
```

`std::make_pair` decays arrays and functions to pointers (like many deduction helpers). Prefer brace init / CTAD when you want exact types; use `make_pair` when you want decay and deduction in one call.

### Members and free-function API

| Member / function | Role |
| :--- | :--- |
| `.first`, `.second` | The two stored values (public data members) |
| `operator=`, swap | Assign / swap both members |
| `==`, `!=`, `<`, `<=`, `>`, `>=` | Lexicographic: compare `first`, then `second` if firsts are equal |
| `std::get<0>(p)`, `std::get<1>(p)` | Tuple-protocol access (C++11); also works with structured bindings |
| `std::make_pair(a, b)` | Deduce and construct a pair |

```cpp
#include <utility>
#include <iostream>

std::pair<int, int> edge{3, 7};
std::cout << edge.first << ' ' << edge.second << '\n';  // 3 7

auto [u, v] = edge;   // C++17 structured bindings: u=3, v=7
int a = std::get<0>(edge);
int b = std::get<1>(edge);
```

### Lexicographic comparison — why pairs sort the way they do

Comparison is **lexicographic**: $p < q$ if and only if

$$
p.\mathrm{first} < q.\mathrm{first}
\quad\text{or}\quad
(p.\mathrm{first} = q.\mathrm{first}\ \land\ p.\mathrm{second} < q.\mathrm{second}).
$$

That is exactly dictionary order on a two-letter word. It is why `std::sort` on `vector<pair<int,int>>` sorts by the first field, breaking ties on the second — the default you want for edges by weight, events by time, then id, and so on.

```cpp
#include <algorithm>
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> edges = {{2, 9}, {1, 5}, {1, 3}, {2, 1}};
std::sort(edges.begin(), edges.end());
// Result: {1,3}, {1,5}, {2,1}, {2,9}  — first ascending, then second
```

::: keypoint
Default `pair` / `tuple` ordering is lexicographic. For "sort by weight, then by node id", store `pair{weight, id}` (or the reverse if you want the other primary key) and call `std::sort` with no comparator.
:::

### Realistic uses: map `value_type` and two-field returns

```cpp
#include <map>
#include <string>
#include <utility>
#include <vector>

// Map elements *are* pairs
std::map<std::string, int> freq;
freq.insert(std::pair<const std::string, int>{"cat", 1});
freq.emplace("dog", 2);          // constructs the pair in place
for (const auto& [key, val] : freq) {  // structured bind each pair
    // ...
}

// Lightweight two-field return (better than out-parameters for small types)
std::pair<int, int> minmax_idx(const std::vector<int>& a) {
    int lo = 0, hi = 0;
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i] < a[lo]) lo = i;
        if (a[i] > a[hi]) hi = i;
    }
    return {lo, hi};             // brace-return a pair
}
```

### Cost notes

A `pair` is as cheap as its two members: no heap, no indirection. Copy/move cost is the sum of the members' copy/move costs. Comparison is $O(1)$ member comparisons in the worst case (at most two). Prefer returning `pair` of scalars over inventing a struct *only* when the names `first`/`second` are clear enough; for named fields in a large codebase, a small `struct` is often clearer.

::: interview
"What is `map<K,V>::value_type`?" — `pair<const K, V>`. "Why `const K`?" — so the key cannot be mutated through the iterator and break the tree order. Also expect: sorting `vector<pair>` uses lexicographic order on `.first` then `.second`.
:::

## `std::tuple<...>` — $N$ values, one name

### What it is and why it exists

A **`std::tuple<Ts...>`** (header `<tuple>`) generalises `pair` to an arbitrary number of heterogeneous types. Use it for multi-value returns, multi-key sort keys, and as a type-level "product" of values. A `pair` is roughly a two-element tuple with named members; a tuple of size 2 interoperates with `pair` via converting constructors.

::: definition
A **`std::tuple<T0, T1, …, TN-1>`** stores $N$ elements of possibly different types, accessed by compile-time index (or by type if unique) via `std::get`.
:::

### Construction

```cpp
#include <tuple>
#include <string>

std::tuple<int, double, char> t1{1, 2.5, 'x'};
auto t2 = std::make_tuple(1, 2.5, 'x');     // deduce types
auto t3 = std::tuple{1, 2.5, 'x'};          // C++17 CTAD

// forward_as_tuple — references (advanced; careful with lifetimes)
int x = 1;
auto refs = std::forward_as_tuple(x, 2);    // tuple<int&, int&&>
```

### Access: `std::get`, structured bindings, `std::tie`

```cpp
#include <tuple>
#include <iostream>

std::tuple<int, std::string, double> t{42, "hi", 3.14};

// By index (compile-time constant)
int    i = std::get<0>(t);
auto&  s = std::get<1>(t);
double d = std::get<2>(t);

// By type — only if that type appears exactly once
std::string s2 = std::get<std::string>(t);

// C++17 structured bindings (preferred for unpacking)
auto [id, name, score] = t;

// std::tie — bind to existing lvalues (pre-C++17 unpack; still useful)
int a; std::string b; double c;
std::tie(a, b, c) = t;

// Ignore some fields
std::tie(a, std::ignore, c) = t;   // skip the string
```

`std::tie` returns a `tuple` of **lvalue references**. That is why `std::tie(a, b) = std::minmax(10, 3)` assigns into existing variables, and why `std::tie` is the classic way to implement multi-field `operator<` without writing a long chain of comparisons.

### Lexicographic comparison and multi-key sorting via `tie`

Tuples compare lexicographically left-to-right, like pairs. To sort a range of structs by several fields, either store a `tuple`/`pair` key or compare with `std::tie`:

```cpp
#include <algorithm>
#include <tuple>
#include <vector>
#include <string>

struct Student {
    std::string name;
    int year;
    double gpa;
};

bool operator<(const Student& a, const Student& b) {
    // Sort by year ascending, then GPA descending, then name ascending:
    // negate GPA via transforming, or compare manually; tie helps the ascending case:
    return std::tie(a.year, a.name) < std::tie(b.year, b.name);
}

// Or materialise a sort key:
std::vector<Student> v;
std::sort(v.begin(), v.end(), [](const Student& a, const Student& b) {
    return std::tuple{a.year, -a.gpa, a.name}
         < std::tuple{b.year, -b.gpa, b.name};  // -gpa ⇒ higher GPA first
});
```

### `tuple_cat` and `std::apply` (brief)

```cpp
#include <tuple>
#include <utility>

auto t = std::tuple_cat(std::make_tuple(1, 2), std::make_pair(3, 4));
// tuple<int,int,int,int> holding 1,2,3,4

auto sum = std::apply([](int a, int b, int c, int d) {
    return a + b + c + d;
}, t);  // C++17: call a callable with the tuple's elements as arguments
```

`std::apply` unpacks a tuple into a function call — useful with generic code and `std::invoke`. Reach for it when you already have a tuple; do not force data into tuples just to use `apply`.

### Cost notes

Like `pair`, a tuple is a thin wrapper: size is roughly the sum of members (plus possible padding). `std::get<I>` is $O(1)$ and typically compiles to a direct member access. Prefer `pair` when $N = 2$ and `.first`/`.second` are idiomatic (map entries, edges); prefer `tuple` when $N \ge 3$ or you need `tie`/`apply`/`tuple_cat`.

::: interview
"How do you sort by multiple keys?" — put the keys in a `pair`/`tuple` (lexicographic `<`), or implement `operator<` / a comparator with `std::tie(a.f1, a.f2) < std::tie(b.f1, b.f2)`. Mention structured bindings for reading the result.
:::

## `std::optional<T>` — maybe a value (C++17)

### What it is and why it exists

A **`std::optional<T>`** (header `<optional>`) either holds a `T` or holds nothing. It replaces "sentinel" return values (`-1`, `nullptr`, empty string) with an explicit empty state. The classic idiom: a search or parse that may fail returns `optional<T>` instead of a magic number.

::: definition
**`std::optional<T>`** is a vocabulary type for an optional value: engaged (contains a `T`) or disengaged (empty). Empty is spelled `std::nullopt`.
:::

Think of it as a box that may or may not contain an object — not a pointer, and not heap-allocated by default (the `T` is typically stored inside the `optional` object).

![`std::optional` either holds a value (engaged) or holds nothing (`nullopt`).](assets/s57_optional.png)

### Construction and state

```cpp
#include <optional>
#include <string>

std::optional<int> a;                 // empty
std::optional<int> b = std::nullopt;  // empty
std::optional<int> c = 42;            // engaged with 42
std::optional<std::string> d{"hi"};   // engaged
std::optional<std::string> e = std::make_optional<std::string>(3, 'x'); // "xxx"
```

### Full access and mutation API

| API | Behaviour |
| :--- | :--- |
| `has_value()` / `operator bool` | `true` if engaged |
| `value()` | Returns reference to `T`; throws `std::bad_optional_access` if empty |
| `value_or(default)` | Returns `T` if engaged, otherwise `default` (by value) |
| `operator*` / `operator->` | Access the contained `T`; **undefined behaviour if empty** |
| `emplace(args...)` | Destroy old value (if any); construct `T` in place |
| `reset()` / `= nullopt` | Disengage (destroy contained value) |
| `swap` | Swap two optionals |

```cpp
#include <optional>
#include <iostream>
#include <vector>

std::optional<int> find_even(const std::vector<int>& v) {
    for (int x : v)
        if (x % 2 == 0) return x;   // implicit optional<int>
    return std::nullopt;
}

int main() {
    auto r = find_even({1, 3, 4, 5});

    if (r) {                        // operator bool
        std::cout << *r << '\n';    // OK: engaged
        std::cout << r.value() << '\n';
    }

    int x = r.value_or(-1);         // 4, or -1 if empty — never throws

    r.emplace(10);                  // now holds 10
    r.reset();                      // empty again
}
```

### Complexity and cost

An `optional<T>` is typically a `T` plus a `bool` (with padding). Construction of an empty optional does not construct a `T`. Engaging constructs a `T`; `reset` destroys it. Access when engaged is $O(1)$. Prefer `value_or` or an `if (opt)` check over bare `*opt` unless you have just proven it is engaged.

::: trap
`opt.value()` on an empty optional throws `std::bad_optional_access`. `*opt` or `opt->` on an empty optional is **undefined behaviour** — no throw, just UB. Always check `has_value()` / `if (opt)` before dereferencing, or use `value()` / `value_or` deliberately.
:::

::: interview
"How do you return 'no result' from a search without a sentinel?" — `std::optional<T>`. Follow-up: difference between `value()` and `operator*` — throw vs UB when empty.
:::

## `std::variant<...>` — a type-safe tagged union (C++17)

### What it is and why it exists

A **`std::variant<Ts...>`** (header `<variant>`) holds **exactly one** of a fixed list of alternative types at any time, together with a tag recording which. It is the type-safe replacement for a C `union` plus a hand-rolled discriminator enum: the library tracks the active alternative and refuses silent misuse at the type level (access of the wrong alternative throws or returns null, rather than reinterpreting bits).

::: definition
A **`std::variant<T0, T1, …>`** is a **discriminated union**: storage for one of the `Ti`, plus an index naming which alternative is active.
:::

Analogy: a labelled jar that can hold tea *or* coffee *or* water — never two at once, and the label always says which.

![`std::variant` is a type-safe tagged union: one active alternative plus an index recording which.](assets/s57_variant.png)

### Construction and query

```cpp
#include <variant>
#include <string>

std::variant<int, std::string, double> v = 42;       // holds int
v = std::string{"hello"};                            // now holds string
v = 3.14;                                            // now holds double

std::size_t i = v.index();                           // 2 (double is alternative 2)
bool is_str = std::holds_alternative<std::string>(v); // false
```

Default construction activates the **first** alternative, value-initialised (so `variant<int, string>{}` holds `0`, not empty — there is no empty state unless you include `std::monostate` as an alternative).

### Access: `get`, `get_if`, and `visit`

| API | On success | On wrong / empty |
| :--- | :--- | :--- |
| `std::get<T>(v)` / `std::get<I>(v)` | Reference to alternative | Throws `std::bad_variant_access` |
| `std::get_if<T>(&v)` / `std::get_if<I>(&v)` | `T*` to alternative | `nullptr` (no throw) |
| `std::holds_alternative<T>(v)` | `bool` | — |
| `v.index()` | Active alternative index | `variant_npos` only in the rare valueless state |
| `std::visit(visitor, v)` | Calls the overload matching the active type | — |

```cpp
#include <variant>
#include <string>
#include <iostream>

std::variant<int, std::string> v = "hi";

// Throwing access
try {
    int n = std::get<int>(v);           // throws bad_variant_access
} catch (const std::bad_variant_access&) {}

if (auto* p = std::get_if<std::string>(&v)) {
    std::cout << *p << '\n';            // safe: pointer, or nullptr
}

// std::visit with a generic lambda (C++17)
std::visit([](const auto& x) {
    std::cout << x << '\n';
}, v);

// Or an explicit overloaded visitor
struct Printer {
    void operator()(int x) const { std::cout << "int " << x << '\n'; }
    void operator()(const std::string& s) const { std::cout << "str " << s << '\n'; }
};
std::visit(Printer{}, v);
```

A common pattern for exhaustive visitors is the **overloaded** helper (pack of lambdas into one callable):

```cpp
template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

std::variant<int, std::string, double> w = 1.5;
std::visit(overloaded{
    [](int x) { /* ... */ },
    [](const std::string& s) { /* ... */ },
    [](double x) { /* ... */ },
}, w);
```

### `valueless_by_exception`

If assigning or emplacing a new alternative throws during construction, a variant may enter the rare **`valueless_by_exception`** state: no alternative is active, `index() == variant_npos`, and `valueless_by_exception()` is `true`. Normal code paths almost never see this; know the name for interviews.

### Contrast with a raw `union`

A C-style `union` (or untagged C++ `union`) lets you write one member and read another — classic UB for non-trivial types. You must maintain a separate enum tag yourself. `std::variant` *is* that tag plus storage, with typed accessors and `visit`. Prefer `variant` whenever the set of alternatives is closed and known at compile time.

### Cost notes

Size is roughly the size of the largest alternative, plus a small discriminant (and padding). Access and `visit` are $O(1)$ (often implemented as a jump table on `index()`). Prefer `variant` over `any` when the type set is fixed; prefer inheritance/`unique_ptr<Base>` when the set of types is open / polymorphic and heap allocation is acceptable.

::: trap
`std::get<T>(v)` when `T` is not the active alternative throws `std::bad_variant_access`. Check with `holds_alternative` / `index`, use `get_if`, or `visit` — do not `get` blindly.
:::

::: interview
"Variant vs union?" — variant is a type-safe tagged union: it tracks the active type and makes wrong access throw or return null. "Variant vs `any`?" — variant's alternatives are fixed at compile time; `any` type-erases any single copyable value.
:::

## `std::any` — type-erased single value (C++17)

### What it is and why it exists

A **`std::any`** (header `<any>`) holds a single value of *any* copy-constructible type, with the type erased at the API boundary. You put something in; you get it back only by naming the correct type in `any_cast`. It is the vocabulary type for "I need to store one object whose type I truly do not know until run time."

```cpp
#include <any>
#include <string>
#include <typeinfo>

std::any a;                         // empty
a = 42;                             // holds int
a = std::string{"hello"};           // holds string — previous int destroyed

if (a.has_value()) {
    const std::type_info& ti = a.type();  // typeid(string) here
}

// Throwing cast (by value / reference forms)
try {
    auto s = std::any_cast<std::string>(a);
} catch (const std::bad_any_cast&) {}

// Non-throwing: pass pointer to any → returns pointer or nullptr
if (auto* p = std::any_cast<std::string>(&a)) {
    // *p is the string
}

a.reset();                          // empty again
```

| API | Role |
| :--- | :--- |
| `has_value()` | Whether something is stored |
| `type()` | `typeid` of the contained value, or `typeid(void)` if empty |
| `emplace<T>(args...)` | Construct a `T` in place |
| `reset()` | Clear |
| `std::any_cast<T>(any)` | Extract; throws `std::bad_any_cast` on mismatch |
| `std::any_cast<T>(&any)` | Pointer form; `nullptr` on mismatch / empty |

### When to use (rarely) vs `variant`

Prefer **`variant`** when the set of possible types is known and closed — it is faster, smaller in intent, and exhaustively visitable. Reach for **`any`** only when the type set is truly open (plugin maps, heterogeneous property bags) and you accept run-time checks and possible small-buffer / heap allocation inside the implementation. In DSA/CP, `any` almost never appears; interviews ask it mainly to contrast with `variant`.

### Cost notes

`any` typically uses a small buffer optimisation for small types and heap-allocates larger ones. Casts are $O(1)$ type checks. Copies copy the contained object. Prefer `variant` or a concrete type whenever you can.

::: keypoint
`any` is type erasure for *one* value; `variant` is a closed tagged union; `optional` is "zero or one `T`". Do not use `any` as a sluggish `optional` or a poorly typed `variant`.
:::

## `std::string_view` — non-owning view of characters (C++17)

### What it is and why it exists

A **`std::string_view`** (header `<string_view>`) is a non-owning `(pointer, length)` pair over a contiguous sequence of `char`. It does **not** allocate, does **not** own, and does **not** guarantee a null terminator. It exists to pass and slice strings without copying — parsers, substring algorithms, and APIs that only *read* character data.

::: definition
A **`std::string_view`** is a non-owning view: a pointer to existing character data plus a size. The viewed data must outlive the view.
:::

Owning strings remain `std::string` (see **s13**). Prefer `string_view` parameters when the callee only reads text and does not need to extend lifetime or mutate ownership.

![A `string_view` is a non-owning pointer+length into characters that someone else owns.](assets/s57_string_view.png)

### Construction and API highlights

```cpp
#include <string>
#include <string_view>

std::string s = "competitive programming";
std::string_view sv = s;                 // view whole string
std::string_view lit = "literal";        // OK: string literals have static storage
std::string_view part(s.data() + 12, 11); // "programming" — ptr + length

// O(1) prefix/suffix / substr (substr is O(1) — no copy)
sv.remove_prefix(12);                    // now views "programming"
sv.remove_suffix(3);                     // views "programmi"

// Observing API (mirrors much of string's read side)
std::size_t n = sv.size();
bool empty = sv.empty();
char c = sv[0];                          // unchecked
char d = sv.at(0);                       // throws out_of_range if bad
auto pos = sv.find('a');                 // npos if missing
auto pos2 = sv.find("gram");

// substr is O(1): new view into the *same* underlying data
std::string_view sub = lit.substr(0, 3); // "lit" — owner is the static literal
```

Common operations: `size` / `length`, `empty`, `data`, `operator[]`, `at`, `front`, `back`, `remove_prefix`, `remove_suffix`, `substr`, `compare`, `starts_with` / `ends_with` (C++20), and the `find` / `rfind` / `find_first_of` family. Modifying the characters requires a writable owner (`string` / array); the view itself only reseats its `(ptr, len)`.

### Complexity

| Operation | Cost |
| :--- | :--- |
| Construct from `string` / literal / `(ptr, n)` | $O(1)$ |
| `substr`, `remove_prefix`, `remove_suffix` | $O(1)$ (adjust pointer/length) |
| `find` / comparisons | $O(n)$ in the lengths involved |
| Copying a `string_view` | $O(1)$ (copies ptr+len, not characters) |

### Trap: dangling views

Because a view does not extend lifetime, it must not outlive the character data it points at. Returning a `string_view` into a function-local `string`, or binding a view to a temporary, creates a dangling view.

```cpp
#include <string>
#include <string_view>

std::string_view bad_api() {
    std::string local = "temp";
    return local;   // DANGLING: local is destroyed; view points at dead memory
}

std::string_view also_bad = std::string{"tmp"};  // temporary string dies at end of statement

// OK patterns:
std::string_view ok_literal = "static";          // literal lives for the program
std::string owner = "keep me";
std::string_view ok = owner;                     // owner outlives ok
std::string copy = std::string{ok};              // if you need ownership, copy into string
```

::: trap
A `string_view` must not outlive its owner. Never return a view of a local `string` or bind a view to a temporary `std::string` and use it later. If ownership or long life is required, return / store a `std::string`.
:::

### Trap: not null-terminated

`string_view::data()` returns a `const char*` that is **not** guaranteed to be followed by `'\0'`. Passing `sv.data()` to C APIs that expect a C string (`strlen`, `fopen`, `printf("%s")`, …) is undefined behaviour unless you know the view covers a null-terminated buffer (e.g. a full `std::string` without an embedded NUL, viewed as the whole string — still prefer being explicit).

```cpp
std::string_view sv = "abcdef";
sv.remove_suffix(3);              // views "abc" — but the literal still has more chars
// strlen(sv.data()) is NOT "3" — it walks past the view into "def"

// Safe bridge to C APIs:
std::string owned{sv};            // copy; c_str() is NUL-terminated
c_api(owned.c_str());
```

::: trap
`string_view` is not a C string. Do not pass `.data()` to APIs that require a null-terminated `const char*` unless you have verified termination. Build a `std::string` (or ensure the owner provides a terminator within the view) first.
:::

::: interview
"Why take `string_view` instead of `const string&`?" — accepts `string`, literals, and substrings without allocating; $O(1)$ slices. Follow-up trap: dangling views and non-NUL-terminated `.data()`.
:::

## Brief related vocabulary: `reference_wrapper` and `span`

**`std::reference_wrapper<T>`** (`<functional>`), usually created with **`std::ref`** / **`std::cref`**, stores a reference in a copyable object so you can put "references" into containers and pass them through templates that decay reference arguments:

```cpp
#include <functional>
#include <vector>

int a = 1, b = 2;
std::vector<std::reference_wrapper<int>> v = {std::ref(a), std::ref(b)};
v[0].get() = 99;   // a is now 99
```

**`std::span<T>`** (C++20, `<span>`) is the contiguous-range analogue of `string_view`: a non-owning `(pointer, length)` over any contiguous sequence (`array`, `vector`, C array). Same dangling discipline as `string_view`. One-liner: use `span` for generic read/write views of buffers; use `string_view` specifically for character data.

## Which to reach for

| Need | Reach for |
| :--- | :--- |
| Two fields; map entry; edge $(u,v)$; sort by key then tie-break | `std::pair` |
| Three or more fields; multi-key `tie` / sort key; `apply` | `std::tuple` |
| "Maybe a result" without a sentinel | `std::optional<T>` |
| One of a *fixed* set of types; visit exhaustively | `std::variant<…>` |
| Truly unknown / open type in one box (rare) | `std::any` |
| Read-only text without copying; $O(1)$ substr | `std::string_view` (owner in **s13** `std::string`) |
| Store references in a container | `std::ref` / `std::reference_wrapper` |
| Non-owning view of any contiguous buffer (C++20) | `std::span` |

::: keypoint
Default ladder: `pair`/`tuple` for products, `optional` for absence, `variant` for closed sums of types, `string_view` for non-owning text. Escalate to `any` only when the type set cannot be named.
:::

::: interview
Expect a rapid-fire: pair lexicographic sort; `optional` `value` vs `*` (throw vs UB); `variant` vs union vs `any`; `string_view` dangling and NUL traps. Naming the header and one safe access pattern for each type is a complete answer.
:::
