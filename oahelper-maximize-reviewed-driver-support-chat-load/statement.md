# Maximize Reviewed Support Chat Load

Uber keeps a minute-by-minute log of active driver-support chats in the array `chatLoad`, where `chatLoad[i]` is the number of chats at minute `i`.

During an audit, the ops team is given an even-length list `reviewMinutes` of `k` specific minutes (values may repeat). They will run exactly `k / 2` investigations. Each investigation:

1. Picks two still-unused indices `i` and `j` from `reviewMinutes`.
2. Lets `start = min(reviewMinutes[i], reviewMinutes[j])` and `end = max(reviewMinutes[i], reviewMinutes[j])`.
3. Adds the sum of `chatLoad[start] + chatLoad[start+1] + ... + chatLoad[end]` to the reviewed total.
4. Removes those two entries from further use.

Choose the pairing that **maximises** the total reviewed chat load, then print that total modulo `10^9 + 7`.

## Input Format

- Line 1: integer `n` — length of `chatLoad`.
- Line 2: `n` integers `chatLoad[0] .. chatLoad[n-1]`.
- Line 3: even integer `k` — length of `reviewMinutes`.
- Line 4: `k` integers `reviewMinutes[0] .. reviewMinutes[k-1]`.

## Output Format

Print a single integer — the maximum total reviewed load, modulo `10^9 + 7`.

## Constraints

- `1 <= n <= 10^5`
- `2 <= k <= 10^5`, `k` is even
- `0 <= chatLoad[i] <= 10^7`
- `0 <= reviewMinutes[i] < n` (duplicates allowed)

## Examples

### Example 1

Input:
```
5
2 4 2 1 6
4
4 1 1 3
```

Output:
```
20
```

Explanation: Pair minutes `4` and `1` (sum `13`), then the remaining `1` and `3` (sum `7`). Total `20`.

### Example 2

Input:
```
4
1 2 3 4
2
0 0
```

Output:
```
1
```

Explanation: The only pair is `(0, 0)`, contributing `chatLoad[0] = 1`.
