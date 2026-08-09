# Top K Frequent Elements

## The whole problem is the comparator

Counting is the easy half: one pass with a hash map gives every tag's frequency in `O(n)`. The half
that people actually lose marks on is the ordering, because it is a **two-key** sort and the two keys
run in opposite directions:

- frequency **descending**,
- spelling **ascending**.

Get that backwards on the tie and you produce a plausible-looking answer that is wrong on exactly the
inputs the grader cares about. In C++:

```cpp
sort(items.begin(), items.end(), [](const auto &a, const auto &b) {
    if (a.second != b.second) return a.second > b.second;   // more frequent first
    return a.first < b.first;                               // then lexicographically smaller
});
```

In Python the same thing is one line, and the trick is negating the count so a single ascending sort
does both jobs:

```python
sorted(freq, key=lambda w: (-freq[w], w))[:k]
```

## Why "position in the input never breaks a tie" is stated explicitly

The natural implementation — walk the list, insert into a dictionary, sort what you get — preserves
*insertion order* among equal counts in Python 3.7+, and that order is the order tags were first
seen. That is a real and silent trap: on example 2 the first-seen order among the three singletons is
`topic, distribution, schema`, so an implementation that forgets the tie-break returns
`logic topic distribution` and passes every test where the input happens to already be alphabetical.
`tests/edge/04.in` (`zeta zeta alpha alpha mid mid`, `k = 2`) exists to fail that solution: `zeta` is
seen first, `alpha` must be answered first.

## Complexity

Counting is `O(n)`. Sorting the `d` distinct tags is `O(d log d)` string comparisons. With
`n <= 2·10^5` that is instant — the max-scale test with 200,000 distinct 20-character tags runs in
about a quarter of a second.

## The O(n log k) version, if they ask

They usually will, because it is the reason this question is asked instead of "sort a list". Keep a
**min-heap of size k** under the *reversed* comparator: the heap's top is the weakest of the current
best `k`, so each new tag is compared once and either dropped or swapped in. That is `O(d log k)`
instead of `O(d log d)`, which matters when `k` is small and `d` is enormous — the streaming case
where you cannot hold every distinct tag's ordering in memory at once.

Watch the comparator direction here: because the heap has to evict the *worst* element, the
comparison inside the heap is the exact inverse of the one used for the final output, so the answer
comes out of the heap backwards and has to be reversed. That inversion is where the bugs live.

## Complexity summary

| Approach | Time | Note |
|---|---|---|
| Count + full sort | `O(n + d log d)` | what the reference does; fine at these limits |
| Count + size-`k` heap | `O(n + d log k)` | the answer they are fishing for |
| Count + `nth_element` | `O(n + d)` average | fastest, but leaves the top `k` unordered — you still sort `k` |

## Related

This is **[LeetCode 692 — Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/)**
with the same tie-break rule. LC 347 is the integer version, where the tie-break is left unspecified
and any order is accepted — which is precisely why 692 is the better practice.
