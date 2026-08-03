Amazon's warehouse management team is planning to roll out standards that every warehouse manager will follow. Some products may need to be moved initially from one container to another so that each container complies.

A warehouse stores `n` identical containers arranged in a circle. The distance between two adjacent containers is 1. Each container should hold the same number of products. Plan the optimal set of movements under the following rules:

- Move products from any location in either the clockwise or the anti-clockwise direction. The direction must remain the same throughout the remaining moves.
- While moving, collect excess products from some locations and deliver them to other locations that need more units. You may never carry a negative cargo (you cannot deliver products you have not yet collected).
- The cost of each product transfer is the distance the product is moved.
- The total cost is the sum of the costs for all products transferred. Equivalently, when a courier walks the circle carrying cargo, each step between adjacent containers costs the current cargo amount.

Find the minimum cost such that finally every container has the same number of products.

It is guaranteed that the total number of products is divisible by `n`, so an equal distribution always exists.

### Input Format

The first line contains an integer `n`, the number of containers.
Each of the next `n` lines contains an integer `products[i]` — the number of products initially at container `i` (0-indexed in storage order; the circle wraps from `n-1` back to `0`).

### Output Format

Print a single integer: the minimum redistribution cost.

### Constraints

- `1 <= n <= 10^5`
- `0 <= products[i] <= 10^5`
- The sum of `products` is divisible by `n`.

### Example 1

Input:
```
5
3
4
6
6
6
```

Output:
```
7
```

Average = 5. Starting at the 3rd container and moving clockwise, collecting one excess from each of positions 3, 4 and 5 and delivering to deficits yields total cost 7, which is optimal.

### Example 2

Input:
```
5
1
11
1
1
1
```

Output:
```
20
```

Average = 3. Starting from the 2nd position clockwise and transferring the excess of 8 units around the circle costs `2*1 + 2*2 + 2*3 + 2*4 = 20`.
