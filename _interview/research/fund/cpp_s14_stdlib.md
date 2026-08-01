# 14. The C Standard Library

The C language itself is remarkably small; it provides almost no built-in primitives for input, output, memory allocation, or string manipulation. Instead, C relies on the **C Standard Library** (often called `libc`), a standardized collection of macros, types, and functions [1].

## 14.1 The Execution Environment: Hosted vs. Freestanding

```{=typst}
#heavy[
```

Dense — slow down: The standard library is not guaranteed to exist everywhere C code runs.

**Analogy:** Writing a C program is like moving into a house. A **hosted environment** is a fully furnished apartment—water, electricity, and appliances (`malloc`, `printf`, file systems) are ready to use. A **freestanding environment** is a plot of land in the wilderness. You have to dig your own well and build your own generator. 

**Example:** If you write `printf("Hello World");` on a Linux PC, the operating system knows how to draw text on your terminal. If you write that same code for a bare-metal microcontroller chip in a microwave oven, where does the text go? There is no screen and no operating system to handle the text [1].

**Plain English:** The C standard defines two worlds. In a hosted environment (Linux, Windows, macOS), the OS provides a full standard library, and your program starts at `main`. In a freestanding environment (embedded firmware, OS kernels), the standard only guarantees a few essential headers defining compiler limits and types, and there is no file system or dynamic memory provided by default.

**Technical:** The freestanding headers include `<stdint.h>` (exact-width integer types), `<stddef.h>` (types like `size_t` and `NULL`), `<stdbool.h>` (boolean macros), `<limits.h>`, and `<float.h>`. Anything requiring an OS, like `<stdio.h>` or `<stdlib.h>`, is absent. 

**Boundary:** This abstraction breaks down when you try to port a C program written for a PC directly to a microcontroller without stripping out the `libc` calls.

```{=typst}
]
```

```{=typst}
#interview[
```

**Q:** Why might you explicitly avoid standard functions like `malloc` and `printf` in embedded firmware, even if a vendor provides a minimal libc?

**A:** `malloc` introduces non-deterministic execution time and the risk of heap fragmentation (eventually leading to out-of-memory errors on long-running systems where rebooting is unacceptable). `printf` is heavily bloated, consuming significant program memory (ROM), which is scarce on microcontrollers. Embedded systems often use static allocation and lightweight, custom formatting functions.

```{=typst}
]
```

## 14.2 Input and Output (`<stdio.h>`)

The `<stdio.h>` header provides standard I/O. It abstracts hardware devices (like keyboards, screens, and disk files) into a uniform concept called a **stream**.

![Standard I/O Streams and File Handling](assets/s14_streams.png)

### 14.2.1 Streams and `FILE*`

A stream is an abstract, sequential flow of bytes. When a C program starts in a hosted environment, three text streams are automatically opened:
1. `stdin` (Standard Input, typically the keyboard).
2. `stdout` (Standard Output, typically the terminal screen).
3. `stderr` (Standard Error, used for error messages, also typically the screen).

To interact with files on a disk, you use a `FILE*`. A `FILE` is an opaque data structure (its exact fields are hidden from you) that holds the state of a stream, including the current position and error flags [2].

```c
FILE *file = fopen("data.txt", "r"); // Open for reading
if (file == NULL) {
    // Handle error (file not found, permissions)
}
// ... read from file ...
fclose(file); // Flush buffers and close the stream
```

```{=typst}
#keypoint[
```

Always pair `fopen` with `fclose`. Failing to close a file leads to resource leaks (the OS limits how many files a program can open) and may cause buffered output to be lost permanently.

```{=typst}
]
```

**Buffering:** Most I/O is buffered for performance. When you call `fprintf` to a file, the text goes into a block of memory (a buffer), not directly to the hard drive. The buffer is "flushed" (written to the actual device) when it fills up, when the file is closed, or when explicitly triggered via `fflush(file)`. `stderr` is unbuffered by default, guaranteeing that error messages appear instantly if the program crashes.

### 14.2.2 Reading Text: `fgets` vs. `scanf`

When reading lines of text from `stdin` or a file, prefer `fgets` over `scanf`.

```c
char buffer[256];
if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    // We read a line safely. It includes the newline '\n' if there was room.
}
```

While `scanf` can parse formatted text, it is fragile. If a user enters letters when `scanf("%d", &num)` expects a number, `scanf` fails, leaves the invalid letters in the input stream, and causes an infinite loop if called repeatedly. A robust pattern reads a whole line into memory with `fgets`, then parses that memory.

```{=typst}
#trap[
```

**The `gets()` trap:** You may encounter `gets(buffer)` in older C books. **Never use it.** It has been completely removed from the C11 standard because it lacks a size parameter. It will blindly write past the end of your buffer if the user types a long line, making buffer overflows inevitable.

```{=typst}
]
```

### 14.2.3 Formatted Output: `printf` and `snprintf`

```{=typst}
#heavy[
```

Dense — slow down: The `sprintf` function formats a string into memory, but it cannot guarantee it won't write past the end of the destination array.

**Analogy:** Using `sprintf` is like pouring water into a bucket while blindfolded, stopping only when your pitcher is empty. If the pitcher holds more water than the bucket, it overflows and damages the floor. Using `snprintf` is pouring water but stopping when the bucket hits its maximum capacity mark.

**Example:**
```c
const char *username = "AlexanderTheGreat";
char msg[16];
// BAD: If username is "AlexanderTheGreat", this overflows msg.
// sprintf(msg, "Hi %s", username); 

// GOOD: Truncates safely if it exceeds 16 bytes.
snprintf(msg, sizeof(msg), "Hi %s", username);
```

**Plain English:** The `printf` family formats data into text using format specifiers like `%d` (integer), `%f` (float), and `%s` (string). When formatting text directly into a memory buffer instead of the screen, you must use `snprintf`, passing the exact size of the buffer so the function knows when to stop.

**Technical:** `int snprintf(char *restrict str, size_t size, const char *restrict format, ...)` writes at most `size - 1` characters to `str`, guaranteeing a null-terminator `\0` is appended. It returns the number of characters it *would* have written had the buffer been large enough, allowing you to detect truncation.

**Boundary:** This breaks down if you pass an incorrect size, such as `sizeof(ptr)` where `ptr` is a `char*` pointing to a dynamic array, resulting in a size of 8 instead of the actual array size.

```{=typst}
]
```

```{=typst}
#trap[
```

**Format String Vulnerability:** Never pass raw user input directly as the format string: `printf(user_input);`. If `user_input` contains `%s` or `%n`, `printf` will interpret them as formatting commands, reading from or writing to arbitrary stack memory. Always use `printf("%s", user_input);`.

```{=typst}
]
```

## 14.3 General Utilities (`<stdlib.h>`)

This header contains foundational operations: dynamic memory (`malloc`, `free`), program termination, and numeric conversions.

### 14.3.1 Robust String-to-Integer Conversion

```{=typst}
#heavy[
```

Dense — slow down: `atoi` fails silently. `strtol` reports errors.

**Analogy:** `atoi` is an unreliable assistant. You hand them a sticky note saying "42xyz" and ask "What number is this?" They reply "42" and throw away the "xyz". You hand them "hello" and they reply "0". `strtol` (string-to-long) is a meticulous accountant. They tell you "The number is 42, and by the way, I stopped reading here at the letter 'x'."

**Example:**
```c
char *endptr;
long val = strtol("42xyz", &endptr, 10);
// val is 42. endptr now points to "xyz".
```

**Plain English:** The `atoi` (ASCII to Integer) function is simple but provides no way to differentiate between a valid string `"0"` and an invalid string `"garbage"`, as both return `0`. Furthermore, if the number is too large to fit in an `int`, `atoi` triggers undefined behavior. `strtol` fixes this by providing an `endptr` to check if trailing garbage exists, and by setting a global error flag if the number overflows.

**Technical:** `long int strtol(const char *nptr, char **endptr, int base);` parses a string in a given base (like 10 for decimal, 16 for hex). If `endptr` is not `NULL`, `strtol` stores the address of the first invalid character in `*endptr`. If the value falls out of range, it returns `LONG_MAX` or `LONG_MIN` and sets `errno` to `ERANGE`.

**Question to sit with:** How would you use `endptr` to verify that a string contained *only* a number and nothing else? (Answer: check if `*endptr == '\0'` after the call).

```{=typst}
]
```

### 14.3.2 Random Numbers and Exiting

- `rand()` generates a pseudo-random integer. It must be seeded once at the start of your program with `srand()`, typically `srand(time(NULL))`. Note that `rand()` is predictably deterministic and cryptographically weak; never use it for security or cryptography.
- `exit(int status)` terminates the program immediately, correctly flushing open `FILE*` buffers before handing control back to the OS. Standard statuses are `EXIT_SUCCESS` (0) and `EXIT_FAILURE`.
- `atexit(void (*func)(void))` registers a function pointer to be called automatically when `exit()` runs, useful for hardware cleanup.
- `abs()` computes the absolute value of an integer (`div()` performs integer division returning quotient and remainder).

## 14.4 String and Memory Manipulation (`<string.h>`)

C strings are null-terminated arrays of characters. Functions in `<string.h>` do not allocate memory; they assume the destination arrays are already large enough.

![Categorical map of C headers](assets/s14_headers.png)

### 14.4.1 String Copying and Concatenation

- `strlen(const char *s)` returns the length of a string, *excluding* the null terminator. It operates in $O(N)$ time by scanning the array until it hits `\0`.
- `strcpy(char *dest, const char *src)` copies `src` to `dest`. It is inherently unsafe if `src` is larger than `dest`.
- `strcmp(const char *s1, const char *s2)` compares two strings, returning 0 if identical.
- `strcat(char *dest, const char *src)` concatenates `src` to the end of `dest`.
- `strchr(const char *s, int c)` and `strstr(const char *haystack, const char *needle)` search for characters and substrings respectively.

```{=typst}
#trap[
```

**The `strncpy()` trap:** `strncpy(dest, src, n)` is **not** a strictly safer version. If `src` is longer than `n`, `strncpy` will **not** append a null terminator to `dest`. It was originally designed to pack data into fixed-width database fields, not for general string safety. If you must copy strings safely, use `snprintf(dest, n, "%s", src)` or POSIX `strlcpy`.

```{=typst}
]
```

### 14.4.2 `memcpy` vs. `memmove`

```{=typst}
#heavy[
```

Dense — slow down: `memcpy` is fast but assumes memory regions are disjoint.

**Analogy:** `memcpy` is like hiring movers to take boxes from House A to House B. `memmove` is like sliding a large rug across a room while you are currently standing on one edge of it; the steps must be carefully sequenced so you don't pull the rug out from under your own feet.

**Example:**
```c
char buffer[10] = "abcdefghi";
// BAD: regions overlap.
// memcpy(buffer + 2, buffer, 5); 

// GOOD: memmove handles the overlap safely.
memmove(buffer + 2, buffer, 5); // Result: "ababcdehi"
```

**Plain English:** When copying raw blocks of memory (like arrays or structs), `memcpy` is the tool of choice. However, if the source and destination memory blocks overlap, `memcpy` causes undefined behavior (it might overwrite the source data before it finishes reading it). For overlapping regions, `memmove` is guaranteed to be safe, typically by calculating the overlap and copying backward if necessary.

**Technical:** `void *memcpy(void *restrict dest, const void *restrict src, size_t n);` The `restrict` keyword in the signature is a promise to the compiler that the pointers do not overlap, enabling aggressive optimization. `memmove` lacks the `restrict` keyword.

**Boundary:** This breaks down if `n` is greater than the allocated size of the buffers.

```{=typst}
]
```

- `memset(void *s, int c, size_t n)` fills a block of memory with the byte `c`. It is heavily used to zero-initialize a structure: `memset(&my_struct, 0, sizeof(my_struct))`.
- `memcmp(const void *s1, const void *s2, size_t n)` compares raw memory blocks, useful for equality testing if structs have no padding.

### 14.4.3 Statefulness in `strtok`

`strtok(char *str, const char *delim)` splits a string into tokens. It is notorious because it mutates the input string (replacing delimiters with `\0`) and maintains internal static state across calls to remember its position. Because of this hidden state, it is **not thread-safe** and cannot be used recursively.

## 14.5 Character Classification (`<ctype.h>`)

Provides macros and functions like `isalpha`, `isdigit`, `isspace`, `toupper`, and `tolower`.

```{=typst}
#trap[
```

**The `<ctype.h>` sign trap:** Notice the signature: `int isdigit(int c);`. It takes an `int`, not a `char`. Why? Because it must be able to accept `EOF` (End Of File, usually `-1`), which is returned by functions like `fgetc` when reading from a file. Passing a signed `char` with a negative value (other than `EOF`) results in undefined behavior. Always cast `char` variables to `unsigned char` when passing them into `<ctype.h>` functions [4].

```{=typst}
]
```

## 14.6 Mathematics (`<math.h>`)

Provides floating-point math: `sin`, `cos`, `sqrt`, `pow`, and `fabs` (absolute value for floats; `abs` in `<stdlib.h>` is strictly for integers). It defines standard macros like `NAN` (Not a Number) and `INFINITY`.

**Linking requirement:** On UNIX-like systems, math functions are historically housed in a separate compiled library (`libm`), not the default `libc`. You must instruct the compiler to link it by adding the `-lm` flag to your build command: `gcc program.c -lm`.

Caution: Remember from earlier sections that floating-point math is imprecise. Avoid strict equality `a == b`, preferring `fabs(a - b) < epsilon`.

## 14.7 Time (`<time.h>`)

Provides tools for manipulating time.
- `time_t time(time_t *arg)` returns the current system calendar time, typically represented as the number of seconds elapsed since the UNIX Epoch (Jan 1, 1970).
- `clock_t clock(void)` returns the processor time used by the program.
- `double difftime(time_t time1, time_t time0)` calculates the difference in seconds safely.
- `struct tm` is a structure holding "broken-down time" (distinct integer fields for year, month, day, hour, minute, second).
- `localtime()` converts a raw `time_t` timestamp into a readable `struct tm`.

## 14.8 Errors, Assertions, and Types

### 14.8.1 System Errors (`<errno.h>`)

When a standard library function fails (like `fopen` failing to find a file), it usually returns a sentinel value (`NULL` or `-1`). It also sets a global, thread-local integer named `errno` to a specific, standardized error code (like `ENOENT` for "No such file or directory"). You can print a human-readable description of this error using `perror()`, or retrieve the string manually with `strerror()` in `<string.h>`.

```c
FILE *f = fopen("missing.txt", "r");
if (f == NULL) {
    perror("Failed to open file"); 
    // Prints: "Failed to open file: No such file or directory"
}
```

### 14.8.2 Assertions (`<assert.h>`)

`assert(condition)` is a powerful debugging macro. If `condition` evaluates to false at runtime, the program prints the file name, line number, and the failing condition, then immediately aborts.

```{=typst}
#keypoint[
```

Assertions are for catching impossible situations caused by *programmer logic errors*, not expected run-time user errors (like a missing network connection). If you compile with the macro `NDEBUG` defined (e.g., `gcc -DNDEBUG`), all `assert` statements are completely removed from the compiled binary, meaning they cost zero CPU time in production [3].

```{=typst}
]
```

### 14.8.3 Type Definitions

- `<stdint.h>` provides exact-width integer types (`int32_t`, `uint8_t`).
- `<stdbool.h>` provides the `bool` type, and the macros `true` and `false`.
- `<stddef.h>` defines fundamental types like `size_t` (unsigned integer type for sizes) and `ptrdiff_t`.
- `<limits.h>` defines limits for integer types (`INT_MAX`, `CHAR_BIT`).

---

## 14.9 Worked Examples

### Worked Example: Safe File Reading

Reading a file line-by-line safely using `fgets`, avoiding the buffering bugs and overflow traps of `scanf` or `gets`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[256];
    // fgets reads up to sizeof(line)-1 characters or until a newline.
    // It returns NULL on EOF or read error.
    while (fgets(line, sizeof(line), file)) {
        // fgets leaves the '\n' in the buffer. We can cleanly strip it:
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        printf("Read successfully: %s\n", line);
    }

    fclose(file); // Always release OS resources
    return EXIT_SUCCESS;
}
```

### Worked Example: Robust Integer Parsing with `strtol`

Parsing a string where we must strictly validate that the input was an integer, handling trailing garbage and magnitude overflow. Contrast this robust handling with `atoi` which would fail silently on all of these edge cases.

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    const char *input = "  42949672950 extra text";
    char *endptr;
    
    // Reset errno to 0 before calling, as standard library functions 
    // do not reset it on success.
    errno = 0; 
    
    // Parse in Base 10
    long val = strtol(input, &endptr, 10);
    
    // 1. Check for overflow/underflow
    if (errno == ERANGE) {
        printf("Error: Number out of range for long int.\n");
    } 
    // 2. Check if no conversion could be performed at all
    else if (endptr == input) {
        printf("Error: No digits were found.\n");
    } 
    // 3. Success, but verify if trailing characters exist
    else {
        printf("Parsed value: %ld\n", val);
        if (*endptr != '\0') {
            printf("Notice: Trailing characters ignored: '%s'\n", endptr);
        }
    }
    
    return EXIT_SUCCESS;
}
```

### Faded Example: Safe Formatting

Fill in the missing size argument to ensure `snprintf` cannot overflow the fixed buffer, regardless of how long `player` is.

```c
#include <stdio.h>

int main(void) {
    char buffer[32];
    int score = 450;
    const char *player = "Alice";

    // Complete the call to safely format the string
    snprintf(buffer, _______, "Player %s scored %d", player, score);
    
    printf("%s\n", buffer);
    return 0;
}
```

---

## 14.10 References

- [1] ISO/IEC 9899:2011 — C11 Standard (Draft N1570) — *§7. Library* — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
- [2] cppreference.com — *C numeric input/output* — https://en.cppreference.com/w/c/io
- [3] Linux man pages (man7.org) — *assert(3)* — https://man7.org/linux/man-pages/man3/assert.3.html
- [4] cppreference.com — *Null-terminated byte strings* — https://en.cppreference.com/w/c/string/byte
