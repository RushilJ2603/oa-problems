# Coding–Decoding

::: keypoint
The bedrock of coding-decoding is the 1-indexed alphabet and its reverse. Memorize the forward positions:
Forward: $A=1, B=2, C=3, \ldots, Z=26$
Reverse (Opposite): $A=26, B=25, C=24, \ldots, Z=1$
Rule: $\text{Reverse Position} = 27 - \text{Forward Position}$
Most codes are a uniform $+n$ or $-n$ shift, a direct positional map, or an opposite-letter substitution. Always test a uniform forward shift first.
:::

## Letter-shift coding

**Q1.** In a certain code, `BAKE` is written as `CCNH`. How is `FIRE` written in that code?
(a) `GJUI` (b) `GKUK` (c) `GKUI` (d) `GLUI`

**Solution:**
Check the shift position-by-position:

- B ($2$) $\to$ C ($3$): $+1$
- A ($1$) $\to$ C ($3$): $+2$
- K ($11$) $\to$ N ($14$): $+3$
- E ($5$) $\to$ H ($8$): $+4$
Applying the $+1, +2, +3, +4$ pattern to `FIRE` ($6, 9, 18, 5$):

- F $+ 1 =$ G ($7$)
- I $+ 2 =$ K ($11$)
- R $+ 3 =$ U ($21$)
- E $+ 4 =$ I ($9$)

**Answer:** `GKUI` (c)

**Q2.** In a certain code language, `WATER` is written as `YCVGT`. Which word is coded as `HKTG` in that language?
(a) `FIRE` (b) `FEAR` (c) `GEAR` (d) `BEAR`

**Solution:**
Identify the encoding shift: W ($23$) $\to$ Y ($25$), which is $+2$. The whole word shifts by $+2$.
Since we are given the *coded* word `HKTG` and need to find the original word, we must decode by shifting $-2$:
H ($8$) $- 2 = 6$ (F)
K ($11$) $- 2 = 9$ (I)
T ($20$) $- 2 = 18$ (R)
G ($7$) $- 2 = 5$ (E)

**Answer:** `FIRE` (a)

::: trap
Always read carefully to see if you are asked to encode a new word ("How is X written") or decode a given code ("Which word is coded as X"). Applying a $+n$ forward shift when you should apply a reverse $-n$ shift is a classic pitfall.
:::

**Q3.** If `MONKEY` is coded as `XDJMNL`, how would `TIGER` be coded?
(a) `QDFHS` (b) `SDFHS` (c) `SHFDQ` (d) `UJHFS`

**Solution:**
When the first letter's shift is irregular, check the opposite end. M ($13$) is far from X ($24$), but the last letter Y ($25$) is adjacent to X ($24$).
The pattern is: reverse the word, then apply a $-1$ shift.
Reverse of `MONKEY` is `YEKNOM`.
Shift $-1$: Y $\to$ X, E $\to$ D, K $\to$ J, N $\to$ M, O $\to$ N, M $\to$ L $\implies$ `XDJMNL`.
Apply to `TIGER`:
Reverse is `REGIT`.
Shift $-1$: R $\to$ Q, E $\to$ D, G $\to$ F, I $\to$ H, T $\to$ S.

**Answer:** `QDFHS` (a)

**Q4.** In a certain code, `ROAST` is written as `PQYUR`. How is `SLOPPY` written in that code?
(a) `QNMRNA` (b) `QJNRRW` (c) `QNNRWA` (d) `QNMMWA`

**Solution:**
Check the shift for each letter:
R ($18$) $\to$ P ($16$): $-2$
O ($15$) $\to$ Q ($17$): $+2$
A ($1$) $\to$ Y ($25$): $-2$ (wrapping around the alphabet)
S ($19$) $\to$ U ($21$): $+2$
T ($20$) $\to$ R ($18$): $-2$
The shift alternates: $-2, +2, -2, +2, -2$.
Apply to `SLOPPY`:
S ($19$) $- 2 = 17$ (Q)
L ($12$) $+ 2 = 14$ (N)
O ($15$) $- 2 = 13$ (M)
P ($16$) $+ 2 = 18$ (R)
P ($16$) $- 2 = 14$ (N)
Y ($25$) $+ 2 = 27 \equiv 1$ (A)

**Answer:** `QNMRNA` (a)

**Q5. (OA Variant)** In a certain logic, if `SERVER` is encoded as `HVIIVI`, how is `CLIENT` encoded?
(a) `XOVRMG` (b) `XOVUOG` (c) `XORVMG` (d) `XROVMG`

**Solution:**
Check the positions of the letters in `SERVER` and `HVIIVI`.
S ($19$) $\to$ H ($8$): Sum is $27$.
E ($5$) $\to$ V ($22$): Sum is $27$.
R ($18$) $\to$ I ($9$): Sum is $27$.
The pattern is the opposite letter in the alphabet ($27 - \text{position}$).
Apply to `CLIENT`:
C ($3$) $\to$ X ($24$)
L ($12$) $\to$ O ($15$)
I ($9$) $\to$ R ($18$)
E ($5$) $\to$ V ($22$)
N ($14$) $\to$ M ($13$)
T ($20$) $\to$ G ($7$)

**Answer:** `XORVMG` (c)

## Substitution / word coding

**Q6.** If `white` is called `blue`, `blue` is called `red`, `red` is called `yellow`, `yellow` is called `green`, `green` is called `black`, and `black` is called `violet`, what would be the color of human blood?
(a) `red` (b) `green` (c) `yellow` (d) `violet`

**Solution:**
The actual color of human blood is red.
According to the forward substitution rule, `red` is called `yellow`.

**Answer:** `yellow` (c)

**Q7.** If `eye` means `hand`, `hand` means `mouth`, `mouth` means `ear`, `ear` means `nose`, and `nose` means `tongue`, with which of the following would a person hear?
(a) `eye` (b) `mouth` (c) `nose` (d) `ear`

**Solution:**
A person hears with an ear.
However, notice the keyword **means**. This denotes a reverse mapping ("Code means Actual Object").
The wording "`mouth` means `ear`" implies that the code word `mouth` is used to denote the actual `ear`.
Therefore, a person hears with a `mouth`.

**Answer:** `mouth` (b)

::: trap
"Is called" implies a forward mapping (Actual $\to$ Code). "Means" implies a backward mapping (Code $\to$ Actual). Always check which keyword is used, or you will answer one step in the wrong direction.
:::

**Q8.** If `ROSE` is coded as $6821$, `CHAIR` is coded as $73456$ and `PREACH` is coded as $961473$, what will be the code for `SEARCH`?
(a) $246173$ (b) $214673$ (c) $214763$ (d) $216473$

**Solution:**
This is a direct letter-to-digit substitution. The letters in `SEARCH` are fully available in the given words.
Find the digits corresponding to each letter:
S = $2$ (from `ROSE`)
E = $1$ (from `ROSE` / `PREACH`)
A = $4$ (from `CHAIR`)
R = $6$ (from `ROSE`)
C = $7$ (from `CHAIR`)
H = $3$ (from `CHAIR`)
So, `SEARCH` = $214673$.

**Answer:** $214673$ (b)

**Q9.** In a certain code, `APPROACH` is written as `CHOAPRAP`. How is `RESTRICT` written in that code?
(a) `CTRISTER` (b) `CTRISTRE` (c) `CTRSTIRE` (d) `CTSRTIRE`

**Solution:**
Analyze the rearrangement of `APPROACH`. Group it into pairs:
`AP`, `PR`, `OA`, `CH`.
The coded word is `CHOAPRAP`. This is exactly the original pairs reversed in their structural order: `CH`, `OA`, `PR`, `AP`.
Apply to `RESTRICT`:
Pairs: `RE`, `ST`, `RI`, `CT`.
Reverse the order of the pairs: `CT`, `RI`, `ST`, `RE`.

**Answer:** `CTRISTRE` (b)

**Q10.** If the word `PHYSICS` is coded as `CHIPSSY`, how is `HISTORY` coded?
(a) `HIORSTY` (b) `HIOSTRY` (c) `HIRSTOY` (d) `HIORSYT`

**Solution:**
Look at the letters in `CHIPSSY`. They are the exact same letters as `PHYSICS`, but sorted in alphabetical order (C, H, I, P, S, S, Y).
Apply this alphabetical sorting to `HISTORY`:
H, I, O, R, S, T, Y.

**Answer:** `HIORSTY` (a)

## Number & symbol coding

**Q11.** If `CAB` is equal to $12$ and `FED` is equal to $30$, then what will `HIDE` be equal to?
(a) $44$ (b) $52$ (c) $68$ (d) $72$

**Solution:**
Write down the standard alphabet positions:
`CAB`: $3, 1, 2$. Sum $= 6$. The code is $12$, which is $6 \times 2$.
`FED`: $6, 5, 4$. Sum $= 15$. The code is $30$, which is $15 \times 2$.
The pattern is: $(\text{Sum of positions}) \times 2$.
`HIDE`: $8, 9, 4, 5$. Sum $= 26$.
Result $= 26 \times 2 = 52$.

**Answer:** $52$ (b)

**Q12.** If `GO` is coded as $32$ and `SHE` is coded as $49$, then how will `SOME` be coded?
(a) $56$ (b) $58$ (c) $62$ (d) $64$

**Solution:**
Test standard positions for `GO`: G($7$) + O($15$) $= 22$. This does not equal $32$.
Test reverse (opposite) positions:
Reverse of G is T ($20$), reverse of O is L ($12$). Sum $= 20 + 12 = 32$. This matches.
Verify with `SHE`:
Reverse positions for S, H, E are $8, 19, 22$.
Sum $= 8 + 19 + 22 = 49$. Matches.
Apply to `SOME`:
Reverse positions for S, O, M, E are $8, 12, 14, 22$.
Sum $= 8 + 12 + 14 + 22 = 56$.

**Answer:** $56$ (a)

::: keypoint
To quickly find the sum of reverse positions for an $n$-letter word without calculating each reverse letter:
$\text{Reverse Sum} = 27n - (\text{Sum of forward positions})$.
For `SOME` ($4$ letters): Forward sum = $19 + 15 + 13 + 5 = 52$.
Reverse Sum $= 27(4) - 52 = 108 - 52 = 56$.
:::

**Q13. (OA Variant)** In a certain coding logic, `PEN` is written as $35$ and `CAR` is written as $22$. How is `BULL` written?
(a) $45$ (b) $47$ (c) $51$ (d) $53$

**Solution:**
Check standard positions:
`PEN`: $16 + 5 + 14 = 35$. Matches directly.
`CAR`: $3 + 1 + 18 = 22$. Matches directly.
The pattern is just the sum of the forward positions.
`BULL`: $2 + 21 + 12 + 12 = 47$.

**Answer:** $47$ (b)

**Q14. (OA Hard Variant)** In a corporate assessment, the word `MACHINE` is coded as $19-7-9-14-15-20-11$. How will you code `DANGER`?
(a) $10-7-20-13-11-24$
(b) $11-7-20-16-11-24$
(c) $13-7-20-9-11-25$
(d) $10-7-20-14-11-24$

**Solution:**
Write standard positions of `MACHINE`:
M($13$), A($1$), C($3$), H($8$), I($9$), N($14$), E($5$).
Compare positions to the given code $19, 7, 9, 14, 15, 20, 11$:
$13 \to 19$ ($+6$)
$1 \to 7$ ($+6$)
$3 \to 9$ ($+6$)
$8 \to 14$ ($+6$)
Each number is the letter's forward alphabetical position $+6$.
Apply to `DANGER` ($4, 1, 14, 7, 5, 18$):
D($4$) $+ 6 = 10$
A($1$) $+ 6 = 7$
N($14$) $+ 6 = 20$
G($7$) $+ 6 = 13$
E($5$) $+ 6 = 11$
R($18$) $+ 6 = 24$
Result: $10-7-20-13-11-24$.

**Answer:** $10-7-20-13-11-24$ (a)

## New-pattern (message) coding

::: heavy
For multiple sentence decoding, do not assume words match up in the exact order they appear. Find common words across different sentences to mechanically isolate their specific codes via elimination.
:::

**Q15.** In a certain code language,
`123` means `hot filtered coffee`,
`356` means `very hot day`,
`589` means `day and night`.
Which digit stands for `very`?
(a) $5$ (b) $6$ (c) $8$ (d) $9$

**Solution:**
Compare statements 1 and 2:
`123` = `hot filtered coffee`
`356` = `very hot day`
The common digit is `3`, and the common word is `hot`. So, `hot` = `3`.
Compare statements 2 and 3:
`356` = `very hot day`
`589` = `day and night`
The common digit is `5`, and the common word is `day`. So, `day` = `5`.
In statement 2 (`356`), `3` is `hot`, `5` is `day`. Thus, the remaining digit `6` must be `very`.

**Answer:** $6$ (b)

**Q16.** In a certain language,
`pit na som` means `bring me water`,
`na jo tod` means `water is life`,
`tub od pit` means `give me toy`,
`jo lin kot` means `life and death`.
Which of the following represents `is` in that language?
(a) `jo` (b) `na` (c) `tod` (d) `lin`

**Solution:**
From statements 1 and 2: `na` is common, `water` is common $\implies$ `water` = `na`.
From statements 2 and 4: `jo` is common, `life` is common $\implies$ `life` = `jo`.
Look at statement 2: `na jo tod` means `water is life`.
We know `na` = `water` and `jo` = `life`. The remaining code is `tod`, which must mean `is`.

**Answer:** `tod` (c)

**Q17. (OA Chinese Coding Variant)** In a secure communication system:
`work is very hard` is coded as `#K4 &S2 @Y4 %D4`
`study and excel there` is coded as `$Y5 *D3 ^L5 !E5`
`always do good deeds` is coded as `~S6 +O2 =D4 -S5`
What is the code for `excel`?
(a) `^L5` (b) `$Y5` (c) `!E5` (d) `*D3`

**Solution:**
Analyze the structure: Symbol + Letter + Number.

1. **Number**: Matches the total number of letters in the word. (`excel` has $5$ letters $\implies$ ends in $5$).
2. **Letter**: Matches the last letter of the word. (`excel` ends in `l` $\implies L$).
Combining these, the code for `excel` must end in `L5`.
Looking at the options, only `^L5` has this structure. (The symbols uniquely map to the first letter of the words, but we do not need to derive that mapping to eliminate the options).

**Answer:** `^L5` (a)

## Conditional coding

::: interview
Conditional coding requires mechanically testing a word against a prioritized list of rules. Interviewers check your attention to detail here: if multiple conditions apply, read the instructions carefully to see if you must apply all of them sequentially, or just the first matching one.
:::

**Q18.** Letters are mapped to digits and symbols as follows:
M $\to 8$, O $\to 9$, T $\to 7$, H $\to @$, E $\to 2$, R $\to *$, I $\to 4$, N $\to \#$, A $\to 1$, S $\to 5$.
Conditions for encoding a word (apply all valid rules sequentially from 1 to 3, modifying the code at each step):

1. If the first and last letters are both consonants, both are coded as `!`.
2. If the first letter is a vowel and the last is a consonant, their codes are interchanged.
3. If the word contains exactly two vowels, the first vowel appearing in the word has its current code changed to `+`.

What is the code for `MOTHER`?
(a) `!97@2!` (b) `*7@2!` (c) `!+7@2!` (d) `!97@+!`

**Solution:**
Base code for `MOTHER` from the mapping: M=$8$, O=$9$, T=$7$, H=$@$, E=$2$, R=$*$. Base is $897@2*$.
Check Rule 1: First letter (M) and last letter (R) are both consonants. This applies. Both are coded as `!`. The code becomes `!97@2!`.
Check Rule 2: First is not a vowel. Does not apply.
Check Rule 3: The word `MOTHER` contains exactly two vowels (O and E). This applies. The first vowel in the word (O) gets its code changed to `+`. The second position becomes `+`. The code becomes `!+7@2!`.

**Answer:** `!+7@2!` (c)

**Q19. (OA Variant)** Using the same mapping and rules as the previous question, what is the code for `OTHER`?
(a) `*7@29` (b) `+7@29` (c) `+7@2*` (d) `*7@+9`

**Solution:**
Base code for `OTHER`: O=$9$, T=$7$, H=$@$, E=$2$, R=$*$. Base is $97@2*$.
Check Rule 1: First letter is a vowel. Does not apply.
Check Rule 2: First letter (O) is a vowel and last letter (R) is a consonant. This applies. Interchange their current codes in the string. $9$ and $*$ swap places. The code becomes $*7@29$.
Check Rule 3: The word `OTHER` contains exactly two vowels (O and E). This applies. The first vowel (O, which is at position 1) has its *current* code changed to `+`. Its current code is $*$ (due to Rule 2). It becomes `+`.
The code becomes `+7@29`.

**Answer:** `+7@29` (b)

## Sources

- IndiaBix — https://www.indiabix.com/logical-reasoning/coding-and-decoding/
- GeeksforGeeks Aptitude — https://www.geeksforgeeks.org/aptitude-coding-decoding/
- PrepInsta — https://prepinsta.com/tcs-nqt/coding-decoding/
- CareerBless — http://www.careerbless.com/aptitude/qa/coding_decoding.php
