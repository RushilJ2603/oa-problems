# LQ05 — Design a Vending Machine

**Interview relevance:** High — the textbook State-pattern LLD / machine-coding question (campus + experienced); Amazon, Microsoft, Google, Walmart, and Indian product cos use it to probe FSM modeling, inventory + change logic, and concurrency.
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Singleton), l03_patterns_structural (Facade); State / Strategy / Observer from behavioral patterns (or Refactoring.Guru links below)

## Read / watch (curated, in order)
- [ ] [Designing a Vending Machine (problem + UML + multi-lang code)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/vending-machine.md) — `awesome-low-level-design` — **start here:** requirements, [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/vendingmachine-class-diagram.png), Singleton + State notes; hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Java vending-machine solution (Idle / HasMoney / ItemSelected / Dispensing)](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/vendingmachine) — `awesome-low-level-design` — runnable reference: `VendingMachine` delegates to `VendingMachineState`; also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/vendingmachine)
- [ ] [State](https://refactoring.guru/design-patterns/state) — `Refactoring.Guru` — **the pattern this problem exists to test**; contrast with Strategy (states know transitions; strategies don’t)
- [ ] [Finite-state machine (overview)](https://en.wikipedia.org/wiki/Finite-state_machine) — `Wikipedia` — draw the state diagram *before* classes; interviewers grade this step
- [ ] [Getting Ready: Vending Machine (Grokking LLD / Educative)](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/getting-ready-vending-machine) — `Educative / Grokking OOD` — clarifying questions on states + money handling; course hub: [Grokking the Low Level Design Interview Using OOD Principles](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles)
- [ ] [Design Patterns — State machine (vending example)](https://www.hellointerview.com/learn/low-level-design/in-a-hurry/patterns) — `Hello Interview` — short “when you see ‘state’ in requirements, use State pattern” framing with a vending snippet
- [ ] [Design a Vending Machine System (LLD) | State Pattern | Class Diagram](https://www.youtube.com/watch?v=FPZXPXrCdn8) — `YouTube` — end-to-end interview walkthrough: requirements → actors → states → UML → Java code
- [ ] [Vending Machine design — A State design pattern approach](https://medium.com/swlh/vending-machine-design-a-state-design-pattern-approach-5b7e1a026cd2) — `Medium / The Startup` — real interview narrative: naive god-class → SOLID fail → State refactor (Animesh Gaitonde)
- [ ] [How to use State Design Pattern in Java? Vending Machine Example](https://javarevisited.blogspot.com/2021/07/state-design-pattern-example-java-vending-machine.html) — `JavaVisited` — Idle / Processing / Sold / SoldOut + change + `NotSufficientChangeException`; pair with the earlier non-pattern [Design a Vending Machine in Java](https://javarevisited.blogspot.com/2016/06/design-vending-machine-in-java.html)
- [ ] [Low-Level Design: Vending Machine (OOP Design Interview)](https://www.techinterview.org/post/3233463566/low-level-design-vending-machine/) — `techinterview` — full Python sketch: `CashBox` greedy change, cents-only money, cancel/refund paths
- [ ] [LLD Case Study: Vending Machine](https://www.calibreos.com/learn/lld-vending-machine) — `CalibreOS` — clarifying questions + slot-based inventory vs product buckets; E4/E5 bar (EXACT_CHANGE_ONLY, integer cents, Strategy payment)
- [ ] [Vending Machine · LLD-flavoured](https://ikshitij.com/learn/lld-object-oriented/vending-machine/) — `ikshitij` — state diagram with jam/refund paths + Java State sketch + patterns (State / Strategy / Observer)
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) / [Singleton](https://refactoring.guru/design-patterns/singleton) / [Facade](https://refactoring.guru/design-patterns/facade) / [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — payment/change algorithms, one physical machine, public API facade, display / low-stock alerts
- [ ] [Change-making problem](https://en.wikipedia.org/wiki/Change-making_problem) — `Wikipedia` — greedy vs DP follow-up (canonical US coins vs arbitrary denominations)
- [ ] [Designing a Coffee Vending Machine](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/coffee-vending-machine.md) — `awesome-low-level-design` — sibling: recipes + ingredient inventory + concurrent dispense (stretch after snacks VM)
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [LLD:13-Vending Machine System](https://dev.to/_noob/lld12-vending-machine-system-4n65) — `DEV` — minimal Java State demo (Idle / HasMoney / Dispensing / OutOfStock) if you want a 5-min mental model
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after you can code the happy path

## Core concepts to master
- **Clarify before coding:** select-then-pay vs pay-then-select? coins only or notes/card/UPI? exact-change-only when hopper is low? slot codes (A1) vs product ids? cancel/refund anytime before dispense? admin restock / collect cash?
- **Draw the FSM first:** typical happy path `Idle → HasMoney (or ItemSelected) → Dispensing → Idle`. Invalid actions in a state must no-op / error / refund — never silently corrupt balance.
- **Core entities:** `VendingMachine` (context + Facade) → `VendingMachineState` hierarchy; `Inventory` / `Slot` + `Product`/`Item`; `CashBox`/`CoinVault` (inserted session + reserve for change); optional `PaymentStrategy`, `Display` (Observer), admin API.
- **State is the star pattern:** each state implements `insertCoin` / `selectItem` / `dispense` / `refund` (or cancel). Transitions live *inside* states via `machine.setState(...)`. Adding `Maintenance` / `ExactChangeOnly` should not edit a giant `switch` in `VendingMachine`.
- **State vs Strategy:** State = behavior that changes with internal mode *and* triggers the next mode; Strategy = interchangeable algorithm (change-making, card vs cash) unaware of sibling strategies.
- **Money = integer cents (or paise):** never `double`/`float` for prices or balance. Denominations as enums (`Coin.QUARTER = 25`).
- **Change-making:** greedy largest-first against *available hopper counts*; if exact change impossible → abort sale, refund full insert (or enter EXACT_CHANGE_ONLY). Mention DP is optimal for non-canonical denomination sets ([change-making problem](https://en.wikipedia.org/wiki/Change-making_problem)).
- **Inventory model:** prefer **slot-based** (`slotId → product + qty + capacity`) over a flat product→qty map — restock fills physical slots; same SKU can span multiple slots.
- **Transaction atomicity:** validate stock *and* `canMakeChange(deposit - price)` *before* decrementing inventory / committing coins. Dispense failure → full refund + lock slot (senior probe).
- **Concurrency:** one physical machine usually serializes customer sessions with a single transaction lock; still protect stock decrement + cash vault (read-calculate-commit) so admin restock / multi-UI can’t double-vend. Prefer fine-grained locks or `ConcurrentHashMap` for stock maps if you claim concurrent requests.
- **Singleton justification:** one process ↔ one physical machine is a reasonable Singleton; prefer DI for tests. Don’t cargo-cult it for multi-machine fleets.
- **SOLID signal:** OCP = new state / payment / change algo without editing `VendingMachine`; SRP = state owns transitions, vault owns change, inventory owns stock; DIP = depend on `VendingMachineState` / `PaymentStrategy` abstractions.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~30–40 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** multi-product inventory with prices/qty; accept coins (and often notes); select product; dispense + return change; reject insufficient funds / out-of-stock; cancel → refund.
- **FR (common extensions — ask):** card/UPI; EXACT_CHANGE_ONLY mode; admin restock + collect cash; display board / low-stock alert; product jam → full refund + lock slot.
- **NFR:** correct state transitions (no charge without dispense); thread-safe stock/cash if concurrent; extensible payment + states; money as integer minor units; working demo / CLI.
- **Assumptions to state:** e.g. one transaction at a time per machine; US/INR canonical denominations (greedy OK); no networked fleet unless asked.
- **Use cases:** Customer inserts money → selects slot → gets item + change; Customer cancels → full refund; Admin restocks slots / empties cash box; Machine refuses sale when change unavailable.

### 2. Back-of-envelope estimation (usually light for LLD)
- Spot/SKU count is tiny (tens of slots). In-memory maps fine.
- If interviewer pushes “scale”: fleet of N machines → per-machine local cash + local FSM; remote inventory sync is HLD (don’t derail the OOD round).

### 3. API / interface
```
// Customer
void insertCoin(Coin coin) / insertNote(Note note)
void selectItem(String slotOrCode)
void dispense()                 // or auto-dispense when paid enough
Map<Coin,Integer> refund() / cancel()
List<ProductView> display()

// Admin
void restock(String code, int qty)
int collectCash()
void setExactChangeOnly(boolean)
```
OOD method surface (awesome-LLD-shaped):
```
VendingMachine.insertCoin(Coin) / selectItem(code) / dispense() / refund()
VendingMachineState.insertCoin / selectItem / dispense / refund   // per state
Inventory.isAvailable(code) / reduceStock(code) / addItem(...)
CashBox.insert / canMakeChange(amount) / makeChange(amount) / refundSession()
```

### 4. Data model / class diagram
```
VendingMachine (Facade, optional Singleton)
  - state: VendingMachineState
  - inventory: Inventory
  - cashBox: CashBox
  - balance / selectedCode / session
  + insertCoin / selectItem / dispense / refund / setState

VendingMachineState <<abstract/interface>>
  └─ IdleState | HasMoneyState | ItemSelectedState | DispensingState
     (+ ExactChangeOnlyState | OutOfStock/Maintenance — optional)

Inventory 1──* Slot/Item (code, product, qty)
Product / Item (code, name, priceCents)
Coin / Note  <<enum>>  (valueCents)
CashBox (reserve: Map<Coin,int>, sessionInserted)
PaymentStrategy <<interface>> → CashPayment | CardPayment   (optional)
Display ──observes──> VendingMachine / Inventory            (optional)
```
Canonical diagram: [vendingmachine-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/vendingmachine-class-diagram.png). Actual Java states in awesome-LLD: `IdleState`, `HasMoneyState`, `ItemSelectedState`, `DispensingState`.

### 5. High-level architecture / component breakdown
```
Customer / Admin UI
        │
        ▼
 VendingMachine (Facade)  ──delegates──►  current VendingMachineState
        │                                      │ setState(...)
        ├── Inventory (slots / stock)
        ├── CashBox (session + change reserve)
        └── Display observers (optional)
```
- **VendingMachine:** holds session fields; public API only; no giant if/else on state enum.
- **States:** own legal operations + transitions; invalid ops print/throw and stay put (or refund).
- **Inventory / CashBox:** domain rules; synchronized on mutate paths under concurrency.
- **Strategies:** swap payment or change algorithm without touching FSM.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Enum FSM vs State pattern classes:** enum + switch is faster to code; State classes win OCP when interviewers add Maintenance / ExactChangeOnly / Jam. Prefer State classes in OOD rounds.
2. **Select-then-pay vs pay-then-select:** both valid — pick one, draw transitions consistently, and reject the other order in Idle/HasMoney.
3. **Greedy vs DP change:** greedy for canonical coin systems; mention DP ([change-making](https://en.wikipedia.org/wiki/Change-making_problem)) when denominations are arbitrary or hopper constraints break greediness.
4. **Singleton VendingMachine:** OK for one physical device; say you’d inject for unit tests / multi-machine simulators.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = **commit transaction** (stock −1 + vault update + change) → one critical section per machine; don’t hold the lock during card network I/O (authorize async, then commit).
- Change hopper exhaustion → flip ExactChangeOnly (Observer can light the LED) rather than failing mid-dispense.
- Optional product stretch (only if asked): coffee recipes / ingredients (see [coffee-vending-machine](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/coffee-vending-machine.md)), fleet telemetry — keep as Strategy/Observer hooks.

**Timed drill:** implement Idle → pay → select → dispense → change in 45–60 min with State classes; then add cancel/refund and a `canMakeChange` pre-check.

## Common follow-ups / gotchas
- “Can I select before inserting money?” — product rule; either allow `ItemSelected` then accept coins, or reject until `HasMoney`. State it explicitly.
- “Machine can’t make change?” — pre-check `canMakeChange`; refund all; optional `ExactChangeOnlyState`.
- “Dispense motor jams after payment?” — full refund (not just change), lock slot, journal the failure; never leave money taken with no item.
- “Two users / concurrent requests?” — serialize one session lock; atomic stock decrement so two selects can’t vend the last unit twice.
- “Add card / UPI?” — `PaymentStrategy`; cashless path often skips change and collapses HasMoney self-loops.
- “Admin restock while a sale is in progress?” — restock only in Idle/Maintenance, or lock inventory mutations against the active transaction.
- Gotcha: god-class `VendingMachine` with nested `if (state == …)` — interviewer docks the State-pattern signal.
- Gotcha: using `double` for money or forgetting to restore hopper coins when change fails mid-calculation.

## Where it appears
- **Campus / machine-coding (Flipkart, Uber, Swiggy, Amazon new-grad, Indian product cos):** common “design + code in 90 min” — working FSM + change + inventory beats a half-finished pattern zoo.
- **Experienced LLD (Amazon / Microsoft / Google / Walmart):** same core; deeper probes on ExactChangeOnly, jam/refund, integer money, Strategy payment, concurrency on stock/vault.
- **Frequency:** among the top canonical LLD problems (with parking lot, elevator, ATM, Tic-Tac-Toe) — treat it as the **State-pattern template** for every later FSM question (ATM, traffic light, document workflow).
