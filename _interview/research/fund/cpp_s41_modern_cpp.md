# Modern C++ Essentials

Starting with C++11, the language underwent a massive evolution, introducing features that make C++ safer, faster, and more expressive. This section provides a tour of the essential "modern C++" features expected in any interview.

## Type deduction: `auto` and `decltype`

The **`auto`** keyword tells the compiler to deduce the type of a variable from its initialiser. This reduces boilerplate, especially with long typenames like iterators.

```cpp
auto i = 42;             // Deduced as int
auto d = 3.14;           // Deduced as double
auto str = "Hello";      // Deduced as const char*
```

By default, `auto` strips away references (`&`) and `const` qualifiers to make a completely independent copy. If you want a reference or a constant reference, you must ask for it explicitly using **`auto&`** or **`const auto&`**:

```cpp
const std::string name = "Alice";

auto val = name;           // std::string (a copy is made; const is dropped)
auto& ref = name;          // ERROR: drops const, tries to bind non-const reference to const data
const auto& cref = name;   // const std::string& (a read-only reference, no copy)
```

::: interview
A common interview question asks what `auto` deduces when assigned a `const` reference. The answer is that it deduces the base type and makes a copy, dropping both `const` and `&`. You must write `const auto&` to avoid copying.
:::

Modern C++ also introduces the **trailing return type** syntax, which is particularly useful when a function's return type depends on its arguments. It uses `auto` at the front and an arrow `->` at the back.

```cpp
// Trailing return type syntax
auto multiply(int a, double b) -> double {
    return a * b;
}
```

Alongside `auto`, the **`decltype`** keyword yields the exact type (including references and `const`) of a given expression without evaluating it, which is heavily used in template metaprogramming.

### `decltype(auto)` versus `auto` for returns

When a function (or lambda) returns with a deduced type, **`auto`** and **`decltype(auto)`** are not interchangeable. Plain `auto` applies the same rules as variable deduction: it drops references and top-level `const`/`volatile`. That is usually what you want for "return a copy", but it silently breaks **perfect return-type deduction** — which means preserving whether the expression was an lvalue reference, an rvalue reference, or a prvalue.

**`decltype(auto)`** (C++14) deduces the return type using `decltype` rules on the `return` expression, so references and value category are preserved:

```cpp
#include <string>

std::string g = "global";

auto by_value() {
    return g;              // auto → std::string (copy)
}

decltype(auto) by_ref() {
    return g;              // decltype(auto) → std::string& (refers to g)
}

decltype(auto) by_ref_safe() {
    return (g);            // parenthesised id-expression → lvalue → std::string&
}

template <typename Container>
decltype(auto) element_at(Container& c, std::size_t i) {
    return c[i];           // preserves whatever operator[] returns (often T&)
}
```

::: keypoint
Use `auto` when you intentionally want a value (a copy or a moved temporary). Use `decltype(auto)` when you are forwarding or returning an existing object and must not accidentally strip `&`. Returning a local variable with `decltype(auto)` still dangles if the deduced type is a reference — deduction preserves the form of the expression; it does not extend lifetimes.
:::

::: trap
`decltype(auto) f() { int x = 1; return x; }` deduces `int` (fine). But `decltype(auto) f() { int x = 1; return (x); }` deduces `int&` to a destroyed local — undefined behaviour. Prefer plain `auto` for locals unless you are deliberately returning a reference into a longer-lived object.
:::

## Range-based for loop

The **range-based for loop** simplifies iterating over arrays and containers, eliminating the need for index variables or explicit iterators. 

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // By value (makes a copy of each element)
    for (auto n : numbers) { std::cout << n << " "; }

    // By const reference (no copy, read-only - PREFERRED for objects)
    for (const auto& n : numbers) { std::cout << n << " "; }

    // By reference (allows modifying the elements in place)
    for (auto& n : numbers) { n *= 2; }
}
```

## Uniform initialisation and `std::initializer_list`

Historically, C++ had many ways to initialise variables (parentheses, equals signs, braces). Modern C++ introduces **uniform initialisation**, using curly braces `{}` for almost everything.

```cpp
int x{10};
std::string s{"Hello"};
int arr[]{1, 2, 3};
```

A major benefit of brace initialisation is that it prevents **narrowing conversions** — implicitly converting a value to a type that cannot fully represent it.

```cpp
int a = 3.14; // Compiles (truncates to 3)
int b{3.14};  // ERROR: narrowing conversion from double to int prevented
```

Under the hood, braced lists are often passed as a **`std::initializer_list`**, allowing containers to be initialised easily. However, this introduces a classic gotcha with `std::vector`:

```cpp
#include <vector>

std::vector<int> v1(5, 2); // Parentheses: calls constructor(size, value) -> [2, 2, 2, 2, 2]
std::vector<int> v2{5, 2}; // Braces: calls initializer_list constructor -> [5, 2]
```

## The `nullptr` keyword

Before C++11, pointers were nullified using `NULL` or `0`. However, `NULL` is typically just a macro for the integer `0`. This caused ambiguity in function overloading.

```cpp
void print(int x);
void print(char* p);

print(0);    // Calls print(int)
print(NULL); // Usually calls print(int) because NULL is 0, defying intent!
```

Modern C++ introduces **`nullptr`**, a type-safe null pointer constant. It implicitly converts to any pointer type, but never to an integer type.

```cpp
print(nullptr); // Unambiguously calls print(char*)
```

## Structured bindings

Introduced in C++17, **structured bindings** allow you to unpack a tuple, pair, or struct into separate, named variables in a single line.

```cpp
#include <map>
#include <string>
#include <iostream>

int main() {
    std::map<int, std::string> users = {{1, "Alice"}, {2, "Bob"}};

    // Unpacking the key-value pair directly
    for (const auto& [id, name] : users) {
        std::cout << "ID: " << id << ", Name: " << name << "\n";
    }
}
```

## Lambdas and `std::function`

A **lambda expression** is a convenient way to define an anonymous, inline function object. Lambdas are heavily used with algorithms like `std::sort`.

The full syntax is: `[captures](parameters) -> return_type { body }`

```cpp
auto add = [](int a, int b) -> int {
    return a + b;
};
```

The return type can usually be deduced by the compiler and omitted.

::: keypoint
In Python, you use `lambda x: x * 2` for simple anonymous functions. C++ lambdas serve the same purpose but are much more powerful, allowing multi-line bodies, explicit state capture, and mutable state.
:::

Under the hood, the compiler manufactures a unique unnamed **closure type** — a class with `operator()` and data members for every captured entity. Writing `auto f = [...](...) { ... };` stores an instance of that closure. Each lambda expression has a distinct type, even if two lambdas look identical.

::: definition
A **closure** is the compiler-generated function object produced by a lambda expression. Its call operator executes the lambda body; its data members hold any captured state.
:::

### Capturing variables

The `[ ]` capture clause allows a lambda to access variables from its surrounding scope.

- `[x, &y]`: Specific and mixed captures — capture `x` by value (read-only copy) and `y` by reference.
- `[=]`: Capture all used variables by value.
- `[&]`: Capture all used variables by reference.
- `[this]`: Capture the current object pointer (allowing access to member variables).

```cpp
int multiplier = 3;
int total = 0;

// Captures 'multiplier' by value, 'total' by reference
auto compute = [multiplier, &total](int x) {
    total += x * multiplier;
};
```

By default, variables captured by value are read-only. To modify a by-value capture within the lambda, you must mark it **`mutable`**:

```cpp
int counter = 0;
auto countUp = [counter]() mutable {
    return ++counter; // Modifies the internal copy of 'counter'
};
```

`mutable` does **not** change the original `counter` outside the lambda — only the closure's private copy. Without `mutable`, the call operator is `const` and assignment to a by-value capture is ill-formed.

Default captures can be combined with specifics. After `[=]` or `[&]`, you may override individual names:

```cpp
int a = 1, b = 2, c = 3;
auto f = [=, &c]() { /* a, b by value; c by reference */ };
auto g = [&, a]()  { /* everything by ref except a by value */ };
```

::: keypoint
Prefer **explicit** captures (`[x, &y]`) over default `[=]` / `[&]` in production code. Explicit lists document intent and make dangling-reference reviews far easier. Defaults are fine for short, immediately invoked lambdas.
:::

### Init-capture (generalised capture)

C++14 generalised the capture clause into **init-capture** (also called *generalised capture*): you can introduce a new named data member in the closure, initialised by an arbitrary expression. The syntax is `[identifier = expression]` or `[&identifier = expression]`.

This unlocks three patterns that classic C++11 captures cannot express cleanly.

**1. Computed captures** — store a derived value, not the original variable:

```cpp
int x = 10;
auto f = [n = x + 1]() {
    return n;   // n is an int member of the closure, initialised to 11
};
// Changing x later does not affect f's captured n
x = 99;
f();            // still returns 11
```

**2. Capture by move** — essential for move-only types such as `std::unique_ptr` or `std::future`, which cannot be copied into a C++11 by-value capture:

```cpp
#include <memory>
#include <utility>

auto ptr = std::make_unique<int>(42);
// auto bad = [ptr]() { return *ptr; };           // ERROR: unique_ptr is not copyable
auto good = [p = std::move(ptr)]() {
    return *p;                                    // p owns the unique_ptr inside the closure
};
// ptr is now empty (nullptr); ownership lives in the lambda
```

**3. Rename on capture** — give the closure member a clearer name than the outer variable:

```cpp
std::string name = "Alice";
auto greeter = [who = std::move(name)]() {
    return "Hello, " + who;
};
```

Init-capture can also bind a reference to an expression result with `[&r = expr]`, but that is rare and easy to get wrong if `expr` is a temporary. Prefer value init-captures unless you have a documented lifetime guarantee.

::: heavy
Dense subsection — init-capture, `this` / `*this`, and dangling captures are the interview-critical edges of lambdas. Read the next few headings slowly.
:::

### Capturing `this` versus `*this`

Inside a member function, naming a data member in a lambda does **not** capture that member directly. The language captures the object pointer **`this`**, and member access is rewritten as `this->member`.

```cpp
#include <string>
#include <iostream>

class Greeter {
    std::string prefix = "Hi";
public:
    auto make_printer() {
        // Equivalent forms: [this] or [=] (which implies capturing this by pointer)
        return [this]() {
            std::cout << prefix << "\n";   // really this->prefix
        };
    }
};
```

- **`[this]`** — captures the raw pointer. The lambda may read and write members. If the object is destroyed while the lambda still exists, every use is a **dangling `this`** — undefined behaviour.
- **`[=]`** in a member function also captures `this` by pointer (not a deep copy of the object). Do not assume `[=]` "snapshots" the whole object.
- **`[*this]`** (C++17) — captures a **by-value copy** of the current object into the closure. The lambda owns an independent instance; destroying the original object is safe. Useful when returning a lambda that must outlive `*this`, or when shipping work to another thread.

```cpp
class Worker {
    int id = 7;
public:
    auto make_safe_callback() {
        // Copy the Worker into the closure (C++17)
        return [*this]() {
            return id;   // uses the copy, not the original object
        };
    }

    auto make_dangerous_callback() {
        return [this]() {
            return id;   // uses this->id — dangles if *this is gone
        };
    }
};

auto cb = Worker{}.make_dangerous_callback();
// Temporary Worker is destroyed here → cb holds a dangling this
// cb();  // UNDEFINED BEHAVIOUR
```

You can mix `[*this]` with other captures: `[=, *this]` is ill-formed (redundant); prefer `[*this, x]` or `[this, x]` explicitly.

::: trap
Capturing a reference or `this` that outlives the lambda is one of the most common C++ lifetime bugs. A lambda stored in a container, returned from a factory, or posted to an async queue must not hold `&local`, a reference capture into a stack frame that has returned, or a bare `[this]` / `[=]` into an object that may be destroyed first. Prefer by-value captures, init-capture with `std::move`, or `[*this]` when the callable must outlive its creator.
:::

### Immediately-invoked lambdas (IIFE)

An **immediately-invoked function expression** (IIFE) is a lambda defined and called in the same expression: `[](...) { ... }(args)`. In C++ it is the cleanest way to initialise a **`const`** (or `constexpr`) object that needs multi-statement logic — something you cannot write as a single expression after `=`.

```cpp
#include <vector>
#include <string>

const std::vector<std::string> titles = [] {
    std::vector<std::string> v;
    v.reserve(3);
    v.push_back("Intro");
    v.push_back("Core");
    v.push_back("Advanced");
    return v;
}();  // trailing () invokes the lambda immediately

// Without IIFE you would need a mutable local, then assign — losing const
```

The pattern also works with captures when the initialisation depends on surrounding state:

```cpp
int scale = 4;
const int area = [scale] {
    int w = 10, h = 20;
    return w * h * scale;
}();
```

::: keypoint
Reach for an IIFE whenever you want `const` (immutability after construction) but the initialiser is too complex for a single expression. The temporary closure dies at the end of the full-expression; only the returned value lives on.
:::

### Capture-less lambdas and function pointers

A lambda with an **empty capture list** `[]` has no state. The language therefore allows an implicit conversion from that closure to a plain **function pointer** of matching signature:

```cpp
#include <cstdlib>

int (*fp)(int, int) = [](int a, int b) { return a + b; };

// Useful with C APIs that demand a function pointer
using Cmp = int(*)(const void*, const void*);
Cmp cmp = [](const void* a, const void* b) -> int {
    return *static_cast<const int*>(a) - *static_cast<const int*>(b);
};
std::qsort(/* ... */, cmp);
```

A lambda that captures **anything** — by value, by reference, `this`, or via init-capture — embeds state in the closure object. There is no single function-pointer type that could carry that state, so the conversion is **ill-formed**:

```cpp
int factor = 2;
// int (*bad)(int) = [factor](int x) { return x * factor; };  // ERROR: capturing lambda
auto ok = [factor](int x) { return x * factor; };              // keep as closure / std::function
```

The technical reason: a function pointer is just an address of code with a fixed ABI; a capturing closure is a class instance. Only the capture-less case can lower to "call this static-like `operator()` with no `this`/captures", which the conversion synthesises.

### Generic lambdas

Since C++14, lambdas can accept `auto` parameters, creating a **generic lambda** (essentially a templated function object).

```cpp
auto printAny = [](const auto& val) {
    std::cout << val << "\n";
};
printAny(42);
printAny("String");
```

Each call with a distinct argument type instantiates a distinct `operator()` overload (as if the call operator were a member function template). From C++20 you can also write explicit template parameters on the lambda (`[]<typename T>(T x) { ... }`), but the C++14 `auto`-parameter form is what interviews expect first.

### `constexpr` lambdas

Since C++17, a lambda's call operator is **`constexpr` if its body satisfies the usual `constexpr` rules** — you need not write the keyword on the lambda itself (though you may mark a variable `constexpr` that holds the result of an immediately invoked constexpr-capable lambda):

```cpp
constexpr int square = [](int n) { return n * n; }(5);  // OK in C++17: square == 25

constexpr auto add = [](int a, int b) { return a + b; };
static_assert(add(2, 3) == 5);
```

If the body performs a non-`constexpr` operation (I/O, heap allocation before C++20, virtual calls, and so on), the lambda is simply not usable in a constant-expression context — the same constraints as any `constexpr` function.

### Returning lambdas and deduced return types

Because every lambda has a unique unnamed type, a function that builds and returns a lambda must use **`auto`** (or a trailing return type naming a type-erasing wrapper such as `std::function`) as its return type — you cannot spell the closure type by hand.

```cpp
#include <functional>

// Return type deduced as the closure type (efficient: no type erasure)
auto make_adder(int n) {
    return [n](int x) { return x + n; };
}

auto add5 = make_adder(5);
int y = add5(10);   // 15

// When you need a named, stable type across TUs, erase with std::function
std::function<int(int)> make_adder_erased(int n) {
    return [n](int x) { return x + n; };
}
```

If the lambda itself uses a deduced return type and you need perfect forwarding of a reference out of the body, prefer **`decltype(auto)`** on the lambda's trailing return (or on the enclosing function) rather than plain `auto`, for the same reasons as in the type-deduction section above:

```cpp
std::vector<int> data = {1, 2, 3};

auto get_ref = [&data](std::size_t i) -> decltype(auto) {
    return data[i];   // returns int&, not a copy
};
get_ref(0) = 99;      // modifies data[0]
```

Returning a lambda that captured locals by reference remains undefined behaviour once those locals die — `auto` on the enclosing function does not extend their lifetime.

### Storing lambdas

While you can store a lambda in an `auto` variable, sometimes you need to store it in a struct or pass it across boundaries where the type must be explicit. For this, include `<functional>` and use **`std::function`**, which can store any callable target (functions, lambdas, functors) matching a specific signature.

```cpp
#include <functional>

// Stores any callable that takes an int and returns a bool
std::function<bool(int)> isEven = [](int n) { return n % 2 == 0; };
```

`std::function` performs **type erasure**: it can hold any matching callable, at the cost of a possible heap allocation and an indirect call. Prefer `auto` (or a function template parameter) when you do not need a single concrete type.

::: trap
Capturing local variables by reference `[&]` in a lambda that is returned from a function or stored for later execution will create a dangling reference. The referent will be destroyed before the lambda is executed.
:::

::: interview
Expect to be asked how lambdas capture state. Explain the difference between `[=]` (value/copy) and `[&]` (reference), and highlight the dangling reference risk if a lambda outlives its enclosing scope.
:::

::: interview
What can a lambda capture, and how? Name by-value, by-reference, init-capture (including `[p = std::move(ptr)]` and `[n = x + 1]`), `[this]`, and C++17 `[*this]`. When does a lambda convert to a function pointer? Only a capture-less lambda (`[]`) converts implicitly to a matching function pointer; any capture makes that conversion impossible because the closure carries state a bare function address cannot hold.
:::

::: heavy
The following section covers smart pointers, which fundamentally change how memory is managed in C++. 
:::

## Smart pointers and RAII

As explored in earlier sections on destructors and memory management (s24/s35), manual memory management using `new` and `delete` is perilous. Modern C++ solves this by codifying RAII (Resource Acquisition Is Initialization) into standard library **smart pointers**, defined in `<memory>`.

The golden rule of modern C++ is: **prefer smart pointers over raw `new` and `delete`**. 

![`unique_ptr` has a single owner, `shared_ptr` shares ownership via a reference count, `weak_ptr` only observes.](assets/s41_smart_ptr_ownership.png)

::: keypoint
In Python, memory is garbage-collected, and file/resource cleanup is often handled via the `with` statement (context managers). In C++, smart pointers use RAII to guarantee deterministic cleanup exactly when the object goes out of scope, achieving both memory and resource safety automatically.
:::

### 1. `std::unique_ptr` (Exclusive ownership)

Think of a `std::unique_ptr` as a strictly personal vault. Only one person holds the key at any time; if you want to give the contents to someone else, you must hand over the key entirely, losing access yourself.

```cpp
#include <memory>
#include <iostream>

class Widget {
public:
    Widget() { std::cout << "Widget created\n"; }
    ~Widget() { std::cout << "Widget destroyed\n"; }
    void doWork() { std::cout << "Working...\n"; }
};

int main() {
    {
        // std::make_unique safely allocates and constructs the object
        std::unique_ptr<Widget> p1 = std::make_unique<Widget>();
        p1->doWork();
        
        // std::unique_ptr<Widget> p2 = p1; // ERROR: Cannot copy!
        
        std::unique_ptr<Widget> p3 = std::move(p1); // OK: Ownership transferred
        // p1 is now null. p3 owns the Widget.
    } 
    // p3 goes out of scope; Widget is automatically destroyed here.
}
```

The plain-English rule is: use a **`std::unique_ptr`** when you want an object to belong to exactly one owner. When that owner goes out of scope, the underlying memory is cleaned up automatically.

Technically, a `unique_ptr` enforces exclusive ownership by deleting its copy constructor and copy assignment operator (making it **non-copyable**). However, it defines move semantics, meaning it is **movable** — ownership can be explicitly transferred using `std::move()`.

You can also provide a custom deleter to a `unique_ptr`, which is useful for wrapping raw operating system resources in a single line:
```cpp
std::unique_ptr<FILE, decltype(&fclose)> file(fopen("data.txt", "r"), &fclose);
```

### 2. `std::shared_ptr` (Shared ownership)

Think of a `std::shared_ptr` as a library book with a sign-out sheet. As long as at least one person is currently reading it, the library will not discard it. When the very last reader returns it, it is thrown away.

```cpp
#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> p1 = std::make_shared<int>(100);
    std::cout << "Count: " << p1.use_count() << "\n"; // Outputs 1
    
    {
        std::shared_ptr<int> p2 = p1; // Shared ownership
        std::cout << "Count: " << p1.use_count() << "\n"; // Outputs 2
    } // p2 goes out of scope; count drops to 1
    
    std::cout << "Count: " << p1.use_count() << "\n"; // Outputs 1
} // p1 goes out of scope; count drops to 0, memory is deleted
```

The plain-English rule is: a **`std::shared_ptr`** allows multiple pointers to own the same resource simultaneously. The resource is destroyed only when the last `shared_ptr` observing it is destroyed.

Technically, `shared_ptr` achieves this by maintaining a hidden heap-allocated **reference count**. Copying the pointer increments the count; destroying a pointer decrements it. Always prefer **`std::make_shared`** over passing a raw pointer to a constructor, because `make_shared` allocates the object and the reference counter in a single contiguous block of memory, improving cache locality and ensuring exception safety.

### 3. `std::weak_ptr` (Breaking cycles)

Think of a `std::weak_ptr` as a person peering through the library window to see if the book is still there. They can look at it, but their presence does not prevent the library from throwing the book away.

```cpp
#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> shared = std::make_shared<int>(42);
    std::weak_ptr<int> weak = shared; // Observes, but does not own
    
    // Attempt to access the data
    if (std::shared_ptr<int> temp = weak.lock()) {
        std::cout << "Value is " << *temp << "\n";
    } else {
        std::cout << "Memory has been freed.\n";
    }
}
```

The plain-English rule is: a **`std::weak_ptr`** observes a `shared_ptr` without keeping the resource alive. To actually use the resource, you must temporarily upgrade it to a `shared_ptr` using **`lock()`**.

Technically, a `weak_ptr` increments a separate "weak count" rather than the main reference count. This is primarily used to break a **reference cycle**.

::: trap
If two objects hold `std::shared_ptr`s pointing to each other, they create a cyclical dependency. Their reference counts will never drop to zero, resulting in a permanent memory leak. Use `weak_ptr` for one half of the relationship to break the cycle.
:::

::: interview
A classic interview question asks you to compare `unique_ptr`, `shared_ptr`, and `weak_ptr`. Be ready to explain exclusive vs shared ownership, reference counting mechanics, why `make_shared` is preferred, and how `weak_ptr` resolves cyclical reference leaks.
:::

## Other modern features

Several modern C++ features have been detailed in earlier sections, but are worth briefly recalling here as integral parts of the modern C++ toolset:
- **`override` and `final`**: Explicit specifiers that prevent silent bugs in virtual function hierarchies by enforcing strict override signatures and inheritance limits.
- **`constexpr`**: A keyword instructing the compiler to evaluate a function or variable entirely at compile time, yielding significant run-time performance gains.
