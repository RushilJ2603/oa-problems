> **Statement only.** Transcribed from the Teradata OA (2 hours, 3 questions, 100 points). There is
> no auto-judge for this one — read it, solve it on paper or in the Compiler tab.

# String Transformation Tracker

Alice starts with a single character string `s = "a"`. She performs a sequence of transformation
operations on this string. Each operation either duplicates the current string or applies an
alphabetic shift transformation before appending. Your task is to determine the character at a
specific position after all transformations are complete.

There are two types of operations:

- **Type 0** duplicates the string by appending an exact copy to itself.
- **Type 1** shifts each character to its next alphabetic character (with `'z'` wrapping to `'a'`),
  then appends this shifted version to the original string.

Given the target position and the sequence of operations, find the character at that position
**efficiently without constructing the entire string**.

**Function Description:** Implement the function `findCharacter` that determines the character at
position `k` in the final string after applying all transformation operations sequentially.

**Function Parameters:**
- `k`: A long long integer representing the target position (**1-indexed**).
- `numOps`: An integer representing the number of operations.
- `ops`: An array of integers where each element is either `0` or `1`, representing the operation type.

**Return:** A single character string representing the character at position `k` in the final
transformed string.

**Input Format:**
- The first line contains a long long integer `k`, the target position.
- The second line contains an integer `numOps`, the number of operations.
- The third line contains `numOps` space-separated integers (`0` or `1`) representing the operation
  sequence.

**Output Format:** Print a single character — the character at position `k` after all
transformations.

**Constraints:**
- `1 <= k <= 10^14`
- `1 <= numOps <= 100`
- `ops[i] ∈ {0, 1}`
- The final string length is guaranteed to be at least `k`

**Sample Input 1:**
```
10
4
0 1 0 1
```
**Sample Output 1:**
```
b
```
**Walkthrough (not printed in the OA — derived from the rules above):** starting from `"a"`,
type 0 gives `"aa"`; type 1 gives `"aa" + "bb" = "aabb"`; type 0 gives `"aabbaabb"`; type 1 gives
`"aabbaabb" + "bbccbbcc"`. Position 10 of that 16-character string is `b`.

---

**Given signature (C++17):**
```cpp
string findCharacter(long long k, int numOps, vector<int> ops) {
    // Write your code here
}
```

**OA limits as shown:** Time 5.0 sec/input file · Memory 256 MB · Source 1024 KB.
Scoring: score is assigned if any testcase passes. Worth 100.00 points.
