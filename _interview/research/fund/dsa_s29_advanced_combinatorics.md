# Advanced Combinatorics

::: definition
**Advanced Counting Formulas**

- **Stars & Bars:** The number of ways to distribute $n$ identical objects into $k$ distinct bins is $\binom{n+k-1}{k-1}$. If each bin must contain at least one object, it is $\binom{n-1}{k-1}$.
- **Inclusion–Exclusion (PIE):** $|A \cup B \cup \ldots| = \sum |A_{i}| - \sum |A_{i} \cap A_{j}| + \sum |A_{i} \cap A_{j} \cap A_{k}| - \dots$
- **Hockey-Stick Identity:** $\sum_{i=k}^{n} \binom{i}{k} = \binom{n+1}{k+1}$.
- **Catalan Numbers:** $C_{n} = \frac{1}{n+1} \binom{2n}{n}$. They count balanced parentheses, triangulations, valid stack sequences, and non-crossing lattice paths.
- **Derangements:** The number of permutations of $n$ elements with no fixed points is $D_{n} = n! \sum_{k=0}^{n} \frac{(-1)^{k}}{k!}$. For large $n$, $D_{n} \approx \frac{n!}{e}$.

:::

## Stars & bars / distributions

**Q1.** How many ways can you distribute $10$ identical candies to $4$ children?

**Solution:** This is the standard non-negative integer solution to $x_{1} + x_{2} + x_{3} + x_{4} = 10$. Using stars and bars with $n=10$, $k=4$: $\binom{10+4-1}{4-1} = \binom{13}{3} = \frac{13 \times 12 \times 11}{3 \times 2 \times 1} = 286$.

**Answer:** $286$

::: trap
A common mistake is using $k$ instead of $k-1$ for the bars. Always remember: to divide items into $k$ groups, you only need $k-1$ partitions.

:::

**Q2.** How many ways can you distribute $15$ identical apples to $5$ distinct people such that each person receives at least one apple?

**Solution:** Positive integer solutions to $x_{1} + x_{2} + x_{3} + x_{4} + x_{5} = 15$. Pre-allocate $1$ apple to each person. We now have $10$ apples left to distribute among $5$ people with no restrictions. By stars and bars, $\binom{10+5-1}{5-1} = \binom{14}{4} = \frac{14 \times 13 \times 12 \times 11}{24} = 1001$.

**Answer:** $1001$

**Q3.** An investor wants to allocate $100$ identical units of capital into $3$ distinct asset classes. They want at least $10$ units in Class A, at least $20$ in Class B, and at least $15$ in Class C. How many valid allocations exist?

**Solution:** $A \ge 10$, $B \ge 20$, $C \ge 15$ with $A+B+C=100$. Give the minimums first: $10+20+15 = 45$ units allocated. The remaining $100 - 45 = 55$ units can be distributed freely among the $3$ classes. Using stars and bars: $\binom{55+3-1}{3-1} = \binom{57}{2} = \frac{57 \times 56}{2} = 1596$.

**Answer:** $1596$

**Q4.** How many non-negative integer solutions are there to the equation $x_{1} + x_{2} + x_{3} = 10$ such that $x_{1} \le 4$?

**Solution:** Count the total ways without the upper bound constraint, then subtract the cases where the constraint is violated ($x_{1} \ge 5$).
Total unrestricted ways: $\binom{10+3-1}{3-1} = \binom{12}{2} = 66$.
Ways where $x_{1} \ge 5$: Pre-allocate $5$ to $x_{1}$, leaving $5$ to distribute among the $3$ variables. The number of ways is $\binom{5+3-1}{3-1} = \binom{7}{2} = 21$.
Valid solutions: $66 - 21 = 45$.

**Answer:** $45$

**Q5.** A hash function maps $6$ distinct requests to $3$ servers. How many ways can the requests be routed such that each server receives exactly $2$ requests?

**Solution:** This is not stars and bars because the items (requests) are *distinct*. We use the multinomial coefficient (or combinations): choose $2$ for the first server, $2$ for the second, and $2$ for the third. $\binom{6}{2} \times \binom{4}{2} \times \binom{2}{2} = 15 \times 6 \times 1 = 90$.

**Answer:** $90$

::: trap
Do not divide by $3!$ here because the servers are *distinct* entities. You only divide by $k!$ when forming $k$ identical or unlabeled groups.

:::

## Inclusion–exclusion

**Q6.** How many integers from $1$ to $100$ are not divisible by $2$, $3$, or $5$?

**Solution:** Use inclusion-exclusion. Total numbers = $100$.
Divisible by $2$: $\lfloor 100/2 \rfloor = 50$. Divisible by $3$: $33$. Divisible by $5$: $20$.
Divisible by $2 \cap 3$ ($6$): $16$. By $2 \cap 5$ ($10$): $10$. By $3 \cap 5$ ($15$): $6$.
Divisible by $2 \cap 3 \cap 5$ ($30$): $3$.
$|A \cup B \cup C| = 50 + 33 + 20 - (16 + 10 + 6) + 3 = 103 - 32 + 3 = 74$.
Numbers NOT divisible: $100 - 74 = 26$.

**Answer:** $26$

**Q7.** How many surjective (onto) functions are there from a set of $4$ distinct elements to a set of $3$ distinct elements?

**Solution:** Total functions is $3^{4} = 81$. We subtract the cases where the image misses at least one element in the codomain using PIE.
Miss at least one element: $\binom{3}{1} \times 2^{4} = 3 \times 16 = 48$.
Miss at least two elements (i.e., all map to $1$ element): $\binom{3}{2} \times 1^{4} = 3 \times 1 = 3$.
Miss at least three elements: $0$.
By PIE, the number of non-surjective functions is $48 - 3 = 45$.
Surjective functions = Total - Non-surjective = $81 - 45 = 36$.

**Answer:** $36$

**Q8.** You are making a $5$-letter password using only uppercase letters. The password must contain at least one 'A', at least one 'B', and at least one 'C'. How many such passwords exist?

**Solution:** Total $5$-letter passwords: $26^{5}$. Let $N(A)$ be passwords missing 'A', etc. We want the complement of $N(A) \cup N(B) \cup N(C)$.
$|N(A)| = 25^{5}$. There are $3$ such sets.
$|N(A) \cap N(B)| = 24^{5}$. There are $3$ such pairs.
$|N(A) \cap N(B) \cap N(C)| = 23^{5}$.
By PIE, missing at least one of them is $3 \times 25^{5} - 3 \times 24^{5} + 23^{5} = 29296875 - 23887872 + 6436343 = 11845346$.
Total with all three: $26^{5} - 11845346 = 11881376 - 11845346 = 36030$.

**Answer:** $36030$

## Binomial identities & combinatorial sums

**Q9.** Evaluate the sum $\binom{5}{5} + \binom{6}{5} + \binom{7}{5} + \dots + \binom{12}{5}$.

**Solution:** This is a direct application of the hockey-stick identity: $\sum_{i=k}^{n} \binom{i}{k} = \binom{n+1}{k+1}$.
Here $k=5$ and $n=12$. The sum evaluates to $\binom{12+1}{5+1} = \binom{13}{6} = 1716$.

**Answer:** $1716$

::: keypoint
The hockey-stick identity $\sum_{i=k}^{n} \binom{i}{k} = \binom{n+1}{k+1}$ always starts with $\binom{k}{k}$. If the sum starts at a higher index, calculate the full sum and subtract the missing terms.

:::

**Q10.** What is the value of $\sum_{k=0}^{10} \binom{10}{k}^{2}$?

**Solution:** The sum of the squares of a row of Pascal's triangle is given by Vandermonde's identity: $\sum_{k=0}^{n} \binom{n}{k}^{2} = \binom{2n}{n}$.
For $n=10$, this is $\binom{20}{10} = 184756$.
*(Intuition: Choosing $10$ items from a pool of $20$, consisting of $10$ men and $10$ women, is equivalent to choosing $k$ men and $10-k$ women over all possible $k$.)*

**Answer:** $184756$

**Q11.** A committee of $k$ members is to be chosen from a group of $100$ people, and one of the committee members must be designated as the chair. The committee size $k$ can be anything from $1$ to $100$. How many ways can this be done?

**Solution:** We are evaluating $\sum_{k=1}^{100} k \binom{100}{k}$. Count this by choosing the chair first!
There are $100$ ways to choose the chair.
For each of the remaining $99$ people, they can either be in the committee or not ($2$ choices each). Thus, there are $2^{99}$ ways to form the rest of the committee.
Total ways = $100 \times 2^{99}$.

**Answer:** $100 \times 2^{99}$

## Catalan-flavoured counting

**Q12.** A robot on a $5 \times 5$ grid starts at $(0,0)$ and wants to reach $(5,5)$ by moving only Right or Up. It must never go above the diagonal $y = x$. How many valid paths exist?

**Solution:** Paths on an $n \times n$ grid that do not cross the diagonal are counted by the $n$-th Catalan number, $C_{n} = \frac{1}{n+1}\binom{2n}{n}$.
Here, $n=5$. $C_{5} = \frac{1}{6} \binom{10}{5} = \frac{252}{6} = 42$.

**Answer:** $42$

**Q13.** How many strings of $4$ left parentheses `(` and $4$ right parentheses `)` are perfectly balanced?

**Solution:** Balanced parenthesis configurations of length $2n$ are exactly the $n$-th Catalan number $C_{n}$.
For $n=4$, $C_{4} = \frac{1}{5} \binom{8}{4} = \frac{70}{5} = 14$.

**Answer:** $14$

::: interview
Catalan numbers frequently appear in coding OAs. Any problem asking for "valid stack sequences", "number of structurally unique BSTs with $n$ nodes", or "balanced bracket combinations" is a thinly veiled $C_{n}$ calculation.

:::

**Q14.** Six people are seated around a circular table. In how many ways can they all shake hands simultaneously across the table such that no arms cross?

**Solution:** This is equivalent to non-crossing partitions or triangulations of a polygon, which is counted by Catalan numbers.
Since there are $6$ people, we are connecting $n=3$ pairs.
The number of ways is $C_{3} = \frac{1}{4} \binom{6}{3} = \frac{20}{4} = 5$.

**Answer:** $5$

## Derangements & matching

**Q15.** Four friends check their coats at a restaurant. If the coats are returned randomly, in how many ways will exactly NONE of them get their own coat back?

**Solution:** This is the classic derangement problem for $n=4$.
$D_{n} = n! \sum_{k=0}^{n} \frac{(-1)^{k}}{k!}$.
$D_{4} = 24(1 - 1 + \frac{1}{2} - \frac{1}{6} + \frac{1}{24}) = 24(\frac{12 - 4 + 1}{24}) = 9$.

**Answer:** $9$

**Q16.** A company runs a Secret Santa for $5$ employees. What is the probability that no one draws their own name?

(a) $9/120$
(b) $44/120$
(c) $53/120$
(d) $60/120$

**Solution:** We need $D_{5}$ divided by the total permutations $5! = 120$.
$D_{5} = 5 \times D_{4} + (-1)^{5} = 5 \times 9 - 1 = 44$.
The probability is $44 / 120$.

**Answer:** $44/120$ (b)

::: keypoint
A handy recursive formula for derangements is $D_{n} = n D_{n-1} + (-1)^{n}$.
Memorize the first few values: $D_{1}=0$, $D_{2}=1$, $D_{3}=2$, $D_{4}=9$, $D_{5}=44$, $D_{6}=265$.

:::

**Q17.** A deck of $52$ cards is shuffled and dealt one by one. A second sorted deck of $52$ cards is dealt alongside it. You win if no two identical cards are dealt at the same position. What is the approximate probability of winning?

**Solution:** The probability of exactly zero matches in a random permutation of length $n$ is $D_{n} / n!$.
For large $n$, the Taylor series for $e^{-1} = 1 - 1 + \frac{1}{2!} - \frac{1}{3!} + \dots$ perfectly matches the derangement sum. Thus, as $n \to \infty$, the probability quickly approaches $1/e$. For $n=52$, the approximation is practically exact.
$1/e \approx 0.3678$.

**Answer:** $1/e$

**Q18.** There are $6$ distinct letters and $6$ distinct envelopes addressed to the respective recipients. In how many ways can you place the letters into the envelopes such that exactly $2$ letters go into their correct envelopes?

**Solution:** First, choose the $2$ letters that go into the correct envelopes: $\binom{6}{2} = 15$ ways.
The remaining $4$ letters must go into the wrong envelopes. This is a derangement of $4$ items. $D_{4} = 9$.
Total ways = $15 \times 9 = 135$.

**Answer:** $135$

## Pigeonhole & existence

::: heavy
The pigeonhole principle in quant interviews usually disguises the "holes". Look for remainders modulo $n$, odd parts, or fractional components to use as your bins.

:::

**Q19.** Given $51$ distinct integers chosen from the set $\{1, 2, \dots, 100\}$, prove that at least one of them must divide another. If the numbers are randomly chosen, what is a simple counter-example showing this fails for $50$ integers?

**Solution:** **Proof:** Every integer $x$ can be written as $x = 2^{k} \cdot m$, where $m$ is an odd number. Since our numbers are from $1$ to $100$, the odd part $m$ must be an odd integer between $1$ and $99$. There are exactly $50$ such odd numbers.
By the pigeonhole principle, if we pick $51$ numbers, at least two of them must share the same odd part $m$. Let these two numbers be $a = 2^{i} \cdot m$ and $b = 2^{j} \cdot m$. If $i < j$, then $a$ divides $b$; otherwise $b$ divides $a$.

**Counter-example for 50:** Choose the upper half of the set: $\{51, 52, \dots, 100\}$. There are $50$ numbers, and no number divides another because the smallest number ($51$) doubled is $102$, which exceeds the maximum bounds of the set.

**Answer:** The odd-part pigeonhole. Counter-example: $\{51, 52, \dots, 100\}$.

**Q20.** A programmer works for $30$ days. They must push code at least once a day, but to avoid burnout, they will push code at most $45$ times total over the $30$ days. Show that there must exist a period of consecutive days where they push code exactly $14$ times.

**Solution:** Let $a_{i}$ be the cumulative total of pushes from day $1$ to day $i$.
Since they push at least once a day, the sequence $a_{1}, a_{2}, \dots, a_{30}$ is strictly increasing, and $1 \le a_{1} < a_{2} < \dots < a_{30} \le 45$.
Consider the sequence $a_{1} + 14, a_{2} + 14, \dots, a_{30} + 14$. This is also strictly increasing, bounded by $15 \le a_{1} + 14 < \dots < a_{30} + 14 \le 59$.
We have $60$ numbers in total ($30$ from the first sequence, $30$ from the second sequence), and all $60$ must fall into the range from $1$ to $59$.
By the pigeonhole principle, at least two of these $60$ numbers must be equal. Since the numbers within each sequence are strictly increasing, the match must cross over: $a_{j} = a_{i} + 14$.
This means $a_{j} - a_{i} = 14$. The sum of pushes from day $i+1$ to day $j$ is exactly $14$.

**Answer:** Proven by pigeonholing cumulative sums $\{a_{i}\}$ and $\{a_{i}+14\}$ into $59$ slots.

**Q21.** Inside a unit square (side length $1$), $5$ points are placed arbitrarily. Which of the following is guaranteed to be an upper bound on the distance between the closest pair of points?

(a) $\sqrt{2}/2$
(b) $1/2$
(c) $\sqrt{3}/2$
(d) $1$

**Solution:** Divide the unit square into $4$ smaller squares of side length $1/2$. By the pigeonhole principle, since there are $5$ points and $4$ small squares, at least one small square must contain at least $2$ points.
The maximum possible distance between two points inside a $1/2 \times 1/2$ square is its diagonal, which is $\sqrt{(1/2)^{2} + (1/2)^{2}} = \sqrt{1/4 + 1/4} = \sqrt{1/2} = \sqrt{2}/2$. Thus, the closest pair is at most $\sqrt{2}/2$ apart.

**Answer:** $\sqrt{2}/2$ (a)

## Sources

- Brainstellar — https://brainstellar.com/ (probability and derangements)
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/ (combinations and PIE)
- QuantQuestions — https://www.quantquestions.com/ (pigeonhole and existence proofs)
- "Fifty Challenging Problems in Probability" (Mosteller) — derangements limit and matching
