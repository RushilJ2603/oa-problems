# L04 — Design Patterns: Behavioral (Strategy, Observer, State, Command, Iterator)

**Interview relevance:** High — LLD / machine-coding rounds lean hardest on Strategy + Observer + State (pricing, notifications, elevator/vending/order lifecycles); Command for undo/remote; Iterator rarely named but expected via collection traversal.
**Type:** LLD-fundamental
**Prereqs:** OOP & SOLID (L01) — especially OCP + composition over inheritance; Creational patterns (L02); Structural patterns (L03) helpful for Adapter/Decorator contrast

## Read / watch (curated, in order)
- [ ] [Behavioral Design Patterns (overview)](https://refactoring.guru/design-patterns/behavioral-patterns) — `Refactoring.Guru` — map of all GoF behavioral patterns; what “algorithms + responsibility assignment” means
- [ ] [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) — `awesome-low-level-design` — LLD sheet index; behavioral pattern links + problem list to practice after this module
- [ ] [Design Patterns (in a hurry)](https://www.hellointerview.com/learn/low-level-design/in-a-hurry/patterns) — `Hello Interview` — interview-realistic take: Strategy/Observer/State Machine as the ones that actually show up; when *not* to force a pattern
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) — `Refactoring.Guru` — family of interchangeable algorithms; Context + Strategy interface; route-planning / payment examples
- [ ] [Strategy (LLD)](https://algomaster.io/learn/lld/strategy) — `AlgoMaster` / awesome-LLD — shipping-cost strategies; swap at runtime without touching the context
- [ ] [Strategy Pattern – Design Patterns (ep 1)](https://www.youtube.com/watch?v=v9ejT8FO-7I) — `YouTube` / Christopher Okhravi — Head First ducks → composition; best first video for Strategy
- [ ] [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — Subject/Publisher + subscribe/unsubscribe/notify; one-to-many dependency
- [ ] [Observer (LLD)](https://algomaster.io/learn/lld/observer) — `AlgoMaster` — fitness-data subject with loose-coupled displays/loggers; attach/detach at runtime
- [ ] [Observer Pattern – Design Patterns (ep 2)](https://www.youtube.com/watch?v=_BpmfnqjgzQ) — `YouTube` / Christopher Okhravi — weather station; push vs pull updates
- [ ] [State](https://refactoring.guru/design-patterns/state) — `Refactoring.Guru` — behavior changes with internal state; states may trigger transitions on the context
- [ ] [State (LLD)](https://algomaster.io/learn/lld/state) — `AlgoMaster` — vending machine + document workflow; kill the giant switch
- [ ] [Replace Type Code with State/Strategy](https://refactoring.guru/replace-type-code-with-state-strategy) — `Refactoring.Guru` — the interview discriminator: algorithm variants → Strategy; whole-object condition + transitions → State
- [ ] [State Pattern – Design Patterns (ep 17)](https://www.youtube.com/watch?v=N12L5D78MAA) — `YouTube` / Christopher Okhravi — deep State walkthrough after you’ve read Strategy
- [ ] [Command](https://refactoring.guru/design-patterns/command) — `Refactoring.Guru` — request as object; invoker/receiver; queue, log, undo/redo
- [ ] [Command (LLD)](https://algomaster.io/learn/lld/command) — `AlgoMaster` — remote control + text editor undo/redo history stack
- [ ] [Command Pattern – Design Patterns (ep 7)](https://www.youtube.com/watch?v=9qA5kw8dcSU) — `YouTube` / Christopher Okhravi — encapsulate actions; macro commands; undo
- [ ] [Iterator](https://refactoring.guru/design-patterns/iterator) — `Refactoring.Guru` — traverse without exposing representation; multiple independent cursors
- [ ] [Iterator (LLD)](https://algomaster.io/learn/lld/iterator) — `AlgoMaster` — playlist / filtered notification iterators; same client loop, different traversal
- [ ] [Iterator Pattern – Design Patterns (ep 16)](https://www.youtube.com/watch?v=uNTNEfwYXhI) — `YouTube` / Christopher Okhravi — Aggregate + Iterator; encapsulation of traversal
- [ ] [Behavioral Patterns in Core Java](https://www.baeldung.com/java-behavioral-patterns-jdk) — `Baeldung` — where these already live in the JDK (`Comparator`, `Iterator`, listeners, `Runnable`/tasks)
- [ ] [Design Patterns playlist (Okhravi)](https://www.youtube.com/playlist?list=PLrhzvIcii6GNjpARdnO4ueTUAVR9eMBpc) — `YouTube` — full Head First–aligned series if you want every GoF pattern after this module

## Core concepts to master
- **Behavioral patterns** answer *how objects collaborate* — algorithms, event notification, lifecycle transitions, request encapsulation, and traversal — without hard-wiring every caller to every callee.
- **Strategy:** extract varying algorithms behind a common interface; Context holds a Strategy and delegates. Client (or factory) chooses/swaps the strategy. Classic: payment methods, fare/pricing, sorting/compression, route modes. Prefer composition over `if (type == …)` switches (OCP).
- **Observer (pub/sub lite):** Subject maintains observer list; `attach` / `detach` / `notify`. Subject depends only on the Observer interface. Know **push** (event carries data) vs **pull** (observers query subject). Don’t confuse with Mediator (hub for many-to-many) or Message Queues (distributed async).
- **State:** Context delegates to a current State object; each state implements the same action interface differently and may call `context.setState(...)`. Models FSMs: elevator, vending machine, order/document lifecycle, media player. States often know about sibling states; Strategies almost never do.
- **State vs Strategy (high-frequency follow-up):** Same shape (composition + interface). Strategy = interchangeable ways to do *one* job, chosen by the client, strategies unaware of each other. State = behavior *is* the object’s mode; transitions are domain rules, often initiated by states themselves. See [Replace Type Code with State/Strategy](https://refactoring.guru/replace-type-code-with-state-strategy).
- **Command:** wrap a request (method + args + receiver) as an object with `execute()` (and often `undo()`). Invoker triggers commands without knowing receivers. Enables undo/redo stacks, macros, queuing, logging, remote execution. Differs from Strategy: Command is *an action to perform* (often once, with history); Strategy is *how* to do an ongoing algorithm.
- **Iterator:** separate traversal from storage. Collection exposes `createIterator()`; client uses `hasNext()` / `next()` (or language `for-each` / `Iterable`). Supports multiple independent cursors and alternate traversals (forward, filtered) without leaking internals. Language iterators (Java `Iterator`, C++ STL, JS `Symbol.iterator`) are this pattern baked in.
- **Pick order in interviews:** Strategy when behavior variants share one interface; Observer when many components must react to one change; State when valid operations depend on lifecycle mode; Command when you need undo/queue/decouple UI from actions; Iterator when hiding collection shape or offering custom walks.
- **Modern shorthand:** Strategy ≈ injectable policy / function object / `Comparator`; Observer ≈ event listeners / reactive streams; Command ≈ task / runnable / undo stack; Iterator ≈ language iteration protocols. Name the pattern when it clarifies design; don’t cargo-cult classes for one variant.

## Practice — how it's asked & how to attack it
1. **Drill — name the pattern:** One sentence each: (a) fare calculation Card/UPI/Wallet, (b) stock tick updates multiple displays, (c) elevator Idle/Moving/DoorOpen, (d) text-editor undo/redo, (e) walk a tree of files without exposing nodes.
2. **Drill — Strategy whiteboard:** Design `PaymentService` with `PaymentStrategy`. Show how adding NetBanking needs a new class only. Then replace Strategy objects with a Java `Function`/`Comparator`-style lambda and say when the interface is still worth it.
3. **Drill — Observer push vs pull:** Sketch `OrderSubject` notifying Inventory, Email, Analytics. Implement once with push (`update(OrderEvent e)`) and once with pull (`update()` then `getState()`). State one concurrency hazard (notify while iterating; copy-on-write / snapshot the list).
4. **Drill — State machine:** Vending machine: Idle → ItemSelected → HasMoney → Dispensing. Draw the transition table, then class-per-state. Show why `dispense()` in Idle is a no-op/error *inside* `IdleState`, not a giant switch in `VendingMachine`.
5. **Drill — Command undo:** `LightOnCommand` / `LightOffCommand` with invoker history stack. Implement undo as inverse ops, then mention Memento when inverse is hard (restore snapshot). Contrast with Strategy: why a “LightOnStrategy” would be the wrong story.
6. **Drill — LLD problem mapping:** Open [awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) (Parking Lot pricing, Elevator, Snake & Ladder, Logging, Splitwise). For each, list which of Strategy / Observer / State / Command you’d mention and where on the class diagram.

## Common follow-ups / gotchas
- “Strategy vs State?” — Same structure, different intent: client-selected algorithms vs self-driven lifecycle modes. Strategies don’t transition each other; states often do.
- “Strategy vs if/else?” — Two–three stable branches may stay as conditionals; reach for Strategy when variants grow, ship independently, or must swap at runtime.
- “Is Observer the same as Kafka/pub-sub?” — Same idea at process scale; in LLD, Observer is in-process Subject↔listeners. Say the distributed version when HLD follows.
- “Command vs Strategy?” — Command = request object (queue/undo/history); Strategy = pluggable algorithm for the same ongoing responsibility.
- “When is State overkill?” — Few states + rare transitions → enum + small switch is fine; explode into State classes when every method branches on state and transitions multiply.
- “Do I implement Iterator from scratch?” — Usually no in Java/C++/Python interviews; know the intent, use `Iterable`/`Iterator`, and custom iterators only for filtered/special traversals.

## Where it appears
- **Campus / new-grad LLD & machine coding (India product cos, FAANG new-grad):** Strategy and Observer are nearly mandatory vocabulary; State dominates elevator / vending / traffic-light / booking-lifecycle problems; Command shows up for undo or remote-control style prompts; Iterator is background knowledge.
- **Experienced / SDE-2 LLD:** expect State vs Strategy clarity, Observer vs event-bus tradeoffs, Command + undo with Memento, and restraint (don’t pattern-stamp every conditional).
- **Frequency:** among all GoF families, these five (especially Strategy/Observer/State) appear inside the largest share of canonical LLD problems — even when the round isn’t titled “design patterns.”
