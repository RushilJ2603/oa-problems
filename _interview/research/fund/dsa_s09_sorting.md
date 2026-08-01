# Sorting Algorithms

Sorting is the process of arranging a collection of items in a specific order (typically ascending or descending). It is a foundational operation that enables faster searching (like binary search) and simplifies many algorithmic problems. A sorting algorithm is **in-place** if it requires $O(1)$ auxiliary space. A **comparison sort** orders elements by examining pairs of elements; such sorts have a theoretical lower bound of $\Omega(n \log n)$ time in the worst case. **Non-comparison sorts** can bypass this bound by exploiting the structure of the data (like integers in a small range).

::: definition
A sorting algorithm is **stable** if it preserves the relative order of equal elements. If two items have the same value, the one that appeared first in the original array will appear first in the sorted array.
:::

In practice, C++ provides `std::sort` (typically Introsort, not stable) and `std::stable_sort` (typically Merge Sort) in `<algorithm>`. This section explores the mechanics of the classical sorts that power these standard library functions.

## Sorting-I

### Selection Sort
Selection Sort divides the array into a sorted left portion and an unsorted right portion. Initially, the sorted portion is empty. In each step, it scans the unsorted portion to find the minimum element and swaps it with the first element of the unsorted portion, thereby growing the sorted portion by one.

**Intuition / approach:**
1. Find the minimum element in the array from index `0` to `n-1`, and swap it with the element at index `0`.
2. Find the minimum element from index `1` to `n-1`, and swap it with the element at index `1`.
3. Repeat this process until the array is fully sorted.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}
```

**Complexity:**
- **Time:** $O(n^{2})$ in all cases (best, average, worst). It always scans the remaining unsorted portion.
- **Space:** $O(1)$ auxiliary space (in-place).
- **Stability:** Not stable. The long-distance swap can jump over and reorder equal elements.

**Practice:** https://leetcode.com/problems/sort-an-array/

### Bubble Sort
Bubble Sort repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. The pass through the list is repeated until the list is sorted. With each pass, the largest remaining element "bubbles up" to its correct position at the end of the array.

**Intuition / approach:**
1. Compare adjacent elements. If the left element is greater than the right, swap them.
2. After the first full pass, the largest element is at the very end.
3. Repeat the process for the remaining `n-1` elements, then `n-2`, and so on.
4. **Optimization:** If a full pass makes zero swaps, the array is already sorted, and we can exit early.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        // The last i elements are already in place
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break; // Early exit if no swaps occurred
        }
    }
}
```

**Complexity:**
- **Time:** $O(n^{2})$ worst and average case. $O(n)$ best case (when the array is already sorted, due to the early-exit optimization).
- **Space:** $O(1)$ auxiliary space (in-place).
- **Stability:** Stable. Adjacent equal elements are never swapped.

**Practice:** https://leetcode.com/problems/sort-an-array/

### Insertion Sort
Insertion Sort builds the final sorted array one item at a time. It iterates through the input elements, taking one element per iteration, and finds the location it belongs within the previously sorted left portion, inserting it there.

**Intuition / approach:**
1. Assume the first element is already sorted.
2. Take the next element and store it in a temporary variable.
3. Shift all elements in the sorted portion that are greater than the temporary variable one position to the right.
4. Insert the temporary variable into the newly opened slot.
5. Repeat for all elements.

```cpp
#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        
        // Shift elements of arr[0..i-1] that are greater than key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```

**Complexity:**
- **Time:** $O(n^{2})$ worst and average case. $O(n)$ best case (when the array is already nearly sorted, the inner `while` loop terminates immediately).
- **Space:** $O(1)$ auxiliary space (in-place).
- **Stability:** Stable. Equal elements are not shifted past each other.

**Practice:** https://leetcode.com/problems/sort-an-array/

## Sorting-II

### Merge Sort
Merge Sort is a quintessential divide-and-conquer algorithm. It recursively splits the array in half until each subarray contains a single element (which is trivially sorted), and then cleanly merges the sorted subarrays back together.

**Intuition / approach:**
1. **Divide:** Recursively halve the array until the base case (size 1) is reached.
2. **Conquer:** A single-element array is sorted.
3. **Combine:** Merge two sorted halves into a single sorted whole by continuously picking the smaller of the two elements from the front of the halves.

```cpp
#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    // Merge the two halves into temp
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // Copy any remaining elements from the left half
    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    // Copy any remaining elements from the right half
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // Transfer from temp back to the original array
    for (int i = low; i <= high; ++i) {
        arr[i] = temp[i - low];
    }
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}
```

::: keypoint
Merge Sort's time complexity is derived from the recurrence relation $T(n) = 2T(n/2) + O(n)$. By the Master Theorem (covered in Complexity), this tightly resolves to $O(n \log n)$ time.
:::

**Complexity:**
- **Time:** $O(n \log n)$ in all cases (best, average, worst). The array is always split evenly, and merging takes linear time.
- **Space:** $O(n)$ auxiliary space to hold the `temp` array during the merge step.
- **Stability:** Stable. The `<=` check ensures elements from the left half are prioritized over equal elements in the right half.

**Practice:** https://leetcode.com/problems/sort-an-array/

### Recursive Bubble Sort
Bubble Sort can be framed recursively. Instead of using an outer loop to track the shrinking size of the array, a recursive function represents the state of placing the largest remaining element at the current end.

**Intuition / approach:**
A recursive call with parameter `n` pushes the largest element to the `n-1` index. The next recursive call handles `n-1`, acting exactly like the outer loop of iterative bubble sort.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void recursiveBubbleSort(vector<int>& arr, int n) {
    // Base case: array of size 1 is sorted
    if (n <= 1) return;

    bool swapped = false;
    // One pass of bubble sort. After this, the largest element is at the end.
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
            swapped = true;
        }
    }

    // Early exit: if no swaps, array is completely sorted
    if (!swapped) return;

    // Largest element is fixed, recurse for the remaining array
    recursiveBubbleSort(arr, n - 1);
}
```

**Complexity:**
- **Time:** $O(n^{2})$ worst and average case, $O(n)$ best case with the early exit.
- **Space:** $O(n)$ auxiliary space due to the call stack depth.
- **Stability:** Stable.

**Practice:** https://leetcode.com/problems/sort-an-array/

### Recursive Insertion Sort
Similarly, Insertion Sort can be modeled recursively. The recursive call sorts the first `n-1` elements, and then the current call inserts the `n`-th element into that already-sorted prefix.

**Intuition / approach:**
Sort the prefix of size `n-1` recursively. Once that returns, the prefix is sorted, so we just perform the standard insertion loop for the element at index `n-1`.

```cpp
#include <iostream>
#include <vector>

using namespace std;

void recursiveInsertionSort(vector<int>& arr, int n) {
    // Base case: an array of size 1 or less is already sorted
    if (n <= 1) return;

    // Sort the first n-1 elements recursively
    recursiveInsertionSort(arr, n - 1);

    // Insert the nth element into its correct position
    int last = arr[n - 1];
    int j = n - 2;

    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = last;
}
```

**Complexity:**
- **Time:** $O(n^{2})$ worst and average case, $O(n)$ best case.
- **Space:** $O(n)$ auxiliary space due to the call stack.
- **Stability:** Stable.

**Practice:** https://leetcode.com/problems/sort-an-array/

### Quick Sort
Quick Sort is a divide-and-conquer algorithm that selects a "pivot" element and partitions the array such that all elements strictly smaller than the pivot appear before it, and all elements greater than or equal to the pivot appear after it. It then recursively sorts the subarrays.

![Quick sort: the pivot partitions the array into a smaller-than half and a greater-than half.](../assets/ss_292.png)

**Intuition / approach:**
1. Choose a pivot (here, we pick the first element, using a standard two-pointer partition approach).
2. Maintain two pointers, scanning from left to right and right to left, swapping out-of-place elements until the pointers cross.
3. Place the pivot in its final correct resting place.
4. Recursively call Quick Sort on the left and right partitions.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        // Find the first element greater than the pivot
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
        }
        // Find the first element smaller than or equal to the pivot
        while (arr[j] > pivot && j >= low + 1) {
            j--;
        }
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }
    // Place the pivot in its correct position
    swap(arr[low], arr[j]);
    return j;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pIndex = partition(arr, low, high);
        quickSort(arr, low, pIndex - 1);
        quickSort(arr, pIndex + 1, high);
    }
}
```

::: trap
If you always pick the first element as the pivot, an **already sorted** (or reverse sorted) array degenerates Quick Sort into $O(n^{2})$ time because the partitions will be extremely unbalanced (size 0 and size $n-1$). To avoid this TLE in practice, choose a randomized pivot or a median-of-three pivot.
:::

**Complexity:**
- **Time:** $O(n \log n)$ average case. $O(n^{2})$ worst case (unbalanced partitions).
- **Space:** $O(\log n)$ auxiliary space on average for the recursion stack, up to $O(n)$ in the worst case. In-place for the array itself.
- **Stability:** Not stable. The partitioning swaps can disrupt the relative order of equal elements.

**Practice:** https://leetcode.com/problems/sort-an-array/

## Non-Comparison Sorts & QuickSelect

::: heavy
Comparison sorts hit a hard mathematical floor of $\Omega(n \log n)$ operations. However, if we know properties about the data (e.g., they are integers within a strict, small range), we can sort them in linear time without ever explicitly comparing two elements against each other.
:::

### Counting Sort
Counting Sort counts the frequencies of each distinct element. It operates by creating an auxiliary array of size $k$ (where $k$ is the maximum value in the input range).

**Intuition / approach:**
1. Find the maximum element to determine the count array size.
2. Count the occurrences of each element.
3. Compute the prefix sums of the count array. This reveals the exact starting index for each element in the final sorted array.
4. Iterate backward over the original array (to maintain stability) and place elements directly into their calculated positions.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    vector<int> output(arr.size());

    // Step 1: Count frequencies
    for (int num : arr) {
        count[num]++;
    }

    // Step 2: Compute prefix sums
    for (int i = 1; i <= maxVal; ++i) {
        count[i] += count[i - 1];
    }

    // Step 3: Build the output array (backward for stability)
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Step 4: Copy back
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = output[i];
    }
}
```

**Complexity:**
- **Time:** $O(n + k)$ where $k$ is the maximum value in the array. This comfortably beats $O(n \log n)$ when $k \approx n$.
- **Space:** $O(n + k)$ for the output and count arrays.
- **Stability:** Stable (because we iterate backward during placement).

### Radix Sort
Radix Sort extends the idea of Counting Sort to handle larger numbers. Instead of counting entire numbers, it sorts them digit by digit, from Least Significant Digit (LSD) to Most Significant Digit (MSD), using Counting Sort as a stable subroutine.

**Intuition / approach:**
Extract the ones digit for all numbers and sort the array by that digit. Then extract the tens digit and sort stably again. Repeat until the maximum number of digits is exhausted. Because the intermediate sorts are stable, the order established by lower-value digits is preserved during ties at higher-value digits.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countingSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    // Count occurrences of the current digit
    for (int i = 0; i < n; ++i) {
        count[(arr[i] / exp) % 10]++;
    }

    // Prefix sums
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    // Build output stably
    for (int i = n - 1; i >= 0; --i) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = *max_element(arr.begin(), arr.end());

    // Do counting sort for every digit.
    // exp is 10^{i} where i is current digit number
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp);
    }
}
```

**Complexity:**
- **Time:** $O(d \cdot (n + b))$ where $d$ is the number of digits in the maximum element and $b$ is the base (10 for decimal).
- **Space:** $O(n + b)$ for the Counting Sort subroutine.
- **Stability:** Stable.

### QuickSelect
QuickSelect is an algorithm to find the $k$-th smallest (or largest) element in an unordered array. It uses the exact same partitioning logic as Quick Sort, but only recurses into the side of the partition that contains the $k$-th element.

::: keypoint
If you only need the $k$-th element, you do not need to fully sort the array. QuickSelect finds it in expected linear time by discarding the irrelevant half of the array at each step.
:::

**Intuition / approach:**
After a partition operation, the pivot is in its absolute final sorted position `pIndex`. If `pIndex == k`, we found the target. If `k < pIndex`, the $k$-th element must be in the left partition. If `k > pIndex`, it must be in the right partition.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Using Lomuto partition for simplicity here
int partitionLomuto(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

int quickSelect(vector<int>& arr, int low, int high, int k) {
    if (low == high) return arr[low];
    
    int pIndex = partitionLomuto(arr, low, high);
    
    // k is passed as 0-indexed
    if (k == pIndex) {
        return arr[pIndex];
    } else if (k < pIndex) {
        return quickSelect(arr, low, pIndex - 1, k);
    } else {
        return quickSelect(arr, pIndex + 1, high, k);
    }
}
```

**Complexity:**
- **Time:** $O(n)$ expected average time. The search space roughly halves each time: $n + n/2 + n/4 \dots = 2n$. Worst case is $O(n^{2})$ if bad pivots are chosen. (In C++, `std::nth_element` implements this pattern).
- **Space:** $O(1)$ auxiliary space if done iteratively, $O(\log n)$ average call stack if recursive.

## Interview Angles

::: interview
What interviewers probe here:
- **Stability understanding:** Can you name a stable sort and explain why stability matters? (e.g., sorting by primary key then secondary key).
- **STL internals:** Knowing that `std::sort` is Introsort (Quick Sort with a fallback to Heap Sort to prevent $O(n^{2})$ TLE) and `std::stable_sort` is Merge Sort.
- **When to dodge comparison sorts:** If an interviewer specifies "array elements are bounded between 1 and 1000" or "sort by age", they are practically begging you to use Counting Sort.
- **Top K / K-th element:** Using QuickSelect (or `std::nth_element`) to get expected $O(n)$ time instead of a priority queue $O(n \log k)$ or a full sort $O(n \log n)$.
- **External sorting:** If data is too large to fit in RAM, how do you sort? (Answer: External Merge Sort — chunk into RAM, sort, write to disk, then merge chunks).
:::
