# Functions: Overloading, Templates, and Default Arguments

Three features let one conceptual operation be written once yet serve many argument shapes: **overloading** gives several functions the same name, **templates** write a function once for any type, and **default arguments** make trailing parameters optional.

## Function overloading

::: definition
Two or more functions may share a name as long as their parameter lists differ — in the number of parameters, or in their types.
:::

The compiler selects the right one by matching the call's arguments:

```cpp
int   add(int x, int y)          { return x + y; }
int   add(int x, int y, int z)   { return x + y + z; }   // differs in count
float add(float x, float y)      { return x + y; }        // differs in type

int a = 10, b = 5, c, d;
c = add(a, b);       // calls the two-int version
d = add(a, b, c);    // calls the three-int version
```

::: keypoint
The decisive rule is that overloads must differ in their parameters, not merely in their return type.
:::

These four declarations make the point:

```cpp
int   max(int, int);
float max(float, float);
int   max(int, int, int);
float max(int, int);     // ERROR: clashes with int max(int, int)
```

The first three are valid overloads. The fourth differs from the first only in return type, with identical parameters `(int, int)` — so it is **not** a distinct overload, and the program will not compile. The return type alone cannot tell two functions apart, because a call site is free to ignore the return value, leaving the compiler no basis on which to choose.

## Function templates

When the *logic* is identical across types and only the types change, writing separate overloads is wasteful. 

::: definition
A template writes the function once with a placeholder type parameter, and the compiler generates a concrete version for each type actually used.
:::

```cpp
template <class T>
T maxim(T a, T b)
{
    return a > b ? a : b;
}

cout << maxim(12, 14);     // T deduced as int
cout << maxim(2.3, 1.4);   // T deduced as double
```

This single definition replaces the hand-written `int max(int,int)`, `float max(float,float)`, and so on. 

::: trap
The catch is that the one template parameter `T` must resolve to a single type per call.
:::

Mixing types defeats deduction:

```cpp
cout << maxim(2.3f, 5.6);   // ERROR: 2.3f is float, 5.6 is double — T cannot be both
```

Because the two arguments have different types, the compiler cannot settle on one `T` and reports "no matching function". Both arguments must be the same type, or be cast to make them so.

## Default arguments

::: definition
A parameter may be given a default value, making it optional at the call site.
:::

Trailing parameters that have defaults can be omitted, and the default is supplied in their place:

```cpp
int add(int x, int y, int z = 0)   // z is optional
{
    return x + y + z;
}

add(2, 5);       // z defaults to 0  -> 7
add(2, 5, 8);    // z is 8           -> 15
add(2, 5, 0);    // z is 0 explicitly -> 7
```

A single function with a default argument often replaces a pair of overloads: here the one `add` covers both the two-argument and three-argument cases that would otherwise require `int add(int,int)` and `int add(int,int,int)` written separately. 

::: keypoint
Only *trailing* parameters may carry defaults, so that the arguments a caller omits are always the last ones.
:::
