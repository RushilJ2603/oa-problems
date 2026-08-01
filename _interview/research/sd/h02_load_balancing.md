# h02_load_balancing — Load balancing & reverse proxies

**Interview relevance:** High — almost every HLD "design X" round (campus + experienced); FAANG and Indian product cos probe L4/L7, algorithms, and sticky-session tradeoffs when you draw a horizontally scaled app tier.
**Type:** HLD-foundation
**Prereqs:** h01_networking

## Read / watch (curated, in order)
- [ ] [system-design-primer — Load balancer](https://github.com/donnemartin/system-design-primer#load-balancer) — `primer` — L4 vs L7, active-passive / active-active HA, why LB can itself be a SPOF; then [Reverse proxy](https://github.com/donnemartin/system-design-primer#reverse-proxy-web-server) and [LB vs reverse proxy](https://github.com/donnemartin/system-design-primer#load-balancer-vs-reverse-proxy)
- [ ] [What is LOAD BALANCING?](https://www.youtube.com/watch?v=K0Ta65OqQkY) — `Gaurav Sen` — request allocation, sticky sessions, and why naive hashing breaks when nodes join/leave (setup for consistent hashing)
- [ ] [What is a LOAD BALANCER really about?](https://www.youtube.com/watch?v=LQuuoHTyYz8) — `ByteByteGo` — L4 vs L7, SSL termination, GSLB mental model in ~7 min
- [ ] [Top 6 Load Balancing Algorithms Every Developer Should Know](https://www.youtube.com/watch?v=dBmxNsS3BGE) — `ByteByteGo` — static vs dynamic algorithms (round robin, weighted, hash, least connections, least response time); pair with [EP47: Common Load-balancing Algorithms](https://blog.bytebytego.com/p/ep47-common-load-balancing-algorithms)
- [ ] [Networking Essentials — Load Balancing](https://www.hellointerview.com/learn/system-design/core-concepts/networking-essentials) — `Hello Interview` — client-side vs dedicated LB, DNS for multi-LB HA, when least-connections beats round robin (WebSockets / long-lived)
- [ ] [Using nginx as HTTP load balancer](https://nginx.org/en/docs/http/load_balancing.html) — `nginx.org` — round-robin / least_conn / ip_hash in practice; session persistence via ip-hash
- [ ] [How Elastic Load Balancing works](https://docs.aws.amazon.com/elasticloadbalancing/latest/userguide/how-elastic-load-balancing-works.html) — `AWS docs` — ALB (L7) vs NLB (L4) routing; health-check-driven failover. Skim [ALB intro](https://docs.aws.amazon.com/elasticloadbalancing/latest/application/introduction.html), [NLB intro](https://docs.aws.amazon.com/elasticloadbalancing/latest/network/introduction.html), [ALB health checks](https://docs.aws.amazon.com/elasticloadbalancing/latest/application/target-group-health-checks.html), [sticky sessions](https://docs.aws.amazon.com/elasticloadbalancing/latest/application/sticky-sessions.html)
- [ ] [Load Balancing, Affinity, Persistence & Sticky Sessions](https://www.haproxy.com/blog/load-balancing-affinity-persistence-sticky-sessions-what-you-need-to-know) — `HAProxy` — affinity (IP) vs persistence (cookie) vs sticky; why shared session store beats stickiness for scale
- [ ] [What is CONSISTENT HASHING and Where is it used?](https://www.youtube.com/watch?v=zaRkONvyGr8) — `Gaurav Sen` — hash-ring for stable request→server mapping when capacity changes (caches, sticky-ish routing)
- [ ] *Designing Data-Intensive Applications* ch.6 (Partitioning) — request routing / partition-aware load balancer — `DDIA ch.6` — book site: [dataintensive.net](https://dataintensive.net/)

## Core concepts to master
- **Role:** LB is the stable front door — distributes traffic across healthy backends for scalability, availability, and even load; a lone LB is a SPOF → run active-active or active-passive + DNS.
- **Reverse proxy vs LB:** reverse proxy sits in front of origin(s) for TLS termination, caching, compression, auth; LB's job is distributing across *many* identical backends. NGINX/HAProxy often do both.
- **L4 (transport):** route on IP/port (TCP/UDP); fast, protocol-agnostic, connection-oriented stickiness for free; no URL/header routing. Typical: AWS NLB, IPVS.
- **L7 (application):** terminate TLS, inspect HTTP (host, path, headers, cookies); content-based routing, sticky cookies, WAF. Slower/CPU-heavier. Typical: AWS ALB, NGINX, HAProxy HTTP mode.
- **Algorithms — static:** round robin (homogeneous, short requests); weighted RR (heterogeneous capacity); IP/URL hash (deterministic affinity).
- **Algorithms — dynamic:** least connections (long-lived / uneven request cost); least response time (latency-aware). Prefer dynamic when backends aren't identical or work is bursty.
- **Health checks:** active probes (TCP connect or `GET /health`) + passive (errors/timeouts in real traffic). Thresholds matter: fail N times → drain; recover after M successes. Shallow "port open" ≠ "app can serve".
- **Sticky sessions (affinity/persistence):** pin a client to one server (cookie or source IP). Use for in-memory sessions / WebSockets — but it hurts even load, complicates deploys, and fails over badly. Prefer external session store (Redis/DB) and keep app servers **stateless**.
- **TLS termination:** decrypt at LB so backends speak HTTP and LB can do L7 routing; re-encrypt to backends if you need encryption in the data center (trade CPU vs security).
- **Connection draining / slow start:** remove a node only after in-flight requests finish; ramp recovered nodes slowly so they aren't slammed.
- **Client-side LB:** service discovery + client picks backend (gRPC/Envoy/xDS style) — removes a hop, but every client must know the pool and health policy.
- **GSLB / geo:** DNS or anycast to send users to the nearest healthy region; complementary to in-region L4/L7, not a replacement.

## Practice — how it's asked & how to attack it
Self-test drills (say answers out loud in ≤2 min each):

1. **L4 vs L7 pick:** Interviewer: "We're adding path-based routing (`/api` vs `/static`) and sticky login cookies." Which layer? What do you lose vs an L4 NLB? When would you still put L4 in front of L7?
2. **Algorithm choice:** Homogeneous stateless HTTP APIs vs mixed WebSocket + short REST vs heterogeneous VM sizes — pick RR / least-conn / weighted / hash and justify failure modes (slow backend under RR; hash remapping on scale-out).
3. **Health-check design:** Sketch `/health` for a service that depends on Postgres + Redis. Active vs passive checks; what happens during a brief GC pause; how connection draining interacts with a rolling deploy.
4. **Sticky sessions debate:** Product wants in-memory carts. Draw sticky-cookie LB vs shared Redis sessions. Probe: one AZ dies, user IP changes (mobile), uneven VIP traffic, horizontal scale of a hot user.
5. **LB itself fails:** You drew one box labeled "Load Balancer". How do you remove that SPOF? (active-active pair, DNS multi-A, cloud managed LB, health of the LB nodes.)
6. **Consistent hashing follow-up:** After Gaurav's video — when is consistent hashing the right *LB* algorithm vs plain round robin? How does it relate to cache hit rate when adding a node?

## Common follow-ups / gotchas
- "Isn't the load balancer a single point of failure?" — yes if singular; mitigate with multiple LBs + DNS, or managed multi-AZ LB.
- Sticky sessions ≠ high availability — if that backend dies, in-memory session is gone unless replicated elsewhere.
- Round robin + long-lived connections → one server can accumulate most open sockets; use least connections.
- Health check that only hits the process (not dependencies) → LB keeps sending traffic to a broken app.
- L7 needed for host/path routing and cookie stickiness; L4 is enough (and preferred) for raw TCP / extreme throughput / passthrough TLS.
- Forgetting connection draining during deploys → dropped in-flight requests and flaky 5xxs.
- Drawing an LB in front of *every* microservice box without saying what it buys — interviewers prefer one edge LB + note that internal services are horizontally scaled (or client-side balanced).

## Where it appears
- **Campus / intern / new-grad HLD:** expected building block in URL shortener, news feed, chat, e-commerce — "add a load balancer" is table stakes; depth on L4/L7 and sticky is what differentiates.
- **Experienced / mid-level (1–4 YOE):** follow-ups on health checks, draining, TLS termination, least-conn vs RR, session store vs stickiness — common at Amazon, Google, Meta, Uber, Atlassian, Flipkart, etc.
- **Frequency:** near-universal in HLD; rarely a standalone "design a load balancer" question outside infra-heavy loops, but the concepts are probed in almost every scale-out design.
