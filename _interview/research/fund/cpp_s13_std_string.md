# The `std::string` Class

::: definition
C++ provides a proper string type, **`std::string`** (from `<string>`), that removes the manual bookkeeping of C-style character arrays. Unlike a fixed character array, a `std::string` manages its own storage: it grows and shrinks as needed, tracks its own length, and offers a large set of member functions for searching, editing, and combining text.
:::

Formally, `std::string` is a typedef for `std::basic_string<char>`. The same template also yields `std::wstring` (`wchar_t`), `std::u16string`, and `std::u32string`; almost all interview and contest work uses the narrow `char` specialisation discussed here.

## Declaring, initialising, and reading

```cpp
#include <string>
using namespace std;

string str;             // an empty string object
string str2 = "Hello";  // initialised from a literal
```

A `std::string` is an **object**, not a bare array. Two ways of reading text into one differ in how much they take:

```cpp
cin >> str;            // reads a single word (stops at whitespace)
getline(cin, str);     // reads an entire line, spaces included
```

::: trap
So `cin >> str` on the input `hello world` stores only `hello`, whereas `getline(cin, str)` stores the whole line `hello world`. Two consecutive `getline` calls read two successive lines.
:::

The free function `std::getline` lives in `<string>` and is the preferred way to read a whole line into a `std::string`. The classic trap of mixing `cin >>` with `getline` (leftover newline), stream-state loops, and contest fast-I/O interaction are covered in depth in **I/O buffering and fast I/O** (`s54`). Prefer `getline(cin, str)` over C-style `cin.getline(buf, n)` whenever you already own a `std::string`.

Other common initialisation forms:

```cpp
#include <string>

std::string a;                          // empty
std::string b(5, 'x');                  // "xxxxx" — count and fill character
std::string c = "hello";                // from a C-string / literal
std::string d(c);                       // copy
std::string e(c, 1, 3);                 // substring of c: "ell"
std::string f({'a', 'b', 'c'});         // from initialiser list
```

## Length, capacity, and storage management

::: definition
Internally a string keeps a block of storage that may be larger than the text it currently holds. The **length** (or size) is the number of characters in use; the **capacity** is the size of the allocated block. The string enlarges its capacity automatically as characters are added.
:::

| Member | Meaning |
| --- | --- |
| `s.length()`, `s.size()` | number of characters currently stored |
| `s.capacity()` | size of the allocated storage block |
| `s.resize(30)` | change the length to 30 characters |
| `s.max_size()` | largest length the implementation can hold |
| `s.clear()` | erase all characters (length becomes 0) |
| `s.empty()` | `true` if the string has no characters |

```cpp
string s1 = "Hello", s2 = "world";
s1.length();   // 5
```

![The std::string keeps a storage block (capacity) that can exceed the current length and grows automatically.](assets/fig_20260617_string-class-capacity.png)

### `resize`, `reserve`, `shrink_to_fit`, and capacity semantics

`size()` / `length()` and `capacity()` answer different questions. Changing one does not automatically force the other to match:

| Member | Effect on size | Effect on capacity |
| --- | --- | --- |
| `s.resize(n)` | sets length to `n` (pad with `'\0'` or a fill char if growing; truncate if shrinking) | may grow if `n > capacity()`; shrinking length does **not** free capacity |
| `s.resize(n, ch)` | as above, padding with `ch` when growing | same |
| `s.reserve(n)` | **unchanged** | ensures `capacity() >= n` (may allocate / reallocate) |
| `s.shrink_to_fit()` | **unchanged** | non-binding request to reduce capacity toward `size()` |
| `s.clear()` | sets size to $0$ | capacity typically **kept** (storage not released) |

```cpp
#include <string>
#include <iostream>

std::string s = "hi";
std::cout << s.size() << ' ' << s.capacity() << '\n';  // 2  and some capacity >= 2

s.reserve(100);   // size still 2; capacity at least 100 — no characters added
s.resize(5, '!'); // size becomes 5: "hi!!!" — may use existing capacity
s.resize(1);      // size becomes 1: "h" — capacity usually still large
s.shrink_to_fit(); // ask the implementation to trim excess capacity (may be a no-op)
```

::: keypoint
`reserve(n)` is the tool for **growth planning**: you promise "I will need about $n$ characters of room" without changing the logical text. `resize(n)` changes the **logical length** — new positions become part of the string (and are readable via `[]` / iterators). Confusing the two is a common bug when building strings character by character.
:::

`clear()` empties the string (`size() == 0`, `empty() == true`) but typically leaves capacity alone so a later rebuild can reuse the buffer. There is no standard "release all storage now" member; `shrink_to_fit()` is only a request, and `std::string().swap(s)` (or move-assigning from a temporary empty string) is the portable idiom when you truly want to drop a large buffer.

<!-- FIG s13: size vs capacity — length marks used chars; capacity is the allocated block -->

## Under the hood: Small String Optimisation (SSO)

::: heavy
Dense subsection — slow down. **Small String Optimisation** explains why short strings are cheap, why `sizeof(std::string)` is larger than a bare pointer, and why moving / copying tiny strings often never touches the heap.
:::

Analogy: a courier van that carries a small locked box *inside the cab* for envelopes, and only opens the trailer for large parcels. Short messages never leave the cab; long ones go in the trailer (the heap).

![The Small String Optimisation: short strings live inline in the object; long strings spill to the heap.](assets/s13_sso.png)

Concrete example first:

```cpp
#include <string>
#include <iostream>

int main() {
    std::string tiny  = "hi";           // typically no heap allocation (SSO)
    std::string large(100, 'x');        // must use the heap

    std::cout << sizeof(std::string) << '\n';  // often 24 or 32 on 64-bit libstdc++/libc++
    std::cout << tiny.capacity() << ' ' << large.capacity() << '\n';
}
```

Plain-English rule: for strings up to some small implementation-defined length (commonly around 15 characters for `char` on 64-bit libstdc++, or a similar band on libc++), the characters live **inside the `std::string` object itself**. Beyond that threshold the object holds a pointer to a heap buffer, plus size and capacity.

Technical statement: **Small String Optimisation (SSO)** (also called *small-string optimisation* or *short-string optimisation*) is an implementation technique whereby `std::basic_string` embeds a fixed internal buffer (or reuses the storage that would otherwise hold the heap pointer / capacity fields via a union) so that short strings need no dynamic allocation. The standard does not mandate SSO, but every major standard library uses it. Consequences:

- Short strings avoid `new` / `delete` — construction, copy, and destruction of tiny strings are cheap.
- `sizeof(std::string)` is **larger than a pointer** (often three words: something like pointer + size + capacity, or an equivalent union layout), because the object must reserve room for that inline buffer and the bookkeeping fields.
- Moving a long string can steal the heap pointer in $O(1)$; moving a short SSO string typically just copies the inline bytes (still $O(1)$ and allocation-free).
- Taking `c_str()` / `data()` on an SSO string still yields a contiguous, null-terminated view — the terminator sits in the inline buffer.

::: keypoint
**SSO** means short strings live inline in the object (no heap), so small strings avoid allocation. That is why building and passing short `std::string` values is far cheaper than a naive "always heap-allocate" design, and why `sizeof(std::string)` exceeds `sizeof(char*)`.
:::

::: interview
"Does `std::string` always allocate on the heap?" — No: with SSO, short strings typically do not. "Why is `sizeof(std::string)` bigger than a pointer?" — The object stores size/capacity (or equivalent) and an inline buffer for SSO, not merely a `char*`.
:::

## Contiguous storage, `c_str()`, and `data()`

Since C++11, `std::string` guarantees **contiguous** storage of its characters, and since C++11 the stored sequence is also **null-terminated**: there is a `'\0'` at `data()[size()]` that is not counted in `size()`. You may treat `&s[0]` / `s.data()` as a pointer to `s.size()` characters, and `s.c_str()` as a pointer to a C-string of length `s.size()`.

| Member | Meaning |
| --- | --- |
| `s.c_str()` | `const char*` to a null-terminated C-string (always `const`) |
| `s.data()` (const overload) | `const CharT*` to the contiguous character buffer |
| `s.data()` (C++17 non-const) | `CharT*` — mutable pointer to the buffer |
| `&s[0]` (when `!s.empty()`) | address of the first character; contiguous through `s[size()-1]` |

```cpp
#include <string>
#include <cstring>
#include <cstdio>

std::string s = "Hello";

const char* p = s.c_str();   // "Hello" with trailing '\0' — for C APIs
std::puts(p);                // fine: null-terminated

const char* d = s.data();    // points at the same contiguous buffer
// Since C++11, data() is also null-terminated like c_str() for std::string.
// Historically (C++98), data() was NOT required to be null-terminated; c_str() was.

#if __cplusplus >= 201703L
char* mut = s.data();        // C++17: non-const data() — can write s.size() chars
mut[0] = 'h';                // s becomes "hello"
#endif
```

::: keypoint
Today, for `std::string`, `c_str()` and the const `data()` overload are interchangeable for reading: both yield a pointer to contiguous, null-terminated storage. Prefer `c_str()` when calling a C API that documents a "C string", and `data()` when you mean "pointer to the character buffer" (especially the C++17 mutable form). Neither pointer remains valid after a non-const operation that may reallocate (e.g. `append`, `+=`, `reserve` that grows).
:::

::: trap
Do **not** `return s.c_str();` from a function when `s` is a local `std::string` — the pointer dangles as soon as `s` is destroyed. Return the `std::string` by value (or a `string_view` only while the owner lives — see `s57`).
:::

## Modifying a string

A family of members edits the text in place:

| Member | Effect |
| --- | --- |
| `s.append("Bye")` | add characters to the end |
| `s.insert(3, "KK")` | insert `"KK"` at index 3 |
| `s.insert(3, "apple", 2)` | insert the first 2 characters of `"apple"` at index 3 |
| `s.replace(3, 4, "KK")` | replace 4 characters from index 3 with `"KK"` |
| `s.erase()` | remove characters |
| `s.push_back('z')` | append one character |
| `s.pop_back()` | remove the last character |
| `s1.swap(s2)` | exchange the contents of two strings |

For example, `replace` applied to `"Programming"` starting at index 3 and spanning a few characters, substituting `"KK"`, yields a spliced result such as `"ProKKming"`.

`append` and `push_back` are the workhorses for building text at the end; `operator+=` (below) is syntactic sugar over the same idea. Prefer `push_back` / `+=` for one character or a known piece; use `reserve` first when the final length is predictable.

## Copying out to a character array

::: trap
`s.copy(dest, n)` copies `n` characters of the string into a character array — but, unlike `strcpy`, it does **not** append a terminating `'\0'`. The caller must add one, or the array will print trailing garbage:
:::

```cpp
string s = "Welcome";
char str[10];

s.copy(str, 3);      // copies 'W','e','l' — but no '\0'
str[3] = '\0';       // terminate manually
cout << str;         // "Wel"
```

When you need a C-string for a legacy API, prefer `s.c_str()` (or copy into your own buffer with an explicit `'\0'`) over `copy` unless you intentionally want a non-terminated substring in a fixed array.

## Searching

| Member | Returns |
| --- | --- |
| `s.find(x)` | index of the **first** occurrence of substring or character `x` |
| `s.rfind(x)` | index of the **last** occurrence |
| `s.find_first_of(set)` | index of the first character that is **any** of those in `set` |
| `s.find_last_of(set)` | index of the last such character |

With `string str = "How are you"`, `str.find('o')` is 1 (the first `o`), while `str.rfind('o')` is 9 (the last). 

::: keypoint
Searching for something absent — `str.find('k')` — returns a special out-of-range value (**`string::npos`**) that signals "not found".
:::

`find_first_of` takes a *set* of characters and stops at the first that matches any of them; an optional second argument supplies the index to start from:

```cpp
string str = "Hello world";
str.find_first_of('l');       // 2  (first 'l')
str.find_first_of('l', 3);    // 3  (first 'l' at or after index 3)
str.find_first_of("le");      // 1  (first char that is 'l' or 'e')
```

### Prefix, suffix, and substring tests (C++20 / C++23)

Modern C++ adds dedicated Boolean queries so you need not compare `find` against `0` or `size()`:

```cpp
#include <string>

std::string s = "filename.txt";

// C++20
bool pre = s.starts_with("file");   // true
bool suf = s.ends_with(".txt");     // true
bool pre2 = s.starts_with('f');     // true — also overloads for char / string_view

// C++23
bool mid = s.contains("name");      // true
bool ch  = s.contains('.');         // true
```

`starts_with` / `ends_with` (C++20) and `contains` (C++23) accept a string-like piece, a `string_view`, or a single character. They express intent clearly and avoid off-by-one mistakes with `find` / `compare`. On older dialects, the equivalents are `s.compare(0, len, prefix) == 0`, `s.size() >= n && s.compare(s.size() - n, n, suffix) == 0`, and `s.find(sub) != std::string::npos`.

## Substrings, comparison, element access, and operators

- `s.substr(start)` returns the tail from `start` to the end; `s.substr(start, number)` returns `number` characters beginning at `start`.
- `s.compare(str)` compares lexicographically and returns a negative, zero, or positive value, exactly like `strcmp`.
- `s.at(i)`, `s.front()`, `s.back()`, and `s[i]` access individual characters.

Because `std::string` is a class, it also overloads the familiar operators:

```cpp
string str1 = "Hello", str2 = "world";

string s3   = str1 + str2;    // "Helloworld"   (+ concatenates)
str1        = str1 + " world";// "Hello world"
bool same   = (str1 == str2); // == compares for equality
```

These operators make string handling read like ordinary value manipulation — joining with `+`, comparing with `==` — which is the central convenience of the string class over raw character arrays.

### Concatenation cost: `+` versus `+=`, and why `reserve` matters

`operator+` builds a **new** string from its operands. Chaining `a + b + c` materialises temporaries; each may allocate. `operator+=` (and `append` / `push_back`) extend an **existing** string in place and only reallocate when `size()` is about to exceed `capacity()`.

```cpp
#include <string>
#include <vector>

// Costly pattern: repeated + creates many temporaries
std::string bad;
for (int i = 0; i < 1000; ++i)
    bad = bad + "x";          // each step: allocate new string, copy old + "x"

// Better: append in place (amortised growth, like vector)
std::string better;
for (int i = 0; i < 1000; ++i)
    better += 'x';            // or better.push_back('x');

// Best when the final length is known: reserve once, then append
std::string best;
best.reserve(1000);
for (int i = 0; i < 1000; ++i)
    best += 'x';             // no reallocation in the loop
```

Growth is typically geometric (capacity multiplies by a constant factor when exhausted), so a loop of `+=` without `reserve` is still amortised $O(n)$ for $n$ appends — but it still performs several allocations and copies. Pre-sizing with `reserve` removes that churn. Joining many pieces with a fold of `+` is $O(n^2)$ in the worst pattern of always copying the growing left-hand side into a brand-new string.

::: trap
`+=` (or `append`) in a tight loop **without** `reserve` repeatedly reallocates and copies as capacity runs out — fine for small $n$, painful for large builders. Prefer `s.reserve(expected)` when you know (or can upper-bound) the final length. Prefer `+=` / `append` over `s = s + piece` so you mutate in place instead of assigning a fresh temporary each iteration.
:::

```cpp
#include <string>
#include <vector>

std::string join(const std::vector<std::string>& parts) {
    std::size_t total = 0;
    for (const auto& p : parts) total += p.size();

    std::string out;
    out.reserve(total);                 // one allocation
    for (const auto& p : parts) out += p;
    return out;
}
```

## Numeric conversions: `std::to_string` and `std::sto*`

::: definition
The header `<string>` provides free functions that convert between numeric types and `std::string`: **`std::to_string`** formats a number as decimal text, and the **`std::sto*`** family (`stoi`, `stol`, `stoll`, `stof`, `stod`, `stold`, …) parses text into a number.
:::

### `std::to_string`

```cpp
#include <string>

std::string a = std::to_string(42);        // "42"
std::string b = std::to_string(3.14);      // implementation-defined formatting of double
std::string c = std::to_string(-1L);       // "-1"
```

Overloads exist for the arithmetic types (`int`, `long`, `long long`, `unsigned` variants, `float`, `double`, `long double`). `to_string` always uses a **decimal** (base-10) representation — there is no `base` argument. For hexadecimal / binary formatting, use iostream manipulators, `std::format` (C++20), or `std::to_chars` (below).

### `std::stoi`, `stol`, `stoll`, `stof`, `stod`, …

Signatures (representative):

```cpp
#include <string>

int       std::stoi (const std::string& str, std::size_t* idx = nullptr, int base = 10);
long      std::stol (const std::string& str, std::size_t* idx = nullptr, int base = 10);
long long std::stoll(const std::string& str, std::size_t* idx = nullptr, int base = 10);

float       std::stof (const std::string& str, std::size_t* idx = nullptr);
double      std::stod (const std::string& str, std::size_t* idx = nullptr);
long double std::stold(const std::string& str, std::size_t* idx = nullptr);
```

There are also `stoul` / `stoull` for unsigned integers, and overloads taking `const std::wstring&`.

- **`base`**: for the integer converters, `base` in $[2, 36]$, or `0` to auto-detect (`0x` → hex, leading `0` → octal, otherwise decimal). Ignored for the floating-point converters.
- **`idx`**: if non-null, `*idx` is set to the index of the first **unconverted** character (how far the parse got). Useful for partial parses and validation.

```cpp
#include <string>
#include <iostream>

std::size_t pos = 0;
int x = std::stoi("42xyz", &pos, 10);  // x == 42, pos == 2  (stopped at 'x')
int y = std::stoi("ff", nullptr, 16);  // y == 255
int z = std::stoi("0x10", nullptr, 0); // z == 16 — base 0 auto-detects 0x
```

### Exceptions: `std::invalid_argument` and `std::out_of_range`

The `sto*` functions report failure by throwing (they do **not** return an error code):

| Situation | Exception |
| --- | --- |
| No conversion could be performed (e.g. `stoi("abc")`, empty string after optional whitespace/sign) | **`std::invalid_argument`** |
| Converted value is outside the range of the result type (e.g. `stoi` on a number bigger than `INT_MAX`) | **`std::out_of_range`** |

Both are defined in `<stdexcept>`. Whitespace may be skipped at the start; parsing then follows `strtol`-like rules. A successful conversion of a *prefix* is allowed — `"42xyz"` yields `42` and does **not** throw; use the `idx` parameter if you require the entire string to be consumed.

```cpp
#include <string>
#include <stdexcept>
#include <iostream>

void parse_strict(const std::string& s) {
    try {
        std::size_t pos = 0;
        int v = std::stoi(s, &pos, 10);
        if (pos != s.size()) {
            // partial parse: e.g. "12ab" → v == 12, pos == 2
            std::cerr << "trailing junk at index " << pos << '\n';
            return;
        }
        std::cout << v << '\n';
    } catch (const std::invalid_argument&) {
        std::cerr << "no conversion\n";
    } catch (const std::out_of_range&) {
        std::cerr << "out of range\n";
    }
}
```

::: trap
`std::stoi` (and family) **throw** on hard failure (`invalid_argument` / `out_of_range`), and they happily accept a **partial** parse (`"42abc"` → `42`) unless you check `idx` against `size()`. Never assume "no exception means the whole string was a clean number." In exception-averse or hot contest code, prefer `<charconv>` (below) or stream extraction with explicit failure checks.
:::

::: interview
"What does `stoi` throw?" — `std::invalid_argument` if no conversion; `std::out_of_range` if the value does not fit. Follow-up: partial parses succeed — validate with the `idx` out-parameter.
:::

### Fast, locale-free alternative: `<charconv>` (`from_chars` / `to_chars`)

For competitive programming and performance-sensitive parsing, **`std::from_chars`** / **`std::to_chars`** (header `<charconv>`, C++17) are the preferred tools:

- They operate on raw character ranges (`const char*` … `const char*`), not on `std::string` temporaries alone.
- They are **locale-independent** and typically much faster than `sto*` / iostreams.
- They **do not throw**; they return a `std::from_chars_result` / `std::to_chars_result` with a pointer and an error `std::errc`.

```cpp
#include <charconv>
#include <string>
#include <iostream>
#include <system_error>

int parse_int_fast(const std::string& s) {
    int value = 0;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), value);
    if (ec != std::errc{} || ptr != s.data() + s.size()) {
        // failure, or trailing non-digits
        return 0;
    }
    return value;
}

std::string format_int_fast(int value) {
    char buf[32];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof buf, value);
    if (ec != std::errc{}) return {};
    return std::string(buf, ptr);  // [buf, ptr) holds the digits
}
```

Integer `from_chars` / `to_chars` are widely available; floating-point support arrived later and can be implementation-dependent in quality. When an interview or contest problem needs bulk integer parsing without locale or exceptions, reach for `<charconv>` and only fall back to `stoi` / `to_string` for convenience code.

## Iterating over a string

::: definition
A string can be traversed character by character either by index or with an **iterator** — an object that points at a character and advances with `++`.
:::

The class provides `begin()`/`end()` for forward iteration and `rbegin()`/`rend()` (of type `reverse_iterator`) for backward:

```cpp
string str = "today";

string::iterator it;
for (it = str.begin(); it != str.end(); it++)
    cout << *it;                  // today

string::reverse_iterator rit;
for (rit = str.rbegin(); rit != str.rend(); rit++)
    cout << *rit;                 // yadot  (reversed)
```

`*it` dereferences the iterator to the character it points at, exactly as with a pointer. Indexed traversal is equally valid and is handy when the position itself is needed — for example, upper-casing a string by subtracting 32 (the ASCII gap between lowercase and uppercase letters) from each lowercase character:

```cpp
string str = "WeLcOmE7";
for (int i = 0; str[i] != '\0'; i++)
{
    if (str[i] >= 97 && str[i] <= 122)   // only lowercase letters
        str[i] -= 32;
}
// str becomes "WELCOME7"
```

Guarding with the range check `97..122` (the ASCII codes of `'a'`..`'z'`) leaves digits and already-uppercase letters untouched.

Range-based `for` is the modern default when you do not need the index:

```cpp
std::string s = "abc";
for (char ch : s)
    std::cout << ch;

for (char& ch : s)   // mutable reference — can assign into the string
    ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
```

Note that the indexed loop above stops at `'\0'`. That works because `std::string` is null-terminated, but the idiomatic bounds are `i < s.size()` (or iterators / range-for). Embedded `'\0'` characters are allowed inside a `std::string` (`size()` counts them); a C-string style loop would stop early — another reason to prefer `size()`-based or iterator loops.

## Non-owning companion: `std::string_view`

A **`std::string_view`** (from `<string_view>`, C++17) is a non-owning view: a pointer and a length into someone else's character sequence. It is the preferred parameter type when a function only *reads* text and does not need to extend the lifetime or mutate storage:

```cpp
#include <string>
#include <string_view>

std::size_t len(std::string_view sv) {   // accepts string, literal, or substring view
    return sv.size();
}

std::string owned = "hello world";
std::string_view sv = owned;             // views owned; does not copy characters
std::string_view sub = sv.substr(0, 5);  // "hello" — still non-owning
```

`string_view` does **not** guarantee null-termination (so do not pass `sv.data()` to a C API expecting a C-string unless you know a `'\0'` follows). It also must not outlive the data it views. Full treatment — lifetime traps, APIs, and interplay with `std::string` — belongs in **`std::string_view`** (`s57`). Here it is enough to remember: own with `std::string`, borrow with `std::string_view`.

::: keypoint
Use `std::string` when you need ownership, mutation, or a guaranteed null-terminated buffer for C APIs. Use `std::string_view` (`s57`) when you only need to read an existing character sequence without copying.
:::
