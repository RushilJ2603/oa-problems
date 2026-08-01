# Enumerations and Type Aliases

C++ offers two facilities for making code read in terms of the problem rather than in terms of bare machine types: **enumerations**, which give names to a fixed set of related integer values, and **type aliases** created with `typedef`, which give an existing type a second, more meaningful name. Both improve readability without changing what the program computes.

## The problem enumerations solve

Programs constantly encode small fixed sets of choices as integers: a menu's actions, the days of the week, the suits of a deck, a feedback rating. Written as raw numbers these encodings are easy to mistype and hard to read. The recurring pattern is a mapping from a readable name to a small integer code:

| Set | Members and their codes |
| --- | --- |
| Menu (File) | New = 0, Open = 1, Save = 2, Close = 3 |
| Days | Mon = 0, Tue = 1, Wed = 2, ... |
| Card shapes | Club = 0, Spade = 1, Diamond = 2, Hearts = 3 |
| Departments | CSE, ECE, IT, Civil |
| Feedback | poor, satisfactory, good, excellent |

::: definition
An enumeration captures exactly this: it defines a new type whose values are a named, fixed set of constants.
:::

## Declaring and using an enum

An `enum` lists its members in braces. By default the members are numbered automatically from zero, in order:

```cpp
enum day { mon, tue, wed, thu, fri, sat, sun };
// mon = 0, tue = 1, wed = 2, thu = 3, fri = 4, sat = 5, sun = 6
```

The enum name becomes a *data type*. A variable of that type may hold only the listed values, and those names can be used directly in expressions and comparisons:

```cpp
int main()
{
    day d;
    d = mon;
    d = fri;
    d = sun;

    if (d == mon)
    {
        // ...
    }
}
```

The same pattern names a set of departments:

```cpp
enum dep { cse, ece, it, civil };   // cse = 0, ece = 1, it = 2, civil = 3

int main()
{
    dep d;
    d = ece;
}
```

::: keypoint
The benefit is that a variable "can have only this set of values," and the code expresses intent (`d == mon`) instead of a magic number (`d == 0`).
:::

## Assigning explicit values

The automatic numbering can be overridden. 

::: keypoint
Any member may be given an explicit value; members that follow without an explicit value continue counting up from the most recent one:
:::

```cpp
enum day { mon = 1, tue, wed = 5, thur, fri, sat = 9, sun };
// mon = 1, tue = 2, wed = 5, thur = 6, fri = 7, sat = 9, sun = 10
```

Here `tue` follows `mon = 1` and so becomes 2; `thur` and `fri` follow `wed = 5` and become 6 and 7; `sun` follows `sat = 9` and becomes 10.

![Enum and Typedef.](assets/fig_20260614_enum-typedef.png)

## Type aliases with `typedef`

::: definition
`typedef` introduces a new name for an existing type. The aliased name is not a new type — it is another spelling of the original — but it documents intent at the point of declaration:
:::

```cpp
typedef int marks;
typedef int rollno;

int main()
{
    marks  m1, m2, m3;   // ints used to store marks
    rollno r1, r2, r3;   // ints used to store roll numbers
}
```

Both `marks` and `rollno` are simply `int`, but the declarations now state what those integers represent: `m1, m2, m3` store marks and `r1, r2, r3` store roll numbers. The aliases make the program self-describing while leaving its behaviour identical to using `int` throughout.
