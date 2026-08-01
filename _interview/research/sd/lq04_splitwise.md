# LQ04 — Design Splitwise (Expense Sharing)

**Interview relevance:** High — staple LLD / machine-coding question (campus + experienced); tests Strategy for split types, pairwise balance ledgers, debt simplification, and concurrency at Flipkart, Uber, Amazon, Microsoft, Atlassian, and fintech loops (Razorpay / CRED / PhonePe style).
**Type:** LLD-question
**Prereqs:** L01 (OOP & SOLID — especially OCP), L02 (creational — Factory / Singleton / Builder), L04 (behavioral — Strategy; Observer optional for notifications), L05 (concurrency for balance updates)

## Read / watch (curated, in order)
- [ ] [Design Splitwise | LLD](https://algomaster.io/learn/lld/design-splitwise) — `algomaster` (via awesome-lld) — clarifying Q&A → FRs (EQUAL / EXACT / PERCENT, pairwise balances, partial settle, rounding) before you draw classes
- [ ] [Design Splitwise | Machine Coding Round](https://workat.tech/machine-coding/practice/splitwise-problem-0kp2yneec2q2/index.html) — `workat.tech` — Flipkart-style problem statement + sample I/O; practice coding to a demoable CLI in ~90 min
- [ ] [Designing Splitwise (problem + diagram)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/splitwise.md) — `awesome-low-level-design` — requirements checklist + [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/splitwise-class-diagram.png); primary sheet problem
- [ ] [Java solution (Strategy + BalanceSheet + simplify)](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/splitwise) — `awesome-low-level-design` — reference code: `SplitStrategy` / `EqualSplitStrategy` / `ExactSplitStrategy` / `PercentageSplitStrategy`, `Expense.ExpenseBuilder`, `simplifyGroupDebts`, `settleUp` (also Python / C++ / C# / Go siblings)
- [ ] [Splitwise Low Level Design — Expense Splitter](https://lldhub.in/blog/expense-splitter-lld-design) — `lldhub` — compact interview guide: Strategy code, balance updates, greedy debt simplification, common follow-ups
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) — `Refactoring.Guru` — swap EQUAL / EXACT / PERCENT (/ SHARE) without editing `Expense` / `ExpenseService` (OCP)
- [ ] [Factory Method](https://refactoring.guru/design-patterns/factory-method) — `Refactoring.Guru` — optional: `SplitFactory` / `ExpenseFactory` from `SplitType` enum so callers never `new` concrete strategies
- [ ] [Singleton](https://refactoring.guru/design-patterns/singleton) — `Refactoring.Guru` — how many reference solutions gate the service (`getInstance`); know the testing / concurrency caveats
- [ ] [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — optional: notify group members on new expense / settlement; don’t force if time-boxed
- [ ] [ConcurrentHashMap (Java)](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/concurrent/ConcurrentHashMap.html) — `Oracle JDK docs` — thread-safe user/group maps; still lock **per pairwise balance update** (map alone ≠ atomic ledger adjust)
- [ ] [Splitwise System Design with Full Code](https://www.youtube.com/watch?v=YFxxTGUdkAE) — `YouTube` — long-form LLD: entities, Strategy/Factory/Observer, then debt-settlement algorithms (greedy → backtracking / DP)
- [ ] [Splitwise LLD: UML + Code](https://www.youtube.com/watch?v=syH7axOpqhA) — `YouTube` — shorter UML → ledger → simplify walkthrough if you want a second pass
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo (Flipkart/Uber/Swiggy style)
- [ ] [gopalbala/billsharing](https://github.com/gopalbala/billsharing) — `GitHub` — alternate Java bill-sharing implementation linked from the LLD primer
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — solutions index (Splitwise / bill-sharing row) after you can code the happy path
- [ ] [Design an LLD of Splitwise (asked-at)](https://www.hellointerview.com/community/questions/splitwise-lld/cm6jwwh6700bxui4bzs4jmddl) — `Hello Interview` — company tags (Microsoft / Uber / Amazon); use as “where asked,” not as a full breakdown

## Core concepts to master
- **Three split types (must ship):** **EQUAL** (amount / N, fix rounding so shares sum to total), **EXACT** (given amounts must sum to total), **PERCENT** (percents must sum to 100). Optional later: **SHARE** (weighted parts).
- **Strategy = the pattern for splits:** `SplitStrategy.calculateShares(amount, participants) → Map<User, Double>`. `EqualSplit` / `ExactSplit` / `PercentageSplit` implement it. Never bury `if (type == EQUAL)` inside `Expense` if the interviewer probes extensibility.
- **Pairwise balances, not just net totals:** maintain who owes whom — e.g. `balances[A][B] = amount A owes B` (or signed `BalanceSheet` per user). Netting A↔B (A owes B 50, B owes A 20 → A owes B 30) is expected.
- **Expense is an immutable ledger entry:** once added, don’t mutate shares; settlements adjust balances (and optionally append a `Settlement` / `Transaction` record). Passbook = list of expenses + settlements a user touched.
- **Key methods to name and implement:** `addUser`, `createGroup` / `addMember`, `addExpense` (or `createExpense` + Builder), `showBalances` / `getBalance(user)`, `settleUp(from, to, amount)`, `simplifyDebts(group)` (optional but frequently asked).
- **Debt simplification (greedy interview default):** compute net balance per user → creditors (net > 0) + debtors (net < 0) → repeatedly match largest creditor with largest debtor for `min(|debt|, credit)` until done. Yields ≤ N−1 transfers; exact min-transfer count is harder (NP-hard) — mention, don’t implement DP unless asked.
- **Validation gates:** reject EXACT if sums ≠ amount; reject PERCENT if ≠ 100; reject settle if amount ≤ 0 or exceeds owed; round to 2 decimals (workat: give remainder to first share so EQUAL still sums).
- **Concurrency:** two expenses updating the same pair must not race. Synchronize `addExpense` / `settleUp` (service-level lock, or lock ordered user-id pairs). `ConcurrentHashMap` for catalogs is fine; balance adjust still needs an atomic critical section.
- **Patterns map:** Strategy (splits) primary; Factory (create strategy from enum); Builder (`Expense.ExpenseBuilder`) common in reference code; Singleton for `SplitwiseService` (optional — DI is cleaner for tests); Observer for “notify on expense” if time permits; Facade = thin `SplitwiseService` API over entities.
- **Out of scope until asked:** multi-currency / FX, recurring expenses, images/notes, real payments rails, auth — call them out early.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈35–45 min LLD / ≈90 min machine-coding):

### 1. Requirements (functional + non-functional) & scale assumptions
- **Clarify first:** group + non-group expenses? EQUAL / EXACT / PERCENT only? partial settle? simplify debts in scope? notifications? concurrency? single currency?
- **FR (typical):** users + groups; add expense (payer, amount, participants, split type); show pairwise balances; settle (full/partial); optional simplify + passbook.
- **NFR:** correct validation + rounding; no lost balances under concurrent updates; OCP for new split types; modular packages (entities / strategy / service); demonstrable `main`.
- **Assumptions to state:** e.g. single currency; expenses immutable; 2-decimal money; groups don’t auto-delete historical members from old expenses.

### 2. Back-of-envelope estimation (for HLD)
- **LLD:** skip capacity math. State only that balance update is O(P) per expense (P participants), show-balances is O(U) non-zero edges for a user, simplify is O(N log N) for N group members.

### 3. API / interface
```
User addUser(String name, String email)
Group createGroup(String name, List<User> members)

void addExpense(String groupId /* nullable */, String desc, double amount,
                User paidBy, List<User> participants,
                SplitType type, List<Double> values /* exact amts or percents */)

Map<User, Double> getBalances(String userId)   // non-zero pairwise
void settleUp(String fromUserId, String toUserId, double amount)

List<Transaction> simplifyGroupDebts(String groupId)  // optional
void showBalances() / showBalances(String userId)     // CLI / demo
```
- Machine-coding variants often parse `EXPENSE …` / `SHOW` / `SHOW u1` lines (see workat.tech). Keep parsing in a thin driver; domain logic stays in services.

### 4. Data model / class diagram
```
SplitwiseService                    // Facade entry (+ optional Singleton)
 - users: Map<id, User>
 - groups: Map<id, Group>
 + addUser / addGroup / createExpense / settleUp / showBalanceSheet / simplifyGroupDebts

User
 - id, name, email
 - balanceSheet: BalanceSheet

Group
 - id, name
 - members: List<User>
 - expenses: List<Expense>          // optional history

Expense                             // immutable after build
 - id, description, amount, paidBy
 - splits: List<Split>              // user + computed share amount
 - (built via ExpenseBuilder + SplitStrategy)

Split                               // value: user + amount owed for this expense
BalanceSheet
 - balances: Map<User, Double>      // signed: + ⇒ others owe you / you are owed
 + adjustBalance(other, delta)
 + showBalances()

Transaction / Settlement
 - from, to, amount

SplitStrategy <<interface>>
 + calculateSplits(amount, participants, values) → List<Split>
 └─ EqualSplitStrategy / ExactSplitStrategy / PercentageSplitStrategy

SplitType { EQUAL, EXACT, PERCENT } // enum; Factory maps → Strategy
```
- Sketch this UML (or the [awesome-lld diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/splitwise-class-diagram.png)) before coding.

### 5. High-level architecture / component breakdown
```
CLI / Driver
     │ EXPENSE / SHOW / SETTLE
     ▼
SplitwiseService (Facade)
     │ uses
     ├─► SplitStrategy (EQUAL | EXACT | PERCENT)
     │        └─ produces Splits
     ├─► Expense (+ Builder)  ──append──► Group.expenses (optional)
     └─► BalanceSheet.adjustBalance  (±amount for payer ↔ participant)
              │
              ▼
        settleUp / simplifyGroupDebts → Transaction list
```
- **Service:** orchestration + locking only — no split math inline.
- **Strategy:** pure calculation + validation.
- **BalanceSheet:** single place that mutates who-owes-whom.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Strategy vs type-switch / inheritance-only Expense subclasses:** Strategy (or Split hierarchy + factory) wins for OCP when SHARE / itemized splits appear; a giant `switch` fails the extensibility follow-up.
2. **Pairwise matrix vs net-only per user:** net-only can’t answer “who do I pay?”; pairwise (or signed bilateral sheet) is the interview default. Simplify collapses the graph when asked.
3. **Simplify greedy vs exact min transfers:** greedy is what you code in 90 min; call out NP-hardness / DP-with-bitmask only if they push “optimal.”
4. **Service-wide `synchronized` vs fine-grained locks:** coarse lock is correct and interview-safe; pair-ordered locks / per-group queues scale better — mention if concurrency is probed.

### 7. Bottlenecks / how you scale it
- Hot group (many concurrent expenses) → serialize updates per group (queue or group lock); keep expense append append-only.
- Large groups → don’t rebuild full N×N on every SHOW; store sparse bilateral edges; simplify only on demand.
- Multi-currency / FX → balances per currency or normalize via a `CurrencyConverter` Strategy before netting — only if asked.
- Persistence / HLD jump → expenses as event log; balances as materialized view; idempotent `expenseId` for retries.

## Common follow-ups / gotchas
- “$100 / 3 people?” — two get 33.33, one gets 33.34 (absorb remainder) so shares sum to 100.00.
- “EXACT / PERCENT invalid input?” — validate before mutating balances; throw / reject the expense atomically.
- “A owes B and B owes A?” — net the pair on read or on write; never show both directions as separate non-zero lines without netting.
- “Simplify: A→B 250 and B→C 200?” — nets become A owes B 50 and A (or B) owes C 200 depending on nets — explain via per-user net, not edge rewriting by hand.
- “Member leaves the group?” — history stays; exclude from new expenses; prompt settle outstanding.
- “Thread safety?” — atomic create-expense (compute splits → adjust all pairs) under one lock; don’t interleave two expenses mid-update.
- “Singleton for the service?” — fine for demo; prefer constructor injection in production / tests (Singleton complicates mocking).

## Where it appears
- **Campus / machine-coding (Flipkart, Uber, Swiggy, Amazon new-grad, Indian product cos):** very common “design + code in 90 min” — working EQUAL/EXACT/PERCENT + balances beat a half-finished pattern zoo; simplify is the usual stretch.
- **Experienced LLD (FAANG / Atlassian / Microsoft / fintech):** same core, deeper probes on Strategy vs switch, pairwise ledger correctness, greedy vs optimal simplify, and concurrent balance updates.
- **Frequency:** among the top ~10 canonical LLD problems (with parking lot, elevator, rate limiter, Tic-Tac-Toe); expect it if your sheet’s LLD track is interview-realistic.
