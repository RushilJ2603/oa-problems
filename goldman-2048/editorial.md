# Editorial — 2048

Write one helper that merges a length-4 line **toward the front** (index 0): drop zeros to compact,
then scan left to right — if two neighbours are equal, replace them with their sum (add that sum to
the score) and skip the next cell; pad with zeros. Every direction reduces to this:

- **Left**: each row as-is.
- **Right**: each row reversed (then write back reversed).
- **Up**: each column top→bottom.
- **Down**: each column bottom→top.

Keep a running cumulative score and print it after every press. `O(N)` per press on a fixed 4×4.
