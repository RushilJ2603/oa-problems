# Blood Relations & Direction Sense

::: keypoint
**Blood Relations:** Draw a family tree using a consistent notation:

- Gender: $+$ for male, $-$ for female.
- Connections: $-$ for siblings, $=$ for married couples, $|$ for parent–child (vertical).
- For pointing/statement puzzles, work backwards from the speaker's relation to the person.

**Direction Sense:**

- Draw standard N-E-S-W axes (North up).
- Trace each movement as a vector, tracking left/right relative to the current facing direction.
- Use Pythagoras ($c^2 = a^2 + b^2$) to find the shortest distance from start to end.
:::

## Blood Relations — Direct & Pointing

**Q1.** Pointing to a photograph, a man says, "She is the daughter of my grandfather's only son." How is the woman in the photograph related to the man?
(a) Mother (b) Sister (c) Aunt (d) Cousin

**Solution:** The man's grandfather's only son is the man's father. The daughter of the man's father is his sister.

**Answer:** Sister (b)

**Q2.** A woman introduces a man as the son of the brother of her mother. How is the man related to the woman?
(a) Nephew (b) Son (c) Cousin (d) Uncle

**Solution:** The brother of the woman's mother is her maternal uncle. The son of her maternal uncle is her cousin.

**Answer:** Cousin (c)

**Q3.** Pointing to a gentleman, Deepak said, "His only brother is the father of my daughter's father." How is the gentleman related to Deepak?
(a) Grandfather (b) Father (c) Brother-in-law (d) Uncle

**Solution:** "My daughter's father" is Deepak himself. So, the gentleman's only brother is Deepak's father. Thus, the gentleman is the brother of Deepak's father, which means he is Deepak's uncle.

**Answer:** Uncle (d)

**Q4.** (OA Variant) While viewing a family album, Alice points to a man and says, "His mother is the only daughter of my mother-in-law." How is Alice related to the man?
(a) Mother (b) Aunt (c) Sister (d) Wife

**Solution:** "My mother-in-law's only daughter" is Alice's husband's sister. So, the man's mother is Alice's husband's sister. Thus, Alice is married to the man's maternal uncle. She is the man's aunt (by marriage).

**Answer:** Aunt (b)

**Q5.** (OA Variant) Pointing to a boy in a photograph, Reena said, "He is the only son of the only child of my grandfather." How is Reena related to that boy?
(a) Mother (b) Sister (c) Aunt (d) Niece

**Solution:** "My grandfather's only child" must be Reena's parent (father or mother). The "only son of the only child" means the only son of Reena's parent, which is Reena's brother. Therefore, Reena is the sister of the boy.

**Answer:** Sister (b)

## Coded Blood Relations

**Q6.** If $P + Q$ means $P$ is the brother of $Q$; $P - Q$ means $P$ is the mother of $Q$; and $P \times Q$ means $P$ is the sister of $Q$. Which of the following means $M$ is the maternal uncle of $R$?
(a) $M + K + R$ (b) $M - R + K$ (c) $M + K - R$ (d) $M \times K + R$

**Solution:** We need $M$ to be a male and the brother of $R$'s mother.
Test option (c): $M + K - R$.

- $M + K$ means $M$ is the brother of $K$ ($M$ is male).
- $K - R$ means $K$ is the mother of $R$ ($K$ is female).
Therefore, $M$ is the brother of $R$'s mother, making him the maternal uncle.

**Answer:** $M + K - R$ (c)

**Q7.** Read the following rules:

1. $A \div B$ means $A$ is the father of $B$.
2. $A \times B$ means $A$ is the wife of $B$.
3. $A + B$ means $A$ is the brother of $B$.
4. $A - B$ means $A$ is the daughter of $B$.
If $P \div R + S \times Q$, which of the following is true?
(a) $P$ is the father-in-law of $Q$ (b) $Q$ is the aunt of $P$ (c) $P$ is the uncle of $Q$ (d) $P$ is the brother of $Q$

**Solution:** Trace the chain $P \div R + S \times Q$:

- $P \div R$: $P$ is the father of $R$ ($P$ is male).
- $R + S$: $R$ is the brother of $S$ ($R$ is male). Thus, $P$ is also the father of $S$.
- $S \times Q$: $S$ is the wife of $Q$ ($S$ is female, $Q$ is male).
Since $S$ is $P$'s daughter, $S$'s husband $Q$ is $P$'s son-in-law. This means $P$ is $Q$'s father-in-law.

**Answer:** $P$ is the father-in-law of $Q$ (a)

**Q8.** In a coded system, $A \$ B$ means $A$ is the mother of $B$, $A \# B$ means $A$ is the father of $B$, $A @ B$ means $A$ is the husband of $B$, and $A \% B$ means $A$ is the daughter of $B$.
If $P @ Q \$ M \# T$, how is $P$ related to $T$?
(a) Grandfather (b) Grandmother (c) Father (d) Uncle

**Solution:** Trace $P @ Q \$ M \# T$:

- $P @ Q$: $P$ is the husband of $Q$.
- $Q \$ M$: $Q$ is the mother of $M$. Together, $P$ is the father of $M$.
- $M \# T$: $M$ is the father of $T$.
Since $P$ is the father of $M$, and $M$ is the father of $T$, $P$ is the grandfather of $T$.

**Answer:** Grandfather (a)

::: trap
When tracing coded relations, do not assume the gender of the last person in the chain unless a symbol specifically defines it. For example, in $A + B$ (where $A$ is the brother of $B$), $B$'s gender is unknown. Also, beware of "in-law" chains where maternal vs paternal isn't explicitly stated.
:::

## Family-Tree / Generation Puzzles

**Q9.** In a family of six persons $A, B, C, D, E,$ and $F$, there are two married couples. $D$ is the grandmother of $A$ and mother of $B$. $C$ is the wife of $B$ and mother of $F$. $F$ is the grand-daughter of $E$. What is the relation of $C$ to $A$?
(a) Mother (b) Grandmother (c) Aunt (d) Sister

**Solution:**

- $D$ is the mother of $B$ and grandmother of $A$. So $D$ is an older female.
- $C$ is the wife of $B$ and mother of $F$. So $B$ and $C$ are a married couple.
- Since $D$ is $B$'s mother and a grandmother, her husband must be $E$ (since $F$ is $E$'s grand-daughter, $E$ is the grandfather).
- The couple $B$ and $C$ have children $A$ and $F$.
- Therefore, $C$ is the mother of $A$.

**Answer:** Mother (a)

**Q10.** $A$ and $B$ are siblings. $C$ and $D$ are spouses. $D$ is the father of $A$. $E$ is the daughter of $C$. $F$ is the brother of $D$. How is $F$ related to $E$?
(a) Uncle (b) Father (c) Brother (d) Cousin

**Solution:**

- $C$ and $D$ are spouses. $D$ is the father of $A$, making $D$ the father and $C$ the mother.
- $A$ and $B$ are siblings, so they are children of $C$ and $D$.
- $E$ is the daughter of $C$, so $E$ is also a sibling to $A$ and $B$.
- $F$ is the brother of $D$ (the father).
- Since $D$ is $E$'s father, $D$'s brother $F$ is $E$'s uncle.

**Answer:** Uncle (a)

**Q11.** (OA Variant) A joint family consists of a man, his wife, his three married sons, and two unmarried daughters. Among the married sons, two have two daughters each, and one has a son. How many female members are there in the family?
(a) $7$ (b) $8$ (c) $9$ (d) $10$

**Solution:** Let's count the females across the generations:

- First generation: The man's wife ($1$).
- Second generation: Three married sons have three wives ($3$), and there are two unmarried daughters ($2$).
- Third generation: Two sons have two daughters each ($2 \times 2 = 4$).
Total females $= 1 + 3 + 2 + 4 = 10$.

**Answer:** $10$ (d)

## Direction Sense — Path Tracing

**Q12.** A man walks $5\text{ km}$ toward South and then turns to the right. After walking $3\text{ km}$ he turns to the left and walks $5\text{ km}$. Now in which direction is he from the starting place?
(a) West (b) South (c) North-East (d) South-West

**Solution:** Map on a Cartesian plane starting at $(0, 0)$:

- $5\text{ km}$ South: reaches $(0, -5)$, facing South.
- Turns right (now faces West), walks $3\text{ km}$: reaches $(-3, -5)$.
- Turns left (now faces South), walks $5\text{ km}$: reaches $(-3, -10)$.
From $(0, 0)$, the point $(-3, -10)$ lies in the South-West quadrant.

**Answer:** South-West (d)

**Q13.** Rahul put his timepiece on the table in such a way that at $6:00\text{ PM}$ the hour hand points to North. In which direction the minute hand will point at $9:15\text{ PM}$?
(a) South-East (b) South (c) North (d) West

**Solution:** Normally at $6:00$, the hour hand points to the $6$ (South) and the minute hand points to the $12$ (North).
If the hour hand ($6$) points North, the entire clock is rotated $180^\circ$.
So the $3$ mark (normally East) now points West.
At $9:15$, the minute hand is at the $3$ mark, which points West.

**Answer:** West (d)

**Q14.** One morning after sunrise, Suresh was standing facing a pole. The shadow of the pole fell exactly to his right. To which direction was he facing?
(a) East (b) South (c) West (d) Data inadequate

**Solution:**

- Time is morning, so the sun is in the East.
- Shadows fall to the West.
- The shadow fell to Suresh's right, meaning his right side points West.
- If your right arm points West, you must be facing South.

**Answer:** South (b)

**Q15.** One evening before sunset, Rekha and Hema were talking to each other face to face. If Hema's shadow was exactly to the right of Hema, which direction was Rekha facing?
(a) North (b) South (c) East (d) Data inadequate

**Solution:**

- Time is evening, so the sun is in the West.
- Shadows fall to the East.
- Hema's shadow was to her right, so Hema's right side points East.
- If your right arm points East, you are facing North. So, Hema faces North.
- Since they are face to face, Rekha must be facing South.

**Answer:** South (b)

::: keypoint
**Shadow Rules:**

- **Morning:** Sun in East, shadows fall West.
- **Evening:** Sun in West, shadows fall East.
- If a shadow falls to the Left or Right, the person is facing North or South.
- If a shadow falls in Front or Back, the person is facing East or West.
:::

## Direction Sense — Shortest Distance & Turns

::: trap
A common mistake in direction sense is forgetting your current facing direction. A "left turn" when facing South actually moves you East on the map. Always re-orient your mental compass after a turn.
:::

**Q16.** A boy rides his bicycle Northwards, then turns left and rides $1\text{ km}$ and again turns left and rides $2\text{ km}$. He found himself exactly $1\text{ km}$ west of his starting point. How far did he ride Northwards initially?
(a) $1\text{ km}$ (b) $2\text{ km}$ (c) $3\text{ km}$ (d) $5\text{ km}$

**Solution:** Trace from start $(0,0)$:

- Rides North by $y$: reaches $(0, y)$.
- Turns left (faces West), rides $1\text{ km}$: reaches $(-1, y)$.
- Turns left (faces South), rides $2\text{ km}$: reaches $(-1, y - 2)$.
He is now $1\text{ km}$ West of start, which is $(-1, 0)$.
Match coordinates: $-1 = -1$ and $y - 2 = 0 \implies y = 2$.
He initially rode $2\text{ km}$ North.

**Answer:** $2\text{ km}$ (b)

**Q17.** K turns towards South-East and travels $7\text{ km}$, then she turns towards West and travels $14\text{ km}$. From here, she turns towards North-West and travels $7\text{ km}$, and finally she turns towards East and travels $4\text{ km}$. How far is she from the starting point?
(a) $3\text{ km}$ (b) $4\text{ km}$ (c) $10\text{ km}$ (d) $11\text{ km}$

**Solution:** Notice the vectors form a parallelogram.

- Path 1: $7\text{ km}$ South-East.
- Path 2: $14\text{ km}$ West.
- Path 3: $7\text{ km}$ North-West. This completely cancels out Path 1's horizontal and vertical shift, placing her exactly $14\text{ km}$ West of the start.
- Path 4: $4\text{ km}$ East.
Net position: $14\text{ km}$ West followed by $4\text{ km}$ East leaves her $10\text{ km}$ West of the starting point.

**Answer:** $10\text{ km}$ (c)

**Q18.** A man walks $10\text{ km}$ towards North. From there, he walks $6\text{ km}$ towards South. Then, he walks $3\text{ km}$ towards East. How far and in which direction is he with reference to his starting point?
(a) $5\text{ km}$ North-East (b) $7\text{ km}$ North-West (c) $5\text{ km}$ North-West (d) $7\text{ km}$ North-East

**Solution:** Find the net displacement from $(0, 0)$:

- Net vertical: $10\text{ km}$ North then $6\text{ km}$ South $\implies 4\text{ km}$ North $(+4)$.
- Net horizontal: $3\text{ km}$ East $(+3)$.
- The final position is $(3, 4)$.
- Distance $c = \sqrt{3^2 + 4^2} = \sqrt{9 + 16} = 5\text{ km}$.
- Direction from origin to $(+3, +4)$ is North-East.

**Answer:** $5\text{ km}$ North-East (a)

**Q19.** (OA Variant) A person starts walking in North direction and travels $4\text{ km}$, then turns left and travels $3\text{ km}$, then turns right and travels $4\text{ km}$, then turns right and travels $3\text{ km}$. How far is he from the starting point?
(a) $0\text{ km}$ (b) $8\text{ km}$ (c) $10\text{ km}$ (d) $14\text{ km}$

**Solution:** 

- Starts at $(0, 0)$, faces North.
- Travels $4\text{ km}$ North $\implies (0, 4)$, faces North.
- Turns left (faces West), travels $3\text{ km} \implies (-3, 4)$, faces West.
- Turns right (faces North), travels $4\text{ km} \implies (-3, 8)$, faces North.
- Turns right (faces East), travels $3\text{ km} \implies (-3 + 3, 8) = (0, 8)$.
He is at $(0, 8)$. Distance from $(0, 0)$ is $8\text{ km}$.

**Answer:** $8\text{ km}$ (b)

**Q20.** (OA Variant) A drone is programmed to survey a field. It takes off from the base, flies $12\text{ m}$ North, then turns $90^\circ$ right and flies $5\text{ m}$. It then turns $90^\circ$ right and flies $20\text{ m}$. Finally, it turns $90^\circ$ right and flies $11\text{ m}$. What is the straight-line distance from the drone to the base?
(a) $10\text{ m}$ (b) $12\text{ m}$ (c) $13\text{ m}$ (d) $15\text{ m}$

**Solution:** Map the coordinates from the base $(0, 0)$:

- $12\text{ m}$ North: $(0, 12)$. Facing North.
- $90^\circ$ right (East), flies $5\text{ m}$: $(5, 12)$.
- $90^\circ$ right (South), flies $20\text{ m}$: $(5, 12 - 20) = (5, -8)$.
- $90^\circ$ right (West), flies $11\text{ m}$: $(5 - 11, -8) = (-6, -8)$.
Shortest distance $d = \sqrt{(-6)^2 + (-8)^2} = \sqrt{36 + 64} = \sqrt{100} = 10\text{ m}$.

**Answer:** $10\text{ m}$ (a)

## Sources

- IndiaBix — Verbal Reasoning: Blood Relation Test — https://www.indiabix.com/verbal-reasoning/blood-relation-test/
- IndiaBix — Verbal Reasoning: Direction Sense Test — https://www.indiabix.com/verbal-reasoning/direction-sense-test/
- GeeksforGeeks — Direction Sense Solved Questions — https://www.geeksforgeeks.org/direction-sense-solved-questions-and-answers/
- PrepInsta — Directional Sense (Logical Reasoning) — https://www.prepinsta.com/logical-reasoning/directional-sense/
