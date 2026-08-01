# LQ03 — Design a Movie Ticket Booking System (BookMyShow)

**Interview relevance:** High — hard concurrency LLD / machine-coding staple (campus + SDE-2); Flipkart, Swiggy, Amazon, Walmart, Razorpay, BookMyShow-style loops probe seat locking + payment; pairs with HLD Ticketmaster/BookMyShow (hq11).
**Type:** LLD-question
**Prereqs:** L01 (OOP & SOLID), L02 (creational — Singleton/Builder), L03 (Facade), L04 (Strategy / State / Observer), L05 (concurrency), L06 (LLD framework); helpful: hq11_booking (HLD seat holds)

## Read / watch (curated, in order)
- [ ] [Movie Ticket Booking LLD (Hello Interview)](https://www.hellointerview.com/learn/low-level-design/problem-breakdowns/bookmyshow) — `Hello Interview` — best free clarifying-questions → entities → concurrent book/cancel walkthrough; know what they put *out of scope* (payment, seat tiers) vs what interviewers usually keep in
- [ ] [Designing a Movie Ticket Booking System (problem + UML)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/movie-ticket-booking-system.md) — `awesome-low-level-design` — **primary sheet problem:** FR checklist, [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/movieticketbookingsystem-class-diagram.png), Singleton + `ConcurrentHashMap` notes (hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design))
- [ ] [Java solution (SeatLockManager + Strategy + Observer)](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/movieticketbookingsystem) — `awesome-low-level-design` — reference: `MovieBookingService` (Singleton), `SeatLockManager` (per-show lock + TTL unlock), `PricingStrategy` / `PaymentStrategy`, Booking Builder (also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/movieticketbookingsystem) / C++ / C# / Go siblings)
- [ ] [Design Movie Booking System | LLD](https://algomaster.io/learn/lld/design-movie-booking-system) — `AlgoMaster` / awesome-LLD — clarifying dialog, city→cinema→screen→show hierarchy, seat types, temporary lock during payment, Strategy for pricing/payment
- [ ] [Design Ticket Booking System (Concurrency)](https://algomaster.io/learn/concurrency-interview/design-ticket-booking-system) — `AlgoMaster` — holds, TTL expiry, atomic multi-seat group booking, race at “Book Now”
- [ ] [Correctness (Hello Interview concurrency)](https://www.hellointerview.com/learn/low-level-design/concurrency/correctness) — `Hello Interview` — seat-booking / inventory races; coarse vs fine locks (pair with [Intro](https://www.hellointerview.com/learn/low-level-design/concurrency/intro))
- [ ] [Race Conditions and Critical Sections](https://algomaster.io/learn/concurrency-interview/race-conditions-and-critical-sections) — `AlgoMaster` — check-then-act that double-books a seat
- [ ] [Intrinsic Locks and Synchronization](https://docs.oracle.com/javase/tutorial/essential/concurrency/sync.html) — `Oracle` — language baseline for `synchronized (show)` style per-show critical sections
- [ ] [Movie Ticket Booking LLD Guide](https://lldhub.in/blog/movie-ticket-booking-lld) — `lldhub` — seat lock service, PENDING→CONFIRMED booking FSM, Strategy for category/surge pricing; Swiggy/Razorpay framing
- [ ] [BookMyShow System Design (Educative blog)](https://www.educative.io/blog/bookmyshow-system-design) — `Educative` — free HLD↔LLD bridge: AVAILABLE → HELD → BOOKED, time-bound holds, payment idempotency framing
- [ ] [Design BookMyShow (GfG)](https://www.geeksforgeeks.org/system-design/design-bookmyshow-a-system-design-interview-question/) — `GfG` — Indian-interview staple: 5–10 min seat block, Redis lock + async ticket/notification (use for follow-up depth, not as LLD code)
- [ ] [System Design | BookMyShow (The Tech Granth)](https://www.youtube.com/watch?v=6UAlDIzqhBo) — `The Tech Granth` — short HLD pass on concurrency + DB choice after your class model works
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) — `Refactoring.Guru` — `PricingStrategy` (weekday/weekend/category) + `PaymentStrategy` (card/UPI) without editing booking flow
- [ ] [State](https://refactoring.guru/design-patterns/state) — `Refactoring.Guru` — seat/booking lifecycle as FSM (enum is fine in machine coding; State objects if transitions explode)
- [ ] [Singleton](https://refactoring.guru/design-patterns/singleton) — `Refactoring.Guru` — `MovieBookingService.getInstance()` as in awesome-LLD (prefer DI in production; know DCL/`volatile`)
- [ ] [Builder](https://refactoring.guru/design-patterns/builder) — `Refactoring.Guru` — multi-field `Booking` construction (awesome-LLD `BookingBuilder`)
- [ ] [Facade](https://refactoring.guru/design-patterns/facade) — `Refactoring.Guru` — thin `bookTickets` / `findShows` entry that hides lock + price + pay + confirm
- [ ] [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — optional: notify users when a watched movie gets a new show (awesome-LLD `MovieObserver`)
- [ ] [PostgreSQL Explicit Locking](https://www.postgresql.org/docs/current/explicit-locking.html) — `Postgres docs` — `SELECT … FOR UPDATE` for short hold txns; docs warn against holding DB locks while the user pays
- [ ] [Distributed locks with Redis](https://redis.io/docs/latest/develop/clients/patterns/distributed-locks/) — `Redis docs` — `SET key token NX PX …` + safe release; multi-instance follow-up
- [ ] [How to do distributed locking (Martin Kleppmann)](https://martin.kleppmann.com/2016/02/08/how-to-do-distributed-locking.html) — `DDIA author` — Redis/Redlock ≠ correctness fence; DB/conditional write as truth
- [ ] [Stripe Idempotent requests](https://docs.stripe.com/api/idempotent_requests) — `Stripe` — `Idempotency-Key` so payment retries don’t double-charge
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD problem index after the happy path + lock path both work

## Core concepts to master
- **Hierarchy (don’t flatten):** `City` → `Cinema` → `Screen` → `Show` (movie + screen + startTime) → **per-show seat inventory**. A seat map template lives on the `Screen`; **availability is per `Show`**, not shared across the day’s shows.
- **ShowSeat vs Seat:** `Seat` = layout (row, col, type). Inventory that races is `ShowSeat` / seat status keyed by `(showId, seatId)`. Mutating a single shared `Seat.status` across shows is a common awesome-LLD simplification — call it out and fix if probed.
- **3-state seat model (the heart of the problem):** `AVAILABLE → LOCKED/HELD → BOOKED`. Never jump AVAILABLE→BOOKED while payment is in flight. Lock TTL typically **5–10 min** (demo code may use ms).
- **Two-phase booking:** (1) **lock/hold** seats atomically → create `Booking(PENDING)`; (2) **confirm** after payment success (`LOCKED→BOOKED`, booking `CONFIRMED`) or **release** on failure/timeout (`LOCKED→AVAILABLE`).
- **Atomic multi-seat hold:** all-or-nothing. Check *all* seats available, then lock all under one critical section; on any conflict, fail the whole request (no orphan partial holds).
- **Lock granularity:** **per-show** `synchronized(show)` / `ReentrantLock` (or Redis key `show:{id}`) so different shows don’t serialize. Never hold a DB row lock for the entire payment window.
- **Patterns that earn points:** **Singleton/Facade** (`MovieBookingService`), **Strategy** (pricing + payment), **Builder** (Booking), **State/FSM** (seat + booking status), optional **Observer** (new show alerts). Don’t force Factory unless creating seat layouts/payment adapters.
- **Payment is external:** mock `PaymentStrategy.pay(amount)`; on failure release locks; on success confirm idempotently (same payment/booking id must not double-book).
- **Concurrency checklist:** check-then-act under one lock; unlock only if still held by *same user*; scheduler/TTL must not release seats already `BOOKED`; ordered lock acquisition if locking seat-by-seat (deadlock).
- **Search vs book:** browse/search can be eventually consistent / stale map OK briefly; **hold+confirm must be strongly consistent** — say this when NFR comes up.
- **Out of scope until asked:** UI seat map rendering, real PGW, refunds, waitlist, partner theatre APIs, flash-sale waiting room (those are HLD/hq11).

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~35–45 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **Clarify first:** single cinema or multi-city aggregator? specific seat pick vs auto-assign? seat tiers/pricing? payment in scope? cancel/refund? hold TTL? concurrency required?
- **FR (typical):** search movies/shows by city (+ title); list cinemas/shows; view seat map for a show; select N seats; temporarily lock; pay; confirm booking; cancel confirmed booking (release seats).
- **FR (admin, if asked):** add/update movies, cinemas, screens, shows, seat layouts.
- **Use cases:** (1) Browse → pick show → select seats → pay → ticket; (2) Two users race same seat → exactly one wins; (3) User abandons checkout → TTL frees seats; (4) Payment fails → seats unlocked; (5) Cancel booking → seats AVAILABLE again.
- **NFR:** **no double-booking**; thread-safe under concurrent holds; extensible pricing/payment; lock TTL; modular services (not one god class).
- **Assumptions to state:** e.g. one city demo, ~100–300 seats/screen, hold = 10 min, payment mocked, in-memory OK for LLD.

### 2. Back-of-envelope estimation (for HLD)
- **LLD:** skip capacity math. State knobs you’ll code against (`numCities`, `seatsPerScreen`, `lockTtlMs`) and that the hot path is **O(k) seats under one per-show lock**, not a global lock.
- If pushed toward HLD: browse QPS ≫ booking writes; partition inventory by `showId`; see hq11 / Educative / GfG links above.

### 3. API / interface
```
# Catalog
List<Movie>  searchMovies(String city, String titleQuery)
List<Show>   getShows(String movieId, String cityId, LocalDate date)
SeatMap      getSeatMap(String showId)          // status per seat for UI

# Booking (two-phase — prefer this over one-shot if payment in scope)
Hold         holdSeats(userId, showId, List<String> seatIds)  // → holdId, expiresAt; 409 on conflict
Booking      confirmBooking(holdId, PaymentRequest)           // pay + BOOKED
void         releaseHold(holdId)                              // explicit cancel / timeout path
boolean      cancelBooking(bookingId)

# Admin (optional)
Movie addMovie(...); Cinema addCinema(...); Show addShow(...);

# Facade one-shot (awesome-LLD style demos)
Optional<Booking> bookTickets(userId, showId, seats, PaymentStrategy)
```

### 4. Data model / class diagram
```
MovieBookingService  <<Singleton / Facade>>
 - cities, cinemas, movies, shows, users : ConcurrentHashMap
 - seatLockManager, bookingManager
 + findShows(movieTitle, city)
 + bookTickets / holdSeats / confirmBooking / cancelBooking
 + addCity / addCinema / addMovie / addShow

City 1──* Cinema 1──* Screen 1──* Seat(layout: row,col,SeatType)
Screen 1──* Show          // Show = movie @ screen @ startTime + PricingStrategy
Show 1──* ShowSeat        // inventory: status AVAILABLE|LOCKED|BOOKED, lockedBy, expiresAt
                          // (or Map<seatId, SeatStatus> on Show)

User 1──* Booking
Booking
 - id, user, show, seats, amount, status(PENDING|CONFIRMED|CANCELLED), payment
 + confirm() / cancel()
BookingBuilder            // Builder

SeatLockManager
 - lockedSeats: Map<Show, Map<Seat, userId>>
 - scheduler (TTL unlock)
 + lockSeats(show, seats, userId)   // synchronized(show); all-or-nothing
 + unlockSeats(show, seats, userId) // only if same user + still LOCKED

PricingStrategy <<interface>> → WeekdayPricing / WeekendPricing / CategoryPricing
PaymentStrategy <<interface>> → CardPayment / UpiPayment
MovieObserver (optional) → notify users of new shows

Enums: SeatType, SeatStatus, BookingStatus, PaymentStatus
```
- Sketch this (or the [awesome-lld diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/movieticketbookingsystem-class-diagram.png)) **before** coding. Call out `ShowSeat` if the diagram only shows `Seat`.

### 5. High-level architecture / component breakdown
```
Client
  │ findShows / getSeatMap
  ▼
MovieBookingService (Facade)
  ├─ Catalog maps (City/Cinema/Movie/Show)
  ├─ SeatLockManager ──TTL──► ScheduledExecutor / expiry worker
  └─ BookingManager
        ├─ PricingStrategy.calculate(seats)
        ├─ PaymentStrategy.pay(amount)
        └─ Booking.confirm → seats BOOKED
```
- **SeatLockManager:** only component allowed to transition AVAILABLE↔LOCKED (and timeout release).
- **BookingManager:** orchestrates lock → price → pay → confirm/release.
- **Strategies:** swap pricing/payment without touching the critical section.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Hold-then-pay vs one-shot book:** one-shot is simpler for demos; two-phase is what real ticketing does and what concurrency follow-ups expect.
2. **Per-show lock vs per-seat locks vs DB `FOR UPDATE`:** per-show = simple + correct for LLD; per-seat = more parallelism, deadlock risk (sort seat ids); DB row lock only for *short* txn that sets `LOCKED`+`expires_at`, not for minutes of user input.
3. **In-memory `synchronized` vs Redis + DB:** single JVM → show lock + status enum; multi-instance → Redis TTL hold *plus* conditional DB update / unique `(show_id, seat_id)` booking constraint as final fence (Kleppmann).
4. **Optimistic vs pessimistic:** booking conflicts are **common** on hot shows → pessimistic / atomic conditional update preferred; OCC alone causes sad “pay then fail” UX unless you still hold first.

### 7. Bottlenecks / how you scale it
- Hot show (blockbuster Friday 7pm) → all contention on one `showId`; waiting room / rate limit is HLD — mention, don’t implement in LLD.
- Don’t use one global lock for all cinemas.
- Seat-map reads: cache layout; re-check availability on hold.
- Expiry worker vs payment race: confirm path must be conditional (`WHERE status=LOCKED AND locked_by=?`) so a late payment can’t overwrite BOOKED or steal an expired hold incorrectly; unlock only transitions LOCKED→AVAILABLE.
- Notifications / e-ticket PDF: async after confirm (queue) — out of LLD critical path.

## Common follow-ups / gotchas
- “Two users click the same seats?” — check+lock atomic under per-show lock (or single conditional multi-row update); loser gets failure/409, not a second ticket.
- “User never pays?” — TTL / scheduler releases LOCKED→AVAILABLE; unlock must no-op if already BOOKED or held by another user.
- “Payment succeeds twice (retry)?” — idempotency key / booking id; confirm is conditional on PENDING+held seats.
- “Partial multi-seat success?” — forbidden; all-or-nothing hold, rollback on any unavailable seat.
- “Is `ConcurrentHashMap` enough?” — fine for catalog maps; **seat check-then-act** still needs an explicit critical section / atomic status transition.
- “Screen seats vs show seats?” — layout ≠ inventory; materialize status per show or you double-sell across showtimes.
- “Distributed systems?” — Redis `SET NX PX` for holds + DB as source of truth; don’t claim Redlock alone makes booking correct.

## Where it appears
- **Campus / machine-coding (Flipkart, Uber, Swiggy, Amazon new-grad, Indian product cos):** very common “BookMyShow LLD” — working hold+confirm + clean classes beat a pattern zoo; concurrency often added as the stretch goal after the happy path.
- **Experienced / SDE-2 LLD (FAANG-adjacent, Razorpay, Walmart, BookMyShow):** expected from the start — TTL locks, multi-seat atomicity, payment failure paths; may bridge into HLD (Redis, waiting room).
- **Frequency:** among the top ~10 hard LLD problems (with Splitwise, Chess, Uber); treat as the canonical **concurrency + inventory** OOD question after Parking Lot / Elevator.
)
