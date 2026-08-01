# Clocks & Calendars

::: keypoint
**Clocks:**

- **Speeds:** Minute hand moves $6^{\circ}/\text{min}$. Hour hand moves $0.5^{\circ}/\text{min}$.
- **Relative speed:** The minute hand closes the gap on the hour hand at $5.5^{\circ}/\text{min}$.
- **Coincidence:** Hands coincide exactly every $65\frac{5}{11}$ minutes.
- **Angle formula:** The angle $\theta$ at $H$ hours and $M$ minutes is $\theta = |30H - 5.5M|^{\circ}$.

**Calendars:**

- **Odd Days:** The remainder when total days are divided by $7$. Mapped as: $0 = \text{Sun}$, $1 = \text{Mon}$, $2 = \text{Tue}$, $3 = \text{Wed}$, $4 = \text{Thu}$, $5 = \text{Fri}$, $6 = \text{Sat}$.
- **Normal year:** $365$ days $\equiv 1$ odd day. Advances the calendar by $1$ weekday.
- **Leap year:** $366$ days $\equiv 2$ odd days. Advances the calendar by $2$ weekdays.
- **Leap year rule:** A year is leap if divisible by $4$, except century years which must be divisible by $400$.
- **Centuries:** 100 years = $5$ odd days; 200 years = $3$; 300 years = $1$; 400 years = $0$.
:::

## Clocks — angle

**Q1.** What is the angle between the hands of a clock at 8:20?
(a) $120^{\circ}$ (b) $130^{\circ}$ (c) $140^{\circ}$ (d) $150^{\circ}$

**Solution:** Use the angle formula $\theta = |30H - 5.5M|^{\circ}$.

$\theta = |30(8) - 5.5(20)| = |240 - 110| = 130^{\circ}$.

**Answer:** $130^{\circ}$ (b)

**Q2.** What is the reflex angle between the hands of a clock at 10:25?
(a) $162.5^{\circ}$ (b) $187.5^{\circ}$ (c) $197.5^{\circ}$ (d) $212.5^{\circ}$

**Solution:** First, find the inner angle: $\theta = |30(10) - 5.5(25)| = |300 - 137.5| = 162.5^{\circ}$.

The reflex angle is $360^{\circ} - 162.5^{\circ} = 197.5^{\circ}$.

**Answer:** $197.5^{\circ}$ (c)

**Q3.** At what times between 5:00 and 6:00 are the hands of a clock at exactly a right angle?
(a) $5:10\frac{10}{11}$ and $5:43\frac{7}{11}$ (b) $5:11$ and $5:44$ (c) $5:15$ and $5:45$ (d) $5:10$ and $5:40$

**Solution:** Set the angle formula to $90^{\circ}$: $|30(5) - 5.5M| = 90$.

Case 1 (minute hand behind): $150 - 5.5M = 90 \implies 5.5M = 60 \implies M = \frac{120}{11} = 10\frac{10}{11}$.

Case 2 (minute hand ahead): $5.5M - 150 = 90 \implies 5.5M = 240 \implies M = \frac{480}{11} = 43\frac{7}{11}$.

**Answer:** $5:10\frac{10}{11}$ and $5:43\frac{7}{11}$ (a)

## Clocks — coincidence / opposite / right angle

**Q4.** How many times in a standard 24-hour day do the hands of a clock coincide, point in opposite directions, and form right angles, respectively?
(a) 24, 24, 48 (b) 22, 22, 44 (c) 22, 24, 44 (d) 24, 22, 48

**Solution:** 

- Coincide ($0^{\circ}$): 11 times every 12 hours (missing exactly at 12:00 twice) $\implies 22$ times/day.
- Opposite ($180^{\circ}$): 11 times every 12 hours (missing exactly at 6:00 twice) $\implies 22$ times/day.
- Right angles ($90^{\circ}$): 22 times every 12 hours $\implies 44$ times/day.

**Answer:** 22, 22, 44 (b)

**Q5.** At what exact time between 3 o'clock and 4 o'clock will the hands of a watch coincide?
(a) $15\frac{3}{11}$ min past 3 (b) $16\frac{4}{11}$ min past 3 (c) $17\frac{5}{11}$ min past 3 (d) $18$ min past 3

**Solution:** Set the angle to $0^{\circ}$: $|30(3) - 5.5M| = 0 \implies 90 = 5.5M$.

$M = \frac{180}{11} = 16\frac{4}{11}$.

::: trap
**Trap:** Thinking the minute hand closes the gap at a simple $6^{\circ}/\text{min}$. Because the hour hand is also retreating at $0.5^{\circ}/\text{min}$, the true closing speed is the difference: $5.5^{\circ}/\text{min}$. Almost all clock times rely on this $5.5$ relative divisor.
:::

**Answer:** $16\frac{4}{11}$ min past 3 (b)

**Q6.** At what exact time between 4 o'clock and 5 o'clock will the hands of a clock point in opposite directions?
(a) $45$ min past 4 (b) $50\frac{4}{11}$ min past 4 (c) $54\frac{6}{11}$ min past 4 (d) $55\frac{5}{11}$ min past 4

**Solution:** Set the angle to $180^{\circ}$: $|30(4) - 5.5M| = 180$.

Since the minute hand must be ahead of the hour hand to oppose it past 4:00, we use $5.5M - 120 = 180$.

$5.5M = 300 \implies M = \frac{600}{11} = 54\frac{6}{11}$.

**Answer:** $54\frac{6}{11}$ min past 4 (c)

## Clocks — faulty / gaining–losing

**Q7.** A clock is set perfectly right at 5 a.m. The clock loses 16 minutes every 24 hours. What will be the true time when the clock indicates 10 p.m. on the fourth day?
(a) 9 p.m. (b) 10 p.m. (c) 11 p.m. (d) 12 a.m.

**Solution:** Find the total elapsed shown time: 5 a.m. Day 1 to 10 p.m. Day 4 = 3 days and 17 hours = $89$ hours.

In $24$ true hours, the faulty clock shows $24 - \frac{16}{60} = 23\frac{44}{60} = \frac{356}{15}$ hours.

The ratio of True time to Shown time is $\frac{24}{356/15} = \frac{360}{356} = \frac{90}{89}$.

True time elapsed = $89 \times \frac{90}{89} = 90$ hours.

$90$ hours = 3 days ($72$ hours) + $18$ hours. $18$ hours past 5 a.m. is 11 p.m.

**Answer:** 11 p.m. (c)

**Q8.** A clock gains 10 minutes every 24 hours. If it is set right at 8 a.m. on Monday, what is the true time when it shows 1 p.m. on the following day (Tuesday)?
(a) 12:48 p.m. (b) 12:50 p.m. (c) 1:10 p.m. (d) 1:12 p.m.

**Solution:** Elapsed shown time: 8 a.m. Monday to 1 p.m. Tuesday = $29$ hours.

In $24$ true hours, the faulty clock shows $24$ hr $10$ min = $24\frac{1}{6} = \frac{145}{6}$ hours.

Ratio of True time to Shown time is $\frac{24}{145/6} = \frac{144}{145}$.

True time elapsed = $29 \times \frac{144}{145} = \frac{144}{5} = 28.8$ hours = $28$ hours and $48$ minutes.

$28$ hours and $48$ minutes past 8 a.m. Monday is 12:48 p.m. Tuesday.

**Answer:** 12:48 p.m. (a)

**Q9.** The hands of a clock overlap every 64 minutes of true time. How much time does the clock gain or lose in a full 24-hour day?
(a) Loses $32\frac{8}{11}$ min (b) Gains $32\frac{8}{11}$ min (c) Loses $33\frac{1}{11}$ min (d) Gains $33\frac{1}{11}$ min

**Solution:** A perfect clock overlaps exactly every $\frac{720}{11} = 65\frac{5}{11}$ minutes. 

Because this clock overlaps in only $64$ minutes, it is running fast (gaining time).

Gain per $64$ true minutes = $65\frac{5}{11} - 64 = \frac{16}{11}$ minutes.

In a full day ($1440$ minutes), total gain = $\frac{16}{11} \times \frac{1440}{64} = \frac{16}{11} \times \frac{45}{2} = \frac{360}{11} = 32\frac{8}{11}$ minutes.

**Answer:** Gains $32\frac{8}{11}$ min (b)

## Calendars — day of week

**Q10.** What was the day of the week on 15th August, 1947?
(a) Thursday (b) Friday (c) Saturday (d) Sunday

**Solution:** Calculate odd days from year 1 to Aug 15, 1947.

Centuries: 1600 ($0$ odd days), 300 ($1$ odd day) $\implies$ up to 1900 = $1$ odd day.

Years 1901–1946 ($46$ years): $46 / 4 = 11$ leap years, $35$ normal years.

Odd days = $(11 \times 2) + (35 \times 1) = 57 \equiv 1 \pmod 7$.

Total up to 1946: $1 + 1 = 2$ odd days.

In 1947 (normal year): Jan($3$), Feb($0$), Mar($3$), Apr($2$), May($3$), Jun($2$), Jul($3$), Aug($15$).

Sum = $3+0+3+2+3+2+3+15 = 31 \equiv 3 \pmod 7$.

Total odd days = $2 + 3 = 5 \implies$ Friday ($0$=Sun, $1$=Mon, $\ldots$, $5$=Fri).

**Answer:** Friday (b)

**Q11.** What was the day of the week on 28th May, 2006?
(a) Thursday (b) Friday (c) Saturday (d) Sunday

**Solution:** 

Up to 2000: $0$ odd days.

2001–2005 ($5$ years): $1$ leap, $4$ normal $\implies (1 \times 2) + (4 \times 1) = 6$ odd days.

In 2006: Jan($3$), Feb($0$), Mar($3$), Apr($2$), May($28$).

Sum = $3+0+3+2+28 = 36 \equiv 1 \pmod 7$.

Total = $6 + 1 = 7 \equiv 0 \pmod 7 \implies$ Sunday.

**Answer:** Sunday (d)

**Q12.** If today is Monday, what day of the week will it be 61 days from today?
(a) Saturday (b) Sunday (c) Monday (d) Tuesday

**Solution:** Find the odd days in 61 days.

$61 \pmod 7 = 5$.

Monday + $5$ days = Saturday (or simply Monday - $2$ days).

**Answer:** Saturday (a)

**Q13.** If January 1, 2006 was a Sunday, what day of the week was January 1, 2010?
(a) Wednesday (b) Thursday (c) Friday (d) Saturday

**Solution:** Count the odd days contributed by each intervening year.

2006 (normal) = $1$

2007 (normal) = $1$

2008 (leap) = $2$

2009 (normal) = $1$

Total = $1+1+2+1 = 5$ odd days.

Sunday + $5$ days = Friday.

**Answer:** Friday (c)

## Calendars — leap years & repetition

**Q14.** How many leap years are there from 1890 to 1920 (inclusive)?
(a) 7 (b) 8 (c) 9 (d) 10

**Solution:** List the multiples of 4 in the range: 1892, 1896, 1900, 1904, 1908, 1912, 1916, 1920.

::: trap
**Trap:** Assuming every 4th year is a leap year without exception. A century year (ending in 00) is ONLY a leap year if it is divisible by 400. Thus, 1900 and 2100 are NOT leap years, but 2000 is.
:::

Because 1900 is not divisible by 400, it is not a leap year. 
Valid leap years are: 1892, 1896, 1904, 1908, 1912, 1916, 1920 ($7$ years).

**Answer:** 7 (a)

**Q15.** The calendar for the year 2007 will be the same for the year:
(a) 2014 (b) 2016 (c) 2017 (d) 2018

**Solution:** A calendar repeats when the net odd days accumulate to a multiple of 7, and the year type (leap/normal) matches.

2007 (normal year) is Year 3 after the previous leap year (2004).

::: keypoint
**Calendar Repetition Shortcut:**
For any year, find its position relative to the previous leap year:

- **Leap Year + 1:** Repeats in 6 years.
- **Leap Year + 2:** Repeats in 11 years.
- **Leap Year + 3:** Repeats in 11 years.
- **Leap Year itself:** Repeats in 28 years.
:::

Since 2007 is Leap + 3, it repeats in $11$ years. $2007 + 11 = 2018$.

**Answer:** 2018 (d)

**Q16.** Which of the following cannot be the last day of a century?
(a) Tuesday (b) Wednesday (c) Friday (d) Monday

**Solution:** Compute odd days for centuries.

- 100 years $\implies 5$ odd days $\implies$ Friday
- 200 years $\implies 3$ odd days $\implies$ Wednesday
- 300 years $\implies 1$ odd day $\implies$ Monday
- 400 years $\implies 0$ odd days $\implies$ Sunday

This cycle repeats. The last day of a century can only be Friday, Wednesday, Monday, or Sunday. It cannot be Tuesday, Thursday, or Saturday.

**Answer:** Tuesday (a)

## Wrapped OA variants

**Q17.** Alice schedules a recurring software deployment that happens exactly every 15 days. If a scheduled deployment falls on a weekend, it is automatically shifted to the following Monday. The first deployment occurs on Tuesday, March 1, 2023. What day of the week will the 5th deployment actually occur on?
(a) Thursday (b) Friday (c) Saturday (d) Monday

**Solution:** The cadence is 15 days, which is exactly $2$ weeks and $1$ day. This means each standard scheduled deployment shifts forward by $1$ weekday.

- 1st: Tuesday
- 2nd (+15 days): Wednesday
- 3rd (+30 days): Thursday
- 4th (+45 days): Friday
- 5th (+60 days): Saturday

The 5th deployment lands on a Saturday. Per the rule, it is shifted to the following Monday.

**Answer:** Monday (d)

**Q18.** A high-frequency trading server reboots on a cycle of "3 days online, 2 days offline" (a 5-day cycle). The very first reboot starts on a Sunday. What is the minimum number of days that must elapse before a new cycle starts on a Sunday again?
(a) 15 (b) 20 (c) 30 (d) 35

**Solution:** For the cycle to begin on a Sunday again, the total number of elapsed days must be a multiple of 7 (the length of a week).

The length of one full server cycle is $5$ days.

We need the smallest positive integer that is a common multiple of $5$ and $7$, which is $\text{LCM}(5, 7) = 35$.

It takes exactly $35$ days (or $7$ full cycles) to reset to a Sunday start.

**Answer:** 35 (d)

## Mirror-Image Time

**Q19.** A clock seen in a vertical mirror shows the time as $3{:}40$. What is the actual time?
(a) $8{:}20$ (b) $9{:}20$ (c) $7{:}40$ (d) $8{:}40$

**Solution:** A vertical mirror reflects a clock face left↔right, so the mirror time and the true time add up to
$12{:}00$. Compute the actual time as $11{:}60 - (\text{shown time})$: $11{:}60 - 3{:}40 = 8{:}20$.

**Answer:** $8{:}20$ (a)

::: keypoint
Mirror image of a clock time $= 11{:}60 - \text{time}$ (i.e. subtract from $12$). For a time between $12{:}00$ and
$1{:}00$, subtract from $23{:}60$ instead. Quick check: mirror-time $+$ true-time always makes a full $12$ hours.
:::

## Sources

- IndiaBix — Aptitude / Clock — https://www.indiabix.com/aptitude/clock/
- IndiaBix — Aptitude / Calendar — https://www.indiabix.com/aptitude/calendar/
- GeeksforGeeks — Aptitude Questions — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
- Hitbullseye — Clocks and Calendars — https://www.hitbullseye.com/Clocks-and-Calendars.php
