# File Handling

> **Prerequisites Block:**
> * **Assumed Knowledge:** Strings, loops.

File handling allows Python programs to read from and write to external files on the disk, making data persistence possible.

## Opening and Closing Files

The built-in `open()` function is used to access files. It returns a file object.

```python
f = open('sample.txt', 'w')
f.write('Hello world')
f.close()
```

> **First-use gloss:** `close()` flushes the in-memory buffers and releases the file back to the operating system. Attempting to write to or read from a closed file raises a `ValueError: I/O operation on closed file.`

## File Modes

The `mode` argument tells Python what you intend to do with the file.

| Character | Meaning |
| :---: | :--- |
| `'r'` | **Read** (default). Opens for reading. Errors if file doesn't exist. |
| `'w'` | **Write**. Opens for writing, **truncating** (overwriting) the file first. |
| `'x'` | **Exclusive creation**. Fails if the file already exists. |
| `'a'` | **Append**. Opens for writing, appending to the end of the file if it exists. |
| `'b'` | **Binary mode**. For reading/writing raw bytes (e.g., images). |
| `'t'` | **Text mode** (default). |

### Overwriting vs. Appending
When using `'w'` mode, if the file already exists, its entire contents are erased before writing the new data.
To add new data without erasing existing content, use append mode `'a'`:

```python
f = open('sample.txt', 'a')
f.write('\nI am fine')
f.close()
```

## Reading from Files

### `read()`
`read()` reads the entire content of the file into a single string.

```python
f = open('sample.txt', 'r')
s = f.read()
print(s)
f.close()
```

To read only a specific number of characters, pass the byte/character count as an argument. Subsequent calls pick up where the previous one left off:

```python
f = open('sample.txt', 'r')
s = f.read(10)  # reads the first 10 characters
print(s)
f.close()
```

### `readline()`
`readline()` reads the file line by line. Each call returns the next line.

```python
f = open('sample.txt', 'r')
print(f.readline())
print(f.readline())
f.close()
```

To read an entire file efficiently line by line:

```python
f = open('sample.txt', 'r')
while True:
    data = f.readline()
    if data == '':
        break
    else:
        print(data, end='')
f.close()
```

### `writelines()`
To write a list of strings directly into a file, use `writelines()`:

```python
L = ['hello\n', 'hi\n', 'how are you\n', 'I am fine\n']
f = open('sample.txt', 'w')
f.writelines(L)
f.close()
```

## The Context Manager (`with` block)

> **Heavy:** Managing file closure manually is error-prone.

If a program crashes before reaching `f.close()`, the file might remain open, leading to resource leaks or corrupted data.

The modern, Pythonic way to handle files is using the `with` keyword, which acts as a **Context Manager**.

```python
with open('sample.txt', 'w') as f:
    f.write('hello')
```

**How it works:** As soon as the indented block finishes (either normally or due to an error), the context manager automatically and safely closes the file. There is no need to write `f.close()`.

## Reading Large Files in Chunks

When dealing with massive files (e.g., gigabytes in size), using `read()` will attempt to load the entire file into memory (RAM), which can crash the system. 

Instead, read the file in manageable chunks using a loop:

```python
with open('big.txt', 'r') as f:
    chunk_size = 100
    chunk = f.read(chunk_size)
    
    while len(chunk) > 0:
        print(chunk)
        chunk = f.read(chunk_size)
```
This guarantees that only `100` characters are kept in memory at any given time, regardless of how large the file is.
