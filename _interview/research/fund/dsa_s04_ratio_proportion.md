# Ratio, Proportion & Variation

::: definition
**Core Formulas & Techniques**

- **Ratio & Combining**: A ratio compares two quantities as $a:b$ or $\frac{a}{b}$. To combine $A:B$ and $B:C$, find the LCM of the $B$ terms, or cross-multiply to form $A:B:C$.
- **Proportion**: An equality $a:b = c:d$. The product of extremes equals the product of means ($ad = bc$).
- **Mean Proportional**: For $a$ and $c$, the mean proportional is $b = \sqrt{ac}$. 
- **Third Proportional**: For $a$ and $b$, it is $c$ such that $a:b = b:c$.
- **Fourth Proportional**: For $a, b, c$, it is $d$ such that $a:b = c:d$.
- **Continued Proportion**: Quantities $a, b, c, d$ are in continued proportion if $a:b = b:c = c:d$.
- **Direct vs Inverse Variation**: 
  - Direct: $y$ varies as $x$ ($y \propto x$) means $y = kx$.
  - Inverse: $y$ varies inversely as $x$ ($y \propto \frac{1}{x}$) means $xy = k$.
- **Componendo–Dividendo**: A powerful algebraic speed tool. If $\frac{a}{b} = \frac{c}{d}$, then $\frac{a+b}{a-b} = \frac{c+d}{c-d}$.
:::

## 1. Ratio manipulation

**Q1.** The ratio of two numbers is $3:4$. If $5$ is added to each number, the new ratio becomes $4:5$. Find the smaller number.
(a) $12$ (b) $15$ (c) $18$ (d) $20$

**Solution:**
Let the numbers be $3x$ and $4x$. 
Notice that the ratio parts increase from $3 \to 4$ and $4 \to 5$. The increase is exactly $1$ unit for both numbers, which corresponds to the equal addition of $5$.
So, $1 \text{ unit} = 5$.
The smaller number is $3 \text{ units} = 3 \times 5 = 15$.

**Answer:** 15 (b)

**Q2.** If $A:B = 2:3$, $B:C = 4:5$, and $C:D = 6:7$, what is $A:B:C:D$?
(a) $16:24:30:35$ (b) $12:20:25:35$ (c) $16:22:30:35$ (d) $18:24:30:35$

**Solution:**
Write them stacked and multiply across branches:
$$
\begin{matrix}
A & & B & & C & & D \\
2 & : & 3 & & & & \\
  &   & 4 & : & 5 & & \\
  &   &   &   & 6 & : & 7
\end{matrix}
$$
$A = 2 \times 4 \times 6 = 48$
$B = 3 \times 4 \times 6 = 72$
$C = 3 \times 5 \times 6 = 90$
$D = 3 \times 5 \times 7 = 105$
$A:B:C:D = 48:72:90:105$. Dividing by $3$, we get $16:24:30:35$.

**Answer:** 16:24:30:35 (a)

::: keypoint
**Fast Combining:** For $A:B$, $B:C$, $C:D$, calculate $A$ by multiplying all first terms, and $D$ by multiplying all second terms. Then deduce $B$ and $C$ proportionally from $A$ and $D$.
:::

**Q3.** An amount of $\$ 2,420$ is divided among $P, Q,$ and $R$ such that $P$'s share to $Q$'s share is $5:4$, and $Q$'s share to $R$'s share is $9:10$. What is $R$'s share?
(a) $\$ 700$ (b) $\$ 800$ (c) $\$ 900$ (d) $\$ 1,000$

**Solution:**
First, combine the ratios $P:Q = 5:4$ and $Q:R = 9:10$.
Multiply the first by $9$ and the second by $4$ to equalize the shared term $Q$:
$P:Q:R = (5 \times 9) : (4 \times 9) : (4 \times 10) = 45:36:40$.
The sum of the ratio parts is $45 + 36 + 40 = 121$.
$R$'s share is $\frac{40}{121} \times 2420 = 40 \times 20 = 800$.

**Answer:** 800 (b)

**Q4.** If $\frac{x}{y} = \frac{3}{4}$, find the value of $\frac{3y + 2x}{3y - 2x}$.
(a) $\frac{18}{7}$ (b) $3$ (c) $\frac{18}{5}$ (d) $4$

**Solution:**
**Method 1 (Substitution):** Since the expression is homogeneous, simply substitute $x = 3$ and $y = 4$.
Result $= \frac{3(4) + 2(3)}{3(4) - 2(3)} = \frac{12 + 6}{12 - 6} = \frac{18}{6} = 3$.

**Method 2 (Componendo-Dividendo):** First isolate the ratio terms in the expression: $\frac{y}{x} = \frac{4}{3} \implies \frac{3y}{2x} = \frac{3 \times 4}{2 \times 3} = \frac{12}{6} = \frac{2}{1}$.
Apply componendo-dividendo ($\frac{a+b}{a-b}$): $\frac{3y+2x}{3y-2x} = \frac{2+1}{2-1} = \frac{3}{1} = 3$.

**Answer:** 3 (b)

## 2. Proportion

**Q5.** What is the fourth proportional to $5, 8,$ and $15$?
(a) $18$ (b) $20$ (c) $24$ (d) $28$

**Solution:**
Let the fourth proportional be $d$.
By proportion, $5:8 = 15:d$.
Product of extremes = Product of means: 
$5d = 8 \times 15 = 120 \implies d = 24$.

**Answer:** 24 (c)

**Q6.** Find the mean proportional between $0.08$ and $0.18$.
(a) $0.12$ (b) $0.144$ (c) $0.16$ (d) $0.108$

**Solution:**
The mean proportional $b$ between $a$ and $c$ is $b = \sqrt{ac}$.
$b = \sqrt{0.08 \times 0.18} = \sqrt{\frac{8}{100} \times \frac{18}{100}} = \sqrt{\frac{144}{10000}} = \frac{12}{100} = 0.12$.

**Answer:** 0.12 (a)

**Q7.** The numbers $x, 12,$ and $54$ are in continued proportion. Find the value of $x$.
(a) $2$ (b) $2.66$ (c) $\frac{8}{3}$ (d) $4$

**Solution:**
For three terms to be in continued proportion, $x:12 = 12:54$, which means $12^{2} = x \times 54$.
$144 = 54x \implies x = \frac{144}{54} = \frac{72}{27} = \frac{8}{3}$.

**Answer:** 8/3 (c)

**Q8.** What number must be added to each of the numbers $6, 14, 18,$ and $38$ to make them proportional?
(a) $1$ (b) $2$ (c) $3$ (d) $4$

**Solution:**
Let the number be $x$. Then $\frac{6+x}{14+x} = \frac{18+x}{38+x}$.
Instead of cross-multiplying to solve the quadratic, immediately test the options:
If $x=2$: $\frac{6+2}{14+2} = \frac{8}{16} = \frac{1}{2}$, and $\frac{18+2}{38+2} = \frac{20}{40} = \frac{1}{2}$. They match perfectly.

**Answer:** 2 (b)

::: keypoint
Always plug in the options for "what number must be added/subtracted" proportion questions to avoid tedious algebra.
:::

## 3. Variation

**Q9.** The quantity $y$ varies directly as the square of $x$. When $x = 4$, $y = 48$. What is the value of $y$ when $x = 5$?
(a) $60$ (b) $75$ (c) $90$ (d) $100$

**Solution:**
Since $y \propto x^{2}$, we have $y = kx^{2}$.
Substitute knowns to find $k$: $48 = k(4^{2}) \implies k = 3$.
When $x = 5$, $y = 3(5^{2}) = 3 \times 25 = 75$.

**Answer:** 75 (b)

**Q10.** The time $t$ taken to build a wall varies directly as the volume of the wall $V$, and inversely as the number of workers $w$. If $10$ workers can build a $500\text{ m}^{3}$ wall in $5$ days, how many days will $15$ workers take to build a $1200\text{ m}^{3}$ wall?
(a) $6$ days (b) $8$ days (c) $10$ days (d) $12$ days

**Solution:**
The joint variation is $t = k\frac{V}{w}$.
Find the constant $k$: $5 = k\frac{500}{10} \implies 5 = 50k \implies k = \frac{1}{10}$.
Now find $t$ for the new case: $t = \frac{1}{10} \times \frac{1200}{15} = \frac{120}{15} = 8$.

**Answer:** 8 days (b)

::: trap
A common mistake is treating an inverse variation as a direct one. Remember: "varies inversely as $x$" means multiply by $1/x$, placing the variable in the denominator.
:::

**Q11.** The cost of a precious stone varies directly as the square of its weight. A stone worth $\$ 18,000$ accidentally breaks into three pieces whose weights are in the ratio $1:2:3$. What is the financial loss incurred due to the breakage?
(a) $\$ 9,000$ (b) $\$ 11,000$ (c) $\$ 12,500$ (d) $\$ 14,000$

**Solution:**
Let the weights of the pieces be $x, 2x,$ and $3x$. The total original weight was $6x$.
Original cost $C = k(6x)^{2} = 36kx^{2}$. We know $36kx^{2} = 18000 \implies kx^{2} = 500$.
The combined cost of the broken pieces is the sum of their individual costs:
$C_{new} = k(x)^{2} + k(2x)^{2} + k(3x)^{2} = (1 + 4 + 9)kx^{2} = 14kx^{2}$.
The financial loss is $36kx^{2} - 14kx^{2} = 22kx^{2}$.
Loss $= 22 \times 500 = 11000$.

**Answer:** 11000 (b)

## 4. Applications

**Q12.** A bag contains $50\text{c}, 25\text{c},$ and $10\text{c}$ coins in the ratio $5:9:4$, amounting to $\$ 206$. Find the number of $50\text{c}$ coins.
(a) $150$ (b) $180$ (c) $200$ (d) $240$

**Solution:**
Let the number of $50\text{c}, 25\text{c},$ and $10\text{c}$ coins be $5x, 9x,$ and $4x$ respectively.
Convert the total value to cents to maintain integer math: $\$ 206 = 20600\text{c}$.
Set up the value equation (Denomination $\times$ Count):
$50(5x) + 25(9x) + 10(4x) = 20600$
$250x + 225x + 40x = 20600$
$515x = 20600 \implies x = 40$.
The number of $50\text{c}$ coins is $5x = 5(40) = 200$.

**Answer:** 200 (c)

**Q13.** Two alloys contain gold and silver in the ratios $3:2$ and $5:4$ respectively. If equal quantities of the two alloys are melted to form a third alloy, what is the ratio of gold to silver in the new alloy? *(For more on mixtures, see Section 05: Mixtures & Alligations)*.
(a) $17:15$ (b) $26:19$ (c) $29:21$ (d) $31:25$

**Solution:**
The first alloy has $3+2 = 5$ parts. The second alloy has $5+4 = 9$ parts.
To combine equal quantities effortlessly without fractions, assume a total volume for each alloy equal to the LCM of their parts: $\text{LCM}(5, 9) = 45$.

- In $45$ units of the first alloy: $\text{Gold} = \frac{3}{5}\times 45 = 27$, $\text{Silver} = 18$.
- In $45$ units of the second alloy: $\text{Gold} = \frac{5}{9}\times 45 = 25$, $\text{Silver} = 20$.

Mixed together: $\text{Total Gold} = 27 + 25 = 52$, $\text{Total Silver} = 18 + 20 = 38$.
New ratio $= 52:38 = 26:19$.

**Answer:** 26:19 (b)

**Q14.** The present ages of A and B are in the ratio $4:5$. Eight years hence, the ratio of their ages will be $5:6$. What is A's present age? *(For more age variations, see Section 06: Ages)*.
(a) $24$ years (b) $28$ years (c) $32$ years (d) $40$ years

**Solution:**
Let the present ages be $4x$ and $5x$.
Notice that both parts naturally increase by exactly $1$ unit (from $4 \to 5$ and $5 \to 6$) after $8$ years.
Therefore, $1 \text{ ratio unit} = 8 \text{ years}$.
A's present age is $4 \text{ units} = 4 \times 8 = 32$ years.

**Answer:** 32 (c)

**Q15.** A mixture contains milk and water in the ratio $4:3$. If $5$ liters of water is added, the ratio becomes $4:5$. Find the quantity of milk in the given mixture.
(a) $8$ liters (b) $10$ liters (c) $12$ liters (d) $15$ liters

**Solution:**
The ratio of milk to water starts at $4:3$ and becomes $4:5$.
The milk remains constant at $4$ units, while the water increases from $3$ units to $5$ units.
This difference of $2$ units corresponds to the $5$ liters of added water.
$2 \text{ units} = 5 \text{ liters} \implies 1 \text{ unit} = 2.5 \text{ liters}$.
Quantity of milk $= 4 \text{ units} = 4 \times 2.5 = 10$ liters.

**Answer:** 10 (b)

## 5. Wrapped OA variants

**Q16.** A cloud infrastructure provider allocates CPU cores, memory (in GB), and storage (in TB) to a client in the initial ratio $2:8:5$. After a scaling event, the client requests a $50\%$ increase in CPU cores and a $25\%$ increase in memory, while leaving storage unchanged. If the upgraded setup contains exactly $360$ total allocated units across the three resources, how much memory (in GB) is provided in the upgraded setup?
(a) $150\text{ GB}$ (b) $180\text{ GB}$ (c) $200\text{ GB}$ (d) $240\text{ GB}$

**Solution:**
Let the initial units be $2x, 8x,$ and $5x$.
Calculate the new units after scaling using multipliers:

- CPU: $2x \times 1.50 = 3x$
- Memory: $8x \times 1.25 = 10x$
- Storage: $5x \times 1 = 5x$

The new ratio is $3:10:5$.
The sum of the upgraded parts is $3x + 10x + 5x = 18x$.
We are given that $18x = 360$, so $x = 20$.
The upgraded memory is $10x = 10(20) = 200\text{ GB}$.

**Answer:** 200 (c)

::: interview
In applied variation and scaling problems during OAs, always translate percentage shifts directly into multipliers on the ratio terms. Normalize fractions back to integers if needed, though well-crafted questions usually resolve cleanly.
:::

**Q17.** The total operational cost of a delivery fleet consists of a fixed base cost and a variable fuel cost that varies directly as the square of the average fleet speed. At an average speed of $40\text{ mph}$, the total cost is $\$ 3,200$, of which $\$ 1,600$ is the fuel cost. If the fleet wants to cap the total cost at $\$ 5,200$, what is the maximum average speed they can maintain?
(a) $50\text{ mph}$ (b) $60\text{ mph}$ (c) $65\text{ mph}$ (d) $70\text{ mph}$

**Solution:**
Let the total cost be $C = F + kV^{2}$, where $F$ is the fixed cost and $V$ is the speed.
At $V = 40\text{ mph}$, the total cost is $\$ 3,200$ and the fuel cost ($kV^{2}$) is $\$ 1,600$.
This means the fixed cost $F = 3200 - 1600 = 1600$.
Now find $k$ for the variable fuel cost:
$k(40^{2}) = 1600 \implies 1600k = 1600 \implies k = 1$.
The new target total cost is $\$ 5,200$. Setup the equation again:
$F + kV^{2} = 5200 \implies 1600 + 1(V^{2}) = 5200 \implies V^{2} = 3600 \implies V = 60$.
The maximum speed is $60\text{ mph}$.

**Answer:** 60 (b)

## Sources

- IndiaBix — https://www.indiabix.com/ (Ratio and Proportion base patterns)
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/ (Variation and direct/inverse modeling)
- Hitbullseye — https://www.hitbullseye.com/ (Coin and mixture applications)
- PrepInsta — https://prepinsta.com/ (Company OA variants on resource scaling)
