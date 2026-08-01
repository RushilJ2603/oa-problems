# I/O systems and disk scheduling

## Disk architecture

A magnetic hard disk is a stack of **platters**, each with two **surfaces**. Each surface holds
concentric **tracks**, and each track is divided into **sectors** (the smallest addressable unit).
The set of tracks at the same radius across all platters is a **cylinder**. A read/write head per
surface, mounted on a moving **arm**, accesses the data. Total capacity is

$$\text{surfaces} \times \text{tracks/surface} \times \text{sectors/track} \times \text{bytes/sector}.$$

## Disk access time

Servicing an I/O request costs three components:

- **Seek time** — time for the arm to move the head to the target track. Usually the dominant,
  most-variable cost, and the one disk scheduling optimizes.
- **Rotational latency** — time for the target sector to rotate under the head. On average this is
  **half a rotation** ($\tfrac{1}{2} \times \tfrac{60}{\text{RPM}}$).
- **Transfer time** — time to actually read/write the data $= \dfrac{\text{data size}}{\text{transfer
  rate}}$.

$$\text{Disk access time} = \text{seek time} + \text{rotational latency} + \text{transfer time}.$$

## Disk scheduling algorithms

Because seek time dominates, the OS reorders pending track requests to minimize total head
movement. All examples below use the same request queue and starting position:

> Track requests: **82, 170, 43, 140, 24, 16, 190**; the head starts at track **50**; the disk has
> 200 tracks (0–199).

| Algorithm | Rule | Service order (from 50) | Total head movement |
|---|---|---|---|
| **FCFS** | Serve in arrival order | 82,170,43,140,24,16,190 | **642** |
| **SSTF** | Shortest seek time first (nearest request) | 43,24,16,82,140,170,190 | **208** |
| **SCAN** (elevator) | Sweep to one end, then reverse | 82,140,170,190,→199,43,24,16 | **332** |
| **LOOK** | Like SCAN but reverse at the last *request* | 82,140,170,190,43,24,16 | **314** |
| **C-SCAN** | Sweep up to the end, jump to 0, sweep up again | 82,140,170,190,→199,→0,16,24,43 | **391** |
| **C-LOOK** | Like C-SCAN but jump between the extreme *requests* | 82,140,170,190,→16,24,43 | **341** |

A few sample computations (moving toward larger tracks):

- **SSTF:** $|50{-}43| + |43{-}24| + |24{-}16| + |16{-}82| + |82{-}140| + |140{-}170| + |170{-}190|
  = 7+19+8+66+58+30+20 = \mathbf{208}$.
- **SCAN:** up to the end and back, $(199-50) + (199-16) = 149 + 183 = \mathbf{332}$.
- **C-LOOK:** up to the last request, jump to the lowest, up again:
  $(190-50) + (190-16) + (43-16) = 140 + 174 + 27 = \mathbf{341}$.

> **Trap.** SSTF and SCAN-family algorithms cut total movement versus FCFS, but SSTF can **starve**
> a request far from the head if closer requests keep arriving. The SCAN family avoids starvation by
> sweeping steadily. The **circular** variants (C-SCAN/C-LOOK) give more *uniform* waiting time by
> always servicing in one direction, at the cost of the return jump. On **SSDs** — which have no
> heads or rotation — seek time vanishes and this scheduling largely loses its point.

## How the CPU talks to devices: polling, interrupts, and DMA

There are three ways for the CPU to move data to and from a device, differing in how the CPU learns
that the device is ready.

- **Programmed I/O / polling.** The CPU repeatedly reads the device's status register in a busy
  loop until it is ready. A poll is cheap (nanoseconds), but the CPU **wastes cycles** whenever the
  device is idle.
- **Interrupt-driven I/O.** The device raises an **interrupt** when it has work; the CPU does other
  things (or sleeps) until then, and a handler runs per event. Each interrupt has a **fixed
  overhead** — saving/restoring context, dispatching the handler, and the cache/pipeline disruption
  it causes — on the order of a microsecond or two.
- **DMA (direct memory access).** A DMA controller transfers a whole block directly between the
  device and memory **without the CPU per word**; the CPU only sets up the transfer and is
  interrupted **once** at completion. Used for bulk transfers (disk, network), it frees the CPU from
  data movement ("cycle stealing" occasionally borrows the memory bus).

| | Polling | Interrupt-driven | DMA |
|---|---|---|---|
| CPU cost when idle | High (busy-wait) | Low (other work) | Lowest |
| Cost per event | Very low | ~µs of overhead | Near zero (one interrupt/block) |
| Best when | Events arrive back-to-back | Events are sparse | Bulk transfers |

### Which to use — and interrupt livelock

The right choice depends on the **event rate**.

- **Sparse events** (a keypress, a door sensor at ~1/minute): use **interrupts**. Polling would pin
  the CPU near 100 % just to catch a rare event.
- **Very high rate** (a 100 Gbps NIC at ~10 million packets/second): interrupts **melt down**. At
  $10^7$ events/s and ~2 µs each, servicing interrupts alone would need $10^7 \times 2\,\mu s = 20$
  seconds of CPU **per second** — impossible. The machine spends all its time entering and leaving
  the handler and makes no forward progress. This is **interrupt livelock**; the fix is to switch to
  **polling** once packets stream in.

> **Key point — the adaptive hybrid (Linux NAPI).** Real NIC drivers combine both: take the **first
> interrupt** to notice work has arrived, then **disable that interrupt and poll**, draining the
> device's queue cheaply while it stays busy; **re-arm the interrupt only when a poll finds the
> queue empty**. The switch is driven by whether each poll still finds work — interrupt-when-idle,
> poll-when-busy — capturing the best of both. **Interrupt coalescing** (one interrupt per batch of
> packets) is a simpler hardware relative.

### Bounded queues and tail latency

A related design choice on a latency-sensitive path is how to implement a bounded work queue:

- A **fixed-capacity ring buffer** (an array with `head`/`tail` indices advanced mod *N*) is
  **O(1) worst-case** for both enqueue and dequeue, allocated once up front and cache-friendly, and
  simply **rejects** when full.
- A **two-stack queue** (an `inbox` and an `outbox`) is O(1) *amortized* for dequeue — but a single
  dequeue that finds the outbox empty must transfer all *n* elements across, an **O(n) worst-case
  spike**.

> **Key point.** "Amortized O(1)" means the *average* over a sequence is constant — each element is
> handled a constant number of times (pushed to the inbox, transferred to the outbox, popped) — but
> it is explicitly **not** a worst-case bound. On a path with a tight, predictable deadline, choose
> the **ring buffer**: its O(1) worst case has no tail-latency spike, whereas the two-stack queue's
> periodic O(n) transfer would blow the deadline even though its average is fine.

---
