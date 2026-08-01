# Averages, Mixtures & Alligation

::: definition
**Core Formulas:**

- **Average (Mean):** $A = \frac{\text{Sum of observations}}{\text{Number of observations } (n)}$
- **Weighted Average:** For groups with sizes $n_1, n_2, \ldots$ and averages $A_1, A_2, \ldots$, the combined average is:
  $$A_w = \frac{n_1A_1 + n_2A_2 + \ldots}{n_1 + n_2 + \ldots}$$

- **Alligation Rule:** When mixing a cheaper quantity (price $c$) and a dearer quantity (price $d$) to produce a mixture of mean price $m$:
  $$\frac{\text{Quantity of cheaper}}{\text{Quantity of dearer}} = \frac{d - m}{m - c}$$

- **Repeated Replacement:** If a vessel contains $V$ units of pure liquid, and $r$ units are repeatedly replaced by water $n$ times, the final amount of pure liquid is:
  $$\text{Final amount} = V \left( 1 - \frac{r}{V} \right)^n$$
:::

## Averages

**Q1. Basic sum relation**
The average of 5 consecutive odd numbers is 27. What is the product of the first and the last number?
(a) 621  (b) 667  (c) 713  (d) 725

**Solution:**

::: keypoint
The average of any set of consecutive terms in an arithmetic progression is simply the middle term.
:::

Since 27 is the average of 5 consecutive odd numbers, it must be the middle (3rd) number.
The sequence is: $23, 25, 27, 29, 31$.
Product of first and last: $23 \times 31 = 713$.

**Answer:** 713 (c)

**Q2. Adding an element**
The average age of a class of 30 students is 14 years. When the teacher's age is included, the average increases by 1 year. What is the teacher's age?
(a) 31  (b) 44  (c) 45  (d) 50

**Solution:**

::: keypoint
New Value = Old Average + (Increase in Average $\times$ New Number of Elements)
:::

The new average is $14 + 1 = 15$.
The teacher brings 15 years for herself, plus she must "give" 1 year to each of the 30 students to raise their individual averages.
Teacher's age = $14 + (1 \times 31) = 45$.

**Answer:** 45 (c)

**Q3. Removing an element**
The average weight of 8 rowers in a boat is increased by $1.5\text{ kg}$ when one of the crew, who weighs $60\text{ kg}$, is replaced by a new man. Find the weight of the new man.
(a) $70\text{ kg}$  (b) $72\text{ kg}$  (c) $75\text{ kg}$  (d) $78\text{ kg}$

**Solution:**
The new man replaces the $60\text{ kg}$ man and provides an *additional* $1.5\text{ kg}$ to all 8 rowers (including himself).
Additional weight brought = $8 \times 1.5 = 12\text{ kg}$.
New man's weight = $60 + 12 = 72\text{ kg}$.

**Answer:** 72 kg (b)

**Q4. The "one wrong value corrected" trick**
The average marks of 40 students was calculated as 65. Later, it was discovered that a score of 83 was mistakenly read as 43. What is the correct average?
(a) 64  (b) 65.5  (c) 66  (d) 66.5

**Solution:**

::: keypoint
Don't recalculate the total sum. Find the net change and divide it across all $n$ items.
:::

Net change in sum = $+83 - 43 = +40$.
This increase of 40 marks must be distributed equally among the 40 students.
Change in average = $\frac{+40}{40} = +1$.
Correct average = $65 + 1 = 66$.

**Answer:** 66 (c)

**Q5. Average speed as weighted average**
A car travels from A to B at $40\text{ km/h}$ and returns from B to A at $60\text{ km/h}$. What is its average speed for the entire journey?
(a) $48\text{ km/h}$  (b) $50\text{ km/h}$  (c) $52\text{ km/h}$  (d) $55\text{ km/h}$

**Solution:**

::: trap
Average speed is NOT the arithmetic mean of the speeds ($\frac{40+60}{2} = 50$). Speed is weighted by *time*, not distance.
:::

For equal distances, average speed = $\frac{2xy}{x+y}$.
Average speed = $\frac{2(40)(60)}{40 + 60} = \frac{4800}{100} = 48\text{ km/h}$.

**Answer:** 48 km/h (a)

## Weighted Average & Alligation

**Q6. Mixing two groups (weighted average)**
A class has 20 boys and 30 girls. The average score of the boys is 75 and the average score of the girls is 85. What is the average score of the whole class?
(a) 79  (b) 80  (c) 81  (d) 82

**Solution:**
Use the weighted average formula. The ratio of boys to girls is $20:30 = 2:3$.
Weighted average = $\frac{(2 \times 75) + (3 \times 85)}{2 + 3} = \frac{150 + 255}{5} = \frac{405}{5} = 81$.

**Answer:** 81 (c)

**Q7. Finding a ratio given the mean (Alligation)**
In what ratio must a grocer mix two varieties of tea worth $\$60\text{/kg}$ and $\$65\text{/kg}$ so that by selling the mixture at $\$68.20\text{/kg}$ he may gain $10\%$?
(a) $3:2$  (b) $3:4$  (c) $4:5$  (d) $5:4$

**Solution:**

::: trap
Never apply alligation on the selling price! Alligation requires costs (or values) on the same basis. First, find the mean cost price (CP) of the mixture.
:::

Selling price (SP) = $\$68.20$, Profit = $10\%$.
Mean CP ($m$) = $\frac{\text{SP}}{1.1} = \frac{68.20}{1.1} = \$62$.
Set up alligation:
Cheaper ($c=60$) ........... Dearer ($d=65$)\
............... Mean ($m=62$) ...............\
$(65 - 62) = 3$ ............ $(62 - 60) = 2$

The required ratio of cheaper to dearer is $3:2$.

**Answer:** 3:2 (a)

**Q8. Concentration alligation**
A vessel contains a mixture of milk and water in the ratio $3:2$. Another vessel contains them in the ratio $4:5$. In what ratio should the two mixtures be mixed to get a new mixture containing equal quantities of milk and water?
(a) $2:3$  (b) $3:5$  (c) $5:4$  (d) $5:9$

**Solution:**

::: keypoint
Calculate the fraction of one component (e.g., milk) in each mixture and apply alligation on those fractions.
:::

Milk fraction in Vessel 1: $c = \frac{3}{3+2} = \frac{3}{5}$.
Milk fraction in Vessel 2: $d = \frac{4}{4+5} = \frac{4}{9}$.
Target milk fraction: $m = \frac{1}{2}$.
Alligation values:
Distance 1 ($d - m$): $\left|\frac{4}{9} - \frac{1}{2}\right| = \frac{1}{18}$
Distance 2 ($m - c$): $\left|\frac{3}{5} - \frac{1}{2}\right| = \frac{1}{10}$
Ratio of Vessel 1 to Vessel 2 = $\frac{1}{18} : \frac{1}{10} = 10 : 18 = 5:9$.

**Answer:** 5:9 (d)

**Q9. Removing and replacing (simple alligation concept)**
A beaker contains $40\text{ L}$ of pure alcohol. $8\text{ L}$ are removed and replaced with water. This process is done once. What is the ratio of alcohol to water now?
(a) $4:1$  (b) $3:1$  (c) $4:5$  (d) $5:1$

**Solution:**
Starting amount $V = 40$. We replace $8\text{ L}$.
Remaining alcohol = $40 - 8 = 32\text{ L}$.
Water added = $8\text{ L}$.
Ratio of alcohol to water = $32 : 8 = 4:1$.

**Answer:** 4:1 (a)

## Mixtures — Replacement

**Q10. Repeated replacement**
A container contains $50\text{ L}$ of milk. From this, $5\text{ L}$ of milk is taken out and replaced with water. This process is repeated 2 more times. How much milk is in the container now?
(a) $36.45\text{ L}$  (b) $38.25\text{ L}$  (c) $39\text{ L}$  (d) $40\text{ L}$

**Solution:**
The replacement happens a total of $n = 3$ times. Initial volume $V = 50$, replaced amount $r = 5$.
$\text{Final Milk} = V \left(1 - \frac{r}{V}\right)^n = 50 \left(1 - \frac{5}{50}\right)^3 = 50 \left(\frac{9}{10}\right)^3$.
$\text{Final Milk} = 50 \times 0.729 = 36.45\text{ L}$.

**Answer:** 36.45 L (a)

**Q11. Finding initial volume from final ratio**
A cask contains a mixture of wine and water. $8\text{ L}$ are drawn and replaced by water. This operation is performed 3 more times. The ratio of wine to water left is $16:65$. How much wine did the cask hold originally?
(a) $18\text{ L}$  (b) $24\text{ L}$  (c) $32\text{ L}$  (d) $42\text{ L}$

**Solution:**

::: keypoint
Use the ratio of (Final Wine) to (Total Volume) to solve for $V$.
:::

The ratio of wine to water is $16:65$, so the ratio of final wine to total volume is $16 : (16 + 65) = 16:81$.
Let the initial pure wine be $V$. Number of operations $n = 4$.
$\frac{\text{Final Wine}}{V} = \left(1 - \frac{8}{V}\right)^4 = \frac{16}{81}$
Taking the fourth root of both sides:
$1 - \frac{8}{V} = \frac{2}{3}$
$\frac{8}{V} = \frac{1}{3} \implies V = 24$.

**Answer:** 24 L (b)

**Q12. Replacement with a different concentration**
A tank contains $20\text{ L}$ of a $20\%$ acid solution. How much of the solution must be removed and replaced with a $50\%$ acid solution to yield a $30\%$ acid solution?
(a) $5.5\text{ L}$  (b) $6\text{ L}$  (c) $6.67\text{ L}$  (d) $7.5\text{ L}$

**Solution:**
We can use alligation on the remaining original solution and the newly added solution.
Component 1 (what remains): $20\%$ acid.
Component 2 (what is added): $50\%$ acid.
Target mixture: $30\%$ acid.
Alligation ratio:
(Added qty $50\%$) / (Remaining qty $20\%$) = $\frac{30 - 20}{50 - 30} = \frac{10}{20} = \frac{1}{2}$.
This means the mixture is 1 part $50\%$ solution and 2 parts $20\%$ solution.
Total parts = 3, representing the total $20\text{ L}$.
Amount to replace (the 1 part of $50\%$) = $\frac{1}{3} \times 20 = 6.67\text{ L}$.

**Answer:** 6.67 L (c)

## Multi-component Mixtures

**Q13. Three-way mix (Double Alligation)**
In what ratio must a grocer mix three kinds of tea costing $\$60\text{/kg}$, $\$75\text{/kg}$, and $\$100\text{/kg}$ so that the resultant mixture is worth $\$80\text{/kg}$?
(a) $1 : 4 : 2$  (b) $1 : 4 : 5$  (c) $4 : 5 : 4$  (d) $1 : 4 : 4$

**Solution:**

::: heavy
For three components, form an equation around the mean, or apply alligation to pairs that bracket the mean and sum the common component.
:::

Let the quantities be $x, y, z$.
Total value = $60x + 75y + 100z = 80(x + y + z)$.
Rearranging: $20z = 20x + 5y \implies 4z = 4x + y$.
Test the options for $(x, y, z)$ to see which satisfies this relation:
(a) $x=1, y=4, z=2 \implies 4(2) = 4(1) + 4 \implies 8 = 8$. (Matches!)
(b) $x=1, y=4, z=5 \implies 4(5) = 4(1) + 4 \implies 20 \neq 8$.
Thus, $1 : 4 : 2$ is a valid ratio.

**Answer:** 1:4:2 (a)

**Q14. Selling a mixture at a profit**
A man buys two types of rice at $\$35\text{/kg}$ and $\$45\text{/kg}$. He mixes them in the ratio $2:3$ respectively. At what price per kg should he sell the mixture to make a $20\%$ profit?
(a) $\$48\text{/kg}$  (b) $\$49.20\text{/kg}$  (c) $\$50.40\text{/kg}$  (d) $\$51\text{/kg}$

**Solution:**
First, find the mean cost price using weighted average.
Mean CP = $\frac{(2 \times 35) + (3 \times 45)}{2 + 3} = \frac{70 + 135}{5} = \frac{205}{5} = \$41\text{/kg}$.
To make a $20\%$ profit, Selling Price = CP $\times 1.20$.
Selling Price = $41 \times 1.2 = \$49.20\text{/kg}$.

**Answer:** $49.20$ (b)

## Wrapped OA Variants

**Q15. The "alloy composition" word problem**
A metallurgist has two alloys of gold and copper. Alloy A contains gold and copper in the ratio $7:2$, and Alloy B contains them in the ratio $7:11$. If she wants to melt them together to form a new $70\text{ kg}$ alloy with equal amounts of gold and copper, how many kilograms of Alloy B must she use?
(a) $20\text{ kg}$  (b) $40\text{ kg}$  (c) $50\text{ kg}$  (d) $60\text{ kg}$

**Solution:**

::: interview
Wordy OA problems often just disguise a basic alligation. Find the fraction of gold in each alloy and target a $1/2$ fraction.
:::

Gold fraction in A: $\frac{7}{9} = \frac{14}{18}$.
Gold fraction in B: $\frac{7}{18}$.
Target gold fraction: $\frac{1}{2} = \frac{9}{18}$.
Using alligation (distances to the mean):
Ratio of A to B = $\left| \frac{7}{18} - \frac{9}{18} \right| : \left| \frac{14}{18} - \frac{9}{18} \right| = \frac{2}{18} : \frac{5}{18} = 2:5$.
The mixture requires 2 parts of A for every 5 parts of B (Total = 7 parts).
If 7 parts = $70\text{ kg}$, then 5 parts (Alloy B) = $50\text{ kg}$.

**Answer:** 50 kg (c)

**Q16. The "fraudulent blending" variant**
A coffee shop blends a cheap robusta bean ($\$12\text{/kg}$) with a premium arabica bean ($\$28\text{/kg}$). The shop owner claims he sells the blend at cost, which he advertises as $\$20\text{/kg}$. However, he secretly replaces $25\%$ of the arabica required for that fair blend with the cheap robusta. What is his actual cost price for this fraudulent blend?
(a) $\$16\text{/kg}$  (b) $\$17\text{/kg}$  (c) $\$18\text{/kg}$  (d) $\$19\text{/kg}$

**Solution:**
First, find the intended "fair" ratio for a $\$20$ mean price using alligation:
Cheaper (12) ........... Dearer (28)\
............... Mean (20) ...............\
$(28 - 20) = 8$ ............ $(20 - 12) = 8$

Intended ratio is $8:8 = 1:1$. So the blend should be $50\%$ robusta, $50\%$ arabica.
He replaces $25\%$ of the *arabica required* with robusta.
Arabica required = $50\%$ of the total. $25\%$ of this is $12.5\%$.
Actual arabica = $50\% - 12.5\% = 37.5\% = \frac{3}{8}$ of the blend.
Actual robusta = $50\% + 12.5\% = 62.5\% = \frac{5}{8}$ of the blend.
Actual cost price = $\frac{5}{8}(12) + \frac{3}{8}(28) = 7.5 + 10.5 = \$18\text{/kg}$.

**Answer:** $18$ (c)

## Sources

- IndiaBix — https://www.indiabix.com/aptitude/alligation-or-mixture/
- CareerBless — http://www.careerbless.com/aptitude/qa/home.php
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- Hitbullseye — https://www.hitbullseye.com/
