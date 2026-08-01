# Strings

> **Prerequisites Block:**
> * **Assumed Knowledge:** Data types, loops, operators.

> **First-use gloss:** A **string** is a sequence of characters used to represent text.


## What a string is

> **First-use gloss:** A string is a sequence of characters. In Python specifically,
> a string is a sequence of **Unicode** characters.

The topics that organise this section:

- Creating strings
- Accessing strings
- Adding characters to strings
- Editing strings
- Deleting strings
- Operations on strings
- String functions

(The sessions captured here develop creation, access by index, slicing, and
immutability; the remaining topics are introduced as the roadmap for what
follows.)

## Creating strings

```python
s = 'hello'
s = "hello"
# multiline strings
s = '''hello'''
s = """hello"""
s = str('hello')
print(s)
```

```text
hello
```

There are five interchangeable ways shown to build the same string: single
quotes, double quotes, triple single quotes, triple double quotes, and the
`str()` constructor.

### Quotes inside strings

Choosing the *other* quote style lets a quote character appear literally inside
the text:

```python
s = "it's raining outside"
print(s)
```

```text
it's raining outside
```

Wrapping in double quotes allows the apostrophe in `it's` without escaping.

## Accessing characters: indexing

Each character has a position. **Positive indexing** counts from the left
starting at `0`; **negative indexing** counts from the right starting at `-1`.

For `s = 'hello world'`:

| Character    | h   | e   | l   | l   | o   | (space) | w  | o  | r  | l  | d   |
|:-------------|:---:|:---:|:---:|:---:|:---:|:-------:|:--:|:--:|:--:|:--:|:---:|
| Positive idx | 0   | 1   | 2   | 3   | 4   | 5       | 6  | 7  | 8  | 9  | 10  |
| Negative idx | -11 | -10 | -9  | -8  | -7  | -6      | -5 | -4 | -3 | -2 | -1  |

Negative indexing in action:

```python
# Negative Indexing
s = 'hello world'
print(s[-1])
```

```text
d
```

```python
print(s[-3])
```

```text
r
```

`s[-1]` is the last character, `s[-3]` the third from the end.

> **Trap.** Indexing past the end of a string raises
> `IndexError: string index out of range`. There is no "off the end" sentinel;
> the position must actually exist.

## Slicing

A slice extracts a substring with the form `s[start:stop:step]`. `start` is
included, `stop` is excluded, and `step` is the stride (default `1`). Any of the
three may be omitted.

For all examples, `s = 'hello world'`.

### Basic slice

```python
print(s[0:5])
```

```text
hello
```

Indices `0` through `4` — `'hello'` (position `5`, the space, is excluded).

### Omitting an endpoint

Leaving out `start` defaults it to the beginning; leaving out `stop` defaults it
to the end. The intended example slices to the first three characters:

```python
print(s[:3])
```

```text
hel
```

> **Trap (notebook hazard).** The captured cell for `print(s[:3])` displayed
> `llo world`. That output is **stale** — it was left over from a previous run
> when the code read `s[2:]` (which *does* give `'llo world'`). The current code
> `s[:3]` evaluates to `'hel'`. In Jupyter/Colab, editing a cell does **not**
> refresh its shown output until you re-execute it; never trust a result you
> have not just run.

### Slicing with a step

A `step` of `2` takes every second character:

```python
print(s[0:6:2])
```

```text
hlo
```

Positions `0`, `2`, `4` → `h`, `l`, `o`.

### Negative step — walking backwards

A negative step moves right-to-left, so `start` should be greater than `stop`.

```python
print(s[6:0:-1])
```

```text
w olle
```

From position `6` (`w`) down to position `1` (`stop` `0` excluded): `w`, space,
`o`, `l`, `l`, `e`.

```python
print(s[6:0:-2])
```

```text
wol
```

Same downward range, stride `2`: positions `6`, `4`, `2` → `w`, `o`, `l`.

### Reversing a string

Omitting both endpoints with a step of `-1` reverses the whole string — the
idiomatic Python reversal:

```python
print(s[::-1])
```

```text
dlrow olleh
```

### Slicing with negative indices

Endpoints may be negative too. Taking from the fifth-from-last to the second-to-last:

```python
print(s[-5:-1])
```

```text
worl
```

Positions `-5` through `-2` → `w`, `o`, `r`, `l`.

The last five characters — negative `start`, omitted `stop`:

```python
print(s[-5:])
```

```text
world
```

A negative-everything reverse of a tail section:

```python
print(s[-1:-6:-1])
```

```text
dlrow
```

From `-1` (`d`) leftwards to `-6` excluded: `d`, `l`, `r`, `o`, `w`.

> **Key point.** Read a slice as "from `start`, up to but not including `stop`,
> stepping by `step`." With a positive step you move left→right and need
> `start < stop`; with a negative step you move right→left and need
> `start > stop`. Mismatched direction yields an empty string rather than an
> error.

## Strings are immutable

A string cannot be changed in place. Attempting to assign to one of its
positions fails:

```python
s = 'hello world'
s[0] = 'H'
# Python strings are immutable
```

```text
TypeError                                 Traceback (most recent call last)
----> 1 s = 'hello world'
      2 s[0] = 'H'

TypeError: 'str' object does not support item assignment
```

> **Trap.** Strings are **immutable**. You cannot edit a character by index;
> `s[0] = 'H'` raises `TypeError: 'str' object does not support item
> assignment`. To "change" a string, build a new one (for example by slicing
> and concatenation) and rebind the name.

## Deleting strings

The `del` keyword deletes a name binding entirely. Attempting to delete a part of a string (such as a slice) fails because strings are immutable.

```python
s = 'hello world'
del s
print(s)
```

```text
NameError: name 's' is not defined
```

Attempting to delete a slice:

```python
s = 'hello world'
del s[-1:-5:2]
print(s)
```

```text
TypeError                                 Traceback (most recent call last)
----> 2 del s[-1:-5:2]

TypeError: 'str' object does not support item deletion
```

## Operations on strings

Strings support concatenation and repetition using arithmetic operators, as well as lexicographical comparison using relational operators.

### Arithmetic operations

The `+` operator concatenates two strings. The `*` operator repeats a string a given number of times.

```python
print('delhi' + ' ' + 'mumbai')
```

```text
delhi mumbai
```

```python
print('delhi'*5)
```

```text
delhidelhidelhidelhidelhi
```

```python
print("*"*50)
```

```text
**************************************************
```

### Relational operations

Relational operators (`==`, `!=`, `>`, `<`, `>=`, `<=`) compare strings lexicographically (based on alphabetical order / Unicode values).

```python
print('delhi' != 'delhi')
```
```

> **Trap (notebook hazard).** The captured cell for `print(s[:3])` displayed
> `llo world`. That output is **stale** — it was left over from a previous run
> when the code read `s[2:]` (which *does* give `'llo world'`). The current code
> `s[:3]` evaluates to `'hel'`. In Jupyter/Colab, editing a cell does **not**
> refresh its shown output until you re-execute it; never trust a result you
> have not just run.

### Slicing with a step

A `step` of `2` takes every second character:

```python
print(s[0:6:2])
```

```text
hlo
```

Positions `0`, `2`, `4` → `h`, `l`, `o`.

### Negative step — walking backwards

A negative step moves right-to-left, so `start` should be greater than `stop`.

```python
print(s[6:0:-1])
```

```text
w olle
```

From position `6` (`w`) down to position `1` (`stop` `0` excluded): `w`, space,
`o`, `l`, `l`, `e`.

```python
print(s[6:0:-2])
```

```text
wol
```

Same downward range, stride `2`: positions `6`, `4`, `2` → `w`, `o`, `l`.

### Reversing a string

Omitting both endpoints with a step of `-1` reverses the whole string — the
idiomatic Python reversal:

```python
print(s[::-1])
```

```text
dlrow olleh
```

### Slicing with negative indices

Endpoints may be negative too. Taking from the fifth-from-last to the second-to-last:

```python
print(s[-5:-1])
```

```text
worl
```

Positions `-5` through `-2` → `w`, `o`, `r`, `l`.

The last five characters — negative `start`, omitted `stop`:

```python
print(s[-5:])
```

```text
world
```

A negative-everything reverse of a tail section:

```python
print(s[-1:-6:-1])
```

```text
dlrow
```

From `-1` (`d`) leftwards to `-6` excluded: `d`, `l`, `r`, `o`, `w`.

> **Key point.** Read a slice as "from `start`, up to but not including `stop`,
> stepping by `step`." With a positive step you move left→right and need
> `start < stop`; with a negative step you move right→left and need
> `start > stop`. Mismatched direction yields an empty string rather than an
> error.

## Strings are immutable

A string cannot be changed in place. Attempting to assign to one of its
positions fails:

```python
s = 'hello world'
s[0] = 'H'
# Python strings are immutable
```

```text
TypeError                                 Traceback (most recent call last)
----> 1 s = 'hello world'
      2 s[0] = 'H'

TypeError: 'str' object does not support item assignment
```

> **Trap.** Strings are **immutable**. You cannot edit a character by index;
> `s[0] = 'H'` raises `TypeError: 'str' object does not support item
> assignment`. To "change" a string, build a new one (for example by slicing
> and concatenation) and rebind the name.

## Deleting strings

The `del` keyword deletes a name binding entirely. Attempting to delete a part of a string (such as a slice) fails because strings are immutable.

```python
s = 'hello world'
del s
print(s)
```

```text
NameError: name 's' is not defined
```

Attempting to delete a slice:

```python
s = 'hello world'
del s[-1:-5:2]
print(s)
```

```text
TypeError                                 Traceback (most recent call last)
----> 2 del s[-1:-5:2]

TypeError: 'str' object does not support item deletion
```

## Operations on strings

Strings support concatenation and repetition using arithmetic operators, as well as lexicographical comparison using relational operators.

### Arithmetic operations

The `+` operator concatenates two strings. The `*` operator repeats a string a given number of times.

```python
print('delhi' + ' ' + 'mumbai')
```

```text
delhi mumbai
```

```python
print('delhi'*5)
```

```text
delhidelhidelhidelhidelhi
```

```python
print("*"*50)
```

```text
**************************************************
```

### Relational operations

Relational operators (`==`, `!=`, `>`, `<`, `>=`, `<=`) compare strings lexicographically (based on alphabetical order / Unicode values).

```python
print('delhi' != 'delhi')
```

```text
False
```

```python
print('mumbai' > 'pune')
# lexicographically
```

```text
False
```

### Logical operations

Strings can be evaluated as booleans. An empty string is falsy; a non-empty string is truthy.
When using `and`, Python returns the second operand if the first is truthy.
When using `or`, Python returns the first operand if it is truthy.

```python
print('hello' and 'world')
```

```text
world
```

```python
print('hello' or 'world')
```

```text
hello
```

```python
print('' and 'world')
```

```text

```

```python
print(not 'hello')
```

```text
False
```

### Loops on strings

Strings are iterable. You can loop through a string character by character.

```python
for i in 'delhi':
    print('pune')
```

```text
pune
pune
pune
pune
pune
```

### Membership operations

You can check if a substring exists within a string using the `in` and `not in` operators. These operations are case-sensitive.

```python
print('D' not in 'Delhi')
```

```text
False
```

## String functions

Python provides common built-in functions that work with strings, as well as string-specific methods.

### Common functions: len, max, min, sorted

- `len(s)`: Returns the number of characters in the string.
- `max(s)`: Returns the character with the highest Unicode value.
- `min(s)`: Returns the character with the lowest Unicode value.
- `sorted(s)`: Returns a list of characters sorted by their Unicode values.

```python
s = 'hello world'
print(len(s))
```

```text
11
```

```python
print(max(s))
```

```text
w
```

```python
print(min(s))
```

```text
 
```

```python
print(sorted(s))
```

```text
[' ', 'd', 'e', 'h', 'l', 'l', 'l', 'o', 'o', 'r', 'w']
```

### Capitalize, Title, Upper, Lower, Swapcase

These methods return a new string with modified casing.

```python
s = 'hello world'
print(s.capitalize())
```

```text
Hello world
```

```python
print(s.title())
```

```text
Hello World
```

```python
print(s.upper())
```

```text
HELLO WORLD
```

### Count, Find, Index

- `count(substring)`: Returns the number of non-overlapping occurrences of substring.
- `find(substring)`: Returns the lowest index in the string where the substring is found. Returns `-1` if not found.
- `index(substring)`: Like `find()`, but raises a `ValueError` when the substring is not found.

```python
print('my name is nitish'.count('i'))
```

```text
3
```

```python
print('my name is nitish'.find('x'))
```

```text
-1
```

```python
print('my name is nitish'.index('x'))
```

```text
ValueError: substring not found
```

### Endswith and Startswith

These methods return boolean values (`True` or `False`) checking if the string starts or ends with a specified suffix/prefix.

```python
print('my name is nitish'.endswith('sho'))
```

```text
False
```

```python
print('my name is nitish'.startswith('my'))
```

```text
True
```

### String Formatting

The `format()` method formats the specified value(s) and inserts them inside the string's placeholder.

```python
name = 'nitish'
gender = 'male'
print('Hi my name is {} and I am a {}'.format(name, gender))
```

```text
Hi my name is nitish and I am a male
```

You can use index numbers `{0}` to be sure the arguments are placed in the correct placeholders:

```python
print('Hi my name is {1} and I am a {0}'.format(gender, name))
```

```text
Hi my name is nitish and I am a male
```

### String Validation Methods

- `isalnum()`: Returns True if all characters in the string are alphanumeric.
- `isalpha()`: Returns True if all characters in the string are in the alphabet.
- `isdigit()`: Returns True if all characters in the string are digits.
- `isidentifier()`: Returns True if the string is a valid identifier (e.g., variable name).

```python
print('nitish123'.isalnum())
```

```text
True
```

### Split and Join

- `split(separator)`: Splits the string into a list of strings using the given separator. Default separator is whitespace.
- `join(iterable)`: Takes all items in an iterable and joins them into one string. The string on which it is called is used as the separator.

```python
print('hi my name is nitish'.split())
```

```text
['hi', 'my', 'name', 'is', 'nitish']
```

```python
print('hi my name is nitish'.split('i'))
```

```text
['h', ' my name ', 's n', 't', 'sh']
```

```python
print(" ".join(['hi', 'my', 'name', 'is', 'nitish']))
```

```text
hi my name is nitish
```

### Replace

Replaces a specified phrase with another specified phrase.

```python
print('hi my name is nitish'.replace('nitish', 'campusx'))
```

```text
hi my name is campusx
```

### Strip

Removes leading and trailing whitespaces.

```python
print('nitish                     '.strip())
```

```text
nitish
```
```
