# C-Style Strings and the `<cstring>` Library

::: definition
A **C-style string** is simply a character array terminated by a null character `'\0'`.
:::

That terminator marks where the text ends inside an array that may be larger than the text it holds. The `<cstring>` header — the C++ name for C's `string.h` — provides a family of functions for working with such strings.

## Reading a line of input

Reading a whole line, spaces included, into a character array is done with `cin.getline`, which takes the array and its capacity:

```cpp
char s[100];
std::cout << "Enter your Name ";
std::cin.getline(s, 100);            // reads up to 99 chars + '\0'
std::cout << "Welcome " << s << '\n';
```

::: keypoint
Passing the size lets `getline` stop before overrunning the buffer, leaving room for the terminating `'\0'`.
:::

## Copying: `strcpy` and `strncpy`

`strcpy(destination, source)` copies the source string — character by character, including its `'\0'` — into the destination array:

```cpp
strcpy(destination, source);   // destination becomes a copy of source
```

::: trap
The destination must be large enough to hold the source plus its terminator.
:::

The bounded variant `strncpy(destination, source, length)` copies at most `length` characters, letting the caller cap how much is written.

![Copying with strcpy: the source characters, including the terminator, are written into the destination array.](assets/fig_20260617_strcpy.png)

## Concatenation: `strcat` and `strncat`

`strcat(destination, source)` appends the source onto the end of the destination: it writes the source's characters starting at the destination's existing `'\0'`, then adds a fresh terminator. Appending `"Morning"` onto `"Good"` yields `"GoodMorning"`. The bounded form `strncat(destination, source, length)` appends at most `length` characters of the source.

## Searching: `strstr`, `strchr`, `strrchr`

- `strstr(main, sub)` finds the first occurrence of the substring `sub` inside `main` and returns a pointer to it. Given `s1 = "Programming"` and `s2 = "gram"`, `strstr(s1, s2)` returns `"gramming"` — the tail of `s1` from the first match onward. With `s2 = "m"`, it returns `"mming"`.
- `strchr(main, ch)` finds the **first** occurrence of a single character `ch`; `strrchr(main, ch)` finds the **last** (the extra `r` stands for *reverse*). Each returns a pointer to the found character — that is, the string from that character to the end.

## Comparing: `strcmp`

`strcmp(str1, str2)` compares two strings lexicographically and returns a value whose **sign** carries the result:

- `0` if the strings are equal,
- a **negative** value if `str1` orders before `str2`,
- a **positive** value if `str1` orders after `str2`.

The comparison walks both strings until the first differing character, then compares those characters by their ASCII codes. Because lowercase letters have larger codes than uppercase ones (`'a'` is 97 while `'A'` is 65), letter case affects ordering. Comparing `"apple"` with `"banana"`, for instance, returns a negative value, since `'a'` (97) precedes `'b'` (98).

## Converting strings to numbers: `strtol` and `strtof`

Two functions parse a leading number out of a character string:

- `strtol(str, NULL, base)` converts a string to a **long int** in the given base (for example, base 10).
- `strtof(str, NULL)` converts a string to a **float**.

```cpp
char s1[10] = "235";
char s2[10] = "54.78";

long int x = strtol(s1, NULL, 10);   // 235 as an integer
float    y = strtof(s2, NULL);       // 54.78 as a float
```

The middle argument can capture a pointer to the first unparsed character; passing `NULL` simply discards it.

## Tokenising: `strtok`

`strtok(str, delimiters)` splits a string into **tokens** separated by any of the delimiter characters.

::: keypoint
The first call passes the string; each later call passes `NULL` to continue from where the previous one stopped, and `NULL` is returned once no tokens remain.
:::

```cpp
char s1[20] = "x=10;y=20;z=35";

char* token = strtok(s1, "=;");      // split on '=' and ';'
while (token != NULL)
{
    std::cout << token << '\n';      // x, 10, y, 20, z, 35
    token = strtok(NULL, "=;");
}
```

With the delimiters `"=;"`, the string `"x=10;y=20;z=35"` breaks into `x, 10, y, 20, z, 35`. Choosing only `";"` instead yields the three chunks `"x=10"`, `"y=20"`, `"z=35"` — the layout famously known as *key-value pairs*. The delimiter set is entirely the caller's choice, so the same routine can carve a string along whatever separators the data happens to use.
