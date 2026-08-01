# Constructors

::: definition
A **constructor** is a special member function that runs automatically when an object is created, used to initialise the object's data. A constructor has the **same name as the class** and **no return type** (not even `void`).
:::

::: keypoint
In Python, the `__init__` method serves the same purpose as a constructor, automatically initialising a new object's state right after it is created.
:::

## The four kinds

```cpp
Rectangle r1;         // (1) default / non-parameterised
Rectangle r2(10, 5);  // (2) parameterised
Rectangle r3(r2);     // (3) copy
```

1. **Default constructor** — supplied by the compiler when you write none; it leaves members uninitialised (or value-initialised).
2. **Non-parameterised constructor** — one you write that takes no arguments and sets default values.
3. **Parameterised constructor** — takes arguments to initialise the object.
4. **Copy constructor** — builds a new object as a copy of an existing one.

Written out for a `Rectangle` class:

```cpp
class Rectangle {
private:
    int length;
    int breadth;

public:
    // 1. Non-parameterised (default) constructor
    Rectangle() {
        length = 0;
        breadth = 0;
    }

    // 2. Parameterised constructor
    Rectangle(int l, int b) {
        length = l;
        breadth = b;
    }

    // 3. Copy constructor
    Rectangle(const Rectangle& rect) {
        length = rect.length;
        breadth = rect.breadth;
    }
};
```

## Constructor overloading and default arguments

Constructors are simply **overloaded** by their parameter lists, so a class may have several. 

You can use **default arguments** to collapse the non-parameterised and parameterised versions into one.

```cpp
class Rectangle {
public:
    // Serves as both Rectangle() and Rectangle(int, int)
    Rectangle(int l = 0, int b = 0) {
        length = l;
        breadth = b;
    }
};
```

::: trap
If you provide both `Rectangle(int l = 0, int b = 0)` and a separate no-argument `Rectangle()`, the compiler will throw an ambiguity error on `Rectangle r;` because both are valid matches.
:::

## The member initialiser list

Inside a constructor, you can assign values to members in the body, but C++ provides a specialised syntax called the **member initialiser list**. It appears after the parameter list and a colon, before the body block.

```cpp
class Rectangle {
private:
    int length;
    int breadth;

public:
    // Using the member initialiser list
    Rectangle(int l, int b) : length(l), breadth(b) {
        // The body is often empty
    }
};
```

Assignment inside the body is a two-step process: the member is first default-constructed, and *then* the new value is assigned over it. The initialiser list is a single-step direct initialisation. For primitive types like `int`, the performance difference is negligible, but for complex object members, the list avoids a wasted default construction.

Moreover, certain members **must** be initialised via the list because they cannot be assigned to after creation:
1. `const` members.
2. Reference (`&`) members.
3. Base class subobjects (if the base has no default constructor).

::: interview
"Why prefer the member initialiser list over assignment in the body?"
**Answer:** It is more efficient for object members (avoiding a construct-then-assign cycle), and it is mandatory for `const` members, reference members, and non-default-constructible base classes.
:::

::: trap
Members in the initialiser list are initialised **in the order they are declared in the class**, NOT the order they appear in the list. Writing `Rectangle(int l, int b) : breadth(b), length(l)` will still initialise `length` first. Always make the list match the declaration order to prevent bugs where one member's initialisation depends on another.
:::

## In-class member initialisation (C++11)

Since C++11, you can provide a default value directly where the member is declared. This is called **non-static data member initialisation** (NSDMI).

```cpp
class Rectangle {
private:
    int length = 1;
    int breadth = 1;
public:
    // Uses the in-class defaults: length=1, breadth=1
    Rectangle() {} 
    
    // Initialiser list overrides the in-class defaults
    Rectangle(int l, int b) : length(l), breadth(b) {}
};
```

This prevents uninitialised variables if you forget a member in the constructor, and reduces boilerplate across multiple constructors.

## Delegating constructors (C++11)

Constructors can call other constructors of the same class to avoid duplicating initialisation logic. This is done via the initialiser list.

```cpp
class Rectangle {
private:
    int length, breadth, area;

public:
    // The "target" constructor with all the logic
    Rectangle(int l, int b) : length(l), breadth(b) {
        area = length * breadth;
    }

    // Delegating constructor: calls the target constructor
    Rectangle() : Rectangle(1, 1) {
        // Target finishes before this body executes
    }
};
```

## `explicit` constructors

A single-argument constructor acts as an **implicit conversion** operator by default. 

```cpp
class String {
public:
    String(int size) { /* allocate buffer of 'size' */ }
};

void printString(String s);

int main() {
    printString(50); // Compiles! Implicitly calls String(50)
}
```

This is often dangerous. To prevent the compiler from using the constructor for silent type conversions, mark it `explicit`.

```cpp
class String {
public:
    explicit String(int size) { /* ... */ }
};

// printString(50); // Now a compiler error.
// printString(String(50)); // Explicit creation still works.
```

## `= default` and `= delete` (C++11)

You can ask the compiler to generate its standard version of a constructor by appending `= default`. You can forbid the use of a constructor by appending `= delete`.

```cpp
class NonCopyable {
public:
    NonCopyable() = default;                      // "Give me the compiler-generated default constructor"
    NonCopyable(const NonCopyable&) = delete;     // "Do not allow copying"
};
```

## Shallow versus deep copy

The default copy constructor generated by the compiler copies each member as-is. For a member that is a **pointer**, copying the pointer value makes both objects point at the *same* heap block. This is a **shallow copy**. That is usually wrong: the two objects become entangled, and both will try to manage the one block.

Consider a class that owns a heap array:

```cpp
class Test {
    int  a;
    int* p;
public:
    Test(int x) {
        a = x;
        p = new int[a];        // each object should own its own array
    }
    
    Test(const Test& t) {      // naive copy constructor
        a = t.a;
        p = t.p;               // SHALLOW: both share one array — wrong
    }
};
```

With `p = t.p`, the copy shares the original's array. A **deep copy** instead allocates a fresh block and copies the contents, so each object owns an independent array:

```cpp
class Test {
    int  a;
    int* p;
public:
    Test(int x) {
        a = x;
        p = new int[a];
    }
    
    Test(const Test& t) {      // deep copy constructor
        a = t.a;
        p = new int[a];        // allocate a separate array
        for (int i = 0; i < a; i++) {
            p[i] = t.p[i];     // copy each element
        }
    }
};
```

Now `Test t(5); Test t1(t);` produces two objects with two distinct arrays, so modifying or destroying one cannot corrupt the other. Whenever a class manages a resource through a pointer, its copy constructor must perform a deep copy.
