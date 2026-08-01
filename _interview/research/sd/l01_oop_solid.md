# L01 — OOP & SOLID principles

**Interview relevance:** High — the vocabulary and judgment bar for every LLD / machine-coding round (campus + experienced); Flipkart, Uber, Swiggy, Amazon, Atlassian, and most Indian product cos grill class design against these before patterns.
**Type:** LLD-fundamental
**Prereqs:** None — start of the LLD track; do this before design patterns and parking-lot / Splitwise-style questions

## Read / watch (curated, in order)
- [ ] [Object-Oriented Programming Concepts (Oracle Java Tutorials)](https://docs.oracle.com/javase/tutorial/java/concepts/) — `Oracle` — objects, classes, inheritance, interfaces, packages; pair with [inheritance](https://docs.oracle.com/javase/tutorial/java/concepts/inheritance.html), [interfaces](https://docs.oracle.com/javase/tutorial/java/concepts/interface.html), [polymorphism](https://docs.oracle.com/javase/tutorial/java/IandI/polymorphism.html), [access control](https://docs.oracle.com/javase/tutorial/java/javaOO/accesscontrol.html)
- [ ] [Encapsulation](https://algomaster.io/learn/lld/encapsulation) / [Abstraction](https://algomaster.io/learn/lld/abstraction) / [Inheritance](https://algomaster.io/learn/lld/inheritance) / [Polymorphism](https://algomaster.io/learn/lld/polymorphism) / [Interfaces](https://algomaster.io/learn/lld/interfaces) — `algomaster` (via [awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)) — interview-depth OOP pillars with LLD-shaped examples
- [ ] [OOP code READMEs (Java)](https://github.com/ashishps1/awesome-low-level-design/tree/main/oop) — `awesome-low-level-design` — runnable multi-language drills; start with [encapsulation](https://github.com/ashishps1/awesome-low-level-design/blob/main/oop/java/encapsulation/README.md), [inheritance](https://github.com/ashishps1/awesome-low-level-design/blob/main/oop/java/inheritance/README.md), [polymorphism](https://github.com/ashishps1/awesome-low-level-design/blob/main/oop/java/polymorphism/README.md), [abstraction](https://github.com/ashishps1/awesome-low-level-design/blob/main/oop/java/abstraction/README.md)
- [ ] [Replace Inheritance with Delegation](https://refactoring.guru/replace-inheritance-with-delegation) — `Refactoring.Guru` — when “is-a” is fake; composition fixes LSP violations and unused inherited APIs
- [ ] [The S.O.L.I.D Principles in Pictures](https://medium.com/backticks-tildes/the-s-o-l-i-d-principles-in-pictures-b34ce2f1e898) — `awesome-low-level-design` curated — 5-min visual map of each letter’s *goal* before code
- [ ] [S.O.L.I.D Principles Explained With Code](https://blog.algomaster.io/p/solid-principles-explained-with-code) — `algomaster` — before/after code for SRP → DIP in LLD voice
- [ ] [A Solid Guide to SOLID Principles](https://www.baeldung.com/solid-principles) — `Baeldung` — Java walkthrough with classic violations (fat interfaces, electric-car/`turnOnEngine`, constructor `new` coupling)
- [ ] [Single Responsibility Principle (Uncle Bob)](https://blog.cleancoder.com/uncle-bob/2014/05/08/SingleReponsibilityPrinciple.html) — `Clean Coder` — SRP = one reason to change ≈ one *actor*/stakeholder, not “one method”
- [ ] [The Open Closed Principle (Uncle Bob)](https://blog.cleancoder.com/uncle-bob/2014/05/12/TheOpenClosedPrinciple.html) — `Clean Coder` — extend via plugins/abstractions; don’t reopen stable policy for every feature
- [ ] [Dive Into Design Patterns — free demo PDF (SOLID chapters)](https://refactoring.guru/files/design-patterns-en-demo.pdf) — `Refactoring.Guru` — free excerpt covering encapsulate-what-varies, program-to-interface, composition-over-inheritance, then all five SOLID letters ([full book](https://refactoring.guru/design-patterns/book) if you want the rest)
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) — `Refactoring.Guru` — OCP + composition in one pattern; how LLD swaps pricing/payment/fare rules without `if`-ladders
- [ ] [DRY](https://algomaster.io/learn/lld/dry) / [KISS](https://algomaster.io/learn/lld/kiss) / [YAGNI](https://algomaster.io/learn/lld/yagni) — `algomaster` — stop over-applying SOLID/patterns when a simpler design ships the mandatory requirements
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → design for extensibility → working demo; Flipkart/Uber/Swiggy-style LLD
- [ ] [awesome-low-level-design (hub)](https://github.com/ashishps1/awesome-low-level-design) — `awesome-low-level-design` — curated OOP → SOLID → patterns → problem list; next stop after this module
- [ ] [low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — question + solution index to practice once OOP/SOLID stick
- [ ] [SOLID (Wikipedia)](https://en.wikipedia.org/wiki/SOLID) — `reference` — crisp definitions + history (Martin / Feathers) for quick recall

## Core concepts to master
- **Four pillars:** **Encapsulation** (hide state; expose validated operations), **Abstraction** (show *what*, hide *how*), **Inheritance** (share *is-a* contracts carefully), **Polymorphism** (one interface, many behaviors — the engine of extensible LLD).
- Prefer **composition / HAS-A** over deep inheritance; inherit for true subtype contracts, compose for reusable behavior (Strategy, pricing engines, payment gateways).
- **SRP:** a class should have one reason to change (often one business actor). God classes (`ParkingLot` that also bills, notifies, and persists) fail LLD reviews.
- **OCP:** open for extension, closed for modification — add a new vehicle/fare/payment type via new class + polymorphism, not another `switch` branch in stable code.
- **LSP:** subtypes must honor the base contract; throwing `UnsupportedOperationException` or weakening preconditions (Square/`Rectangle`, Bicycle/`startEngine`) is an inheritance smell → redesign the hierarchy.
- **ISP:** don’t force clients onto fat interfaces; split by role (`Parkable` vs `Chargeable`) so implementers aren’t stubbing unused methods.
- **DIP:** high-level policy depends on abstractions, not concretions — inject `PaymentGateway`, don’t `new StripeClient()` inside the service (also unlocks testing).
- Supporting heuristics: **DRY** (don’t copy domain rules), **KISS** / **YAGNI** (in a 90-min machine-coding round, a working SRP/OCP design beats a half-finished pattern zoo).
- Interview signal: name the principle when you choose an interface, inject a dependency, or refuse a bad inheritance — then keep coding toward a runnable demo.

## Practice — how it's asked & how to attack it
1. **Drill — pillars in one sentence each:** For a `BankAccount`, point to encapsulation (private balance + `withdraw`), abstraction (`Account` API), inheritance vs composition choice, and polymorphism (Savings vs Current interest).
2. **Drill — SRP smell test:** Given a `UserManager` that authenticates, updates profile, and sends email — split into classes and state each one’s single reason to change.
3. **Drill — OCP without rewriting:** Start with `PriceCalculator` using `if (type == ...)`. Refactor to a `PricingStrategy` (or shape/`area`) hierarchy so a new type needs **zero** edits to the calculator.
4. **Drill — LSP failure:** Design `Bird` with `fly()`, then add `Penguin`. Fix the model (separate `FlyingBird` / capability interfaces) and explain why the first hierarchy lied.
5. **Drill — ISP + DIP together:** Fat `Machine` with print/scan/fax → segregate; then make a `DocumentService` depend on `Printer` abstraction injected at construction, not a concrete `HpPrinter`.
6. **Drill — machine-coding checklist:** Pick any tiny system (vending machine / parking spot allocator). Spend 10 minutes listing entities, IS-A vs HAS-A, and which SOLID moves you’ll use; only then code a working happy path.

## Common follow-ups / gotchas
- “Isn’t SRP just ‘small classes’?” — No; it’s **one axis of change**. A cohesive 200-line domain class can be fine; a 50-line class with two stakeholders is not.
- “Why not inherit everything for reuse?” — Inheritance couples you to parent APIs and often violates LSP; composition + delegation reuses behavior without fake *is-a*.
- “Does every new feature need a new interface?” — No. Apply OCP/DIP where change is likely (payment, pricing, vehicle type); YAGNI elsewhere in a timed round.
- “ElectricCar implements Car but throws on `turnOnEngine`” — classic LSP fail; redesign the abstraction (e.g. `start()` / capability interfaces).
- “Where do patterns fit?” — Patterns are *applications* of SOLID (Strategy ≈ OCP+composition; DI ≈ DIP). Don’t name a pattern you didn’t need.
- “Working code vs perfect SOLID?” — Mandatory requirements + clean core model win; call out follow-up refactors you’d do with more time.

## Where it appears
- **Campus / new-grad:** almost every LLD or machine-coding round opens with OOP pillars + “apply SOLID”; Flipkart, Uber, Swiggy, Amazon, Razorpay, Atlassian-style loops expect it before patterns.
- **Experienced / mid-level:** less “define SRP,” more “why this interface / why not inherit”; still the grading rubric for parking lot, Splitwise, elevator, booking, and game designs.
- **Frequency:** foundational for **all** LLD questions; explicit SOLID quizzes are common early in Indian product-company loops and as follow-ups during code review of your machine-coding solution.
