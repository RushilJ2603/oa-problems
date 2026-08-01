# Tries

::: heavy
We now shift from standard binary trees to **tries** (often pronounced "tries" as in "retrieval", though originally "trees"), a specialized data structure for fast prefix-based string operations.
:::

::: definition
A **trie** (or prefix tree) is an $n$-ary tree where each edge represents a character, and each root-to-node path spells out a string prefix. A boolean flag at a node marks the end of a valid word. The defining property is that insertion, search, and prefix-matching take $O(L)$ time, where $L$ is the length of the word, independent of how many words are stored in the trie.
:::

In a standard string trie, the canonical node uses a fixed-size array to map characters to child nodes. For lowercase English letters, a node looks like this:

```cpp
struct Node {
    Node* next[26];
    bool isEnd;
    
    Node() {
        for (int i = 0; i < 26; ++i) next[i] = nullptr;
        isEnd = false;
    }
};
```

::: keypoint
Why an array of size 26 instead of a `unordered_map<char, Node*>`? For small alphabets, fixed arrays are vastly superior because they provide cache-friendly, zero-overhead $O(1)$ lookups. However, for large alphabets (like full Unicode), the memory cost becomes prohibitive, making hash maps or balanced BSTs the necessary alternative.
:::

::: trap
A trie can be extremely memory-heavy. Each node allocates 26 pointers, most of which may be null. Nodes are typically heap-allocated dynamically. In competitive programming and interviews, memory leaks from not freeing the trie are often tolerated for speed, but you can also use an index-pool `vector<array<int, 26>>` instead of pointers to avoid allocations entirely.
:::

## Standard Trie Operations

### Trie Implementation and Operations
Implement a trie supporting `insert`, `search`, and `startsWith` methods.

**Intuition:**
To insert a word, we start at the root and iterate through each character of the word. If the current character's edge does not exist, we create a new node. We then move to the child node. After processing all characters, we mark the final node's `isEnd` flag as true. For `search` and `startsWith`, we follow the path dictated by the characters. If a required child pointer is ever null, the word or prefix does not exist. The only difference is that `search` requires the final node's `isEnd` flag to be true, while `startsWith` just requires reaching the end of the prefix.

```cpp
#include <string>

using namespace std;

struct Node {
    Node* next[26];
    bool isEnd;
    
    Node() {
        for (int i = 0; i < 26; ++i) {
            next[i] = nullptr;
        }
        isEnd = false;
    }
    
    bool containsKey(char ch) {
        return next[ch - 'a'] != nullptr;
    }
    
    void put(char ch, Node* node) {
        next[ch - 'a'] = node;
    }
    
    Node* get(char ch) {
        return next[ch - 'a'];
    }
};

class Trie {
private:
    Node* root;
    
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) {
                return false;
            }
            node = node->get(ch);
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containsKey(ch)) {
                return false;
            }
            node = node->get(ch);
        }
        return true;
    }
};
```

**Complexity:** Time $O(L)$ and Space $O(L)$ for `insert`, where $L$ is the length of the string. `search` and `startsWith` take $O(L)$ time and $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/implement-trie-prefix-tree/

### Trie Implementation and Advanced Operations
Implement a trie supporting `insert`, `countWordsEqualTo(word)`, `countWordsStartingWith(prefix)`, and `erase(word)`.

**Intuition:**
To answer frequency queries efficiently, we augment the trie node with two integer counters instead of a single boolean flag: `cntEnd` (how many exact words end at this node) and `cntPrefix` (how many words share this path as a prefix). When inserting a word, we increment `cntPrefix` at every node visited and `cntEnd` at the final node. When erasing a word, we simply traverse the path and decrement these same counters. 

```cpp
#include <string>

using namespace std;

struct Node {
    Node* next[26];
    int cntEnd;
    int cntPrefix;
    
    Node() {
        for (int i = 0; i < 26; ++i) {
            next[i] = nullptr;
        }
        cntEnd = 0;
        cntPrefix = 0;
    }
    
    bool containsKey(char ch) {
        return next[ch - 'a'] != nullptr;
    }
    
    void put(char ch, Node* node) {
        next[ch - 'a'] = node;
    }
    
    Node* get(char ch) {
        return next[ch - 'a'];
    }
};

class Trie {
private:
    Node* root;
    
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
            node->cntPrefix++;
        }
        node->cntEnd++;
    }
    
    int countWordsEqualTo(string word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) {
                return 0;
            }
            node = node->get(ch);
        }
        return node->cntEnd;
    }
    
    int countWordsStartingWith(string prefix) {
        Node* node = root;
        for (char ch : prefix) {
            if (!node->containsKey(ch)) {
                return 0;
            }
            node = node->get(ch);
        }
        return node->cntPrefix;
    }
    
    void erase(string word) {
        Node* node = root;
        for (char ch : word) {
            if (node->containsKey(ch)) {
                node = node->get(ch);
                node->cntPrefix--;
            }
        }
        node->cntEnd--;
    }
};
```

**Complexity:** Time $O(L)$ for all operations. Space $O(L)$ for `insert`, $O(1)$ auxiliary space for queries and deletion.

**Practice:** https://www.naukri.com/code360/problems/implement-trie_1387095

## String and Prefix Problems

### Longest Word With All Prefixes
Given an array of strings, find the longest string such that every prefix of the string is also present in the array. If there is a tie, return the lexicographically smallest string.

**Intuition:**
First, insert all strings into a trie. To verify if a string has all its prefixes present, we can walk down its path in the trie and check that `isEnd` is true for every node along the way. We can optimize this by doing a single Depth-First Search (DFS) on the trie starting from the root, exploring only edges where `isEnd` is true. As we traverse, we keep track of the longest string constructed so far.

::: keypoint
When comparing lengths, to easily break ties by lexicographic order, we can either sort the input strings before processing or explicitly handle the comparison `currentWord < bestWord` when lengths are equal. Processing via DFS with ordered child traversal (`'a'` to `'z'`) automatically handles lexicographic tie-breaking if implemented carefully.
:::

```cpp
#include <string>
#include <vector>

using namespace std;

struct Node {
    Node* next[26];
    bool isEnd;
    
    Node() {
        for (int i = 0; i < 26; ++i) next[i] = nullptr;
        isEnd = false;
    }
};

class Solution {
private:
    Node* root;
    
    void insert(string& word) {
        Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->next[idx]) {
                node->next[idx] = new Node();
            }
            node = node->next[idx];
        }
        node->isEnd = true;
    }

public:
    string longestWord(vector<string>& words) {
        root = new Node();
        for (string& w : words) {
            insert(w);
        }
        
        string longest = "";
        for (string& w : words) {
            Node* node = root;
            bool allPrefixes = true;
            for (char ch : w) {
                node = node->next[ch - 'a'];
                if (!node->isEnd) {
                    allPrefixes = false;
                    break;
                }
            }
            if (allPrefixes) {
                if (w.length() > longest.length() || 
                   (w.length() == longest.length() && w < longest)) {
                    longest = w;
                }
            }
        }
        return longest;
    }
};
```

**Complexity:** Time $O(N \cdot L)$ to insert and verify, where $N$ is the number of words and $L$ is the maximum length of a word. Space $O(N \cdot L)$ for the trie.

**Practice:** https://leetcode.com/problems/longest-word-in-dictionary/

### Number of Distinct Substrings in a String
Given a string, find the total number of distinct substrings it contains.

**Intuition:**
A substring is simply a prefix of a suffix. If we take every suffix of the string and insert them all into a single trie, the trie will naturally merge identical prefixes. Every unique path from the root to any node in this trie represents exactly one unique substring. Therefore, the number of distinct substrings is exactly equal to the total number of nodes in the trie, excluding the root.

```cpp
#include <string>

using namespace std;

struct Node {
    Node* next[26];
    Node() {
        for (int i = 0; i < 26; ++i) next[i] = nullptr;
    }
};

int countDistinctSubstrings(string s) {
    Node* root = new Node();
    int distinctCount = 0;
    int n = s.length();
    
    for (int i = 0; i < n; ++i) {
        Node* node = root;
        for (int j = i; j < n; ++j) {
            int idx = s[j] - 'a';
            if (node->next[idx] == nullptr) {
                node->next[idx] = new Node();
                distinctCount++;
            }
            node = node->next[idx];
        }
    }
    
    return distinctCount + 1;
}
```

**Complexity:** Time $O(N^{2})$ because there are $N$ suffixes and inserting each takes up to $O(N)$ time. Space $O(N^{2})$ for the maximum number of nodes in the trie.

**Practice:** https://www.naukri.com/code360/problems/count-distinct-substrings_985292

## Bit Tries (XOR Problems)

::: heavy
A **binary trie** (or XOR trie) modifies the standard character trie to store binary representations of integers. Instead of an array of 26 character pointers, each node simply has `Node* next[2]` (for bit `0` and bit `1`). By inserting the 32-bit representations of numbers from Most Significant Bit (MSB) to Least Significant Bit (LSB), we can efficiently solve complex bitwise queries, particularly those involving maximum XOR.
:::

### Maximum XOR of Two Numbers in an Array
Given an integer array, find the maximum bitwise XOR of any two elements.

**Intuition:**
To maximize the XOR of a number `X` with some element in the array, we want the corresponding bits to be as different as possible. We insert all numbers into a binary trie, padding them to 32 bits (MSB first). For each number in the array, we query the trie: starting from the MSB, we greedily try to traverse the branch representing the *opposite* bit. If the opposite bit exists, we take it (adding $2^{k}$ to our running XOR total); if not, we are forced to take the same bit.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

struct TrieNode {
    TrieNode* next[2];
    TrieNode() {
        next[0] = nullptr;
        next[1] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(int num) {
        TrieNode* node = root;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!node->next[bit]) {
                node->next[bit] = new TrieNode();
            }
            node = node->next[bit];
        }
    }
    
    int getMaxXor(int num) {
        TrieNode* node = root;
        int maxXor = 0;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            int opposite = 1 - bit;
            if (node->next[opposite]) {
                maxXor |= (1 << i);
                node = node->next[opposite];
            } else {
                node = node->next[bit];
            }
        }
        return maxXor;
    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie trie;
        for (int num : nums) {
            trie.insert(num);
        }
        
        int maxi = 0;
        for (int num : nums) {
            maxi = max(maxi, trie.getMaxXor(num));
        }
        return maxi;
    }
};
```

**Complexity:** Time $O(N \cdot 32)$ to insert and query each number. Space $O(N \cdot 32)$ to store the bit trie.

**Practice:** https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/

### Maximum XOR With an Element From an Array
Given an array `nums` and an array of queries where each `queries[i] = [x_i, m_i]`, answer each query by finding the maximum XOR of `x_i` with any element from `nums` that is less than or equal to `m_i`. If no element is $\le m_i$, return `-1`.

**Intuition:**
Because we can only XOR with elements up to `m_i`, we can sort the queries offline. If we sort the queries by `m_i` in ascending order, and also sort the `nums` array in ascending order, we can dynamically insert elements into our XOR trie just before they are needed. For each query, we insert all `nums` that are $\le m_i$. After inserting, we query the trie for the maximum XOR with `x_i`. 

::: keypoint
This "offline sorting" trick turns a problem with dynamic constraints into a standard sweeping algorithm. By sorting queries by their limit, we only insert each element into the trie once, rather than building and tearing down tries for every query.
:::

```cpp
#include <vector>
#include <algorithm>

using namespace std;

struct TrieNode {
    TrieNode* next[2];
    TrieNode() {
        next[0] = nullptr;
        next[1] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }
    
    void insert(int num) {
        TrieNode* node = root;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!node->next[bit]) {
                node->next[bit] = new TrieNode();
            }
            node = node->next[bit];
        }
    }
    
    int getMaxXor(int num) {
        TrieNode* node = root;
        int maxXor = 0;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            int opposite = 1 - bit;
            if (node->next[opposite]) {
                maxXor |= (1 << i);
                node = node->next[opposite];
            } else {
                node = node->next[bit];
            }
        }
        return maxXor;
    }
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        int q = queries.size();
        vector<vector<int>> offlineQueries;
        for (int i = 0; i < q; ++i) {
            offlineQueries.push_back({queries[i][1], queries[i][0], i});
        }
        
        sort(offlineQueries.begin(), offlineQueries.end());
        sort(nums.begin(), nums.end());
        
        vector<int> ans(q, -1);
        Trie trie;
        int idx = 0;
        int n = nums.size();
        
        for (auto& query : offlineQueries) {
            int m = query[0];
            int x = query[1];
            int qIdx = query[2];
            
            while (idx < n && nums[idx] <= m) {
                trie.insert(nums[idx]);
                idx++;
            }
            
            if (idx == 0) {
                ans[qIdx] = -1;
            } else {
                ans[qIdx] = trie.getMaxXor(x);
            }
        }
        
        return ans;
    }
};
```

**Complexity:** Time $O(Q \log Q + N \log N + Q \cdot 32)$ where sorting dominates the $Q$ and $N$ factors, and trie operations take constant $32$ steps. Space $O(N \cdot 32 + Q)$ for the trie and offline query storage.

**Practice:** https://leetcode.com/problems/maximum-xor-with-an-element-from-array/

## Conclusion

::: interview
In real interviews, tries are predominantly tested in three scenarios: autocomplete/prefix search, word dictionaries, and greedy bitwise optimization via the XOR trie. While a standard hash set gives $O(1)$ lookup for an exact word, a trie unlocks powerful prefix queries and ordered traversals. If memory allocations or garbage collection become a bottleneck, remember the index-pool implementation style: instead of `Node*`, you use a `vector<array<int, 26>>` and represent pointers as integer indices.
:::
