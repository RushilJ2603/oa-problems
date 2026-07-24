# Alphanumeric Combinations

> **This is a Goldman Sachs OA wrapper around a classic problem.** The underlying algorithm is
> exactly **[LeetCode 91 — Decode Ways](https://leetcode.com/problems/decode-ways/)**, so solve and
> get judged there. The original OA story is kept below for context.

John is teaching his son Rob the English alphabet and number counting. He represents `a` as the 1st
character, `b` as the 2nd, …, `z` as the 26th. John says the word `kite` can be represented as
`119205` — the 11th character is `k`, the 9th is `i`, the 20th is `t`, and the 5th is `e`.

Rob, being smarter, points out that `119205` can also mean `aaite` = `(1)(1)(9)(20)(5)`, or
`aste` = `(1)(19)(20)(5)`, and so on. Enthusiastic about it, John wants to know: given a string of
length `n` containing digits `0`–`9`, **how many such words are possible?**

## Rules
- Each letter is a number from `1` to `26`.
- `0` is only valid as the second digit of `10` or `20` (a leading `0` or standalone `0` is invalid).
  The string will not begin with `0`.

## Examples
- `2112` → `5` (`baab`, `bal`, `bkb`, `uab`, `ul`)
- `2101` → `1` (`(2)(10)(1)`)

## Constraints
- `1 ≤ length(S) ≤ 250`; digits `0`–`9`; does not begin with `0`.

---
👉 **[Open it on LeetCode to solve and submit](https://leetcode.com/problems/decode-ways/)** — same
algorithm (count decodings with a `1..26` mapping).
