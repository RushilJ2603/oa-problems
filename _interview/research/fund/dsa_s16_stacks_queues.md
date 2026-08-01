# Stacks & Queues

::: heavy
A **stack** is a Last-In-First-Out (LIFO) data structure, while a **queue** is a First-In-First-Out (FIFO) data structure. Both offer core operations—pushing and popping elements—in $O(1)$ time. In C++, `std::stack` and `std::queue` are container adapters; they do not manage memory themselves but wrap an underlying container (by default, `std::deque`). A `std::deque` (double-ended queue) is a sequence container that allows fast insertion and deletion at both its beginning and its end.
:::

::: keypoint
A **monotonic stack** is a powerful concept built on top of a standard stack. By enforcing that the elements in the stack remain strictly increasing or decreasing, we can answer queries like "find the next greater element" for an entire array in $O(n)$ time. This pattern is central to many advanced problems.
:::

## Implementations & Basics

### Implement Stack Using Arrays
Design a stack using a simple array to support `push`, `pop`, `top`, and `size` operations.

**Intuition / approach:**
The brute force or naive approach for a stack is to shift elements, but that is unnecessary. The optimal approach uses a fixed-size array and an integer `topIndex` initialized to `-1`. When pushing, increment `topIndex` and store the value. When popping, decrement `topIndex`. This makes all operations $O(1)$.

```cpp
#include <iostream>
#include <stdexcept>

class MyStack {
private:
    int* arr;
    int topIndex;
    int capacity;

public:
    MyStack(int size = 1000) {
        capacity = size;
        arr = new int[capacity];
        topIndex = -1;
    }

    ~MyStack() {
        delete[] arr;
    }

    void push(int x) {
        if (topIndex >= capacity - 1) {
            throw std::overflow_error("Stack overflow");
        }
        arr[++topIndex] = x;
    }

    int pop() {
        if (topIndex == -1) {
            throw std::underflow_error("Stack underflow");
        }
        return arr[topIndex--];
    }

    int top() {
        if (topIndex == -1) {
            throw std::underflow_error("Stack is empty");
        }
        return arr[topIndex];
    }

    int size() {
        return topIndex + 1;
    }

    bool empty() {
        return topIndex == -1;
    }
};
```

**Complexity:**
- **Time:** $O(1)$ for all operations, as we only update an index.
- **Space:** $O(n)$ where $n$ is the capacity of the array.

**Practice:** https://www.geeksforgeeks.org/problems/implement-stack-using-array/1

### Implement Queue Using Arrays
Design a queue using an array to support `push`, `pop`, `front`, and `size` operations.

**Intuition / approach:**
Using a naive array where we push at the end and pop from the front (by shifting all elements left) would make `pop` $O(n)$. The optimal approach uses two pointers, `front` and `rear`, and treats the array as circular (or simply bounds-checked if size is fixed). Elements are enqueued at `rear` and dequeued at `front`. Using a counter for the current size simplifies the circular arithmetic.

```cpp
#include <iostream>
#include <stdexcept>

class MyQueue {
private:
    int* arr;
    int frontIndex;
    int rearIndex;
    int currentSize;
    int capacity;

public:
    MyQueue(int size = 1000) {
        capacity = size;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        currentSize = 0;
    }

    ~MyQueue() {
        delete[] arr;
    }

    void push(int x) {
        if (currentSize == capacity) {
            throw std::overflow_error("Queue overflow");
        }
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = x;
        currentSize++;
    }

    int pop() {
        if (currentSize == 0) {
            throw std::underflow_error("Queue underflow");
        }
        int popped = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        currentSize--;
        return popped;
    }

    int front() {
        if (currentSize == 0) {
            throw std::underflow_error("Queue is empty");
        }
        return arr[frontIndex];
    }

    int size() {
        return currentSize;
    }

    bool empty() {
        return currentSize == 0;
    }
};
```

**Complexity:**
- **Time:** $O(1)$ for all operations.
- **Space:** $O(n)$ where $n$ is the capacity.

**Practice:** https://www.geeksforgeeks.org/problems/implement-queue-using-array/1

### Implement Stack Using a Queue
Implement a Last-In-First-Out (LIFO) stack using only a standard queue.

**Intuition / approach:**
A queue is FIFO. To simulate a stack (LIFO), when pushing a new element, we can enqueue it, and then repeatedly dequeue and re-enqueue all previously existing elements. This moves the newly added element to the front of the queue, making it the first to be dequeued (matching stack `pop` behavior). We only need a single `std::queue`.

```cpp
#include <queue>

class MyStack {
private:
    std::queue<int> q;

public:
    MyStack() {}

    void push(int x) {
        int s = q.size();
        q.push(x);
        for (int i = 0; i < s; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }

    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};
```

**Complexity:**
- **Time:** $O(n)$ for `push`, as we cycle $n$ elements. $O(1)$ for `pop`, `top`, and `empty`.
- **Space:** $O(n)$ to hold the elements in the queue.

**Practice:** https://leetcode.com/problems/implement-stack-using-queues/

### Implement Queue Using Stacks
Implement a First-In-First-Out (FIFO) queue using only two stacks.

**Intuition / approach:**
A stack reverses order. If we pass elements through two stacks, the order is reversed twice, restoring the original FIFO order. We keep an `input` stack for pushes and an `output` stack for pops/peeks. When pushing, we always push to `input`. When popping or peeking, we need the oldest element, which should be at the top of `output`. If `output` is empty, we pop all elements from `input` and push them into `output`, which puts the oldest element at the top.

::: keypoint
Transferring elements from `input` to `output` takes $O(n)$ time, but it only happens when `output` is empty. Every element is moved exactly once to `output` and popped once, making the **amortized** time complexity of `pop`/`peek` strictly $O(1)$.
:::

```cpp
#include <stack>

class MyQueue {
private:
    std::stack<int> input;
    std::stack<int> output;

    void transferIfEmpty() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
    }

public:
    MyQueue() {}

    void push(int x) {
        input.push(x);
    }

    int pop() {
        transferIfEmpty();
        int val = output.top();
        output.pop();
        return val;
    }

    int peek() {
        transferIfEmpty();
        return output.top();
    }

    bool empty() {
        return input.empty() && output.empty();
    }
};
```

**Complexity:**
- **Time:** $O(1)$ for `push` and `empty`. Amortized $O(1)$ for `pop` and `peek` (worst-case $O(n)$ but averages out).
- **Space:** $O(n)$ for the two stacks.

**Practice:** https://leetcode.com/problems/implement-queue-using-stacks/

### Implement Stack Using a Linked List
Design a stack using a singly linked list.

**Intuition / approach:**
In a singly linked list, inserting and deleting at the head takes $O(1)$ time. We can treat the head of the linked list as the top of the stack. A `push` creates a new node, points its next to the current head, and updates the head. A `pop` advances the head pointer and deletes the old head.

```cpp
#include <stdexcept>

struct StackNode {
    int data;
    StackNode* next;
    StackNode(int val) : data(val), next(nullptr) {}
};

class MyStack {
private:
    StackNode* head;
    int currentSize;

public:
    MyStack() {
        head = nullptr;
        currentSize = 0;
    }

    ~MyStack() {
        while (head != nullptr) {
            StackNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(int x) {
        StackNode* newNode = new StackNode(x);
        newNode->next = head;
        head = newNode;
        currentSize++;
    }

    int pop() {
        if (head == nullptr) {
            throw std::underflow_error("Stack underflow");
        }
        int val = head->data;
        StackNode* temp = head;
        head = head->next;
        delete temp;
        currentSize--;
        return val;
    }

    int top() {
        if (head == nullptr) {
            throw std::underflow_error("Stack is empty");
        }
        return head->data;
    }

    int size() {
        return currentSize;
    }

    bool empty() {
        return head == nullptr;
    }
};
```

**Complexity:**
- **Time:** $O(1)$ for all operations.
- **Space:** $O(n)$ for dynamic allocations of nodes, though each node has a constant space overhead for pointers.

**Practice:** https://www.geeksforgeeks.org/problems/implement-stack-using-linked-list/1

### Implement Queue Using a Linked List
Design a queue using a singly linked list.

**Intuition / approach:**
For a queue, we need $O(1)$ insertions at one end and $O(1)$ deletions at the other. We maintain both a `head` (for dequeueing) and a `tail` (for enqueueing) pointer. When pushing, we attach a node after the `tail` and update `tail`. When popping, we remove the `head` node and advance it, handling the edge case where the queue becomes empty (updating `tail` to `nullptr` as well).

```cpp
#include <stdexcept>

struct QueueNode {
    int data;
    QueueNode* next;
    QueueNode(int val) : data(val), next(nullptr) {}
};

class MyQueue {
private:
    QueueNode* head;
    QueueNode* tail;
    int currentSize;

public:
    MyQueue() {
        head = nullptr;
        tail = nullptr;
        currentSize = 0;
    }

    ~MyQueue() {
        while (head != nullptr) {
            QueueNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(int x) {
        QueueNode* newNode = new QueueNode(x);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        currentSize++;
    }

    int pop() {
        if (head == nullptr) {
            throw std::underflow_error("Queue underflow");
        }
        int val = head->data;
        QueueNode* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        currentSize--;
        return val;
    }

    int front() {
        if (head == nullptr) {
            throw std::underflow_error("Queue is empty");
        }
        return head->data;
    }

    int size() {
        return currentSize;
    }

    bool empty() {
        return head == nullptr;
    }
};
```

**Complexity:**
- **Time:** $O(1)$ for all operations, since we maintain both head and tail pointers.
- **Space:** $O(n)$ for dynamically allocated nodes.

**Practice:** https://www.geeksforgeeks.org/problems/implement-queue-using-linked-list/1

### Check for Balanced Parentheses
Given a string containing just the characters `'(', ')', '{', '}', '['` and `']'`, determine if the input string is valid (brackets close in the correct order).

**Intuition / approach:**
The brute force method repeatedly finds and removes adjacent matching pairs `()`, `{}`, `[]`, which takes $O(n^{2})$ time. The optimal approach uses a stack. As we iterate through the string, opening brackets are pushed onto the stack. When we encounter a closing bracket, it must match the most recently seen unclosed opening bracket—which is exactly the element at the top of the stack. If it matches, we pop the opening bracket. If it doesn't, or the stack is empty, the string is invalid. Finally, the stack must be empty if all brackets were perfectly matched.

::: keypoint
Nested structures like parentheses perfectly mirror Last-In-First-Out behavior. The innermost closing bracket resolves the most recently opened bracket, making a stack the natural tool.
:::

```cpp
#include <string>
#include <stack>

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } else {
                if (st.empty()) return false;
                char topChar = st.top();
                if ((c == ')' && topChar == '(') ||
                    (c == '}' && topChar == '{') ||
                    (c == ']' && topChar == '[')) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }
        return st.empty();
    }
};
```

**Complexity:**
- **Time:** $O(n)$, since we process each character of the string exactly once.
- **Space:** $O(n)$ in the worst case (e.g., all opening brackets) to store characters in the stack.

**Practice:** https://leetcode.com/problems/valid-parentheses/

### Implement Min Stack
Design a stack that supports `push`, `pop`, `top`, and retrieving the minimum element in constant time.

**Intuition / approach:**
A brute force way to find the minimum is scanning the stack taking $O(n)$ time. The better approach uses extra space: store pairs of `(value, current_min)` in the stack, so the top of the stack always knows the minimum value seen so far.
The optimal space approach uses an encoding trick: we track a single `minElement` variable. When pushing a value $x$ smaller than `minElement`, we push a modified value $2x - \text{minElement}$ (which is guaranteed to be less than $x$, acting as a flag) and update `minElement` to $x$. When popping, if we see a value smaller than `minElement`, we know it's a flagged value indicating the minimum is changing, so we restore the previous minimum using $2 \times \text{minElement} - \text{popped\_value}$. We will use `long long` to prevent overflow in the encoding calculation.

::: keypoint
The encoded value $2x - \text{prev\_min}$ is always less than the new minimum $x$. This lets us detect during a `pop` operation that we are removing the current minimum element and must restore the previous one.
:::

```cpp
#include <stack>

class MinStack {
private:
    std::stack<long long> st;
    long long minElement;

public:
    MinStack() {}

    void push(long long val) {
        if (st.empty()) {
            st.push(val);
            minElement = val;
        } else {
            if (val < minElement) {
                // Encode the new min to store it, flagging it as a min-update
                st.push(2 * val - minElement);
                minElement = val;
            } else {
                st.push(val);
            }
        }
    }

    void pop() {
        if (st.empty()) return;

        long long topVal = st.top();
        st.pop();

        if (topVal < minElement) {
            // Restore previous minElement
            minElement = 2 * minElement - topVal;
        }
    }

    int top() {
        if (st.empty()) return -1;
        
        long long topVal = st.top();
        if (topVal < minElement) {
            return minElement;
        }
        return topVal;
    }

    int getMin() {
        return minElement;
    }
};
```

**Complexity:**
- **Time:** $O(1)$ for all operations.
- **Space:** $O(n)$ to store elements, but optimal space-wise compared to the pair approach as we use only one value per push.

**Practice:** https://leetcode.com/problems/min-stack/

## Expression Conversions & Monotonic Stacks

Expressions can be written in infix, prefix, or postfix notation. Before converting them, note that operator precedence dictates the evaluation order (typically `^` > `*`, `/` > `+`, `-`), and associativity breaks ties (left-to-right for most, but right-to-left for `^`).

### Infix to Postfix
Infix notation (e.g., `A+B*C`) places operators between operands. Postfix (`ABC*+`) places them after. To convert, we use a stack to defer operators until their operands are processed and lower-precedence operators force them out.

**Intuition:**
We read characters left to right. Operands go directly to the output. We push operators onto a stack, but to maintain precedence, before pushing an operator, we pop all operators from the stack that have greater or equal precedence (for left-associative operators). Parentheses bypass precedence rules: `(` is pushed unconditionally, and `)` pops everything until `(`.

```cpp
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int prec(char c) {
    if (c == '^') return 3;
    if (c == '/' || c == '*') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}

string infixToPostfix(string s) {
    stack<char> st;
    string res = "";
    for (char c : s) {
        if (isalnum(c)) {
            res += c;
        } else if (c == '(') {
            st.push('(');
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                res += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop(); // pop '('
        } else {
            while (!st.empty() && prec(c) <= prec(st.top())) {
                // ^ is right-associative: do not pop another ^
                if (c == '^' && st.top() == '^') break;
                res += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    return res;
}
```
**Complexity:** $O(n)$ time since each character is pushed and popped at most once. $O(n)$ space for the stack.
**Practice:** https://practice.geeksforgeeks.org/problems/infix-to-postfix-1587115620/1

### Infix to Prefix
Prefix notation (`+A*BC`) places operators before operands.

**Intuition:**
A clever trick maps this to the postfix algorithm: if we reverse the infix string and swap parentheses, a left-to-right scan becomes a right-to-left scan. We then apply infix-to-postfix, but because the expression is reversed, we only pop operators of *strictly greater* precedence (or equal precedence if right-associative) to respect the flipped associativity. Finally, we reverse the result.

```cpp
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int prec(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}

string infixToPrefix(string s) {
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') s[i] = ')';
        else if (s[i] == ')') s[i] = '(';
    }
    
    stack<char> st;
    string res = "";
    for (char c : s) {
        if (isalnum(c)) {
            res += c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                res += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();
        } else {
            while (!st.empty() && prec(c) < prec(st.top())) {
                res += st.top();
                st.pop();
            }
            // For right-associative ^, pop if equal precedence
            while (!st.empty() && prec(c) == prec(st.top()) && c == '^') {
                res += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    cout << infixToPrefix("(a-b/c)*(a/k-l)") << "\n"; // *-a/bc-/akl
    return 0;
}
```
**Complexity:** $O(n)$ time and $O(n)$ space.
**Practice:** https://www.geeksforgeeks.org/convert-infix-prefix-notation/

### Prefix to Infix
**Intuition:**
In prefix, the operator precedes its operands. By reading from right to left, we encounter the operands before their operator. When an operator is found, the top two elements on the stack are guaranteed to be its operands.

```cpp
#include <iostream>
#include <string>
#include <stack>

using namespace std;

string prefixToInfix(string s) {
    stack<string> st;
    for (int i = s.length() - 1; i >= 0; i--) {
        char c = s[i];
        if (isalnum(c)) {
            st.push(string(1, c));
        } else {
            string op1 = st.top(); st.pop();
            string op2 = st.top(); st.pop();
            st.push("(" + op1 + c + op2 + ")");
        }
    }
    return st.top();
}
```
**Complexity:** $O(n)$ time, $O(n)$ space (ignoring string concatenation overhead).
**Practice:** https://practice.geeksforgeeks.org/problems/prefix-to-infix-conversion/1

### Postfix to Infix
**Intuition:**
Similar to prefix-to-infix, but reading left to right. When an operator is encountered, the operands are already on the stack. The first popped element is the right operand (since it was pushed last), and the second is the left operand.

```cpp
#include <iostream>
#include <string>
#include <stack>

using namespace std;

string postfixToInfix(string s) {
    stack<string> st;
    for (char c : s) {
        if (isalnum(c)) {
            st.push(string(1, c));
        } else {
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();
            st.push("(" + op1 + c + op2 + ")");
        }
    }
    return st.top();
}
```
**Complexity:** $O(n)$ time and $O(n)$ space.
**Practice:** https://practice.geeksforgeeks.org/problems/postfix-to-infix-conversion/1

### Prefix to Postfix
**Intuition:**
Read right to left. When an operator is found, pop two operands, concatenate them as `op1 + op2 + operator`, and push back.

```cpp
#include <iostream>
#include <string>
#include <stack>

using namespace std;

string prefixToPostfix(string s) {
    stack<string> st;
    for (int i = s.length() - 1; i >= 0; i--) {
        char c = s[i];
        if (isalnum(c)) {
            st.push(string(1, c));
        } else {
            string op1 = st.top(); st.pop();
            string op2 = st.top(); st.pop();
            st.push(op1 + op2 + c);
        }
    }
    return st.top();
}
```
**Complexity:** $O(n)$ time and $O(n)$ space.
**Practice:** https://practice.geeksforgeeks.org/problems/prefix-to-postfix-conversion/1

### Postfix to Prefix
**Intuition:**
Read left to right. Pop two operands, concatenate as `operator + op1 + op2`, and push back.

```cpp
#include <iostream>
#include <string>
#include <stack>

using namespace std;

string postfixToPrefix(string s) {
    stack<string> st;
    for (char c : s) {
        if (isalnum(c)) {
            st.push(string(1, c));
        } else {
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();
            st.push(string(1, c) + op1 + op2);
        }
    }
    return st.top();
}
```
**Complexity:** $O(n)$ time and $O(n)$ space.
**Practice:** https://practice.geeksforgeeks.org/problems/postfix-to-prefix-conversion/1

::: keypoint
**The Monotonic Stack Pattern:**
A monotonic stack maintains its elements in a strictly increasing or decreasing order. When a new element arrives that would break this order, we pop elements from the stack until the order can be preserved. This popping process inherently resolves "next greater" or "next smaller" queries in $O(n)$ time, because each element is pushed and popped exactly once.
:::

### Next Greater Element I
Given two arrays where `nums1` is a subset of `nums2`, find the next greater element for each element of `nums1` in `nums2`.

**Intuition:**
The brute force takes $O(n^2)$ by scanning to the right of each element. 
Instead, we process `nums2` from right to left using a monotonic decreasing stack. If the stack top is smaller than or equal to the current element, it can never be the "next greater" for this or any future element to the left, so we pop it. The stack top is then our next greater element. We map this in a hash map for $O(1)$ lookups when iterating `nums1`.

```cpp
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> nge;
    stack<int> st;
    
    for (int i = nums2.size() - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= nums2[i]) {
            st.pop();
        }
        nge[nums2[i]] = st.empty() ? -1 : st.top();
        st.push(nums2[i]);
    }
    
    vector<int> res;
    for (int num : nums1) {
        res.push_back(nge[num]);
    }
    return res;
}
```
**Complexity:** $O(N + M)$ time where $N$ and $M$ are lengths of the arrays. $O(N)$ space for the stack and map.
**Practice:** https://leetcode.com/problems/next-greater-element-i/

### Next Greater Element II
Find the next greater element in a circular array (the next element of the last element is the first element).

**Intuition:**
A circular array of size $n$ can be simulated by unrolling it to size $2n$. We iterate from $2n - 1$ down to 0, using the modulo operator `i % n` to wrap around. The monotonic stack logic remains identical.

```cpp
#include <vector>
#include <stack>

using namespace std;

vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> nge(n, -1);
    stack<int> st;
    
    for (int i = 2 * n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= nums[i % n]) {
            st.pop();
        }
        if (i < n) {
            nge[i] = st.empty() ? -1 : st.top();
        }
        st.push(nums[i % n]);
    }
    return nge;
}
```
**Complexity:** $O(n)$ time to process $2n$ elements. $O(n)$ space for the stack.
**Practice:** https://leetcode.com/problems/next-greater-element-ii/

### Next Smaller Element
Find the nearest smaller element to the left (or right) of every element.

**Intuition:**
Just like Next Greater Element, but we want the stack to be monotonically increasing. To find the next smaller to the right, we iterate right-to-left and pop elements that are strictly greater than or equal to the current element.

```cpp
#include <vector>
#include <stack>

using namespace std;

vector<int> nextSmallerElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n, -1);
    stack<int> st;
    
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() >= arr[i]) {
            st.pop();
        }
        nse[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return nse;
}
```
**Complexity:** $O(n)$ time as elements are pushed/popped at most once. $O(n)$ space.
**Practice:** https://www.geeksforgeeks.org/problems/help-classmates--141631/1

### Number of NGEs to the Right
Given an array and multiple queries (each providing an index), find the count of elements to the right of the given index that are strictly greater than the element at that index.

**Intuition:**
For competitive programming platforms where query counts are small, a brute force traversal to the right for each query suffices. A fully optimized approach (like a Segment Tree or Fenwick Tree) is $O(Q \log N)$, but basic array iterations yield $O(Q \times N)$, which is acceptable for simple queries on smaller arrays or when asked in preliminary interviews to test understanding of the problem.

```cpp
#include <vector>

using namespace std;

vector<int> countGreater(vector<int>& arr, vector<int>& queries) {
    vector<int> res;
    int n = arr.size();
    
    for (int q : queries) {
        int count = 0;
        int val = arr[q];
        for (int i = q + 1; i < n; i++) {
            if (arr[i] > val) {
                count++;
            }
        }
        res.push_back(count);
    }
    return res;
}
```
**Complexity:** $O(Q \times N)$ time where $Q$ is the number of queries. $O(1)$ auxiliary space.
**Practice:** https://www.geeksforgeeks.org/problems/number-of-nges-to-the-right/1

### Trapping Rain Water
Given an elevation map representing bar heights, compute how much water it can trap after raining.

::: keypoint
Water trapped above any bar `i` is determined by the shortest of the tallest boundaries to its left and right: `min(left_max, right_max) - height[i]`.
:::

**Intuition:**
The brute force finds the left and right max for each bar in $O(n^2)$. Precomputing these arrays reduces time to $O(n)$ but requires $O(n)$ space.
*Two-pointer approach:* We can track `left_max` and `right_max` dynamically. The smaller of the two maxes bottlenecks the water level. By moving the pointer with the smaller max inward, we confidently compute trapped water without extra arrays.
*Stack approach:* Alternatively, a monotonic decreasing stack computes water horizontally. When we find a bar taller than the stack top, it forms a "basin". The trapped water is bounded by the current bar and the new stack top (after popping the valley).

**Two-Pointer Solution:**
```cpp
#include <vector>
#include <algorithm>

using namespace std;

int trap(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int left_max = 0, right_max = 0;
    int water = 0;
    
    while (left <= right) {
        if (height[left] <= height[right]) {
            if (height[left] >= left_max) {
                left_max = height[left];
            } else {
                water += left_max - height[left];
            }
            left++;
        } else {
            if (height[right] >= right_max) {
                right_max = height[right];
            } else {
                water += right_max - height[right];
            }
            right--;
        }
    }
    return water;
}
```
**Complexity:** $O(n)$ time, $O(1)$ space.
**Practice:** https://leetcode.com/problems/trapping-rain-water/

### Sum of Subarray Minimums
Given an array of integers, find the sum of `min(b)` where `b` ranges over every contiguous subarray. Return the answer modulo $10^9 + 7$.

::: heavy
Instead of generating all subarrays ($O(n^2)$), we use the **contribution technique**. We ask: for a given element `arr[i]`, in how many subarrays is it the *strict* minimum? 
If `arr[i]` is the minimum, we find the Previous Smaller Element (PSE) at index `L` and the Next Smaller Element (NSE) at index `R`. The number of subarrays where `arr[i]` is the minimum is `(i - L) * (R - i)`. We must handle duplicates carefully by using strictly less `<` on one side and less-than-or-equal `<=` on the other to prevent overcounting.
:::

**Intuition:**
We find the index of the next smaller element (`NSE`) and previous smaller or equal element (`PSEE`) for each element using two monotonic stacks. The contribution of `arr[i]` is `arr[i] * (i - PSEE[i]) * (NSE[i] - i)`.

```cpp
#include <vector>
#include <stack>

using namespace std;

int sumSubarrayMins(vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n, n);
    vector<int> psee(n, -1);
    stack<int> st;
    
    // Find Next Smaller Element (strict)
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }
        if (!st.empty()) nse[i] = st.top();
        st.push(i);
    }
    
    while (!st.empty()) st.pop();
    
    // Find Previous Smaller or Equal Element
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            st.pop();
        }
        if (!st.empty()) psee[i] = st.top();
        st.push(i);
    }
    
    long long total = 0;
    int mod = 1e9 + 7;
    for (int i = 0; i < n; i++) {
        long long left_count = i - psee[i];
        long long right_count = nse[i] - i;
        total = (total + (left_count * right_count % mod) * arr[i]) % mod;
    }
    return total;
}
```
**Complexity:** $O(n)$ time to run the monotonic stacks. $O(n)$ space for stacks and arrays.
**Practice:** https://leetcode.com/problems/sum-of-subarray-minimums/

### Asteroid Collision
An array represents asteroids. Positive values move right, negative values move left. Find the state of the asteroids after all collisions.

**Intuition:**
A collision only happens when a right-moving asteroid (positive) is followed by a left-moving asteroid (negative). We use a stack to track survivors. When a negative asteroid arrives, it destroys all positive asteroids smaller than it in the stack. If they are equal, both destroy each other.

```cpp
#include <vector>
#include <cmath>

using namespace std;

vector<int> asteroidCollision(vector<int>& asteroids) {
    vector<int> st; // using vector as a stack for easy conversion to result
    
    for (int ast : asteroids) {
        bool destroyed = false;
        while (!st.empty() && st.back() > 0 && ast < 0) {
            if (st.back() < abs(ast)) {
                st.pop_back(); // positive asteroid is destroyed, continue checking
            } else if (st.back() == abs(ast)) {
                st.pop_back(); // both destroyed
                destroyed = true;
                break;
            } else {
                destroyed = true; // negative asteroid is destroyed
                break;
            }
        }
        if (!destroyed) {
            st.push_back(ast);
        }
    }
    return st;
}
```
**Complexity:** $O(n)$ time because each asteroid is pushed and popped at most once. $O(n)$ space.
**Practice:** https://leetcode.com/problems/asteroid-collision/

### Sum of Subarray Ranges
Find the sum of all subarray ranges (max - min).

**Intuition:**
The brute force $O(n^2)$ computes the max and min for every subarray explicitly. Using the contribution technique from *Sum of Subarray Minimums*, we know that `Sum(max(b) - min(b)) = Sum(max(b)) - Sum(min(b))`. We can compute the contribution of every element as a maximum (using Next/Previous Greater Elements) and as a minimum (using Next/Previous Smaller Elements), and subtract the two results.

```cpp
#include <vector>
#include <stack>

using namespace std;

long long subArrayRanges(vector<int>& nums) {
    int n = nums.size();
    long long total_min = 0, total_max = 0;
    
    // Sum of Mins
    vector<int> nse(n, n), psee(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && nums[st.top()] >= nums[i]) st.pop();
        if (!st.empty()) nse[i] = st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] > nums[i]) st.pop();
        if (!st.empty()) psee[i] = st.top();
        st.push(i);
    }
    for (int i = 0; i < n; i++) {
        total_min += (long long)(i - psee[i]) * (nse[i] - i) * nums[i];
    }
    
    // Sum of Maxs
    vector<int> nge(n, n), pgee(n, -1);
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && nums[st.top()] <= nums[i]) st.pop();
        if (!st.empty()) nge[i] = st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] < nums[i]) st.pop();
        if (!st.empty()) pgee[i] = st.top();
        st.push(i);
    }
    for (int i = 0; i < n; i++) {
        total_max += (long long)(i - pgee[i]) * (nge[i] - i) * nums[i];
    }
    
    return total_max - total_min;
}
```
**Complexity:** $O(n)$ time via multiple monotonic passes. $O(n)$ space.
**Practice:** https://leetcode.com/problems/sum-of-subarray-ranges/

### Remove K Digits
Given string `num` representing a non-negative integer and an integer `k`, remove `k` digits from `num` so that the new number is the smallest possible.

::: keypoint
A smaller digit at a more significant position yields a smaller overall number. Therefore, we should greedily maintain a monotonic increasing stack of digits, removing larger preceding digits when we find a smaller one, as long as we still have deletions left (`k > 0`).
:::

**Intuition:**
We read the digits left to right. If the current digit is smaller than the stack top and `k > 0`, we pop the stack top (discarding a larger digit from a higher place value). We push the current digit. If `k` is still greater than 0 after the loop, we pop from the end (since the stack is monotonic increasing, the largest digits are at the end). Finally, we strip leading zeros.

```cpp
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string removeKdigits(string num, int k) {
    string res = ""; // acts as our stack
    
    for (char c : num) {
        while (!res.empty() && res.back() > c && k > 0) {
            res.pop_back();
            k--;
        }
        // prevent leading zeros
        if (!res.empty() || c != '0') {
            res.push_back(c);
        }
    }
    
    // if k > 0, we still need to drop digits (they are the largest at the end)
    while (!res.empty() && k > 0) {
        res.pop_back();
        k--;
    }
    
    return res.empty() ? "0" : res;
}
```
**Complexity:** $O(n)$ time since each digit is pushed and popped at most once. $O(n)$ space.
**Practice:** https://leetcode.com/problems/remove-k-digits/

## Advanced Stack Problems & Cache Design

### Largest Rectangle in Histogram

::: heavy
This problem introduces the single-pass stack technique to compute boundaries simultaneously, a dense but powerful pattern.
:::

Given an array of integers representing the histogram's bar height where the width of each bar is $1$, return the area of the largest rectangle in the histogram.

**Intuition:**
The brute force approach considers every pair of bars as boundaries and finds the minimum height between them, taking $O(n^{2})$ time. A better approach finds the Next Smaller Element (NSE) to the left and right for each bar. The rectangle bounded by a bar `h` can extend to the left until a smaller bar is encountered, and similarly to the right. We can compute NSE-left and NSE-right arrays using monotonic stacks in two passes, yielding $O(n)$ time.

The optimal approach merges this into a single pass. We maintain a stack of indices for bars in strictly increasing height order. When we encounter a bar smaller than the top of the stack, the current bar is the NSE-right for the stack top. The new stack top becomes the NSE-left. We compute the area for the popped bar immediately.

```cpp
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int max_area = 0;
        int n = heights.size();
        
        for (int i = 0; i <= n; i++) {
            while (!st.empty() && (i == n || heights[st.top()] >= heights[i])) {
                int height = heights[st.top()];
                st.pop();
                int width;
                if (st.empty()) {
                    width = i;
                } else {
                    width = i - st.top() - 1;
                }
                max_area = max(max_area, height * width);
            }
            st.push(i);
        }
        
        return max_area;
    }
};
```

**Complexity:** Time $O(n)$ because each index is pushed and popped at most once. Space $O(n)$ for the stack.
**Practice:** https://leetcode.com/problems/largest-rectangle-in-histogram/

### Maximal Rectangle

Given a `rows` x `cols` binary matrix filled with `0`'s and `1`'s, find the largest rectangle containing only `1`'s and return its area.

**Intuition:**
The brute force approach explores all possible rectangles, which takes $O((R \times C)^{2})$ or worse. We can optimize this by treating each row as the base of a histogram. We maintain an array of heights representing the number of consecutive `1`s directly above and including the current row. For each row, we update the heights and then solve the Largest Rectangle in Histogram problem.

```cpp
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int max_area = 0;
        int n = heights.size();
        for (int i = 0; i <= n; i++) {
            while (!st.empty() && (i == n || heights[st.top()] >= heights[i])) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                max_area = max(max_area, height * width);
            }
            st.push(i);
        }
        return max_area;
    }

public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int max_area = 0;
        vector<int> heights(matrix[0].size(), 0);
        
        for (const auto& row : matrix) {
            for (int j = 0; j < row.size(); j++) {
                if (row[j] == '1') heights[j]++;
                else heights[j] = 0;
            }
            max_area = max(max_area, largestRectangleArea(heights));
        }
        return max_area;
    }
};
```

**Complexity:** Time $O(R \times C)$, where $R$ is rows and $C$ is columns, as we process each cell and compute the histogram area in $O(C)$ time per row. Space $O(C)$ for the heights array and stack.
**Practice:** https://leetcode.com/problems/maximal-rectangle/

### Sliding Window Maximum

::: keypoint
A monotonic deque efficiently finds extremes in a sliding window by evicting useless elements from the back and out-of-bounds elements from the front.
:::

Given an array of integers `nums`, there is a sliding window of size `k` moving from the very left to the very right. Return the maximum sliding window for each position.

**Intuition:**
The brute force approach finds the maximum in each window of size `k`, taking $O(n \times k)$ time. A better approach uses a max-heap (priority queue), bringing the time to $O(n \log n)$, but we must handle removal of elements that fall out of the window.

The optimal approach uses a double-ended queue (`std::deque`). We store indices in the deque. The deque maintains elements in strictly decreasing order. For each element, we remove indices from the front that are no longer in the window. We then remove indices from the back whose corresponding values are less than or equal to the current element, because they will never be the maximum now that a larger element has appeared. Finally, we push the current index to the back.

```cpp
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> res;
        
        for (int i = 0; i < nums.size(); i++) {
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }
            
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            if (i >= k - 1) {
                res.push_back(nums[dq.front()]);
            }
        }
        
        return res;
    }
};
```

**Complexity:** Time $O(n)$ since each element is pushed and popped from the deque at most once. Space $O(k)$ to store up to `k` indices in the deque.
**Practice:** https://leetcode.com/problems/sliding-window-maximum/

### Stock Span Problem

Design a class that calculates the span of a stock's price for today. The span is the maximum number of consecutive days (starting from today and going backward) for which the stock price was less than or equal to today's price.

**Intuition:**
The brute force solution iterates backwards from the current day to count consecutive smaller or equal prices, taking $O(n)$ time per query. This is equivalent to finding the Previous Greater Element (PGE). By maintaining a monotonic stack, we can achieve $O(1)$ amortized time per query.

We store pairs of `{price, span}` in a stack. When a new price arrives, we pop all elements with prices less than or equal to the new price, accumulating their spans. The sum of these spans plus $1$ (for the current day) becomes the span of the new price, which we then push onto the stack.

```cpp
#include <stack>

using namespace std;

class StockSpanner {
    stack<pair<int, int>> st;
public:
    StockSpanner() {}
    
    int next(int price) {
        int span = 1;
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second;
            st.pop();
        }
        st.push({price, span});
        return span;
    }
};
```

**Complexity:** Time $O(1)$ amortized per `next` call, since every element is pushed and popped at most once. Space $O(n)$ for the stack in the worst case (e.g., strictly decreasing prices).
**Practice:** https://leetcode.com/problems/online-stock-span/

### The Celebrity Problem

In a party of $n$ people, there may exist one celebrity. A celebrity is someone who is known by everyone else, but knows nobody. Given a helper function `knows(a, b)` that tells you if `a` knows `b`, find the celebrity's label ($0$ to $n - 1$) or return $-1$ if there is no celebrity.

**Intuition:**
A brute force approach checks the in-degree and out-degree for each person using $O(n^{2})$ queries. However, a single call to `knows(a, b)` eliminates one person: if `a` knows `b`, `a` cannot be the celebrity. If `a` does not know `b`, `b` cannot be the celebrity. 

We can use two pointers (or a stack) to eliminate candidates in $O(n)$ time. We initialize pointers `left = 0` and `right = n - 1`. If `knows(left, right)` is true, `left` is eliminated, so we increment `left`. Otherwise, `right` is eliminated, so we decrement `right`. The last remaining person is the potential celebrity. We must do a final pass to verify this candidate knows nobody and is known by everyone.

```cpp
// Forward declaration of the knows API.
bool knows(int a, int b);

class Solution {
public:
    int findCelebrity(int n) {
        int left = 0;
        int right = n - 1;
        
        while (left < right) {
            if (knows(left, right)) {
                left++;
            } else {
                right--;
            }
        }
        
        int candidate = left;
        
        for (int i = 0; i < n; i++) {
            if (i != candidate) {
                if (knows(candidate, i) || !knows(i, candidate)) {
                    return -1;
                }
            }
        }
        
        return candidate;
    }
};
```

**Complexity:** Time $O(n)$ because we make exactly $n - 1$ calls to find the candidate and $2n$ calls to verify. Space $O(1)$ using two pointers.
**Practice:** https://leetcode.com/problems/find-the-celebrity/

### LRU Cache

![LRU cache design: a doubly linked list of nodes plus a hash map from key to node.](../assets/ss_224.png)

::: heavy
LRU Cache requires constant time access and arbitrary constant time eviction, mandating a hash map linked with a doubly linked list.
:::

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache. It must support `get(key)` and `put(key, value)` in $O(1)$ average time complexity.

**Intuition:**
An array or standard queue cannot support $O(1)$ arbitrary removals when a key is accessed. A hash map provides $O(1)$ key lookups, but does not track ordering. To track ordering with $O(1)$ updates, we need a doubly linked list where the most recently used (MRU) node is kept near the head, and the least recently used (LRU) node is kept near the tail.

The optimal approach combines a `std::unordered_map` linking keys to node pointers, and a doubly linked list. When a node is accessed or updated, it is removed from its current position and inserted at the front. When capacity is exceeded, the node at the tail is removed from both the list and the hash map. Dummy head and tail nodes greatly simplify insertion and deletion edge cases.

```cpp
#include <unordered_map>

using namespace std;

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void addToHead(Node* node) {
        node->next = head->next;
        node->next->prev = node;
        node->prev = head;
        head->next = node;
    }
    
public:
    LRUCache(int cap) {
        capacity = cap;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            removeNode(node);
            addToHead(node);
            return node->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            removeNode(node);
            addToHead(node);
        } else {
            if (cache.size() == capacity) {
                Node* lru = tail->prev;
                cache.erase(lru->key);
                removeNode(lru);
                delete lru;
            }
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addToHead(newNode);
        }
    }
    
    ~LRUCache() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};
```

**Complexity:** Time $O(1)$ for both `get` and `put`. Space $O(capacity)$ for the hash map and doubly linked list.
**Practice:** https://leetcode.com/problems/lru-cache/

### LFU Cache

::: heavy
LFU Cache demands $O(1)$ eviction by both frequency and time, requiring an architecture of nested hash maps or a hash map pointing to frequency buckets containing doubly linked lists.
:::

Design a data structure that follows the constraints of a Least Frequently Used (LFU) cache. When capacity is reached, it should invalidate and remove the least frequently used key. If there is a tie, remove the least recently used key among them.

**Intuition:**
A simple min-heap based on frequency yields $O(\log n)$ updates, which is too slow. To achieve $O(1)$, we must group nodes by frequency. We need a hash map from `key` to `Node`, and another hash map from `frequency` to a doubly linked list of nodes (which inherently tracks LRU for that specific frequency). 

We also maintain a `min_freq` variable. When a node is accessed, its frequency increases: we remove it from its current frequency list and push it to the `frequency + 1` list. If the `min_freq` list becomes empty as a result, we increment `min_freq`. When eviction is needed, we pop the tail from the list at `min_freq`. `std::list` in C++ provides a ready-made doubly linked list.

```cpp
#include <unordered_map>
#include <list>

using namespace std;

struct Node {
    int key, value, freq;
    Node(int k, int v, int f) : key(k), value(v), freq(f) {}
};

class LFUCache {
    int capacity;
    int min_freq;
    unordered_map<int, list<Node>::iterator> key_table;
    unordered_map<int, list<Node>> freq_table;

public:
    LFUCache(int cap) : capacity(cap), min_freq(0) {}
    
    int get(int key) {
        if (capacity == 0 || key_table.find(key) == key_table.end()) {
            return -1;
        }
        auto it = key_table[key];
        int val = it->value;
        int freq = it->freq;
        
        freq_table[freq].erase(it);
        if (freq_table[freq].empty() && min_freq == freq) {
            min_freq++;
        }
        
        freq_table[freq + 1].push_front(Node(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
        return val;
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        
        if (key_table.find(key) != key_table.end()) {
            auto it = key_table[key];
            it->value = value;
            get(key);
            return;
        }
        
        if (key_table.size() == capacity) {
            auto lru_node = freq_table[min_freq].back();
            key_table.erase(lru_node.key);
            freq_table[min_freq].pop_back();
        }
        
        min_freq = 1;
        freq_table[1].push_front(Node(key, value, 1));
        key_table[key] = freq_table[1].begin();
    }
};
```

**Complexity:** Time $O(1)$ for both `get` and `put` since `std::list::erase` and map lookups are $O(1)$ (average). Space $O(capacity)$ for nodes and hash tables.
**Practice:** https://leetcode.com/problems/lfu-cache/

::: interview
When approaching array or streaming problems, identifying the right tool is half the battle:
- **Matching/nesting boundaries?** Use a stack.
- **Sliding-window extremes?** Use a monotonic deque.
- **Next-greater/smaller element family?** Use a monotonic stack.
- **Cache design (LRU/LFU)?** Combine a hash map with a linked list.
:::
