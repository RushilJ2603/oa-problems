# Progressions & Series (AP/GP/HP)

::: definition
**Arithmetic Progression (AP):** $a_{n} = a + (n-1)d$, $S_{n} = \frac{n}{2}(2a + (n-1)d)$ or $\frac{n}{2}(a+l)$

**Geometric Progression (GP):** $a_{n} = ar^{n-1}$, $S_{n} = a\frac{r^{n}-1}{r-1}$ (for $r > 1$), infinite $S_{\infty} = \frac{a}{1-r}$ for $|r|<1$

**Harmonic Progression (HP):** The reciprocals of the terms form an AP.

**Means:** $\text{AM} \ge \text{GM} \ge \text{HM}$, and $\text{GM}^{2} = \text{AM} \cdot \text{HM}$ for two numbers.

**Standard Sums:**

- Natural numbers: $\sum n = \frac{n(n+1)}{2}$
- Squares: $\sum n^{2} = \frac{n(n+1)(2n+1)}{6}$
- Cubes: $\sum n^{3} = \left(\frac{n(n+1)}{2}\right)^{2}$
:::

## Arithmetic Progressions

**Q1.** Find the $20^{\text{th}}$ term of the arithmetic progression $3, 7, 11, 15, \dots$
(a) $75$  (b) $79$  (c) $83$  (d) $87$

**Solution:**

Here, the first term $a = 3$ and common difference $d = 7 - 3 = 4$.

The $n^{\text{th}}$ term is $a_{n} = a + (n-1)d$.

For $n = 20$:

$a_{20} = 3 + (19 \times 4) = 3 + 76 = 79$.

**Answer:** $79$ (b)

**Q2.** How many terms are there in the sequence $7, 13, 19, \dots, 205$?
(a) $33$  (b) $34$  (c) $35$  (d) $36$

**Solution:**

Here, $a = 7$, $d = 6$, and the last term $a_{n} = 205$.

$a_{n} = a + (n-1)d \implies 205 = 7 + (n-1)6$

$198 = 6(n-1) \implies n-1 = 33 \implies n = 34$.

::: keypoint
To find the number of terms quickly, use $n = \frac{\text{Last} - \text{First}}{\text{Difference}} + 1$.
:::

**Answer:** $34$ (b)

**Q3.** The sum of the first $15$ terms of an AP is $600$, and the common difference is $5$. Find the first term.
(a) $5$  (b) $8$  (c) $10$  (d) $15$

**Solution:**

Using the sum formula $S_{n} = \frac{n}{2}(2a + (n-1)d)$:

$600 = \frac{15}{2}(2a + 14 \times 5)$

$1200 = 15(2a + 70) \implies 80 = 2a + 70 \implies 2a = 10 \implies a = 5$.

**Answer:** $5$ (a)

**Q4.** The sum of three numbers in an arithmetic progression is $27$, and their product is $504$. What is the largest of these numbers?
(a) $12$  (b) $14$  (c) $15$  (d) $17$

**Solution:**

Assume the three terms are $a-d$, $a$, $a+d$.

Sum $= 3a = 27 \implies a = 9$.

Product $= (9-d)(9)(9+d) = 504$.

$81 - d^{2} = \frac{504}{9} = 56 \implies d^{2} = 25 \implies d = 5$ (or $-5$).

The terms are $4, 9, 14$. The largest is $14$.

::: keypoint
When asked for $3$, $4$, or $5$ terms in AP, assume them symmetrically around $a$:

- $3$ terms: $a-d, a, a+d$ (common difference $d$)
- $4$ terms: $a-3d, a-d, a+d, a+3d$ (common difference $2d$)
:::

**Answer:** $14$ (b)

## Geometric Progressions

**Q5.** What is the $7^{\text{th}}$ term of the geometric progression $2, 6, 18, 54, \dots$?
(a) $486$  (b) $1458$  (c) $4374$  (d) $2187$

**Solution:**

Here, $a = 2$, common ratio $r = 3$.

The $n^{\text{th}}$ term is $a_{n} = ar^{n-1}$.

$a_{7} = 2 \times 3^{6} = 2 \times 729 = 1458$.

**Answer:** $1458$ (b)

**Q6.** Find the sum of the first $6$ terms of the geometric progression $5, 10, 20, 40, \dots$
(a) $310$  (b) $315$  (c) $320$  (d) $325$

**Solution:**

Here, $a = 5$, $r = 2$.

$S_{n} = a\frac{r^{n}-1}{r-1}$.

$S_{6} = 5\frac{2^{6} - 1}{2 - 1} = 5(64 - 1) = 5 \times 63 = 315$.

**Answer:** $315$ (b)

**Q7.** Find the sum of the infinite geometric series: $9 - 3 + 1 - \frac{1}{3} + \dots$
(a) $6$  (b) $6.75$  (c) $7.5$  (d) $13.5$

**Solution:**

Here, $a = 9$ and the common ratio $r = -\frac{3}{9} = -\frac{1}{3}$.

The sum of an infinite GP is $S_{\infty} = \frac{a}{1 - r}$ (since $|r| < 1$).

$S_{\infty} = \frac{9}{1 - (-1/3)} = \frac{9}{4/3} = 9 \times \frac{3}{4} = \frac{27}{4} = 6.75$.

**Answer:** $6.75$ (b)

## HP & Means

**Q8.** Find the $10^{\text{th}}$ term of the harmonic progression $\frac{1}{2}, \frac{1}{5}, \frac{1}{8}, \dots$
(a) $\frac{1}{27}$  (b) $\frac{1}{29}$  (c) $\frac{1}{31}$  (d) $\frac{1}{32}$

**Solution:**

The reciprocals form an AP: $2, 5, 8, \dots$

For the AP, $a = 2$ and $d = 3$.

$10^{\text{th}}$ term of AP $= a + 9d = 2 + 9(3) = 29$.

Therefore, the $10^{\text{th}}$ term of the HP is the reciprocal of $29$.

**Answer:** $\frac{1}{29}$ (b)

**Q9.** The arithmetic mean of two distinct positive numbers is $10$, and their geometric mean is $8$. Find their harmonic mean.
(a) $6.4$  (b) $7.2$  (c) $8.5$  (d) $9.6$

**Solution:**

For any two numbers, $\text{GM}^{2} = \text{AM} \times \text{HM}$.

$8^{2} = 10 \times \text{HM}$

$64 = 10 \times \text{HM} \implies \text{HM} = 6.4$.

**Answer:** $6.4$ (a)

**Q10.** The AM and GM of two positive integers are $17$ and $15$ respectively. What is the absolute difference between the two numbers?
(a) $10$  (b) $12$  (c) $14$  (d) $16$

**Solution:**

Let the numbers be $x$ and $y$.

$\text{AM} = \frac{x+y}{2} = 17 \implies x+y = 34$.

$\text{GM} = \sqrt{xy} = 15 \implies xy = 225$.

We want $|x-y|$. Use the algebraic identity $(x-y)^{2} = (x+y)^{2} - 4xy$.

$(x-y)^{2} = 34^{2} - 4(225) = 1156 - 900 = 256$.

$|x-y| = \sqrt{256} = 16$.

(The numbers are $25$ and $9$.)

**Answer:** $16$ (d)

## Special & Telescoping Series

**Q11.** What is the sum of the squares of the first $12$ natural numbers?
(a) $506$  (b) $650$  (c) $728$  (d) $819$

**Solution:**

The sum of squares is given by $\sum n^{2} = \frac{n(n+1)(2n+1)}{6}$.

For $n = 12$:

$\sum_{k=1}^{12} k^{2} = \frac{12 \times 13 \times 25}{6} = 2 \times 13 \times 25 = 26 \times 25 = 650$.

**Answer:** $650$ (b)

**Q12.** Find the sum of the series $2^{3} + 4^{3} + 6^{3} + \dots + 20^{3}$.
(a) $24200$  (b) $28800$  (c) $32400$  (d) $36000$

**Solution:**

Factor out $2^{3}$:

$2^{3}(1^{3} + 2^{3} + 3^{3} + \dots + 10^{3}) = 8 \sum_{n=1}^{10} n^{3}$.

The sum of cubes is $\left(\frac{n(n+1)}{2}\right)^{2}$.

For $n=10$, $\sum n^{3} = \left(\frac{10 \times 11}{2}\right)^{2} = 55^{2} = 3025$.

Total sum $= 8 \times 3025 = 24200$.

**Answer:** $24200$ (a)

**Q13.** Evaluate the sum: $\frac{1}{1\times 2} + \frac{1}{2\times 3} + \frac{1}{3\times 4} + \dots + \frac{1}{99\times 100}$
(a) $\frac{98}{99}$  (b) $\frac{99}{100}$  (c) $1$  (d) $\frac{100}{101}$

**Solution:**

This is a standard telescoping series. Note that $\frac{1}{n(n+1)} = \frac{1}{n} - \frac{1}{n+1}$.

Expanding the sum:

$\left(1 - \frac{1}{2}\right) + \left(\frac{1}{2} - \frac{1}{3}\right) + \dots + \left(\frac{1}{99} - \frac{1}{100}\right)$.

All intermediate terms cancel out, leaving only the first and last terms:

$1 - \frac{1}{100} = \frac{99}{100}$.

::: keypoint
For any telescoping sum of the form $\sum_{k=1}^{n} \frac{1}{k(k+d)}$, the trick is splitting into $\frac{1}{d}\left(\frac{1}{k} - \frac{1}{k+d}\right)$.
:::

**Answer:** $\frac{99}{100}$ (b)

## Number-Series Puzzles

**Q14.** Find the missing number in the series: $3, 9, 21, 39, ?, 87$
(a) $57$  (b) $61$  (c) $63$  (d) $65$

**Solution:**

Find the differences between consecutive terms:

$9 - 3 = 6$

$21 - 9 = 12$

$39 - 21 = 18$

The differences form an AP: $6, 12, 18, \dots$

The next difference should be $24$.

Therefore, missing term $= 39 + 24 = 63$.

Check the next term: $63 + 30 = 87$. This matches.

**Answer:** $63$ (c)

**Q15.** Identify the wrong number in the series: $2, 5, 10, 17, 26, 37, 50, 64$
(a) $17$  (b) $26$  (c) $37$  (d) $64$

**Solution:**

Look at the pattern of the terms related to squares:

$2 = 1^{2} + 1$

$5 = 2^{2} + 1$

$10 = 3^{2} + 1$

$17 = 4^{2} + 1$

$26 = 5^{2} + 1$

$37 = 6^{2} + 1$

$50 = 7^{2} + 1$

The next term should be $8^{2} + 1 = 65$, but $64$ is written. Thus, $64$ is the wrong term.

::: trap
A common mistake in "find the wrong term" puzzles is checking differences once, finding no pattern, and giving up. Always check if the sequence is $n^{2} \pm k$ or $n^{3} \pm k$ early on.
:::

**Answer:** $64$ (d)

**Q16.** What is the next term in the sequence: $1, 8, 9, 64, 25, 216, ?$
(a) $36$  (b) $49$  (c) $343$  (d) $512$

**Solution:**

The series alternates between squares and cubes of natural numbers:

$1^{\text{st}}$ term: $1^{2} = 1$

$2^{\text{nd}}$ term: $2^{3} = 8$

$3^{\text{rd}}$ term: $3^{2} = 9$

$4^{\text{th}}$ term: $4^{3} = 64$

$5^{\text{th}}$ term: $5^{2} = 25$

$6^{\text{th}}$ term: $6^{3} = 216$

The $7^{\text{th}}$ term must be $7^{2} = 49$.

**Answer:** $49$ (b)

## Wrapped OA Variants

**Q17.** An engineer starts a new savings plan. She saves $10$ dollars the first week, $20$ dollars the second week, $40$ dollars the third week, doubling the amount every week. How much total money has she saved exactly after $10$ weeks?
(a) $5120$ dollars  (b) $10230$ dollars  (c) $10240$ dollars  (d) $20470$ dollars

**Solution:**

This is a geometric progression where the first term $a = 10$ and common ratio $r = 2$.

We need the sum of the first $10$ terms ($S_{10}$).

$S_{n} = a\frac{r^{n}-1}{r-1}$

$S_{10} = 10 \frac{2^{10} - 1}{2 - 1} = 10(1024 - 1) = 10 \times 1023 = 10230$.

(Note: Option (a) is just the $10^{\text{th}}$ week's deposit, $10 \times 2^{9} = 5120$. Option (c) is a trap if you mistakenly calculate $10 \times 2^{10}$.)

::: interview
In many automated assessments, options will include the $n^{\text{th}}$ term value as a trap when the question asks for the **total sum**. Read "total saved" versus "saved in week 10" carefully.
:::

**Answer:** $10230$ (b)

**Q18.** A highly elastic ball is dropped from a height of $20$ meters. Upon each collision with the floor, it bounces back to $80\%$ of its previous height. What is the total vertical distance the ball travels before coming to a complete rest?
(a) $100$ m  (b) $160$ m  (c) $180$ m  (d) $200$ m

**Solution:**

The ball drops $20$ m.

It bounces up $20 \times 0.8$ m and drops $20 \times 0.8$ m (two trips of this distance).

The next bounce is up $20 \times 0.8^{2}$ m and down $20 \times 0.8^{2}$ m, and so on.

Total distance $D = 20 + 2(20 \times 0.8) + 2(20 \times 0.8^{2}) + \dots$

Let the subsequent infinite geometric series be $S = 2(20 \times 0.8) + 2(20 \times 0.8^{2}) + \dots$

Here, first term $a = 2 \times 16 = 32$, common ratio $r = 0.8$.

$S_{\infty} = \frac{a}{1 - r} = \frac{32}{1 - 0.8} = \frac{32}{0.2} = 160$.

Total distance $= 20 + 160 = 180$ m.

::: heavy
For a bouncing ball dropped from height $H$ with rebound ratio $r$, the total distance is $D = H + 2\left(\frac{rH}{1-r}\right) = H\left(\frac{1+r}{1-r}\right)$. Plugging in $H=20, r=0.8$ gives $20\left(\frac{1.8}{0.2}\right) = 20(9) = 180$.
:::

**Answer:** $180$ (c)

## Sources

* IndiaBix — AP and GP basics (https://www.indiabix.com/aptitude/progressions/)
* GeeksforGeeks Aptitude — Telescoping series and Means (https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/)
* Brainstellar — Bouncing ball total distance puzzle (https://brainstellar.com/puzzles/quantitative)
* PrepInsta — Number series and missing term puzzles (https://prepinsta.com/)
