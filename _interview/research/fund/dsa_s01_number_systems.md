# Number Systems & Divisibility

::: definition
**Number Types:**

- **Natural ($\mathbb{N}$):** $1, 2, 3, \ldots$
- **Whole:** $0, 1, 2, 3, \ldots$
- **Integers ($\mathbb{Z}$):** $\ldots, -2, -1, 0, 1, 2, \ldots$
- **Rational ($\mathbb{Q}$):** Expressible as $\frac{p}{q}$ where $p, q \in \mathbb{Z}, q \neq 0$. Terminating or repeating decimals.
- **Irrational:** Non-terminating, non-repeating decimals (e.g., $\sqrt{2}, \pi$).
- **Prime:** Exactly two distinct positive divisors: $1$ and itself (Note: $1$ is neither prime nor composite).
- **Composite:** More than two positive divisors.

**Core Tool: Prime Factorisation**
Every integer $N > 1$ can be uniquely expressed as $N = p^{a} q^{b} r^{c} \ldots$ where $p, q, r$ are distinct primes.

- **Number of Factors:** $(a + 1)(b + 1)(c + 1) \ldots$
- **Sum of Factors:** $\left(\frac{p^{a+1} - 1}{p - 1}\right) \left(\frac{q^{b+1} - 1}{q - 1}\right) \ldots$
:::

## Divisibility Rules & Factors

::: keypoint
**Divisibility Shortcuts:**

- **2, 4, 8:** Last 1, 2, 3 digits divisible by 2, 4, 8 respectively.
- **3, 9:** Sum of digits divisible by 3, 9 respectively.
- **5, 10:** Ends in 0/5, or 0 respectively.
- **11:** Difference between the sum of digits in odd positions and even positions is $0$ or a multiple of $11$.
- **Composite (e.g., 72):** Must be divisible by co-prime factors (8 and 9).
:::

**Q1.** What is the value of $x$ if the six-digit number $4x573y$ is divisible by $72$, given that $y$ is a single digit?

(a) $2$
(b) $4$
(c) $6$
(d) $8$

**Solution:**
Divisibility by $72$ requires divisibility by its co-prime factors $8$ and $9$.
Step 1: Check $8$. The last three digits $73y$ must be a multiple of $8$. $720$ is a multiple, so $728$ is, meaning $736$ is. Thus, $y = 6$.
Step 2: Check $9$. The sum of digits must be a multiple of $9$.
$4 + x + 5 + 7 + 3 + 6 = x + 25$.
The next multiple of $9$ after $25$ is $27$, giving $x = 2$.

**Answer:** 2 (a)

**Q2.** If the seven-digit number $136x57y$ is divisible by $11$, and $x + y = 10$, what is the value of $x$?

(a) $3$
(b) $4$
(c) $6$
(d) $7$

**Solution:**
For divisibility by $11$, the difference between the sums of alternating digits must be $0$ or a multiple of $11$.
Odd positions (from left): $1 + 6 + 5 + y = y + 12$.
Even positions (from left): $3 + x + 7 = x + 10$.
Difference: $(y + 12) - (x + 10) = y - x + 2$.
This must be $0, 11, -11, \ldots$
Since $x, y \le 9$, $y - x + 2$ is between $-7$ and $11$.
If $y - x + 2 = 0 \Rightarrow x - y = 2$.
We are given $x + y = 10$.
Adding the two equations: $2x = 12 \Rightarrow x = 6, y = 4$.
(If $y - x + 2 = 11 \Rightarrow y - x = 9$, which means $y = 9, x = 0$, but $x + y = 9 \neq 10$).

**Answer:** 6 (c)

**Q3.** Find the total number of positive factors of $1080$.

(a) $24$
(b) $30$
(c) $32$
(d) $36$

**Solution:**
Step 1: Prime factorise the number.
$1080 = 108 \times 10 = (27 \times 4) \times (2 \times 5) = (3^{3} \times 2^{2}) \times (2^{1} \times 5^{1}) = 2^{3} \times 3^{3} \times 5^{1}$.
Step 2: Add $1$ to each exponent and multiply.
Number of factors $= (3 + 1)(3 + 1)(1 + 1) = 4 \times 4 \times 2 = 32$.

**Answer:** 32 (c)

**Q4.** What is the sum of all positive factors of $360$?

(a) $1170$
(b) $1240$
(c) $1440$
(d) $1500$

**Solution:**
Prime factorise: $360 = 36 \times 10 = 2^{3} \times 3^{2} \times 5^{1}$.
Use the sum of factors formula: $S = \left(\frac{p^{a+1} - 1}{p - 1}\right) \left(\frac{q^{b+1} - 1}{q - 1}\right) \ldots$
For $2^{3}$: $\frac{2^{4} - 1}{2 - 1} = 15$
For $3^{2}$: $\frac{3^{3} - 1}{3 - 1} = 13$
For $5^{1}$: $\frac{5^{2} - 1}{5 - 1} = 6$
Sum $= 15 \times 13 \times 6 = 15 \times 78 = 1170$.

**Answer:** 1170 (a)

**Q5.** In how many ways can $400$ be written as the product of two positive co-prime factors?

(a) $1$
(b) $2$
(c) $4$
(d) $8$

**Solution:**
Two factors $A$ and $B$ are co-prime if their HCF is $1$. This means they cannot share any prime factors.
Prime factorise: $400 = 2^{4} \times 5^{2}$.
To ensure $A$ and $B$ are co-prime, the entire block of $2^{4}$ must go to one factor, and the entire block of $5^{2}$ must go to the other (or one gets everything and the other gets $1$).
The number of distinct prime bases is $n = 2$ (which are $2$ and $5$).
The number of ways to express $N$ as a product of two co-prime factors is $2^{n-1}$.
Ways $= 2^{2-1} = 2$.
(The pairs are $1 \times 400$ and $16 \times 25$).

**Answer:** 2 (b)

**Q6.** A security software generates a valid 5-digit passcode $abcde$. It must be the largest possible multiple of $36$ with all distinct digits, starting with $741$. What is the passcode?

(a) $74124$
(b) $74160$
(c) $74196$
(d) $74182$

**Solution:**
Passcode: $741de$. Divisibility by $36$ means divisible by $4$ and $9$.
For the largest passcode, we want the largest possible $d$ and $e$.
Sum of digits: $7 + 4 + 1 + d + e = 12 + d + e$. This must be a multiple of $9$ ($18$ or $27$).
Since $d, e \le 9$, max $12 + d + e = 30$. So the sum can be $18$ or $27$.
Case sum $= 27 \Rightarrow d + e = 15$.
Since digits must be distinct from $\{1, 4, 7\}$, possible pairs for $(d, e)$ from remaining $\{0, 2, 3, 5, 6, 8, 9\}$ adding to $15$ are $(6, 9)$ and $(9, 6)$.
Check divisibility by $4$ (last two digits):

- $69$ is not divisible by $4$.
- $96$ is divisible by $4$.
Thus, $74196$ satisfies all conditions (distinct digits, multiple of $36$). Since it uses the largest possible sum ($27$) and largest $d=9$, it is the maximum.

**Answer:** 74196 (c)

## HCF & LCM

::: keypoint

- **Fractions:** $\text{HCF} = \frac{\text{HCF of numerators}}{\text{LCM of denominators}}$, $\text{LCM} = \frac{\text{LCM of numerators}}{\text{HCF of denominators}}$.
- **Core Property:** For any two numbers $A$ and $B$, $\text{HCF}(A,B) \times \text{LCM}(A,B) = A \times B$.
:::

**Q7.** The HCF of two numbers is $15$ and their LCM is $225$. If one number is $75$, find the other.

(a) $15$
(b) $45$
(c) $60$
(d) $105$

**Solution:**
Use the property: $A \times B = \text{HCF} \times \text{LCM}$.
$75 \times B = 15 \times 225$
$B = \frac{15 \times 225}{75} = \frac{225}{5} = 45$.

**Answer:** 45 (b)

**Q8.** Three numbers are in the ratio $3 : 4 : 5$ and their LCM is $2400$. What is their HCF?

(a) $40$
(b) $80$
(c) $120$
(d) $200$

**Solution:**
Let the numbers be $3x, 4x,$ and $5x$.
Their HCF is clearly $x$ (since $3, 4, 5$ are pairwise co-prime).
Their LCM is the product of their HCF and the co-prime ratios: $\text{LCM} = x \times 3 \times 4 \times 5 = 60x$.
We are given $\text{LCM} = 2400$.
$60x = 2400 \Rightarrow x = 40$.
Since $x$ is the HCF, it is $40$.

**Answer:** 40 (a)

**Q9.** Five bells toll at intervals of $4, 6, 7, 8,$ and $12$ seconds respectively. If they start tolling together, how many times will they toll together in $1$ hour (excluding the start)?

(a) $19$
(b) $20$
(c) $21$
(d) $22$

**Solution:**
The bells will toll together after an interval equal to the LCM of their individual tolling times.
$\text{LCM}(4, 6, 7, 8, 12) = 168$ seconds.
Time given $= 1$ hour $= 3600$ seconds.
Number of times they toll together $= \lfloor \frac{3600}{168} \rfloor = \lfloor 21.42 \rfloor = 21$.

**Answer:** 21 (c)

**Q10.** A rectangular courtyard is $18$ m $72$ cm long and $13$ m $20$ cm broad. It is to be paved exactly with square tiles of the same size. What is the minimum number of such tiles required?

(a) $4290$
(b) $4350$
(c) $4410$
(d) $4500$

**Solution:**
First, convert to identical units: length $= 1872$ cm, breadth $= 1320$ cm.
To minimise the number of tiles, the size of each square tile must be the maximum possible.
Maximum side of the square tile $= \text{HCF}(1872, 1320)$.
Using prime factorisation or division method:
$1872 = 24 \times 78 = 24 \times 6 \times 13 = 2^{4} \times 3^{2} \times 13$.
$1320 = 10 \times 132 = 10 \times 12 \times 11 = 2^{3} \times 3^{1} \times 5^{1} \times 11^{1}$.
$\text{HCF} = 2^{3} \times 3^{1} = 24$ cm.
Number of tiles $= \frac{\text{Area of courtyard}}{\text{Area of one tile}} = \frac{1872 \times 1320}{24 \times 24} = 78 \times 55 = 4290$.

**Answer:** 4290 (a)

**Q11.** Find the greatest number that divides $43, 91,$ and $183$ so as to leave the same remainder in each case.

(a) $4$
(b) $7$
(c) $9$
(d) $13$

**Solution:**
When a number $N$ divides $x, y, z$ leaving the same remainder, $N$ exactly divides their differences: $|x-y|, |y-z|, |z-x|$.
Differences:
$91 - 43 = 48$
$183 - 91 = 92$
$183 - 43 = 140$
The required number is the HCF of $48, 92,$ and $140$.
$48 = 4 \times 12$
$92 = 4 \times 23$
$140 = 4 \times 35$
Since $12, 23, 35$ share no common factors, $\text{HCF} = 4$.

**Answer:** 4 (a)

**Q12.** Two autonomous delivery robots, R1 and R2, traverse a circular perimeter of $1200$ metres. R1 moves at $2$ m/s and R2 at $3$ m/s in the same direction. If they start simultaneously from the base station, after how many minutes will they first meet again at the base station?

(a) $10$
(b) $12$
(c) $20$
(d) $24$

**Solution:**
They meet *at the starting point* when the time elapsed is a multiple of both their individual lap times.
Lap time of R1 $= \frac{1200}{2} = 600$ seconds.
Lap time of R2 $= \frac{1200}{3} = 400$ seconds.
Time to meet at start $= \text{LCM}(600, 400) = 1200$ seconds.
Convert to minutes: $1200 / 60 = 20$ minutes.

**Answer:** 20 (c)

## Remainders

::: definition
**Remainder Algebra:**

- **Addition/Multiplication:** $(A + B) \bmod M = (A \bmod M + B \bmod M) \bmod M$
- **Negative Remainders:** $-R \bmod M \equiv (M - R) \bmod M$. Extremely useful for numbers close to the divisor (e.g., $14 \bmod 15 \equiv -1$).
:::

**Q13.** Find the remainder when $17 \times 23 \times 126 \times 38$ is divided by $8$.

(a) $1$
(b) $2$
(c) $4$
(d) $6$

**Solution:**
Take the remainder of each term individually, then multiply.
$17 \bmod 8 = 1$
$23 \bmod 8 = 7 \equiv -1$
$126 \bmod 8 = 6 \equiv -2$
$38 \bmod 8 = 6 \equiv -2$
Product of remainders $= 1 \times (-1) \times (-2) \times (-2) = -4$.
Convert back to a positive remainder: $-4 \bmod 8 \equiv 8 - 4 = 4$.

**Answer:** 4 (c)

**Q14.** What is the remainder when $2^{256}$ is divided by $17$?

(a) $1$
(b) $2$
(c) $15$
(d) $16$

**Solution:**
Look for a power of $2$ that is close to a multiple of $17$.
We know $2^{4} = 16$.
$16 \bmod 17 = -1$.
Rewrite the expression using this power:
$2^{256} = (2^{4})^{64} = (16)^{64}$.
Remainder $= (-1)^{64} = 1$.

**Answer:** 1 (a)

::: keypoint
**Fermat's Little Theorem:**
If $p$ is a prime number and $a$ is not divisible by $p$, then $a^{p-1} \bmod p = 1$.
:::

**Q15.** Find the remainder when $3^{102}$ is divided by $101$.

(a) $1$
(b) $3$
(c) $9$
(d) $27$

**Solution:**
$101$ is prime, and $3$ is not a multiple of $101$.
By Fermat's Little Theorem: $3^{100} \bmod 101 = 1$.
Rewrite the given expression:
$3^{102} = 3^{100} \times 3^{2}$.
Remainder $= (1 \times 9) \bmod 101 = 9$.

**Answer:** 9 (c)

::: heavy
**Euler's Totient Theorem (Generalisation of Fermat's):**
$a^{\phi(n)} \bmod n = 1$, where $a$ and $n$ are co-prime, and $\phi(n)$ is the count of numbers less than $n$ that are co-prime to $n$.
For $n = p^{x} q^{y} \dots$, $\phi(n) = n(1 - \frac{1}{p})(1 - \frac{1}{q})\dots$
:::

**Q16.** What is the remainder when $7^{42}$ is divided by $15$?

(a) $1$
(b) $4$
(c) $7$
(d) $9$

**Solution:**
$15$ is not prime. We use Euler's Totient Theorem.
$\phi(15) = 15(1 - \frac{1}{3})(1 - \frac{1}{5}) = 15 \times \frac{2}{3} \times \frac{4}{5} = 8$.
Since $7$ and $15$ are co-prime, $7^{8} \bmod 15 = 1$.
Divide the power $42$ by the totient $8$: $42 = 8 \times 5 + 2$.
$7^{42} = (7^{8})^{5} \times 7^{2} \equiv 1^{5} \times 49 \pmod{15}$.
$49 \bmod 15 = 4$.

**Answer:** 4 (b)

**Q17.** A server receives packets in batches. If batched by $5$, $3$ are left over. If batched by $7$, $2$ are left over. What is the minimum possible number of packets received?

(a) $23$
(b) $33$
(c) $38$
(d) $43$

**Solution:**
This is a Chinese Remainder Theorem problem.
Let the number be $N$.
$N = 5a + 3 \Rightarrow N \in \{8, 13, 18, 23, 28, 33, 38, \dots\}$
$N = 7b + 2 \Rightarrow N \in \{9, 16, 23, 30, 37, \dots\}$
The smallest common value in both series is $23$.
*(Fast check: $23 / 5$ leaves $3$. $23 / 7$ leaves $2$.)*

**Answer:** 23 (a)

## Unit Digit & Cyclicity

::: keypoint
**Power Cyclicity (Unit Digit):**
The unit digit of $a^{n}$ repeats in cycles of up to $4$ depending on the unit digit of $a$:

- **1, 5, 6, 0:** Always stay the same (cycle length 1).
- **4, 9:** Cycle length 2 ($4 \to 6$, $9 \to 1$).
- **2, 3, 7, 8:** Cycle length 4.
Always find $n \bmod 4$ to determine the position in the cycle. (If $n \bmod 4 = 0$, it is the $4$th position).
:::

**Q18.** Find the unit digit of $(234)^{102} + (234)^{103}$.

(a) $0$
(b) $2$
(c) $4$
(d) $6$

**Solution:**
The unit digit of $234$ is $4$. The cycle for $4$ is $4, 6, 4, 6 \ldots$
Odd powers end in $4$, even powers end in $6$.
$102$ is even, so $(234)^{102}$ ends in $6$.
$103$ is odd, so $(234)^{103}$ ends in $4$.
Sum of unit digits $= 6 + 4 = 10$. The final unit digit is $0$.

**Answer:** 0 (a)

**Q19.** Find the unit digit of $7^{105}$.

(a) $1$
(b) $3$
(c) $7$
(d) $9$

**Solution:**
The cycle of $7$ is $7, 9, 3, 1$ (length $4$).
Divide the power by $4$: $105 = 4 \times 26 + 1$.
The remainder is $1$, so it is the $1$st number in the cycle.
The unit digit is $7$.

**Answer:** 7 (c)

**Q20.** What is the unit digit of $1! + 2! + 3! + \ldots + 99!$?

(a) $1$
(b) $3$
(c) $5$
(d) $9$

**Solution:**
Evaluate the factorials:
$1! = 1$
$2! = 2$
$3! = 6$
$4! = 24 \Rightarrow$ ends in $4$
$5! = 120 \Rightarrow$ ends in $0$
For all $n \ge 5$, $n!$ ends in $0$ because it contains both $2$ and $5$ as factors.
So, we only need to sum the unit digits of the first four terms:
$1 + 2 + 6 + 4 = 13$.
The final unit digit is $3$.

**Answer:** 3 (b)

## Last Two Digits

::: keypoint
**Last Two Digits Shortcut:**

- **Numbers ending in 1:** For $(\ldots a 1)^{\ldots b}$, the last two digits are $(a \times b \bmod 10)1$.
- **Numbers ending in 3, 7, 9:** Raise to a power to make it end in 1 (e.g., $3^{4}=81$, $7^{4}=2401$, $9^{2}=81$), then use the rule above.
- **Numbers ending in 5:**
  - If the ten's digit is odd AND the power is odd $\Rightarrow$ ends in $75$.
  - All other cases $\Rightarrow$ ends in $25$.
:::

**Q21.** What are the last two digits of $31^{47}$?

(a) $11$
(b) $31$
(c) $71$
(d) $91$

**Solution:**
The base ends in $1$.
Unit digit is always $1$.
Ten's digit $= (\text{ten's digit of base} \times \text{unit digit of power}) \bmod 10$.
$= (3 \times 7) \bmod 10 = 21 \bmod 10 = 1$.
Last two digits are $11$.

**Answer:** 11 (a)

**Q22.** What are the last two digits of $7^{2024}$?

(a) $01$
(b) $07$
(c) $49$
(d) $43$

**Solution:**
The base ends in $7$. We know $7^{4} = 2401$, which ends in $01$.
Rewrite the expression: $7^{2024} = (7^{4})^{506} = (\dots 01)^{506}$.
Using the rule for numbers ending in $1$:
Ten's digit $= (0 \times 6) \bmod 10 = 0$.
Unit digit $= 1$.
Last two digits are $01$.

**Answer:** 01 (a)

**Q23.** What are the last two digits of $65^{33}$?

(a) $15$
(b) $25$
(c) $65$
(d) $75$

**Solution:**
The base ends in $5$.
Rule check: The ten's digit of the base is $6$ (even).
If the ten's digit is odd AND the power is odd, it ends in $75$. Here, the ten's digit is even.
Therefore, it falls under "all other cases" and ends in $25$.

**Answer:** 25 (b)

## Factorials

::: definition
**Legendre's Formula:**
The highest power of a prime $p$ that divides $n!$ is given by:
$E_{p}(n!) = \lfloor \frac{n}{p} \rfloor + \lfloor \frac{n}{p^{2}} \rfloor + \lfloor \frac{n}{p^{3}} \rfloor + \dots$
Stop when $p^{k} > n$.
:::

**Q24.** What is the highest power of $3$ that exactly divides $50!$?

(a) $16$
(b) $20$
(c) $22$
(d) $24$

**Solution:**
Using Legendre's formula for $p=3, n=50$:
$= \lfloor \frac{50}{3} \rfloor + \lfloor \frac{50}{9} \rfloor + \lfloor \frac{50}{27} \rfloor$
$= 16 + 5 + 1 = 22$.

**Answer:** 22 (c)

::: trap
**Trailing Zeros:** A trailing zero is created by a factor of $10$ ($2 \times 5$). In any factorial $n!$, the number of $2$s is always greater than the number of $5$s. Thus, the number of trailing zeros is simply the highest power of $5$ in $n!$. Don't waste time calculating the power of $2$.
:::

**Q25.** How many trailing zeros are there in $100!$?

(a) $20$
(b) $21$
(c) $24$
(d) $25$

**Solution:**
Trailing zeros = highest power of $5$ in $100!$.
$= \lfloor \frac{100}{5} \rfloor + \lfloor \frac{100}{25} \rfloor$
$= 20 + 4 = 24$.

**Answer:** 24 (c)

## Base Systems

::: keypoint

- **Base $B$ to Decimal:** Multiply digits by $B^{0}, B^{1}, B^{2} \dots$ from right to left.
- **Decimal to Base $B$:** Successively divide by $B$ and read remainders upwards.
- **Binary/Hex:** Each Hex digit corresponds to exactly $4$ bits (a nibble).
:::

**Q26.** Convert the binary number $110110_{2}$ to decimal.

(a) $52$
(b) $54$
(c) $56$
(d) $58$

**Solution:**
Write the powers of $2$ from right to left: $32, 16, 8, 4, 2, 1$.
Multiply by the binary digits:
$= (1 \times 32) + (1 \times 16) + (0 \times 8) + (1 \times 4) + (1 \times 2) + (0 \times 1)$
$= 32 + 16 + 0 + 4 + 2 + 0 = 54$.

**Answer:** 54 (b)

**Q27.** (Cisco-style) You have a 32-bit register containing a value. The hex representation of this value is `0x4A`. How many bits are set to `1` in this register?

(a) $2$
(b) $3$
(c) $4$
(d) $5$

**Solution:**
Convert each hex digit to its 4-bit binary equivalent.
Hex `4` $= 0100_{2}$ (one bit set).
Hex `A` $= 10_{10} = 1010_{2}$ (two bits set).
Concatenated binary: `01001010`.
Total number of `1`s $= 1 + 2 = 3$.
*(Note: A 32-bit register is padded with leading zeros, which don't add any `1`s).*

**Answer:** 3 (b)

**Q28.** Find the base $x$ if $123_{x} = 38_{10}$.

(a) $4$
(b) $5$
(c) $6$
(d) $7$

**Solution:**
Expand $123_{x}$ to decimal:
$1 \times x^{2} + 2 \times x^{1} + 3 \times x^{0} = 38$
$x^{2} + 2x + 3 = 38$
$x^{2} + 2x - 35 = 0$
$(x + 7)(x - 5) = 0$
Since a base must be positive and greater than its digits, $x = 5$.

**Answer:** 5 (b)

## Sources

- IndiaBix — Number Systems & Aptitude — https://www.indiabix.com/aptitude/numbers/
- GeeksforGeeks Aptitude — Divisibility & Factorials — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- PrepInsta — OA Prep (TCS/Infosys) Number system patterns — https://prepinsta.com/
- Brainstellar — Quant Number theory puzzles — https://brainstellar.com/
- CareerBless — HCF/LCM Word Problems — http://www.careerbless.com/aptitude/qa/home.php
