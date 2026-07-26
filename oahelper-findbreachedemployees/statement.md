# Find Breached Employees

Amazon manages `m` digital storage units accessed by `n` employees. A cybercriminal breached some employee accounts and tampered with storage units those accounts can reach.

You know which `k` units were tampered with (`modifiedUnits`, 1-indexed, distinct). Access rights are given as `n` binary strings of length `m`: the `j`-th character of the `i`-th string is `1` iff employee `i+1` can access unit `j+1`.

An employee is a **potential** suspect if every unit they can access is among the tampered ones (they never touch an untampered unit). Among potential suspects, an employee is **assuredly compromised** if they alone (among potential suspects) can access at least one tampered unit — that unit could only have been reached through their account.

Return the sorted list of assuredly compromised employee IDs (1-indexed). If none, return a single `-1`.

## Input Format

- Line 1: integer `k`.
- Next `k` lines: the tampered unit IDs.
- Next line: integer `n`.
- Next `n` lines: binary strings `accessRights[i]`.

## Output Format

Print the answer IDs one per line (sorted ascending), or a single line `-1`.

## Constraints

- `1 <= n, m <= 2500`
- `1 <= k <= m`
- `1 <= modifiedUnits[i] <= m`, all distinct
- Each `accessRights[i]` has length `m` and contains only `0`/`1`

## Examples

### Example 1

Input:
```
2
2
4
2
0100
0001
```

Output:
```
1
2
```

### Example 2

Input:
```
3
1
2
3
2
111
111
```

Output:
```
-1
```
