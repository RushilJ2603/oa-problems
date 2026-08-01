# Mathematics for DSA and Competitive Programming

Integer arithmetic in C++ has two fundamental behaviors that frequently cause bugs: modulo semantics with negative numbers, and integer overflow. Integer division truncates towards zero (e.g., `-5 / 2` is `-2`), and the modulo operator `%` takes the sign of the dividend (e.g., `-5 % 2` is `-1`). Overflow occurs when a value exceeds the capacity of its data type. Always use `long long` when dealing with products of large numbers or sums that might exceed $10^{9}$. Remember to append `LL` to integer literals when shifting or multiplying (e.g., `1LL << 32`), as literals are `int` by default.

::: trap
The modulo of a negative number in C++ is negative. To get the mathematically positive modulo for $a \bmod m$, always use `(a % m + m) % m`. Furthermore, intermediate products like `a * b` will overflow if both are `int` but the result exceeds $2 \cdot 10^{9}$, even if you assign the result to a `long long`. Cast one operand first: `(long long)a * b`.
:::

## Digit & number problems

### Count all Digits of a Number
Given an integer $n$, count the number of digits it has.

**Intuition:** 
A brute force approach repeatedly divides the number by 10 until it becomes 0, counting the steps. A better approach uses logarithms: the number of digits in base 10 is $\lfloor \log_{10}(n) \rfloor + 1$. The most convenient C++ approach is to convert the number to a string and return its size.

**C++ Solution:**
```cpp
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Optimal: String conversion
int countDigitsString(int n) {
    if (n == 0) return 1;
    return to_string(abs(n)).size();
}

// Optimal: Logarithm approach
int countDigitsLog(int n) {
    if (n == 0) return 1;
    return floor(log10(abs(n))) + 1;
}

// Brute Force: Iterative division
int countDigitsIterative(int n) {
    if (n == 0) return 1;
    int count = 0;
    n = abs(n);
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}
```

**Complexity:** Time is $O(1)$ for string conversion and log (assuming fixed 32-bit integers, else $O(\log_{10} n)$). Space is $O(1)$ (or $O(\log_{10} n)$ for string conversion).
**Practice:** https://www.geeksforgeeks.org/problems/count-digits5716/1

### Reverse a Number
Given a signed 32-bit integer $x$, return $x$ with its digits reversed. If reversing $x$ causes the value to go outside the signed 32-bit integer range $[-2^{31}, 2^{31} - 1]$, then return 0.

**Intuition:**
We can extract the last digit of the number using modulo 10 and append it to our reversed number by multiplying the current reversed number by 10 and adding the digit. To handle overflow properly, we must check if the next step will overflow before performing the multiplication.

**C++ Solution:**
```cpp
#include <climits>

using namespace std;

int reverse(int x) {
    int rev = 0;
    while (x != 0) {
        int pop = x % 10;
        x /= 10;
        // Check for overflow before multiplying by 10
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
        rev = rev * 10 + pop;
    }
    return rev;
}
```

**Complexity:** Time is $O(\log_{10} x)$ as there are roughly $\log_{10} x$ digits. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/reverse-integer/

### Palindrome Number
Given an integer $x$, return true if $x$ is a palindrome, and false otherwise.

**Intuition:**
Negative numbers are never palindromes because of the minus sign. A brute force approach converts the number to a string and checks if it equals its reverse. A better approach reverses the entire integer and compares it. The optimal approach reverses only half of the integer to prevent overflow and save time. When the reversed half is greater than or equal to the remaining half, we have processed at least half the digits.

**C++ Solution:**
```cpp
using namespace std;

bool isPalindrome(int x) {
    // Negatives and numbers ending in 0 (except 0 itself) are not palindromes
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }

    int reversedHalf = 0;
    while (x > reversedHalf) {
        reversedHalf = reversedHalf * 10 + x % 10;
        x /= 10;
    }

    // When length is odd, we can get rid of the middle digit by reversedHalf/10
    return x == reversedHalf || x == reversedHalf / 10;
}
```

**Complexity:** Time is $O(\log_{10} x)$ because we divide the input by 10 for half of its digits. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/palindrome-number/

### GCD of Two Numbers
Given two integers $a$ and $b$, find their Greatest Common Divisor (GCD) and Least Common Multiple (LCM).

**Intuition:**
The brute force approach iterates from $\min(a, b)$ down to 1 to find the largest divisor. The optimal approach uses the Euclidean algorithm: $\gcd(a, b) = \gcd(b, a \bmod b)$. This can be implemented iteratively or recursively. Once the GCD is found, the LCM can be computed using the property $a \cdot b = \gcd(a, b) \cdot \text{lcm}(a, b)$. To avoid overflow, compute LCM as $(a / \gcd) \cdot b$.

::: keypoint
The Euclidean algorithm is the gold standard for GCD. In modern C++, you should prefer `std::gcd(a, b)` (since C++17) or `std::__gcd(a, b)` (older GCC) from the `<numeric>` header rather than rolling your own.
:::

**C++ Solution:**
```cpp
#include <numeric>

using namespace std;

// Optimal: Recursive Euclidean Algorithm
int gcdRecursive(int a, int b) {
    if (b == 0) return a;
    return gcdRecursive(b, a % b);
}

// Optimal: Iterative Euclidean Algorithm
int gcdIterative(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// LCM computation
long long lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (long long)(a / gcdIterative(a, b)) * b;
}
```

**Complexity:** Time is $O(\log(\min(a, b)))$ for both iterative and recursive approaches. Space is $O(1)$ for iterative and $O(\log(\min(a, b)))$ auxiliary stack space for recursive.
**Practice:** https://www.geeksforgeeks.org/problems/lcm-and-gcd4516/1

### Check if the Number is Armstrong
Given an integer $n$, check if it is an Armstrong number. An Armstrong number of $k$ digits is a number equal to the sum of the $k$-th powers of its digits.

**Intuition:**
Extract each digit, raise it to the power of the total number of digits, and sum them up. If the sum equals the original number, it is an Armstrong number.

**C++ Solution:**
```cpp
#include <cmath>
#include <string>

using namespace std;

bool isArmstrong(int n) {
    int originalNum = n;
    int k = to_string(n).length();
    long long sum = 0;
    
    while (n > 0) {
        int digit = n % 10;
        sum += pow(digit, k);
        n /= 10;
    }
    
    return sum == originalNum;
}
```

**Complexity:** Time is $O(\log_{10} n)$ to process each digit. Space is $O(1)$.
**Practice:** https://www.geeksforgeeks.org/problems/armstrong-numbers2727/1

### Print all Divisors
Given an integer $n$, find all of its divisors.

**Intuition:**
The brute force way checks all numbers from 1 to $n$. A better approach leverages the fact that divisors come in pairs. If $i$ divides $n$, then $n/i$ also divides $n$. Therefore, we only need to check up to $\sqrt{n}$.

::: keypoint
The $O(\sqrt{n})$ trick is ubiquitous in number theory. If $i \le \sqrt{n}$, then its pair $n/i \ge \sqrt{n}$. This allows us to find all divisors (or prime factors) by iterating only up to the square root.
:::

**C++ Solution:**
```cpp
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getDivisors(int n) {
    vector<int> divisors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            // Check if the pair divisor is different
            if (i != n / i) {
                divisors.push_back(n / i);
            }
        }
    }
    // Sort to return them in increasing order
    sort(divisors.begin(), divisors.end());
    return divisors;
}
```

**Complexity:** Time is $O(\sqrt{n})$ to find divisors, plus $O(k \log k)$ to sort where $k$ is the number of divisors. Space is $O(k)$ for the answer array.
**Practice:** https://www.geeksforgeeks.org/problems/sum-of-all-divisors-from-1-to-n4738/1

### Check for Prime Number
Given an integer $n$, determine if it is prime.

**Intuition:**
A prime number is greater than 1 and has no positive divisors other than 1 and itself. Using the $O(\sqrt{n})$ trick from finding divisors, we only need to perform trial division up to $\sqrt{n}$. If no divisor is found in this range, the number is prime.

**C++ Solution:**
```cpp
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
```

**Complexity:** Time is $O(\sqrt{n})$. Space is $O(1)$.
**Practice:** https://www.geeksforgeeks.org/problems/prime-number2314/1

## Number theory the OAs assume

::: heavy
The following concepts are fundamental tools for Online Assessments (OAs). They bridge the gap between simple math loops and optimal number theory routines required under strict time limits.
:::

### Sieve of Eratosthenes
To efficiently find all prime numbers up to $n$, the Sieve of Eratosthenes is optimal. We maintain a boolean array `isPrime`. Starting from 2, if a number is prime, we mark all of its multiples (starting from its square) as composite.

**C++ Solution:**
```cpp
#include <vector>

using namespace std;

vector<int> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}
```

**Complexity:** Time is $O(n \log \log n)$. Space is $O(n)$ for the boolean array.

### Smallest Prime Factor (SPF) sieve
If we need to prime factorize multiple numbers efficiently, we can precompute the Smallest Prime Factor (SPF) for every number up to $n$. This allows $O(\log n)$ factorization per query after $O(n \log \log n)$ precomputation.

**C++ Solution:**
```cpp
#include <vector>

using namespace std;

vector<int> computeSPF(int n) {
    vector<int> spf(n + 1);
    for (int i = 1; i <= n; i++) spf[i] = i; // Initialize with itself
    
    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j <= n; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
    return spf;
}

vector<int> factorize(int n, const vector<int>& spf) {
    vector<int> factors;
    while (n != 1) {
        factors.push_back(spf[n]);
        n /= spf[n];
    }
    return factors;
}
```

**Complexity:** $O(n \log \log n)$ to build the SPF array. Factorization takes $O(\log n)$ time per query. Space is $O(n)$.

### Modular arithmetic
When answers can be very large, problems ask for the result modulo some integer $m$ (often $10^{9} + 7$). Modular arithmetic ensures that intermediate values do not overflow. The standard rules are:
- $(a + b) \bmod m = ((a \bmod m) + (b \bmod m)) \bmod m$
- $(a \cdot b) \bmod m = ((a \bmod m) \cdot (b \bmod m)) \bmod m$
- $(a - b) \bmod m = ((a \bmod m) - (b \bmod m) + m) \bmod m$

::: keypoint
Always apply the modulo operator at every step of your calculation, not just at the end. For subtraction, always add $m$ before taking the modulo to avoid negative results. The standard modulus $10^{9} + 7$ is prime and fits in a 32-bit signed integer, but the product of two such numbers requires a 64-bit integer (`long long`).
:::

### Fast (binary) exponentiation
To compute $a^{b} \bmod m$ efficiently, we use binary exponentiation. Instead of multiplying $a$ by itself $b$ times ($O(b)$), we observe that $a^{b} = (a^{b/2})^{2}$ for even $b$, and $a^{b} = a \cdot (a^{b/2})^{2}$ for odd $b$.

**C++ Solution:**
```cpp
using namespace std;

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}
```

**Complexity:** Time is $O(\log b)$. Space is $O(1)$.

### Modular inverse
Division under modulo $m$ is defined by multiplying by the modular inverse: $(a / b) \bmod m = (a \cdot b^{-1}) \bmod m$. By Fermat's Little Theorem, if $m$ is prime, $b^{m-1} \equiv 1 \pmod m$. Multiplying both sides by $b^{-1}$ gives $b^{-2} \cdot b = b^{-1} \implies b^{-1} \equiv b^{m-2} \pmod m$. 

Thus, the modular inverse of $b$ modulo a prime $m$ is simply `binpow(b, m - 2, m)`. For a non-prime modulus, you must use the Extended Euclidean algorithm instead.

### Combinatorics
To compute combinations $nCr \bmod p$ efficiently, we can precompute factorials and their modular inverses. Since $nCr = \frac{n!}{r!(n-r)!}$, under modulo $p$ this becomes $n! \cdot (r!)^{-1} \cdot ((n-r)!)^{-1} \bmod p$. This is much faster than computing Pascal's triangle for large $n$, though Pascal's identity ($nCr = (n-1)Cr + (n-1)C(r-1)$) is useful when dynamic programming is required for small constraints.

## Advanced Maths

### Print Prime Factors of a Number
Given an integer $n$, print all of its prime factors.

**Intuition:**
We can find prime factors by repeatedly dividing $n$ by the smallest prime. Using the $O(\sqrt{n})$ trick, we only need to trial-divide up to $\sqrt{n}$. Any remaining value of $n$ strictly greater than 1 at the end of the loop is itself a prime factor. If multiple queries are needed, the SPF sieve approach is much faster.

**C++ Solution:**
```cpp
#include <vector>

using namespace std;

vector<int> primeFactors(int n) {
    vector<int> factors;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
    return factors;
}
```

**Complexity:** Time is $O(\sqrt{n})$ in the worst case (when $n$ is prime). Space is $O(1)$ excluding the output array.
**Practice:** https://www.geeksforgeeks.org/problems/prime-factors5052/1

### Divisors of a Number
Given $n$, count or sum its divisors.

**Intuition:**
Counting or summing divisors can be done in $O(\sqrt{n})$ using the pair trick. If $i$ divides $n$, we add $i$ and $n/i$ to our sum (or count by 2), taking care not to double count when $i = n/i$. 

**C++ Solution:**
```cpp
using namespace std;

long long sumOfDivisors(int n) {
    long long sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}
```

**Complexity:** Time is $O(\sqrt{n})$. Space is $O(1)$.
**Practice:** https://www.geeksforgeeks.org/problems/sum-of-all-divisors-from-1-to-n4738/1

### Count Primes in range L to R
Given $L$ and $R$, count the number of primes in the range $[L, R]$.

**Intuition:**
If $R$ is small (up to $10^{7}$), we can use a standard Sieve of Eratosthenes to precompute prime statuses up to $R$, and build a prefix sum array to answer any query in $O(1)$. For very large $L$ and $R$ (where $R - L$ is small but $R \approx 10^{12}$), a segmented sieve is required.

**C++ Solution:**
```cpp
#include <vector>

using namespace std;

// Assuming R <= 10^7, precompute
vector<int> countPrimesPrefix(int maxR) {
    vector<bool> isPrime(maxR + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= maxR; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= maxR; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    vector<int> prefixPrimes(maxR + 1, 0);
    for (int i = 1; i <= maxR; i++) {
        prefixPrimes[i] = prefixPrimes[i - 1] + (isPrime[i] ? 1 : 0);
    }
    return prefixPrimes;
}

int queryRange(int L, int R, const vector<int>& prefixPrimes) {
    return prefixPrimes[R] - prefixPrimes[L - 1];
}
```

**Complexity:** Precomputation takes $O(R \log \log R)$ time and $O(R)$ space. Each query is $O(1)$.
**Practice:** https://www.geeksforgeeks.org/problems/count-primes-in-range1604/1

### Prime Factorisation of a Number
Given a number $n$, return its prime factorization with multiplicities.

**Intuition:**
This combines the logic of finding prime factors but stores both the prime factor and its count (power). We perform trial division up to $\sqrt{n}$ and count how many times we can divide by each prime.

**C++ Solution:**
```cpp
#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> primeFactorization(int n) {
    vector<pair<int, int>> factors;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                count++;
                n /= i;
            }
            factors.push_back({i, count});
        }
    }
    if (n > 1) {
        factors.push_back({n, 1});
    }
    return factors;
}
```

**Complexity:** Time is $O(\sqrt{n})$. Space is $O(1)$ auxiliary.
**Practice:** https://www.geeksforgeeks.org/problems/prime-factors5052/1

### Pow(x, n)
Implement `pow(x, n)`, which calculates $x$ raised to the power $n$.

**Intuition:**
This is binary exponentiation for real numbers. We must handle negative powers by reciprocating the base ($x = 1/x$) and making the power positive. A critical edge case is when $n = \text{INT\_MIN}$, as making it positive overflows a 32-bit signed integer. We solve this by casting $n$ to a `long long` before taking its absolute value.

**C++ Solution:**
```cpp
using namespace std;

double myPow(double x, int n) {
    double ans = 1.0;
    long long nn = n;
    
    if (nn < 0) {
        nn = -nn;
        x = 1.0 / x;
    }
    
    while (nn > 0) {
        if (nn % 2 == 1) {
            ans = ans * x;
            nn = nn - 1;
        } else {
            x = x * x;
            nn = nn / 2;
        }
    }
    return ans;
}
```

**Complexity:** Time is $O(\log n)$. Space is $O(1)$.
**Practice:** https://leetcode.com/problems/powx-n/

::: interview
In actual coding interviews and OAs, expect GCD/LCM, standard Sieve of Eratosthenes, fast modular exponentiation (`modpow`), combinatorics modulo $p$, and rigorous integer overflow discipline to appear frequently. Heavy number-theory olympiad concepts (like Möbius inversion or advanced Diophantine equations) virtually never show up in standard software engineering interviews.
:::
