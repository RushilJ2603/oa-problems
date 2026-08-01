# Mental Math & Rapid Calculation

::: definition
**Core Mental Math Heuristics**

- **Multiply by $11$**: Write the outer digits, sum adjacent pairs for the inner digits.
- **Multiply by $5$, $25$, $125$**: Multiply by $10, 100, 1000$ and divide by $2, 4, 8$ respectively.
- **Numbers ending in $5$ squared**: $(10n+5)^2 = 100n(n+1) + 25$.
- **Difference of squares**: $a \times b = \left(\frac{a+b}{2}\right)^2 - \left(\frac{a-b}{2}\right)^2$. Use when $a$ and $b$ are close.
- **Percentage Swap**: $x\% \text{ of } y = y\% \text{ of } x$.
- **Fraction equivalents**: Learn $1/2$ to $1/12$. Notably, $1/6 \approx 16.67\%$, $1/7 \approx 14.28\%$, $1/8 = 12.5\%$, $1/9 \approx 11.11\%$, $1/11 \approx 9.09\%$.
:::

::: interview
In quantitative trading interviews (e.g., Optiver "80 in 8", Jane Street) and speed-based OAs, you are tested on raw throughput and accuracy without a calculator. They grade your ability to spot patterns (like $(a+b)(a-b)$) rather than brute-forcing calculations. Accuracy is strictly penalized (e.g., $+1$ for correct, $-1$ or $-2$ for incorrect), so intelligent skipping and fast sanity checks are crucial.
:::

## Fast multiplication & squaring

**Q1.** $85^2$

**Solution:**
For any number ending in $5$ (format $10n+5$), the result ends in $25$ and the leading digits are $n(n+1)$.
Here, $n = 8$. We calculate $8 \times (8+1) = 8 \times 9 = 72$.
Append $25$ to get $7225$.

**Answer:** $7225$

**Q2.** $43 \times 47$

**Solution:**
When multiplying two numbers with the same tens digit and units digits that sum to $10$ (here $3+7=10$), use the same trick as squaring numbers ending in $5$.
Multiply the tens digit by itself plus one: $4 \times 5 = 20$.
Multiply the units digits: $3 \times 7 = 21$.
Concatenate the two parts: $2021$.

**Answer:** $2021$

**Q3.** $96 \times 107$

**Solution:**
Use algebraic expansion around a base of $100$.
$(100 - 4)(100 + 7) = 10000 + 700 - 400 - 28 = 10300 - 28 = 10272$.

**Answer:** $10272$

**Q4.** $28 \times 25$

**Solution:**
Multiply by $100$ and divide by $4$.
$28 \times 100 / 4 = 2800 / 4 = 700$.
Alternatively, calculate $28 / 4 = 7$, then append two zeros.

**Answer:** $700$

**Q5.** $32 \times 125$

**Solution:**
Multiply by $1000$ and divide by $8$.
$32 / 8 = 4$. Append three zeros to get $4000$.

**Answer:** $4000$

**Q6.** $432 \times 11$

**Solution:**
To multiply by $11$, write the rightmost digit ($2$), then sum adjacent digits moving left ($2+3=5$, $3+4=7$), then write the leftmost digit ($4$).
Result: $4752$.

**Answer:** $4752$

## Division, fractions & percentages at speed

**Q7.** $16\% \text{ of } 25$

**Solution:**
Use the percentage swap trick: $x\% \text{ of } y = y\% \text{ of } x$.
$25\% \text{ of } 16 = \frac{1}{4} \times 16 = 4$.

**Answer:** $4$

**Q8.** $12.5\% \text{ of } 848$

**Solution:**
Memorize fraction equivalents: $12.5\% = \frac{1}{8}$.
$\frac{1}{8} \times 848 = 106$.

**Answer:** $106$

**Q9.** $87.5\% \text{ of } 320$

**Solution:**
Notice that $87.5\% = 100\% - 12.5\% = 1 - \frac{1}{8} = \frac{7}{8}$.
$\frac{7}{8} \times 320 = 7 \times 40 = 280$.

**Answer:** $280$

**Q10.** What is $\frac{3}{7} \text{ of } 60\% \text{ of } 140$?

**Solution:**
Chain the fractions: $60\% = \frac{3}{5}$.
$\frac{3}{7} \times \frac{3}{5} \times 140 = \frac{9}{35} \times 140$.
Notice that $140 / 35 = 4$.
$9 \times 4 = 36$.

**Answer:** $36$

**Q11.** $11.11\% \text{ of } 279$

**Solution:**
Memorize the repeating percent: $11.11\% = \frac{1}{9}$.
$\frac{1}{9} \times 279 = 31$.

**Answer:** $31$

## Powers, roots & approximation

**Q12.** What is the closest integer to $\sqrt{7500}$?

**Solution:**
Find nearby squares of multiples of $10$: $80^2 = 6400$ and $90^2 = 8100$.
Test $85^2$ using the ending-in-5 trick: $8 \times 9 = 72$, so $85^2 = 7225$.
Since $7500$ is greater than $7225$, test $86^2$ and $87^2$.
$86^2 = (85+1)^2 \approx 7225 + 2 \times 85 = 7395$ (exact is $7396$).
$87^2 = (90-3)^2 = 8100 - 540 + 9 = 7569$.
$7500$ is between $86^2$ ($7396$, gap $104$) and $87^2$ ($7569$, gap $69$). The closest integer is $87$.

**Answer:** $87$

**Q13.** Calculate $2^{12} - 2^{10}$

**Solution:**
Factor out the smaller power: $2^{10}(2^2 - 1) = 2^{10} \times 3$.
Memorize powers of $2$: $2^{10} = 1024$.
$1024 \times 3 = 3072$.

**Answer:** $3072$

**Q14.** What is the cube root of $4096$?

**Solution:**
Memorize powers of $2$, or use bounds and last digits.
$10^3 = 1000$ and $20^3 = 8000$, so the root is between $10$ and $20$.
The last digit is $6$. The only single digit whose cube ends in $6$ is $6$ (since $6 \times 6 = 36$, and $36 \times 6 = 216$).
Therefore, the root must be $16$. Verify: $16 = 2^4$, so $16^3 = 2^{12} = 4096$.

**Answer:** $16$

::: trap
When estimating square roots of larger powers of $10$, do not simply divide the root of the smaller base by $10$. For example, $\sqrt{1000} \neq 10$. It is $\sqrt{100 \times 10} = 10\sqrt{10} \approx 31.6$.
:::

## Sequences & totals in your head

**Q15.** What is the sum of the first $40$ positive integers?

**Solution:**
Use the arithmetic series sum formula $S = \frac{n(n+1)}{2}$.
$S = \frac{40 \times 41}{2} = 20 \times 41 = 820$.

**Answer:** $820$

**Q16.** What is the sum of all odd numbers between $1$ and $50$?

**Solution:**
There are $25$ odd numbers between $1$ and $50$ (from $1$ to $49$).
The sum of the first $n$ odd positive integers is exactly $n^2$.
Here $n = 25$, so $25^2 = 625$.

**Answer:** $625$

**Q17.** Find the average of $143, 147, 151, 158, 161$.

**Solution:**
Pick a base number to subtract from all values, say $150$.
The deviations from $150$ are $-7, -3, +1, +8, +11$.
Sum the deviations: $-10 + 20 = +10$.
Divide the total deviation by $5$: $+10 / 5 = +2$.
Add this average deviation back to the base: $150 + 2 = 152$.

**Answer:** $152$

## Number sense / sanity checks

**Q18.** Which of the following numbers is evenly divisible by $9$?
(a) $34561$  (b) $81235$  (c) $72531$  (d) $49123$

**Solution:**
A number is divisible by $9$ if the sum of its digits is divisible by $9$ (Casting out nines). You can group digits that sum to $9$ and cross them out to evaluate faster.
(a) $3+4+5+6+1 = 19$
(b) $8+1=9$ (cross out), remaining $2+3+5 = 10$
(c) $7+2=9$ (cross out), remaining $5+3+1 = 9$ (divisible by $9$).

**Answer:** (c)

**Q19.** What is the last digit of $3^{47}$?

**Solution:**
Powers of numbers ending in $3$ have a repeating cycle of $4$ for their last digits: $3, 9, 7, 1$.
Divide the exponent by $4$: $47 \div 4 = 11$ with a remainder of $3$.
The 3rd item in the repeating cycle is $7$.

**Answer:** $7$

::: keypoint
**Last Digit Cycles:**

- End in $0, 1, 5, 6$: always end in the same digit.
- End in $4, 9$: cycle of $2$ length (e.g., $4, 6$).
- End in $2, 3, 7, 8$: cycle of $4$ length.
:::

## Rapid-fire OA set

**Q20.** $18 \times 14$

**Solution:**
Use the base-$10$ trick for teens: add the units digit of the second number to the entire first number, multiply by $10$, and add the product of the units.
$(18 + 4) \times 10 = 220$.
$8 \times 4 = 32$.
$220 + 32 = 252$.

**Answer:** $252$

**Q21.** $37 \times 43$

**Solution:**
Notice this is $(40 - 3)(40 + 3)$.
Use the difference of squares shortcut: $40^2 - 3^2 = 1600 - 9 = 1591$.

**Answer:** $1591$

**Q22.** $\frac{13}{50} \text{ of } 450$

**Solution:**
Divide $450$ by $50$ first: $450 / 50 = 9$.
Then multiply by $13$: $13 \times 9 = 117$.

**Answer:** $117$

**Q23.** $1.5 \times 2.8$

**Solution:**
Multiply $2.8$ by $1$ and add half of $2.8$.
$2.8 + 1.4 = 4.2$.

**Answer:** $4.2$

**Q24.** $384 + 297$

**Solution:**
Add $300$ and subtract $3$.
$384 + 300 = 684$.
$684 - 3 = 681$.

**Answer:** $681$

**Q25.** A stock drops by $20\%$ then increases by $25\%$. If its final price is $150$ dollars, what was its starting price?
(a) $140$  (b) $150$  (c) $160$  (d) $170$

**Solution:**
A drop of $20\%$ multiplies the price by $0.8$ (or $\frac{4}{5}$). An increase of $25\%$ multiplies by $1.25$ (or $\frac{5}{4}$).
The net change multiplier is $\frac{4}{5} \times \frac{5}{4} = 1$.
The stock is exactly back to its original price.

**Answer:** $150$ (b)

::: trap
When dealing with successive percentage changes, beginners often just add the percentages. A $20\%$ decrease followed by a $25\%$ increase does not yield a net $5\%$ increase. You must multiply the factors: $0.80 \times 1.25 = 1.00$.
:::

## Sources

- TraderMath — https://www.tradermath.org/ (Mental-math drills & 80-in-8 format)
- QuantQuestions — https://www.quantquestions.com/ (Speed arithmetic logic)
- RankYourBrain — https://rankyourbrain.com/ (Expert-level mental math patterns)
