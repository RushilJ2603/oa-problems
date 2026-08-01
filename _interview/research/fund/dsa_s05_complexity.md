# Complexity Analysis and Asymptotics

## Why Complexity Analysis?

When evaluating an algorithm, timing its execution in seconds is fundamentally flawed. A poorly designed algorithm running on a supercomputer might finish faster than an optimal algorithm on a decade-old laptop. Furthermore, execution time depends on the programming language, compiler optimizations, and system load.

**Complexity analysis** provides a mathematical framework to evaluate the efficiency of an algorithm independent of hardware and environment. Instead of measuring time directly, we measure the *number of fundamental operations* an algorithm performs as a function of the input size, typically denoted as $n$. This allows us to understand how the algorithm's performance scales as the input grows toward infinity.

## Asymptotic Notation

To describe this growth, we use asymptotic notation. It focuses on the dominant term of the growth function and drops constants and lower-order terms, as they become negligible for sufficiently large $n$.

### Big-O Notation: The Upper Bound

Big-O ($O$) notation provides an asymptotic upper bound on the growth rate of a function. It represents the worst-case scenario.

::: definition
Formally, a function $f(n)$ is $O(g(n))$ if there exist positive constants $c$ and $n_{0}$ such that:
$$ f(n) \le c \cdot g(n) \text{ for all } n \ge n_{0} $$
In plain English: past a certain input size $n_{0}$, the algorithm's operations will never exceed $g(n)$ multiplied by some constant.
:::

### Big-Omega Notation: The Lower Bound

Big-Omega ($\Omega$) provides an asymptotic lower bound.

::: definition
Formally, a function $f(n)$ is $\Omega(g(n))$ if there exist positive constants $c$ and $n_{0}$ such that:
$$ f(n) \ge c \cdot g(n) \text{ for all } n \ge n_{0} $$
In plain English: the algorithm takes *at least* this much time for large inputs.
:::

### Big-Theta Notation: The Tight Bound

Big-Theta ($\Theta$) provides an asymptotically tight bound. It means the function grows exactly at the same rate as the bound.

::: definition
Formally, a function $f(n)$ is $\Theta(g(n))$ if it is both $O(g(n))$ and $\Omega(g(n))$. That is, there exist positive constants $c_{1}, c_{2},$ and $n_{0}$ such that:
$$ c_{1} \cdot g(n) \le f(n) \le c_{2} \cdot g(n) \text{ for all } n \ge n_{0} $$
In plain English: the algorithm's runtime is sandwiched between two constant multiples of $g(n)$.
:::

In industry and interviews, people colloquially say "$O(n)$" when they often mathematically mean a tight bound $\Theta(n)$. We will stick to the standard $O$-notation to describe upper bounds, which is the convention in technical interviews.

## Best, Average, and Worst Cases

An algorithm's runtime often depends not just on the size $n$ of the input, but on the *actual values* in the input.

- **Best case**: The minimum number of operations for an input of size $n$.
- **Worst case**: The maximum number of operations for an input of size $n$. This is usually what we care about the most, as it provides a guarantee.
- **Average case**: The expected number of operations over all possible inputs of size $n$, assuming a specific probability distribution (often uniform).

Consider a simple linear search to find a target value in an array:

```cpp
#include <vector>

int linearSearch(const std::vector<int>& arr, int target) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}
```

- **Best case**: The `target` is at the very first index. The loop runs once. Complexity is $O(1)$.
- **Worst case**: The `target` is at the very last index, or not in the array at all. The loop runs $n$ times. Complexity is $O(n)$.
- **Average case**: Assuming the `target` is equally likely to be anywhere, we check about $n/2$ elements on average. Dropping the constant $1/2$, the complexity is $O(n)$.

Similarly, in QuickSort, the worst-case time complexity is $O(n^{2})$ if the pivot chosen is consistently the largest or smallest element. However, its average-case time complexity, with a randomly chosen pivot, is $O(n \log n)$.

## Common Complexity Classes

Understanding the hierarchy of growth rates is crucial. Here are the common classes ordered from fastest to slowest.

| Complexity | Name | Real DSA Example | Growth Rate / Characteristics |
|---|---|---|---|
| $O(1)$ | Constant | Accessing an array by index, hash map lookup. | Does not depend on $n$. |
| $O(\log n)$ | Logarithmic | Binary search, operations on a balanced BST. | Grows extremely slowly. If $n=10^{6}$, $\log_{2}(n) \approx 20$. |
| $O(n)$ | Linear | Traversing an array, linear search. | Grows directly proportionally with $n$. |
| $O(n \log n)$ | Linearithmic | Merge sort, quicksort (average), `std::sort`. | Slower than linear, but standard for efficient sorting. |
| $O(n^{2})$ | Quadratic | Bubble sort, finding all pairs, 2D matrix traversal. | Feasible for $n \le 5000$. |
| $O(2^{n})$ | Exponential | Generating all subsets of a set. | Grows violently. Unusable beyond $n \approx 25$. |
| $O(n!)$ | Factorial | Generating all permutations. | Even worse than exponential. Unusable beyond $n \approx 12$. |

## Amortized Analysis

::: heavy
The concept of amortized analysis can be counter-intuitive because it allows a theoretically expensive operation to be averaged out over a sequence of cheap operations, yielding a low overall cost per operation.
:::

Sometimes, worst-case analysis is too pessimistic for a sequence of operations. **Amortized analysis** calculates the average time taken per operation, over a worst-case *sequence* of operations.

The classic example is adding elements to a dynamic array (`std::vector` in C++).

```cpp
#include <vector>

void appendElements() {
    std::vector<int> nums;
    for (int i = 0; i < 1000; ++i) {
        nums.push_back(i); 
    }
}
```

When you call `push_back`, if the underlying array has capacity, the cost is $O(1)$. However, if the array's capacity is full, the vector must allocate a new, larger block of memory (usually double the current capacity), copy all existing elements over, and then add the new element. This reallocation takes $O(n)$ time.

If we only look at the worst-case single operation, `push_back` is $O(n)$. But in a sequence of $n$ pushes, the expensive $O(n)$ reallocations happen very rarely (at sizes 1, 2, 4, 8, 16...). 

Using the **aggregate method**: the total cost to push $n$ elements involves $n$ standard $O(1)$ insertions, plus the cost of copying elements during expansions: $1 + 2 + 4 + \dots + n/2 \approx n$. The total cost for $n$ operations is bounded by $2n = O(n)$. Therefore, the amortized cost per single `push_back` is $O(n) / n = O(1)$.

::: keypoint
Amortized $O(1)$ means that while a single operation might occasionally be expensive, the *average* cost over a long sequence of operations is strictly bounded by a constant.
:::

## Space Complexity

Just as time complexity measures time, **space complexity** measures the peak memory used by an algorithm as a function of the input size $n$.

We distinguish between two types of space:
1. **Total Space**: The memory taken by the input data plus any extra memory used.
2. **Auxiliary Space**: The extra, temporary memory used by the algorithm *excluding* the input data itself.

In interviews, when asked for "space complexity," the interviewer is almost always asking for **auxiliary space**.

Crucially, **the call stack during recursion consumes memory**. Each recursive call adds a frame to the stack containing local variables and return addresses.

```cpp
#include <iostream>

// Prints from n down to 1
void printDown(int n) {
    if (n <= 0) return;
    std::cout << n << '\n';
    printDown(n - 1); 
}
```

Although `printDown` allocates no dynamic memory (no `new`, no `vector`), it recurses $n$ times. Thus, the maximum depth of the call stack is $n$, meaning the auxiliary space complexity is $O(n)$.

## Recurrence Relations & The Master Theorem

Recursive algorithms often have their runtime expressed as a recurrence relation. The **Master Theorem** provides a direct way to find the Big-O time complexity for divide-and-conquer recurrences of the form:

$$ T(n) = aT(n/b) + f(n) $$

Where:
- $a \ge 1$: The number of subproblems.
- $b > 1$: The factor by which the problem size is divided.
- $f(n)$: The cost of the work done outside the recursive calls (e.g., dividing the problem or merging results). Let $f(n) = O(n^{d})$ for some $d \ge 0$.

By comparing $a$ (the rate of subproblem proliferation) with $b^{d}$ (the rate of work reduction), the Master Theorem defines three cases:

1. **Case 1 (Leaves dominate):** If $a > b^{d}$, then $T(n) = O(n^{\log_{b} a})$. The work at the bottom of the recursion tree dwarfs the work at the top.
2. **Case 2 (Evenly distributed):** If $a = b^{d}$, then $T(n) = O(n^{d} \log n)$. The work is distributed equally across all levels of the tree.
3. **Case 3 (Root dominates):** If $a < b^{d}$, then $T(n) = O(f(n)) = O(n^{d})$. The work done at the top level dominates the total runtime.

### Examples

**Merge Sort:** Divides the array in half ($b=2$), solves two subproblems ($a=2$), and merges them in linear time ($f(n) = O(n^{1})$, so $d=1$).
- $a = 2$, $b^{1} = 2$.
- Since $a = b^{d}$, we are in Case 2.
- $T(n) = O(n^{1} \log n) = O(n \log n)$.

**Binary Search:** Cuts the array in half ($b=2$), solves only one subproblem ($a=1$), and takes constant time to check the midpoint ($f(n) = O(n^{0})$, so $d=0$).
- $a = 1$, $b^{0} = 1$.
- Since $a = b^{d}$, we are in Case 2.
- $T(n) = O(n^{0} \log n) = O(\log n)$.

Alternatively, the **recursion-tree method** draws out the tree of recursive calls, summing the work done at each level to find the total limit. This method provides strong visual intuition and is especially useful when the recurrence falls outside the strict form of the Master Theorem.

## Reading Constraints: The Practical Skill

In competitive programming and modern Online Assessments (OAs), the optimal time complexity is usually implicitly given by the problem's constraints.

Modern servers can comfortably execute around $10^{8}$ simple operations per second in C++. If you have a time limit of $1$ second, you must ensure your worst-case operations do not exceed this magnitude. By looking at the maximum value of $n$, you can reverse-engineer the expected algorithmic approach.

| Constraint (n) | Target complexity | Typical technique |
|---|---|---|
| $n \le 10$..$12$ | $O(n!)$ / $O(2^{n})$ | permutations, bitmask, meet-in-middle |
| $n \le 20$..$25$ | $O(2^{n})$ | subset enumeration, bitmask DP |
| $n \le 500$ | $O(n^{3})$ | Floyd-Warshall, 3D DP |
| $n \le 5000$ | $O(n^{2})$ | nested loops, 2D DP |
| $n \le 10^{5}$..$10^{6}$ | $O(n\log n)$ / $O(n)$ | sorting, binary search, two-pointer, prefix sums |
| $n \ge 10^{7}$..$10^{8}$ | $O(n)$ / $O(\log n)$ | math, greedy, bit tricks |

If an OA specifies $n \le 10^{5}$, writing a nested `for` loop solution $O(n^{2})$ will require $10^{10}$ operations, which will inevitably yield a Time Limit Exceeded (TLE) error. You immediately know you must look for an $O(n \log n)$ or $O(n)$ solution.

::: keypoint
When stating a solution's complexity in an interview, explicitly state both time and space, and give a one-sentence justification. For example: "The time complexity is $O(n \log n)$ because we sort the array, and the auxiliary space complexity is $O(n)$ because we store the frequencies in a hash map."
:::

::: trap
A frequent interview mistake is ignoring the hidden costs of library functions inside loops.
- `std::string` concatenation (`s = s + "a"`) is an $O(k)$ operation, where $k$ is the current string length. In a loop of size $n$, this yields $O(n^{2})$ time.
- `std::map<int, int>` operations (insertion, lookup) are $O(\log n)$, meaning a simple loop over $n$ items doing map lookups is $O(n \log n)$, not $O(n)$.
- `.substr()` creates a brand new string and copies characters, taking $O(L)$ time where $L$ is the length of the substring.
:::
