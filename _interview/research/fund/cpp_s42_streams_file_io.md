# Streams and File I/O

In C++, input and output are not built directly into the language syntax. Instead, I/O is handled by a standard library abstraction known as the **stream model**. A stream is a sequence of characters flowing into or out of a program, decoupling the I/O logic from the specific device (console, file, or string buffer).

## The stream class hierarchy

The C++ I/O stream library is built on a complex inheritance hierarchy. You rarely instantiate the base classes directly, but understanding the hierarchy explains why file streams and string streams can be used anywhere a standard stream is expected.

![The iostream class hierarchy, from `ios_base` down to the file- and string-stream types.](assets/s42_stream_hierarchy.png)

1. `std::ios_base`: The root base class. It manages formatting flags and the stream state, independent of the character type.
2. `std::ios`: A template class (instantiated as `std::basic_ios<char>`) that derives from `ios_base`. It manages the pointer to the underlying stream buffer (`std::streambuf`).
3. `std::istream` and `std::ostream`: Derive from `ios` (via virtual inheritance). They provide the high-level formatted and unformatted input and output functions.
4. **Concrete streams**: Classes like `std::ifstream` (file input) and `std::istringstream` (string input) inherit from `std::istream`. Because of polymorphism, any function accepting an `std::istream&` can seamlessly accept a file or string stream.

## The standard streams

The `<iostream>` header declares four global stream objects that are automatically opened when a C++ program starts:

- **`std::cin`**: Tied to the standard input (usually the keyboard). It is an instance of `std::istream`.
- **`std::cout`**: Tied to the standard output (usually the console screen). It is an instance of `std::ostream`.
- **`std::cerr`**: Tied to the standard error stream. Crucially, it is **unbuffered**, meaning output appears immediately, bypassing any queuing. This makes it ideal for crash diagnostics.
- **`std::clog`**: Also tied to the standard error stream, but it is buffered, making it more efficient for writing large volumes of general log messages.

## Formatted versus unformatted I/O

C++ provides two distinct ways to interact with streams: formatted and unformatted.

### Formatted I/O

Formatted I/O uses the overloaded extraction (`>>`) and insertion (`<<`) operators. They are "formatted" because they automatically convert between text characters and binary types (like `int` or `float`). When extracting, they automatically skip leading whitespace (spaces, tabs, newlines).

```cpp
#include <iostream>
#include <string>

int main() {
    int age;
    std::string name;
    
    // Formatted extraction: skips whitespace, stops at the next whitespace
    std::cin >> name >> age;
    
    // Formatted insertion: converts integers to characters
    std::cout << "Name: " << name << ", Age: " << age << "\n";
}
```

### Unformatted I/O

Unformatted I/O treats the stream as raw characters. It does not skip whitespace and does not convert types. The stream classes provide several member functions for this:

```cpp
// Common unformatted input members of std::istream:
int get();                                              // Returns one char or EOF
std::istream& get(char& c);                             // Reads one char into 'c'
std::istream& read(char* s, std::streamsize n);         // Reads a block of 'n' bytes
std::istream& ignore(std::streamsize n, int delim);     // Discards up to 'n' chars or until 'delim'

// Note: std::getline is typically used as a free function from <string>
std::istream& getline(std::istream& is, std::string& str, char delim = '\n');

// Common unformatted output members of std::ostream:
std::ostream& put(char c);                              // Writes one char
std::ostream& write(const char* s, std::streamsize n);  // Writes a block of 'n' bytes
```

Example usage:
```cpp
#include <iostream>
#include <string>

int main() {
    char c = std::cin.get(); // Reads exactly one char, even if it is a space or newline
    std::cout.put(c);
    
    std::string line;
    // Reads an entire line, including spaces, up to the newline character
    std::getline(std::cin, line); 
}
```

### The `>>` then `getline` trap

Mixing formatted extraction and unformatted line reading is a notorious source of bugs in C++.

::: trap
When `std::cin >> x` reads a value, it leaves the trailing newline character (`\n`) in the input buffer. If you immediately call `std::getline()`, it sees that left-over newline instantly, reads an empty string, and stops, skipping your intended input.
:::

```cpp
int age;
std::string name;

std::cin >> age;                  // User types "25\n". Reads 25, leaves '\n' in buffer.
std::getline(std::cin, name);     // Instantly hits '\n', reads "", and continues.
```

To fix this, you must discard the leftover newline using `std::cin.ignore()`.

```cpp
#include <iostream>
#include <string>
#include <limits>

int main() {
    int age;
    std::string name;
    
    std::cin >> age;
    // Discard characters until a newline is found and discarded
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::getline(std::cin, name); // Now correctly waits for the next line
}
```

## Manipulators

Manipulators are objects or functions that modify the behaviour or formatting of a stream when inserted or extracted. 

### `std::endl` versus `\n`

Both output a newline, but `std::endl` performs an additional operation: it flushes the output buffer, forcing any pending characters to be written to the destination immediately.

::: trap
Using `std::endl` inside a large loop is incredibly slow because flushing the buffer to the OS is a heavy system call. Always prefer `\n` for newlines unless you explicitly need to ensure the output is immediately visible.
:::

::: interview
A common interview question is "What is the difference between `std::endl` and `\n`?". The correct answer is that `std::endl` outputs a newline *and* flushes the stream buffer, whereas `\n` only outputs a newline.
:::

### Formatting with `<iomanip>`

The `<iomanip>` header provides manipulators to format output dynamically.

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.14159265;
    int num = 255;
    bool isTrue = true;

    // Output: 3.14 (fixed point, 2 decimal places)
    std::cout << std::fixed << std::setprecision(2) << pi << "\n";
    
    // Output: 3.141593e+00 (scientific notation)
    std::cout << std::scientific << pi << "\n";
    
    // std::setw sets a field width. std::setfill sets the padding character.
    // Output: ***42
    std::cout << std::setfill('*') << std::setw(5) << 42 << "\n";
    
    // Output: ff (hexadecimal, use std::uppercase for FF)
    std::cout << std::hex << num << "\n";
    
    // Other bases: std::dec (decimal), std::oct (octal)
    std::cout << std::dec << num << "\n"; 
    
    // Output: +42 (shows the positive sign explicitly)
    std::cout << std::showpos << 42 << "\n";
    
    // Output: true (prints 'true'/'false' instead of 1/0)
    std::cout << std::boolalpha << isTrue << "\n";
}
```

## File streams

The `<fstream>` header provides classes for file I/O:
- `std::ifstream`: Input file stream (read).
- `std::ofstream`: Output file stream (write).
- `std::fstream`: Bidirectional file stream (read and write).

### Open modes

File stream constructors and the `.open()` method take an optional bitmask of type `std::ios_base::openmode`:

```cpp
explicit ifstream(const char* filename, ios_base::openmode mode = ios_base::in);
explicit ofstream(const char* filename, ios_base::openmode mode = ios_base::out);
explicit fstream(const char* filename, ios_base::openmode mode = ios_base::in | ios_base::out);
```

The available modes (scoped under `std::ios` or `std::ios_base`) can be combined using the bitwise OR operator `|`:
- `ios::in`: Open for reading.
- `ios::out`: Open for writing.
- `ios::app`: Append mode; all output is added to the end of the file.
- `ios::trunc`: Truncate mode; discards the file's existing contents (default if `ios::out` is used alone).
- `ios::binary`: Open in binary mode (prevents newline translation).
- `ios::ate`: (At end) Opens the file and immediately seeks to the end.

### Managing file lifecycle

Files should be opened by passing the filename to the constructor. The file is automatically closed when the stream object goes out of scope and its destructor is called (an application of RAII). 

You can check if opening succeeded using `.is_open()`, the overloaded `operator bool()`, or `.fail()`.

```cpp
#include <fstream>
#include <iostream>
#include <string>

int main() {
    // 1. Open the file via constructor
    std::ifstream fin("data.txt");
    
    // 2. Check for success 
    if (!fin.is_open()) { // Alternatively: if (!fin) or if (fin.fail())
        std::cerr << "Failed to open file.\n";
        return 1;
    }
    
    // 3. Read data...
    
    // 4. No manual close() needed. 'fin' going out of scope closes the file safely.
    return 0;
}
```

::: keypoint
In Python, you use the `with open("file.txt") as f:` context manager to ensure a file is automatically closed. In C++, this same safety is achieved implicitly through RAII — the file stream's destructor closes the file handle as soon as the stream variable leaves scope. Prefer this over calling `.close()` manually.
:::

### Reading line by line and word by word

To read a file word by word, use the formatted extraction operator in a `while` loop, which evaluates to false when it hits the end of the file. To read line by line, use `std::getline()`.

```cpp
#include <fstream>
#include <iostream>
#include <string>

void readLineByLine() {
    std::ifstream fin("data.txt");
    std::string line;
    
    // std::getline evaluates to true as long as a line was successfully read
    while (std::getline(fin, line)) {
        std::cout << line << "\n";
    }
}

void readWordByWord() {
    std::ifstream fin("data.txt");
    std::string word;
    
    // Extracts space-separated tokens
    while (fin >> word) {
        std::cout << word << "\n";
    }
}
```

## Text versus binary mode

By default, file streams open in **text mode**. In text mode, the operating system translates line endings (e.g., converting `\r\n` on Windows to a single `\n` in memory, and back again upon writing).

For structured data (like images or raw memory dumps), this translation corrupts the data. You must open the file in **binary mode** by passing `std::ios::binary`. 

Binary I/O bypasses the formatting operators `<<` and `>>`. Instead, you use the unformatted `.write()` and `.read()` methods, passing a raw `char*` buffer and the number of bytes to transfer.

```cpp
#include <fstream>
#include <iostream>

struct Record {
    int id;
    double value;
};

int main() {
    Record outRec{42, 3.14};
    
    // Writing raw binary data
    std::ofstream fout("record.bin", std::ios::out | std::ios::binary);
    // reinterpret_cast is required to cast the pointer to a char buffer
    fout.write(reinterpret_cast<const char*>(&outRec), sizeof(Record));
    fout.close();
    
    // Reading raw binary data
    Record inRec;
    std::ifstream fin("record.bin", std::ios::in | std::ios::binary);
    fin.read(reinterpret_cast<char*>(&inRec), sizeof(Record));
    
    std::cout << "Read ID: " << inRec.id << "\n";
}
```

*(Note: Directly writing structs to disk is a form of crude serialisation that works for simple data, but breaks if the struct contains pointers, strings, or is moved between systems with different endianness or padding rules.)*

::: interview
Be prepared to explain the difference between text and binary file modes. Text mode performs OS-specific newline translation behind the scenes; binary mode reads and writes the exact bytes untouched. Use `read()` and `write()` for binary data.
:::

## String streams

The `<sstream>` header provides streams that read from and write to `std::string` objects in memory:
- `std::istringstream`: Reads from a string (useful for parsing).
- `std::ostringstream`: Writes to a string (useful for formatting).

### Common uses

String streams are the classic C++ mechanism for converting between numbers and strings, and for tokenising a line of text.

```cpp
#include <sstream>
#include <string>
#include <iostream>

int main() {
    // 1. Building a string (number to string conversion)
    std::ostringstream oss;
    oss << "Error code " << 404 << ": Not Found";
    std::string result = oss.str(); // Extracts the built string
    
    // 2. Parsing a string (string to number conversion)
    std::string data = "100 200 300";
    std::istringstream iss(data);
    
    int x, y, z;
    iss >> x >> y >> z; // x=100, y=200, z=300
    
    // 3. Tokenising a CSV line using getline with a custom delimiter
    std::string csv = "apple,banana,cherry";
    std::istringstream csvStream(csv);
    std::string token;
    
    while (std::getline(csvStream, token, ',')) {
        std::cout << "Token: " << token << "\n";
    }
}
```

::: interview
If asked how to parse a complex string or tokenise input, `std::istringstream` is the standard library answer. It provides the full power of formatted extraction (`>>`) against a string in memory.
:::

::: heavy
The final topic covers the stream state flags, which dictate how a stream reacts to errors. This requires understanding how to manually query and reset a stream's internal state.
:::

## Stream state flags

::: definition
A stream maintains an internal bitmask of **state flags** that record its health. If a stream encounters an error, it enters a failed state and will silently ignore all further I/O attempts until explicitly cleared.
:::

Every stream has four state query functions and a reset function:

```cpp
bool good() const; // Returns true if no error flags are set
bool eof() const;  // Returns true if the End-Of-File has been reached
bool fail() const; // Returns true if a logical error occurred (e.g., type mismatch)
bool bad() const;  // Returns true if a severe physical error occurred (e.g., disk failure)

// Resets the state flags to the specified state (default is goodbit)
void clear(std::ios_base::iostate state = std::ios_base::goodbit);
```

### The ADEPT breakdown of stream failures

**Analogy**: A railway signal system. If a train derails, the system raises a red flag. Until an engineer explicitly goes to the switchbox, acknowledges the crash, and resets the flag to green, no other trains are allowed onto that track.

![A failed extraction sets `failbit`; the stream stays unusable until `clear()` resets its state.](assets/s42_stream_state.png)

**Example**: You ask `std::cin` for an integer, but the user types `"abc"`.

```cpp
#include <iostream>
#include <limits>

int main() {
    int x = 0;
    std::cout << "Enter a number: ";
    
    std::cin >> x; // User types "abc"
    
    if (std::cin.fail()) {
        std::cout << "That was not a number!\n";
        
        // 1. Reset the error flags back to 'good' so the stream works again
        std::cin.clear();
        
        // 2. Discard the offending input still sitting in the buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
}
```

**Plain-English rule**: When an extraction fails because the data is the wrong type, the stream gives up, leaves the bad data in the buffer, and raises its `fail` flag. You must call `.clear()` to lower the flag, and then `.ignore()` to throw away the bad data.

**Technical statement**: Failed formatted extraction sets the `std::ios_base::failbit`. Once this bit is set, `operator bool()` evaluates to `false`, and all subsequent calls to `operator>>` or `operator<<` return immediately without performing any I/O. The `clear()` member function resets the `iostate` bitmask to `std::ios_base::goodbit`.
