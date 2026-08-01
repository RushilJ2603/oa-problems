# Additional OA Reasoning Formats

## Logical Venn Diagrams

::: definition
**Convention:** You are given three categories (e.g., A, B, C) and asked which of four Venn diagrams best represents their relationship. The solution requires evaluating whether the categories are disjoint, partially overlapping (some A are B), or fully contained (all A are B).
:::

**Q1.** Which diagram best represents the relationship between: **Dog, Animal, Pet**?

(a) Three completely separate circles
(b) One large circle containing two smaller overlapping circles
(c) One large circle containing two smaller separate circles
(d) Three overlapping circles

**Solution:**
All dogs are animals, and all pets are animals. Therefore, both the "Dog" and "Pet" circles must be completely contained within the large "Animal" circle. Furthermore, some dogs are pets, some dogs are not pets (e.g., wild dogs), and some pets are not dogs (e.g., cats). Therefore, the "Dog" and "Pet" circles must partially overlap each other inside the "Animal" circle.

**Answer:** (b) One large circle containing two smaller overlapping circles

**Q2.** Which diagram best represents the relationship between: **Doctor, Man, Father**?

(a) Three overlapping circles
(b) One circle completely inside another, with a third circle intersecting both
(c) One circle inside another, and a third separate circle
(d) One large circle containing two smaller separate circles

**Solution:**
All fathers are men. Therefore, the "Father" circle is completely contained inside the "Man" circle. A doctor can be a man and a father, a man but not a father, or neither (e.g., a woman). Thus, the "Doctor" circle must intersect both the "Father" circle and the "Man" circle, while also having a section outside the "Man" circle.

**Answer:** (b) One circle completely inside another, with a third circle intersecting both

**Q3.** Which diagram best represents the relationship between: **Table, Furniture, Wood**?

(a) Three overlapping circles
(b) One large circle containing two smaller overlapping circles
(c) One circle inside another, with a third intersecting both
(d) One large circle containing a smaller circle, with a third circle entirely separate

**Solution:**
All tables are furniture, so the "Table" circle is completely inside the "Furniture" circle. Wood is a material; some tables are made of wood, and some furniture (other than tables) is made of wood. Also, there is wood that is not furniture. Therefore, the "Wood" circle intersects both the "Table" circle and the broader "Furniture" circle.

**Answer:** (c) One circle inside another, with a third intersecting both

## Statement & Course of Action

::: definition
**Convention:** You are given a situation (the statement) and two suggested actions (I and II). You must decide which action(s) logically *follow*. An action follows only if it is a proper, feasible, and practical response to the problem that reduces or solves it.
:::

::: trap
An action does not follow if it only partly addresses the issue while ignoring the main problem, if it creates a larger secondary problem, or if it is an extreme overreaction to a minor issue.
:::

**Q4.** **Statement:** A severe drought has been reported in many districts of State X, leading to crop failures.
**Courses of Action:**

I. The government should immediately provide financial assistance and relief materials to the affected farmers.
II. All the people from the affected districts should be forced to migrate to neighboring states.

(a) Only I follows
(b) Only II follows
(c) Both I and II follow
(d) Neither I nor II follows

**Solution:**
Action I is a direct, practical, and standard governmental response to a natural disaster to mitigate hardship. It follows. Action II is an extreme, impractical, and human-rights-violating overreaction. It does not follow.

**Answer:** (a) Only I follows

**Q5.** **Statement:** A large number of fatal traffic accidents have been occurring on Highway 42 due to over-speeding.
**Courses of Action:**

I. The government should ban all private vehicles from using Highway 42.
II. The traffic police should deploy speed cameras and increase patrols to penalize speeders.

(a) Only I follows
(b) Only II follows
(c) Both I and II follow
(d) Neither I nor II follows

**Solution:**
Action I is an absurd overreaction that stops the utility of the highway entirely; it does not follow. Action II directly targets the root cause (over-speeding) in a feasible and standard law-enforcement manner; it follows.

**Answer:** (b) Only II follows

**Q6.** **Statement:** Company ABC has seen its smartphone sales drop by $30\%$ over the last quarter.
**Courses of Action:**

I. The company should immediately shut down its smartphone division.
II. The company should conduct market research to understand the cause of the decline and adjust its strategy.

(a) Only I follows
(b) Only II follows
(c) Both I and II follow
(d) Neither I nor II follows

**Solution:**
Action I is a premature extreme measure for a single bad quarter. Action II is the logical, measured business response to identify and fix the issue.

**Answer:** (b) Only II follows

## Assertion (A) & Reason (R)

::: definition
**Convention:** You are given an Assertion (A) and a Reason (R). You must choose:

(a) Both A and R are true and R is the correct explanation of A.
(b) Both A and R are true but R is NOT the correct explanation of A.
(c) A is true but R is false.
(d) A is false but R is true.
:::

::: trap
In option (b), the Reason is a factually correct statement on its own, but it fails to *explain* why the Assertion happens. Always insert a "because" between A and R to test the explanatory link.
:::

**Q7.** **Assertion (A):** We feel comfortable wearing white clothes in summer.
**Reason (R):** White clothes are bad absorbers and good reflectors of heat.

(a) Both true & R explains A
(b) Both true, R does NOT explain A
(c) A true, R false
(d) A false, R true

**Solution:**
A is true; white clothes are preferred in summer. R is true; the physics principle is correct. Does R explain A? Yes, reflecting heat keeps the body cooler, leading to comfort.

**Answer:** (a) Both true & R explains A

**Q8.** **Assertion (A):** Diamond is used for cutting glass.
**Reason (R):** Diamond has a high refractive index.

(a) Both true & R explains A
(b) Both true, R does NOT explain A
(c) A true, R false
(d) A false, R true

**Solution:**
A is true; diamond is a standard glass-cutting tool. R is true; diamond does have a high refractive index (which causes its sparkle). Does R explain A? No. Diamond cuts glass because it is extremely hard (highest on the Mohs scale), not because it bends light.

**Answer:** (b) Both true, R does NOT explain A

**Q9.** **Assertion (A):** The boiling point of water decreases at higher altitudes.
**Reason (R):** The atmospheric pressure is higher at higher altitudes.

(a) Both true & R explains A
(b) Both true, R does NOT explain A
(c) A true, R false
(d) A false, R true

**Solution:**
A is true; water boils faster (at a lower temperature) on mountains. R is false; atmospheric pressure *decreases* at higher altitudes, which is exactly why the boiling point drops.

**Answer:** (c) A true, R false

**Q10.** **Assertion (A):** Silver is not used to make electric wires for domestic use.
**Reason (R):** Silver is a bad conductor of electricity.

(a) Both true & R explains A
(b) Both true, R does NOT explain A
(c) A true, R false
(d) A false, R true

**Solution:**
A is true; we use copper or aluminum, not silver, primarily due to cost. R is false; silver is actually the *best* metallic conductor of electricity.

**Answer:** (c) A true, R false

## Input–Output (Machine) Reasoning

::: definition
**Convention:** A word/number arrangement machine processes an input string step-by-step according to a fixed logical rule. You must deduce the rule by comparing the Input to Step I, Step I to Step II, and so on, until the final step. Then apply this exact rule to a new input string.
:::

**Common Rules:** Elements might be sorted alphabetically, numerically (ascending/descending), or alternating. Shifts can happen on the left end, right end, or both.

**Directions for Q11–Q14:** Study the given information and answer the questions.
A machine rearranges a line of words and numbers using a specific rule.
**Input:** `85 say 14 cold 42 deep 90 base`
**Step I:** `90 85 say 14 cold 42 deep base`
**Step II:** `90 base 85 say 14 cold 42 deep`
**Step III:** `90 base 85 cold say 14 42 deep`
**Step IV:** `90 base 85 cold 42 say 14 deep`
**Step V:** `90 base 85 cold 42 deep say 14`
**Step VI:** `90 base 85 cold 42 deep 14 say`
Step VI is the last step for this input.

**Q11.** What is the rule of the machine?

**Solution:**
Look at the final output (Step VI): `90 base 85 cold 42 deep 14 say`. The pattern alternates a number and a word.
The numbers are strictly descending: $90 > 85 > 42 > 14$.
The words are strictly alphabetical: `base`, `cold`, `deep`, `say`.
Looking at the step-by-step changes, the machine processes one element per step, moving it to the front (left side) of the *unprocessed* string.
Step I brings the highest number (`90`) to the extreme left.
Step II brings the first alphabetical word (`base`) to the second position.
It alternates this process. If an element is already in the correct position for that step, it takes no action on it and brings the next required element instead.

**Answer:** The machine alternates bringing the highest available number and the earliest available alphabetical word to the left side, one per step.

**Q12.** Given the **Input:** `64 toll 22 fall 38 ask 75 mass`, what will be **Step III**?

(a) `75 ask 64 toll 22 fall 38 mass`
(b) `75 ask 64 fall toll 22 38 mass`
(c) `75 ask 64 fall 38 mass toll 22`
(d) `75 ask 64 fall 38 toll 22 mass`

**Solution:**
Input: `64 toll 22 fall 38 ask 75 mass`
Step I (bring highest number `75`): `75 64 toll 22 fall 38 ask mass`
Step II (bring first word `ask`): `75 ask 64 toll 22 fall 38 mass`
Step III: The next needed element is the second highest number (`64`). Looking at the remaining string after `75 ask`, which is `64 toll 22 fall 38 mass`, `64` is *already* at the front. The machine skips `64` and uses this step to bring the next needed element, which is the second word (`fall`).
So, bring `fall` after `64`: `75 ask 64 fall toll 22 38 mass`

**Answer:** (b) `75 ask 64 fall toll 22 38 mass`

**Q13.** For the Input in Q12, how many total steps are required to complete the arrangement?

(a) 4
(b) 5
(c) 6
(d) 7

**Solution:**
Continue from Step III: `75 ask 64 fall toll 22 38 mass`
Step IV (bring next number `38` after `fall`): `75 ask 64 fall 38 toll 22 mass`
Step V (bring next word `mass` after `38`): `75 ask 64 fall 38 mass toll 22`
Step VI (bring next number `22` after `mass`): `75 ask 64 fall 38 mass 22 toll`
The remaining string is now fully sorted. Total $6$ steps.

**Answer:** (c) 6

**Q14.** If Step II of an input is `81 car 12 sit 45 joy 72 pan`, what is the original Input?

(a) `12 sit 45 joy 72 pan 81 car`
(b) `45 joy 12 sit 72 pan 81 car`
(c) `car 81 12 sit 45 joy 72 pan`
(d) Cannot be determined

**Solution:**
Because the machine physically extracts elements from unknown previous positions and pushes them to the front, we cannot know where `81` and `car` were originally located in the input string. The operation is not reversible.

**Answer:** (d) Cannot be determined

## Decision-Making / Eligibility Criteria

::: definition
**Convention:** You are given a set of criteria required to select a candidate. You are also given exceptions (if a candidate fails a specific rule but meets an alternative, their case is referred to higher management). Based strictly on the data provided for a candidate, you must decide their status: Selected, Rejected, or Referred.
:::

**Directions for Q15–Q17:** 
To select an IT Officer, the following criteria must be met:

1. Have a B.Tech degree with at least $60\%$ marks.
2. Be at least $21$ years and not more than $30$ years of age as of 01-Jan-2023.
3. Have passed the online selection test with at least $70\%$ marks.
4. Pay a security deposit of Rs. $50,000$.

Exceptions:

(A) If a candidate fulfills all criteria EXCEPT (1), but has an M.Tech degree with at least $65\%$ marks, their case is to be referred to the General Manager (GM).
(B) If a candidate fulfills all criteria EXCEPT (4), but can pay at least Rs. $25,000$ and sign a bond for the rest, their case is to be referred to the HR Head.

**Q15.** Candidate Amit is $25$ years old. He scored $65\%$ in his B.Tech. He scored $75\%$ in the online selection test and is ready to pay the full security deposit of Rs. $50,000$. What is his status?

(a) Selected
(b) Rejected
(c) Refer to GM
(d) Refer to HR Head

**Solution:**
Check criteria:

1. B.Tech $\ge 60\%$? Yes ($65\%$).
2. Age 21–30? Yes ($25$).
3. Test $\ge 70\%$? Yes ($75\%$).
4. Deposit Rs. 50,000? Yes.
All primary criteria are met.

**Answer:** (a) Selected

**Q16.** Candidate Priya is $28$ years old. She scored $55\%$ in her B.Tech and $68\%$ in her M.Tech. She scored $72\%$ in the selection test and can pay the Rs. $50,000$ deposit. What is her status?

(a) Selected
(b) Rejected
(c) Refer to GM
(d) Refer to HR Head

**Solution:**
Check criteria:

1. B.Tech $\ge 60\%$? No ($55\%$). Fails rule 1.
Check Exception (A): Has M.Tech $\ge 65\%$? Yes ($68\%$).
2. Age 21–30? Yes ($28$).
3. Test $\ge 70\%$? Yes ($72\%$).
4. Deposit Rs. 50,000? Yes.
She meets the exception for rule 1 and all other rules.

**Answer:** (c) Refer to GM

**Q17.** Candidate Rahul is $24$ years old. He has a B.Tech with $70\%$. He scored $65\%$ in the online selection test. He can pay Rs. $30,000$ now and sign a bond for the rest. What is his status?

(a) Selected
(b) Rejected
(c) Refer to GM
(d) Refer to HR Head

**Solution:**
Check criteria:

1. B.Tech $\ge 60\%$? Yes ($70\%$).
2. Age 21–30? Yes ($24$).
3. Test $\ge 70\%$? No ($65\%$). Fails rule 3.
Is there an exception for rule 3? No. Therefore, he is rejected immediately. It does not matter that he qualifies for the deposit exception (B), because he failed a hard criterion without a fallback.

**Answer:** (b) Rejected

## Quantitative Comparison (Quantity I vs Quantity II)

::: definition
**Convention:** You must calculate or deduce the values of two mathematical quantities (Quantity I and Quantity II). You then compare them and select one of the following standard options:

(a) Quantity I $>$ Quantity II
(b) Quantity I $<$ Quantity II
(c) Quantity I $\ge$ Quantity II
(d) Quantity I $\le$ Quantity II
(e) Quantity I $=$ Quantity II or the relationship cannot be determined
:::

**Q18.**
**Quantity I:** The value of $x$ where $x^2 - 13x + 42 = 0$.
**Quantity II:** The value of $y$ where $y^2 - 17y + 72 = 0$.

**Solution:**
Solve Quantity I: $x^2 - 13x + 42 = 0 \implies (x-6)(x-7) = 0 \implies x = 6 \text{ or } 7$.
Solve Quantity II: $y^2 - 17y + 72 = 0 \implies (y-8)(y-9) = 0 \implies y = 8 \text{ or } 9$.
Comparing the sets $\{6, 7\}$ and $\{8, 9\}$, every possible value of $x$ is strictly less than every possible value of $y$.

**Answer:** (b) Quantity I $<$ Quantity II

**Q19.**
**Quantity I:** The average of the first $50$ positive even integers.
**Quantity II:** The average of the first $51$ positive odd integers.

**Solution:**
Quantity I: The first $50$ even integers are $2, 4, \dots, 100$. The average of an arithmetic progression is $\frac{\text{first} + \text{last}}{2} = \frac{2 + 100}{2} = 51$. (Alternatively, average of first $n$ even integers is $n + 1 = 51$).
Quantity II: The first $51$ odd integers are $1, 3, \dots, 101$. Their average is $\frac{1 + 101}{2} = 51$. (Alternatively, average of first $n$ odd integers is $n = 51$).
Both quantities equal $51$.

**Answer:** (e) Quantity I $=$ Quantity II

**Q20.**
**Quantity I:** The area of a circle with a circumference of $44$ cm. (Assume $\pi = \frac{22}{7}$)
**Quantity II:** The area of a square with a perimeter of $44$ cm.

**Solution:**
Quantity I: Circumference $2\pi r = 44 \implies 2 \times \frac{22}{7} \times r = 44 \implies r = 7$. Area $= \pi r^2 = \frac{22}{7} \times 49 = 154$.
Quantity II: Perimeter $4s = 44 \implies s = 11$. Area $= s^2 = 121$.
$154 > 121$.

**Answer:** (a) Quantity I $>$ Quantity II

**Q21.**
**Quantity I:** The current age of A, if A is $5$ years older than B, and the sum of their ages is $35$.
**Quantity II:** $20$ years.

**Solution:**
Quantity I: Let B's age be $x$. A's age is $x + 5$. Sum $= x + x + 5 = 35 \implies 2x = 30 \implies x = 15$. So A's age is $15 + 5 = 20$.
Quantity II: $20$.
Both are equal to $20$.

**Answer:** (e) Quantity I $=$ Quantity II or the relationship cannot be determined

## Sources

* IndiaBix — https://www.indiabix.com/ (Logical Venn Diagrams, Statement and Course of Action)
* GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/ (Assertion and Reason)
* PrepInsta — https://prepinsta.com/ (Company OA formats for AMCAT, Infosys, and TCS - Input/Output and Decision Making)
* Hitbullseye — https://www.hitbullseye.com/ (Quantitative Comparison frameworks)
