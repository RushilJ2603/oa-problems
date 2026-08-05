You are given a string `s` of lowercase English letters. Some letters may occur more than once.

You may delete **one contiguous block** of characters from `s` — that is, choose two indices and
remove everything between them. What is left is the part before the block followed by the part after
it, joined together.

Delete a block so that **every letter in the remaining string occurs exactly once**, and make that
block as short as possible. Print its length.

The block may be empty (if `s` already has no repeated letter, the answer is `0`), and it may be the
whole string.

Read the input from STDIN and print the output to STDOUT. Do not print anything else.

**Input Format:** A single line containing the string `s`.

**Output Format:** A single integer — the length of the shortest block whose removal leaves every
letter distinct.

**Constraints:**
- `1 <= |s| <= 200000`
- `s` contains only lowercase English letters (`a`–`z`)

**Sample Input 1:**
```
abbcbbd
```
**Sample Output 1:**
```
4
```
**Explanation 1:** Removing `bbcb` (positions 2 to 5) leaves `a` + `bd` = `abd`, in which every
letter occurs once. No block of length 3 works: removing `abb` leaves `cbbd`, removing `bbc` leaves
`abbd`, removing `bcb` leaves `abbd`, removing `cbb` leaves `abbd`, and removing `bbd` leaves
`abbc` — each still has a repeated `b`.

**Sample Input 2:**
```
abcde
```
**Sample Output 2:**
```
0
```
**Explanation 2:** Every letter is already distinct, so nothing needs to be removed.

**Sample Input 3:**
```
aaaa
```
**Sample Output 3:**
```
3
```
**Explanation 3:** Any three of the four characters can be removed, leaving a single `a`.
