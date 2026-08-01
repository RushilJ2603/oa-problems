# Virtual memory

## Demand paging

> **Definition — Virtual memory.** A technique that lets a process execute even when it is not
> entirely in physical memory, by keeping only the actively used pages in RAM and the rest on a disk
> **backing store (swap)**. It gives each process the illusion of a large, contiguous address space
> larger than physical memory.

Virtual memory is realized by **demand paging**: a page is brought into a frame only when it is
first referenced, never in advance. Each page-table entry carries a **valid/invalid** bit — valid
means the page is in a frame, invalid means it is on disk (or illegal).

**The page-fault sequence.** When the CPU references a page whose entry is invalid, the hardware
raises a **page fault** (a trap), and the OS:

1. checks that the reference is legal;
2. finds a free frame (or frees one via page replacement);
3. schedules a disk read to bring the page into the frame;
4. updates the page table (entry now valid);
5. restarts the instruction that faulted.

> **Key point.** A page fault is a normal, expected event, not an error — it is the very mechanism
> that makes demand paging work. But because it involves a disk access, it is enormously slower than
> a memory reference, so the *rate* of page faults dominates performance.

### Effective memory access time

If the page-fault rate is $p$ (with $0 \le p \le 1$), memory access time is $m$, and servicing a
fault costs $s$ (dominated by disk I/O), the **effective memory access time** is:

$$\text{EMAT} = (1-p)\cdot m + p\cdot s.$$

Because $s$ (milliseconds) is roughly a hundred thousand times $m$ (nanoseconds), even a tiny fault
rate inflates EMAT sharply — which is why keeping $p$ near zero, through good replacement and enough
frames, is critical.

## The translation lookaside buffer

Every logical reference needs a page-table lookup, and the page table itself lives in memory — so a
naive design costs **two** memory accesses per reference (one for the table, one for the data). A
**translation lookaside buffer (TLB)** is a small, fast associative cache of recent page→frame
translations that removes most of that cost.

On a reference, the MMU checks the TLB first. A **TLB hit** yields the frame immediately; a **TLB
miss** falls back to the page table (and loads the translation into the TLB). With TLB access time
$c$, memory access time $m$, and TLB hit ratio $h$:

$$\text{EMAT} = h\,(c + m) + (1-h)\,(c + 2m).$$

**Worked example.** TLB access $c = 10$ ns, memory access $m = 50$ ns, hit ratio $h = 0.8$:

$$\text{EMAT} = 0.8\,(10 + 50) + 0.2\,(10 + 50 + 50) = 0.8(60) + 0.2(110) = 48 + 22 = 70 \text{ ns}.$$

The 80 % of references that hit the TLB cost one memory access; the 20 % that miss pay for the extra
page-table access.

## Page replacement

When a page must be brought in but no frame is free, the OS chooses a **victim** page to evict
(writing it back first only if its **dirty** bit is set). The choice of victim is made by a **page
replacement algorithm**. All examples below use the reference string

$$7,\ 0,\ 1,\ 2,\ 0,\ 3,\ 0,\ 4,\ 2,\ 3,\ 0,\ 3,\ 1,\ 2,\ 0 \qquad (15 \text{ references})$$

with **three frames**.

### FIFO and Belady's anomaly

**FIFO** evicts the page that has been in memory longest (a simple queue). Tracing the string:

| Ref | 7 | 0 | 1 | 2 | 0 | 3 | 0 | 4 | 2 | 3 | 0 | 3 | 1 | 2 | 0 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| f1 | 7 | 7 | 7 | 2 | 2 | 2 | 2 | 4 | 4 | 4 | 0 | 0 | 0 | 0 | 0 |
| f2 |   | 0 | 0 | 0 | 0 | 3 | 3 | 3 | 2 | 2 | 2 | 2 | 1 | 1 | 1 |
| f3 |   |   | 1 | 1 | 1 | 1 | 0 | 0 | 0 | 3 | 3 | 3 | 3 | 2 | 2 |
| | ✗ | ✗ | ✗ | ✗ | ✓ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✓ | ✗ | ✗ | ✓ |

This gives **12 page faults and 3 hits**, a hit ratio of $3/15 = 20\%$.

> **Trap — Belady's anomaly.** Intuition says more frames should mean fewer faults. Under **FIFO**
> that can fail. For the string $1,2,3,4,1,2,5,1,2,3,4,5$, FIFO incurs **9 faults with 3 frames but
> 10 faults with 4 frames** — adding a frame made it *worse*. This is **Belady's anomaly**, and it
> can only occur in algorithms (like FIFO) that are not "stack algorithms"; LRU and Optimal never
> exhibit it.

### Optimal

**Optimal (OPT/MIN)** evicts the page that will not be used for the longest time in the **future**.
On the reference string it achieves the fewest possible faults — **8 faults, 7 hits** ($7/15$). It
is unrealizable in practice (it needs to see the future), but it is the yardstick every real
algorithm is measured against.

### Least recently used

**LRU** approximates Optimal by looking at the **past**: evict the page unused for the longest time,
on the assumption that the recent past predicts the near future. On the reference string LRU gives
**12 faults, 3 hits** — matching FIFO here, but in general better and, crucially, **free of Belady's
anomaly**. Exact LRU needs per-access timestamps or a stack; hardware approximates it cheaply with
the **reference bit** (the "second-chance"/clock algorithm).

### Most recently used

**MRU** does the opposite — evict the *most* recently used page. It is rarely a good general policy;
on the reference string it is the worst of the four, **13 faults, 2 hits**. It helps only for
specific access patterns (e.g. a large file scanned once, where the most-recently-used page is the
least likely to be needed again).

| Algorithm | Rule | Faults (3 frames) | Hits |
|---|---|---|---|
| Optimal | Evict furthest-future use | **8** | 7 |
| FIFO | Evict oldest-loaded | 12 | 3 |
| LRU | Evict least-recently-used | 12 | 3 |
| MRU | Evict most-recently-used | 13 | 2 |

## Thrashing

If the degree of multiprogramming is pushed too high, each process gets too few frames to hold its
active pages, so almost every reference faults. The system then spends nearly all its time paging in
and out rather than executing.

> **Definition — Thrashing.** A condition in which a process (or the whole system) spends more time
> servicing page faults than doing useful work. As the degree of multiprogramming rises, CPU
> utilization climbs, peaks, and then **collapses sharply** once thrashing sets in.

The remedy is the **working-set model**: track the set of pages a process has referenced in a recent
window (its *working set*) and give it enough frames to hold that set; admit new processes only when
their working sets fit. If demand exceeds available frames, **reduce** the degree of multiprogramming
(swap a process out) rather than adding more.

## Related mechanisms

- **Copy-on-write** (introduced with `fork`) is a virtual-memory optimization: parent and child
  share physical frames marked read-only until one writes, at which point that single page is copied.
- **Memory-mapped files (`mmap`)** map a file's contents into a process's address space, so file
  access becomes ordinary memory access, paged in on demand and shared between processes.
- **Page cache** — the OS keeps recently used disk pages in otherwise-free RAM, so "free" memory is
  effectively used as a disk cache; dirty cached pages are written back lazily.

---
