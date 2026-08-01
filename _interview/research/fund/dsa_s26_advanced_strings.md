# Advanced String Algorithms

::: keypoint
Naive substring search takes $O(n \cdot m)$ time, where $n$ is the length of the text and $m$ is the length of the pattern. The algorithms in this section achieve $O(n + m)$ linear time by avoiding re-examining characters, using precomputed information (like a prefix/failure array) or a rolling hash.
:::

## KMP — Knuth–Morris–Pratt Pattern Matching

::: heavy
The Knuth-Morris-Pratt (KMP) algorithm efficiently searches for a pattern in a text by preprocessing the pattern. The core of KMP is the **prefix function** or **failure function**, commonly represented as an array named `lps` (Longest Proper Prefix that is also a Suffix). It tells the algorithm how far to backtrack when a mismatch occurs, preventing the need to start over from the beginning of the pattern.
:::

A **proper prefix** of a string is a prefix that is not the entire string itself. The `lps[i]` value is the length of the longest proper prefix of `pattern[0...i]` that exactly matches a suffix of `pattern[0...i]`.

Let's compute the `lps` array for the pattern `pattern = "ABABACA"` character by character. We use two pointers: `i` for the current character we are processing (starting at 1), and `len` for the length of the previous longest prefix suffix (starting at 0). `lps[0]` is always 0.

1. **`i = 1`, `pattern[1] = 'B'`, `len = 0`**: `pattern[len]` which is `'A'` does not match `'B'`. So `lps[1] = 0`.
2. **`i = 2`, `pattern[2] = 'A'`, `len = 0`**: `pattern[len]` (`'A'`) matches `pattern[2]`. We increment `len` to 1. `lps[2] = 1`. (Prefix "A" matches suffix "A" in "ABA").
3. **`i = 3`, `pattern[3] = 'B'`, `len = 1`**: `pattern[len]` (`'B'`) matches `pattern[3]`. We increment `len` to 2. `lps[3] = 2`. (Prefix "AB" matches suffix "AB" in "ABAB").
4. **`i = 4`, `pattern[4] = 'A'`, `len = 2`**: `pattern[len]` (`'A'`) matches `pattern[4]`. We increment `len` to 3. `lps[4] = 3`. (Prefix "ABA" matches suffix "ABA" in "ABABA").
5. **`i = 5`, `pattern[5] = 'C'`, `len = 3`**: `pattern[len]` (`'B'`) does NOT match `'C'`. This is the crucial part. Instead of resetting `len` to 0, we fall back to the longest prefix suffix of the prefix we were just matching: `len = lps[len - 1] = lps[2] = 1`. We then compare `pattern[len]` (`pattern[1] = 'B'`) with `'C'`. Still a mismatch. We fall back again: `len = lps[1 - 1] = lps[0] = 0`. Now `pattern[0]` (`'A'`) vs `'C'`. Mismatch. We can't fall back further, so `lps[5] = 0`.
6. **`i = 6`, `pattern[6] = 'A'`, `len = 0`**: `pattern[len]` (`'A'`) matches `pattern[6]`. We increment `len` to 1. `lps[6] = 1`.

The final `lps` array is `[0, 0, 1, 2, 3, 0, 1]`.

### Implement strStr() / Find the First Occurrence of a Pattern

Given two strings `needle` (the pattern) and `haystack` (the text), return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.

**Intuition:**
A naive approach would check for the pattern starting at every index in the text ($O(n \cdot m)$). Using the KMP algorithm and the `lps` array we just constructed, we can scan the `haystack` in one pass. When characters match, we move both our text pointer `i` and pattern pointer `j` forward. If there is a mismatch, the `lps` array tells us exactly where to reposition `j` (the pattern pointer) without backtracking `i` (the text pointer).

::: keypoint
KMP uses the `lps` array to avoid re-evaluating the text. On a mismatch after matching some characters, we know the text matched a prefix of the pattern. The `lps` array gives us the longest proper prefix of that matched portion that is also a suffix, allowing us to align the pattern optimally.
:::

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    vector<int> computeLPS(const string& pattern) {
        int m = pattern.length();
        vector<int> lps(m, 0);
        int len = 0; 
        int i = 1;
        
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1]; // Fall back
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        
        int n = haystack.length();
        int m = needle.length();
        vector<int> lps = computeLPS(needle);
        
        int i = 0; // index for haystack
        int j = 0; // index for needle
        
        while (i < n) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }
            if (j == m) {
                return i - j; // Match found
            } else if (i < n && haystack[i] != needle[j]) {
                if (j != 0) {
                    j = lps[j - 1]; // Mismatch, use LPS to shift pattern
                } else {
                    i++;
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    string haystack = "sadbutsad";
    string needle = "sad";
    cout << "Index of first occurrence: " << sol.strStr(haystack, needle) << endl;
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n + m)$ where $n$ and $m$ are the lengths of `haystack` and `needle`. The `lps` array takes $O(m)$ to compute. The matching phase takes $O(n)$ as `i` never decrements.
- **Space Complexity:** $O(m)$ to store the `lps` array.

**Practice:** https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/

### Longest Happy Prefix

Given a string `s`, return the longest prefix of `s` that is also a suffix (excluding the string itself).

**Intuition:**
This is exactly the definition of the KMP algorithm's `lps` array! The `lps` array at the last index (`lps[n-1]`) stores the length of the longest proper prefix that is also a suffix for the entire string. We compute the `lps` array and use the final value to extract the prefix.

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string longestPrefix(string s) {
        int n = s.length();
        if (n == 0) return "";
        
        vector<int> lps(n, 0);
        int len = 0;
        int i = 1;
        
        while (i < n) {
            if (s[i] == s[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        
        int longest_len = lps[n - 1];
        return s.substr(0, longest_len);
    }
};

int main() {
    Solution sol;
    cout << "Longest happy prefix: " << sol.longestPrefix("level") << endl;
    cout << "Longest happy prefix: " << sol.longestPrefix("ababab") << endl;
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n)$ where $n$ is the length of `s`, as we are just computing the `lps` array.
- **Space Complexity:** $O(n)$ to store the `lps` array.

**Practice:** https://leetcode.com/problems/longest-happy-prefix/

### Shortest Palindrome

Given a string `s`, find the shortest palindrome you can find by adding characters in front of it. (Alternatively, what is the shortest string to append to the end to make it a palindrome? The logic is symmetrical).

**Intuition:**
We need to find the longest palindromic prefix of `s`. Once we find it, the remaining suffix characters just need to be reversed and appended to the front. 
We can find the longest palindromic prefix efficiently by creating a new string `combined = s + "#" + reverse(s)`. If we compute the `lps` array for `combined`, the last element `lps.back()` will be the length of the longest proper prefix of `combined` that is also a suffix of `combined`. Because the suffix of `combined` is the reversed `s`, this length is exactly the length of the longest palindromic prefix of the original string `s`. The `#` separator prevents the prefix from overlapping with the suffix beyond the original string's length.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        
        string combined = s + "#" + rev_s;
        int n = combined.length();
        
        vector<int> lps(n, 0);
        int len = 0;
        int i = 1;
        
        while (i < n) {
            if (combined[i] == combined[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        
        int longest_palindromic_prefix_len = lps.back();
        string to_add = s.substr(longest_palindromic_prefix_len);
        reverse(to_add.begin(), to_add.end());
        
        return to_add + s;
    }
};

int main() {
    Solution sol;
    cout << "Shortest palindrome: " << sol.shortestPalindrome("aacecaaa") << endl;
    cout << "Shortest palindrome: " << sol.shortestPalindrome("abcd") << endl;
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n)$ where $n$ is the length of the string. `combined` length is $2n+1$, and calculating `lps` is linear.
- **Space Complexity:** $O(n)$ to store the `combined` string and `lps` array.

**Practice:** https://leetcode.com/problems/shortest-palindrome/

## Z-Algorithm

The Z-algorithm builds an array, `Z`, where `Z[i]` stores the length of the longest substring starting at `s[i]` which is also a prefix of `s`. This array is extremely useful for string matching.

We compute the Z-array efficiently by maintaining a window `[l, r]` that records the rightmost matching prefix found so far.
- If we are processing index `i` and `i > r`, we have no prior information. We compute `Z[i]` naively by comparing characters and update `[l, r]`.
- If `i <= r`, then `s[i]` is inside the current window. This means `s[i]` matches `s[i - l]`. Thus, we can copy the previously computed `Z[i - l]`. However, we cannot guarantee a match beyond `r`. So we initialize `Z[i] = min(Z[i - l], r - i + 1)`, and then attempt to match further characters outside the `r` bound naively. If we match beyond `r`, we update our `[l, r]` window.

### Pattern Matching with the Z-function

Find all occurrences of a `pattern` in a `text`.

**Intuition:**
We concatenate the pattern and the text with a separator character that doesn't appear in either string (e.g., `$`). Let this string be `combined = pattern + "$" + text`. We compute the Z-array for `combined`. If `Z[i]` is equal to the length of the pattern, it means a substring starting at index `i` matches the pattern prefix.

::: keypoint
By searching for a pattern by prepending it to the text with a unique delimiter, the Z-algorithm reduces substring search to computing a single property (the Z-array) on one string.
:::

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    vector<int> computeZ(const string& s) {
        int n = s.length();
        vector<int> Z(n, 0);
        int l = 0, r = 0;
        
        for (int i = 1; i < n; i++) {
            if (i <= r) {
                Z[i] = min(Z[i - l], r - i + 1);
            }
            while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
                Z[i]++;
            }
            if (i + Z[i] - 1 > r) {
                l = i;
                r = i + Z[i] - 1;
            }
        }
        return Z;
    }

public:
    vector<int> search(string text, string pattern) {
        string combined = pattern + "$" + text;
        vector<int> Z = computeZ(combined);
        vector<int> result;
        
        int m = pattern.length();
        for (int i = m + 1; i < Z.size(); i++) {
            if (Z[i] == m) {
                result.push_back(i - (m + 1)); // adjust index relative to text
            }
        }
        return result;
    }
};

int main() {
    Solution sol;
    string text = "ababcababaad";
    string pattern = "ababa";
    vector<int> matches = sol.search(text, pattern);
    
    cout << "Pattern found at indices: ";
    for (int idx : matches) cout << idx << " ";
    cout << endl;
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n + m)$ where $n$ is the length of `text` and $m$ is the length of `pattern`. The Z-array is computed in linear time.
- **Space Complexity:** $O(n + m)$ to store the combined string and the Z-array.

**Practice:** https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/

## Rabin–Karp / String Hashing

Rabin-Karp is a string-searching algorithm that uses hashing. It computes a numerical hash value for the pattern and for each window of length $m$ (the pattern's length) in the text. If the hash values match, it performs a naive string comparison to confirm the match, resolving **spurious collisions** (where different strings map to the same hash).

We use a **polynomial rolling hash**. For a string $S$, the hash is calculated as:
$H = S_0 \cdot B^{m-1} + S_1 \cdot B^{m-2} + \dots + S_{m-1} \cdot B^0 \pmod M$
where $B$ is a base (typically an odd prime like 31, 257) and $M$ is a large modulus (like $10^9 + 7$).

The power of the rolling hash is that we can compute the hash of the next window from the current window in $O(1)$ time. When sliding the window to the right:
1. Remove the contribution of the leftmost character.
2. Multiply the remaining hash by $B$ (shifting characters up).
3. Add the contribution of the new rightmost character.
4. Apply modulo arithmetic at every step.

Let's compute rolling hashes for `text = "ABAC"`, pattern length $m = 2$, base $B = 10$, mod $M = 97$. Let characters map to their ASCII values minus 'A' + 1 (A=1, B=2, C=3).
- **Window 1 ("AB")**: $H_1 = (1 \cdot 10^1 + 2 \cdot 10^0) \pmod{97} = 12 \pmod{97} = 12$.
- **Window 2 ("BA")**: We remove 'A' (value 1), shift, add 'A' (value 1).
  $H_2 = ((H_1 - 1 \cdot 10^1) \cdot 10 + 1) \pmod{97} = ((12 - 10) \cdot 10 + 1) \pmod{97} = 21$. (Note: "BA" is $2 \cdot 10 + 1 = 21$. Matches!)
- **Window 3 ("AC")**: We remove 'B' (value 2), shift, add 'C' (value 3).
  $H_3 = ((H_2 - 2 \cdot 10^1) \cdot 10 + 3) \pmod{97} = ((21 - 20) \cdot 10 + 3) \pmod{97} = 13$.

::: trap
Hash collisions happen! If two different substrings have the same hash value, we must check character by character. To minimise collisions, use a large prime $M$. In highly adversarial tests (like LeetCode), use **double hashing**: compute two hashes with different moduli for each string. A collision in both is practically impossible.
:::

### Rabin-Karp Substring Search

Find the index of the first occurrence of a pattern in a text using string hashing.

**Intuition:**
Compute the hash for the pattern and the first window of the text. Then continuously roll the text hash window by one character and compare it against the pattern's hash.

::: keypoint
Rabin-Karp is rarely faster than KMP for single pattern matching, but its rolling hash technique is incredibly powerful for multi-pattern search, finding duplicate substrings, and matching multidimensional patterns.
:::

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.length();
        int m = needle.length();
        if (m == 0) return 0;
        if (n < m) return -1;
        
        long long B = 257;
        long long MOD = 1e9 + 7;
        
        long long p_hash = 0;
        long long t_hash = 0;
        long long h = 1;
        
        // Calculate B^(m-1) % MOD
        for (int i = 0; i < m - 1; i++) {
            h = (h * B) % MOD;
        }
        
        // Initial hashes for pattern and first window of text
        for (int i = 0; i < m; i++) {
            p_hash = (B * p_hash + needle[i]) % MOD;
            t_hash = (B * t_hash + haystack[i]) % MOD;
        }
        
        for (int i = 0; i <= n - m; i++) {
            // If hashes match, verify character by character to handle collisions
            if (p_hash == t_hash) {
                bool match = true;
                for (int j = 0; j < m; j++) {
                    if (haystack[i + j] != needle[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) return i;
            }
            
            // Roll the hash to the next window
            if (i < n - m) {
                t_hash = (B * (t_hash - haystack[i] * h) + haystack[i + m]) % MOD;
                // We might get negative values after modulo, convert to positive
                if (t_hash < 0) {
                    t_hash += MOD;
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    cout << "Index: " << sol.strStr("hello", "ll") << endl;
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n + m)$ average case, but $O(n \cdot m)$ worst case if there are many spurious collisions (e.g., searching "AAA" in "AAAAA" where every window matches the hash).
- **Space Complexity:** $O(1)$.

**Practice:** https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/

### Longest Duplicate Substring

Given a string `s`, consider all duplicated substrings: (contiguous) substrings of `s` that occur 2 or more times. Return any one of the longest duplicated substrings.

**Intuition:**
We can use binary search on the length of the duplicated substring. The minimum length is 1, and the maximum length is `n - 1`. For a given length `L`, we use a rolling hash to track the hashes of all substrings of length `L`. If we see a hash we've seen before, we verify it. If it matches, we try a longer length; otherwise, we try a shorter length.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
    long long B = 257;
    long long MOD = 1e9 + 7;

    // Checks if there is a duplicate substring of length L
    int search(const string& s, int L) {
        unordered_map<long long, vector<int>> seen;
        long long h = 1;
        for (int i = 0; i < L - 1; i++) {
            h = (h * B) % MOD;
        }

        long long current_hash = 0;
        for (int i = 0; i < L; i++) {
            current_hash = (B * current_hash + s[i]) % MOD;
        }
        seen[current_hash].push_back(0);

        for (int i = 1; i <= s.length() - L; i++) {
            current_hash = (B * (current_hash - s[i - 1] * h) + s[i + L - 1]) % MOD;
            if (current_hash < 0) current_hash += MOD;

            if (seen.count(current_hash)) {
                // Verify to avoid spurious collisions
                for (int start_idx : seen[current_hash]) {
                    if (s.substr(start_idx, L) == s.substr(i, L)) {
                        return start_idx; // Found a duplicate
                    }
                }
            }
            seen[current_hash].push_back(i);
        }
        return -1; // No duplicate found
    }

public:
    string longestDupSubstring(string s) {
        int n = s.length();
        int left = 1, right = n - 1;
        int best_start = -1, max_len = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int start_idx = search(s, mid);
            if (start_idx != -1) {
                best_start = start_idx;
                max_len = mid;
                left = mid + 1; // Try to find a longer one
            } else {
                right = mid - 1;
            }
        }

        if (best_start == -1) return "";
        return s.substr(best_start, max_len);
    }
};

int main() {
    Solution sol;
    cout << "Longest dup: " << sol.longestDupSubstring("banana") << endl;
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n \log n)$. Binary searching over the lengths takes $O(\log n)$. For each length, computing the rolling hash takes $O(n)$. Verification on collision takes extra time, but with a good hash, it is infrequent.
- **Space Complexity:** $O(n)$ to store hashes in the hash map.

**Practice:** https://leetcode.com/problems/longest-duplicate-substring/

## Manacher's Algorithm

::: heavy
Finding the longest palindromic substring takes $O(n^2)$ using the expand-around-centre technique. Manacher's Algorithm optimizes this to $O(n)$ by reusing palindromic checks that have already been done. It operates by maintaining a boundary of the rightmost palindrome discovered so far. If our current centre is within this boundary, we can use the palindrome's mirror on the left to initialize our current palindrome's radius, skipping redundant checks.
:::

Because even-length palindromes have a centre between characters (e.g., "abba"), we first transform the string by inserting a separator character (like `#`) between every letter, and start/end boundaries (like `^` and `$`). "abba" becomes `^#a#b#b#a#$`. All palindromes in the transformed string have an actual character or `#` as an exact centre.

Let `P[i]` be the radius of the longest palindrome centred at `i`.
We maintain `C` (the centre of the rightmost palindrome found) and `R` (its right boundary `C + P[C]`).
For a new centre `i` (where `i > C`):
- We find its mirror `i_mirror = C - (i - C)`.
- If `i < R`, `i` is inside the rightmost palindrome. We can immediately say that `P[i]` is at least `min(R - i, P[i_mirror])`.
- After this initial setup, we expand around `i` normally to find the true radius.
- Finally, if the palindrome at `i` extends beyond `R`, we update `C = i` and `R = i + P[i]`.

### Longest Palindromic Substring (Manacher)

Given a string `s`, return the longest palindromic substring in `s`.

**Intuition:**
We implement Manacher's algorithm. The longest radius in the `P` array directly gives us the length of the longest palindrome in the original string, and the centre index helps us extract the exact substring.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        // Transform the string
        string t = "^";
        for (char c : s) {
            t += "#" + string(1, c);
        }
        t += "#$";
        
        int n = t.length();
        vector<int> P(n, 0);
        int C = 0; // Centre of rightmost palindrome
        int R = 0; // Right boundary of rightmost palindrome
        
        for (int i = 1; i < n - 1; i++) {
            int i_mirror = 2 * C - i; // Same as C - (i - C)
            
            if (R > i) {
                P[i] = min(R - i, P[i_mirror]);
            } else {
                P[i] = 0;
            }
            
            // Expand palindrome centred at i
            while (t[i + 1 + P[i]] == t[i - 1 - P[i]]) {
                P[i]++;
            }
            
            // Update C and R if we expanded past R
            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }
        }
        
        // Find the maximum element in P
        int max_len = 0;
        int center_index = 0;
        for (int i = 1; i < n - 1; i++) {
            if (P[i] > max_len) {
                max_len = P[i];
                center_index = i;
            }
        }
        
        // Calculate the starting index in the original string
        int start_idx = (center_index - 1 - max_len) / 2;
        return s.substr(start_idx, max_len);
    }
};

int main() {
    Solution sol;
    cout << "Longest palindrome: " << sol.longestPalindrome("babad") << endl;
    cout << "Longest palindrome: " << sol.longestPalindrome("cbbd") << endl;
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n)$ where $n$ is the length of `s`. The inner `while` loop only executes when expanding the `R` boundary, and `R` can only increase up to $2n+3$. Thus, the total amortized cost of the expansion is $O(n)$.
- **Space Complexity:** $O(n)$ to store the transformed string and the `P` array.

**Practice:** https://leetcode.com/problems/longest-palindromic-substring/

## Close

::: interview
When should you use which algorithm?
- **Single pattern search:** KMP or Z-algorithm. Both are $O(n+m)$ and rely on preprocessing the pattern.
- **Many queries, duplicate substrings, or multidimensional search:** Rabin-Karp (Rolling Hash). It is extremely versatile for matching lengths across different starting positions.
- **Longest palindromic substring:** Manacher's Algorithm is optimal $O(n)$, but the simpler Expand-Around-Centre $O(n^2)$ approach is almost always the acceptable fallback in an interview if you forget Manacher's details.
:::
