# Editorial — Non-repeating Digit in Product

The range is small (`< 10^5`), so iterate `n` from `y` to `z` and check the condition directly.
Represent the set of digits of a number as a 10-bit mask (bit `d` set if digit `d` occurs). Then
`n` is valid iff `digitMask(n) & digitMask(n * x) == 0`. Count the valid ones. `O((z − y) · digits)`.
