# 13. Algorithms & Problem-Solving in C

Algorithms are step-by-step procedures for solving problems. In C, without a large standard library of data structures, we write algorithms directly against raw memory and arrays.

## Complexity Analysis: Big-O, $\Omega$, and $\Theta$

```{=typst}
#heavy[
```

Dense — slow down: Complexity analysis shifts our focus from how a program runs today on a specific machine, to how its resource demands mathematically scale as the input grows toward infinity.

```{=typst}
]
```

**(A) Analogy**: Imagine searching for a specific page in a book. Opening to the exact page directly takes constant effort—you simply turn there. Reading every page from start to finish takes effort proportional to the book's length. If, for every single word in the book, you had to read the entire book again to count its occurrences, the effort would compound dramatically.

**(D)** 

![Growth curves of common time complexities](assets/s13_bigo.png)

**(E) Example First**:

```c
// O(n) Time Complexity, O(1) Space Complexity
int sum_array(const int arr[], int n) {
    int total = 0; 
    for (int i = 0; i < n; i++) {
        total += arr[i]; 
    }
    return total;
}
```

**(P) Plain-English**: We evaluate algorithms by tracking the maximum number of fundamental operations (such as additions or memory reads) they perform relative to the size of the input, denoted as $n$. As $n$ becomes massive, the largest scaling term dominates the time taken. If an algorithm takes $3n^{2} + 5n + 10$ steps, the $n^{2}$ portion overwhelms everything else, so we drop the constants and smaller terms, calling it roughly proportional to $n^{2}$. We evaluate both Time (how many CPU cycles) and Space (how much extra memory must be allocated).

**(T) Technical Statement**: 
- **Big-O ($O$)**: The asymptotic upper bound (worst-case). The resource function $f(n) \le c \cdot g(n)$ for some constant $c$ as $n \to \infty$.
- **Big-Omega ($\Omega$)**: The asymptotic lower bound (best-case).
- **Big-Theta ($\Theta$)**: The tight bound, meaning the algorithm grows exactly at that rate from both above and below.

*Why here*: We introduce complexity now because you cannot evaluate searching and sorting choices without a standardized vocabulary for their efficiency. 

*Alternative rejected*: We reject timing the code with a stopwatch because elapsed execution time depends on the specific CPU, system load, and compiler optimizations, not the mathematical limits of the underlying algorithm.

```{=typst}
#trap[
```

A common trap is assuming two nested loops always yield an $O(n^{2})$ time complexity. If the outer loop runs $n$ times, but the inner loop halves its workload on each step, the total complexity might be $O(n \log n)$. Always count the exact number of iterations.

```{=typst}
]
```

*Question to sit with*: If an $O(n)$ algorithm takes 1 second to process 10,000 items, how long will it roughly take for 20,000 items? What if it were an $O(n^{2})$ algorithm?

*Boundary*: This model breaks when $n$ is very small; an $O(n^{2})$ algorithm might outperform an $O(n \log n)$ algorithm on tiny arrays due to having lower constant overhead.

## Searching Arrays

Searching is the process of locating a specific target value within a collection.

**Linear Search**
Linear search inspects every element sequentially from the first to the last. It is $O(n)$ in time and $O(1)$ in space. It matters because it is the only viable option for completely unsorted, unstructured data.

**Binary Search**
If the array is already sorted, we can use binary search. We check the middle element; if our target is smaller, we restrict our search to the left half, and if larger, the right half. This halves the search space at each step, yielding an $O(\log n)$ time complexity. 

![Binary search narrowing lo/mid/hi on a sorted array](assets/s13_binsearch.png)

```{=typst}
#trap[
```

When calculating the middle index, beginners intuitively write `mid = (lo + hi) / 2`. If `lo` and `hi` are large, their sum can exceed the maximum value an `int` can hold, causing signed integer overflow (which is undefined behavior). The correct, overflow-safe formulation is `mid = lo + (hi - lo) / 2`.

```{=typst}
]
```

This algorithm breaks when the data is not strictly sorted or if it contains multiple identical values and we need a specific one (like the very first occurrence) without modifying the boundary checks.

## Sorting Arrays

Sorting organizes data into a sequential order, enabling faster retrieval techniques like binary search.

**Quadratic Sorts ($O(n^{2})$)**
Bubble sort, insertion sort, and selection sort are $O(n^{2})$ algorithms. They are generally too slow for large datasets. However, insertion sort is highly efficient for very small arrays or arrays that are already nearly sorted.

**Divide-and-Conquer Sorts ($O(n \log n)$)**
Merge sort and quicksort divide the array into smaller chunks, sort those chunks recursively, and combine them. 

![Divide-and-conquer split/merge tree](assets/s13_mergesort.png)

- **Merge Sort**: Recursively halves the array until the sizes are 1, then merges the sorted halves. It guarantees $O(n \log n)$ time but requires $O(n)$ auxiliary space to hold the merged elements. It is a *stable* sort (identical elements retain their original relative order).
- **Quicksort**: Chooses a "pivot" element and partitions the array so all smaller elements are to the left and larger elements are to the right. It is typically performed in-place ($O(\log n)$ space for the recursion stack) and is exceptionally fast in practice. 

```{=typst}
#interview[
```

**Q: What is the worst-case time complexity of Quicksort, and why does it happen?**
A: $O(n^{2})$. This worst case occurs when the chosen pivot is consistently the smallest or largest element at every step (for example, picking the first element in an array that is already sorted). We mitigate this risk by choosing a random pivot or taking the median of three elements.

```{=typst}
]
```

In practical C programming, you rarely write these algorithms from scratch unless constrained; you use the standard library `qsort` (which we will revisit in §14).

These algorithms break when sorting data that does not fit entirely in main memory, requiring specialized external sorting techniques.

## Recursion and Divide-and-Conquer

Divide-and-conquer (recap §3) solves a problem by breaking it down into smaller sub-problems of the exact same type. Mathematically, this is expressed as a *recurrence relation*, such as $T(n) = 2T(n/2) + O(n)$ for merge sort. 
Recursion provides an elegant way to implement this technique, but it trades off memory for simplicity. Every recursive call consumes stack space. If the recursion goes too deep, it will exceed the operating system's stack depth limits, resulting in a stack overflow crash. Iterative solutions are safer for massive inputs, but are often significantly harder to read.

## Array Manipulation Patterns

Many algorithmic challenges rely on specific index manipulation patterns:
- **Two-Pointer**: Using one index starting at `0` and another starting at `n - 1`, moving them toward the center. This is used to reverse an array in-place or check for palindromes.
- **Sliding-Window**: Maintaining a "window" (a sub-array) defined by a `start` and `end` index that expands and shrinks as it moves across the array. Useful for finding the longest or shortest contiguous sequence satisfying a specific condition.
- **In-Place Partitioning**: Swapping elements within the same array to group them (e.g., all negative numbers to the left, positive to the right) without allocating $O(n)$ extra space.

## The Standard Library: `qsort` and `bsearch`

The `<stdlib.h>` header provides generic sorting and searching via `qsort` and `bsearch` [1]. Because C lacks generics or templates, these functions operate on opaque `void *` pointers. This requires you to provide the size of the elements and a function pointer to a custom comparator (recap §4) [2][3]. 

The comparator function must return a negative integer if the first argument is less than the second, zero if they are equal, and a positive integer if the first is greater. 

```{=typst}
#trap[
```

A classic bug is writing a comparator for integers by simply returning `*(int*)a - *(int*)b`. If `a` is a large positive number and `b` is a large negative number, the subtraction will overflow the 32-bit integer, resulting in a completely wrong sign and a broken sort. Always use explicit `if`/`else` comparisons.

```{=typst}
]
```

## Bit-Manipulation Algorithms

Bitwise operations (recap §11) often yield $O(1)$ time and space solutions for highly specific numerical problems.
- **Power of Two**: Evaluating `(x & (x - 1)) == 0` checks if an integer `x` is a power of two (assuming `x > 0`).
- **Popcount**: Counting the number of set bits (1s) can be done by repeatedly applying `x &= (x - 1)` until `x` becomes 0.
- **XOR Find-Unique**: `x ^ x` evaluates to `0`. XORing all elements in an array where every number appears exactly twice except for one will leave you with the unique number.

## Problem-Solving for Interviews

When facing an algorithmic interview question, structure your approach methodically:
1. **Clarify**: Ask about bounds, types (signed versus unsigned), and edge cases (such as empty arrays).
2. **Brute Force**: Verbally state the naive $O(n^{2})$ or exponential solution first to establish a baseline.
3. **Optimize**: Look for repeated work. Can a hash map reduce the lookup time? Does sorting the array first help? 
4. **Test Edges**: Trace your code manually with an array of size 0, 1, and 2 before declaring that you are done.

---

## WORKED-EXAMPLE ZONE

**Worked: Binary Search (Overflow-Safe)**
Here is a complete, exact C implementation of binary search. Notice how `mid` is calculated carefully to avoid integer overflow.

```c
#include <stdio.h>

// Returns the index of 'target' if found, otherwise -1.
int binary_search(const int arr[], int n, int target) {
    int lo = 0;
    int hi = n - 1;

    while (lo <= hi) {
        // Safe from signed integer overflow
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}
```
*Trace*: For `arr = [2, 5, 8, 12, 16]`, `target = 12`.
1. `lo = 0`, `hi = 4`. `mid = 0 + (4 - 0) / 2 = 2`. The element `arr[2]` is 8. Since $8 < 12$, we update `lo = 3`.
2. `lo = 3`, `hi = 4`. `mid = 3 + (4 - 3) / 2 = 3`. The element `arr[3]` is 12. Since $12 == 12$, we return `3`.

**Worked: Merge Sort (The Merge Step)**
The core logic of merge sort is the step that combines two already-sorted halves back into a single sorted sequence.

```c
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;      // Iterator for the left half
    int j = mid + 1;   // Iterator for the right half
    int k = left;      // Iterator for the temporary array

    // Compare and copy the smaller element
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy any remaining elements from the left half
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy any remaining elements from the right half
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy the merged elements back to the original array
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}
```

**Worked: Using `qsort`**
An exact, safe comparator and a call to the standard library `qsort` function.

```c
#include <stdlib.h>
#include <stdio.h>

// Safe integer comparator
int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int main(void) {
    int data[] = {42, -5, 100, 0, 7};
    size_t n = sizeof(data) / sizeof(data[0]);

    qsort(data, n, sizeof(int), compare_ints);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", data[i]); // Prints: -5 0 7 42 100
    }
    printf("\n");
    return 0;
}
```

**Faded Example: Insertion Sort**
Complete the inner loop of insertion sort. The shift mechanism is written, but the `while` loop condition is missing. You must check that `j` is within bounds AND the previous element is larger than the `key`.

```c
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // FILL IN THE CONDITION:
        // while (___ >= 0 && arr[___] > ___) {
            arr[j + 1] = arr[j];
            j = j - 1;
        // }
        arr[j + 1] = key;
    }
}
```

---

### References
[1] ISO/IEC 9899:2011 (C11) — WG14 / open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[2] qsort(3) - Linux manual page — man7.org — https://man7.org/linux/man-pages/man3/qsort.3.html
[3] bsearch(3) - Linux manual page — man7.org — https://man7.org/linux/man-pages/man3/bsearch.3.html
