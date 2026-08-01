# LQ18 — Design a Meeting Scheduler / Calendar

**Interview relevance:** High — staple LLD / OOD whiteboard (and occasional machine-coding) question; Amazon, Microsoft, Google/Meta-style loops, Qualcomm, Atlassian, and Indian product cos use it to probe interval conflict detection, room allocation Strategy, Observer notifications, recurrence, and the double-booking race.
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Singleton / Factory), l03_patterns_structural (Facade), l04_patterns_behavioral (Strategy / Observer; State optional for booking lifecycle), l05_concurrency_lld; treat Google Calendar HLD (sharding, sync) as a stretch — do not substitute it for class design

## Read / watch (curated, in order)
- [ ] [Getting Ready: The Meeting Scheduler Problem](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/getting-ready-the-meeting-scheduler-problem) — `Educative / Grokking OOD` — **start here:** problem framing (room assignment + attendee availability + lifecycle + notifications); course hub: [Grokking the Low Level Design Interview Using OOD Principles](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles)
- [ ] [Requirements for the Meeting Scheduler](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/requirements-for-the-meeting-scheduler) — `Educative / Grokking OOD` — FR checklist (capacity, booking rules, participants, notifications) before you invent scope
- [ ] [Use Case Diagram for the Meeting Scheduler](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/use-case-diagram-for-the-meeting-scheduler) — `Educative / Grokking OOD` — Organizer vs Participant actors; schedule / invite / RSVP / cancel / calendar-update flows
- [ ] [Class Diagram for the Meeting Scheduler](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/class-diagram-for-the-meeting-scheduler) — `Educative / Grokking OOD` — bottom-up UML: `User`, `Interval`, `MeetingRoom`, `Meeting`, `Calendar`, `MeetingScheduler`, `Notification` + Singleton / Observer callouts
- [ ] [Design Meeting Scheduler \| LLD](https://algomaster.io/learn/lld/design-meeting-room-scheduler) — `algomaster` (companion to awesome-lld) — meeting-**room** scheduler angle: clarify → prevent double bookings; hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design) *(no dedicated `problems/meeting-scheduler.md` yet — use Educative + this chapter)*
- [ ] [Design Meeting Scheduler (Skilled Coder)](https://theskilledcoder.com/posts/low-level-design/design-calendar) — `Skilled Coder` — free high-signal principles: Calendar = conflict detector (not a dumb list); per-user calendars; recurrence as a rule, not Meeting fields
- [ ] [Calendar / Meeting Scheduler LLD](https://ikshitij.com/learn/lld-object-oriented/calendar-scheduler-lld/) — `ikshitij` — text class diagram, interval-tree / sorted-list conflict checks, **find earliest slot for N attendees**, RFC 5545 recurrence, UTC + TZ notes
- [ ] [LLD Case Study: Meeting Room Scheduler](https://www.calibreos.com/learn/lld-meeting-room-scheduler) — `CalibreOS` — senior bar: invariant “no two ACTIVE bookings for a room overlap,” check+insert atomicity, TENTATIVE→CONFIRMED→CANCELLED, per-room lock vs optimistic version
- [ ] [LLD-6 Meeting Scheduler](https://akhileshmj.medium.com/lld-6-meeting-scheduler-0eb8b23d9b04) — `Medium` — compact entity list + **Observer** for invite notifications + **Strategy** for room assignment (FCFS)
- [ ] [Low-Level Design (LLD) of Google Calendar System](https://interview.anuraggoel.in/low-level-design-lld-of-google-calendar-system-871e91642ec9) — `Interview Simplified` — calendar-first variant: `RecurringRule` Strategy + Factory, share/permissions, find-availability API sketch + Python locks
- [ ] [Design a Meeting Scheduler \| LLD (class diagram, patterns, concurrency & code)](https://www.youtube.com/watch?v=e3MaS40kv8I) — `YouTube` — full walkthrough: requirements → classes → availability/room book → notifications; companion code: [Devaraj-Umapathi MeetingScheduler (Java)](https://github.com/Devaraj-Umapathi/Low-Level-Design/tree/main/problems/java/MeetingScheduler)
- [ ] [Mock LLD Interview — Design Meeting Scheduler (Qualcomm Sr. Engineer)](https://www.youtube.com/watch?v=MRx40JVmmF4) — `YouTube` — live clarifying questions + pacing under interview pressure
- [ ] [Observer](https://refactoring.guru/design-patterns/observer) / [Strategy](https://refactoring.guru/design-patterns/strategy) / [Singleton](https://refactoring.guru/design-patterns/singleton) / [Facade](https://refactoring.guru/design-patterns/facade) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) — `Refactoring.Guru` — the five patterns interviewers expect you to name (invite notify, room pick / recurrence, one scheduler service, orchestration API, recurrence-rule creation)
- [ ] [ConcurrentHashMap (Java)](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/concurrent/ConcurrentHashMap.html) — `Oracle JDK docs` — safe user/room/meeting catalogs; **map alone ≠ atomic book** — still lock per room / per calendar on check+insert
- [ ] [RFC 5545 — iCalendar](https://www.rfc-editor.org/rfc/rfc5545) — `IETF` — canonical `RRULE` / `RDATE` / `EXDATE` for recurring events (mention when recurrence is probed)
- [ ] [Google Calendar API — Calendars & events](https://developers.google.com/workspace/calendar/api/concepts/events-calendars) — `Google Developers` — real product model: calendar vs event, recurring parent + instances/exceptions, store times with TZ / expand recurrence in a single zone
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo (Flipkart/Uber/Swiggy pacing)
- [ ] [keertipurswani/Meeting-Scheduler-Low-Level-Design](https://github.com/keertipurswani/Meeting-Scheduler-Low-Level-Design) — `GitHub` — C++/Java reference implementation after you can sketch the UML
- [ ] [thesaltree meeting_scheduler (Go)](https://github.com/thesaltree/low-level-design-golang/tree/main/meeting_scheduler) — `GitHub` — alternate Go design: room capacity, Observer notify, mutex + cancel + list-free-rooms (good concurrency comparison)
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — broader OOD index / alternate codebases after the happy path works

## Core concepts to master
- **Clarify before coding:** rooms only, people calendars only, or both? capacity checks? RSVP (ACCEPT/DECLINE/TENTATIVE)? recurring meetings? find-common-slot? timezones? concurrency / tentative holds?
- **Two interview flavors (state which):** (A) **Meeting-room booking** — rooms are scarce resources; prevent double-book. (B) **Personal calendar / Google Calendar** — per-user calendars, invites, recurrence, find mutual free time. Strong answers support both with shared `Interval` / conflict logic.
- **Core entities:** `User` (organizer / participant), `Calendar` (per user **and/or** per room), `Meeting` / `Event`, `MeetingRoom` (id, capacity, amenities), `Interval` / `TimeSlot` (start, end), optional `RecurrenceRule`, `Notification`, `MeetingScheduler` facade.
- **Calendar is a conflict detector, not a list:** primary op = `isAvailable(interval)` / `getConflicts(interval)`. Prefer sorted intervals or an interval tree over scanning a global meeting dump. Give each user (and each room) its own calendar.
- **Overlap rule (must state):** intervals A and B conflict iff `A.start < B.end && B.start < A.end` (half-open `[start, end)` avoids touching-edge false positives).
- **Patterns that earn points:** **Strategy** (`RoomAssignmentStrategy`: FCFS / min-capacity-fit / nearest; also recurrence expand), **Observer** (notify participants on create/update/cancel/RSVP), **Facade** (`MeetingScheduler.scheduleMeeting(...)`), **Singleton** (optional scheduler service — prefer DI in production), **Factory** (`RecurrenceRuleFactory` from DAILY/WEEKLY/MONTHLY).
- **Key methods to name:** `addRoom`, `bookMeeting(organizer, participants, interval, minCapacity?) → Meeting|Conflict`, `cancelMeeting`, `respondToInvite(user, meeting, RSVP)`, `getAvailableRooms(interval, capacity)`, `findEarliestSlot(attendees, duration, window)`, optional `reschedule` / `getHistory`.
- **Find common slot:** union busy intervals across attendees in window → merge overlaps → walk gaps → first gap ≥ duration (classic interview stretch).
- **Recurrence:** store a **rule** (+ optional exception instances), expand only inside the query window — don’t materialize years of meetings up front. Decline/edit one instance ≠ edit the series (Google: parent + instances / `EXDATE`).
- **Concurrency (the senior probe):** two organizers must not book the same room for overlapping times. **Check-then-act is a race** — atomic “check free + insert booking” under a **per-room lock** (or optimistic version / DB constraint). Per-user calendar locks for invite accept that blocks conflicts. Coarse global lock is correct but over-serializes unrelated rooms.
- **Booking lifecycle (stretch):** `TENTATIVE` (short hold) → `CONFIRMED` → `CANCELLED` / `EXPIRED` — beats binary booked/free when the interviewer probes holds.
- **Timezones:** store instants in **UTC**; display in user TZ; expand recurrence in one IANA zone (Google requires a TZ on recurring events).
- **SOLID signal:** OCP = new room-pick / recurrence / notify channel without editing the facade; SRP = Calendar owns conflicts, Strategy owns pick, Observer owns notify, Scheduler orchestrates.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~35–45 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **Clarify first:** rooms + people? capacity? RSVP? recurrence? find mutual free time? notifications? concurrency? single TZ vs multi-TZ?
- **FR (typical room scheduler):** list rooms; book room for `[start, end)` if free and capacity ≥ attendees; cancel/release; list free rooms for a slot; notify participants; meeting history.
- **FR (typical calendar):** create/update/cancel events; invite attendees + RSVP; conflict check on organizer/attendees; optional recurring series; find earliest common slot.
- **NFR:** no double-booking under concurrent requests; OCP for assignment / notify / recurrence; modular packages; demonstrable `main` / CLI.
- **Assumptions to state:** e.g. times in UTC internally; meetings are closed-open intervals; attendees assumed free unless you model personal calendars; one building / one process for machine coding.
- **Use cases:** Organizer schedules → system checks room (+ people) → books → notifies; Participant accepts/declines → calendars update; Organizer cancels → room freed + notify; User queries free rooms / common slot.

### 2. Back-of-envelope estimation (usually light for LLD)
- Spot count: tens–hundreds of rooms, meetings/day per room in the dozens — in-memory sorted lists fine for machine coding.
- If interviewer pushes scale: conflict check should be **O(log n + k)** (sorted structure / interval tree), not O(n) full scan of history; lock granularity = per room, not global.

### 3. API / interface
```
MeetingRoom addRoom(String name, int capacity)
Meeting scheduleMeeting(User organizer, List<User> participants,
                        Instant start, Instant end, Integer minCapacity)
  → Meeting | throw ConflictException
void cancelMeeting(String meetingId)
void respond(String meetingId, User user, RsvpStatus status)  // ACCEPT|DECLINE|TENTATIVE

List<MeetingRoom> getAvailableRooms(Instant start, Instant end, int minCapacity)
Optional<Interval> findEarliestSlot(List<User> attendees, Duration duration,
                                    Instant windowStart, Instant windowEnd)
List<Meeting> getMeetingsForUser(User user) / getMeetingsForRoom(MeetingRoom room)
```
- Keep CLI parsing in a thin driver; domain logic stays in `MeetingScheduler` + calendars/strategies.

### 4. Data model / class diagram
```
MeetingScheduler                         // Facade (+ optional Singleton)
 - rooms: Map<id, MeetingRoom>
 - users: Map<id, User>
 - meetings: Map<id, Meeting>
 - roomAssignment: RoomAssignmentStrategy
 + scheduleMeeting / cancelMeeting / getAvailableRooms / findEarliestSlot

User
 - id, name, email, timezone
 - calendar: Calendar                 // personal conflict detector
 + respondToInvite(meeting, rsvp)

Calendar
 - bookings: sorted Intervals | IntervalTree
 + isAvailable(Interval) → bool
 + add(Interval) / remove(Interval)
 + getBusy(window) → List<Interval>

MeetingRoom
 - id, name, capacity
 - calendar: Calendar                 // room resource schedule
 + canFit(attendeeCount) → bool

Meeting  (implements Observable / notifies Observers)
 - id, title, organizer, participants
 - interval: Interval
 - room: MeetingRoom?
 - rsvp: Map<User, RsvpStatus>
 - status: SCHEDULED|CANCELLED|(TENTATIVE|CONFIRMED)
 - recurrence: RecurrenceRule?        // optional
 + addParticipant / cancel / notifyAll

Interval / TimeSlot
 - start, end
 + overlaps(other) → bool             // start < other.end && other.start < end

RoomAssignmentStrategy <<interface>>
 + pickRoom(rooms, interval, capacity) → MeetingRoom?
 └─ FirstAvailableStrategy / MinCapacityFitStrategy

RecurrenceRule <<interface>>          // optional Strategy
 + occurrencesIn(window) → List<Interval>
 └─ Daily / Weekly / Monthly   (+ Factory from enum)

NotificationService / User as Observer
 + update(meeting, eventType)         // CREATED|UPDATED|CANCELLED|REMINDER
```
- Sketch this (or Educative’s class-diagram lesson) on the whiteboard **before** coding.

### 5. High-level architecture / component breakdown
```
CLI / Driver
     │ schedule / cancel / respond / free-rooms / find-slot
     ▼
MeetingScheduler (Facade)
     │ uses
     ├─► RoomAssignmentStrategy ──► MeetingRoom.calendar.isAvailable + book
     ├─► User.calendar.isAvailable (if people conflicts in scope)
     ├─► Meeting (+ RecurrenceRule expand in window)
     └─► Observer / NotificationService ──► participants
```
- **Scheduler:** orchestration + locking only — no overlap math inline if Calendar owns it.
- **Calendar:** single place that answers “is this interval free?” and mutates bookings.
- **Strategy / Observer:** swappable room pick and notify channels (OCP).

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Room-centric vs people-centric calendars:** room-only is faster to ship; adding per-user calendars enables RSVP conflicts and find-common-slot — say you’d compose both behind the same `Calendar` abstraction.
2. **Strategy vs hardcoded “first free room”:** hardcoded passes demos; Strategy is the expected answer for “prefer smallest room that fits” / “prefer floor X.”
3. **Check-then-book race:** correct overlap code still double-books under concurrency unless check+insert is one critical section (per-room lock) or DB/optimistic version enforces the invariant.
4. **Materialize recurrence vs lazy expand:** materialize simplifies conflict checks but explodes storage; lazy expand + windowed query is the production answer (RFC 5545 / Google instances).
5. **Singleton MeetingScheduler:** fine for demos; prefer constructor injection for tests (same caveat as parking lot / Splitwise).

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = **book under contention** → per-room lock + sorted free/busy structure; don’t hold the lock while sending emails (notify async / after commit).
- Find-common-slot for large attendee sets → merge busy intervals carefully; bound the search window (e.g. next 7 days).
- Recurring series → expand only in query/book windows; store exceptions (`EXDATE` / overridden instances) separately.
- Multi-process stretch (only if asked): in-process locks aren’t enough — enforce with DB exclusion constraint / transactional “insert if no overlap,” same invariant.

**Timed drill:** implement room book/cancel + conflict detection + notify stub in 60–75 min; then add `RoomAssignmentStrategy` and a one-line note on per-room locking.

## Common follow-ups / gotchas
- “Two organizers book Room A 10:00–11:00 at once?” — classic check-then-act race; show synchronized / locked book path or optimistic version conflict.
- “Meeting ends at 11:00, next starts at 11:00 — conflict?” — use half-open intervals so adjacent slots are OK.
- “10 people, rooms of capacity 6 and 12?” — capacity filter before assignment; MinCapacityFit prefers 12 (or smallest fit — product rule; make it Strategy).
- “Decline one occurrence of a weekly standup?” — exception on that instance; don’t mutate the whole `RRULE`.
- “Find a 30-min slot for Alice, Bob, Carol this week?” — merge busy unions, walk gaps (ikshitij algorithm).
- “Add Slack + email notifications?” — new Observer / notifier; don’t `if (channel == …)` inside `Meeting`.
- “Timezones / DST?” — UTC storage; recurrence expand in organizer IANA TZ (Google model).
- Gotcha: god-class `Meeting` holding recurrence strings, reminder prefs, and room search — split SRP.
- Gotcha: finishing recurrence UML but failing mandatory book/cancel without double-booking — mandatory first.

## Where it appears
- **Campus / machine-coding (Flipkart, Uber, Swiggy, Amazon new-grad, Indian product cos):** common as “meeting room booking” CLI — working conflict-free book/cancel + capacity beats a half-finished recurrence engine.
- **Experienced LLD (FAANG / Microsoft / Atlassian / Qualcomm-style):** same domain, deeper probes — per-room concurrency, Strategy vs switch, Observer notifications, find-common-slot, recurrence parent/instance model, tentative holds.
- **Frequency:** among the **top ~15 canonical LLD problems** (with parking lot, elevator, Splitwise, movie booking); treat it as the template for any interval-resource booking design (rooms, courts, desks, interview panels).
