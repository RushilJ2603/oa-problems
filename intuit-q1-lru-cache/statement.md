# LRU Cache

> **This is a direct LeetCode classic, so it is not re-judged here.** Solve and submit it at
> **[LeetCode 146 — LRU Cache](https://leetcode.com/problems/lru-cache/)**. The recall of the Intuit
> version is kept below so the tab still records that this question came up.

Design a data structure that behaves like a **Least Recently Used (LRU) cache** of fixed capacity.

Implement a class `LRUCache` with:

- `LRUCache(int capacity)` — create the cache with a positive `capacity`.
- `int get(int key)` — return the value stored for `key`, or `-1` if `key` is not present.
- `void put(int key, int value)` — insert or overwrite the value for `key`. If inserting would push
  the number of stored keys above `capacity`, **evict the least recently used key first**.

Both `get` and `put` count as a **use** of that key, so both move it to the most-recently-used end.

## Required complexity

Both operations must run in **average O(1)**. This is the whole question — a correct answer that
scans the cache to find the least recently used key is the wrong answer here.

## Example

```
LRUCache cache = new LRUCache(2);
cache.put(1, 1);        // cache = {1=1}
cache.put(2, 2);        // cache = {1=1, 2=2}
cache.get(1);           // returns 1, and 1 is now the most recently used
cache.put(3, 3);        // capacity exceeded -> evicts key 2 (least recently used)
cache.get(2);           // returns -1 (not found)
cache.put(4, 4);        // evicts key 1
cache.get(1);           // returns -1 (not found)
cache.get(3);           // returns 3
cache.get(4);           // returns 4
```

## Constraints

- `1 <= capacity <= 3000`
- `0 <= key <= 10^4`, `0 <= value <= 10^5`
- Up to `2 * 10^5` calls to `get` and `put` combined.

## What the interviewer is checking

A **hash map** from key to node, plus a **doubly linked list** in use-order. The hash map gives O(1)
lookup; the linked list gives O(1) removal and O(1) re-insertion at the front, because you already
hold a pointer to the node and never have to search for it. The two structures point at each other —
that pairing *is* the answer. (In C++ `std::list` + `unordered_map<int, list<...>::iterator>` gives
you both; in Java `LinkedHashMap` with `accessOrder=true` does it in one line, which is worth saying
out loud but usually not what they want you to write.)

---

👉 **[Open it on LeetCode to solve and submit](https://leetcode.com/problems/lru-cache/)**
