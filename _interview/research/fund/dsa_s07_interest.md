# Simple & Compound Interest

::: definition
**Simple Interest (SI)**
$$SI = \frac{P \times R \times T}{100}$$
where $P$ is principal, $R$ is rate per annum, and $T$ is time in years. Amount $A = P + SI$.

**Compound Interest (CI)**
Amount after $n$ periods:
$$A = P \left(1 + \frac{R}{100}\right)^n$$
where $R$ is the rate per period, and $n$ is the number of compounding periods. $CI = A - P$.

**Frequency Adjustments**

- **Half-yearly:** Rate becomes $R/2$, periods become $2T$.
- **Quarterly:** Rate becomes $R/4$, periods become $4T$.

**CI − SI Differences**

- **For 2 years:** $\text{Diff} = P \left(\frac{R}{100}\right)^2$
- **For 3 years:** $\text{Diff} = P \left(\frac{R}{100}\right)^2 \left(\frac{R}{100} + 3\right)$
:::

## Simple Interest

**Q1.** A sum of \$4,000 is lent at $12\%$ per annum simple interest. What is the interest earned after 3 years and 4 months?
(a) \$1,200 (b) \$1,600 (c) \$1,440 (d) \$1,800

**Solution:**
Time $T = 3 + \frac{4}{12} = \frac{10}{3}$ years.
$$SI = \frac{4000 \times 12 \times \frac{10}{3}}{100} = 40 \times 12 \times \frac{10}{3} = 40 \times 40 = 1600$$

**Answer:** 1600 (b)

**Q2.** A certain sum of money amounts to \$5,200 in 5 years and \$5,680 in 7 years at simple interest. What is the rate of interest per annum?
(a) $3\%$ (b) $4\%$ (c) $5\%$ (d) $6\%$

**Solution:**
Interest for 2 years (from year 5 to year 7) $= 5680 - 5200 = 480$.
Interest for 1 year $= \frac{480}{2} = 240$.
Interest for 5 years $= 240 \times 5 = 1200$.
Principal $P = \text{Amount after 5 years} - \text{Interest for 5 years} = 5200 - 1200 = 4000$.
Rate $R = \frac{SI \times 100}{P \times T} = \frac{240 \times 100}{4000 \times 1} = 6\%$.

**Answer:** 6% (d)

**Q3.** A sum of money put at simple interest doubles itself in 8 years. In how many years will it become 5 times itself at the same rate of interest?
(a) 16 years (b) 24 years (c) 32 years (d) 40 years

**Solution:**
Let the principal be $P$. To double ($2P$), the interest earned is $P$.
Time to earn $P$ interest $= 8$ years.
To become 5 times itself ($5P$), the interest earned must be $4P$.
Since simple interest scales linearly with time, the time required is $4 \times 8 = 32$ years.

::: keypoint
If a sum becomes $n$ times itself in $T$ years at SI, it will become $m$ times itself in $\frac{m-1}{n-1} \times T$ years.
:::

**Answer:** 32 years (c)

**Q4.** A man lent a part of \$10,000 at $8\%$ per annum and the rest at $10\%$ per annum, both at simple interest. If the total interest earned in one year is \$880, how much was lent at $8\%$?
(a) \$4,000 (b) \$5,000 (c) \$6,000 (d) \$8,000

**Solution:**
Using allegation on the rates:
Rate 1 $= 8\%$, Rate 2 $= 10\%$.
Net average rate $= \frac{880}{10000} \times 100 = 8.8\%$.
Ratio of parts $= (10 - 8.8) : (8.8 - 8) = 1.2 : 0.8 = 3 : 2$.
Amount lent at $8\%$ (the first part) $= \frac{3}{5} \times 10000 = 6000$.

**Answer:** 6000 (c)

## Compound Interest

**Q5.** What is the compound interest on \$8,000 for 2 years at $5\%$ per annum, compounded annually?
(a) \$800 (b) \$820 (c) \$840 (d) \$860

**Solution:**
Amount $A = 8000 \left(1 + \frac{5}{100}\right)^2 = 8000 \left(\frac{21}{20}\right)^2 = 8000 \times \frac{441}{400} = 20 \times 441 = 8820$.
$CI = 8820 - 8000 = 820$.

::: keypoint
For 2 years, compound interest can be quickly calculated as successive percentage changes. An $R\%$ rate for 2 years yields an effective rate of $R + R + \frac{R^2}{100}\%$. Here, $5 + 5 + 0.25 = 10.25\%$.
$10.25\%$ of $8000 = 820$.
:::

**Answer:** 820 (b)

**Q6.** Find the compound interest on \$10,000 at $20\%$ per annum for 18 months, compounded half-yearly.
(a) \$3,000 (b) \$3,200 (c) \$3,310 (d) \$3,450

**Solution:**
Rate per half-year $= \frac{20\%}{2} = 10\%$.
Time in half-years $= 18 \text{ months} = 3 \text{ periods}$.
Amount $A = 10000 \left(1 + \frac{10}{100}\right)^3 = 10000 \left(\frac{11}{10}\right)^3 = 10000 \times \frac{1331}{1000} = 13310$.
$CI = 13310 - 10000 = 3310$.

**Answer:** 3310 (c)

**Q7.** A sum is invested for 9 months at $16\%$ per annum, compounded quarterly. If the amount becomes \$17,576, what is the principal?
(a) \$15,000 (b) \$15,625 (c) \$16,000 (d) \$16,500

**Solution:**
Rate per quarter $= \frac{16\%}{4} = 4\%$.
Time in quarters $= 9 \text{ months} = 3 \text{ periods}$.
$$A = P\left(1 + \frac{4}{100}\right)^3 = P\left(\frac{26}{25}\right)^3$$
$$17576 = P \times \frac{17576}{15625}$$
$$P = 15625$$

**Answer:** 15625 (b)

**Q8.** What will be the compound interest on \$10,000 for $2 \frac{1}{2}$ years at $10\%$ per annum, compounded annually?
(a) \$2,500 (b) \$2,625 (c) \$2,705 (d) \$2,805

**Solution:**
For fractional periods, calculate CI for full years, then use the proportional simple interest rate for the fraction of the year.
Amount after 2 years $= 10000 \times (1.1)^2 = 12100$.
For the final half-year, the rate is $10\% \times \frac{1}{2} = 5\%$.
Amount after 2.5 years $= 12100 \times 1.05 = 12705$.
$CI = 12705 - 10000 = 2705$.

**Answer:** 2705 (c)

**Q9.** The simple interest on a sum of money for 2 years at $8\%$ per annum is \$2,400. What would be the compound interest on the same sum for the same period and rate?
(a) \$2,484 (b) \$2,496 (c) \$2,512 (d) \$2,540

**Solution:**
Simple interest for 2 years is \$2,400, so SI for 1 year is \$1,200.
Compound interest for the first year is identical to SI: \$1,200.
CI for the second year includes interest on the principal (\$1,200) plus interest on the first year's interest.
Interest on first year's interest $= 8\%$ of $1200 = 96$.
Total CI $= 1200 + 1200 + 96 = 2496$.

**Answer:** 2496 (b)

## CI − SI Differences

**Q10.** The difference between compound interest and simple interest on a certain sum for 2 years at $10\%$ per annum is \$40. What is the sum?
(a) \$3,000 (b) \$4,000 (c) \$5,000 (d) \$6,000

**Solution:**
For 2 years, the difference between CI and SI on principal $P$ is:
$$\text{Diff} = P \left(\frac{R}{100}\right)^2$$
$$40 = P \left(\frac{10}{100}\right)^2 = P \left(\frac{1}{10}\right)^2 = \frac{P}{100}$$
$$P = 40 \times 100 = 4000$$

**Answer:** 4000 (b)

**Q11.** What is the difference between the compound interest and simple interest on \$8,000 for 3 years at $5\%$ per annum?
(a) \$61 (b) \$65 (c) \$70 (d) \$75

**Solution:**
For 3 years, the difference between CI and SI is:
$$\text{Diff} = P \left(\frac{R}{100}\right)^2 \left(\frac{R}{100} + 3\right)$$
$$\text{Diff} = 8000 \left(\frac{5}{100}\right)^2 \left(3 + \frac{5}{100}\right)$$
$$\text{Diff} = 8000 \times \frac{1}{400} \times 3.05 = 20 \times 3.05 = 61$$

**Answer:** 61 (a)

**Q12.** The difference between compound interest and simple interest on a sum for 2 years is \$15, and for 3 years is \$48. What is the rate of interest?
(a) $15\%$ (b) $20\%$ (c) $25\%$ (d) $30\%$

**Solution:**
Let the difference for 2 years be $D_2 = P\left(\frac{R}{100}\right)^2$.
The difference for 3 years is $D_3 = P\left(\frac{R}{100}\right)^2 \left(3 + \frac{R}{100}\right)$.
Thus, taking the ratio:
$$\frac{D_3}{D_2} = 3 + \frac{R}{100}$$
$$\frac{48}{15} = 3.2 = 3 + \frac{R}{100}$$
$$\frac{R}{100} = 0.2 \implies R = 20\%$$

**Answer:** 20% (b)

## Applications

**Q13.** A sum of money placed at compound interest becomes 3 times itself in 4 years. In how many years will it become 81 times itself?
(a) 12 years (b) 16 years (c) 20 years (d) 24 years

**Solution:**
At CI, the amount grows exponentially: $A = P(1+R)^n$.
If the sum triples ($P \to 3P$) in 4 years, then every 4 years the amount is multiplied by 3.
We need the amount to become 81 times itself.
$81 = 3^4$.
It takes 4 compounding cycles to multiply the sum by 81.
Total time $= 4 \times 4 = 16$ years.

**Answer:** 16 (b)

**Q14.** The population of a town increases by $10\%$ every year. If the current population is 13,310, what was the population 3 years ago?
(a) 9,000 (b) 10,000 (c) 11,000 (d) 12,000

**Solution:**
Population growth acts precisely like compound interest.
$$\text{Current Population} = \text{Past Population} \times \left(1 + \frac{R}{100}\right)^n$$
$$13310 = P \times \left(1 + \frac{10}{100}\right)^3$$
$$13310 = P \times \left(\frac{11}{10}\right)^3 = P \times \frac{1331}{1000}$$
$$P = \frac{13310 \times 1000}{1331} = 10000$$

**Answer:** 10000 (b)

**Q15.** A man borrows \$21,000 at $10\%$ per annum compound interest. He wants to repay it in two equal annual instalments, paid at the end of each year. What is the value of each instalment?
(a) \$11,500 (b) \$12,100 (c) \$12,600 (d) \$13,000

**Solution:**
Let the instalment be $X$. We equate the present values of each future instalment to the initial loan principal $P$.
$$P = \frac{X}{1+r} + \frac{X}{(1+r)^2}$$
Here, $r = 0.1$, so $1+r = 1.1 = \frac{11}{10}$.
$$21000 = X \left(\frac{10}{11}\right) + X \left(\frac{10}{11}\right)^2$$
$$21000 = X \left( \frac{10}{11} + \frac{100}{121} \right) = X \left( \frac{110 + 100}{121} \right) = X \left( \frac{210}{121} \right)$$
$$X = \frac{21000 \times 121}{210} = 100 \times 121 = 12100$$

::: interview
Instalment problems often trap candidates because they try to subtract instalments from the principal directly or divide the final amount by two. In OAs, you must always equate the *present values* of the instalments to the original loan amount.
:::

**Answer:** 12100 (b)

## Wrapped OA Variants

**Q16.** A startup founder invests her initial seed capital of \$100,000 into a low-risk fund yielding $10\%$ compounded annually. Exactly one year later, after the interest is credited, she withdraws \$30,000 to fund operational costs. The remaining balance is left to compound for another 2 years at the same rate. What is the final value of the fund at the end of the 3rd year?
(a) \$95,400 (b) \$96,800 (c) \$98,200 (d) \$100,000

**Solution:**
Value after Year 1 before withdrawal $= 100000 \times 1.10 = 110000$.
Value after withdrawal $= 110000 - 30000 = 80000$.
This new principal compounds for the remaining 2 years.
Value after Year 3 $= 80000 \times (1.10)^2 = 80000 \times 1.21 = 96800$.

::: trap
A common mistake is treating the withdrawal as reducing the initial principal instead of the compounded amount, or trying to calculate interest on \$100,000 and \$30,000 entirely separately without matching their timelines. Always calculate step-by-step when a deposit or withdrawal interrupts compounding.
:::

**Answer:** 96800 (b)

**Q17.** A cloud storage platform offers a rewards system: users deposit "cloud credits" which grow at a simple interest rate of $15\%$ per annum. However, any credits kept in the system beyond 3 years are automatically converted to a new tier that grows at $20\%$ per annum compound interest, compounding annually on the new balance. If a user deposits 2,000 credits and leaves them untouched, how many credits will they have at the exact end of 5 years?
(a) 3,850 (b) 4,176 (c) 4,200 (d) 4,536

**Solution:**
First 3 years (Simple Interest phase):
$$SI = \frac{2000 \times 15 \times 3}{100} = 20 \times 45 = 900$$
Amount at the end of year 3 $= 2000 + 900 = 2900$.
This 2,900 becomes the principal for the next phase.
Next 2 years (Compound Interest phase at $20\%$):
$$\text{Amount} = 2900 \times \left(1 + \frac{20}{100}\right)^2 = 2900 \times (1.2)^2 = 2900 \times 1.44$$
$2900 \times 1.44 = 29 \times 144 = 4176$.

**Answer:** 4176 (b)

## Sources

- IndiaBix — https://www.indiabix.com/aptitude/simple-interest/
- IndiaBix — https://www.indiabix.com/aptitude/compound-interest/
- CareerBless — http://www.careerbless.com/aptitude/qa/home.php
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
