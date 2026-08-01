# hq11_booking — Design a Booking System (Ticketmaster / BookMyShow, seat locking)

**Interview relevance:** High — canonical HLD for contention + inventory; campus + FAANG / Indian product cos (Amazon, Flipkart, Uber, Atlassian, BookMyShow-style rounds); also maps to hotels/airlines.
**Type:** HLD-question
**Prereqs:** h06_consistency_cap, h03_caching, h04_databases_indexing, h05_db_scaling, h08_message_queues, h10_api_design, h14_estimation; helpful: h02_load_balancing, h09_rate_limiting, h01_networking

## Read / watch (curated, in order)
- [ ] [Design a Ticket Booking Site Like Ticketmaster](https://www.hellointerview.com/learn/system-design/problem-breakdowns/ticketmaster) — `Hello Interview` — best free junior→mid walkthrough: FRs/NFRs → entities → API → reserve+pay → Redis TTL lock vs DB status → virtual waiting room; pair with video [Design Ticketmaster (ex-Meta Staff)](https://www.youtube.com/watch?v=fhdPyoO6aXI)
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — 45-min skeleton you reuse (FRs → NFRs → entities → API → HLD → deep dives)
- [ ] [CAP Theorem](https://www.hellointerview.com/learn/system-design/core-concepts/cap-theorem) — `Hello Interview` — **CP for booking, AP for browse/search** (Ticketmaster called out as the textbook split)
- [ ] [Redis Deep Dive (distributed locks section)](https://www.hellointerview.com/learn/system-design/deep-dives/redis) — `Hello Interview` — `SET NX EX`, why Redis lock ≠ correctness guarantee, Redlock caveats
- [ ] [Key Technologies — Distributed Locks](https://www.hellointerview.com/learn/system-design/in-a-hurry/key-technologies) — `Hello Interview` — short framing of ~10 min ticket holds vs DB transaction locks
- [ ] [Online Ticketing Platform (ByteByteGo newsletter EP34)](https://blog.bytebytego.com/p/ep34-session-cookie-jwt-token-sso) — `ByteByteGo` — free visual: China 12306-style peak booking (separate read/write, in-memory remaining inventory, bot bans, multi-DC) after Ticketmaster/Taylor Swift demand
- [ ] [Ticketmaster System Design (Grokking / Educative)](https://www.educative.io/courses/grokking-the-system-design-interview/ticketmaster-system-design) — `Grokking / Educative` — classic paid chapter: estimation, reserve/confirm APIs, optimistic vs pessimistic vs distributed locking
- [ ] [BookMyShow System Design](https://www.educative.io/blog/bookmyshow-system-design) — `Educative` — free blog: AVAILABLE → HELD → BOOKED state machine, time-bound holds, payment idempotency framing
- [ ] [Design BookMyShow](https://www.geeksforgeeks.org/system-design/design-bookmyshow-a-system-design-interview-question/) — `GfG` — Indian-interview staple: theatre integration, 5–10 min seat block, Redis lock + async ticket/notification workers
- [ ] [System Design | BookMyShow (The Tech Granth)](https://www.youtube.com/watch?v=6UAlDIzqhBo) — `The Tech Granth` — short Hindi/English HLD pass focused on concurrency + DB choice
- [ ] [11: Design TicketMaster/StubHub (Ex-Google SWE)](https://www.youtube.com/watch?v=sMgxHf9AU_U) — `Jordan has no life` — alternate full whiteboard if you want a second narration
- [ ] [Airbnb / Booking.com System Design (codeKarle)](https://www.youtube.com/watch?v=YyOXt2MEkv4) — `codeKarle` — cousin problem (hotel inventory holds); useful for booking-service + RDBMS transaction talk; notes/diagrams: [codekarle/system-design](https://github.com/codekarle/system-design)
- [ ] [System Design playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — foundations (scale, cache, consistency) you name inside this design; further dump: [InterviewReady system-design-resources](https://github.com/InterviewReady/system-design-resources); course site: [interviewready.io](https://interviewready.io/)
- [ ] [Distributed locks with Redis](https://redis.io/docs/latest/develop/clients/patterns/distributed-locks/) — `Redis docs` — canonical `SET resource token NX PX …` + safe release; Redlock algorithm reference
- [ ] [How to do distributed locking (Martin Kleppmann)](https://martin.kleppmann.com/2016/02/08/how-to-do-distributed-locking.html) — `DDIA author` — why Redis/Redlock alone is not a correctness fence; fencing tokens / DB as truth
- [ ] [PostgreSQL Explicit Locking (`SELECT FOR UPDATE`)](https://www.postgresql.org/docs/current/explicit-locking.html) — `Postgres docs` — row locks are for **short** transactions; docs warn against holding locks while waiting for user input
- [ ] [Stripe Idempotent requests](https://docs.stripe.com/api/idempotent_requests) — `Stripe` — `Idempotency-Key` so payment retries do not double-charge
- [ ] [Technical takeaways from the Taylor Swift/Ticketmaster meltdown](https://www.cockroachlabs.com/blog/taylor-swift-ticketmaster-meltdown/) — `Cockroach Labs` — real peak framing (~14M users, ~3.5B requests); capacity planning / bot flood / bottleneck lesson
- [ ] [Queue-it (virtual waiting room)](https://queue-it.com/) — `industry` — production pattern Ticketmaster-style onsales use: admit users at a controlled rate before inventory
- [ ] [Movie Ticket Booking LLD (Hello Interview)](https://www.hellointerview.com/learn/low-level-design/problem-breakdowns/bookmyshow) — `Hello Interview` — optional LLD crossover after HLD (classes, concurrent seat booking)

## Core concepts to master
- **Split consistency by path:** **browse/search/event page = AP** (stale seat map OK for seconds); **hold + confirm = CP / strong consistency** (never sell the same seat twice). Say this in NFRs first.
- **Seat state machine:** `AVAILABLE → HELD (reserved) → BOOKED` (sold). Hold is time-bound (typical interview **5–10 min**). Abandoned checkout must free inventory without a human sweeper being on the critical path.
- **Two-phase booking:** (1) **reserve/hold** seats → return `bookingId` + timer; (2) **confirm** after payment success. Never charge then discover the seat is gone without a refund path.
- **Lock options (tradeoffs):** (1) long-running `SELECT FOR UPDATE` while user pays — **bad** (holds DB connections for minutes); (2) DB `status` + `expires_at` with short txn / lazy reclaim — **good**; (3) Redis `SET seat:{event}:{seat} {owner} NX EX ttl` — **great** for speed + auto-expiry; (4) DB unique constraint / OCC on confirm — **final safety net**.
- **Redis lock is an efficiency layer, not truth:** Postgres/MySQL (or conditional write) must still reject double-sell. If Redis dies, UX degrades (pay then fail) but correctness holds. Cite Kleppmann if interviewer pushes Redlock.
- **Multi-seat atomicity:** hold all seats or none (Lua / ordered lock acquisition + rollback). Partial holds create orphaned inventory and bad UX.
- **Flash / onsale load:** virtual **waiting room** (Redis ZSET FIFO or product like Queue-it) admits N users/sec so booking + DB are not thundering-herded. SSE/WebSocket for queue position; admission token checked on hold API.
- **Seat-map freshness:** cache event/venue aggressively; treat live availability carefully (short TTL, SSE push, or “informational + re-check on hold”). Never let a stale green seat skip the atomic hold.
- **Payments:** external gateway + **idempotency keys**; saga-style compensate (release hold / refund) on failure or TTL expiry mid-payment. Notifications/PDF tickets go **async** (queue) off the confirm path.
- **Hot partition:** shard/partition inventory by `event_id` / `show_id` so one Taylor Swift onsale does not melt the whole cluster — but one event still needs a waiting room because that shard is inherently hot.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈40–45 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (core):** browse/search events; view seat map + availability; select seats and **hold**; pay and **confirm** booking; view confirmation / ticket.
- **FR (optional / ask):** cancel/refund, waitlist, dynamic pricing, admin create events, multi-city cinema aggregator (BookMyShow), Verified Fan / bot gates.
- **NFR:** **no double-booking**; booking path strongly consistent; browse highly available; hold window ~10 min; survive onsale spikes (millions concurrent); search latency ≪ 500 ms; read-heavy outside onsale.
- **Clarify:** movie shows vs concerts? assigned seats vs GA? peak QPS? hold TTL? payment in-scope?

### 2. Back-of-envelope estimation
State assumptions out loud (replace with interviewer's numbers):
- **Steady state:** e.g. 100M DAU × 100 req/user/day → huge browse QPS; **booking writes ≪ reads** (~100:1 outside onsale).
- **Onsale spike:** 1 popular event, 50k–100k seats, **millions** concurrent users at T0 (Taylor Swift-class: ~14M users / multi-billion requests cited publicly). Booking confirm rate may only be thousands/min — **queue must absorb the rest**.
- **Storage:** venues/events small; per-seat ticket rows dominate (stadium × shows). Example: 1k cities × 5 venues × 1k seats × 2 shows/day ≈ manageable tens of millions of seat-rows/year; booking rows ~100 B each.
- Implication: **cache + waiting room + Redis holds** matter more than “buy a bigger SQL box.”

### 3. API / interface
- `GET /events/{eventId}` → event + venue + seat map metadata (+ ticket statuses or availability overlay)
- `GET /events/search?keyword=&city=&from=&to=&page=` → `Event[]`
- `POST /events/{eventId}/holds` body: `{ "seatIds": ["A1","A2"] }` → `{ "holdId", "expiresAt" }` — **409** if any seat taken
- `POST /bookings` body: `{ "holdId", "paymentMethodId" }` (or payment intent confirm) → `{ "bookingId", "tickets" }` — idempotent
- Optional: `DELETE /holds/{holdId}`, `GET /bookings/{bookingId}`, `GET /queue/{eventId}` (position)
- Auth user from token; never trust `userId` in body for ownership of a hold.

### 4. Data model
```
event(id PK, venue_id, title, starts_at, status, ...)
venue(id PK, name, seat_map_json, capacity, ...)
ticket(id PK, event_id, section, row, seat, price_cents,
       status ENUM('available','held','booked'),
       hold_id NULL, hold_expires_at NULL, version INT)
       UNIQUE(event_id, section, row, seat)
booking(id PK, user_id, event_id, status, total_cents, created_at, ...)
booking_seat(booking_id, ticket_id)  UNIQUE(ticket_id)  -- final no-double-sell
hold / Redis: key seat:{eventId}:{ticketId} = {userId|holdId}, TTL 600s
```
- Index `(event_id, status)` / compound for seat-map queries; search often offloaded to Elasticsearch via CDC.
- Payment intents + idempotency keys live with payments, not on the seat-map hot path.

### 5. High-level architecture
```
Client → CDN / Edge (static + bot challenges)
       → LB / API Gateway (auth, rate limit)
       ├─ Search Service → Elasticsearch
       ├─ Event Service → Cache → Events DB (AP-friendly reads)
       ├─ Waiting Room (optional, Redis ZSET) → admit token
       ├─ Booking Service → Redis seat locks → Tickets/Bookings DB (Postgres)
       │                 → Payment Gateway (idempotent)
       └─ async: Queue → Notification / Ticket PDF workers
```
- Stateless app tier; **Booking** fleet sized for admitted users only.
- Postgres (or equivalent ACID store) = source of truth for sold seats; Redis = ephemeral holds + queue.

### 6. Deep dives & the 2–3 key tradeoffs interviewers probe
1. **How do you prevent double-booking?** Prefer Redis `SET NX EX` hold + short DB txn on confirm with `UNIQUE(ticket_id)` / `UPDATE … WHERE status='held' AND hold_id=?` (OCC). Call out why multi-minute `SELECT FOR UPDATE` is wrong. Mention refund if TTL races payment.
2. **Hold in Redis vs status columns in DB:** Redis = auto TTL + speed; DB status = simpler single store, needs sweeper or lazy expiry checks. Hybrid (Redis TTL + write-through held flag) is a common senior answer.
3. **Waiting room vs “just scale horizontally”:** inventory is finite and contended — more servers do not create more seats; admission control + fairness beat blind autoscale (bots/cost). SSE seat-map updates help medium events; mega onsales need the queue **before** the map.
4. **Optimistic vs pessimistic locking on confirm:** OCC/version under moderate contention; under blockbuster contention, fail fast on hold acquisition and keep confirm txn tiny.

### 7. Bottlenecks / how you scale it
- **Onsale thundering herd:** waiting room + edge rate limits + bot mitigation; do not let millions hit hold API.
- **Hot event shard:** partition by `event_id`; accept that one event is hot — protect it with queue + Redis, not infinite SQL connections.
- **Seat-map read QPS:** CDN/cache event+venue; availability overlay from Redis sets or short-TTL cache; optional SSE fan-out via pub/sub.
- **Payment / notification latency:** never block confirm response on email/SMS; queue workers. Extend hold TTL when payment starts.
- **Failure modes:** Redis down → degrade holds (or fail closed on hold) but keep DB uniqueness; payment success + booking fail → reconcile job + refund; expired hold after charge → refund path.
- **Search:** do not `LIKE '%Taylor%'` on primary; Elasticsearch + CDC.

## Common follow-ups / gotchas
- “Two users click the same seat at once — who wins?” → atomic hold (`SET NX` / conditional DB update); loser gets 409; seat map should refresh.
- “User closes the tab mid-checkout?” → TTL expiry releases seat; no dependency on client `unload`.
- “Payment succeeds after hold expired and someone else booked?” → confirm txn fails; **automatic refund**; ideally extend lock when payment begins.
- “Is Redlock required?” → usually no for interviews; single Redis + DB fence is the expected answer; know Kleppmann’s critique if they push.
- “GA / quantity inventory vs assigned seats?” → counter/`DECR` with floor at 0 (still atomic) vs per-seat keys; same two-phase hold idea.
- “BookMyShow vs theatre’s own inventory?” → aggregator either reserved allotment or live API to theatre; still need local hold TTL so the seat is blocked across channels for ~10 min.
- Drawing caches of “available seats” as source of truth — interviewer will force a double-book scenario; cache is advisory.

## Where it appears
- **Campus / intern / new-grad HLD:** very common as “BookMyShow / Ticketmaster / movie booking”; expects seat lock + payment window + basic scale.
- **Experienced (1–4 YOE):** same prompt; depth shifts to waiting rooms, Redis vs DB correctness, payment sagas/idempotency, hot-event isolation, bot/fairness.
- **Frequency:** among the **top contention/inventory** HLD questions — practice alongside URL shortener and rate limiter; LLD twin is movie ticket booking (classes + concurrency).
