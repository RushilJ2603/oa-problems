# LQ10 — Design a Logging Framework

**Interview relevance:** High — classic LLD / machine-coding round that packs Chain of Responsibility, Strategy, Singleton/Factory, Observer-style fan-out, and concurrency into one problem; asked at Uber, Google, Atlassian, Amazon, and many Indian product cos.
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Singleton / Factory), l03_patterns_structural (Decorator); Chain of Responsibility / Strategy / Observer from behavioral patterns (or Refactoring.Guru links below)

## Read / watch (curated, in order)
- [ ] [Designing a Logging Framework (problem + UML + multi-lang code)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/logging-framework.md) — `awesome-low-level-design` — **start here:** requirements (levels, destinations, config, thread-safety), [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/loggingframework-class-diagram.png); hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Java logging-framework solution](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/loggingframework) — `awesome-low-level-design` — runnable reference: named hierarchical `Logger`, `LogManager` registry, `CopyOnWriteArrayList` appenders, `AsyncLogProcessor`; also [Python](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/python/loggingframework) / [C++](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/cpp/loggingframework) / [C#](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/csharp/loggingframework) / [Go](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/golang/loggingframework) / [TypeScript](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/typescript/src/LoggingFramework)
- [ ] [Logging Service (Hello Interview LLD breakdown)](https://www.hellointerview.com/learn/low-level-design/problem-breakdowns/logging-service) — `Hello Interview` — best clarifying-questions script: in-process library vs aggregator, per-destination level + independent Formatter/Sink composition, concurrency bar, what to explicitly scope out
- [ ] [Design Logging Framework | LLD (AlgoMaster)](https://algomaster.io/learn/lld/design-logging-framework) — `AlgoMaster` — FR/NFR checklist: multi-appender fan-out, custom formatters, async logging, thread-safety
- [ ] [Logger Framework · LLD-flavoured](https://ikshitij.com/learn/lld-object-oriented/logger-framework/) — `ikshitij` — full class diagram + `effectiveLevel()` walk + `AsyncAppenderWrapper` Decorator + MDC / backpressure follow-ups (closest to “senior answer”)
- [ ] [Design a Logger (CalibreOS)](https://www.calibreos.com/learn/lld-logger) — `CalibreOS` — E4 vs E5 vs E6 bar: Singleton-on-Logger is junior; Factory + hierarchy + Async Decorator + additivity is senior
- [ ] [Design Logging Framework (Skilled Coder)](https://theskilledcoder.com/posts/low-level-design/design-logger) — `Skilled Coder` — why if-else destinations fail OCP; CoR + Strategy framing for handlers
- [ ] [Designing a Logging Framework (LLD Mastery)](https://www.lowleveldesignmastery.com/interview-guide/case-studies/easy/logging-framework/) — `LLD Mastery` — pipeline view Logger → Filter → Formatter → Appender; async queue tradeoff callout
- [ ] [Logger System LLD (Java)](https://dev.to/devcorner/logger-system-lld-java-3fcm) — `DEV` — compact Java sketch: `LogLevel` / `LogMessage` / `Appender` / Singleton `Logger` + extension list (rolling file, Kafka, MDC)
- [ ] [Low Level Design - Logging Framework](https://dev.to/ahmedadel/low-level-design-logging-framework-n12) — `DEV` — Singleton + CoR level chain + Observer targets walkthrough
- [ ] [How to design a logging system using Chain of Responsibility](https://devcookies.medium.com/how-to-design-a-logging-system-using-the-chain-of-responsibility-design-pattern-106f4a64eae7) — `Medium` — classic INFO→DEBUG→ERROR handler chain demo (pattern intuition, not production Log4j model)
- [ ] [Logger / Logging Framework (LLD Hub)](https://lldhub.in/problem/logger-system) — `LLD Hub` — short practice prompt: levels, destinations, registry-per-name, discard below threshold
- [ ] [Chain of Responsibility](https://refactoring.guru/design-patterns/chain-of-responsibility) / [Strategy](https://refactoring.guru/design-patterns/strategy) / [Singleton](https://refactoring.guru/design-patterns/singleton) / [Observer](https://refactoring.guru/design-patterns/observer) / [Decorator](https://refactoring.guru/design-patterns/decorator) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) / [Template Method](https://refactoring.guru/design-patterns/template-method) — `Refactoring.Guru` — the patterns interviewers expect you to name (hierarchy/handlers, formatters+appenders, registry, multi-appender fan-out, async wrapper, `getLogger`, handle→emit skeleton)
- [ ] [Log4j 2 Architecture](https://logging.apache.org/log4j/2.x/manual/architecture.html) — `Apache Log4j` — canonical production model: Logger → LoggerConfig → Appender + Filter + Layout (what “good” looks like)
- [ ] [Log4j 2 Asynchronous Loggers](https://logging.apache.org/log4j/2.x/manual/async.html) — `Apache Log4j` — Disruptor / non-blocking path; cite when interviewer asks “how do real frameworks avoid blocking?”
- [ ] [SLF4J Manual](https://www.slf4j.org/manual.html) — `SLF4J` — facade vs binding; why apps depend on an API, not a concrete logger impl
- [ ] [Python `logging` HOWTO](https://docs.python.org/3/howto/logging.html) + [logging module](https://docs.python.org/3/library/logging.html) — `Python docs` — free hierarchical logger + Handler + Formatter + `propagate` reference (mirrors Log4j additivity)
- [ ] [java.util.logging package](https://docs.oracle.com/javase/8/docs/api/java/util/logging/package-summary.html) — `Oracle JDK` — JDK baseline: `Logger` / `Handler` / `Formatter` / `Level` vocabulary
- [ ] [awesome-LLD issue #153 — hierarchy & per-appender levels](https://github.com/ashishps1/awesome-low-level-design/issues/153) — `GitHub` — common doubt: root→child inheritance, default level, console INFO + file DEBUG (multi-threshold)
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after you can code the happy path

## Core concepts to master
- **Clarify scope first:** in-process library (Log4j/SLF4J-style) vs distributed log aggregator (Kafka → ELK). Interviews almost always want the **library**. State async, hierarchy, rotation, remote sinks as optional extensions.
- **Core pipeline:** `Logger.log(level, msg)` → level check → build immutable `LogMessage`/`LogRecord` → (optional filters) → fan out to one or more `Appender`s → each appender applies a `Formatter`/`Layout` then writes.
- **Log levels are an ordered enum:** TRACE < DEBUG < INFO < WARN < ERROR < FATAL. Threshold means “emit if `messageLevel >= configuredLevel`”. Put the check **before** allocating/formatting (hot-path short-circuit).
- **Patterns that earn points:** **Strategy** (`LogAppender`, `LogFormatter`), **Chain of Responsibility** (logger parent hierarchy *or* linked handlers), **Observer**/broadcast (one record → many appenders), **Singleton/Factory** (`LogManager`/`LoggerFactory.getLogger(name)` registry — not “one Logger for the whole app”), **Decorator** (`AsyncAppender` wrapping any appender), **Template Method** (handler: filter → format → emit).
- **Compose format × destination:** Formatter and Appender vary independently (JSON-to-console, plain-to-file) — don’t explode into `JsonFileAppender` × `PlainConsoleAppender` classes (Hello Interview’s composition signal).
- **Named hierarchical loggers:** dotted names (`com.app.service`); child inherits effective level from nearest configured ancestor; `additivity`/`propagate` controls whether records bubble to parent appenders (Log4j / Python model — the senior CoR answer).
- **Config surface:** min level, list of appenders, formatter(s), optional async flag. Prefer `LoggerConfig` / factory setup over hardcoding inside `log()`.
- **Concurrency:** synchronize **per appender** (or use a single-writer async thread) so one record’s bytes never interleave with another’s; `CopyOnWriteArrayList` / snapshot appender list under concurrent reconfiguration; `ConcurrentHashMap` for the logger registry.
- **Async logging:** enqueue `LogMessage` on a bounded `BlockingQueue` / single-thread executor; caller returns fast. Discuss backpressure: drop / block / write-inline when full; flush on shutdown.
- **SOLID signal:** OCP = new appender/formatter without editing `Logger`; SRP = Logger filters+dispatches, Appender transports, Formatter shapes; DIP = depend on `LogAppender` / `LogFormatter` abstractions.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~30–40 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** log at DEBUG/INFO/WARN/ERROR/FATAL; each record has timestamp + level + message (+ thread name if asked); configurable min level; write to console and/or file; extensible for new destinations.
- **FR (common extensions — ask):** multiple appenders per logger; custom formatters (plain / JSON); async non-blocking path; named hierarchical loggers + additivity; Database/Kafka appender; rolling files; MDC (requestId).
- **NFR:** thread-safe (no interleaved lines); low overhead when level disabled; OCP for new sinks/formats; simple client API (`logger.info("…")`).
- **Assumptions to state:** in-process library; v1 sync OK if you leave an async hook; config at startup unless interviewer wants hot-reload.
- **Use cases:** App calls `info`/`error` → filtered by level → formatted → written to configured sinks; Admin raises root level to DEBUG in prod; Worker threads log concurrently without garbled output.

### 2. Back-of-envelope estimation (usually light for LLD)
- Volume often **thousands–millions of lines/sec** in prod mental model; interview care = don’t allocate/`String.format` on disabled DEBUG, don’t block request threads on disk/network I/O.
- If pushed on scale: async single-writer or Disruptor-style ring buffer; batch file writes; drop DEBUG in hot paths via effective-level short-circuit.

### 3. API / interface
Client-facing:
```
Logger logger = LogManager.getLogger("com.app.OrderService")
logger.debug/info/warn/error/fatal(String message)
logger.log(LogLevel level, String message)
logger.setLevel(LogLevel) / addAppender(LogAppender) / setAdditivity(boolean)
LogManager.shutdown()  // flush async + close appenders
```
Internal contracts:
```
LogAppender.append(LogMessage) / close()
LogFormatter.format(LogMessage) → String
Logger.getEffectiveLevel() → LogLevel
AsyncLogProcessor.process(LogMessage, List<LogAppender>)
```

### 4. Data model / class diagram
```
LogManager / LoggerFactory (Singleton) 1──* Logger (name → registry)
Logger ──parent──> Logger?          (hierarchy / CoR for level + additivity)
Logger 1──* LogAppender             (fan-out / Observer-style)
LogAppender ──uses──> LogFormatter  (Strategy)
LogAppender <|-- ConsoleAppender | FileAppender | DatabaseAppender
LogAppender <|-- AsyncAppender (Decorator wraps another Appender)
LogLevel <<enum>>  DEBUG < INFO < WARN < ERROR < FATAL
LogMessage (level, message, timestamp, loggerName, threadName?)
LoggerConfig (minLevel, appenders)   // optional explicit config object
```
Canonical diagram: [loggingframework-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/loggingframework-class-diagram.png). Richer hierarchy diagram: [ikshitij Logger Framework](https://ikshitij.com/learn/lld-object-oriented/logger-framework/).

### 5. High-level architecture / component breakdown
- **LogManager / LoggerFactory:** singleton registry; `getLogger(name)` builds parent chain from dotted name; owns optional `AsyncLogProcessor`.
- **Logger:** public API; level gate via `getEffectiveLevel()`; builds `LogMessage`; `callAppenders` then bubbles to parent if `additivity`.
- **LogMessage:** immutable event (timestamp, level, text, logger name).
- **LogAppender (+ Strategy implementations):** Console / File / DB; each may hold its own min level + formatter.
- **LogFormatter:** SimpleText / JSON — injected into appenders.
- **Async path:** queue + daemon drain thread (or Decorator `AsyncAppender`) so callers don’t wait on I/O.
- **Concurrency layer:** concurrent registry; COW appender lists; synchronize writes inside file/console appenders (or serialize via single async worker).

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Singleton Logger vs Singleton Factory + many named Loggers:** putting Singleton on `Logger` itself blocks per-module levels/appenders (junior smell). Prefer `LogManager.getLogger(name)` registry (CalibreOS E5 bar).
2. **Handler CoR vs list-of-appenders + hierarchy CoR:** “INFO→DEBUG→ERROR class chain” teaches CoR but isn’t how Log4j works. Prefer: appenders as a list (fan-out), hierarchy for level inheritance + additivity (production model). Say both; implement the list+hierarchy version.
3. **Sync vs async append:** sync is correct and simpler for demos; async decouples latency but risks loss on crash / full queue — name the backpressure policy.
4. **Global lock vs per-appender lock / single-writer:** global `synchronized log()` is correct but serializes the app; prefer lock inside each appender or one async consumer thread.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = **disabled-level calls** → ordinal compare, return before `new LogMessage` / string concat (use parameterized logging or guard with `isDebugEnabled` if discussing SLF4J).
- I/O bottleneck = **FileAppender under burst** → async queue + batching; rolling file by size/time.
- Contention = many threads → one appender lock; mitigate with async single-writer so producers only contend on the queue.
- Optional stretches (only if asked): MDC ThreadLocal map, sampling/`RateLimitFilter`, hot-reload config, remote Kafka/OTLP appender behind the same interface.

**Timed drill:** implement `Logger` + `LogLevel` + `ConsoleAppender`/`FileAppender` + level filter + thread-safe writes in 60–75 min; then add multi-appender list and a note/sketch for async + hierarchy.

## Common follow-ups / gotchas
- “Two threads log at once — garbled line?” — race on shared `PrintStream`/file handle; synchronize `append()` or use a single-writer async thread.
- “Console DEBUG but file only WARN?” — per-appender (or per-destination) thresholds, not one global filter only ([issue #153](https://github.com/ashishps1/awesome-low-level-design/issues/153)).
- “Add Slack / Kafka / DB sink” — new `LogAppender` impl; don’t edit `Logger.log` if-else.
- “Make it non-blocking” — `AsyncAppender` Decorator or shared processor queue; discuss drop vs block when full; `shutdown()` flush.
- “Named loggers / `com.app` inherits INFO” — parent pointer + `getEffectiveLevel()` walk; `additivity=false` stops bubble-up.
- “JSON vs plain text” — `LogFormatter` Strategy swap; same appender.
- Gotcha: concatenating `"user="+id` before the level check — allocates even when DEBUG is off; prefer lazy/parameterized messages.
- Gotcha: appender throws → must not crash the app; catch + fallback stderr / error handler.
- Gotcha: process exit loses async queue — register shutdown hook / explicit `LogManager.shutdown()`.

## Where it appears
- **Campus / new-grad:** common machine-coding or LLD round in India (Amazon, Flipkart, Uber, Walmart, Atlassian-style loops); expect working console+file logger with levels and a clear class diagram.
- **Experienced / SDE-2:** same domain, harder probes — hierarchy + additivity, async backpressure, per-appender levels, MDC, lock granularity, comparison to Log4j/SLF4J.
- **FAANG OOD:** whiteboard “design a logger”; clarifying questions + pattern naming matter as much as code.
- **Frequency:** among the **standard** LLD set (with parking lot, elevator, Splitwise) — especially when the interviewer wants to test **Chain of Responsibility + concurrency** in one shot.
)
