# Critical Reasoning & Truth-Teller Puzzles

::: keypoint
**The Core Framework for Critical Reasoning**
Every argument consists of a **premise** (the stated facts), a **conclusion** (the author's claim), and an **assumption** (the unstated link connecting the two). 

- **Assumption:** To find it, use the **Negation Test**: if you negate an assumption and it destroys the argument, that assumption is logically required.
- **Strengthen / Weaken:** To support or attack an argument, you must support or attack the *link* (the assumption), not the premise itself. A new fact must make the conclusion more or less likely to follow from the given evidence.
:::

## 1. Statement & Assumption / Conclusion

**Q1.** **Statement:** "In order to reduce pollution, the city government has decided to double the parking fees in the downtown area starting next month."

**Assumptions:**
I. People will continue to drive to the downtown area even if they have to pay double the parking fee.
II. A significant number of people will switch to public transport or carpool due to the increased parking fee.

(a) Only I is implicit
(b) Only II is implicit
(c) Both I and II are implicit
(d) Neither I nor II is implicit

**Solution:** The government's goal is to reduce pollution by raising parking fees. For this plan to work, the government must *assume* that the higher cost will deter people from driving (hence switching to other modes). If people just pay the fee and drive anyway (Assumption I), pollution won't decrease. The negation of II ("People will NOT switch to public transport...") destroys the plan's logic. Therefore, only II is the intended assumption behind the action.

**Answer:** (b)

**Q2.** **Statement:** "Please consult a physician before starting this intense 90-day workout program." — An instruction on a fitness app.

**Assumptions:**
I. The 90-day workout program may not be medically safe for everyone.
II. A physician can determine whether a person is physically fit enough to handle the program.

(a) Only I is implicit
(b) Only II is implicit
(c) Both I and II are implicit
(d) Neither I nor II is implicit

**Solution:** Why put a medical warning on an app? Because the creator assumes the workout has physical risks (I) and that a doctor is capable of assessing those risks for an individual (II). Negate I: "The program is medically safe for everyone" — then the warning is pointless. Negate II: "A physician cannot determine fitness" — then consulting them is useless. Both are required assumptions.

**Answer:** (c)

**Q3.** **Statement:** "The company's new flagship phone features a larger battery and a more efficient processor. Therefore, users will experience a significantly longer battery life."

**Conclusions:**
I. The new screen on the flagship phone does not consume significantly more power than the previous model.
II. The company's older phones had poor battery life.

(a) Only I follows
(b) Only II follows
(c) Both I and II follow
(d) Neither I nor II follows

**Solution:** The conclusion is that battery life will be *longer*. For this to be true given a bigger battery and better processor, it must be true that other components (like the screen) don't offset these gains by draining massively more power. So I is a required logical bridge (an assumption that functions as a required conclusion). II is an overreach; the old phones might have had great battery life, and the new one just has *longer* battery life.

**Answer:** (a)

**Q4. (OA Variant)** **Statement:** "Our new AI coding assistant reduces syntax errors by $40\%$. Therefore, deploying it across our engineering team will decrease our overall software development time."
Which of the following must be true for the conclusion to follow?

(a) Syntax errors currently account for a significant portion of the team's software development time.
(b) The AI coding assistant is free to deploy.
(c) Engineers will not introduce new types of logical errors when using the AI assistant.
(d) The AI assistant writes code faster than a human engineer.

**Solution:** The argument links a reduction in *syntax errors* to a reduction in *overall development time*. 
Negation test on (a): "Syntax errors currently do NOT account for a significant portion of time." If syntax errors take up almost $0\%$ of development time, then reducing them by $40\%$ will have virtually no impact on overall time, destroying the argument. (c) is a trap; even if they introduce some new errors, overall time might still decrease if the syntax savings are huge. (a) is strictly necessary.

**Answer:** (a)

## 2. Strengthen / Weaken the Argument

::: trap
When asked to weaken an argument, a common trap is picking an option that attacks the *premise* (e.g., saying the data is fake) or picking an option that is generally true but *out of scope*. You must attack the *reasoning* that connects the premise to the conclusion.
:::

**Q5.** **Argument:** A recent study showed that students who ate a heavy breakfast before the morning exam scored, on average, $15\%$ higher than those who skipped breakfast. The school principal concluded that eating a heavy breakfast directly improves cognitive performance and exam scores.
Which of the following, if true, most seriously **weakens** the principal's conclusion?

(a) Heavy breakfasts are often expensive, and only wealthier students can afford them.
(b) Students who skipped breakfast generally spent the previous night studying late and sleeping less.
(c) Some students who ate a heavy breakfast still scored below the class average.
(d) A separate study showed that eating a heavy lunch causes drowsiness in the afternoon.

**Solution:** The argument claims a causal link: Breakfast $\rightarrow$ Higher Scores. To weaken a causal claim, find an alternative cause for the effect. 

- (a) Socioeconomic status might be a factor, but doesn't directly address the exam score mechanism as well as an immediate physiological one.
- (b) **Alternative cause:** Lack of sleep caused the lower scores, not the lack of breakfast. This breaks the causal link.
- (c) Attacks the premise slightly (by pointing out outliers), but averages still hold true. 
- (d) Out of scope (lunch/afternoon is irrelevant).

**Answer:** (b)

**Q6.** **Argument:** The city of Neo-Veridia recently replaced all its streetlights with highly efficient LED bulbs to save money. However, after one year, the city's overall electricity bill for public lighting actually increased. Critics argue the new LED bulbs are secretly consuming more power than advertised.
Which of the following, if true, most strongly **weakens** the critics' argument?

(a) The cost of manufacturing LED bulbs has decreased over the last decade.
(b) The city expanded its public park system this year, adding thousands of new light fixtures that did not previously exist.
(c) The old streetlights required frequent and costly maintenance.
(d) Neighboring cities that switched to LEDs reported a decrease in their electricity bills.

**Solution:** The critics claim the *bulbs themselves* are faulty/power-hungry because the total bill went up.

- (a) Out of scope (manufacturing cost is not the electricity bill).
- (b) **Alternative cause:** The bill went up because there are *more* lights in total, not because the individual LEDs are inefficient. This destroys the critics' logic.
- (c) Maintenance costs are irrelevant to the *electricity* bill.
- (d) Actually strengthens the idea that Neo-Veridia's LEDs might be defective, or at least doesn't weaken the critics directly like (b) does.

**Answer:** (b)

**Q7.** **Argument:** Commuter airline Beta Airways has the lowest rate of lost luggage in the industry. The CEO claims this is because they use a proprietary barcode scanning system that tracks bags more accurately than competitors.
Which of the following, if true, most strongly **strengthens** the CEO's claim?

(a) Beta Airways only operates direct flights, meaning luggage is never transferred between connecting planes.
(b) Before implementing the proprietary scanning system, Beta Airways had the highest rate of lost luggage in the industry.
(c) Beta Airways charges a premium fee for checked luggage, reducing the total number of bags they handle.
(d) The proprietary scanning system was developed by a leading tech firm.

**Solution:** We need to *support* the claim that the scanning system is the definitive reason for the low lost-luggage rate.

- (a) Weakens the claim by providing an alternative cause (direct flights = fewer lost bags).
- (b) **Strengthens:** Shows a clear before-and-after effect. If they were the worst, and became the best right after installing the system, the system is highly likely the cause.
- (c) Weakens the claim (fewer bags = easier to manage).
- (d) Irrelevant to whether it actually works in practice.

**Answer:** (b)

**Q8. (OA Variant)** **Argument:** A software company implemented a strict "no meetings on Thursdays" policy to boost developer productivity. After six months, the number of code commits per developer on Thursdays increased by $30\%$. Management concluded the policy successfully boosted productivity.
Which of the following, if true, most seriously **weakens** the conclusion?

(a) Developers reported feeling more isolated due to the lack of meetings.
(b) The company also introduced a mandatory Friday morning deadline for all weekly code reviews, forcing developers to rush commits on Thursday.
(c) Other tech companies have tried similar policies with mixed results.
(d) The number of bugs reported in production code did not decrease during this six-month period.

**Solution:** The argument assumes the $30\%$ increase in commits is strictly due to the "no meeting" policy granting deep-focus time.

- (a) Out of scope (focuses on morale vs productivity metric).
- (b) **Alternative cause:** The impending Friday deadline forced the Thursday commit spike, regardless of the meeting policy.
- (c) Out of scope (other companies are irrelevant).
- (d) Out of scope (addresses quality of commits, while the argument is about the quantity/productivity rate).

**Answer:** (b)

## 3. Cause & Effect / Inference

**Q9.** **Statements:**

I. The local government recently imposed a heavy tax on the sale of sugary carbonated beverages.
II. There has been a significant surge in the sales of packaged fruit juices and sports drinks in the city over the last two months.
Which of the following best describes the relationship between the two statements?

(a) Statement I is the cause and Statement II is its effect.
(b) Statement II is the cause and Statement I is its effect.
(c) Both statements are independent causes.
(d) Both statements are effects of independent causes.

**Solution:** A tax on sugary sodas makes them significantly more expensive (I). Consumers look for cheaper or untaxed sweet alternatives, leading to a surge in sales of fruit juices and sports drinks (II). Therefore, the tax is the logical cause, and the shift in consumer buying behavior is the effect.

**Answer:** (a)

**Q10.** **Passage:** "While renewable energy sources like solar and wind are critical for a sustainable future, their intermittent nature—the sun doesn't always shine, and the wind doesn't always blow—poses a challenge for maintaining a stable power grid. Therefore, transitioning to a $100\%$ renewable grid requires massive investments in grid-scale battery storage technology."
Which of the following can be logically **inferred** from the passage?

(a) Solar energy is more reliable than wind energy.
(b) Without large-scale battery storage, a power grid relying entirely on wind and solar would experience instability.
(c) Fossil fuels will remain the primary source of energy for the next century.
(d) Grid-scale batteries are currently too expensive to manufacture.

**Solution:** An inference must be provable *strictly* from the text provided. 

- (a) The text doesn't compare their individual reliability.
- (b) **Inferred:** The text states renewables are intermittent (which poses a challenge for stability) and therefore transitioning to $100\%$ requires batteries. Thus, without batteries, a $100\%$ renewable grid is inherently unstable.
- (c) Out of scope.
- (d) Out of scope (cost isn't mentioned, only the *need* for massive investments).

**Answer:** (b)

**Q11. (OA Variant)** **Statements:**

I. The central bank abruptly increased interest rates by $0.75\%$ this week.
II. The national stock market index plummeted by $4\%$ on the same day.
Which of the following best describes the relationship?

(a) Statement I is the cause and Statement II is its effect.
(b) Statement II is the cause and Statement I is its effect.
(c) Both statements are effects of a common cause.
(d) Both statements are independent causes.

**Solution:** In standard economics (which OA logical reasoning models follow), an abrupt increase in interest rates raises borrowing costs and yields on safe assets, causing investors to pull money out of riskier equities. This triggers a stock market sell-off. Therefore, the central bank's action (I) caused the market reaction (II).

**Answer:** (a)

## 4. Truth-Teller & Liar Puzzles (Knights & Knaves)

::: keypoint
**Solving Truth-Teller Puzzles**
Always proceed by **case-splitting** (Proof by Contradiction). Pick a character and assume they are a Truth-Teller. If their statement leads to a logical contradiction, your assumption is wrong.
A key rule: *No one can ever claim "I am a liar."* A Truth-Teller can't say it (because it's a lie), and a Liar can't say it (because it would be the truth).
:::

**Q12.** You encounter two inhabitants of an island, A and B. Everyone on the island is either a Knight (always tells the truth) or a Knave (always lies). 
A says: "At least one of us is a Knave."
What are A and B?

(a) A is a Knight, B is a Knight
(b) A is a Knight, B is a Knave
(c) A is a Knave, B is a Knight
(d) A is a Knave, B is a Knave

**Solution:** 
Case 1: Assume A is a Knave. Then A's statement ("At least one of us is a Knave") must be FALSE. The negation of "at least one is a Knave" is "both are Knights". But we assumed A is a Knave, so they can't both be Knights. Contradiction.
Case 2: A must be a Knight. Since A is a Knight, A's statement is TRUE. So, at least one of them is indeed a Knave. Since A is already established as a Knight, B must be the Knave.

**Answer:** (b)

**Q13.** You meet three inhabitants: X, Y, and Z. 
X says: "All three of us are Knaves."
Y says: "Exactly one of us is a Knight."
What is the identity of Z?

(a) Knight
(b) Knave
(c) Cannot be determined
(d) Truth-teller on alternate days

**Solution:** 
Analyze X: If X were a Knight, his statement ("All three are Knaves") would be true, which is a contradiction (since X himself is a Knight). So, X is definitively a Knave. Since X is a Knave, his statement is false. So there is at least one Knight among them.
Analyze Y: Assume Y is a Knave. Then Y's statement ("Exactly one is a Knight") is false. This means there are either 0, 2, or 3 Knights. We know there's at least 1, and X is a Knave (so not 3). Thus, there would be exactly 2 Knights (Y and Z). But we assumed Y is a Knave! Contradiction.
So Y must be a Knight. Y's statement is true: there is exactly one Knight. Since Y is that one Knight, Z must be a Knave.

**Answer:** (b)

**Q14.** You meet two inhabitants, P and Q.
P says: "We are both the same type (both Knights or both Knaves)."
Q says: "We are of different types."
Which of the following is true?

(a) P is a Knight, Q is a Knave
(b) P is a Knave, Q is a Knight
(c) Both are Knights
(d) Both are Knaves

**Solution:** Their statements perfectly contradict each other, so exactly one is a Knight and one is a Knave.
Since they are definitively of different types, P's statement ("We are the same type") is false, making P the Knave.
Q's statement ("We are of different types") is true, making Q the Knight.

**Answer:** (b)

**Q15. (The Classic Two-Guards Variant)** You are trapped in a dungeon with two doors. One leads to freedom, the other to certain doom. Two guards stand before the doors. One guard always tells the truth, and the other always lies, but you don't know which is which. You can ask exactly **one** question to **one** guard to find the door to freedom. 
Which of the following questions guarantees you find the exit?

(a) "Which door leads to freedom?"
(b) "Are you the truth-teller?"
(c) "If I were to ask the other guard which door leads to freedom, what would he say?"
(d) "Is the door on the left the safe one?"

**Solution:** You must ask a question that forces the same predictable output regardless of which guard you are speaking to. 
Option (c) creates a double-negative logic chain. 

- If you ask the Truth-Teller: He knows the Liar will point to the Doom door, so the Truth-Teller truthfully reports this and points to the Doom door.
- If you ask the Liar: He knows the Truth-Teller will point to the Freedom door, so the Liar lies about this and points to the Doom door.
In both cases, the answer you receive will point to the Door of Doom. You simply take the *opposite* door to walk to freedom.

**Answer:** (c)

## 5. Logical Deduction Sets (Syllogisms)

::: keypoint
**Solving Syllogisms via Venn Diagrams**
Translate absolute statements into sets:

- "All A are B": Circle A is entirely inside Circle B.
- "Some A are B": Circle A intersects Circle B.
- "No A are B": Circle A and Circle B do not touch.
A conclusion only follows if it is true in *every possible* valid Venn diagram you can draw.
:::

**Q16.** **Statements:**

1. All computers are machines.
2. Some machines are robots.

**Conclusions:**
I. Some robots are computers.
II. Some computers are robots.

(a) Only I follows
(b) Only II follows
(c) Both I and II follow
(d) Neither I nor II follows

**Solution:** Draw the Venn diagram. The "computers" circle is completely inside the "machines" circle. The "robots" circle overlaps with the "machines" circle. However, there is no guarantee that the "robots" circle overlaps with the inner "computers" circle. It *might*, but it doesn't *have to*. Since a conclusion must be unequivocally true in all scenarios, neither follows.

**Answer:** (d)

**Q17.** **Statements:**

1. No pen is a pencil.
2. All pencils are erasers.

**Conclusions:**
I. No pen is an eraser.
II. Some erasers are pencils.

(a) Only I follows
(b) Only II follows
(c) Both I and II follow
(d) Neither I nor II follows

**Solution:** 

- "No pen is a pencil" $\rightarrow$ Pen and Pencil circles are disjoint (do not touch).
- "All pencils are erasers" $\rightarrow$ Pencil circle is completely inside the Eraser circle.
Conclusion I: "No pen is an eraser." The Pen circle must avoid the Pencil circle, but it *could* easily overlap with the outer Eraser circle. So I does not definitely follow.
Conclusion II: "Some erasers are pencils." Since all pencils are erasers, the space occupied by pencils is part of the eraser space. This is always true.

**Answer:** (b)

**Q18. (OA Variant)** **Statements:**

1. All network anomalies are security alerts.
2. No security alert is a false positive.
3. Some false positives are user errors.

**Conclusions:**
I. No network anomaly is a false positive.
II. Some user errors are not network anomalies.

(a) Only I follows
(b) Only II follows
(c) Both I and II follow
(d) Neither I nor II follows

**Solution:**

- "All anomalies ($A$) are alerts ($S$)" $\rightarrow$ $A$ is inside $S$.
- "No alert ($S$) is a false positive ($F$)" $\rightarrow$ $S$ and $F$ are disjoint. Since $A$ is inside $S$, $A$ and $F$ must also be completely disjoint.
- "Some false positives ($F$) are user errors ($U$)" $\rightarrow$ $F$ and $U$ overlap.
Conclusion I: "No network anomaly is a false positive." This is definitely true because $A$ is strictly inside $S$, and $S$ never touches $F$.
Conclusion II: "Some user errors are not network anomalies." The overlapping region between $F$ and $U$ represents user errors that are false positives. Since false positives ($F$) can never be anomalies ($A$), this specific overlapping group of user errors can *never* be anomalies. Thus, some user errors are definitely not anomalies.

**Answer:** (c)

## Sources

- IndiaBix — https://www.indiabix.com/logical-reasoning/statement-and-assumption/
- IndiaBix — https://www.indiabix.com/logical-reasoning/cause-and-effect/
- PrepInsta — https://prepinsta.com/ (Company-specific logical deduction logic)
- Raymond Smullyan's "What is the Name of This Book?" — Canonical Knights and Knaves truth-teller mechanics
