# 12. Data Structures in C

C has no built-in containers. There are no standard `std::vector` or `List<T>` types waiting for you to use. Instead, you build them from scratch using structs, pointers, and `malloc` [1]. This section is the payoff for mastering memory and pointers: you now have the tools to shape data into any form a problem demands.

## Dynamic Arrays

```{=typst}
#definition[
```

A *dynamic array* is an array that resizes itself automatically as elements are added, typically by doubling its capacity when full.

```{=typst}
]
```

Fixed-size arrays (`int arr[10];`) are rigid. If you need to store an unknown number of items, you build a dynamic array using a struct to track the pointer to the heap-allocated memory, the current length, and the total capacity.

```c
typedef struct {
    int *data;
    size_t len;
    size_t cap;
} int_vec_t;
```

When `len == cap`, you allocate a new block of memory (often `cap * 2`), `memcpy` the old elements over, and `free` the old block (or simply use `realloc`). This "amortized doubling" ensures that appending an element takes $O(1)$ time on average, even though occasionally an append triggers an $O(n)$ copy.

## Singly Linked Lists

```{=typst}
#heavy[
```

Dense — slow down: A linked list scatters its data across memory, connected only by pointers, breaking the contiguous memory model you rely on for arrays.

```{=typst}
]
```

Imagine a scavenger hunt. The first clue is at the starting point. It contains some information, and the address of the next clue. To find the third clue, you *must* visit the first, then the second. This is a singly linked list.

![A singly linked list where each node points to the next.](assets/s12_linkedlist.png)

Here is how two nodes connect in memory:

```c
struct node {
    int val;
    struct node *next;
};

// Example instantiation:
struct node *head = malloc(sizeof(struct node));
head->val = 10;
head->next = malloc(sizeof(struct node));
head->next->val = 20;
head->next->next = NULL;
```

A linked list consists of self-referential structures (nodes). Each node holds data and a pointer to the next node. The last node points to `NULL`, marking the end. Unlike arrays, you cannot jump instantly to the 5th element; you must traverse from the head, following pointers one by one.

```{=typst}
#trap[
```

**The Lost Node Trap:** If you update a pointer before saving its target, the rest of the list is lost forever, causing a memory leak.

```{=typst}
]
```

For instance, when deleting a node, you cannot just do `free(current); current = current->next;` because `current->next` is unreadable once `current` is freed. You must stash the `next` pointer in a temporary variable first.

*Question to sit with:* How do you traverse a list to print its contents without losing the original head pointer? (Answer: Use a separate `current` pointer to walk the list.)

This structure shines when you need to insert or delete elements in the middle of a sequence frequently, as it requires zero shifting of subsequent elements—only updating a few pointers. However, it breaks when you need rapid random access.

### Doubly Linked Lists

A *doubly linked list* adds a `struct node *prev;` pointer. This allows traversal in both directions and $O(1)$ deletion if you already have a pointer to the node, at the cost of managing more pointers during every operation.

## Stacks, Queues, and Ring Buffers

Stacks (Last-In, First-Out) and queues (First-In, First-Out) are abstract concepts. In C, you back them with either dynamic arrays or linked lists. An array-backed stack is just a dynamic array where you only push and pop at the end. A list-backed queue maintains a pointer to both the `head` (for dequeue) and `tail` (for enqueue).

In embedded systems, you rarely have the luxury of `malloc`. The standard solution for a queue is a **circular buffer** (or ring buffer).

```{=typst}
#keypoint[
```

A circular buffer uses a fixed-size array and two indices (`head` and `tail`) that wrap around back to zero using the modulo operator (`%`) when they reach the end.

```{=typst}
]
```

![A circular buffer wrapping around an array.](assets/s12_ringbuffer.png)

This allows continuous $O(1)$ enqueuing and dequeuing without shifting elements or allocating memory.

## Binary Search Trees

```{=typst}
#heavy[
```

Dense — slow down: Trees use recursive data definitions and inherently demand recursive algorithms for elegant traversal.

```{=typst}
]
```

Imagine a physical filing cabinet. To find "Miller", you check the middle drawer. If Miller is alphabetically after the drawer's label, you ignore everything before it. You repeat this halving process. A Binary Search Tree (BST) structures data in memory to enable this exact search.

![A binary search tree maintaining the ordering property.](assets/s12_bst.png)

Let's look at manual insertion: To insert 6 into a tree rooted at 8, 6 is less than 8, so we go left. The left child is 3. 6 is greater than 3, so we go right, attaching 6 as the right child of 3.

A BST node contains left and right pointers:

```c
struct bst_node {
    int val;
    struct bst_node *left;
    struct bst_node *right;
};
```

The strict ordering rule is: For any node $N$, all values in its left subtree are less than $N$, and all values in its right subtree are greater than $N$.

Deletion involves three cases:
1. **Leaf node:** Free it and set the parent's pointer to `NULL`.
2. **One child:** Link the parent directly to the child, then free the node.
3. **Two children:** Find the in-order successor (the smallest value in the right subtree), swap its value into the node to be deleted, and delete the successor (which will have at most one child).

```{=typst}
#trap[
```

**The Degeneration Trap:** If you insert already-sorted data (e.g., 1, 2, 3, 4) into a standard BST, every new node goes to the right. The tree degenerates into a linked list, degrading search time from $O(\log n)$ to $O(n)$.

```{=typst}
]
```

*Why here?* Basic BSTs don't rebalance themselves. Production systems use balanced variants like Red-Black trees or AVL trees to guarantee $O(\log n)$ depth.

*Question to sit with:* Why is an in-order traversal of a BST (visit left, print current, visit right) guaranteed to yield a sorted sequence?

This structure shines for rapid lookup and sorted iteration. It breaks when the insertion order is heavily skewed.

## Hash Tables

When $O(\log n)$ search isn't fast enough, we use a hash table to achieve $O(1)$ average lookups [2].

A hash table maps a "key" (like a string) to an integer index using a *hash function*. The table itself is a dynamically allocated array of "buckets."

![A hash table resolving collisions using separate chaining.](assets/s12_hashtable.png)

Because the array is finite, two different keys might hash to the same bucket. This is a *collision*. The most common resolution in C is **separate chaining**: each bucket is actually a pointer to a linked list. If a collision occurs, you append the new key-value pair to the bucket's list.

The table's health is measured by its *load factor* (number of entries / number of buckets). When this exceeds a threshold (often 0.75), you must allocate a larger array, re-hash all existing keys, and insert them into the new array.

## Generic Containers in C

In higher-level languages, you might write `List<String>`. C lacks templates. To write a generic container (like a hash table or dynamic array that can hold *any* data type), you use `void *`.

```c
typedef struct {
    void **data; // Array of void pointers
    size_t len, cap;
} vec_t;
```

To sort or free these elements, the container cannot know how to handle the opaque `void *`. You must pass **function pointers** to the container. A generic BST might require an initialization like `bst_init(int (*compare)(void*, void*), void (*free_element)(void*));`.

## Memory Ownership

When building node-based structures, ownership dictates who calls `free()`.
- Does the linked list *own* the data it points to? If so, `list_free()` must iterate through and `free(node->data)` before freeing the node itself.
- Or is the list just *borrowing* references? If so, freeing the data is the caller's job, and the list only frees the node structs.

Failure to rigorously define and document this boundary results in double-frees or memory leaks.

## Complexity Quick-Reference

| Data Structure | Access $i$-th | Search | Insert | Delete |
|---|---|---|---|---|
| Array (unsorted) | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| Singly Linked List | $O(n)$ | $O(n)$ | $O(1)$* | $O(1)$* |
| Binary Search Tree | N/A | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ |
| Hash Table | N/A | $O(1)$ avg | $O(1)$ avg | $O(1)$ avg |

*\*If you have a pointer to the preceding node.*

## Interview Classics

```{=typst}
#interview[
```

**Q: How do you detect a cycle in a linked list?**
**A:** Use Floyd's Cycle-Finding Algorithm (the "tortoise and hare"). Two pointers start at the head. The slow pointer moves one step; the fast pointer moves two steps. If they ever point to the same node, a cycle exists. If the fast pointer hits `NULL`, there is no cycle.

```{=typst}
]
```

Other frequent interview questions involve finding the middle of a list (using the same slow/fast pointer trick), validating if a binary tree is a valid BST (by tracking the min and max allowed values during recursive descent), and building a queue using two stacks.

---

## Worked Examples

### Worked: Singly Linked List Operations

This snippet shows a robust pattern for insertion, traversal, and cleanup.

```c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};

// Insert at head: returns the new head
struct node* push(struct node *head, int val) {
    struct node *new_node = malloc(sizeof(struct node));
    if (!new_node) return head; // allocation failed
    new_node->val = val;
    new_node->next = head;
    return new_node;
}

// Traverse and print
void print_list(struct node *head) {
    struct node *curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->val);
        curr = curr->next;
    }
    printf("NULL\n");
}

// Free the entire list
void free_list(struct node *head) {
    struct node *curr = head;
    while (curr != NULL) {
        struct node *next = curr->next; // stash next before free
        free(curr);
        curr = next;
    }
}

int main(void) {
    struct node *head = NULL;
    head = push(head, 30);
    head = push(head, 20);
    head = push(head, 10);
    print_list(head); // Output: 10 -> 20 -> 30 -> NULL
    free_list(head);
    return 0;
}
```

### Worked: Reversing a Linked List

Reversing a list iteratively requires three pointers to avoid breaking the chain.

```c
struct node* reverse_list(struct node *head) {
    struct node *prev = NULL;
    struct node *curr = head;
    struct node *next = NULL;
    
    while (curr != NULL) {
        // 1. Save the next node
        next = curr->next;
        // 2. Reverse the link
        curr->next = prev;
        // 3. Advance prev and curr
        prev = curr;
        curr = next;
    }
    // prev is the new head
    return prev;
}
```

*Trace:* If list is `1 -> 2 -> NULL`.
- Loop 1: `curr` is 1. `next` becomes 2. `1->next` becomes `NULL`. `prev` becomes 1, `curr` becomes 2.
- Loop 2: `curr` is 2. `next` becomes `NULL`. `2->next` becomes 1. `prev` becomes 2, `curr` becomes `NULL`.
- Returns `prev` (node 2, pointing to 1).

### Faded Example: BST Insertion

Implement the recursive `bst_insert`. The base case is left open for you to complete.

```c
struct bst_node {
    int val;
    struct bst_node *left, *right;
};

struct bst_node* bst_insert(struct bst_node *root, int val) {
    // ??? (Base case: if root is NULL, allocate new node, return it)

    if (val < root->val) {
        root->left = bst_insert(root->left, val);
    } else if (val > root->val) {
        root->right = bst_insert(root->right, val);
    }
    // If equal, do nothing (no duplicates)
    
    return root;
}
```

---

### References

[1] C11 Standard (ISO/IEC 9899:2011), Section 7.22.3 — open-std.org — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[2] The GNU C Library - Hash Search and Insertion — gnu.org — https://www.gnu.org/software/libc/manual/html_node/Hash-Search-Function.html
