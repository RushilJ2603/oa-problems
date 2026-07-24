# Editorial — Dora's Preferred Route

This asks for the **longest simple path** from S to D, tie-broken lexicographically. Longest simple
path is NP-hard in general, but the constraints are small, so a **backtracking DFS** works: from S,
recurse into unvisited neighbours; whenever you arrive at D, compare the current path against the
best so far (more cities wins; on a tie, the lexicographically smaller sequence wins).

Exploring neighbours in **increasing index order** and keeping the best `(length, sequence)` gives
the lexicographically smallest maximum route directly. Mark/unmark `visited` on the way down/up.
