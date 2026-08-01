# HQ08 — Design a notification / push system

**Interview relevance:** High — classic 45-min HLD at FAANG + Indian product cos (Meta, Uber, Flipkart, PhonePe, Amazon, Microsoft); probes async queues, multi-channel delivery (APNs/FCM/SMS/email), preferences, idempotency, and priority isolation.
**Type:** HLD-question
**Prereqs:** h08_message_queues, h01_networking, h03_caching, h14_estimation; helpful: h09_rate_limiting, h06_consistency_cap, h02_load_balancing

## Read / watch (curated, in order)
- [ ] [Design a Notification System](https://www.hellointerview.com/learn/system-design/problem-breakdowns/notification-system) — `Hello Interview` — best free end-to-end interview breakdown: platform framing, surge vs OTP isolation, preferences, durability, dedupe deep dives
- [ ] [How Does a Typical Push Notification System Work?](https://bytebytego.com/guides/how-does-a-typical-push-notification-system-work/) — `ByteByteGo` — gateway → distribution (templates + preferences) → queues → channel services → tracking diagram
- [ ] [Design a Notification System (SDI Vol.1 course chapter)](https://bytebytego.com/courses/system-design-interview/design-a-notification-system) — `ByteByteGo` — Alex Xu canonical chapter (APNs/FCM/SMS/email, MQ decoupling, settings, retry/log); course may be gated
- [ ] [EP14: How are notifications pushed… (FCM walkthrough)](https://blog.bytebytego.com/p/ep14-algorithms-you-should-known) — `ByteByteGo` — device registration token → app server → FCM queue/route → platform transport (skip the algorithms half if short on time)
- [ ] [What is a MESSAGE QUEUE and Where is it used?](https://www.youtube.com/watch?v=oUJbuFMyBDk) — `Gaurav Sen` — why producers never call Twilio/APNs synchronously; buffer + async workers mental model
- [ ] [What is the Publisher Subscriber Model?](https://www.youtube.com/watch?v=FMhbR_kQeHw) — `Gaurav Sen` — when fan-out is pub/sub (topics) vs work-queue (one consumer owns a send)
- [ ] [Managing Long Running Tasks](https://www.hellointerview.com/learn/system-design/patterns/long-running-tasks) — `Hello Interview` — `202` + enqueue pattern (intake must not wait on providers)
- [ ] [Kafka Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/kafka) — `Hello Interview` — durable buffer, partitions, consumer groups for channel workers
- [ ] [How Slack Put Kafka in Front of Its Redis Job Queue](https://www.hellointerview.com/learn/system-design/in-the-wild/slack-job-queue) — `Hello Interview` — real push/job pipeline: Kafka absorbs bursts, Redis stays the short dispatch window
- [ ] [Real-time Updates pattern](https://www.hellointerview.com/learn/system-design/patterns/realtime-updates) — `Hello Interview` — optional in-app path (WS / SSE) vs offline OS push
- [ ] [Firebase Cloud Messaging](https://firebase.google.com/docs/cloud-messaging) — `Google` — don’t reinvent device push; pair with [FCM server send](https://firebase.google.com/docs/cloud-messaging/server)
- [ ] [Sending notification requests to APNs](https://developer.apple.com/documentation/usernotifications/sending-notification-requests-to-apns) — `Apple` — HTTP/2 provider API, device token, payload limits, invalid-token handling
- [ ] [Twilio SMS docs](https://www.twilio.com/docs/sms) — `Twilio` — canonical SMS provider shape (costly channel → rate + prefer push/email when possible)
- [ ] [SendGrid](https://sendgrid.com/) — `Twilio SendGrid` — transactional/marketing email provider (Alex Xu ch.10-style third party)
- [ ] [Amazon SNS](https://docs.aws.amazon.com/sns/latest/dg/welcome.html) — `AWS` — optional managed pub/sub + SMS/email/push fan-out if interviewer wants cloud-native shorthand
- [ ] [You Cannot Have Exactly-Once Delivery](https://bravenewgeek.com/you-cannot-have-exactly-once-delivery/) — `Brave New Geek` — at-least-once + idempotency/dedupe is the honest answer for provider sends
- [ ] [How Reddit Delivers Notifications to Tens of Millions of Users](https://blog.bytebytego.com/p/how-reddit-delivers-notifications) — `ByteByteGo` — staff-depth follow-up: budget / fatigue, retrieval → rank → rerank (not the basic HLD; cite after core pipeline)
- [ ] [system-design-primer — Message queues](https://github.com/donnemartin/system-design-primer#message-queues) — `primer` — queue vocabulary for decoupling intake from delivery
- [ ] [ByteByteGo — system_design_links (Ch.10 refs)](https://github.com/alex-xu-system/bytebytego/blob/main/system_design_links.md) — `ByteByteGo` — Twilio/SendGrid/Mailchimp + exactly-once essay pointers from the book chapter
- [ ] *Designing Data-Intensive Applications* ch.11 (Stream Processing) — `DDIA ch.11` — logs vs queues when arguing Kafka-backed delivery; book site: [dataintensive.net](https://dataintensive.net/)
- [ ] [InterviewReady — system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` / Gaurav Sen — curated follow-on dump after the walkthrough
- [ ] [System Design Interview: A Step-By-Step Guide](https://www.youtube.com/watch?v=i7twT3x5yv8) — `ByteByteGo` — clarify *platform* vs consumer product + transactional vs marketing before drawing boxes

## Core concepts to master
- **Platform, not product:** other services call *you* (`POST /notifications`); you own preferences, templates, retries, provider credentials — callers don’t talk to APNs/FCM/Twilio directly.
- **Channels:** mobile push (APNs / FCM), email, SMS, optional in-app inbox. Push = wake OS; in-app = already-open session (WS/SSE/poll).
- **Transactional vs marketing:** OTPs / payments / security must never queue behind a 1M-user promo blast → **separate topics / worker pools / priority lanes**.
- **Async by default:** intake validates + persists/enqueues → **`202 Accepted`**. Providers are slow, flaky, rate-limited; sync calls couple product APIs to third parties.
- **Preferences gate every send:** per-type × per-channel opt-in/out, quiet hours (timezone), verified contact points; cache hot path in Redis; **transactional may bypass quiet hours** (product call with interviewer).
- **Device tokens:** store `(user_id, device_id, platform, token, updated_at)`; prune on provider “Unregistered” / invalid; multi-device fan-out per user.
- **Delivery semantics:** end-to-end **exactly-once is a lie** across networks/providers → design **at-least-once** + **idempotency key** (dedupe *before* provider call) so retries don’t double-SMS.
- **Templates:** producers send `template_id` + params; render once after preference pass (localization, length limits — APNs ~4KB).
- **Retries / DLQ:** exponential backoff + jitter for transient 5xx/429; permanent failures (bad token, hard bounce) → drop + cleanup, don’t infinite-retry; dead-letter for ops.
- **Rate limits:** per-user / per-channel frequency caps (fatigue) **and** provider quotas (Twilio/SendGrid/APNs). Marketing throttled; OTP path protected.
- **Tracking:** statuses `queued → sent → delivered/failed` via provider webhooks; “sent to APNs” ≠ “user saw it.”
- **Don’t reinvent push transport:** keep persistent connections to phones inside Apple/Google; your job is routing + reliability around their APIs.

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈45 min):

### 1. Requirements (functional + non-functional) & scale assumptions
**Functional (in scope):** send to a user (or campaign segment) via push / email / SMS; immediate + scheduled; honor preferences + quiet hours; at-least-once with dedupe; basic delivery status.
**Out of scope (say so):** rich template CMS / A/B UI, full analytics dashboards, ML ranking (unless asked — Reddit-style), building your own APNs/FCM.
**NFRs:** high-priority (OTP) p99 ≪ few seconds; marketing can lag minutes; no silent drop after accept; isolate channels so email outage ≠ SMS outage; absorb **campaign surges** without starving transactional traffic.
**Clarify:** channels in scope; transactional vs promo; in-app needed?; retention of notification history.

### 2. Back-of-envelope estimation
Pick round numbers with the interviewer, e.g.:
- **10M notifs/day** → ~115/s average — easy if uniform.
- Real shape: **1M campaign in 5 min** → ~3.3K/s; design for **~5K/s surge** (or ask their number). Peak ≫ average.
- Mix example (Alex Xu-style): tens of M push + fewer email + least SMS (SMS cost dominates).
- Storage: metadata/log ~hundreds of bytes/event; device tokens + prefs fit in DB + Redis; don’t store large bodies forever.
- Workers: partition parallelism ≈ desired send QPS / provider RPS per connection; pool HTTP/2 to APNs/FCM.

### 3. API / interface
- `POST /v1/notifications` `{ idempotency_key, user_id | user_ids | segment_id, template_id, params, channels?, priority, schedule_at? }` → `202 { notification_id }`
- `POST /v1/notifications/batch` for campaigns (or create `campaign` then async fan-out).
- `GET /v1/notifications/{id}` status; `GET/PUT /v1/users/{id}/preferences`
- Client device: `PUT /v1/devices` `{ device_id, platform, push_token }` on login/token refresh.
- Auth: service-to-service for producers; user auth for prefs/devices.
- Optional webhooks inbound from providers → `POST /internal/provider-callbacks/{channel}`.

### 4. Data model
- **UserContact / Device:** `user_id`, email, phone (verified flags); devices[`device_id`, platform, token, last_seen].
- **Preference:** `(user_id, notification_type, channel) → opted_in`; `quiet_hours_start/end`, `timezone`.
- **Template:** `template_id`, channel, locale, body/title with placeholders.
- **Notification:** `notification_id`, producer, user_id, type, priority, payload/template refs, `idempotency_key`, `created_at`, `schedule_at`.
- **DeliveryAttempt:** `(notification_id, channel, device_or_address)`, status, provider_msg_id, attempts, last_error; TTL/archive.
- **Dedupe store:** Redis `SETNX idempotency_key` (or hash of user+type+business_id) with TTL (e.g. 24h transactional / longer for campaigns).
- **Campaign / segment** (if needed): segment definition + cursor for paced fan-out.

### 5. High-level architecture / component breakdown
1. **Producers** (order, auth, social, marketing) → **Notification API** (validate, authz, idempotency, light preference check optional).
2. Persist notification row (or outbox) → publish to **Kafka / SQS** (topics by **priority** and/or **channel**).
3. **Scheduler** service for `schedule_at` / digests (writes back into same API/queue when due).
4. **Dispatcher / orchestrator** workers: load prefs + tokens (Redis cache) → decide channels → enqueue **channel queues**.
5. **Channel workers:** Push (APNs/FCM), Email (SES/SendGrid), SMS (Twilio) — independent scale, retries, DLQ.
6. **Preference + Template + Device** services/DBs; Redis for prefs/tokens/dedupe/rate limits.
7. **Tracking / webhook handler** updates DeliveryAttempt; metrics for lag, fail rate, provider 429s.
8. Optional **in-app:** write inbox row + pub/sub to connected gateways (see realtime pattern).

**Happy path (OTP push):** Auth → `POST /notifications` (critical) → Kafka `notif.critical` → push worker → FCM/APNs → `sent`; webhook → `delivered`.

**Campaign path:** Marketing → create campaign → paced fan-out generator → `notif.bulk` topic → email/push workers with stricter rate limits; never share consumer lag with critical topic.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **Priority isolation:** one shared queue → promo backlog delays OTP. Prefer **separate topics + worker pools** (and/or weighted fair scheduling). Overload should stretch marketing, not transactional.
2. **At-least-once vs double-send:** provider timeout after send → retry duplicates. **Dedupe key SETNX before provider call**; idempotent business keys (`order_id + shipped`); accept rare dupes only if product allows — never for SMS OTP without care.
3. **Preferences + quiet hours:** cache aggressively but **invalidate on write**; define whether security alerts bypass DND; defer non-critical to end of quiet window via scheduler.
4. **Campaign fan-out:** don’t explode 10M messages synchronously in the API — generator/cursor workers pace to provider limits; store segment membership separately.
5. **Provider failure:** circuit breaker + secondary provider (e.g. SES ↔ SendGrid); channel isolation so one bad integration doesn’t take the platform down.
6. **In-app vs push:** online → cheap inbox/WS; offline → APNs/FCM. Collapse/coalesce noisy social events (“Alice and 5 others liked…”) before send.

### 7. Bottlenecks / how you scale it
- **Kafka / queue lag** on bulk topics → more partitions + workers; never let bulk consumer group steal critical capacity.
- **Hot preference/token Redis** → shard by `user_id`; local LRU in workers with short TTL.
- **Provider rate limits / 429** → token buckets per provider + per-tenant; backoff; smooth campaigns.
- **SMS cost & throughput** → reserve for high-value; fallback email/push; verify numbers.
- **Invalid token storm** after app reinstall → aggressive prune on permanent errors.
- **Webhook / tracking write QPS** → batch writes, TTL old attempts, don’t block send path on analytics.
- **Multi-region:** regional API + queues near users; provider endpoints are global — watch data residency for phone/email.
- **Failure:** API durable accept (DB/outbox) before 202; workers restart-safe via idempotency; DLQ + replay tooling.

## Common follow-ups / gotchas
- Calling APNs/Twilio **synchronously** from the order/payment request path.
- One Kafka topic for OTP + marketing → **head-of-line blocking**.
- Claiming **exactly-once** delivery without idempotency/dedupe story ([Brave New Geek](https://bravenewgeek.com/you-cannot-have-exactly-once-delivery/)).
- Setting dedupe **after** provider success (timeout → double charge/SMS).
- Ignoring **user preferences / quiet hours / unsubscribe** (compliance + product).
- Forgetting **multi-device** tokens or never deleting invalid ones.
- No **retry vs DLQ** distinction (infinite retry on hard bounces).
- Building a custom persistent connection to phones instead of **APNs/FCM**.
- Campaign API that tries to **fan out millions inline**.
- Skipping **estimation of surge** and designing only for average QPS.

## Where it appears
- **Campus / intern / new-grad:** very common “design notification service” / “push notifications”; expect channels, queue decoupling, preferences, and basic retry.
- **Experienced (1–4+ YOE):** priority isolation, idempotency timing, provider limits, campaign pacing, webhook status, estimation of burst QPS; Meta/Uber/Amazon/Flipkart-style depth.
- **Frequency:** top-tier HLD prompt alongside chat, news feed, rate limiter, URL shortener. Depth = tradeoffs around reliability and traffic isolation — not implementing APNs or ML rankers unless explicitly asked.
