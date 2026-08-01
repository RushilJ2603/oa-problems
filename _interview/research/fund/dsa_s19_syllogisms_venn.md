# Syllogisms & Venn Diagrams

::: keypoint
**The Venn Diagram Method for Syllogisms:** Solve categorical syllogisms by representing each category as a circle. 

- **All A are B:** Circle A is drawn entirely inside circle B.
- **No A is B:** Circle A and circle B are disjoint (no overlap).
- **Some A are B:** Circle A and circle B overlap.
- **Some A are not B:** At least one part of circle A is outside circle B.
A definite conclusion must hold true in **every** valid diagram. A "possibility" conclusion is true if it holds in **at least one** valid diagram.
:::

::: trap
**The "Some" Fallacy:** In formal logic, "Some A are B" does NOT imply "Some A are not B". "Some" strictly means *at least one, possibly all*. The most common error is relying on a single minimum-overlap diagram. You must test all extreme cases, including complete overlap, when evaluating conclusions.
:::

## Two-statement syllogisms

**Q1.** Statements:

1. All cats are dogs.
2. Some dogs are birds.
Conclusions:
I. Some cats are birds.
II. Some birds are dogs.
(a) Only I follows (b) Only II follows (c) Both follow (d) Neither follows

**Solution:**
Draw a circle for Cats completely inside Dogs. Draw the Birds circle overlapping with Dogs. The Birds circle *can* overlap with Cats, but it does not *have* to. 
Conclusion I: False. It is possible, but not definitely true in all diagrams.
Conclusion II: True. "Some dogs are birds" inherently means "Some birds are dogs" (the overlap is bidirectional).

**Answer:** (b)

**Q2.** Statements:

1. All pens are pencils.
2. All pencils are erasers.
Conclusions:
I. All pens are erasers.
II. Some erasers are pens.
(a) Only I follows (b) Only II follows (c) Both follow (d) Neither follows

**Solution:**
Draw Pens inside Pencils, and Pencils inside Erasers. 
Conclusion I: True. The Pens circle is entirely nested within the Erasers circle.
Conclusion II: True. Since Pens is a subset of Erasers, the region occupied by Pens guarantees that at least some part of Erasers is Pens.

**Answer:** (c)

**Q3.** Statements:

1. No tree is a flower.
2. Some trees are fruits.
Conclusions:
I. Some fruits are not flowers.
II. No fruit is a flower.
(a) Only I follows (b) Only II follows (c) Both follow (d) Neither follows

**Solution:**
Trees and Flowers are disjoint. Fruits overlap with Trees. 
The specific fruits that reside in the Tree overlap can never be flowers (since no tree is a flower). Therefore, there is a guaranteed set of fruits that are not flowers. Conclusion I is True.
Conclusion II is False, because the remaining portion of the Fruits circle outside of Trees *could* overlap with Flowers.

**Answer:** (a)

**Q4.** Statements:

1. Some managers are leaders.
2. No leader is a follower.
Conclusions:
I. Some managers are not followers.
II. All followers are managers.
(a) Only I follows (b) Only II follows (c) Both follow (d) Neither follows

**Solution:**
Managers and Leaders overlap. Leaders and Followers are entirely separate.
The managers who are in the intersection with leaders cannot be followers. Thus, at least some managers are definitely not followers. Conclusion I is True.
Followers have no restricting relationship with Managers; they could be disjoint or overlapping. Conclusion II is False.

**Answer:** (a)

## Three-statement & possibility syllogisms

**Q5.** Statements:

1. Some papers are boards.
2. No board is a card.
3. All cards are keys.
Conclusions:
I. Some papers are not cards.
II. Some keys are not boards.
(a) Only I follows (b) Only II follows (c) Both follow (d) Neither follows

**Solution:**
Papers overlap with Boards. Boards and Cards are completely disconnected. Cards are entirely inside Keys.
The papers that are also boards can never intersect with Cards. Thus, some papers are not cards. Conclusion I is True.
Since all cards are keys, the region of Keys that contains Cards is strictly separated from Boards. Therefore, those specific keys are not boards. Conclusion II is True.

**Answer:** (c)

**Q6.** Statements:

1. All lions are tigers.
2. Some tigers are bears.
3. No bear is a wolf.
Conclusions:
I. All lions being bears is a possibility.
II. All tigers being wolves is a possibility.
(a) Only I follows (b) Only II follows (c) Both follow (d) Neither follows

**Solution:**
Conclusion I asks for a possibility. Can we draw Lions entirely inside Bears? Yes. Lions is inside Tigers, and Tigers overlaps Bears. The overlap between Tigers and Bears can be drawn large enough to completely engulf the Lions circle. Conclusion I is True.
Conclusion II asks if all Tigers can be Wolves. Since some tigers are bears, and no bear is a wolf, the tigers that are bears can never be wolves. Thus, it is impossible for all tigers to be wolves. Conclusion II is False.

**Answer:** (a)

**Q7.** Statements:

1. Some phones are laptops.
2. All laptops are tablets.
3. Some tablets are not watches.
Conclusions:
I. All phones being watches is a possibility.
II. Some laptops are phones.
(a) Only I follows (b) Only II follows (c) Both follow (d) Neither follows

**Solution:**
Conclusion I: The only restriction regarding Watches is that a specific part of Tablets cannot overlap with it. The Phones circle (and its overlap with Laptops/Tablets) can easily be placed entirely inside the Watches circle without violating the premise that some other part of Tablets remains outside Watches. Conclusion I is True.
Conclusion II: "Some phones are laptops" symmetrically implies "Some laptops are phones". Conclusion II is True.

**Answer:** (c)

::: keypoint
**"Only a few":** In modern placement OAs, the modifier "Only a few A are B" is a strict hybrid: it translates to **"Some A are B" AND "Some A are not B"**.
:::

**Q8.** A company's logic test contains this scenario:
Statements:

1. Only a few engineers are coders.
2. All coders are hackers.
3. No hacker is a designer.
Conclusions:
I. All engineers being hackers is a possibility.
II. Some hackers are engineers.
(a) Only I follows (b) Only II follows (c) Both follow (d) Neither follows

**Solution:**
"Only a few engineers are coders" establishes that engineers overlap with coders, but a section of engineers must remain strictly outside coders.
Conclusion I: Can all engineers be hackers? Yes. The engineers that are not coders can still be placed inside the broader hackers circle, as long as they stay outside the coders circle. Conclusion I is True.
Conclusion II: Engineers and coders overlap, and all coders are within hackers. The engineers in the coder overlap are definitively hackers. Therefore, some hackers are engineers. Conclusion II is True.

**Answer:** (c)

## Either–or & complementary pairs

::: keypoint
**Complementary Pairs (Either-Or):** When two conclusions share the same subject and predicate, and neither is individually definite, they form an "either-or" pair if they exhaust all logical possibilities. The two standard complementary pairs are:

1. "Some A are B" and "No A is B"
2. "All A are B" and "Some A are not B"
:::

**Q9.** Statements:

1. Some doors are windows.
2. No window is a roof.
Conclusions:
I. Some doors are roofs.
II. No door is a roof.
(a) Only I follows (b) Only II follows (c) Either I or II follows (d) Neither follows

**Solution:**
Doors overlap with Windows, and Windows are separate from Roofs. The relationship between Doors and Roofs is completely undefined. 
In any valid diagram, the Doors circle will either overlap with Roofs or it will not. Therefore, either Conclusion I must be true, or Conclusion II must be true. They form a complementary pair.

**Answer:** (c)

**Q10.** Statements:

1. All cars are buses.
2. Some buses are trains.
Conclusions:
I. All cars are trains.
II. Some cars are not trains.
(a) Only I follows (b) Only II follows (c) Either I or II follows (d) Neither follows

**Solution:**
Cars is nested inside Buses. Buses overlaps with Trains. Cars and Trains have no defined relationship.
Individually, neither conclusion is definite. However, in any conceivable setup, either the Cars circle is completely enveloped by the Trains circle (I is true), or at least some part of the Cars circle lies outside the Trains circle (II is true). These cover all possibilities.

**Answer:** (c)

::: trap
**False Pairs:** "Some A are B" and "Some A are not B" do NOT form an either-or pair. Both can easily be true simultaneously, so they are not mutually exclusive. If neither follows definitely, the answer is "Neither".
:::

**Q11.** Statements:

1. Some red are blue.
2. Some blue are green.
Conclusions:
I. Some red are green.
II. Some red are not green.
(a) Only I follows (b) Only II follows (c) Either I or II follows (d) Neither follows

**Solution:**
Red and Green have no restrictive relationship. Neither I nor II is definitely true.
Because "Some" and "Some-not" can both be true at the same time (a partial overlap), they do not form an exhaustive complementary pair. It is also possible that all red are green (making II false), or no red are green (making I false). Since we don't have a strict mutually exclusive dichotomy, neither follows.

**Answer:** (d)

## Venn — set counting

**Q12.** In a class of $80$ students, $45$ like Math, $50$ like Science, and $10$ like neither. How many students like exactly one of the two subjects?
(a) $25$ (b) $45$ (c) $55$ (d) $70$

**Solution:**
Let $M$ be Math, $S$ be Science. Total = $80$, Neither = $10$.
The union of both sets is $|M \cup S| = 80 - 10 = 70$.
Using the set formula: $|M \cup S| = |M| + |S| - |M \cap S|$
$70 = 45 + 50 - |M \cap S| \implies |M \cap S| = 25$.
Students liking exactly one subject = Only Math + Only Science.
Only Math = $45 - 25 = 20$. Only Science = $50 - 25 = 25$.
Total exactly one = $20 + 25 = 45$.
(Fast formula: $|M| + |S| - 2|M \cap S| = 95 - 50 = 45$).

**Answer:** $45$ (b)

**Q13.** In a survey of $100$ people, $40$ read newspaper A, $50$ read B, and $30$ read C. It is known that $15$ read both A and B, $10$ read both B and C, and $12$ read both A and C. If $5$ read all three, how many people read none of the three newspapers?
(a) $5$ (b) $8$ (c) $12$ (d) $15$

**Solution:**
Use the inclusion-exclusion principle for three sets:
$|A \cup B \cup C| = |A| + |B| + |C| - |A \cap B| - |B \cap C| - |A \cap C| + |A \cap B \cap C|$
$|A \cup B \cup C| = 40 + 50 + 30 - 15 - 10 - 12 + 5 = 88$.
This is the number of people who read at least one newspaper.
People who read none = Total - $|A \cup B \cup C| = 100 - 88 = 12$.

**Answer:** $12$ (c)

**Q14.** In a group of $150$ athletes, $60$ play soccer, $70$ play basketball, and $50$ play tennis. $20$ play both soccer and basketball, $15$ play both basketball and tennis, and $10$ play both soccer and tennis. If $10$ athletes play all three sports, how many play exactly two sports?
(a) $15$ (b) $25$ (c) $35$ (d) $45$

**Solution:**
The pairwise intersections ($20$, $15$, $10$) *include* the athletes who play all three. To find those playing *exactly* two, we subtract the "all three" count from each intersection.
Exactly soccer & basketball = $20 - 10 = 10$.
Exactly basketball & tennis = $15 - 10 = 5$.
Exactly soccer & tennis = $10 - 10 = 0$.
Total playing exactly two sports = $10 + 5 + 0 = 15$.

**Answer:** $15$ (a)

## Venn — min–max overlap

**Q15.** In an office of $200$ employees, $130$ drink coffee and $110$ drink tea. What is the minimum and maximum possible number of employees who drink both?
(a) $40$ and $110$ (b) $0$ and $110$ (c) $40$ and $130$ (d) $20$ and $110$

**Solution:**
Let $C = 130$ and $T = 110$. Total $N = 200$.
**Maximum overlap:** The smaller set is entirely contained within the larger set. Max $|C \cap T| = \min(130, 110) = 110$.
**Minimum overlap:** The sets are spread out as much as possible to cover the entire population without overlapping unnecessarily.
$|C \cup T| \le 200 \implies |C| + |T| - |C \cap T| \le 200$
$130 + 110 - |C \cap T| \le 200 \implies 240 - 200 \le |C \cap T| \implies |C \cap T| \ge 40$.
The overlap range is between $40$ and $110$.

**Answer:** $40$ and $110$ (a)

**Q16.** In a batch of $100$ students, $80$ passed in Math, $75$ passed in Physics, and $70$ passed in Chemistry. What is the minimum possible number of students who passed in all three subjects?
(a) $20$ (b) $25$ (c) $0$ (d) $35$

**Solution:**
To find the minimum overlap of all three (minimum passes), we must maximize the number of failures.
Number who failed Math = $100 - 80 = 20$.
Number who failed Physics = $100 - 75 = 25$.
Number who failed Chemistry = $100 - 70 = 30$.
To maximize students failing at least one subject without overlapping, assume the failure groups are completely disjoint. 
Max distinct failures = $20 + 25 + 30 = 75$.
The remaining students must have passed every subject.
Minimum passed all three = $100 - 75 = 25$.

**Answer:** $25$ (b)

## Sources

- IndiaBix — Verbal Reasoning: Syllogism (https://www.indiabix.com/verbal-reasoning/syllogism/)
- IndiaBix — Verbal Reasoning: Venn Diagrams (https://www.indiabix.com/verbal-reasoning/venn-diagrams/)
- GeeksforGeeks — Syllogism in Aptitude (https://www.geeksforgeeks.org/aptitude/aptitude-questions-and-answers/)
- PrepInsta — Logical Reasoning: Syllogism (https://prepinsta.com/)
- Hitbullseye — Syllogism and Logic (https://www.hitbullseye.com/)
