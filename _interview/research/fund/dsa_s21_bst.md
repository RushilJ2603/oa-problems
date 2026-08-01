# Binary Search Trees

::: heavy
A Binary Search Tree (BST) is a node-based binary tree data structure with a specific ordering property. The fundamental power of a BST is its ability to efficiently maintain a dynamically changing dataset while supporting fast lookup, insertion, and deletion operations, mirroring the logic of binary search on an array.
:::

::: definition
A **Binary Search Tree** is a binary tree where, for every node, all keys in its left subtree are strictly smaller than its key, and all keys in its right subtree are strictly larger than its key.
:::

::: keypoint
An **inorder traversal of a BST yields keys in sorted order**. This is the single most important property of a BST; many BST problems elegantly reduce to "do something on a sorted stream."
:::

The cost model for a BST is strictly dependent on its height, $h$. Operations like search, insert, and delete take $O(h)$ time. If the tree is balanced, $h = \log n$, making operations $O(\log n)$.

::: trap
A standard BST is not guaranteed to be balanced. If elements are inserted in an already sorted (or reverse-sorted) order, the BST degenerates into a skewed linked list, yielding $O(n)$ time for all operations.
:::

Contrast a BST with a hash set: while a hash set provides $O(1)$ average time for insertions and lookups, it offers no ordering. A BST provides ordered operations like finding the floor, ceiling, successor, or range queries efficiently. In practice, C++ `std::set` and `std::map` are implemented as balanced BSTs (specifically, Red-Black Trees).

## 1. Search in a Binary Search Tree

### Search in a Binary Search Tree
Given the root of a binary search tree and an integer `val`, find the node in the BST that has a value equal to `val` and return the subtree rooted with that node. If such a node does not exist, return `nullptr`.

**Intuition:** 
A brute force approach would search every node using a standard tree traversal in $O(n)$ time. However, the optimal approach exploits the BST ordering property. Starting at the root, we compare the target value with the current node's value. If the target is smaller, we know it must reside in the left subtree; if it is larger, it must reside in the right subtree. This allows us to discard an entire subtree at each step.

```cpp
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root != nullptr && root->val != val) {
            root = (val < root->val) ? root->left : root->right;
        }
        return root;
    }
};

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    
    Solution sol;
    TreeNode* result = sol.searchBST(root, 2);
    std::cout << (result ? result->val : -1) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(h)$ where $h$ is the tree's height ($O(\log n)$ balanced, $O(n)$ skewed). We traverse one path from root to leaf.
- **Space:** $O(1)$ auxiliary space for the iterative approach.

**Practice:** https://leetcode.com/problems/search-in-a-binary-search-tree/

## 2. Find Min and Max in a BST

### Find Min and Max in a BST
Given the root of a binary search tree, find the minimum and maximum elements in it.

**Intuition:** 
A brute force approach visits all nodes to track the minimum and maximum, taking $O(n)$ time. The optimal approach leverages the BST properties: the smallest element is always the leftmost node (following left children until `nullptr`), and the largest element is always the rightmost node (following right children).

```cpp
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int findMin(TreeNode* root) {
        if (root == nullptr) return -1;
        while (root->left != nullptr) {
            root = root->left;
        }
        return root->val;
    }
    
    int findMax(TreeNode* root) {
        if (root == nullptr) return -1;
        while (root->right != nullptr) {
            root = root->right;
        }
        return root->val;
    }
};

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    
    Solution sol;
    std::cout << "Min: " << sol.findMin(root) << ", Max: " << sol.findMax(root) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(h)$ for both operations, since we trace a single path down the tree ($O(\log n)$ balanced, $O(n)$ skewed).
- **Space:** $O(1)$ auxiliary space.

**Practice:** https://www.geeksforgeeks.org/find-the-minimum-element-in-a-binary-search-tree/

## 3. Ceil in a BST

### Ceil in a BST
Given a BST and a key, find the ceil of the given key. The ceil is the smallest node value that is greater than or equal to the given key.

**Intuition:** 
A brute force approach flattens the tree into a sorted array and performs a binary search. The optimal approach uses the BST ordering. If we encounter a node with a value equal to the key, we found our exact ceil. If the node's value is less than the key, the ceil must exist in the right subtree. If the node's value is greater than the key, this node is a potential ceil candidate, but a smaller valid candidate might exist in its left subtree, so we search left.

```cpp
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int findCeil(TreeNode* root, int key) {
        int ceil = -1;
        while (root != nullptr) {
            if (root->val == key) {
                return root->val;
            }
            if (root->val < key) {
                root = root->right;
            } else {
                ceil = root->val;
                root = root->left;
            }
        }
        return ceil;
    }
};

int main() {
    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(4);
    root->right = new TreeNode(12);
    
    Solution sol;
    std::cout << sol.findCeil(root, 5) << "\n"; // Expected 8
    return 0;
}
```

**Complexity:**
- **Time:** $O(h)$ where $h$ is the height of the tree ($O(\log n)$ balanced, $O(n)$ skewed).
- **Space:** $O(1)$ auxiliary space.

**Practice:** https://www.geeksforgeeks.org/floor-and-ceil-from-a-bst/

## 4. Floor in a BST

### Floor in a BST
Given a BST and a key, find the floor of the given key. The floor is the largest node value that is smaller than or equal to the given key.

**Intuition:** 
Symmetric to finding the ceil, a brute force approach explores all nodes. The optimal approach uses the BST properties. If the node's value is exactly the key, we return it. If the node's value is greater than the key, the floor must be in the left subtree. If the node's value is less than the key, the current node is a potential floor candidate, and we move to the right subtree to search for a potentially larger, yet still valid floor.

```cpp
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int findFloor(TreeNode* root, int key) {
        int floor = -1;
        while (root != nullptr) {
            if (root->val == key) {
                return root->val;
            }
            if (root->val > key) {
                root = root->left;
            } else {
                floor = root->val;
                root = root->right;
            }
        }
        return floor;
    }
};

int main() {
    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(4);
    root->right = new TreeNode(12);
    
    Solution sol;
    std::cout << sol.findFloor(root, 5) << "\n"; // Expected 4
    return 0;
}
```

**Complexity:**
- **Time:** $O(h)$ where $h$ is the height of the tree ($O(\log n)$ balanced, $O(n)$ skewed).
- **Space:** $O(1)$ auxiliary space.

**Practice:** https://www.geeksforgeeks.org/floor-and-ceil-from-a-bst/

## 5. Insert a Node in a BST

### Insert a Node in a BST
Given the root node of a BST and a `value` to be inserted, insert the value into the BST and return the root. It is guaranteed that the new value does not exist in the original BST.

**Intuition:** 
A brute force approach of rebuilding the tree is slow. The optimal approach is to traverse the tree using the BST property to find the appropriate `nullptr` leaf position where the new value naturally belongs. We keep track of the current node and attach the new node as either its left or right child based on the value comparison.

```cpp
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }
        
        TreeNode* curr = root;
        while (true) {
            if (val < curr->val) {
                if (curr->left != nullptr) {
                    curr = curr->left;
                } else {
                    curr->left = new TreeNode(val);
                    break;
                }
            } else {
                if (curr->right != nullptr) {
                    curr = curr->right;
                } else {
                    curr->right = new TreeNode(val);
                    break;
                }
            }
        }
        return root;
    }
};

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    
    Solution sol;
    root = sol.insertIntoBST(root, 5);
    std::cout << (root->right->left ? root->right->left->val : -1) << "\n"; // Expected 5
    return 0;
}
```

**Complexity:**
- **Time:** $O(h)$ where $h$ is the height of the tree ($O(\log n)$ balanced, $O(n)$ skewed).
- **Space:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/insert-into-a-binary-search-tree/

## 6. Delete a Node in a BST

### Delete a Node in a BST
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

**Intuition:** 
A brute force solution might rebuild the entire tree without the target node, taking $O(n)$ time. The optimal strategy identifies the node and carefully manipulates pointers to remove it while preserving the BST structure. There are three cases:
1. The node is a leaf: simply remove it.
2. The node has one child: replace the node with its child.
3. The node has two children.

::: keypoint
For the two-children case, replace the node's value with its inorder successor (the smallest node in the right subtree) or predecessor, and recursively delete the successor.
:::

```cpp
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node found
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            
            // Node with two children: Get the inorder successor
            TreeNode* temp = findMin(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
        return root;
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    
    Solution sol;
    root = sol.deleteNode(root, 3);
    std::cout << root->left->val << "\n"; // Expected 4
    return 0;
}
```

**Complexity:**
- **Time:** $O(h)$ where $h$ is the tree's height ($O(\log n)$ balanced, $O(n)$ skewed).
- **Space:** $O(h)$ space for the recursion stack.

**Practice:** https://leetcode.com/problems/delete-node-in-a-bst/

## 7. Kth Smallest and Kth Largest Element in a BST

### Kth Smallest and Kth Largest Element in a BST
Given the root of a BST, and an integer $k$, find the $k$-th smallest and $k$-th largest values (1-indexed) of all the values of the nodes in the tree.

**Intuition:** 
A brute force approach would collect all nodes into an array using any traversal, sort the array, and return the $k$-th element in $O(n \log n)$ time. The optimal approach exploits the fact that an inorder traversal of a BST natively yields elements in strictly increasing order. For the $k$-th smallest, we perform a standard inorder traversal and stop at the $k$-th node. For the $k$-th largest, we perform a reverse inorder traversal (right, root, left) to visit nodes in strictly decreasing order.

```cpp
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    void inorder(TreeNode* root, int& k, int& ans) {
        if (root == nullptr || k == 0) return;
        
        inorder(root->left, k, ans);
        
        if (--k == 0) {
            ans = root->val;
            return;
        }
        
        inorder(root->right, k, ans);
    }
    
    void reverseInorder(TreeNode* root, int& k, int& ans) {
        if (root == nullptr || k == 0) return;
        
        reverseInorder(root->right, k, ans);
        
        if (--k == 0) {
            ans = root->val;
            return;
        }
        
        reverseInorder(root->left, k, ans);
    }

public:
    int kthSmallest(TreeNode* root, int k) {
        int ans = -1;
        inorder(root, k, ans);
        return ans;
    }
    
    int kthLargest(TreeNode* root, int k) {
        int ans = -1;
        reverseInorder(root, k, ans);
        return ans;
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    
    Solution sol;
    std::cout << "3rd Smallest: " << sol.kthSmallest(root, 3) << "\n"; // Expected 4
    return 0;
}
```

**Complexity:**
- **Time:** $O(h + k)$ in the worst case to reach the $k$-th node, bounded by $O(n)$.
- **Space:** $O(h)$ for the recursion stack space.

**Practice:** https://leetcode.com/problems/kth-smallest-element-in-a-bst/

## 8. Validate a Binary Search Tree

### Validate a Binary Search Tree
Given the root of a binary tree, determine if it is a valid binary search tree.

**Intuition:** 

::: trap
Checking only if `node->left->val < node->val` and `node->right->val > node->val` is a common mistake, as it fails to ensure that a node deep in the right subtree is greater than the overall tree's root.
:::

The optimal approach enforces that every node must lie within a strict numerical range `(min, max)`. The root can be any value `(-∞, ∞)`. When branching left, the maximum allowed value becomes the parent's value. When branching right, the minimum allowed value becomes the parent's value. We pass these bounds recursively.

```cpp
#include <iostream>
#include <limits>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    bool isValidBST(TreeNode* node, long long minVal, long long maxVal) {
        if (node == nullptr) return true;
        
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        return isValidBST(node->left, minVal, node->val) &&
               isValidBST(node->right, node->val, maxVal);
    }
    
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max());
    }
};

int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    
    Solution sol;
    std::cout << (sol.isValidBST(root) ? "Valid" : "Invalid") << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(n)$ as we visit every node exactly once.
- **Space:** $O(h)$ for the recursion stack space.

**Practice:** https://leetcode.com/problems/validate-binary-search-tree/

## 9. Lowest Common Ancestor in a BST

### Lowest Common Ancestor in a BST
Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

**Intuition:** 
A brute force approach might use a standard binary tree LCA algorithm that requires fully exploring paths and returning nodes upward. The optimal approach is uniquely possible in a BST.

::: keypoint
Start at the root and walk down using the BST ordering. The first node we encounter whose value lies between `p->val` and `q->val` (inclusive) is definitively the lowest common ancestor.
:::

If both `p` and `q` are strictly smaller than the current node, the LCA must reside in the left subtree. If both are strictly greater, it must reside in the right subtree. Otherwise, the paths diverge here, making the current node the LCA.

```cpp
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root != nullptr) {
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            } else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            } else {
                return root; // Found the split point (or one of them is the root)
            }
        }
        return nullptr;
    }
};

int main() {
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    TreeNode* p = root->left;        // Node 2
    TreeNode* q = new TreeNode(4);   // Node 4
    root->left->right = q;
    
    Solution sol;
    TreeNode* lca = sol.lowestCommonAncestor(root, p, q);
    std::cout << "LCA: " << (lca ? lca->val : -1) << "\n"; // Expected 2
    return 0;
}
```

**Complexity:**
- **Time:** $O(h)$ where $h$ is the tree's height ($O(\log n)$ balanced, $O(n)$ skewed).
- **Space:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

## 10. Construct a BST from its Preorder Traversal

### Construct a BST from its Preorder Traversal
Given an array of integers `preorder`, which represents the preorder traversal of a BST, construct the tree and return its root.

**Intuition:** 
A brute force solution takes the first element as the root, then inserts each subsequent element sequentially in $O(n^2)$ time. The optimal $O(n)$ solution passes a dynamic upper bound downwards. As we process elements linearly, a node belongs in the left subtree if its value is less than the parent's value (the current bound). If it exceeds the bound, it belongs higher up the right subtree of an ancestor.

```cpp
#include <iostream>
#include <vector>
#include <limits>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* build(const std::vector<int>& preorder, int& idx, int upperBound) {
        if (idx == preorder.size() || preorder[idx] > upperBound) {
            return nullptr;
        }
        
        TreeNode* root = new TreeNode(preorder[idx++]);
        root->left = build(preorder, idx, root->val);
        root->right = build(preorder, idx, upperBound);
        
        return root;
    }
    
public:
    TreeNode* bstFromPreorder(std::vector<int>& preorder) {
        int idx = 0;
        return build(preorder, idx, std::numeric_limits<int>::max());
    }
};

int main() {
    std::vector<int> preorder = {8, 5, 1, 7, 10, 12};
    Solution sol;
    TreeNode* root = sol.bstFromPreorder(preorder);
    std::cout << root->val << "\n"; // Expected 8
    return 0;
}
```

**Complexity:**
- **Time:** $O(n)$ because we process each element in the vector exactly once.
- **Space:** $O(h)$ for the recursion stack ($O(\log n)$ balanced, $O(n)$ skewed).

**Practice:** https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/

## 11. Inorder Successor and Predecessor in a BST

### Inorder Successor and Predecessor in a BST
Given a BST and a node, find the inorder successor and predecessor of that node in the BST.

**Intuition:** 
A brute force approach computes the entire inorder traversal and searches for the element, taking $O(n)$ time. The optimal approach uses the BST ordering to find them efficiently in $O(h)$ time. To find the successor: track a potential successor candidate. If the current node's value is greater than the key, it is a candidate, and we move left to search for a smaller valid candidate. If the node's value is less than or equal to the key, we move right. The predecessor is symmetric: if the node is less than the key, it's a candidate, so we move right to find a larger one.

```cpp
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* successor = nullptr;
        while (root != nullptr) {
            if (p->val < root->val) {
                successor = root;
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return successor;
    }

    TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {
        TreeNode* predecessor = nullptr;
        while (root != nullptr) {
            if (p->val > root->val) {
                predecessor = root;
                root = root->right;
            } else {
                root = root->left;
            }
        }
        return predecessor;
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    TreeNode* p = new TreeNode(3);
    root->left = p;
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    
    Solution sol;
    TreeNode* succ = sol.inorderSuccessor(root, p);
    TreeNode* pred = sol.inorderPredecessor(root, p);
    
    std::cout << "Predecessor: " << (pred ? pred->val : -1) 
              << ", Successor: " << (succ ? succ->val : -1) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(h)$ where $h$ is the tree's height ($O(\log n)$ balanced, $O(n)$ skewed).
- **Space:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/inorder-successor-in-bst/

## 12. Binary Search Tree Iterator

### Binary Search Tree Iterator
Implement the `BSTIterator` class that represents an iterator over the in-order traversal of a binary search tree. Calling `next()` will return the next smallest number in the BST, and `hasNext()` returns whether a next number exists.

**Intuition:** 
A brute force approach runs a complete inorder traversal during the constructor and stores all elements in an array. This provides $O(1)$ time for `next()`, but consumes $O(n)$ space upfront. The optimal solution simulates the inorder traversal iteratively using a stack, keeping the space bounded to the tree's height. We initialize by pushing the root and all its left descendants onto the stack. When `next()` is called, we pop a node, yield its value, and then push its right child along with all of its left descendants.

```cpp
#include <iostream>
#include <stack>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BSTIterator {
private:
    std::stack<TreeNode*> st;
    
    void pushAll(TreeNode* node) {
        for (; node != nullptr; node = node->left) {
            st.push(node);
        }
    }
    
public:
    BSTIterator(TreeNode* root) {
        pushAll(root);
    }
    
    int next() {
        TreeNode* topNode = st.top();
        st.pop();
        pushAll(topNode->right);
        return topNode->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
};

int main() {
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);
    
    BSTIterator bSTIterator(root);
    std::cout << bSTIterator.next() << "\n"; // Expected 3
    std::cout << bSTIterator.next() << "\n"; // Expected 7
    std::cout << bSTIterator.hasNext() << "\n"; // Expected 1 (true)
    return 0;
}
```

**Complexity:**
- **Time:** $O(1)$ amortized for `next()` and $O(1)$ for `hasNext()`. Pushing left descendants occasionally takes more than $O(1)$ time, but across all nodes, each node is pushed and popped exactly once.
- **Space:** $O(h)$ for the maximum number of nodes stored in the stack at any time.

**Practice:** https://leetcode.com/problems/binary-search-tree-iterator/

## 13. Two Sum in a BST

### Two Sum in a BST
Given the root of a binary search tree and an integer `k`, return `true` if there exist two elements in the BST such that their sum is equal to `k`, or `false` otherwise.

**Intuition:** 
A brute force approach generates an inorder traversal array of size $n$, and uses the standard two-pointer technique on the sorted array in $O(n)$ space. The optimal approach bypasses generating the full array by mimicking the two-pointer technique directly on the tree. We instantiate two custom iterators: one that iterates forward (inorder, yielding smallest to largest) and one that iterates backward (reverse inorder, yielding largest to smallest).

```cpp
#include <iostream>
#include <stack>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BSTIterator {
private:
    std::stack<TreeNode*> st;
    bool reverse; 
    
    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            node = reverse ? node->right : node->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root, bool isReverse) : reverse(isReverse) {
        pushAll(root);
    }
    
    int next() {
        TreeNode* topNode = st.top();
        st.pop();
        pushAll(reverse ? topNode->left : topNode->right);
        return topNode->val;
    }
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (root == nullptr) return false;
        
        BSTIterator l(root, false);
        BSTIterator r(root, true);
        
        int i = l.next();
        int j = r.next();
        
        while (i < j) {
            if (i + j == k) return true;
            if (i + j < k) {
                i = l.next();
            } else {
                j = r.next();
            }
        }
        return false;
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    
    Solution sol;
    std::cout << (sol.findTarget(root, 9) ? "True" : "False") << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(n)$ to traverse elements from both ends.
- **Space:** $O(h)$ because we only maintain two stacks of height $h$.

**Practice:** https://leetcode.com/problems/two-sum-iv-input-is-a-bst/

## 14. Recover a BST — Two Nodes Swapped

### Recover a BST — Two Nodes Swapped
You are given the root of a binary search tree, where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

::: heavy
Because exactly two nodes are swapped, an inorder traversal will yield an almost sorted array containing two anomalies (dips). The challenge is to identify these two offending nodes dynamically during the traversal and swap them back, using $O(h)$ space, or even $O(1)$ space using Morris Traversal.
:::

**Intuition:** 
A brute force approach stores the entire inorder traversal in an array, sorts a copy to find the discrepancies, and patches the tree, requiring $O(n)$ space. The optimal strategy keeps track of a `prev` node pointer as we traverse inorder. Whenever `prev->val > curr->val`, a violation has occurred.
- If it's the first time we see a violation, the swapped nodes might be adjacent. We mark `prev` as the first anomaly (`first`) and `curr` as a candidate for the second (`middle`).
- If we see a second violation later, we mark the new `curr` as the second anomaly (`last`).
At the end, we swap the values of `first` and either `last` (if two distant nodes were swapped) or `middle` (if two adjacent nodes were swapped).

```cpp
#include <iostream>
#include <algorithm>
#include <limits>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* first;
    TreeNode* prev;
    TreeNode* middle;
    TreeNode* last;
    
    void inorder(TreeNode* root) {
        if (root == nullptr) return;
        
        inorder(root->left);
        
        if (prev != nullptr && root->val < prev->val) {
            if (first == nullptr) {
                first = prev;
                middle = root;
            } else {
                last = root;
            }
        }
        prev = root;
        
        inorder(root->right);
    }
    
public:
    void recoverTree(TreeNode* root) {
        first = middle = last = nullptr;
        prev = new TreeNode(std::numeric_limits<int>::min()); 
        
        inorder(root);
        
        if (first && last) {
            std::swap(first->val, last->val);
        } else if (first && middle) {
            std::swap(first->val, middle->val);
        }
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(2);
    
    Solution sol;
    sol.recoverTree(root);
    std::cout << root->right->left->val << "\n"; // Expected 4
    return 0;
}
```

**Complexity:**
- **Time:** $O(n)$ for exploring every node in an inorder traversal.
- **Space:** $O(h)$ for the recursion stack space.

**Practice:** https://leetcode.com/problems/recover-binary-search-tree/

::: interview
**What interviewers look for in BSTs:**
1. **The Inorder Property:** Transforming a "BST problem" into a "sorted array problem" mentally. Interviewers expect you to realize that an inorder traversal yields keys in sorted order.
2. **Cost Model:** Recognizing that BST operations take $O(h)$ time, not strictly $O(\log n)$, unless balanced.
3. **Delete Operation:** Properly swapping the value with the inorder successor/predecessor to gracefully remove a node with two children.
4. **Validation:** Using global `[min, max]` bounds to correctly validate a BST, rejecting the trap of just checking local parent–child relationships.
5. **Practical Use:** Knowing that `std::set` and `std::map` in C++ are implemented as balanced BSTs under the hood and provide the same $O(\log n)$ operations dynamically.
:::
