# Binary Trees

::: heavy
A **binary tree** is a hierarchical data structure where each node has at most two children, referred to as the left child and the right child. Unlike arrays or linked lists, trees are non-linear and represent hierarchical relationships.

![Binary tree terminology: root, parent, child, leaf, height, depth.](../assets/fig_terminology.png)

**Terminology:**
- **Root:** The topmost node in the tree.
- **Parent / Child:** A node is a parent of the nodes connected directly below it (children).
- **Leaf:** A node with no children.
- **Height:** The length of the longest path from a node to a leaf. The height of the tree is the height of the root.
- **Depth:** The length of the path from the root to a node.

![Array vs linked representation of a binary tree.](../assets/fig_representation.png)

**Representation:** Trees can be represented using arrays (commonly used for heaps, where child indices are $2i+1$ and $2i+2$) or using pointers (linked representation), where each node holds pointers to its children. Pointer representation is the most common for arbitrary binary trees.

**Tree Types:**

![A full binary tree.](../assets/fig_fullbt.png)
- **Full Binary Tree:** Every node has either 0 or 2 children.

![A complete binary tree.](../assets/fig_completebt.png)
- **Complete Binary Tree:** All levels are completely filled except possibly the last, which is filled from left to right.

![A perfect binary tree.](../assets/fig_perfectbt.png)
- **Perfect Binary Tree:** All internal nodes have two children and all leaves are at the same level.

![A height-balanced binary tree.](../assets/fig_balancedbt.png)
- **Balanced Binary Tree:** The height of the left and right subtrees of every node differs by at most 1.
- **Degenerate Tree:** Every internal node has exactly one child, making it effectively a linked list.

![The three DFS traversal orders: preorder, inorder, postorder.](../assets/fig_traversals.png)

**Traversals:** 
Tree traversal strategies fall into two categories: Depth-First Search (DFS) and Breadth-First Search (BFS). BFS visits nodes level by level (level-order traversal). DFS explores as far down a branch as possible before backtracking.
:::

::: keypoint
Preorder, inorder, and postorder traversals are all DFS. They differ only by WHERE the current node is processed relative to its children:
- **Preorder:** Node, Left, Right
- **Inorder:** Left, Node, Right
- **Postorder:** Left, Right, Node
:::

## Tree Traversals

### 1. Binary Tree Representation in C++
Building a binary tree using pointer representation requires a node structure. Given an array or sequence of values, the goal is to construct the tree in memory.

**Intuition:** 
Instead of arrays, we use dynamically allocated nodes connected by pointers. The `TreeNode` structure contains the node's value and pointers to its left and right children.

```cpp
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int main() {
    // Constructing a small binary tree:
    //      1
    //     / \
    //    2   3
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    cout << "Root: " << root->val << "\n";
    cout << "Left child: " << root->left->val << "\n";
    cout << "Right child: " << root->right->val << "\n";
    
    // Clean up memory
    delete root->left;
    delete root->right;
    delete root;
    return 0;
}
```

**Complexity:** 
- **Time:** $O(1)$ to create a single node.
- **Space:** $O(1)$ auxiliary space per node.

**Practice:** https://www.geeksforgeeks.org/introduction-to-binary-tree/

### 2. Preorder Traversal
Given the root of a binary tree, return the preorder traversal of its nodes' values.

**Intuition:** 
In preorder traversal, we process the current node first, then recursively traverse the left subtree, and finally recursively traverse the right subtree (Node-Left-Right). 

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    void dfs(TreeNode* node, vector<int>& res) {
        if (!node) return;
        res.push_back(node->val); // Node
        dfs(node->left, res);     // Left
        dfs(node->right, res);    // Right
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        dfs(root, res);
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution sol;
    vector<int> res = sol.preorderTraversal(root);
    for (int x : res) cout << x << " "; // Output: 1 2 3
    
    delete root->right->left;
    delete root->right;
    delete root;
    return 0;
}
```

**Complexity:** 
- **Time:** $O(n)$ because each node is visited exactly once.
- **Space:** $O(h)$ where $h$ is the height of the tree, representing the maximum depth of the call stack (worst-case $O(n)$, average $O(\log n)$).

**Practice:** https://leetcode.com/problems/binary-tree-preorder-traversal/

### 3. Inorder Traversal
Given the root of a binary tree, return the inorder traversal of its nodes' values.

**Intuition:** 
In inorder traversal, we first recursively traverse the left subtree, process the current node, and then recursively traverse the right subtree (Left-Node-Right). For a Binary Search Tree (BST), this visits the nodes in sorted order.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    void dfs(TreeNode* node, vector<int>& res) {
        if (!node) return;
        dfs(node->left, res);     // Left
        res.push_back(node->val); // Node
        dfs(node->right, res);    // Right
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        dfs(root, res);
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution sol;
    vector<int> res = sol.inorderTraversal(root);
    for (int x : res) cout << x << " "; // Output: 1 3 2
    
    delete root->right->left;
    delete root->right;
    delete root;
    return 0;
}
```

**Complexity:** 
- **Time:** $O(n)$ to visit each node once.
- **Space:** $O(h)$ for the recursion stack space, where $h$ is the height of the tree.

**Practice:** https://leetcode.com/problems/binary-tree-inorder-traversal/

### 4. Postorder Traversal
Given the root of a binary tree, return the postorder traversal of its nodes' values.

**Intuition:** 
In postorder traversal, we recursively traverse the left subtree, then the right subtree, and finally process the current node (Left-Right-Node). This is often used when we need to gather information from children before resolving the parent (e.g., computing height).

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    void dfs(TreeNode* node, vector<int>& res) {
        if (!node) return;
        dfs(node->left, res);     // Left
        dfs(node->right, res);    // Right
        res.push_back(node->val); // Node
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        dfs(root, res);
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution sol;
    vector<int> res = sol.postorderTraversal(root);
    for (int x : res) cout << x << " "; // Output: 3 2 1
    
    delete root->right->left;
    delete root->right;
    delete root;
    return 0;
}
```

**Complexity:** 
- **Time:** $O(n)$ as every node is visited once.
- **Space:** $O(h)$ for the recursion stack.

**Practice:** https://leetcode.com/problems/binary-tree-postorder-traversal/

### 5. Level Order Traversal / BFS

::: keypoint
Whenever processing a tree level by level, capture `size = queue.size()` at the start of the loop to isolate nodes of the current level.
:::

Given the root of a binary tree, return the level order traversal of its nodes' values (i.e., from left to right, level by level).

**Intuition:** 
Instead of going deep (DFS), we want to visit nodes layer by layer. We achieve this Breadth-First Search (BFS) using a Queue. We start by pushing the root into the queue. While the queue is not empty, we determine the current level's size, pop that many nodes, record their values, and push their children for the next level.

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            res.push_back(level);
        }
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    Solution sol;
    vector<vector<int>> res = sol.levelOrder(root);
    for (const auto& level : res) {
        for (int x : level) cout << x << " ";
        cout << "| ";
    }
    // Output: 3 | 9 20 | 15 7 | 
    return 0;
}
```

**Complexity:** 
- **Time:** $O(n)$ because each node is enqueued and dequeued exactly once.
- **Space:** $O(n)$ due to the queue holding at most the maximum number of nodes in a level (which can be $n/2$ in a perfect tree).

**Practice:** https://leetcode.com/problems/binary-tree-level-order-traversal/

### 6. Iterative Preorder Traversal
Given the root of a binary tree, return its preorder traversal iteratively (without recursion).

**Intuition:** 
Recursion uses the call stack implicitly. To convert it to an iterative approach, we use our own `stack`. For preorder (Node-Left-Right), we process the node, then we want to process the left subtree before the right subtree. Since a stack is LIFO (Last-In, First-Out), we must push the right child FIRST, then the left child, so the left child is popped and processed first.

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        
        stack<TreeNode*> st;
        st.push(root);
        
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            res.push_back(node->val);
            
            // Push right first so left is processed first
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution sol;
    vector<int> res = sol.preorderTraversal(root);
    for (int x : res) cout << x << " "; // Output: 1 2 3
    return 0;
}
```

**Complexity:** 
- **Time:** $O(n)$ to process each node.
- **Space:** $O(h)$ for the stack holding paths, where $h$ is the height.

**Practice:** https://leetcode.com/problems/binary-tree-preorder-traversal/

### 7. Iterative Inorder Traversal
Given the root of a binary tree, return its inorder traversal iteratively.

**Intuition:** 
In inorder (Left-Node-Right), we must traverse as far left as possible before processing a node. We use a stack and a current pointer. We push nodes while moving left. When we hit a null, it means there are no more left children. We pop from the stack, process the node, and then shift our current pointer to its right child to explore that subtree.

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> st;
        TreeNode* curr = root;
        
        while (curr != nullptr || !st.empty()) {
            if (curr != nullptr) {
                // Keep going left
                st.push(curr);
                curr = curr->left;
            } else {
                // Reached leftmost, process node and go right
                curr = st.top();
                st.pop();
                res.push_back(curr->val);
                curr = curr->right;
            }
        }
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution sol;
    vector<int> res = sol.inorderTraversal(root);
    for (int x : res) cout << x << " "; // Output: 1 3 2
    return 0;
}
```

**Complexity:** 
- **Time:** $O(n)$ to visit all nodes.
- **Space:** $O(h)$ for the stack.

**Practice:** https://leetcode.com/problems/binary-tree-inorder-traversal/

### 8. Iterative Postorder Traversal using two stacks
Given the root of a binary tree, return its postorder traversal iteratively using two stacks.

**Intuition:** 
Postorder is Left-Right-Node. If we generate Node-Right-Left and then reverse it, we get Left-Right-Node. A preorder traversal is Node-Left-Right. By swapping the order we push children (push left, then right), we generate Node-Right-Left. We push these nodes into a second stack (which inherently reverses them), yielding the exact postorder traversal when popped.

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        
        stack<TreeNode*> st1, st2;
        st1.push(root);
        
        while (!st1.empty()) {
            TreeNode* node = st1.top();
            st1.pop();
            st2.push(node);
            
            if (node->left) st1.push(node->left);
            if (node->right) st1.push(node->right);
        }
        
        while (!st2.empty()) {
            res.push_back(st2.top()->val);
            st2.pop();
        }
        
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution sol;
    vector<int> res = sol.postorderTraversal(root);
    for (int x : res) cout << x << " "; // Output: 3 2 1
    return 0;
}
```

**Complexity:** 
- **Time:** $O(n)$ to visit all nodes.
- **Space:** $O(n)$ due to `st2` storing all the nodes.

**Practice:** https://leetcode.com/problems/binary-tree-postorder-traversal/

### 9. Iterative Postorder Traversal using one stack
Given the root of a binary tree, return its postorder traversal iteratively using only one stack.

**Intuition:** 
Using one stack is harder because when we return from a child, we need to know whether we just came from the left or right child. We traverse down the left as far as possible. When we can't go left, we check the right child of the top node. If it's non-null and hasn't been processed, we move to it. Otherwise, we process the node and keep track of it as the last processed node so we don't traverse its right child again.

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> st;
        TreeNode* curr = root;
        TreeNode* lastProcessed = nullptr;
        
        while (curr != nullptr || !st.empty()) {
            if (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            } else {
                TreeNode* peekNode = st.top();
                // If right child exists and hasn't been processed yet
                if (peekNode->right != nullptr && lastProcessed != peekNode->right) {
                    curr = peekNode->right;
                } else {
                    res.push_back(peekNode->val);
                    lastProcessed = peekNode;
                    st.pop();
                }
            }
        }
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution sol;
    vector<int> res = sol.postorderTraversal(root);
    for (int x : res) cout << x << " "; // Output: 3 2 1
    return 0;
}
```

**Complexity:** 
- **Time:** $O(n)$ to visit nodes.
- **Space:** $O(h)$ for the stack.

**Practice:** https://leetcode.com/problems/binary-tree-postorder-traversal/

### 10. Preorder, Inorder and Postorder in a Single Traversal
Given the root of a binary tree, produce all three depth-first traversals in one iterative pass.

**Intuition:** 
We can view DFS as a state machine for each node. When we visit a node for the first time, it's the preorder step (state 1). After exploring its left subtree, we visit it a second time for the inorder step (state 2). After exploring its right subtree, we visit it a third time for the postorder step (state 3) and pop it. We can store pairs of `{TreeNode*, int state}` in a stack.

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> allTraversals(TreeNode* root) {
        vector<int> pre, in, post;
        if (!root) return {pre, in, post};
        
        // stack of pair<TreeNode*, state>
        stack<pair<TreeNode*, int>> st;
        st.push({root, 1});
        
        while (!st.empty()) {
            auto& [node, state] = st.top();
            
            if (state == 1) {
                // Preorder: process node, increment state, go left
                pre.push_back(node->val);
                state++;
                if (node->left) st.push({node->left, 1});
            } 
            else if (state == 2) {
                // Inorder: process node, increment state, go right
                in.push_back(node->val);
                state++;
                if (node->right) st.push({node->right, 1});
            } 
            else {
                // Postorder: process node, pop from stack
                post.push_back(node->val);
                st.pop();
            }
        }
        
        return {pre, in, post};
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    Solution sol;
    vector<vector<int>> res = sol.allTraversals(root);
    
    cout << "Preorder: ";
    for (int x : res[0]) cout << x << " ";
    cout << "\nInorder: ";
    for (int x : res[1]) cout << x << " ";
    cout << "\nPostorder: ";
    for (int x : res[2]) cout << x << " ";
    
    return 0;
}
```

**Complexity:** 
- **Time:** $O(n)$ as we visit each node 3 times.
- **Space:** $O(h)$ for the stack.

**Practice:** https://www.naukri.com/code360/problems/tree-traversals_981269

## Medium Binary Tree Problems

### 1. Height / Maximum Depth of a Binary Tree
Statement: Given the root of a binary tree, return its maximum depth. The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

![Computing the height of a binary tree bottom-up.](../assets/fig_maxdepth.png)

**Intuition / approach**:
The maximum depth of a binary tree can be defined recursively. A tree's maximum depth is $1$ plus the maximum of the depths of its left and right subtrees. We can use a simple Depth-First Search (DFS) or postorder traversal. We traverse down to the leaves and compute the height bottom-up.

::: keypoint
The height of an empty tree (a `nullptr` node) is $0$. This acts as the base case for our recursion.
:::

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        
        return 1 + max(leftDepth, rightDepth);
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    Solution sol;
    cout << "Max depth: " << sol.maxDepth(root) << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N)$ where $N$ is the number of nodes, as we visit each node exactly once.
- **Space Complexity:** $O(H)$ where $H$ is the height of the tree (for the recursion stack). In the worst case (skewed tree), this is $O(N)$.

**Practice:** https://leetcode.com/problems/maximum-depth-of-binary-tree/

### 2. Check if a Binary Tree is Height-Balanced
Statement: Given a binary tree, determine if it is height-balanced. A height-balanced binary tree is a binary tree in which the left and right subtrees of every node differ in height by no more than $1$.

![Checking height-balance in one bottom-up pass.](../assets/fig_balanced_check.png)

**Intuition / approach**:
- **Brute force:** For every node, compute the height of its left and right subtrees and check if their difference is at most $1$. Since computing height takes $O(N)$ and we do it for each of the $N$ nodes, this takes $O(N^2)$ time.
- **Optimal:** We can optimize by checking the balance condition while computing the height. We use a bottom-up DFS (postorder traversal). If a subtree is unbalanced, we return $-1$ (or another sentinel value) to indicate failure. Otherwise, we return the actual height of the subtree. If the recursion ever returns $-1$, we propagate it immediately to the root.

::: keypoint
Returning $-1$ as an error code lets a single recursive function compute the height AND flag imbalances simultaneously, reducing $O(N^2)$ to $O(N)$.
:::

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    int checkBalance(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        
        int leftHeight = checkBalance(root->left);
        if (leftHeight == -1) return -1;
        
        int rightHeight = checkBalance(root->right);
        if (rightHeight == -1) return -1;
        
        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        
        return 1 + max(leftHeight, rightHeight);
    }
    
public:
    bool isBalanced(TreeNode* root) {
        return checkBalance(root) != -1;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    
    Solution sol;
    cout << "Is balanced: " << (sol.isBalanced(root) ? "true" : "false") << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N)$ because every node is visited exactly once.
- **Space Complexity:** $O(H)$ for the recursion stack space, where $H$ is the height of the tree.

**Practice:** https://leetcode.com/problems/balanced-binary-tree/

### 3. Diameter of a Binary Tree
Statement: Given the root of a binary tree, return the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

**Intuition / approach**:
- **Brute force:** The longest path passing through a node is the sum of the heights of its left and right subtrees. We could compute this for every node ($O(N^2)$).
- **Optimal:** We can find the diameter during a bottom-up DFS (postorder). As we compute the height of the left and right subtrees for a node, the longest path passing through that node is simply `leftHeight + rightHeight`. We maintain a global or reference variable to track the maximum of these paths across all nodes.

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    int height(TreeNode* root, int& diameter) {
        if (root == nullptr) {
            return 0;
        }
        
        int leftHeight = height(root->left, diameter);
        int rightHeight = height(root->right, diameter);
        
        // Update the maximum diameter found so far
        diameter = max(diameter, leftHeight + rightHeight);
        
        return 1 + max(leftHeight, rightHeight);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        height(root, diameter);
        return diameter;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    Solution sol;
    cout << "Diameter: " << sol.diameterOfBinaryTree(root) << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N)$ as each node is visited once during the postorder traversal.
- **Space Complexity:** $O(H)$ for the recursion stack, where $H$ is the height of the tree.

**Practice:** https://leetcode.com/problems/diameter-of-binary-tree/

### 4. Maximum Path Sum
Statement: Given a non-empty binary tree, find the maximum path sum. A path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

::: heavy
Unlike the diameter problem, node values can be negative. We must decide whether to include a subtree's path or ignore it entirely (by taking $0$ instead of a negative sum). A path can also "turn" at a node, meaning the node is the highest point of that path.
:::

**Intuition / approach**:
We use a bottom-up DFS. For any node, a path has two choices:
1. It forms a curve (an arch) passing through the node and going down into both the left and right subtrees. This sum is `node->val + leftMaxPath + rightMaxPath`. This is a candidate for the global maximum path sum.
2. It continues straight up to the node's parent. For this, it can only include ONE of the subtrees (either left or right). This sum is `node->val + max(leftMaxPath, rightMaxPath)`.

To handle negative sums, if a subtree yields a negative maximum path, it's better not to include it at all. We take `max(0, subtreeMaxPath)`.

```cpp
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    int findMaxPath(TreeNode* root, int& maxi) {
        if (root == nullptr) {
            return 0;
        }
        
        // Ignore paths with negative sums
        int leftMaxPath = max(0, findMaxPath(root->left, maxi));
        int rightMaxPath = max(0, findMaxPath(root->right, maxi));
        
        // Update the global maximum if the path "turns" at this node
        maxi = max(maxi, root->val + leftMaxPath + rightMaxPath);
        
        // Return the maximum path sum moving upward to the parent
        return root->val + max(leftMaxPath, rightMaxPath);
    }
    
public:
    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN;
        findMaxPath(root, maxi);
        return maxi;
    }
};

int main() {
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    Solution sol;
    cout << "Max path sum: " << sol.maxPathSum(root) << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N)$ because every node is visited exactly once.
- **Space Complexity:** $O(H)$ for the recursion stack.

**Practice:** https://leetcode.com/problems/binary-tree-maximum-path-sum/

### 5. Check if Two Trees are Identical
Statement: Given the roots of two binary trees `p` and `q`, write a function to check if they are the same or not. Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

**Intuition / approach**:
We can solve this recursively by traversing both trees simultaneously.
- If both nodes are `nullptr`, they are identical up to that point.
- If one is `nullptr` and the other is not, or if their values differ, they are not identical.
- Otherwise, we recursively check if their left subtrees are identical and their right subtrees are identical.

```cpp
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Both are null
        if (p == nullptr && q == nullptr) return true;
        
        // One is null or values differ
        if (p == nullptr || q == nullptr || p->val != q->val) return false;
        
        // Recursively check left and right subtrees
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

int main() {
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);
    
    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);
    
    Solution sol;
    cout << "Are identical: " << (sol.isSameTree(p, q) ? "true" : "false") << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N)$ where $N$ is the number of nodes in the smaller tree, since we stop as soon as we find a mismatch.
- **Space Complexity:** $O(H)$ where $H$ is the minimum height of the two trees, for the recursion stack.

**Practice:** https://leetcode.com/problems/same-tree/

### 6. Zig-Zag / Spiral Level Order Traversal
Statement: Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

**Intuition / approach**:
This is a variation of Level Order Traversal (BFS). We use a queue to traverse the tree level by level. We maintain a boolean flag `leftToRight`.
- When processing a level, we create a temporary array/vector for that level's nodes.
- If `leftToRight` is true, we insert nodes into the vector from left to right.
- If `leftToRight` is false, we insert nodes into the vector from right to left (by calculating the insertion index as `size - 1 - i`).
- After completing a level, we toggle the flag.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size);
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Determine the correct position based on the flag
                int index = leftToRight ? i : (size - 1 - i);
                level[index] = node->val;
                
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            
            // Toggle the flag for the next level
            leftToRight = !leftToRight;
            result.push_back(level);
        }
        
        return result;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    Solution sol;
    vector<vector<int>> res = sol.zigzagLevelOrder(root);
    
    for (const auto& level : res) {
        for (int val : level) cout << val << " ";
        cout << endl;
    }
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N)$ since each node is processed exactly once.
- **Space Complexity:** $O(N)$ to store the nodes in the queue, which at most holds the nodes of the widest level.

**Practice:** https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

### 7. Boundary Traversal of a Binary Tree
Statement: Given a binary tree, print boundary nodes of the binary tree Anti-Clockwise starting from the root. The boundary includes left boundary, leaves, and right boundary in order without duplicate nodes.

**Intuition / approach**:
The traversal can be divided into three parts:
1. **Left Boundary:** Traverse the left boundary excluding the leaf nodes. We go left if possible; otherwise, we go right.
2. **Leaf Nodes:** Traverse all the leaf nodes from left to right using a simple inorder or preorder traversal.
3. **Right Boundary:** Traverse the right boundary excluding the leaf nodes in reverse order. We go right if possible; otherwise, we go left. We collect these nodes and reverse them (or use a stack) before adding them to the result.

The root node is handled separately to avoid duplication if it is a leaf.

```cpp
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    bool isLeaf(TreeNode* root) {
        return root->left == nullptr && root->right == nullptr;
    }
    
    void addLeftBoundary(TreeNode* root, vector<int>& res) {
        TreeNode* curr = root->left;
        while (curr) {
            if (!isLeaf(curr)) res.push_back(curr->val);
            if (curr->left) curr = curr->left;
            else curr = curr->right;
        }
    }
    
    void addRightBoundary(TreeNode* root, vector<int>& res) {
        TreeNode* curr = root->right;
        vector<int> temp;
        while (curr) {
            if (!isLeaf(curr)) temp.push_back(curr->val);
            if (curr->right) curr = curr->right;
            else curr = curr->left;
        }
        // Add right boundary in reverse order
        for (int i = temp.size() - 1; i >= 0; --i) {
            res.push_back(temp[i]);
        }
    }
    
    void addLeaves(TreeNode* root, vector<int>& res) {
        if (isLeaf(root)) {
            res.push_back(root->val);
            return;
        }
        if (root->left) addLeaves(root->left, res);
        if (root->right) addLeaves(root->right, res);
    }

public:
    vector<int> printBoundary(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
        
        if (!isLeaf(root)) res.push_back(root->val);
        
        addLeftBoundary(root, res);
        addLeaves(root, res);
        addRightBoundary(root, res);
        
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(8);
    root->right->right = new TreeNode(6);
    root->right->right->left = new TreeNode(9);
    root->right->right->right = new TreeNode(10);
    
    Solution sol;
    vector<int> res = sol.printBoundary(root);
    for (int val : res) cout << val << " ";
    cout << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N)$ since the left boundary, right boundary, and leaf traversals each take $O(H)$ or $O(N)$ time, making the total time linear.
- **Space Complexity:** $O(H)$ for the recursion stack during the leaf traversal, plus the space for the output array.

**Practice:** https://leetcode.com/problems/boundary-of-binary-tree/

### 8. Vertical Order Traversal
Statement: Given the root of a binary tree, calculate the vertical order traversal of the binary tree. For each node at position `(row, col)`, its left and right children will be at positions `(row + 1, col - 1)` and `(row + 1, col + 1)` respectively. Nodes sharing the same row and column should be sorted by their values.

**Intuition / approach**:
We need to track the `(row, col)` coordinates of every node. 
- Use a BFS queue holding `pair<TreeNode*, pair<int, int>>` which represents `{node, {row, col}}`.
- Use a `map<int, map<int, multiset<int>>>` to store the nodes. The outer map keys on the column (vertical line), the inner map keys on the row (level), and the multiset automatically sorts the values if they share the exact same row and column.
- After the BFS, iterate through the map and construct the result.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) return result;
        
        // map<col, map<row, multiset<val>>>
        map<int, map<int, multiset<int>>> nodes;
        // queue<pair<node, pair<row, col>>>
        queue<pair<TreeNode*, pair<int, int>>> q;
        
        q.push({root, {0, 0}});
        
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            
            TreeNode* node = p.first;
            int row = p.second.first;
            int col = p.second.second;
            
            nodes[col][row].insert(node->val);
            
            if (node->left) q.push({node->left, {row + 1, col - 1}});
            if (node->right) q.push({node->right, {row + 1, col + 1}});
        }
        
        for (auto& p : nodes) {
            vector<int> col_vals;
            for (auto& q : p.second) {
                col_vals.insert(col_vals.end(), q.second.begin(), q.second.end());
            }
            result.push_back(col_vals);
        }
        
        return result;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    Solution sol;
    vector<vector<int>> res = sol.verticalTraversal(root);
    for (const auto& col : res) {
        for (int val : col) cout << val << " ";
        cout << endl;
    }
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N \log N)$ where $N$ is the number of nodes. The `multiset` insertion and map operations take logarithmic time.
- **Space Complexity:** $O(N)$ for the queue and the maps.

**Practice:** https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/

### 9. Top View of a Binary Tree
Statement: Given below is a binary tree. The task is to print the top view of the binary tree. Top view of a binary tree is the set of nodes visible when the tree is viewed from the top.

**Intuition / approach**:
The top view contains the first node encountered at each vertical column. 
- We can perform a BFS (Level Order Traversal) keeping track of the vertical distance (column).
- We use a map (`map<int, int>`) where the key is the column and the value is the node's data. 
- If the column is NOT already in the map, we add the node to the map. Because we use BFS, the first node we encounter at a column is guaranteed to be the topmost node.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> topView(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) return ans;
        
        // map<col, val>
        map<int, int> mpp;
        // queue<pair<node, col>>
        queue<pair<TreeNode*, int>> q;
        
        q.push({root, 0});
        
        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            
            TreeNode* node = it.first;
            int col = it.second;
            
            // If this is the first node we see at this column, record it
            if (mpp.find(col) == mpp.end()) {
                mpp[col] = node->val;
            }
            
            if (node->left) q.push({node->left, col - 1});
            if (node->right) q.push({node->right, col + 1});
        }
        
        for (auto it : mpp) {
            ans.push_back(it.second);
        }
        
        return ans;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->left->right->right = new TreeNode(5);
    root->left->right->right->right = new TreeNode(6);
    
    Solution sol;
    vector<int> res = sol.topView(root);
    for (int val : res) cout << val << " ";
    cout << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N \log N)$ where $N$ is the number of nodes (due to map insertions, though it can be $O(N)$ with an unordered_map combined with min/max tracking).
- **Space Complexity:** $O(N)$ for the queue and the map.

**Practice:** https://www.geeksforgeeks.org/problems/top-view-of-binary-tree/1

### 10. Bottom View of a Binary Tree
Statement: Given a binary tree, print the bottom view from left to right. A node is included in the bottom view if it can be seen when we look at the tree from the bottom.

**Intuition / approach**:
This is nearly identical to the Top View problem. The difference is that we want the *last* node at each vertical column rather than the first.
- We perform a BFS traversal.
- For each node at a column, we continually overwrite the value in the map for that column. By the end of the BFS, the map will hold the last visited node (the bottom-most node) for each column.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> bottomView(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) return ans;
        
        // map<col, val>
        map<int, int> mpp;
        // queue<pair<node, col>>
        queue<pair<TreeNode*, int>> q;
        
        q.push({root, 0});
        
        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            
            TreeNode* node = it.first;
            int col = it.second;
            
            // Constantly overwrite to keep the latest (bottom-most) node
            mpp[col] = node->val;
            
            if (node->left) q.push({node->left, col - 1});
            if (node->right) q.push({node->right, col + 1});
        }
        
        for (auto it : mpp) {
            ans.push_back(it.second);
        }
        
        return ans;
    }
};

int main() {
    TreeNode* root = new TreeNode(20);
    root->left = new TreeNode(8);
    root->right = new TreeNode(22);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(25);
    root->left->right->left = new TreeNode(10);
    root->left->right->right = new TreeNode(14);
    
    Solution sol;
    vector<int> res = sol.bottomView(root);
    for (int val : res) cout << val << " ";
    cout << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N \log N)$ due to map operations.
- **Space Complexity:** $O(N)$ for the queue and map.

**Practice:** https://www.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1

### 11. Right / Left View of a Binary Tree
Statement: Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom. (The Left View is the equivalent from the left side).

**Intuition / approach**:
- **BFS approach:** Traverse level by level. For a right view, push the *last* node of each level into the result. For a left view, push the *first* node.
- **DFS approach (Optimal):** We can use a modified preorder traversal. For a right view, we visit the `right` child before the `left` child. We keep track of the current depth. If the current depth equals the size of our result vector, it means we are seeing the first node of a new level, so we add it to the result.

```cpp
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    void recursion(TreeNode* root, int level, vector<int>& res) {
        if (root == nullptr) return;
        
        // If we visit this level for the first time, add the node
        if (res.size() == level) {
            res.push_back(root->val);
        }
        
        // Traverse right first for the Right View
        recursion(root->right, level + 1, res);
        // Traverse left
        recursion(root->left, level + 1, res);
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        recursion(root, 0, res);
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);
    
    Solution sol;
    vector<int> res = sol.rightSideView(root);
    for (int val : res) cout << val << " ";
    cout << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N)$ as we visit every node exactly once.
- **Space Complexity:** $O(H)$ for the recursion stack space, where $H$ is the height of the tree.

**Practice:** https://leetcode.com/problems/binary-tree-right-side-view/

### 12. Check for Symmetric Binary Tree
Statement: Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

**Intuition / approach**:
A tree is symmetric if the left subtree is a mirror reflection of the right subtree.
Two trees are a mirror reflection of each other if:
1. Their root node values are the same.
2. The right subtree of each tree is a mirror reflection of the left subtree of the other tree.

We can solve this recursively. We pass the left child and right child of the root to a helper function. At each step, we compare the left node's value with the right node's value. Then we recursively compare the left node's left child with the right node's right child, and the left node's right child with the right node's left child.

```cpp
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    bool isMirror(TreeNode* leftNode, TreeNode* rightNode) {
        // If both are null, they are symmetric
        if (leftNode == nullptr && rightNode == nullptr) return true;
        // If one is null or their values differ, they are not symmetric
        if (leftNode == nullptr || rightNode == nullptr || leftNode->val != rightNode->val) {
            return false;
        }
        
        // Compare outer pairs and inner pairs
        return isMirror(leftNode->left, rightNode->right) && 
               isMirror(leftNode->right, rightNode->left);
    }
    
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return isMirror(root->left, root->right);
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);
    
    Solution sol;
    cout << "Is symmetric: " << (sol.isSymmetric(root) ? "true" : "false") << endl;
    return 0;
}
```

**Complexity**: 
- **Time Complexity:** $O(N)$ because we traverse the entire tree once in the worst case.
- **Space Complexity:** $O(H)$ where $H$ is the tree's height, for the recursion stack.

**Practice:** https://leetcode.com/problems/symmetric-tree/

## Hard Binary Tree Problems

### Root-to-Node Path in a Binary Tree
Given a binary tree and a target node value, find the path from the root down to the target node. Return the sequence of values.

**Intuition / approach**: 
A standard brute force approach might search for the node and then try to reconstruct the path, but the optimal approach does this in one pass using Depth-First Search (DFS). We maintain the current path in an array as we recurse downward. If a node matches the target, we have found our path. If neither the left nor right subtrees contain the target, the current node cannot be part of the path, so we backtrack by popping it from the array and returning false.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    bool getPath(TreeNode* root, vector<int>& path, int target) {
        if (!root) return false;
        
        path.push_back(root->val);
        if (root->val == target) return true;
        
        if (getPath(root->left, path, target) || getPath(root->right, path, target)) {
            return true;
        }
        
        path.pop_back();
        return false;
    }
public:
    vector<int> solve(TreeNode* root, int target) {
        vector<int> path;
        getPath(root, path, target);
        return path;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    Solution sol;
    vector<int> path = sol.solve(root, 5);
    for (int v : path) cout << v << " ";
    return 0;
}
```

**Complexity**: Time $O(n)$ where $n$ is the number of nodes, as we visit each node at most once. Space $O(h)$ where $h$ is the height of the tree, for the recursion stack and the path array.

**Practice:** https://www.interviewbit.com/problems/path-to-given-node/

### Lowest Common Ancestor (LCA) of a Binary Tree

::: keypoint
The Lowest Common Ancestor (LCA) of two nodes $p$ and $q$ is the lowest node in the tree that has both $p$ and $q$ as descendants. A node is allowed to be a descendant of itself.
:::

Given a binary tree, find the lowest common ancestor of two given nodes in the tree.

**Intuition / approach**: 
A naive approach would find the root-to-node path for both nodes and compare the paths to find the last common node. A more optimal approach is to traverse the tree bottom-up using DFS. If the current node is either $p$ or $q$, we return the current node. Otherwise, we recursively search the left and right subtrees. If both the left and right subtrees return a non-null node, it means $p$ and $q$ are in different subtrees of the current node, making the current node their LCA. If only one subtree returns a non-null node, we propagate that result upwards.

```cpp
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) {
            return root;
        }
        
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        if (left && right) {
            return root;
        }
        return left ? left : right;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    TreeNode* p = root->left = new TreeNode(5);
    TreeNode* q = root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    
    Solution sol;
    TreeNode* lca = sol.lowestCommonAncestor(root, p, q);
    if (lca) cout << lca->val << "\n";
    return 0;
}
```

**Complexity**: Time $O(n)$ because we do a single pass DFS covering all nodes in the worst case. Space $O(h)$ auxiliary stack space for the recursion, where $h$ is the height of the tree.

**Practice:** https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

### Maximum Width of a Binary Tree
The width of a level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes are also counted. Find the maximum width among all levels.

**Intuition / approach**: 
To measure the width correctly including null nodes, we can assign an index to each node. If a parent has index $i$, its left child has index $2i + 1$ and its right child has index $2i + 2$ (0-indexed). The width of a level is simply `last_node_index - first_node_index + 1`. We use a level-order traversal (BFS) with a queue that stores pairs of `(TreeNode*, index)`. To prevent integer overflow for skewed trees, we normalize indices at each level by subtracting the minimum index of that level (the index of the first node).

```cpp
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int maxWidth = 0;
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 0});
        
        while (!q.empty()) {
            int size = q.size();
            unsigned long long minIndex = q.front().second;
            unsigned long long first, last;
            
            for (int i = 0; i < size; ++i) {
                unsigned long long curIndex = q.front().second - minIndex;
                TreeNode* node = q.front().first;
                q.pop();
                
                if (i == 0) first = curIndex;
                if (i == size - 1) last = curIndex;
                
                if (node->left) q.push({node->left, curIndex * 2 + 1});
                if (node->right) q.push({node->right, curIndex * 2 + 2});
            }
            maxWidth = max(maxWidth, static_cast<int>(last - first + 1));
        }
        return maxWidth;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(9);
    
    Solution sol;
    cout << sol.widthOfBinaryTree(root) << "\n";
    return 0;
}
```

**Complexity**: Time $O(n)$ as we visit every node once using BFS. Space $O(n)$ since the queue can hold at most $n/2$ nodes at the widest level.

**Practice:** https://leetcode.com/problems/maximum-width-of-a-binary-tree/

### Check for Children-Sum Property
Given a binary tree, determine if the tree satisfies the Children-Sum Property. The property states that for every node, its value must be equal to the sum of the values of its left and right children. Leaf nodes automatically satisfy this property.

**Intuition / approach**: 
We traverse the tree using DFS. For any node, we calculate the sum of its children's values. If it matches the node's value, we recursively check its left and right subtrees. The tree is valid if both subtrees are valid and the current node satisfies the condition. A base case is when the tree is empty or the node is a leaf, both of which are valid by definition.

```cpp
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isSumProperty(TreeNode* root) {
        if (!root) return true;
        if (!root->left && !root->right) return true;
        
        int sum = 0;
        if (root->left) sum += root->left->val;
        if (root->right) sum += root->right->val;
        
        return (root->val == sum) 
            && isSumProperty(root->left) 
            && isSumProperty(root->right);
    }
};

int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(4);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(4);
    
    Solution sol;
    cout << (sol.isSumProperty(root) ? "true" : "false") << "\n";
    return 0;
}
```

**Complexity**: Time $O(n)$ as each node is visited once during the traversal. Space $O(h)$ for the recursion stack.

**Practice:** https://www.geeksforgeeks.org/problems/children-sum-parent/1

### Print All Nodes at Distance K
Given the root of a binary tree, a target node, and an integer $k$, return an array of the values of all nodes that have a distance $k$ from the target node.

**Intuition / approach**: 
A binary tree normally only has downward pointers, so from a target node, we can easily find descendants at distance $k$. However, we also need to move upwards to ancestors and their other subtrees. We first perform an initial BFS or DFS to map each node to its parent, essentially converting the tree into an undirected graph. Then, starting from the target node, we perform a BFS radially outwards, keeping track of visited nodes. Once we complete $k$ levels of BFS, the nodes currently in the queue are exactly at distance $k$.

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    void markParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parentTrack) {
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            if (curr->left) {
                parentTrack[curr->left] = curr;
                q.push(curr->left);
            }
            if (curr->right) {
                parentTrack[curr->right] = curr;
                q.push(curr->right);
            }
        }
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<TreeNode*, TreeNode*> parentTrack;
        markParents(root, parentTrack);
        
        unordered_map<TreeNode*, bool> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited[target] = true;
        int curr_level = 0;
        
        while (!q.empty()) {
            if (curr_level == k) break;
            curr_level++;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* curr = q.front();
                q.pop();
                
                if (curr->left && !visited[curr->left]) {
                    q.push(curr->left);
                    visited[curr->left] = true;
                }
                if (curr->right && !visited[curr->right]) {
                    q.push(curr->right);
                    visited[curr->right] = true;
                }
                if (parentTrack[curr] && !visited[parentTrack[curr]]) {
                    q.push(parentTrack[curr]);
                    visited[parentTrack[curr]] = true;
                }
            }
        }
        
        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front()->val);
            q.pop();
        }
        return result;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    TreeNode* target = root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    
    Solution sol;
    vector<int> res = sol.distanceK(root, target, 2);
    for (int v : res) cout << v << " ";
    return 0;
}
```

**Complexity**: Time $O(n)$ for mapping parents and the subsequent BFS traversal. Space $O(n)$ for the parent map, visited map, and BFS queue.

**Practice:** https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/

### Minimum Time to Burn the Binary Tree
Given a binary tree and a start node (leaf or internal), find the minimum time required to burn the complete binary tree. The fire spreads to adjacent nodes (parent, left child, right child) in 1 unit of time.

**Intuition / approach**: 
This is fundamentally identical to finding the maximum distance from a given target node to any other node in the tree. Like the "nodes at distance $k$" problem, we first traverse the tree to build a parent mapping. Next, starting from the given start node, we perform BFS in all three directions (left, right, parent). Every level of BFS expansion represents 1 unit of time. We count how many levels it takes until the queue becomes empty.

```cpp
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    TreeNode* mapParentsAndFindTarget(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& mpp, int start) {
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* res = nullptr;
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            if (node->val == start) res = node;
            if (node->left) {
                mpp[node->left] = node;
                q.push(node->left);
            }
            if (node->right) {
                mpp[node->right] = node;
                q.push(node->right);
            }
        }
        return res;
    }
public:
    int minTime(TreeNode* root, int start) {
        unordered_map<TreeNode*, TreeNode*> mpp;
        TreeNode* target = mapParentsAndFindTarget(root, mpp, start);
        if (!target) return 0;
        
        unordered_map<TreeNode*, int> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited[target] = 1;
        int time = 0;
        
        while (!q.empty()) {
            int size = q.size();
            bool burned = false;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node->left && !visited[node->left]) {
                    q.push(node->left);
                    visited[node->left] = 1;
                    burned = true;
                }
                if (node->right && !visited[node->right]) {
                    q.push(node->right);
                    visited[node->right] = 1;
                    burned = true;
                }
                if (mpp[node] && !visited[mpp[node]]) {
                    q.push(mpp[node]);
                    visited[mpp[node]] = 1;
                    burned = true;
                }
            }
            if (burned) time++;
        }
        return time;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->left->right = new TreeNode(7);
    
    Solution sol;
    cout << sol.minTime(root, 7) << "\n";
    return 0;
}
```

**Complexity**: Time $O(n)$ to build the parent map and traverse the tree layer-by-layer. Space $O(n)$ to store parents and visited nodes.

**Practice:** https://www.geeksforgeeks.org/problems/burning-tree/1

### Count Total Nodes in a Complete Binary Tree

::: keypoint
A complete binary tree has all levels fully filled except possibly the last level, which is filled from left to right. We can leverage this property by comparing the heights of the extreme left and right paths of any subtree.
:::

Given the root of a complete binary tree, return the number of the nodes in the tree. Try to solve this in sub-linear time complexity.

**Intuition / approach**: 
A brute force DFS/BFS counts every node in $O(n)$ time. However, for a *complete* binary tree, if the leftmost path's height equals the rightmost path's height from a given node, the subtree rooted at this node is a *perfect* binary tree. A perfect binary tree of height $h$ has exactly $2^h - 1$ nodes. If the heights do not match, we recursively sum the node counts of the left and right subtrees plus 1 for the root. Because at least one child of a complete binary tree will always be a perfect binary tree, we quickly bypass visiting most nodes.

```cpp
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    int getLeftHeight(TreeNode* node) {
        int height = 0;
        while (node) {
            height++;
            node = node->left;
        }
        return height;
    }
    
    int getRightHeight(TreeNode* node) {
        int height = 0;
        while (node) {
            height++;
            node = node->right;
        }
        return height;
    }
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        
        int lh = getLeftHeight(root);
        int rh = getRightHeight(root);
        
        if (lh == rh) {
            return (1 << lh) - 1; // 2^h - 1
        }
        
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    
    Solution sol;
    cout << sol.countNodes(root) << "\n";
    return 0;
}
```

**Complexity**: Time $O(\log^2 n)$. Calculating the left and right heights takes $O(\log n)$ time. At each level of the tree (height $\log n$), we only recurse down one path because one of the subtrees is guaranteed to be a perfect binary tree and short-circuits. Space $O(\log n)$ for the recursion stack.

**Practice:** https://leetcode.com/problems/count-complete-tree-nodes/

### Construct a Binary Tree from Preorder and Inorder Traversal

::: heavy
Reconstructing a tree requires two traversals because one determines the structure (root identification) and the other partitions the elements (left/right sizes).
:::

Given two integer arrays `preorder` and `inorder` where `preorder` is the preorder traversal of a binary tree and `inorder` is the inorder traversal of the same tree, construct and return the binary tree.

**Intuition / approach**: 
In a preorder traversal, the first element is always the root. Once we know the root, we can locate it in the inorder traversal. The inorder traversal splits the tree: all elements to the left of the root's index belong to the left subtree, and all elements to the right belong to the right subtree. By counting the number of elements in the left subtree, we can identify the exact boundary in the preorder array where the left subtree's elements end and the right subtree's elements begin. We recursively apply this logic to build the left and right subtrees. To optimize finding the root in the inorder array, we use a hash map.

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    TreeNode* buildTreeHelper(vector<int>& preorder, int preStart, int preEnd, 
                              vector<int>& inorder, int inStart, int inEnd, 
                              unordered_map<int, int>& inMap) {
        if (preStart > preEnd || inStart > inEnd) return nullptr;
        
        TreeNode* root = new TreeNode(preorder[preStart]);
        int inRoot = inMap[root->val];
        int numsLeft = inRoot - inStart;
        
        root->left = buildTreeHelper(preorder, preStart + 1, preStart + numsLeft, 
                                     inorder, inStart, inRoot - 1, inMap);
        
        root->right = buildTreeHelper(preorder, preStart + numsLeft + 1, preEnd, 
                                      inorder, inRoot + 1, inEnd, inMap);
        
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inMap;
        for (int i = 0; i < inorder.size(); ++i) {
            inMap[inorder[i]] = i;
        }
        return buildTreeHelper(preorder, 0, preorder.size() - 1, 
                               inorder, 0, inorder.size() - 1, inMap);
    }
};

int main() {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    
    Solution sol;
    TreeNode* root = sol.buildTree(preorder, inorder);
    cout << (root ? root->val : -1) << "\n";
    return 0;
}
```

**Complexity**: Time $O(n)$ since building the hash map takes $O(n)$ and we visit each node exactly once. Space $O(n)$ for the hash map and the recursion stack.

**Practice:** https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

### Construct a Binary Tree from Postorder and Inorder Traversal
Given two integer arrays `inorder` and `postorder` where `inorder` is the inorder traversal of a binary tree and `postorder` is the postorder traversal of the same tree, construct and return the binary tree.

**Intuition / approach**: 
This is nearly identical to reconstructing from preorder and inorder. In postorder traversal (Left, Right, Root), the last element is the root. We locate this root in the inorder traversal to find the sizes of the left and right subtrees. Then we recurse, knowing the left subtree elements in postorder start from the beginning and take up exactly the left subtree's size, while the right subtree elements follow them.

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    TreeNode* buildTreeHelper(vector<int>& inorder, int inStart, int inEnd,
                              vector<int>& postorder, int postStart, int postEnd,
                              unordered_map<int, int>& inMap) {
        if (inStart > inEnd || postStart > postEnd) return nullptr;
        
        TreeNode* root = new TreeNode(postorder[postEnd]);
        int inRoot = inMap[root->val];
        int numsLeft = inRoot - inStart;
        
        root->left = buildTreeHelper(inorder, inStart, inRoot - 1, 
                                     postorder, postStart, postStart + numsLeft - 1, inMap);
        root->right = buildTreeHelper(inorder, inRoot + 1, inEnd, 
                                      postorder, postStart + numsLeft, postEnd - 1, inMap);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> inMap;
        for (int i = 0; i < inorder.size(); ++i) {
            inMap[inorder[i]] = i;
        }
        return buildTreeHelper(inorder, 0, inorder.size() - 1, 
                               postorder, 0, postorder.size() - 1, inMap);
    }
};

int main() {
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};
    
    Solution sol;
    TreeNode* root = sol.buildTree(inorder, postorder);
    cout << (root ? root->val : -1) << "\n";
    return 0;
}
```

**Complexity**: Time $O(n)$ where $n$ is the number of nodes, as mapping takes $O(n)$ and creating nodes is linear. Space $O(n)$ for the map and recursion stack.

**Practice:** https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

### Serialize and Deserialize a Binary Tree
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link. Design an algorithm to serialize and deserialize a binary tree.

**Intuition / approach**: 
A clean approach is using a level-order traversal (BFS) with a queue. When serializing, we append the node's value and a delimiter (like `,`) to a string. If a node is null, we append a special character (like `#`). This fully encodes the structure, similar to how arrays represent trees. When deserializing, we read comma-separated tokens. We use a queue to track nodes being built. For each parent popped from the queue, we read the next two tokens for its left and right children, attaching them if they aren't `#`, and pushing the new non-null children onto the queue.

```cpp
#include <iostream>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) return "";
        string s = "";
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            if (curr == nullptr) {
                s += "#,";
            } else {
                s += to_string(curr->val) + ",";
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        return s;
    }

    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        stringstream s(data);
        string str;
        getline(s, str, ',');
        
        TreeNode* root = new TreeNode(stoi(str));
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            
            getline(s, str, ',');
            if (str != "#") {
                curr->left = new TreeNode(stoi(str));
                q.push(curr->left);
            }
            
            getline(s, str, ',');
            if (str != "#") {
                curr->right = new TreeNode(stoi(str));
                q.push(curr->right);
            }
        }
        return root;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    
    Codec codec;
    string ser = codec.serialize(root);
    TreeNode* ans = codec.deserialize(ser);
    cout << codec.serialize(ans) << "\n";
    return 0;
}
```

**Complexity**: Time $O(n)$ for both serialization and deserialization as we process each node constantly. Space $O(n)$ for the serialized string and the BFS queue.

**Practice:** https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

### Morris Inorder Traversal

::: heavy
Morris Traversal achieves an $O(1)$ space footprint by temporarily altering the tree structure, creating threads (links) from a node's inorder predecessor back to the node itself.
:::

Given the root of a binary tree, return the inorder traversal of its nodes' values using $O(1)$ extra space.

**Intuition / approach**: 
Normally, when we go left, we lose the path back up without a stack. Morris Traversal prevents this. Before moving to a left child, we find the current node's inorder predecessor (the rightmost node in the left subtree). We create a temporary thread making the current node the right child of that predecessor, allowing us to safely move left. When we later revisit this node via the thread, we know the left subtree is fully processed. We then safely remove the thread, process the current node, and move to its right child.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder;
        TreeNode* curr = root;
        
        while (curr != nullptr) {
            if (curr->left == nullptr) {
                inorder.push_back(curr->val);
                curr = curr->right;
            } else {
                TreeNode* prev = curr->left;
                while (prev->right != nullptr && prev->right != curr) {
                    prev = prev->right;
                }
                
                if (prev->right == nullptr) {
                    prev->right = curr; 
                    curr = curr->left;
                } else {
                    prev->right = nullptr; 
                    inorder.push_back(curr->val);
                    curr = curr->right;
                }
            }
        }
        return inorder;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution sol;
    vector<int> res = sol.inorderTraversal(root);
    for (int v : res) cout << v << " ";
    return 0;
}
```

**Complexity**: Time $O(n)$ because each node is visited at most twice and each edge is traversed at most three times. Space $O(1)$ because we only use two pointers (`curr` and `prev`) and modify the tree temporarily in place.

**Practice:** https://leetcode.com/problems/binary-tree-inorder-traversal/

### Morris Preorder Traversal
Given the root of a binary tree, return the preorder traversal of its nodes' values using $O(1)$ extra space.

**Intuition / approach**: 
This is almost the exact same logic as Morris Inorder, but adapting the visitation order. Preorder is Root, Left, Right. Therefore, the moment we establish a new thread (when `prev->right == nullptr`), we process the current node *before* stepping left, because this is our first time seeing it. When we revisit the node via the thread (meaning the left subtree is done), we simply sever the thread and step right. If a node has no left child, we process it and step right directly.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> preorder;
        TreeNode* curr = root;
        
        while (curr != nullptr) {
            if (curr->left == nullptr) {
                preorder.push_back(curr->val);
                curr = curr->right;
            } else {
                TreeNode* prev = curr->left;
                while (prev->right != nullptr && prev->right != curr) {
                    prev = prev->right;
                }
                
                if (prev->right == nullptr) {
                    prev->right = curr; 
                    preorder.push_back(curr->val); 
                    curr = curr->left;
                } else {
                    prev->right = nullptr; 
                    curr = curr->right;
                }
            }
        }
        return preorder;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution sol;
    vector<int> res = sol.preorderTraversal(root);
    for (int v : res) cout << v << " ";
    return 0;
}
```

**Complexity**: Time $O(n)$ where every edge is traversed a constant number of times. Space $O(1)$ auxiliary footprint by leveraging temporary right-pointer threads.

**Practice:** https://leetcode.com/problems/binary-tree-preorder-traversal/

### Flatten a Binary Tree to a Linked List
Given the `root` of a binary tree, flatten the tree into a "linked list":
- The "linked list" should use the same `TreeNode` class where the `right` child pointer points to the next node in the list and the `left` child pointer is always null.
- The "linked list" should be in the same order as a pre-order traversal of the binary tree.

**Intuition / approach**: 
A recursive approach modifies pointers during a reverse post-order traversal (Right, Left, Root), maintaining a global `prev` pointer. However, Morris Traversal gives an $O(1)$ space iterative solution. If a node has a left child, we find its predecessor (the rightmost node of the left subtree). The predecessor's right child should point to the current node's original right child. Then, we move the entire left subtree to the right, nullify the left child, and move right to process the next node.

```cpp
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* curr = root;
        while (curr) {
            if (curr->left) {
                TreeNode* prev = curr->left;
                while (prev->right) {
                    prev = prev->right;
                }
                
                prev->right = curr->right;
                curr->right = curr->left;
                curr->left = nullptr;
            }
            curr = curr->right;
        }
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    
    Solution sol;
    sol.flatten(root);
    
    TreeNode* curr = root;
    while (curr) {
        cout << curr->val << " ";
        curr = curr->right;
    }
    return 0;
}
```

**Complexity**: Time $O(n)$ because we touch every node's predecessor at most once during traversal. Space $O(1)$ since no recursion or queue is used, operating entirely in-place.

**Practice:** https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

::: interview
**Tree patterns interviewers expect:**
- **Recursive "return info from children" pattern**: Many hard problems rely on propagating state up from the leaves.
- **Level-order with a queue**: Crucial for tracking distance, width, or structural serialization.
- **LCA (Lowest Common Ancestor)**: A classic structural pattern often used as a sub-routine.
- **Inorder = sorted for BSTs**: A fundamental property to exploit for search trees.
- **Morris for $O(1)$ space**: Keep threading in mind when interviewers constrain space complexity after a recursive solution.
:::
