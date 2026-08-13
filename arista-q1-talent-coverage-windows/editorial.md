# Talent Coverage Windows

## The observation that makes it linear

Write `end(i)` for the first position at which a group starting at `i` becomes complete. The whole
problem is the claim:

> `end(i)` never decreases as `i` increases.

Which is obvious once stated: the group starting at `i+1` is the group starting at `i` with one
student removed. Removing a student cannot complete a collection that was not already complete, so
`i+1` can never finish earlier than `i` did.

So the right end only ever moves forward. Across the entire run it advances at most `n` times, which
is what turns an apparently quadratic problem — "for each of `n` starts, find a window" — into a
single pass.

## The sweep

Keep `seen[t]`, a count per talent, and `distinct`, how many talents currently have a non-zero
count. For each start `i`:

1. Push the right end forward while the group is incomplete.
2. If it is complete, `ans[i] = r - i`. If the queue ran out first, `ans[i] = -1` — **and so is every
   later answer**, because a later start has strictly fewer students available. Break.
3. Remove student `i` from the counts before moving on.

Each of `i` and `r` advances at most `n` times, so this is O(n + talentsCount).

## Where this goes wrong

**Recomputing completeness from scratch.** Calling a `check()` helper that scans all
`talentsCount` counters on every step is O(n · talentsCount) and times out on the large tests.
The count of distinct talents has to be maintained incrementally: it goes up exactly when a counter
rises from 0 to 1, and down exactly when one falls from 1 to 0. Those two lines replace the helper.

**Not stopping at the first `-1`.** Once the right end has hit the end of the queue without
completing, no later start can complete either. Continuing to loop is not wrong, but it is easy to
write it so the right end tries to advance again on every remaining index.

**Off-by-one in the length.** The answer is `r - i` when `r` is one past the last student taken,
and `r - i + 1` when `r` is the last student taken. Pick one convention and hold it; `[2,3,1,2]`
with `talentsCount = 3` is a good check — `ans[0]` is 3, not 4. (`[2,2,3,1]` is the one that
answers 4, because the duplicate at the front buys nothing.)

## A C++ trap worth knowing

Calling the frequency array `hash` compiles fine as a **local**:

```cpp
int main() {
    vector<int> hash(k + 1);   // fine — shadows ::std::hash
    hash[talent[r]]--;
}
```

but as a **global**, alongside `using namespace std;`, it detonates:

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> hash(200001);      // <-- namespace scope
bool check() { ... }

int main() { hash[talent[r]]--; }
```

```
error: reference to 'hash' is ambiguous
note: candidates are: 'template<class _Tp> struct std::hash'
```

`std::hash` is a class template, `using namespace std;` drags it into the global namespace, and now
`hash` at namespace scope is two different things. The error is reported at every *use*, not at the
declaration, so a single bad name produces a screenful of errors pointing at lines that are
perfectly correct. A local declaration shadows the `std` name and is fine — which is why moving the
array inside `main` can make the same code compile.

Other names that do this: `count`, `distance`, `size`, `data`, `begin`, `end`, `next`, `prev`,
`swap`, `max`, `min`, `left`, `right`, `y1`. If a variable name produces errors that make no sense,
rename it before reading them.
