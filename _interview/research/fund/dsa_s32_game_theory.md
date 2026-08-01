# Game Theory & Market-Making Reasoning

::: definition
**Game Theory & Market-Making Equilibrium**

- **Dominant Strategy:** A move that yields the best payoff regardless of what the opponent does.
- **Nash Equilibrium:** A state where no player can improve their expected payoff by unilaterally changing their strategy.
- **Backward Induction:** The master method for sequential games. Start at the *last possible move*, determine the optimal choice there, and reason backwards to the first move.
- **Mixed Strategy:** Playing different choices with specific probabilities to make the opponent *indifferent* between their counter-moves.
- **Fair Value (No-Arbitrage):** In a market-making or betting game, pricing an asset such that neither side can lock in a risk-free profit (a Dutch book), properly accounting for **adverse selection** (the risk of being "picked off" by an informed trader).

:::

## Combinatorial Take-Away Games

::: keypoint
In take-away games (Nim variants), work backwards from the target to identify winning ($W$) and losing ($L$) positions. A position is $W$ if it has at least one transition to an $L$ position; it is $L$ if *all* transitions lead to a $W$ position.

:::

**Q1.** Two players start with a pile of $20$ coins. They take turns removing $1$, $2$, or $3$ coins. The player who takes the last coin **loses**. You go first. How many coins should you take on your first turn to guarantee a win?
(a) $1$
(b) $2$
(c) $3$
(d) There is no winning strategy for the first player

**Solution:**
Work via backward induction to find the target positions (leaving these guarantees victory).
To make the opponent take the last coin, you must leave exactly $1$ coin on your final turn.
To guarantee leaving $1$, you must previously leave $1 + (3+1) = 5$ coins, because however many ($x$) the opponent takes from $5$, you can take $4 - x$ to leave exactly $1$.
Continuing backwards by multiples of $4$, the winning targets to leave are $1, 5, 9, 13, 17$.
Starting at $20$, you can reach $17$ by taking $3$ coins.

**Answer:** $3$ (c)

**Q2.** Two players start at $0$. They take turns adding any integer from $1$ to $10$ to the running total. The first player to reach exactly $100$ wins. You go first. What number do you say?
(a) $1$
(b) $9$
(c) $10$
(d) $11$

**Solution:**
The target is $100$. Apply backward induction.
To guarantee reaching $100$, you must leave $100 - (10+1) = 89$ on your previous turn.
The winning positions are $100 - 11k$.
For $k=9$, the target is $100 - 99 = 1$.
Since the game starts at $0$, you must add $1$ on your first turn.

**Answer:** $1$ (a)

**Q3.** There are two piles of coins, each containing exactly $10$ coins. On a turn, a player may take any number of coins ($>0$) from a *single* pile. The player to take the last coin wins. You go first. What is your best strategy?
(a) Take $1$ coin from one pile
(b) Take all $10$ coins from one pile
(c) Take $5$ coins from one pile
(d) You cannot guarantee a win

**Solution:**
This is 2-pile Nim. The winning strategy is to maintain symmetry via backward induction.
If you leave two identical piles, whatever the opponent does to one pile, you can mirror on the other pile, guaranteeing you take the last coin.
However, since the game starts with equal piles ($10$ and $10$), the *second* player has the symmetry advantage. Any move you make breaks the symmetry, allowing the opponent to restore it. Thus, the first player has no winning strategy against a perfect opponent.

**Answer:** You cannot guarantee a win (d)

**Q4.** (Nim) There are three piles of coins containing $3$, $4$, and $5$ coins respectively. You can take any number of coins from a single pile. The last player to take a coin wins. You go first. What is the winning move?
(a) Take $1$ from the pile of $3$
(b) Take $2$ from the pile of $3$
(c) Take $2$ from the pile of $4$
(d) Take $1$ from the pile of $5$

**Solution:**
A position in Nim is losing if the XOR sum ($\oplus$) of the pile sizes is $0$.
Current XOR sum: $3 \oplus 4 \oplus 5 = 011_2 \oplus 100_2 \oplus 101_2 = 010_2 = 2$.
To make the sum $0$, you must reduce a pile such that its new size equals the XOR sum of the other two piles.
Try the pile of $3$: the XOR sum of the others is $4 \oplus 5 = 100_2 \oplus 101_2 = 001_2 = 1$.
Since $1 < 3$, you can reduce the pile of $3$ to $1$ (by taking $2$ coins).
The new state is $1, 4, 5$, which has an XOR sum of $0$.

**Answer:** Take $2$ from the pile of $3$ (b)

## Backward Induction

::: heavy
**Backward Induction**
Do not attempt to plan forward through a game tree. Go to the terminal state (the end of the game), figure out what the last player is forced to do, substitute that payoff one step up, and repeat.

:::

**Q5.** Five highly rational pirates (ranked $1$ to $5$, with $1$ being the most senior) must divide $100$ gold coins. Pirate $1$ proposes a distribution. All pirates (including $1$) vote. If at least $50\%$ accept, it passes. If not, $1$ is thrown overboard, and Pirate $2$ proposes, with the same rules. What distribution should Pirate $1$ propose?
(a) $98, 0, 1, 0, 1$
(b) $20, 20, 20, 20, 20$
(c) $96, 1, 1, 1, 1$
(d) $100, 0, 0, 0, 0$

**Solution:**
Use backward induction.

- **$2$ pirates left (4, 5):** Pirate $4$ proposes $100, 0$. Pirate $4$ votes yes ($50\%$), so it passes. Pirate $5$ gets $0$.
- **$3$ pirates left (3, 4, 5):** Pirate $3$ needs $2$ votes (including themselves). Pirate $5$ gets $0$ if Pirate $3$ dies, so Pirate $3$ can buy Pirate $5$'s vote for $1$ coin. Proposal: $99, 0, 1$.
- **$4$ pirates left (2, 3, 4, 5):** Pirate $2$ needs $2$ votes. If Pirate $2$ dies, Pirate $4$ gets $0$. Pirate $2$ buys Pirate $4$'s vote for $1$ coin. Proposal: $99, 0, 1, 0$.
- **$5$ pirates left (1, 2, 3, 4, 5):** Pirate $1$ needs $3$ votes. If Pirate $1$ dies, Pirates $3$ and $5$ get $0$. Pirate $1$ buys their votes for $1$ coin each. Proposal: $98, 0, 1, 0, 1$.

**Answer:** $98, 0, 1, 0, 1$ (a)

**Q6.** You are offered $100$ dollars to split with a completely rational, profit-maximizing stranger. You propose an integer split. If the stranger accepts, you both get the proposed amounts. If they reject, you both get $0$ dollars. What do you offer them to maximize your own payoff?
(a) $50$
(b) $1$
(c) $49$
(d) $0$

**Solution:**
Backward induction from the stranger's decision.
If you offer them $1$ dollar, their choice is between accepting $1$ or rejecting for $0$. A rational profit-maximizer strictly prefers $1$ over $0$.
Therefore, they will accept $1$. Offering anything more decreases your payoff.
*(Note: Real humans often reject unfair offers due to spite, but game-theory questions assume perfect utility maximization unless stated otherwise).*

**Answer:** $1$ (b)

::: trap
Do not confuse real-world psychology with game-theoretic rationality. If a problem states players are "rational", they will accept a $1$-unit profit over $0$.

:::

**Q7.** A teacher announces: "There will be a surprise test on one day next week (Monday to Friday). It will be a surprise because, on the morning of the test, you will not be able to logically deduce that the test is that day." Assuming students have perfect logic, on which day can the test be held?
(a) Wednesday
(b) Any day
(c) Monday
(d) The test cannot logically exist

**Solution:**
Apply backward induction.

- Could it be Friday? If no test occurred Mon–Thu, students would *know* it must be Friday. It wouldn't be a surprise. So Friday is eliminated.
- Could it be Thursday? Since Friday is eliminated, if no test occurs Mon–Wed, students would *know* it must be Thursday. Not a surprise. Thursday is eliminated.
- This logic cascades backwards, eliminating Wednesday, Tuesday, and Monday.

Therefore, a truly "surprise" test under these strict logical conditions is a paradox and cannot exist.

**Answer:** The test cannot logically exist (d)

**Q8.** Two rational players participate in an auction for a $100$ dollar bill. Bidding starts at $1$ and increases in $1$ dollar increments. The highest bidder wins the $100$ bill, but **both** the highest and the second-highest bidder must pay their final bids to the auctioneer. What is the rational strategy?
(a) Bid $100$ immediately
(b) Do not enter the auction
(c) Bid up to $99$ and stop
(d) Bid $50$

**Solution:**
If Player A bids $1$, Player B has an incentive to bid $2$ to win $100$.
However, if Player A bids $99$ and Player B bids $100$, Player A is about to lose their $99$ and get nothing. Player A has a rational incentive to bid $101$ to win the $100$ (net loss of $1$, which is better than a net loss of $99$).
This leads to an infinite escalation where both players lose massive amounts of money (the Dollar Auction trap).
The only rational choice via backward induction is to recognize this trap and refuse to make the first bid.

**Answer:** Do not enter the auction (b)

## Auctions & Fair Value

::: keypoint
In a **First-Price Auction**, you bid *below* your true valuation to secure a profit margin.
In a **Second-Price (Vickrey) Auction**, it is a dominant strategy to bid *exactly* your true valuation.

:::

**Q9.** You are in a sealed-bid first-price auction for an item you value at $100$ dollars. There is one other bidder. You believe their valuation is uniformly distributed between $0$ and $100$. What should you bid to maximize your expected profit?
(a) $100$
(b) $50$
(c) $99$
(d) $75$

**Solution:**
If you bid $b$, you win if $b >$ the opponent's bid.
Your expected profit is $(100 - b) \times P(\text{win})$.
Assuming a symmetric equilibrium, the opponent bids a fraction of their value, so their bid is uniformly distributed on $[0, c]$. The probability you win is proportional to $b$.
Expected profit $\propto (100 - b) \times b = 100b - b^{2}$.
Taking the derivative with respect to $b$ and setting it to $0$: $100 - 2b = 0 \implies b = 50$.
Against $1$ uniformly distributed opponent, you shade your bid to exactly half your valuation.

**Answer:** $50$ (b)

**Q10.** You are in a sealed-bid **second-price** auction for an item you value at $100$ dollars. The highest bidder wins, but pays the price of the *second-highest* bid. What should you bid?
(a) $50$
(b) $99$
(c) $100$
(d) $101$

**Solution:**
In a second-price auction, your bid only determines *if* you win, not *what you pay* (as long as you win).

- If you bid less than $100$, you risk losing the item to someone bidding between your bid and $100$, missing out on guaranteed profit.
- If you bid more than $100$, you risk winning the item at a price higher than $100$, taking a loss.

Bidding your exact true valuation is a dominant strategy, eliminating the need to guess others' valuations via backward induction.

**Answer:** $100$ (c)

**Q11.** (Winner's Curse) A startup is worth a uniformly random amount between $0$ and $100$ million dollars to its current owners. Because of synergies, it will be worth exactly $1.5$ times that amount to you. You can make a single blind cash bid. The owners will accept only if your bid is greater than or equal to their value. What should you bid to maximize expected profit?
(a) $0$
(b) $50$
(c) $75$
(d) $100$

**Solution:**
Assume you bid $B$. The owners accept if their value $V \le B$.
Given that they accept, $V$ is uniformly distributed between $0$ and $B$.
The expected value of the company *to its owners*, conditional on them accepting, is $B / 2$.
The expected value *to you* is $1.5 \times (B / 2) = 0.75B$.
If you win, you pay $B$ for an asset with an expected value to you of $0.75B$.
Your expected profit is $0.75B - B = -0.25B$.
Since the expected profit is negative for any positive bid, you should not bid.

**Answer:** $0$ (a)

::: trap
The **Winner's Curse** occurs when you win an auction precisely because you overestimated the asset's value more than anyone else, or because the seller knows something you don't. Always calculate expected value *conditional on your bid being accepted*.

:::

**Q12.** (Keynesian Beauty Contest) $100$ rational players are asked to choose a real number between $0$ and $100$ inclusive. The winner is the person whose number is closest to exactly **two-thirds of the average** of all numbers chosen. What number does every rational player choose?
(a) $50$
(b) $33.3$
(c) $22.2$
(d) $0$

**Solution:**
Use iterated backward induction on dominated strategies.

- The highest the average could possibly be is $100$. Thus, $2/3$ of the average can never exceed $66.67$. A rational player will never guess above $66.67$.
- If everyone realizes this, the new maximum average is $66.67$. Then $2/3$ of that is $44.44$. So no one will guess above $44.44$.
- This iterated elimination continues infinitely.
- The only equilibrium point is $0$.

**Answer:** $0$ (d)

## Betting & Market-Making Games

::: interview
In quant and trading interviews, "market-making" games test your ability to price risk under **adverse selection**. The interviewer has asymmetric information (they see the dice/card, you don't). If they trade with you, it's because *your price is wrong in their favor*. You must price this in.

:::

**Q13.** A bookmaker offers odds of $2.0$ (a $1:1$ payout) on Team A winning, and $3.0$ (a $2:1$ payout) on Team B winning. There are no other outcomes. How can you lock in a guaranteed risk-free profit (a Dutch book) if you have $50$ dollars to bet?
(a) Bet $25$ on A and $25$ on B
(b) Bet $30$ on A and $20$ on B
(c) Bet $20$ on A and $30$ on B
(d) It is impossible

**Solution:**
To guarantee the same payout regardless of the outcome, the payouts must be equal.
Let $x$ be the bet on A, and $y$ be the bet on B.
Payout if A wins: $2.0x$. Payout if B wins: $3.0y$.
Set $2.0x = 3.0y \implies x = 1.5y$.
Since total capital is $50$, $x + y = 50 \implies 1.5y + y = 50 \implies 2.5y = 50 \implies y = 20$.
Then $x = 30$.
In either case, the payout is $60$. You bet $50$, locking in a $10$ risk-free profit.

**Answer:** Bet $30$ on A and $20$ on B (b)

**Q14.** You are invited to play a game with a fair coin. If it lands Heads, you win $100$ dollars. If Tails, you lose $100$ dollars. Before deciding whether to play, an oracle offers to sell you the outcome of the flip. What is the maximum fair price you should pay for this information?
(a) $0$
(b) $25$
(c) $50$
(d) $100$

**Solution:**

- Without information: The game has an EV of $0$ ($0.5 \times 100 - 0.5 \times 100$). You are indifferent to playing, EV is $0$.
- With information: You only choose to play when the oracle says Heads. You decline to play on Tails (payout $0$).
- Your expected payoff with information is $0.5 \times 100 + 0.5 \times 0 = 50$.

The value of the information is the difference in EV: $50 - 0 = 50$.

**Answer:** $50$ (c)

**Q15.** The interviewer rolls a fair $6$-sided die and hides it. You must quote a single price $P$. The interviewer will **sell** the die's outcome to you for $P$ if the roll is $\le P$, and will **buy** it from you for $P$ if the roll is $> P$. What price $P$ minimizes your expected worst-case loss?
(a) $3.0$
(b) $3.5$
(c) $4.0$
(d) $4.5$

**Solution:**
Because of adverse selection, you will always lose money. The interviewer only trades when it advantages them.
If roll $\le P$, they sell. You pay $P$. The expected value of the die given it is $\le P$ is $(P+1)/2$. Your loss is $P - (P+1)/2 = (P-1)/2$.
If roll $> P$, they buy. You receive $P$. The expected value of the die given it is $> P$ is $(P+1+6)/2 = (P+7)/2$. Your loss is $(P+7)/2 - P = (7-P)/2$.
Since the die is fair, probability of $\le P$ is $P/6$, and $> P$ is $(6-P)/6$.
Total Expected Loss = $(P/6) \times (P-1)/2 + ((6-P)/6) \times (7-P)/2 = (P^{2} - P + 42 - 13P + P^{2})/12 = (P^{2} - 7P + 21)/6$.
To minimize this parabola, take the derivative with respect to $P$ and set to $0$: $2P - 7 = 0 \implies P = 3.5$.

**Answer:** $3.5$ (b)

**Q16.** You act as a market maker for the sum of two $6$-sided dice. The interviewer rolls the dice secretly. You quote a bid of $6$ and an ask of $8$. The interviewer immediately says "Sold" (meaning they sell the outcome to you for $6$). What is your expected loss on this transaction?
(a) $0$
(b) $1.33$
(c) $1.50$
(d) $2.00$

**Solution:**
The interviewer selling at $6$ means the true sum is strictly $\le 6$.
The possible sums $\le 6$ and their frequencies (out of $36$ total combinations) are:

- $2$: $1$ way
- $3$: $2$ ways
- $4$: $3$ ways
- $5$: $4$ ways
- $6$: $5$ ways

Total ways = $15$.
The expected value of the sum given it is $\le 6$ is:
$E[\text{Sum} \mid \le 6] = \frac{2(1) + 3(2) + 4(3) + 5(4) + 6(5)}{15} = \frac{2 + 6 + 12 + 20 + 30}{15} = \frac{70}{15} \approx 4.67$.
You paid $6$ for an asset worth exactly $4.67$.
Your expected loss is $6 - 4.67 = 1.33$.

**Answer:** $1.33$ (b)

## Mixed Strategies & Symmetry

::: keypoint
In a zero-sum game with no pure dominant strategy, you must use a **mixed strategy** (randomizing your moves). The correct probabilities are found by setting your opponent's expected payoffs for their various choices to be *exactly equal*, making them indifferent to what they choose.

:::

**Q17.** In an asymmetric game of Rock-Paper-Scissors, winning with Rock against Scissors pays $10$ dollars. Winning with Paper against Rock pays $5$ dollars. Winning with Scissors against Paper pays $5$ dollars. In all cases, the loser pays the winner. Draws pay $0$. To maximize your expected payoff against a perfect opponent, with what probability should you play Rock?
(a) $1/3$
(b) $1/4$
(c) $1/2$
(d) $2/5$

**Solution:**
Let $p_R, p_P, p_S$ be the probabilities your opponent plays R, P, S.
To make you indifferent to your choices, your expected values must be equal. (Since the game is symmetric between players, the equilibrium EV is $0$).

- EV(Rock) = $0(p_R) - 5(p_P) + 10(p_S) = 0 \implies 5p_P = 10p_S \implies p_P = 2p_S$
- EV(Paper) = $5(p_R) + 0(p_P) - 5(p_S) = 0 \implies 5p_R = 5p_S \implies p_R = p_S$

Since $p_R + p_P + p_S = 1$:
$p_S + 2p_S + p_S = 1 \implies 4p_S = 1 \implies p_S = 1/4$.
Then $p_R = 1/4$ and $p_P = 1/2$.
To force the opponent's EV to be $0$, you must play the exact same distribution. You should play Rock with probability $1/4$.

**Answer:** $1/4$ (b)

**Q18.** (The Truel) Alice, Bob, and Charlie are in a three-way duel (truel) with water balloons. They take turns shooting. Alice hits her target $30\%$ of the time, Bob $100\%$ of the time, and Charlie $50\%$ of the time. The turn order is Alice, then Charlie, then Bob (if they are still in). What is Alice's optimal first move?
(a) Shoot at Bob
(b) Shoot at Charlie
(c) Miss on purpose
(d) Shoot at herself

**Solution:**
Use backward induction. Bob ($100\%$) is the greatest threat.

- If Alice shoots at Bob and hits, Bob is out. Next is Charlie ($50\%$), who will shoot at Alice. Alice has a $50\%$ chance of being eliminated before getting another turn.
- If Alice shoots at Charlie and hits, Charlie is out. Next is Bob ($100\%$). Bob will shoot at Alice and hit with certainty. Alice dies ($0\%$ survival).
- If Alice misses on purpose, next is Charlie. Charlie will shoot at Bob (the biggest threat to Charlie). If Charlie hits, Bob is out, and it's Alice's turn again. If Charlie misses, it's Bob's turn. Bob will shoot at Charlie (the bigger threat than Alice). Bob hits, Charlie is out, and it's Alice's turn again.

By missing on purpose, Alice guarantees that Bob and Charlie will fight each other, ensuring Alice gets the first shot in the final 1-on-1 showdown.

**Answer:** Miss on purpose (c)

## Sources

- Brainstellar — https://brainstellar.com/ (Combinatorial games, Pirates, Truel)
- QuantQuestions — https://www.quantquestions.com/ (Dice market-making, expected value, adverse selection)
- TraderMath — https://www.tradermath.org/ (Dutch book, betting odds, market-making)
- "Fifty Challenging Problems in Probability" (Mosteller) — (Value of information, mixed strategies)
- "A Practical Guide to Quantitative Finance Interviews" (Xinfeng Zhou) — (Winner's curse, auctions, beauty contest)
