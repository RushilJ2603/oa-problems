# Literals

> **Prerequisites Block:**
> * **Assumed Knowledge:** Data types.

> **First-use gloss:** A **literal** is a fixed value written directly in source code.


A *literal* is a fixed value written directly in source code. Python provides
distinct notations for integers in several bases, for floats, for complex
numbers, and for strings.

## Integer literals in different bases

```python
a = 0b1010    # Binary Literal
b = 100       # Decimal Literal
c = 0o310     # Octal Literal
d = 0x12c     # Hexadecimal Literal
```

| Prefix | Base | Literal  | Decimal value |
|:------:|:----:|:--------:|:-------------:|
| `0b`   | 2    | `0b1010` | 10            |
| (none) | 10   | `100`    | 100           |
| `0o`   | 8    | `0o310`  | 200           |
| `0x`   | 16   | `0x12c`  | 300           |

```python
print(a, b, c, d)
```

```text
10 100 200 300
```

Regardless of the notation used to *write* them, all four are ordinary integers
once stored; printing shows their decimal values.

## Float literals and scientific notation

```python
# Float Literal
float_1 = 10.5
float_2 = 1.5e2     # 1.5 * 10**2
float_3 = 1.5e-3    # 1.5 * 10**-3
```

The `e` notation means "times ten to the power of." So `1.5e2` is
`1.5 × 10² = 150.0` and `1.5e-3` is `1.5 × 10⁻³ = 0.0015`.

```python
print(float_1, float_2, float_3)
```

```text
10.5 150.0 0.0015
```

A standalone example of the same notation:

```python
print(1.5e3)
```

```text
1500.0
```

## Complex literals

The imaginary unit is written as a `j` suffix. A complex number exposes `.real`
and `.imag` attributes:

```python
# Complex Literal
x = 3.14j
print(x, x.imag, x.real)
```

```text
3.14j 3.14 0.0
```

## String literals

Strings can be written several ways, and a few special prefixes change how the
text is interpreted.

```python
string      = 'This is Python'
strings     = "This is Python"
char        = "C"
multiline_str = """This is a multiline string with more than one line code."""
unicode     = u"\U0001F606\U0001F606\U0001F923"
raw_str     = r"raw \n string"

print(string)
print(strings)
print(char)
print(multiline_str)
print(unicode)
print(raw_str)
```

```text
This is Python
This is Python
C
This is a multiline string with more than one line code.
😆😆🤣
raw \n string
```

The behaviours on display:

- **Single vs. double quotes** (`'...'`, `"..."`) are equivalent; choose
  whichever avoids escaping.
- **Triple quotes** (`"""..."""` or `'''...'''`) create multi-line strings.
- **`u"..."`** marks a Unicode string; `\U0001F606` is a Unicode escape naming a
  character by code point, here producing emoji.
- **`r"..."`** marks a *raw* string: backslash escapes are taken literally, so
  `\n` stays the two characters backslash-n instead of becoming a newline.

> **Key point.** A raw string (`r"..."`) is invaluable for things like Windows
> paths and regular-expression patterns, where literal backslashes are wanted.

## Boolean and `None` literals

`True`, `False`, and `None` are themselves literals — the only values of their
respective kinds.
