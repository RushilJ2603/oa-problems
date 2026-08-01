# Data Interpretation

Data Interpretation (DI) rewards *reading* over *calculating*. The arithmetic is deliberately light; the
difficulty is in extracting the right numbers quickly and estimating instead of computing to the last decimal.

::: keypoint
**The DI drill.** (1) Read the **title, units, and legend first** — half of all DI errors are unit slips
(thousands vs lakhs, % vs absolute). (2) **Approximate**: for "which is largest / roughly what %" you rarely
need exact figures — round and compare. (3) Learn the three workhorse operations cold: percentage change
$\dfrac{\text{new}-\text{old}}{\text{old}}\times 100$, share $\dfrac{\text{part}}{\text{total}}\times 100$, and
ratio. (4) Compute a **row/column total once** and reuse it across sub-questions.
:::

::: trap
Never carry a running "percentage of a percentage" in your head. To combine, convert to absolute values first,
then take the final ratio. And a percentage change is always measured *against the earlier (base) value*, not
the later one.
:::

## 1. Table Interpretation

The table shows units sold (in **thousands**) of five products by a retailer over three years.

| Product | 2021 | 2022 | 2023 | Total |
|---------|-----:|-----:|-----:|------:|
| P1      |  40  |  45  |  60  |  145  |
| P2      |  55  |  50  |  65  |  170  |
| P3      |  30  |  42  |  48  |  120  |
| P4      |  25  |  35  |  40  |  100  |
| P5      |  50  |  48  |  57  |  155  |
| **Total** | **200** | **220** | **270** | **690** |

**Q1.** How many units (in thousands) were sold across all products in 2022?
(a) $200$ (b) $220$ (c) $260$ (d) $270$

**Solution:** Read the 2022 column total directly: $45+50+42+35+48 = 220$.

**Answer:** $220$ (b)

**Q2.** Over the three years combined, which product sold the most units?
(a) P1 (b) P2 (c) P5 (d) P3

**Solution:** Compare row totals: P1 $145$, P2 $170$, P3 $120$, P4 $100$, P5 $155$. The largest is P2.

**Answer:** P2 (b)

**Q3.** What is the percentage increase in P1's sales from 2021 to 2023?
(a) $33.3\%$ (b) $40\%$ (c) $50\%$ (d) $60\%$

**Solution:** $\dfrac{60-40}{40}\times 100 = \dfrac{20}{40}\times 100 = 50\%$.

**Answer:** $50\%$ (c)

**Q4.** In 2023, P2's sales were approximately what percentage of the total sales that year?
(a) $18\%$ (b) $21\%$ (c) $24\%$ (d) $29\%$

**Solution:** $\dfrac{65}{270}\times 100 = 24.07\% \approx 24\%$.

**Answer:** $24\%$ (c)

**Q5.** What is the ratio of total sales in 2021 to total sales in 2023?
(a) $20:27$ (b) $10:11$ (c) $5:7$ (d) $4:5$

**Solution:** $200:270$. Divide both by $10$: $20:27$ (already in lowest terms since $27=3^3$ shares no factor with $20$).

**Answer:** $20:27$ (a)

::: keypoint
When a question says "approximately," round aggressively *before* dividing. $65/270$ is near $65/270 \approx
66/264 = 1/4 = 25\%$ — close enough to eliminate all options but $24\%$ without long division.
:::

## 2. Bar Graph

![Annual revenue of TechCorp Ltd. (in Rs crore), 2019 to 2023](figs/s24_bar_revenue.png)

**Q6.** What is the total revenue earned over the five years?
(a) Rs $735$ crore (b) Rs $780$ crore (c) Rs $795$ crore (d) Rs $810$ crore

**Solution:** $120+150+135+180+210 = 795$.

**Answer:** Rs $795$ crore (c)

**Q7.** What is the average annual revenue over the period?
(a) Rs $153$ crore (b) Rs $159$ crore (c) Rs $165$ crore (d) Rs $172$ crore

**Solution:** $\dfrac{795}{5} = 159$.

**Answer:** Rs $159$ crore (b)

**Q8.** By what percentage did revenue grow from 2022 to 2023?
(a) $14.3\%$ (b) $16.7\%$ (c) $20\%$ (d) $30\%$

**Solution:** $\dfrac{210-180}{180}\times 100 = \dfrac{30}{180}\times 100 = 16.67\%$.

**Answer:** $16.7\%$ (b)

**Q9.** Which year recorded the highest year-on-year **percentage** growth?
(a) $2020$ (b) $2021$ (c) $2022$ (d) $2023$

**Solution:** Compute each step: $2019\to 2020 = \tfrac{30}{120}=25\%$; $2020\to 2021 = \tfrac{-15}{150}=-10\%$;
$2021\to 2022 = \tfrac{45}{135}=33.3\%$; $2022\to 2023 = \tfrac{30}{180}=16.7\%$. The peak is the jump into 2022.

**Answer:** $2022$ (c)

::: trap
"Highest growth" almost always means **percentage** growth, not the largest absolute jump. Here 2020 and 2023
share the same absolute rise of $+30$, but their percentage rises ($25\%$ vs $16.7\%$) differ because the base
differs. Always check which the question wants.
:::

## 3. Pie Chart

![Monthly household budget split, total Rs 48,000](figs/s24_pie_budget.png)

**Q10.** How much is spent on Rent each month?
(a) Rs $12{,}000$ (b) Rs $13{,}200$ (c) Rs $14{,}400$ (d) Rs $15{,}000$

**Solution:** $30\%$ of $48{,}000 = 0.30 \times 48{,}000 = 14{,}400$.

**Answer:** Rs $14{,}400$ (c)

**Q11.** What is the central angle of the sector representing Food?
(a) $72^{\circ}$ (b) $80^{\circ}$ (c) $90^{\circ}$ (d) $96^{\circ}$

**Solution:** A full circle is $360^{\circ}$, so Food's $25\%$ maps to $0.25 \times 360 = 90^{\circ}$.

**Answer:** $90^{\circ}$ (c)

**Q12.** How much more is spent on Transport than on Utilities?
(a) Rs $1{,}920$ (b) Rs $2{,}400$ (c) Rs $2{,}880$ (d) Rs $3{,}360$

**Solution:** The gap is $15\% - 10\% = 5\%$ of $48{,}000 = 2{,}400$.

**Answer:** Rs $2{,}400$ (b)

**Q13.** If savings were raised to $20\%$ of the budget (total unchanged), by how much would the monthly saving rise?
(a) Rs $3{,}840$ (b) Rs $4{,}800$ (c) Rs $5{,}760$ (d) Rs $9{,}600$

**Solution:** New saving $= 20\%$ of $48{,}000 = 9{,}600$; old saving $= 12\% = 5{,}760$. Rise $= 9{,}600 - 5{,}760 = 3{,}840$.

**Answer:** Rs $3{,}840$ (a)

## 4. Line Graph

![Monthly sales of Product A vs Product B, in thousands of units](figs/s24_line_sales.png)

**Q14.** What were the total sales (in thousands) of Product A over the six months?
(a) $320$ (b) $332$ (c) $338$ (d) $346$

**Solution:** $40+55+50+65+70+58 = 338$.

**Answer:** $338$ (c)

**Q15.** In which month did Product B's sales first overtake Product A's?
(a) March (b) April (c) May (d) June

**Solution:** Compare month by month — A leads through May ($70$ vs $55$); in June, B $65$ exceeds A $58$ for the first time.

**Answer:** June (d)

**Q16.** What is the difference between the six-month totals of A and B?
(a) $54$ (b) $61$ (c) $68$ (d) $72$

**Solution:** Total A $= 338$; total B $= 30+35+45+40+55+65 = 270$. Difference $= 338 - 270 = 68$.

**Answer:** $68$ (c)

**Q17.** In which month was the **combined** sales of A and B the highest?
(a) April (b) May (c) June (d) March

**Solution:** Combined totals: Jan $70$, Feb $90$, Mar $95$, Apr $105$, May $125$, Jun $123$. May is the peak.

**Answer:** May (b)

**Q18.** By what percentage did Product A's sales fall from May to June?
(a) $12\%$ (b) $14.3\%$ (c) $17.1\%$ (d) $20\%$

**Solution:** $\dfrac{70-58}{70}\times 100 = \dfrac{12}{70}\times 100 = 17.14\%$.

**Answer:** $17.1\%$ (c)

## 5. Caselet (Data in Prose)

An office has $300$ employees, of whom $60\%$ are male. Among the men, $25\%$ work in Sales; among the women,
$40\%$ work in Sales.

**Q19.** How many employees work in Sales in total?
(a) $84$ (b) $90$ (c) $93$ (d) $102$

**Solution:** Men $= 60\%$ of $300 = 180$; women $= 120$. Men in Sales $= 25\%$ of $180 = 45$; women in Sales
$= 40\%$ of $120 = 48$. Total $= 45 + 48 = 93$.

**Answer:** $93$ (c)

**Q20.** What fraction of the Sales team is female?
(a) $\dfrac{15}{31}$ (b) $\dfrac{16}{31}$ (c) $\dfrac{1}{2}$ (d) $\dfrac{17}{31}$

**Solution:** $\dfrac{48}{93} = \dfrac{16}{31}$ (dividing numerator and denominator by $3$).

**Answer:** $\dfrac{16}{31}$ (b)

## 6. Wrapped OA Variant

**Q21.** *(OA projection.)* TechCorp (bar graph, Section 2) has set a revenue target of Rs $250$ crore for 2024.
By approximately what percentage must it grow its 2023 revenue to reach that target?

(a) $16.0\%$ (b) $19.0\%$ (c) $23.8\%$ (d) $40.0\%$

**Solution:** 2023 revenue was Rs $210$ crore, so the required growth is
$\dfrac{250-210}{210}\times 100 = \dfrac{40}{210}\times 100 = 19.05\% \approx 19\%$. Option (d) is the trap of
dividing the $40$-crore gap by $100$ instead of by the base; option (c) uses $168$ as the base by mistake.

**Answer:** $19.0\%$ (b)

::: interview
DI in an OA is a *speed* filter: 4–6 questions on one exhibit in a couple of minutes. Graders don't see your
work, only the answer, so the winning move is ruthless approximation and computing each shared total exactly
once. In a case-interview setting the opposite holds — say your assumptions and the base you are dividing by out
loud, because the reasoning is what's being scored.
:::

## Sources

- Data Interpretation (tables, bar/line/pie, caselets) — IndiaBix — https://www.indiabix.com/data-interpretation/questions-and-answers/
- Data Interpretation practice sets — GeeksforGeeks — https://www.geeksforgeeks.org/data-interpretation/
- DI for placements & bank exams — PrepInsta — https://prepinsta.com/data-interpretation/
- Quantitative aptitude: Data Interpretation — Hitbullseye — https://www.hitbullseye.com/Data-Interpretation.php
