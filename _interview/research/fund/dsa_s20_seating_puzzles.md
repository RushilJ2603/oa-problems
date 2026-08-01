# Seating Arrangements & Puzzles

::: keypoint
**The Universal Framework for Seating Puzzles**

1. **Draw the frame first:** Sketch the row, circle, or grid before reading all the clues.
2. **Place the most constrained clue first:** Start with definitive statements (e.g., "A sits at the extreme right end") rather than relative ones ("B is somewhere left of C").
3. **Track facing direction:** In linear arrangements, note who faces North (left is your left) and South (left is your right). In circular arrangements, "facing centre" means left is clockwise, while "facing outward" means left is counter-clockwise.
:::

## Linear Arrangement

In a single-row linear arrangement, unless stated otherwise, assume everyone faces North. In a two-row arrangement, one row faces North and the other faces South.

**Set 1: Single Row**
Seven friends — A, B, C, D, E, F, and G — are sitting in a straight line facing North.

- D is to the immediate right of F.
- E is at the sixth position to the right of G.
- C is the neighbour of B and D.
- The person who is third to the left of D is at one of the extreme ends.

**Solution:**

1. "The person who is third to the left of D is at one of the extreme ends."
   Let the 7 seats be 1 to 7 (left to right). If someone is third to the left of D, D must be at seat 4 or 5. Since the person is at an *extreme end* (seat 1 or 7), it must be seat 1. Thus, D is at seat 4.
   ```text
   _ _ _ D _ _ _
   ```
2. "D is to the immediate right of F." So F is at seat 3.
   ```text
   _ _ F D _ _ _
   ```
3. "C is the neighbour of B and D." Since F is to the left of D, C must be to the right of D (seat 5). B must be at seat 6 to make C the neighbour of both.
   ```text
   _ _ F D C B _
   ```
4. "E is at the sixth position to the right of G." Only seats 1, 2, and 7 are empty. Being six seats apart forces G to seat 1 and E to seat 7. (G at seat 2 would place E at seat 8, which does not exist.)
   ```text
   G _ F D C B E
   ```
5. The only person left is A, who takes seat 2.
   ```text
   G A F D C B E
   ```

**Q1.** Who are the immediate neighbours of G?
(a) A and F  (b) Only A  (c) E and B  (d) Only F

**Answer:** Only A (b)

**Q2.** What is the position of E with respect to F?
(a) Fourth to the right
(b) Third to the right
(c) Second to the left
(d) Fourth to the left

**Answer:** Fourth to the right (a)

**Set 2: Parallel Rows**
Eight people are sitting in two parallel rows containing four people each, such that there is an equal distance between adjacent persons. In row 1: P, Q, R, and S are seated and all of them are facing South. In row 2: A, B, C, and D are seated and all of them are facing North.

- R sits second to the left of the person who faces A.
- S is an immediate neighbour of R.
- Only one person sits between A and D.
- One of the immediate neighbours of C faces Q.
- B does not sit at any extreme end.

**Solution:**

1. Row 1 (South): P, Q, R, S. Left/Right is reversed.
   Row 2 (North): A, B, C, D. Left/Right is normal.
2. "Only one person sits between A and D." "B does not sit at any extreme end."
   Since A and D have one gap, B must be in the middle with them.
3. "R sits second to the left of the person who faces A."
   Since R is in Row 1 (facing South), "left" means our right.
   Let the person facing A be X. R is two seats to the right of X from our perspective.
   Layout possibilities:
   Case 1:
   ```text
   R1 (South): X  _  R  _
   R2 (North): A  _  _  _
   ```
   Case 2:
   ```text
   R1 (South): _  X  _  R
   R2 (North): _  A  _  _
   ```
4. Resolve Row 2: "Only one person sits between A and D." "B does not sit at any extreme end."
   In Case 1, A is at pos 1, so D is at pos 3. B is not at the end, so B is at pos 2, and C is at pos 4.
   ```text
   R1 (South): X  _  R  _
   R2 (North): A  B  D  C
   ```
   In Case 2, A is at pos 2, D is at pos 4. B is not at the end, so B is at pos 3, and C is at pos 1.
   ```text
   R1 (South): _  X  _  R
   R2 (North): C  A  B  D
   ```
5. "One of the immediate neighbours of C faces Q."
   In Case 1, C's only neighbour is D. The person facing D is at pos 3, which is occupied by R. This contradicts Q facing D. Case 1 is invalid.
   In Case 2, C's only neighbour is A. The person facing A is X. So X must be Q.
   ```text
   R1 (South): _  Q  _  R
   R2 (North): C  A  B  D
   ```
6. "S is an immediate neighbour of R."
   In Case 2, S must be at pos 3. The remaining person P is at pos 1.
   ```text
   R1 (South): P  Q  S  R
   R2 (North): C  A  B  D
   ```

**Q3.** Who among the following faces S?
(a) A  (b) B  (c) C  (d) D

**Answer:** B (b)

**Q4.** What is the position of P with respect to the person who faces C?
(a) Immediate right
(b) Immediate left
(c) Same person
(d) Cannot be determined

**Answer:** Same person (c)

## Circular Arrangement

::: trap
**The Facing Trap**
When a person faces the centre of a circle, their "Left" is clockwise.
When a person faces outward (away from the centre), their "Left" is counter-clockwise.
Do not map your own left and right onto the top/bottom seats without flipping them based on the person's facing direction.
:::

**Set 3: Facing Centre**
Eight executives — J, K, L, M, N, O, P, and Q — are sitting around a circular table for a meeting, facing the centre.

- J is second to the right of P, who is third to the right of K.
- M is second to the left of O, who sits between P and J.
- L is not a neighbour of K or N.

**Solution:**
Draw a circle with 8 seats (numbered 1 to 8, anti-clockwise).

1. "J is second to the right of P, who is third to the right of K."
   Place K at seat 1 (facing centre). P is third to the right (anti-clockwise) of K, so P is at seat 4. J is second to the right of P, so J is at seat 6.
   ```text
   1: K, 4: P, 6: J
   ```
2. "M is second to the left of O, who sits between P and J."
   O is between P (seat 4) and J (seat 6). So O is at seat 5.
   M is second to the left (clockwise) of O (seat 5). So M is at seat 3.
   ```text
   1: K, 3: M, 4: P, 5: O, 6: J
   ```
3. "L is not a neighbour of K or N."
   The empty seats are 2, 7, and 8. L cannot be a neighbour of K (seats 2 and 8 are K's neighbours). Thus, L must be at seat 7.
   ```text
   1: K, 3: M, 4: P, 5: O, 6: J, 7: L
   ```
4. Only seats 2 and 8 are left for N and Q.
   If N is at 8, L (at 7) would be a neighbour of N, which violates "L is not a neighbour of N".
   So N must be at seat 2, and Q must be at seat 8.
   ```text
   1: K, 2: N, 3: M, 4: P, 5: O, 6: J, 7: L, 8: Q
   ```

**Q5.** Who is to the immediate left of L?
(a) Q  (b) J  (c) O  (d) K

**Answer:** J (b)
*(L faces centre, so L's left is clockwise, which is seat 6, occupied by J.)*

**Q6.** Who sits third to the right of Q?
(a) O  (b) M  (c) P  (d) N

**Answer:** M (b)

**Set 4: Mixed Facing (Centre and Outward)**
Six people — U, V, W, X, Y, and Z — are sitting around a circular table.

- X faces the centre. V sits second to the left of X.
- Y sits second to the right of V.
- W sits to the immediate left of Y. W faces the centre.
- U sits second to the right of W.
- V and Y face the same direction.
- Z faces outward.

**Solution:**
Draw a circle with 6 seats (numbered 1 to 6, anti-clockwise).

1. "X faces the centre. V sits second to the left of X."
   X at 1 (centre). Left is clockwise. V is at 5.
   ```text
   1:X(in), 5:V
   ```
2. "Y sits second to the right of V."
   If V faces centre, second right is 1 (occupied by X).
   So V must face outward. Second right (clockwise) is 3.
   ```text
   1:X(in), 3:Y, 5:V(out)
   ```
3. "V and Y face the same direction."
   So Y also faces outward.
4. "W sits to the immediate left of Y. W faces the centre."
   Y is at 3, facing outward. Y's immediate left is clockwise, which is seat 2. So W is at 2, facing centre.
   ```text
   1:X(in), 2:W(in), 3:Y(out), 5:V(out)
   ```
5. "U sits second to the right of W."
   W is at 2, facing centre. W's second right (anti-clockwise) is seat 4. So U is at 4.
6. The only empty seat is 6, which must be taken by Z. "Z faces outward."
   ```text
   1:X(in), 2:W(in), 3:Y(out), 4:U, 5:V(out), 6:Z(out)
   ```

**Q7.** Who sits exactly opposite to U?
(a) X  (b) Y  (c) V  (d) Z

**Answer:** X (a)

**Q8.** What is the position of Z with respect to W?
(a) Second to the left
(b) Second to the right
(c) Third to the left
(d) Immediate right

**Answer:** Second to the left (a)

## Complex / Double-Lineup Puzzles

**Set 5: Matrix Matching**
Five people — P, Q, R, S, and T — live on five different floors of a building (numbered 1 to 5, bottom to top). Each of them drives a different car: Honda, Tata, Ford, Maruti, and Hyundai.

- S lives on an odd-numbered floor but not the top floor.
- The one who drives a Tata lives immediately above R.
- P lives on the fourth floor and does not drive a Hyundai.
- The one who drives a Maruti lives on an even-numbered floor.
- T drives a Honda and lives below S.
- The one on the top floor drives a Ford.

**Solution:**
Create a grid mapping Floors, People, and Cars.

1. "P lives on the fourth floor."
2. "The one on the top floor drives a Ford." Floor 5 drives Ford.
3. "S lives on an odd-numbered floor but not the top floor." Odd floors are 1, 3, 5. Not 5. So S is on 1 or 3.
4. "T drives a Honda and lives below S." If S is on 1, nobody can live below S. So S must be on floor 3. Since T lives below S, T must be on floor 1 or 2.
5. "The one who drives a Tata lives immediately above R." 
   If T is on floor 2 (Honda), R cannot be on 1 because Tata would be on 2 (clash with Honda). So T must be on floor 1. 
   This leaves floors 2 and 5 for R and Q.
   If R is on 5, there is no floor above it for the Tata driver. Thus, R is on floor 2.
   This places Q on floor 5.
   Floor 3 (S) drives Tata (since it is immediately above R).
6. "The one who drives a Maruti lives on an even-numbered floor." Even floors are 2 and 4.
   Since P (floor 4) does not drive a Hyundai, P must drive the Maruti.
   This leaves the Hyundai for R (floor 2).

| Floor | Person | Car |
| :--- | :--- | :--- |
| 5 | Q | Ford |
| 4 | P | Maruti |
| 3 | S | Tata |
| 2 | R | Hyundai |
| 1 | T | Honda |

**Q9.** Who drives the Hyundai?
(a) P  (b) Q  (c) R  (d) S

**Answer:** R (c)

**Q10.** Which of the following combinations is correct?
(a) Floor 2 - S - Maruti
(b) Floor 5 - Q - Ford
(c) Floor 4 - P - Hyundai
(d) Floor 3 - T - Tata

**Answer:** Floor 5 - Q - Ford (b)

**Q11.** How many floors are there between the one who drives a Honda and P?
(a) None  (b) One  (c) Two  (d) Three

**Answer:** Two (c)

## Scheduling / Floor Puzzles

**Set 6: Weekday Scheduling**
Six exams — Math, Physics, Chemistry, Biology, English, and History — are scheduled from Monday to Saturday, one exam per day.

- Physics is scheduled immediately after Chemistry.
- Math is scheduled on Thursday.
- There are two days between the English and Biology exams.
- English is scheduled before Biology.
- History is not scheduled on Monday.
- Chemistry is not scheduled on Wednesday or Friday.

**Solution:**

1. "Math is scheduled on Thursday."
2. "Physics is immediately after Chemistry." Possible consecutive slots are (Mon, Tue), (Tue, Wed), (Fri, Sat). "Chemistry is not on Wednesday or Friday" eliminates (Wed, Thu) and (Fri, Sat).
3. "There are two days between English and Biology. English is before Biology."
   If Chemistry/Physics take (Tue, Wed), the remaining slots are Mon, Fri, Sat. This does not allow a 2-day gap for English and Biology.
   Thus, Chemistry and Physics must take (Mon, Tue).
   The remaining slots are Wed, Fri, Sat. A 2-day gap perfectly fits Wed and Sat for English and Biology respectively.
4. The remaining subject is History, which must be on Friday. (This automatically satisfies "History is not scheduled on Monday").

| Day | Exam |
| :--- | :--- |
| Mon | Chemistry |
| Tue | Physics |
| Wed | English |
| Thu | Math |
| Fri | History |
| Sat | Biology |

**Q12.** On which day is History scheduled?
(a) Tuesday  (b) Wednesday  (c) Friday  (d) Saturday

**Answer:** Friday (c)

**Q13.** Which exam is scheduled immediately before Math?
(a) Physics  (b) Chemistry  (c) History  (d) English

**Answer:** English (d)

## Wrapped OA Variant

::: interview
**The OA Formatting Trick**
Modern online assessments often disguise standard linear or matrix puzzles as "corporate team assignments" or "server rack placements" to make them appear like reading comprehension. The underlying logic remains identical. Extract the pure constraints on your scratchpad immediately.
:::

**Set 7: Desk Assignment (OA Style)**
You are the office manager configuring a new hot-desk layout. Five engineers (Dev, QA, DevOps, Data, Sec) are assigned to five adjacent desks in a single row (Desks 1 to 5, from left to right).

- The QA engineer sits at an extreme end.
- There are exactly two desks between the Sec engineer and the Dev engineer.
- The DevOps engineer is seated to the immediate right of the Data engineer.
- The Dev engineer sits to the immediate left of the QA engineer.

**Solution:**
Translate the story to a standard linear puzzle. 5 seats, facing North.

1. "The QA engineer sits at an extreme end." (Desk 1 or 5).
2. "The Dev engineer sits to the immediate left of the QA engineer." 
   If QA is at Desk 1, there is no desk to the left. Thus, QA is at Desk 5, and Dev is at Desk 4.
   ```text
   _  _  _  Dev  QA
   ```
3. "There are exactly two desks between the Sec engineer and the Dev engineer."
   Since Dev is at Desk 4, Sec must be at Desk 1 (desks 2 and 3 form the gap).
   ```text
   Sec  _  _  Dev  QA
   ```
4. "The DevOps engineer is seated to the immediate right of the Data engineer."
   The only two adjacent empty desks are 2 and 3. Data is at Desk 2, and DevOps is at Desk 3.
   ```text
   Sec  Data  DevOps  Dev  QA
   ```

**Q14.** Which engineer is seated at Desk 3?
(a) Data  (b) DevOps  (c) Dev  (d) QA

**Answer:** DevOps (b)

**Q15.** How many engineers sit between the Sec engineer and the DevOps engineer?
(a) None  (b) One  (c) Two  (d) Three

**Answer:** One (b)

**Q16.** If the Data and QA engineers swap their desks, who will sit to the immediate right of the Dev engineer?
(a) QA  (b) DevOps  (c) Sec  (d) Data

**Answer:** Data (d)

## Sources

- IndiaBix — Verbal Reasoning: Seating Arrangement (https://www.indiabix.com/verbal-reasoning/seating-arrangement/)
- GeeksforGeeks — Aptitude: Seating Arrangement (https://www.geeksforgeeks.org/aptitude-seating-arrangement/)
- Hitbullseye — Reasoning: Seating Arrangement Tricks (https://www.hitbullseye.com/Seating-Arrangement.php)
- PrepInsta — Logical Reasoning: Sitting Arrangement (https://prepinsta.com/logical-reasoning/sitting-arrangement/)
