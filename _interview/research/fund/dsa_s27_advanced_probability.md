# Advanced Probability

::: definition
**Core Probability Rules**

- **Conditional Probability & Bayes' Theorem:** $P(A\mid B) = \frac{P(A \cap B)}{P(B)} = \frac{P(B\mid A)P(A)}{P(B)}$
- **Law of Total Probability:** $P(A) = \sum_{i} P(A\mid B_{i})P(B_{i})$ for any partition $B_{i}$ of the sample space.
- **Independence:** $A$ and $B$ are independent if $P(A \cap B) = P(A)P(B)$.
- **Complement Rule:** $P(A) = 1 - P(A^{c})$. Always consider $1 - P(\text{none})$ for "at least one" problems.
:::

::: interview
In quant and top-tier product interviews, getting the right number is only half the battle. Interviewers are testing your ability to simplify the problem mathematically. When you spot a symmetry trick, say it out loud. Never grind through an infinite series without first checking if a recursive state or symmetry argument solves it in one line.
:::

## 1. Conditional Probability & Bayes

**Q1. The Base-Rate Disease Paradox.** A certain disease affects $1$ in $10000$ people. A test for the disease is $99\%$ accurate (i.e., it correctly identifies $99\%$ of people with the disease, and correctly identifies $99\%$ of people without the disease). If you test positive, what is the probability you actually have the disease?

**Solution:** Use Bayes' Theorem. Let $D$ be having the disease, $T^{+}$ be a positive test. We want $P(D\mid T^{+})$.
$P(D) = 0.0001$, $P(D^{c}) = 0.9999$.
$P(T^{+}\mid D) = 0.99$, $P(T^{+}\mid D^{c}) = 0.01$.
$P(T^{+}) = P(T^{+}\mid D)P(D) + P(T^{+}\mid D^{c})P(D^{c}) = (0.99)(0.0001) + (0.01)(0.9999) = 0.000099 + 0.009999 = 0.010098$.
$P(D\mid T^{+}) = \frac{0.000099}{0.010098} \approx 0.0098$.

**Answer:** $\approx 1\%$

::: trap
**Base-rate neglect:** Most candidates intuitively guess $99\%$. Because the disease is incredibly rare ($1$ in $10000$), the sheer volume of false positives ($1\%$ of $9999$) completely overwhelms the true positives ($99\%$ of $1$).
:::

**Q2. Two Children, One Boy.** A family has two children. You are told that at least one of them is a boy. What is the probability that both children are boys? Assume boy and girl births are equally likely.

**Solution:** The sample space for two children is $\{BB, BG, GB, GG\}$, each with probability $\frac{1}{4}$.
The given information "at least one is a boy" eliminates the $GG$ outcome, leaving the sample space $\{BB, BG, GB\}$.
Since each of these 3 remaining outcomes is equally likely, the probability of $BB$ is $\frac{1}{3}$.

**Answer:** $\frac{1}{3}$

**Q3. Two Children, Tuesday Boy.** A family has two children. You are told that at least one of them is a boy born on a Tuesday. What is the probability that both children are boys?

**Solution:** There are $14$ possible combinations of gender and day of the week for a child. For two children, there are $14 \times 14 = 196$ total equally likely pairs.
Let $A$ be the event "at least one child is a Tuesday Boy ($B_{T}$)".
The number of pairs without a Tuesday Boy is $13 \times 13 = 169$. Thus, $|A| = 196 - 169 = 27$.
The pairs in $A$ where both are boys ($BB$) are of the form $(B_{T}, B_{\text{any}})$ or $(B_{\text{any}}, B_{T})$.
There are $7$ options for the second boy and $7$ for the first boy, but $(B_{T}, B_{T})$ is counted twice. Total $BB$ pairs with at least one $B_{T}$ is $7 + 7 - 1 = 13$.
The conditional probability is $\frac{13}{27}$.

**Answer:** $\frac{13}{27}$

**Q4. The Monty Hall Problem.** You are on a game show. There are 3 doors. Behind one is a car; behind the other two are goats. You pick Door 1. The host, who knows what's behind the doors, opens Door 3, which has a goat. He then asks, "Do you want to switch to Door 2?" What is the probability of winning the car if you switch?

**Solution:** You originally chose the car with probability $\frac{1}{3}$ and a goat with probability $\frac{2}{3}$.
If you originally chose the car, switching gets you a goat.
If you originally chose a goat, the host is forced to reveal the *other* goat. Switching guarantees you the car.
Therefore, switching gives you the car exactly when your initial choice was a goat, which happens with probability $\frac{2}{3}$.

**Answer:** $\frac{2}{3}$

**Q5. The Unfair Coin Pick.** You have a bag with $10$ coins: $9$ are fair, and $1$ is double-headed. You draw one coin at random, flip it $3$ times, and get Heads every time. What is the probability that you picked the double-headed coin?

**Solution:** Let $D$ be double-headed, $F$ be fair. We want $P(D \mid HHH)$.
$P(D) = \frac{1}{10}$, $P(F) = \frac{9}{10}$.
$P(HHH \mid D) = 1$, $P(HHH \mid F) = \frac{1}{8}$.
Total $P(HHH) = P(HHH \mid D)P(D) + P(HHH \mid F)P(F) = (1)(\frac{1}{10}) + (\frac{1}{8})(\frac{9}{10}) = \frac{1}{10} + \frac{9}{80} = \frac{17}{80}$.
$P(D \mid HHH) = \frac{P(HHH \mid D)P(D)}{P(HHH)} = \frac{1/10}{17/80} = \frac{8}{17}$.

**Answer:** $\frac{8}{17}$

## 2. Symmetry & Complement Arguments

::: keypoint
If a problem involves a sequence or an infinite series of symmetric events, look for a shortcut. Often, all irrelevant events can be ignored, or the probability can be determined purely by symmetry without calculating the total number of permutations.
:::

**Q6. Aces Before Kings.** A standard $52$-card deck is shuffled thoroughly. Cards are turned over one by one. What is the probability that the first Ace appears before the first King?

**Solution:** The deck contains $4$ Aces and $4$ Kings. For the question of "which comes first", the other $44$ cards in the deck are completely irrelevant padding.
Imagine removing the $44$ other cards. We only care about the relative ordering of the $8$ target cards (4 Aces, 4 Kings).
By symmetry, any of these $8$ cards is equally likely to be the first one among them to appear. Since $4$ of them are Aces, the probability the first target card is an Ace is $\frac{4}{8} = \frac{1}{2}$.

**Answer:** $\frac{1}{2}$

**Q7. Best of Five.** Two evenly matched teams, A and B, play a "best of 5" series (first to win 3 games wins). What is the probability that team A wins the series?

**Solution:** The long way is adding the probabilities of winning in 3, 4, or 5 games.
The fast way: Imagine they *always* play exactly 5 games, regardless of who wins early. A team wins the series if and only if they win 3, 4, or 5 games out of those 5.
Since the teams are evenly matched (each game is $50/50$), the total number of wins for A out of 5 games will be $3, 4$, or $5$ exactly half the time (the other half, B gets $3, 4$, or $5$ wins).

**Answer:** $\frac{1}{2}$

**Q8. Three Heads Before Two Tails.** You flip a fair coin repeatedly. What is the probability that you observe $3$ Heads before you observe $2$ Tails?

**Solution:** The game is guaranteed to end in at most $3 + 2 - 1 = 4$ flips.
Imagine you always flip the coin exactly $4$ times. You get $3$ Heads before $2$ Tails if and only if you get at least $3$ Heads in those $4$ flips.
The outcomes with $\ge 3$ Heads in $4$ flips are: exactly $4$ Heads ($1$ way), or exactly $3$ Heads ($4$ ways).
Total successful outcomes is $5$. Total possible outcomes for 4 flips is $2^{4} = 16$.

**Answer:** $\frac{5}{16}$

**Q9. First to Roll a Six.** Alice, Bob, and Charlie take turns rolling a standard fair $6$-sided die in that order. The first person to roll a $6$ wins. What is the probability that Alice wins?

**Solution:** Let $P(A)$ be Alice's probability of winning.
On her first turn, she wins with probability $\frac{1}{6}$.
If she loses (probability $\frac{5}{6}$), the game passes to Bob. At this point, Bob is in the exact same position Alice was initially. So Bob's probability of winning from the start is $P(B) = \frac{5}{6} P(A)$.
Similarly, Charlie's probability is $P(C) = \frac{5}{6} P(B) = (\frac{5}{6})^{2} P(A)$.
Since someone must eventually win, $P(A) + P(B) + P(C) = 1$.
$P(A) + \frac{5}{6} P(A) + \frac{25}{36} P(A) = 1 \implies P(A)(\frac{36 + 30 + 25}{36}) = 1 \implies P(A) = \frac{36}{91}$.

**Answer:** $\frac{36}{91}$

## 3. Recursion & State Problems

::: heavy
State-based probability questions often require defining a variable for the unknown probability and setting up a recursive algebraic equation based on the first transition.
:::

**Q10. Gambler's Ruin.** You start with $\$5$. You repeatedly bet $\$1$ on a fair coin flip (win $\$1$ on Heads, lose $\$1$ on Tails). What is the probability you reach $\$10$ before you reach $\$0$ (ruin)?

**Solution:** For a fair game, your expected wealth never changes. Since the endpoints are absorbing states, the probability of reaching the upper bound $N$ starting from $k$ is simply $\frac{k}{N}$.
Here, $k=5$ and $N=10$, so the probability is $\frac{5}{10} = \frac{1}{2}$.

**Answer:** $\frac{1}{2}$

**Q11. Unfair Gambler's Ruin.** Same as above, but you start with $\$1$, want to reach $\$3$, and the game is biased: you win with probability $p=\frac{2}{3}$ and lose with $q=\frac{1}{3}$. Probability you reach $\$3$ before $\$0$?

**Solution:** Let $P_{k}$ be the probability of reaching $\$3$ starting from $\$k$. We know $P_{0} = 0$, $P_{3} = 1$.

$P_{1} = p P_{2} + q P_{0} = \frac{2}{3} P_{2}$

$P_{2} = p P_{3} + q P_{1} = \frac{2}{3}(1) + \frac{1}{3} P_{1}$

Substitute $P_{2}$ into the first equation:

$P_{1} = \frac{2}{3} (\frac{2}{3} + \frac{1}{3} P_{1}) = \frac{4}{9} + \frac{2}{9} P_{1}$.

$\frac{7}{9} P_{1} = \frac{4}{9} \implies P_{1} = \frac{4}{7}$.

**Answer:** $\frac{4}{7}$

**Q12. The HH vs TH Coin Race.** Alice and Bob observe a sequence of fair coin flips. Alice wins if the sequence `HH` appears first. Bob wins if `TH` appears first. What is the probability that Bob wins?

**Solution:** Look at the very first flip.
If the first flip is `T`, Bob is guaranteed to win. The next `H` that appears will immediately complete Bob's `TH` pattern. Alice's `HH` requires an `H` to follow an `H`, which can never happen before a `TH` if we've already seen a `T`. $P(\text{start with T}) = \frac{1}{2}$.
If the first flip is `H`, Alice wins if the second flip is `H` (probability $\frac{1}{4}$ for `HH`). If the second flip is `T`, we have seen `HT`, which means Bob is now guaranteed to win (as we have seen a `T`). This adds $\frac{1}{4}$ to Bob's win probability.
Bob's total probability $= \frac{1}{2} + \frac{1}{4} = \frac{3}{4}$.

**Answer:** $\frac{3}{4}$

::: trap
**Probability vs. Expected Value:** Never confuse "what is the expected number of flips to see `HH`?" with "what is the probability `HH` appears before `TH`?". Expected value solves for time (a number like 6), while probability solves for likelihood (a fraction $\le 1$).
:::

## 4. Geometric Probability

**Q13. The Broken Stick.** You break a stick of length $1$ at two uniformly random points. What is the probability that the three resulting pieces can form a triangle?

**Solution:** Let the cut points be $x$ and $y$. For a triangle to form, the triangle inequality dictates that no single piece can be strictly greater than or equal to half the total length ($\frac{1}{2}$).
If we graph the uniform sample space of $(x, y)$ as a unit square, the region where $x, y-x$, and $1-y$ (assuming $x < y$) are all $< \frac{1}{2}$ forms a triangle in the center of the square.
The area of this valid region represents $\frac{1}{4}$ of the total area of the square.

**Answer:** $\frac{1}{4}$

**Q14. Meeting in an Hour.** Two friends agree to meet at a coffee shop between 12:00 PM and 1:00 PM. Each arrives at a uniformly random time in that hour, waits for exactly 15 minutes, and leaves if the other hasn't arrived. What is the probability they successfully meet?

**Solution:** Let $x$ and $y$ be their arrival times in minutes past 12:00. Both are in $[0, 60]$.
They meet if $|x - y| \le 15$.
Graph this in a $60 \times 60$ square. The area where they *don't* meet consists of two large triangles in the corners: one where $x - y > 15$, one where $y - x > 15$.
These triangles each have a base and height of $45$.
Total area of failure $= 2 \times (\frac{1}{2} \times 45 \times 45) = 45^{2} = 2025$.
Total area of sample space $= 60^{2} = 3600$.
Probability of failure $= \frac{2025}{3600} = \frac{9}{16}$.
Probability they meet $= 1 - \frac{9}{16} = \frac{7}{16}$.

**Answer:** $\frac{7}{16}$

**Q15. Real Roots.** Two real numbers $B$ and $C$ are chosen uniformly at random from the interval $[-1, 1]$. What is the probability that the quadratic equation $x^{2} + Bx + C = 0$ has real roots?

**Solution:** For real roots, the discriminant must be non-negative: $B^{2} - 4C \ge 0$, so $C \le \frac{B^{2}}{4}$.
The sample space is a square of area $2 \times 2 = 4$.
If $C \le 0$ (the bottom half of the square, area 2), the condition always holds since $B^{2}/4 \ge 0$.
If $C > 0$ (the top half), we need the area under the parabola $C = B^{2}/4$ from $B=-1$ to $1$.
Area $= \int_{-1}^{1} \frac{B^{2}}{4} dB = [\frac{B^{3}}{12}]_{-1}^{1} = \frac{1}{12} - (-\frac{1}{12}) = \frac{1}{6}$.
Total successful area $= 2 + \frac{1}{6} = \frac{13}{6}$.
Probability $= \frac{13/6}{4} = \frac{13}{24}$.

**Answer:** $\frac{13}{24}$

## 5. Urn & Combinatorial Probability

**Q16. Hypergeometric Sampling.** A bag contains $5$ red balls and $7$ blue balls. You draw $4$ balls without replacement. What is the probability of drawing exactly $2$ red balls and $2$ blue balls?

**Solution:** Use combinations (hypergeometric distribution).
Total ways to draw 4 balls from 12 is $\binom{12}{4} = \frac{12 \times 11 \times 10 \times 9}{4 \times 3 \times 2 \times 1} = 495$.
Ways to draw 2 red from 5 is $\binom{5}{2} = 10$.
Ways to draw 2 blue from 7 is $\binom{7}{2} = 21$.
Total successful ways is $10 \times 21 = 210$.
Probability $= \frac{210}{495} = \frac{42}{99} = \frac{14}{33}$.

**Answer:** $\frac{14}{33}$

**Q17. The Drunk Secret Santa (Derangements).** 4 people put their names in a hat and draw one uniformly at random. What is the probability that *nobody* draws their own name?

**Solution:** This asks for the probability of a "derangement" (a permutation with no fixed points).
Total permutations for 4 people is $4! = 24$.
The number of derangements for $n$ items, denoted $!n$, follows the recurrence $!n = (n-1)(!(n-1) + !(n-2))$, with $!1 = 0$, $!2 = 1$.
For $n=3$, $!3 = 2(1 + 0) = 2$.
For $n=4$, $!4 = 3(2 + 1) = 9$.
Probability $= \frac{9}{24} = \frac{3}{8}$.

**Answer:** $\frac{3}{8}$

**Q18. Russian Roulette.** You are forced to play Russian Roulette with a standard 6-chamber revolver. The gun is loaded with two bullets in *adjacent* chambers. The first player spins the cylinder, pulls the trigger, and gets a click (empty chamber). It's your turn. Should you pull the trigger immediately, or spin the cylinder first? What are your probabilities of surviving in both cases?

**Solution:** There are 6 chambers. Let bullets be `B` and empty be `E`. The cylinder looks like `B B E E E E`.
If you spin, you select a random chamber out of the 6. There are 2 bullets, so probability of dying is $\frac{2}{6} = \frac{1}{3}$, meaning your survival probability is $\frac{2}{3}$.
If you *don't* spin, you know the previous chamber was an `E`. There are 4 `E`s in the cylinder. The sequence of chambers is `... - B - B - E1 - E2 - E3 - E4 - B - ...`

- After E1, the next chamber is E2 (safe).
- After E2, the next chamber is E3 (safe).
- After E3, the next chamber is E4 (safe).
- After E4, the next chamber is B (deadly).
Since the first player landed on an `E`, they landed on one of these four equally likely `E`s. In 3 out of 4 cases, the next chamber is safe.
Your probability of surviving if you don't spin is $\frac{3}{4}$.
Since $\frac{3}{4} > \frac{2}{3}$, you should NOT spin.

**Answer:** Survival without spinning is $\frac{3}{4}$; with spinning is $\frac{2}{3}$. Do not spin.

## 6. Wrapped OA / Interview Variants

**Q19. The E-Commerce Bot Attack.**
An e-commerce platform identifies $2\%$ of its incoming traffic as malicious bots. The company deploys an AI filter that correctly flags $95\%$ of actual bots. However, it also incorrectly flags $3\%$ of legitimate human traffic as bots. If a session is flagged as a bot by the filter, what is the approximate probability that it is actually a human?
(a) $5\%$
(b) $26\%$
(c) $61\%$
(d) $95\%$

**Solution:** This is Bayes disguised as a system-design word problem.
Let $B$ be a bot ($P(B) = 0.02$, $P(B^{c}) = 0.98$).
Let $F$ be the event of being flagged.
$P(F \mid B) = 0.95$. $P(F \mid B^{c}) = 0.03$.
We want the probability it is a human given it was flagged: $P(B^{c} \mid F)$.
$P(F) = (0.95)(0.02) + (0.03)(0.98) = 0.0190 + 0.0294 = 0.0484$.
$P(B^{c} \mid F) = \frac{0.0294}{0.0484} \approx 0.6074$, which is roughly $61\%$.

**Answer:** $61\%$ (c)

**Q20. Network Packet Routing.**
A network switch has 50 red packets and 50 blue packets. You must distribute them into two separate queues (Queue A and Queue B) in any way you like, provided both queues have at least one packet. The router will first pick one of the two queues with exactly $50\%$ probability, and then draw a packet uniformly at random from that queue. How should you distribute the packets to maximize the probability that the router processes a red packet?

**Solution:** To maximize the chance of drawing a red packet, you want to guarantee a red packet is drawn if one queue is selected, and keep the odds as high as possible if the other is selected.
Put exactly $1$ red packet in Queue A. Put the remaining $49$ red packets and all $50$ blue packets in Queue B.
If Queue A is chosen (prob $\frac{1}{2}$), you get a red packet with probability $1$.
If Queue B is chosen (prob $\frac{1}{2}$), you get a red packet with probability $\frac{49}{99}$.
Total probability $= \frac{1}{2}(1) + \frac{1}{2}(\frac{49}{99}) = \frac{1}{2} + \frac{49}{198} = \frac{99 + 49}{198} = \frac{148}{198} = \frac{74}{99} \approx 74.7\%$.
Any other distribution yields a lower total probability.

**Answer:** Place 1 red packet in Queue A, and 49 red + 50 blue in Queue B.

## The Birthday Paradox

**Q21.** In a room of $23$ people (ignore leap years; $365$ equally likely birthdays), the probability that at
least two share a birthday is closest to:
(a) $6\%$ (b) $30\%$ (c) $50\%$ (d) $70\%$

**Solution:** Attack it by the **complement** — the chance that all $23$ birthdays are *different*:
$$P(\text{all different}) = \frac{365}{365}\cdot\frac{364}{365}\cdots\frac{343}{365} = \frac{365!}{(365-23)!\,365^{23}} \approx 0.493.$$
So $P(\text{at least one shared}) = 1 - 0.493 \approx 0.507$, i.e. about $51\%$ — better than even odds with only
$23$ people, which is why it feels paradoxical.

**Answer:** $\approx 50\%$ (c)

::: keypoint
Count **pairs**, not people: $23$ people form $\binom{23}{2} = 253$ pairs, each with a $\tfrac{1}{365}$ chance of
matching, so a collision is likely far sooner than intuition suggests. Always take "at least one" through the
complement $1 - P(\text{none})$.
:::

## Sources

- Brainstellar — https://brainstellar.com/ (Coin races, Gambler's Ruin, Combinatorics)
- Heard on the Street (Timothy Crack) — (Russian Roulette, Broken Stick)
- Fifty Challenging Problems in Probability (Mosteller) — (Aces before Kings, Two Children paradoxes)
- QuantQuestions — https://www.quantquestions.com/ (Bayes disease variants, Real roots)
