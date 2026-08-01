# LQ16 — Design a Hotel Booking System

**Interview relevance:** High — canonical date-range inventory LLD / OOD (campus + SDE-2); Flipkart/Uber/Swiggy-style machine coding and FAANG whiteboards; often framed as Hotel Management (single property) or Booking.com/Airbnb (multi-hotel search + book); concurrency + overlap checks are the probe.
**Type:** LLD-question
**Prereqs:** L01 (OOP & SOLID), L02 (creational — Factory / Singleton), L03–L04 (Facade / Strategy / State / Observer / Decorator), L05 (concurrency), L06 (LLD framework); helpful: LQ03 movie booking (hold+confirm inventory races), HLD Airbnb/Booking.com if in sheet

## Read / watch (curated, in order)
- [ ] [Designing a Hotel Management System (problem + UML)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/hotel-management-system.md) — `awesome-low-level-design` — **primary sheet problem:** FR checklist (book / check-in / check-out / payments / concurrency), [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/hotelmanagementsystem-class-diagram.png) (hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design))
- [ ] [Java solution (Facade + State + Factory + Decorator + Observer)](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/hotelmanagementsystem) — `awesome-low-level-design` — reference: `HotelManagerFacade.bookRoom`, `BookingService`, `Room`/`RoomState` (`Available`/`Occupied`/`Maintenance`), `RoomFactory`, amenity Decorator, `Payment` Strategy (also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/hotelmanagementsystem) / [C++](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/cpp/hotelmanagementsystem) / [C#](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/csharp/hotelmanagementsystem) / [Go](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/golang/hotelmanagementsystem))
- [ ] [Issue #31 — Room.status breaks non-overlapping future bookings](https://github.com/ashishps1/awesome-low-level-design/issues/31) — `awesome-low-level-design` — **must-read gotcha:** flipping a room to `BOOKED` blocks later non-overlapping stays; fix = date-range calendar / reservation list per room (not a single status bit)
- [ ] [Getting Ready: Hotel Management System (Educative)](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/getting-ready-the-hotel-management-system) — `Educative / Grokking OOD` — clarify booking, pricing, cancel before classes; pair with [class diagram lesson](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/class-diagram-for-the-hotel-management-system); course hub: [Grokking the Low Level Design Interview Using OOD Principles](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles)
- [ ] [Design a Hotel Management System (tssovi / Grokking OOD)](https://github.com/tssovi/grokking-the-object-oriented-design-interview/blob/master/object-oriented-design-case-studies/design-a-hotel-management-system.md) — `Grokking OOD (open source)` — use cases, `Hotel`/`HotelLocation`, `Room`/`RoomBooking`, accounts (Guest/Receptionist/Housekeeper), housekeeping + keys (mirror: [wyaadarsh/Grokking-OOD](https://github.com/wyaadarsh/Grokking-OOD/blob/master/object-oriented-design-case-studies/design-a-hotel-management-system.md))
- [ ] [Hotel Management | AlgoMonster LLD](https://algo.monster/courses/lld/lld_hotel_management) — `AlgoMonster` — machine-coding shaped: half-open `[checkin, checkout)`, overlap invariant owned by `Room`, `Hotel` as Facade for `room`/`book`/`cancel`/`available`
- [ ] [Design Hotel Management System (Skilled Coder)](https://theskilledcoder.com/posts/low-level-design/design-hotel) — `Skilled Coder` — why **time** is the unique constraint; overlap formula `A.start < B.end && B.start < A.end`; RoomType vs specific Room
- [ ] [LLD Case Study: Hotel Booking System (CalibreOS)](https://www.calibreos.com/learn/lld-hotel-booking) — `CalibreOS` — what interviewers grade: date-range modeling, Strategy pricing, State for booking lifecycle, optimistic/`FOR UPDATE` vs check-then-act race
- [ ] [Hotel Management · LLD-flavoured](https://ikshitij.com/learn/lld-object-oriented/hotel-management/) — `ikshitij` — compact class model + multiplicities, hold→confirm path, State/Strategy/Observer map
- [ ] [Low Level Designing (LLD-3): Hotel Booking System](https://www.youtube.com/watch?v=6zZALeDMFew) — `Interview With Bunny` — whiteboard LLD walkthrough (entities → relationships → HotelBookingSystem facade) for Booking.com / Airbnb / MakeMyTrip framing
- [ ] [Airbnb / Booking.com System Design (codeKarle)](https://www.youtube.com/watch?v=YyOXt2MEkv4) — `codeKarle` — short **HLD** bridge after your class model works (search vs book paths, Elasticsearch, ACID store)
- [ ] [Design Hotel Booking App — HLD + LLD deep dive](https://www.youtube.com/watch?v=mH2Ye3_vErw) — `YouTube` — proximity/search + schema deep dive once OOD core is solid
- [ ] [Design a Hotel Booking System (SpaceComplexity)](https://spacecomplexity.ai/blog/hotel-booking-system-design-interview) — `SpaceComplexity` — inventory row-per-(room,date), soft hold + confirm, idempotency; use for senior follow-ups
- [ ] [Design a Hotel Reservation System (HLD Handbook)](https://hld.handbook.academy/curriculum/case-studies/hotel-reservation/) — `HLD Handbook` — Postgres `EXCLUDE USING GIST` as final fence; search vs booking path split
- [ ] [System Design of Airbnb | Hotel Reservation (GfG)](https://www.geeksforgeeks.org/system-design/system-design-of-airbnb-hotel-reservation-system/) — `GfG` — Indian-interview staple HLD overview (use for vocabulary after LLD classes work)
- [ ] [Correctness (Hello Interview concurrency)](https://www.hellointerview.com/learn/low-level-design/concurrency/correctness) — `Hello Interview` — inventory races; coarse vs fine locks (pair with [Intro](https://www.hellointerview.com/learn/low-level-design/concurrency/intro))
- [ ] [Race Conditions and Critical Sections](https://algomaster.io/learn/concurrency-interview/race-conditions-and-critical-sections) — `AlgoMaster` — check-then-act that double-books
- [ ] [Design Ticket Booking System (Concurrency)](https://algomaster.io/learn/concurrency-interview/design-ticket-booking-system) — `AlgoMaster` — hold TTL / atomic multi-unit booking ideas transfer to rooms+nights
- [ ] [Intrinsic Locks and Synchronization](https://docs.oracle.com/javase/tutorial/essential/concurrency/sync.html) — `Oracle` — `synchronized (room)` style per-room critical sections for LLD demos
- [ ] [PostgreSQL Range Types](https://www.postgresql.org/docs/current/rangetypes.html) — `Postgres docs` — `daterange` / half-open `[)` bounds so checkout day frees for next check-in ([exclusion constraints section](https://www.postgresql.org/docs/current/rangetypes.html#RANGETYPES-CONSTRAINT); [btree_gist](https://www.postgresql.org/docs/current/btree-gist.html); [DDL constraints](https://www.postgresql.org/docs/current/ddl-constraints.html); [explicit locking](https://www.postgresql.org/docs/current/explicit-locking.html))
- [ ] [PostgreSQL DateRange and Efficient Time Management (Hashrocket)](https://hashrocket.com/blog/posts/postgresql-daterange-and-efficient-time-management) — `Hashrocket` — hotel_reservations + `EXCLUDE USING gist (room WITH =, stay WITH &&)` worked example
- [ ] [PostgreSQL GiST Exclusion Constraint (Amitav Roy)](https://amitavroy.com/articles/postgresql-gist-exclusion-constraintthe-database-evel-answer-to-double-bookings) — `blog` — partial exclusion (`WHERE status != 'cancelled'`) so cancelled rows don’t block rebooking
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) — `Refactoring.Guru` — `PricingStrategy` (flat / seasonal / occupancy) + `PaymentStrategy` (cash/card/UPI)
- [ ] [State](https://refactoring.guru/design-patterns/state) — `Refactoring.Guru` — room + reservation lifecycle FSMs (enum OK in machine coding; State objects if transitions explode)
- [ ] [Factory Method](https://refactoring.guru/design-patterns/factory-method) — `Refactoring.Guru` — `RoomFactory` for STANDARD/DELUXE/SUITE
- [ ] [Facade](https://refactoring.guru/design-patterns/facade) — `Refactoring.Guru` — thin `bookRoom` / `checkIn` / `checkOut` entry that hides search + lock + price + pay
- [ ] [Singleton](https://refactoring.guru/design-patterns/singleton) — `Refactoring.Guru` — one `HotelManagementSystem` in demos (prefer DI in production)
- [ ] [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — booking confirm / housekeeping / email notifications
- [ ] [Decorator](https://refactoring.guru/design-patterns/decorator) — `Refactoring.Guru` — breakfast/spa amenity pricing layered on base room (as in awesome-LLD Java)
- [ ] [Stripe Idempotent requests](https://docs.stripe.com/api/idempotent_requests) — `Stripe` — `Idempotency-Key` so payment retries don’t double-charge / double-create bookings
- [ ] [Distributed locks with Redis](https://redis.io/docs/latest/develop/clients/patterns/distributed-locks/) — `Redis docs` — multi-instance hold follow-up (`SET NX PX` + safe release)
- [ ] [How to do distributed locking (Martin Kleppmann)](https://martin.kleppmann.com/2016/02/08/how-to-do-distributed-locking.html) — `DDIA author` — Redis/Redlock ≠ correctness fence; DB/exclusion constraint as truth
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [Mock LLD of Hotel Management (gist)](https://gist.github.com/kuntalchandra/f8260dee9bf3e8c0084ce8c31fe3554e) — `GitHub gist` — alternate skeleton (accounts, Decorator charges) after awesome-LLD
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after happy path + overlap path both work ([solutions.md](https://github.com/prasadgujar/low-level-design-primer/blob/master/solutions.md))

## Core concepts to master
- **Clarify scope first:** single-property **Hotel Management** (rooms, check-in/out, housekeeping, billing) vs multi-hotel **Booking platform** (city search, many properties, payments)? Specific room pick vs book-by-`RoomType` then assign at check-in? Hold TTL? Cancel/refund policy? Concurrency required?
- **#1 trap — Room.status alone:** `AVAILABLE|BOOKED|OCCUPIED` cannot express “booked Mar 13–15 but free Mar 17–22.” Availability is **date-range overlap** over a room’s reservation calendar ([issue #31](https://github.com/ashishps1/awesome-low-level-design/issues/31)). Status is for *ops* (occupied / dirty / maintenance), not for multi-stay inventory.
- **Overlap predicate (memorize):** ranges `[start, end)` overlap iff `A.start < B.end && B.start < A.end`. Half-open end so **checkout day = next guest’s check-in day** is free.
- **RoomType vs Room:** `RoomType` = category (STANDARD/DELUXE/SUITE + base rate); `Room` = physical unit (`roomNumber`). Search often by type; assignment of a concrete room can be at booking time *or* at check-in (late assignment).
- **Reservation / Booking lifecycle:** `PENDING/HELD → CONFIRMED → CHECKED_IN → CHECKED_OUT` (+ `CANCELLED` / `NO_SHOW`). Never jump AVAILABLE→OCCUPIED while payment is in flight if payment is in scope.
- **Two-phase booking (when payment in scope):** (1) **hold** room+dates atomically → `PENDING` + `expiresAt`; (2) **confirm** after pay, or **release** on fail/TTL. Same pattern as movie seats (LQ03) with date ranges instead of seat IDs.
- **Patterns that earn points:** **Facade** (`HotelManagerFacade` / `HotelManagementSystem`), **State** (room + reservation), **Strategy** (pricing + payment), **Factory** (rooms), **Observer** (confirm / housekeeping), **Decorator** (amenities/folio extras). Optional **Specification** for composable room search (awesome-LLD Java). Don’t force Singleton beyond demos.
- **Key methods to name:** `addRoom` / `addGuest`, `searchAvailable(type, checkIn, checkOut)`, `hold` / `book` / `confirm`, `cancel`, `checkIn`, `checkOut`, `processPayment`, `getFolio` / bill.
- **Concurrency checklist:** synchronize **per room** (or lock inventory rows for those dates); check+insert under one critical section; unlock/release only if still held by same guest; TTL must not free a `CONFIRMED` stay; ordered locks if multi-room booking (deadlock).
- **Search vs book:** browse/search can be slightly stale; **hold+confirm must be strongly consistent**. Multi-instance → Redis TTL hold *plus* DB fence (`SELECT FOR UPDATE` or GiST exclusion constraint) — Kleppmann.
- **Out of scope until asked:** full PMS (housekeeping schedules, keys, OTAs), dynamic yield management ML, real PGW, multi-currency, flash-sale waiting rooms (those are HLD).

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~35–45 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **Clarify first:** one hotel or chain/aggregator? book by room number or by type? payment in scope? cancel windows? housekeeping / maintenance? concurrency + hold TTL?
- **FR (typical single-hotel LLD):** manage room types + rooms; search available rooms for `[checkIn, checkOut)`; create reservation; cancel; check-in / check-out; process payment; (admin) mark maintenance.
- **FR (platform stretch):** search hotels by city + dates + guests; list room types with price; hold → pay → confirm across properties.
- **Use cases:** (1) Guest searches dates → picks room/type → pays → confirmation; (2) Two guests race same room+dates → exactly one wins; (3) Guest abandons checkout → TTL frees inventory; (4) Payment fails → hold released; (5) Cancel → dates free again; (6) Check-in assigns/occupies room; check-out → housekeeping → available.
- **NFR:** **no double-booking**; thread-safe concurrent holds; extensible pricing/payment; modular services (not one god class).
- **Assumptions to state:** e.g. one hotel demo, ~50–200 rooms, hold = 10–15 min, payment mocked, in-memory OK for LLD; half-open date ranges.

### 2. Back-of-envelope estimation (for HLD)
- **LLD:** skip capacity math. State knobs (`numRooms`, `avgStayNights`, `lockTtlMs`) and that the hot path is **overlap check + atomic insert under per-room lock**, not a global lock.
- If pushed toward HLD: search QPS ≫ booking writes; inventory partitioned by `hotelId`/`roomId`; see codeKarle / SpaceComplexity / HLD Handbook / GfG links above.

### 3. API / interface
```
# Inventory / search
List<Room>     searchAvailable(RoomType type, LocalDate checkIn, LocalDate checkOut)
List<Hotel>    searchHotels(city, checkIn, checkOut, guests)   // platform stretch

# Booking (two-phase — prefer if payment in scope)
Hold           holdRoom(guestId, roomId, checkIn, checkOut)    // → holdId, expiresAt; 409 on conflict
Reservation    confirm(holdId, PaymentRequest)
void           releaseHold(holdId)
boolean        cancel(reservationId)

# Stay ops
void           checkIn(reservationId)     // → room OCCUPIED / assign room if late-assignment
Invoice        checkOut(reservationId)    // bill + free/housekeeping

# Admin
Room addRoom(...); void markMaintenance(roomId);

# Facade one-shot (awesome-LLD style demos)
Booking bookRoom(guest, type, style, start, end, amenities)
```

### 4. Data model / class diagram
```
HotelManagerFacade / HotelManagementSystem  <<Facade (+ optional Singleton)>>
 - roomService, bookingService, paymentService
 + searchAvailable / bookRoom / hold / confirm / cancel
 + checkIn / checkOut

Hotel 1──* Room
Room
 - roomNumber, RoomType, price, RoomState (AVAILABLE|OCCUPIED|MAINTENANCE|DIRTY)
 - reservations: List<Reservation>     // THE inventory calendar
 + isAvailable(checkIn, checkOut)      // no overlap with active stays
 + book() / checkIn() / checkOut()     // State pattern transitions

RoomType <<enum>>  STANDARD | DELUXE | SUITE
Guest 1──* Reservation

Reservation / Booking
 - id, guest, room (or roomType + room assigned later)
 - checkIn, checkOut, status(PENDING|CONFIRMED|CHECKED_IN|CHECKED_OUT|CANCELLED)
 - lockedBy?, expiresAt?               // for holds
 + confirm() / cancel() / checkIn() / checkOut()

RoomState <<interface>> → AvailableState / OccupiedState / MaintenanceState
PricingStrategy <<interface>> → FlatNightly / Seasonal / OccupancyBased
PaymentStrategy <<interface>> → CashPayment / CardPayment
BookingObserver (optional) → email / housekeeping notify
Bookable + Decorator (optional) → RoomBooking + BreakfastDecorator / SpaDecorator

Enums: RoomType, RoomStatus/State, ReservationStatus, PaymentStatus
```
- Sketch this (or the [awesome-lld diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/hotelmanagementsystem-class-diagram.png)) **before** coding. Call out the **reservation calendar on `Room`** if the diagram only shows a single `RoomStatus`.

### 5. High-level architecture / component breakdown
```
Client
  │ searchAvailable / bookRoom
  ▼
HotelManagerFacade
  ├─ RoomService          // catalog + Specification/filter search
  ├─ BookingService       // overlap check + create Reservation + Observer notify
  │     └─ per-room lock / synchronized(room)
  └─ PaymentService       // PaymentStrategy
        └─ confirm or release hold
```
- **Room owns the overlap invariant** (`isAvailable` / `book` under lock) — don’t scatter the predicate across services.
- **BookingService** orchestrates hold → price → pay → confirm/release.
- **Strategies / Decorators** swap pricing & amenities without touching the critical section.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Status-bit inventory vs date-range calendar:** status-bit is simpler but wrong for non-overlapping future stays — prefer calendar + overlap (or per-night inventory rows for platform scale).
2. **Hold-then-pay vs one-shot book:** one-shot OK for demos; two-phase is what real booking does and what concurrency follow-ups expect.
3. **Per-room lock vs DB `FOR UPDATE` vs GiST exclusion:** per-room `synchronized` = correct LLD demo; short DB row lock to set `PENDING`+`expires_at` (don’t hold lock while user pays); exclusion constraint `EXCLUDE USING GIST (room_id WITH =, stay WITH &&)` as structural final fence.
4. **Book specific Room vs book RoomType:** specific room is simpler; type-level booking + late assignment increases occupancy but needs a pool count / assignment step at check-in.
5. **Optimistic vs pessimistic:** conflicts on popular weekends are common → pessimistic / conditional insert preferred; OCC alone causes “pay then fail” unless you still hold first.

### 7. Bottlenecks / how you scale it
- Hot room / hot weekend → contention on one `roomId` (or one type pool); don’t use one global lock for the whole hotel.
- Search: index/filter by type + scan that room’s reservations (or maintain per-night availability counts); re-check on hold.
- Expiry worker vs payment race: confirm must be conditional (`status=PENDING AND locked_by=? AND expires_at > now`); unlock only PENDING→AVAILABLE.
- Platform scale: separate search index (eventual) from booking DB (strong); Redis holds + Postgres exclusion/row locks as truth.
- Notifications / invoice email: async after confirm — out of LLD critical path.

## Common follow-ups / gotchas
- “Two users book the same room for overlapping dates?” — atomic check+insert under per-room lock (or exclusion constraint); loser gets failure/409.
- “Booked Mar 13–15 — can someone book Mar 17–20?” — **yes** if you model date ranges; **no** if you only flip `Room.status=BOOKED` (issue #31).
- “Same-day checkout/check-in?” — use half-open `[checkIn, checkOut)` so they don’t overlap.
- “User never pays?” — TTL / scheduler releases PENDING hold; must no-op if already CONFIRMED or held by another guest.
- “Payment succeeds twice (retry)?” — idempotency key / reservation id; confirm conditional on PENDING.
- “Partial multi-room success?” — all-or-nothing; ordered lock acquisition by `roomId`.
- “RoomType vs Room?” — don’t put inventory only on the type enum; physical conflicts live on `Room` (or typed pool counts with careful accounting).
- “Distributed systems?” — Redis `SET NX PX` for holds + DB as source of truth; don’t claim Redlock alone makes booking correct.
- Gotcha: god-class facade that also prices, pays, emails, and persists — split SRP or design score drops.

## Where it appears
- **Campus / machine-coding (Flipkart, Uber, Swiggy, Amazon new-grad, Indian product cos):** common “Hotel Management / Hotel Booking LLD” — working search+book+cancel with correct **overlap** beats a pattern zoo; concurrency often the stretch after the happy path.
- **Experienced / SDE-2 LLD (FAANG-adjacent, Booking.com/Airbnb-style loops):** expected from the start — date-range modeling, TTL holds, payment failure paths, Strategy pricing; may bridge into HLD (search index, Redis, exclusion constraints).
- **Frequency:** top-tier LLD problem alongside Parking Lot, Movie Booking, Library — treat as the canonical **temporal inventory** OOD question (movie seats = discrete units; hotel = intervals over time).
