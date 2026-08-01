# LQ12 — Design a Notification Service

**Interview relevance:** High — staple LLD / machine-coding + bridge-to-HLD question (campus + experienced); Uber, Microsoft, Amazon, Flipkart, Meta, LinkedIn, Airbnb-style loops probe multi-channel Strategy/Adapter, Observer decoupling, preferences, retries, and concurrency.
**Type:** LLD-question
**Prereqs:** l01_oop_solid, l02_patterns_creational (Factory), l03_patterns_structural (Adapter / Decorator / Facade), l04_patterns_behavioral (Strategy / Observer / Command); l05_concurrency_lld; warm-up sibling: awesome-lld Pub-Sub (in-process Observer fan-out)

## Read / watch (curated, in order)
- [ ] [Design Notification Service (object discovery + routing framing)](https://theskilledcoder.com/posts/low-level-design/design-notification-service) — `Skilled Coder` — **start here for LLD framing:** food-delivery story → nouns (Notification / Channel / Template / Preference / Retry); why “scatter send calls” and “god `notify()`” fail; Channels + Templates + Preferences architecture
- [ ] [Notification System using Java (Factory + Strategy + Observer + Decorator + Singleton)](https://www.geeksforgeeks.org/java/notification-system-using-java/) — `GeeksforGeeks` — runnable console LLD: `NotificationFactory`, `SendStrategy`, `NotificationManager` Singleton, Logger/Analytics observers, message Decorators
- [ ] [Low Level Design — Scalable Notification System](https://vishalsheth4.medium.com/ldesign-a-scalable-notification-system-3c77b5314304) — `Medium` — compact interview sketch: `NotificationChannel` Strategy + `ChannelFactory` + `RetryPolicy` + `NotificationDispatcher` + Facade `NotificationService`; Kafka/DLQ talking points
- [ ] [Day 15 — Designing a Notification Service (Email, SMS, Push)](https://techpreneurr.medium.com/learn-low-level-design-in-25-days-day-15-designing-a-notification-service-email-sms-push-419e58464884) — `Medium` — Factory for senders + queue/worker mental model (async dispatch without losing OOP clarity)
- [ ] [Design a Notification Service (requirements + Strategy / retry / batching)](https://www.lowleveldesignmastery.com/interview-guide/case-studies/hard/notification-service/) — `Low Level Design Mastery` — FR/NFR checklist: templates, preferences, rate limits, retries, digests; Strategy for providers; Command + Retry Decorator; priority vs batch
- [ ] [Low-Level Design: Notification System (OOP Interview)](https://www.techinterview.org/post/3233464069/lld-notification-system/) — `techinterview` — full Python walkthrough: templates, quiet hours, per-channel rate limits, `ChannelHandler` Strategy, status enums, digest/priority follow-ups
- [ ] [Extensible Order Notification System \| LLD \| Flipkart \| Cleartrip](https://medium.com/@abhijeetkarmakar1920/extensible-order-notification-system-lld-flipkart-cleartrip-3a606c026493) — `Medium` — order-event → subscription map → Strategy channels + Factory; Flipkart/Cleartrip-flavored machine-coding shape
- [ ] [Designing a scalable notification system — HLD to LLD](https://medium.com/@tanushree2102/designing-a-scalable-notification-system-from-hld-to-lld-e2ed4b3fb348) — `Medium` — Factory + Strategy senders, schedulable interface split, then Kafka workers / DLQ (good “when LLD becomes HLD” bridge)
- [ ] [Build Your Own Notification Engine \| System Design](https://www.youtube.com/watch?v=t-4r2AsJz_Q) — `YouTube / Coder Army` — end-to-end LLD: Email/SMS/Push, Observer + Strategy + Decorator, UML + code
- [ ] [Notification Service & Design Patterns (Amazon SDE-2)](https://www.youtube.com/watch?v=uf9wBcRcyNo) — `YouTube` — live machine-coding style: Strategy / Observer / Factory on a notification service
- [ ] [Observer design pattern \| Notify Me](https://www.youtube.com/watch?v=38Hy7-sv_Zw) — `YouTube` — Amazon “Notify Me when back in stock” Observer warm-up (same muscle as event → notify)
- [ ] [Live LLD — Observer Design Pattern & real-world use-cases](https://www.youtube.com/watch?v=MNjz8gve40M) — `YouTube / Concept && Coding` — Observer deep dive (Shrayansh); pairs with Notify-Me before full multi-channel service
- [ ] [Observer Pattern \| How Swiggy sends 4 notifications at once](https://www.youtube.com/watch?v=B37EfNl29xg) — `YouTube / Runtime Ethos` — why Checkout must not import Email/SMS/Push directly; Observer vs Mediator vs Pub-Sub
- [ ] [Designing a Pub-Sub System (problem + UML + multi-lang code)](https://github.com/ashishps1/awesome-low-level-design/blob/main/problems/pub-sub-system.md) — `awesome-low-level-design` — **closest awesome-lld sibling** (no dedicated `notification-service.md` in the index): topics/subscribers, [class diagram](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/pubsubsystem-class-diagram.png), [Java](https://github.com/ashishps1/awesome-low-level-design/tree/main/solutions/java/src/pubsubsystem) with `ConcurrentHashMap` + `ExecutorService`; hub: [ashishps1/awesome-low-level-design](https://github.com/ashishps1/awesome-low-level-design)
- [ ] [Observer](https://refactoring.guru/design-patterns/observer) / [Strategy](https://refactoring.guru/design-patterns/strategy) / [Adapter](https://refactoring.guru/design-patterns/adapter) / [Factory Method](https://refactoring.guru/design-patterns/factory-method) / [Decorator](https://refactoring.guru/design-patterns/decorator) / [Facade](https://refactoring.guru/design-patterns/facade) / [Command](https://refactoring.guru/design-patterns/command) / [Singleton](https://refactoring.guru/design-patterns/singleton) — `Refactoring.Guru` — patterns interviewers expect you to name: event fan-out, channel send algorithms, Twilio/SendGrid/FCM wrappers, channel creation, retry/timestamp wrappers, `NotificationService` API, queueable send tasks, optional single manager
- [ ] [How to Answer a LLD Interview Problem](https://blog.algomaster.io/p/how-to-answer-a-lld-interview-problem) — `AlgoMaster` — clarify → entities → relationships → code skeleton pacing (use on this problem)
- [ ] [How to ace the machine coding round?](https://workat.tech/machine-coding/article/how-to-ace-machine-coding-round-hi8lnpp8tlmo/) — `workat.tech` — timebox: clarify → extensible design → working demo
- [ ] [Design Notification Service (HLD chapter)](https://algomaster.io/learn/system-design-interviews/design-notification-service) — `AlgoMaster` — after OOP design: preferences, scheduler, per-channel queues, retries/DLQ, scale numbers
- [ ] [Design a Notification System](https://www.hellointerview.com/learn/system-design/problem-breakdowns/notification-system) — `Hello Interview` — platform FR (OTP vs campaigns), surge vs critical traffic, preferences/quiet hours framing
- [ ] [Design a Notification System (ByteByteGo / Alex Xu Vol 1 Ch.10)](https://bytebytego.com/courses/system-design-interview/design-a-notification-system) — `ByteByteGo` — canonical HLD companion; book TOC: [Vol 1 vs Vol 2](https://blog.bytebytego.com/p/system-design-interview-books-volume); free chapter notes: [Pagefy summary](https://pagefy.io/system-design/system-design-interview-by-alex-xu/notification-system)
- [ ] [Notification_System (requirements + Notifier chain notes)](https://github.com/code123-tech/Low-Level-Design-Questions/tree/master/Questions/Notification_System) — `GitHub` — alternate problem brief: multi-channel subscribe, priority, templates, concurrency clarifying Qs
- [ ] [GabrielTiziano/notify (Strategy + Factory Spring sketch)](https://github.com/GabrielTiziano/notify) — `GitHub` — DI-resolved `NotificationStrategy` per channel (Email/SMS/WhatsApp) — compare to interview Factory map
- [ ] [prasadgujar/low-level-design-primer](https://github.com/prasadgujar/low-level-design-primer) — `LLD primer` — extra OOD index after you can code the happy path

## Core concepts to master
- **Clarify before coding:** channels (Email / SMS / Push / In-App / WhatsApp)? event types (OTP vs promo vs social)? templates with placeholders? user preferences + quiet hours? priority + rate limits? retry / fallback channel? sync vs async? delivery status tracking? digests?
- **Core entities:** `Notification` / `NotificationRequest` (id, userId, type, priority, payload/context, status); `Channel` enum; `NotificationTemplate` (+ render); `UserPreferences` (opt-in per type×channel, quiet hours, caps); `NotificationChannel` / `ChannelHandler` (Strategy); optional `NotificationProvider` Adapter (Twilio / SendGrid / FCM); `NotificationService` Facade/orchestrator; optional `RetryPolicy`, `RateLimiter`, queue/`NotificationTask`.
- **Dual decoupling (the design insight):** (1) producers (Order/Payment) must not import Email/SMS SDKs → **Observer / event bus / Pub-Sub**; (2) orchestrator must not hardcode Twilio/SendGrid → **Strategy (+ Adapter)** behind `send(notification)`.
- **Patterns that earn points:** **Strategy** (per-channel send), **Factory** (resolve channel/provider), **Adapter** (vendor SDKs), **Observer** (event → notify / analytics/logger side effects), **Decorator** (timestamp, encrypt, retry wrapper), **Facade** (`NotificationService.notify`), **Command** (queueable send + retry metadata), optional **Singleton** manager (prefer DI in production).
- **Routing is the hard part:** given event → load preferences → pick channels → render template → rate-limit → dispatch. Sending is the easy leaf.
- **Templates:** store `subject`/`body` with `{placeholders}`; `Template.render(context)` keeps copy out of `if (type == ORDER_PLACED)` god methods.
- **Preferences & compliance:** opt-out promotional; never opt-out security/OTP (or force Email+SMS); quiet hours skip Push/SMS but allow CRITICAL; frequency caps per channel.
- **Reliability:** retries with exponential backoff; after N failures → FAILED / DLQ; optional fallback channel (Push fails → SMS). Distinguish provider ACK vs user-read.
- **Concurrency:** thread-safe preference reads; concurrent dispatches across users; don’t double-send same `notificationId` (idempotency key); pub-sub notify must not mutate subscriber list unsafely (copy-on-write / concurrent structures — see awesome-lld Pub-Sub).
- **SOLID signal:** OCP = new channel/provider/event without editing orchestrator; SRP = template renders, channel sends, preference gates, service orchestrates; DIP = depend on `NotificationChannel` / `NotificationProvider` abstractions.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (whiteboard ~30–40 min or machine-coding ~90 min):

### 1. Requirements (functional + non-functional) & scale assumptions
- **FR (mandatory):** send via ≥2 channels (Email, SMS, Push); create notification from event/request; respect user channel preferences; basic success/fail status.
- **FR (common extensions — ask):** templates; priorities (HIGH/MED/LOW); retries + fallback; rate limits / quiet hours; scheduled send; digests; in-app inbox; delivery webhooks.
- **NFR:** extensible new channels (OCP); no tight coupling to vendors; correct under concurrent sends; optional async queue for scale talk.
- **Assumptions to state:** in-memory prefs/templates OK for machine coding; third-party APIs mocked; at-least-once OK unless asked for exactly-once.
- **Use cases:** Order placed → Email receipt + Push; OTP → SMS (ignore promo opt-out); Push fails → fallback SMS; User disables promo SMS → skip; Promo blast rate-limited.

### 2. Back-of-envelope estimation (usually light for LLD)
- Machine coding: thousands of in-flight notifications, in-memory maps fine.
- If interviewer pushes scale: ingest API returns after enqueue; per-channel workers; peak ≫ average (campaigns); cite AlgoMaster/Hello Interview surge framing only as stretch.

### 3. API / interface
```
notify(userId, eventType, context) → List<NotificationResult>
notify(NotificationRequest) → NotificationId
setPreferences(userId, Preferences)
registerTemplate(templateId, channel, subjectTpl, bodyTpl)
getStatus(notificationId) → Status
```
OOD method surface:
```
NotificationService.notify(request) → results
UserPreferences.isAllowed(channel, eventType, now) → bool
NotificationTemplate.render(context) → (subject, body)
NotificationChannel.send(user, notification) → bool
ChannelFactory.get(channel) → NotificationChannel
RetryPolicy.shouldRetry(attempt) / nextDelay(attempt)
```

### 4. Data model / class diagram
```
NotificationService (Facade)
  ├── uses → UserPreferences
  ├── uses → TemplateRegistry
  ├── uses → ChannelFactory / Map<Channel, NotificationChannel>
  ├── uses → RateLimiter (optional)
  └── uses → RetryPolicy / Queue (optional)

NotificationChannel <<interface>>  <|-- EmailChannel | SMSChannel | PushChannel | InAppChannel
NotificationProvider <<interface>> <|-- SendGridAdapter | TwilioAdapter | FCMAdapter   (optional Adapter layer)

Notification (id, userId, channel, subject, body, priority, status, attempts)
NotificationTemplate (id, channel, subjectTpl, bodyTpl) — render(context)
UserPreferences (enabledChannels, quietHours, maxPerHour, typeOptIns)

EventPublisher ──notifies──> NotificationObserver / NotificationService   (optional Observer)
LoggerObserver / AnalyticsObserver ──observe──> send lifecycle
```
Pub-Sub sibling diagram: [pubsubsystem-class-diagram.png](https://github.com/ashishps1/awesome-low-level-design/blob/main/class-diagrams/pubsubsystem-class-diagram.png).

### 5. High-level architecture / component breakdown
- **NotificationService (Facade):** validate request → check prefs/rate limits → render → dispatch per channel → record status.
- **Channel Strategies:** one class per channel implementing `send`; no `switch` forest inside the service.
- **Factory:** maps `Channel` → strategy/provider instance (registry/`HashMap`).
- **Adapters (senior):** Strategy may call Adapter wrapping vendor SDK so swapping SendGrid→SES is one class.
- **Observer / event path:** `OrderService` publishes `OrderPlaced`; notification + analytics subscribe — producers stay clean.
- **Async (stretch):** service enqueues `NotificationTask`; workers pull per-channel queue; retry/DLQ outside request thread.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Strategy-only vs Strategy+Adapter:** Strategy is enough for mock sends; Adapter shows you can swap Twilio without touching channel policy (failover providers).
2. **Sync send vs queue:** sync is demable in 60 min; say you’d enqueue for scale/retries — don’t build Kafka in machine coding unless asked.
3. **Observer in-process vs message bus:** Observer = same JVM, simple; Pub-Sub/queue = durable, multi-service — name both and pick for scope.
4. **Idempotency:** at-least-once workers need `notificationId` / idempotency key so retries don’t spam OTP twice.

### 7. Bottlenecks / how you “scale” it (LLD sense)
- Hot path = preference + template lookup → cache prefs/templates; channel map O(1).
- Fan-out: parallelize channel sends per user carefully; never share mutable notification status without sync.
- Provider rate limits: token bucket / per-channel limiter; isolate slow SMS from email workers.
- Campaigns: batch/chunk recipients; priority queue so OTP isn’t stuck behind promo (Hello Interview critical-vs-surge idea).

**Timed drill:** implement GFG/Vishalsheth happy path (3 channels + prefs + Factory) in 45–60 min; then add RetryPolicy + one Observer (logger); narrate Kafka upgrade in 2 minutes.

## Common follow-ups / gotchas
- “Add WhatsApp without changing `NotificationService`?” — new `WhatsAppChannel` + Factory registration (OCP); fail if you `switch` inside the service.
- “Push failed — try SMS?” — fallback chain / Chain of Responsibility or explicit `FallbackPolicy`; don’t bury in one channel class.
- “User opted out of promo but must get OTP” — gate by notification type; security overrides preferences.
- “Two workers process the same message” — idempotency key + status CAS (`PENDING→SENT`); gotcha of naive at-least-once.
- “Digest: Bob and 5 others liked your post” — buffer low-priority events; flush on timer (batching vs real-time tradeoff).
- “Quiet hours + priority” — CRITICAL bypasses quiet hours/rate limits; promo does not.
- Gotcha: god-class `NotificationService` with hardcoded bodies and vendor HTTP — split template / channel / provider.
- Gotcha: calling Observer `notify` while holding a lock and subscriber tries to unsubscribe → deadlock; copy listener list first.

## Where it appears
- **Campus / new-grad:** common machine-coding or LLD round in India (Amazon, Flipkart, Uber, Swiggy, Microsoft-style); expect working multi-channel demo + pattern names.
- **Experienced / SDE-2:** same OOP core, harder probes — Adapter failover, retries/DLQ, idempotency, rate limits, async boundaries, priority vs promo isolation.
- **FAANG / product OOD:** often starts as LLD classes then expands toward Alex Xu / Hello Interview HLD (queues, APNs/FCM, preferences DB).
- **Frequency:** among the **most asked** “design a service” LLD problems after parking lot / rate limiter-ish utilities — treat as the template for any multi-provider integration design.
