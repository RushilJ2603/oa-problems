# Strings — Basic and Medium

`std::string` in C++ is a mutable dynamic array of `char`. It supports fast random access and provides a rich API for manipulation, including `substr` for extracting substrings, `find` for substring searches, and `+=` for efficient appending. For a complete API reference, refer to the C++ STL section. However, string manipulation comes with performance pitfalls. A frequent mistake is using `s = s + c` instead of `s += c` inside a loop.

::: trap
Building a string in a loop using `s = s + c` creates a brand new string and copies all characters every time, resulting in an $O(n^2)$ time complexity. Always use `s += c` or `s.push_back(c)` to append characters in amortized $O(1)$ time.
:::

Because characters in C++ are represented by their underlying ASCII integer values, character arithmetic is done directly. For example, `s[i] - 'a'` maps lowercase letters to their $0$-based alphabet index ($0$ to $25$). The `<cctype>` header provides essential utility functions like `isalpha`, `isdigit`, `isalnum`, `tolower`, and `toupper`.

## Basic and Easy String Problems

### Remove Outermost Parentheses
Given a valid parentheses string `s`, remove the outermost parentheses of every primitive string in its primitive decomposition.

**Intuition:**
A valid parentheses string has an equal number of open and close parentheses. We can keep a running balance or depth counter. An open parenthesis `(` is considered "outermost" if it is the very first one in a block (when the depth is $0$). A close parenthesis `)` is "outermost" if it brings the depth back to $0$. We append only the inner characters to the result.

**C++ Solution:**
```cpp
#include <string>

std::string removeOuterParentheses(std::string s) {
    std::string result;
    int depth = 0;
    
    for (char c : s) {
        if (c == '(') {
            if (depth > 0) result += c;
            depth++;
        } else {
            depth--;
            if (depth > 0) result += c;
        }
    }
    return result;
}
```

**Complexity:** Time $O(n)$ to process each character exactly once. Space $O(n)$ for the resulting string, or $O(1)$ auxiliary space.
**Practice:** https://leetcode.com/problems/remove-outermost-parentheses/

### Reverse Words in a String / Palindrome Check
Given an input string `s`, reverse the order of the words. A word is defined as a sequence of non-space characters.

**Intuition:**
Checking if a string is a palindrome or reversing a string relies on a fundamental two-pointer technique: comparing or swapping characters from both ends moving inwards. For reversing words, a brute-force approach extracts all words into an array and reverses the array. An optimal, in-place approach (if mutability allows) trims spaces, reverses the entire string, and then reverses the individual characters of each token back to their correct order.

**C++ Solution:**
```cpp
#include <string>
#include <algorithm>

std::string reverseWords(std::string s) {
    std::reverse(s.begin(), s.end());
    int n = s.length();
    int idx = 0;
    
    for (int start = 0; start < n; ++start) {
        if (s[start] != ' ') {
            if (idx != 0) {
                s[idx++] = ' ';
            }
            int end = start;
            while (end < n && s[end] != ' ') {
                s[idx++] = s[end++];
            }
            std::reverse(s.begin() + idx - (end - start), s.begin() + idx);
            start = end;
        }
    }
    s.erase(s.begin() + idx, s.end());
    return s;
}
```

**Complexity:** Time $O(n)$ as each character is reversed at most twice. Space $O(1)$ since the modifications are done entirely in place.
**Practice:** https://leetcode.com/problems/reverse-words-in-a-string/

### Largest Odd Number in a String
Given a string `num` representing a large integer, return the largest-valued odd integer (as a string) that is a non-empty substring of `num`.

**Intuition:**
The parity of an integer is dictated solely by its last digit. To find the largest odd substring, scan from the right for the first odd digit. Everything from the start of the string up to this odd digit forms the largest possible odd integer.

**C++ Solution:**
```cpp
#include <string>

std::string largestOddNumber(std::string num) {
    for (int i = num.length() - 1; i >= 0; --i) {
        if ((num[i] - '0') % 2 != 0) {
            return num.substr(0, i + 1);
        }
    }
    return "";
}
```

**Complexity:** Time $O(n)$ worst-case to scan the string. Space $O(1)$ auxiliary, though extracting the substring takes $O(n)$ space.
**Practice:** https://leetcode.com/problems/largest-odd-number-in-string/

### Longest Common Prefix
Given an array of strings, find the longest common prefix string amongst them.

**Intuition:**
Imagine the strings aligned vertically. Examine the first character of all strings. If they match, it is part of the common prefix. Continue this vertical scan column by column until a mismatch is encountered or the end of the shortest string is reached.

**C++ Solution:**
```cpp
#include <string>
#include <vector>

std::string longestCommonPrefix(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    
    for (int i = 0; i < strs[0].length(); ++i) {
        char c = strs[0][i];
        for (int j = 1; j < strs.size(); ++j) {
            if (i == strs[j].length() || strs[j][i] != c) {
                return strs[0].substr(0, i);
            }
        }
    }
    return strs[0];
}
```

**Complexity:** Time $O(S)$ where $S$ is the sum of all characters in all strings in the worst case. Space $O(1)$ auxiliary.
**Practice:** https://leetcode.com/problems/longest-common-prefix/

### Isomorphic String
Given two strings `s` and `t`, determine if they are isomorphic. Two strings are isomorphic if the characters in `s` can be replaced to get `t`, maintaining character order and avoiding mapping two characters to the same character.

**Intuition:**
A bijection (a one-to-one mapping) between characters in `s` and `t` is required. Maintain two arrays tracking the last seen index of each character. If the current characters in `s` and `t` were previously seen at different indices, the mapping is broken, and the strings are not isomorphic.

**C++ Solution:**
```cpp
#include <string>
#include <vector>

bool isIsomorphic(std::string s, std::string t) {
    if (s.length() != t.length()) return false;
    
    std::vector<int> mapS(256, -1);
    std::vector<int> mapT(256, -1);
    
    for (int i = 0; i < s.length(); ++i) {
        if (mapS[s[i]] != mapT[t[i]]) {
            return false;
        }
        mapS[s[i]] = i;
        mapT[t[i]] = i;
    }
    return true;
}
```

**Complexity:** Time $O(n)$ where $n$ is the length of the strings. Space $O(1)$ since the alphabet size is constant (256 ASCII characters).
**Practice:** https://leetcode.com/problems/isomorphic-strings/

### Rotate String
Given two strings `s` and `goal`, return `true` if and only if `s` can become `goal` after some number of shifts on `s`.

**Intuition:**
When a string `s` is shifted, a prefix of `s` moves to the back. By concatenating `s` with itself (`s + s`), the new string contains all possible valid rotations of `s` as substrings. Thus, if `goal` has the same length as `s` and is a substring of `s + s`, it is a valid rotation.

**C++ Solution:**
```cpp
#include <string>

bool rotateString(std::string s, std::string goal) {
    if (s.length() != goal.length()) return false;
    std::string doubled = s + s;
    return doubled.find(goal) != std::string::npos;
}
```

**Complexity:** Time $O(n^2)$ using the standard library `find` (or $O(n)$ if implemented with KMP). Space $O(n)$ to store the concatenated string.
**Practice:** https://leetcode.com/problems/rotate-string/

### Check if Two Strings are Anagrams
Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise.

**Intuition:**
An anagram contains identical characters with identical frequencies. While sorting both strings takes $O(n \log n)$ time, a linear approach counts the frequencies of characters in `s` and decrements them for `t`. If all counts resolve to $0$, they are anagrams.

::: keypoint
Whenever a string problem involves character frequencies and a limited alphabet (like lowercase letters), a fixed-size array `int freq[26] = {0}` is dramatically faster and uses less memory than a `std::unordered_map`.
:::

**C++ Solution:**
```cpp
#include <string>
#include <vector>

bool isAnagram(std::string s, std::string t) {
    if (s.length() != t.length()) return false;
    
    std::vector<int> freq(26, 0);
    for (int i = 0; i < s.length(); ++i) {
        freq[s[i] - 'a']++;
        freq[t[i] - 'a']--;
    }
    
    for (int count : freq) {
        if (count != 0) return false;
    }
    return true;
}
```

**Complexity:** Time $O(n)$ to iterate through the strings. Space $O(1)$ for the constant-size frequency array.
**Practice:** https://leetcode.com/problems/valid-anagram/

## Medium String Problems

### Sort Characters by Frequency
Given a string `s`, sort it in decreasing order based on the frequency of the characters.

**Intuition:**
Count the occurrences of each character using a frequency map or array. Then, sort the characters from highest frequency to lowest. This can be achieved by placing the counts and characters into a `std::vector` of pairs and sorting, or by utilizing a bucket sort or priority queue since the maximum frequency cannot exceed the string's length.

**C++ Solution:**
```cpp
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::string frequencySort(std::string s) {
    std::unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    
    std::vector<std::pair<int, char>> sortedChars;
    for (auto const& [c, count] : freq) {
        sortedChars.push_back({count, c});
    }
    
    std::sort(sortedChars.rbegin(), sortedChars.rend());
    
    std::string result;
    for (auto const& [count, c] : sortedChars) {
        result += std::string(count, c);
    }
    return result;
}
```

**Complexity:** Time $O(n \log k)$ where $n$ is the string length and $k$ is the number of unique characters ($k \le 256$, simplifying to $O(n)$). Space $O(n)$ to store frequencies and the output string.
**Practice:** https://leetcode.com/problems/sort-characters-by-frequency/

### Maximum Nesting Depth of the Parentheses
Given a valid parentheses string `s`, return its maximum nesting depth.

**Intuition:**
The depth at any given point is the number of open parentheses `(` minus the number of closed parentheses `)` encountered so far. Maintain a running depth counter that increments on `(` and decrements on `)`. The result is the maximum value this counter achieves.

**C++ Solution:**
```cpp
#include <string>
#include <algorithm>

int maxDepth(std::string s) {
    int max_depth = 0;
    int current_depth = 0;
    
    for (char c : s) {
        if (c == '(') {
            current_depth++;
            max_depth = std::max(max_depth, current_depth);
        } else if (c == ')') {
            current_depth--;
        }
    }
    return max_depth;
}
```

**Complexity:** Time $O(n)$ for a single linear scan. Space $O(1)$ utilizing only integer counters.
**Practice:** https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/

### Roman to Integer
Given a roman numeral, convert it to an integer.

**Intuition:**
Roman numerals are evaluated by summing the values of their individual characters. The subtractive rule dictates that if a smaller numeral appears before a larger one, it is subtracted instead of added (e.g., `IX` is $9$). By comparing each character's value with the next, we can correctly add or subtract the value from a running total.

**C++ Solution:**
```cpp
#include <string>
#include <unordered_map>

int romanToInt(std::string s) {
    std::unordered_map<char, int> roman = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
    
    int total = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (i + 1 < s.length() && roman[s[i]] < roman[s[i+1]]) {
            total -= roman[s[i]];
        } else {
            total += roman[s[i]];
        }
    }
    return total;
}
```

**Complexity:** Time $O(n)$ to evaluate each character. Space $O(1)$ for the fixed-size lookup map.
**Practice:** https://leetcode.com/problems/roman-to-integer/

### String to Integer (atoi)
Implement the `myAtoi(string s)` function, which converts a string to a 32-bit signed integer, handling leading whitespace, optional signs, and out-of-bounds clamping.

**Intuition:**
Parse the string in stages: skip leading spaces, identify a `+` or `-` sign, and append contiguous digits to form the number. The primary challenge is preventing integer overflow. Before appending a digit by multiplying the running total by $10$, verify that the total does not already exceed `INT_MAX / 10`.

::: trap
Do not accumulate the result in a `long long` and clamp at the end, as interviewers frequently prohibit types larger than 32-bit for this specific problem. You must check for overflow *before* the multiplication and addition.
:::

**C++ Solution:**
```cpp
#include <string>
#include <climits>
#include <cctype>

int myAtoi(std::string s) {
    int i = 0;
    int n = s.length();
    
    while (i < n && s[i] == ' ') {
        i++;
    }
    
    int sign = 1;
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }
    
    int result = 0;
    while (i < n && std::isdigit(s[i])) {
        int digit = s[i] - '0';
        
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > INT_MAX % 10)) {
            return (sign == 1) ? INT_MAX : INT_MIN;
        }
        
        result = result * 10 + digit;
        i++;
    }
    
    return result * sign;
}
```

**Complexity:** Time $O(n)$ for a single pass through the string. Space $O(1)$ auxiliary memory.
**Practice:** https://leetcode.com/problems/string-to-integer-atoi/

### Longest Palindromic Substring
Given a string `s`, return the longest palindromic substring in `s`.

**Intuition:**
A brute-force solution checks all substrings in $O(n^3)$ time. A superior $O(n^2)$ approach expands around possible centers. Palindromes mirror around their center, which can be a single character (for odd-length palindromes) or the space between two characters (for even-length). Iterate through all $2n - 1$ centers and expand outwards symmetrically. A linear $O(n)$ solution via Manacher's Algorithm exists, but is strictly an advanced string technique.

**C++ Solution:**
```cpp
#include <string>
#include <algorithm>

std::string longestPalindrome(std::string s) {
    if (s.empty()) return "";
    
    int start = 0, max_len = 0;
    
    auto expandAroundCenter = [&](int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    };
    
    for (int i = 0; i < s.length(); ++i) {
        int len1 = expandAroundCenter(i, i);
        int len2 = expandAroundCenter(i, i + 1);
        int len = std::max(len1, len2);
        
        if (len > max_len) {
            max_len = len;
            start = i - (len - 1) / 2;
        }
    }
    return s.substr(start, max_len);
}
```

**Complexity:** Time $O(n^2)$ as it expands outwards from $2n - 1$ centers, taking at most $O(n)$ per expansion. Space $O(1)$ auxiliary.
**Practice:** https://leetcode.com/problems/longest-palindromic-substring/

### Sum of Beauty of All Substrings
The beauty of a string is the difference in frequencies between the most frequent and least frequent characters. Given a string `s`, return the sum of beauty of all of its substrings.

**Intuition:**
An $O(n^2)$ enumeration of all substrings is required. Fix the start of the substring and dynamically extend the end character by character. Maintain a running frequency array of the characters in the current window. For every character added, update its frequency and calculate the difference between the maximum and non-zero minimum frequencies.

**C++ Solution:**
```cpp
#include <string>
#include <vector>
#include <algorithm>

int beautySum(std::string s) {
    int totalBeauty = 0;
    int n = s.length();
    
    for (int i = 0; i < n; ++i) {
        std::vector<int> freq(26, 0);
        for (int j = i; j < n; ++j) {
            freq[s[j] - 'a']++;
            
            int max_f = 0;
            int min_f = n;
            for (int f : freq) {
                if (f > 0) {
                    max_f = std::max(max_f, f);
                    min_f = std::min(min_f, f);
                }
            }
            totalBeauty += (max_f - min_f);
        }
    }
    return totalBeauty;
}
```

**Complexity:** Time $O(n^2)$ since fixing start and end points takes two nested loops, and iterating the 26-element array takes $O(1)$ at each step. Space $O(1)$ for the fixed-size frequency array.
**Practice:** https://leetcode.com/problems/sum-of-beauty-of-all-substrings/

### Reverse Every Word in a String
Given a string `s`, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

**Intuition:**
A two-pointer sequence can reverse the characters within a specific window. Scan the string linearly to identify spaces, which delineate word boundaries. When a word boundary is found, reverse the characters from the start of the word to the end of the word in place.

**C++ Solution:**
```cpp
#include <string>
#include <algorithm>

std::string reverseWordsInPlace(std::string s) {
    int i = 0;
    int n = s.length();
    
    for (int j = 0; j <= n; ++j) {
        if (j == n || s[j] == ' ') {
            std::reverse(s.begin() + i, s.begin() + j);
            i = j + 1;
        }
    }
    return s;
}
```

**Complexity:** Time $O(n)$ as `std::reverse` visits each character precisely once per word. Space $O(1)$ since all reversals occur entirely in place.
**Practice:** https://leetcode.com/problems/reverse-words-in-a-string-iii/

## Interview Insights

::: interview
What interviewers probe in string manipulation problems:
1. **Memory efficiency:** They evaluate whether you comprehend the cost of copying strings in loops versus making $O(1)$ in-place modifications using references or pointer arithmetic.
2. **Frequency counting:** Using a fixed integer array (e.g., `int freq[26]`) instead of a `std::unordered_map` is a strong signal that you understand constant time and spatial overhead.
3. **Two pointers and sliding windows:** Many basic string algorithms (like palindromes and pattern matching) reduce to sliding windows or two-pointer logic. Recognizing when a problem falls into these categories is essential.
4. **ASCII arithmetic:** You are expected to seamlessly utilize basic mappings like `s[i] - 'a'` without relying on heavy library structures.
:::
