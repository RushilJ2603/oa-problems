# Calibration Values

## The whole problem is one line of ambiguity

Finding the first and last digit of a string is trivial. What makes this a real question is a single
decision: **when a spelled word matches, do its letters stay available?**

They do. And every wrong solution to this problem is a solution that assumed they don't.

## The trap: replacing words with digits

The instinct is to normalise first and parse second:

```cpp
// WRONG
for (int w = 0; w < 9; w++)
    replaceAll(s, WORDS[w], to_string(w + 1));   // "one" -> "1", "two" -> "2", ...
// now just take the first and last digit character
```

It reads beautifully and it is wrong, because English digit words share letters:

| query | overlap | correct | replace-first gets |
|---|---|---|---|
| `oneight` | `one` and `eight` share the `e` | `18` | `11` — `one` becomes `1`, leaving `1ight` |
| `twone` | `two` and `one` share the `o` | `21` | `22` |
| `eightwo` | `eight` and `two` share the `t` | `82` | `88` |
| `sevenine` | `seven` and `nine` share the `n` | `79` | `77` |

The order you replace in changes the answer, which is the tell that the approach is unsound —
replacing `one` first destroys `eight`, replacing `eight` first destroys `one`. There is no ordering
that saves it. `edge/04` is all eight overlapping pairs and `edge/02` (`eightwoneightwone` → `81`)
chains four of them.

The same bug wears a second costume: scanning left to right but advancing `i` by the **length of the
word that matched** instead of by one. Consuming the word is exactly what `replaceAll` does, just
spelled differently.

## The fix

Treat every index as an independent question — *does a digit begin here?* — and always step forward
by one:

```cpp
for (size_t i = 0; i < s.size(); i++) {
    int d = -1;
    if (isdigit(s[i])) d = s[i] - '0';
    else for (int w = 0; w < 9; w++)
        if (s.compare(i, strlen(WORDS[w]), WORDS[w]) == 0) { d = w + 1; break; }
    if (d >= 0) { if (first < 0) first = d; last = d; }
}
value = 10 * first + last;
```

`first` is set once, `last` is overwritten every time — no second pass, no storing the digit list.

`brute.py` gets there a different way, with a zero-width lookahead:
`(?=(\d|one|two|...|nine))`. The lookahead consumes nothing, so the regex engine reports a match at
*every* position, including positions inside a word it already matched. That is the same "advance by
one" rule, delegated to the pattern.

## Smaller things that still cost the test case

- **Only one digit in the query.** Then first *is* last, and `abc4def` is `44`, not `4`. `edge/09`.
- **`0`.** It is a legal digit character, but there is no spelled `zero` — `0abc0` is `0`, and a
  solution that maps the word `zero` to a digit reads a digit that is not there. `edge/06`.
- **Near misses.** `on`, `thre`, `eigh`, `nin` are not digits, and neither are reversed words like
  `eno` or `owt`. A prefix check that fires early, or a `find` against a partially built buffer,
  picks these up. `edge/07` and `edge/10` are made of nothing else.
- **The sum.** With `n = 2·10^5` queries the total reaches ~`2·10^7`, which still fits in `int` —
  but accumulate into `long long` anyway; there is no reason to be one constraint bump away from
  wrapping.

## Complexity

Let `L` be the total length of all queries. Each index is examined once and compared against nine
words of length at most five, so the whole thing is `O(45 · L)` — linear, with a tiny constant.
Space is `O(1)` beyond the input, since each query can be scored and discarded as it is read.
