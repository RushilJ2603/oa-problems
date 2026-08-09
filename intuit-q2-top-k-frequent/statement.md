# Top K Frequent Elements

A log line arrives as a list of tags — words like `distribution`, `topic`, `logic`. Given the list
and an integer `k`, report the `k` tags that occur most often.

The order of the report is fixed:

1. **more frequent first**;
2. when two tags occur the **same** number of times, the **lexicographically smaller** one comes
   first (`logic` before `topic`, and `ab` before `abc`).

Position in the input never breaks a tie — only the spelling does.

## Input

- The first line contains a single integer `n` — the number of tags in the list.
- The second line contains `n` space-separated tags.
- The third line contains a single integer `k`.

## Output

A single line with the `k` tags, space-separated, in the order defined above.

## Constraints

- `1 <= n <= 2 * 10^5`
- Each tag is `1` to `20` lowercase English letters (`a`–`z`).
- `1 <= k <=` the number of **distinct** tags in the list.

## Example 1

**Input**
```
6
topic logic distribution topic logic topic
2
```

**Output**
```
topic logic
```

**Explanation:** `topic` appears 3 times, `logic` 2 times, `distribution` once. The two most frequent
are `topic`, then `logic`.

## Example 2

**Input**
```
5
topic logic distribution schema logic
3
```

**Output**
```
logic distribution schema
```

**Explanation:** `logic` appears twice, so it is first. `distribution`, `schema` and `topic` each
appear once; among those three the lexicographically smallest two are `distribution` and `schema`,
so `topic` is left out even though it appeared earlier in the list.
