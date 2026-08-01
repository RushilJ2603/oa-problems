# Permutations & Combinations

::: definition
**Fundamental Counting Principle:** If one event can occur in $m$ ways and a second independent event can occur in $n$ ways, the two events in succession can occur in $m \times n$ ways (Multiplication Principle). If one event OR another event can occur (mutually exclusive), they can occur in $m + n$ ways (Addition Principle).

**Permutation (Arrangement):** Order matters. The number of ways to arrange $r$ items selected from $n$ distinct items is:
$^{n}P_{r} = \frac{n!}{(n-r)!}$

**Combination (Selection):** Order does NOT matter. The number of ways to select $r$ items from $n$ distinct items is:
$^{n}C_{r} = \frac{n!}{r!(n-r)!}$
:::

## 1. Counting Principle & Number Formation

**Q1.** A person has 4 different shirts, 3 different pairs of pants, and 2 different pairs of shoes. In how many distinct ways can they dress up?
(a) 9
(b) 12
(c) 24
(d) 48

**Solution:**
By the fundamental multiplication principle, we multiply the independent choices:
$4 \times 3 \times 2 = 24$

**Answer:** $24$ (c)

**Q2.** How many 3-digit numbers can be formed from the digits 1, 2, 3, 4, 5 if repetition of digits is not allowed?
(a) 60
(b) 125
(c) 20
(d) 120

**Solution:**
We have 3 places to fill.
Hundreds place: 5 choices.
Tens place: 4 choices (one digit used).
Units place: 3 choices (two digits used).
Total ways = $5 \times 4 \times 3 = 60$
Alternatively, arrange 3 items from 5: $^{5}P_{3} = \frac{5!}{2!} = 60$

**Answer:** $60$ (a)

**Q3.** How many 4-digit numbers can be formed using the digits 0, 1, 2, 3, 4, 5 if repetition is allowed?
(a) 1296
(b) 1080
(c) 1200
(d) 720

**Solution:**
The thousands place cannot be 0 (otherwise it's a 3-digit number), so we have 5 choices (1-5).
The remaining three places can use any of the 6 digits since repetition is allowed.
Hundreds: 6 choices.
Tens: 6 choices.
Units: 6 choices.
Total = $5 \times 6 \times 6 \times 6 = 1080$

**Answer:** $1080$ (b)

**Q4.** How many 4-digit even numbers can be formed from the digits 0, 1, 2, 3, 4, 5 without repetition?
(a) 156
(b) 120
(c) 144
(d) 160

**Solution:**
An even number must end in 0, 2, or 4. When 0 is among the digits, handle it separately to avoid leading zeros.
Case 1: Ends in 0.
Units place: 1 choice (0).
The remaining 3 places can be filled by the remaining 5 digits in $5 \times 4 \times 3 = 60$ ways.
Case 2: Ends in 2 or 4.
Units place: 2 choices (2 or 4).
Thousands place: cannot be 0 and cannot be the unit digit, so 4 choices.
Hundreds place: 4 choices (0 becomes available).
Tens place: 3 choices.
Ways = $2 \times 4 \times 4 \times 3 = 96$
Total = $60 + 96 = 156$

::: trap
A common mistake is treating all even endings identically: "3 choices for the last digit, so $4 \times 4 \times 3 \times 3$". This fails because if 0 is the last digit, it CANNOT be the first digit, changing the number of choices for the thousands place. Always split cases for 0.
:::

**Answer:** $156$ (a)

## 2. Permutations

**Q5.** In how many different ways can the letters of the word 'SMART' be arranged?
(a) 25
(b) 60
(c) 120
(d) 240

**Solution:**
'SMART' has 5 distinct letters.
The number of ways to arrange them is $5! = 120$.

**Answer:** $120$ (c)

**Q6.** In how many different ways can the letters of the word 'SUCCESS' be arranged?
(a) 5040
(b) 420
(c) 840
(d) 1260

**Solution:**
'SUCCESS' has 7 letters. Frequencies: S appears 3 times, C appears 2 times, U and E appear 1 time each.
When items are identical, divide the total factorial by the factorials of the identical counts:
$\frac{7!}{3! \times 2!} = \frac{5040}{6 \times 2} = 420$

**Answer:** $420$ (b)

**Q7.** In how many ways can the letters of the word 'OPTICAL' be arranged so that the vowels always come together?
(a) 720
(b) 5040
(c) 120
(d) 4320

**Solution:**
'OPTICAL' has 7 letters. Vowels are O, I, A (3). Consonants are P, T, C, L (4).
Group the vowels together and treat them as a single entity: (OIA), P, T, C, L.
This gives us 5 entities to arrange, which can be done in $5! = 120$ ways.
Inside the group, the 3 vowels can be arranged among themselves in $3! = 6$ ways.
Total ways = $120 \times 6 = 720$

::: keypoint
**The Bundle Trick:** Whenever items must be "always together", tie them into a single bundle. Arrange the bundles + loose items, then multiply by the internal arrangements of the bundle.
:::

**Answer:** $720$ (a)

**Q8.** In how many ways can 4 boys and 3 girls be seated in a row so that no two girls sit together?
(a) 144
(b) 5040
(c) 1440
(d) 720

**Solution:**
To ensure no two girls sit together, first seat the 4 boys. They can be arranged in $4! = 24$ ways.
This creates 5 potential gaps (including the ends) where the girls can sit:
_ B _ B _ B _ B _
We have 5 gaps and 3 girls. We select and arrange the 3 girls into these 5 gaps in $^{5}P_{3}$ ways.
$^{5}P_{3} = 5 \times 4 \times 3 = 60$
Total ways = $24 \times 60 = 1440$

::: keypoint
**The Gap Method:** When items must be separated ("no two together"), arrange the *other* items first, count the gaps between them (including ends), and place the restricted items in those gaps using Permutations ($^{n}P_{r}$).
:::

**Answer:** $1440$ (c)

**Q9.** In how many ways can 6 people be seated around a circular table?
(a) 720
(b) 120
(c) 60
(d) 360

**Solution:**
For a circular arrangement, placing the first person fixes the starting point. The remaining $(n-1)$ people can be arranged around them.
Ways = $(6 - 1)! = 5! = 120$

::: trap
Do not use $n!$ for circular tables. A circle has no fixed start or end, so rotating the same relative seating order doesn't create a new arrangement. Always use $(n-1)!$.
:::

**Answer:** $120$ (b)

**Q10.** In how many ways can a necklace be formed using 8 distinct colored beads?
(a) 5040
(b) 40320
(c) 2520
(d) 20160

**Solution:**
Circular arrangements of 8 items give $(8-1)! = 7! = 5040$ ways.
However, a necklace can be flipped over (clockwise and counter-clockwise arrangements are physically identical).
So, we divide by 2:
$\frac{7!}{2} = \frac{5040}{2} = 2520$

**Answer:** $2520$ (c)

## 3. Combinations

**Q11.** A committee of 4 members is to be formed from 6 men and 5 women. In how many ways can this be done?
(a) 330
(b) 7920
(c) 11! / 4!
(d) 120

**Solution:**
We are selecting 4 people out of $6 + 5 = 11$ people. Order of selection does not matter.
$^{11}C_{4} = \frac{11 \times 10 \times 9 \times 8}{4 \times 3 \times 2 \times 1} = 330$

**Answer:** $330$ (a)

**Q12.** At a party, everyone shakes hands with everyone else exactly once. If there are a total of 66 handshakes, how many people are at the party?
(a) 11
(b) 12
(c) 13
(d) 14

**Solution:**
A handshake is a selection of 2 people from $n$ people, which is $^{n}C_{2}$.
$^{n}C_{2} = 66 \implies \frac{n(n-1)}{2} = 66 \implies n(n-1) = 132$
Since $12 \times 11 = 132$, there are 12 people.
*(Also useful for diagonals of a polygon: a polygon of $n$ sides has $^{n}C_{2} - n$ diagonals).*

**Answer:** $12$ (b)

**Q13.** A team of 5 is to be formed from 6 boys and 4 girls. In how many ways can it be done if the team must contain exactly 2 girls?
(a) 120
(b) 60
(c) 160
(d) 240

**Solution:**
We need exactly 2 girls from 4, and the remaining 3 members must be boys from the 6.
Ways to select girls = $^{4}C_{2} = \frac{4 \times 3}{2 \times 1} = 6$
Ways to select boys = $^{6}C_{3} = \frac{6 \times 5 \times 4}{3 \times 2 \times 1} = 20$
Total ways = $6 \times 20 = 120$

**Answer:** $120$ (a)

**Q14.** From 5 consonants and 4 vowels, how many words of 3 consonants and 2 vowels can be formed?
(a) 60
(b) 120
(c) 7200
(d) 14400

**Solution:**
First, **select** the letters:
Ways to select 3 consonants from 5 = $^{5}C_{3} = 10$
Ways to select 2 vowels from 4 = $^{4}C_{2} = 6$
Total selections = $10 \times 6 = 60$.
Second, **arrange** the 5 selected letters to form words:
$5! = 120$.
Total words = $60 \times 120 = 7200$.

**Answer:** $7200$ (c)

**Q15.** A committee of 3 people is to be chosen from 4 men and 5 women. In how many ways can this be done if it must include at least one man?
(a) 74
(b) 84
(c) 64
(d) 94

**Solution:**
Method 1 (Direct): 1M, 2W + 2M, 1W + 3M, 0W
$(^{4}C_{1} \times ^{5}C_{2}) + (^{4}C_{2} \times ^{5}C_{1}) + (^{4}C_{3} \times ^{5}C_{0}) = (4 \times 10) + (6 \times 5) + (4 \times 1) = 40 + 30 + 4 = 74$.

Method 2 (Subtraction / "All minus None"):
Total ways to pick 3 people from 9 = $^{9}C_{3} = \frac{9 \times 8 \times 7}{3 \times 2 \times 1} = 84$.
Ways to pick 0 men (all 3 are women) = $^{5}C_{3} = 10$.
Ways with at least one man = Total - (None) = $84 - 10 = 74$.

::: keypoint
**"At Least One" Trick:** Whenever a problem says "at least one", it is almost always faster to calculate Total Possible - Cases with None.
:::

**Answer:** $74$ (a)

## 4. Distribution & Grouping

**Q16.** In how many ways can 9 different books be distributed among 3 students such that the first student gets 4 books, the second gets 3 books, and the third gets 2 books?
(a) 1260
(b) 2520
(c) 3150
(d) 5040

**Solution:**
We are forming groups of distinct items of sizes 4, 3, and 2, and handing them to specific people.
First student gets 4 books from 9: $^{9}C_{4}$
Second student gets 3 books from the remaining 5: $^{5}C_{3}$
Third student gets 2 books from the remaining 2: $^{2}C_{2}$
Total ways = $\frac{9!}{4!5!} \times \frac{5!}{3!2!} \times \frac{2!}{2!0!} = \frac{9!}{4!3!2!} = 1260$

**Answer:** $1260$ (a)

**Q17.** In how many ways can 6 distinct students be divided into 3 equal groups of 2 students each?
(a) 90
(b) 15
(c) 120
(d) 30

**Solution:**
We divide 6 distinct items into groups of sizes 2, 2, and 2.
Using the formula, this is initially $\frac{6!}{2!2!2!}$.
However, because the three groups are of *equal size* and are indistinguishable (they are just "groups", not assigned to specific rooms or labels), we have overcounted their permutations. We must divide by $3!$ to correct for the identical group sizes.
Total ways = $\frac{6!}{2!2!2!} \times \frac{1}{3!} = \frac{720}{8 \times 6} = 15$

::: trap
When dividing $n$ distinct items into equal, unlabelled groups of size $r$, always divide by the factorial of the number of identical groups ($k!$) to avoid overcounting permutations of the groups themselves.
:::

**Answer:** $15$ (b)

**Q18.** In how many ways can 10 identical apples be distributed among 3 children such that each child can receive any number of apples (including zero)?
(a) 66
(b) 120
(c) 36
(d) 220

**Solution:**
This is a classic "identical objects into distinct bins" problem, solved by Stars and Bars.
Number of ways to distribute $n$ identical items into $r$ distinct bins is $^{n+r-1}C_{r-1}$.
Here, $n = 10$, $r = 3$.
Ways = $^{10+3-1}C_{3-1} = ^{12}C_{2} = \frac{12 \times 11}{2} = 66$
*(Note: We will cover Stars and Bars in depth in a later section).*

**Answer:** $66$ (a)

## 5. Wrapped OA Variants

**Q19.** An Uber driver needs to navigate a grid-like city block from point $(0,0)$ to point $(4,3)$. They can only travel Right (R) or Up (U). How many distinct shortest paths can the driver take?
(a) 12
(b) 35
(c) 144
(d) 7

**Solution:**
Any shortest path from $(0,0)$ to $(4,3)$ requires exactly 4 Right moves and 3 Up moves, in some order (e.g., R-R-U-R-U-U-R).
The problem reduces to arranging 7 items where 4 are identical (R) and 3 are identical (U).
Total paths = $\frac{7!}{4!3!} = \frac{7 \times 6 \times 5}{3 \times 2 \times 1} = 35$
Alternatively, out of 7 total steps, choose 4 to be Right: $^{7}C_{4} = 35$.

**Answer:** $35$ (b)

**Q20.** A software system requires a 5-character password using uppercase letters (A-Z) and digits (0-9). The password must start with a letter and contain at least one digit. Repetition is allowed. How many valid passwords exist?
(a) $26 \times 36^{4}$
(b) $26 \times (36^{4} - 26^{4})$
(c) $36^{5} - 26^{5}$
(d) $26 \times 10^{4}$

**Solution:**
The password has 5 slots.
Slot 1 must be a letter: 26 choices.
Slots 2 to 5 can be letters or digits: 36 choices each.
Total unrestricted passwords starting with a letter = $26 \times 36 \times 36 \times 36 \times 36 = 26 \times 36^{4}$.
The constraint is "at least one digit". We use the subtraction trick:
Passwords starting with a letter but containing NO digits (all letters) = $26 \times 26 \times 26 \times 26 \times 26 = 26^{5}$.
Valid passwords = Total - (All Letters) = $26 \times 36^{4} - 26^{5} = 26 \times (36^{4} - 26^{4})$.

**Answer:** Option (b)

**Q21.** A high-frequency trading firm has an assessment involving 4 quants and 4 developers. They must sit in a row of 8 chairs. To facilitate cross-team communication, no two quants can sit next to each other, and no two developers can sit next to each other. In how many ways can they be seated?
(a) 1152
(b) 576
(c) 40320
(d) 2304

**Solution:**
This requires an alternating pattern: either Q-D-Q-D-Q-D-Q-D or D-Q-D-Q-D-Q-D-Q.
Case 1: Quants in odd seats, Developers in even seats.
Quants arrange among themselves in $4! = 24$ ways.
Developers arrange among themselves in $4! = 24$ ways.
Ways = $24 \times 24 = 576$.
Case 2: Developers in odd seats, Quants in even seats.
By the same logic, $24 \times 24 = 576$ ways.
Total = $576 + 576 = 1152$.

::: interview
In tricky arrangement OAs, watch out for the difference between "no two X sit together" (Gap Method) and "must alternate" (Specific overlapping patterns). The Gap Method on 4 Quants and 4 Devs would yield $4! \times ^{5}P_{4} = 24 \times 120 = 2880$ ways where Quants are separated, but that allows Devs to sit together (e.g., Q-D-D-Q-D-Q-D-Q). To separate *both* groups, they must alternate.
:::

**Answer:** $1152$ (a)

## Rank of a Word (Dictionary Order)

**Q22.** If all distinct arrangements of the letters of **MEAT** are listed in dictionary order, what is the rank
of the word MEAT?
(a) $12$ (b) $15$ (c) $18$ (d) $24$

**Solution:** Sort the letters: $A, E, M, T$. Count arrangements that come before MEAT, letter by letter.

- **First letter $<$ M** ($A$ or $E$): $2$ choices, each fixing $3! = 6$ arrangements $\Rightarrow 2 \times 6 = 12$.
- First letter $=$ M, **second $<$ E** (only $A$): $1 \times 2! = 2$.
- First $=$ M, second $=$ E, **third $<$ A**: none $\Rightarrow 0$.
- M, E, A fixed, then T — this is MEAT itself.

Rank $= 12 + 2 + 0 + 1 = 15$.

**Answer:** $15$ (b)

::: keypoint
Rank $=$ (words that precede it) $+ 1$. At each position, count how many *unused* letters are smaller than the
actual letter, multiply by the factorial of the remaining positions, and sum. Divide by repeated-letter
factorials if any letter repeats.
:::

## Sources

- IndiaBix — https://www.indiabix.com/aptitude/permutation-and-combination/
- PrepInsta — https://prepinsta.com/aptitude/permutation-and-combination/
- Hitbullseye — https://www.hitbullseye.com/Permutation-and-Combination.php
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/
