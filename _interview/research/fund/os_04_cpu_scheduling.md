# CPU scheduling

## Scheduling fundamentals

When several processes sit in the **ready queue**, the CPU scheduler selects one to run.
The choice is governed by two things: the **criterion** the algorithm keys on (arrival
time, burst length, priority, or a time quantum) and its **mode**:

- **Non-preemptive** — once a process holds the CPU it runs until it finishes its burst (or
  voluntarily blocks). A newly arrived, more deserving process must wait.
- **Preemptive** — the running process can be interrupted and returned to the ready queue if
  another process becomes more deserving under the algorithm's criterion.

### Timing attributes

Each process is described by its **Arrival Time (AT)** — when it enters the ready queue — and
its **Burst Time (BT)** — the CPU time it requires. The scheduler's behaviour is then
evaluated through four derived quantities.

> **Definition — Completion Time (CT).** The instant at which a process finishes execution
> and leaves the system.

> **Definition — Turnaround Time (TAT).** Total time a process spends in the system, from
> arrival to completion:
> $$\text{TAT} = \text{CT} - \text{AT}$$

> **Definition — Waiting Time (WT).** Time spent waiting in the ready queue, i.e. turnaround
> minus the time actually spent executing:
> $$\text{WT} = \text{TAT} - \text{BT}$$

> **Definition — Response Time (RT).** Time from arrival until the process is *first* given
> the CPU — not its completion:
> $$\text{RT} = (\text{time of first CPU allocation}) - \text{AT}$$

In a non-preemptive algorithm a process runs in one unbroken stretch, so its first CPU
allocation coincides with the start of its only execution interval; there
$\text{RT} = \text{WT}$. The two diverge only under preemption, where a process may begin,
be interrupted, and resume later.

### The algorithms at a glance

| Algorithm | Criterion | Mode |
|---|---|---|
| First Come First Serve (FCFS) | Arrival time | Non-preemptive |
| Shortest Job First (SJF) | Burst time | Non-preemptive |
| Shortest Remaining Time First (SRTF) | Burst time (remaining) | Preemptive |
| Round Robin (RR) | Time quantum | Preemptive |
| Priority scheduling | Priority | Preemptive (or non-preemptive) |
| Multilevel Queue | Per-queue priority | — |
| Multilevel Feedback Queue | Per-queue, with movement | — |

---

## First Come First Serve (FCFS)

FCFS allocates the CPU in order of arrival: the process that requested the CPU earliest runs
first. The criterion is **arrival time** and the mode is **non-preemptive**.

**Worked example.**

| Process | AT | BT | CT | TAT | WT | RT |
|---|---|---|---|---|---|---|
| P1 | 0 | 2 | 2 | 2 | 0 | 0 |
| P2 | 1 | 2 | 4 | 3 | 1 | 1 |
| P3 | 5 | 3 | 8 | 3 | 0 | 0 |
| P4 | 6 | 4 | 12 | 6 | 2 | 2 |

P1 arrives first and runs over $[0,2]$. P2 (arrived at 1) follows over $[2,4]$. After P2 the
CPU is **idle** from 4 to 5, because the next process, P3, does not arrive until time 5;
this is a key feature of FCFS — the CPU can sit idle even with work pending in the future.
P3 then runs $[5,8]$ and P4 runs $[8,12]$.

**Gantt chart**

| Time | 0–2 | 2–4 | 4–5 | 5–8 | 8–12 |
|---|---|---|---|---|---|
| CPU | P1 | P2 | *idle* | P3 | P4 |

The derived values follow directly from $\text{TAT}=\text{CT}-\text{AT}$ and
$\text{WT}=\text{TAT}-\text{BT}$. For P4: $\text{TAT}=12-6=6$ and $\text{WT}=6-4=2$.

> **Trap.** FCFS is simple but suffers the *convoy effect*: a long burst arriving early
> forces many short jobs to wait behind it, inflating average waiting time.

---

## Shortest Job First (SJF) — non-preemptive

Among the processes that have **already arrived**, SJF selects the one with the smallest
**burst time**. The criterion is burst time; the mode here is **non-preemptive**, so once a
job starts it runs to completion.

**Worked example.**

| Process | AT | BT | CT | TAT | WT | RT |
|---|---|---|---|---|---|---|
| P1 | 1 | 3 | 6 | 5 | 2 | 2 |
| P2 | 2 | 4 | 10 | 8 | 4 | 4 |
| P3 | 1 | 2 | 3 | 2 | 0 | 0 |
| P4 | 4 | 4 | 14 | 10 | 6 | 6 |

The CPU is idle over $[0,1]$ until the first arrivals at time 1 (P1 and P3). Of those two,
P3 has the shorter burst (2 vs 3), so P3 runs first $[1,3]$. At time 3 the arrived set is
{P1, P2}; P1's burst (3) is shorter, so P1 runs $[3,6]$. Next P2 runs $[6,10]$, and finally
P4 runs $[10,14]$.

**Gantt chart**

| Time | 0–1 | 1–3 | 3–6 | 6–10 | 10–14 |
|---|---|---|---|---|---|
| CPU | *idle* | P3 | P1 | P2 | P4 |

**Averages**

$$\text{Average TAT} = \frac{5+8+2+10}{4} = \frac{25}{4} = 6.25$$
$$\text{Average WT} = \frac{2+4+0+6}{4} = \frac{12}{4} = 3$$

> **Trap — ties.** When two processes have equal burst time (here P2 and P4 both have 4),
> break the tie by arrival order (and, failing that, by process number). P2 arrived earlier,
> so it is scheduled before P4.

> **Key point.** Non-preemptive SJF gives the minimum average waiting time for a *fixed* set
> of jobs available together, but it cannot react to a short job arriving while a long job is
> already running — that limitation motivates the preemptive variant below.

---

## Shortest Remaining Time First (SRTF) — preemptive SJF

SRTF is the preemptive form of SJF. At every instant the CPU runs the process with the
smallest **remaining** burst time; the arrival of a process with a shorter remaining time
**preempts** the current one. Criterion: burst (remaining) time. Mode: preemptive.

**Worked example.**

| Process | AT | BT | CT | TAT | WT | RT |
|---|---|---|---|---|---|---|
| P1 | 0 | 5 | 9 | 9 | 4 | 0 |
| P2 | 1 | 3 | 4 | 3 | 0 | 0 |
| P3 | 2 | 4 | 13 | 11 | 7 | 7 |
| P4 | 4 | 1 | 5 | 1 | 0 | 0 |

Tracing the remaining times:

- $t=0$: only P1 is present; it runs. (P1 remaining $5\to4$ by $t=1$.)
- $t=1$: P2 arrives with burst 3, which is less than P1's remaining 4, so P2 preempts P1 and
  runs.
- $t=2$: P3 arrives (burst 4); the running P2 has remaining 2, still the smallest, so P2
  continues.
- $t=4$: P2 completes (CT 4). P4 has just arrived with burst 1 — the smallest — so P4 runs.
- $t=5$: P4 completes (CT 5). The contenders are P1 (remaining 4) and P3 (remaining 4); the
  tie is resolved in P1's favour, and P1 runs to completion at $t=9$.
- $t=9$: P3 runs last, completing at $t=13$.

**Gantt chart**

| Time | 0–1 | 1–4 | 4–5 | 5–9 | 9–13 |
|---|---|---|---|---|---|
| CPU | P1 | P2 | P4 | P1 | P3 |

Note how response time and waiting time now differ. P1 starts immediately ($\text{RT}=0$)
but is preempted, so its $\text{WT}=4$. P3 is never preempted but waits a long time before
its first slice: $\text{RT} = 9 - 2 = 7$, equal to its waiting time here.

---

## Round Robin (RR)

Round Robin shares the CPU fairly by giving each ready process a fixed **time quantum (TQ)**.
A process runs for at most one quantum, then — if unfinished — is preempted and sent to the
**back** of the ready queue, while the next process is dispatched. The criterion is the time
quantum; the mode is preemptive. Conceptually each process cycles between the **Ready** and
**Running** states.

**Worked example** (TQ = 2).

| Process | AT | BT | CT | TAT | WT | RT |
|---|---|---|---|---|---|---|
| P1 | 0 | 5 | 12 | 12 | 7 | 0 |
| P2 | 1 | 4 | 11 | 10 | 6 | 1 |
| P3 | 2 | 2 | 6 | 4 | 2 | 2 |
| P4 | 4 | 1 | 9 | 5 | 4 | 4 |

The ready-queue discipline is the crux. When a process's quantum expires, every process that
arrived *during* that quantum is enqueued **before** the preempted process is re-added.

- $[0,2]$ P1 runs (remaining $5\to3$). During this slice P2 (t=1) and P3 (t=2) arrive.
- $[2,4]$ P2 runs (remaining $4\to2$). P4 arrives at $t=4$.
- $[4,6]$ P3 runs and finishes (CT 6).
- $[6,8]$ P1 runs (remaining $3\to1$).
- $[8,9]$ P4 runs and finishes (CT 9).
- $[9,11]$ P2 runs and finishes (CT 11).
- $[11,12]$ P1 runs its last unit and finishes (CT 12).

The resulting **sequence of processes in the ready queue** is therefore
P1, P2, P3, P1, P4, P2, P1.

**Gantt chart**

| Time | 0–2 | 2–4 | 4–6 | 6–8 | 8–9 | 9–11 | 11–12 |
|---|---|---|---|---|---|---|---|
| CPU | P1 | P2 | P3 | P1 | P4 | P2 | P1 |

> **Key point.** Each boundary between two different processes in the Gantt chart is a
> **context switch**. RR guarantees a small response time (no process waits longer than
> $(n-1)\times\text{TQ}$ for its first slice) at the cost of more context switches.

> **Trap.** Response time is *not* the same as waiting time here. P3, for instance, first
> gets the CPU at $t=4$, so $\text{RT}=4-2=2$, while its waiting time also happens to be 2;
> but P1 has $\text{RT}=0$ and $\text{WT}=7$ because it is repeatedly preempted.

---

## Priority scheduling (preemptive)

Each process carries a **priority** value; the scheduler always runs the highest-priority
ready process. In the preemptive form, a newly arrived higher-priority process immediately
displaces the running one.

> **Convention (this example).** *Higher number = higher priority.* (The numeric convention
> is arbitrary and must be stated for each problem — the I/O example that follows uses the
> opposite convention.)

**Worked example** — priorities 10, 20, 30, 40 with larger meaning more urgent.

| Priority | Process | AT | BT | CT | TAT | WT |
|---|---|---|---|---|---|---|
| 10 | P1 | 0 | 5 | 12 | 12 | 7 |
| 20 | P2 | 1 | 4 | 8 | 7 | 3 |
| 30 | P3 | 2 | 2 | 4 | 2 | 0 |
| 40 | P4 | 4 | 1 | 5 | 1 | 0 |

- $[0,1]$ P1 runs (only process present).
- $t=1$: P2 (priority 20 > 10) preempts P1 and runs $[1,2]$.
- $t=2$: P3 (priority 30) preempts P2 and runs $[2,4]$ to completion (CT 4).
- $t=4$: P4 (priority 40, highest) runs $[4,5]$ to completion (CT 5).
- $[5,8]$ the remaining highest priority is P2 (20 > P1's 10); it finishes (CT 8).
- $[8,12]$ P1 finally completes (CT 12).

**Gantt chart**

| Time | 0–1 | 1–2 | 2–4 | 4–5 | 5–8 | 8–12 |
|---|---|---|---|---|---|---|
| CPU | P1 | P2 | P3 | P4 | P2 | P1 |

> **Trap — starvation.** A continuous stream of high-priority arrivals can keep a
> low-priority process (here P1) waiting indefinitely. The standard remedy is **aging**:
> gradually raising the priority of a process the longer it waits.

---

## Priority scheduling with I/O bursts

Real processes alternate between CPU activity and I/O. This example models each process as a
**CPU burst → I/O burst → CPU burst** sequence and schedules the CPU bursts by priority
(preemptive). While a process is doing I/O it is not contending for the CPU, which frees the
CPU for others and changes the schedule substantially.

> **Convention (this example).** *Lower number = higher priority*, so priority 1 is the
> highest and 4 is the lowest — the reverse of the previous example.

| Process | AT | Priority | CPU | I/O | CPU |
|---|---|---|---|---|---|
| P1 | 0 | 2 | 1 | 5 | 3 |
| P2 | 2 | 3 | 3 | 3 | 1 |
| P3 | 3 | 1 *(highest)* | 2 | 3 | 1 |
| P4 | 3 | 4 *(lowest)* | 2 | 4 | 1 |

**Resulting completion times:** P1 = 10, P2 = 15, P3 = 9, P4 = 18.

Working through the timeline (priority 1 beats 2 beats 3 beats 4, preemptive on CPU bursts):

- $[0,1]$ P1 runs its first CPU burst, then leaves for I/O (returns at $t=6$).
- $[1,2]$ CPU **idle** — nothing has arrived yet (P2, P3, P4 arrive at 2, 3, 3).
- $[2,3]$ P2 starts (it is alone).
- $t=3$: P3 (priority 1) arrives and preempts P2; P3 runs $[3,5]$, finishing its first CPU
  burst, then leaves for I/O (returns at $t=8$).
- $[5,6]$ P2 resumes (P4 is lower priority).
- $t=6$: P1 returns from I/O (priority 2) and preempts P2; P1 runs $[6,8]$.
- $t=8$: P3 returns from I/O (priority 1, highest) and preempts P1; P3 runs $[8,9]$ — its
  final CPU burst — and **completes at 9**.
- $[9,10]$ P1 resumes and **completes at 10**.
- $[10,11]$ P2 runs; this ends its first CPU burst, so it leaves for I/O (returns at $t=14$).
- $[11,13]$ P4 runs its first CPU burst, then leaves for I/O (returns at $t=17$).
- $[13,14]$ CPU idle (everyone is in I/O).
- $[14,15]$ P2 returns and runs its final CPU burst — **completes at 15**.
- $[15,17]$ CPU idle (P4 still in I/O).
- $[17,18]$ P4 returns and runs its final CPU burst — **completes at 18**.

**Gantt chart**

| Time | 0–1 | 1–2 | 2–3 | 3–5 | 5–6 | 6–8 | 8–9 | 9–10 | 10–11 | 11–13 | 13–14 | 14–15 | 15–17 | 17–18 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| CPU | P1 | *idle* | P2 | P3 | P2 | P1 | P3 | P1 | P2 | P4 | *idle* | P2 | *idle* | P4 |

**Concurrent I/O intervals** (overlapping the CPU timeline above):

| Process | In I/O during |
|---|---|
| P1 | 1 → 6 |
| P3 | 5 → 8 |
| P2 | 11 → 14 |
| P4 | 13 → 17 |

> **Key point.** Overlapping I/O with CPU work is exactly why a process can "leave" and
> "return," producing idle CPU gaps (1–2, 13–14, 15–17) even while jobs are technically in
> the system. The schedule cannot be read off burst lengths alone — the I/O return times
> drive it.

---

## Multilevel Queue (MLQ) scheduling

Instead of one ready queue, MLQ partitions processes into **several separate queues by
type**, each with its own scheduling algorithm and a **fixed priority**. A process is
permanently assigned to one queue and never moves between them.

In the configuration shown, three queues feed the CPU:

| Priority | Queue (process type) | Scheduling algorithm |
|---|---|---|
| Highest | System processes | Round Robin |
| Medium | Interactive processes | Shortest Job First |
| Lowest | Batch processes | First Come First Serve |

A higher-priority queue is generally served entirely before a lower one is considered. This
contrasts with ordinary scheduling, where a single ready queue (P1, P2, …, Pₙ) feeds the CPU
directly, as drawn on the right of the figure.

![Multilevel Queue scheduling: three fixed-priority queues (system / interactive / batch), each with its own algorithm, contrasted with a single ready queue feeding the CPU.](assets/multilevel_queue.png)

> **Key point.** The defining property of MLQ is **no migration** — a batch process can
> never be promoted into the system-process queue. This rigidity is what the Multilevel
> Feedback Queue relaxes.

---

## Multilevel Feedback Queue (MLFQ) scheduling

MLFQ keeps multiple queues but allows a process to **move between them** based on its
behaviour. A process that uses up its time quantum without finishing is **demoted** to the
next queue, which grants a larger quantum. The final queue runs FCFS, absorbing the
long-running jobs.

The configuration shown uses four queues, with the time quantum doubling at each level:

| Queue | Discipline | Priority (as labelled in source) |
|---|---|---|
| RQ₁ | Time quantum = 2 | Lowest *(batch)* |
| RQ₂ | Time quantum = 4 | — |
| RQ₃ | Time quantum = 8 | — |
| RQ₄ | FCFS | Highest *(system)* |

A process enters RQ₁. The rule at every level above the last is the same: **if it completes,
it leaves the system; otherwise it falls through to the next queue.** Whatever remains by RQ₄
is "executed in FCFS manner."

**Worked trace.** A process with a total burst of 19 is whittled down as it descends:

$$19 \xrightarrow{\;\text{RQ}_1,\ \text{run }2\;} 17 \xrightarrow{\;\text{RQ}_2,\ \text{run }4\;} 13 \xrightarrow{\;\text{RQ}_3,\ \text{run }8\;} 5 \xrightarrow{\;\text{RQ}_4,\ \text{FCFS, run }5\;} 0$$

The four service slices sum to $2 + 4 + 8 + 5 = 19$, exhausting the burst.

![Multilevel Feedback Queue: a process flows RQ1 (TQ 2) → RQ2 (TQ 4) → RQ3 (TQ 8) → RQ4 (FCFS), being demoted each time it fails to finish within its quantum; the worked trace reduces a burst of 19 to 0.](assets/multilevel_feedback_queue.png)

> **Key point.** MLFQ approximates "shortest job first" *without* knowing burst times in
> advance: short jobs finish in the early, small-quantum queues and leave quickly, while
> long jobs sink to the FCFS queue. The doubling quanta (2, 4, 8) limit how often a
> long-running job is preempted.

---

## Assessment templates: average-turnaround drills

Online assessments (Cisco's among them) reuse two scheduling templates almost verbatim: *"given
arrival and burst times, find the average turnaround time under preemptive SJF"* and *"…under
preemptive priority."* Both are pure simulations — build the Gantt chart, decide at **every arrival
and every completion**, then average $\text{TAT}=\text{CT}-\text{AT}$. The two fully worked
examples below are the templates to drill.

### Template A — Preemptive SJF (SRTF), five processes

| Process | AT | BT | CT | TAT | WT |
|---|---|---|---|---|---|
| P1 | 0 | 8 | 18 | 18 | 10 |
| P2 | 2 | 4 | 7 | 5 | 1 |
| P3 | 3 | 1 | 4 | 1 | 0 |
| P4 | 5 | 3 | 12 | 7 | 4 |
| P5 | 6 | 2 | 9 | 3 | 1 |

Deciding at each event by smallest **remaining** time: P1 runs alone from 0; at $t=2$ P2 (burst 4)
undercuts P1's remaining 6 and preempts it; at $t=3$ P3 (burst 1) preempts P2; P3 finishes at 4,
after which P2 (remaining 3) is shortest and runs to completion at 7; then P5 (2), P4 (3), and
finally the long P1 tail.

**Gantt chart**

| Time | 0–2 | 2–3 | 3–4 | 4–7 | 7–9 | 9–12 | 12–18 |
|---|---|---|---|---|---|---|---|
| CPU | P1 | P2 | P3 | P2 | P5 | P4 | P1 |

$$\text{Average TAT} = \frac{18+5+1+7+3}{5} = \frac{34}{5} = 6.8$$

> **Trap.** The single most common error is forgetting to preempt when a shorter job arrives
> mid-run (here P2→P3 at $t=3$). Re-evaluate the ready set at **every** arrival, not just at
> completions. Note also that SRTF starves the long job: P1 arrived first yet finishes last.

### Template B — Preemptive priority, five processes

Here **a smaller priority number means higher priority** (priority 1 is the most urgent). This
convention is the reverse of the earlier preemptive-priority example, and flipping it is the
classic misread on these questions — always confirm which way the problem defines it.

| Process | AT | BT | Priority | CT | TAT |
|---|---|---|---|---|---|
| P1 | 0 | 7 | 4 | 14 | 14 |
| P2 | 1 | 3 | 2 | 5 | 4 |
| P3 | 2 | 1 | 1 *(highest)* | 3 | 1 |
| P4 | 4 | 3 | 3 | 8 | 4 |
| P5 | 6 | 2 | 5 *(lowest)* | 16 | 10 |

At $t=1$ P2 (priority 2) preempts P1 (priority 4); at $t=2$ P3 (priority 1) preempts P2 and finishes
at 3; P2 then resumes and completes at 5; P4 (priority 3) runs next while P1 (4) and the not-yet-more
-urgent arrivals wait; P1 finally runs its long remainder, and the lowest-priority P5 runs last.

**Gantt chart**

| Time | 0–1 | 1–2 | 2–3 | 3–5 | 5–8 | 8–14 | 14–16 |
|---|---|---|---|---|---|---|---|
| CPU | P1 | P2 | P3 | P2 | P4 | P1 | P5 |

$$\text{Average TAT} = \frac{14+4+1+4+10}{5} = \frac{33}{5} = 6.6$$

> **Trap — starvation and convention.** Because urgency, not burst length, drives the choice, a
> low-priority process (P5) is pushed to the very end. And the *only* thing separating a correct
> answer from a wrong one is often the priority convention: read "lower number = higher priority"
> versus "higher number = higher priority" before touching the Gantt chart.

---
