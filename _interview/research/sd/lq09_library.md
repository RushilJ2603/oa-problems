# LQ09 — Design a Library Management System

**Interview relevance:** High — classic OOD / LLD question (campus + experienced); probes Book vs BookItem, State for copy lifecycle, Strategy for search/fines, Observer for holds, and concurrency on checkout. Common at Indian product cos (Flipkart-style loops) and FAANG-style OOD whiteboards (Google lore).
**Type:** LLD-question
**Prereqs:** L01 (OOP & SOLID — especially OCP / SRP), L02 (creational — Factory / Singleton), L03–L04 (State, Strategy, Observer, Facade), L05 (concurrency — lock the copy, not the whole catalog)

## Read / watch (curated, in order)
- [ ] [Design Library Management System | LLD](https://algomaster.io/learn/lld/design-library-management-system) — `algomaster` — clarifying Q&A → FRs (multi-type catalog, per-copy tracking, checkout/return, holds, Strategy search) before you draw classes
- [ ] [Designing a Library Management System (problem + UML)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/library-management-system.md) — `awesome-low-level-design` — requirements + [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/librarymanagementsystem-class-diagram.png); hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Java solution (State + Strategy + Factory + Observer)](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/librarymanagementsystem) — `awesome-low-level-design` — reference code: `LibraryItem`/`BookCopy`, `ItemState` (`Available`/`CheckedOut`/`OnHold`), `SearchStrategy`, `ItemFactory`, hold observers on `LibraryItem` (also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/librarymanagementsystem) / [C++](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/cpp/librarymanagementsystem) / [C#](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/csharp/librarymanagementsystem) / [Go](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/golang/librarymanagementsystem))
- [ ] [Design a Library Management System (tssovi / Grokking OOD)](https://github.com/tssovi/grokking-the-object-oriented-design-interview/blob/master/object-oriented-design-case-studies/design-a-library-management-system.md) — `Grokking OOD (open source)` — full requirements (limits 5 books / 10 days, fines, reserve/renew, barcodes), use cases, class list (`Book`/`BookItem`/`Catalog`/`BookLending`/`Fine`), checkout/return/renew flows
- [ ] [Getting Ready: Library Management System (Educative)](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/getting-ready-library-management-system) — `Educative / Grokking OOD` — bottom-up OOD framing + [class diagram lesson](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles/class-diagram-for-the-library-management-system); course hub: [Grokking the Low Level Design Interview Using OOD Principles](https://www.educative.io/courses/grokking-the-low-level-design-interview-using-ood-principles)
- [ ] [How to Actually Solve LLD Interview Questions | Library Management System](https://www.youtube.com/watch?v=GLrVJDTvI5s) — `YouTube` — step-by-step interview attack on this problem (clarify → entities → patterns)
- [ ] [Google Interview Question | LLD of Library Management System — Part 1](https://www.youtube.com/watch?v=71W8QTdFWw8) — `YouTube` — long-form whiteboard-style walkthrough (requirements → classes)
- [ ] [LLD Case Study: Library Management System (CalibreOS)](https://www.calibreos.com/learn/lld-library-management) — `CalibreOS` — what interviewers grade: Book vs BookItem, per-copy locks, Strategy fines, Observer waitlist; clarifying Qs (e-books, multi-branch, member tiers)
- [ ] [Design Library Management System (Skilled Coder)](https://theskilledcoder.com/posts/low-level-design/design-library) — `Skilled Coder` — resource-lifecycle framing; why borrowing a `Book` (metadata) instead of a `BookItem` (copy) fails the interview
- [ ] [Library Management · LLD-flavoured](https://ikshitij.com/learn/lld-object-oriented/library-management/) — `ikshitij` — compact patterns map: Strategy fine policy, State for `BookItem`, Observer notifications, Factory for media types
- [ ] [Design a Library Management System (Low Level Design Mastery)](https://www.lowleveldesignmastery.com/problems/library-management-system) — `LLD Mastery` — search / borrow / return / reserve / fines checklist + waitlist-on-Book (not on copy) tip
- [ ] [Library Management System — requirements walkthrough](https://www.onenoughtone.com/learn/library-management-system/1) — `OneNoughtOne` — FR by subsystem (catalog / member / circulation / fines) + in-scope vs out-of-scope for interviews
- [ ] [State](https://refactoring.guru/design-patterns/state) / [Strategy](https://refactoring.guru/design-patterns/strategy) / [Observer](https://refactoring.guru/design-patterns/observer) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) / [Singleton](https://refactoring.guru/design-patterns/singleton) / [Facade](https://refactoring.guru/design-patterns/facade) — `Refactoring.Guru` — the six patterns interviewers expect you to name here (copy lifecycle, search/fines, hold notifications, item creation, single library facade)
- [ ] [ConcurrentHashMap (Java)](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/concurrent/ConcurrentHashMap.html) — `Oracle JDK docs` — thread-safe catalog/member maps; still lock **per BookCopy checkout** (map alone ≠ atomic occupy)
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [System Design for Library Management (GFG)](https://www.geeksforgeeks.org/system-design/system-design-for-library-management/) — `GeeksforGeeks` — optional broader HLD/LLD overview after the OOD core (use for vocabulary, not as the primary class model)
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — adjacent solutions index after you can code the happy path ([solutions.md](https://github.com/prasadgujar/low-level-design-primer/blob/master/solutions.md))

## Core concepts to master
- **Clarify before coding:** physical only or e-books? multi-branch? member tiers (student/faculty)? max books + loan days? fines + cap? reservations / renewals? search axes (title/author/ISBN/subject)? concurrency?
- **#1 trap — Book vs BookItem/BookCopy:** `Book`/`LibraryItem` = catalog metadata (ISBN, title, authors); `BookItem`/`BookCopy` = physical copy (barcode/copyId, rack, status). Loans attach to a **copy**, never to the abstract book. Modeling `Member.borrow(Book)` is the classic fail.
- **Copy state machine:** `AVAILABLE` → `LOANED`/`CHECKED_OUT` → `AVAILABLE` (or `ON_HOLD`/`RESERVED` if waitlist nonempty) → `LOST`. Encode transitions in **State** (`ItemState`) so illegal ops (`return` while available) are impossible.
- **Patterns that earn points:** **State** (copy lifecycle), **Strategy** (search by title/author; fine per-day / tiered / waived), **Factory** (`ItemFactory` for Book vs Magazine), **Observer** (notify hold queue on return), **Facade** (`LibraryManagementSystem` / `LibraryManager` API), **Singleton** (one library/manager — optional; prefer DI for tests).
- **Catalog search:** inverted maps or Strategy over the catalog — `search(query, SearchStrategy)`; don’t `if (byTitle)` forever inside the facade (OCP).
- **Lending rules:** max books issued (often 5), max lending days (often 10–14), reject reference-only items, unpaid-fine threshold before new loans (extension).
- **Reservation / hold queue:** attach waitlist to the **Book** (any returned copy can fulfill), not a specific copy. On return: if observers → `ON_HOLD` + notify next member; else → `AVAILABLE`.
- **Fines:** `FineStrategy.calculate(daysOverdue, member, item)` — never bury rate math inside `returnBook`. Cap at replacement cost if asked.
- **Key methods to name:** `addItem` / `addBookItem`, `registerMember`, `search`, `checkout(memberId, copyId)`, `returnItem(copyId)`, `placeHold(memberId, itemId)`, `renew`, `collectFine` / `calculateFine`.
- **Concurrency:** two librarians must not checkout the same last copy. Prefer `synchronized(bookCopy)` or atomic status CAS; `ConcurrentHashMap` for catalogs is necessary but not sufficient. Coarse lock on whole library works for demos, serializes all desks.
- **SOLID signal:** OCP = new item type / search / fine without editing facade; SRP = catalog ≠ lending ≠ notifications; DIP = depend on `SearchStrategy` / `ItemState` / `FineStrategy` abstractions.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~35–45 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** add books (with N copies); register members; search catalog; checkout available copy; return copy; enforce borrow limit + loan duration.
- **FR (common extensions — ask):** place hold when none available; renew (blocked if another member holds); overdue fines; librarian vs member roles; rack location / barcode scan.
- **NFR:** correct under concurrent checkout; extensible item types & search/fine policies; modular files (not one god class); working demo / CLI.
- **Assumptions to state:** single branch unless told otherwise; physical copies first; in-memory catalog OK for LLD; one open loan per copy.
- **Use cases:** Librarian adds book + copies; Member searches → checkouts; Member returns (fine if late); Member places hold → notified on return; System sends overdue / availability notifications.

### 2. Back-of-envelope estimation (usually light for LLD)
- Catalog often **10k–1M titles**, few copies each. In-memory maps + indexes fine for machine coding.
- If interviewer pushes scale: title/author indexes (`Map<String, List<Book>>`) not O(n) scan; locks per copy, not global; multi-branch later = `branchId` on copies.

### 3. API / interface
```
addItem(type, id, title, author, numCopies) → List<BookCopy>
addMember(id, name) → Member
search(query, SearchStrategy) → List<LibraryItem>
checkout(memberId, copyId) → void | error
returnItem(copyId) → void (may notify holds)
placeHold(memberId, itemId) → void
renew(memberId, copyId) → bool          // optional
calculateFine(loan) → Money              // optional
```
OOD surface:
```
LibraryManagementSystem.checkout(Member, BookCopy)
BookCopy.checkout / returnItem / placeHold   // delegates to ItemState
Catalog / SearchStrategy.search(...)
FineStrategy.calculate(overdueDays, ...)
TransactionService.createLoan / endLoan
```

### 4. Data model / class diagram
```
LibraryManagementSystem (Facade, optional Singleton)
    1──* LibraryItem (Book | Magazine) 1──* BookCopy
    1──* Member
LibraryItem ──observes──> Member (hold waitlist)
BookCopy ──state──> ItemState (Available | CheckedOut | OnHold)
BookCopy 1──0..1 Loan ──> Member
LibraryManagementSystem ──uses──> ItemFactory
LibraryManagementSystem ──uses──> SearchStrategy
Loan / BookLending ──optional──> Fine
Catalog implements Search (title | author | subject | pubDate indexes)
Account <|-- Member | Librarian          // Grokking-style RBAC
BookItem ──placed_at──> Rack             // optional physical location
```
Canonical diagram: [librarymanagementsystem-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/librarymanagementsystem-class-diagram.png). Richer entity set: [tssovi Grokking write-up](https://github.com/tssovi/grokking-the-object-oriented-design-interview/blob/master/object-oriented-design-case-studies/design-a-library-management-system.md).

### 5. High-level architecture / component breakdown
- **LibraryManagementSystem / LibraryManager (Facade):** entry point; holds catalog, members, copy registry; orchestrates checkout/return/hold/search.
- **LibraryItem + Factory:** catalog metadata; Book/Magazine subtypes; owns copies + Observer list for holds.
- **BookCopy + State:** identity + current `ItemState`; all transitions go through state object.
- **Member / Librarian:** borrowing history / loans; member receives hold notifications (`update`).
- **Loan / TransactionService:** active loan map keyed by copyId; due date; return clears loan.
- **Strategies:** pluggable search (and fines if in scope).
- **Concurrency layer:** synchronize checkout/return on the copy (or CAS status); concurrent maps for catalogs.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Book vs BookItem:** if you skip this, you can’t track which copy is damaged/lost or fulfill holds correctly — call it out first.
2. **Enum status vs State pattern:** enum + switches ships faster; State wins when transitions/guards grow (hold-only checkout). Prefer State in OOD rounds; enum OK if timeboxed and transitions are centralized.
3. **Waitlist on Book vs BookItem:** Book-level queue is correct (any copy satisfies); item-level waitlist breaks when a different copy returns first.
4. **Global lock vs per-copy lock:** `synchronized checkout()` on the library is correct but serializes desks; per-copy lock shows senior thinking — name the double-checkout race explicitly.
5. **Singleton Library:** common in tutorials; say you’d inject a single instance for testability unless interviewer wants classic Singleton.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = **checkout under contention** → lock/CAS on the specific `BookCopy`; keep active-loans map concurrent.
- Search: maintain indexes per field; Strategy selects which index — don’t linear-scan the catalog each query.
- Notifications: Observer push on return; don’t poll all members.
- Optional product stretch (only if asked): multi-branch transfers, e-book concurrent-license limits, priority holds (faculty) — keep as strategy/config hooks, don’t implement mid-round.

**Timed drill:** implement add → search → checkout → return → placeHold happy path in 60–75 min (awesome-LLD Java shape), then add Strategy search + a spoken note on per-copy thread-safety and fines.

## Common follow-ups / gotchas
- “Two members checkout the last copy at once?” — race on read-then-write status; show synchronized/`compareAndSet` on the copy.
- “Add magazines / e-books / audiobooks” — `LibraryItem` hierarchy + Factory; e-books may use license count instead of physical scarcity.
- “Different fine rates for student vs faculty” — `FineStrategy` (or member-type policy); don’t `if` inside `returnItem`.
- “Renew when someone else holds the title” — reject renew; optionally force return path into `ON_HOLD` + notify waiter (Grokking renew flow).
- “Where does the reservation queue live?” — on the Book/LibraryItem; gotcha is attaching it only to one BookItem.
- “Reference-only / rare books” — flag on copy; checkout returns false (tssovi `is_reference_only`).
- Gotcha: god-class `Library` that also searches, bills, notifies, and persists — split SRP or interviewer docks design score.
- Gotcha: finishing optional notifications but failing mandatory checkout/return/search — mandatory first.

## Where it appears
- **Campus / new-grad:** very common OOD / LLD or machine-coding warm-up in India (Flipkart/Uber/Amazon-style loops, service companies’ advanced LLD); often timed class design + core methods.
- **Experienced / SDE-2:** same domain, harder follow-ups — Book vs BookItem, State vs enum, hold fairness, fine Strategy, per-copy concurrency, multi-branch.
- **FAANG OOD:** classic “design a library” whiteboard (Google lore / Soumyajit-style walkthroughs); focus on clarifying questions + clean class model more than CLI I/O.
- **Frequency:** among the **most asked** inventory-style LLD problems — treat it as the template for other “resource + copy + reservation” domains (car rental, hotel rooms, tool checkout).
