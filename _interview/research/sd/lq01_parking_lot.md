# LQ01 — Design a Parking Lot

**Interview relevance:** High — the canonical first LLD / machine-coding question (campus + experienced); Flipkart, Uber, Swiggy, Amazon, Microsoft, Atlassian, Walmart, Adobe, and most Indian product cos use it to probe OOP, SOLID, Strategy/Factory, and concurrency.
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational, l03_patterns_structural; Strategy / Observer from behavioral patterns (or Refactoring.Guru links below)

## Read / watch (curated, in order)
- [ ] [Design Parking Lot (problem + UML + multi-lang code)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/parking-lot.md) — `awesome-low-level-design` — **start here:** requirements, [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/parkinglot-class-diagram.png), Singleton/`synchronized` notes, links to Java/Python/C++/Go/TS solutions (hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design))
- [ ] [Java parking-lot solution](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/parkinglot) — `awesome-low-level-design` — runnable reference for `ParkingLot` / `ParkingFloor` / `ParkingSpot` / `Vehicle`
- [ ] [Design a Parking Lot (workat.tech machine coding)](https://workat.tech/machine-coding/practice/design-parking-lot-qm6hwq4wkhp8/) — `workat.tech` — Flipkart/Uber-style CLI: floors, typed slots, ticket IDs, `display` commands, extensibility + thread-safety optional requirements
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → design for extensibility → working demo (use this pacing on parking lot)
- [ ] [Design a Parking Lot (ByteByteGo OOD)](https://bytebytego.com/courses/object-oriented-design-interview/design-a-parking-lot) — `ByteByteGo` — Facade-style `ParkingLot` + `ParkingManager` + fare calculation; clean interview narrative
- [ ] [Getting Ready: Parking Lot (Grokking LLD / Educative)](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/getting-ready-parking-lot) — `Educative / Grokking OOD` — clarify payment, spot types, vehicle types, pricing before drawing classes; course hub: [Grokking the Low Level Design Interview Using OOD Principles](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles)
- [ ] [Design a parking lot (Educative free blog)](https://www.educative.io/blog/design-a-parking-lot) — `Educative` — free written pass: requirements R1–R8, entities, patterns overview without the full paywall
- [ ] [Parking Lot Design | Grokking The Object Oriented Design Interview](https://www.youtube.com/watch?v=tVRyb4HaHgw) — `YouTube` — bottom-up OOD walkthrough (entities → Strategy for spots → payment)
- [ ] [DESIGN A PARKING LOT — asked at Google, Facebook](https://www.youtube.com/watch?v=DSGsa0pu8-k) — `YouTube` — ambiguity handling + clarifying questions before class hierarchy (great opener mindset)
- [ ] [Parking Lot LLD | Design Principles | FAANG](https://www.youtube.com/watch?v=7IX84K9g23U) — `YouTube` — full LLD + principles (linked from LLD primer solutions)
- [ ] [Design a Parking Lot — Machine coding LLD](https://www.youtube.com/watch?v=nnpT0WXifLk) — `YouTube` — machine-coding oriented alternate narration
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) / [Singleton](https://refactoring.guru/design-patterns/singleton) / [Facade](https://refactoring.guru/design-patterns/facade) / [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — the five patterns interviewers expect you to name on this problem (pricing/allocation, vehicle creation, single lot, entry API, display boards)
- [ ] [low-level-design-primer — solutions index](https://github.com/prasadgujar/low-level-design-primer/blob/master/solutions.md) — `LLD primer` — parking-lot row → alternate codebases; hub: [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer)
- [ ] [anomaly2104/lld-parking-lot](https://github.com/anomaly2104/lld-parking-lot) / [gopalbala/parkinglot](https://github.com/gopalbala/parkinglot) — `GitHub` — second/third implementations after awesome-LLD (compare allocation & ticket models)
- [ ] [LLD for Parking Lot System (Abstract Algorithms)](https://abstractalgorithms.dev/lld-parking-lot-system) — `Abstract Algorithms` — OOP pillars mapped onto the domain + Strategy/Factory + O(log n) nearest-spot heap framing

## Core concepts to master
- **Clarify before coding:** multi-floor? vehicle types (bike/car/truck)? spot types match 1:1 or size hierarchy (motorcycle fits compact)? multiple entry/exit gates? ticket + fee on exit? display boards? concurrency?
- **Core entities:** `ParkingLot` (1) → `ParkingFloor` (many) → `ParkingSpot` (many); `Vehicle` hierarchy; `Ticket` (entry time + spot + vehicle); optional `Gate` / `Payment` / `DisplayBoard`.
- **IS-A vs HAS-A:** inherit `Vehicle` / optionally typed `ParkingSpot`; compose floors into the lot; inject strategies — don’t subclass `ParkingLot` per pricing rule.
- **Patterns that actually earn points:** **Strategy** (fee + spot allocation), **Factory** (create `Vehicle`/`Spot` from type), **Facade** (`ParkingLot.park` / `unpark` orchestrates subsystems), **Singleton** (one lot instance — optional/controversial; prefer DI in production), **Observer** (display boards on occupancy change).
- **Allocation policy:** default interview rule = same type, lowest floor, lowest slot number (workat.tech). Make it a `SpotAllocationStrategy` so “nearest entrance” / “even fill” is a new class, not an `if`.
- **Pricing policy:** `PricingStrategy.calculate(ticket, exitTime)` — hourly / flat / vehicle-type / EV surcharge; never hardcode rates inside `unpark`.
- **Ticket lifecycle:** park → issue ticket id → hold active tickets map → unpark by id → compute fee → free spot → invalidate ticket. Ticket format often `{lotId}_{floor}_{slot}`.
- **Concurrency (the senior probe):** two gates must not assign the same spot. Prefer fine-grained locks (per floor / per spot type) or atomic “find + occupy” under one critical section; `ConcurrentHashMap` for active tickets. Coarse `synchronized` on the whole lot works for demos, bottlenecks under multi-gate load.
- **Availability queries:** maintain free counts / free-slot lists (or heaps) per floor × vehicle type — don’t scan all spots on every `display` / park if you claim scale.
- **SOLID signal:** OCP = new vehicle/fee/allocation without editing `ParkingLot`; SRP = lot orchestrates, floor owns spots, strategy owns fees; DIP = depend on `PricingStrategy` / `SpotAllocationStrategy` abstractions.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~30–40 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** create multi-floor lot; park vehicle → assign typed spot + ticket; unpark by ticket; show free/occupied counts (and optionally slot lists) per floor × type.
- **FR (common extensions — ask):** hourly fee + payment (cash/card); multiple gates; EV spots; handicapped/accessible; overflow / reject when full; admin add floor/slot.
- **NFR:** correct under concurrent park/unpark; extensible for new vehicle types & allocation/pricing strategies; modular files (not one god class); working demo / CLI.
- **Assumptions to state:** one physical lot (or inject lot id); spot type ↔ vehicle type mapping fixed unless told otherwise; no reservations unless asked.
- **Use cases:** Customer enters → system finds spot → prints ticket; Customer exits → pays fee → spot freed; Admin views occupancy; Display board updates free counts.

### 2. Back-of-envelope estimation (usually light for LLD)
- Spot count often **hundreds–tens of thousands** (Educative cites ~40k). In-memory structures fine for machine coding.
- If interviewer pushes “scale”: allocation should be **O(log n)** per type (heap/TreeSet of free slots) not O(n) full scan; locks shouldn’t serialize all gates globally.

### 3. API / interface
Machine-coding CLI (workat.tech-shaped) or methods:
```
create_parking_lot(lotId, floors, slotsPerFloor)
park_vehicle(type, regNo, color) → Ticket | FULL
unpark_vehicle(ticketId) → VehicleInfo | INVALID
display(free_count | free_slots | occupied_slots, vehicleType)
```
OOD method surface:
```
ParkingLot.park(Vehicle) → Ticket
ParkingLot.unpark(TicketId) → Receipt / fee
ParkingFloor.findSpot(VehicleType) → ParkingSpot?
ParkingSpot.assign(Vehicle) / release()
PricingStrategy.calculate(Ticket, exitTime) → Money
```

### 4. Data model / class diagram
```
ParkingLot 1──* ParkingFloor 1──* ParkingSpot
ParkingLot ──uses──> SpotAllocationStrategy
ParkingLot ──uses──> PricingStrategy
ParkingLot 1──* Ticket (active)
Vehicle <|-- Bike | Car | Truck
ParkingSpot (type, id, floorNo, occupied?, vehicle?)
Ticket (id, vehicle, spot, entryTime)
DisplayBoard ──observes──> ParkingLot / Floor   (optional Observer)
EntryGate / ExitGate ──facade calls──> ParkingLot (optional)
```
Canonical diagram: [parkinglot-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/parkinglot-class-diagram.png).

### 5. High-level architecture / component breakdown
- **ParkingLot (Facade + optional Singleton):** entry point; holds floors + strategies + ticket registry.
- **ParkingFloor:** owns spots; `park`/`unpark` within floor; maintains free lists/heaps per type.
- **ParkingSpot:** state machine free ↔ occupied; type check on assign.
- **Vehicle (+ Factory):** identity (`regNo`) + type; factory from CLI string.
- **Ticket / Payment:** duration bridge for billing; payment can stay stubbed if timeboxed.
- **Strategies:** allocation + pricing plugged at construction (OCP).
- **Concurrency layer:** synchronized assign path or per-floor lock + concurrent ticket map.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Enum vs class hierarchy for Vehicle/Spot:** enum is faster to code; abstract class/subtypes win OCP when behavior diverges (EV charging). Prefer hierarchy in OOD rounds; enum OK if timeboxed and mapping is centralized.
2. **Allocation Strategy vs hardcoded lowest-floor scan:** hardcoded passes tests; Strategy is the expected extensibility answer for “change how we pick spots.”
3. **Global lock vs fine-grained concurrency:** `synchronized park()` is correct but serializes gates; per-floor / per-type locks or compare-and-set on spot occupancy show senior thinking — mention double-booking race explicitly.
4. **Singleton ParkingLot:** common in tutorials; say you’d inject a single instance (testability) unless interviewer wants classic Singleton.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = **find free spot under contention** → free-slot heap/TreeSet per floor×type; avoid linear scans.
- Multi-gate: don’t lock the entire lot for fee calculation; only for assign/release + ticket map update.
- Display boards: Observer push or pull counts from floor free-maps — don’t recount all spots.
- Optional product stretch (only if asked): reservations, dynamic pricing, multi-lot — keep as strategy/config hooks, don’t implement mid-round.

**Timed drill:** implement workat.tech CLI happy path in 60–75 min, then add Strategy for allocation and a note on thread-safety.

## Common follow-ups / gotchas
- “Can a car take a truck spot (or vice versa)?” — product rule; default = exact type match; size hierarchy is a deliberate extension.
- “Two cars enter at once — same spot?” — race on read-then-write; show synchronized assign or atomic occupy.
- “Add EV charging / handicapped spots” — new spot subtype + allocation filter; don’t `switch` forever inside `ParkingLot`.
- “Hourly vs flat vs weekend pricing” — Strategy swap; receipt includes breakdown.
- “Multiple parking lots / multi-city” — drop process-wide Singleton; `ParkingLotRepository` keyed by id (workat optional).
- “Nearest-to-entrance allocation” — new `SpotAllocationStrategy` using spot distance/id order; heap by distance.
- Gotcha: god-class `ParkingLot` that also bills, prints, and persists — split SRP or interviewer docks design score.
- Gotcha: finishing optional extensibility but failing mandatory `park`/`unpark`/`display` — mandatory first.

## Where it appears
- **Campus / new-grad:** extremely common first LLD or machine-coding round in India (Flipkart, Uber, Swiggy, Amazon, Walmart, Razorpay, Atlassian-style loops); often a timed CLI.
- **Experienced / SDE-2:** same domain, harder follow-ups — concurrency, Strategy vs inheritance, payment flows, Observer display boards, allocation complexity.
- **FAANG OOD:** classic “design a parking lot” whiteboard (Google/Meta lore); focus on clarifying questions + clean class model more than CLI I/O.
- **Frequency:** among the **most asked** LLD problems — treat as the template for every later LLD question (elevator, Splitwise, booking).
