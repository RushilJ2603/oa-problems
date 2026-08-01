# Time & Work; Pipes & Cisterns

::: keypoint
**The LCM / Total Work Method**  
Instead of calculating fractional work per day (e.g., $\frac{1}{A}$), define the **Total Work** as the Least Common Multiple (LCM) of the given times. This turns every rate into a clean integer.

1. **Total Work** = $\text{LCM}(t_1, t_2, \dots)$ units.
2. **Efficiency (Rate)** = $\frac{\text{Total Work}}{\text{Time taken}}$ units per day.
3. **Combined Rate** = Sum of individual rates.
4. **Time to Complete** = $\frac{\text{Total Work}}{\text{Combined Rate}}$.

For groups of workers (men, days, hours), use the **MDH Equation**:  
$$\frac{M_1 \times D_1 \times H_1}{W_1} = \frac{M_2 \times D_2 \times H_2}{W_2}$$
:::

## Single & Combined Workers

**Q1.** A can do a piece of work in 10 days, and B can do it in 15 days. How many days will they take to complete the work if they work together?
(a) 5
(b) 6
(c) 8
(d) 9

**Solution:**
Let Total Work = $\text{LCM}(10, 15) = 30$ units.

- A's rate = $\frac{30}{10} = 3$ units/day.
- B's rate = $\frac{30}{15} = 2$ units/day.
- Combined rate = $3 + 2 = 5$ units/day.
Time taken = $\frac{30}{5} = 6$ days.

**Answer:** 6 (b)

**Q2.** A, B, and C can complete a job in 10, 12, and 15 days respectively. If they work together, how long will it take to finish the job?
(a) 3 days
(b) 4 days
(c) 5 days
(d) 6 days

**Solution:**
Total Work = $\text{LCM}(10, 12, 15) = 60$ units.
Rates: $A = 6$, $B = 5$, $C = 4$.
Combined rate = $6 + 5 + 4 = 15$ units/day.
Time = $\frac{60}{15} = 4$ days.

**Answer:** 4 days (b)

**Q3.** A and B can do a piece of work in 15 days and 20 days respectively. If they work together for 4 days, what fraction of the work is left?
(a) $\frac{1}{4}$
(b) $\frac{7}{15}$
(c) $\frac{8}{15}$
(d) $\frac{11}{15}$

**Solution:**
Total Work = $\text{LCM}(15, 20) = 60$ units.
Rates: $A = 4$, $B = 3$.
Combined rate = $7$ units/day.
Work done in 4 days = $4 \times 7 = 28$ units.
Work left = $60 - 28 = 32$ units.
Fraction left = $\frac{32}{60} = \frac{8}{15}$.

**Answer:** $\frac{8}{15}$ (c)

**Q4.** A and B together can complete a piece of work in 15 days, while B alone can do it in 20 days. How many days would A alone take to complete the work?
(a) 45
(b) 50
(c) 60
(d) 75

**Solution:**
Total Work = $\text{LCM}(15, 20) = 60$ units.
Combined rate $(A + B) = 4$ units/day.
B's rate = $3$ units/day.
A's rate = $(A + B) - B = 4 - 3 = 1$ unit/day.
Time for A alone = $\frac{60}{1} = 60$ days.

**Answer:** 60 (c)

**Q5.** A and B can do a piece of work in 12 days, B and C in 15 days, and C and A in 20 days. How long will they take working together?
(a) 8 days
(b) 10 days
(c) 12 days
(d) 15 days

**Solution:**
Total Work = $\text{LCM}(12, 15, 20) = 60$ units.
Rates: $(A + B) = 5$, $(B + C) = 4$, $(C + A) = 3$.
Adding them up: $2(A + B + C) = 5 + 4 + 3 = 12$.
Combined rate $(A + B + C) = \frac{12}{2} = 6$ units/day.
Time taken = $\frac{60}{6} = 10$ days.

**Answer:** 10 days (b)

## Efficiency & Wages

**Q6.** A is 30% more efficient than B. If B alone can complete a work in 26 days, in how many days can A alone complete the same work?
(a) 18
(b) 20
(c) 22
(d) 24

**Solution:**
Efficiency ratio $A : B = 130 : 100 = 13 : 10$.
Time is inversely proportional to efficiency, so the time ratio $A : B = 10 : 13$.
Let A's time be $10x$ and B's time be $13x$.
Given $13x = 26 \implies x = 2$.
A's time = $10 \times 2 = 20$ days.

**Answer:** 20 (b)

**Q7.** A can do a piece of work in twice the time of B and thrice the time of C. Working together, they complete the work in 2 days. In how many days can B alone complete the work?
(a) 4
(b) 6
(c) 8
(d) 12

**Solution:**
Let the times taken by A, B, and C be $6x$, $3x$, and $2x$ respectively.
Total Work = $\text{LCM}(6x, 3x, 2x) = 6x$ units.
Rates: $A = 1$, $B = 2$, $C = 3$.
Combined rate = $1 + 2 + 3 = 6$ units/day.
Time taken together = $\frac{6x}{6} = x$ days.
Given $x = 2$.
Time for B alone = $3x = 3(2) = 6$ days.

**Answer:** 6 (b)

**Q8.** If 39 persons can repair a road in 12 days, working 5 hours a day, in how many days will 30 persons, working 6 hours a day, complete the same work?
(a) 10
(b) 13
(c) 14
(d) 15

**Solution:**
Use the MDH equation: $M_1 \times D_1 \times H_1 = M_2 \times D_2 \times H_2$.
$39 \times 12 \times 5 = 30 \times D_2 \times 6$
$2340 = 180 \times D_2$
$D_2 = \frac{2340}{180} = 13$ days.

**Answer:** 13 (b)

**Q9.** 10 men and 15 women together can complete a work in 6 days. It takes 100 days for one man alone to complete the same work. How many days will it take for one woman alone to complete the work?
(a) 150
(b) 180
(c) 200
(d) 225

**Solution:**
Let $M$ and $W$ be the daily work rates of a man and a woman.
Total work = $100M$ (since 1 man takes 100 days).
Also, total work = $(10M + 15W) \times 6$.
Equating the two:
$100M = 60M + 90W$
$40M = 90W \implies 4M = 9W \implies W = \frac{4}{9}M$.
Time for 1 woman = $\frac{\text{Total Work}}{W} = \frac{100M}{\frac{4}{9}M} = 100 \times \frac{9}{4} = 225$ days.

**Answer:** 225 (d)

**Q10.** A, B, and C can do a piece of work in 6, 8, and 12 days respectively. They do it together and get paid \$1350. What is B's share of the money?
(a) \$300
(b) \$450
(c) \$500
(d) \$600

**Solution:**
Wages are distributed in the ratio of work done. Since they work together for the same time, the ratio is simply their efficiency (rate) ratio.
Total Work = $\text{LCM}(6, 8, 12) = 24$.
Rates: $A = 4$, $B = 3$, $C = 2$.
Total rate = $4 + 3 + 2 = 9$.
B's share = $\frac{3}{9} \times 1350 = \$450$.

**Answer:** \$450 (b)

## Alternate-Day & Partial Work

**Q11.** A and B can do a piece of work in 8 days and 12 days respectively. If they work on alternate days, starting with A on the first day, in how many days will the work be completed?
(a) $9$
(b) $9\frac{1}{2}$
(c) $10$
(d) $10\frac{1}{2}$

**Solution:**
Total Work = $\text{LCM}(8, 12) = 24$ units.
Rates: $A = 3$, $B = 2$.
In a 2-day cycle (A then B), work done = $3 + 2 = 5$ units.
Number of full cycles = $\lfloor \frac{24}{5} \rfloor = 4$ cycles.
Time for 4 cycles = $4 \times 2 = 8$ days. Work completed = $4 \times 5 = 20$ units.
Remaining work = $24 - 20 = 4$ units.
Day 9 (A's turn): A completes 3 units. Remaining = 1 unit.
Day 10 (B's turn): B needs to complete 1 unit. Time taken = $\frac{1}{2}$ day.
Total time = $9 + \frac{1}{2} = 9\frac{1}{2}$ days.

**Answer:** $9\frac{1}{2}$ (b)

**Q12.** A and B can do a work in 20 and 30 days respectively. They start working together, but A leaves after 4 days. How long will B take to finish the remaining work?
(a) 15 days
(b) 16 days
(c) 18 days
(d) 20 days

**Solution:**
Total Work = $\text{LCM}(20, 30) = 60$ units.
Rates: $A = 3$, $B = 2$.
Combined rate = $5$ units/day.
Work done in first 4 days = $4 \times 5 = 20$ units.
Remaining work = $60 - 20 = 40$ units.
Time for B to finish remaining work = $\frac{40}{2} = 20$ days.

**Answer:** 20 (d)

**Q13.** A, B, and C can complete a job in 10, 12, and 15 days respectively. They started the work together, but A left 2 days before the completion of the work, and B left 3 days before completion. In how many days was the total work completed?
(a) $5$
(b) $5.4$
(c) $5.8$
(d) $6.2$

**Solution:**

::: keypoint
**The "Didn't Leave" Trick**  
If a worker leaves $x$ days *before completion*, assume they stayed and add the work they *would have done* in those $x$ days to the Total Work. Then, divide by the combined rate of all workers.
:::

Total Work = $\text{LCM}(10, 12, 15) = 60$ units.
Rates: $A = 6$, $B = 5$, $C = 4$. Combined = $15$.
If A had not left 2 days early, A would have done $2 \times 6 = 12$ more units.
If B had not left 3 days early, B would have done $3 \times 5 = 15$ more units.
Adjusted Total Work = $60 + 12 + 15 = 87$ units.
Total time taken = $\frac{87}{15} = 5.8$ days.

**Answer:** 5.8 (c)

## Pipes & Cisterns

**Q14.** Two pipes A and B can fill a tank in 20 minutes and 30 minutes respectively. If both pipes are opened simultaneously, how long will it take to fill the tank?
(a) 10 min
(b) 12 min
(c) 15 min
(d) 18 min

**Solution:**
Total Capacity = $\text{LCM}(20, 30) = 60$ units.
Rates: $A = +3$, $B = +2$.
Combined rate = $+5$ units/min.
Time = $\frac{60}{5} = 12$ minutes.

**Answer:** 12 min (b)

**Q15.** Pipe A can fill a tank in 12 minutes, Pipe B can fill it in 15 minutes, but Pipe C can empty the full tank in 20 minutes. If all three pipes are opened together, how long will it take to fill the empty tank?
(a) 8 min
(b) 10 min
(c) 12 min
(d) 15 min

**Solution:**

::: trap
**The Negative Work Trap**  
Always assign a negative rate to outlet pipes or leaks. If you blindly add their rates as positive, you are calculating the time for three pipes to *fill* the tank together, which is a classic multiple-choice trap.
:::

Total Capacity = $\text{LCM}(12, 15, 20) = 60$ units.
Rates: $A = +5$, $B = +4$, $C = -3$.
Combined rate = $5 + 4 - 3 = 6$ units/min.
Time = $\frac{60}{6} = 10$ minutes.

**Answer:** 10 min (b)

**Q16.** Pipe A can fill a cistern in 10 hours. Due to a leak in the bottom, it takes 15 hours to fill the cistern. How long will the leak alone take to empty a completely full cistern?
(a) 20 hours
(b) 25 hours
(c) 30 hours
(d) 35 hours

**Solution:**
Total Capacity = $\text{LCM}(10, 15) = 30$ units.
Rate of A = $+3$ units/hour.
Effective rate (A + Leak) = $\frac{30}{15} = +2$ units/hour.
Leak rate = Effective rate $-$ A's rate = $2 - 3 = -1$ unit/hour.
Time for leak to empty tank = $\frac{30}{1} = 30$ hours.

**Answer:** 30 hours (c)

**Q17.** Pipes A and B can fill a tank in 24 minutes and 32 minutes respectively. Both pipes are opened simultaneously. After how much time should pipe B be closed so that the tank is completely full in exactly 18 minutes?
(a) 6 min
(b) 8 min
(c) 10 min
(d) 12 min

**Solution:**
Total Capacity = $\text{LCM}(24, 32) = 96$ units.
Rates: $A = +4$, $B = +3$.
Since the tank is full in 18 minutes, Pipe A was open for the entire 18 minutes.
Work done by A = $18 \times 4 = 72$ units.
Remaining capacity to be filled by B = $96 - 72 = 24$ units.
Time B was open = $\frac{24}{3} = 8$ minutes.
Therefore, B should be closed after 8 minutes.

**Answer:** 8 min (b)

## Wrapped OA Variants

**Q18.** Server Alpha can process a batch of telemetry logs in 45 minutes, while Server Beta can process the same batch in 30 minutes. Both servers are spun up simultaneously to process a new batch. However, Server Beta crashes exactly 10 minutes into the job, and Server Alpha must finish the remaining logs alone. What is the total time taken to process the entire batch?
(a) 20 min
(b) 25 min
(c) 30 min
(d) 35 min

**Solution:**

::: interview
In system design or technical OAs, "workers" are often framed as servers, threads, or autonomous agents, and "work" as log processing, map-reduce tasks, or requests. The math is identical to a standard pipes-and-cisterns problem.
:::

Total Work = $\text{LCM}(45, 30) = 90$ units.
Rates: Alpha = $+2$, Beta = $+3$.
Combined rate = $5$ units/min.
Work done in the first 10 minutes (both active) = $10 \times 5 = 50$ units.
Remaining work = $90 - 50 = 40$ units.
Time for Alpha to finish the remainder = $\frac{40}{2} = 20$ minutes.
Total time = $10 \text{ (initial)} + 20 \text{ (alone)} = 30$ minutes.

**Answer:** 30 min (c)

**Q19.** Drone Swarm A can map a specified sector in 60 hours, while Swarm B can map it in 40 hours. An enemy jamming system, C, corrupts mapping data at a constant rate that would completely ruin a fully mapped sector in 120 hours. If both swarms are deployed while the jammer is active, how many hours will it take to successfully map the entire sector?
(a) 24 hours
(b) 30 hours
(c) 36 hours
(d) 40 hours

**Solution:**
This is a pipes and cisterns problem in disguise (two inlets, one outlet).
Total Work = $\text{LCM}(60, 40, 120) = 120$ units.
Rates: Swarm A = $+2$, Swarm B = $+3$, Jammer C = $-1$.
Effective rate = $2 + 3 - 1 = 4$ units/hour.
Time to map sector = $\frac{120}{4} = 30$ hours.

**Answer:** 30 hours (b)

## Sources

- IndiaBix — Time and Work basics & alternate day patterns — https://www.indiabix.com/aptitude/time-and-work/
- IndiaBix — Pipes and Cisterns standard models — https://www.indiabix.com/aptitude/pipes-and-cisterns/
- GeeksforGeeks Aptitude — MDH problems and worker-leaving traps — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- Hitbullseye — Wrapped server/processing scenarios — https://www.hitbullseye.com/
