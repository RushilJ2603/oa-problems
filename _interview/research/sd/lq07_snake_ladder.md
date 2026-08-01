# LQ07 — Design Snake and Ladder

**Interview relevance:** High — the canonical Flipkart/Uber-style **machine-coding** starter (campus + SDE-1/2); also a common OOD whiteboard warm-up. Tests OOP modeling, turn loops, Strategy/Builder, and (optionally) concurrent game sessions.
**Type:** LLD-question
**Prereqs:** L01 (OOP & SOLID), L02 (creational — Builder / Singleton), L03 (structural — Facade); Strategy from behavioral patterns (Refactoring.Guru links below)

## Read / watch (curated, in order)
- [ ] [Design Snake And Ladder (workat.tech practice problem)](https://workat.tech/machine-coding/practice/snake-and-ladder-problem-zgtac9lxwntg/) — `workat.tech` — **start here for machine coding:** CLI input format, exact-land-on-100, snake/ladder **chaining**, sample I/O, optional extensions (multi-dice, board size, extra turn on 6)
- [ ] [How to design Snake and Ladder? (workat.tech editorial)](https://workat.tech/machine-coding/editorial/how-to-design-snake-and-ladder-machine-coding-ehskk9c40x2w/) — `workat.tech` — Gaurav Chandak’s models + `SnakeAndLadderService` walkthrough; Driver / service separation; hooks for all 5 optional requirements
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → design for extensibility → working demo (use this pacing on S&L)
- [ ] [Designing Snake and Ladder Game (problem + UML)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/snake-and-ladder.md) — `awesome-low-level-design` — requirements checklist + [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/snakeandladdergame-class-diagram.png); hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Java solution (Builder + BoardEntity + Queue turns)](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/snakeandladdergame) — `awesome-low-level-design` — runnable reference: `Game` / `Board` / `Snake` / `Ladder` / `Dice` / `GameStatus` (also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/snakeandladdergame) / C++ / C# / Go siblings)
- [ ] [Design Snake and Ladder Game | LLD (AlgoMaster)](https://algomaster.io/learn/lld/design-snake-and-ladder) — `algomaster` (via awesome-lld) — clarifying Qs (exact win, roll-6 extra turn, 3×6 forfeit), `BoardEntity` hierarchy, Builder, O(1) jump map
- [ ] [Design Snake and Ladder (Skilled Coder)](https://theskilledcoder.com/posts/low-level-design/design-snake-and-ladder) — `theskilledcoder` — core insight: snake and ladder are the **same Jump abstraction** (data differs, not behavior)
- [ ] [Snake Ladders · LLD-flavoured](https://ikshitij.com/learn/lld-object-oriented/snake-ladders/) — `ikshitij` — turn FSM framing; `Board.nextPosition` as pure function; chaining / loop detection seam
- [ ] [Java LLD: Snakes and Ladders with O(1) Move Resolution](https://dev.to/machinecodingmaster/java-lld-designing-snakes-and-ladders-with-o1-move-resolution-31k2) — `DEV` — precomputed jump array + `MovementStrategy`; companion: [javalld.com problem](https://www.javalld.com/problems/snakes-ladders)
- [ ] [Design Snake and Ladder Game using OOPs (GeeksforGeeks)](https://www.geeksforgeeks.org/system-design/design-snake-and-ladder-game-using-python-oops/) — `GeeksforGeeks` — `MovingEntity` base + ranks / consecutive-6s rules in a full Python walkthrough
- [ ] [Snake and Ladder LLD + Machine Coding (YouTube)](https://www.youtube.com/watch?v=rwBmrSfRP0Y) — `YouTube` — Flipkart/FAANG-shaped machine-coding narration (pairs with workat problem)
- [ ] [System Design: Snake and Ladder | Machine Coding (YouTube)](https://www.youtube.com/watch?v=zRz1GPSH50I) — `YouTube` — alternate OOPS / machine-coding pass
- [ ] [Build Snake and Ladder Game | UML + Code (YouTube)](https://www.youtube.com/watch?v=1NJB54UB8nE) — `YouTube` — UML-first + code
- [ ] [Snakes and Ladders LLD in Java | Extensible Design (YouTube)](https://www.youtube.com/watch?v=L7hvkK188Ek) — `YouTube` — extensibility-focused Java walkthrough
- [ ] [Builder](https://refactoring.guru/design-patterns/builder) / [Strategy](https://refactoring.guru/design-patterns/strategy) / [Singleton](https://refactoring.guru/design-patterns/singleton) / [Facade](https://refactoring.guru/design-patterns/facade) — `Refactoring.Guru` — patterns interviewers expect you to name (game construction, dice/win/turn policies, multi-session manager, `Game.play()` entry)
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD problem index after you can code the happy path

## Core concepts to master
- **Clarify before coding:** board size fixed 100 vs configurable? exact land on last cell? overshoot = stay put? snake/ladder **chains**? extra turn on 6? 3 consecutive 6s cancel? same cell allowed for multiple players? continue until last player or stop at first winner?
- **Core entities:** `Board` (size + jump map), `Player` (name, position), `Dice` (roll), `Snake`/`Ladder` (or unified `Jump` / `BoardEntity`), `Game` / `SnakeAndLadderService` (turn loop + win), optional `GameManager` for concurrent sessions.
- **Jump model:** prefer one `Map<start, end>` (or `int[]` destinations) for **O(1)** resolve — don’t scan snake/ladder lists every move. Inheritance (`BoardEntity` → Snake/Ladder) is fine for validation; a single `Jump` class is cleaner if behavior is identical.
- **Turn rotation = Queue:** `poll()` → roll → move → if not won, `offer()` back. Scales to N players without index math.
- **Exact-win rule (default interview):** `pos + roll > size` → skip move (stay). First to `pos == size` wins. State this assumption early.
- **Chaining (workat mandatory):** after a jump, if the landing cell is also a head/start, keep resolving until stable; detect cycles (assumptions usually: no infinite loop, no snake at 100, unique starts).
- **Patterns that earn points:** **Builder** (`Game` needs board + players + dice), **Strategy** (dice count / win condition / “extra turn on 6”), **Facade** (`play()` / `startGame()`), **Singleton** only for a multi-game `GameManager` (controversial — prefer DI). Don’t force State/Observer unless asked.
- **Concurrency (senior probe):** one game is single-threaded. Multi-session = independent `Game` instances on separate threads; never share mutable board/player state across games. Prefer `ThreadLocalRandom` (or injected RNG) over shared `Random`.
- **SOLID signal:** OCP = new win/dice/turn rules without editing the game loop; SRP = Driver I/O ≠ service logic ≠ board jump map; DIP = depend on `Dice` / strategy abstractions for testability.
- **Out of scope until asked:** UI, persistence, online multiplayer networking, AI bots — call them out.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈90 min machine coding / ≈35–45 min LLD whiteboard):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (workat mandatory):** read snakes, ladders, players from CLI/file; simulate turns with fair d6; print each move; print winner; start at 0; exact reach 100; overshoot stays; apply snakes/ladders with chaining.
- **FR (common extensions — ask):** multi-dice; custom board size; play until one left; extra turn on 6 + cancel after 3 sixes; auto-generate snakes/ladders.
- **NFR:** modular files (not one god class); working demo; extensible for optional rules; optionally concurrent independent games.
- **Assumptions to state:** unique jump starts; no snake on final cell; no infinite jump cycles; ≥2 players; same cell OK for multiple pieces.
- **Use cases:** Admin/Driver configures board → Game starts → Player rolls → Board resolves landing → Game checks win → next turn / end.

### 2. Back-of-envelope estimation (usually light for LLD)
- Board ≤ few hundred cells; players ≤ tens. In-memory structures fine.
- Per move should be **O(1)** average with a jump map (or O(chain length) with a visited set). Avoid O(S+L) list scans per move if you claim polish.

### 3. API / interface
Machine-coding shaped (workat) or method surface:
```
// Driver / CLI
read snakes[], ladders[], players[]
startGame()

// Core
Dice.roll() → int
Board.getFinalPosition(pos) → int   // apply jump(s)
Game.play() / SnakeAndLadderService.startGame()
Game.takeTurn(Player)               // roll + move + win check
```
Optional knobs (setters / Strategy / Builder):
```
setNoOfDices(n)
setShouldAllowMultipleDiceRollOnSix(bool)
setShouldGameContinueTillLastPlayer(bool)
WinningStrategy.hasWon(position, boardSize)
```

### 4. Data model / class diagram
```
Game / SnakeAndLadderService          // Facade + turn loop
 ├─ Board (size, Map<start,end> jumps)
 ├─ Queue<Player>                     // round-robin
 ├─ Dice
 └─ GameStatus (NOT_STARTED|RUNNING|FINISHED)

BoardEntity <|-- Snake | Ladder       // OR unified Jump(start,end)
Player (name, position | piece on board map)
Dice.roll()

Optional:
GameManager (Singleton) 1──* Game     // startNewGame → new thread
Game.Builder → Game                   // setBoard / setPlayers / setDice
```
Canonical diagram: [snakeandladdergame-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/snakeandladdergame-class-diagram.png).

### 5. High-level architecture / component breakdown
```
Driver (I/O)
   │
   ▼
SnakeAndLadderService / Game.play()
   │  poll player → Dice.roll()
   │  tentative = pos + roll
   │  if tentative > size: stay
   │  else: pos = Board.resolve(tentative)  // chain jumps
   │  if pos == size: win / remove from queue
   │  else: enqueue player (or re-turn on 6)
   ▼
Board jump map (O(1))
```
- **Driver:** parsing + wiring only.
- **Service/Game:** orchestration, win, optional rules.
- **Board:** pure position resolution.
- **Dice:** injectable/mockable randomness.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Separate Snake/Ladder classes vs unified Jump:** separate classes encode validation (`start > end` vs `<`); unified Jump avoids duplicate lookup logic. Strong answer: one map + optional subclasses for validation only.
2. **List scan vs O(1) map/array:** lists are fine for tiny boards; map/array is the expected “clean” answer and makes chaining trivial.
3. **Hardcoded rules vs Strategy:** hardcoding exact-win + single die passes the mandatory path; Strategy/flags win the optional multi-dice / continue-until-last / extra-turn follow-ups without rewriting `startGame`.
4. **Recursive “roll 6 again” vs loop with counters:** recursion is short; a loop with consecutive-6 counter is safer for the “3 sixes cancel” rule.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = resolve landing — keep jumps hashed; cap chain length / track visited to guarantee termination.
- Many concurrent lobbies → one `Game` per session, thread-per-game or executor; no shared mutable board.
- Long games / determinism → inject `Random` seed for tests; don’t couple logic to `System.out` (wrap printer if time allows).
- Optional product stretch: undo/redo, bots, networked rooms — only if asked.

**Timed drill:** implement workat CLI happy path (exact win + chaining + print format) in 60–75 min, then add Strategy/flags for multi-dice or extra turn on 6.

## Common follow-ups / gotchas
- “Snake/ladder at the landing of another — chain?” — **yes** in workat; loop until stable; mention cycle guard.
- “Roll past 100?” — stay put (exact win). Alternate product rule: bounce back — make it a `WinningStrategy` / movement rule.
- “Roll a 6 → extra turn; three 6s?” — extra turn optional; three consecutive often cancel the whole turn (return to turn-start position).
- “Two players on same cell?” — usually allowed; no capture unless product says otherwise.
- “Multiple dice / custom board size?” — `noOfDices` + `boardSize` constructor params; don’t hardcode `100` and `6` in the loop.
- “Concurrent games?” — `GameManager.startNewGame` spawns independent games; synchronize only the manager’s game list, not board cells.
- Gotcha: god-class that parses input, rolls dice, and prints in one file — interviewers dock design score.
- Gotcha: finishing optional extensibility but failing mandatory move print / win — mandatory first.

## Where it appears
- **Campus / machine-coding (Flipkart, Uber, Swiggy, Amazon new-grad, Indian product cos):** extremely common first LLD coding problem — often **the** example used to explain the round (workat.tech). Timed CLI (~90–120 min) + design review.
- **Experienced / SDE-2:** same core, harder follow-ups — Strategy for rules, chaining edge cases, concurrent sessions, testability of randomness.
- **FAANG OOD whiteboard:** lighter coding, heavier clarifying questions + clean class model (Jump abstraction, turn queue).
- **Frequency:** among the **top machine-coding** LLD problems (with parking lot, Splitwise, Tic-Tac-Toe); treat as the template for turn-based game designs.
