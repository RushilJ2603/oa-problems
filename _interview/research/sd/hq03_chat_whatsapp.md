# HQ03 — Design a chat / messaging system (WhatsApp / Messenger)

**Interview relevance:** High — classic 45-min HLD round at FAANG + Indian product cos (Meta, WhatsApp/Meta infra, Uber, Flipkart, Atlassian, PhonePe, etc.); probes WebSockets, stateful gateways, offline delivery, fan-out, and presence.
**Type:** HLD-question
**Prereqs:** h01_networking (WebSockets / push), h02_load_balancing, h08_message_queues, h14_estimation; helpful: h03_caching (Redis session/presence), h05_db_scaling, h06_consistency_cap, h11_storage (media / object store)

## Read / watch (curated, in order)
- [ ] [Short/long polling, SSE, WebSocket](https://bytebytego.com/guides/shortlong-polling-sse-websocket/) — `ByteByteGo` — why chat picks WebSocket over polling/SSE; protocol tradeoffs before drawing boxes
- [ ] [Real-time Updates pattern](https://www.hellointerview.com/learn/system-design/patterns/realtime-updates) — `Hello Interview` — persistent connections, pub/sub fan-out across gateways, sticky vs redistributed state
- [ ] [Design a Messaging App Like WhatsApp](https://www.hellointerview.com/learn/system-design/problem-breakdowns/whatsapp) — `Hello Interview` — best free end-to-end walkthrough: requirements → WS API → inbox → media → Redis pub/sub scale-out → multi-device
- [ ] [FAANG System Design Interview: Design A Chat System](https://www.youtube.com/watch?v=okrR1KXNLtA) — `ByteByteGo` — ~9 min WhatsApp/Messenger/Discord/Slack framing: WS chat servers, presence, push (APNs/FCM)
- [ ] [EP 42: Designing a chat application](https://blog.bytebytego.com/p/ep-42-designing-a-chat-application) — `ByteByteGo` — login/presence + 1:1 messaging flow diagram (sequencing → store → sync queue → push-or-WS)
- [ ] [Design a Chat System (SDI Vol.1 course chapter)](https://bytebytego.com/courses/system-design-interview/design-a-chat-system) — `ByteByteGo` — Alex Xu canonical chapter (WebSocket vs HTTP, chat/presence/KV/push layers, small-group fan-out)
- [ ] [High-Level Design for WhatsApp](https://medium.com/@interviewready/high-level-design-for-whatsapp-133b317977e2) — `InterviewReady` / Gaurav Sen org — gateway + session map, receipts, group fan-out limits, media offload
- [ ] [What is the Publisher Subscriber Model?](https://www.youtube.com/watch?v=FMhbR_kQeHw) — `Gaurav Sen` — pub/sub mental model used when gateways don’t share sockets
- [ ] [System Design Interview: A Step-By-Step Guide](https://www.youtube.com/watch?v=i7twT3x5yv8) — `ByteByteGo` — clarify *which* chat (WhatsApp vs Slack vs Discord) before designing
- [ ] [1 million is so 2011](https://blog.whatsapp.com/1-million-is-so-2011) — `WhatsApp Eng` — FreeBSD + Erlang sustaining **2M+** TCP connections/box (scale folklore interviewers expect)
- [ ] [ONE MILLION!](https://blog.whatsapp.com/on-e-millio-n) — `WhatsApp Eng` — earlier 1M ESTABLISHED TCP milestone; same stack story
- [ ] [Facebook Chat](https://engineering.fb.com/2008/05/13/web/facebook-chat/) — `Meta Eng` — Erlang long-poll chat servers; why chat state ≠ classic request/response web apps
- [ ] [end-to-end encryption](https://blog.whatsapp.com/end-to-end-encryption?lang=en_US) — `WhatsApp` — product claim; pair with [Signal: WhatsApp’s Signal Protocol integration](https://signal.org/blog/whatsapp-complete/) and [WhatsApp Security Whitepaper (PDF)](https://www.whatsapp.com/security/WhatsApp-Security-Whitepaper.pdf) — mention E2EE depth, don’t derive crypto in 45 min
- [ ] [Signal Protocol docs](https://signal.org/docs/) — `Signal` — optional depth if interviewer pushes on Double Ratchet / sender keys
- [ ] [Firebase Cloud Messaging](https://firebase.google.com/docs/cloud-messaging) — `Google` — offline Android/iOS wake path (don’t reinvent device push)
- [ ] [system-design-primer — Message queues](https://github.com/donnemartin/system-design-primer#message-queues) — `primer` — fan-out / async delivery vocabulary for group and offline paths
- [ ] [Design a chat server (OOD notebook)](https://github.com/donnemartin/system-design-primer/blob/master/solutions/object_oriented_design/online_chat/online_chat.ipynb) — `primer` — optional LLD companion (classes for User/Chat/Message); not the HLD answer
- [ ] *Designing Data-Intensive Applications* ch.11 (Stream Processing) — `DDIA ch.11` — logs vs queues when discussing Kafka-backed delivery; book site: [dataintensive.net](https://dataintensive.net/)
- [ ] [InterviewReady — system-design-resources](https://github.com/InterviewReady/system-design-resources) — `InterviewReady` — curated link dump; optional follow-on reading after the walkthrough

## Core concepts to master
- **Clarify the product:** WhatsApp/Messenger (1:1 + small groups, mobile, offline store) ≠ Slack/Discord (large channels, fan-out-on-read). Cap group size early (e.g. 100 / 256 / 1024).
- **Transport:** HTTP for auth/profile/media URLs; **WebSocket (or custom TCP)** for bidirectional chat. Polling wastes battery; SSE is server→client only.
- **Stateful chat gateways:** each client pins to one gateway holding the socket; modern boxes hold 10⁴–10⁶ connections (WhatsApp Erlang lore: millions/box).
- **Cross-gateway routing:** sender and receiver rarely share a host → **session registry** (`user_id → gateway_id`) and/or **sharded pub/sub** (Redis) keyed by `user_id` (or adaptive chat-id for large groups).
- **Durability before push:** write message (+ per-recipient **inbox**) to durable store **then** best-effort realtime publish. Pub/sub alone is at-most-once; inbox/sync is the safety net.
- **Delivery semantics:** at-least-once to devices + **client ACK** + **idempotent `message_id`** (client UUID). Exactly-once end-to-end is not the interview default.
- **Ordering:** per-conversation (or per-sender-in-chat) sequence / partition key — not global total order.
- **Presence:** heartbeats + Redis TTL / last-seen; treat as **eventual / lossy** (don’t couple to the message write path).
- **Receipts:** sent (server accepted) → delivered (device ACK) → read (client event); each is another fan-out message.
- **Media off path:** pre-signed upload to object storage; chat carries a URL/hash, not blobs over WS.
- **Offline / multi-device:** per-**device** inbox or sync cursor; APNs/FCM when no WS. Cap linked devices.
- **E2EE (mention, don’t implement):** Signal Protocol — server stores ciphertext + metadata; complicates server-side search/moderation (product tradeoff vs Messenger history).

## Practice — how it's asked & how to attack it
Interview walk-through skeleton (≈45 min):

### 1. Requirements (functional + non-functional) & scale assumptions
**Functional (in scope):** 1:1 + small group text; online/offline delivery; sent/delivered/read; presence/last-seen; media via separate upload; optional typing indicators.
**Out of scope (say so):** voice/video calls, Stories/channels at Discord scale, full E2EE crypto design, spam/abuse ML.
**NFRs:** p99 delivery latency ≪ 500 ms when online; no silent message loss; high availability of gateways; store offline messages for days–weeks (e.g. 30d TTL) unless product says otherwise.
**Clarify:** history forever on server (Messenger-like) vs store-until-delivered / client-primary (classic WhatsApp framing).

### 2. Back-of-envelope estimation
Pick round numbers with the interviewer, e.g.:
- 500M DAU, ~25% concurrent online → **~125M** open sockets.
- ~40 msgs/user/day → ~20B msgs/day ≈ **~230K msg/s** average; peak **5–10×**.
- Group fan-out: if avg recipients ≈ 2–3 after 1:1 dominance, delivery QPS ≈ few× send QPS.
- Gateways: at 100K–1M conns/box → hundreds–thousands of chat servers.
- Storage: avg 100 B ciphertext + metadata; 20B/day → ~2 TB/day raw (before replication/indexes); media dwarfs text → object store + CDN.
- Presence heartbeats (e.g. every 30s) can dominate QPS — keep presence off the message DB write path.

### 3. API / interface
- **REST/HTTP:** signup/login, profile, create group, **pre-signed media URL**, history pagination (if server history).
- **WebSocket commands (JSON/Protobuf):** `sendMessage {chatId, clientMsgId, ciphertext, attachmentRefs}` → `{serverMsgId, seq}`; `ack {messageId}`; `receipt {messageId, type}`; `presence` / `typing`.
- **Server → client:** `newMessage`, `receiptUpdate`, `chatUpdate`; client must **ACK** so inbox can clear.
- Auth: token on WS handshake; reconnect with last `seq` / inbox sync.

### 4. Data model
- **User / Device:** `user_id`, devices[`device_id`, push_token, last_seq].
- **Chat:** `chat_id`, type (dm/group), created_at; **ChatMember:** `(chat_id, user_id)` + GSI/reverse index `(user_id → chat_id)`.
- **Message:** PK `chat_id`, SK `seq` or `timestamp+id`; fields: sender_id, client_msg_id (unique), ciphertext, media_refs. Wide-column / KV (Cassandra/Dynamo) fits append + time-range reads.
- **Inbox (undelivered):** PK `user_id` or `device_id`, SK `message_id` / time; TTL; delete on ACK.
- **Session:** `user_id → gateway_id` (Redis); **Presence:** `user_id → online|last_seen` with TTL refreshed by heartbeat.
- **Group fan-out:** for small N, copy inbox rows per recipient (fan-out-on-write).

### 5. High-level architecture / component breakdown
1. **Clients** ↔ **L4 LB** ↔ **Chat gateway cluster** (WS; local `user→conn` map).
2. **API / Auth service** (HTTP, stateless).
3. **Message service:** validate → assign seq/id → durable write (messages + inboxes) → publish to **pub/sub or Kafka**.
4. **Routing backplane:** Redis pub/sub (sharded by user) *or* Kafka + workers that look up session and RPC/push to the right gateway.
5. **Session + Presence** (Redis).
6. **Push service** → APNs / FCM when offline.
7. **Media:** client → object storage (S3) via pre-signed URL; CDN for download.
8. **Optional:** sequencing service, group metadata service, notification preference service.

**Happy path (online 1:1):** A→gateway → persist → pub/sub to B’s channel → B’s gateway → WS push → B ACK → clear inbox → delivery receipt to A.

### 6. Deep dives & the 2–3 key tradeoffs an interviewer probes
1. **How do we scale beyond one gateway?** Naive LB without routing breaks delivery. Prefer **sharded Redis pub/sub by `user_id`** (durable inbox first) over “Kafka topic per user” (won’t scale). Consistent-hash sticky users is workable but painful on rebalance.
2. **Group fan-out-on-write vs fan-out-on-read:** write-amplification OK for ≤100–1K members; large channels (Discord) store one log and let clients pull/cursor — different design.
3. **Multi-device sync:** inbox/cursor per **device**; pub/sub still per user; all devices get copies; cap device count.
4. **WS death / flaky networks:** app-level **ping/pong** (don’t wait for TCP timeout); ACK timeout → close → reconnect → inbox catch-up; exponential backoff + jitter on reconnect (thundering herd).
5. **Ordering & retries:** per-chat seq; client `client_msg_id` dedupe; at-least-once + idempotent apply on client.
6. **E2EE vs features:** server can’t read/search plaintext; multi-device key management is the hard part — usually “mention Signal, defer crypto.”

### 7. Bottlenecks / how you scale it
- **Connection count / FD limits** on gateways → more boxes, efficient runtime (evented / Erlang-style), tune kernel socket limits.
- **Hot users / large groups** → adaptive pub/sub key (user vs chat), rate limits, degrade receipts/typing first.
- **Inbox / message DB write QPS** → partition by `user_id` / `chat_id`; TTL compaction; don’t store media in DB.
- **Presence heartbeat storm** → separate store, coarser TTL, fan-out presence only to open chats / friends subset.
- **Push provider quotas** → batch, respect quiet hours, collapse notifications.
- **Regional latency** → regional gateway pools + local session; cross-region for roaming users.
- **Failure:** gateway death → clients reconnect elsewhere, re-subscribe pub/sub, drain inbox; no single gateway is source of truth for history.

## Common follow-ups / gotchas
- Drawing WebSockets then **forgetting cross-server routing** (both users on different gateways).
- Using **Kafka topic-per-user** for inbox — operationally impossible at WhatsApp scale.
- Claiming **exactly-once** delivery without client idempotency / ACK story.
- Putting **images on the WS path** or as DB BLOBs instead of pre-signed object storage.
- **Global message ordering** across all chats — unnecessary and unscalable.
- Treating **presence** as strongly consistent or writing every heartbeat to Cassandra.
- Designing **Discord-sized channels** with WhatsApp fan-out-on-write (or vice versa) after the interviewer scoped small groups.
- Ignoring **multi-device** or clearing a shared inbox when only one device ACKed.
- Reconnect **thundering herd** with synchronized retries after a regional outage.
- Spending half the interview on **Signal Protocol math** instead of delivery, storage, and fan-out.

## Where it appears
- **Campus / intern / new-grad:** very common “design WhatsApp/chat” prompt; expect WS vs polling, basic online path, offline store, and a simple group fan-out story.
- **Experienced (1–4+ YOE) / mid-senior:** Redis pub/sub vs sticky hash, per-device sync, heartbeat/ACK failure modes, media pipeline, estimation of connections and write QPS; Meta/WhatsApp, Uber, Flipkart, Atlassian, etc.
- **Frequency:** among the top HLD design questions alongside URL shortener, news feed, and rate limiter. Depth stops at tradeoffs — not implementing E2EE or Erlang OTP.
