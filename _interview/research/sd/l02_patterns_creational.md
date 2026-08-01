# L02 — Design Patterns: Creational (Singleton, Factory, Builder, Prototype)

**Interview relevance:** High — LLD / machine-coding rounds ask you to name and apply these when creating objects (parking lot vehicle types, notification channels, HTTP clients, game entities); Singleton + Factory come up most at campus; Builder/Prototype at mid-level product cos.
**Type:** LLD-fundamental
**Prereqs:** OOP fundamentals & SOLID (L01) — especially SRP, OCP, and “program to an interface”

## Read / watch (curated, in order)
- [ ] [Creational Design Patterns (overview)](https://refactoring.guru/design-patterns/creational-patterns) — `Refactoring.Guru` — map of all five creational GoF patterns and what “flexible object creation” means
- [ ] [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) — `awesome-low-level-design` — LLD sheet index; creational pattern links + problem list to practice after this module
- [ ] [Design Patterns (in a hurry)](https://www.hellointerview.com/learn/low-level-design/in-a-hurry/patterns) — `Hello Interview` — interview-realistic take: simple factory vs GoF Factory Method, when Builder/Singleton actually show up, and when *not* to force a pattern
- [ ] [Factory Comparison](https://refactoring.guru/design-patterns/factory-comparison) — `Refactoring.Guru` — clears the #1 interview confusion: creation method vs simple factory vs Factory Method vs Abstract Factory
- [ ] [Singleton](https://refactoring.guru/design-patterns/singleton) — `Refactoring.Guru` — intent, private ctor + `getInstance`, multithreaded double-check, SRP/testability cons
- [ ] [Singleton (LLD deep dive)](https://algomaster.io/learn/lld/singleton) — `AlgoMaster` / awesome-LLD — eager vs lazy, synchronized, double-checked locking, Bill Pugh holder, enum Singleton (Java)
- [ ] [Factory Method](https://refactoring.guru/design-patterns/factory-method) — `Refactoring.Guru` — Creator/Product, subclass chooses concrete type; logistics & cross-platform UI examples
- [ ] [Factory Method (LLD)](https://algomaster.io/learn/lld/factory-method) — `AlgoMaster` — simple factory → Factory Method evolution via notifications; OCP-friendly extension
- [ ] [Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory) — `Refactoring.Guru` — families of related products (GUI themes/OS widgets) without mixing variants
- [ ] [Abstract Factory (LLD)](https://algomaster.io/learn/lld/abstract-factory) — `AlgoMaster` — when one product type isn’t enough; matrix of product types × families
- [ ] [Builder](https://refactoring.guru/design-patterns/builder) — `Refactoring.Guru` — step-by-step construction, optional Director, vs telescoping constructors
- [ ] [Builder (LLD)](https://algomaster.io/learn/lld/builder) — `AlgoMaster` — fluent Java-style builder (HttpRequest), immutability, when Director helps
- [ ] [Prototype](https://refactoring.guru/design-patterns/prototype) — `Refactoring.Guru` — clone via interface; prototype registry; avoids subclass-per-config
- [ ] [Prototype (LLD)](https://algomaster.io/learn/lld/prototype) — `AlgoMaster` — shallow vs deep copy, game-enemy / email-template drills
- [ ] [Introduction to Creational Design Patterns](https://www.baeldung.com/creational-design-patterns) — `Baeldung` — compact Java walkthrough (Singleton holder, simple factory, Bloch-style Builder)
- [ ] [Creational Design Patterns in Java (Factory → Prototype)](https://www.youtube.com/watch?v=jdJW99i4qrE) — `YouTube` — full creational pass with interview-style contrasts in one sitting

## Core concepts to master
- **Creational patterns** control *how* objects are created so clients depend on abstractions, not `new ConcreteX()` everywhere — flexibility + reuse without scattering construction logic.
- **Singleton:** one instance + global access (`private` ctor + static `getInstance`). Prefer DI/shared instance passed in unless the domain truly needs a process-wide single resource (logger, config, connection pool). Hard to mock; violates SRP; needs care under concurrency.
- **Thread-safe Singleton (Java interview checklist):** naive lazy (broken under races) → synchronized `getInstance` → double-checked locking + `volatile` → Bill Pugh static holder → **enum Singleton** (serialization/reflection-safe). Eager init is simple if always needed.
- **Simple factory (not GoF):** one class/method with `if`/`switch` that returns a product interface. Common in LLD answers; intermediate step before Factory Method. Interviewers often say “factory” and mean this.
- **Factory Method (GoF):** Creator declares `createProduct()`; ConcreteCreators override to return ConcreteProducts. Client uses Product interface. Adds types via new subclasses (OCP) instead of editing a giant switch.
- **Abstract Factory:** factory of related factories — creates a *family* (Button+Checkbox matching a theme/OS). Use when products must stay consistent together; overkill for a single varying type.
- **Builder:** step-by-step construction for complex objects with many optional fields; kills telescoping constructors. Fluent builders (`withX().build()`) are interview gold; optional Director encodes named recipes (sports car, SUV).
- **Prototype:** create by **cloning** a configured instance via a `clone()`/`copy()` API — useful when construction is expensive or concrete class is unknown. Know **shallow vs deep** copy; registries return clones, never the live prototype.
- **Pick order in interviews:** start with simple factory / Factory Method when type varies at runtime; Builder when *configuration* is complex; Abstract Factory when *families* must match; Prototype when copy-from-template beats rebuild; Singleton last and only when truly global.
- **Relation cheat-sheet:** Factory Method often evolves into Abstract Factory / Builder / Prototype; Abstract Factories, Builders, and Prototypes can themselves be Singletons — don’t stack patterns without a reason.

## Practice — how it's asked & how to attack it
1. **Drill — name the pattern:** For each prompt, pick one creational pattern and justify in one sentence: (a) notification Email/SMS/Push, (b) HTTP request with 8 optional fields, (c) light/dark UI widget set, (d) spawn 100 similarly configured enemies, (e) app-wide logger.
2. **Drill — Singleton whiteboard:** Sketch lazy + double-checked locking; then rewrite as enum or Bill Pugh holder. State one testing problem Singleton causes and the DI alternative.
3. **Drill — Factory Method vs Abstract Factory:** Design a `PaymentProcessor` factory (card/UPI/wallet) with Factory Method. Then extend: each channel needs matching `ReceiptFormatter` + `FraudChecker` — refactor to Abstract Factory and explain why mixing families is wrong.
4. **Drill — Builder vs constructor:** Given `Pizza(size, cheese, pepperoni, mushrooms, crust, sauce, …)`, write the telescoping mess, then a fluent Builder with required `size` in the builder ctor and optional toppings; call out immutability of the final product.
5. **Drill — Prototype shallow/deep:** Object has `List<Item> inventory`. Show why a shallow `clone()` corrupts both copies when one mutates the list; write the deep-copy fix; optionally add a registry keyed by enemy type.
6. **Drill — LLD problem mapping:** Open [awesome-low-level-design problems](https://github.com/ashishps1/awesome-low-level-design) (Parking Lot, Logging Framework, Snake & Ladder). For each, list which creational pattern(s) you’d mention and where in the class diagram.

## Common follow-ups / gotchas
- “Is a static `create()` a Factory Method?” — No. Static creation methods can’t be overridden; Factory Method relies on subclassing. See [Factory Comparison](https://refactoring.guru/design-patterns/factory-comparison).
- “Should the Logger be a Singleton?” — Often yes in toy LLD; in production prefer injected shared instance. Interview win: acknowledge testability/global-state cost.
- “Simple factory vs Factory Method?” — Simple factory = one class with conditionals; Factory Method = polymorphic creators. Most campus answers use simple factory and that’s OK if you name it honestly.
- “When is Abstract Factory overkill?” — If you only ever create one product type (one interface), Factory Method / simple factory is enough; families are the trigger.
- “Builder vs setters?” — Setters allow half-built mutable objects; Builder + private ctor can enforce invariants at `build()` and yield an immutable product.
- “Prototype vs `new` + copy fields?” — External copy breaks encapsulation (private fields) and couples to concrete classes; `clone()` keeps copying inside the type hierarchy. Always ask shallow vs deep.

## Where it appears
- **Campus / new-grad LLD & machine coding (India product cos, FAANG new-grad):** Factory (simple or method) and Singleton are nearly mandatory vocabulary; Builder appears when entities have many optional attributes; Prototype less often unless games/templates.
- **Experienced / SDE-2 LLD:** expect precise Factory Method vs Abstract Factory distinction, thread-safe Singleton tradeoffs, and choosing *not* to Singleton everything; fluent Builder for request/query objects.
- **Frequency:** creational patterns are the first pattern family interviewers probe; they show up inside almost every canonical LLD problem as “how do you create X?” even when the round isn’t titled “design patterns.”
