# Memory management

## The goal and the memory hierarchy

**Memory management** is how the operating system manages primary (main) memory so that many
processes can reside in it at once. The CPU reads instructions and data only from registers and,
below them, from cache and main memory; the disk (secondary memory) is far slower. The aim is
**efficient utilization of main memory** — keeping the CPU busy by holding enough processes in RAM.

> **Definition — Degree of multiprogramming.** The number of processes held in main memory at once.
> Raising it improves CPU utilization (there is more likely to be a ready process when one blocks),
> up to the point where memory pressure causes thrashing (covered under virtual memory).

The techniques divide into two families:

- **Contiguous allocation** — each process occupies one continuous block of memory. Either **fixed
  (static) partitioning** or **variable (dynamic) partitioning**.
- **Non-contiguous allocation** — a process is scattered across memory in pieces: **paging**,
  **multilevel/inverted paging**, **segmentation**, and **segmented paging**.

## Fixed (static) partitioning

Main memory is divided in advance into a **fixed number of partitions of fixed size**; each holds at
most one process, and a process must fit entirely within a single partition.

> **Trap — Cisco-style multi-select.** All of the following are true of fixed partitioning: the
> number of partitions is fixed; each partition's size is fixed at configuration time; a process
> occupies exactly one partition and cannot span partitions; and it suffers **both** internal
> **and** external fragmentation. The "both fragmentations" fact is the option people wrongly
> deselect.

Its four limitations:

1. **Internal fragmentation** — a process smaller than its partition wastes the leftover space
   *inside* it (a 6 MB process in an 8 MB partition wastes 2 MB).
2. **Limit on process size** — a process larger than the biggest partition cannot run at all.
3. **Limit on the degree of multiprogramming** — at most one process per partition, so the number
   of partitions caps how many processes can be resident.
4. **External fragmentation** — a free partition may be unusable because no waiting process is small
   enough for it, so free memory exists but cannot be used.

## Variable (dynamic) partitioning

Here partitions are created **to fit each process exactly**, at load time. This removes internal
fragmentation and the fixed limits on process size and process count. But as processes come and go,
memory becomes pocked with **holes** — **external fragmentation**: the total free memory may be
large, yet split into pieces none of which is big enough for the next process.

Two remedies:

- **Compaction** — periodically slide the allocated blocks together to merge the holes into one big
  free region. It works but is expensive (it must pause and relocate processes).
- **Non-contiguous allocation** (paging) — the more powerful fix, which sidesteps external
  fragmentation entirely.

### Placement algorithms

When several holes can fit a process, which do you pick?

| Algorithm | Rule | Trade-off |
|---|---|---|
| **First fit** | The first hole large enough | Fast; good general choice |
| **Next fit** | Like first fit, but resume searching from the last placement | Spreads usage; can be worse than first fit |
| **Best fit** | The smallest hole that fits | Wastes least *now*, but leaves many tiny useless holes; slow (scans all) |
| **Worst fit** | The largest hole | Leaves a usable remainder, but consumes big holes; slow |

## Paging

Paging removes external fragmentation by decoupling a process's logical layout from its physical
placement.

### Pages, frames, and the page table

Physical memory is divided into fixed-size **frames**; logical memory into **pages** of the *same
size*. A process's pages are loaded into any free frames, not necessarily contiguous. A per-process
**page table** maps each page number to the frame that holds it. The hardware **memory-management
unit (MMU)** performs this translation on every access.

> **Key point.** Because page size equals frame size, there is **no external fragmentation** (any
> free frame fits any page). Only the last page of a process may be partly empty — a bounded
> **internal fragmentation** of at most one page per process.

### Address translation

A logical address splits into a **page number** and a **page offset**; the page number indexes the
page table to get a **frame number**, which is concatenated with the (unchanged) offset to form the
physical address.

$$\text{logical address} = (\text{page number} \mid \text{offset}) \xrightarrow{\text{page table}}
(\text{frame number} \mid \text{offset}) = \text{physical address}$$

**Worked example** (memory byte-addressable):

- Logical address space $= 4\text{ GB} = 2^{32}$ B, so a **logical address is 32 bits**.
- Physical address space $= 64\text{ MB} = 2^{26}$ B, so a **physical address is 26 bits**.
- Page size $=$ frame size $= 4\text{ KB} = 2^{12}$ B, so the **offset is 12 bits**.

From these:

| Quantity | Computation | Result |
|---|---|---|
| Number of pages | $2^{32} / 2^{12}$ | $2^{20}$ |
| Number of frames | $2^{26} / 2^{12}$ | $2^{14}$ |
| Page-number bits / frame-number bits | $32-12$ / $26-12$ | 20 / 14 |
| Number of page-table entries | one per page | $2^{20}$ |
| Size of the page table | entries $\times$ frame-number bits $= 2^{20} \times 14$ bits | $\approx$ 2.5 MB |

> **Trap.** A page-table entry stores the **frame number** (14 bits here), not the full physical
> address — the offset is not stored. Multiply the number of entries by the frame-number width, not
> by the page size.

### Page-table entry format

Each entry holds the frame number plus control bits:

- **Valid/invalid (present/absent)** — whether the page is currently in a frame.
- **Protection** — read/write/execute permissions.
- **Reference** — set when the page is accessed (used by replacement algorithms).
- **Dirty (modified)** — set when the page is written, so a clean page need not be written back.
- **Caching** — whether the page may be cached.

### Multilevel paging

A single page table can itself be huge ($2^{20}$ entries above). **Multilevel (hierarchical)
paging** pages the page table: an **outer page table** points to **pages of the inner page table**,
which point to frames. Only the portions of the table actually needed are kept in memory, so the
table no longer has to be one large contiguous block. The logical address gains an index per level.

### Inverted page table

A normal page table has one entry per *page*, per process — costly when there are many large address
spaces. An **inverted page table** has one entry per *frame* of physical memory (one table for the
whole system), each recording which `<process id, page number>` currently occupies that frame. This
shrinks the table dramatically but makes lookup slower — the entry must be *searched* for rather than
indexed — so a hash table (and the TLB) is used to speed it up.

## Segmentation

Paging is invisible to the programmer and ignores a program's logical structure. **Segmentation**
instead divides a process into **variable-size, logically meaningful segments** — code, stack, heap,
a data array — each identified by a segment number. A **segment table** stores, per segment, a
**base address** and a **limit** (length).

Translation of a logical address `(segment number, offset)`: look up the segment's base and limit;
if `offset < limit`, the physical address is `base + offset`; otherwise the access is illegal and
the hardware raises a **trap** (segmentation fault).

> **Key point — paging vs segmentation.** Paging uses fixed-size pages, is invisible to the
> programmer, and suffers only minor internal fragmentation; segmentation uses variable-size
> logical segments, is visible and matches program structure, but suffers **external**
> fragmentation. **Segmented paging** combines them — segments divided into pages — to get logical
> structure without external fragmentation.

---
