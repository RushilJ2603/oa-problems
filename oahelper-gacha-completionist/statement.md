# Gacha Completionist

A mobile game runs a limited banner with `N` distinct collectible characters. Every **pull** returns exactly one character. Character `i` appears with probability proportional to a weight `W_i`:

\[
P_i = \frac{W_i}{W_1 + W_2 + \cdots + W_N}.
\]

You are a completionist: you keep pulling until you own **at least one copy of every character**. Compute the expected number of pulls needed.

The expectation is a rational number `p/q`. Output it modulo `998244353`, i.e. `(p · q⁻¹) mod 998244353`, where `q⁻¹` is the modular multiplicative inverse of `q` modulo `998244353`.

## Input Format

- The first line contains a single integer `N` — the number of unique characters.
- The second line contains `N` integers `W_1, W_2, …, W_N` — the character weights.

## Output Format

Output a single integer: the expected number of pulls to collect all characters, modulo `998244353`.

## Constraints

- \(1 \le N \le 10^5\)
- \(1 \le W_i \le 100\)
- \(W_1 + W_2 + \cdots + W_N \le 10^5\)

## Examples

### Example 1

**Input**
```
2
1 1
```

**Output**
```
3
```

**Explanation.** Two characters, each with probability \(1/2\). The first pull always gives a new character; waiting for the other takes 2 pulls in expectation. Total expectation \(1 + 2 = 3\).

### Example 2

**Input**
```
1
1
```

**Output**
```
1
```

**Explanation.** A single character is obtained on the first pull.

### Example 3

**Input**
```
3
1 1 1
```

**Output**
```
499122182
```

**Explanation.** Equal weights of 1. The expectation equals \(3 \cdot (1 + 1/2 + 1/3) = 11/2\), and \(11 \cdot 2^{-1} \equiv 499122182 \pmod{998244353}\).
