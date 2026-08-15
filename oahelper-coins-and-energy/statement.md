# Coins and Energy

Alex visits houses arranged in a line. Each house contains both coins and energy. Alex must start at the first house and visit consecutive houses without skipping any, though the journey can end at any point. Moving from one house to the next costs 1 unit of energy.

When visiting a house, Alex can collect either the energy or the coins available there, but not both. The goal is to determine the maximum number of coins Alex can collect while never having a negative energy amount.

**Function Description**

Complete the function `getRich` in the editor with the following parameter(s):

- `long int initialEnergy`: Alex's initial energy
- `int energy[n]`: the energy value at each house
- `int coins[n]`: the coins at each house

**Returns**

`int`: the maximum number of coins that can be collected

**Constraints**

- 1 <= n <= 1000
- 0 <= initialEnergy <= 10^14
- 0 <= energy[i], coins[i] <= 10^3

**Example 1**
Input:
```
1
5
1
5
3
3
1
5
3
23
9
2
2
```
Output:
```
32
```
Explanation:
The best solution is to take energy from the first house, coins from the second and third, then stop. Remaining energy is 3 - 1 - 1 = 1 and 23 + 9 = 32 coins are collected.

**Example 2**
Input:
```
19999
3
12
2
2
3
5
5
5
```
Output:
```
15
```
Explanation:
Alex begins with enough energy to visit all of the houses. The coins collected are 5 + 5 + 5 = 15.
