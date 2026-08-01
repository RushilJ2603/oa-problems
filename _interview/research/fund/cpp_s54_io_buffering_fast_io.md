# Input, Output, and Buffering: Streams from the Ground Up

Every C++ tutorial mentions "the input buffer" when explaining `cin` and `getline`, yet almost none explain what that buffer *is*, why it exists, or how characters actually move between your program and the keyboard. This section fills that gap: buffering from first principles, the mechanics of `cin`/`cout`, the classic mixing trap, stream-state loops, and the competitive-programming fast-I/O boilerplate.

::: heavy
Dense section — slow down. Buffering, flush rules, and the `>>`/`getline` interaction are the foundation for every I/O bug and every "why is my contest code TLE?" question about printing.
:::

## What a buffer actually is (and why it exists)

### The cost of talking to the operating system

Reading a keystroke or writing a character ultimately requires a **system call** — which means a transition from user mode into the kernel, copying data, and returning. That round-trip is orders of magnitude more expensive than touching ordinary memory. If every `cout << 'a'` or every character of input triggered a system call, even a small program would crawl.

The solution is **batching**. The C++ stream library (and beneath it, the C stdio layer and the OS) keeps an in-memory array of characters — a **buffer** — and only talks to the kernel when that array fills, empties, or is forcibly emptied.

::: definition
An I/O **buffer** is a block of memory owned by the stream (via its `std::streambuf`) that accumulates characters so the program can perform many cheap memory operations for each expensive OS transfer.
:::

### The data path

Characters do not jump straight from your source code to the terminal. They travel through layers:

```
  your program  ↔  stream buffer (streambuf)  ↔  OS kernel buffer  ↔  device
       │                    │                         │
   cin / cout          in-memory array          read/write syscall
```

![I/O flows through in-memory buffers so many reads/writes cross the expensive syscall boundary in a few batches.](assets/s54_io_dataflow.png)

- **Output** (`cout << ...`): characters are written into the stream's output buffer. Only when the buffer is flushed do those bytes cross into the OS and eventually the device.
- **Input** (`cin >> ...` / `getline`): the stream asks the OS for a chunk of data (often a whole line from the terminal), parks it in the input buffer, and then your extractions consume characters from that in-memory store — without another syscall for every token.

A brief C contrast aids intuition: C's `FILE*` (`stdin`/`stdout`/`stderr` in `<stdio.h>`) uses the same buffering idea. C++ `iostream` objects sit above their own `streambuf`, and by default are *synchronised* with the C stdio buffers — a detail that matters later for fast I/O.

### The three standard streams and their buffering modes

`<iostream>` provides three (plus `clog`) global objects, each with a conventional buffering policy:

| Stream | Role | Typical buffering |
|--------|------|-------------------|
| `std::cin` | Standard input | Fully buffered for efficiency; often filled a line at a time from a terminal |
| `std::cout` | Standard output | **Line-buffered** when connected to a terminal; **fully buffered** when redirected to a file/pipe |
| `std::cerr` | Standard error | **Unbuffered** — every write is effectively flushed so diagnostics appear immediately |
| `std::clog` | Logging to stderr | Buffered (like `cout`), for bulk log volume |

::: definition
- **Fully buffered**: characters sit in memory until the buffer is full, or an explicit flush occurs.
- **Line-buffered**: the buffer is also flushed when a newline (`'\n'`) is written (typical for interactive terminals).
- **Unbuffered**: characters are handed to the OS as soon as they are written (as with `cerr`).
:::

### When a buffer is flushed

An **output flush** means: copy the pending characters out of the stream buffer into the OS (and toward the device). Flushing happens when any of the following occurs:

1. **The buffer is full** — natural consequence of full buffering.
2. **A newline is written** — for line-buffered streams (interactive `cout`).
3. **Explicit flush** — `std::cout.flush()`, `std::flush` manipulator, or `std::endl` (newline *plus* flush).
4. **Program exit** — destructors and the runtime flush open streams so pending output is not lost.
5. **Reading from a tied stream** — by default `cin` is **tied** to `cout`, so any input operation on `cin` first flushes `cout`. That way a prompt printed with `cout` appears before the program blocks waiting for input.

```cpp
#include <iostream>

int main() {
    std::cout << "Enter n: ";   // may sit in the buffer...
    int n = 0;
    std::cin >> n;              // ...but tie flushes cout before waiting
}
```

::: keypoint
`cin` is tied to `cout` so prompts show up before you block on input. `cin.tie(nullptr)` breaks that link — useful for speed in contests, dangerous if you forget to flush prompts yourself.
:::

## `cin` and `cout` mechanics

### Formatted extraction: `operator>>`

The overloaded **extraction operator** `>>` performs *formatted* input: it converts a character sequence into a typed value (`int`, `double`, `std::string`, …).

Rules that matter in practice:

1. **Leading whitespace is skipped.** Spaces, tabs, and newlines before the token are discarded.
2. **Extraction stops at the next whitespace** (or when the token is complete for that type). That terminating whitespace is **not consumed** — it remains in the input buffer for the next operation.
3. For `std::string`, `>>` reads one whitespace-delimited word, not a full line.

```cpp
#include <iostream>
#include <string>

int main() {
    int age = 0;
    std::string word;

    // User types:  25 Alice\n
    std::cin >> age;   // reads "25"; buffer left with " Alice\n"
    std::cin >> word;  // skips space, reads "Alice"; buffer left with "\n"
}
```

That leftover `'\n'` is harmless if the next operation is also `>>` (which skips it). It is disastrous if the next operation is `getline` — see the trap below.

### Formatted insertion and flushing on `cout`

`operator<<` converts values to characters and appends them to `cout`'s buffer. Visibility on screen depends on buffering mode and flush points. Prefer `"\n"` for ordinary newlines; reserve flushing for when the user (or judge) must see output *now*.

```cpp
#include <iostream>

int main() {
    std::cout << "partial";           // may not appear yet
    std::cout << std::flush;          // force pending output out
    std::cout << " done\n";           // newline; may flush if line-buffered
}
```

## THE CLASSIC TRAP: `cin >>` then `getline`

This is the single most common interactive-I/O bug in C++ student and interview code.

::: trap
After `std::cin >> x`, the terminating newline stays in the buffer. The next `std::getline(std::cin, s)` consumes that leftover `'\n'` immediately, stores an empty string, and never waits for the line you intended to type.
:::

### Step-by-step: what the buffer holds

Suppose the user will type age `25`, press Enter, then type `Ada Lovelace` and press Enter again.

```cpp
#include <iostream>
#include <string>

int main() {
    int age = 0;
    std::string name;

    std::cin >> age;               // (1)
    std::getline(std::cin, name);  // (2) — bug: name becomes ""
    // name was meant to be "Ada Lovelace"
}
```

![Why `getline` reads an empty line right after `cin >> x`: the leftover newline is consumed as an empty line.](assets/s54_getline_trap.png)

Trace the buffer (characters waiting to be read):

| Step | Action | Buffer contents (schematic) | Effect |
|------|--------|-----------------------------|--------|
| 0 | User typed `25\n` | `['2','5','\n']` | waiting |
| 1 | `cin >> age` | `['\n']` | read `25`; **left** `'\n'` |
| 2 | `getline(cin, name)` | `[]` | sees `'\n'` at once; stores `""`; **consumes** delimiter |
| — | User's next line never paired with this `getline` | | |

Why? `>>` stops *before* whitespace and leaves it. `getline` reads *until* the delimiter and treats that leftover newline as "end of an empty line".

### The fix

Discard the remainder of the current line (at least the leftover newline) before calling `getline`.

**Option A — `ignore` (most common):**

```cpp
#include <iostream>
#include <string>
#include <limits>

int main() {
    int age = 0;
    std::string name;

    std::cin >> age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Discard everything up to and including the next '\n'

    std::getline(std::cin, name); // waits for a real line, spaces included
}
```

`ignore(n, delim)` discards up to `n` characters or until `delim` is extracted (and discarded). Passing `numeric_limits<streamsize>::max()` means "as many as needed until the newline".

**Option B — `std::ws` manipulator:**

```cpp
#include <iostream>
#include <string>

int main() {
    int age = 0;
    std::string name;

    std::cin >> age;
    std::getline(std::cin >> std::ws, name); // skip leading whitespace, then line
}
```

`std::ws` extracts and discards leading whitespace (including the leftover `'\n'`). This is tidy when you want the next *non-empty* line; prefer `ignore` when you must discard exactly the rest of the *current* line even if more content followed the number on the same line.

::: interview
"Why does `getline` read an empty string after `cin >> n`?" Answer: `>>` leaves the newline; `getline` treats that newline as a complete (empty) line. Fix with `cin.ignore(numeric_limits<streamsize>::max(), '\n')` or extract with `>> std::ws` before `getline`.
:::

## `getline` in full

### Signatures

The usual overload lives in `<string>` as a free function (there is also `istream::getline` for C-style `char` buffers — prefer the `std::string` form):

```cpp
#include <string>
#include <iostream>

// Read until '\n' (default delimiter)
std::istream& std::getline(std::istream& is, std::string& str);

// Read until a custom delimiter
std::istream& std::getline(std::istream& is, std::string& str, char delim);
```

### Behaviour

1. Characters are extracted from `is` and appended to `str` (after `str` is cleared).
2. Extraction stops when `delim` is found, when the stream ends, or on error.
3. The delimiter is **consumed** (removed from the stream) but **not stored** in `str`.
4. The function **returns the stream**, so it can be used as a `while` condition (`operator bool` on the stream).

```cpp
#include <iostream>
#include <string>

int main() {
    std::string line;
    // Returns the stream; loop while a line was successfully read
    while (std::getline(std::cin, line)) {
        // 'line' has no trailing '\n'; may be empty if the line was blank
        std::cout << "[" << line << "]\n";
    }
}
```

Custom delimiter example (CSV-style field):

```cpp
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::istringstream in("a,b,c");
    std::string field;
    while (std::getline(in, field, ',')) {
        std::cout << field << "\n"; // a  then b  then c
    }
}
```

### Difference from `>>`

| | `cin >> s` | `getline(cin, s)` |
|--|------------|-------------------|
| Skips leading whitespace? | Yes | No (leading spaces are part of the line) |
| Stops at | First whitespace | Delimiter (default `'\n'`) |
| Consumes trailing whitespace/delimiter? | Leaves it | Consumes delimiter, does not store it |
| Reads phrases with spaces? | No (one word) | Yes (whole line) |

::: keypoint
Use `>>` for whitespace-separated tokens and numbers. Use `getline` when the unit of input is a whole line — including spaces — such as names, sentences, or contest problems that specify "the next line contains…".
:::

## Reading until EOF and stream state

### Loop idioms

Both of these stop cleanly when extraction fails (including end-of-file):

```cpp
#include <iostream>
#include <string>

void words() {
    int x;
    while (std::cin >> x) {
        // process x
    }
}

void lines() {
    std::string line;
    while (std::getline(std::cin, line)) {
        // process line
    }
}
```

Why the loop works: `operator>>` and `getline` return the stream. In a boolean context the stream converts via `operator bool()`, which is `true` while the stream is not in a failed state (`!fail()`). Hitting EOF during an extraction sets `eofbit` and usually `failbit`, so the loop condition becomes false.

### State flags (compact reference)

::: definition
A stream keeps an **`iostate` bitmask**: `goodbit`, `eofbit`, `failbit`, and `badbit`. Query with `good()`, `eof()`, `fail()`, `bad()`; reset with `clear()`.
:::

| Flag / query | Meaning |
|--------------|---------|
| `good()` | No error bits set |
| `eof()` | End-of-file reached |
| `fail()` | Logical failure (e.g. tried to read `int`, got `"abc"`) — or EOF on extraction |
| `bad()` | Hard failure (e.g. disk error) |
| `operator bool` | Equivalent to `!fail()` for loop conditions |

### Recovering from a failed extraction

A failed `>>` sets `failbit` and **leaves the bad characters in the buffer**. Further I/O is a no-op until you recover:

```cpp
#include <iostream>
#include <limits>

int main() {
    int x = 0;
    if (!(std::cin >> x)) {
        std::cin.clear(); // reset failbit / eofbit so the stream works again
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // discard the rest of the line, including the offending token
    }
}
```

Full treatment of the stream hierarchy and file I/O lives in the streams section (`s42`); here the essential point for loops is: **failed state ⇒ clear, then ignore residual input**.

::: interview
Expect "how do you read until EOF?" — answer with `while (cin >> x)` or `while (getline(cin, line))`, and explain that the stream's boolean conversion reflects `fail()`. Mentions of `clear()` + `ignore()` after bad input score well.
:::

## `endl` versus `"\n"`

```cpp
std::cout << x << std::endl; // newline AND flush
std::cout << x << '\n';      // newline only (flush later by policy / explicit flush)
```

::: trap
`std::endl` flushes the stream every time. Inside a tight loop (or contest output of \(10^5\)–\(10^6\) lines) those flushes dominate run time and can cause TLE. Prefer `'\n'` (or `"\n"`) and flush once at the end if needed: `std::cout << std::flush;`.
:::

```cpp
#include <iostream>

int main() {
    // Slow in competitive programming:
    // for (int i = 0; i < n; ++i) std::cout << i << std::endl;

    // Fast pattern:
    for (int i = 0; i < 100000; ++i)
        std::cout << i << '\n';
    std::cout << std::flush; // optional single flush
}
```

## Fast I/O for competitive programming

Contest problems often dump megabytes of input. Default C++ stream behaviour is correct but deliberately conservative: it stays synchronised with C stdio and keeps `cin` tied to `cout`. Turning those off is the standard speed-up.

### `ios_base::sync_with_stdio(false)`

By default, C++ streams (`cin`/`cout`) and C stdio (`scanf`/`printf`, `stdin`/`stdout`) share coordinated buffering so mixing them is safe.

```cpp
std::ios_base::sync_with_stdio(false);
```

This **decouples** the two layers. Each uses its own buffers independently. The C++ side can then buffer more aggressively and avoid the synchronisation tax — often a large speed win.

::: trap
After `sync_with_stdio(false)`, **do not mix** `cin`/`cout` with `scanf`/`printf` (or other C stdio on the same streams). The buffers diverge; you can lose, reorder, or corrupt I/O. Pick one style for the whole program.
:::

Call it **before any I/O**. Calling it after the first `cin`/`cout`/`printf` is implementation-defined in effect and may be ignored.

### `cin.tie(nullptr)`

```cpp
std::cin.tie(nullptr);
```

By default `cin.tie(&cout)` means every input operation flushes `cout` first. That is polite for interactive prompts and costly when you interleave huge volumes of input and output. Untying removes automatic flushes; flush yourself only when interactivity requires it.

### Standard boilerplate

Place this at the start of `main` (or before any I/O in a global init — `main` is clearest):

```cpp
#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Now safe to use cin/cout heavily; do not call scanf/printf
    int n;
    std::cin >> n;
    std::string line;
    std::getline(std::cin >> std::ws, line); // getline still works after sync-off

    std::cout << n << '\n' << line << '\n';
}
```

::: keypoint
`getline` continues to work after `sync_with_stdio(false)`. Untying and desynchronising change *performance and flush coupling*, not the meaning of `>>` or `getline`. Still use `ignore` / `ws` when mixing `>>` with `getline`.
:::

### Reading large input — practical notes

- Prefer `cin` with the boilerplate above for most contests; it is fast enough for typical limits once sync and tie are off.
- Still avoid `endl` in output loops.
- For extreme input sizes some competitors use custom buffer readers; that is optional sophistication — know the two-liner above first.
- Interactive problems are different: you may *need* ties or explicit `flush` so the judge sees output before your next read.

::: interview
"How do you speed up C++ I/O in contests?" State both calls, explain sync (C++ ↔ C stdio) and tie (`cout` flush before `cin`), list caveats (no mixing with `scanf`/`printf`; call before I/O), and mention preferring `'\n'` over `endl`.
:::

## Brief toolkit: stringstream, precision, and files

### `stringstream` for parsing and conversions

`<sstream>` gives stream semantics over an in-memory `string` — ideal for tokenising a line you already read with `getline`, or converting between numbers and strings.

```cpp
#include <sstream>
#include <string>
#include <iostream>

int main() {
    std::string line = "10 20 30";
    std::istringstream iss(line);
    int a, b, c;
    iss >> a >> b >> c; // parse tokens from the line

    std::ostringstream oss;
    oss << "sum=" << (a + b + c);
    std::string out = oss.str(); // number/text → string
}
```

### Output precision

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double x = 3.1415926535;
    std::cout << std::fixed << std::setprecision(6) << x << '\n';
    // fixed: precision = digits after the decimal point
}
```

`std::setprecision` without `fixed` sets significant digits for default floating format; with `std::fixed` it sets digits after the decimal. Include `<iomanip>`.

### File streams

File I/O uses `std::ifstream` / `std::ofstream` / `std::fstream` from `<fstream>`, with the same `>>`, `<<`, `getline`, and state-flag rules as `cin`/`cout`. Open modes, RAII closing, text versus binary, and hierarchy details are covered in **Streams and File I/O** (`s42`) — the buffering and flush ideas in this section apply equally to file streams (files are typically fully buffered).

## Looking ahead

You now have a coherent model: characters sit in stream buffers; `>>` and `getline` consume those buffers by different rules; flush policy explains `endl`, ties, and interactive prompts; and two calls unlock contest-grade throughput. Treat every I/O surprise as a question about *what is still sitting in the buffer* and *when that buffer is emptied* — that habit eliminates most stream bugs at the source.
