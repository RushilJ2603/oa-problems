# Programming Paradigms and the Road to Object Orientation

Before studying any single language feature it helps to understand *why* **object-oriented programming** exists at all.

::: definition
A **programming paradigm** is a style of organising code.
:::

The history of these styles is a history of managing growing complexity: each paradigm keeps the previous one's capabilities and adds a new way of grouping related things together so that large programs stay comprehensible.

Four stages mark this evolution, and they are best read left to right as increasing structure.

**Monolithic / basic program.** The earliest style. The entire program is one undivided block of statements with no separation into reusable units. Everything lives together; there is no notion of a named function to call or a structure to group data. This works only for very small programs.

**Procedural / modular (the C style).** Logic is broken into **functions**. The data still lives loosely in the program, but the actions performed on that data are now packaged into named, callable routines — `function1()`, `function2()`, and so on — which `main()` invokes in sequence. This separates *what is done* into units, but the data and the functions that operate on it are still kept apart.

**Modular with structures.** A refinement of the procedural style. Related data fields are bundled into a **structure** (`data1, data2, data3` grouped under one `structure Info`). Functions then receive that whole structure as an argument — `function1(Info)`, `function2(Info)`. Data that belongs together now travels together, but the functions are still defined separately from the data they act on.

**Object-oriented.** The final step fuses the two halves. A **class** binds both the data **and** the functions that operate on that data into a single unit (`class Info` containing `data1; data2; data3; function1(); function2();`). In `main()` one then creates **objects** of that class (`Info i;`) and calls the functions *through* the object (`i.function1(); i.function2();`). Data and behaviour are no longer separate concerns kept in different places — they are **encapsulated** together, and code is organised around the *things* (objects) in the problem rather than around a flat list of procedures.

The whiteboard below shows all four columns side by side, making the progression from a single block, to functions, to structures-plus-functions, to a unified class explicit.

![Programming paradigms: the progression from a monolithic program, through procedural and structure-based modular styles, to the object-oriented model where data and functions are unified inside a class.](assets/paradigms-whiteboard.png)

::: keypoint
The guiding intuition is one of grouping. Each paradigm answers the question "what belongs together?" with a larger, more meaningful unit than the last — culminating in the object, which keeps state and the operations on that state in one place.
:::
