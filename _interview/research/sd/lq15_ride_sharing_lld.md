# LQ15 — Design a Ride-Sharing Service (Uber / Ola)

**Interview relevance:** High — hard LLD / machine-coding staple (campus + experienced); Uber, Ola, Flipkart, Swiggy, Amazon, Microsoft, and Grab-style loops use it to probe trip state machines, Strategy for matching/pricing, Observer for status, and the driver double-assignment race.
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Singleton / Factory / Builder), l03_patterns_structural (Facade), l04_patterns_behavioral (Strategy / State / Observer), l05_concurrency_lld; keep HLD Uber (geo-index, Kafka, DISCO) as a stretch — do not substitute it for class design

## Read / watch (curated, in order)
- [ ] [Design Ride-Sharing Service like Uber (problem + UML)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/ride-sharing-service.md) — `awesome-low-level-design` — **start here:** requirements (request / accept / match / fare / payment / tracking / concurrency) + [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/ridesharingservice-class-diagram.png); hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Java ridesharingservice solution](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/ridesharingservice) — `awesome-low-level-design` — runnable reference: `RideSharingService` Singleton + `PricingStrategy` / `DriverMatchingStrategy` + `Trip.TripBuilder` + Observer-style rider/driver updates; siblings: [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/ridesharingservice) / [C++](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/cpp/ridesharingservice) / [C#](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/csharp/ridesharingservice) / [Go](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/golang/ridesharingservice)
- [ ] [Ride Sharing Low Level Design (Uber/Ola)](https://lldhub.in/blog/ride-sharing-lld-design) — `lldhub` — free interview guide: FR/NFR, text class diagram, trip state machine Java, `FareStrategy` / `MatchingStrategy`, Haversine nearest-driver, common follow-ups
- [ ] [Cab Booking LLD](https://ikshitij.com/learn/lld-object-oriented/cab-booking-lld/) — `ikshitij` — Trip state machine + pluggable Matching/Pricing; **CAS `tryReserve` on driver status** called out as the concurrency crux
- [ ] [LLD Case Study: Ride-Sharing Booking Engine](https://www.calibreos.com/learn/lld-ride-sharing) — `CalibreOS` — LLD vs HLD scope (don’t open with Kafka); E4→E6 bar: Trip as aggregate, per-driver lock / CAS, TripRequest vs Trip, LocationStore interface
- [ ] [Design Ride Sharing (Uber)](https://theskilledcoder.com/posts/low-level-design/design-ride-sharing) — `Skilled Coder` — matching strategies (nearest / best-fit / broadcast-first-accept), fare formula, entity boundaries (Driver ≠ fare owner)
- [ ] [Low Level Design in a Hurry (intro — ride-sharing example)](https://www.hellointerview.com/learn/low-level-design/in-a-hurry/introduction) — `Hello Interview` — crisp LLD vs HLD contrast using Trip / TripState / PricingCalculator as the canonical example
- [ ] [System Design Interview: Cab/Taxi Booking like Uber, Ola | LLD](https://www.youtube.com/watch?v=Yn7C0x5ozx4) — `YouTube (Udit Agarwal)` — classic walkthrough: models → managers → Strategy for matching/pricing → JUnit; code: [anomaly2104/lld-cab-booking-ola-uber-grab-lyft](https://github.com/anomaly2104/lld-cab-booking-ola-uber-grab-lyft)
- [ ] [Design Uber (LLD) — Fare, Matching, ETA, GeoHashing](https://www.youtube.com/watch?v=fWWY6He81nk) — `YouTube` — UML → Strategy matching (nearest / highest-rated) → fare estimate TTL → concurrency on driver assign; GeoHashing as the “scale matching” answer
- [ ] [Uber/Ola LLD | Built Uber from Scratch | Machine Coding](https://www.youtube.com/watch?v=VkB6NDEbFsc) — `YouTube (Lavakumar Techie)` — machine-coding narration (rider flow + OTP/surge stretch); code hub: [lavakumarThatisetti/Machine-Coding-Round](https://github.com/lavakumarThatisetti/Machine-Coding-Round)
- [ ] [Java Machine Coding: Scalable Cab Booking (Uber/Ola)](https://dev.to/machinecodingmaster/java-machine-coding-how-to-design-a-scalable-cab-booking-system-uberola-32dh) — `DEV` — short senior checklist: Strategy for match/price, thread-safe trip transitions, don’t hardcode nearest-driver inside the service
- [ ] [LLD Domain Modeling: Ride Sharing System](https://dev.to/saras_growth_space/lld-domain-modeling-designing-a-ride-sharing-system-applying-domain-modeling-in-a-real-system-52la) — `DEV` — Ride as aggregate root, invariants (one active ride per driver, payment once), service vs entity logic split
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) / [State](https://refactoring.guru/design-patterns/state) / [Observer](https://refactoring.guru/design-patterns/observer) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) / [Singleton](https://refactoring.guru/design-patterns/singleton) / [Facade](https://refactoring.guru/design-patterns/facade) — `Refactoring.Guru` — the six patterns interviewers expect you to name (matching + fare, trip lifecycle, status push, ride/vehicle creation, service instance, orchestration API)
- [ ] [ConcurrentHashMap (Java)](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/concurrent/ConcurrentHashMap.html) — `Oracle JDK docs` — safe rider/driver/trip catalogs (awesome-lld uses this); **map alone ≠ atomic driver claim** — still CAS / lock per driver
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo (Flipkart/Uber/Swiggy pacing)
- [ ] [mananchopra/uber-trip-Scheduler](https://github.com/mananchopra/uber-trip-Scheduler) — `GitHub` — alternate Manager + dual Strategy (pricing + allocation) codebase after you can code the happy path
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index / alternate codebases after awesome-lld

## Core concepts to master
- **Clarify before coding:** on-demand only or scheduled? vehicle tiers (bike/auto/economy/premium/XL)? auto-assign vs broadcast-to-N / first-accept? surge in scope? pool/shared rides? ratings? cancel fees? concurrency expected?
- **LLD vs HLD split:** LLD = classes, Trip state machine, MatchingStrategy / FareStrategy, Observer notifications, CAS on driver status. HLD = Redis GEO, Kafka location stream, city sharding, DISCO — mention as stretch; don’t open the whiteboard with Kafka.
- **Core entities:** `Rider`, `Driver` (+ `Vehicle`, `DriverStatus`), `Trip` / `Ride` (+ `TripStatus`), `Location` (lat/lng), optional `TripRequest` (pre-match) vs `Trip` (post-match aggregate), `Payment` / `Rating`.
- **Trip is the aggregate root:** owns rider + driver refs and legal transitions. External code mutates ride state only through Trip / RideSharingService — not by poking fields.
- **State machine (must ship):** typical `REQUESTED → DRIVER_ASSIGNED (or ACCEPTED) → IN_PROGRESS (ONGOING) → COMPLETED`, with `CANCELLED` from pre-start states. Reject illegal moves (`complete` without `start`, cancel mid-trip if product forbids).
- **Patterns that earn points:** **Strategy** (matching + fare/surge), **State** or guarded enum transitions (lifecycle), **Observer** (notify rider/driver on status / location), **Factory** (vehicle / ride type), **Builder** (`Trip.TripBuilder`), **Singleton** (service — optional; prefer DI in production), **Facade** (`RideSharingService` API).
- **Key methods to name:** `registerRider` / `registerDriver`, `requestRide(rider, pickup, dropoff, rideType)`, `acceptRide` / `declineRide`, `startTrip`, `endTrip` / `completeTrip`, `cancelTrip`, `updateDriverLocation`, `calculateFare` (via strategy), optional `rateTrip` / `processPayment`.
- **Matching:** filter AVAILABLE + vehicle type (+ radius) → rank (nearest Haversine / highest rating / ETA) → **atomically claim** driver. Don’t bury `if` trees inside the service if OCP is probed.
- **Pricing:** `base + distance×rate + time×rate` × surge (and ride-type multipliers). Estimate at request; final fare at complete (distance/time actuals). Keep surge as an injected multiplier — don’t hardcode peak logic in `Trip`.
- **Concurrency (the senior probe):** two riders must not get the same driver. Prefer `Driver.tryAssign()` / CAS (`AVAILABLE → ON_TRIP`) or per-driver lock — not a global lock over all matching. Synchronize Trip transitions so cancel vs start can’t corrupt state.
- **SOLID signal:** OCP = new match/fare/ride type without editing the facade; SRP = Trip owns lifecycle, strategies own algorithms, service orchestrates; DIP = depend on `MatchingStrategy` / `PricingStrategy` abstractions.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~35–45 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** register riders/drivers; request ride (pickup, dropoff, type); match available driver; accept; start; complete; cancel; compute fare.
- **FR (common extensions — ask):** surge; ratings; payment stub; live location / ETA; decline + re-match; cancel fee after arrival; multiple vehicle tiers.
- **NFR:** correct under concurrent requests (no double-assign); extensible matching/pricing; modular packages; demonstrable `main` / CLI.
- **Assumptions to state:** single city / in-memory for LLD; Euclidean or Haversine distance OK; no pool unless asked; one active trip per driver/rider.
- **Use cases:** Rider requests → system finds drivers → driver accepts → trip starts → completes → fare/payment; Rider cancels before pickup; Driver goes OFFLINE; Admin/demo prints active trips.

### 2. Back-of-envelope estimation (usually light for LLD)
- In-memory: hundreds–thousands of drivers fine for machine coding.
- If probed on scale: matching must not scan all drivers — `LocationStore` / geo-hash grid / QuadTree; claim remains O(1) CAS on the chosen driver. Leave Redis GEO / city shards for the HLD follow-up.

### 3. API / interface
```
Rider registerRider(name, contact)
Driver registerDriver(name, contact, Vehicle, Location)

Trip requestRide(riderId, pickup, dropoff, RideType) → Trip | null
void acceptRide(driverId, tripId)      // or decline → re-match
void startTrip(tripId)
void endTrip(tripId)                   // fare finalize + driver ONLINE
void cancelTrip(tripId, reason)

void updateDriverLocation(driverId, Location)
void setPricingStrategy(PricingStrategy)
void setDriverMatchingStrategy(DriverMatchingStrategy)
```
OOD surface on entities:
```
MatchingStrategy.findDrivers(drivers, pickup, rideType) → List<Driver>
PricingStrategy.calculateFare(pickup, dropoff, rideType) → double
Trip.assignDriver / startTrip / endTrip / cancel   // guarded transitions
Driver.tryAssign() → boolean                       // CAS availability
```

### 4. Data model / class diagram
```
RideSharingService (Facade + optional Singleton)
  - riders / drivers / trips: ConcurrentHashMap
  - pricingStrategy: PricingStrategy
  - matchingStrategy: DriverMatchingStrategy
  + register* / requestRide / acceptRide / startTrip / endTrip / cancelTrip

Rider  ──requests──► Trip ◄──accepts── Driver
Trip   ──has──► Location(pickup), Location(dropoff)
Driver ──has──► Vehicle, Location, DriverStatus
Trip   ──notifies──► Rider, Driver          (Observer)
Trip   ──uses──► PricingStrategy            (at estimate / complete)

TripStatus:  REQUESTED | DRIVER_ASSIGNED | IN_PROGRESS | COMPLETED | CANCELLED
DriverStatus: OFFLINE | AVAILABLE/ONLINE | ON_TRIP/IN_TRIP

PricingStrategy <<interface>>
  └─ StandardPricing / SurgePricing / RideTypePricing
DriverMatchingStrategy <<interface>>
  └─ NearestDriverStrategy / HighestRatedDriverStrategy
```
Canonical diagram: [ridesharingservice-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/ridesharingservice-class-diagram.png).

### 5. High-level architecture / component breakdown
```
CLI / Driver
     │ request / accept / start / end / cancel
     ▼
RideSharingService (Facade)
     │ uses
     ├─► DriverMatchingStrategy  → candidate drivers
     ├─► PricingStrategy         → estimate / final fare
     ├─► Trip (state machine + Observer notify)
     └─► Driver.tryAssign (CAS) + ConcurrentHashMap catalogs
              │
              ▼
        Payment / Rating stubs (optional, timeboxed)
```
- **Service:** orchestration + strategy injection + catalogs only.
- **Trip:** lifecycle invariants + notifications.
- **Strategies:** pure algorithms (match / price).
- **Driver:** availability claim is a first-class operation.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Auto-assign nearest vs broadcast / first-accept:** auto-assign is simpler for 90 min; broadcast matches real Uber UX but needs offer TTL + race on accept — say both, implement one.
2. **Strategy vs hardcoded matching/pricing:** hardcoded passes demos; Strategy is the expected answer for “add surge / highest-rated / XL-only.”
3. **Enum-guarded transitions vs full State pattern classes:** enum + `IllegalStateException` is interview-default; State classes win if many behaviors diverge per status — don’t over-engineer mid-round.
4. **Global `synchronized` vs per-driver CAS:** coarse lock is correct but serializes the city; per-driver CAS / lock shows senior thinking on the double-assignment race.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = **find + claim driver** → geo index for candidates; atomic assign; retry next candidate on CAS fail.
- Location heartbeats: update a `LocationStore`, don’t rebuild global lists on every GPS ping.
- Trip transitions: lock the Trip (or optimistic version), not the whole service, for cancel-vs-start races.
- Optional product stretch (only if asked): pool waypoints, scheduled holds, surge by geohash zone, OTP start — keep as strategy/config hooks.

**Timed drill:** code register → request → accept → start → end with NearestDriver + StandardFare in 60–75 min, then add Surge strategy + a one-paragraph note on CAS assign.

## Common follow-ups / gotchas
- “Two riders, one nearest driver?” — race on read-then-write; show `tryAssign` / CAS / `UPDATE … WHERE status=AVAILABLE`; loser re-matches.
- “Driver declines / no accept within TTL?” — offer next candidate or fail “no drivers”; don’t leave Trip stuck in REQUESTED forever.
- “Add surge / premium / XL?” — new `PricingStrategy` / ride-type filter in matching; don’t `switch` forever inside `RideSharingService`.
- “Cancel after driver arrived?” — product rule (fee?); still a legal transition from ASSIGNED, illegal from IN_PROGRESS unless specified.
- “Pool / shared rides?” — Trip gets multiple stop waypoints / riders; say out of scope early unless they insist — it reshapes the model.
- “Where do you put fare math?” — Strategy (or FareCalculator), not inside Driver; estimate ≠ final charge.
- Gotcha: opening with Redis/Kafka in an LLD round — interviewer wanted classes and CAS, not HLD.
- Gotcha: Singleton god-service that also prices, matches, pays, and notifies inline — split strategies + Observer or design score drops.
- Gotcha: finishing surge UML but never shipping working request → accept → complete — mandatory path first.

## Where it appears
- **Campus / machine-coding (Flipkart, Uber, Swiggy, Ola, Amazon new-grad, Indian product cos):** common hard problem in ~90 min — working trip lifecycle + one matching + one pricing strategy beats a half-finished pattern zoo.
- **Experienced LLD (FAANG / Uber / Grab / Microsoft):** same domain, deeper probes — double-assignment CAS, Strategy vs switch, Observer vs callbacks, TripRequest vs Trip, geo-index interface without building Redis.
- **Frequency:** among the **top hard** LLD problems (with BookMyShow, Splitwise, food delivery); treat as the template for any two-sided marketplace matching design.
