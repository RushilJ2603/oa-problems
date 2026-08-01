# L03 — Design patterns: structural (Adapter, Decorator, Facade, Composite, Proxy)

**Interview relevance:** High — LLD / machine-coding rounds constantly probe “which wrapper?”, composition vs inheritance, and distinguishing Adapter vs Decorator vs Proxy vs Facade (campus + experienced; FAANG + Indian product cos).
**Type:** LLD-fundamental
**Prereqs:** L01 (OOP & SOLID), L02 (creational patterns)

## Read / watch (curated, in order)
- [ ] [Structural Design Patterns](https://refactoring.guru/design-patterns/structural-patterns) — `Refactoring.Guru` — map of how objects assemble into flexible structures; skim intents before deep-diving each pattern
- [ ] [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) — `awesome-low-level-design` — LLD hub; Structural column links Adapter / Bridge / Composite / Decorator / Facade / Proxy (Algomaster)
- [ ] [Adapter](https://refactoring.guru/design-patterns/adapter) — `Refactoring.Guru` — incompatible interfaces → translator; object vs class adapter; relations to Decorator / Proxy / Facade
- [ ] [Adapter (LLD walkthrough)](https://algomaster.io/learn/lld/adapter) — `awesome-low-level-design` / Algomaster — payment-gateway adapter + media-player example; object adapter preferred in Java
- [ ] [Decorator](https://refactoring.guru/design-patterns/decorator) — `Refactoring.Guru` — stack behaviors at runtime without class explosion; encryption/compression data-source example
- [ ] [Decorator (LLD walkthrough)](https://algomaster.io/learn/lld/decorator) — `awesome-low-level-design` / Algomaster — text-format / coffee-shop stacking; order of wrappers matters
- [ ] [FilterInputStream (Java IO)](https://docs.oracle.com/javase/8/docs/api/java/io/FilterInputStream.html) — `JDK` — canonical real Decorator: `BufferedInputStream` / `DataInputStream` wrap an `InputStream`
- [ ] [Facade](https://refactoring.guru/design-patterns/facade) — `Refactoring.Guru` — one simple entry point over a noisy subsystem; video-converter example; god-facade warning
- [ ] [Facade (LLD walkthrough)](https://algomaster.io/learn/lld/facade) — `awesome-low-level-design` / Algomaster — deploy pipeline / home-theater orchestration without leaking subsystems
- [ ] [Composite](https://refactoring.guru/design-patterns/composite) — `Refactoring.Guru` — tree of leaf + container sharing one interface; recursive ops (price, draw, size)
- [ ] [Composite (LLD walkthrough)](https://algomaster.io/learn/lld/composite) — `awesome-low-level-design` / Algomaster — file explorer + org chart; kill `instanceof` in folder logic
- [ ] [Proxy](https://refactoring.guru/design-patterns/proxy) — `Refactoring.Guru` — same interface, control access: virtual / protection / remote / caching / logging / smart reference
- [ ] [Proxy (LLD walkthrough)](https://algomaster.io/learn/lld/proxy) — `awesome-low-level-design` / Algomaster — lazy image load, auth proxy, DB caching proxy
- [ ] [java.lang.reflect.Proxy](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/lang/reflect/Proxy.html) — `JDK` — dynamic proxies (AOP-style); interview name-drop for logging/auth wrappers without hand-written classes
- [ ] [Facade vs Proxy vs Adapter vs Decorator](https://www.geeksforgeeks.org/system-design/difference-between-the-facade-proxy-adapter-and-decorator-design-patterns/) — `GFG` — one comparison table for the “which pattern?” trap question
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra practice problems where structural patterns show up in class diagrams

## Core concepts to master
- **Structural patterns** compose classes/objects into larger structures **without** inheritance trees that explode; default tool is **composition + delegation** behind a shared interface.
- **Adapter** — convert an **incompatible** interface into the one the client already uses (legacy SDK, 3rd-party payment). Interface **changes**. Prefer **object adapter** (wrap adaptee) in Java/C#.
- **Decorator** — wrap an object that already has the **same** interface to add behavior (logging, compression, toppings). Supports **recursive stacking**; client controls the wrap order.
- **Facade** — new **simplified** API over a **subsystem** of many classes; clients call one method instead of orchestrating N collaborators. Subsystem classes usually **don’t know** the facade.
- **Composite** — model a **part–whole tree** (file/folder, UI widget, org chart) so clients call the **same** ops on leaves and containers; composites recurse and aggregate.
- **Proxy** — stand-in with the **same** interface that **controls access** (lazy init, auth, cache, remote, logging). Proxy often **owns** the real subject’s lifecycle; Decorator usually does not.
- **Distinguish the wrappers (interview gold):** Adapter → *different* interface; Decorator → *same/enhanced* interface + add behavior (client stacks); Proxy → *same* interface + gate/control (often manages real object); Facade → *new* coarse API over *many* objects, not a 1:1 stand-in.
- **Decorator vs Composite:** both recurse; Decorator has **one** child and *adds* responsibility; Composite has **many** children and *sums/aggregates*.
- **OCP / SRP angle:** each adapter/decorator/proxy is a small class; add a new payment provider or topping without editing checkout / coffee / IO core.
- **When not to use:** don’t introduce Adapter if you can change the source; don’t Facade into a god class; don’t Proxy/Decorate everything — wrapper depth hurts debugability and order-sensitive bugs.

## Practice — how it's asked & how to attack it
1. **Drill — name the pattern:** For each prompt, pick one and say *why not* the others: (a) wrap Stripe SDK to fit `PaymentProcessor`, (b) `checkout()` that talks to inventory + payment + notify, (c) add milk/sugar to coffee at runtime, (d) `Folder.getSize()` over nested files, (e) load a heavy image only on first `display()`, (f) deny `delete()` unless role is ADMIN.
2. **Drill — sketch classes (5 min each):** Adapter for `LegacyGateway` → `PaymentProcessor`; Decorator stack `FileDataSource` + `Compression` + `Encryption`; `VideoConverter` Facade; `File`/`Folder` Composite; `ImageProxy` virtual proxy. Draw Client → Interface → Wrapper → Real.
3. **Drill — Java IO as Decorator:** Explain how `new BufferedInputStream(new FileInputStream(...))` is Decorator; what would Adapter vs Proxy look like for the same stream.
4. **Drill — order sensitivity:** Given encrypt-then-compress vs compress-then-encrypt, explain why Decorator **order** matters and how you’d document/test the stack.
5. **Drill — Composite ISP tension:** Should `add`/`remove` live on the Component interface (uniform client, empty on leaves) or only on Composite (ISP-clean, client must distinguish)? State a preference and tradeoff.
6. **Drill — Proxy vs Decorator in code review:** “We wrapped `UserService` to add caching and auth.” Argue whether that’s Proxy, Decorator, or both stacked — and who creates/owns the real service.

## Common follow-ups / gotchas
- “Adapter vs Facade?” — Adapter makes **one** existing interface usable; Facade invents a **new** coarse API over a **subsystem**.
- “Decorator vs inheritance?” — inheritance is static and combinatorial (`BoldItalicUnderline…`); Decorator composes features at runtime (OCP).
- “Can Proxy and Decorator look identical in UML?” — yes (both wrap + delegate); intent differs: **control access / lifecycle** vs **add optional behavior** stacked by the client.
- “Is Facade just a bad god class?” — if it grows unbounded, split into focused facades (e.g. `OrderFacade`, `PaymentFacade`); keep the 80% happy path short.
- “Composite + leaf safety?” — calling `add` on a leaf: throw, no-op, or keep child ops only on Composite — pick one and be consistent.
- “Dynamic proxy / AOP?” — `java.lang.reflect.Proxy` (and Spring AOP) are Proxy-family: intercept calls for tx, logging, security without hand-writing each wrapper.

## Where it appears
- **Campus / machine coding:** Decorator (pizza/coffee/IO), Adapter (multi-provider payment), Composite (file system / org), Facade (library or checkout orchestration) are staple pattern questions and appear inside parking-lot / bookstore / notification designs.
- **Experienced LLD:** Proxy (cache, lazy DAO, auth), Adapter (vendor integrations), and “justify composition over inheritance” deep dives; interviewers often ask you to **contrast** two wrappers on the whiteboard.
- **Frequency:** among the highest-yield LLD fundamentals after SOLID; expect at least one structural pattern by name or by “add feature without changing class X” wording in most product-company LLD rounds.
