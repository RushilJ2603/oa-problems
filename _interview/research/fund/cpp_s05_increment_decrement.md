# Increment and Decrement Operators

C++ provides four closely related operators that change a variable by one:

- **pre-increment** `++x` and **post-increment** `x++`, which add one;
- **pre-decrement** `--x` and **post-decrement** `x--`, which subtract one.

Within each pair the two forms compute the same change to the variable but differ in *what they hand back* to the surrounding expression, and therefore in value category and in cost. The distinction matters whenever the operator is used inside a larger expression — in assignments, comparisons, or function arguments. The discussion below uses the increment forms; the decrement forms behave identically, subtracting one instead of adding it.

## Pre-increment (`++x`)

::: definition
With pre-increment, the variable is incremented **first**, and the updated value is then used in the expression.
:::

- **Behaviour:** increment, then return.
- **Result:** it returns an **lvalue** — a reference to the actual variable — because it hands back the variable itself after modification.
- **Performance:** slightly more efficient for complex types, because it does not need to create a temporary copy.

```cpp
int x = 5;
int y = ++x;
// Step 1: x becomes 6
// Step 2: y becomes 6
```

## Post-increment (`x++`)

::: definition
With post-increment, the current value is used in the expression **first**, and the variable is incremented afterwards.
:::

```cpp
int x = 5;
int y = x++;
// Step 1: y gets the current value (5)
// Step 2: x becomes 6
```

::: keypoint
Because the operator must yield the original value while still leaving the variable incremented, it has to keep a copy of the old value to return. That copy is a temporary, which is why post-increment returns an **rvalue** and costs slightly more for non-trivial types.
:::

## Side-by-side comparison

| Feature | Pre-increment (`++x`) | Post-increment (`x++`) |
| --- | --- | --- |
| **Action order** | Increment then use | Use then increment |
| **Return value** | The updated variable | A copy of the old value |
| **Value category** | lvalue (identifiable) | rvalue (temporary) |
| **Analogy** | "Change it now, then show me." | "Show me now, then change it." |

The analogy captures the essence: pre-increment changes the variable and shows you the variable; post-increment shows you the old value and changes the variable behind the scenes.

## Worked examples: the operators inside expressions

Concrete values make the difference between the two forms tangible. Take a variable initialised to five and assign the result of incrementing it to a second variable.

With **pre-increment**, the increment happens before the value is read, so both variables end up at six:

```cpp
int x = 5, y;
y = ++x;   // step 1: increment x -> 6   step 2: assign -> y = 6
// result: x = 6, y = 6
```

With **post-increment**, the original value is read before the increment, so the assigned variable keeps the old value while the incremented variable moves on:

```cpp
int x = 5, y;
y = x++;   // step 1: assign old value -> y = 5   step 2: increment x -> 6
// result: x = 6, y = 5
```

The same ordering rule governs the operator when it appears inside a larger arithmetic expression. Consider multiplying the incremented variable by another operand:

```cpp
int x = 5, y = 10, z;

z = x++ * y;   // post: uses the OLD x (5):  z = 5 * 10 = 50, then x -> 6
// result: x = 6, y = 10, z = 50

z = ++x * y;   // pre: increments x FIRST (6): z = 6 * 10 = 60
// result: x = 6, y = 10, z = 60
```

The post-increment form multiplies with the pre-increment value of `x` (five) and yields fifty, leaving `x` at six afterwards; the pre-increment form raises `x` to six before the multiplication and yields sixty. In both cases `y` is only read, so it is unchanged. This is the same lvalue-versus-rvalue behaviour established earlier, now visible in the numeric result: post-increment hands the expression a copy of the old value, while pre-increment hands back the already-updated variable.

![Increment and decrement operators.](assets/fig_20260614_increment-decrement.png)

## Overflow: incrementing past a type's range

::: trap
Incrementing a value that is already at the maximum its type can hold does not produce a larger number — it *wraps around* to the type's minimum. This is **overflow**, and it follows directly from how signed integers are represented.
:::

A `signed char` occupies eight bits and stores values in the range $-128$ to $127$. Consider a `char` sitting at the top of that range and then incrementing it:

```cpp
char x = 127;
++x;
std::cout << (int) x;   // prints -128, not 128
```

The cast to `int` is only there to print the numeric value rather than a character. The surprising result, $-128$, comes from **two's-complement** representation. The value 127 in eight bits is `01111111` (the leading bit, the *sign* bit, is 0, marking the number as non-negative). Adding one carries all the way up:

$$01111111 + 1 = 10000000$$

The result `10000000` has its sign bit set, and in two's complement that bit pattern is exactly $-128$. So incrementing the largest positive `char` rolls over to the most negative one. The binary of 127 itself is obtained by the familiar repeated-division-by-two method ($127, 63, 31, 15, 7, 3, 1$, each step recording a remainder of 1), giving `1111111`.

![Overflow.](assets/fig_20260614_overflow.png)

::: keypoint
The lesson generalises to every fixed-width integer type: arithmetic that crosses the type's maximum (or minimum) silently wraps to the other end of the range rather than growing without bound.
:::
