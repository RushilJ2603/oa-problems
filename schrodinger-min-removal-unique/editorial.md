# Shortest Block to Delete for Distinct Letters

## The observation that collapses the problem

Whatever you delete, what **survives** is a prefix `s[0..i-1]` followed by a suffix `s[j..n-1]`. For
the result to have every letter distinct, three things must hold:

1. the prefix has no repeat inside it,
2. the suffix has no repeat inside it,
3. the prefix and the suffix share no letter.

There are only 26 letters, so **an all-distinct string is at most 26 characters long**. That caps
the prefix at 26 characters and the suffix at 26 characters — regardless of whether `n` is 7 or
200,000. There are therefore at most 27 candidate prefixes and at most 27 candidate suffixes, and
the whole search is a 27 × 27 table.

That is the trap in the original OA: the natural "try every substring" loop is O(n²) windows with an
O(26) check each, which is fine at `n = 100` and hopeless at `n = 200000`.

## Algorithm

1. Walk forward from the start while the letters stay distinct — that gives `P`, the longest
   admissible prefix length. Admissible prefix lengths are `0, 1, …, P`.
2. Walk backward from the end while the letters stay distinct — that gives `q`, the smallest
   admissible suffix start. Admissible suffix starts are `q, q+1, …, n` (`j = n` means the suffix is
   empty, i.e. delete everything after the prefix).
3. Keep a 26-bit mask of the prefix's letters and a 26-bit mask of each suffix. For every prefix
   length `i`, take the smallest `j >= max(i, q)` whose suffix mask does not intersect the prefix
   mask, and record `j - i`.

Lengthening the prefix can only ever push `j` to the right, so a single two-pointer sweep also works
and is O(n) — but with at most 27 prefixes and 27 suffixes, the plain double loop is already
constant work after the two linear scans.

Answer: the smallest `j - i` found. It is always achievable because deleting the entire string (or
all but one character) is legal.

**Complexity:** O(n + 26²) time, O(n) memory (only for the suffix masks; O(26) is possible).

## Traps

- **Deleting nothing is legal.** If `s` already has no repeated letter the answer is `0`, not `1`.
- **Deleting everything is legal.** Guard against reporting "impossible" — for `"aaaa"` the answer
  is `3`, and for a 200,000-character run of one letter it is `199999`.
- **The prefix and suffix are each internally distinct AND mutually disjoint.** Checking only the
  first two conditions passes the small samples and fails as soon as the same letter bookends the
  string (`"abcdefghijklmnopqrstuvwxyza"` — answer `1`, not `0`).
- The empty prefix and the empty suffix both have to be in the candidate set. Off-by-one here shows
  up only when the optimum deletes a block touching one end.
