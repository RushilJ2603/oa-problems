# Operators

> **Prerequisites Block:**
> * **Assumed Knowledge:** Variables, basic data types.

> **First-use gloss:** **Operators** are special symbols that perform computations on values and variables.


Python's operators group into arithmetic, relational, logical, bitwise,
assignment, and membership families.

## Arithmetic operators

```python
print(5 + 6)
print(5 - 6)
print(5 * 6)
print(5 / 2)
print(5 // 2)
print(5 % 2)
print(5 ** 2)
```

```text
11
-1
30
2.5
2
1
25
```

| Operator | Meaning            | Example  | Result |
|:--------:|:-------------------|:--------:|:------:|
| `+`      | Addition           | `5 + 6`  | `11`   |
| `-`      | Subtraction        | `5 - 6`  | `-1`   |
| `*`      | Multiplication     | `5 * 6`  | `30`   |
| `/`      | True division      | `5 / 2`  | `2.5`  |
| `//`     | Floor division     | `5 // 2` | `2`    |
| `%`      | Modulus (remainder)| `5 % 2`  | `1`    |
| `**`     | Exponentiation     | `5 ** 2` | `25`   |

> **Key point.** `/` always produces a `float` (`5 / 2` is `2.5`, never `2`),
> while `//` performs floor division and keeps an integer result when both
> operands are integers. `%` returns the remainder, and `**` raises to a power.

## Relational operators

Relational (comparison) operators compare two values and evaluate to a boolean.
In the notebook they produce results such as `True`, `True`, `False`.

| Operator | Meaning                   |
|:--------:|:--------------------------|
| `==`     | Equal to                  |
| `!=`     | Not equal to              |
| `>`      | Greater than              |
| `<`      | Less than                 |
| `>=`     | Greater than or equal to  |
| `<=`     | Less than or equal to     |

## Logical operators

```python
print(1 and 0)
print(1 or 0)
print(not 1)
```

```text
0
1
False
```

`and` returns the first falsy operand (or the last value if all are truthy);
`or` returns the first truthy operand; `not` inverts truthiness to a boolean.
Here `1` is truthy and `0` is falsy, so `1 and 0` yields `0`, `1 or 0` yields
`1`, and `not 1` yields `False`.

## Bitwise operators

These act on the binary representations of integers.

```python
print(2 & 3)    # bitwise and
print(2 | 3)    # bitwise or
print(2 ^ 3)    # bitwise xor
print(~3)
print(4 >> 2)
print(5 << 2)
```

```text
2
3
1
-4
1
20
```

| Operator | Name         | Example  | Result | Reasoning                        |
|:--------:|:-------------|:--------:|:------:|:---------------------------------|
| `&`      | AND          | `2 & 3`  | `2`    | `10 & 11 = 10`                   |
| `\|`     | OR           | `2 \| 3` | `3`    | `10 \| 11 = 11`                  |
| `^`      | XOR          | `2 ^ 3`  | `1`    | `10 ^ 11 = 01`                   |
| `~`      | NOT (invert) | `~3`     | `-4`   | `~x = -(x + 1)`                  |
| `>>`     | Right shift  | `4 >> 2` | `1`    | `100` shifted right twice → `1`  |
| `<<`     | Left shift   | `5 << 2` | `20`   | `101` shifted left twice → `10100` |

> **Key point.** Shifting left by *n* multiplies by `2**n`; shifting right by
> *n* divides by `2**n` (floor). Bitwise NOT of `x` is `-(x + 1)`, which is why
> `~3` is `-4`.

## Assignment operators

`=` binds a value to a name. The *augmented* assignment operators combine an
operation with assignment.

```python
# Assignment Operators
# =
# a = 2
a = 2

# a = a + 2
a += 2
print(a)
```

```text
4
```

`a += 2` is shorthand for `a = a + 2`. The same pattern exists for the other
arithmetic operators (`-=`, `*=`, `/=`, `//=`, `%=`, `**=`, and the bitwise
ones).

> **Trap.** Python has **no** `++` or `--` operators. The increment idioms
> `a++` and `++a` from C-style languages are not valid Python; use `a += 1`
> instead.

## Membership operators

`in` and `not in` test whether a value occurs within a sequence (a string, list,
tuple, and so on), returning a boolean.

```python
print('D' in 'Delhi')
```

```text
True
```

```python
print('D' not in 'Delhi')
print(1 in [2, 3, 4, 5, 6])
```

```text
False
False
```

`'D'` is a character of `'Delhi'`, so `in` is `True` and `not in` is `False`.
The integer `1` is absent from `[2, 3, 4, 5, 6]`, so that membership test is
`False`.
