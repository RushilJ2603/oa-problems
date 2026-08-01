# Expected Value & Fair Games

::: definition
**Expected Value (EV):** For a discrete random variable $X$, the expectation is $E[X] = \sum x_{i} P(X = x_{i})$. A game is **fair** when the expected net profit is zero, meaning the **fair price** to play is exactly its expected payoff.

**Linearity of Expectation:** For any random variables $X_{1}, X_{2}, \ldots, X_{n}$:
$$E\left[\sum X_{i}\right] = \sum E[X_{i}]$$
This holds **even if the variables are dependent** — the most powerful tool in expected value problems.

**Non-negative Integers Trick:** For a random variable $X$ taking values in $\{0, 1, 2, \ldots\}$:
$$E[X] = \sum_{k \ge 1} P(X \ge k)$$

**Expectation via Conditioning (Recursion):**
$$E[X] = \sum P(\text{state}) \cdot E[X \mid \text{state}]$$
:::

::: keypoint
Linearity of expectation needs **no independence**. Whenever you are asked for the expected total of something complex, try breaking it into a sum of simple indicator variables $X_{i} \in \{0, 1\}$ and sum their individual expected values.
:::

## Basic EV & Fair Price

**Q1.** A game involves rolling a fair 6-sided die. You are paid the face value in dollars. What is the fair price to play this game?

**Solution:** The fair price is the expected payout of the die.
$E[X] = \frac{1}{6}(1 + 2 + 3 + 4 + 5 + 6) = \frac{21}{6} = 3.5$.

**Answer:** $3.5$

**Q2.** You flip a fair coin twice. You win \$3 for each Heads, but lose \$2 for each Tails. What is your expected net winnings?

**Solution:** Let $X$ be the payoff for a single flip.
$E[X] = \frac{1}{2}(3) + \frac{1}{2}(-2) = 1.5 - 1 = 0.5$.
By linearity of expectation, the expected payoff for $2$ flips is $2 \cdot E[X] = 1$.

**Answer:** $1$

**Q3.** You are offered a choice between two games. Game A guarantees a \$100 payout. Game B is a coin flip: Heads pays \$200, Tails pays \$0. Both have an expected return of \$100. Why might a candidate be asked to choose between them?

**Solution:** While both have $E[X] = 100$, their variances differ wildly.
$Var(A) = 0$, while $Var(B) = \frac{1}{2}(200 - 100)^{2} + \frac{1}{2}(0 - 100)^{2} = 10000$.
A risk-averse person prefers Game A (lower variance), while a risk-seeking person prefers Game B. In quant interviews, unless specified otherwise, you price games based purely on expected value (risk-neutral), but variance matters for position sizing.

**Answer:** Game A has zero variance; Game B has high variance.

**Q4.** You roll two fair 6-sided dice. You win the product of the two rolls in dollars. What is your expected payout?

**Solution:** Let $X$ and $Y$ be the outcomes of the two dice. We want $E[XY]$. Since the dice are independent, $E[XY] = E[X] \cdot E[Y]$.
We know $E[X] = 3.5$ and $E[Y] = 3.5$.
$E[XY] = 3.5 \times 3.5 = 12.25$.

**Answer:** $12.25$

## Optional Stopping / Reroll & Option Value

**Q5.** You roll a fair 6-sided die. You may keep the face value in dollars, or you can choose to reroll exactly once. If you reroll, you must keep the second value. What is the expected value of this game?

**Solution:** Work backwards using conditioning. On the second roll, the expected value is $3.5$.
On the first roll, you should only reroll if your face value is strictly less than the expected value of the second roll. So, keep a $4$, $5$, or $6$. Reroll a $1$, $2$, or $3$.
The expected payoff of the game is $E[\max(\text{first roll}, 3.5)]$.
$E[X] = \frac{1}{6}(3.5 + 3.5 + 3.5 + 4 + 5 + 6) = \frac{25.5}{6} = 4.25$.

**Answer:** $4.25$

**Q6.** Consider the same game, but you can choose to reroll up to two times (meaning up to three rolls total, keeping the final roll). What is the expected value?

**Solution:** Work backwards again. If you reach the third roll, the expected value is $3.5$.
If you are on the second roll, you know the expected value of rerolling is $3.5$. So you keep $4, 5, 6$ and reroll $1, 2, 3$, yielding an expected value of $4.25$ (from Q5).
If you are on the first roll, you know the expected value of proceeding is $4.25$. You should only keep a $5$ or $6$, and reroll a $1, 2, 3$, or $4$.
$E[X] = \frac{1}{6}(4.25 + 4.25 + 4.25 + 4.25 + 5 + 6) = \frac{17 + 11}{6} = \frac{28}{6} = 4.67$.

**Answer:** $4.67$

**Q7.** You roll a 100-sided die. You can keep the number, or pay \$1 to roll again. You can do this indefinitely. What is your optimal strategy and expected payoff?

**Solution:** Let $V$ be the expected payoff of the game using the optimal strategy. If you play optimally, rolling again gives an expected value of $V - 1$.
You should stop if your roll $x \ge V - 1$. The threshold $k$ is the smallest integer $\ge V - 1$.
$V = \sum_{x=1}^{100} \frac{1}{100} \max(x, V - 1)$.
Assume the threshold is $k = 87$. Then $V - 1$ is around $86$. Let's test $k=87$:
$100V = 86(V - 1) + \sum_{x=87}^{100} x = 86V - 86 + 1309 \implies 14V = 1223 \implies V \approx 87.35$.
Since $87.35 - 1 = 86.35$, the threshold to stop is indeed $87$.

**Answer:** $87.35$ (keep $\ge 87$)

## Linearity of Expectation Gems

**Q8.** (Hat Check) $N$ people check their hats at a party. The hats are returned uniformly at random. What is the expected number of people who receive their own hat?

**Solution:** Let $X$ be the number of people who get their own hat. We express $X = X_{1} + X_{2} + \ldots + X_{N}$, where $X_{i} = 1$ if person $i$ gets their own hat, and $0$ otherwise.
$E[X_{i}] = P(\text{person } i \text{ gets own hat}) = \frac{1}{N}$.
By linearity of expectation, $E[X] = E[X_{1}] + \ldots + E[X_{N}] = N \cdot \frac{1}{N} = 1$.
Notice how this result is completely independent of $N$.

**Answer:** $1$

**Q9.** A standard deck of 52 cards is shuffled. What is the expected number of adjacent pairs of cards that are both aces? (For example, if the aces are at positions 1, 2, 4, 10, there is 1 adjacent pair at positions 1 and 2).

**Solution:** There are $51$ possible adjacent pairs (positions 1-2, 2-3, ..., 51-52). Let $X_{i} = 1$ if the pair at positions $i$ and $i+1$ are both aces, and $0$ otherwise.
$E[X_{i}] = P(\text{cards } i \text{ and } i+1 \text{ are aces}) = \frac{4}{52} \cdot \frac{3}{51} = \frac{1}{13 \cdot 17} = \frac{1}{221}$.
By linearity of expectation, the expected total is $E[X] = \sum_{i=1}^{51} E[X_{i}] = 51 \cdot \frac{1}{221} = \frac{51}{221} = \frac{3}{13}$.

**Answer:** $\frac{3}{13}$

**Q10.** (Expected Records) You are given an array of $N$ distinct random numbers, uniformly permuted. As you scan from left to right, you count a "record" every time you see a number larger than all previous numbers. What is the expected number of records? (The first number is always a record).

**Solution:** Let $X_{i} = 1$ if the $i$-th number is a record, and $0$ otherwise.
The $i$-th number is a record if and only if it is the largest among the first $i$ numbers. Since the permutation is random, any of the first $i$ numbers is equally likely to be the largest among them.
Thus, $E[X_{i}] = P(\text{record at } i) = \frac{1}{i}$.
By linearity of expectation, $E[X] = \sum_{i=1}^{N} E[X_{i}] = 1 + \frac{1}{2} + \frac{1}{3} + \ldots + \frac{1}{N} = H_{N}$ (the $N$-th harmonic number).

**Answer:** $H_{N}$

## Expected Length / Number of Trials

**Q11.** You flip a fair coin repeatedly. What is the expected number of flips until you see Heads for the first time?

**Solution:** The waiting time for the first success in independent Bernoulli trials follows a geometric distribution with probability $p$.
Using the formula: $E[X] = \frac{1}{p} = \frac{1}{1/2} = 2$.
Alternatively, using recursion: $E = 1 + \frac{1}{2}(0) + \frac{1}{2}(E)$, giving $\frac{1}{2}E = 1 \implies E = 2$.

**Answer:** $2$

**Q12.** What is the expected number of fair coin flips to get two Heads in a row (HH)?

**Solution:** Let $E$ be the expected flips to get HH. Condition on the first flip.
If the first flip is T (prob $1/2$), we've wasted $1$ flip and start over: $1 + E$.
If the first flip is H (prob $1/2$), we condition on the second flip:
If the second flip is T (prob $1/2$), we've wasted $2$ flips and start over: $2 + E$.
If the second flip is H (prob $1/2$), we've succeeded in $2$ flips: $2$.
$E = \frac{1}{2}(1 + E) + \frac{1}{4}(2 + E) + \frac{1}{4}(2)$.
$E = \frac{1}{2} + \frac{1}{2}E + \frac{1}{2} + \frac{1}{4}E + \frac{1}{2} = 1.5 + \frac{3}{4}E$.
$\frac{1}{4}E = 1.5 \implies E = 6$.

**Answer:** $6$

::: trap
A common mistake is assuming that since HH and HT both have a probability of $1/4$ in two flips, their expected waiting times are equal. They are not! If you fail to get HH because you rolled HT, the T completely ruins your streak. If you fail to get HT because you rolled HH, you still have an H to build upon.
:::

**Q13.** What is the expected number of fair coin flips to get Heads followed by Tails (HT)?

**Solution:** Let $E$ be the expected flips to get HT.
From the start, the expected flips to get the first H is $2$. Once we roll a Heads, we are in a "have H" state. Let $E_{H}$ be the expected additional flips from this state.
$E = 2 + E_{H}$.
From the "have H" state, if we flip T (prob $1/2$), we are done in $1$ additional flip.
If we flip H (prob $1/2$), we are still in the "have H" state, using $1$ flip: $1 + E_{H}$.
$E_{H} = \frac{1}{2}(1) + \frac{1}{2}(1 + E_{H}) \implies E_{H} = 1 + \frac{1}{2}E_{H} \implies E_{H} = 2$.
Thus, $E = 2 + 2 = 4$.

**Answer:** $4$

**Q14.** (Coupon Collector) You roll a fair 6-sided die repeatedly. What is the expected number of rolls until you have seen all six faces at least once?

**Solution:** Let $X$ be the total rolls, $X = T_{1} + T_{2} + \ldots + T_{6}$, where $T_{k}$ is the rolls needed to get a new face when you already have $k-1$ distinct faces.
The probability of a new face is $p_{k} = \frac{6 - (k-1)}{6}$.
Since each $T_{k}$ is geometric, $E[T_{k}] = \frac{1}{p_{k}} = \frac{6}{7-k}$.
$E[X] = \sum_{k=1}^{6} \frac{6}{7-k} = 6 \left( 1 + \frac{1}{2} + \frac{1}{3} + \frac{1}{4} + \frac{1}{5} + \frac{1}{6} \right) = 6 \left( \frac{147}{60} \right) = 14.7$.

**Answer:** $14.7$

## Random Walks & Gambler's Ruin EV

**Q15.** A gambler starts with \$A and plays a fair game where they win \$1 or lose \$1 with equal probability at each step. They will stop when they reach \$N (where $N > A$) or go broke (\$0). What is the probability they reach \$N?

**Solution:** Let $P(A)$ be the probability of reaching $N$ starting from $A$. Since the game is fair, the expected wealth is constant (it is a martingale).
$\text{Initial wealth} = \text{Expected final wealth}$.
$A = P(A) \cdot N + (1 - P(A)) \cdot 0$.
$P(A) = \frac{A}{N}$.

**Answer:** $\frac{A}{N}$

::: keypoint
For fair random walks with absorbing boundaries at $0$ and $N$, use the **martingale property**: the expected value of your position at the end of the game must identically equal your starting position.
:::

**Q16.** In the same setup (starting at $A$, boundaries at $0$ and $N$, fair $\pm 1$ game), what is the expected number of steps until the game ends?

**Solution:** Let $E(A)$ be the expected number of steps starting from $A$.
$E(A) = 1 + \frac{1}{2}E(A+1) + \frac{1}{2}E(A-1)$, with boundary conditions $E(0) = 0$ and $E(N) = 0$.
This is a linear recurrence that forms a parabola. The function $f(A) = A(N-A)$ naturally satisfies the boundaries.
Plugging $A(N-A)$ into the right side:
$1 + \frac{1}{2}(A+1)(N-A-1) + \frac{1}{2}(A-1)(N-A+1)$
$= 1 + \frac{1}{2} [ A(N-A) + N - 2A - 1 + A(N-A) - N + 2A - 1 ] = 1 + A(N-A) - 1 = A(N-A)$.
It satisfies the recurrence.

**Answer:** $A(N-A)$

## Interview Market-Making Variant

::: interview
In trading interviews, they often ask you to "make a market" (quote a bid and an ask price) on a random variable. Your fair value should be the expected value. Your spread (ask - bid) reflects your uncertainty and desired profit margin, but the midpoint is typically the EV. The interviewer will "trade" with you based on your quote to exploit any mispricing.
:::

**Q17.** Make a market on the sum of 100 fair 6-sided dice.

**Solution:** First, find the expected value. The EV of one die is $3.5$.
By linearity of expectation, the EV of 100 dice is $100 \times 3.5 = 350$.
You should center your market exactly around $350$. A reasonable market would be a tight spread around it, say bid $348$, ask $352$. If you improperly quote $340$ @ $345$, the interviewer will immediately "buy" from you at $345$, knowing the true EV is $350$, thereby securing a positive expected value at your expense.

**Answer:** $350$ (quote a tight spread around it, e.g., $348$ @ $352$)

**Q18.** Make a market on the expected number of tosses of a fair coin to get 3 Heads in a row (HHH).

**Solution:** Let $E$ be the expected tosses for HHH. Condition on the sequence that breaks our streak or completes it.
If T (prob $1/2$), we waste $1$ toss: $1 + E$.
If HT (prob $1/4$), we waste $2$ tosses: $2 + E$.
If HHT (prob $1/8$), we waste $3$ tosses: $3 + E$.
If HHH (prob $1/8$), we are done in $3$ tosses: $3$.
$E = \frac{1}{2}(1+E) + \frac{1}{4}(2+E) + \frac{1}{8}(3+E) + \frac{1}{8}(3)$.
$E = \left(\frac{1}{2} + \frac{2}{4} + \frac{3}{8} + \frac{3}{8}\right) + E\left(\frac{1}{2} + \frac{1}{4} + \frac{1}{8}\right) = \frac{14}{8} + \frac{7}{8}E$.
$E - \frac{7}{8}E = \frac{14}{8} \implies \frac{1}{8}E = \frac{14}{8} \implies E = 14$.

**Answer:** $14$

**Q19.** (Optiver) We play a game. You flip a fair coin. If it's Heads, you win \$1. If it's Tails, your payout is \$0, but you face a choice: stop and take \$0, or pay \$1 to play the game again. What is the fair value of this game?

**Solution:** Let $V$ be the fair value of the game. If you roll Tails, you choose between taking \$0, or paying \$1 to restart (expected net value of $V - 1$).
Since you play optimally, your value after Tails is $\max(0, V - 1)$.
The equation for the game's overall value is: $V = \frac{1}{2}(1) + \frac{1}{2} \max(0, V - 1)$.
Assume $V - 1 \le 0 \implies V \le 1$. Then $\max(0, V - 1) = 0$.
$V = \frac{1}{2}(1) + 0 = 0.5$.
Checking our assumption: $0.5 - 1 = -0.5 \le 0$. The assumption mathematically holds.
So you should always stop on Tails.

**Answer:** $0.50$

**Q20.** You have a bag containing 2 red balls and 2 black balls. You draw them one by one without replacement. You can choose to stop at any time. Your payoff is the number of red balls drawn minus the number of black balls drawn. What is your optimal strategy and expected payoff?

**Solution:** Work backwards. The state is $(r, b)$ where $r, b$ are the remaining red and black balls. The current payoff is $(2-r) - (2-b) = b - r$. Let $V(r, b)$ be the expected payoff from this state playing optimally.
At any state, you choose the maximum between stopping ($b - r$) and drawing ($\frac{r}{r+b}V(r-1, b) + \frac{b}{r+b}V(r, b-1)$).
$V(0, 0) = 0$.
$V(1, 0) = \max(-1, 0) = 0$ (draw the last red).
$V(0, 1) = \max(1, 0) = 1$ (stop, don't draw black).
$V(2, 0) = \max(-2, 0) = 0$ (draw both reds).
$V(0, 2) = \max(2, 0) = 2$ (stop immediately).
$V(1, 1) = \max(0, \frac{1}{2}(1) + \frac{1}{2}(0)) = 0.5$.
$V(2, 1) = \max(-1, \frac{2}{3}(0.5) + \frac{1}{3}(0)) = \frac{1}{3}$.
$V(1, 2) = \max(1, \frac{1}{3}(2) + \frac{2}{3}(0.5)) = \max(1, 1) = 1$.
$V(2, 2) = \max(0, \frac{1}{2}(1) + \frac{1}{2}(\frac{1}{3})) = \max(0, \frac{2}{3}) = \frac{2}{3}$.

**Answer:** $\frac{2}{3}$

## Two Famous Paradoxes: St. Petersburg & the Secretary Problem

**Q21.** *(St. Petersburg.)* A fair coin is tossed until the first head. If the first head appears on toss $k$, you
are paid $2^{k}$ dollars. What is the expected payout — and what is the lesson?

**Solution:** The first head lands on toss $k$ with probability $\tfrac{1}{2^{k}}$, paying $2^{k}$, so each term
of the expectation is $\tfrac{1}{2^{k}}\cdot 2^{k} = 1$:
$$E[\text{payout}] = \sum_{k=1}^{\infty} \frac{1}{2^{k}}\cdot 2^{k} = \sum_{k=1}^{\infty} 1 = \infty.$$
The expected value is **infinite**, yet nobody would pay a large fee to play — the paradox. Its resolution
(diminishing marginal utility of money, and finite bankrolls) is exactly why expected value alone is a poor guide
for heavy-tailed payoffs.

**Answer:** infinite expected value

::: trap
A **divergent or heavy-tailed** expectation is a warning flag: the mean is dominated by astronomically rare
outcomes, so variance and ruin risk — not EV — should drive the decision.
:::

**Q22.** *(Secretary problem.)* You interview $n$ candidates one at a time in random order and must accept or
reject each on the spot, with no recalls; you want the single best. What strategy maximises your chance, and what
is that chance for large $n$?

**Solution:** Use **look-then-leap**: reject the first $\approx n/e$ candidates outright (just record the best so
far), then accept the first later candidate who beats everyone seen. As $n$ grows, both the optimal cutoff and the
success probability tend to $1/e \approx 37\%$.

**Answer:** skip the first $\approx 37\%$, then take the next record-beater — succeeds $\approx 37\%$ of the time

::: interview
The "$37\%$ rule" generalises to hiring, apartment-hunting, and buy/sell timing: sample to calibrate, then commit
to the first option that beats your sample. Interviewers look for the *reason* $1/e$ appears, not just the number.
:::

## Sources

- Brainstellar — https://brainstellar.com/
- TraderMath — https://www.tradermath.org/
- QuantQuestions — https://www.quantquestions.com/
- "A Practical Guide to Quantitative Finance Interviews" (Xinfeng Zhou)
