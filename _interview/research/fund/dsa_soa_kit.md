# The OA Survival Kit — From LeetCode Logic to Real OA Harnesses

::: heavy
LeetCode hands you a method (`class Solution { int solve(vector<int>& a){...} }`) — the platform reads the input, manages memory, and calls your function. Real Online Assessments (OAs from companies like Cisco, Amazon, and D. E. Shaw) are often vastly different. They may hand you a complete **`main` function that reads from standard input (`stdin`)**, a provided **`struct` or parser**, and a fixed empty function signature to fill. Alternatively, they might just give you a completely empty file where **you** must read `stdin` and print to `stdout` yourself. The *algorithm* is usually easy; the **wrapping** (parsing the raw text and formatting the exact expected output) is the wall that makes an otherwise easy problem unsolvable under time pressure.
:::

::: keypoint
There are three main OA harness styles you will encounter:
1. **Function-stub:** The platform handles all I/O, and you just fill a function (common on HackerRank, Codility, CodeSignal).
2. **Provided full harness:** You are given a `struct` definition, a `parse_input` function, a `format_output` function, and a `solve` function that you must complete without touching the rest (the Cisco style).
3. **Bare `main`:** You are given an empty file and must read standard input and format output yourself (the competitive programming style).
:::

### Reading custom input — the #1 skill

::: heavy
Mastering `cin` and standard input streams is the single most important mechanical skill for OAs. The idioms below are the building blocks. You must be able to write these from muscle memory without bugs.
:::

### `cin >>` basics
The standard extraction operator `>>` reads whitespace-delimited tokens. It automatically skips leading spaces, tabs, and newlines. It reads directly into your typed variables (`int`, `long long`, `double`, `string`). When reading into a `string`, `>>` stops at the very first whitespace character.

**Input:**
```
  42 
3.1415
   hello_world
```

**C++ Snippet:**
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    int i;
    double d;
    string s;
    
    if (cin >> i >> d >> s) {
        // i = 42, d = 3.1415, s = "hello_world"
        cout << "Parsed: " << i << " " << d << " " << s << "\n";
    }
    return 0;
}
```

### Read N then N numbers into a vector
A very common format: the first token `N` dictates the size of the array, followed by `N` integers.

**Input:**
```
5
10 20 30 40 50
```

**C++ Snippet:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cout << "Read array of size " << arr.size() << "\n";
    }
    return 0;
}
```

### Read an R×C grid/matrix
Often seen in grid traversal problems (like the Cisco drone grid). You read the number of rows `R` and columns `C`, followed by the matrix elements.

**Input:**
```
2 3
1 2 3
4 5 6
```

**C++ Snippet:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int r, c;
    if (cin >> r >> c) {
        vector<vector<int>> grid(r, vector<int>(c));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> grid[i][j];
            }
        }
        cout << "Read a " << r << "x" << c << " grid\n";
    }
    return 0;
}
```

### Read a graph (adjacency list)
You are given `N` vertices and `M` edges. The next `M` lines define the edges. This idiom populates an adjacency list represented by a `vector<vector<int>>`.

**Input:**
```
4 4
0 1
1 2
2 3
3 0
```

**C++ Snippet:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    if (cin >> n >> m) {
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            // For an undirected graph, add the edge in both directions
            adj[u].push_back(v);
            adj[v].push_back(u); 
        }
        cout << "Graph parsed with " << adj.size() << " nodes\n";
    }
    return 0;
}
```

### Read T test cases
The outer loop pattern. The first line is `T` (the number of test cases), followed by `T` separate problem instances.

**Input:**
```
2
3
1 2 3
2
10 20
```

**C++ Snippet:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << "Processed array of size " << n << "\n";
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
```

### Read until EOF
Sometimes, the input size is not specified at all. You just read continuously until the file ends (EOF). This works because `cin >> x` returns a reference to the stream, which implicitly evaluates to `false` when reading fails or EOF is reached.

**Input:**
```
1 2 3 4 5
6 7 8
```

**C++ Snippet:**
```cpp
#include <iostream>

using namespace std;

int main() {
    int x;
    int sum = 0;
    while (cin >> x) {
        sum += x;
    }
    cout << "Total sum: " << sum << "\n";
    return 0;
}
```

### Read entire lines and tokenizing with `stringstream`
When you need to read an entire line (including spaces) into a single string, use `getline(cin, string_var)`. If that line contains multiple elements (like comma-separated values), you can pass it to a `stringstream` to split it up.

**Input:**
```
apple banana orange
10,20,30,40
```

**C++ Snippet:**
```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    string words_line;
    if (getline(cin, words_line)) {
        stringstream ss(words_line);
        string token;
        while (ss >> token) {
            cout << "Token: " << token << "\n";
        }
    }

    string csv_line;
    if (getline(cin, csv_line)) {
        stringstream ss(csv_line);
        string token;
        vector<int> values;
        // The third parameter to getline acts as a delimiter
        while (getline(ss, token, ',')) {
            values.push_back(stoi(token));
        }
        cout << "Parsed " << values.size() << " CSV numbers\n";
    }
    return 0;
}
```

::: trap
The classic `cin >> x` then `getline` bug: `cin >> n` extracts the integer but leaves the trailing newline character `\n` sitting in the input stream. If you immediately call `getline`, it sees the leftover `\n`, assumes it just read an empty line, and halts. You must flush the buffer using `cin.ignore()`.
:::

**Broken approach:**
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    int id;
    string name;
    
    // If input is:
    // 42
    // John Doe
    cin >> id; 
    getline(cin, name); 
    
    // BAD: 'name' is now empty because it consumed the newline after 42!
    return 0;
}
```

**Fixed approach:**
```cpp
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
    int id;
    string name;
    
    cin >> id;
    
    // FIX: ignore characters up to and including the newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    getline(cin, name); 
    // GOOD: 'name' is now "John Doe"
    return 0;
}
```

### Fast & correct I/O

### Fast I/O desync (`ios_base::sync_with_stdio`)
By default, C++ syncs its `iostream` (`cin`/`cout`) with the C standard library (`stdio` like `scanf`/`printf`) so you can mix them safely. It also ties `cin` to `cout` so that output flushes automatically before input. Both guarantees are terribly slow. Disabling them massively speeds up parsing.

**C++ Snippet:**
```cpp
#include <iostream>

using namespace std;

int main() {
    // Disable synchronization with C I/O
    ios_base::sync_with_stdio(false);
    
    // Untie cin from cout
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        cout << "Read " << n << "\n";
    }
    return 0;
}
```

::: trap
Once you add `ios_base::sync_with_stdio(false);`, **never mix** C-style `scanf`/`printf` with C++ `cin`/`cout`. The input and output buffers are independent, and mixing them will result in jumbled, interleaved outputs and incorrect parsing.
:::

### The `\n` vs `endl` trap
Using `std::endl` does two things: it inserts a newline, and it **flushes the output buffer**. Flushing forces the OS to write to the console/file immediately, which is an extremely expensive operation. In a loop of 100,000 iterations, `endl` can cause a Time Limit Exceeded (TLE) error all on its own. Prefer `"\n"`.

**C++ Snippet:**
```cpp
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // SLOW: Inserts newline AND flushes the stream
    cout << "Line 1" << endl; 

    // FAST: Just inserts newline
    cout << "Line 2\n";

    return 0;
}
```

### Large output optimization (String/`fwrite`)
For massive outputs (like the Cisco online auction sniper problem), you should avoid calling `cout` hundreds of thousands of times. Instead, pre-build a large `string` and print it all at once using C-style fast I/O functions like `fputs` or `fwrite`.

**C++ Snippet:**
```cpp
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main() {
    string out_buffer;
    out_buffer.reserve(100000); // Reserve memory to prevent reallocation

    for (int i = 1; i <= 5; ++i) {
        out_buffer += to_string(i) + " ";
    }
    out_buffer += "\n";

    // Fast C-style output bypasses C++ streams entirely
    fputs(out_buffer.c_str(), stdout);

    return 0;
}
```

### The competitive I/O template
Paste this boilerplate at the top of any bare `main` OA file. It ensures the environment reads and writes as fast as physically possible.

**C++ Snippet:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    // Your logic goes here
}

int main() {
    // 1. Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // 2. Main loop (if T test cases exist)
    int t = 1; 
    // cin >> t; // uncomment if the problem provides T
    while (t--) {
        solve();
    }

    return 0;
}
```

## Anatomy of a Provided Harness

In many enterprise Online Assessments (OAs), candidates are not asked to write code completely from scratch. Instead, they are presented with a **provided harness** right in the code editor. This harness handles all input reading and output formatting, leaving you to focus solely on the algorithmic logic.

Let's reproduce and dissect the provided harness for the **Cisco "Drone Delivery"** problem, first in C++ and then in C.

### The C++ Harness

Here is the exact boilerplate provided for the C++ version of the Drone Delivery problem:

```cpp
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct InputData {
    int rows;
    int cols;
    vector<vector<int>> grid;
    int sr, sc;
    int er, ec;
    int B;
    int M;
    vector<pair<int, int>> stations;
    int K;
};

static bool parse_input(InputData &D) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> D.rows >> D.cols)) return false;
    D.grid.assign(D.rows, vector<int>(D.cols, 0));
    for (int r = 0; r < D.rows; ++r)
        for (int c = 0; c < D.cols; ++c) cin >> D.grid[r][c];
    cin >> D.sr >> D.sc >> D.er >> D.ec >> D.B >> D.M;
    D.stations.assign(D.M, make_pair(0, 0));
    for (int i = 0; i < D.M; ++i) cin >> D.stations[i].first >> D.stations[i].second;
    cin >> D.K;
    return true;
}

static void format_output(int result) {
    // Single integer: the minimum number of moves, or -1 if infeasible.
    cout << result << "\n";
}

static int solve(const InputData &D) {
    // TODO: compute and return the minimum number of moves (or -1).
    (void)D;
    return -1;
}

int main() {
    InputData D;
    if (!parse_input(D)) return 0;
    format_output(solve(D));
    return 0;
}
```

This harness breaks down into five distinct pieces:

1. **`struct InputData`**: This bundles all the inputs the problem gives you into one neatly packaged object.
2. **`parse_input`**: This function reads the raw text from standard input (`cin`), instantiates the vectors, and populates the `InputData` struct in the exact order the problem specifies.
3. **`format_output`**: This function takes the final answer and prints it out exactly as the autograder expects.
4. **`main`**: The entry point. It creates an empty `InputData D`, passes it to `parse_input` to be filled, hands it to `solve`, and then feeds the result to `format_output`.
5. **`solve`**: This is the only part that matters to you. It takes a populated `InputData` object and must return an `int`.

::: keypoint
Read the struct fields — they tell you exactly what the input contains and often hint the algorithm (separate `B` and `K` fields in the Drone problem imply you need state search).
:::

**The Golden Rule:** You edit only `solve`; never touch `main`, `parse_input`, `format_output`, the struct, or the function signatures. Altering them will instantly break the hidden test runner.

### The C Harness

The C version of the same harness lacks C++'s automatic memory management and container types, exposing raw pointers:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows, cols;
    int **grid;            /* 0 = open, 1 = wall */
    int sr, sc;
    int er, ec;
    int B;
    int M;
    int (*stations)[2];    /* M kiosk coordinates */
    int K;
} InputData;

static int parse_input(InputData *D) {
    if (scanf("%d %d", &D->rows, &D->cols) != 2) return 0;
    D->grid = (int **)malloc(sizeof(int *) * (size_t)D->rows);
    for (int r = 0; r < D->rows; ++r) {
        D->grid[r] = (int *)malloc(sizeof(int) * (size_t)D->cols);
        for (int c = 0; c < D->cols; ++c) scanf("%d", &D->grid[r][c]);
    }
    scanf("%d %d", &D->sr, &D->sc);
    scanf("%d %d", &D->er, &D->ec);
    scanf("%d", &D->B);
    scanf("%d", &D->M);
    D->stations = (int (*)[2])malloc(sizeof(int[2]) * (size_t)D->M);
    for (int i = 0; i < D->M; ++i)
        scanf("%d %d", &D->stations[i][0], &D->stations[i][1]);
    scanf("%d", &D->K);
    return 1;
}

static void format_output(int result) {
    printf("%d\n", result);
}

static int solve(const InputData *D) {
    /* TODO: compute and return the minimum number of moves (or -1). */
    (void)D;
    return -1;
}

int main(void) {
    InputData D;
    if (!parse_input(&D)) return 0;
    int result = solve(&D);
    format_output(result);
    for (int r = 0; r < D.rows; ++r) free(D.grid[r]);
    free(D.grid);
    free(D.stations);
    return 0;
}
```

The core structure is identical, but `parse_input` uses `malloc` to dynamically allocate arrays for the `grid` and `stations`, and `main` carefully cleans them up with `free` at the end. You still only edit `solve`.

### The Sniper Harness: Return Values vs Out-Parameters

In the **Online Auction Sniper Detector** problem, the solution must yield multiple values for each input element. 

In **C++**, the `solve` function returns a compound type — a vector of pairs:

```cpp
static vector<pair<int, long long>> solve(const InputData &D) {
    // Return a vector of answers
    return vector<pair<int, long long>>(D.N, make_pair(0, (long long)-1));
}
```

In **C**, because there are no dynamic vectors or tuples, the caller (`main`) pre-allocates arrays for the answers and passes them as pointers. The `solve` function returns `void` and must fill those arrays. These are called **out-parameters**:

```c
static void solve(const InputData *D, int *flags, long long *smallest) {
    for (int i = 0; i < D->N; ++i) { 
        flags[i] = 0; 
        smallest[i] = -1; 
    }
}
```

## Syntax deep-dives — every token in the harness, explained fully

The harness boilerplate uses specific C and C++ idioms. If you only know the basics, these can look daunting. Here is an exhaustive breakdown of every token used.

### `#include <...>`

The `#include` directive pastes the contents of a header file into your program. 

**Meaning 1: Angle brackets `<...>`**
Includes standard library headers or system headers. The compiler searches its default system directories.
```cpp
#include <iostream>
int main() { std::cout << "Hello\n"; return 0; }
```

**Meaning 2: Quotes `"..."`**
Includes local headers you wrote. The compiler searches the current directory first.
```cpp
// #include "my_header.h"
int main() { return 0; }
```

In the harness it means: pulling in standard tools. `<iostream>` gives streams, `<vector>` gives dynamic arrays, `<cstdio>` gives `scanf`/`printf`, `<cstdlib>` gives memory functions, `<utility>` gives `pair`, `<unordered_map>` gives hash maps, and `<set>` gives ordered sets.

### `using namespace std;`

A namespace is a named scope that prevents name collisions. The standard library puts all its features inside the `std` namespace.

**Meaning 1: Explicit prefixing**
Production code avoids `using` directives to prevent naming conflicts, explicitly typing `std::`.
```cpp
#include <iostream>
int main() { std::cout << "Hello\n"; return 0; }
```

**Meaning 2: `using namespace std;` directive**
Brings everything from `std` into the global scope. Standard in competitive programming to save typing.
```cpp
#include <iostream>
using namespace std;
int main() { cout << "Hello\n"; return 0; }
```

**Meaning 3: Type aliasing (`using` / `typedef`)**
Creates a new name for an existing type. `using` is the modern syntax, `typedef` is the older C-style syntax.
```cpp
using ll = long long;
typedef long long ll_old;
int main() { ll x = 5; ll_old y = 5; return 0; }
```

In the harness it means: dropping the `std::` prefix so `std::vector` becomes just `vector`, and (in the sniper harness) creating an alias `ll` for `long long`.

### `static`

The `static` keyword in C++ is notoriously overloaded and has four entirely distinct meanings.

**Meaning 1: `static` local variable**
A variable inside a function that initializes only once and retains its value across multiple calls.
```cpp
#include <iostream>
void count() {
    static int x = 0;
    std::cout << ++x << " ";
}
int main() { count(); count(); return 0; } // Outputs: 1 2
```

**Meaning 2: `static` at file or namespace scope (Internal Linkage)**
Restricts the visibility of a variable or function to the current file only. It prevents naming collisions if another file has a function with the exact same name.
```cpp
static int helper(int x) { return x * 2; }
int main() { return helper(5); }
```

**Meaning 3: `static` data member in a class/struct**
A variable shared by all instances of a class, rather than each instance having its own copy.
```cpp
struct Dog { static int total_dogs; };
int Dog::total_dogs = 0;
int main() { Dog::total_dogs++; return 0; }
```

**Meaning 4: `static` member function**
A class function that can be called without an instance (no `this` pointer), usually to operate on static data members.
```cpp
struct Math {
    static int add(int a, int b) { return a + b; }
};
int main() { return Math::add(2, 3); }
```

In the harness, `static bool parse_input(...)` uses meaning 2: internal linkage so the symbol stays local to this file.

### `struct` vs `class`

They are identical concepts in C++ used to bundle data and functions together, with one minor difference.

**Meaning 1: `class`**
Members are `private` by default (hidden from outside code).
```cpp
class Person {
    int age; // private
public:
    void set_age(int a) { age = a; }
};
int main() { Person p; p.set_age(20); return 0; }
```

**Meaning 2: `struct`**
Members are `public` by default. Used for simple data containers.
```cpp
struct Point {
    int x, y; // public
};
int main() { Point p; p.x = 5; return 0; }
```

In the harness it means: defining a public data container (`struct InputData`) to hold the parsed input, and creating an instance with `InputData D;`.

### references vs pointers

Both let you refer to memory without copying it, but with different syntax and rules.

**Meaning 1: References (`T&` and `const T&`)**
An alias for an existing variable. It cannot be null and cannot be reseated to point to something else. Uses `.` for accessing members. A `const T&` is a read-only alias, heavily used to avoid expensive copies.
```cpp
void by_ref(int &x) { x = 10; }
int main() { int a = 5; by_ref(a); return 0; } // a becomes 10
```

**Meaning 2: Pointers (`T*`)**
A variable holding a memory address. It can be null, and you must dereference it with `*` (or `->` for members). You pass an address with the address-of operator `&`.
```cpp
struct Node { int val; };
void by_ptr(Node *n) { n->val = 10; }
int main() { Node n; by_ptr(&n); return 0; }
```

**Comparing passing conventions:**
```cpp
struct Node { int val; };
void by_value(Node n) { n.val = 1; }
void by_ref(Node &n) { n.val = 2; }
void by_ptr(Node *n) { n->val = 3; }
int main() {
    Node n{0};
    by_value(n);   // Caller passes n. n.val remains 0 (copied).
    by_ref(n);     // Caller passes n. n.val becomes 2.
    by_ptr(&n);    // Caller passes &n (address). n.val becomes 3.
    return 0;
}
```

In the harness it means: `parse_input(InputData &D)` takes a reference so it can mutate the original `D` object. The C harness uses pointers `parse_input(InputData *D)` and `D->rows`.

### `const`

The `const` keyword promises that a value will not be modified.

**Meaning 1: `const` variable**
A variable that cannot be reassigned after initialization.
```cpp
int main() { const int x = 5; return 0; }
```

**Meaning 2: `const` reference (`const T&`)**
Passes a parameter efficiently (no copy) while guaranteeing the function won't change it (const-correctness).
```cpp
#include <vector>
int sum(const std::vector<int> &v) { return v[0]; }
int main() { std::vector<int> arr = {1}; sum(arr); return 0; }
```

**Meaning 3: `const` member function**
A class method that promises not to modify the object's state.
```cpp
struct Point {
    int x;
    int get_x() const { return x; }
};
int main() { Point p{5}; p.get_x(); return 0; }
```

In the harness it means: `solve(const InputData &D)` uses meaning 2, promising the solver won't accidentally modify the input struct while avoiding a massive data copy.

### `bool` and `return true;/false;`

`bool` represents boolean truth values, `true` or `false`.

**Meaning 1: Boolean logic and returns**
Functions returning `bool` indicate success/failure or yes/no.
```cpp
bool is_even(int x) { return x % 2 == 0; }
int main() { return is_even(4) ? 0 : 1; }
```

In the harness it means: `parse_input` returns `true` if reading the input succeeded. `if (!parse_input(D)) return 0;` reads smoothly as "if parsing the input fails, exit the program."

### `vector<T>`, `vector<vector<int>>`, `.assign`, `.resize`, `.push_back`, `v[i]`, `.size()`

`std::vector` is a dynamic array that grows as needed.

**Meaning 1: Creating, indexing, and sizing**
```cpp
#include <vector>
int main() {
    std::vector<int> v;
    v.assign(5, 0);       // sets size to 5, all elements 0
    v.resize(10);         // grows size to 10
    v.push_back(42);      // appends to the very end
    int val = v[0];       // indexing via v[i]
    size_t sz = v.size(); // returns element count (unsigned)
    return 0;
}
```

**Meaning 2: 2D Vectors**
A vector of vectors represents a matrix or grid.
```cpp
#include <vector>
int main() {
    std::vector<std::vector<int>> grid(3, std::vector<int>(4, 0));
    grid[0][0] = 1;
    return 0;
}
```

In the harness it means: declaring the `grid` and dynamically sizing it with `D.grid.assign(D.rows, vector<int>(D.cols, 0))` once the dimensions are read.

### `pair<A,B>`, `make_pair`, `.first`, `.second`

`std::pair` couples two values together into one object.

**Meaning 1: Creating and accessing pairs**
You access the elements via `.first` and `.second`.
```cpp
#include <utility>
int main() {
    std::pair<int, int> p = std::make_pair(1, 2);
    return p.first + p.second == 3 ? 0 : 1;
}
```

**Meaning 2: Vector of pairs**
Used heavily to represent coordinates, edges, or records.
```cpp
#include <vector>
#include <utility>
int main() {
    std::vector<std::pair<long long, long long>> bids;
    bids.push_back(std::make_pair(1000LL, 5LL));
    return 0;
}
```

In the harness it means: storing the kiosk coordinates in a `vector<pair<int, int>> stations;`, and returning the two answers per bid in the sniper problem as a `vector<pair<int, ll>>`.

### `cin >> a >> b;` and `cout << x << "\n";`

The standard input and output streams.

**Meaning 1: Reading input (`>>`)**
The `>>` operator extracts typed data from text, skipping whitespace. It returns the stream itself, allowing chaining.
```cpp
#include <iostream>
int main() {
    int a, b;
    if (std::cin >> a >> b) { } // reads two integers safely
    return 0;
}
```

**Meaning 2: Writing output (`<<`)**
The `<<` operator inserts data into the text stream.
```cpp
#include <iostream>
int main() {
    std::cout << 42 << "\n";
    return 0;
}
```

In the harness it means: reading the input fields sequentially and safely checking if the read succeeded via `if (!(cin >> D.rows >> D.cols)) return false;`.

### `ios_base::sync_with_stdio(false); cin.tie(nullptr);`

Covered above in Part 1. 

In the harness it means: disconnecting C++ streams from C streams and untying `cin` from `cout` for massive I/O performance gains.

### `scanf`/`printf` format specifiers

The C-style I/O functions use format strings to define how bytes are parsed into types.

**Meaning 1: `scanf` for reading**
Requires the address-of operator `&` on its targets so it knows exactly where in memory to write the parsed values.
```cpp
#include <cstdio>
int main() {
    int a; long long b;
    scanf("%d %lld", &a, &b);
    return 0;
}
```

**Meaning 2: `printf` for writing**
Prints values according to the format specifiers. You can also specify width and precision (like `%.2f` for two decimal places).
```cpp
#include <cstdio>
int main() {
    printf("%d %s\n", 5, "hello");
    return 0;
}
```

| Specifier | Type |
| :--- | :--- |
| `%d` | `int` |
| `%u` | `unsigned int` |
| `%ld` | `long` |
| `%lld` | `long long` |
| `%f` / `%lf` | `float` / `double` |
| `%c` | `char` |
| `%s` | `char*` (string) |

In the harness it means: `scanf("%d %lld %d", &D.N, &D.W, &D.K)` reads an integer, a long long, and an integer directly into the struct's fields.

### `malloc`/`free`/`sizeof`

C's manual dynamic memory allocation.

**Meaning 1: Allocating memory (`malloc`)**
`malloc` asks the OS for a raw block of bytes. It returns a generic `void*`, which must be cast to the proper pointer type. `sizeof` is required to request the correct number of bytes.
```c
#include <stdlib.h>
int main() {
    int *arr = (int*)malloc(sizeof(int) * 10);
    arr[0] = 42;
    free(arr);
    return 0;
}
```

**Meaning 2: Freeing memory (`free`)**
Every `malloc` must have exactly one matching `free` to return the memory and avoid leaks.
```c
#include <stdlib.h>
int main() {
    int *p = (int*)malloc(sizeof(int));
    free(p);
    return 0;
}
```

**Meaning 3: Pointers to arrays**
The type `int (*stations)[2]` is a pointer to an array of 2 integers, used to represent the coordinate pairs.
```c
#include <stdlib.h>
int main() {
    int (*stations)[2] = (int (*)[2])malloc(sizeof(int[2]) * 5);
    stations[0][0] = 1;
    free(stations);
    return 0;
}
```

In the harness it means: allocating the raw C-arrays for `grid` and `stations`. Contrast this with C++ `vector` where memory frees itself automatically.

::: trap
Forgetting to call `free` causes a memory leak. While OA graders rarely penalize leaks on short-lived programs, the C harness strictly includes it to demonstrate correct discipline.
:::

### `size_t`

The unsigned integer type used for representing sizes and memory byte counts.

**Meaning 1: Sizes and memory**
It is the return type of `sizeof` and `.size()`.
```cpp
#include <vector>
int main() {
    std::vector<int> v(5);
    size_t sz = v.size();
    return 0;
}
```

In the harness it means: casting loop bounds or counts to `size_t` inside `malloc` calls to ensure the byte calculation happens in unsigned math, averting signed integer overflow warnings during signed/unsigned comparisons.

### `(void)D;`

A compiler trick to manage unused variables.

**Meaning 1: Silencing unused parameter warnings**
If a parameter is unused, the compiler might warn you. Casting it to `void` does nothing at runtime, but tells the compiler "I know this is here, don't warn me."
```cpp
int solve(int x) {
    (void)x; // silence warning
    return 0;
}
int main() { return solve(5); }
```

In the harness it means: the placeholder `solve(const InputData &D)` hasn't used `D` yet, so `(void)D;` keeps the stub cleanly compiling without warnings. You delete this line when you write your solution.

### `to_string`, string `+=` concatenation, `fputs`/`fwrite`, `stdout`

Fast string operations.

**Meaning 1: Integer to String (`to_string`)**
```cpp
#include <string>
int main() { std::string s = std::to_string(42); return 0; }
```

**Meaning 2: Fast append (`+=`)**
```cpp
#include <string>
int main() { std::string s = "a"; s += "b"; return 0; }
```

**Meaning 3: Fast C-style output (`fputs` / `fwrite` to `stdout`)**
Printing a complete string buffer in one system call instead of many `printf` calls.
```cpp
#include <cstdio>
int main() { fputs("Hello\n", stdout); return 0; }
```

In the harness it means: the sniper problem outputs 200,000 lines. The harness builds one massive string buffer and dumps it with `fputs` to `stdout` for maximum performance, dodging the overhead of standard output streams.

### out-parameter arrays

A pattern in C where the caller allocates space, and the function fills it.

**Meaning 1: Passing arrays to be filled**
```c
void solve(int *flags, int n) {
    for (int i = 0; i < n; i++) flags[i] = 1;
}
int main() {
    int arr[5];
    solve(arr, 5);
    return 0;
}
```

In the harness it means: `void solve(const InputData* D, int* flags, long long* smallest)` gives you pointers to memory already created by `main`. You treat `flags` and `smallest` like standard arrays (`flags[i] = 1;`) and write the answers directly into them, which contrasts with returning a compound `vector` in C++.

### `%` modulo and integer division, `1LL`

Math boundaries and scaling.

**Meaning 1: Modulo (`%`)**
The remainder after integer division.
```cpp
int main() { int rem = 10 % 3; return rem == 1 ? 0 : 1; }
```

**Meaning 2: Integer division**
Truncates toward zero.
```cpp
int main() { int div = 10 / 3; return div == 3 ? 0 : 1; }
```

**Meaning 3: Forcing 64-bit literals (`1LL`)**
Appending `LL` forces an integer literal to be an 8-byte `long long`, preventing overflow in expressions.
```cpp
int main() { long long big = 1LL << 40; return 0; }
```

In the harness it means: `%` and `/` are used extensively to pack and unpack multi-dimensional states into a single integer. The `1LL` literal (or explicit `long long` types) is mandatory when IDs or timestamps reach $10^9$ to prevent integer overflow.

## Filling `solve()` — Two Real OA Problems, Start to Finish

Online Assessments often wrap straightforward logic problems in dense, confusing harnesses. The core challenge is stripping away the boilerplate to find the standard textbook algorithm hiding underneath. Let's walk through two real Cisco OA questions end-to-end.

### Cisco Drone Delivery (State-Augmented 0-1 BFS)

**The underlying problem:** Find the shortest path on a 2D grid from a start to an end cell. You have a limited battery capacity, and can use a limited number of vouchers to instantly recharge the battery at specific kiosk locations.

**The standard technique:** State-augmented 0-1 BFS (or Dijkstra's). Because the validity of a move depends on both your coordinates and your remaining resources (battery and vouchers), a standard BFS that only tracks `(row, col)` will fail. We augment the state to `(row, col, battery_left, vouchers_left)`. Moves to adjacent open cells cost 1 battery and 1 distance (weight 1), while recharging at a kiosk costs a voucher but 0 distance (weight 0). Exploring a graph where edge weights are 0 and 1 is the textbook use case for 0-1 BFS.

**The complete, compilable program:**

```cpp
#include <iostream>
#include <vector>
#include <utility>
#include <deque>
#include <climits>
#include <algorithm>

using namespace std;

struct InputData {
    int rows;
    int cols;
    vector<vector<int>> grid;
    int sr, sc;
    int er, ec;
    int B;
    int M;
    vector<pair<int, int>> stations;
    int K;
};

static bool parse_input(InputData &D) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> D.rows >> D.cols)) return false;
    D.grid.assign(D.rows, vector<int>(D.cols, 0));
    for (int r = 0; r < D.rows; ++r)
        for (int c = 0; c < D.cols; ++c) cin >> D.grid[r][c];
    cin >> D.sr >> D.sc >> D.er >> D.ec >> D.B >> D.M;
    D.stations.assign(D.M, make_pair(0, 0));
    for (int i = 0; i < D.M; ++i) cin >> D.stations[i].first >> D.stations[i].second;
    cin >> D.K;
    return true;
}

static void format_output(int result) {
    // Single integer: the minimum number of moves, or -1 if infeasible.
    cout << result << "\n";
}

static int solve(const InputData &D) {
    int R = D.rows, C = D.cols, B = D.B, K = D.K;
    vector<vector<char>> kiosk(R, vector<char>(C, 0));
    for (auto &s : D.stations) kiosk[s.first][s.second] = 1;

    // Flatten state (r,c,b,k) -> single index.
    auto id = [&](int r, int c, int b, int k) {
        return ((r * C + c) * (B + 1) + b) * (K + 1) + k;
    };
    vector<int> dist((size_t)R * C * (B + 1) * (K + 1), INT_MAX);
    deque<int> dq;
    int start = id(D.sr, D.sc, B, K);
    dist[start] = 0;
    dq.push_back(start);

    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        int k = u % (K + 1), t = u / (K + 1);
        int b = t % (B + 1); t /= (B + 1);
        int c = t % C, r = t / C;
        int d = dist[u];

        // 0-cost swap at a kiosk (only if it helps and a voucher remains).
        if (kiosk[r][c] && k > 0 && b < B) {
            int v = id(r, c, B, k - 1);
            if (d < dist[v]) { dist[v] = d; dq.push_front(v); }
        }
        // 1-cost moves into open neighbours (needs battery).
        if (b > 0) {
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir], nc = c + dc[dir];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (D.grid[nr][nc] != 0) continue;
                int v = id(nr, nc, b - 1, k);
                if (d + 1 < dist[v]) { dist[v] = d + 1; dq.push_back(v); }
            }
        }
    }

    int ans = INT_MAX;
    for (int b = 0; b <= B; ++b)
        for (int k = 0; k <= K; ++k)
            ans = min(ans, dist[id(D.er, D.ec, b, k)]);
    return ans == INT_MAX ? -1 : ans;
}

int main() {
    InputData D;
    if (!parse_input(D)) return 0;
    format_output(solve(D));
    return 0;
}
```

**Testing on an example:**
Consider a grid of `1x8`, start at `(0,0)`, end at `(0,7)`. Battery `B = 4`, 1 voucher (`K = 1`). Kiosks at `(0,1)` and `(0,4)`.
The drone starts at `(0,0)` with battery 4. It flies to `(0,4)` (4 moves, battery reaches 0). Since `(0,4)` is a kiosk, it uses its voucher to swap batteries (0 cost, battery jumps to 4). It then flies to `(0,7)` (3 moves).
Expected output: `7`.

The lesson here is that the algorithm itself is a first-week BFS variant. The friction lies in deciphering the 9-section input block, populating the exact `struct` the harness demands, and realizing the problem requires an augmented state rather than getting confused by the separation of the `B` and `K` fields.

### Cisco Sniper Detector (Sliding Window)

**The underlying problem:** Given a chronological sequence of bids `(timestamp, user_id)`, identify if the current bid puts the user at or above a threshold `K` bids within the last `W` seconds. Furthermore, return the smallest user ID that currently meets this condition.

**The standard technique:** Variable sliding window with a frequency map and an ordered set. We maintain a window `[t - W, t]` of active bids. A hash map tracks the frequency of each user's bids within the window. An ordered `set` keeps track of users currently meeting the threshold `K`, naturally keeping the smallest ID at the front.

**The complete, compilable program:**

```cpp
#include <cstdio>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <set>

using namespace std;
typedef long long ll;

struct InputData {
    int N;                        // number of bids
    ll  W;                        // window length (seconds)
    int K;                        // sniping threshold (bids per user)
    vector<pair<ll, ll>> bids;    // (timestamp, user_id), timestamps increasing
};

static bool parse_input(InputData &D) {
    if (scanf("%d %lld %d", &D.N, &D.W, &D.K) != 3) return false;
    D.bids.resize(D.N);
    for (int i = 0; i < D.N; ++i)
        scanf("%lld %lld", &D.bids[i].first, &D.bids[i].second);
    return true;
}

static void format_output(const vector<pair<int, ll>> &results) {
    // One line per bid: "<flag> <smallest_sniper>"
    string out;
    for (size_t i = 0; i < results.size(); ++i) {
        out += to_string(results[i].first);
        out += ' ';
        out += to_string(results[i].second);
        out += '\n';
    }
    fputs(out.c_str(), stdout);
}

static vector<pair<int, ll>> solve(const InputData &D) {
    vector<pair<int, ll>> res(D.N);
    unordered_map<ll, int> cnt;   // user id -> #bids currently in window
    set<ll> snipers;              // users with cnt >= K, ordered => smallest first
    int left = 0;
    for (int i = 0; i < D.N; ++i) {
        ll t = D.bids[i].first, u = D.bids[i].second;
        // add bid i
        if (++cnt[u] == D.K) snipers.insert(u);
        // evict bids that fell out of the window [t - W, t]
        while (t - D.bids[left].first > D.W) {
            ll ul = D.bids[left].second;
            if (--cnt[ul] == D.K - 1) snipers.erase(ul);
            ++left;
        }
        int flag = (cnt[u] >= D.K) ? 1 : 0;
        ll smallest = snipers.empty() ? -1 : *snipers.begin();
        res[i] = make_pair(flag, smallest);
    }
    return res;
}

int main() {
    InputData D;
    if (!parse_input(D)) return 0;
    format_output(solve(D));
    return 0;
}
```

**Testing on an example:**
Bids: `(0, 1)`, `(2, 1)`, `(3, 2)`, `(8, 1)`. Window `W = 10`, threshold `K = 3`.
At `t = 8`, user 1 has bids at 0, 2, and 8. The window `[8 - 10, 8]` covers them all. User 1 hits 3 bids, triggering the flag. Smallest sniper is 1. Output for this bid: `1 1`.

The lesson: the logic is textbook two-pointer counting. The traps are parsing large constraints (necessitating `long long` and a hash map over arrays), delivering the dual-output format per line, and correctly establishing the half-open vs closed window boundary (`t_i - t' <= W`).

::: interview
How to attack any OA coding question: (1) read the `struct` or function signature; (2) find the trivial logic hiding behind the jargon; (3) fill the stub without touching the boilerplate; (4) match the exact output format character-for-character (`-1` sentinels, newlines).
:::

## Templates you can paste into any OA

Give each as a labelled, compilable `cpp` block.

**Fast-I/O Header**
Use when: you are writing a bare `main()` and need to process large amounts of standard I/O rapidly.
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef long long ll;

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}
```

**Read `N` + Array, `R×C` Grid, `M`-Edge Graph, `T` Test Cases**
Use when: the input demands parsing arrays, grids, or graphs across multiple test cases.
```cpp
void read_structures() {
    int T; 
    if (!(cin >> T)) return;
    while (T--) {
        int N; cin >> N;
        vector<int> arr(N);
        for (int i = 0; i < N; ++i) cin >> arr[i];

        int R, C; cin >> R >> C;
        vector<vector<int>> grid(R, vector<int>(C));
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) cin >> grid[r][c];
        }

        int V, M; cin >> V >> M;
        vector<vector<int>> adj(V);
        for (int i = 0; i < M; ++i) {
            int u, v; cin >> u >> v;
            // Assumes 0-indexed undirected graph
            adj[u].push_back(v);
            adj[v].push_back(u); 
        }
    }
}
```

**Grid BFS (4-Neighbour) Template**
Use when: you need to find the shortest path in an unweighted 2D grid.
```cpp
#include <queue>
#include <vector>

using namespace std;

int grid_bfs(int R, int C, int sr, int sc, int er, int ec) {
    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int, int>> q;
    q.push({sr, sc});
    dist[sr][sc] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == er && c == ec) return dist[r][c];

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C && dist[nr][nc] == -1) {
                // Check if cell is traversable before pushing
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return -1;
}
```

**0-1 BFS / State-BFS Template**
Use when: edges have weights of 0 or 1, or you are searching an augmented state space.
```cpp
#include <deque>
#include <vector>

using namespace std;

int zero_one_bfs(int start_state, int end_state, int max_states) {
    vector<int> dist(max_states, 1e9);
    deque<int> dq;
    
    dist[start_state] = 0;
    dq.push_back(start_state);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        
        if (u == end_state) return dist[u];

        // Replace with actual neighbor iteration:
        int v = u + 1; // dummy next state
        int w = 0;     // dummy weight (0 or 1)
        
        if (v < max_states && dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            if (w == 0) dq.push_front(v);
            else dq.push_back(v);
        }
    }
    return -1;
}
```

**Sliding-Window (Variable) Template**
Use when: finding the optimal contiguous subarray that meets a dynamic condition.
```cpp
#include <vector>
#include <algorithm>

using namespace std;

int sliding_window(const vector<int>& arr) {
    int left = 0, max_len = 0;
    
    for (int right = 0; right < (int)arr.size(); ++right) {
        // 1. Add arr[right] to window state here
        
        // 2. Shrink window while invalid
        bool window_is_invalid = false; // replace with actual check
        while (window_is_invalid && left <= right) {
            // Remove arr[left] from window state here
            left++;
        }
        
        // 3. Process valid window
        max_len = max(max_len, right - left + 1);
    }
    return max_len;
}
```

**`unordered_map` + Ordered `set` Template**
Use when: tracking element frequencies while dynamically retrieving the absolute smallest/largest qualifying key.
```cpp
#include <unordered_map>
#include <set>

using namespace std;
typedef long long ll;

void freq_and_smallest_qualifying() {
    unordered_map<ll, int> counts;
    set<ll> qualified;
    int threshold = 3;

    // Add an item
    ll item_add = 5;
    if (++counts[item_add] == threshold) {
        qualified.insert(item_add);
    }

    // Remove an item
    ll item_remove = 5;
    if (--counts[item_remove] == threshold - 1) {
        qualified.erase(item_remove);
    }

    // Smallest qualifying item
    ll smallest = qualified.empty() ? -1 : *qualified.begin();
}
```

## Beyond coding: the rounds people forget to prepare

While competitive programming dominates the coding rounds, companies increasingly evaluate debugging skills, systems reasoning, and output-prediction nuances.

### Read-and-fix / debug-the-pseudocode

These rounds present a codebase that is structurally complete but failing edge cases. Your goal is to identify the root cause and apply a minimal fix.

**Example 1: The Non-Leaf Path Bug**
```cpp
struct Node { int value; Node *left = nullptr, *right = nullptr; };

bool hasPathSum(Node* node, int target) {
    if (!node) return false;
    if (node->value == target) return true; // BUG
    return hasPathSum(node->left, target - node->value) 
        || hasPathSum(node->right, target - node->value);
}
```
- **The Bug:** The success test (`node->value == target`) fires immediately when the remaining sum hits zero, without requiring that the current node is a leaf.
- **The Failing Condition:** The routine produces a wrong `true` when an internal (non-leaf) node's value equals the remaining target. It incorrectly accepts partial paths.
- **The Minimal Fix:** Explicitly test the leaf condition before comparing:
```cpp
    if (!node->left && !node->right) {
        return node->value == target;
    }
```

**Example 2: The Lost Tail in Merge**
```cpp
#include <vector>
using namespace std;

vector<int> merge_sorted(const vector<int>& A, const vector<int>& B) {
    vector<int> out; 
    size_t i = 0, j = 0;
    while (i < A.size() && j < B.size()) {
        if (A[i] <= B[j]) out.push_back(A[i++]);
        else              out.push_back(B[j++]);
    }
    while (i < A.size()) out.push_back(A[i++]); // BUG
    return out;
}
```
- **The Bug:** Following the main loop, only the leftover tail of array `A` is appended. The tail of `B` is silently dropped.
- **The Failing Condition:** The routine loses elements precisely when `B` still holds elements after the main loop finishes (which occurs when `A` is exhausted first).
- **The Minimal Fix:** Add the symmetric drain loop for `B`.
```cpp
    while (j < B.size()) out.push_back(B[j++]);
```

### Output-prediction MCQs

These questions assess language semantics and trick behaviors in C/C++.

**Recursion Stack Sequencing:**
```cpp
#include <iostream>
using namespace std;

void fun(int n) {
    if (n == 0) return;
    cout << n % 2;
    fun(n / 2);
}
```
`fun(25)` outputs `10011`. Since `cout` occurs *before* the recursive call, it prints the binary representation in reverse order (head recursion). 

**Integer Overflow / Type Promotion:**
```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned int a = 10;
    int b = -20;
    if (a + b > 10) cout << "Greater";
    else cout << "Lesser";
    return 0;
}
```
Outputs `Greater`. The signed integer `b` is implicitly promoted to an unsigned integer when operated alongside `a`. A negative number cast to unsigned becomes a massive positive number via two's complement.

**Pointer Arithmetic and Post-increment:**
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30};
    int *p = arr;
    cout << *p++ << " " << *p;
    return 0;
}
```
Outputs `10 20`. The post-increment operator (`++`) resolves its side-effect *after* the dereference (`*`), returning the value at the original pointer address (10) before advancing the pointer to the next element (20).

**Modulo with Negative Numbers:**
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = -5;
    int b = 3;
    cout << (a % b);
    return 0;
}
```
Outputs `-2`. Unlike Python which computes a strictly positive modulo, the `%` operator in C/C++ retains the sign of the dividend.

### Design / short-answer rounds

You are prompted to design a data structure for specific operational constraints and defend the memory/time trade-offs.

**Example: Time-Versioned Key-Value Store**
Design an in-memory store allowing `set(key, value, timestamp)` and `get(key, timestamp)`, returning the greatest timestamp version $\le$ the query timestamp.
- **The Choice:** Use a top-level `unordered_map` connecting keys to a `vector<pair<int, Value>>` sorted by timestamp. `set` is $O(1)$ amortized by appending. `get` utilizes binary search (`upper_bound` minus one) for $O(\log M)$ time.
- **The Edge Case:** If the query timestamp is earlier than the key's first stored timestamp, the predecessor search correctly yields nothing, rightfully returning a not-found sentinel rather than an invalid "earliest" value.

**Example: Two-Stack Queue vs. Ring Buffer**
You need a FIFO queue bounded to 1000 tasks.
- **The Comparison:** A ring buffer maintains an array with modulo arithmetic, ensuring true $O(1)$ worst-case enqueues and dequeues. A two-stack queue requires an $O(N)$ dump from the inbox to the outbox when the outbox is empty.
- **The Justification:** For latency-sensitive paths with tight deadlines, select the **Ring Buffer**. While the two-stack queue is $O(1)$ amortized, it periodically suffers catastrophic tail-latency spikes during its $O(N)$ inbox transfer, missing the deadline.

In addition to design questions, companies like Cisco seamlessly intermix **OS, Networking, and Aptitude MCQs** directly into the SDE OA. You are expected to answer why a TCP handshake operates at the Transport layer, or what triggers a Page Fault. Thorough practice sets for these domains live alongside this material.

## The same problem, five different wrappers

Knowing what scaffold you are facing instantly aligns your coding strategy. We can demonstrate this by wrapping the exact same trivial problem ("sum an array") in the three most common OA harness types.

**1. The Function-Stub (HackerRank, Codility, CodeSignal)**
You edit a single method. I/O is hidden; native C++ STL structures are passed perfectly.
```cpp
#include <vector>

class Solution {
public:
    long long sumArray(std::vector<int>& arr) {
        long long sum = 0;
        for (int x : arr) sum += x;
        return sum;
    }
};
```

**2. The Provided Full-Harness (Cisco, specialized portals)**
You are given `main()`, custom structs, and raw I/O parsing. You must strictly edit the body of a locked `solve()` signature.
```cpp
#include <vector>

struct Data { 
    std::vector<int> arr; 
};

void solve(const Data& D, long long& out_sum) {
    out_sum = 0;
    for (int x : D.arr) out_sum += x;
}
```

**3. Bare `main` (D.E. Shaw, manual HackerRank/competitive)**
You receive a blank text editor. You are responsible for reading directly from `std::cin` and writing to `std::cout`.
```cpp
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; 
    if (!(cin >> n)) return 0;
    
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        int val; cin >> val;
        sum += val;
    }
    
    cout << sum << "\n";
    return 0;
}
```

::: keypoint
Identify the wrapper type in your first 30 seconds. If it's a stub, focus purely on algorithmic logic. If it's bare `main`, paste your fast-I/O template immediately.
:::

## The 60-second OA harness checklist

1. **Identify the wrapper type.** Does it need manual `cin`/`cout` parsing, or is it a function stub?
2. **Read the exact input format.** Understand constraints, array dimensions, and data types (do you need `long long`?).
3. **Find the trivial logic.** Strip away the dense story to identify the core algorithm.
4. **Write `solve` / your code.** Keep it decoupled from the platform's parsing boilerplate.
5. **Match the output format byte-for-byte.** Pay explicit attention to requested sentinels (like `-1`) and newline characters.
6. **Test on the provided example.** Walk your code through the visible test case before hitting submit.
