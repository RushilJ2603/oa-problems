# H10 — API design (REST vs gRPC vs GraphQL, pagination, idempotency, versioning, webhooks)

**Interview relevance:** High — nearly every HLD "design X" round starts with sketching APIs; FAANG and Indian product cos probe protocol choice, pagination, retries/idempotency, and (for payments/integrations) webhooks + versioning.
**Type:** HLD-foundation
**Prereqs:** h01_networking (HTTP semantics, caching); helpful after load balancing / API gateway awareness

## Read / watch (curated, in order)
- [ ] [API Design for System Design Interviews](https://www.hellointerview.com/learn/system-design/core-concepts/api-design) — `Hello Interview` — interview default: REST; when to name GraphQL / gRPC; resource naming, status codes, pagination in the ~5 min API step
- [ ] [system-design-primer — REST](https://github.com/donnemartin/system-design-primer#representational-state-transfer-rest) / [RPC](https://github.com/donnemartin/system-design-primer#remote-procedure-call-rpc) — `primer` — resource-oriented public APIs vs behavior-oriented RPC; when each fits
- [ ] [What’s the Difference Between RPC and REST?](https://aws.amazon.com/compare/the-difference-between-rpc-and-rest/) — `AWS` — side-by-side examples (POST `/addProduct` vs POST `/products`); stateful vs stateless; when RPC still wins
- [ ] [REST API vs. GraphQL](https://bytebytego.com/guides/rest-api-vs-graphql/) — `ByteByteGo` — over/under-fetch, caching ease vs flexible client queries
- [ ] [What is GraphQL?](https://bytebytego.com/guides/what-is-graphql/) — `ByteByteGo` — single endpoint, queries/mutations/subscriptions; schema + aggregation role
- [ ] [What Is GraphQL? REST vs. GraphQL](https://www.youtube.com/watch?v=yWzKJPw_VzM) — `ByteByteGo` — visual REST vs GraphQL request shapes; caching and abuse caveats
- [ ] [What is gRPC?](https://bytebytego.com/guides/what-is-grpc/) — `ByteByteGo` — protobuf + HTTP/2, codegen, streaming; internal microservice fit
- [ ] [Introduction to gRPC](https://grpc.io/docs/what-is-grpc/introduction/) — `gRPC docs` — service definition, stubs, proto3; mental model for interviews
- [ ] [EP208 — REST vs gRPC](https://blog.bytebytego.com/p/ep208-load-balancer-vs-api-gateway) — `ByteByteGo` — JSON vs protobuf, resource vs method, streaming, browser/CDN caching tradeoffs
- [ ] [EP215 — REST vs GraphQL vs gRPC](https://blog.bytebytego.com/p/ep215-the-anatomy-of-an-ai-agent) — `ByteByteGo` — one-page rule of thumb: public REST, flexible GraphQL, internal gRPC
- [ ] [How do we Perform Pagination in API Design?](https://bytebytego.com/guides/how-do-we-perform-pagination-in-api-design/) — `ByteByteGo` — offset / page / cursor / keyset / time / hybrid — pick by scale + UI needs
- [ ] [Pagination (GraphQL)](https://graphql.org/learn/pagination/) — `GraphQL.org` — why cursor + opaque tokens; edges/nodes/`pageInfo` connection model
- [ ] [Using pagination in the REST API (GitHub)](https://docs.github.com/en/rest/using-the-rest-api/using-pagination-in-the-rest-api) — `GitHub docs` — real `Link` headers, `page` / `before`/`after`, `per_page` in production
- [ ] [Idempotent requests (Stripe)](https://docs.stripe.com/api/idempotent_requests) — `Stripe` — `Idempotency-Key` for safe POST retries; store first status+body; UUID keys
- [ ] [APIs as infrastructure: future-proofing Stripe with versioning](https://stripe.com/blog/api-versioning) — `Stripe` — date-pinned versions, additive-safe changes, version-change transforms (interview gold)
- [ ] [API versioning](https://docs.stripe.com/api/versioning) / [API upgrades](https://docs.stripe.com/upgrades) — `Stripe` — `Stripe-Version` header; what counts as backward-compatible
- [ ] [Receive Stripe events (webhooks)](https://docs.stripe.com/webhooks) — `Stripe` — push vs poll; signature verification; retries; async handler pattern
- [ ] [About webhooks](https://docs.github.com/en/webhooks/about-webhooks) + [Validating webhook deliveries](https://docs.github.com/en/webhooks/using-webhooks/validating-webhook-deliveries) + [Best practices](https://docs.github.com/en/webhooks/using-webhooks/best-practices-for-using-webhooks) — `GitHub docs` — HMAC secrets, fast 2xx + queue, delivery IDs / replay
- [ ] [DDIA Ch.4 — Encoding and Evolution (REST vs RPC)](https://dataintensive.net/) — `DDIA ch.4` — network ≠ local call; schema evolution; versioning across clients ([free notes](https://timilearning.com/posts/ddia/part-one/chapter-4/))
- [ ] [Learn GraphQL](https://graphql.org/learn/) — `GraphQL.org` — schema, queries, mutations; skim security / N+1 / schema evolution lessons
- [ ] [System Design playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — listen for how APIs are sketched early in each design; contracts before boxes
- [ ] [InterviewReady system-design-resources](https://github.com/InterviewReady/system-design-resources) — `Gaurav Sen / InterviewReady` — curated link dump; cross-check whitepapers after core concepts

## Core concepts to master
- **REST:** resources as nouns (`/users/{id}/orders`), HTTP verbs for CRUD, stateless requests, status codes, cacheable GETs. Default for **public / browser / mobile** APIs in interviews.
- **RPC / gRPC:** action-oriented methods (`GetUser`, `ChargeCard`); gRPC = protobuf + HTTP/2 + codegen + unary/streaming. Default for **internal service-to-service** when latency, typing, and streaming matter; browsers need gRPC-Web / a gateway.
- **GraphQL:** client declares the response shape on one endpoint; kills over/under-fetch for heterogeneous clients. Cost shifts to server: resolvers, **N+1**, query cost limits, harder HTTP caching / rate limits.
- **Rule of thumb:** REST at the edge, gRPC inside the datacenter, GraphQL when interviewers emphasize flexible multi-client fetching (mobile + dashboard) — justify, don’t cargo-cult.
- **Pagination — offset/page:** simple, supports “jump to page N”; deep `OFFSET` gets slow; concurrent inserts → duplicates/skips. Fine for small admin lists.
- **Pagination — cursor/keyset:** opaque cursor encodes last sort key(s); `WHERE (ts, id) < (...) ORDER BY ... LIMIT n` seeks via index; stable for feeds/infinite scroll; no random page jumps. Cap `limit`; prefer `has_next` over expensive `COUNT(*)`.
- **Idempotency:** GET/PUT/DELETE are naturally retry-safe; **POST create/charge** needs an **idempotency key** (client UUID) so retries after timeouts don’t double-charge. Server stores first response keyed by key (+ request fingerprint); same key + different body → conflict.
- **Versioning:** prefer additive changes (new optional fields/endpoints). Strategies: URL `/v1`, header (`Accept` / `Stripe-Version`), or date-pinned account versions (Stripe). Breaking change → new version + deprecation window; don’t force big-bang `/v2` rewrites lightly.
- **Webhooks:** server **pushes** events to subscriber URLs (vs client polling). Must: **HMAC signature** verify, HTTPS, fast **2xx** then async process, **retries + backoff**, dedupe on delivery/event id, ignore unknown event types gracefully.
- **Contract hygiene:** consistent error envelope, auth (API key / OAuth / JWT), rate limits at gateway, OpenAPI/proto as source of truth; DDIA: remote calls fail partially — design for timeout + retry + idempotence.

## Practice — how it's asked & how to attack it
Self-test drills (≤2 min out loud each):

1. **Protocol pick:** Mobile feed + admin dashboard + internal OrderService. Assign REST / GraphQL / gRPC to each hop and name one downside of picking wrong.
2. **REST sketch:** Design Ticketmaster-lite booking APIs (search events, hold seat, confirm payment). Nouns, methods, status codes (`201`, `409` hold conflict, `429`).
3. **Pagination drill:** News feed vs admin “page 47 of users.” Choose cursor vs offset; explain duplicate risk and DB query shape for cursor.
4. **Idempotency drill:** Client POSTs `/payments` , times out, retries. Walk Idempotency-Key store lookup → first success replayed → same key different amount → `409`.
5. **Versioning drill:** You rename `verified: bool` → `status: enum`. What breaks? How would Stripe-style version transforms or a `/v2` path handle old clients?
6. **Webhook drill:** Stripe `payment_intent.succeeded` hits your endpoint. Sequence: verify signature → return 200 → enqueue → process once (event id dedupe) → what if handler fails after 200?

## Common follow-ups / gotchas
- “Why not GraphQL everywhere?” — caching, authz per field, abusive nested queries, operational complexity; REST often enough.
- “Is gRPC always faster?” — protobuf/HTTP/2 help, but most designs aren’t serialization-bound; public API ergonomics + CDN caching often favor REST/JSON.
- Offset pagination on a hot write-heavy feed — interviewer expects cursor + “duplicates/skips under concurrent writes.”
- Retrying non-idempotent POSTs without keys — classic double-charge / double-booking failure mode.
- Webhooks without signature checks or sync heavy work in the request path — spoofing + timeout retries storm.
- Breaking mobile clients with silent field removals — version or additive-only evolution; sunset old versions deliberately.

## Where it appears
- **Campus / new-grad HLD:** almost always the “define APIs” step after requirements; REST + pagination is table stakes; GraphQL/gRPC as named alternatives separates strong candidates.
- **Experienced / mid-level (1–4 YOE):** idempotency (payments, booking), cursor pagination at scale, webhook reliability, and API versioning strategy are common deep dives at Stripe-like, marketplace, and platform companies (Amazon, Uber, Atlassian, Flipkart, etc.).
- **Frequency:** universal building block every design round; dedicated “design Stripe API / webhook system” prompts are less common but the patterns show up inside payments, notifications, and marketplace designs.
