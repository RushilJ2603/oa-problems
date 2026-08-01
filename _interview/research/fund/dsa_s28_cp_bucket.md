# The Competitive & OA Toolbox

These are the miscellaneous tools that turn a "I have no idea" Online Assessment (OA) problem into a known pattern. 

::: keypoint
Most OA "hard" problems are a standard technique below wearing a costume.
:::

## Modular Arithmetic Toolkit

When answers must be returned modulo $m$ (typically $10^{9}+7$ or $998244353$), operations must be done safely to prevent integer overflow. Addition, subtraction, and multiplication distribute over modulo, but division does not.

::: trap
Always cast to `long long` before multiplying two 32-bit integers, even if the result will immediately be modulo $m$. Otherwise, the overflow happens before the modulo is applied.
:::

To handle division $\frac{a}{b} \pmod m$, we multiply by the **modular inverse** of $b$. By Fermat's Little Theorem, if $m$ is prime, $b^{m-1} \equiv 1 \pmod m$, which implies $b^{-1} \equiv b^{m-2} \pmod m$. We compute this efficiently using **binary exponentiation** in $O(\log m)$. For combinatorics, precomputing factorials and their inverses allows $O(1)$ computation of $\binom{n}{r} \pmod m$.

::: keypoint
Binary exponentiation computes $x^{n}$ in $O(\log n)$ by relying on the recurrence $x^{n} = (x^{n/2})^{2}$ for even $n$, and $x \cdot x^{n-1}$ for odd $n$.
:::

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

// Safely add, subtract, and multiply modulo MOD
long long add(long long a, long long b) {
    return (a + b) % MOD;
}

long long sub(long long a, long long b) {
    return (a - b % MOD + MOD) % MOD; // +MOD prevents negative results
}

long long mul(long long a, long long b) {
    return (a % MOD) * (b % MOD) % MOD;
}

// Binary exponentiation: base^exp % MOD in O(log exp)
long long binpow(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Modular inverse assuming MOD is prime
long long modInverse(long long n) {
    return binpow(n, MOD - 2);
}

// Combinatorics (nCr % MOD) with O(N) precomputation and O(1) query
struct Combinatorics {
    vector<long long> fact, invFact;
    Combinatorics(int n) {
        fact.assign(n + 1, 1);
        invFact.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }
        invFact[n] = modInverse(fact[n]);
        for (int i = n - 1; i >= 1; i--) {
            invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
        }
    }
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
    }
};

int main() {
    Combinatorics combo(1000);
    cout << "5C2 mod 10^9+7 = " << combo.nCr(5, 2) << "\n";
    return 0;
}
```

## Sieve of Eratosthenes & Factorization

Finding primes and prime factorizations are common subtasks. The **Sieve of Eratosthenes** finds all primes up to $n$ in $O(n \log \log n)$. 
For factorizing a single number $x$, trial division up to $\sqrt{x}$ takes $O(\sqrt{x})$. However, if we need to factorize multiple numbers up to $n$, we can modify the Sieve to store the **Smallest Prime Factor (SPF)** for each number. This allows factorization of any $x \le n$ in $O(\log x)$ time.

```cpp
#include <iostream>
#include <vector>

using namespace std;

// Standard Sieve: O(N log log N)
vector<int> getPrimes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }
    vector<int> primes;
    for (int p = 2; p <= n; p++) {
        if (isPrime[p]) primes.push_back(p);
    }
    return primes;
}

// SPF Sieve: O(N log log N) precomputation, O(log X) factorization
vector<int> getSPF(int n) {
    vector<int> spf(n + 1);
    for (int i = 1; i <= n; i++) spf[i] = i;
    for (int p = 2; p * p <= n; p++) {
        if (spf[p] == p) { // if p is prime
            for (int i = p * p; i <= n; i += p) {
                if (spf[i] == i) spf[i] = p; // mark smallest prime factor
            }
        }
    }
    return spf;
}

// O(log X) factorization using precomputed SPF
vector<int> factorize(int x, const vector<int>& spf) {
    vector<int> factors;
    while (x != 1) {
        factors.push_back(spf[x]);
        x /= spf[x];
    }
    return factors;
}

// O(sqrt X) factorization for a single number without precomputation
vector<int> factorizeSingle(int x) {
    vector<int> factors;
    for (int d = 2; d * d <= x; d++) {
        while (x % d == 0) {
            factors.push_back(d);
            x /= d;
        }
    }
    if (x > 1) factors.push_back(x);
    return factors;
}

int main() {
    vector<int> primes = getPrimes(20);
    vector<int> spf = getSPF(100);
    vector<int> factors = factorize(60, spf);
    
    cout << "Prime factors of 60: ";
    for (int f : factors) cout << f << " ";
    cout << "\n";
    return 0;
}
```

## GCD, LCM & the Euclidean Algorithm

The Greatest Common Divisor (GCD) is foundational for number theory problems. C++17 provides `std::gcd` and `std::lcm` in the `<numeric>` header. The Least Common Multiple (LCM) is computed as $\frac{a \cdot b}{\gcd(a, b)}$. 

::: keypoint
Always compute LCM as `(a / gcd(a, b)) * b` rather than `(a * b) / gcd(a, b)` to prevent integer overflow during the intermediate multiplication.
:::

The **Extended Euclidean Algorithm** finds the coefficients $x$ and $y$ such that $a \cdot x + b \cdot y = \gcd(a, b)$. This is used for solving linear Diophantine equations and linear congruences, and for finding modular inverses when $m$ is not prime.

```cpp
#include <iostream>
#include <numeric>

using namespace std;

// Iterative GCD (if std::gcd is not available)
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Safe LCM to avoid overflow
long long lcm(long long a, long long b) {
    return (a / std::gcd(a, b)) * b;
}

// Extended Euclidean Algorithm: returns gcd and updates x, y
// such that a*x + b*y = gcd(a, b)
long long extendedGCD(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int main() {
    long long a = 30, b = 12;
    cout << "GCD: " << std::gcd(a, b) << "\n";
    cout << "LCM: " << lcm(a, b) << "\n";
    
    long long x, y;
    long long g = extendedGCD(a, b, x, y);
    cout << a << "(" << x << ") + " << b << "(" << y << ") = " << g << "\n";
    return 0;
}
```

## Coordinate Compression

When problem inputs contain values up to $10^{9}$ but $N$ is small (e.g., $10^{5}$), and we only care about their relative order, we can map the values to a dense range $[0, k)$ where $k \le N$. This is called **Coordinate Compression**.

This technique is mandatory when you need to use the values as indices in an array, such as in a Binary Indexed Tree or Segment Tree over big values.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> a = {1000000000, 10, -500, 10, 888888};
    
    // 1. Copy and sort
    vector<int> vals = a;
    sort(vals.begin(), vals.end());
    
    // 2. Remove duplicates
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    
    // 3. Replace original elements with their compressed rank
    vector<int> compressed(a.size());
    for (int i = 0; i < a.size(); i++) {
        compressed[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
    }
    
    cout << "Original: ";
    for (int x : a) cout << x << " ";
    cout << "\nCompressed: ";
    for (int x : compressed) cout << x << " ";
    cout << "\n";
    return 0;
}
```

## Meet in the Middle

::: heavy
Meet in the Middle reduces a backtracking time complexity of $O(2^{n})$ to $O(2^{n/2} \log(2^{n/2}))$ by splitting the search space.
:::

When $N$ is small but just slightly too large for an $O(2^{N})$ brute force (e.g., $N \le 40$), we split the input array into two halves of size $N/2$. We generate all $2^{N/2}$ subset sums for each half. We can then sort one half's sums and use binary search (or two pointers) to pair them with the other half to reach a target sum.

::: keypoint
**Recognising Meet in the Middle.** It is one of the most telegraphed patterns in competitive programming — it announces itself through a very specific combination of constraints. Check all four:

1. **The golden range: $20 \le N \le 40$.** This is the single biggest giveaway. If the maximum array size is around 30 to 40, alarm bells should ring. Below 20, standard brute force / backtracking is fine — $2^{20}$ is about a million operations. Above 40, brute force is out of the question entirely and you need DP or a greedy. **Exactly** in the 20–40 band is the sweet spot: a full $2^{40}$ brute force is over a trillion operations and hopeless, but split in half, brute-forcing each $2^{20}$ half takes milliseconds.
2. **It is a "subset" or "choice" problem** — you make an independent decision for each element. Pick/don't-pick (subset sums, subsequences, partitioning), or assign each element to one of a few buckets (multiply by $1$, $-1$ or $0$).
3. **Dynamic programming is impossible** — and deliberately so. The values are huge (e.g. $|nums[i]| \le 10^9$), so a DP table indexed by sum would exceed memory limits; or the elements include negatives, making DP indices awkward without massive offsets; or you must track multiple constraints at once (exact subset *size* and target sum), adding too many dimensions.
4. **The halves can be efficiently combined.** Splitting is useless if you cannot stitch the answers back quickly. The combination step must be $O(K \log K)$ or $O(K)$ where $K = 2^{N/2}$ — typically binary search for an exact-or-closest target, a hash map for exact matches, or two pointers from opposite ends of both sorted halves.

**The quick filter:** *"Does this ask me to pick combinations from an array where $N$ is around 30 or 40, and the numbers inside the array are massive?"* If yes, stop trying to build a DP table — split the array down the middle, enumerate both halves exhaustively, and marry them with a sort plus binary search.
:::

**Practice:** [LeetCode 1755: Closest Subsequence Sum](https://leetcode.com/problems/closest-subsequence-sum/)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Generates all subset sums of array 'arr'
vector<long long> getSubsetSums(const vector<int>& arr) {
    int n = arr.size();
    vector<long long> sums;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long currentSum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                currentSum += arr[i];
            }
        }
        sums.push_back(currentSum);
    }
    return sums;
}

int minAbsDifference(vector<int>& nums, int goal) {
    int n = nums.size();
    vector<int> leftHalf(nums.begin(), nums.begin() + n / 2);
    vector<int> rightHalf(nums.begin() + n / 2, nums.end());
    
    vector<long long> leftSums = getSubsetSums(leftHalf);
    vector<long long> rightSums = getSubsetSums(rightHalf);
    
    sort(rightSums.begin(), rightSums.end());
    
    long long ans = 2e18; // Infinity
    
    for (long long lSum : leftSums) {
        long long target = goal - lSum;
        // Binary search for the closest match in rightSums
        auto it = lower_bound(rightSums.begin(), rightSums.end(), target);
        
        if (it != rightSums.end()) {
            ans = min(ans, abs(goal - (lSum + *it)));
        }
        if (it != rightSums.begin()) {
            it--;
            ans = min(ans, abs(goal - (lSum + *it)));
        }
    }
    
    return ans;
}

int main() {
    vector<int> nums = {5, -7, 3, 5};
    int goal = 6;
    cout << "Minimum absolute difference: " << minAbsDifference(nums, goal) << "\n";
    return 0;
}
```

## Matrix Exponentiation

Linear recurrences (like the Fibonacci sequence $F_{n} = F_{n-1} + F_{n-2}$) can be computed in $O(\log n)$ time using **Matrix Exponentiation**. We express the transition between states as a matrix multiplication, and then exponentiate the transition matrix in $O(k^{3} \log n)$ time, where $k$ is the number of states (the dimension of the matrix).

::: keypoint
If you need the $N$-th term of a linear recurrence where $N$ is up to $10^{18}$, Matrix Exponentiation is the intended solution.
:::

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
typedef vector<vector<long long>> Matrix;

// Multiply two matrices modulo MOD
Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// Matrix exponentiation in O(k^3 log power)
Matrix matrixPow(Matrix A, long long power) {
    int n = A.size();
    Matrix res(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) res[i][i] = 1; // Identity matrix
    
    while (power > 0) {
        if (power % 2 == 1) res = multiply(res, A);
        A = multiply(A, A);
        power /= 2;
    }
    return res;
}

// Compute N-th Fibonacci number in O(log N)
long long fibonacci(long long n) {
    if (n == 0) return 0;
    Matrix T = {{1, 1},
                {1, 0}}; // Transition matrix
    
    T = matrixPow(T, n - 1);
    // Base cases F_1 = 1, F_0 = 0
    return T[0][0]; 
}

int main() {
    cout << "10th Fibonacci modulo 10^9+7: " << fibonacci(10) << "\n";
    return 0;
}
```

## Bit Tricks (recap + extras)

A compact cheat list of bitwise operations that frequently shortcut logic. See the main Bit Manipulation section for in-depth coverage.

- Count set bits: `__builtin_popcount(x)` for `int`, `__builtin_popcountll(x)` for `long long`.
- Lowest set bit: `x & -x`.
- Check if power of two: `(x & (x - 1)) == 0` and `x > 0`.
- XOR properties: $a \oplus a = 0$, $a \oplus 0 = a$.
- Iterate all submasks of a mask: `for (int sub = mask; sub > 0; sub = (sub - 1) & mask)`.

```cpp
#include <iostream>

using namespace std;

int main() {
    int mask = 13; // 1101 in binary
    
    cout << "Set bits in " << mask << ": " << __builtin_popcount(mask) << "\n";
    
    int lowestBit = mask & -mask; // 0001
    cout << "Lowest set bit: " << lowestBit << "\n";
    
    int p = 16;
    bool isPow2 = (p > 0) && ((p & (p - 1)) == 0);
    cout << p << " is power of 2? " << isPow2 << "\n";
    
    cout << "Submasks of " << mask << ":\n";
    for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
        cout << sub << " ";
    }
    cout << "\n";
    
    return 0;
}
```

## Randomization & Misc

For heavy I/O, untie `cin` from `cout` and avoid `endl` to prevent Time Limit Exceeded (TLE) verdicts (see the OA Survival Kit for details).

For randomization, do not use `rand()`. It is outdated, has a small period, and often outputs predictable values. Instead, use the Mersenne Twister engine `std::mt19937`.

When facing an unknown array problem without an obvious algorithm, the first two reflexes to test should be **prefix sums** (for subarray properties) and **two pointers** (if the array can be sorted or is monotonic).

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>

using namespace std;

int main() {
    // Fast I/O reminder
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Robust randomization using Mersenne Twister seeded with high-resolution clock
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    // Generate a random integer in [1, 100]
    uniform_int_distribution<int> dist(1, 100);
    int randomValue = dist(rng);
    
    cout << "Random Value: " << randomValue << "\n";
    return 0;
}
```

## Close

::: interview
**The "I'm Stuck" Checklist**
When an interview or OA problem seems impossible, systematically run through these angles:
1. **Is the search space monotonic?** (Try Binary Search on Answer).
2. **Is it a graph in disguise?** (States as nodes, transitions as edges → BFS/Dijkstra).
3. **Is it DP?** (Identify the state variables, does the problem ask for min/max/ways over choices?).
4. **Is it a math/counting identity?** (Can you map it to combinations, XOR properties, or a known sequence?).
5. **Is it a known data structure?** (Does it need range queries? → Segment Tree. Dynamic median? → Two Heaps).

This section plus the OA Survival Kit are your final safety net.
:::
