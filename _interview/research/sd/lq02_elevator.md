# LQ02 — Design an Elevator System

**Interview relevance:** High — staple LLD / machine-coding question (campus + experienced); tests OOP modeling, Strategy/State, scheduling (LOOK/SCAN), and concurrency at Flipkart, Uber, Amazon, Google, Microsoft, Atlassian-style loops.
**Type:** LLD-question
**Prereqs:** L01 (OOP & SOLID), L02 (creational), L03 (structural — Facade); behavioral patterns Strategy / State / Observer (Refactoring.Guru links below)

## Read / watch (curated, in order)
- [ ] [Elevator Low Level Design (Hello Interview)](https://www.hellointerview.com/learn/low-level-design/problem-breakdowns/elevator) — `Hello Interview` — best free clarifying-questions → entities → `step()` simulation walkthrough; direction-aware hall calls vs cabin destinations
- [ ] [Low-Level Design Interview: Design an Elevator (video)](https://www.youtube.com/watch?v=fODT0ldeBiU) — `Hello Interview` — Ex-Meta Staff Engineer whiteboard of the same problem; watch after (or with) the article
- [ ] [Designing an Elevator System (problem + diagram)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/elevator-system.md) — `awesome-low-level-design` — requirements checklist + [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/elevatorsystem-class-diagram.png); primary sheet problem
- [ ] [Java solution (Strategy + State + Observer)](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/elevatorsystem) — `awesome-low-level-design` — reference code: `ElevatorSelectionStrategy`, `IdleState` / `MovingUpState` / `MovingDownState`, display observers (also Python / C++ / C# / Go siblings)
- [ ] [Design Elevator System | LLD](https://algomaster.io/learn/lld/design-elevator-system) — `algomaster` (via awesome-lld) — FIFO vs SCAN vs LOOK intuition; pluggable dispatch; thread-per-elevator NFR framing
- [ ] [Elevator algorithm (SCAN)](https://en.wikipedia.org/wiki/Elevator_algorithm) — `Wikipedia` — why “serve current direction then reverse” exists; pair with [LOOK algorithm](https://en.wikipedia.org/wiki/LOOK_algorithm) (reverse at last pending request, not shaft end)
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) — `Refactoring.Guru` — swap `NearestElevator` / `LeastBusy` / zoning without editing the controller
- [ ] [State](https://refactoring.guru/design-patterns/state) — `Refactoring.Guru` — Idle / MovingUp / MovingDown (/ DoorOpen) as objects so transitions aren’t a giant `switch`
- [ ] [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — cabin/floor displays subscribe to floor/direction changes; elevator must not `new Display()`
- [ ] [Command](https://refactoring.guru/design-patterns/command) — `Refactoring.Guru` — optional: button presses as command objects (queue / log); don’t force if a simple `Request` DTO suffices
- [ ] [Elevator System | Google SWE Teaches LLD Ep.3](https://www.youtube.com/watch?v=4OjHA-BcJhw) — `Jordan has no life` — alternate mock-style pass focused on scheduling tradeoffs
- [ ] [Elevator System Design (OOD)](https://www.youtube.com/watch?v=siqiJAJWUVg) — `Think Software` — Grokking-shaped OOD narration if you want a second video voice
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo (Flipkart/Uber/Swiggy style)
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD problem index after you can code the happy path

## Core concepts to master
- **Two request kinds:** **hall call** = `(floor, direction UP|DOWN)`; **cabin call** = destination floor only. Stopping rules differ — an UP car should not pick a DOWN hall call “on the way.”
- **Roles:** `ElevatorController` (or dispatcher) assigns hall calls; each `Elevator` owns movement + its pending stops. Floors are usually `int`s, not classes, unless you need per-floor panels/displays.
- **LOOK (interview default):** keep serving pending stops in the current direction; reverse only when none remain ahead (vs **SCAN**, which rides to the shaft end; vs **FIFO**, which zigzags). Implement with two ordered structures (e.g. min-heap / `TreeSet` for UP, max-heap for DOWN).
- **Dispatch = Strategy:** `selectElevator(elevators, request)` — start with nearest car that is idle or already moving toward the caller; keep the algorithm swappable (OCP).
- **Elevator motion = State (or a clean enum FSM):** Idle ↔ MovingUp ↔ MovingDown (± DoorOpen / Maintenance). State objects (or a disciplined enum) beat nested `if`s when interviewers add door/emergency transitions.
- **Displays = Observer:** elevators publish floor/direction; hall/cabin displays subscribe — elevator stays unaware of UI.
- **Simulation vs threads:** most LLD rounds want a deterministic `step()` / `tick()` that advances every car one floor. Experienced / concurrency follow-ups want **one thread (or actor) per elevator** + thread-safe request queues.
- **Concurrency hotspots:** controller reads `currentFloor`/`direction` while cars mutate them → `volatile` or locked getters; `addRequest` must be synchronized with the car’s consume loop; never share one mutable queue across cars without locking.
- **Cost function for assignment:** distance + directional compatibility + pending-load; “closest idle” alone can stampede one car under bursty lobby traffic.
- **Out of scope until asked:** weight sensors, door timing FSMs, emergency/fire mode, destination-dispatch panels, multi-building banks — call them out early.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈35–45 min LLD / machine-coding):

### 1. Requirements (functional + non-functional) & scale assumptions
- **Clarify first:** simulation (`step()`) vs real-time threads? classic up/down hall buttons vs destination dispatch? capacity / doors / emergency in scope?
- **FR (typical):** N elevators, M floors; hall call `(floor, dir)`; cabin select destination(s); assign a car; cars move, stop, reverse using LOOK; optional floor/cabin displays.
- **NFR:** correct direction-aware stopping; no lost requests; thread-safe if concurrent; extensible dispatch strategy; testable without hardware.
- **Assumptions to state:** e.g. 3 cars, floors 0–9; reject invalid floors; same-floor request = no-op; doors abstracted unless asked.

### 2. Back-of-envelope estimation (for HLD)
- **LLD:** skip capacity math. State only scale knobs you’ll code against (`numElevators`, `numFloors`) and that dispatch is O(E) per hall call, LOOK ops are O(log F) per add/stop with heaps/`TreeSet`.

### 3. API / interface
```
// External / hall
boolean requestElevator(int floor, Direction dir)   // or RequestType.PICKUP_UP/DOWN

// Internal / cabin
boolean selectFloor(int elevatorId, int destinationFloor)

// Simulation (preferred in most LLD rounds)
void step()   // advance all elevators one tick

// Optional queries for tests / UI
int getCurrentFloor(int elevatorId)
Direction getDirection(int elevatorId)
```
- Immediate-dispatch model: controller picks a car and calls `elevator.addRequest(...)`. Alternative: pending global queue that idle cars pull from — mention if “all cars busy” comes up.

### 4. Data model / class diagram
```
ElevatorSystem / Building          // thin Facade entry (optional)
 └─ ElevatorController
      - elevators: List<Elevator>
      - strategy: ElevatorSelectionStrategy
      + requestElevator(floor, dir)
      + selectFloor(elevatorId, floor)
      + step()

ElevatorSelectionStrategy <<interface>>
 └─ NearestElevatorStrategy / LeastBusyStrategy

Elevator
 - id, currentFloor, direction (UP|DOWN|IDLE)
 - upStops: SortedSet / min-heap
 - downStops: SortedSet / max-heap
 - state: ElevatorState                 // optional State pattern
 - observers: List<ElevatorObserver>    // optional displays
 + addRequest(Request)
 + step() / run()                       // simulation tick or thread loop
 + getCurrentFloor() / getDirection()

Request
 - floor, type (PICKUP_UP | PICKUP_DOWN | DESTINATION)
   // equals/hash on (floor, type) so UP≠DOWN hall at same floor

ElevatorState <<interface>> → IdleState, MovingUpState, MovingDownState
ElevatorObserver <<interface>> → HallDisplay, CabinDisplay
Direction, RequestSource / RequestType  // enums
```
- Sketch this UML (or the [awesome-lld diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/elevatorsystem-class-diagram.png)) before coding.

### 5. High-level architecture / component breakdown
```
HallPanel / CabinPanel
        │
        ▼
 ElevatorController  ──strategy──►  selectElevator(...)
        │ assign Request
        ▼
   Elevator (×N)  ──LOOK queues──►  move / stop / reverse
        │ notify
        ▼
   Displays (Observer)
```
- **Controller:** system coordination only — no per-floor motor logic.
- **Elevator:** autonomous LOOK server of its own stops.
- **Strategy / State / Observer:** plug points for the “extend without editing” follow-ups.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **FIFO vs SCAN vs LOOK:** FIFO wastes travel; SCAN overshoots empty extremes; LOOK is the usual interview sweet spot — implement with dual ordered sets.
2. **Floor-only stops vs typed `Request`:** floor sets are simpler but stop UP cars for DOWN hall calls; typed requests fix passenger-facing direction correctness.
3. **`step()` simulation vs thread-per-elevator:** simulation is deterministic and interview-friendly; threads show concurrency maturity — protect queues + published floor/direction.
4. **Immediate assign vs global pending queue:** immediate is simpler; queued assign helps when every car is saturated or you want re-balancing.

### 7. Bottlenecks / how you scale it
- Hot lobby / morning up-peak → zoning (cars prefer floor ranges), express shafts, or destination-dispatch (passenger enters destination before boarding).
- Many floors / cars → keep assign O(E), movement O(log F); avoid scanning all pending floors linearly each tick.
- Fairness: track wait time so nearest-car doesn’t starve far floors; mention peak-mode strategies if asked “how do real buildings do it?”

## Common follow-ups / gotchas
- “Hall UP and hall DOWN on the same floor — one stop or two?” — treat as **two request types**; only stop when car direction matches (unless destination).
- “New request appears while moving — do you stop?” — LOOK: if it’s ahead in current direction, yes; else queue for the reverse pass.
- “Starvation / always-busy lobby?” — aging / max-wait, peak modes, or destination dispatch; nearest-only can ping-pong.
- “Thread safety?” — sync `addRequest` with the mover; make floor/direction visible to the dispatcher (`volatile` / locked reads); no shared mutable stop set across cars.
- “Doors / capacity / emergency?” — add `DoorOpen` state + capacity check on boarding; emergency overrides strategy (e.g. force ground) — only if interviewer expands scope.
- “State vs Strategy?” — Strategy = interchangeable *algorithms* (dispatch); State = behavior that *changes with internal mode* and often triggers the next transition.

## Where it appears
- **Campus / machine-coding (Flipkart, Uber, Swiggy, Amazon new-grad, Indian product cos):** very common “design + code in 90 min” — working LOOK + clean classes beat a half-finished pattern zoo.
- **Experienced LLD (FAANG / Atlassian / Microsoft):** same core, deeper probes on concurrency, direction-aware stopping, and pluggable dispatch; sometimes compared to parking-lot / traffic-light FSMs.
- **Frequency:** among the top ~10 canonical LLD problems (with parking lot, Splitwise, rate limiter, Tic-Tac-Toe); expect it if your sheet’s LLD track is interview-realistic.
