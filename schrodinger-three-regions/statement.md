A company runs `n` server regions. Region `i` currently holds `machineCount[i]` machines.

Management has decided to concentrate on **exactly three** regions, which must end up holding
`finalMachineCount[0]`, `finalMachineCount[1]` and `finalMachineCount[2]` machines. Any three of the
`n` regions may be chosen — they do not have to be adjacent — and any of the three may be matched to
any of the three required counts. Regions that are not chosen may be left in any state; they do not
have to be emptied.

Two operations are available.

1. **Adjust.** Add machines to a region, or remove machines from it. This costs **1 unit per
   machine** added or removed. A region must still hold at least one machine after an adjustment, so
   a region can never be emptied this way.
2. **Transfer.** Move **all** the machines of one region into another region. This costs
   `shiftingCost` units **per transfer**. The source region is spent: it has given everything away
   and cannot itself be one of the three final regions.

Find the minimum total cost to bring three regions to the three required counts.

Read the input from STDIN and print the output to STDOUT. Do not print anything else.

**Input Format:**
- The first line contains an integer `n`, the number of regions.
- The second line contains `n` integers — `machineCount`.
- The third line contains 3 integers — `finalMachineCount`.
- The fourth line contains an integer — `shiftingCost`.

**Output Format:** A single integer — the minimum total cost.

**Constraints:**
- `3 <= n <= 10`
- `1 <= machineCount[i] <= 10^9`
- `1 <= finalMachineCount[i] <= 10^9`
- `1 <= shiftingCost <= 10^9`

**Sample Input 1:**
```
5
10 15 5 20 12
25 16 8
5
```
**Sample Output 1:**
```
8
```
**Explanation 1:** Adjust the region holding 20 up to 25 (cost 5), the region holding 15 up to 16
(cost 1), and the region holding 10 down to 8 (cost 2), for a total of 8. The regions holding 5 and
12 are left alone. Transferring instead — for example pouring the region of 5 into the region of 12
to get 17 and adjusting down to 16 — costs `shiftingCost + 1 = 6` for that one target, which is
worse than the 1 unit it takes to turn 15 into 16.

**Sample Input 2:**
```
3
4 4 4
12 1 1
1
```
**Sample Output 2:**
```
14
```
**Explanation 2:** With only three regions, all three must be used and no transfer is possible —
a transfer would spend one of the three. The cheapest matching adjusts one region 4 → 12 (cost 8)
and the other two 4 → 1 (cost 3 each): 8 + 3 + 3 = 14.

**Sample Input 3:**
```
6
3 3 3 3 100 1
9 100 1
2
```
**Sample Output 3:**
```
4
```
**Explanation 3:** Pour two of the regions holding 3 into a third, giving 9 at a cost of
`2 × shiftingCost = 4`, and take 100 and 1 as they stand.
