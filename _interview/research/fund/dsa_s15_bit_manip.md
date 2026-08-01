# Bit Manipulation

::: heavy
At the lowest level of modern computing, all data is stored as a sequence of 0s and 1s. Bit manipulation is the act of algorithmically manipulating these individual bits. While most everyday programming abstracts these details away, bit manipulation is essential for high-performance computing, cryptography, and solving specific algorithmic constraints optimally.
:::

## Binary Representation and Operators

In a standard C++ environment, an `int` is a 32-bit signed integer. The **two's complement** system is universally used to represent signed integers. In this system, the most significant bit (the 31st bit, zero-indexed from the right) acts as the sign bit. If it is 0, the number is positive; if it is 1, the number is negative. To find the negative of a number, we invert all its bits (bitwise NOT) and add 1.

![Two's complement: bitwise NOT and how the sign bit is interpreted.](../assets/ss_068.png)

C++ provides six fundamental bitwise operators. `&` (AND), `|` (OR), and `^` (XOR) operate on pairs of bits. `~` (NOT) inverts all bits. The left shift `<<` shifts all bits to the left, bringing in 0s from the right, which is mathematically equivalent to multiplying by a power of 2. The right shift `>>` shifts bits to the right.

![Truth tables for AND, OR, XOR, NOT and the left/right shift operators.](../assets/ss_061.png)

::: trap
**Undefined Behavior and Precedence Traps:**
1. Left-shifting a negative signed integer, or shifting any integer by a value greater than or equal to its width (e.g., `1 << 32` for a 32-bit `int`), invokes Undefined Behavior in C++.
2. The bitwise operators `&`, `|`, and `^` have **lower precedence** than the equality operators `==` and `!=`. Thus, `n & 1 == 0` evaluates as `n & (1 == 0)`. Always parenthesize: `(n & 1) == 0`.
:::

### Core One-Liners

Bit manipulation relies heavily on combining basic operators into "tricks." The following table summarizes the most common bitwise idioms.

| Operation | C++ Expression | Explanation |
| :--- | :--- | :--- |
| Set the $i$-th bit | `x | (1 << i)` | ORing with a 1 at position $i$ forces that bit to 1. |
| Clear the $i$-th bit | `x & ~(1 << i)` | ANDing with a 0 at position $i$ forces it to 0. |
| Toggle the $i$-th bit | `x ^ (1 << i)` | XORing with 1 flips the bit. |
| Check the $i$-th bit | `(x >> i) & 1` | Shift the bit to position 0, then AND with 1. |
| Lowest set bit | `x & -x` | Two's complement `-x` is `~x + 1`, which isolates the lowest 1. |
| Remove lowest set bit | `x & (x - 1)` | Subtracting 1 flips all bits up to the lowest set bit. |
| Check if even | `(x & 1) == 0` | The 0-th bit is 0 for even numbers. |
| Multiply by $2^{k}$ | `x << k` | Shifts the binary representation left. |
| Divide by $2^{k}$ | `x >> k` | Shifts the binary representation right. |

For counting set bits or finding the highest/lowest set bit, prefer the C++ built-ins covered in Part I: `__builtin_popcount()`, `__builtin_clz()`, and `__builtin_ctz()`.

## Learn Bit Manipulation

### Introduction to Bits and Tricks

The expressions in the table above can be written as tiny helper functions or used directly inline. Familiarizing yourself with these one-liners is the first step, as they serve as the building blocks for the more complex algorithms that follow.

### Check if the i-th Bit is Set

Given a number $N$ and a 0-indexed position $i$, check if the $i$-th bit from the right is set to 1.

We shift $N$ to the right by $i$ places to bring the bit of interest to the 0-th position, and then perform a bitwise AND with 1 to isolate it.

```cpp
bool checkKthBit(int n, int k) {
    return ((n >> k) & 1) != 0;
}
```

**Complexity:** $O(1)$ time and $O(1)$ space.
**Practice:** GeeksforGeeks Check whether K-th bit is set or not

### Check if a Number is Odd

Given an integer $N$, determine if it is odd using bit manipulation.

The least significant bit (0-th bit) of any odd integer is 1, and for even integers, it is 0. A bitwise AND with 1 zeroes out all higher-order bits, leaving only the 0-th bit.

```cpp
bool isOdd(int n) {
    return (n & 1) != 0;
}
```

**Complexity:** $O(1)$ time and $O(1)$ space.
**Practice:** GeeksforGeeks Odd or Even

### Check if a Number is a Power of 2

Given an integer $N$, determine if it is a power of 2.

A power of 2 has exactly one bit set in its binary representation (e.g., 8 is `1000` in binary). Subtracting 1 flips all bits up to and including that single set bit (e.g., 7 is `0111`). Thus, bitwise ANDing $N$ with $N-1$ clears that sole set bit. If $N$ was indeed a power of 2, the result becomes exactly 0. We must also check `n > 0` since non-positive numbers cannot be powers of 2.

![Checking a power of two: a power of two has exactly one set bit, so N & (N-1) clears it to zero.](../assets/ss_082.png)

::: keypoint
The expression `n & (n - 1)` drops the lowest set bit of `n`. For a power of 2, since it only has one set bit, this operation yields exactly 0.
:::

```cpp
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}
```

**Complexity:** $O(1)$ time and $O(1)$ space.
**Practice:** https://leetcode.com/problems/power-of-two/

### Count the Number of Set Bits

Given an integer $N$, return the number of set bits (1s) in its binary representation.

Instead of iterating through all 32 bits, we can use Brian Kernighan's algorithm. By repeatedly updating $N$ to `n & (n - 1)`, we systematically clear the lowest set bit on each iteration. The number of iterations until $N$ becomes 0 is exactly the number of set bits.

```cpp
int countSetBits(int n) {
    int count = 0;
    while (n != 0) {
        n = n & (n - 1);
        count++;
    }
    return count;
}
```

In competitive programming, you should use the compiler intrinsic `__builtin_popcount(n)` instead, which often compiles down to a single hardware instruction.

**Complexity:** $O(k)$ time where $k$ is the number of set bits, $O(1)$ space.
**Practice:** https://leetcode.com/problems/number-of-1-bits/

### Swap Two Numbers

Swap the values of two variables $A$ and $B$ without using an extra variable.

XOR is self-inverse (`X ^ X = 0`) and has an identity of 0 (`X ^ 0 = X`). If we chain XOR operations between the two variables, we can swap their contents algebraically. Note that this is mostly an interview curiosity; in production code, always use `std::swap`.

```cpp
void swapNumbers(int& a, int& b) {
    a = a ^ b;
    b = a ^ b; // b becomes (a ^ b) ^ b = a
    a = a ^ b; // a becomes (a ^ b) ^ a = b
}
```

**Complexity:** $O(1)$ time and $O(1)$ space.
**Practice:** GeeksforGeeks Swap two numbers

### Divide Two Integers without `*` `/` `%`

Divide two integers `dividend` and `divisor` without using multiplication, division, and modulo operations.

Division is fundamentally repeated subtraction. To optimize, we find the largest multiple of the `divisor` scaled by $2^{k}$ that fits in the `dividend`. We shift the `divisor` left until it exceeds the `dividend`, subtract that shifted value, and add $2^{k}$ to our quotient. We repeat this process for the remainder.

::: trap
Left-shifting a value until it reaches the sign bit is Undefined Behavior. We must safely convert values to `long long` before operating. Additionally, dividing `INT_MIN` by `-1` yields `INT_MAX + 1`, which overflows a 32-bit integer.
:::

```cpp
#include <climits>
#include <cmath>

int divide(int dividend, int divisor) {
    // Handle overflow edge case
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }
    
    long long n = std::abs((long long)dividend);
    long long d = std::abs((long long)divisor);
    long long quotient = 0;
    
    while (n >= d) {
        long long temp = d;
        long long multiple = 1;
        
        // Find the highest power of 2 that d can be multiplied by
        while (n >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }
        
        n -= temp;
        quotient += multiple;
    }
    
    // Determine the sign of the result
    bool sign = (dividend < 0) == (divisor < 0);
    return sign ? quotient : -quotient;
}
```

**Complexity:** $O(\log n)$ time where $n$ is the dividend (we shift at most 31 times), $O(1)$ space.
**Practice:** https://leetcode.com/problems/divide-two-integers/

## Interview Problems

### Minimum Bit Flips to Convert Number

Given two numbers `start` and `goal`, find the minimum number of bit flips to convert `start` to `goal`.

A bit flip is required precisely where the bits of `start` and `goal` differ. The bitwise XOR operator `^` yields a 1-bit exactly at the positions where two numbers differ. We simply compute `start ^ goal` and count its set bits.

```cpp
int minBitFlips(int start, int goal) {
    int xorResult = start ^ goal;
    int count = 0;
    while (xorResult != 0) {
        xorResult = xorResult & (xorResult - 1);
        count++;
    }
    return count;
}
```

**Complexity:** $O(k)$ time where $k$ is the number of differing bits, $O(1)$ space.
**Practice:** https://leetcode.com/problems/minimum-bit-flips-to-convert-number/

### Single Number I

Given a non-empty array of integers where every element appears twice except for one, find that single one.

XOR is commutative and associative. Because XORing a number with itself yields 0, all the numbers that appear twice will cancel each other out, leaving only the unique number.

::: keypoint
XOR is its own inverse. When paired elements are XORed cumulatively, they annihilate each other, cleanly isolating the odd-one-out.
:::

```cpp
#include <vector>

int singleNumber(const std::vector<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num;
    }
    return result;
}
```

**Complexity:** $O(n)$ time, $O(1)$ space.
**Practice:** https://leetcode.com/problems/single-number/

### Power Set (subsets via bitmask)

Given an integer array of unique elements, return all possible subsets.

An array of $n$ elements has $2^{n}$ subsets. Each subset corresponds exactly to a binary number from $0$ to $2^{n}-1$. If the $i$-th bit is set in the binary representation of our loop variable `mask`, we include the $i$-th element of the array in our current subset. While elegant, note that backtracking is often preferred when subsets must be generated in a specific lexicographical order.

```cpp
#include <vector>

std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
    int n = nums.size();
    int subsetCount = 1 << n;
    std::vector<std::vector<int>> result;
    
    for (int mask = 0; mask < subsetCount; mask++) {
        std::vector<int> currentSubset;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                currentSubset.push_back(nums[i]);
            }
        }
        result.push_back(currentSubset);
    }
    
    return result;
}
```

**Complexity:** $O(n \cdot 2^{n})$ time to generate all subsets, $O(n \cdot 2^{n})$ space to store the output.
**Practice:** https://leetcode.com/problems/subsets/

### XOR of Numbers in a Given Range

Given a range $[L, R]$, find the XOR of all numbers from $L$ to $R$ inclusive.

A linear scan would be $O(n)$, which is too slow. We use the prefix XOR property: let $f(n)$ be the XOR of all numbers from 1 to $n$. The XOR from $L$ to $R$ is $f(R) \oplus f(L-1)$. The function $f(n)$ exhibits a strict repeating cycle based on $n \pmod 4$.

```cpp
int xor1ToN(int n) {
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0; // if n % 4 == 3
}

int findXORInRange(int l, int r) {
    return xor1ToN(r) ^ xor1ToN(l - 1);
}
```

**Complexity:** $O(1)$ time and $O(1)$ space.
**Practice:** GeeksforGeeks Find XOR of numbers from L to R

### Single Number III

Given an integer array where exactly two elements appear only once and all other elements appear exactly twice, find the two elements that appear only once.

If we XOR all elements, the pairs cancel out, leaving $X \oplus Y$ where $X$ and $Y$ are the unique numbers. Since $X \neq Y$, their XOR result will have at least one set bit. We extract the lowest set bit of this XOR result. This bit represents a specific position where $X$ and $Y$ differ. By grouping all numbers in the original array based on whether this particular bit is set or not, we cleanly separate $X$ and $Y$ into two different buckets. XORing through each bucket isolates them.

```cpp
#include <vector>

std::vector<int> singleNumber(const std::vector<int>& nums) {
    long long xorAll = 0;
    for (int num : nums) {
        xorAll ^= num;
    }
    
    // Find the lowest set bit. Cast to long long to prevent UB on INT_MIN
    long long lowestSetBit = xorAll & -xorAll;
    
    int bucket1 = 0;
    int bucket2 = 0;
    
    for (int num : nums) {
        if ((num & lowestSetBit) != 0) {
            bucket1 ^= num;
        } else {
            bucket2 ^= num;
        }
    }
    
    return {bucket1, bucket2};
}
```

**Complexity:** $O(n)$ time, $O(1)$ space.
**Practice:** https://leetcode.com/problems/single-number-iii/

## Close

::: interview
What interviewers probe here:
- **Popcount algorithms:** Do you know Brian Kernighan's algorithm (`n & (n - 1)`) versus a naive shift-by-1 loop?
- **Power of Two:** They expect the $O(1)$ `(n & (n - 1)) == 0` check, not a `while` loop dividing by 2.
- **XOR Pair Tricks:** Using XOR to cancel out duplicate pairs and isolate odd-appearing numbers.
- **Bitmask Subsets:** Can you cleanly iterate `mask` from $0$ to $2^{n}-1$ and extract bits to generate subsets?
- **Precedence Trap:** Do you explicitly parenthesize bitwise operations (e.g., `(n & 1) == 0`), knowing that `==` binds tighter than `&`?
:::
