# Gotchas, Undefined Behaviour, and Interview Craft

This capstone section brings together the critical edge cases and pitfalls of C++. In an interview, knowing the "happy path" proves you can write code; knowing the traps proves you can ship production software.

## The three categories of behaviour

The C++ standard classifies program behaviour that is not fully, rigidly defined into three precise categories.

::: definition
**Undefined behaviour (UB)** is the red zone. If your code triggers UB, the standard imposes no requirements on the compiler. The program may crash, output garbage, or appear to work normally.
:::

Crucially, **the optimiser is allowed to assume UB never happens**. If a code path contains UB, the compiler may legally delete that code path entirely during optimisation.

::: definition
**Unspecified behaviour** is when the standard permits two or more valid outcomes, and the compiler is not required to document which one it uses.
:::

A classic example is the evaluation order of function arguments.
```cpp
int f(int a, int b);
int i = 0;
// Unspecified whether i++ or ++i is evaluated first
f(i++, ++i); 
```

::: definition
**Implementation-defined behaviour** is behaviour that varies between compilers or platforms, but the compiler *must* choose one and document how it decides.
:::

For example, the size of an `int` or whether a `char` is signed or unsigned is implementation-defined.
```cpp
int x = sizeof(int); // Implementation-defined: could be 4 or 8 bytes
```

## Catalogue of classic undefined behaviour

This is a rapid-fire checklist of common UB. In an interview, instantly spotting these is a strong positive signal.

### Out-of-bounds access
Accessing an array or `std::vector` outside its allocated memory boundaries.
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int x = arr[5]; // UB: accessing the 6th element

#include <vector>
std::vector<int> v = {1, 2};
int y = v[2];   // UB: operator[] does not perform bounds checking
```
::: trap
For vectors, `v[i]` does not check bounds to maximise performance. Use `v.at(i)` if you want a guaranteed `std::out_of_range` exception on invalid access.
:::

### Dereferencing null or a dangling pointer
Dereferencing a pointer that is null, or points to memory that has already been deallocated.
```cpp
int* p = nullptr;
int val = *p; // UB: dereferencing null

int* q = new int(10);
delete q;
int val2 = *q; // UB: q is now a dangling pointer
```

### Use-after-free and double free
Attempting to free memory that has already been freed, or using an object after its lifetime has ended.
```cpp
int* p = new int(42);
delete p;
delete p; // UB: double free
```
::: trap
A double free typically corrupts the heap manager's internal data structures, leading to a crash much later in the program's execution, making it notoriously difficult to track down.
:::

### Reading an uninitialised variable
Reading from a primitive variable before assigning it a value yields indeterminate data, and reading it is UB.
```cpp
int x; 
int y = x + 5; // UB: reading uninitialised variable x
```

### Signed integer overflow
If a signed arithmetic operation overflows the maximum value the type can hold, it is UB. 
```cpp
#include <limits>
int max = std::numeric_limits<int>::max();
int overflow = max + 1; // UB: signed integer overflow
```
::: keypoint
Unsigned integer arithmetic is defined by the standard to wrap around using modulo arithmetic. Signed integer overflow is UB, and optimisers routinely exploit this to delete bounds checks.
:::

### Modifying a const object via const_cast
While `const_cast` can be used to cast away the constness of a reference or pointer, using it to *modify* an object that was originally declared `const` is UB.
```cpp
const int original = 10;
int* p = const_cast<int*>(&original);
*p = 20; // UB: modifying an inherently const object
```

### Invalid downcast via static_cast
Downcasting a base pointer to a derived pointer when the actual object is *not* of the derived type.
```cpp
class Base { public: virtual ~Base() = default; };
class Derived : public Base { public: void doSomething() {} };
class OtherDerived : public Base {};

Base* b = new OtherDerived();
// UB: b actually points to OtherDerived, not Derived
Derived* d = static_cast<Derived*>(b); 
d->doSomething(); 
```

### Data races
When two or more threads access the same memory location concurrently, at least one access is a write, and no synchronisation (like a mutex) is used.
```cpp
#include <thread>
int sharedCounter = 0;

// UB: concurrent unguarded writes
std::thread t1([&]{ sharedCounter++; });
std::thread t2([&]{ sharedCounter++; });

t1.join(); 
t2.join();
```

### Strict-aliasing violations
Accessing an object through a pointer of a different, incompatible type. The compiler assumes pointers of different types do not point to the same memory.
```cpp
float f = 3.14f;
// UB: treating a float as an int breaks strict aliasing
int* p = reinterpret_cast<int*>(&f);
int val = *p; 
```

### Returning a reference/pointer to a local
Returning an address of a local variable allocated on the stack. The variable is destroyed when the function returns.
```cpp
int& getLocalRef() {
    int x = 42;
    return x; // UB: returning reference to local variable
}
```
::: interview
If asked to review code, immediately check the return types. If a function returns a reference or pointer, trace exactly who owns the data being returned.
:::

## Catalogue of common C++ gotchas

A gotcha is not necessarily undefined behaviour; it is well-defined but extremely counter-intuitive behaviour that causes silent logical bugs.

### The most vexing parse
When a declaration is ambiguous between a variable instantiation and a function declaration, C++ will choose the function declaration.
```cpp
class Widget {
public:
    Widget() {}
};

// GOTCHA: This declares a function 'w' returning a Widget, taking no arguments!
Widget w();

// FIX: Remove parentheses or use uniform initialisation
Widget w1; 
Widget w2{}; 
```
::: trap
This often bites beginners trying to invoke a default constructor: `std::mutex m();` creates a function declaration, whereas `std::mutex m;` creates the lock.
:::

### Integer division truncation and mixed arithmetic
Dividing two integers truncates the fractional part. Furthermore, mixing signed and unsigned integers forces the signed integer to be converted to unsigned, which can lead to disastrous underflows.
```cpp
// GOTCHA: Integer division truncation
double result = 3 / 2; // result is 1.0, not 1.5

// FIX: Make at least one operand a floating-point type
double resultFixed = 3.0 / 2; // 1.5

// GOTCHA: Mixed signed/unsigned arithmetic
unsigned int u = 10;
int s = -20;
// -20 is converted to a massive unsigned value, yielding true!
bool isGreater = (u + s > 0); 
```
::: trap
Implicit conversions between signed and unsigned types are a leading cause of infinite loops in `for` loops counting downwards. Always compile with `-Wsign-compare`.
:::

### Floating-point equality
Due to precision limits, floats and doubles cannot be reliably compared with `==`.
```cpp
double a = 0.1 + 0.2;
double b = 0.3;
// GOTCHA: a == b is usually false!

// FIX: Compare the absolute difference against a small epsilon
#include <cmath>
bool isEqual = std::abs(a - b) < 0.00001;
```

### Dangling reference/pointer and dangling lambda captures
Creating a reference or pointer to data that is about to be destroyed is a classic bug, particularly when capturing by reference `[&]` inside a lambda that escapes its scope.
```cpp
#include <functional>
#include <iostream>
#include <string>

// GOTCHA 1: Pointer to a temporary object's internal buffer
const char* getString() {
    std::string temp = "hello";
    return temp.c_str(); // BUG: 'temp' is destroyed, pointer becomes dangling
}

// GOTCHA 2: Dangling lambda capture
std::function<void()> createLambda() {
    int local = 100;
    // BUG: Captures 'local' by reference. 
    return [&]() { std::cout << local << "\n"; }; 
}

// FIX: Return objects by value (e.g. return std::string), and capture by value [=] or [local] if the lambda escapes.
```

### Object slicing
As seen earlier (ref s29), assigning a derived object by value to a base object slices off the derived members and dynamic type.
```cpp
#include <iostream>

class Base { public: virtual void print() { std::cout << "Base\n"; } };
class Derived : public Base { public: void print() override { std::cout << "Derived\n"; } };

void printValue(Base b) { b.print(); }

int main() {
    Derived d;
    // GOTCHA: d is copied into a Base value, losing its Derived nature
    printValue(d); // Outputs: "Base"
}

// FIX: Pass by reference (Base& b) or pointer (Base* b).
```

### Calling a virtual function inside a constructor/destructor
During construction, the derived part of the object does not exist yet. Calling a virtual function dispatches to the *current* class's implementation, not the derived class's override (ref s29).
```cpp
#include <iostream>

class Base {
public:
    Base() { setup(); } // GOTCHA: Calls Base::setup, not Derived::setup
    virtual void setup() { std::cout << "Base setup\n"; }
};

class Derived : public Base {
public:
    void setup() override { std::cout << "Derived setup\n"; }
};

// FIX: Do not call virtual functions in constructors/destructors. 
// Use a separate init() function or pass configuration directly to the base constructor.
```

### The static initialisation order fiasco
If you have global or static objects across different translation units, the order in which they are initialised is undefined.
```cpp
// file1.cpp
extern int dependency;
// GOTCHA: If file1.cpp is initialised before file2.cpp, 'dependency' is 0 (or uninitialised)!
int globalVal = dependency + 1; 

// file2.cpp
int dependency = 42;

// FIX: Wrap globals in functions (the "Construct On First Use" idiom)
int& getDependency() {
    static int dep = 42; // Initialised exactly once on first call
    return dep;
}
```

### Forgetting a virtual destructor
Deleting a derived object through a base pointer when the base class lacks a virtual destructor causes undefined behaviour; typically, only the base destructor runs, leaking derived resources (ref s24).
```cpp
class Base {
public:
    // GOTCHA: ~Base() is not virtual
    ~Base() {} 
};

// FIX: Always declare `virtual ~Base() = default;` in polymorphic base classes.
```

### Iterator invalidation
Modifying a container (like adding elements to a `std::vector`) can cause it to reallocate its underlying memory, leaving existing iterators pointing to freed memory (ref s44/s46).
```cpp
#include <vector>

std::vector<int> v = {1, 2, 3};
auto it = v.begin();
v.push_back(4); // GOTCHA: May trigger reallocation
// int val = *it; // UB: iterator 'it' is now invalid

// FIX: Re-assign iterators after modifying containers, or use indices.
```
::: trap
Calling `erase()` also invalidates iterators at or after the point of erasure. Always use the return value: `it = v.erase(it);`.
:::

### Shallow copy and the Rule of 3/5
If your class manages a raw pointer and you rely on the compiler-generated copy constructor, it will copy the pointer address, not the data. Two objects now own one heap block, leading to a double free upon destruction (ref s35).
```cpp
class Buffer {
    int* data;
public:
    Buffer() : data(new int[10]) {}
    // GOTCHA: Missing custom copy constructor for heap data!
    ~Buffer() { delete[] data; }
};

// FIX: Implement the Rule of Three/Five (destructor, copy constructor, copy assignment).
```

### Uninitialised member order in the initialiser list
Members in a constructor's member-initialiser list are always initialised in the exact order they are *declared in the class*, regardless of the order they appear in the list (ref s22).
```cpp
class BadInit {
    int y;
    int x; // Declared second!
public:
    // GOTCHA: 'y' is initialised first using uninitialised 'x'
    BadInit(int val) : x(val), y(x) {} 
};

// FIX: Always list initialisers in the exact order of member declaration.
```

## Interview craft: reasoning about edge cases

When presented with a code snippet in an interview and asked "What does this output?", take a deliberate, cautious approach.

::: interview
Never rush to trace logic without first scanning for UB, uninitialised variables, or missing virtual destructors. If you spot UB, state clearly: "This is undefined behaviour because of [reason]. In practice it might crash or print garbage, but formally, the standard guarantees nothing."
:::

### Mention the tooling
Demonstrate production readiness by mentioning how you prevent these issues in the real world:
- **Compiler warnings**: "I would compile this with `-Wall -Wextra -Werror` to catch uninitialised variables, missing return statements, and implicit truncations."
- **Sanitizers**: "To catch that out-of-bounds access or use-after-free, I would run the test suite with AddressSanitizer (`-fsanitize=address`) and UndefinedBehaviorSanitizer (`-fsanitize=undefined`)."
- **Valgrind**: For environments where compiling with sanitizers isn't possible, mention using Valgrind to detect memory leaks and uninitialised reads.

### State your pre- and post-conditions
When writing an algorithm on a whiteboard or in a shared editor, explicitly state the invariants and assumptions before you begin coding.
- *"I am assuming `ptr` is not null. In production, I would add an `assert(ptr != nullptr);` here."*
- *"This index logic assumes the vector is not empty. Let's add an early return if `v.empty()`."*

::: keypoint
The goal in a C++ interview is not just to prove you can write algorithms, but to prove you write defensive code that respects the unforgiving nature of the language.
:::
