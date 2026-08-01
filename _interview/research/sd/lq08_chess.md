# LQ08 — Design a Chess / Tic-Tac-Toe Game

**Interview relevance:** High — flagship board-game LLD pair; Tic-Tac-Toe is the warm-up / machine-coding staple (Flipkart, Uber, Amazon, Microsoft), Chess is the harder OOD probe (piece polymorphism, legality, Command undo) at Amazon/Microsoft/Meta-style loops.
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Factory), l03_patterns_structural; Strategy / State / Command / Template Method from behavioral patterns (or Refactoring.Guru links below)

## Read / watch (curated, in order)
- [ ] [Design Tic Tac Toe Game (problem + UML + multi-lang code)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/tic-tac-toe.md) — `awesome-low-level-design` — **start here (warm-up):** requirements, [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/tictactoe-class-diagram.png); hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Java tic-tac-toe solution](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/tictactoe) — `awesome-low-level-design` — `Player` / `Board` / `Game` reference; also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/tictactoe)
- [ ] [Design Tic-Tac-Toe (workat.tech machine coding)](https://workat.tech/machine-coding/practice/design-tic-tac-toe-smyfi9x064ry/) — `workat.tech` — Flipkart/Uber-style CLI: validate moves, print board, win / Game Over; optional N×N / multi-player / new piece types
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → design for extensibility → working demo
- [ ] [Design Tic Tac Toe | LLD (AlgoMaster)](https://algomaster.io/learn/lld/design-tic-tac-toe) — `AlgoMaster` — entities → win check → concurrency note (`synchronized` move) → Observer scoreboard extension
- [ ] [Java LLD: Design Tic-Tac-Toe with O(1) Win Detection](https://dev.to/machinecodingmaster/java-lld-design-tic-tac-toe-with-o1-win-detection-5gpg) — `DEV` — +1/−1 row/col/diag counters; pair with [LeetCode 348 — Design Tic-Tac-Toe (doocs)](https://leetcode.doocs.org/en/lc/348/) for the O(1) API drill
- [ ] [Tic-Tac-Toe · LLD-flavoured](https://ikshitij.com/learn/lld-object-oriented/tic-tac-toe/) — `ikshitij` — Human vs Bot Strategy, Deque-style multi-player stretch, O(1) counters, minimax
- [ ] [Low-Level Design of Tic Tac Toe | SCALER](https://www.youtube.com/watch?v=ULnY8VW7YCs) — `YouTube` — entities → Board → Game → driver + tests walkthrough
- [ ] [Design Chess Game (problem + UML + multi-lang code)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/chess-game.md) — `awesome-low-level-design` — **chess hub:** requirements, [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/chessgame-class-diagram.png), `Piece.canMove` polymorphism
- [ ] [Java chessgame solution](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/chessgame) — `awesome-low-level-design` — abstract `Piece` + King/Queen/Rook/Bishop/Knight/Pawn; also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/chessgame)
- [ ] [Design Chess (Grokking OOD case study)](https://github.com/tssovi/grokking-the-object-oriented-design-interview/blob/master/object-oriented-design-case-studies/design-chess.md) — `Grokking OOD` — use cases, `Box`/`Board`/`Piece`/`Move`/`Game`, sample Java skeleton
- [ ] [anomaly2104/chess-low-level-system-design](https://github.com/anomaly2104/chess-low-level-system-design) — `GitHub` — [problem statement](https://github.com/anomaly2104/chess-low-level-system-design/blob/master/problem-statement.md) + extensible move validators; video: [Chess LLD | Design Principles](https://www.youtube.com/watch?v=RVHNcng0oF0)
- [ ] [Chess Engine · LLD-flavoured](https://ikshitij.com/learn/lld-object-oriented/chess-engine/) — `ikshitij` — pseudo-legal vs legal filter, Command undo, specials (castle / en passant / promotion), FEN/PGN stretch
- [ ] [Rules of chess](https://en.wikipedia.org/wiki/Rules_of_chess) — `Wikipedia` — only skim for check / mate / stalemate / castling / en passant / promotion vocabulary — don’t memorize openings
- [ ] [Strategy](https://refactoring.guru/design-patterns/strategy) / [Command](https://refactoring.guru/design-patterns/command) / [State](https://refactoring.guru/design-patterns/state) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) / [Template Method](https://refactoring.guru/design-patterns/template-method) / [Observer](https://refactoring.guru/design-patterns/observer) — `Refactoring.Guru` — win/AI/player input, undoable `Move`, game status FSM, piece creation, shared move-validation skeleton, UI/scoreboard
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after you can code the happy path

## Core concepts to master
- **Two problems, one skeleton:** both are turn-based board games → `Game` orchestrator + `Board` + `Player` + `Move` + terminal status. Tic-Tac-Toe tests win detection + extensibility; Chess tests polymorphism + legality filtering.
- **Clarify before coding (TTT):** fixed 3×3 or N×N? win length K? 2 players or P? Human vs Bot? undo? print format / CLI I/O exactness (workat.tech)?
- **Clarify before coding (Chess):** full FIDE rules or subset? specials (castling, en passant, promotion)? clocks? undo? online two-player vs local CLI? resign / draw offer?
- **Core TTT entities:** `Board` (grid + place/validate), `Player` (name + symbol), `PlayingPiece`/`Symbol`, `Game` (turns + outcome), optional `WinningStrategy`, `Deque<Player>` for round-robin.
- **Core Chess entities:** abstract `Piece` → King/Queen/Rook/Bishop/Knight/Pawn; `Board` (8×8 of `Square`/`Box`); `Move` (from/to + captured + flags); `Player` (color); `Game` / `ChessGame` (turn, status, history).
- **Patterns that earn points:** **Strategy** (win rules / AI / Human vs Bot input); **Command** (`Move.execute` / `undo` + history stack); **State** / status enum (`IN_PROGRESS`, `CHECK`, `CHECKMATE`, `STALEMATE`, `DRAW`); **Factory** (create pieces / players); **Template Method** or polymorphism on `Piece.canMove` / `getPseudoLegalMoves`; **Observer** (UI / scoreboard).
- **TTT win detection:** naive scan all lines after each move (fine for 3×3). Senior bar = **O(1)** with row/col/diag counters (+1/−1 per player) — LeetCode 348 follow-up. For N×N with K-in-a-row, check only lines through last move (O(N) or O(K)).
- **Chess move pipeline:** (1) own piece + turn, (2) piece geometry (`canMove`), (3) path clear (sliders), (4) destination empty or enemy, (5) **simulate** move and reject if own king remains in check, (6) commit + evaluate check/mate/stalemate. Separate *pseudo-legal* from *legal*.
- **Don’t put movement `switch(pieceType)` in `Board`/`Game`:** each subclass owns geometry — OCP for fairy pieces / Chess960 stretch.
- **Concurrency:** local CLI = single-threaded. If “online / shared game object”: serialize `makeMove` (one lock per game); never let two clients mutate the same board. Chess clocks / network are product stretch — mention server-side validation, don’t implement mid-round.
- **SOLID signal:** OCP = new piece / win strategy / bot without editing `Game`; SRP = Board holds cells, Piece validates geometry, Game owns turns + legality filter; DIP = depend on `Piece` / `WinningStrategy` / `PlayerStrategy` abstractions.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~30–45 min or machine-coding ~90 min). Prefer **Tic-Tac-Toe first** unless interviewer says Chess.

### 1. Requirements (functional + non-functional) & scale assumptions
**Tic-Tac-Toe — FR (mandatory):** N×N board (default 3); two players X/O alternate; reject occupied / OOB cells; detect win (row/col/diag) and draw (full board); print board after valid moves.
**TTT — FR (common extensions):** P players + Deque turns; K-in-a-row; undo; Bot (random / minimax); scoreboard across games.
**Chess — FR (mandatory):** 8×8; two players White/Black; White first; place standard 16+16 pieces; validate piece moves; alternate turns; detect checkmate / stalemate (at least sketch).
**Chess — FR (extensions):** castling, en passant, promotion; move history + undo; resign; clocks; PGN/FEN.
**NFR:** modular files (not one god class); extensible rules; correct under concurrent move attempts if multi-client; working CLI demo.
**Assumptions to state:** TTT = exact CLI format if workat.tech; Chess interview often accepts subset of specials if you call them out and hook them.
**Use cases:** Player places mark / moves piece → system validates → updates board → announces win/draw/checkmate or next turn; optional Bot computes move; Admin views scoreboard / bans player (Grokking online framing).

### 2. Back-of-envelope estimation (usually light for LLD)
- TTT board ≤ hundreds of cells in interviews; O(1) win check is the complexity flex, not scale.
- Chess: 64 squares; legal-move gen is O(#pieces × moves) per turn — fine in-memory. AI search (minimax) explodes — only discuss if asked (alpha-beta, iterative deepening).

### 3. API / interface
TTT machine-coding (workat-shaped) or methods:
```
create_game(players[], n)
make_move(row, col) → BoardSnapshot | INVALID | WIN | DRAW
get_board() / print_board()
undo()? 
```
LeetCode-shaped:
```
TicTacToe(n)
move(row, col, player) → 0 | 1 | 2
```
Chess OOD surface:
```
Game.start(white, black)
Game.makeMove(from, to, promotion?) → MoveResult
Piece.canMove(board, from, to) / getPseudoLegalMoves(board)
Board.isSquareAttacked(square, byColor)
Game.isInCheck(color) / isCheckmate / isStalemate
Move.execute(board) / undo(board)
```

### 4. Data model / class diagram
**Tic-Tac-Toe:**
```
Game 1──1 Board
Game 1──* Player          (or Deque<Player>)
Game ──uses──> WinningStrategy
Board (n×n cells: Symbol|empty; rowSum[], colSum[], diag, antiDiag)
Player (name, Symbol) ──optional──> PlayerStrategy (Human|Bot)
Move (row, col, player)   // for undo history
GameStatus: IN_PROGRESS | WIN | DRAW
```
Canonical diagram: [tictactoe-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/tictactoe-class-diagram.png).

**Chess:**
```
Game 1──1 Board 1──* Square/Box
Game 1──2 Player
Game 1──* Move (history stack)
Piece <|-- King | Queen | Rook | Bishop | Knight | Pawn
Square (row, col, piece?)
Move (from, to, piece, captured?, isCastle?, isEnPassant?, promotion?)
GameStatus: ACTIVE | CHECK | CHECKMATE | STALEMATE | RESIGNED | DRAW
```
Canonical diagram: [chessgame-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/chessgame-class-diagram.png). Grokking also models `Account` / `GameController` / `GameView` for online framing.

### 5. High-level architecture / component breakdown
- **Game (Facade / controller):** owns turn, status, history; public `makeMove`; never embeds piece geometry or win-line formulas inline if Strategy is expected.
- **Board:** cell storage + helpers (`get`/`set`, path clear, attacked squares). Keep it a grid service — not a god object of all rules.
- **Piece hierarchy (Chess):** polymorphic movement; shared helpers for sliding (rook/bishop/queen) via Template Method or composition.
- **WinningStrategy (TTT):** `StandardLineWin` / `KInARow`; swap without editing `Game`.
- **PlayerStrategy:** Human (stdin) vs Bot (minimax) — Game only asks `nextMove(board)`.
- **Move as Command:** push on success; `undo` restores board + counters / captured piece / castling rights.
- **Concurrency layer:** `synchronized makeMove` (or per-game lock) for shared instances; AlgoMaster flags this on TTT.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Scan vs incremental win check (TTT):** full scan is OK for 3×3 demos; counters / last-move check show you won’t die on N=100 (LC 348).
2. **Inheritance vs Strategy for Chess movement:** subclass-per-piece is the classic answer; Strategy-per-movement-style (slide/leap/pawn) reduces duplication for Queen = Rook∪Bishop — either is fine if you justify.
3. **Pseudo-legal vs legal moves:** geometry-only validators miss self-check; always mention simulate-or-filter. Checkmate = in check + zero legal moves; stalemate = not in check + zero legal moves.
4. **Enum status vs State pattern:** enum + guarded transitions is enough for interviews; full State objects if behavior per status grows (e.g. reject moves after mate).
5. **Special moves:** implement promotion + castling hooks if time; say en passant needs `lastMove` metadata — don’t claim full FIDE if you only did basics.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- TTT hot path = win check → O(1) counters; undo must reverse counters.
- Chess hot path = legality (attack maps / pin detection); for AI, alpha-beta + transposition tables — discuss only if asked.
- Multi-game server: one `Game` instance per match id; lock per game, not global; validate moves server-side.
- Optional product stretch: ratings, matchmaking, PGN export — keep as interfaces, don’t code mid-round.

**Timed drills:** (1) workat.tech TTT CLI happy path in 45–60 min, then add Deque + N×N + Strategy win; (2) Chess: piece hierarchy + basic moves + turn loop in 60–75 min, sketch check filter + Command undo on the board.

## Common follow-ups / gotchas
- “Make the board N×N / support 3 players” — parameterize size; `Deque` turns; don’t hardcode 2 or 3×3 constants in `Game`.
- “O(1) win detection?” — +1/−1 row/col/diag counters; win when abs == N (or winLength).
- “Add a Bot” — `PlayerStrategy` / `BotPlayer` with minimax; Game unchanged.
- “Undo last move” — Command stack; reverse board cell + TTT counters / Chess captured piece & flags.
- “Is the king in check after this move?” — simulate on a copy (or make/unmake); never skip this filter.
- “Castling / en passant / promotion” — special `Move` subtypes or flags; track `hasMoved`, `lastMove`, promote on last rank.
- “How is checkmate different from stalemate?” — both = no legal moves; mate requires currently in check.
- Gotcha: god-class `Game` with giant `switch` on piece type / win lines — docks OCP.
- Gotcha: finishing optional AI/specials but failing mandatory validate + alternate turns + terminal detection — mandatory first.
- Gotcha (workat): wrong print format / continuing after win — read I/O contract carefully.

## Where it appears
- **Campus / new-grad (India):** Tic-Tac-Toe and Snake & Ladder are frequent machine-coding openers (Flipkart, Uber, Swiggy, Amazon, Razorpay); timed CLI + extensibility review.
- **Experienced / SDE-2:** Chess (or TTT with N×N + Strategy + Bot) — polymorphism, Command undo, legality, concurrency on shared game objects.
- **FAANG OOD:** “Design Chess” / “Design Tic-Tac-Toe” whiteboard; clarifying questions + clean class model matter more than full FIDE or GUI.
- **Frequency:** among the **most asked** game LLDs — treat TTT as the template for turn-based games; Chess as the polymorphism stress test.
