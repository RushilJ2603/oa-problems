# Expressions, Types, and Value Categories

This part establishes the model C++ uses to reason about every expression in a program. It underpins later topics: which operands an operator accepts, why references bind the way they do, and why pre-increment and post-increment behave differently.

## What an expression produces

An expression is evaluated to produce a result, and it may also have side effects. For example, in a program containing `++x`, the expression increments the value of `x`, and that changed value persists even after the expression has finished evaluating — that persistence is the side effect. Beyond producing values and side effects, expressions do one more thing: they can evaluate to objects or to functions.

## The two properties of every expression

To determine how an expression may be evaluated and where it is allowed to appear, C++ gives **every** expression two properties: a **type** and a **value category**.

### The type of an expression

The type of an expression is the type of the value, object, or function that results from evaluating it. Consider:

```cpp
int main()
{
    int x{};

    x = 5;     // valid: we can assign 5 to x
    5 = x;     // error: cannot assign the value of x to literal value 5

    return 0;
}
```

One of these assignments is valid (assigning `5` to the variable `x`) and one is not (it is meaningless to assign the value of `x` to the literal `5`). The compiler must have some rule that decides which expressions may legally appear on each side of an assignment. The type alone does not explain it — both `5` and `x` are `int`. The answer lies in the second property.

### The value category of an expression

::: definition
The value category of an expression (or sub-expression) indicates whether the expression resolves to a value, a function, or an object of some kind.
:::

It is the property that determines where an expression may legally be used.

Prior to C++11 there were only two value categories: lvalue and rvalue. These two suffice for everything covered here.

## lvalues: modifiable and non-modifiable

::: definition
An **lvalue** is an expression that evaluates to an identifiable object — something with a name and a fixed location, which can be referred to again later.
:::

Since constants entered the language, lvalues come in two subtypes:

- A **modifiable lvalue** is an lvalue whose value can be changed.
- A **non-modifiable lvalue** is an lvalue whose value cannot be changed, because the object is `const` or `constexpr`.

```cpp
int main()
{
    int x{};
    const double d{};

    int y { x };          // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression

    return 0;
}
```

Here `x` names an object whose value may be reassigned, so it is a modifiable lvalue; `d` names a `const` object, so although it is still an identifiable object, it is a non-modifiable lvalue.

## rvalues

::: definition
An **rvalue** (pronounced "arr-value", short for "right value", and sometimes written `r-value`) is an expression that is **not** an lvalue. Rvalue expressions evaluate to a value.
:::

Commonly encountered rvalues include literals (with the exception of C-style string literals, which are lvalues) and the values returned by functions and operators that return by value.

Rvalues are **not identifiable** — they must be used immediately, and they exist only within the scope of the expression in which they appear.

```cpp
int main()
{
    int x{ 5 };                  // 5 is an rvalue expression
    const double d{ 1.2 };       // 1.2 is an rvalue expression

    int y { x };                 // x is a modifiable lvalue expression
    const double e { d };        // d is a non-modifiable lvalue expression
    int z { return5() };         // return5() is an rvalue expression (the result is returned by value)

    int w { x + 1 };             // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static-casting d to an int is an rvalue expression

    return 0;
}
```

where `return5()` is simply:

```cpp
int return5()
{
    return 5;
}
```

It may seem surprising that `return5()`, `x + 1`, and `static_cast<int>(d)` are all rvalues. The reason is that each of these expressions produces a **temporary value that is not stored in an identifiable object** — the computed result exists only for the duration of the expression.

::: keypoint
Lvalue expressions evaluate to an identifiable object.
Rvalue expressions evaluate to a value.
:::

## Value categories and operators

Unless stated otherwise, operators expect their operands to be rvalues. For instance, binary `operator+` expects its operands to be rvalues:

```cpp
#include <iostream>
```

(The point is that `operator+` does not need an identifiable object — it only needs the *values* of its operands. This is why arithmetic on lvalues works: the lvalue is read for its value.)

### Why `x = 5` is legal but `5 = x` is not

We can now state the rule precisely.

::: keypoint
The assignment operator requires its left operand to be a modifiable lvalue expression, and its right operand to be an rvalue expression.
:::

```cpp
int main()
{
    int x{};

    // Assignment requires the left operand to be a modifiable lvalue expression
    // and the right operand to be an rvalue expression
    x = 5; // valid: x is a modifiable lvalue expression and 5 is an rvalue expression
    5 = x; // error: 5 is an rvalue expression and x is a modifiable lvalue expression

    return 0;
}
```

`5 = x` fails because the left operand `5` is an rvalue, not a modifiable lvalue — there is no object on the left to assign into.

## lvalue-to-rvalue conversion

If assignment expects its right operand to be an rvalue, how does the following compile?

```cpp
int main()
{
    int x{ 1 };
    int y{ 2 };

    x = y; // y is not an rvalue, but this is legal

    return 0;
}
```

Here `y` is an lvalue, yet it appears where an rvalue is expected. This works because of lvalue-to-rvalue conversion.

::: definition
**lvalue-to-rvalue conversion**: in any context where an rvalue is expected but an lvalue is supplied, the lvalue is evaluated to produce its value.
:::

In the example above, the lvalue expression `y` undergoes lvalue-to-rvalue conversion, which evaluates `y` to produce the rvalue `2`, and that value is then assigned to `x`.

::: keypoint
An lvalue will implicitly convert to an rvalue. This means an lvalue can be used anywhere an rvalue is expected.
An rvalue, on the other hand, will **not** implicitly convert to an lvalue.
:::

This asymmetry is the heart of the model. Anywhere a value is needed, a named object can stand in (it is read for its value); but a bare value cannot stand in where an addressable, named object is required.

## Worked examples: string literals and the increment operators

The following cases are worth committing to memory, because they expose subtleties that an intuitive reading would get wrong. Treat each as the value category of the parenthesised expression.

- **A named variable `x`** → lvalue. It can be pointed to; it occupies a specific location in memory.

- **`std::string("Hello")`** → rvalue. This constructs an unnamed, temporary `std::string` object on the fly. Because it is temporary and unnamed, it is an rvalue.

- **`"Hello"` (a C-style string literal)** → lvalue. 
    ::: trap
    This is a famous C++ quirk. Unlike numeric literals such as `5`, C-style string literals are stored as arrays of characters in a read-only section of the program's memory. Because they have a permanent memory address, they are lvalues.
    :::

- **`++x` (pre-increment)** → lvalue. Pre-increment adds 1 to `x` and then returns the *actual, modified variable* `x` itself. Since it hands back the variable, the result is an lvalue.

- **`x++` (post-increment)** → rvalue. Post-increment is trickier. It must return the *old* value of `x`, but `x` has already been updated. To do this, C++ creates a *temporary copy* of the old value and returns that copy. Temporary copies are always rvalues.

These two increment cases are the bridge to the next part, where the mechanics behind them are examined in full.
