# Pointer Arithmetic

::: definition
Because a pointer holds an address, **pointer arithmetic** is defined in terms of the elements it points at, not in raw bytes. Adding one to a pointer advances it to the *next element* of its type, whatever that element's size happens to be.
:::

This is what makes a pointer a natural cursor for walking through an array.

Set up an array and a pointer to its first element:

```cpp
int A[5] = {2, 4, 6, 8, 10};
int* p = A;   // p points at A[0]; an array name decays to the address of its first element
```

Suppose the array begins at address `200` and — for a small, readable example — each `int` occupies 2 bytes. Then the elements sit at addresses `200, 202, 204, 206, 208`, each one element-width apart.

## Increment, decrement, and adding an integer

| Operation | Effect | New address (from `p = 200`) |
| --- | --- | --- |
| `p++;` | advance one element | `202` |
| `p--;` | step back one element | `200` |
| `p = p + 2;` | jump forward two elements | `206` |
| `p = p - 2;` | jump back two elements | `200` |

::: keypoint
The compiler scales every pointer addition by the size of the pointed-to type. The crucial point is that `p++` does **not** add `1` to the address; it adds `1 × sizeof(*p)`.
:::

With 2-byte ints, `p++` moves the stored address from `200` to `202` — forward by one *element*, which here is two bytes. Likewise `p + 2` moves forward by two elements (four bytes here), landing on `206`. Therefore, `p + 2` advances four bytes for 2-byte ints, or eight bytes for 4-byte ints — always two elements.

## Pointer difference: how many elements apart

::: keypoint
**Pointer difference**: Subtracting one pointer from another gives the number of elements between them, not the number of bytes.
:::

Take two pointers into the same array:

```cpp
int* p = A;        // p = 200  (points at A[0])
int* q = &A[3];    // q = 206  (points at A[3])

int d = q - p;     //  3   — q is 3 elements past p
int e = p - q;     // -3   — p is 3 elements before q
```

The arithmetic is `(206 - 200) / sizeof(int) = 6 / 2 = 3`. The division by the element size is automatic: the language reports the gap in elements, not in bytes. The **sign** records direction — a positive difference means the second pointer is *ahead*, a negative difference means it is *behind*. So `q - p = 3` says `q` is three elements after `p`, while `p - q = -3` says `p` is three elements before `q`.

![Pointer arithmetic: increment, decrement, adding an integer, and the element-distance between two pointers.](assets/fig_20260615_pointer-arithmetic.png)

The rule unifying all of this is that pointer arithmetic counts in elements. Whether incrementing, adding an integer, or subtracting two pointers, the address moves in multiples of the pointed-to type's size — which is exactly what lets a pointer step cleanly from one array element to the next.
