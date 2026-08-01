# hq12_payment — Design a Payment System (idempotency, ledger, reconciliation)

**Interview relevance:** High — correctness-heavy HLD at Stripe / OpenAI / fintech + FAANG / Indian product cos (PhonePe, Razorpay, Flipkart Pay, Uber); probes idempotency, double-entry ledger, and reconciliation more than raw QPS.
**Type:** HLD-question
**Prereqs:** h06_consistency_cap, h08_message_queues, h04_databases_indexing, h10_api_design, h14_estimation; helpful: h05_db_scaling, h09_rate_limiting, h01_networking

## Read / watch (curated, in order)
- [ ] [Design a Payment System like Stripe](https://www.hellointerview.com/learn/system-design/problem-breakdowns/payment-system) — `Hello Interview` — best free interview framing (FRs → API → HLD → security / durability / async networks / scale deep dives)
- [ ] [System Design Delivery Framework](https://www.hellointerview.com/learn/system-design/in-a-hurry/delivery) — `Hello Interview` — 45-min skeleton you reuse; payments = **correctness & durability** over flashy throughput math
- [ ] [Designing a Payment System (Alex Xu Vol.2 chapter — free)](https://newsletter.pragmaticengineer.com/p/designing-a-payment-system) — `ByteByteGo` / Pragmatic Engineer — **canonical** pay-in flow: payment service → executor → PSP → wallet → ledger + reconciliation / exactly-once
- [ ] [Payment System](https://bytebytego.com/guides/payment-system/) — `ByteByteGo` — short free diagram of Buy-button → PSP → wallet → ledger → nightly settlement file; source: [payment-system.md](https://github.com/ByteByteGoHq/system-design-101/blob/main/data/guides/payment-system.md)
- [ ] [How to Avoid Double Payment](https://bytebytego.com/guides/how-to-avoid-double-payment/) — `ByteByteGo` — exactly-once = **retry (at-least-once) + idempotency key (at-most-once)**; newsletter twin: [How to avoid double payment?](https://blog.bytebytego.com/p/how-to-avoid-double-payment)
- [ ] [EP 39: Accounting 101 in Payment Systems](https://blog.bytebytego.com/p/ep-39-accounting-101-in-payment-systems) — `ByteByteGo` — double-entry journal lines; Assets = Liabilities + Equity; why ledgers make recon easy
- [ ] [Money movement when you buy a product online](https://blog.bytebytego.com/p/money-movement-when-you-buy-a-product) — `ByteByteGo` — **information flow vs fund flow**; clearing vs settlement — the reason reconciliation exists
- [ ] [Payment System (SDI Vol.2 course chapter)](https://bytebytego.com/courses/system-design-interview/payment-system) — `ByteByteGo` — book/course deep version (may be gated); pair with [Digital Wallet](https://bytebytego.com/courses/system-design-interview/digital-wallet) for ledger/balance focus
- [ ] [Designing robust and predictable APIs with idempotency](https://stripe.com/blog/idempotency) — `Stripe Eng` — industry-standard mental model for `Idempotency-Key`; API ref: [Idempotent requests](https://docs.stripe.com/api/idempotent_requests)
- [ ] [The Payment Intents API](https://docs.stripe.com/payments/payment-intents) / [lifecycle](https://docs.stripe.com/payments/paymentintents/lifecycle) — `Stripe docs` — real state machine (`requires_payment_method` → … → `succeeded` / `canceled`); webhooks: [Webhooks](https://docs.stripe.com/webhooks)
- [ ] [Stripe Elements](https://docs.stripe.com/payments/elements) — `Stripe docs` — tokenize PAN in iframe so card data never hits your servers; PCI: [PCI compliance guide](https://stripe.com/guides/pci-compliance), council: [pcisecuritystandards.org](https://www.pcisecuritystandards.org/)
- [ ] [Multi-step Processes (sagas)](https://www.hellointerview.com/learn/system-design/patterns/multi-step-processes) — `Hello Interview` — authorize → capture → ledger → webhook as a durable multi-step process (crash mid-flow)
- [ ] [Transactional outbox pattern](https://docs.aws.amazon.com/prescriptive-guidance/latest/cloud-design-patterns/transactional-outbox.html) — `AWS` — atomic DB write + event publish (no dual-write loss between payment row and webhook/queue)
- [ ] [UPI System Design Mock Interview](https://www.youtube.com/watch?v=QpLy0_c_RXk) — `Gaurav Sen` — India-relevant payments mock (routing, banks, failure/retry); foundations playlist: [System Design](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX)
- [ ] [At most once, at least once, exactly once](https://blog.bytebytego.com/p/at-most-once-at-least-once-exactly) — `ByteByteGo` — vocabulary for PSP calls and queue consumers
- [ ] [Double-entry bookkeeping](https://en.wikipedia.org/wiki/Double-entry_bookkeeping) — `Wikipedia` — debit/credit + accounting equation cheat sheet
- [ ] *Designing Data-Intensive Applications* ch.7 (Transactions) + ch.8 (Distributed Systems Trouble) — `DDIA` — ACID / isolation for money rows; book site: [dataintensive.net](https://dataintensive.net/)
- [ ] [system-design-primer](https://github.com/donnemartin/system-design-primer) — `primer` — CAP / queues / DB vocabulary applied here; follow-on dump: [InterviewReady system-design-resources](https://github.com/InterviewReady/system-design-resources)

## Core concepts to master
- **Scope first:** interview default = **e-commerce pay-in** (charge card via a **PSP** like Stripe/Braintree), not building VisaNet or a consumer wallet app. Say so out loud.
- **Correctness > throughput:** never double-charge, never lose a settled payment, always leave an **audit trail**. Availability matters, but **CP for money mutations** (strong consistency on payment + ledger writes).
- **Exactly-once side effects:** networks only give at-least-once; you get **exactly-once business effect** via **retry + idempotency key** (client UUID in `Idempotency-Key`; server stores key → response; same key returns cached result).
- **Payment as a state machine:** e.g. `created → pending/authorized → captured/succeeded | failed | canceled` (+ refunds). Illegal transitions must be DB-enforced; map to Stripe PaymentIntent mental model.
- **Components (Alex Xu shape):** **Payment service** (orchestrate) → **Payment executor** (call PSP) → **PSP / card schemes** (move money) → **Wallet** (merchant balance) → **Ledger** (immutable journal).
- **Double-entry ledger:** every money move = ≥2 journal lines that **sum to zero** (debit one account, credit another). Append-only; balance = sum of entries (optional cached balance). Makes audit + recon tractable.
- **Info flow ≠ fund flow:** your DB updates instantly; **settlement** (real bank money) is async / batch. Nightly **settlement files** from PSP/bank must be **reconciled** against internal ledger — mismatches become tickets, not silent drift.
- **PCI scope reduction:** never store raw PAN; use **hosted fields / Elements** so card data is tokenized to the PSP. Mention PCI DSS; don’t invent compliance theater.
- **Dual-write fix:** updating `payments` and publishing “payment.succeeded” must be atomic → **transactional outbox** (or CDC) + **idempotent consumers**.
- **Async confirmation:** PSP/3DS can delay; trust **webhooks / polling** for final status, not only the sync HTTP response. Merchant webhooks need signature verify + idempotent delivery.
- **Retries with backoff + jitter:** timeout ≠ failure; safe retry only with the **same** idempotency key; exponential backoff so you don’t stampede a downed PSP.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈45 min). Anchor on **idempotency + ledger + reconciliation**; keep subscriptions / multi-PSP routing / FX below the line unless asked.

### 1. Requirements (functional + non-functional) & scale assumptions
- **Clarify product:** Amazon-style **pay-in** backend? Stripe-like PSP for merchants? Wallet P2P? (Pick one — usually e-commerce + third-party PSP.)
- **FR (core):** create/charge a payment; track status (`pending` / `succeeded` / `failed`); survive retries without double charge.
- **FR (optional / ask):** partial/full refunds, merchant payouts, saved payment methods, multi-seller cart (one event → many orders).
- **NFR:** **financial integrity** (no double charge / lost settle); **durability + auditability**; low p99 for create/confirm where possible; **PCI** (no raw cards on your servers); scale to interview number (often **~1k–10k TPS peak** — Hello Interview uses ~10k).
- **Out of scope (say so):** building card networks, full fraud ML, multi-currency FX engine, chargeback workflows (mention only if probed).

### 2. Back-of-envelope estimation
State assumptions; for payments, math is secondary to correctness — still show you can size storage/QPS:
- Example: **10M payments / day** ≈ **115 TPS** avg; peak **5–10×** → design for **~1k TPS** (or use interviewer’s 10k).
- Payload ~**1 KB**/payment + **2–4 ledger lines** → tens of GB/day raw; retain years → **partition/archive** ledger by time.
- Sync path latency budget dominated by **PSP RTT** (100s of ms), not your DB.
- Implication: one SQL primary can start; **shard by `merchant_id` / `payment_id`** when hot merchants or write volume demand it — don’t invent Kafka for the charge itself.

### 3. API / interface
- `POST /v1/payments`  
  Headers: `Idempotency-Key: <uuid>`  
  Body: `{ amount, currency, merchant_id, customer_id, payment_method_token, capture_method? }`  
  → `{ payment_id, status, client_secret? }`
- `GET /v1/payments/{payment_id}` → status + amounts
- `POST /v1/payments/{payment_id}/refunds` (+ its own idempotency key)
- `POST /v1/webhooks/psp` — inbound PSP events (verify signature)
- Optional outbound: merchant webhook delivery API / dashboard poll
- Never accept raw card PAN on your API if designing a merchant platform — accept **tokens** from Elements / PSP.js.

### 4. Data model
```
payments(
  payment_id PK,
  merchant_id, customer_id,
  amount, currency,
  status,                 -- state machine
  psp_reference,          -- PSP charge / PaymentIntent id
  idempotency_key UNIQUE, -- per merchant scope
  created_at, updated_at
)

idempotency_records(
  scope, key UNIQUE,      -- e.g. merchant_id + key
  request_hash,
  response_body,
  status_code,
  created_at              -- TTL ~24h (Stripe-style) or longer
)

ledger_accounts(account_id PK, owner_type, owner_id, currency)
ledger_entries(
  entry_id PK,
  journal_id,             -- groups balancing lines
  account_id,
  amount,                 -- signed or debit/credit columns
  payment_id,
  created_at              -- append-only; no updates
)

wallets(merchant_id PK, currency, available_balance, held_balance, version)
outbox(id, aggregate_id, event_type, payload, created_at, published_at)
reconciliation_runs(id, psp_file_id, status, mismatch_count, run_at)
```
- Enforce **UNIQUE(idempotency_key)** (scoped) and **balanced journal** (sum of lines for `journal_id` = 0) in the same DB transaction as status transitions.

### 5. High-level architecture
```
Merchant / Checkout
   │  (Stripe.js / Elements → token; no PAN to you)
   ▼
API Gateway → Payment Service
                 │ 1. check idempotency key → return cached if hit
                 │ 2. insert payment (pending) + outbox (same TX)
                 ▼
            Payment Executor ──HTTPS──► PSP (Stripe / …) ──► card networks / banks
                 │
                 │ on success (sync or webhook)
                 ▼
            Wallet update + Ledger journal (ACID TX)
                 │
                 ▼
            Outbox relay → Queue → Merchant webhooks / notifications

Nightly: PSP settlement file → Reconciliation job ↔ Ledger → alert / repair queue
```
- Stateless payment workers; **SQL** (Postgres) for payments + ledger; Redis optional for idempotency cache **in front of** durable store (source of truth = DB).
- Risk/fraud check as sync gate or async side path — don’t pretend you built Radar unless asked.

### 6. Deep dives & the 2–3 key tradeoffs interviewers probe
1. **Idempotency implementation:** store `(key → response)` **before** calling PSP vs after? Best practice: persist “in progress” under the key, call PSP with **PSP-side idempotency key too**, then finalize. Same client key must never create two PSP charges. Compare params on replay (Stripe rejects mismatched body).
2. **Ledger vs mutable balance only:** balance-only is fast but loses audit trail and makes recon painful; **double-entry append-only** is the interview answer. Cached `wallets.balance` updated in the **same TX** as ledger lines (or derived asynchronously with care).
3. **Sync PSP call vs async + webhook:** sync is simpler UX; webhooks are source of truth for delayed/3DS methods. Design for **both**: optimistic pending + durable webhook handler that is idempotent on `psp_event_id`.
4. **Reconciliation:** daily/continuous compare internal ledger totals ↔ PSP settlement file; classify mismatches (missing internal, missing PSP, amount skew); never “fix” by editing ledger history — post **adjustment journals**.
5. **Saga vs single DB TX:** payment + ledger + wallet in one DB = simple; cross-service = **saga/outbox** with compensating refunds — Hello Interview multi-step pattern.

### 7. Bottlenecks / how you scale it
- **Hot merchant wallet row:** optimistic versioning / row lock; for extreme credit fan-in, **batch ledger flush** or shard sub-accounts — call out the tradeoff (fresher balance vs write amplification).
- **PSP latency / outages:** timeouts, circuit breaker per PSP, queue retries with backoff; never unbounded auto-retry without idempotency.
- **Idempotency store:** unique index + short critical section; shard by key hash at huge QPS.
- **Ledger growth:** partition by month; online queries use recent partitions + aggregates; cold archive to object storage.
- **Webhook storms:** durable queue, concurrency limits, dedupe on event id.
- **Recon at scale:** stream settlement files, keyed joins on `psp_reference`, human ops queue for residual breaks.
- **Multi-region:** active-active money writes are hard — usually **single primary region for ledger** + regional read replicas; mention clock/conflict pain if interviewer pushes geo.

## Common follow-ups / gotchas
- “Timeout after charge — did we take money?” → ambiguous; **retry same idempotency key**; reconcile with PSP list/get by key; never create a new key on retry.
- “How do you guarantee exactly-once?” → you don’t on the wire; you guarantee **exactly-once effect** (at-least-once delivery + idempotent handler).
- “Wallet says $X but bank says $Y” → expected until settlement; **reconciliation** closes the gap; show adjustment journals + alerting.
- “Where do card numbers live?” → **not in your DB**; PSP token / Elements; PCI scope = SAQ A-style if hosted fields only.
- “Refund after partial capture / double refund?” → refund state machine + idempotency; ledger posts reversing entries.
- “What if outbox published but wallet TX rolled back?” → that’s why outbox is **in the same TX**; consumers still idempotent for at-least-once relay.
- Drawing microservices everywhere but keeping **no ledger** — interviewers treat that as a fail for payments.

## Where it appears
- **Experienced / fintech / Stripe-adjacent:** very common full round; depth on idempotency, ledger, recon, PCI.
- **Campus / new-grad HLD:** less common than URL shortener / chat, but rising at product cos with payments (PhonePe, Razorpay, Amazon, Uber, Flipkart); often framed as “checkout payment” or **UPI**.
- **Frequency:** **high** for backend/fintech tracks; treat as mandatory if targeting payments companies — practice the **three pillars** (idempotency, ledger, reconciliation) until you can whiteboard them cold.
