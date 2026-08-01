# Variables and Binding

> **Prerequisites Block:**
> * **Assumed Knowledge:** Basic data types (integers, floats, booleans, strings).

> **First-use gloss:** A **variable** is a name bound to a value. Assignment uses `=`.

## Dynamic typing

Python is **dynamically typed**: a variable's type is inferred from the value
assigned to it, and is never declared.

```python
# Dynamic Typing
a = 5

# Static Typing
int a = 5
```

The first form is valid Python. The second (`int a = 5`) is how a *statically
typed* language such as C or Java would force you to declare the type up front —
it is shown only as a contrast and is **not** valid Python syntax.

## Dynamic binding

> **Heavy.** Variables in Python are fundamentally different from variables in languages like C or Java.

**Analogy:** In C or Java, a variable is like a fixed plastic bucket. If you declare an `int` bucket, you can only ever put numbers in it. If you try to put a string in it, it won't fit. In Python, a variable is like a **sticky name tag**. You can take the `a` name tag off a number and slap it onto a string. The "type" lives on the object itself, not on the name tag.

**Concrete Example FIRST:**
Because only the value carries a type, the *same* name may be rebound to a value of a completely different type during a program's life:

```python
# Dynamic Binding
a = 5
print(a)
a = 'nitish'
print(a)
```

```text
5
nitish
```

**Plain-English:** You can assign a number to `a`, and then on the very next line, assign a string to `a`. Python does not complain. It simply removes the `a` name tag from the integer `5` and attaches it to the string `'nitish'`.

**Technical Definition:** The name `a` first refers to an integer, then to a string. This freedom is **dynamic binding** — the binding between a variable name and an object (and therefore its type) can change dynamically at runtime.

## The `None` keyword

`None` is Python's null value — a literal meaning "no value." Assigning it does
not print anything by itself:

```python
k = None
a = 5
b = 6
print('Program exe')
```

```text
Program exe
```

## Identifiers must exist before use

Referring to a name that was never assigned raises a `NameError`:

```python
k
a = 5
b = 6
print('Program exe')
```

```text
NameError                                 Traceback (most recent call last)
----> 1 k
      2 a = 5
      3 b = 6
      4 print('Program exe')

NameError: name 'k' is not defined
```

> **Trap.** Evaluating a bare name (`k`) that has not been bound is an error,
> *not* a silent no-op. Note also that execution stops at the failing line —
> the later assignments and the `print` never run.
