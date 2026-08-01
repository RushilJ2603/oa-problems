# Linked Lists

::: heavy
A **linked list** is a linear data structure consisting of nodes where each node contains data and one or more pointers to other nodes. Unlike arrays, nodes are heap-allocated and scattered in memory, meaning there is no random access (you cannot jump to the $i$-th element in $O(1)$ time). Lists come in three main varieties: **singly linked** (forward pointer only), **doubly linked** (forward and backward pointers), and **circular** (the tail points back to the head). A linked list beats an array when you need $O(1)$ insertions or deletions at a known position and you want to avoid reallocation overhead. It loses to arrays when you need $O(1)$ indexed access or when cache-friendly contiguous memory is critical.
:::

::: keypoint
The **dummy head** (or sentinel node) trick is a common technique that simplifies operations. By creating a temporary node that points to the actual head of the list, you can handle insertions and deletions at the head using the exact same logic as any other node, eliminating edge cases for an empty list or changing the head.
:::

::: trap
A frequent mistake is losing the entire list by reassigning the `head` pointer directly while traversing, instead of using a temporary pointer (like `curr`). Additionally, always check for `nullptr` before dereferencing a pointer (`node->next` or `node->data`); failing to do so will cause a segmentation fault.
:::

## Singly & Doubly Linked List Basics

### 1. Introduction to Linked List
**Problem:** Construct a singly linked list from an array and traverse it to print its elements.

**Intuition:** 
An array stores elements contiguously, but a linked list requires creating individual nodes and linking them together. To build the list, we can create the `head` node with the first array element, then use a `tail` (or `curr`) pointer to iterate through the rest of the array, appending new nodes in $O(1)$ time per step. Traversing the list simply requires a temporary pointer starting at `head` that advances (`curr = curr->next`) until it hits `nullptr`.

**C++ Solution:**
```cpp
#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* constructList(const std::vector<int>& arr) {
    if (arr.empty()) return nullptr;
    Node* head = new Node(arr[0]);
    Node* curr = head;
    for (size_t i = 1; i < arr.size(); i++) {
        curr->next = new Node(arr[i]);
        curr = curr->next;
    }
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> arr = {10, 20, 30, 40};
    Node* head = constructList(arr);
    printList(head);
    return 0;
}
```

**Complexity:**
- **Time:** $O(N)$, where $N$ is the number of elements in the array. We visit each element once to construct, and once to traverse.
- **Space:** $O(N)$ auxiliary space to allocate the $N$ nodes on the heap.
- **Practice:** https://www.geeksforgeeks.org/problems/introduction-to-linked-list/1

### 2. Insert a Node
**Problem:** Insert a new node with a given value at the head, at the tail, or at a specific position $k$ (1-indexed) in a singly linked list.

**Intuition:**
- **At Head:** Create a new node, point its `next` to the current `head`, and update `head` to this new node.
- **At Tail:** Traverse to the last node (where `next` is `nullptr`) and point its `next` to the new node.
- **At Position $k$:** Traverse to the $(k-1)$-th node. The new node's `next` will point to the $k$-th node, and the $(k-1)$-th node's `next` will point to the new node. If $k=1$, it is an insert-at-head operation.

**C++ Solution:**
```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* insertAtHead(Node* head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    return newNode; // New head
}

Node* insertAtTail(Node* head, int val) {
    if (head == nullptr) return new Node(val);
    Node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = new Node(val);
    return head;
}

Node* insertAtPosition(Node* head, int val, int k) {
    if (k == 1) return insertAtHead(head, val);
    
    Node* curr = head;
    // Traverse to the (k-1)-th node
    for (int i = 1; i < k - 1 && curr != nullptr; i++) {
        curr = curr->next;
    }
    
    // If curr is valid, insert the new node after it
    if (curr != nullptr) {
        Node* newNode = new Node(val);
        newNode->next = curr->next;
        curr->next = newNode;
    }
    return head;
}

void printList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = nullptr;
    head = insertAtHead(head, 20); // List: 20
    head = insertAtHead(head, 10); // List: 10 -> 20
    head = insertAtTail(head, 40); // List: 10 -> 20 -> 40
    head = insertAtPosition(head, 30, 3); // List: 10 -> 20 -> 30 -> 40
    printList(head);
    return 0;
}
```

**Complexity:**
- **Time:** $O(1)$ for inserting at the head. $O(N)$ for inserting at the tail (without a tail pointer) or at a specific position, since we may need to traverse the entire list.
- **Space:** $O(1)$, only modifying pointers.
- **Practice:** https://www.geeksforgeeks.org/problems/linked-list-insertion/1

### 3. Delete a Node
**Problem:** Delete a node at the head, at the tail, by a specific value, or by a position $k$ (1-indexed) in a singly linked list.

**Intuition:**
Deleting a node requires adjusting pointers to bypass the target node and then freeing its memory. 
- **Head:** Move the `head` pointer to `head->next` and delete the old head.
- **Tail / Specific Position:** Traverse to the node *immediately preceding* the node to be deleted. Adjust its `next` pointer to skip the target node, then delete the target node. We must handle edge cases like an empty list or deleting the only node.

**C++ Solution:**
```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* deleteHead(Node* head) {
    if (head == nullptr) return nullptr;
    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}

Node* deleteTail(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        delete head;
        return nullptr;
    }
    Node* curr = head;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
    return head;
}

Node* deletePosition(Node* head, int k) {
    if (head == nullptr) return nullptr;
    if (k == 1) return deleteHead(head);
    
    Node* curr = head;
    for (int i = 1; i < k - 1 && curr != nullptr; i++) {
        curr = curr->next;
    }
    
    if (curr == nullptr || curr->next == nullptr) return head;
    
    Node* temp = curr->next;
    curr->next = curr->next->next;
    delete temp;
    return head;
}

void printList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);
    
    head = deletePosition(head, 2); // Deletes 20
    head = deleteTail(head);        // Deletes 40
    head = deleteHead(head);        // Deletes 10
    
    printList(head); // Output: 30
    return 0;
}
```

**Complexity:**
- **Time:** $O(1)$ for deleting the head. $O(N)$ for deleting the tail or a specific position because traversal is required.
- **Space:** $O(1)$, only pointers are modified.
- **Practice:** https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1

### 4. Length of a Linked List
**Problem:** Find the number of nodes in a singly linked list.

**Intuition:**
Since linked lists do not store their size, we must traverse the list from the `head` to `nullptr`, incrementing a counter at each node.

**C++ Solution:**
```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

int countNodes(Node* head) {
    int length = 0;
    Node* curr = head;
    while (curr != nullptr) {
        length++;
        curr = curr->next;
    }
    return length;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    
    std::cout << "Length: " << countNodes(head) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(N)$ where $N$ is the length of the list. We visit each node exactly once.
- **Space:** $O(1)$ as we only need a counter and a pointer.
- **Practice:** https://www.geeksforgeeks.org/problems/count-nodes-of-linked-list/1

### 5. Search an Element in a Linked List
**Problem:** Determine if a given target value exists in a singly linked list.

**Intuition:**
To search for an element, traverse the linked list starting from the `head`. Compare the `data` of each node to the target value. If a match is found, return true. If the traversal finishes (`curr` reaches `nullptr`) without finding the value, return false.

**C++ Solution:**
```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

bool searchElement(Node* head, int target) {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

int main() {
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    
    std::cout << (searchElement(head, 20) ? "Found" : "Not Found") << "\n";
    std::cout << (searchElement(head, 40) ? "Found" : "Not Found") << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(N)$ in the worst case (the element is at the end or not present).
- **Space:** $O(1)$, only constant space is used.
- **Practice:** https://www.geeksforgeeks.org/problems/search-in-linked-list-1664434326/1

### 6. Introduction to Doubly Linked List
**Problem:** Construct a doubly linked list from an array and traverse it both forward and backward.

**Intuition:**
A doubly linked list node has two pointers: `next` (pointing to the subsequent node) and `prev` (pointing to the preceding node). When constructing the list, each new node must point back to the previous node, and the previous node must point forward to the new node. This two-way linkage enables traversing backwards starting from the tail.

**C++ Solution:**
```cpp
#include <iostream>
#include <vector>

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
    DNode(int x) : data(x), next(nullptr), prev(nullptr) {}
};

DNode* constructDLL(const std::vector<int>& arr) {
    if (arr.empty()) return nullptr;
    DNode* head = new DNode(arr[0]);
    DNode* curr = head;
    
    for (size_t i = 1; i < arr.size(); i++) {
        DNode* newNode = new DNode(arr[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }
    return head;
}

void printForwardAndBackward(DNode* head) {
    DNode* curr = head;
    DNode* tail = nullptr;
    
    std::cout << "Forward: ";
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        tail = curr; // Keep track of the last node
        curr = curr->next;
    }
    std::cout << "\n";
    
    std::cout << "Backward: ";
    while (tail != nullptr) {
        std::cout << tail->data << " ";
        tail = tail->prev;
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4};
    DNode* head = constructDLL(arr);
    printForwardAndBackward(head);
    return 0;
}
```

**Complexity:**
- **Time:** $O(N)$ to iterate through the array and link nodes.
- **Space:** $O(N)$ auxiliary space for $N$ newly allocated nodes.
- **Practice:** https://www.geeksforgeeks.org/problems/introduction-to-doubly-linked-list/1

### 7. Insert in a Doubly Linked List
**Problem:** Insert a node before the head, after the tail, or at a specific position (e.g., after the $k$-th node) in a doubly linked list.

**Intuition:**
Inserting requires carefully updating up to four pointers (the `next` and `prev` of both the new node and its neighbors).
- **At Head:** The new node's `next` becomes the old `head`, and the old `head`'s `prev` becomes the new node.
- **At Position $k$:** Traverse to the $k$-th node. The new node sits between node $k$ and node $k+1$. Connect the new node to both, then update node $k$'s `next` and node $k+1$'s `prev`.

**C++ Solution:**
```cpp
#include <iostream>

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
    DNode(int x) : data(x), next(nullptr), prev(nullptr) {}
};

DNode* insertBeforeHead(DNode* head, int val) {
    DNode* newNode = new DNode(val);
    if (head != nullptr) {
        newNode->next = head;
        head->prev = newNode;
    }
    return newNode; // New head
}

// Inserts after the k-th node (1-indexed)
DNode* insertAfterPosition(DNode* head, int val, int k) {
    DNode* curr = head;
    for (int i = 1; i < k && curr != nullptr; i++) {
        curr = curr->next;
    }
    
    if (curr == nullptr) return head;
    
    DNode* newNode = new DNode(val);
    newNode->next = curr->next;
    newNode->prev = curr;
    
    if (curr->next != nullptr) {
        curr->next->prev = newNode;
    }
    curr->next = newNode;
    
    return head;
}

void printList(DNode* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    DNode* head = new DNode(10);
    head = insertBeforeHead(head, 5); // 5 <-> 10
    head = insertAfterPosition(head, 15, 2); // Insert after 2nd node: 5 <-> 10 <-> 15
    printList(head);
    return 0;
}
```

**Complexity:**
- **Time:** $O(1)$ for inserting at the head. $O(N)$ for inserting at a specific position due to traversal.
- **Space:** $O(1)$ as we only adjust pointers.
- **Practice:** https://www.geeksforgeeks.org/problems/insert-a-node-in-doubly-linked-list/1

### 8. Delete a Node in a Doubly Linked List
**Problem:** Delete the head, the tail, or a node at a specific position in a doubly linked list.

**Intuition:**
To delete a node in a doubly linked list, we bypass it by connecting its `prev` neighbor directly to its `next` neighbor, and vice versa.
- If deleting the head, update the new head's `prev` to `nullptr`.
- If deleting the tail, update the new tail's `next` to `nullptr`.
Always ensure you check for `nullptr` before dereferencing neighbors, especially when deleting the only node in the list.

**C++ Solution:**
```cpp
#include <iostream>

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
    DNode(int x) : data(x), next(nullptr), prev(nullptr) {}
};

DNode* deleteHead(DNode* head) {
    if (head == nullptr) return nullptr;
    DNode* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
    return head;
}

DNode* deletePosition(DNode* head, int k) {
    if (head == nullptr) return nullptr;
    if (k == 1) return deleteHead(head);
    
    DNode* curr = head;
    for (int i = 1; i < k && curr != nullptr; i++) {
        curr = curr->next;
    }
    
    if (curr == nullptr) return head; // Position out of bounds
    
    // Connect previous node to next node
    if (curr->prev != nullptr) {
        curr->prev->next = curr->next;
    }
    // Connect next node to previous node
    if (curr->next != nullptr) {
        curr->next->prev = curr->prev;
    }
    
    delete curr;
    return head;
}

void printList(DNode* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    DNode* head = new DNode(10);
    DNode* n2 = new DNode(20);
    DNode* n3 = new DNode(30);
    
    head->next = n2; n2->prev = head;
    n2->next = n3; n3->prev = n2;
    
    head = deletePosition(head, 2); // Deletes 20
    printList(head); // Output: 10 30
    return 0;
}
```

**Complexity:**
- **Time:** $O(1)$ for deleting the head. $O(N)$ for deleting a specific position because we must traverse to it.
- **Space:** $O(1)$, since deletion is done in place.
- **Practice:** https://www.geeksforgeeks.org/problems/delete-node-in-doubly-linked-list/1

### 9. Reverse a Doubly Linked List
**Problem:** Reverse a doubly linked list in place.

**Intuition:**
A doubly linked list can be reversed by swapping the `next` and `prev` pointers for every single node. We traverse the list, and at each node, we swap its two pointers. Because the `next` pointer is updated to point backward, we must use the original `prev` (which is now stored in `next` after the swap? No, original `next` is now stored in `prev`) to continue our traversal. The new `head` will be the last node we successfully process.

**C++ Solution:**
```cpp
#include <iostream>

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
    DNode(int x) : data(x), next(nullptr), prev(nullptr) {}
};

DNode* reverseDLL(DNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    DNode* curr = head;
    DNode* temp = nullptr;
    
    // Swap next and prev for all nodes
    while (curr != nullptr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        
        // Move to the next node in the original list
        // which is now curr->prev due to the swap
        curr = curr->prev;
    }
    
    // After the loop, temp points to the old second-to-last node.
    // The new head is temp->prev (which was the old tail).
    return temp->prev;
}

void printList(DNode* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    DNode* head = new DNode(1);
    DNode* n2 = new DNode(2);
    DNode* n3 = new DNode(3);
    
    head->next = n2; n2->prev = head;
    n2->next = n3; n3->prev = n2;
    
    head = reverseDLL(head);
    printList(head); // Output: 3 2 1
    return 0;
}
```

**Complexity:**
- **Time:** $O(N)$, as we traverse every node exactly once to swap pointers.
- **Space:** $O(1)$, reversing is performed strictly in-place with a few auxiliary pointers.
- **Practice:** https://www.geeksforgeeks.org/problems/reverse-a-doubly-linked-list/1

## Medium Linked List Problems

### Middle of the Linked List
Given the head of a singly linked list, return the middle node of the linked list. If there are two middle nodes, return the second middle node.

**Intuition:**
A naive approach is to traverse the linked list to find its length $n$, and then traverse again to the $\lfloor n/2 \rfloor$-th node. This requires two passes. 
An optimal approach uses the tortoise and hare technique. We maintain a `slow` pointer moving one step at a time and a `fast` pointer moving two steps. When `fast` reaches the end of the list, `slow` will be exactly at the middle.

::: keypoint
The slow and fast pointer (tortoise and hare) technique is the canonical way to find the middle of a linked list in a single pass.
:::

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* middleNode(Node* head) {
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    
    Node* mid = middleNode(head);
    if (mid) {
        std::cout << "Middle node data: " << mid->data << "\n";
    }
    return 0;
}
```

**Complexity:** Time is $O(n)$ because the fast pointer traverses the list once. Space is $O(1)$ since only two pointers are used.
**Practice:** https://leetcode.com/problems/middle-of-the-linked-list/

### Reverse a Linked List — Iterative
Given the head of a singly linked list, reverse the list and return its new head.

**Intuition:**
To reverse a list iteratively, we need to reverse the direction of the `next` pointers. We maintain three pointers: `prev` (initially `nullptr`), `curr` (initially `head`), and `nextTemp`. As we iterate, we store the next node, reverse the current node's pointer to point to `prev`, and then step `prev` and `curr` forward.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    
    while (curr != nullptr) {
        Node* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    
    return prev;
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    
    head = reverseList(head);
    printList(head); // Expected: 3 2 1
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ as we visit each node exactly once. Space is $O(1)$ as we only use a few pointers.
**Practice:** https://leetcode.com/problems/reverse-linked-list/

### Reverse a Linked List — Recursive
Given the head of a singly linked list, reverse the list using recursion and return its new head.

**Intuition:**
A recursive approach assumes that the rest of the list has already been reversed, and we just need to correctly attach the current node to the reversed sublist. For a node `curr`, if the rest of the list is reversed, its original next node `curr->next` will be the tail of the reversed sublist. We make `curr->next->next` point back to `curr`, and set `curr->next` to `nullptr`.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* reverseListRecursive(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    Node* newHead = reverseListRecursive(head->next);
    
    head->next->next = head;
    head->next = nullptr;
    
    return newHead;
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    
    head = reverseListRecursive(head);
    printList(head); // Expected: 3 2 1
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ to reach the end of the list. Space is $O(n)$ due to the call stack depth from recursion.
**Practice:** https://leetcode.com/problems/reverse-linked-list/

### Detect a Loop / Cycle
Given the `head` of a linked list, determine if the linked list has a cycle in it.

**Intuition:**
A brute force approach involves using a hash set to store visited nodes. If we encounter a node already in the set, a cycle exists. This takes $O(n)$ space.
The optimal solution is Floyd's cycle detection algorithm. We use a slow pointer and a fast pointer. If there is a cycle, the fast pointer will eventually lap the slow pointer and they will meet. If the fast pointer reaches `nullptr`, there is no cycle.

::: keypoint
Floyd's cycle detection algorithm (tortoise and hare) uses two pointers moving at different speeds to detect cycles in $O(1)$ space.
:::

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

bool hasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    
    return false;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = head->next; // Creates a cycle at node 2
    
    std::cout << (hasCycle(head) ? "Cycle detected" : "No cycle") << "\n";
    
    return 0;
}
```

**Complexity:** Time is $O(n)$. In the worst case, the fast pointer traverses the cycle a finite number of times before meeting the slow pointer. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/linked-list-cycle/

### Starting Point of the Loop
Given the `head` of a linked list, return the node where the cycle begins. If there is no cycle, return `nullptr`.

**Intuition:**
We can use a hash set to store nodes and return the first node we see twice (taking $O(n)$ space).
Optimally, we extend Floyd's cycle detection. Once the slow and fast pointers meet inside the loop, we reset the slow pointer to the `head` of the list and keep the fast pointer at the meeting point. We then move both pointers one step at a time. The node where they meet again is guaranteed to be the starting point of the loop.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* detectCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    
    return nullptr;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = head->next; // Cycle starts at node 2
    
    Node* start = detectCycle(head);
    if (start) {
        std::cout << "Cycle starts at node with data: " << start->data << "\n";
    }
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ since each pointer traverses the list linearly. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/linked-list-cycle-ii/

### Length of the Loop
Given a linked list that contains a loop, find the length of the loop.

**Intuition:**
We first detect the loop using the slow and fast pointer approach. Once they meet inside the loop, the meeting node is part of the loop. To find the length, we can keep the slow pointer fixed at the meeting point and move the fast pointer one step at a time until it returns to the slow pointer, counting the steps along the way.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

int countNodesInLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            int count = 1;
            fast = fast->next;
            while (slow != fast) {
                count++;
                fast = fast->next;
            }
            return count;
        }
    }
    
    return 0;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = head->next; // Loop size 3 (nodes 2, 3, 4)
    
    std::cout << "Length of loop: " << countNodesInLoop(head) << "\n";
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ to detect the cycle and count the nodes. Space is $O(1)$.
**Practice:** https://www.geeksforgeeks.org/find-length-of-loop-in-linked-list/

### Check if a Linked List is a Palindrome
Given the `head` of a singly linked list, return true if it is a palindrome.

**Intuition:**
A brute force approach copies all node values into an array and checks if the array is a palindrome (taking $O(n)$ space).
The optimal approach avoids extra space by modifying the list:
1. Find the middle of the linked list using the slow/fast pointer technique.
2. Reverse the second half of the linked list.
3. Compare the first half and the reversed second half node by node.
4. (Optional but good practice) Restore the list to its original state by reversing the second half again.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr) {
        Node* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}

bool isPalindrome(Node* head) {
    if (head == nullptr || head->next == nullptr) return true;
    
    // Step 1: Find middle
    Node* slow = head;
    Node* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Step 2: Reverse second half
    Node* secondHalf = reverseList(slow->next);
    
    // Step 3: Compare halves
    Node* p1 = head;
    Node* p2 = secondHalf;
    bool palindrome = true;
    while (p2 != nullptr) {
        if (p1->data != p2->data) {
            palindrome = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    
    // Step 4: Restore list (optional)
    slow->next = reverseList(secondHalf);
    
    return palindrome;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(2);
    head->next->next->next = new Node(1);
    
    std::cout << (isPalindrome(head) ? "Palindrome" : "Not Palindrome") << "\n";
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ as we traverse the list a constant number of times. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/palindrome-linked-list/

### Segregate Odd and Even Nodes
Given the `head` of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list. (The first node is considered odd, the second is even, and so on).

**Intuition:**
We can separate the list into two disjoint lists: one containing odd-indexed nodes and the other containing even-indexed nodes. We keep track of the head of the even list to eventually connect the tail of the odd list to it. We iterate through the list, linking odd nodes to the next odd node and even nodes to the next even node.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* oddEvenList(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    Node* odd = head;
    Node* even = head->next;
    Node* evenHead = even;
    
    while (even != nullptr && even->next != nullptr) {
        odd->next = odd->next->next;
        odd = odd->next;
        
        even->next = even->next->next;
        even = even->next;
    }
    
    odd->next = evenHead;
    return head;
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    
    head = oddEvenList(head);
    printList(head); // Expected: 1 3 5 2 4
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ since we process each node once. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/odd-even-linked-list/

### Remove Nth Node from the End
Given the `head` of a linked list, remove the $n$-th node from the end of the list and return its head.

**Intuition:**
A two-pass solution finds the length of the list, $L$, and then removes the $(L - n + 1)$-th node from the start.
An optimal one-pass solution uses two pointers. We move a `fast` pointer $n$ steps ahead. Then, we move both `slow` and `fast` pointers at the same pace. When `fast` reaches the last node, `slow` will be exactly at the node *before* the one we need to delete. Using a dummy head handles edge cases (like removing the head node) cleanly.

::: keypoint
A dummy node pointing to the head simplifies edge cases where the head itself might be deleted or modified. The gap between the fast and slow pointer ensures we find the target node from the end in one pass.
:::

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* removeNthFromEnd(Node* head, int n) {
    Node* dummy = new Node(0);
    dummy->next = head;
    
    Node* slow = dummy;
    Node* fast = dummy;
    
    // Move fast n steps ahead
    for (int i = 0; i < n; ++i) {
        fast = fast->next;
    }
    
    // Move both until fast reaches the last node
    while (fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }
    
    // Remove the nth node
    Node* nodeToDelete = slow->next;
    slow->next = slow->next->next;
    delete nodeToDelete;
    
    Node* newHead = dummy->next;
    delete dummy;
    
    return newHead;
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    
    head = removeNthFromEnd(head, 2);
    printList(head); // Expected: 1 2 3 5
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ as we make exactly one pass through the list. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/remove-nth-node-from-end-of-list/

### Delete the Middle Node
Given the `head` of a linked list, delete the middle node and return the modified list's head.

**Intuition:**
We can use the tortoise and hare approach to find the middle node, but to delete it, we need a pointer to the node *before* the middle node. By using a `prev` pointer, we can stop right before the middle node and bypass it.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* deleteMiddle(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        delete head;
        return nullptr;
    }
    
    Node* slow = head;
    Node* fast = head;
    Node* prev = nullptr;
    
    while (fast != nullptr && fast->next != nullptr) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    prev->next = slow->next;
    delete slow;
    
    return head;
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    
    head = deleteMiddle(head);
    printList(head); // Expected: 1 2 4 5
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ to reach the middle of the list. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/

### Sort a Linked List
Given the `head` of a linked list, return the list after sorting it in ascending order.

**Intuition:**
A naive approach is to copy all values to an array, sort the array, and reconstruct the linked list, taking $O(n)$ space.
To sort a linked list in $O(n \log n)$ time and $O(1)$ space (ignoring the recursion stack), merge sort is the most suitable algorithm. We recursively divide the list into two halves using the slow/fast pointer technique, sort them, and merge the two sorted halves.

::: keypoint
Merge sort is the ideal sorting algorithm for linked lists because it sequentially processes elements without requiring random access, yielding $O(n \log n)$ time and $O(1)$ auxiliary space.
:::

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* merge(Node* l1, Node* l2) {
    Node* dummy = new Node(0);
    Node* tail = dummy;
    
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->data < l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    if (l1 != nullptr) tail->next = l1;
    if (l2 != nullptr) tail->next = l2;
    
    Node* res = dummy->next;
    delete dummy;
    return res;
}

Node* sortList(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    // Find middle and split list
    Node* slow = head;
    Node* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    Node* mid = slow->next;
    slow->next = nullptr;
    
    Node* left = sortList(head);
    Node* right = sortList(mid);
    
    return merge(left, right);
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = new Node(4);
    head->next = new Node(2);
    head->next->next = new Node(1);
    head->next->next->next = new Node(3);
    
    head = sortList(head);
    printList(head); // Expected: 1 2 3 4
    
    return 0;
}
```

**Complexity:** Time is $O(n \log n)$ due to the merge sort recurrences. Space is $O(\log n)$ due to the recursion stack.
**Practice:** https://leetcode.com/problems/sort-list/

### Sort a Linked List of 0s, 1s and 2s
Given a linked list consisting of only `0`s, `1`s, and `2`s, sort the list.

**Intuition:**
We can solve this in two passes by counting the occurrences of 0, 1, and 2, and then overwriting the data of nodes. However, modifying data is often discouraged in linked lists.
A better approach rearranges the pointers in one pass. We create three separate dummy nodes for 0, 1, and 2. We traverse the original list, append each node to its respective list, and finally connect the three lists together.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* sort012(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    
    Node* zeroDummy = new Node(0);
    Node* oneDummy = new Node(0);
    Node* twoDummy = new Node(0);
    
    Node* zero = zeroDummy;
    Node* one = oneDummy;
    Node* two = twoDummy;
    
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == 0) {
            zero->next = curr;
            zero = zero->next;
        } else if (curr->data == 1) {
            one->next = curr;
            one = one->next;
        } else {
            two->next = curr;
            two = two->next;
        }
        curr = curr->next;
    }
    
    // Connect the three lists
    zero->next = (oneDummy->next != nullptr) ? oneDummy->next : twoDummy->next;
    one->next = twoDummy->next;
    two->next = nullptr; // Terminate the final list
    
    Node* newHead = zeroDummy->next;
    
    delete zeroDummy;
    delete oneDummy;
    delete twoDummy;
    
    return newHead;
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(0);
    head->next->next = new Node(2);
    head->next->next->next = new Node(1);
    head->next->next->next->next = new Node(0);
    
    head = sort012(head);
    printList(head); // Expected: 0 0 1 1 2
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ for a single traversal. Space is $O(1)$ as we only allocate a few dummy nodes.
**Practice:** https://www.geeksforgeeks.org/sort-a-linked-list-of-0s-1s-or-2s/

### Intersection Point of Two Linked Lists
Given the heads of two singly linked lists `headA` and `headB`, return the node at which the two lists intersect. If the two linked lists have no intersection, return `nullptr`.

**Intuition:**
A hash set approach stores all nodes of list A and checks if any node from list B is in the set, taking $O(n)$ space.
To achieve $O(1)$ space, we can compute the lengths of both lists. The difference in lengths tells us how far ahead we must advance the pointer of the longer list so both pointers are equidistant from the intersection.
An even more elegant solution uses two pointers. When pointer $A$ reaches the end of list A, redirect it to the head of list B. When pointer $B$ reaches the end of list B, redirect it to the head of list A. They will traverse the same total distance ($A + B$) and meet at the intersection point simultaneously.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* getIntersectionNode(Node* headA, Node* headB) {
    if (headA == nullptr || headB == nullptr) return nullptr;
    
    Node* pA = headA;
    Node* pB = headB;
    
    while (pA != pB) {
        pA = (pA == nullptr) ? headB : pA->next;
        pB = (pB == nullptr) ? headA : pB->next;
    }
    
    return pA;
}

int main() {
    Node* common = new Node(8);
    common->next = new Node(10);
    
    Node* headA = new Node(4);
    headA->next = new Node(1);
    headA->next->next = common;
    
    Node* headB = new Node(5);
    headB->next = new Node(6);
    headB->next->next = new Node(1);
    headB->next->next->next = common;
    
    Node* intersection = getIntersectionNode(headA, headB);
    if (intersection) {
        std::cout << "Intersect at node with data: " << intersection->data << "\n";
    }
    
    return 0;
}
```

**Complexity:** Time is $O(n + m)$ where $n$ and $m$ are the lengths of the two lists. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/intersection-of-two-linked-lists/

### Add 1 to a Number Represented as a Linked List
Given a number represented by a linked list (where each node contains a single digit), add 1 to the number and return the modified linked list.

**Intuition:**
Addition happens from right to left (least significant to most significant digit). To do this, we can reverse the linked list, add 1 starting from the head while keeping track of carries, and then reverse the list again.
Alternatively, a recursive approach naturally visits the end of the list and propagates the carry backward as the recursion unwinds.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

int addOneHelper(Node* head) {
    if (head == nullptr) return 1;
    
    int carry = addOneHelper(head->next);
    int sum = head->data + carry;
    head->data = sum % 10;
    return sum / 10;
}

Node* addOne(Node* head) {
    int carry = addOneHelper(head);
    
    if (carry > 0) {
        Node* newHead = new Node(carry);
        newHead->next = head;
        return newHead;
    }
    
    return head;
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    Node* head = new Node(9);
    head->next = new Node(9);
    head->next->next = new Node(9);
    
    head = addOne(head);
    printList(head); // Expected: 1 0 0 0
    
    return 0;
}
```

**Complexity:** Time is $O(n)$ as we visit every node. Space is $O(n)$ for the recursion stack (or $O(1)$ if we use the iterative list reversal approach).
**Practice:** https://www.geeksforgeeks.org/add-1-to-a-number-represented-as-linked-list/

### Add Two Numbers Represented as Linked Lists
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

**Intuition:**
Because the digits are stored in reverse order, the heads of the lists correspond to the least significant digits. We can simulate the standard addition process by iterating through both lists, adding the corresponding digits and a carry from the previous position. We build a new list to store the results and manage the carry. A dummy head makes appending to the new list easy.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* addTwoNumbers(Node* l1, Node* l2) {
    Node* dummy = new Node(0);
    Node* curr = dummy;
    int carry = 0;
    
    while (l1 != nullptr || l2 != nullptr || carry > 0) {
        int sum = carry;
        if (l1 != nullptr) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2 != nullptr) {
            sum += l2->data;
            l2 = l2->next;
        }
        
        carry = sum / 10;
        curr->next = new Node(sum % 10);
        curr = curr->next;
    }
    
    Node* res = dummy->next;
    delete dummy;
    return res;
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    // 342 (represented as 2 -> 4 -> 3)
    Node* l1 = new Node(2);
    l1->next = new Node(4);
    l1->next->next = new Node(3);
    
    // 465 (represented as 5 -> 6 -> 4)
    Node* l2 = new Node(5);
    l2->next = new Node(6);
    l2->next->next = new Node(4);
    
    Node* sumList = addTwoNumbers(l1, l2);
    printList(sumList); // Expected: 7 0 8 (represents 807)
    
    return 0;
}
```

**Complexity:** Time is $O(\max(n, m))$ where $n$ and $m$ are the lengths of the two lists. Space is $O(\max(n, m))$ for the newly created sum list.
**Practice:** https://leetcode.com/problems/add-two-numbers/

## Doubly List Medium & Hard Problems

### Delete all Occurrences of a Key in a Doubly Linked List

Given a doubly linked list and a key `k`, delete all nodes with the value `k`.

**Intuition:** 
A naive approach would be to traverse the list, find a node with the key, delete it by adjusting pointers, and restart the traversal from the head until no such node is found. This takes $O(n^2)$ time.
An optimal approach traverses the list exactly once. We iterate through the list, and whenever we find a node with the key `k`, we adjust the `next` pointer of the previous node (if it exists) and the `prev` pointer of the next node (if it exists) to bypass the current node. If the node to delete is the head, we must also update the head pointer.

```cpp
#include <iostream>

struct DNode { 
    int data; 
    DNode* next; 
    DNode* prev; 
    DNode(int x) : data(x), next(nullptr), prev(nullptr) {} 
};

DNode* deleteAllOccurrences(DNode* head, int k) {
    DNode* temp = head;
    while (temp != nullptr) {
        if (temp->data == k) {
            DNode* nodeToDelete = temp;
            if (temp == head) {
                head = temp->next;
            }
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }
            temp = temp->next;
            delete nodeToDelete;
        } else {
            temp = temp->next;
        }
    }
    return head;
}

int main() {
    DNode* head = new DNode(10);
    head->next = new DNode(4); head->next->prev = head;
    head->next->next = new DNode(10); head->next->next->prev = head->next;
    head->next->next->next = new DNode(10); head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new DNode(6); head->next->next->next->next->prev = head->next->next->next;
    
    head = deleteAllOccurrences(head, 10);
    
    DNode* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    return 0;
}
```

**Complexity:** Time is $O(n)$ where $n$ is the number of nodes in the list. Space is $O(1)$ since we modify the list in place.

**Practice:** https://www.geeksforgeeks.org/problems/delete-all-occurrences-of-a-given-key-in-a-doubly-linked-list/1

### Find Pairs with a Given Sum in a Sorted Doubly Linked List

Given a sorted doubly linked list of distinct positive integers and a target sum, find all pairs of nodes whose sum equals the target.

**Intuition:**
The brute-force solution uses two nested loops, checking every possible pair for the target sum, taking $O(n^2)$ time.
Since the list is sorted and doubly linked (which means we can traverse backward), we can use a two-pointer approach, similar to finding a pair in a sorted array. We place a `left` pointer at the head of the list and a `right` pointer at the tail. If the sum of their values is the target, we record the pair and move both pointers inward. If the sum is less than the target, we move `left` to the right to increase the sum. If the sum is greater, we move `right` to the left to decrease the sum. We stop when `left` and `right` meet or cross.

```cpp
#include <iostream>
#include <vector>
#include <utility>

struct DNode { 
    int data; 
    DNode* next; 
    DNode* prev; 
    DNode(int x) : data(x), next(nullptr), prev(nullptr) {} 
};

std::vector<std::pair<int, int>> findPairsWithGivenSum(DNode* head, int target) {
    std::vector<std::pair<int, int>> ans;
    if (head == nullptr) return ans;
    
    DNode* left = head;
    DNode* right = head;
    while (right->next != nullptr) {
        right = right->next;
    }
    
    while (left != nullptr && right != nullptr && left != right && left->prev != right) {
        int currentSum = left->data + right->data;
        if (currentSum == target) {
            ans.push_back({left->data, right->data});
            left = left->next;
            right = right->prev;
        } else if (currentSum < target) {
            left = left->next;
        } else {
            right = right->prev;
        }
    }
    
    return ans;
}

int main() {
    DNode* head = new DNode(1);
    head->next = new DNode(2); head->next->prev = head;
    head->next->next = new DNode(4); head->next->next->prev = head->next;
    head->next->next->next = new DNode(5); head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new DNode(6); head->next->next->next->next->prev = head->next->next->next;
    head->next->next->next->next->next = new DNode(8); head->next->next->next->next->next->prev = head->next->next->next->next;
    head->next->next->next->next->next->next = new DNode(9); head->next->next->next->next->next->next->prev = head->next->next->next->next->next;
    
    std::vector<std::pair<int, int>> pairs = findPairsWithGivenSum(head, 7);
    for (const auto& p : pairs) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    return 0;
}
```

**Complexity:** Time is $O(n)$ where $n$ is the number of nodes in the list, as the `left` and `right` pointers will traverse the list at most once. Space is $O(1)$ (excluding the output array).

**Practice:** https://www.geeksforgeeks.org/problems/find-pairs-with-given-sum-in-doubly-linked-list/1

### Remove Duplicates from a Sorted Doubly Linked List

Given a sorted doubly linked list, remove all duplicate nodes such that each element appears only once.

**Intuition:**
We can iterate through the linked list with a pointer. Since the list is sorted, any duplicates will be adjacent. When we are at a node, we can keep moving a `next` pointer forward until we find a node with a different value. We then link our current node directly to that different node, bypassing all the duplicates, and correctly updating the `prev` pointers.

```cpp
#include <iostream>

struct DNode { 
    int data; 
    DNode* next; 
    DNode* prev; 
    DNode(int x) : data(x), next(nullptr), prev(nullptr) {} 
};

DNode* removeDuplicates(DNode* head) {
    if (head == nullptr) return nullptr;
    
    DNode* temp = head;
    while (temp != nullptr && temp->next != nullptr) {
        DNode* nextNode = temp->next;
        while (nextNode != nullptr && nextNode->data == temp->data) {
            DNode* duplicate = nextNode;
            nextNode = nextNode->next;
            delete duplicate;
        }
        temp->next = nextNode;
        if (nextNode != nullptr) {
            nextNode->prev = temp;
        }
        temp = temp->next;
    }
    return head;
}

int main() {
    DNode* head = new DNode(1);
    head->next = new DNode(1); head->next->prev = head;
    head->next->next = new DNode(2); head->next->next->prev = head->next;
    head->next->next->next = new DNode(3); head->next->next->next->prev = head->next->next;
    head->next->next->next->next = new DNode(3); head->next->next->next->next->prev = head->next->next->next;
    
    head = removeDuplicates(head);
    
    DNode* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    return 0;
}
```

**Complexity:** Time is $O(n)$ where $n$ is the number of nodes. Space is $O(1)$ since we update links in place.

**Practice:** https://www.geeksforgeeks.org/problems/remove-duplicates-from-a-sorted-doubly-linked-list/1

### Reverse Nodes in Groups of Size K

Given the head of a singly linked list, reverse the nodes of the list `k` at a time, and return the modified list. If the number of nodes is not a multiple of `k`, the left-out nodes at the end should remain as they are.

::: keypoint
The trick to in-place sub-list reversal is maintaining a pointer to the node *before* the current group of $k$, allowing you to splice the newly reversed sub-list back into the main list.
:::

**Intuition:**
A brute-force approach could extract the values into an array, reverse the values in chunks of size `k`, and write them back into the list. This uses $O(n)$ extra space.
For an optimal $O(1)$ space solution, we count the number of nodes in the list to determine how many full groups of size `k` exist. For each full group, we reverse the $k$ nodes in place using standard pointer reversal. We maintain a `dummy` node to simplify operations at the head, and use pointers to keep track of the node just before the group being reversed (`prevGroupTail`), and the first node of the group being reversed (`curr`), which becomes the tail of the group after reversal.

```cpp
#include <iostream>

struct Node { 
    int data; 
    Node* next; 
    Node(int x) : data(x), next(nullptr) {} 
};

Node* reverseKGroup(Node* head, int k) {
    if (head == nullptr || k == 1) return head;

    int count = 0;
    Node* curr = head;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }

    Node* dummy = new Node(0);
    dummy->next = head;
    Node* prevGroupTail = dummy;
    curr = head;

    while (count >= k) {
        Node* prev = nullptr;
        Node* nextNode = nullptr;
        Node* groupHead = curr;
        
        for (int i = 0; i < k; ++i) {
            nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        
        prevGroupTail->next = prev;
        groupHead->next = curr;
        prevGroupTail = groupHead;
        
        count -= k;
    }

    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    
    head = reverseKGroup(head, 2);
    
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    return 0;
}
```

**Complexity:** Time is $O(n)$ since each node is visited at most twice. Space is $O(1)$ using constant extra pointers.

**Practice:** https://leetcode.com/problems/reverse-nodes-in-k-group/

### Rotate a Linked List

Given the head of a linked list, rotate the list to the right by `k` places.

**Intuition:**
A naive approach would be to move the last element to the front `k` times, taking $O(n \times k)$ time.
Optimally, we realize that rotating the list by `k` places means the last `k % n` nodes will be moved to the front (where `n` is the length of the list). We can first traverse the list to find its length and the original tail node. We link the tail to the head, making it a circular list. Then, we find the new tail, which is at position `n - (k % n)` from the original head. The new head is the next node. Finally, we break the cycle by setting the new tail's `next` pointer to `nullptr`.

```cpp
#include <iostream>

struct Node { 
    int data; 
    Node* next; 
    Node(int x) : data(x), next(nullptr) {} 
};

Node* rotateRight(Node* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) return head;

    int len = 1;
    Node* tail = head;
    while (tail->next != nullptr) {
        len++;
        tail = tail->next;
    }

    k = k % len;
    if (k == 0) return head;

    tail->next = head; // create a cycle

    int stepsToNewTail = len - k;
    Node* newTail = head;
    for (int i = 1; i < stepsToNewTail; ++i) {
        newTail = newTail->next;
    }

    Node* newHead = newTail->next;
    newTail->next = nullptr; // break the cycle

    return newHead;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    
    head = rotateRight(head, 2);
    
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    return 0;
}
```

**Complexity:** Time is $O(n)$ where $n$ is the number of nodes, as we traverse the list to find the length and then to the new tail. Space is $O(1)$.

**Practice:** https://leetcode.com/problems/rotate-list/

### Flattening a Linked List

Given a linked list where every node represents a linked list and contains two pointers of its type: an ordinary `next` pointer to the next node, and a `bottom` pointer to a sub-linked list. The sub-linked lists are sorted. Flatten the list into a single sorted linked list using the `bottom` pointer.

::: heavy
Flattening a linked list requires a bottom-up recursive approach. Because each sub-list is already sorted, the operation mimics the merge step of Merge Sort, combining the last two lists, then merging the result with the third-to-last, and so on.
:::

**Intuition:**
A naive approach would extract all values by traversing the `next` and `bottom` pointers, sort them in an array, and construct a new flattened linked list, which takes $O(N \log N)$ time and $O(N)$ extra space.
Optimally, we can merge the linked lists pair by pair. Using recursion, we go to the rightmost node of the top-level list, and start returning backward. At each step, we merge the current list (pointed to by `bottom` pointers) with the already flattened list returned from the recursive call. We use the standard algorithm to merge two sorted linked lists.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* bottom;
    Node(int x) : data(x), next(nullptr), bottom(nullptr) {}
};

Node* mergeTwoLists(Node* a, Node* b) {
    Node* dummy = new Node(0);
    Node* temp = dummy;
    while (a != nullptr && b != nullptr) {
        if (a->data < b->data) {
            temp->bottom = a;
            a = a->bottom;
        } else {
            temp->bottom = b;
            b = b->bottom;
        }
        temp = temp->bottom;
    }
    if (a != nullptr) temp->bottom = a;
    else temp->bottom = b;
    
    Node* res = dummy->bottom;
    delete dummy;
    return res;
}

Node* flatten(Node* root) {
    if (root == nullptr || root->next == nullptr) {
        return root;
    }
    
    // Recur for list on right
    root->next = flatten(root->next);
    
    // Merge current and right
    root = mergeTwoLists(root, root->next);
    
    return root;
}

int main() {
    Node* head = new Node(5);
    head->bottom = new Node(7);
    head->bottom->bottom = new Node(8);
    head->bottom->bottom->bottom = new Node(30);

    head->next = new Node(10);
    head->next->bottom = new Node(20);
    
    head->next->next = new Node(19);
    head->next->next->bottom = new Node(22);
    head->next->next->bottom->bottom = new Node(50);
    
    head->next->next->next = new Node(28);
    head->next->next->next->bottom = new Node(35);
    head->next->next->next->bottom->bottom = new Node(40);
    head->next->next->next->bottom->bottom->bottom = new Node(45);
    
    head = flatten(head);
    
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->bottom;
    }
    return 0;
}
```

**Complexity:** Time is $O(N)$ where $N$ is the total number of nodes across all sub-lists. We merge progressively larger lists, leading to proportional total work. Space is $O(1)$ auxiliary space if iterative, but recursion takes $O(k)$ call stack space where $k$ is the number of nodes in the top-level list.

**Practice:** https://www.geeksforgeeks.org/problems/flattening-a-linked-list/1

### Clone a Linked List with Random and Next Pointers

Given a linked list where every node contains an additional `random` pointer which could point to any node in the list or `nullptr`, construct a deep copy of the list.

::: keypoint
We can avoid using $O(n)$ extra space for a hash map by weaving the cloned nodes directly into the original list (placing each clone immediately after its original), updating the random pointers, and then separating them back into two distinct lists.
:::

**Intuition:**
A simple brute force approach uses a Hash Map (`unordered_map<Node*, Node*>`) to store the mapping from each original node to its newly created clone. In a second pass, we can populate the `next` and `random` pointers of the clones using the hash map. This takes $O(n)$ space.
The optimal $O(1)$ space approach does this in three passes without a map:
1. **Insert Clones:** Iterate through the original list and insert a cloned node just after every original node (`A -> A' -> B -> B'`).
2. **Assign Random Pointers:** Since `A->random` points to `C`, the cloned node `A'` should point to `C'`. We can find `C'` easily because it is exactly `A->random->next`.
3. **Extract Clones:** Detach the cloned nodes to form the deep copy, restoring the original list to its initial state.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* random;
    Node(int x) : data(x), next(nullptr), random(nullptr) {}
};

Node* copyRandomList(Node* head) {
    if (head == nullptr) return nullptr;

    // Step 1: Create interleaved cloned nodes
    Node* curr = head;
    while (curr != nullptr) {
        Node* clone = new Node(curr->data);
        clone->next = curr->next;
        curr->next = clone;
        curr = clone->next;
    }

    // Step 2: Assign random pointers for cloned nodes
    curr = head;
    while (curr != nullptr) {
        if (curr->random != nullptr) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }

    // Step 3: Extract the cloned list and restore original
    Node* dummy = new Node(0);
    Node* cloneTail = dummy;
    curr = head;

    while (curr != nullptr) {
        cloneTail->next = curr->next;
        cloneTail = cloneTail->next;
        
        curr->next = curr->next->next;
        curr = curr->next;
    }

    Node* cloneHead = dummy->next;
    delete dummy;
    return cloneHead;
}

int main() {
    Node* node1 = new Node(7);
    Node* node2 = new Node(13);
    Node* node3 = new Node(11);
    Node* node4 = new Node(10);
    Node* node5 = new Node(1);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    node1->random = nullptr;
    node2->random = node1;
    node3->random = node5;
    node4->random = node3;
    node5->random = node1;

    Node* clonedHead = copyRandomList(node1);
    
    Node* curr = clonedHead;
    while (curr != nullptr) {
        std::cout << "[" << curr->data << ",";
        if (curr->random) std::cout << curr->random->data;
        else std::cout << "null";
        std::cout << "] ";
        curr = curr->next;
    }
    return 0;
}
```

**Complexity:** Time is $O(n)$ as we make three linear passes over the list. Space is $O(1)$ because we do not use any extra auxiliary data structures (excluding the space for the cloned list itself).

**Practice:** https://leetcode.com/problems/copy-list-with-random-pointer/

::: interview
What interviewers probe here: your fluency with in-place pointer manipulation. They want to see if you intuitively reach for the dummy head to handle edge cases cleanly, whether you know how to use slow/fast pointers (like tortoise-hare for cycles or middle finding), and if you can execute in-place pointer reversal or Floyd's cycle detection without hesitation.
:::
