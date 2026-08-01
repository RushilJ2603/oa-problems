# Cryptarithmetic & Symbol Arithmetic

::: definition
**Cryptarithmetic Rules:**

1. Each letter represents a **distinct digit** from $0$ to $9$.
2. The **leading digit** of any number is never $0$.
3. Solve **column by column** from the right, tracking the **carry**. 
4. In the addition of two numbers, the carry to the next column is always **$0$ or $1$**. (The maximum sum of two digits plus a carry is $9 + 9 + 1 = 19$).
:::

**Q1. (Flagship) Find the values of the letters in the classic puzzle:**
`  S E N D`
`+ M O R E`
`---------`
`M O N E Y`

**Solution:**
Solve column by column:

1. **Ten-thousands column:** $M$ is the carry from the thousands column. Since the max carry from adding two digits is $1$, **$M = 1$**.
2. **Thousands column:** $S + M + c = MO \implies S + 1 + c = 10 + O$. To reach $\ge 10$, $S$ must be $8$ or $9$. If $S=9$ and $c=0$, then $O=0$. (If $S=8, c=1 \implies O=0$). Thus, **$O = 0$**.
3. **Hundreds column:** $E + O + c = N \implies E + 0 + c = N$. Since letters must be distinct, $E \neq N$, so there must be a carry ($c=1$). Thus, $E + 1 = N$.
4. **Tens column:** $N + R + c = E + 10$. Substitute $N = E+1$ to get $(E+1) + R + c = E + 10 \implies R + c = 9$. Since $S=9$, $R$ cannot be $9$. Thus $R = 8$ and the carry in is $1$.
5. **Units column:** $D + E = Y + 10$ (since it must generate the carry $c=1$ for the tens column). 
Available digits: $2, 3, 4, 5, 6, 7$. We need $E+1=N$ and $D+E \ge 10$. Trying $E=5 \implies N=6$. Then $D+5 = Y+10 \implies D=Y+5$. From the remaining digits ($2, 3, 4, 7$), $D=7$ and $Y=2$ fits perfectly.

**Answer:** $O=0, M=1, Y=2, E=5, N=6, D=7, R=8, S=9$

## Addition Cryptarithms

**Q2.** Solve the classic addition and find the 5-digit number `APPLE`:
`    E A T`
`+ T H A T`
`---------`
`A P P L E`

**Solution:**

1. **Size bound (the key first move):** $EAT + THAT \le 999 + 9999 = 10998 < 11000$, and the sum has $5$ digits, so it lies in $[10000, 10998]$. Its ten-thousands digit is therefore $1$ and its thousands digit is $0$: **$A = 1$** and **$P = 0$**.
2. **Thousands column:** $T + c_3 = P + 10 = 10$ (the $10$ carries out to make the ten-thousands digit $A=1$). Since the carry-in $c_3 \le 1$, this forces $T = 9$ and $c_3 = 1$.
3. **Units column:** $T + T = 9 + 9 = 18 = E + 10 \implies E = 8$, with carry $c_1 = 1$.
4. **Tens column:** $A + A + c_1 = 1 + 1 + 1 = 3$. There is no carry, so $c_2 = 0$ and $L = 3$.
5. **Hundreds column:** $E + H + c_2 = P + 10c_3 \implies 8 + H + 0 = 0 + 10 \implies H = 2$.
All six letters are distinct: $E=8,\, A=1,\, T=9,\, H=2,\, P=0,\, L=3$. Check: $819 + 9219 = 10038$.

**Answer:** $APPLE = 10038$ (the unique solution)

::: interview
Constraint satisfaction problems like these are graded on speed. Always start with the most-constrained column — usually the leftmost column (which dictates carries) or the rightmost column (which dictates parity).
:::

**Q3.** In the equation `GO + TO = OUT`, what is the 3-digit number `OUT`?

**Solution:**

1. **Hundreds:** $O$ is the carry from the tens column ($G+T$), so $O = 1$.
2. **Units:** $O + O = T \implies 1 + 1 = 2$. So $T = 2$.
3. **Tens:** $G + T = OU \implies G + 2 = 10 + U$ (since $O=1$). So $G = U + 8$.
Since $G \le 9$, $U$ can be $0$ or $1$. But $O=1$, so $U=0$. This forces $G=8$.
Equation: $81 + 21 = 102$.

**Answer:** $102$

**Q4.** If $W$ is a prime digit, find the value of $E$ in the addition `WE + WE = TOO`.

**Solution:**

1. $T$ is the carry-out, so $T=1$.
2. Tens: $W + W + c = 10 + O$.
3. Units: $E + E = O$ (or $O+10$).
Assume no carry from units ($c=0$): $O$ must be even. 
Since $W$ is a prime digit ($2, 3, 5, 7$), try $W=7$. 
Then $7 + 7 = 14 \implies O=4$.
From units: $E + E = 4 \implies E=2$.
Equation: $72 + 72 = 144$. All letters distinct.

**Answer:** $E = 2$

**Q5.** In the addition `ONE + ONE = TWO`, if $O$ is an even digit and $T=8$, find the value of $W$.

**Solution:**

1. Hundreds: $O + O + c = T \implies O + O + c = 8$. Since $O$ is an even digit, $c=0$ and $O=4$.
2. Units: $E + E = O \implies E + E = 4$. So $E=2$ (since $c=0$ for the tens column, $E+E$ cannot be $14$).
3. Tens: $N + N = W$. We have used $O=4, E=2, T=8$. Available digits: $0, 1, 3, 5, 6, 7, 9$.
We need $N+N = W$ with no carry (since $c=0$ to hundreds).
Try $N=3 \implies W=6$. (Fits! $432 + 432 = 864$).

**Answer:** $6$

::: trap
A common trap is assuming a letter can take any available digit without checking the whole equation. Every final assignment MUST satisfy the entire sum and maintain distinct digits for all letters.
:::

## Multiplication and Subtraction Cryptarithms

**Q6.** In the subtraction problem `NINE - TEN = TWO`, what is the maximum possible value of the digit $T$?

(a) $7$ (b) $8$ (c) $9$ (d) $6$

**Solution:**
Rewrite as addition: `TWO + TEN = NINE`.

1. **Result length:** 3-digit + 3-digit = 4-digit. Thus, $N = 1$.
2. **Hundreds:** $T + T + c = 10 + I$ (since $N=1$). This means $I$ is odd.
3. **Tens:** $W + E + c = 11$ (must end in $1$ and carry to hundreds).
4. **Units:** $O + 1 = E$ (if no carry).
To maximize $T$, try $T=9$. Then $9+9+c \ge 18 \implies I=8$ or $9$. But $I$ is odd, so $I=9$ (conflict with $T=9$).
Try $T=8$: $8+8+1 = 17 \implies I=7$.
If $T=8, I=7, N=1$. Available: $0, 2, 3, 4, 5, 6, 9$.
We need $O + 1 = E$ and $W + E = 11$.
Substituting $E$: $W + O + 1 = 11 \implies W + O = 10$.
Pairs for $10$ from available: $(4, 6)$.
If $O=4, W=6$, then $E = 4+1=5$.
Check distinct: $T(8), W(6), O(4), E(5), N(1), I(7)$. All distinct!
Equation: $864 + 851 = 1715$.

**Answer:** $8$ (b)

**Q7.** Find the value of $C$ if $AB \times 4 = CA$. (Here $AB$ and $CA$ are two-digit numbers).

**Solution:**

1. **Units:** $B \times 4$ ends in $A$. This implies $A$ must be an even digit.
2. **Tens:** $A \times 4 + \text{carry} = C$. Since $CA$ is a two-digit number, $C$ is a single digit. This means $A$ can only be $1$ or $2$.
3. Since $A$ is even, $A = 2$.
4. Back to units: $B \times 4$ ends in $2$. Thus $B$ can be $3$ or $8$.
If $B = 8$: $28 \times 4 = 112$ (3 digits, invalid).
If $B = 3$: $23 \times 4 = 92$. This matches $CA \implies C=9, A=2$.

**Answer:** $9$

**Q8.** In the multiplication $PQ \times 3 = RQQ$, find the values of the distinct digits $P, Q,$ and $R$.

**Solution:**

1. **Units:** $Q \times 3$ ends in $Q$. The only digits where this is true are $0$ ($0 \times 3 = 0$) and $5$ ($5 \times 3 = 15$).
If $Q = 0$: $P0 \times 3 = R00 \implies P \times 3 = R0 \implies P$ must be at least $10$, impossible.
Thus, $Q = 5$.
2. **Tens:** $P5 \times 3 = R55$. 
$5 \times 3 = 15$, so there is a carry of $1$.
$P \times 3 + 1$ ends in $5$.
This means $P \times 3$ ends in $4$. The only digit is $P = 8$ ($8 \times 3 = 24$).
3. **Full equation:** $85 \times 3 = 255$. So $R = 2$.

**Answer:** $P=8, Q=5, R=2$

## Find-the-Digit Equations

**Q9.** The sum of $3A5$ and $2B7$ is $6C2$. If $A, B, C$ are distinct digits, what is the value of $C$?

**Solution:**
Set up the addition:
`  3 A 5`
`+ 2 B 7`
`-------`
`  6 C 2`

1. **Units:** $5 + 7 = 12$. Write down $2$, carry $1$.
2. **Hundreds:** $3 + 2 + c = 6$. The carry $c$ from the tens column must be $1$.
3. **Tens:** $1 (\text{carry}) + A + B = 10 + C \implies A + B = C + 9$.
We need $A$ and $B$ to be $\le 9$. The max sum $A+B = 17$ (since they are distinct, e.g., $8+9$).
If $C=8 \implies A+B=17 \implies 8, 9$ (conflicts with $C=8$).
If $C=7 \implies A+B=16 \implies 7, 9$ (conflicts with $C=7$).
If $C=6 \implies A+B=15 \implies 6, 9$ (conflicts with $C=6$) or $7, 8$.
So $A, B$ are $7, 8$ and $C=6$.
Check: $375 + 287 = 662$.

**Answer:** $6$

::: keypoint
For "Find the digit" problems with explicit numbers, immediately compute the carries generated by the given constants. This directly translates the letters into a simple algebraic equation like $A + B = C + 9$.
:::

**Q10.** In the sum $4A6 + 3B8 = 8C4$, find the exact value of $A + B - C$.

**Solution:**

1. **Units:** $6 + 8 = 14$. Write $4$, carry $1$.
2. **Hundreds:** $4 + 3 + c_{\text{tens}} = 8 \implies c_{\text{tens}} = 1$.
3. **Tens:** $1 (\text{carry}) + A + B = C + 10$ (must yield carry of 1).
$A + B - C = 10 - 1 = 9$.

**Answer:** $9$

**Q11.** Given $5A2 + 3B9 = C21$, where $A$ and $B$ are non-zero digits, find $C$.

**Solution:**

1. **Units:** $2 + 9 = 11$. Write $1$, carry $1$.
2. **Tens:** $1 + A + B = 2$ or $12$.
If it equals $2$, $A+B=1$, meaning one is $0$ (but they are non-zero).
So $1 + A + B = 12 \implies$ carry to hundreds is $1$.
3. **Hundreds:** $5 + 3 + 1 = C \implies C = 9$.

**Answer:** $9$

## Symbol & Operator Substitution

**Q12.** If $+$ means $\times$, $-$ means $\div$, $\times$ means $-$, and $\div$ means $+$, what is the value of $16 - 4 + 2 \times 5 \div 3$?

(a) $6$ (b) $8$ (c) $12$ (d) $10$

**Solution:**
Translate the expression using the given rules:
$16 \div 4 \times 2 - 5 + 3$
Apply BODMAS (Division, then Multiplication, then Addition/Subtraction):
$16 \div 4 = 4$
$4 \times 2 = 8$
$8 - 5 + 3 = 6$

**Answer:** $6$ (a)

**Q13.** In a certain code, digits $1-9$ are represented by letters.
$A + A = B$
$B \times B = C$
$C + B = D$
If $A, B, C, D$ represent distinct digits, what digit does $D$ represent?

**Solution:**

1. $B \times B = C$, and $C$ is a single digit. $B$ cannot be $1$ (else $C=1=B$). So $B$ is $2$ or $3$.
2. If $B = 3$, then $A+A=3$, which means $A=1.5$ (not a digit). So $B$ must be even.
3. Therefore, $B = 2$.
4. $A + A = 2 \implies A = 1$.
5. $C = 2 \times 2 \implies C = 4$.
6. $D = 4 + 2 \implies D = 6$.

**Answer:** $6$

**Q14.** An operator $\Delta$ is defined for single digits as $x \Delta y = x^2 + y^2 - xy$.
Find the value of $(2 \Delta 3) \Delta 1$.

**Solution:**
Evaluate the parenthesis first:
$2 \Delta 3 = 2^2 + 3^2 - 2(3) = 4 + 9 - 6 = 7$.
Now evaluate $7 \Delta 1$:
$7 \Delta 1 = 7^2 + 1^2 - 7(1) = 49 + 1 - 7 = 43$.

**Answer:** $43$

## Wrapped OA Variants

**Q15.** (eLitmus) An encryption algorithm logs a 4-digit key via the equation `KEY + KEY = LOCK`. Assuming each letter represents a distinct digit from $0-9$, $K \neq 0$, $L \neq 0$, and given that $K = 8$ and $E = 3$, what is the 4-digit key $LOCK$?

**Solution:**
`  8 3 Y`
`+ 8 3 Y`
`-------`
`L O C 8`

1. **Thousands/Hundreds:** $8 + 8 + c = LO$. Since the maximum carry is $1$, $LO$ is $16$ or $17$. So $L=1$.
2. **Tens:** $3 + 3 + c = C$. $C$ is either $6$ or $7$, which means there is no carry to the hundreds column. Thus $LO = 16 \implies O=6$.
3. **Units:** $Y + Y = 8$ or $18$. 
If $Y = 4$: $834 + 834 = 1668 \implies C=6$. But $O=6$, so digits aren't distinct.
If $Y = 9$: $839 + 839 = 1678 \implies C=7$.
Check distinct: $K=8, E=3, Y=9, L=1, O=6, C=7$. All valid!

**Answer:** $1678$

::: trap
Remember the leading-zero ban. In $KEY + KEY = LOCK$, $K$ and $L$ can never be $0$. If you are brute-forcing possibilities, always skip $0$ for the leading letters.
:::

**Q16.** (Amazon) A 4-digit passcode $A B C D$ consists of distinct EVEN digits. It satisfies the rule: 
$A B C \times D = 1728$
Find the sum of the digits $A+B+C+D$.

**Solution:**
$D$ is a single even digit ($2, 4, 6, 8$). Test the divisions:
$1728 \div 8 = 216$ (contains odd digit $1$).
$1728 \div 6 = 288$ (not distinct).
$1728 \div 4 = 432$ (contains odd digit $3$).
$1728 \div 2 = 864$ (Digits: $8, 6, 4, 2$. Distinct and all even!).
So $A=8, B=6, C=4, D=2$.
Sum $= 8 + 6 + 4 + 2 = 20$.

**Answer:** $20$

## Sources

* IndiaBix — https://www.indiabix.com/
* Hitbullseye — https://www.hitbullseye.com/
* PrepInsta (eLitmus Placement Papers) — https://prepinsta.com/
* FacePrep (Cryptarithmetic Tricks) — https://faceprep.in/
