# H01 — Networking (DNS, TCP/IP, HTTP/HTTPS, TLS, WebSockets, long-polling/SSE)

**Interview relevance:** High — assumed in nearly every HLD round; real-time protocol choice is probed in chat, notifications, feeds, and collaborative apps (campus + experienced, FAANG and Indian product cos).
**Type:** HLD-foundation
**Prereqs:** None — start here before caching, load balancing, or design questions

## Read / watch (curated, in order)
- [ ] [What happens when you type a URL into your browser?](https://www.youtube.com/watch?v=AlkDbnbv7dk) — `ByteByteGo` — DNS → TCP → (TLS) → HTTP end-to-end mental model in ~10 min
- [ ] [Domain name system (primer)](https://github.com/donnemartin/system-design-primer#domain-name-system) — `primer` — hierarchy, TTL/caching, record types, managed DNS tradeoffs
- [ ] [How does the Domain Name System (DNS) lookup work?](https://blog.bytebytego.com/p/how-does-the-domain-name-system-dns) — `ByteByteGo` — root → TLD → authoritative walk with diagram
- [ ] [TCP](https://github.com/donnemartin/system-design-primer#transmission-control-protocol-tcp) / [UDP](https://github.com/donnemartin/system-design-primer#user-datagram-protocol-udp) — `primer` — reliability vs latency; when each wins in designs
- [ ] [Networking Essentials](https://www.hellointerview.com/learn/system-design/core-concepts/networking-essentials) — `Hello Interview` — L3/L4/L7 stack for interviews: IP, TCP/UDP/QUIC, HTTP, WebSockets, LB implications
- [ ] [SSL, TLS, HTTPS Explained](https://www.youtube.com/watch?v=j9QmMEWmcfo) — `ByteByteGo` — handshake, certs, asymmetric → symmetric session keys
- [ ] [HTTP overview (MDN)](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Overview) — `MDN` — request/response model, methods, headers; pair with [HTTP/2](https://developer.mozilla.org/en-US/docs/Glossary/HTTP_2) / [HTTP/3](https://developer.mozilla.org/en-US/docs/Glossary/HTTP_3) glossaries
- [ ] [Head-of-line blocking in HTTP/1 and HTTP/2](https://engineering.cred.club/head-of-line-hol-blocking-in-http-1-and-http-2-50b24e9e3372) — `InterviewReady` curated — why multiplexing still hurts on TCP; motivates HTTP/3/QUIC
- [ ] [HTTP/3: the past, present, and future](https://blog.cloudflare.com/http3-the-past-present-and-future/) — `Cloudflare` — QUIC over UDP, 0-RTT, stream-level loss isolation
- [ ] [Short/long polling, SSE, WebSocket](https://bytebytego.com/guides/shortlong-polling-sse-websocket/) — `ByteByteGo` — four real-time patterns and when each fits
- [ ] [Network protocols behind server push](https://blog.bytebytego.com/p/network-protocols-behind-server-push) — `ByteByteGo` — polling → WebSocket → SSE with concrete use cases
- [ ] [Real-time Updates pattern](https://www.hellointerview.com/learn/system-design/patterns/realtime-updates) — `Hello Interview` — protocol choice + scaling push at interview depth
- [ ] [DDIA Ch.4 — Encoding and Evolution (REST vs RPC)](https://dataintensive.net/) — `DDIA ch.4` — network calls ≠ local calls; REST for public APIs vs RPC internally ([free notes](https://timilearning.com/posts/ddia/part-one/chapter-4/))
- [ ] [System Design playlist (Gaurav Sen)](https://www.youtube.com/playlist?list=PLMCXHnjXnTnvo6alSjVkgxV-VH6EPyvoX) — `Gaurav Sen` — foundations + designs; listen for protocol calls in streaming/CDN deep dives
- [ ] [System Design for Beginners (Gaurav Sen / freeCodeCamp)](https://www.youtube.com/watch?v=m8Icp_Cid5o) — `Gaurav Sen` — network-protocol selection inside a full beginner design walkthrough

## Core concepts to master
- **DNS** maps names → IPs via recursive resolvers over a hierarchy (root → TLD → authoritative); TTL caching speeds lookups but delays IP/record changes (propagation).
- **TCP** = connection-oriented, ordered, reliable (3-way handshake, ACKs, retransmission, congestion control); default for HTTP, DBs, most APIs. **UDP** = connectionless, best-effort, low overhead; DNS queries, VoIP, gaming, QUIC under HTTP/3.
- A browser request path: DNS → TCP (and **TLS** if HTTPS) → HTTP request/response; keep-alive / multiplexing amortizes handshake cost.
- **HTTPS = HTTP over TLS**: cert validates identity; asymmetric crypto negotiates a session key, then symmetric encryption for bulk data; TLS adds RTTs (TLS 1.3 ≈ 1-RTT; session resumption / 0-RTT help).
- **HTTP/1.1** needs many connections (HOL blocking); **HTTP/2** multiplexes streams on one TCP connection (still TCP HOL); **HTTP/3/QUIC** runs over UDP so one lost packet doesn’t stall all streams.
- **HTTP** is request/response and client-initiated — the server cannot freely push without a held or upgraded connection.
- **Short polling**: client asks on an interval (simple, wasteful). **Long polling**: server holds the request until data or timeout (fewer empty responses, still HTTP-heavy).
- **SSE**: long-lived HTTP, server → client only; auto-reconnect via `EventSource`; great for feeds, dashboards, notifications.
- **WebSockets**: HTTP upgrade → full-duplex persistent channel; needed for chat, multiplayer, collaborative editing where both sides push often; sticky sessions / connection state complicate L7 LB.
- Default to HTTP(+SSE/long-poll) unless you truly need bidirectional low-latency streams; WebSockets add fan-out, reconnect, and sticky-routing cost.
- **REST vs RPC (DDIA)**: network failure, latency, and partial failure make “remote = local call” a lie; REST/HTTP wins public APIs and tooling; RPC (e.g. gRPC) is common inside the datacenter.

## Practice — how it's asked & how to attack it
1. **Drill — “What happens when you type `https://example.com`?”** Narrate cache checks → recursive DNS → TCP handshake → TLS handshake → HTTP GET → response; name each latency source.
2. **Drill — TCP vs UDP:** For each of {file download, live video, DNS, payment API, heartbeats}, pick transport and justify (loss tolerance vs correctness).
3. **Drill — real-time matrix:** For {stock ticker, WhatsApp-style chat, unread badge, QR login wait}, choose short poll / long poll / SSE / WebSocket and state one scaling downside of your pick.
4. **Drill — HTTPS tradeoffs:** Explain why HTTPS is non-negotiable for auth cookies/PII, what a cert proves, and how TLS handshake cost is mitigated (keep-alive, session tickets, HTTP/2+/connection reuse).
5. **Drill — HTTP versions:** Explain why domain sharding helped HTTP/1.1 but can hurt HTTP/2, and why HTTP/3 exists if HTTP/2 already multiplexes.
6. **Drill — load balancer angle:** Contrast L4 vs L7 for WebSocket vs plain REST; say when you need sticky sessions and why that hurts failure domains.

## Common follow-ups / gotchas
- “Why not always WebSockets?” — state, reconnect storms, proxy/LB sticky affinity, horizontal scaling pain; SSE/long-poll often enough for server→client push.
- “Is HTTP/2 enough?” — app-layer multiplexing still suffers **TCP head-of-line blocking**; HTTP/3/QUIC isolates loss per stream.
- “How do you scale millions of open sockets?” — connection servers, pub/sub fan-out, heartbeats, timeouts, regional gateways; estimate RAM/FD per connection.
- “DNS TTL too high/low?” — high TTL = stale IPs after failover/deploy; low TTL = more resolver load and slightly higher p99 latency.
- “TLS termination where?” — edge/LB vs app; termination at edge offloads CPU but moves trust boundary; mTLS for service-to-service is a separate story.
- “Long polling vs SSE?” — both are HTTP-friendly; SSE is streaming + browser-native reconnect; long polling reopens a full request per event and is the legacy fallback.

## Where it appears
- **Campus / new-grad HLD:** almost always as unspoken background; explicit “type a URL” or TCP vs UDP still shows up at some Indian product cos and mid-tier FAANG-adjacent rounds.
- **Experienced / mid-level HLD:** protocol choice is a standard deep dive in chat, notifications, live feeds, multiplayer, and collaborative docs; HTTP/2 vs HTTP/3 and WebSocket scaling separate strong answers.
- **Frequency:** foundational every design round; real-time protocol tradeoffs appear whenever the prompt mentions “live,” “push,” or “instant.”
