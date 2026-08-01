# Classic Brain Teasers & Puzzles

::: interview
In quant and tech interviews, the answer to a brain teaser matters less than *how you think*. Interviewers want to hear you narrate the invariants you spot, your base-case testing, and your logical deductions. Always speak your thoughts out loud.

:::

::: keypoint
**The Puzzle-Solver's Toolkit**

- **Invariants & Parity:** Look for things that never change (e.g., odd/even counts, total mass, total time).
- **Work Backwards:** Start from the desired end state and reverse the operations.
- **Extreme / Edge Cases:** What happens with $1$ item? What happens with $0$ or $\infty$?
- **Symmetry:** Assume a symmetric solution unless forced otherwise.
- **Reframe Information:** In weighing/testing puzzles, think about how much *information* (in bits or base-$3$ states) each test provides, rather than just the items themselves.

:::

## Weighing & measuring

**Q1.** You have $9$ identical-looking balls. One is heavier than the rest. Using a balance scale, what is the minimum number of weighings required to identify the heavy ball?

**Solution:** Break the items into groups of $3$. 
Weighing 1: Compare $3$ balls vs $3$ balls (leave $3$ aside). If they balance, the heavy ball is in the unweighed $3$. If one side is heavier, the heavy ball is in that group of $3$.
Weighing 2: Take the heavy group of $3$. Compare $1$ ball vs $1$ ball (leave $1$ aside). The heavy side is the ball, or if balanced, the unweighed ball is the one.

::: keypoint
A balance scale has $3$ states (left down, right down, balanced). Thus, $k$ weighings can distinguish up to $3^k$ states. For $9$ items, $3^2 = 9$, so $2$ weighings are mathematically optimal.

:::

**Answer:** $2$ weighings.

**Q2.** You have $12$ identical-looking balls. Exactly one is fake and is either strictly lighter or strictly heavier than the rest. You have a balance scale. How can you find the fake ball and determine if it is heavier or lighter in exactly $3$ weighings?

**Solution:** Label the balls $1$ through $12$. Divide them into three groups of four: $A = \{1, 2, 3, 4\}$, $B = \{5, 6, 7, 8\}$, $C = \{9, 10, 11, 12\}$.
Weighing 1: Weigh $A$ against $B$.
*Case 1: $A = B$ (Balanced).* The fake is in $C$. Weigh $9, 10, 11$ against three known good balls (e.g., $1, 2, 3$). If they balance, ball $12$ is the fake; weigh it against ball $1$ to see if it is heavy or light. If $9, 10, 11$ is heavier (or lighter), the fake is among them and is heavy (or light); weigh $9$ vs $10$ to find it.
*Case 2: $A > B$ (Unbalanced, $A$ is heavy or $B$ is light).* The fake is in $A$ (and heavy) or $B$ (and light). $C$ is known good.
Weighing 2: Weigh $\{1, 2, 5\}$ against $\{3, 6, 9\}$ (putting two from $A$ and one from $B$ on left, one from $A$ and one from $B$ and one good on right).

- If $\{1, 2, 5\} = \{3, 6, 9\}$, the fake is in the unweighed $\{4, 7, 8\}$. Since $A>B$ initially, either $4$ is heavy or $7, 8$ are light. Weigh $7$ vs $8$.
- If $\{1, 2, 5\} > \{3, 6, 9\}$, the fake is either $1, 2$ (heavy) or $6$ (light). Weigh $1$ vs $2$.
- If $\{1, 2, 5\} < \{3, 6, 9\}$, the fake is either $5$ (light) or $3$ (heavy). Weigh $5$ against a good ball (or just weigh $3$ against a good ball).

**Answer:** $3$ weighings (using the $4$-$4$-$4$ split scheme).

**Q3.** You have $10$ stacks of coins, each containing $10$ coins. Nine stacks consist of real coins weighing $10$ g each. One stack consists of fake coins weighing $11$ g each. You have a digital scale (not a balance scale) that reads exact weights. What is the minimum number of weighings needed to identify the fake stack?

**Solution:** You need a single weighing by encoding the stack number into the number of coins taken. Take $1$ coin from stack $1$, $2$ coins from stack $2$, $\dots$, and $10$ coins from stack $10$.
Total coins = $55$. If all were real, the weight would be $550$ g.
Since the fake coins weigh $1$ g more, the excess weight directly indicates the stack. If the scale reads $554$ g, the excess is $4$ g, meaning $4$ fake coins were included, so stack $4$ is fake.

**Answer:** $1$ weighing.

**Q4.** You have a $3$-liter jug and a $5$-liter jug, and an unlimited supply of water. How can you measure exactly $4$ liters of water?

**Solution:**

1. Fill the $5$-liter jug.
2. Pour from the $5$-liter jug into the $3$-liter jug until it is full. (The $5$-liter jug now has $2$ liters).
3. Empty the $3$-liter jug.
4. Pour the $2$ liters from the $5$-liter jug into the $3$-liter jug. (The $3$-liter jug now has $2$ liters, with $1$ liter of space left).
5. Fill the $5$-liter jug again.
6. Pour from the $5$-liter jug into the $3$-liter jug until it is full (this takes exactly $1$ liter).
7. The $5$-liter jug now holds exactly $4$ liters.

**Answer:** Fill $5$, pour to $3$, empty $3$, pour remaining $2$ to $3$, fill $5$, top off $3$. $4$ liters remain in the $5$-liter jug.

**Q5.** You have two empty jugs, a $3$-liter jug and a $5$-liter jug. Can you measure exactly $1$ liter using only these jugs and an infinite water supply?

**Solution:** Yes. Fill the $3$-liter jug. Pour it into the $5$-liter jug. The $5$-liter jug now has $3$ liters.
Fill the $3$-liter jug again. Pour it into the $5$-liter jug until the $5$-liter jug is full. This takes $2$ liters from the $3$-liter jug.
The $3$-liter jug now contains exactly $1$ liter.

**Answer:** Fill $3$, pour into $5$. Fill $3$ again, pour into $5$ until full. $1$ liter remains in the $3$-liter jug.

## Crossing / transport

**Q6.** Four people need to cross a rickety bridge at night. They have one flashlight. The bridge can hold at most two people at a time, and they must carry the flashlight. The flashlight must be walked back (it cannot be thrown). The four people take $1$, $2$, $5$, and $10$ minutes respectively to cross. When two people cross, they move at the slower person's pace. What is the minimum time for all four to cross?

**Solution:** The common mistake is sending the fastest person ($1$) back every time.
Instead, send the two slowest ($5$ and $10$) together so their slow times overlap, and use the two fastest ($1$ and $2$) to shuttle the flashlight.

1. $1$ and $2$ cross together: $2$ mins. (Elapsed: $2$)
2. $1$ returns with the flashlight: $1$ min. (Elapsed: $3$)
3. $5$ and $10$ cross together: $10$ mins. (Elapsed: $13$)
4. $2$ returns with the flashlight: $2$ mins. (Elapsed: $15$)
5. $1$ and $2$ cross together: $2$ mins. (Elapsed: $17$)

**Answer:** $17$ minutes.

**Q7.** A farmer has a fox, a goose, and a bag of beans. He must cross a river in a boat that can only hold himself and one item. If left unattended together, the fox will eat the goose, or the goose will eat the beans. How does he get everything across?

**Solution:** The goose is the bottleneck (it conflicts with both).

1. Take the goose across (leaving fox and beans safe).
2. Return alone.
3. Take the fox across.
4. Return with the goose (leaving the fox alone).
5. Take the beans across (leaving the goose on the starting side).
6. Return alone.
7. Take the goose across.

**Answer:** Seven trips; the key insight is bringing the goose back on the middle return trip.

## Rope / time

**Q8.** You have two ropes. Each rope takes exactly $60$ minutes to burn completely, but they burn at irregular rates (e.g., half a rope might burn in $10$ minutes and the other half in $50$ minutes). You have a lighter. How can you measure exactly $45$ minutes?

**Solution:** Since they burn irregularly, you cannot measure time by length. However, if you light a rope from *both* ends simultaneously, it will burn out in exactly $30$ minutes, regardless of the irregularity.

1. Light Rope A from both ends, and Rope B from one end.
2. When Rope A finishes burning, exactly $30$ minutes have passed. Rope B has $30$ minutes of burn time left.
3. At that exact moment, light the other end of Rope B.
4. Rope B will now burn twice as fast, taking $15$ minutes to finish its remainder.
Total time = $30 + 15 = 45$ minutes.

**Answer:** Light one rope from both ends and the other from one end; when the first finishes, light the unlit end of the second.

**Q9.** You have a $7$-minute hourglass and an $11$-minute hourglass. How can you boil an egg for exactly $15$ minutes?

**Solution:**
Start both hourglasses simultaneously as you drop the egg in the boiling water.
When the $7$-minute hourglass runs out, flip it immediately. ($7$ mins elapsed)
When the $11$-minute hourglass runs out, the $7$-minute hourglass has been running for $4$ minutes (since the first flip).
At this exact moment ($11$ mins elapsed), flip the $7$-minute hourglass again. Since the sand ran for $4$ minutes, it will take exactly $4$ minutes to flow back.
Total time = $11 + 4 = 15$ minutes.

**Answer:** Start both; when $7$ ends, flip $7$; when $11$ ends, flip $7$ again to time the remaining $4$ minutes.

## Logic & hats

**Q10.** Three prisoners are in a room. The warden places a hat on each person's head. The hats are drawn from a pool of $2$ black hats and $3$ white hats. Each person can see the others' hats but not their own. The warden asks them one by one if they know their hat color.
Prisoner A says "No."
Prisoner B says "No."
Prisoner C says "Yes, my hat is white."
Assuming all are perfectly logical, how did C know?

**Solution:** Work backwards from the available information.
If C and B both had black hats, A would have seen two black hats. Since there are only two black hats, A would have immediately known their own hat was white. A said "No", so B and C cannot *both* have black hats.
Now consider B. B knows that B and C cannot both have black hats. If C had a black hat, B would know that B's own hat must be white. B said "No", which means B did not see a black hat on C.
Therefore, C's hat cannot be black. C deduces their hat must be white.

**Answer:** C deduces that if they had a black hat, B would have figured out their own hat color after A passed.

**Q11.** Ten prisoners are standing in a single file line, facing forward. The warden places a black or white hat on each prisoner. They can only see the hats of the people in front of them. Starting from the back of the line, the warden asks each prisoner their hat color. If they guess wrong, they are executed. They can only say "Black" or "White". What strategy saves the most prisoners?

**Solution:** The prisoners can agree on a parity code beforehand.
The person at the back (who sees $9$ hats) counts the number of Black hats in front of them.

- If the number of Black hats is EVEN, they say "Black".
- If the number of Black hats is ODD, they say "White".
This first prisoner has a $50\%$ chance of surviving, as their guess is just a signal.
The $9$th prisoner hears the parity of the remaining $9$ hats. By looking at the $8$ hats in front of them, they can deduce their own hat color. For example, if the parity was EVEN, and they see an ODD number of Black hats, their own hat must be Black to make the total EVEN.
Each subsequent prisoner keeps track of the parity based on the initial signal and the answers of the prisoners behind them.

::: keypoint
Parity is the ultimate invariant for binary states. Using one person's guess to encode the parity of a sequence allows all subsequent people to deduce their exact state perfectly.

:::

**Answer:** The first person encodes the parity of black hats (even = Black, odd = White), saving $9$ prisoners deterministically and the first with $50\%$ probability.

**Q12.** You are blindfolded and placed at a table with $100$ coins. You are told that exactly $10$ coins are showing heads, and $90$ are showing tails. You cannot feel or see which side is up. How can you divide the coins into two piles such that both piles have the *exact same number* of heads?

**Solution:** Count out $10$ coins into a new Pile A, leaving $90$ coins in Pile B.
Currently, Pile A has $h$ heads (where $0 \le h \le 10$). Pile B must therefore have $10 - h$ heads.
Now, flip *every* coin in Pile A over.
Since Pile A originally had $h$ heads and $10 - h$ tails, flipping every coin turns the $10 - h$ tails into heads.
Pile A now has $10 - h$ heads. Pile B also has $10 - h$ heads.

**Answer:** Take $10$ coins at random to form a second pile, then flip all $10$ coins in that new pile.

**Q13.** There are $100$ prisoners numbered $1$ to $100$. A room contains $100$ boxes, each containing a slip of paper with a prisoner's number on it (randomly distributed). Each prisoner may enter the room and open up to $50$ boxes to find their own number. They must leave the room exactly as they found it and cannot communicate with others afterward. If *every* prisoner finds their number, they all go free; if even one fails, they all die. If they pick boxes uniformly at random, the survival probability is $(1/2)^{100} \approx 0$. What is the strategy that gives them a $\approx 31\%$ chance of survival?

**Solution:** The strategy relies on cycle decomposition of permutations.

1. Prisoner $k$ goes to box $k$ and opens it.
2. They look at the number inside (let's say it's $m$).
3. If $m = k$, they are done. Otherwise, they go to box $m$ and open it.
4. They repeat this process, following the chain of numbers until they find their own number or open $50$ boxes.
Because the boxes contain a permutation of $1$ to $100$, following this chain guarantees the prisoner is traversing a closed cycle. Since they start at the box corresponding to their own number, their number *must* be in the cycle they are currently traversing.
The prisoners win if and only if the random permutation contains no cycle longer than $50$. The probability that a random permutation of $100$ elements has no cycle longer than $50$ is $1 - \sum_{k=51}^{100} \frac{1}{k} \approx 0.311$.

::: interview
Do not try to derive the exact $31\%$ in your head. Explain the cycle-following mechanism clearly and state that success hinges entirely on the absence of a cycle length $> 50$.

:::

**Answer:** Follow the cycle: open the box with your number, then the box of the number found inside, etc. They win if no cycle exceeds length $50$ ($\approx 31\%$ chance).

**Q14.** You are outside a closed room. There are three light switches outside, all currently off. Inside the room, there are three incandescent light bulbs, each connected to one of the switches. You cannot see inside the room. You are allowed to manipulate the switches however you like, but you can only enter the room *once*. How do you determine which switch controls which bulb?

**Solution:** A simple on/off state only gives $2$ states, but you need to distinguish $3$ bulbs. You need a third state. For incandescent bulbs, this state is *heat*.

1. Turn on Switch 1 and leave it on for $5$ minutes (it gets hot).
2. Turn off Switch 1 and immediately turn on Switch 2.
3. Leave Switch 3 off.
4. Enter the room.

- The bulb that is ON is controlled by Switch 2.
- The bulb that is OFF and HOT is controlled by Switch 1.
- The bulb that is OFF and COLD is controlled by Switch 3.

**Answer:** Use heat as a third state: leave one switch on for a while, turn it off, turn another on, and immediately check the bulbs for light and temperature.

## Pouring / division / fair-split

**Q15.** You have a circular cake. You must cut it into exactly $8$ equal pieces using only $3$ straight cuts. How do you do it?

**Solution:**
Two cuts are made vertically (in the shape of a cross or an X) from the top, dividing the cake into $4$ equal wedges.
The third cut is made horizontally through the middle of the cake (parallel to the table), slicing all $4$ wedges in half to create $8$ equal pieces.

**Answer:** Two vertical cuts forming an 'X', and one horizontal slice through the equator of the cake.

**Q16.** You have a gold bar that is pre-scored into $7$ equal segments. You must pay a worker one segment of gold per day for $7$ consecutive days. You are only allowed to make exactly $2$ straight cuts in the gold bar. Where do you make the cuts so you can pay the worker exactly one segment each day (assuming you can make change with the pieces you've already given them)?

**Solution:** You need pieces that can sum to any value from $1$ to $7$. Binary representation is optimal here.
Cut the bar to create three pieces of length $1$, $2$, and $4$. This requires two cuts (at the $1/7$ mark and the $3/7$ mark).

- Day 1: Give piece $1$.
- Day 2: Give piece $2$, take back piece $1$.
- Day 3: Give piece $1$ (worker has $1$ and $2$).
- Day 4: Give piece $4$, take back $1$ and $2$.
- Day 5: Give piece $1$ (worker has $4$ and $1$).
- Day 6: Give piece $2$, take back $1$ (worker has $4$ and $2$).
- Day 7: Give piece $1$ (worker has $4, 2, 1$).

::: keypoint
When making change or measuring continuous amounts efficiently, powers of two (binary encoding) provide the optimal split strategy.

:::

**Answer:** Make cuts to yield pieces of size $1$, $2$, and $4$. Use them to make change in binary.

**Q17.** Two people want to share a cake fairly, such that neither person feels cheated. What is the classic algorithm?

**Solution:** The "Divide and Choose" protocol.
Person A cuts the cake into two pieces that they believe are perfectly equal.
Person B chooses which piece they want. Person A takes the remaining piece.
This ensures Person A cuts fairly (otherwise they get the smaller piece), and Person B gets their preferred piece.

**Answer:** One person cuts, the other person chooses.

**Q18.** Three people want to share a cake fairly. How can this be done using a moving knife?

**Solution:** A neutral party (or one of the three) slowly moves a knife over the cake from left to right.
As soon as any of the three people believes the piece to the left of the knife is exactly $1/3$ of the cake, they yell "Cut!"
That person receives the piece. They are satisfied because they got what they believe is $1/3$.
The remaining two people now have a cake they both believe is at least $2/3$. They use the "One cuts, the other chooses" method (from Q17) to split the remainder.

**Answer:** Move a knife across the cake; the first person to yell "Cut!" gets that piece, and the remaining two split the rest using "I cut, you choose."

## Number & grid teasers

**Q19.** There are $100$ closed lockers in a hallway. A hundred students walk down the hall.
The first student opens every locker.
The second student closes every $2$nd locker ($2, 4, 6, \dots$).
The third student changes the state of every $3$rd locker (opens it if closed, closes it if open).
This continues until the $100$th student changes the state of the $100$th locker. Which lockers remain open at the end?

**Solution:** A locker's state is changed by every student whose number is a divisor of the locker's number.
Locker $n$ is toggled $d(n)$ times, where $d(n)$ is the number of divisors of $n$.
All lockers start closed. A locker ends up open if and only if it is toggled an ODD number of times.
A number has an odd number of divisors if and only if it is a perfect square (since divisors normally come in pairs like $a \times b = n$, but for squares, $\sqrt{n} \times \sqrt{n} = n$ adds only one unique divisor).
The perfect squares between $1$ and $100$ are $1, 4, 9, 16, 25, 36, 49, 64, 81$, and $100$.

**Answer:** The perfect square lockers: $1, 4, 9, 16, 25, 36, 49, 64, 81, 100$.

**Q20.** A king has $1000$ bottles of wine. He knows that exactly one bottle is poisoned. The poison takes exactly $24$ hours to kill anyone who drinks it. The king has $10$ prisoners whom he can use as taste testers. How can he identify the poisoned bottle in exactly $24$ hours?

**Solution:** You have $10$ prisoners, each can either live or die ($2$ states). This can be used to represent a binary number. $2^{10} = 1024$, which is enough to encode all $1000$ bottles.

1. Number the bottles from $1$ to $1000$.
2. Write the number of each bottle in binary (e.g., bottle $1$ is $0000000001$, bottle $2$ is $0000000010$, ..., bottle $1000$ is $1111101000$).
3. Line up the $10$ prisoners and assign each a bit position from $0$ to $9$.
4. For each bottle, if its binary representation has a `1` in the $k$-th position, give a drop of that wine to prisoner $k$.
5. Wait $24$ hours. The pattern of dead prisoners forms the exact binary number of the poisoned bottle (e.g., if prisoners $0$ and $2$ die, the poisoned bottle is $101_2 = 5$).

::: keypoint
Whenever testing multiple items simultaneously with testers that yield binary outcomes (dead/alive, positive/negative), represent the items in binary and map testers to bit positions.

:::

**Answer:** Number bottles in binary. Each prisoner represents a bit and drinks from all bottles having a `1` in their bit position. The dead prisoners yield the binary number of the poisoned bottle.

**Q21.** Three ants are placed at the three corners of an equilateral triangle. Each ant randomly chooses a direction (clockwise or counter-clockwise) and starts walking along the edge of the triangle at the same speed. What is the probability that no two ants collide?

**Solution:** The ants will avoid a collision if and only if they all walk in the same direction.
There are $2$ such scenarios: all three walk clockwise, or all three walk counter-clockwise.
Each ant has $2$ choices, so there are $2^3 = 8$ total possible combinations of directions.
The probability of no collision is the number of safe scenarios divided by the total number of scenarios.
$P(\text{no collision}) = \frac{2}{8} = \frac{1}{4}$.

**Answer:** $\frac{1}{4}$ (or $25\%$).

**Q22.** $100$ ants are placed on a $1$-meter long rod. They walk at a constant speed of $1$ cm/s. When two ants collide, they instantly bounce off each other and reverse directions. When an ant reaches the end of the rod, it falls off. What is the maximum possible time before all ants have fallen off the rod?

**Solution:** The bounce is a distraction. Since all ants are identical and walk at the same speed, when two ants collide and reverse directions, it is macroscopically identical to the ants *passing through* each other.
If we imagine them passing through each other, the longest possible time an ant can remain on the rod is the time it takes for an ant starting at one extreme end to walk all the way to the other end.
The rod is $100$ cm long. Walking at $1$ cm/s, the maximum distance is $100$ cm, taking $100$ seconds.

::: keypoint
When identical objects collide and swap velocities elastically, treat them as passing through one another. This "ghosting" invariant simplifies complex bounce problems.

:::

**Answer:** $100$ seconds.

## Spatial, Invariant & Optimization Puzzles

**Q23.** An ant sits at one corner of a solid cube of edge $s$ and must crawl along the **surface** to the
diagonally opposite corner. What is the length of the shortest path?

(a) $3s$ (b) $s\sqrt{3}$ (c) $s\sqrt{5}$ (d) $s(1+\sqrt{2})$

![Unfolding the two faces of a cube turns the surface path into a straight-line diagonal of a rectangle](figs/s31_ant_cube.png)

**Solution:** The ant cannot pass through the interior, so **unfold** the two faces it crosses into one flat
plane. The two adjacent faces become a $2s \times s$ rectangle, and the start and end corners become opposite
corners of that rectangle. The shortest path in a plane is the straight line: $\sqrt{(2s)^2 + s^2} = \sqrt{5s^2}
= s\sqrt{5} \approx 2.236\,s$. This beats crawling along edges ($3s$) and the naive over-one-fold route
($s + s\sqrt{2} \approx 2.414\,s$). Note $s\sqrt{3}$ is the straight distance *through* the cube — a path the ant
is not allowed to take.

**Answer:** $s\sqrt{5}$ (c)

::: keypoint
For a shortest path over the surface of a box, **unfold** the faces flat and draw a straight line. On a box with
unequal sides, try each way of unfolding and take the smallest straight-line distance — the naive unfolding is
not always the shortest.

:::

**Q24.** A trader has $3000$ bananas and one camel. The camel carries at most $1000$ bananas at a time and eats
$1$ banana for every kilometre it walks (in either direction). The market is $1000$ km away. What is the greatest
number of bananas that can be delivered?

(a) $500$ (b) $533$ (c) $667$ (d) $833$

**Solution:** With $3000$ bananas the camel needs $3$ loads, so moving the whole stock forward $1$ km costs
$3$ trips forward $+ 2$ back $= 5$ bananas per km. Run this until the stock drops to $2000$: that loses $1000$
bananas at $5$/km $\Rightarrow 200$ km covered. Now $2$ loads: $2$ forward $+ 1$ back $= 3$ bananas/km until the
stock drops to $1000$: another $1000$ bananas at $3$/km $\Rightarrow 333\tfrac13$ km (total $533\tfrac13$ km).
Now a single load of $1000$: $1$ banana/km straight to the market over the remaining $1000 - 533\tfrac13 =
466\tfrac23$ km, arriving with $1000 - 466\tfrac23 = 533\tfrac13$. So **$533$** bananas.

**Answer:** $533$ (b)

::: keypoint
Segment the journey by how many loads remain: the per-km cost is $2k-1$ bananas while $k$ loads are needed
(because of the return trips). Change segment exactly when a full load is used up.

:::

**Q25.** Every islander is a perfect logician who can see everyone's eye colour but their own, and never discusses
eyes. The rule: anyone who deduces they have blue eyes must leave that midnight. A visitor announces, "At least
one of you has blue eyes." If exactly $n$ islanders have blue eyes, what happens?

(a) Nothing — they already knew (b) Only one leaves, on night $1$ (c) All $n$ leave on night $n$ (d) They leave one per night forever

**Solution:** Induct on $n$. If $n=1$, the lone blue-eyed islander sees no other blue eyes, so the announcement
must refer to them — they leave on night $1$. If $n=2$, each blue-eyed islander sees exactly one other and
reasons: "if I am not blue-eyed, that person is the only one and leaves night $1$." When night $1$ passes with
nobody leaving, each concludes they too are blue-eyed — both leave on night $2$. In general, once $n-1$ nights
pass with no departure, each of the $n$ deduces they are the $n$-th, and all leave on **night $n$**. The
announcement looks redundant (everyone can already see a blue-eyed person), but it creates **common knowledge**,
which is what lets the induction begin.

**Answer:** All $n$ leave on the $n$-th night (c)

**Q26.** You have $2$ identical eggs and a $100$-floor building. There is a floor $X$ at or above which an egg
breaks when dropped, and below which it survives (same for both eggs). What is the minimum number of drops that
**guarantees** finding $X$ in the worst case?

(a) $7$ (b) $10$ (c) $14$ (d) $50$

**Solution:** With only $2$ eggs you cannot binary-search: once the first egg breaks you must test the remaining
range one floor at a time with the last egg. Drop the first egg at floors spaced so that each break leaves just
enough single-step tests to keep the worst case constant: first at floor $d$, then $d+(d-1)$, then
$d+(d-1)+(d-2)$, … The worst case is $d$ drops when $d + (d-1) + \cdots + 1 = \tfrac{d(d+1)}{2} \ge 100$. Since
$\tfrac{13\cdot 14}{2} = 91 < 100$ and $\tfrac{14\cdot 15}{2} = 105 \ge 100$, the minimum is $d = 14$ (start at
floor $14$, then $27$, then $39$, …).

**Answer:** $14$ (c)

**Q27.** The two diagonally opposite corner squares are cut from an $8\times 8$ chessboard, leaving $62$ squares.
Can it be tiled exactly by $31$ dominoes, each covering two edge-adjacent squares?

(a) Yes (b) No (c) Only if rotations are allowed (d) Only for a $6\times 6$ board

**Solution:** Colour the board in the usual alternating pattern. Every domino covers exactly **one black and one
white** square. The two diagonally opposite corners are the **same** colour, so removing them leaves, say, $32$
black and $30$ white squares. A valid tiling needs equal black and white ($31$ each), but the counts differ by
$2$. Therefore no tiling exists.

**Answer:** No (b)

::: keypoint
When asked whether something *can* be done, hunt for an **invariant** — a quantity every allowed move preserves
(here, each domino keeps black − white $= 0$). If the goal violates the invariant, it is impossible, and you have
a one-line proof.

:::

## Sources

- Brainstellar — https://brainstellar.com/
- Hitbullseye — https://www.hitbullseye.com/
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- InterviewQuery — https://www.interviewquery.com/
