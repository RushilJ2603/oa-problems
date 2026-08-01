# Debugging C++ Blind — When You Cannot See the Test Cases

::: heavy
On HackerRank, HirePro, Codility, CodeSignal and most in-house OA platforms, a failing submission tells you almost nothing. There is no failing input, no stack trace, no partial diff — usually a single word: *Wrong Answer*. Worse, the platforms that host function-stub harnesses often carry the instruction **"Do not print arbitrary strings anywhere in the program, as these contribute to the output and test cases will fail"**, which removes the one debugging tool every programmer reaches for first: `cout`. This section is about the techniques that still work when the obvious ones are forbidden.
:::

The central skill is this: **you cannot see the test data, but the verdict itself is a communication channel.** A submission returns one of a small set of outcomes, and by deliberately choosing code that maps a *hypothesis about the hidden data* onto *different outcomes*, you can extract information from a system that was not designed to give you any. Everything below builds on that idea.

## The verdict is a signal — learn to read it

Every OA platform reports some variation of five outcomes. They are not interchangeable, and the single most common mistake is treating them as one undifferentiated "it failed".

| Verdict | What actually happened | What it rules **out** |
|---|---|---|
| Compilation Error | `g++` rejected your source | Nothing ran; your logic is untested |
| Wrong Answer | Ran to completion, exit 0, stdout mismatched | No crash, no timeout, no overflow *detected* |
| Runtime Error | Non-zero exit or fatal signal | The process died — this is a **loud, distinguishable** signal |
| Time Limit Exceeded | Ran past the cap | Your algorithm's complexity is too high *for the real bounds* |
| Accepted | stdout matched on every hidden test | — |

::: keypoint
**Runtime Error is the most useful verdict on a blind platform**, because it is the one you can trigger deliberately. Wrong Answer and Accepted are determined by your output; Runtime Error is determined by *whether your process survives*. That makes it a channel you control independently of the answer — and the basis of the assertion probe described below.
:::

### Distinguishing TLE from Wrong Answer when both look the same

A subtle trap: on many platforms, a solution that is *nearly* fast enough fails some tests on time and others on correctness, and the reported verdict is whichever test failed first. Before concluding your logic is wrong, do the arithmetic on the stated bounds.

::: trap
**Read the constraint block before you write code, and convert it to an operation count.** If `n <= 2·10^5` and your solution is O(n²), that is 4·10^10 operations — roughly a minute of CPU time, against a limit that is typically 1–2 seconds. The statement often *describes* the naive algorithm in prose ("find the element, delete it, insert it before the other"), and candidates implement exactly what they read. The prose describes the problem; **the bounds specify the algorithm**.
:::

The practical rule of thumb for a 1-second limit with C++:

| Bound on n | Operation budget | Admissible complexity |
|---|---|---|
| n ≤ 10 | — | O(n!), O(2ⁿ·n) |
| n ≤ 25 | — | O(2ⁿ), meet-in-the-middle |
| n ≤ 500 | ~10^8 | O(n³) |
| n ≤ 5·10^3 | ~10^8 | O(n²) |
| n ≤ 10^6 | ~10^8 | O(n log n) |
| n ≤ 10^8 | ~10^8 | O(n), O(1) |

## `stderr`: the channel that does not pollute your answer

Here is the observation that makes blind debugging tractable. The checker compares your program's **standard output** against expected output. Standard error is a *separate stream*. Writing to `cerr` does not put a single byte into `cout`.

```cpp
#include <iostream>

int main() {
    int n;
    std::cin >> n;

    std::cerr << "[dbg] n = " << n << "\n";   // does NOT enter stdout

    std::cout << n * 2 << "\n";               // this is the answer
    return 0;
}
```

::: keypoint
`cerr` is unbuffered and independent of `cout`. On platforms that display a "Debug output" / "stderr" pane — HackerRank does, and most custom-input runners do — you get full `printf`-style debugging **with zero risk of corrupting the graded output.** This is the single highest-value habit in this section: develop the reflex of typing `cerr` rather than `cout` for anything diagnostic, always, even in local testing, so that the debug lines are already safe when you paste into an OA.
:::

::: trap
**Verify the platform's stderr policy once, cheaply, before relying on it.** A small number of graders capture stderr into the comparison, or kill submissions that write to it, or cap total output across both streams. Test it with a throwaway submission on a problem you have already solved: add one `cerr` line to an Accepted solution and re-submit. Still Accepted → stderr is safe on this platform, and you now know it for every remaining question. Verdict changes → you have learned something vital for two minutes of cost.

Note also that `cerr` writes are **slow** (unbuffered, one syscall per insertion). A `cerr` inside a 10^6-iteration loop can turn a passing solution into a TLE. Guard heavy tracing behind a condition, and strip it before final submission regardless.
:::

## Assertions: turning a hypothesis into a verdict

This is the core technique. `assert` calls `abort()` when its condition is false, which kills the process — producing **Runtime Error**. So:

> Write an assertion that holds if and only if your hypothesis about the hidden data is true. Submit. **Accepted / Wrong Answer means the hypothesis held on every test; Runtime Error means it failed on at least one.**

You have just performed a query against a database you cannot read.

```cpp
#include <cassert>
#include <iostream>

int main() {
    int n;
    std::cin >> n;

    assert(n >= 1 && n <= 100000);   // RE ⇒ the real bounds differ from the statement
    assert(n % 2 == 0);              // RE ⇒ odd n occurs in the hidden tests

    // ... solution ...
}
```

Empirically, on `g++`/Linux — which is what these platforms run — a failed assertion produces:

```
p3: probe3.cpp:2: int main(): Assertion `1==2' failed.
```

on **stderr**, with **exit code 134** (`SIGABRT`). Two useful consequences: the message names the source line, so if the platform shows stderr you learn *which* assertion fired; and 134 is distinguishable from 139 (`SIGSEGV`, a null/out-of-bounds dereference), so the exit code alone tells you whether you asserted or crashed.

::: keypoint
**Questions worth asking the hidden tests via assertion:**

- *Are the stated constraints real?* `assert(n <= 100000);` — statements are frequently copied between problems and left stale.
- *Is the input sorted / distinct / positive?* Statements omit these constantly, and the answer changes your algorithm.
- *Can this edge case occur?* `assert(!v.empty());`, `assert(k <= (int)v.size());`
- *Is my invariant actually invariant?* Put the assertion inside the loop, on the property your correctness argument depends on.
- *Does the ambiguous reading matter?* If you cannot tell whether "positive" means `> 0` or `>= 0`, assert that the distinguishing case never arises. If that passes, the ambiguity is untested and you can stop worrying.
:::

::: trap
**`assert` is disabled by `-DNDEBUG`.** Some judges compile with `-O2 -DNDEBUG`, which makes every assertion a no-op and silently destroys this technique — you would read "no Runtime Error" as "hypothesis confirmed" when in fact nothing was checked. Calibrate first with a deliberately false assertion (`assert(false);`) on an already-Accepted solution: if the verdict does not become Runtime Error, assertions are compiled out on this platform, and you must use an explicit abort instead:

```cpp
if (!(condition)) { volatile int *p = nullptr; *p = 1; }   // forced SIGSEGV, survives -DNDEBUG
```
:::

### Binary-searching the failure

Once you have a reliable crash channel, you can localise a bug across submissions. Suppose your solution is Wrong Answer and you suspect it breaks for large inputs. Submit with `assert(n <= 1000);`:

- **Runtime Error** → the hidden tests do contain large `n`; your suspicion is live, and the failure is plausibly a complexity or overflow issue.
- **Wrong Answer** (unchanged) → every hidden test has small `n`; large-input reasoning is a dead end and the bug is logical.

Each submission yields one bit. Three or four well-chosen submissions narrow a mystery dramatically. Spend them on hypotheses that *change what you would do next*, not on confirming things you already believe.

::: trap
**Submission counts are sometimes limited, and always timed.** Check the rules before burning attempts on probes. If the platform offers a **Run** button with custom input that does *not* consume a submission, do all of this there instead — probing is only a last resort for information that exists solely in the hidden tests.
:::

## The custom-input panel is an oracle — use it properly

Most OA platforms provide a "Run with custom input" box that executes your code against text you supply and shows stdout, stderr, and often the exit status. This is enormously more powerful than it appears, and most candidates use it for exactly one thing (pasting sample 1) before abandoning it.

::: keypoint
**A disciplined custom-input protocol, in order:**

1. **Round-trip the provided sample verbatim, before writing any logic.** Paste the sample into the box and run the untouched stub. You are testing *the harness and your understanding of the input format* — not your algorithm. If the stub reads the input without crashing, your mental model of the format is right.
2. **Reproduce every sample.** If sample 2 fails while sample 1 passes, diff the two inputs and you have localised the bug to whatever differs.
3. **Then attack the edges the samples do not cover.** Minimum n. Maximum n. All elements equal. Already sorted. Reverse sorted. Single element. Empty collection. The value `0`. Negative values, if the constraints permit them.
4. **Test the ambiguity directly.** Every time you had to *guess* what the statement meant, construct an input where the two readings give different answers, and check which one your code implements. You still will not know which is correct — but you will know precisely what you have built, and that is what makes an assertion probe worth spending.
5. **Test the maximum bound for time.** Generate the largest legal input and run it. Custom-input runs usually report wall time. This converts a suspected TLE from speculation into a measurement.
:::

Generating a large input by hand is impractical; generate it *from your program* on the local machine, or add a temporary branch to the submitted code that synthesises the input instead of reading it:

```cpp
    // Temporary: replace stdin with a worst case to measure runtime.
    int n = 200000;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = (i * 1103515245 + 12345) & 0x7fffffff;
```

::: trap
**Whitespace and trailing-newline mismatches are invisible in the custom-input box.** The panel renders your output as text, so a trailing space, a missing final newline, or `\r\n` line endings from a copy-paste look identical to correct output. If a solution passes visibly-identical output but fails the grader, this is a prime suspect. Most graders trim trailing whitespace, but not all — and none forgive a *missing* separator between fields.
:::

## Reading compiler messages precisely

The compile error is the one message an OA gives you in full. It is worth being fluent.

### Read the first error, not the last

`g++` errors cascade: one missing semicolon produces forty messages. **The first error is almost always the real one**; everything after it is the compiler confused by its own recovery. Scroll up, not down.

### The template error wall

An error inside `std::sort` or `std::map` produces hundreds of lines of instantiation trace. The technique is to ignore all of it and find the line reading:

```
required from here
```

The line **immediately above** that phrase is the line *you* wrote that triggered the instantiation. That is your bug. The wall of `_M_insert<...>` noise is the library's internals and is never where you fix anything.

### The messages that mean something specific

| Message | Actual cause |
|---|---|
| `'x' was not declared in this scope` | Typo, missing `#include`, or a variable used outside the block that declares it |
| `no matching function for call to 'f(...)'` | The types you passed do not match any overload — read the *candidate* list for what it expected |
| `invalid conversion from 'const char*' to 'int'` | Almost always `'x'` vs `"x"`, or arguments in the wrong order |
| `expected ';' before '}'` | The missing token is usually at the **end of the previous line** |
| `cannot bind non-const lvalue reference to an rvalue` | Passing a temporary to a `T&` parameter — the parameter wants `const T&` |
| `passing 'const X' as 'this' argument discards qualifiers` | Calling a non-`const` method inside a `const` method, or on a `const` reference |
| `undefined reference to 'f'` | This is the **linker**, not the compiler — declared but never defined |

::: keypoint
**Turn on the warnings that find real bugs.** Locally, always compile with:

```
g++ -std=c++17 -O2 -Wall -Wextra -fsanitize=address,undefined -D_GLIBCXX_DEBUG prog.cpp
```

Each flag catches a distinct class of silent failure, and every one of these has been verified to fire:

- `-Wall -Wextra` catches uninitialised reads at *compile* time —
  `warning: 's' is used uninitialized [-Wuninitialized]`
- `-fsanitize=undefined` catches signed overflow at *run* time —
  `runtime error: signed integer overflow: 2000000000 * 2 cannot be represented in type 'int'`
- `-fsanitize=address` catches out-of-bounds heap/stack access with the exact offending address
- `-D_GLIBCXX_DEBUG` upgrades `vector::operator[]` out-of-range from silent memory corruption into a
  clean abort naming the container and the index

Never submit with these flags — sanitizers slow execution by 2–20× and will cause TLE. They are for the local pass before you paste.
:::

## The silent killers

These are the bugs that compile cleanly, run without crashing, produce plausible output on the samples, and fail hidden tests with no diagnostic whatsoever. On a blind platform they are the expensive ones, because nothing points at them.

### Integer overflow

The single most common cause of "correct algorithm, Wrong Answer".

::: trap
`int` holds up to 2,147,483,647 — a little over 2·10^9. Sums, products and counts blow past that constantly: `n = 2·10^5` elements of size `10^9` sum to 2·10^14, five orders of magnitude over. The arithmetic wraps silently, produces a wrong number, and the program continues happily.

Watch specifically for **intermediate** overflow, which survives even a `long long` destination:

```cpp
int a = 100000, b = 100000;

long long bad  = a * b;              // a, b are int → the MULTIPLY overflows first
long long good = (long long)a * b;   // widen BEFORE the operation
// bad  == 1410065408   (wrapped)
// good == 10000000000  (correct)
```

`(l + r) / 2` in binary search is the classic instance — `l + r` overflows before the division. Prefer `l + (r - l) / 2`. When in doubt, use `long long` everywhere; the performance cost is negligible and the debugging cost of an overflow you cannot see is enormous.
:::

### Failed reads leave the variable unchanged

This one is worth its own warning because its symptom is so misleading.

::: trap
Since C++11, a failed `cin >> x` — at end of input, or on a type mismatch — sets the stream's fail bit and leaves **`x` at its previous value** (verified: a variable holding `777` still holds `777` after the failed read). Consequences:

- A read loop that runs one iteration too many silently **reprocesses the previous value**, typically emitting one extra line of output. If your output has exactly one spurious trailing line, this is almost certainly why.
- Once the fail bit is set, **every subsequent read is a no-op**. A single mis-parse near the start turns the rest of your input handling into garbage, and the resulting output looks like a logic bug.

Drive every loop from the count declared in the input, never from "read until it stops working", and check `if (!(cin >> n)) return 0;` at the top when the format permits.
:::

### Uninitialised variables

`int sum;` inside a function does not contain zero — it contains whatever was on the stack. The program is *usually* fine by luck locally and fails on the grader, or vice versa, which makes it maddening to chase. `-Wall` catches the straightforward cases at compile time; initialise everything explicitly regardless.

### The stub's poisoned initialiser

::: trap
Function-stub harnesses habitually seed the answer variable with a sentinel:

```cpp
int totalAmount(int x, int y)
{
    int count = -1;          // <- this is a decoy

    // WRITE YOUR CODE HERE

    return count;
}
```

If your logic legitimately accumulates nothing — an empty range, no matching elements, a sum of zero items — you return `-1` instead of `0`. There is virtually always a hidden test for exactly this. **Overwrite the initialiser explicitly**, even when it looks harmless. The same applies to placeholder return strings: a Python stub setting `final_output = "NONE"` while the specification says to return `"NA"` is a trap, not a hint.
:::

### Undefined behaviour that "works"

`v[i]` past the end of a `vector` does not check anything; it reads adjacent memory and returns a plausible number. Verified: the same out-of-bounds write that silently corrupts memory under plain `g++` aborts cleanly under `-D_GLIBCXX_DEBUG`. Locally, use `.at()` or the debug flag while developing, then switch to `[]` for the submission if you need the speed.

## Reconstructing the hidden tests from the statement

The hidden tests are not arbitrary. They were written by a person, from the same statement you are reading, and that makes them predictable.

::: keypoint
**A test-setter writes, near-universally:** the provided samples; the minimum and maximum of every stated bound; each explicitly named edge case; one test per branch of the specification; and — critically — **one test per rule that the statement bothered to state separately.**

That last one is the most useful heuristic in this section. If a specification says *"processingHours must be greater than or equal to zero"*, there is a test with a negative value. If it says *"a delivered shipment must never be printed, even if its risk score is HIGH"*, there is a test with a high-scoring delivered shipment. **Every sentence that exists only to exclude something is a test case.** Go through the statement, list every such sentence, and construct that input yourself in the custom-input box.
:::

::: trap
**When a worked explanation contradicts the rules, trust the rules and the sample *output*.** Sample explanations are hand-written prose; they are not generated from the reference solution, and they contain arithmetic errors with some regularity. The sample *output* is machine-generated and is ground truth. If implementing the rule literally reproduces the sample output, the rule is right and the explanation's intermediate numbers are wrong.
:::

## When you are convinced your code is right

Sometimes it is. The expensive failure mode is the inverse of the usual one: **you conclude your code is broken, when in fact your hand-computed expected value is wrong.**

::: heavy
This is not hypothetical. Both worked examples written by hand for the DE Shaw problems in this collection turned out to be wrong, and both were caught only by running the solution against a brute force — one claimed a maximum of 2 flips where the true answer is 3, the other declared five queries in a header while supplying four. Neither error was visible by inspection. Had either been used as an OA sanity check, the natural conclusion would have been "my implementation is broken", and the next hour would have gone into fixing correct code.
:::

The defence is **stress testing**, and it is the most reliable debugging technique in existence for problems with small-case verifiability:

1. Write a deliberately naive, obviously-correct brute force — exponential is fine.
2. Write a generator producing small random inputs (n ≤ 8) within the constraints.
3. Loop: generate, run both, compare. Stop at the first mismatch.
4. That mismatch is a **minimal failing case you can actually look at** — the exact thing the OA refuses to give you.

```python
import random, subprocess
for _ in range(500):
    n = random.randint(1, 8)
    a = [random.randint(1, 12) for _ in range(n)]
    inp = f"{n}\n" + " ".join(map(str, a)) + "\n"
    fast = subprocess.run(["./fast"], input=inp, capture_output=True, text=True).stdout
    slow = subprocess.run(["./brute"], input=inp, capture_output=True, text=True).stdout
    if fast.split() != slow.split():
        print("MISMATCH on:\n" + inp, "fast:", fast, "brute:", slow)
        break
```

::: keypoint
Small random cases find nearly every bug. A counter-example almost always exists at n ≤ 8, because the logic errors that matter — an off-by-one, a wrong comparison, a mishandled tie — do not require large inputs to manifest. Generate small and generate *many*; hundreds of tiny cases beat a handful of large ones, and a tiny failing case is one you can trace by hand.
:::

## The pre-submission checklist

::: interview
Run this list before every OA submission. It takes ninety seconds and catches the overwhelming majority of blind failures.

1. **Removed every debug print from `cout`?** Search the source for `cout` and confirm each one is genuine output. Debug lines belong in `cerr`, and ideally are deleted.
2. **Overwrote the stub's sentinel initialiser** (`= -1`, `= "NONE"`)?
3. **`long long` anywhere a sum, product or count can exceed 2·10^9** — including intermediates?
4. **Complexity checked against the stated bound**, not against the sample size?
5. **Both samples reproduced exactly**, including separators and line endings?
6. **Edge cases run in the custom-input box:** minimum n, maximum n, all-equal, single element, empty?
7. **Every variable initialised?**
8. **Output format exact** — separator character, field order, no trailing separator, correct empty-case token?
9. **Sanitizer and debug flags removed** from the submitted code?
10. **`endl` replaced with `'\n'`** in any loop that runs more than a few thousand times?
:::

::: heavy
The meta-lesson: on a platform that shows you nothing, **the information has to come from somewhere you control.** It comes from the constraint block (which specifies the algorithm), from the statement's exclusion clauses (which enumerate the tests), from `cerr` and the custom-input runner (which give you real observation), from assertions (which convert a hypothesis into a verdict), and from stress testing against a brute force (which manufactures the failing case the platform withheld). None of these require seeing the tests. All of them require deciding, before you write code, what you would need to know — and then building the code so that it tells you.
:::
