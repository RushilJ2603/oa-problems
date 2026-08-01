# LQ14 — Design Food Delivery (Swiggy / Zomato)

**Interview relevance:** High — hard multi-actor LLD / machine-coding staple (campus + SDE-2); Swiggy, Zomato, Flipkart, Uber, Amazon, Dunzo-style loops probe order FSM + delivery assignment + notifications; pairs with HLD ride-hailing / geo matching (hq06) and notification LLD (lq12).
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Singleton / Factory), l03_patterns_structural (Facade), l04_patterns_behavioral (Strategy / Observer / State), l05_concurrency_lld, l06_lld_framework; helpful: hq06_ride_hailing (dispatch/geo), lq12_notification_lld (status fan-out)

## Read / watch (curated, in order)
- [ ] [Design Online Food Delivery Service | LLD](https://algomaster.io/learn/lld/design-online-food-delivery-service) — `AlgoMaster` — clarifying Q&A → FRs (search, place/cancel, auto-assign by proximity, notify on status); payment often out of scope — lock scope before drawing classes
- [ ] [Designing an Online Food Delivery Service Like Swiggy (problem + UML)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/food-delivery-service.md) — `awesome-low-level-design` — **primary sheet problem:** FR checklist, [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/fooddeliveryservice-class-diagram.png), Singleton `FoodDeliveryService` notes (hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design))
- [ ] [Java solution (Strategy + Observer + search filters)](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/fooddeliveryservice) — `awesome-low-level-design` — reference: `FoodDeliveryService` (DCL Singleton + `ConcurrentHashMap`), `DeliveryAssignmentStrategy` / `NearestAvailableAgentStrategy`, `RestaurantSearchStrategy` (city / keyword / proximity), `Order` + `OrderObserver` (also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/fooddeliveryservice) / [C++](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/cpp/fooddeliveryservice) siblings)
- [ ] [Food Delivery System LLD (Swiggy/Zomato)](https://lldhub.in/blog/food-delivery-lld-design) — `lldhub` — compact interview guide: order transition map, Haversine nearest-partner Strategy, Observer notifications, concurrent capacity / double-assign gotchas
- [ ] [Swiggy/Zomato Low Level System Design (UML + code)](https://www.youtube.com/watch?v=XN17WWiUzT4) — `YouTube / Keerti Purswani` — whiteboard split into food subsystem vs delivery subsystem before classes
- [ ] [Food Ordering System using Observer (Zomato/Swiggy)](https://www.youtube.com/watch?v=v9ehOtY_x7Q) — `YouTube` — deep-dive on status fan-out (what interviewers actually probe after the happy path)
- [ ] [Build Zomato Food Delivery App | System Design](https://www.youtube.com/watch?v=2SAUqTn3TrU) — `YouTube / Coder Army` — alternate end-to-end LLD narration (entities → cart/order → assignment)
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) — `Refactoring.Guru` — `DeliveryAssignmentStrategy` + `RestaurantSearchStrategy` (+ optional `PaymentStrategy`) without editing `FoodDeliveryService`
- [ ] [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — customer / restaurant / agent notified on `Order.setStatus` (awesome-LLD `OrderObserver`)
- [ ] [State](https://refactoring.guru/design-patterns/state) — `Refactoring.Guru` — order lifecycle as FSM (enum + transition table is fine in machine coding; State objects if transitions explode)
- [ ] [Singleton](https://refactoring.guru/design-patterns/singleton) / [Facade](https://refactoring.guru/design-patterns/facade) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) — `Refactoring.Guru` — single service entry, thin place/update API, create payment/order adapters from type
- [ ] [Chain of Responsibility](https://refactoring.guru/design-patterns/chain-of-responsibility) — `Refactoring.Guru` — optional framing for sequential search filters (awesome-LLD comment on composing `RestaurantSearchStrategy`s)
- [ ] [ConcurrentHashMap (Java)](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/concurrent/ConcurrentHashMap.html) — `Oracle JDK docs` — thread-safe catalogs; **agent assign still needs an atomic critical section**
- [ ] [Intrinsic Locks and Synchronization](https://docs.oracle.com/javase/tutorial/essential/concurrency/sync.html) — `Oracle` — language baseline for `synchronized` assign / status transition
- [ ] [Redis geospatial](https://redis.io/docs/latest/develop/data-types/geospatial/) / [`GEORADIUS`](https://redis.io/docs/latest/commands/georadius/) / [`GEOSEARCH`](https://redis.io/commands/geosearch/) — `Redis docs` — scale follow-up for nearby restaurants / agents (O(log n) vs linear scan)
- [ ] [Stripe Idempotent requests](https://docs.stripe.com/api/idempotent_requests) — `Stripe` — if payment is in scope: retries must not double-charge
- [ ] [How to Answer a LLD Interview Problem](https://blog.algomaster.io/p/how-to-answer-a-lld-interview-problem) — `AlgoMaster` — clarify → entities → relationships → code skeleton pacing
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [Design Food Delivery Service (HLD)](https://algomaster.io/learn/system-design-interviews/design-food-delivery-service) — `AlgoMaster` — after OOP works: lunch/dinner spikes, geo, dispatch tradeoffs
- [ ] [Food Delivery System Design: Orders, Dispatch & Tracking](https://codelit.io/blog/food-delivery-system-design) — `Codelit` — HLD bridge: order / dispatch / tracking / ETA services + event-driven boundaries
- [ ] [System Design Interview: DoorDash (Educative)](https://www.educative.io/courses/system-design-interview-doordash) — `Educative` — paid HLD depth; component sketch: [Creating the Component Design & Architecture](https://www.educative.io/courses/system-design-interview-doordash/creating-the-component-design-architecture-of-the-system)
- [ ] [Design a Local Delivery Service like Gopuff](https://www.hellointerview.com/learn/system-design/problem-breakdowns/gopuff) — `Hello Interview` — related inventory + nearby-fulfillment HLD (quick-commerce cousin, not restaurant marketplace)
- [ ] [Design DoorDash (asked-at Meta/Amazon)](https://www.hellointerview.com/community/questions/food-delivery-platform/cm5omjbka00023b6q9bfevwjl) — `Hello Interview` — company tags / FR framing; use as “where asked,” not as a full LLD breakdown
- [ ] [Design Ride-Sharing Service (Uber) — sibling problem](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/ride-sharing-service.md) — `awesome-low-level-design` — same matching + Observer muscles; [Ride Sharing LLD guide](https://lldhub.in/blog/ride-sharing-lld-design)
- [ ] [Design Restaurant Management System](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/restaurant-management-system.md) — `awesome-low-level-design` — single-restaurant cousin (menu / order / payment without marketplace dispatch)
- [ ] [Design Restaurant Management System (GfG HLD↔LLD)](https://www.geeksforgeeks.org/system-design/design-restaurant-management-system-system-design/) — `GfG` — client / restaurant-admin / delivery services framing for follow-ups
- [ ] [How to Design a Database for Zomato](https://www.geeksforgeeks.org/dbms/how-to-design-a-database-for-zomato/) — `GfG` — Users / Restaurants / Menu / Orders / Agents tables if interviewer pivots to schema
- [ ] [UML State Machine Diagrams](https://www.geeksforgeeks.org/system-design/unified-modeling-language-uml-state-diagrams/) — `GfG` — how to sketch the order FSM on the whiteboard
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after the happy path + assign path both work

## Core concepts to master
- **Three actors, one order:** `Customer` browses/places; `Restaurant` owns menu + prep status; `DeliveryAgent` fulfills. `Order` is the shared aggregate that coordinates them — don’t put assign logic inside `Restaurant` or notify logic inside `Customer`.
- **Clarify before coding:** multi-city? search by city/cuisine/keyword/proximity? cart across restaurants (usually **no** — one restaurant per order)? payment in scope? cancel rules? auto-assign vs agent accept? live GPS tracking?
- **Order FSM (the heart of the problem):** typical awesome-LLD path: `PENDING → CONFIRMED → PREPARING → READY_FOR_PICKUP → OUT_FOR_DELIVERY → DELIVERED` (+ `CANCELLED`). Enforce **allowed transitions** (table/map); reject illegal jumps (e.g. `PREPARING → PENDING`).
- **Cancel window:** usually only while `PENDING` / `CONFIRMED` (before kitchen starts). After `PREPARING`, cancel needs refund/policy — call out, don’t invent silently.
- **Patterns that earn points:** **Facade + Singleton** (`FoodDeliveryService`), **Strategy** (assignment + search + optional payment/pricing), **Observer** (status → customer/restaurant/agent), **State/FSM** (order lifecycle), optional **Factory** (payment/order creation), optional **CoR** for search filter pipelines.
- **Assignment Strategy:** `findAgent(order, agents) → Optional<Agent>` — default = nearest **available** to restaurant (Haversine). Mark agent busy **atomically** with the assign; release on deliver/cancel. Swap for “least-loaded” / “highest-rated” without editing the facade.
- **Search Strategy:** compose filters (`SearchByCity`, `SearchByMenuKeyword`, `SearchByProximity`) over restaurant list — OCP for new filters.
- **Notifications ≠ OrderService:** on status change, notify observers / push service; don’t `import SMSClient` inside `Order.updateStatus`.
- **Concurrency checklist:** (1) two orders must not get the **same** agent; (2) menu item availability / restaurant capacity under concurrent place; (3) status transitions race-free; (4) `ConcurrentHashMap` for catalogs is fine — **check-then-act on agent.available still needs a lock / CAS**.
- **Key methods to name:** `registerCustomer/Restaurant/DeliveryAgent`, `searchRestaurants(strategies)`, `getRestaurantMenu`, `placeOrder(customerId, restaurantId, items)`, `updateOrderStatus`, `cancelOrder`, `assignDelivery` (private, triggered on `READY_FOR_PICKUP` or `ACCEPTED` depending on product rule).
- **Out of scope until asked:** real PGW, surge pricing, batching multi-order routes, ETA ML, ratings UI, partner APIs, Instamart/dark stores (those are HLD / Codelit / Educative DoorDash).

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~35–45 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **Clarify first:** marketplace vs single restaurant? auto-assign timing (on place vs on ready)? cancel rules? payment? multi-item from one restaurant only?
- **FR (typical):** register customers / restaurants / agents; restaurants manage menu (add/remove/availability/price); customers search restaurants + view menu; place order of N items; restaurant updates prep status; system assigns delivery agent; track status to delivered; cancel early; notify parties on status change.
- **Use cases:** (1) Browse → place → restaurant accepts → prepare → ready → agent assigned → deliver; (2) Two orders race one agent → exactly one wins; (3) Customer cancels while PENDING; (4) No agents available → order stays ready, retry/queue; (5) Menu item goes unavailable mid-browse → fail at place, not after pay.
- **NFR:** thread-safe under concurrent orders; extensible assignment/search/payment; modular services (not one god class); status updates reach observers promptly (demo = sync notify).
- **Assumptions to state:** e.g. one city demo, in-memory OK, payment mocked/auto, Haversine distance, assign on `READY_FOR_PICKUP`, cancel only from `PENDING`.

### 2. Back-of-envelope estimation (usually light for LLD)
- **LLD:** skip city-wide QPS math. State knobs you’ll code against (`numRestaurants`, `numAgents`, linear scan OK for demo).
- If pushed toward HLD: lunch/dinner peaks; geo index for agents; event bus between order/dispatch/notify — see AlgoMaster HLD / Codelit / Educative DoorDash / hq06.

### 3. API / interface
```
# Registration / catalog
Customer      registerCustomer(name, phone, Address)
Restaurant    registerRestaurant(name, Address)
DeliveryAgent registerDeliveryAgent(name, phone, Address)
void          addMenuItem(restaurantId, MenuItem) / updateAvailability(...)
List<Restaurant> searchRestaurants(List<RestaurantSearchStrategy> filters)
Menu          getRestaurantMenu(restaurantId)

# Order lifecycle
Order  placeOrder(customerId, restaurantId, List<OrderItem>)
void   updateOrderStatus(orderId, OrderStatus)   // restaurant / system driven
void   cancelOrder(orderId)                      // allowed only in early states
Order  getOrder(orderId)

# Assignment (usually internal)
Optional<DeliveryAgent> findAgent(Order, List<DeliveryAgent>)  // Strategy
```

### 4. Data model / class diagram
```
FoodDeliveryService  <<Singleton / Facade>>
 - customers, restaurants, deliveryAgents, orders : ConcurrentHashMap
 - assignmentStrategy : DeliveryAssignmentStrategy
 + register* / searchRestaurants / placeOrder / updateOrderStatus / cancelOrder
 + assignDelivery(order)   // private; on READY_FOR_PICKUP

Customer / Restaurant / DeliveryAgent  <|-- User? (optional shared base)
Restaurant 1──1 Menu 1──* MenuItem (id, name, price, available)
Customer 1──* Order (history)

Order
 - id, customer, restaurant, items: List<OrderItem>, status, deliveryAgent?
 - observers: List<OrderObserver>
 + setStatus(s) → validate transition + notifyObservers()
 + cancel() / assignDeliveryAgent(agent)
OrderItem (menuItem, qty)
OrderStatus enum: PENDING | CONFIRMED | PREPARING | READY_FOR_PICKUP
                  | OUT_FOR_DELIVERY | DELIVERED | CANCELLED

DeliveryAssignmentStrategy <<interface>>
  → NearestAvailableAgentStrategy (Haversine to restaurant)
RestaurantSearchStrategy <<interface>>
  → SearchByCity / SearchByMenuKeyword / SearchByProximity

OrderObserver <<interface>> → Customer, Restaurant, DeliveryAgent implement onUpdate(Order)

Address / GeoPoint (lat, lon, distanceTo)
PaymentStrategy (optional extension) → Card / UPI / Wallet
```
- Sketch this (or the [awesome-lld diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/fooddeliveryservice-class-diagram.png)) **before** coding. Call out the transition table even if the starter code only sets status.

### 5. High-level architecture / component breakdown
```
Client
  │ search / placeOrder / cancel / (restaurant) updateStatus
  ▼
FoodDeliveryService (Facade)
  ├─ Catalog maps (Customer / Restaurant / Agent / Order)
  ├─ RestaurantSearchStrategy*  (compose filters)
  ├─ Order (FSM + Observer fan-out)
  └─ DeliveryAssignmentStrategy
        └─ on READY_FOR_PICKUP → findAgent → mark busy → OUT_FOR_DELIVERY
```
- **Order owns lifecycle + observers;** service owns registries + when to invoke assignment.
- **Strategies** keep search/assign swappable (OCP).
- **Don’t** put Redis/Kafka in the LLD diagram unless asked — mention as scale follow-up.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **When to assign the agent:** on `placeOrder` (agent waits at restaurant) vs on `READY_FOR_PICKUP` (less idle time). State the product rule; awesome-LLD assigns on ready.
2. **Linear nearest scan vs geo index:** Haversine over all available agents is correct for LLD demos; production → Redis GEO / quadtree (hq06 toolkit) for O(log n) radius queries.
3. **Enum FSM vs State pattern objects:** enum + `VALID_TRANSITIONS` map ships fast and is interview-standard; full State classes only if behavior per state diverges heavily.
4. **Singleton service vs DI:** tutorials use `getInstance()`; say you’d inject one instance for tests unless interviewer wants classic Singleton.

### 7. Bottlenecks / how you “scale” it (LLD → HLD bridge)
- Hot path = **assign under dinner rush** → don’t hold a global lock for all cities; lock per agent or CAS `available`; optionally shard agents by geo-cell.
- Search/browse can be stale briefly; **place + assign + status must be consistent**.
- Notifications / push / SMS: async after status commit (queue) — out of LLD critical path (lq12).
- Restaurant capacity / item stock: atomic decrement or reject when over capacity (lldhub follow-up).
- Live tracking: agent GPS pings ≠ order writes; buffer locations (Redis) and push via WebSocket — HLD only unless asked.

**Timed drill:** implement register + place + status FSM + nearest assign + Observer notify in 60–75 min; then add cancel rules and a note on agent double-assign.

## Common follow-ups / gotchas
- “Two orders, one agent?” — filter `available`, assign + `setAvailable(false)` under one critical section / CAS; loser retries or waits.
- “Restaurant rejects after place?” — transition to `CANCELLED` (from `PENDING`/`CONFIRMED`), notify customer, trigger refund if payment captured.
- “Customer cancels while PREPARING?” — usually deny or escalate to support/refund policy; don’t allow silent cancel.
- “No agents online?” — leave order in `READY_FOR_PICKUP`, retry/queue; don’t mark `OUT_FOR_DELIVERY` without an agent.
- “Is `ConcurrentHashMap` enough?” — fine for id→entity maps; **agent availability check-then-act** still needs explicit sync.
- “Add surge / VIP assignment / batching?” — new `DeliveryAssignmentStrategy`; don’t `if`-ladder inside the facade.
- “Payments?” — `PaymentStrategy.pay` before confirming; idempotency key on retries (Stripe docs); failure → don’t advance FSM.
- “Live map tracking?” — separate location stream; Observer/WebSocket on location updates, not on every menu read.
- Gotcha: god-class `FoodDeliveryService` that also prices, pays, routes, and SMS — split SRP or interviewer docks design score.
- Gotcha: finishing Strategy zoo but failing mandatory place → status → assign → deliver demo — mandatory first.

## Where it appears
- **Campus / machine-coding (Swiggy, Zomato, Flipkart, Uber, Amazon new-grad, Indian product cos):** common “design Swiggy/Zomato LLD” — working order FSM + nearest assign + clean classes beat a pattern zoo; concurrency/notifications often the stretch after the happy path.
- **Experienced / SDE-2:** expected from the start — valid transitions, atomic agent assign, Observer decoupling, Strategy for search/assign; may bridge into HLD (Redis GEO, dispatch queues, dinner-peak scaling).
- **FAANG-adjacent OOD:** “design a food delivery / DoorDash-like app” whiteboard (Meta/Amazon tags on Hello Interview); focus on clarifying multi-actor flows + class model more than CLI I/O.
- **Frequency:** among the top hard LLD problems with Movie Booking, Ride Sharing, and Splitwise — treat as the canonical **multi-party workflow + Strategy matching + Observer** question after Parking Lot / Elevator.
)
