# Variable Scope and Storage: Global, Local, and Static

Where a variable is declared controls two things: which code can see it (**scope**) and how long it lives (its **lifetime**, or storage duration).

## Global versus local variables

::: definition
A **global** variable is declared outside every function and is visible to all of them; a **local** variable is declared inside a function or block and is visible only there.
:::

```cpp
int g = 0;            // global: reachable from any function

void fun()
{
    int a = 5;        // local to fun
    g = g + a;        // reads and updates the global
    cout << g;
}

int main()
{
    int x = 10;       // local to main
    g = 15;
    fun();            // g becomes 20
    g++;              // g becomes 21
    cout << g;        // 21
}
```

::: keypoint
Globals are convenient when a value must be reachable by many functions, but for that same reason they can be changed from anywhere, which is why locals are preferred whenever a value is needed in only one place.
:::

## Nested scopes and shadowing

Scopes nest, and an inner declaration may reuse a name from an outer scope. 

::: definition
The inner name then **shadows** the outer one within its block, and an unqualified use refers to the *nearest* enclosing declaration.
:::

```cpp
int x = 10;           // global

int main()
{
    int x = 20;       // shadows the global within main
    {
        int x = 30;   // shadows again within this block
        cout << x;    // 30  (innermost)
    }
    cout << x;        // 20  (main's x)
}
// outside all of these, the global x (10) is what remains
```

Printing `x` at each level yields `30`, then `20`, then `10` — each reference resolving to the closest `x` in scope.

## Static local variables

::: definition
A **static** local variable lives inside a function but, unlike an ordinary local, retains its value between calls.
:::

It is initialised once and persists for the whole run of the program, while staying visible only inside its function:

```cpp
void fun()
{
    static int v = 0;     // initialised once; survives across calls
    int a = 5;            // ordinary local; recreated each call
    v++;
    cout << a << " " << v;
}

int main()
{
    fun();   // a = 5, v = 1
    fun();   // a = 5, v = 2
    fun();   // a = 5, v = 3
}
```

Each call recreates `a` afresh (always 5), but `v` carries over, counting 1, 2, 3 across the three calls.

::: keypoint
A static local thus combines a local's narrow visibility with a global's lifetime.
:::
