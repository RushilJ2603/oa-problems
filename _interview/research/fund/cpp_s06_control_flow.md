# Control Flow and Statement-Level Features

This part collects three statement-level features of C++: how the logical operators evaluate their operands, how a variable can be declared inside a condition, and how the `switch` statement selects among many cases. Each carries a practical trap worth knowing.

## Short-circuit evaluation of logical operators

The two logical operators are `&&` (logical AND) and `||` (logical OR).

::: definition
Both evaluate their operands left to right and stop as soon as the result is certain — this is **short-circuit evaluation**.
:::

- For `a && b`: if `a` is false the whole expression is already false, so `b` is **not evaluated**.
- For `a || b`: if `a` is true the whole expression is already true, so `b` is **not evaluated**.

The consequence is subtle when the skipped operand has a side effect. Consider:

```cpp
int a = 5, b = 7, i = 5;

if (a > b && ++i < b)
{
    // ...
}

std::cout << i;   // prints 5
```

The left operand `a > b` is `5 > 7`, which is false. Because `&&` short-circuits on a false left operand, the right operand `++i < b` is never evaluated, so `++i` never runs and `i` remains 5. Had `a > b` been true, `++i` would have executed and `i` would have changed.

::: trap
This leads to a firm rule: **do not place an increment, decrement, or any other side-effecting expression in the second (or later) operand of a logical operator**, because it may silently be skipped depending on the first operand's value.
:::

## Declaring variables inside conditions

A variable can be declared as part of an `if` statement, with its scope limited to that statement. Modern C++ (from C++17) allows an **init-statement** inside the condition, separated by a semicolon:

```cpp
int main()
{
    int a, b, c, x;

    if (int k = exp; k < a)
    {
        // k is visible only inside this if
    }
}
```

Here `k` is created when the `if` is reached, used in the condition `k < a`, and destroyed when the `if` finishes.

::: keypoint
Limiting the lifetime this way keeps the surrounding scope uncluttered: the function's activation record on the stack grows to hold `k` only while the `if` is active and shrinks again afterwards.
:::

![Dynamic Declaration.](assets/fig_20260614_dynamic-declaration.png)

## The switch statement

A `switch` selects one path among many based on the value of an integral expression — its **controlling expression** must be of an integer or character type (`int` / `char`). Each `case` gives a label to compare against, and `default` handles any value that matches no case:

```cpp
switch (expr)        // expr is int or char
{
    case 1:
        // ...
        break;
    case 2:
        // ...
        break;
    default:
        // ...
}
```

Character labels are equally valid, since `char` is an integral type:

```cpp
switch (expr)
{
    case 'a':
        // ...
        break;
    case 'b':
        // ...
        break;
    default:
        // ...
}
```

::: trap
The crucial detail is **`break`**. Control enters at the matching `case` and then **falls through** into the statements of the following cases until a `break` (or the end of the switch) is reached. Omitting a `break` therefore causes the code to execute the matched case and every case after it — usually a bug. Each case that should stand alone must end with its own `break`.
:::
