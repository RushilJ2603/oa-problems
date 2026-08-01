# Profit, Loss & Discount

::: definition
**Core Terminology:**

- **Cost Price (CP):** The price at which goods are purchased.
- **Selling Price (SP):** The price at which goods are sold.
- **Marked Price (MP):** The listed or printed price.

**Formulas:**

- **Profit / Loss \%:** Always calculated on CP.
  $$\text{Profit \%} = \left(\frac{SP - CP}{CP}\right) \times 100$$
  $$\text{Loss \%} = \left(\frac{CP - SP}{CP}\right) \times 100$$

- **SP from CP:** $SP = CP \times \left(1 \pm \frac{p}{100}\right)$ where $p$ is the profit (+) or loss (-) percentage.
- **Discount:** Always calculated on MP.
  $$SP = MP \times \left(1 - \frac{d}{100}\right)$$

- **Successive Discounts:** Successive discounts of $a\%$ and $b\%$ yield a single equivalent discount of:
  $$\left(a + b - \frac{ab}{100}\right)\%$$
:::

## Core CP/SP

**Q1.** A man buys a toy for $\$250$ and sells it for $\$300$. What is his profit percentage?

(a) $15\%$ (b) $16.67\%$ (c) $20\%$ (d) $25\%$

**Solution:** The profit is $300 - 250 = 50$. The profit percentage is calculated on CP:
$$\frac{50}{250} \times 100 = \frac{1}{5} \times 100 = 20\%$$

**Answer:** 20% (c)

**Q2.** The selling price of an article is $\frac{5}{4}$ of its cost price. What is the profit percentage?

(a) $15\%$ (b) $20\%$ (c) $25\%$ (d) $30\%$

**Solution:** Let $CP = x$. Then $SP = \frac{5}{4}x$.
$$\text{Profit} = SP - CP = \frac{1}{4}x$$
$$\text{Profit \%} = \frac{1/4}{1} \times 100 = 25\%$$
Alternatively, just read the ratio: $SP:CP = 5:4$. Profit is $1$ part on a base of $4$, so $\frac{1}{4} \equiv 25\%$.

**Answer:** 25% (c)

::: keypoint
When moving between two selling prices of the same item at different profit/loss percentages, scale directly without finding CP: 
$$SP_{2} = SP_{1} \times \frac{100 \pm p_{2}}{100 \pm p_{1}}$$
:::

**Q3.** By selling a bicycle for $\$2850$, a shopkeeper gains $14\%$. If the profit is reduced to $8\%$, what will be the new selling price?

(a) $\$2600$ (b) $\$2700$ (c) $\$2750$ (d) $\$2800$

**Solution:** Use the scaling ratio instead of calculating CP explicitly. 
The first SP corresponds to $114\%$ of CP. The target SP corresponds to $108\%$ of CP.
$$SP_{\text{new}} = 2850 \times \frac{108}{114}$$
$$SP_{\text{new}} = 2850 \times \frac{18}{19} = 150 \times 18 = 2700$$

**Answer:** $2700$ (b)

**Q4.** A vendor sells lemons at $5$ for a dollar, gaining $40\%$. How many did he buy for a dollar?

(a) $6$ (b) $7$ (c) $8$ (d) $9$

**Solution:** Selling $5$ lemons for $\$1$ means $SP = \frac{1}{5}$ per lemon.
He gains $40\%$, meaning $SP = 1.4 \times CP$.
$$\frac{1}{5} = \frac{140}{100} \times CP \implies CP = \frac{1}{5} \times \frac{100}{140} = \frac{1}{7}$$
If the CP is $\$ \frac{1}{7}$ per lemon, he bought $7$ lemons for a dollar.

**Answer:** 7 (b)

## Marked Price & Discount

**Q5.** What is the single equivalent discount for two successive discounts of $20\%$ and $15\%$?

(a) $32\%$ (b) $34\%$ (c) $35\%$ (d) $38\%$

**Solution:** Use the successive discount formula $a + b - \frac{ab}{100}$:
$$20 + 15 - \frac{20 \times 15}{100} = 35 - 3 = 32\%$$

**Answer:** 32% (a)

**Q6.** A tradesman marks his goods $25\%$ above the cost price and allows a discount of $12\%$ on the marked price. What is his exact profit percentage?

(a) $8\%$ (b) $10\%$ (c) $12\%$ (d) $13\%$

**Solution:** Let $CP = 100$. The MP is $125$. 
Discount is $12\%$ of $MP = 0.12 \times 125 = 15$.
$SP = 125 - 15 = 110$.
Profit is $110 - 100 = 10\%$.
Alternatively, use the successive percentage formula with $+25$ and $-12$:
$$25 - 12 - \frac{25 \times 12}{100} = 13 - 3 = 10\%$$

**Answer:** 10% (b)

::: keypoint
The direct relationship between Cost Price and Marked Price is given by the ratio:
$$\frac{MP}{CP} = \frac{100 + \text{Profit \%}}{100 - \text{Discount \%}}$$
:::

**Q7.** A retailer offers a discount of $10\%$ on the marked price of an item and still makes a profit of $20\%$. If the item cost him $\$450$, what is its marked price?

(a) $\$500$ (b) $\$540$ (c) $\$600$ (d) $\$650$

**Solution:** Using the shortcut ratio:
$$\frac{MP}{450} = \frac{100 + 20}{100 - 10} = \frac{120}{90} = \frac{4}{3}$$
$$MP = 450 \times \frac{4}{3} = 600$$

**Answer:** $600$ (c)

**Q8.** A smartphone is listed at $\$800$. A customer buys it for $\$612$ after receiving two successive discounts. If the first discount is $15\%$, what is the second discount?

(a) $8\%$ (b) $10\%$ (c) $12\%$ (d) $15\%$

**Solution:** Value after the first discount of $15\%$:
$$800 \times \left(1 - 0.15\right) = 800 \times 0.85 = 680$$
The final price is $\$612$. The second discount is applied to $\$680$.
$$\text{Discount amount} = 680 - 612 = 68$$
$$\text{Second discount \%} = \frac{68}{680} \times 100 = 10\%$$

**Answer:** 10% (b)

## Dishonest Dealer / False Weights

::: keypoint
For dishonest dealer problems where goods are sold at the claimed Cost Price but false weights are used:
$$\text{Gain \%} = \left(\frac{\text{Error}}{\text{True Value} - \text{Error}}\right) \times 100$$
The denominator is the *actual* weight handed over to the customer.
:::

**Q9.** A dishonest dealer promises to sell his groceries at cost price, but uses a false weight of $900\text{g}$ for every $1\text{kg}$. What is his profit percentage?

(a) $10\%$ (b) $11.11\%$ (c) $12.5\%$ (d) $9\%$

**Solution:** The error is $100\text{g}$. The actual weight given is $900\text{g}$.
$$\text{Gain \%} = \frac{100}{900} \times 100 = \frac{1}{9} \times 100 = 11.11\%$$

**Answer:** 11.11% (b)

**Q10.** A merchant marks up his goods by $20\%$ but uses a $800\text{g}$ weight instead of $1\text{kg}$. What is his overall profit percentage?

(a) $40\%$ (b) $50\%$ (c) $44\%$ (d) $60\%$

**Solution:** Treat this as a chain of scaling factors (multiplying ratios).

1. Markup step: Customer pays for $1200\text{g}$ equivalent value per $1000\text{g}$ (Ratio: $\frac{1200}{1000}$).
2. Weight step: Dealer gives only $800\text{g}$ per $1000\text{g}$ claimed (Ratio: $\frac{1000}{800}$).

Net ratio of (Revenue/Cost): 
$$\frac{120}{100} \times \frac{1000}{800} = \frac{12}{10} \times \frac{10}{8} = \frac{12}{8} = \frac{3}{2}$$
A ratio of $\frac{3}{2}$ means $SP = 1.5 \times CP$, which is a $50\%$ profit.

**Answer:** 50% (b)

**Q11.** A vendor professes to sell his goods at a loss of $10\%$, but uses a weight of $750\text{g}$ instead of a kilogram. What is his actual profit or loss percentage?

(a) $10\%$ loss (b) $20\%$ profit (c) $15\%$ profit (d) $25\%$ loss

**Solution:** Use the successive ratio method.

1. Pricing step: Revenue is $90\%$ of claimed CP (Ratio: $\frac{90}{100}$).
2. Weight step: Cost is incurred for only $750\text{g}$ out of $1000\text{g}$ (Ratio: $\frac{1000}{750}$).

Net ratio: 
$$\frac{90}{100} \times \frac{1000}{750} = \frac{9}{10} \times \frac{4}{3} = \frac{36}{30} = \frac{6}{5}$$
A ratio of $\frac{6}{5}$ is $1.2$, representing a $20\%$ profit.

**Answer:** 20% profit (b)

::: trap
When a dealer cheats during both buying and selling, do not simply add the percentages. The base changes because he acquires more goods and delivers fewer goods.
:::

**Q12.** A shopkeeper cheats to the extent of $10\%$ while buying and $10\%$ while selling by using false weights. What is his total gain percentage?

(a) $20\%$ (b) $21\%$ (c) $22.22\%$ (d) $23.45\%$

**Solution:** 
When buying, he takes $1100\text{g}$ while paying for $1000\text{g}$.
When selling, he gives $900\text{g}$ while charging for $1000\text{g}$.
Let $1\text{g}$ cost $\$1$. 
He spends $\$1000$ to get $1100\text{g}$. (His actual CP per gram is $\frac{1000}{1100}$).
He sells $1100\text{g}$. Since he uses a $900\text{g}$ weight in place of $1000\text{g}$, he bills the customer for $\frac{1100}{900} \times 1000 = \frac{11000}{9}$ grams.
His total revenue is $\$ \frac{11000}{9}$.
$$\text{Profit ratio} = \frac{\text{Revenue}}{\text{Cost}} = \frac{11000/9}{1000} = \frac{11}{9}$$
Gain is $\frac{2}{9} \times 100 \approx 22.22\%$.

**Answer:** 22.22% (c)

## Multiple Articles & Equivalences

**Q13.** The cost price of $15$ articles is equal to the selling price of $12$ articles. Find the profit percentage.

(a) $15\%$ (b) $20\%$ (c) $25\%$ (d) $30\%$

**Solution:** $15 \times CP = 12 \times SP$.
Rearranging gives the ratio: 
$$\frac{SP}{CP} = \frac{15}{12} = \frac{5}{4}$$
A ratio of $\frac{5}{4}$ means a profit of $\frac{1}{4}$, which is $25\%$.

**Answer:** 25% (c)

**Q14.** A store offers a "Buy 3, Get 2 Free" promotion. What is the effective discount percentage?

(a) $33.33\%$ (b) $40\%$ (c) $50\%$ (d) $66.67\%$

**Solution:** The customer receives a total of $5$ items but pays for only $3$.
The discount is the value of the $2$ free items out of the total $5$ items marked price.
$$\text{Discount \%} = \frac{\text{Free Items}}{\text{Total Items}} \times 100 = \frac{2}{5} \times 100 = 40\%$$

**Answer:** 40% (b)

::: trap
Many candidates guess "No profit no loss" when two items are sold at the same price with equal and opposite profit/loss percentages. But profit/loss are percentages of different Cost Prices, leading to a net loss!
:::

**Q15.** A man sells two houses for $\$53,685$ each. On one he gains $20\%$ and on the other he loses $20\%$. Find his gain or loss percentage on the whole transaction.

(a) $4\%$ loss (b) $4\%$ gain (c) No profit no loss (d) $8\%$ loss

**Solution:** When two items are sold at the *same selling price* with an equal profit and loss percentage $x$, there is always a net loss on the whole transaction. 
The net loss percentage is given by:
$$\text{Loss \%} = \frac{x^{2}}{100}$$
$$\text{Loss \%} = \frac{20^{2}}{100} = \frac{400}{100} = 4\%$$
The messy $\$53,685$ figure is a distractor and is not needed.

**Answer:** 4% loss (a)

**Q16.** A merchant buys two items for a total of $\$800$. He sells one at a $10\%$ profit and the other at a $15\%$ loss, making an overall loss of $\$20$. What was the cost price of the item sold at a loss?

(a) $\$300$ (b) $\$400$ (c) $\$450$ (d) $\$500$

**Solution:** Let the CP of the item sold at a profit be $x$ and the one sold at a loss be $y$.

1. $x + y = 800$
2. $0.10x - 0.15y = -20$

Multiply equation 1 by $0.10$ to get $0.10x + 0.10y = 80$. 
Subtract equation 2 from this:
$$(0.10x + 0.10y) - (0.10x - 0.15y) = 80 - (-20)$$
$$0.25y = 100 \implies y = 400$$

**Answer:** $400$ (b)

## Wrapped OA Variants

::: interview
In modern OAs (e.g., at Uber or Amazon), simple profit equations are often wrapped in operational story problems involving bulk purchasing, defect rates, or platform fees. You must map these costs into a single net CP before applying standard formulas.
:::

**Q17.** A drop-shipper imports $500$ delicate glass lamps for $\$15$ each. Shipping costs a flat $\$500$ for the entire batch. Upon arrival, he finds that $10\%$ of the lamps are broken and cannot be sold. If he wants to make a $20\%$ net profit on his entire investment, at what price must he sell each remaining lamp?

(a) $\$18.50$ (b) $\$20.00$ (c) $\$21.33$ (d) $\$22.50$

**Solution:** 
Total investment (CP) = $(\$15 \times 500) + \$500 = \$7500 + \$500 = \$8000$.
Target revenue (total SP) to hit a $20\%$ profit = $8000 \times 1.20 = \$9600$.
Number of sellable lamps = $500 \times 0.90 = 450$.
Selling price per lamp = $\frac{9600}{450} = \frac{960}{45} = \frac{64}{3} \approx 21.33$.

**Answer:** $21.33$ (c)

**Q18.** An artisan sells handcrafted wallets on a digital marketplace. The marketplace takes a $15\%$ commission on the final selling price. Shipping costs the artisan $\$4$ per wallet, and raw materials cost $\$13$ per wallet. To achieve a net profit of $\$10$ per wallet, what should the listed selling price be?

(a) $\$31.76$ (b) $\$32.50$ (c) $\$27.00$ (d) $\$30.00$

**Solution:** Let the listed selling price be $SP$. 
The artisan receives the $SP$ minus the $15\%$ commission, so the net revenue is $0.85 \times SP$.
The total expenses (CP) per wallet are $13 + 4 = 17$.
Profit = Net Revenue - Expenses
$$10 = (0.85 \times SP) - 17$$
$$27 = 0.85 \times SP$$
$$SP = \frac{27}{0.85} = \frac{2700}{85} = \frac{540}{17} \approx 31.76$$

**Answer:** $31.76$ (a)

## Sources

- IndiaBix — Core Profit and Loss Concepts — https://www.indiabix.com/aptitude/profit-and-loss/
- GeeksforGeeks — Dishonest Dealer Formulas — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- Hitbullseye — Successive Discounts — https://www.hitbullseye.com/Profit-and-Loss.php
- PrepInsta — OA Variants and Traps — https://prepinsta.com/
