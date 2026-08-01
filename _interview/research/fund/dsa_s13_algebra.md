# Algebra — Equations, Surds, Indices, Logarithms, Functions

::: definition
**Indices:** $x^a \times x^b = x^{a+b}$, $\frac{x^a}{x^b} = x^{a-b}$, $(x^a)^b = x^{ab}$, $x^{-a} = \frac{1}{x^a}$, $x^{\frac{a}{b}} = \sqrt[b]{x^a}$.

**Surds:** $\sqrt{a}\sqrt{b} = \sqrt{ab}$, $\frac{\sqrt{a}}{\sqrt{b}} = \sqrt{\frac{a}{b}}$. To rationalise $\frac{1}{\sqrt{a}+\sqrt{b}}$, multiply by $\frac{\sqrt{a}-\sqrt{b}}{\sqrt{a}-\sqrt{b}}$.

**Logarithms:** $\log_b(xy)=\log_b x+\log_b y$, $\log_b\left(\frac{x}{y}\right)=\log_b x-\log_b y$, $\log_b(x^k)=k\log_b x$, $\log_b x=\frac{\log_c x}{\log_c b}$.

**Quadratic Roots ($ax^2+bx+c=0$):** $x = \frac{-b\pm\sqrt{b^2-4ac}}{2a}$. Sum of roots $\alpha+\beta = -\frac{b}{a}$. Product $\alpha\beta = \frac{c}{a}$. Discriminant $\Delta = b^2-4ac$ (if $\Delta > 0$ real distinct, $\Delta = 0$ real equal, $\Delta < 0$ complex).
:::

## Linear & Simultaneous Equations

**Q1.** A man has $340$ dollars in five-dollar and ten-dollar bills. If he has a total of $46$ bills, how many ten-dollar bills does he possess?
(a) $18$ (b) $20$ (c) $22$ (d) $24$

**Solution:** Let $x$ be the number of ten-dollar bills. The number of five-dollar bills is $46 - x$.

$10x + 5(46 - x) = 340 \implies 5x + 230 = 340 \implies 5x = 110 \implies x = 22$.

*Fast trick:* If all bills were five-dollar bills, the total would be $46 \times 5 = 230$. The shortfall $340 - 230 = 110$ is made up by the extra $5$ dollars per ten-dollar bill. $110 / 5 = 22$.

**Answer:** $22$ (c)

**Q2.** The sum of the digits of a two-digit number is $12$. If the digits are reversed, the new number is $18$ greater than the original number. What is the original number?
(a) $48$ (b) $57$ (c) $75$ (d) $84$

**Solution:** Let the original number be $10x + y$. The sum of digits is $x + y = 12$. Reversing the digits gives $10y + x$.

The difference is $(10y + x) - (10x + y) = 18 \implies 9(y - x) = 18 \implies y - x = 2$.

Solving $y + x = 12$ and $y - x = 2$ yields $2y = 14 \implies y = 7$ and $x = 5$. The number is $57$.

::: keypoint
The difference between any two-digit number and its reverse is always $9 \times (\text{difference of its digits})$.
:::

**Answer:** $57$ (b)

**Q3.** Three friends buy office supplies. Alice buys $2$ pens and $3$ notebooks for $18$ dollars. Bob buys $3$ pens and $2$ notebooks for $17$ dollars. What is the combined cost of $1$ pen and $1$ notebook?
(a) $5$ dollars (b) $6$ dollars (c) $7$ dollars (d) $8$ dollars

**Solution:** Let $p$ be the cost of a pen and $n$ be the cost of a notebook.

$2p + 3n = 18$

$3p + 2n = 17$

Instead of solving for individual variables, add the two equations directly: $5p + 5n = 35$. Divide by $5$ to get $p + n = 7$.

**Answer:** $7$ dollars (c)

**Q4.** (OA Variant: Software Licensing) A startup purchases $x$ standard licenses at $40$ dollars each and $y$ pro licenses at $100$ dollars each. The total bill is $2600$ dollars. If they had swapped the quantities (bought $y$ standard and $x$ pro), the bill would have been $3000$ dollars. How many licenses did they buy in total?
(a) $35$ (b) $40$ (c) $45$ (d) $50$

**Solution:** Set up the system:

$40x + 100y = 2600$

$100x + 40y = 3000$

Add both equations: $140x + 140y = 5600 \implies 140(x + y) = 5600 \implies x + y = 40$.

**Answer:** $40$ (b)

## Quadratic Equations

**Q5.** Find the roots of the equation $3x^2 - 14x + 8 = 0$.
(a) $\frac{1}{3}, 8$ (b) $\frac{2}{3}, 4$ (c) $-\frac{2}{3}, -4$ (d) $\frac{4}{3}, 2$

**Solution:** Factor by splitting the middle term. We need two numbers that multiply to $3 \times 8 = 24$ and sum to $-14$. These are $-12$ and $-2$.

$3x^2 - 12x - 2x + 8 = 0 \implies 3x(x - 4) - 2(x - 4) = 0 \implies (3x - 2)(x - 4) = 0$.

The roots are $x = \frac{2}{3}$ and $x = 4$.

**Answer:** $\frac{2}{3}, 4$ (b)

**Q6.** If $\alpha$ and $\beta$ are the roots of the equation $2x^2 - 5x + 7 = 0$, what is the value of $\frac{1}{\alpha} + \frac{1}{\beta}$?
(a) $\frac{5}{7}$ (b) $-\frac{5}{7}$ (c) $\frac{7}{5}$ (d) $\frac{2}{7}$

**Solution:** The expression simplifies to $\frac{\alpha + \beta}{\alpha\beta}$.

Using the sum and product of roots formulas:

Sum of roots $\alpha + \beta = -\frac{-5}{2} = \frac{5}{2}$.

Product of roots $\alpha\beta = \frac{7}{2}$.

Divide the sum by the product: $\frac{5/2}{7/2} = \frac{5}{7}$.

**Answer:** $\frac{5}{7}$ (a)

**Q7.** For what value of $k$ does the equation $kx^2 - 12x + 9 = 0$ have real and equal roots?
(a) $2$ (b) $3$ (c) $4$ (d) $6$

**Solution:** Real and equal roots require the discriminant to be exactly zero: $\Delta = b^2 - 4ac = 0$.

$(-12)^2 - 4(k)(9) = 0 \implies 144 - 36k = 0 \implies k = 4$.

**Answer:** $4$ (c)

**Q8.** (OA Variant: Maximising Profit) A company's daily profit when selling $x$ units of a specialized server is given by $P(x) = -2x^2 + 120x - 1000$. What is the maximum possible daily profit?
(a) $600$ (b) $800$ (c) $1000$ (d) $1200$

**Solution:** This is a downward-opening parabola. The maximum occurs at the vertex $x = -\frac{b}{2a}$.

$x = -\frac{120}{2(-2)} = \frac{120}{4} = 30$.

Substitute $x = 30$ back into the profit function:

$P(30) = -2(30)^2 + 120(30) - 1000 = -1800 + 3600 - 1000 = 800$.

::: keypoint
The absolute maximum or minimum value of a quadratic function $ax^2+bx+c$ always occurs at $x = -\frac{b}{2a}$.
:::

**Answer:** $800$ (b)

## Surds & Indices

**Q9.** Simplify the expression $\frac{3}{\sqrt{5} - \sqrt{2}}$.
(a) $\sqrt{5} - \sqrt{2}$ (b) $\sqrt{5} + \sqrt{2}$ (c) $3\sqrt{5} + 3\sqrt{2}$ (d) $\frac{\sqrt{5} + \sqrt{2}}{3}$

**Solution:** Rationalise the denominator by multiplying the numerator and denominator by the conjugate $\sqrt{5} + \sqrt{2}$.

$\frac{3(\sqrt{5} + \sqrt{2})}{(\sqrt{5})^2 - (\sqrt{2})^2} = \frac{3(\sqrt{5} + \sqrt{2})}{5 - 2} = \frac{3(\sqrt{5} + \sqrt{2})}{3} = \sqrt{5} + \sqrt{2}$.

**Answer:** $\sqrt{5} + \sqrt{2}$ (b)

**Q10.** Solve for $x$ in the equation $4^{x+1} \times 8^{2x} = 16^{3x-1}$.
(a) $\frac{3}{2}$ (b) $2$ (c) $\frac{5}{2}$ (d) $3$

**Solution:** Express all terms using a common base of $2$.

$4^{x+1} = (2^2)^{x+1} = 2^{2x+2}$

$8^{2x} = (2^3)^{2x} = 2^{6x}$

$16^{3x-1} = (2^4)^{3x-1} = 2^{12x-4}$

The equation becomes $2^{2x+2} \times 2^{6x} = 2^{12x-4}$. Add the exponents on the left:

$2^{8x+2} = 2^{12x-4} \implies 8x + 2 = 12x - 4 \implies 4x = 6 \implies x = \frac{3}{2}$.

**Answer:** $\frac{3}{2}$ (a)

**Q11.** Which of the following surds is the largest? $\sqrt{2}$, $\sqrt[3]{3}$, $\sqrt[4]{4}$, $\sqrt[6]{6}$
(a) $\sqrt{2}$ (b) $\sqrt[3]{3}$ (c) $\sqrt[4]{4}$ (d) $\sqrt[6]{6}$

**Solution:** To compare, raise all terms to a common power that eliminates the roots. The least common multiple of the indices ($2, 3, 4, 6$) is $12$.

$(\sqrt{2})^{12} = 2^6 = 64$

$(\sqrt[3]{3})^{12} = 3^4 = 81$

$(\sqrt[4]{4})^{12} = 4^3 = 64$ (note that $\sqrt[4]{4} = \sqrt{2}$)

$(\sqrt[6]{6})^{12} = 6^2 = 36$

The largest result is $81$, which corresponds to $\sqrt[3]{3}$.

**Answer:** $\sqrt[3]{3}$ (b)

**Q12.** (OA Variant: Server Scaling) A distributed database scales its storage capacity according to the formula $C(n) = 27^{n/3} \times 9^{n/2}$, where $n$ is the number of node clusters. If the required capacity is $3^{10}$ terabytes, how many clusters $n$ are needed?
(a) $3$ (b) $4$ (c) $5$ (d) $6$

**Solution:** Convert the base of each term to $3$.

$27^{n/3} = (3^3)^{n/3} = 3^n$.

$9^{n/2} = (3^2)^{n/2} = 3^n$.

The capacity function simplifies to $C(n) = 3^n \times 3^n = 3^{2n}$.

Equate to the required capacity: $3^{2n} = 3^{10} \implies 2n = 10 \implies n = 5$.

**Answer:** $5$ (c)

## Logarithms

**Q13.** Evaluate the expression $\log_2(16) + \log_3\left(\frac{1}{27}\right) - \log_5(1)$.
(a) $-1$ (b) $1$ (c) $4$ (d) $7$

**Solution:** Evaluate each logarithm independently:

$\log_2(16) = \log_2(2^4) = 4$.

$\log_3\left(\frac{1}{27}\right) = \log_3(3^{-3}) = -3$.

$\log_5(1) = 0$.

The sum is $4 + (-3) - 0 = 1$.

**Answer:** $1$ (b)

**Q14.** Given $\log_{10} 2 = 0.3010$ and $\log_{10} 3 = 0.4771$, what is the number of digits in $6^{50}$?
(a) $38$ (b) $39$ (c) $40$ (d) $41$

**Solution:** Let $N = 6^{50}$. Take the base-10 logarithm of both sides:

$\log_{10} N = 50 \log_{10} 6 = 50 (\log_{10} 2 + \log_{10} 3) = 50 (0.3010 + 0.4771) = 50(0.7781) = 38.905$.

The integer part (characteristic) is $38$.

::: keypoint
If $\log_{10} x = c + m$ (where $c$ is the characteristic and $m \ge 0$ is the mantissa), the number of digits in the integer part of $x$ is $c + 1$.
:::

The number of digits is $38 + 1 = 39$.

**Answer:** $39$ (b)

**Q15.** (OA Variant: Logarithmic Collapse) Evaluate the logarithmic expression $\log_{10}(x^5) + 3\log_{10}\left(\frac{10}{x}\right) - \log_{10}(x^2)$ for any $x > 0$.
(a) $3$ (b) $30$ (c) $\log_{10}(x)$ (d) $1000$

**Solution:** Use the logarithm laws to expand and simplify the terms:

$3\log_{10}\left(\frac{10}{x}\right) = 3(\log_{10} 10 - \log_{10} x) = 3(1 - \log_{10} x) = 3 - 3\log_{10} x$.

$\log_{10}(x^5) = 5\log_{10} x$.

$\log_{10}(x^2) = 2\log_{10} x$.

Combine all terms:

$5\log_{10} x + (3 - 3\log_{10} x) - 2\log_{10} x = 3$. All $x$ terms cancel out.

**Answer:** $3$ (a)

## Functions

**Q16.** If $f(x) = \frac{x-1}{x+1}$, find the composed function $f(f(x))$.
(a) $-\frac{1}{x}$ (b) $x$ (c) $\frac{1}{x}$ (d) $-x$

**Solution:** Substitute $f(x)$ into itself.

$f(f(x)) = \frac{\frac{x-1}{x+1} - 1}{\frac{x-1}{x+1} + 1}$

Multiply the numerator and denominator by $x+1$ to clear the complex fraction:

$\frac{(x-1) - (x+1)}{(x-1) + (x+1)} = \frac{x - 1 - x - 1}{x - 1 + x + 1} = \frac{-2}{2x} = -\frac{1}{x}$.

**Answer:** $-\frac{1}{x}$ (a)

**Q17.** A function $g$ satisfies $g(x) = g(x-1) + g(x-2)$ for $x > 2$. If $g(1) = 2$ and $g(2) = 3$, what is $g(5)$?
(a) $8$ (b) $11$ (c) $13$ (d) $21$

**Solution:** This is a recurrence relation that acts like the Fibonacci sequence. Build up to $g(5)$:

$g(3) = g(2) + g(1) = 3 + 2 = 5$.

$g(4) = g(3) + g(2) = 5 + 3 = 8$.

$g(5) = g(4) + g(3) = 8 + 5 = 13$.

**Answer:** $13$ (c)

**Q18.** (OA Variant: Functional Maze) A function $f: \mathbb{R} \to \mathbb{R}$ satisfies $f(x+y) = f(x) + f(y) - 4$ for all real numbers $x, y$. If $f(2) = 10$, find $f(7)$.
(a) $20$ (b) $21$ (c) $25$ (d) $31$

**Solution:** To remove the constant, define a new function $g(x) = f(x) - 4$.

$g(x+y) = f(x+y) - 4 = (f(x) + f(y) - 4) - 4 = (f(x) - 4) + (f(y) - 4) = g(x) + g(y)$.

Since $g(x+y) = g(x) + g(y)$, $g(x)$ represents a linear function passing through the origin, so $g(x) = cx$.

Thus, $f(x) = cx + 4$.

We know $f(2) = 10 \implies 2c + 4 = 10 \implies 2c = 6 \implies c = 3$.

The function is strictly $f(x) = 3x + 4$.

Therefore, $f(7) = 3(7) + 4 = 21 + 4 = 25$.

::: keypoint
**Shift the constant:** For functional equations resembling $f(x+y) = f(x) + f(y) + k$, define $g(x) = f(x) + k$ to reach Cauchy's additive equation $g(x+y) = g(x) + g(y)$, which yields $g(x) = cx$.
:::

**Answer:** $25$ (c)

## Inequalities & AM–GM

**Q19.** Find the range of $x$ that satisfies the inequality $x^2 - 5x + 6 < 0$.
(a) $x < 2$ (b) $x > 3$ (c) $2 < x < 3$ (d) $x < 2 \text{ or } x > 3$

**Solution:** Factor the quadratic expression: $(x-2)(x-3) < 0$.

The roots are $2$ and $3$. Since the coefficient of $x^2$ is positive, the parabola opens upwards. It falls strictly below the $x$-axis between its roots.

Thus, the inequality holds for $2 < x < 3$.

**Answer:** $2 < x < 3$ (c)

**Q20.** For any positive real number $x$, what is the minimum value of $4x + \frac{9}{x}$?
(a) $6$ (b) $12$ (c) $13$ (d) $36$

**Solution:** Apply the Arithmetic Mean–Geometric Mean (AM-GM) inequality: for positive $a, b$, we have $\frac{a+b}{2} \ge \sqrt{ab}$.

Let $a = 4x$ and $b = \frac{9}{x}$.

$\frac{4x + \frac{9}{x}}{2} \ge \sqrt{4x \times \frac{9}{x}} = \sqrt{36} = 6$.

Multiplying by $2$ gives $4x + \frac{9}{x} \ge 12$. The minimum value is $12$ (occurring when $4x = \frac{9}{x} \implies x = \frac{3}{2}$).

**Answer:** $12$ (b)

**Q21.** (OA Variant: Latency Minimisation) A system's processing time $T$ in milliseconds, given an allocated cache of $C$ megabytes ($C > 0$), is modelled by $T = 2C + \frac{32}{C} + 5$. What is the absolute minimum processing time the system can achieve?
(a) $13$ ms (b) $16$ ms (c) $21$ ms (d) $25$ ms

**Solution:** We want to minimise the variable part $2C + \frac{32}{C}$. Using the AM-GM inequality:

$\frac{2C + \frac{32}{C}}{2} \ge \sqrt{2C \times \frac{32}{C}} = \sqrt{64} = 8$.

So, $2C + \frac{32}{C} \ge 16$.

Add the constant $5$ back to find the minimum time: $T_{\min} = 16 + 5 = 21$ ms.

::: interview
Quant and logic-heavy OAs frequently use AM-GM to test your ability to find minimums of $ax + b/x$ structures without relying on calculus. The minimum value is always $2\sqrt{ab}$.
:::

**Answer:** $21$ ms (c)

## Sources

- IndiaBix — https://www.indiabix.com/
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- PrepInsta — https://prepinsta.com/
- Hitbullseye — https://www.hitbullseye.com/
- Cisco SDE-intern aptitude set (internal)
