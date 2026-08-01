# H08 — Message queues & streaming (Kafka, RabbitMQ, pub/sub, delivery semantics, backpressure)

**Interview relevance:** High — almost every HLD "design X" that needs async work, fan-out, or spike buffering (notifications, feeds, orders, video pipelines, chat fanout); FAANG and Indian product cos expect you to place a queue/stream, name delivery semantics, and pick Kafka vs RabbitMQ/SQS for the use case.
**Type:** HLD-foundation
**Prereqs:** h01_networking, h02_load_balancing; helpful: h03_caching, h06_consistency_cap (eventual consistency after async)

## Read / watch (curated, in order)
- [ ] [system-design-primer — Message queues](https://github.com/donnemartin/system-design-primer#message-queues) — `primer` — why async (Starbucks / tweet fanout mental model); then [Task queues](https://github.com/donnemartin/system-design-primer#task-queues) and [Back pressure](https://github.com/donnemartin/system-design-primer#back-pressure)
- [ ] [What is the Publisher Subscriber Model?](https://www.youtube.com/watch?v=FMhbR_kQeHw) — `Gaurav Sen` — request/response vs pub/sub; brokers (Kafka/RabbitMQ); decoupling + eventual-consistency cost (~11 min)
- [ ] [Why Do We Need a Message Queue?](https://blog.bytebytego.com/p/why-do-we-need-a-message-queue) — `ByteByteGo` — flash-sale framing: fan-out, async, rate limiting, decoupling, horizontal scale, persistence, ordering
- [ ] [Kafka vs. RabbitMQ vs. Messaging Middleware vs. Pulsar](https://www.youtube.com/watch?v=x4k1XEjNzYQ) — `ByteByteGo` — ~4 min evolution diagram; pair with [IBM MQ → RabbitMQ → Kafka → Pulsar](https://bytebytego.com/guides/how-do-message-queue-architectures-evolve/)
- [ ] [How to Choose a Message Queue? Kafka vs. RabbitMQ](https://blog.bytebytego.com/p/how-to-choose-a-message-queue-kafka) — `ByteByteGo` — DB/Redis queues vs dedicated brokers; push-delete (Rabbit) vs pull-retain (Kafka); when each wins
- [ ] [EP203: RabbitMQ vs Kafka vs Pulsar](https://blog.bytebytego.com/p/ep203-rabbitmq-vs-kafka-vs-pulsar) — `ByteByteGo` — three mental models in one diagram (task broker vs log vs compute/storage split)
- [ ] [Kafka vs RabbitMQ: How to know which one to use](https://www.hellointerview.com/blog/kafka-vs-rabbitmq) — `Hello Interview` — interview decision tree: retention, ordering, throughput, routing, delivery, ops; "use both" is valid
- [ ] [Kafka Deep Dive for System Design Interviews](https://www.hellointerview.com/learn/system-design/deep-dives/kafka) — `Hello Interview` — topics / partitions / offsets / consumer groups; queue-mode vs stream-mode consumption
- [ ] [When to Use Event Driven Architecture](https://www.hellointerview.com/blog/event-driven-architecture) — `Hello Interview` — commands vs events; when *not* to sprinkle Kafka on every microservice call
- [ ] [Queues (Key Technologies)](https://www.hellointerview.com/learn/system-design/in-a-hurry/key-technologies) — `Hello Interview` — skim the Queues section: buffer bursts, decoupling, ordering, partitioning, **backpressure**
- [ ] [RabbitMQ Tutorials](https://www.rabbitmq.com/tutorials) — `RabbitMQ docs` — do [Work Queues](https://www.rabbitmq.com/tutorials/tutorial-two-python) (acks, prefetch) then [Publish/Subscribe](https://www.rabbitmq.com/tutorials/tutorial-three-python) (exchanges / fanout)
- [ ] [Apache Kafka](https://kafka.apache.org/) — `Kafka` — product mental model; delivery semantics: [documentation § Semantics](https://kafka.apache.org/documentation/#semantics) and [Confluent — Message Delivery Guarantees](https://docs.confluent.io/kafka/design/delivery-semantics.html) (at-most / at-least / exactly-once)
- [ ] [Top 5 Kafka Use Cases](https://bytebytego.com/guides/top-5-kafka-use-cases/) — `ByteByteGo` — logs, recommendations stream, monitoring, CDC, migration — when "stream" not "task queue"
- [ ] [What is Pub/Sub?](https://docs.cloud.google.com/pubsub/docs/overview) — `Google Cloud` — managed pub/sub vocabulary; pair with [AWS pub/sub messaging](https://aws.amazon.com/pub-sub-messaging/) and [Amazon SNS](https://docs.aws.amazon.com/sns/latest/dg/welcome.html) (SNS fanout → SQS workers)
- [ ] [Amazon SQS visibility timeout](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/sqs-visibility-timeout.html) — `AWS docs` — lease/hide → process → delete; pair with [Dead-letter queues](https://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSDeveloperGuide/sqs-dead-letter-queues.html)
- [ ] [Applying Back Pressure When Overloaded](https://mechanical-sympathy.blogspot.com/2012/05/apply-back-pressure-when-overloaded.html) — `Mechanical Sympathy` (cited by primer) — bound queues; reject/503 above capacity instead of unbounded latency → OOM
- [ ] [Avoiding Double Payments (Airbnb)](https://medium.com/airbnb-engineering/avoiding-double-payments-in-a-distributed-payments-system-2981f6b070bb) — `Airbnb Eng` — why at-least-once forces **idempotency** in money paths
- [ ] *Designing Data-Intensive Applications* ch.11 (Stream Processing) — `DDIA ch.11` — AMQP/JMS brokers vs log-based brokers (Kafka); backpressure / drop / buffer; retention & replay — book site: [dataintensive.net](https://dataintensive.net/)
- [ ] [InterviewReady — Intra-Service Messaging](https://github.com/InterviewReady/system-design-resources#intra-service-messaging) — `InterviewReady` — link dump (idempotency, async computing); optional: [Message Queue Antipattern](https://github.com/InterviewReady/system-design-resources#message-queue-antipattern)

## Core concepts to master
- **Why a queue/stream:** temporal **decoupling** (producer doesn't wait on consumer), **buffer spikes**, **retry/durability** when a worker is down, **fan-out** to many downstreams, independent **horizontal scale** of producers vs consumers.
- **Queue (point-to-point) vs pub/sub vs log:** queue = competing consumers, one winner per message (task/job). Pub/sub = one publish, many subscribers. **Log/stream (Kafka)** = append-only retained events; many **consumer groups** each get a full copy and track their own **offset**.
- **RabbitMQ mental model:** smart broker — producer → **exchange** (direct / topic / fanout) → queues → push to consumers; ack then delete. Great for **work queues**, complex routing, moderate throughput.
- **Kafka mental model:** dumb broker / smart consumer — producer appends to **topic partitions**; retention by time/size (not by "consumed"); consumers **pull** and commit offsets. Great for **event backbone**, replay, analytics, CDC, multi-team read.
- **Ordering:** global total order is expensive. Interview default: **order per key** (e.g. `user_id` / `order_id`) → same Kafka partition or FIFO message-group; parallelism across keys.
- **Delivery semantics:** **at-most-once** (may lose, never dup) · **at-least-once** (no loss, may dup — default real answer) · **exactly-once** (hard; Kafka EOS mostly Kafka→Kafka; once you write DB/API you still need app-level idempotency).
- **Ack / visibility / offset:** Rabbit ack / SQS **visibility timeout** / Kafka **offset commit** — commit/ack *after* successful side effects for at-least-once; commit-before-process ≈ at-most-once (can lose work).
- **Idempotent consumers:** required with at-least-once — dedupe key / unique constraint / upsert ("process payment `idempotency_key` once"). Never assume the broker alone saves you from double charges.
- **Backpressure:** unbounded queues hide overload until latency hockey-sticks or OOM. Bound depth / reject (HTTP 503) / shed / slow producers / scale consumers; Rabbit **prefetch**; Kafka consumer **lag** as the signal.
- **DLQ / poison messages:** after N failed receives, move to a **dead-letter queue** for inspect/replay — don't block the main queue forever.
- **When *not* to use a queue:** need sync reply on the critical path; tiny system where a DB transaction + worker table is enough; "microservices" that only need one RPC. Don't invent Kafka for a cron that runs once a night.

## Practice — how it's asked & how to attack it
Self-test drills (say answers out loud in ≤2 min each):

1. **Place the box:** Design Instagram-like upload. Where does the queue sit (API returns 202 → workers resize/transcode)? What if the worker dies mid-job? Name acks + retries + DLQ.
2. **Kafka vs RabbitMQ pick:** (a) email/SMS workers with priority routing, (b) clickstream used by fraud + analytics + ML feature store, (c) order.placed fan-out to inventory/notify/analytics. Pick broker + one sentence why.
3. **Semantics drill:** Payment charge on `OrderPlaced`. Choose at-least-once + idempotency key. What goes wrong if you claim "exactly-once" because Kafka transactions exist but the consumer writes Postgres?
4. **Ordering drill:** Chat messages for a room, or stock trades for a ticker. How do you get per-entity order *and* scale? What breaks if you use random partitioning?
5. **Backpressure drill:** Flash sale — producers enqueue 10× faster than payment workers. Draw: bound queue / 503 or waiting room / scale workers / DLQ for poison. Why "just add a bigger unbounded Redis list" fails?
6. **Pub/sub vs competing consumers:** One `OrderPlaced` event must update inventory *and* send email. One queue with two workers vs one topic with two consumer groups — which, and why?

## Common follow-ups / gotchas
- Drawing Kafka then describing "message deleted after consume" — that's Rabbit/SQS, not Kafka retention.
- Saying "exactly-once" without saying **where** (broker log vs end-to-end including DB/email).
- Ignoring **duplicates** on retry — interviewer will ask about double email / double charge.
- Unbounded queue as "infinite buffer" with no lag alert, DLQ, or reject path.
- Forcing global FIFO at million msg/s — order only where the product needs it (per key).
- Using a queue when the user needs an immediate sync answer (checkout total, auth) — keep that path RPC; queue the side effects.
- Hot partition: all events keyed by one celebrity `user_id` → one partition / one consumer melts.

## Where it appears
- **Campus / intern / new-grad HLD:** expected building block in news feed, chat, notification system, URL shortener (async analytics), e-commerce order, YouTube/TikTok upload — "add a queue" is table stakes; Kafka vs Rabbit + at-least-once + idempotency differentiates.
- **Experienced / mid-level (1–4 YOE):** consumer lag, partition key design, DLQ, backpressure, SNS→SQS fanout, event vs command, when EDA is overkill — common at Amazon, Meta, Uber, Flipkart, Atlassian, etc.
- **Frequency:** near-universal async building block; full "design Kafka" / "design SQS" is rarer and usually an experienced/infra loop. Depth stops at tradeoffs — not broker internals or Raft.
