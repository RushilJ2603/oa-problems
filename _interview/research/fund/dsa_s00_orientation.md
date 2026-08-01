# Orientation — How Aptitude Assessments Work

Before diving into specific problem patterns, it is crucial to understand *why* you are being tested and *how* to approach these tests. Aptitude is not a test of deep theoretical mathematics; it is a test of pattern-recognition, mental agility, and speed.

## The assessment landscape

Different companies test aptitude differently, tailored to the demands of their roles.

| Target Track | Format & Focus Areas | Typical Timing |
| :--- | :--- | :--- |
| **Product-SDE OAs** (Microsoft, Google, Uber) | Mostly Data Structures & Algorithms (DSA) coding, with 10–15 logical or quant MCQs. Focus on combinatorics, probability, and bitwise logic. | Fast (1–2 mins/MCQ) alongside 45+ min coding. |
| **Service-Firm OAs** (TCS, Infosys, Wipro, Accenture) | Comprehensive sections covering quantitative aptitude, logical reasoning, verbal ability, and data interpretation (DI). | Speed-heavy (45–60 secs/question). |
| **Quant / Prop-Trading** (De Shaw, Millennium, Jane St) | Advanced probability, expected value, statistics, mental math, game theory, and brain teasers. | Brutal time limits or live high-pressure interviews. |
| **BA / Analyst Roles** | Statistics, guesstimates, data interpretation (charts/graphs), and case-based reasoning. | Moderate to fast; emphasizes accuracy and business logic. |

<br>

::: keypoint
**Match your prep to your target.** If you are aiming for Google, focus on bitwise tricks and probability. If targeting Jane Street, live mental math and expected value are paramount. If writing the TCS NQT, you need speed across all standard arithmetic topics.
:::

## The mental-math & speed toolkit

You cannot afford to calculate everything from scratch under time pressure. The following facts and tricks must be memorized to shave seconds off your solving time.

### Essential Tables

**Fractions to Percentages**

| Fraction | Percentage | Fraction | Percentage |
| :--- | :--- | :--- | :--- |
| $1/2$ | $50\%$ | $1/8$ | $12.5\%$ |
| $1/3$ | $33.33\%$ | $1/9$ | $11.11\%$ |
| $1/4$ | $25\%$ | $1/10$ | $10\%$ |
| $1/5$ | $20\%$ | $1/11$ | $9.09\%$ |
| $1/6$ | $16.66\%$ | $1/12$ | $8.33\%$ |
| $1/7$ | $14.28\%$ | $1/16$ | $6.25\%$ |

**Squares (1 to 30)**
$1^2 = 1, 2^2 = 4, 3^2 = 9, 4^2 = 16, 5^2 = 25, \ldots, 10^2 = 100$
$11^2 = 121, 12^2 = 144, 13^2 = 169, 14^2 = 196, 15^2 = 225$
$16^2 = 256, 17^2 = 289, 18^2 = 324, 19^2 = 361, 20^2 = 400$
$21^2 = 441, 22^2 = 484, 23^2 = 529, 24^2 = 576, 25^2 = 625$
$26^2 = 676, 27^2 = 729, 28^2 = 784, 29^2 = 841, 30^2 = 900$

**Cubes (1 to 15)**
$1^3 = 1, 2^3 = 8, 3^3 = 27, 4^3 = 64, 5^3 = 125, 6^3 = 216, 7^3 = 343, 8^3 = 512, 9^3 = 729, 10^3 = 1000$
$11^3 = 1331, 12^3 = 1728, 13^3 = 2197, 14^3 = 2744, 15^3 = 3375$

**Powers of 2 (up to $2^{12}$)**
$2^1=2$, $2^2=4$, $2^3=8$, $2^4=16$, $2^5=32$, $2^6=64$, $2^7=128$, $2^8=256$, $2^9=512$, $2^{10}=1024$, $2^{11}=2048$, $2^{12}=4096$

### Divisibility & Cyclicity

**Divisibility Rules**

- **2, 4, 8:** Check the last $1$, $2$, or $3$ digits, respectively.
- **3, 9:** The sum of all digits must be divisible by $3$ or $9$.
- **5:** The last digit is $0$ or $5$.
- **6:** Must be divisible by both $2$ and $3$.
- **7:** Double the last digit and subtract it from the rest of the number; the result must be divisible by $7$.
- **11:** The alternating sum of the digits must be $0$ or divisible by $11$.

**Unit Digit Cyclicity**
When taking powers of numbers, the unit digit repeats in a cycle:

| End Digit | Cycle Length | Cyclicity Pattern (powers 1, 2, 3, 4) |
| :--- | :--- | :--- |
| **0, 1, 5, 6** | 1 | Stays the same (e.g. $5^n$ ends in $5$) |
| **4, 9** | 2 | $4 \to 4, 6$; $9 \to 9, 1$ |
| **2, 3, 7, 8** | 4 | $2 \to 2, 4, 8, 6$; $3 \to 3, 9, 7, 1$; $7 \to 7, 9, 3, 1$; $8 \to 8, 4, 2, 6$ |

<br>

::: keypoint
**Fast Multiplication Tricks**

- **$\times 11$:** Split the number, insert the sum in the middle. E.g., $43 \times 11 \implies 4\_3 \implies 4\,(4+3)\,3 = 473$.
- **$\times 25$:** Add two zeros and divide by $4$. E.g., $36 \times 25 = 3600 / 4 = 900$.
- **Near-Base (e.g., base 100):** $96 \times 98$. Deficits are $-4$ and $-2$. Result = $(96 - 2) \times 100 + (-4 \times -2) = 9408$.
- **Split & Add:** Break one number apart. $43 \times 12 = 43 \times (10 + 2) = 430 + 86 = 516$.
:::

### Speed Drills

**Q1. Find $11.11\%$ of $4509$.**

**Solution:** Recognize $11.11\%$ as exactly $1/9$. So, $4509 / 9 = 501$.

**Answer: 501**

**Q2. What is the unit digit of $7^{105}$?**

**Solution:** The cycle length of $7$ is $4$. Divide the power by $4$: $105 = 4 \times 26 + 1$. The remainder is $1$, so it maps to the first item in the cycle for $7$, which is $7^1$.

**Answer: 7**

**Q3. Is $9182736$ divisible by $11$?**

**Solution:** Alternating sum: $9 - 1 + 8 - 2 + 7 - 3 + 6 = 24$. Since $24$ is not divisible by $11$, the number is not.

**Answer: No**

**Q4. Calculate $104 \times 107$ quickly.**

**Solution:** Near-base $100$. Surpluses are $+4$ and $+7$. Result = $(104+7) \times 100 + (4 \times 7) = 11128$.

**Answer: 11128**

**Q5. Evaluate $64 \times 25$.**

**Solution:** Multiply by $100$ and divide by $4$. $6400 / 4 = 1600$.

**Answer: 1600**

## Approximation & sanity-checking under time pressure

Often, calculating the exact decimal is a trap. If the multiple-choice options are far apart, approximate aggressively.

- **Percentage Estimation:** To find $16\%$ of a number, find $10\%$ (move decimal once), find $5\%$ (half of $10\%$), and $1\%$ (move decimal twice), then sum them.
- **Order-of-Magnitude Checks:** If computing $4.1 \times 213$, the answer must be slightly more than $4 \times 200 = 800$. If your result is $87$ or $8000$, you missed a decimal.

**Q6. Approximate $14.8\%$ of $610$.**

**Solution:** $10\% = 61$. $5\% \approx 30$. Sum is $91$. Since $14.8\%$ is slightly less than $15\%$, the answer is just below $91$. (Exact is $90.28$).

**Answer: ~90**

**Q7. Estimate $1205 \times 399$.**

**Solution:** Round to $1200 \times 400$. $12 \times 4 = 48$, and append four zeros $\to 480000$. (Exact is $480795$).

**Answer: ~480000**

## Decoding "wrapped" OA questions

Modern OA questions rarely present a naked formula; they wrap it in a narrative or a software engineering context. 

<br>

::: keypoint
**Strip the story.** The moment you read a word problem, strip away the narrative to expose the underlying math model (e.g., relative speed, set theory, or bitwise arithmetic).
:::

**Q8. Two autonomous robots, Rover and Probe, are deployed on a circular track of circumference $360\text{ m}$. Rover moves clockwise at $8\text{ m/s}$ and Probe moves anticlockwise at $10\text{ m/s}$. They deploy simultaneously from locations $90\text{ m}$ apart along the path. How long until their second sensor handshake (meeting)?**

**Solution:** This is a classic **relative speed** problem dressed up. Their combined speed is $8 + 10 = 18\text{ m/s}$. 
First meeting distance = initial gap = $90\text{ m}$.
Second meeting requires covering the initial gap PLUS one full track perimeter = $90 + 360 = 450\text{ m}$.
Time = Distance / Combined Speed = $450 / 18 = 25\text{ s}$.

**Answer: 25 s**

**Q9. Calculate the number of active nodes in a networking tree if the total is given by the expression $3 \times 4096 + 15 \times 256 + 5 \times 16 + 3$.**

**Solution:** Strip the arithmetic. Notice the multipliers are all $< 16$, and the bases ($16^3, 16^2, 16^1, 16^0$) represent hexadecimal place values. This is just the hex number `0x3F53`. The question is asking for the `popcount` (number of set bits) of `0x3F53`.
$3 = 0011$ (2 bits), $F (15) = 1111$ (4 bits), $5 = 0101$ (2 bits), $3 = 0011$ (2 bits).
Total set bits = $2 + 4 + 2 + 2 = 10$.

**Answer: 10**

## Thinking out loud on puzzles (interviews)

For quantitative, prop-trading, and analytical roles, interviews often feature live probability questions and brain teasers. 

<br>

::: interview
Interviewer grading is based on your **reasoning and structured approach**, not just the final number. Blurting out a memorized answer actually hurts you. You must think out loud.
:::

**The 5-Step Interview Attack:**

1. **Restate the problem:** Confirm all constraints so you don't solve the wrong problem.
2. **Simplify or try a small case:** If the problem asks about 100 prisoners or 100 coins, solve it for 2, then 3.
3. **Find the invariant or expected value:** Look for what stays constant (e.g., parity) or set up a recursive EV equation.
4. **Generalize:** Extend your small-case pattern to $N$.
5. **Sanity-check:** Test edge cases ($N=0, N=1$, or extremes like probabilities of $0$ or $1$) to ensure your formula doesn't break.

## Sources

- PrepInsta — https://prepinsta.com/ (Company-specific OA patterns and aptitude).
- Hitbullseye — https://www.hitbullseye.com/ (Speed math tricks and quantitative tutorials).
- TraderMath — https://www.tradermath.org/ (Mental math speed drills and approximations).
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/ (Topic-wise question banks and interview experiences).
- Cisco OA Transcribed Set (Wrapped problem examples).
