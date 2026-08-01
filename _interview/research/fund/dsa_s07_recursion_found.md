# Recursion Foundations

::: heavy
Recursion is like standing between two mirrors facing each other: the image contains a smaller version of itself, repeating until it fades away. In programming, instead of using loops to repeat an action, a function can pause its own execution to call a fresh copy of itself to solve a smaller piece of the problem.
:::

## The anatomy of recursion

Imagine you are in a line of people and want to know your position. Instead of stepping out to count everyone in front of you, you ask the person directly in front of you: "What is your position?" That person does not know either, so they ask the person in front of them. This continues until the question reaches the very first person in line, who confidently answers, "I am number 1." The second person hears this and realizes they are number 2, and the answer ripples back down to you.

::: definition
**Recursion** is a programming technique where a function is defined in terms of itself. Every valid recursive function consists of two parts: a **base case** that stops the recursion by returning a direct answer, and a **recursive case** that shrinks the problem size toward the base case.
:::

When a function calls itself, the computer uses a **call stack** to keep track of the active function calls. Each time the function is invoked, a new call frame containing its local variables and parameters is pushed onto the stack. When a function returns, its frame is popped off the stack, and execution resumes in the caller's frame. The maximum space required is proportional to the maximum depth of the call tree, giving a space complexity of $O(\text{depth})$.

::: trap
If a recursive function lacks a valid base case, or if the recursive case does not correctly shrink toward it, the function will call itself endlessly. This is called **infinite recursion** and results in a **stack overflow** error as the call stack exhausts all available memory.
:::

To reason about a recursive function, we use a recursion tree to visualize the sequence of calls and their returns. Conceptually, it is best to "trust the recursion": assume that the recursive call correctly solves the subproblem, and focus only on how to use that subproblem's result to solve the current problem. The total time complexity can often be modeled as a recurrence relation, such as $T(n) = T(n-1) + O(1)$.

## Types of recursion

**Tail recursion** occurs when the recursive call is the absolute last action executed in the function, with no computation left to perform upon returning. In **head/non-tail recursion**, operations remain after the recursive call returns.

```cpp
#include <iostream>
using namespace std;

void tailRec(int n) {
    if (n == 0) return;
    cout << n << " ";
    tailRec(n - 1); // Last action
}

void headRec(int n) {
    if (n == 0) return;
    headRec(n - 1);
    cout << n << " "; // Action happens after the call returns
}

int main() {
    tailRec(3); // Output: 3 2 1
    cout << "\n";
    headRec(3); // Output: 1 2 3
    cout << "\n";
    return 0;
}
```

**Linear recursion** makes a single recursive call to itself, forming a straight line of calls. **Tree recursion** makes multiple recursive calls, causing the call stack to branch like a tree.

```cpp
#include <iostream>
using namespace std;

int treeRec(int n) {
    if (n <= 1) return n;
    return treeRec(n - 1) + treeRec(n - 2);
}

int main() {
    cout << treeRec(5) << "\n"; // Output: 5
    return 0;
}
```

**Indirect (or mutual) recursion** happens when function `A` calls function `B`, and function `B` calls function `A`.

```cpp
#include <iostream>
using namespace std;

void functionB(int n);

void functionA(int n) {
    if (n > 0) {
        cout << "A" << n << " ";
        functionB(n - 1);
    }
}

void functionB(int n) {
    if (n > 0) {
        cout << "B" << n << " ";
        functionA(n / 2);
    }
}

int main() {
    functionA(5); // Output: A5 B4 A2 B1 
    cout << "\n";
    return 0;
}
```

**Nested recursion** occurs when the argument to the recursive function is itself a recursive call to that function.

```cpp
#include <iostream>
using namespace std;

int nestedRec(int n) {
    if (n > 100) return n - 10;
    return nestedRec(nestedRec(n + 11));
}

int main() {
    cout << nestedRec(95) << "\n"; // Output: 91
    return 0;
}
```

When structuring recursive states, there are two primary patterns: **parameterised recursion** and **functional recursion**. In parameterised recursion, the answer is built as we go down the call stack by passing an accumulator parameter. In functional recursion, the answer is built on the way up by combining the return values of the sub-calls.

::: keypoint
The distinction is fundamental: parameterised recursion passes an accumulator *down* the call chain, whereas functional recursion combines results on the way *up*.
:::

## Basic recursion problems

### Print 1 to N using Recursion

We are given an integer $N$ and must print the numbers from 1 to $N$.

**Intuition:**
We can solve this using parameterised recursion by passing a counter `i` that increments from 1 up to $N$. Alternatively, we can use a backtracking-order approach (head recursion): if we want to print from 1 to $N$, we can recursively call to print 1 to $N-1$ first, and only print $N$ after the recursive call returns.

```cpp
#include <iostream>
using namespace std;

// Parameterised style
void print1toN_param(int i, int n) {
    if (i > n) return;
    cout << i << " ";
    print1toN_param(i + 1, n);
}

// Backtracking (head recursion) style
void print1toN_backtrack(int n) {
    if (n == 0) return;
    print1toN_backtrack(n - 1);
    cout << n << " ";
}

int main() {
    print1toN_param(1, 4);      // Output: 1 2 3 4
    cout << "\n";
    print1toN_backtrack(4);     // Output: 1 2 3 4
    cout << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(N)$ since there are $N$ function calls.
- **Space Complexity:** $O(N)$ for the recursion stack space.
**Practice:** GeeksforGeeks Print 1 to N

### Print N to 1 using Recursion

We are given an integer $N$ and must print the numbers from $N$ down to 1.

**Intuition:**
We print $N$ immediately, and then make a recursive call to print from $N-1$ down to 1. The base case is when $N$ drops to 0.

```cpp
#include <iostream>
using namespace std;

void printNto1(int n) {
    if (n == 0) return;
    cout << n << " ";
    printNto1(n - 1);
}

int main() {
    printNto1(4); // Output: 4 3 2 1
    cout << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(N)$ because the function is called $N$ times.
- **Space Complexity:** $O(N)$ for the call stack.
**Practice:** GeeksforGeeks Print N to 1

### Sum of First N Numbers

Given an integer $N$, calculate the sum of all integers from 1 to $N$.

**Intuition:**
In the parameterised style, we carry a `sum` variable downwards, adding $N$ to it at each step until $N$ becomes 0. In the functional style, we trust the recursion to compute the sum of the first $N-1$ numbers, and then we add $N$ to that returned result.

```cpp
#include <iostream>
using namespace std;

// Parameterised style
void sumParam(int n, int currentSum) {
    if (n == 0) {
        cout << currentSum << "\n";
        return;
    }
    sumParam(n - 1, currentSum + n);
}

// Functional style
int sumFunctional(int n) {
    if (n == 0) return 0;
    return n + sumFunctional(n - 1);
}

int main() {
    sumParam(5, 0);                   // Output: 15
    cout << sumFunctional(5) << "\n"; // Output: 15
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(N)$ to process each number exactly once.
- **Space Complexity:** $O(N)$ for the depth of the call stack.
**Practice:** GeeksforGeeks Sum of first n terms

### Factorial of a Given Number

Given an integer $N$, compute its factorial $N! = N \times (N-1) \times \dots \times 1$.

**Intuition:**
We use a functional style returning $N \times (N-1)!$. The base case is $0! = 1$. Since factorials grow extremely quickly, we must use a `long long` to prevent integer overflow for even relatively small values of $N$.

```cpp
#include <iostream>
using namespace std;

long long factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

int main() {
    cout << factorial(5) << "\n"; // Output: 120
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(N)$ as we multiply $N$ numbers.
- **Space Complexity:** $O(N)$ auxiliary stack space.
**Practice:** GeeksforGeeks Factorial of N numbers

### Reverse an Array

Reverse the elements of an array in-place.

**Intuition:**
We can use a two-pointer recursion approach. A `left` pointer starts at the beginning and a `right` pointer starts at the end. We swap the elements at `left` and `right`, then recursively solve for the smaller internal subarray by incrementing `left` and decrementing `right`. The base case is when `left` meets or crosses `right`.

```cpp
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void reverseArray(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    swap(arr[left], arr[right]);
    reverseArray(arr, left + 1, right - 1);
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    reverseArray(arr, 0, arr.size() - 1);
    for (int x : arr) cout << x << " "; // Output: 5 4 3 2 1
    cout << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(N)$ to swap elements for half the array's length.
- **Space Complexity:** $O(N)$ stack space.
**Practice:** GeeksforGeeks Reverse an Array

### Check if a String is Palindrome

Determine whether a given string reads the same forwards and backwards.

**Intuition:**
We check the outermost characters. If they do not match, the string is not a palindrome. If they do match, we recursively check the inner substring. We can optimize this by only using an index `i` that increments from 0 up to half the string's length, comparing `s[i]` with `s[n - i - 1]`.

```cpp
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string& s, int i) {
    if (i >= s.length() / 2) return true;
    if (s[i] != s[s.length() - i - 1]) return false;
    return isPalindrome(s, i + 1);
}

int main() {
    string s = "racecar";
    cout << (isPalindrome(s, 0) ? "True" : "False") << "\n"; // Output: True
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(N)$ to check up to half the string's characters.
- **Space Complexity:** $O(N)$ for the recursion depth.
**Practice:** GeeksforGeeks Palindrome String

### Fibonacci Number

Compute the $n$-th Fibonacci number, where $F(0) = 0$, $F(1) = 1$, and $F(n) = F(n-1) + F(n-2)$.

**Intuition:**
The problem statement itself is a mathematical recurrence. We directly translate it into a tree-recursive function. Each call branches into two more calls until hitting the base cases $n \le 1$.

![The recursion tree for Fibonacci — each call spawns two, and subproblems repeat.](../assets/fig_fib_rectree.png)

This pure recursive approach is exponential because it redundantly recalculates the same subproblems repeatedly across the recursion tree. This extreme inefficiency sets the stage for Dynamic Programming, where we memoize these repeated results.

```cpp
#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    cout << fibonacci(5) << "\n"; // Output: 5
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(2^n)$ because the recursion tree branches exponentially, bounding the number of nodes at $O(2^n)$.
- **Space Complexity:** $O(n)$ proportional to the maximum height of the recursion tree.
**Practice:** https://leetcode.com/problems/fibonacci-number/

## Close

::: interview
In actual interviews, pure recursion is rarely the final answer. Interviewers will probe your ability to identify the precise base case, state the recurrence relation, analyze the time and space complexity, and discuss the trade-offs between recursion and iteration (particularly stack depth limits and overhead). Often, they will ask you to manually simulate the call stack for a small input or rewrite the algorithm iteratively to eliminate $O(N)$ auxiliary space.
:::

Recursion builds the foundation for more advanced topics: algorithms involving backtracking (subsequences and subsets) and Dynamic Programming build directly on this mental model.
