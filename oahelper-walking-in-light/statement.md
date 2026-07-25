# Walking In Light

You are stranded in a dark field at night. Scattered across the field are **N** lamps; each lamp lights a perfect disk of radius **R_i** centered at **(X_i, Y_i)**. A point on the boundary of a disk is considered lit and therefore safe.

You may move freely inside any single lit disk, and you may cross from one disk into another wherever the two disks **overlap or touch**. Your entire path from the start point **S** to the end point **T** must stay inside the union of the lit disks.

It is guaranteed that both **S** and **T** already lie inside at least one disk. Decide whether a safe path from **S** to **T** exists.

## Input Format

- Line 1: integer **N** — the number of lamps.
- Next **N** lines: three real numbers **X_i Y_i R_i** — center and radius of lamp *i*.
- Last line: four real numbers **X_s Y_s X_t Y_t** — coordinates of **S** and **T**.

Coordinates and radii may contain decimal points.

## Output Format

Print `YES` if a safe path exists, otherwise print `NO`. Letter case does not matter.

## Constraints

- \(1 \le N \le 10^3\)
- \(-10^8 \le X_i, Y_i, X_s, Y_s, X_t, Y_t \le 10^8\)
- \(1 \le R_i \le 10^8\)

## Examples

### Example 1

**Input:**
```
3
0 0 4
9 0 4
4.5 1.5 1
1 2 9 0
```

**Output:**
```
YES
```

The middle lamp bridges the first two disks, so **S** can reach **T**.

### Example 2

**Input:**
```
2
0 0 3
6 0 3
0 0 6 0
```

**Output:**
```
YES
```

The two disks touch at \((3, 0)\), which is enough to cross.

### Example 3

**Input:**
```
2
0 0 3
10 0 3
0 0 10 0
```

**Output:**
```
NO
```

The disks are separated; no safe crossing exists.

### Example 4

**Input:**
```
1
0 0 10
-5 0 5 0
```

**Output:**
```
YES
```

Both points lie in the same single disk.
