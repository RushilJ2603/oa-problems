# Control Flow: Loops

> **Prerequisites Block:**
> * **Assumed Knowledge:** Operators, Booleans, basic data types.

> **First-use gloss:** A **loop** is a programming construct that repeats a block of code as long as a specified condition is met or for every item in a sequence.


## The `for` loop and `range()`

`range(start, stop, step)` generates a sequence of integers from `start` up to
(but not including) `stop`, advancing by `step`. A negative step counts
downward.

```python
# For loop demo
for i in range(10, 0, -1):
    print(i)
```

```text
10
9
8
7
6
5
4
3
2
1
```

The loop runs from `10` down to `1`; `stop` is `0`, which is excluded.

## Iterating directly over a sequence

A `for` loop can walk the elements of any iterable directly — no index needed.

Over a **string**, it yields one character at a time:

```python
for i in 'Delhi':
    print(i)
```

```text
D
e
l
h
i
```

Over a **list**:

```python
for i in [1, 2, 3, 4, 5]:
    print(i)
```

```text
1
2
3
4
5
```

Over a **tuple** — identical behaviour, different bracket:

```python
for i in (1, 2, 3, 4, 5):
    print(i)
```

```text
1
2
3
4
5
```

## The `for…else` and `while…else` construct

> **Heavy.** A control-flow paradigm unique to Python that breaks standard intuition from other languages.

**Analogy:** Imagine searching a dark room for your keys with a flashlight. You sweep the beam across the room (the loop). If you spot the keys, you stop searching immediately (`break`). If you sweep the entire room and never see them, you conclude they aren't there (the `else` block). The `else` only happens if the search naturally finishes without being interrupted.

**Concrete Example FIRST:**
The classic use is searching: `break` out when the target is found; let `else` report failure if the search runs to completion.

Target present — the `break` fires, so `else` is skipped:

```python
# Scenario A: the item is found (break triggers, else is skipped)
numbers = [1, 2, 3, 4, 5]

for num in numbers:
    if num == 3:
        print("Found the number 3!")
        break
else:
    print("Searched the whole list, but didn't find a 3.")
```

Target absent — the loop completes, so `else` runs:

```python
numbers = [1, 2, 4, 5]

for num in numbers:
    if num == 3:
        print("Found the number 3!")
        break
else:
    print("Searched the whole list, but didn't find a 3.")

# Output: "Searched the whole list, but didn't find a 3."
```

**Plain-English:** The `else` block attached to a loop only executes if the loop finishes all its iterations naturally. If you exit the loop early using a `break` statement, Python skips the `else` block entirely. Many developers mentally rename `else` to `no_break` to remember this behavior.

**Technical Definition:** Python loops may carry an `else` clause. The `else` block runs **only if the iterable is exhausted** (for `for`) or **the condition becomes `False`** (for `while`). If the loop is terminated by a `break` statement, the `else` block is unconditionally skipped.

### `while…else`

The same rule applies to `while`: if the condition naturally becomes `False`, the `else` runs; a `break` would skip it.

```python
count = 3

while count > 0:
    print(f"Countdown: {count}")
    count -= 1
else:
    print("Countdown finished successfully!")

# Output:
# Countdown: 3
# Countdown: 2
# Countdown: 1
# Countdown finished successfully!
```

### Worked example: printing primes with `for…else`

A nested loop puts the construct to work. The inner loop tries every potential
divisor of `i`; if one divides evenly, `i` is composite and the inner loop
`break`s. Only when no divisor is found does the inner `else` run and print `i`
— exactly the numbers that are prime.

```python
lower = int(input('enter lower range'))
upper = int(input('enter upper range'))

for i in range(lower, upper + 1):
    for j in range(2, i):
        if i % j == 0:
            break
    else:
        print(i)
```

```text
enter lower range10
enter upper range100
11
13
17
19
...
```

The `else` is attached to the **inner** `for`, so it fires once per `i` that
survived the divisor test — the prime numbers in the requested range.

> **Key point.** Loop `else` pairs naturally with `break`. Read it as "if the
> loop never broke, then…". Without a `break` inside, the `else` is equivalent
> to code placed after the loop and adds nothing.
