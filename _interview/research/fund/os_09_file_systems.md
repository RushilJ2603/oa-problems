# File systems

## Files, attributes, and operations

> **Definition — File.** A named collection of related information stored on secondary storage. It
> is the operating system's abstraction over the raw blocks of a disk: a user works with files and
> folders, and the file system maps those onto disk blocks and sectors.

A file carries **attributes** kept in its directory entry / control block: name, an
**extension/type**, a unique **identifier**, its **location** on the device, **size**,
**timestamps** (created/modified), **protection/permissions**, and possibly encryption or
compression flags.

The OS provides **operations** on files as system calls: **create, read, write, delete, truncate,
open/close,** and **reposition** (seek). Files are organized into a **directory** structure (a
tree of folders), which is itself a special file mapping names to file control blocks.

## File allocation methods

The core design question is *how a file's data blocks are laid out on disk*. There are three
schemes.

### Contiguous allocation

Each file occupies a set of **consecutive** blocks; the directory records the start block and
length.

- **Advantages:** simple; **excellent read performance** — sequential reads need no seeks, and
  random access to block *i* is a direct computation (`start + i`).
- **Disadvantages:** **external fragmentation** (free space fragments into gaps); and a file is
  **hard to grow** — if the following blocks are taken, the file must be moved.

### Linked allocation

Each block stores a pointer to the **next** block of the file; the directory holds only the first
block. The blocks can be scattered anywhere.

- **Advantages:** **no external fragmentation**; a file can **grow** easily by linking another
  block.
- **Disadvantages:** effectively **sequential access only** — reaching block *i* means following
  *i* pointers, so random access is slow; the pointers consume space; and a single corrupted
  pointer can lose the rest of the file.

### Indexed allocation

Each file has an **index block** holding the addresses of all its data blocks; the directory points
to the index block.

- **Advantages:** supports **direct (random) access** (index the block table) and has **no external
  fragmentation**.
- **Disadvantages:** the index block is overhead (wasteful for tiny files), and a file larger than
  one index block can hold needs a **multilevel index**.

## The Unix inode

Unix generalizes indexed allocation into a **multilevel index** that is efficient for both small and
huge files. Each file is described by an **inode** containing its attributes plus a set of block
pointers:

- several **direct** pointers (each to a data block) — enough for small files with no indirection;
- one **single-indirect** pointer (to a block of pointers to data blocks);
- one **double-indirect** pointer (to a block of pointers to single-indirect blocks);
- one **triple-indirect** pointer (one more level).

Small files use only the direct pointers, so their access is fast; large files reach further out
through the indirect blocks. The number of pointers a block can hold is
$\dfrac{\text{block size}}{\text{address size}}$.

**Worked example.** An inode has **8 direct** block addresses, one single-, one double-, and one
triple-indirect block. Each **disk block is 128 B** and each **block address is 8 B**.

Pointers per block:
$$\frac{128\text{ B}}{8\text{ B}} = \frac{2^{7}}{2^{3}} = 2^{4} = 16.$$

Maximum number of data blocks a file can address:
$$\underbrace{8}_{\text{direct}} + \underbrace{16}_{\text{single}} + \underbrace{16^2}_{\text{double}} + \underbrace{16^3}_{\text{triple}} = 8 + 16 + 256 + 4096 = 4376 \text{ blocks}.$$

Maximum file size:
$$4376 \times 128\text{ B} = 560{,}128\text{ B} = \mathbf{547\text{ KB}}.$$

> **Key point.** The triple-indirect level dominates the capacity ($16^3 = 4096$ of the $4376$
> blocks), yet a small file that fits in the 8 direct blocks pays no indirection cost at all. This
> asymmetry — cheap small files, still-reachable huge files — is why the inode design endures.

## Free-space management

The file system also tracks which blocks are free, typically with a **bit vector** (one bit per
block, set if free — fast to scan for a run of free blocks) or a **linked list** of free blocks.
**Journaling** file systems additionally record intended changes in a log before applying them, so
that an interrupted operation (a crash mid-write) can be replayed or rolled back, keeping the file
system consistent.

---
