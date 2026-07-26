# Add One to a Streamed Big Number

A number is so large it cannot be held in any fixed-width integer type. You receive it as a **stream
of decimal digits**, most-significant digit first (as if produced by repeated calls to a `read()`
that yields one digit at a time, left to right). You must output the digits of the number **plus one**,
again most-significant first (as if written one digit at a time through `write()`).

Formally: given the decimal representation of a non-negative integer **N**, output the decimal
representation of **N + 1**, with no leading zeros.

## Input Format

- A single line: the digits of **N** with no separating spaces. **N** has no leading zeros (the only
  representation beginning with `0` is `N = 0` itself, written as `0`).

## Output Format

- A single line: the digits of **N + 1**, with no leading zeros.

## Constraints

- **N** has between $1$ and $10^6$ digits.

## Examples

### Example 1

**Input:**
```
12345
```

**Output:**
```
12346
```

### Example 2

**Input:**
```
999
```

**Output:**
```
1000
```

Adding one carries all the way through the run of nines, producing an extra leading digit.

### Example 3

**Input:**
```
0
```

**Output:**
```
1
```
