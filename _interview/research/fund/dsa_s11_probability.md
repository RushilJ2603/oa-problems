# Probability (Foundations)

::: definition
**Core Formula:** $P(E) = \frac{\text{favourable outcomes}}{\text{total outcomes}}$. All probabilities bounded by $0 \le P(E) \le 1$.
**Complement:** $P(E') = 1 - P(E)$ (the probability of an event *not* happening).
**Addition Rule:** $P(A \cup B) = P(A) + P(B) - P(A \cap B)$.
**Independence:** $P(A \cap B) = P(A)P(B)$ (happens when $A$ and $B$ do not affect each other).
**Conditional:** $P(A \mid B) = \frac{P(A \cap B)}{P(B)}$ (probability of $A$ given that $B$ has occurred).
:::

## 1. Basic Probability (Coins, Dice, Cards, Single Draws)

**Q1. Two fair coins are tossed simultaneously. What is the probability of getting at least one head?**
(a) $1/4$ (b) $1/2$ (c) $3/4$ (d) $1$

**Solution:** Sample space is $\{HH, HT, TH, TT\}$. Total outcomes = $4$.
Favourable outcomes for "at least one head" are $\{HH, HT, TH\}$. Count is $3$.
$P(\text{at least one head}) = \frac{3}{4}$.

**Answer:** $3/4$ (c)

**Q2. Three fair coins are tossed. What is the probability of getting exactly two tails?**
(a) $1/8$ (b) $3/8$ (c) $1/2$ (d) $5/8$

**Solution:** Total outcomes for $3$ coins is $2^{3} = 8$.
Favourable outcomes (exactly two tails) are $\{HTT, THT, TTH\}$. Count is $3$.
$P(\text{exactly two tails}) = \frac{3}{8}$.

**Answer:** $3/8$ (b)

**Q3. A single fair die is rolled. What is the probability that the number rolled is a prime number?**
(a) $1/6$ (b) $1/3$ (c) $1/2$ (d) $2/3$

**Solution:** Sample space is $\{1, 2, 3, 4, 5, 6\}$.
Prime numbers in this set are $\{2, 3, 5\}$. Count is $3$. (Note: $1$ is not prime).
$P(\text{prime}) = \frac{3}{6} = \frac{1}{2}$.

**Answer:** $1/2$ (c)

**Q4. Two fair dice are rolled simultaneously. What is the probability that the sum of the numbers appearing on top is exactly $8$?**
(a) $1/9$ (b) $5/36$ (c) $1/6$ (d) $7/36$

**Solution:** Total outcomes for two dice is $6 \times 6 = 36$.
Favourable sums of $8$: $(2,6), (3,5), (4,4), (5,3), (6,2)$. Count is $5$.
$P(\text{sum is } 8) = \frac{5}{36}$.

::: keypoint
**Dice Sum Shortcut:** The number of ways to get a sum $S$ on two dice is:
For $S \le 7$: ways = $S - 1$.
For $S \ge 8$: ways = $13 - S$.
Example: ways to get $8$ is $13 - 8 = 5$.
:::

**Answer:** $5/36$ (b)

**Q5. Two fair dice are rolled. What is the probability that the product of the numbers rolled is an even number?**
(a) $1/4$ (b) $1/2$ (c) $3/4$ (d) $5/8$

**Solution:** Use the complement. The product is odd *only* if both numbers are odd.
$P(\text{odd die}) = \frac{3}{6} = \frac{1}{2}$.
$P(\text{both odd}) = \frac{1}{2} \times \frac{1}{2} = \frac{1}{4}$.
$P(\text{product is even}) = 1 - P(\text{both odd}) = 1 - \frac{1}{4} = \frac{3}{4}$.

**Answer:** $3/4$ (c)

**Q6. A card is drawn at random from a standard deck of $52$ cards. What is the probability that it is a red face card?**
(a) $1/26$ (b) $3/26$ (c) $1/13$ (d) $3/52$

**Solution:** A standard deck has $52$ cards. Face cards are Jacks, Queens, and Kings ($3$ per suit).
There are two red suits (Hearts and Diamonds).
Number of red face cards = $3 \times 2 = 6$.
$P(\text{red face card}) = \frac{6}{52} = \frac{3}{26}$.

**Answer:** $3/26$ (b)

**Q7. A number is chosen at random from $1$ to $50$. What is the probability that it is a multiple of $7$?**
(a) $7/50$ (b) $1/7$ (c) $3/25$ (d) $4/25$

**Solution:** The multiples of $7$ between $1$ and $50$ are $\{7, 14, 21, 28, 35, 42, 49\}$. Count is $7$.
Total outcomes = $50$.
$P(\text{multiple of } 7) = \frac{7}{50}$.

**Answer:** $7/50$ (a)

## 2. Combinatorial Probability (Multiple Draws & Arrangements)

**Q8. A bag contains $4$ red balls and $5$ green balls. If $3$ balls are drawn at random without replacement, what is the probability that all $3$ are green?**
(a) $5/42$ (b) $1/14$ (c) $5/21$ (d) $10/63$

**Solution:** Total balls = $9$. We need to choose $3$ from $9$, which is $^{9}C_{3}$.
We want to choose $3$ green balls from the $5$ available, which is $^{5}C_{3}$.
$P(\text{all green}) = \frac{^{5}C_{3}}{^{9}C_{3}} = \frac{10}{(9 \times 8 \times 7) / (3 \times 2 \times 1)} = \frac{10}{84} = \frac{5}{42}$.
Alternatively, using successive probabilities: $\frac{5}{9} \times \frac{4}{8} \times \frac{3}{7} = \frac{60}{504} = \frac{5}{42}$.

**Answer:** $5/42$ (a)

::: trap
**With vs. Without Replacement:** "Drawn at random" implies *without* replacement unless stated otherwise. If the problem explicitly says *with* replacement, use independent probabilities ($\frac{5}{9} \times \frac{5}{9} \times \frac{5}{9}$) instead of combinations.
:::

**Q9. A committee of $3$ members is to be formed from a group of $5$ men and $4$ women. What is the probability that the committee contains exactly $2$ men and $1$ woman?**
(a) $10/21$ (b) $11/21$ (c) $5/14$ (d) $20/43$

**Solution:** Total people = $9$. We select $3$, so total ways = $^{9}C_{3} = 84$.
Ways to select $2$ men from $5$ = $^{5}C_{2} = 10$.
Ways to select $1$ woman from $4$ = $^{4}C_{1} = 4$.
Favourable ways = $10 \times 4 = 40$.
$P(\text{2 men, 1 woman}) = \frac{40}{84} = \frac{10}{21}$.

**Answer:** $10/21$ (a)

**Q10. The letters of the word "RANDOM" are arranged in all possible ways. What is the probability that the two vowels (A, O) are always together?**
(a) $1/6$ (b) $1/3$ (c) $1/2$ (d) $2/3$

**Solution:** The word "RANDOM" has $6$ distinct letters. Total arrangements = $6! = 720$.
To keep the vowels A and O together, treat (AO) as a single block. We now have $5$ entities: R, N, D, M, and (AO).
These $5$ entities can be arranged in $5!$ ways. The vowels inside the block can be arranged in $2!$ ways.
Favourable arrangements = $5! \times 2! = 120 \times 2 = 240$.
$P(\text{vowels together}) = \frac{240}{720} = \frac{1}{3}$.

**Answer:** $1/3$ (b)

## 3. Addition Rule & Complement

**Q11. In a group of students, the probability that a student passes Math is $0.6$, the probability of passing Physics is $0.5$, and the probability of passing both is $0.3$. What is the probability that a student passes at least one of the two subjects?**
(a) $0.7$ (b) $0.8$ (c) $0.9$ (d) $1.1$

**Solution:** Use the addition rule: $P(M \cup P) = P(M) + P(P) - P(M \cap P)$.
$P(M \cup P) = 0.6 + 0.5 - 0.3 = 0.8$.

**Answer:** $0.8$ (b)

**Q12. Two dice are tossed. What is the probability that the sum of the numbers is either a multiple of $3$ or a multiple of $4$?**
(a) $5/9$ (b) $17/36$ (c) $1/2$ (d) $19/36$

**Solution:** Total outcomes = $36$. Let $A$ be sum is multiple of $3$, $B$ be sum is multiple of $4$.
Sums for $A$: $3, 6, 9, 12$. Using the shortcut ($S-1$ and $13-S$):
Ways for sum $3$ (2), $6$ (5), $9$ (4), $12$ (1). Total $P(A) = 12/36$.
Sums for $B$: $4, 8, 12$.
Ways for sum $4$ (3), $8$ (5), $12$ (1). Total $P(B) = 9/36$.
Intersection $A \cap B$: Sum is a multiple of both $3$ and $4$, which is $12$.
$P(A \cap B) = \text{ways to get } 12 = 1/36$.
$P(A \cup B) = \frac{12}{36} + \frac{9}{36} - \frac{1}{36} = \frac{20}{36} = \frac{5}{9}$.

**Answer:** $5/9$ (a)

**Q13. Three archers A, B, and C have probabilities of hitting a target of $1/2$, $1/3$, and $1/4$ respectively. If they all shoot simultaneously, what is the probability that the target is hit by at least one of them?**
(a) $1/24$ (b) $3/4$ (c) $1/4$ (d) $11/24$

**Solution:** "At least one" problems are almost always solved fastest using the complement: $1 - P(\text{none hit})$.
$P(\text{A misses}) = 1 - 1/2 = 1/2$.
$P(\text{B misses}) = 1 - 1/3 = 2/3$.
$P(\text{C misses}) = 1 - 1/4 = 3/4$.
$P(\text{none hit}) = \frac{1}{2} \times \frac{2}{3} \times \frac{3}{4} = \frac{6}{24} = \frac{1}{4}$.
$P(\text{at least one hit}) = 1 - \frac{1}{4} = \frac{3}{4}$.

::: keypoint
**The "At Least One" Trick:** Whenever a question asks for the probability of "at least one" success across independent trials, instantly calculate $1 - P(\text{all fail})$. This bypasses summing multiple complex scenarios.
:::

**Answer:** $3/4$ (b)

## 4. Independence & Simple Conditional

**Q14. A bag contains $5$ white and $7$ black balls. Two balls are drawn successively with replacement. What is the probability that both balls are white?**
(a) $25/144$ (b) $5/33$ (c) $5/12$ (d) $10/144$

**Solution:** With replacement, the draws are independent.
$P(\text{first is white}) = \frac{5}{12}$.
$P(\text{second is white}) = \frac{5}{12}$.
$P(\text{both white}) = \frac{5}{12} \times \frac{5}{12} = \frac{25}{144}$.

**Answer:** $25/144$ (a)

**Q15. From a standard deck of cards, two cards are drawn one after the other without replacement. What is the probability that the first card is a Heart and the second card is a Spade?**
(a) $13/204$ (b) $169/2704$ (c) $13/102$ (d) $1/16$

**Solution:** $P(\text{Heart on first draw}) = \frac{13}{52} = \frac{1}{4}$.
Since the first card is not replaced, $51$ cards remain, including all $13$ Spades.
$P(\text{Spade on second} \mid \text{Heart on first}) = \frac{13}{51}$.
Total probability = $\frac{1}{4} \times \frac{13}{51} = \frac{13}{204}$.

**Answer:** $13/204$ (a)

**Q16. Two fair dice are rolled. Given that the sum of the numbers is $8$, what is the probability that the first die shows a $3$?**
(a) $1/6$ (b) $1/5$ (c) $5/36$ (d) $1/4$

**Solution:** This is simple conditional probability $P(A \mid B) = \frac{P(A \cap B)}{P(B)}$.
Condition $B$: The sum is $8$. The reduced sample space is $\{(2,6), (3,5), (4,4), (5,3), (6,2)\}$. Total = $5$ outcomes.
Event $A$: The first die is $3$. Looking at our reduced sample space, this only happens in $(3,5)$. Count = $1$.
$P(\text{first is } 3 \mid \text{sum is } 8) = \frac{1}{5}$.

**Answer:** $1/5$ (b)

**Q17. A family has two children. Given that at least one of the children is a boy, what is the probability that both children are boys? (Assume boy and girl are equally likely).**
(a) $1/2$ (b) $1/3$ (c) $1/4$ (d) $2/3$

**Solution:** The full sample space for two children is $\{BB, BG, GB, GG\}$.
Condition: At least one is a boy. This eliminates $GG$. The reduced sample space is $\{BB, BG, GB\}$. Total = $3$.
We want both to be boys: The only favourable outcome is $BB$.
$P(\text{both boys} \mid \text{at least one boy}) = \frac{1}{3}$.

**Answer:** $1/3$ (b)

## 5. Wrapped OA Variants

**Q18. A quality assurance engineer at Amazon is testing a batch of $20$ servers, $4$ of which have faulty power supplies. The engineer randomly selects $3$ servers for a deep diagnostic check. What is the probability that exactly $1$ of the selected servers is faulty?**
(a) $16/95$ (b) $24/95$ (c) $8/19$ (d) $48/95$

**Solution:** This is a disguised combinatorial problem.
Total servers = $20$, Faulty = $4$, Good = $16$. We choose $3$.
Ways to choose $1$ faulty and $2$ good = $^{4}C_{1} \times ^{16}C_{2} = 4 \times \frac{16 \times 15}{2} = 4 \times 120 = 480$.
Total ways to choose $3$ servers = $^{20}C_{3} = \frac{20 \times 19 \times 18}{3 \times 2} = 1140$.
$P(\text{exactly one faulty}) = \frac{480}{1140} = \frac{48}{114} = \frac{8}{19}$.

::: interview
**The hypergeometric distribution:** Interviewers often dress up basic combination problems in QA, testing, or selection scenarios. Recognizing this as "choose $k$ from group A, choose $n-k$ from group B" allows you to skip straight to combinations without worrying about draw order.
:::

**Answer:** $8/19$ (c)

**Q19. An algorithmic trading firm executes a sequence of trades. Each trade has a $20\%$ chance of hitting the profit target, independent of others. What is the minimum number of trades the system must execute to ensure that the probability of hitting at least one profit target is greater than $90\%$?**
(a) $9$ (b) $10$ (c) $11$ (d) $12$

**Solution:** Let $n$ be the number of trades. $P(\text{success}) = 0.2$. $P(\text{fail}) = 0.8$.
$P(\text{at least one success}) = 1 - P(\text{all fail}) = 1 - (0.8)^{n}$.
We need: $1 - (0.8)^{n} > 0.90$, which simplifies to $(0.8)^{n} < 0.10$.
Calculate powers of $0.8$ (or $4/5$):
$(0.8)^{2} = 0.64$
$(0.8)^{3} = 0.512$
By testing values:
$(0.8)^{10} \approx 0.107$.
$(0.8)^{11} \approx 0.0859$.
Since $(0.8)^{11} < 0.10$, a minimum of $11$ trades is required.

**Answer:** $11$ (c)

::: heavy
**Derangements (Matching Problems)**
A classic quant interview pattern asks for the probability that *none* of $n$ items end up in their correct positions (e.g., hats on heads, letters in envelopes). The number of completely incorrect arrangements (derangements) for $n$ items is $!n \approx \frac{n!}{e}$.
For small $n$: $!1 = 0$, $!2 = 1$, $!3 = 2$, $!4 = 9$, $!5 = 44$.
:::

**Q20. An absent-minded secretary seals $4$ different letters into $4$ different pre-addressed envelopes at random. What is the probability that no letter goes into its correct envelope?**
(a) $1/4$ (b) $3/8$ (c) $1/3$ (d) $9/24$

**Solution:** Total number of ways to distribute $4$ letters into $4$ envelopes is $4! = 24$.
We need the number of ways where *none* match (a derangement of $4$ items).
Using the derangement sequence: $!4 = 9$.
(To derive manually: total $24$ $-$ ($1$ way all match) $-$ ($6$ ways exactly two match) $-$ ($8$ ways exactly one matches) = $9$).
$P(\text{no match}) = \frac{9}{24} = \frac{3}{8}$.

**Answer:** $3/8$ (b)

## Sources

- IndiaBix — https://www.indiabix.com/aptitude/probability/
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- QuantQuestions — https://www.quantquestions.com/
- Hitbullseye — https://www.hitbullseye.com/Probability-Questions.php
