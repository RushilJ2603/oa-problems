# LQ06 — Design an ATM

**Interview relevance:** High — canonical State + Chain-of-Responsibility LLD / machine-coding question (campus + experienced); especially common at fintech / payments loops (Paytm, PhonePe, Razorpay, Visa, banks) and product cos probing FSM modeling, hardware orchestration, and transactional safety.
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Singleton), l03_patterns_structural (Facade); State / Chain of Responsibility / Command from l04_patterns_behavioral (or Refactoring.Guru links below); l05_concurrency_lld; warm-up sibling: lq05_vending_machine (same State-pattern muscle)

## Read / watch (curated, in order)
- [ ] [Designing an ATM System (problem + UML + multi-lang code)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/atm.md) — `awesome-low-level-design` — **start here:** requirements, [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/atm-class-diagram.png), Card / Account / Transaction / BankingService / CashDispenser; hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Java ATM solution (State + Chain of Responsibility)](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/atm) — `awesome-low-level-design` — runnable reference: `ATMSystem` + [`state/`](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/atm/state) (`IdleState` / `HasCardState` / `AuthenticatedState`) + [`chainofresponsibility/`](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/atm/chainofresponsibility) (`NoteDispenser100` → `50` → `20`); also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/atm)
- [ ] [Design ATM | LLD](https://algomaster.io/learn/lld/design-atm) — `algomaster` (via awesome-lld) — clarifying-questions script, denominations ($100/$50/$20/$10), validation-before-commit framing
- [ ] [State](https://refactoring.guru/design-patterns/state) — `Refactoring.Guru` — **primary pattern:** same actions (`insertCard` / `enterPin` / `withdraw`) behave differently per state; contrast with Strategy (states own transitions)
- [ ] [Chain of Responsibility](https://refactoring.guru/design-patterns/chain-of-responsibility) — `Refactoring.Guru` — **cash dispenser:** each denomination cassette handles what it can, passes remainder down the chain
- [ ] [Finite-state machine (overview)](https://en.wikipedia.org/wiki/Finite-state_machine) — `Wikipedia` — draw Idle → HasCard → Authenticated → Dispensing → Idle *before* classes; interviewers grade this step
- [ ] [Getting Ready: The ATM System (Grokking LLD / Educative)](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/getting-ready-the-atm-system) — `Educative / Grokking OOD` — hardware components, auth, cash limits, edge cases; course hub: [Grokking the Low Level Design Interview Using OOD Principles](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles)
- [ ] [Design an ATM (Grokking OOD — free GitHub mirror)](https://github.com/tssovi/grokking-the-object-oriented-design-interview/blob/master/object-oriented-design-case-studies/design-an-atm.md) — `tssovi / Grokking OOD` — full free write-up: use cases, hardware entities, Checking/Savings, Transaction hierarchy, skeleton code (Educative classic also reachable via [Design an ATM](https://www.educative.io/courses/grokking-the-object-oriented-design-interview/design-an-atm))
- [ ] [Design ATM Machine (LLD) | Cash Withdrawal Flow | State + COR](https://www.youtube.com/watch?v=GSuaqBR0Wpc) — `YouTube` — end-to-end withdrawal walkthrough pairing State with denomination Chain of Responsibility
- [ ] [Low level design of an ATM machine | Understand State design pattern](https://www.youtube.com/watch?v=JEi7i7poflM) — `YouTube / Sanket Singh` — State-focused ATM LLD narration
- [ ] [State Design Pattern in detail | Interview Question](https://www.youtube.com/watch?v=JjgYV1jXC4I) — `YouTube` — pattern primer if State still feels fuzzy before coding ATM
- [ ] [ATM Machine Low Level Design — Complete LLD Interview Guide](https://lldhub.in/blog/atm-machine-lld-design) — `lldhub` — State + COR + Facade walkthrough with class list and Java sketches (fintech-flavored FAQ)
- [ ] [ATM Machine · LLD-flavoured](https://ikshitij.com/learn/lld-object-oriented/atm-machine/) — `ikshitij` — state diagram with PinFailed / InsufficientFunds / CashUnavailable; debit-before-eject ordering notes
- [ ] [LLD Case: ATM](https://resources.devweekends.com/lld/case-atm) — `DevWeekends` — why ATM is *the* State showcase + entity-responsibility table (ATM / ATMState / CashDispenser / Transaction / Bank)
- [ ] [ATM Machine LLD in Java — SOLID Design & State Pattern](https://sinhaanwesha16.medium.com/atm-machine-lld-in-java-solid-design-state-pattern-56b25993fb4b) — `Medium` — Idle / HasCard / Authenticated / Transaction / EjectCard + SOLID mapping
- [ ] [Building a Robust ATM Simulator in Java Using the State Pattern](https://dev.to/zeeshanali0704/building-a-robust-atm-simulator-in-java-using-the-state-pattern-54c3) — `DEV` — inventory-by-denomination + two-phase dispense + concurrency notes
- [ ] [LLD:14-ATM Machine System](https://dev.to/_noob/lld14-atm-machine-system-5e8b) — `DEV` — minimal State demo (Idle → InsertCard → EnterPin → Withdraw) if you want a 5-min mental model
- [ ] [Facade](https://refactoring.guru/design-patterns/facade) / [Command](https://refactoring.guru/design-patterns/command) / [Singleton](https://refactoring.guru/design-patterns/singleton) — `Refactoring.Guru` — ATM as facade over CardReader/Dispenser/BankService; Transaction as Command; one physical machine instance (optional)
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after you can code the happy path

## Core concepts to master
- **Clarify before coding:** which txns (balance / withdraw / deposit / transfer / mini-statement)? denominations & greedy largest-first? PIN retry / card retain? daily limits? one user at a time? simulate bank vs real network? receipt / deposit slot / operator refill in scope?
- **Draw the FSM first:** happy path `Idle → HasCard (PIN) → Authenticated → (Processing/Dispensing) → Idle`. Invalid actions in a state must reject / no-op — never allow `withdraw` from Idle.
- **Core entities:** `ATM` / `ATMSystem` (context + Facade) → `ATMState` hierarchy; `Card`, `Account`, `BankService`/`BankNetwork`; `CashDispenser` + denomination chain; `Transaction` hierarchy (Withdraw / Deposit / BalanceInquiry); optional hardware: `CardReader`, `Keypad`, `Screen`, `Printer`, `DepositSlot`.
- **State is the star pattern:** `ATMState` defines `insertCard` / `enterPin` / `selectOperation` / `ejectCard`; each concrete state implements valid behavior and calls `atm.changeState(...)`. Adding `OutOfService` / `Maintenance` / `CardBlocked` should not edit a giant `switch` in `ATM`.
- **Chain of Responsibility for cash:** `NoteDispenser2000 → 500 → 200 → 100` (or $100→$50→$20→$10). Each cassette: `num = min(amount/denom, stock)`, reduce stock, forward remainder. **Dry-run `canDispense` before debiting the account.**
- **Validation-before-commit (the money invariant):** check (1) account balance, (2) ATM inventory / `canDispense`, (3) optional daily limit — *then* debit; if hardware dispense fails → **credit back / reverse** (see awesome-lld `withdrawCash` try/catch).
- **PIN security:** max 3 attempts → lock/retain card → reset to Idle. Keep attempt counter on session/state, not sprinkled through ATM methods.
- **Session model:** one physical ATM → one active card/session; card stays until cancel/eject; cancel anytime → eject + Idle.
- **Concurrency:** physical ATM is usually single-user (session lock), but **BankService accounts** and **CashDispenser inventory** must be thread-safe if you claim concurrent ATMs or admin refill mid-session — `synchronized` withdraw/deposit on `Account`, `synchronized` dispense/`canDispense` on dispenser, `ConcurrentHashMap` for accounts (awesome-lld pattern).
- **Money units:** prefer integer minor units (cents/paise) in production; demos often use `int` dollars — never rely on `double` equality for cash math in serious answers.
- **SOLID signal:** OCP = new state / denomination / transaction type without editing `ATM`; SRP = state owns transitions, dispenser owns notes, bank owns balances; DIP = depend on `ATMState` / `DispenseChain` / `BankService` abstractions.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~30–40 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** authenticate via card + PIN; balance inquiry; cash withdrawal (check balance + ATM cash); cash deposit; eject/cancel ends session.
- **FR (common extensions — ask):** transfer; mini-statement; PIN change; daily withdrawal limit; operator refill; receipt print; Checking vs Savings selection.
- **NFR:** correct state transitions; no debit without successful dispense (or auto-reversal); thread-safe account + inventory; extensible states/denominations/txns; working demo / CLI.
- **Assumptions to state:** e.g. one customer at a time per machine; fixed denominations; bank simulated in-memory; no multi-currency unless asked.
- **Use cases:** Customer inserts card → enters PIN → withdraws cash → takes card; wrong PIN ×3 → card blocked; ATM out of notes → refuse withdrawal, allow balance; Operator refills cassettes.

### 2. Back-of-envelope estimation (usually light for LLD)
- Single machine: inventory is tens–thousands of notes — in-memory maps fine.
- If interviewer pushes “fleet of ATMs”: each ATM is a process with local cash inventory; bank is the shared consistency boundary (not the ATM’s in-memory `Account` map).

### 3. API / interface
```
// Session / State-delegated surface
void insertCard(String cardNumber)
void enterPin(String pin)
void selectOperation(OperationType op, int... args)  // WITHDRAW, DEPOSIT, BALANCE
void ejectCard()

// Internals the Authenticated state / ATM use
boolean authenticate(Card, pin) → bool
double checkBalance()
void withdrawCash(int amount)   // canDispense → debit → dispense (reverse on fail)
void depositCash(int amount)

// Dispenser
boolean canDispense(int amount)
void dispense(int amount)
```

### 4. Data model / class diagram
```
ATMSystem / ATM                    // Facade + State context (+ optional Singleton)
 - currentState: ATMState
 - currentCard: Card?
 - bankService: BankService
 - cashDispenser: CashDispenser
 + insertCard / enterPin / selectOperation / ejectCard   // delegate to state
 + changeState(ATMState)

ATMState <<interface>>
 + insertCard(atm, cardNumber)
 + enterPin(atm, pin)
 + selectOperation(atm, op, args)
 + ejectCard(atm)
 └─ IdleState | HasCardState | AuthenticatedState | (OutOfServiceState)

CashDispenser
 - chain: DispenseChain
 + canDispense(amount) / dispense(amount)   // synchronized

DispenseChain <<interface>>
 └─ NoteDispenser (abstract) → NoteDispenser100 / 50 / 20 / ...

BankService
 - accounts: ConcurrentHashMap
 - cards: ConcurrentHashMap
 + authenticate / getBalance / withdrawMoney / depositMoney

Card (number, pin) ──linked──► Account (number, balance)  // synchronized debit/credit
Transaction <|-- WithdrawalTransaction | DepositTransaction | BalanceInquiry   // optional Command
```
Canonical diagram: [atm-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/atm-class-diagram.png).

### 5. High-level architecture / component breakdown
```
CardReader / Keypad / Screen
        │ user events
        ▼
   ATM (Facade + State context)
        │ delegates
        ├─► ATMState (Idle / HasCard / Authenticated / ...)
        ├─► BankService  (PIN, balance, debit/credit)
        └─► CashDispenser ──► NoteDispenser chain (COR)
```
- **ATM:** orchestration only — no giant if/else on state.
- **States:** own what is legal now and which transition fires next.
- **BankService:** authority for money movement (simulated network).
- **Dispenser:** physical cash constraint separate from account balance.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Enum FSM vs State pattern classes:** enum + switch is faster to code; State classes win OCP when interviewers add Maintenance / CardBlocked / OutOfCash. Prefer State in OOD rounds (same lesson as vending machine).
2. **Greedy COR vs DP for notes:** greedy largest-first matches interview demos and canonical denominations; mention DP / alternate strategies if denominations are awkward or “minimize note count under stock constraints” is probed.
3. **Debit-then-dispense vs dispense-then-debit:** industry ATM flows debit (or hold) then dispense; **must reverse on hardware failure**. Never leave “debited but no cash” without a recovery path.
4. **Singleton ATM:** OK for one physical machine demo; prefer DI for tests / multi-ATM fleets.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = **canDispense + debit + dispense** under contention → synchronize dispenser; per-account locks for balances; don’t lock the whole bank for unrelated accounts.
- Cassette empty / partial dispense → dry-run first; fail closed (no debit) rather than partial silent dispense unless product asks for partial.
- Fleet scale (only if asked): ATM is a thin client; bank/switch owns ledger; local inventory is eventually reconciled via operator + settlement logs.
- Optional product stretch: EMV/chip, biometric, contactless, multi-currency — keep as strategy/hardware ports, don’t implement mid-round.

**Timed drill:** code Idle → HasCard → Authenticated + withdraw with COR dispenser + reversal-on-fail in 60–75 min; then add PIN lockout and `OutOfServiceState`.

## Common follow-ups / gotchas
- “Withdraw before PIN?” — State rejects; only Authenticated (or PINEntered) allows txns.
- “3 wrong PINs?” — lock card / retain; reset attempts on success; transition to Idle after eject.
- “ATM has balance but wrong denominations (e.g. need $30 with only $20s)?” — `canDispense` fails even if total cash ≥ amount; don’t debit.
- “Dispense hardware jammed after debit?” — reverse credit + error screen; log for operator; don’t eject until safe (senior probe: card retention ordering).
- “Add ₹200 notes / new txn type?” — new `NoteDispenser` link in chain / new `Transaction` + operation enum; no edit to IdleState.
- “Two ATMs, same account?” — bank-side locking / optimistic balance check; local `synchronized` on one ATM’s demo map is not enough for a real fleet.
- Gotcha: god-class `ATM` with nested if (state) × if (op) — State pattern is the expected fix.
- Gotcha: using `double` for cash and claiming precision; or skipping dry-run and overdrafting the cassette.

## Where it appears
- **Campus / machine-coding (Flipkart, Uber, Swiggy, Amazon new-grad, Indian product cos):** common “design + code in 90 min” — working State FSM + withdraw/deposit beats a half-finished pattern zoo.
- **Fintech / payments / banks (Paytm, PhonePe, Razorpay, Visa, GS/JPM-style loops):** especially frequent; expect PIN lockout, atomic debit/dispense, and denomination COR probes.
- **Experienced LLD (FAANG / Atlassian / Microsoft):** same core, deeper concurrency + failure-reversal + extensibility; often paired mentally with vending machine (State) and parking lot (Strategy/Facade).
- **Frequency:** top-tier canonical LLD problem — treat as the **State + COR** showcase after you’ve done parking lot and vending machine.
