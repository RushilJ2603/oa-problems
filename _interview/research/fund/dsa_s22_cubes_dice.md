# Cubes, Dice & Cutting Problems

<br>

::: definition
**Cube Painting Formulas**
For a solid painted cube cut into $n^3$ identical smaller cubes (where $n$ is the number of divisions along one edge):

- **3 faces painted** (the corners): $8$
- **2 faces painted** (the edges): $12(n-2)$
- **1 face painted** (the face centres): $6(n-2)^2$
- **0 faces painted** (the inner core): $(n-2)^3$
Total smaller cubes $= n^3$.
:::

<br>

::: keypoint
**Dice Rules**

- **Standard Die:** Opposite faces always sum to $7$ (e.g., $1$ is opposite $6$).
- **One Common Face (Rotation Rule):** If two views of a die share exactly one face, write the faces in clockwise order starting from the common face. The corresponding terms in both sequences are opposite to each other.
- **Two Common Faces:** If two views share two faces, the remaining unmatched faces in each view are opposite to each other.
:::

## Painted-cube counting

<br>

::: trap
**The $n \ge 3$ trap**
The formulas for 1-face and 2-face painted cubes rely on the term $(n-2)$. This means the formulas only apply when $n \ge 3$. If $n=2$, the cube is entirely corners, so $(n-2)=0$, yielding exactly $8$ cubes with 3 painted faces and $0$ cubes with fewer painted faces.
:::

**Q1.** A solid cube is painted blue on all sides and then cut into $125$ smaller, identical cubes. How many of the smaller cubes have exactly one face painted?

(a) $27$
(b) $36$
(c) $54$
(d) $64$

**Solution:**
The total number of cubes is $n^3 = 125$, so $n = 5$.
The number of cubes with exactly one face painted (the face centres) is $6(n-2)^2$.
Substitute $n = 5$: $6(5-2)^2 = 6(3)^2 = 6(9) = 54$.

**Answer:** $54$ (c)

**Q2.** A painted cube is divided into $343$ identical smaller cubes. How many of the smaller cubes have at least two faces painted?

(a) $44$
(b) $60$
(c) $68$
(d) $72$

**Solution:**
Total cubes $= n^3 = 343$, giving $n = 7$.
"At least two faces painted" means the sum of cubes with exactly 2 faces painted and those with 3 faces painted.
2-face painted (edges) $= 12(n-2) = 12(7-2) = 12(5) = 60$.
3-face painted (corners) $= 8$ (always).
Total $= 60 + 8 = 68$.

**Answer:** $68$ (c)

**Q3.** A larger cube is painted on all six faces and cut into a certain number of identical smaller cubes. If exactly $216$ of the smaller cubes have no faces painted, what is the total number of smaller cubes?

(a) $343$
(b) $512$
(c) $729$
(d) $1000$

**Solution:**
The formula for unpainted inner cubes is $(n-2)^3$.
Set $(n-2)^3 = 216$. Since $6^3 = 216$, we have $n-2 = 6 \implies n = 8$.
The total number of cubes is $n^3 = 8^3 = 512$.

**Answer:** $512$ (b)

**Q4.** A solid cube has five of its faces painted red and one face unpainted. It is then cut into $64$ smaller, identical cubes. How many of the smaller cubes have exactly one face painted red?

(a) $20$
(b) $24$
(c) $28$
(d) $32$

**Solution:**
Total cubes $n^3 = 64 \implies n = 4$.
A small cube has exactly 1 face painted if it is:

1. A centre cube on one of the $5$ painted faces. Count: $5 \times (n-2)^2 = 5 \times (4-2)^2 = 20$.
2. An edge cube touching the unpainted face (it touches 1 painted face and 1 unpainted face). The unpainted face has $4$ edges, each containing $(n-2)$ cubes. Count: $4 \times (4-2) = 8$.
Total $= 20 + 8 = 28$.

**Answer:** $28$ (c)

**Q5.** A cube is painted such that two opposite faces are red, two opposite faces are blue, and two opposite faces are green. It is then cut into $216$ identical small cubes. How many small cubes have exactly one red and one blue face painted (and no green)?

(a) $8$
(b) $12$
(c) $16$
(d) $24$

**Solution:**
Total cubes $n^3 = 216 \implies n = 6$.
Cubes with exactly two faces painted are located on the edges. There are $12$ edges in total, and each edge has $(n-2)$ such cubes.
Since opposite faces have the same color, no edge can be formed by two faces of the same color.
The $12$ edges are divided equally among the color boundaries: Red-Blue, Blue-Green, and Green-Red.
Thus, there are $4$ edges where a red face meets a blue face.
The number of cubes with exactly one red and one blue face is $4(n-2)$.
Substitute $n = 6$: $4(6-2) = 4(4) = 16$.

**Answer:** $16$ (c)

**Q6.** A large cube is painted black on all faces except one top face and one adjacent side face, which are left unpainted. It is cut into $64$ small cubes. How many small cubes have exactly zero faces painted?

(a) $12$
(b) $16$
(c) $18$
(d) $20$

**Solution:**
We have $n^3 = 64 \implies n = 4$.
Usually, the number of 0-face painted cubes is $(n-2)^3 = 8$.
Since two adjacent faces are unpainted, any small cube on those faces that would normally have paint *only* from those faces now becomes 0-face painted.

- Centre cubes on the unpainted top face: $(n-2)^2 = 4$.
- Centre cubes on the unpainted side face: $(n-2)^2 = 4$.
- The edge cubes shared between these two unpainted faces: $(n-2) = 2$.
Total 0-face painted cubes $= 8 \text{ (inner)} + 4 \text{ (top centre)} + 4 \text{ (side centre)} + 2 \text{ (shared edge)} = 18$.

**Answer:** $18$ (c)

## Cutting / minimum cuts

**Q7.** What is the minimum number of straight planar cuts required to divide a solid cube into $125$ identical smaller cubes?

(a) $10$
(b) $12$
(c) $15$
(d) $25$

**Solution:**
To cut a cube into $n \times n \times n$ identical pieces, we need $n-1$ cuts along each of the three perpendicular axes.
Here, $125 = 5 \times 5 \times 5$, so $n = 5$.
We need $4$ cuts along the length, $4$ cuts along the width, and $4$ cuts along the height.
Total cuts $= 4 + 4 + 4 = 12$.

**Answer:** $12$ (b)

**Q8.** What is the maximum number of identical pieces a cube can be cut into using exactly $10$ straight cuts?

(a) $64$
(b) $72$
(c) $80$
(d) $100$

**Solution:**
Let the number of cuts along the three axes be $x$, $y$, and $z$. We are given $x + y + z = 10$.
The total number of pieces is $(x+1)(y+1)(z+1)$.
To maximize this product, $x$, $y$, and $z$ should be as close to each other as possible.
We distribute $10$ evenly: $3$, $3$, and $4$.
The number of pieces is $(3+1)(3+1)(4+1) = 4 \times 4 \times 5 = 80$.

**Answer:** $80$ (c)

**Q9.** You have a block of cheese and want to divide it into exactly $60$ identical pieces using the minimum number of straight cuts. If the pieces must form a grid (no restacking), how many cuts are needed?

(a) $9$
(b) $10$
(c) $11$
(d) $12$

**Solution:**
The number of pieces is $x \cdot y \cdot z = 60$. The number of cuts is $(x-1) + (y-1) + (z-1) = x + y + z - 3$.
To minimize $x + y + z$, we need the factors of $60$ to be as close to each other as possible.
The prime factorization is $60 = 2 \times 2 \times 3 \times 5$.
The closest three factors are $3$, $4$, and $5$ (since $3 \times 4 \times 5 = 60$).
Total cuts $= (3-1) + (4-1) + (5-1) = 2 + 3 + 4 = 9$.

**Answer:** $9$ (a)

**Q10.** What is the minimum number of straight planar cuts needed to divide a cube into $64$ identical pieces, assuming you are allowed to restack the pieces between cuts?

(a) $6$
(b) $9$
(c) $12$
(d) $16$

**Solution:**
Without restacking, we need $3+3+3 = 9$ cuts.
With restacking, a single cut can double the total number of pieces. To get $N$ pieces, the theoretical minimum number of cuts is $\lceil \log_2 N \rceil$.
For $64$ pieces, $\log_2 64 = 6$.
We can achieve this by halving the block along its length (1 cut $\rightarrow$ 2 pieces), stacking them and halving again (1 cut $\rightarrow$ 4 pieces). Doing this 2 times for each of the 3 dimensions yields $2+2+2 = 6$ cuts.

**Answer:** $6$ (a)

## Standard dice — opposite faces

<br>

::: trap
**The sum-to-7 assumption**
Do not assume every die is a "standard die" where opposite faces sum to $7$ unless the problem explicitly states it or only provides one view. If multiple views of a die are given, deduce the opposites purely from the rotations.
:::

**Q11.** A standard die is rolled. If the number $2$ is on the front face and $3$ is on the top face, what number is on the bottom face?

(a) $1$
(b) $4$
(c) $5$
(d) $6$

**Solution:**
In a standard die, the sum of numbers on opposite faces is always $7$.
The face opposite to the top face is the bottom face.
Since the top face is $3$, the bottom face is $7 - 3 = 4$. (The front face is extra information).

**Answer:** $4$ (b)

**Q12.** Two positions of the same die are shown below. Which number is on the face opposite to $4$?
```text
Position 1: Top=3, Front=1, Right=4
Position 2: Top=3, Front=6, Right=2
```

(a) $1$
(b) $2$
(c) $5$
(d) $6$

**Solution:**
Both positions share exactly one common face: $3$.
Starting from $3$, write the numbers in clockwise order for both positions.
Position 1 (from Top to Right to Front): $3 \rightarrow 4 \rightarrow 1$.
Position 2 (from Top to Right to Front): $3 \rightarrow 2 \rightarrow 6$.
Comparing the corresponding positions in the sequences, $4$ is opposite $2$, and $1$ is opposite $6$. The remaining number $5$ is opposite $3$.

**Answer:** $2$ (b)

**Q13.** Two positions of a die are shown below. What number is opposite to $6$?
```text
Position 1: Top=6, Front=2, Right=4
Position 2: Top=4, Front=5, Right=3
```

(a) $1$
(b) $2$
(c) $3$
(d) $5$

**Solution:**
The two views share exactly one number: $4$.
Write the visible faces in clockwise sequence starting from the common face.
Position 1: $4 \rightarrow 6 \rightarrow 2$.
Position 2: $4 \rightarrow 5 \rightarrow 3$.
Matching the corresponding positions, $6$ is opposite $5$, and $2$ is opposite $3$.

**Answer:** $5$ (d)

**Q14.** Two views of a die are shown below. Which symbol is opposite to the circle `O`?
```text
Position 1: Top=O, Front=X, Right=@
Position 2: Top=@, Front=X, Right=#
```

(a) `X`
(b) `@`
(c) `#`
(d) Cannot be determined

**Solution:**
Both views share exactly two faces: `X` and `@`.
When two positions share two faces, the third faces in both views must be opposite to each other.
Therefore, `O` (from Position 1) is opposite `#` (from Position 2).

**Answer:** `#` (c)

## Dice folding (net $\rightarrow$ cube)

**Q15.** The following net is folded to form a cube. Which number will be opposite to $2$?
```text
    [1]
[4] [2] [3]
    [5]
    [6]
```

(a) $1$
(b) $3$
(c) $5$
(d) $6$

**Solution:**
In a standard cross-shaped net, faces that are in a straight line and separated by exactly one face are opposite each other.
Looking at the vertical line: $1$ is separated from $5$ by $2$, so $1$ and $5$ are opposite. $2$ is separated from $6$ by $5$, so $2$ and $6$ are opposite.
Looking at the horizontal line: $4$ and $3$ are separated by $2$, so $4$ and $3$ are opposite.
The number opposite to $2$ is $6$.

**Answer:** $6$ (d)

**Q16.** Consider the following Z-shaped net folded into a cube:
```text
[A] [B]
    [C] [D]
        [E] [F]
```
Which face will be opposite to `C`?

(a) `A`
(b) `E`
(c) `F`
(d) `B`

**Solution:**
In a stair-step (Z-shape) net, we can find opposite faces using the "Z-rule": the ends of any Z-shape composed of four squares are opposite each other.

- The squares `A`, `B`, `C`, `D` form a Z-shape, so `A` is opposite `D`.
- The squares `B`, `C`, `D`, `E` form a Z-shape, so `B` is opposite `E`.
- The squares `C`, `D`, `E`, `F` form a Z-shape, so `C` is opposite `F`.
The face opposite `C` is `F`.

**Answer:** `F` (c)

**Q17.** A cube is formed by folding the given net. Which of the following 3D views is a valid representation of this cube?
```text
      [=]
  [*] [+] [%]
      [#]
      [@]
```
View 1: Top `=`, Front `+`, Right `%`

View 2: Top `*`, Front `#`, Right `%`

View 3: Top `@`, Front `#`, Right `*`

(a) View 1 only
(b) View 2 only
(c) View 1 and 3
(d) View 3 only

**Solution:**
First, identify the opposite pairs using the alternate-face rule:

- `=` is opposite `#` (vertical).
- `+` is opposite `@` (vertical).
- `*` is opposite `%` (horizontal).
Any valid 3D view cannot show two opposite faces simultaneously.

- View 1 shows `=`, `+`, `%`. None are opposite pairs. In the net, if `+` is Front and `%` is Right, the Top face would be `=`. This matches exactly. View 1 is valid.
- View 2 shows `*` and `%`. These are opposite faces, so they cannot both be visible. View 2 is invalid.
- View 3 shows `@`, `#`, `*`. None are opposite. If we fold the net with `+` as Front, then Top = `=`, Bottom = `#`, Left = `*`, Right = `%`, and Back = `@`. To make `#` the Front and `@` the Top, we pitch the cube down 90 degrees. Left and Right remain the same, so Right should be `%`. View 3 incorrectly places `*` on the Right. View 3 is invalid.
Therefore, only View 1 is valid.

**Answer:** View 1 only (a)

## Wrapped OA variants

<br>

::: interview
**The hidden parameters trick**
In OAs, a standard painted cube question is often wrapped in a story with physical dimensions (e.g., cm or inches) to obscure $n$. You must first calculate $n = (\text{large edge}) / (\text{small edge})$ before applying the standard formulas.
:::

**Q18.** A carpenter has a solid block of oak measuring $15\text{ cm} \times 15\text{ cm} \times 15\text{ cm}$. He paints the entire exterior of the block with a thick layer of gold paint. After it dries, he feeds it into a precision saw, cutting it entirely into smaller, perfect $3\text{ cm} \times 3\text{ cm} \times 3\text{ cm}$ cubes. He then randomly selects one of the small cubes from the pile. What is the probability that the selected cube has exactly one face painted gold?

(a) $24/125$
(b) $36/125$
(c) $54/125$
(d) $64/125$

**Solution:**
First, find $n$, the number of small cubes along one edge:
$n = 15\text{ cm} / 3\text{ cm} = 5$.
The total number of small cubes is $n^3 = 5^3 = 125$.
The number of cubes with exactly one painted face (the face centres) is $6(n-2)^2$.
Substitute $n = 5$: $6(5-2)^2 = 6(3)^2 = 6 \times 9 = 54$.
The probability of selecting one of these is $\frac{54}{125}$.

**Answer:** $54/125$ (c)

## Sources

- IndiaBix — Cubes and Dice (Non-Verbal Reasoning) — https://www.indiabix.com/non-verbal-reasoning/cubes-and-dice/
- CareerBless — Cube Painted and Cut Problems — http://www.careerbless.com/aptitude/qa/home.php
- GeeksforGeeks — Aptitude Dice Reasoning — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- PrepInsta — Logical Reasoning Cubes & Dice — https://prepinsta.com/
