# Ranking, Ordering & Data Sufficiency

::: keypoint
**Ranking/order:** To convert between positions from either end in a sequence:
$\text{Total} = (\text{rank from top}) + (\text{rank from bottom}) - 1$
For the number of people strictly between two positions $A$ and $B$ (where $A < B$ in a sorted index):
$\text{Between} = B - A - 1$
:::

::: definition
**Data Sufficiency Standard Options:**
In these questions, you are given a question followed by two statements, I and II. Choose:

(a) if statement I alone is sufficient to answer the question, but statement II alone is not.
(b) if statement II alone is sufficient, but statement I alone is not.
(c) if both statements I and II together are necessary to answer the question.
(d) if each statement alone is sufficient.
(e) if statements I and II together are not sufficient to answer the question, and additional data is needed.
:::

## Rank & position

**Q1.** In a row of students facing north, Rahul is $14^{\text{th}}$ from the left end and $23^{\text{rd}}$ from the right end. How many students are in the row?
(a) $35$ (b) $36$ (c) $37$ (d) $38$

**Solution:**
Using the total formula: $\text{Total} = \text{Left} + \text{Right} - 1$.
$\text{Total} = 14 + 23 - 1 = 36$.

**Answer:** $36$ (b)

**Q2.** In a class of $50$ students, A is $18^{\text{th}}$ from the top. If B is $7$ ranks below A, what is B's rank from the bottom?
(a) $24^{\text{th}}$ (b) $25^{\text{th}}$ (c) $26^{\text{th}}$ (d) $27^{\text{th}}$

**Solution:**
B's rank from the top is $18 + 7 = 25^{\text{th}}$.
Using $\text{Total} = \text{Top} + \text{Bottom} - 1$:
$50 = 25 + \text{Bottom} - 1 \implies \text{Bottom} = 50 - 24 = 26$.

**Answer:** $26^{\text{th}}$ (c)

**Q3.** In a row of boys, P is $15^{\text{th}}$ from the left and Q is $21^{\text{st}}$ from the right. When they interchange their positions, P becomes $25^{\text{th}}$ from the left. How many boys are in the row?
(a) $44$ (b) $45$ (c) $46$ (d) $47$

**Solution:**
After swapping, P is at Q's original position.
So, Q's original position is $25^{\text{th}}$ from the left AND $21^{\text{st}}$ from the right.
$\text{Total} = \text{Left} + \text{Right} - 1 = 25 + 21 - 1 = 45$.

**Answer:** $45$ (b)

**Q4.** In a row of $40$ girls, R is $22^{\text{nd}}$ from the left and S is $26^{\text{th}}$ from the right. How many girls are sitting between them?
(a) $6$ (b) $7$ (c) $8$ (d) $9$

**Solution:**
Sum of positions is $22 + 26 = 48$.
Since $48 > 40$, the sequence overlaps (S is to the left of R).
The number of people between them is $(\text{Left} + \text{Right}) - \text{Total} - 2 = 48 - 40 - 2 = 6$.
(The $-2$ excludes R and S themselves).

**Answer:** $6$ (a)

::: trap
When $\text{Left} + \text{Right} > \text{Total}$, the positions cross over. The number of people strictly between them is $(\text{Left} + \text{Right}) - \text{Total} - 2$. Do not forget the $- 2$!
:::

## Comparison ordering

**Q5.** A is taller than B but shorter than C. D is taller than A but shorter than C. E is taller than B but shorter than A. Who is the tallest?
(a) A (b) C (c) D (d) Cannot be determined

**Solution:**
Construct the chain step-by-step.
From "A > B, C > A", we have C > A > B.
From "D > A, C > D", we insert D to get C > D > A > B.
From "A > E, E > B", we insert E to get C > D > A > E > B.
C is strictly greater than all others.

**Answer:** C (b)

**Q6.** Among five friends P, Q, R, S, and T, each having a different weight, R is heavier than only P. S is lighter than Q and heavier than T. Who is the heaviest?
(a) Q (b) S (c) T (d) Cannot be determined

**Solution:**
"R is heavier than *only* P" locks their positions at the bottom. The lightest is P, and the second lightest is R (positions 5 and 4).
The top three spots belong to Q, S, and T.
We are given S < Q and S > T, which means Q > S > T.
The full order is Q > S > T > R > P.
The heaviest is Q.

**Answer:** Q (a)

**Q7.** Five buildings are of different heights. Building V is taller than building W but shorter than X. Building Y is taller than Z but shorter than W. Which building is the median in height?
(a) V (b) W (c) X (d) Y

**Solution:**
From the first statement: X > V > W.
From the second statement: W > Y > Z.
Combining them gives a single strict chain: X > V > W > Y > Z.
The middle (median) building is W.

**Answer:** W (b)

**Q8.** A group of five runners finished a race. P finished before Q but after R. S finished before T but after Q. Who finished last?
(a) P (b) Q (c) S (d) T

**Solution:**
R > P > Q (where > means finished earlier).
Q > S > T.
Combined: R > P > Q > S > T.
T finished last.

**Answer:** T (d)

## Data Sufficiency — quant

**Q9.** What is the value of the two-digit positive integer $x$?

I. The sum of the digits of $x$ is $9$.
II. The difference between the digits of $x$ is $5$.

(a) Statement I alone is sufficient
(b) Statement II alone is sufficient
(c) Both statements together are sufficient
(d) Each statement alone is sufficient
(e) Both statements together are insufficient

**Solution:**
Test I: Sum is $9$. Could be $18, 27, 36, \dots$ Not sufficient.
Test II: Difference is $5$. Could be $16, 61, 27, 72, \dots$ Not sufficient.
Test I + II: Digits sum to $9$, differ by $5$. The digits must be $7$ and $2$. So $x$ can be $72$ or $27$. Two possible values remain. Still not sufficient to find the *unique* value of $x$.

**Answer:** (e)

::: trap
In Data Sufficiency, "sufficient" means you can determine exactly ONE unique answer. If multiple values are still possible (like $72$ and $27$), the data is strictly insufficient.
:::

**Q10.** What is the present age of the mother?

I. The ratio of the present ages of the mother and her son is $5:2$.
II. Five years ago, the mother was three times as old as her son.
(a) I alone (b) II alone (c) Both together (d) Either alone (e) Insufficient

**Solution:**
Test I: $M = 5k, S = 2k$. We don't know $k$. Not sufficient.
Test II: $(M - 5) = 3(S - 5)$. Infinite integer solutions (e.g., $M=20, S=10$). Not sufficient.
Test I + II: Substitute $M = 5k, S = 2k$ into the second equation:
$(5k - 5) = 3(2k - 5) \implies 5k - 5 = 6k - 15 \implies k = 10$.
$M = 50$. A unique answer exists. Both together are sufficient.

**Answer:** (c)

**Q11.** Is the integer $n$ odd?

I. $2n + 5$ is odd.
II. $n^{2} + n$ is even.
(a) I alone (b) II alone (c) Both together (d) Either alone (e) Insufficient

**Solution:**
Test I: $2n + 5$ is odd. Since $5$ is odd, $2n$ must be even. But $2n$ is *always* even for any integer $n$. So $n$ could be even ($2(2)+5 = 9$) or odd ($2(3)+5 = 11$). Not sufficient.
Test II: $n^{2} + n = n(n+1)$. The product of consecutive integers is always even. So $n$ could be even or odd. Not sufficient.
Test I + II: Both statements are mathematical tautologies for any integer. We still cannot know if $n$ is odd.

**Answer:** (e)

**Q12.** What is the speed of the train in m/s?

I. The train crosses a $200\text{ m}$ long platform in $20\text{ seconds}$.
II. The train crosses a stationary pole in $10\text{ seconds}$.
(a) I alone (b) II alone (c) Both together (d) Either alone (e) Insufficient

**Solution:**
Test I: Let length be $L$, speed $v$. $(L + 200) / v = 20$. Two variables, not sufficient.
Test II: $L / v = 10$. Two variables, not sufficient.
Test I + II: From II, $L = 10v$. Substitute into I: $(10v + 200) / v = 20 \implies 10v + 200 = 20v \implies 10v = 200 \implies v = 20\text{ m/s}$. The speed is uniquely found. Both together are sufficient.

**Answer:** (c)

**Q13.** Is $x > y$? (Given $x, y$ are real numbers)

I. $x^{2} > y^{2}$
II. $x > 0$
(a) I alone (b) II alone (c) Both together (d) Either alone (e) Insufficient

**Solution:**
Test I: $x^{2} > y^{2}$. True if $x=3, y=2$ ($3 > 2$). Also true if $x=-3, y=2$ ($-3 \not> 2$). Not sufficient.
Test II: $x > 0$. We know nothing about $y$. Not sufficient.
Test I + II: $x^{2} > y^{2}$ implies $|x| > |y|$.
Since we know $x > 0$ from II, $|x| = x$. Thus, $x > |y|$.
Because absolute value is always greater than or equal to the number itself ($|y| \ge y$ and $|y| \ge -y$), it follows that $x > y$ in all cases. Sufficient.

**Answer:** (c)

## Data Sufficiency — logic

**Q14.** Among five boxes A, B, C, D, and E stacked one above another, which box is at the bottom?

I. Box A is exactly above box C, and box D is exactly above box B.
II. Box E is somewhere above box D, and box C is exactly above box E.
(a) I alone (b) II alone (c) Both together (d) Either alone (e) Insufficient

**Solution:**
Test I: We have blocks (AC) and (DB). Order could be ACDBE, EDBAC, etc. Not sufficient.
Test II: We have block (CE), and E is above D. Order could be CE ... D ... Not sufficient.
Test I + II: From I, we have (AC) and (DB). From II, we have (CE), so combining with (AC) yields (ACE). II also says E is above D, and since we have block (DB), the full sequence from top to bottom must be A, C, E, D, B. The box at the bottom is B. Both together are sufficient.

**Answer:** (c)

**Q15.** What is the rank of Rahul from the top in a class of $40$ students?

I. Rahul is $4$ ranks below Sachin, who is $15^{\text{th}}$ from the bottom.
II. Rahul is exactly in the middle of Amit, who is $10^{\text{th}}$ from the top, and Sumit, who is $20^{\text{th}}$ from the top.
(a) I alone (b) II alone (c) Both together (d) Either alone (e) Insufficient

**Solution:**
Test I: Total is $40$. Sachin is $15^{\text{th}}$ from bottom, so Sachin is $(40 - 15 + 1) = 26^{\text{th}}$ from the top. Rahul is $4$ ranks below Sachin, so Rahul is $26 + 4 = 30^{\text{th}}$ from the top. Sufficient alone.
Test II: Amit is $10^{\text{th}}$, Sumit is $20^{\text{th}}$ from the top. Rahul is exactly in the middle. Their average rank is $(10 + 20) / 2 = 15^{\text{th}}$. Rahul's rank is uniquely found. Sufficient alone.

**Answer:** (d)

::: trap
When testing statements, test I completely separately from II. If I gives an answer, do NOT stop. Test II separately. If II also gives an answer independently, the correct choice is (d) "each alone is sufficient", not (c).
:::

**Q16.** On which day of the week did John visit the museum?

I. John's sister remembers that he visited after Tuesday but before Saturday.
II. John's friend remembers that he visited after Thursday but before Sunday.
(a) I alone (b) II alone (c) Both together (d) Either alone (e) Insufficient

**Solution:**
Test I: After Tuesday, before Saturday $\implies$ Wed, Thu, or Fri. Not sufficient.
Test II: After Thursday, before Sunday $\implies$ Fri or Sat. Not sufficient.
Test I + II: The intersection of {Wed, Thu, Fri} and {Fri, Sat} is exactly {Friday}. A unique day is found.

**Answer:** (c)

## Wrapped OA variant

**Q17.** An e-commerce platform ranks products based on their conversion rate. Product X is currently ranked $112^{\text{th}}$ from the top and $428^{\text{th}}$ from the bottom in the "Electronics" category. A batch of $35$ new products is added to the category. If all new products achieve a higher conversion rate than Product X, what will be Product X's new rank from the bottom?
(a) $427^{\text{th}}$ (b) $428^{\text{th}}$ (c) $462^{\text{th}}$ (d) $463^{\text{th}}$

**Solution:**
Product X's initial rank from the bottom is $428^{\text{th}}$.
Adding $35$ products *above* Product X shifts X's rank down from the top (it becomes $112 + 35 = 147^{\text{th}}$ from the top).
However, the number of products performing *worse* than X remains completely unchanged.
Therefore, X's rank from the bottom remains exactly the same.

**Answer:** $428^{\text{th}}$ (b)

**Q18.** The algorithm needs to classify a customer as "High Value". A customer is "High Value" if their lifetime spending exceeds \$5000. Is customer C "High Value"?

I. Customer C has made $15$ purchases, and the average value of their first $10$ purchases is \$350.
II. The average value of customer C's last $5$ purchases is \$250.
(a) I alone (b) II alone (c) Both together (d) Either alone (e) Insufficient

**Solution:**
Test I: Total for first $10$ purchases is $10 \times 350 = \$3500$. We know nothing about the remaining $5$. Not sufficient.
Test II: Total for last $5$ purchases is $5 \times 250 = \$1250$. We know nothing about earlier purchases. Not sufficient.
Test I + II: Total lifetime spending is $3500 + 1250 = \$4750$.
The total is $\$4750$, which does NOT exceed $\$5000$.
With both statements, we can definitively answer "NO" to the question "Is customer C High Value?".
A definitive "NO" means the data IS sufficient to answer the yes/no question.

**Answer:** (c)

::: interview
In Yes/No Data Sufficiency questions, a definitive "NO" is a completely sufficient answer. You do not need the data to yield a "YES" to select (c). You just need it to yield a single, unambiguous truth value.
:::

## Sources

- IndiaBix — https://www.indiabix.com/
- Hitbullseye — https://www.hitbullseye.com/
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- PrepInsta — https://prepinsta.com/
