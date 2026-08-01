# H07 — Consensus & coordination (leader election, Raft/Paxos idea, ZooKeeper, quorums)

**Interview relevance:** Medium–High — rarely “implement Raft”; often a follow-up when you draw a primary, Kafka controller, etcd/ZooKeeper box, or say “strong consistency / no split-brain” (experienced more than campus; FAANG + infra-heavy product cos).
**Type:** HLD-foundation
**Prereqs:** h06_consistency_cap, h05_db_scaling; h01_networking helps for partitions / timeouts

## Read / watch (curated, in order)
- [ ] [system-design-primer — CAP theorem](https://github.com/donnemartin/system-design-primer#cap-theorem) — `primer` — refresh CP under partition (consensus systems refuse minority writes); pair [Consistency patterns](https://github.com/donnemartin/system-design-primer#consistency-patterns) (strong ≈ what quorum commit buys you)
- [ ] [Data Consistency and Tradeoffs in Distributed Systems](https://www.youtube.com/watch?v=m4q7VkgDWrM) — `Gaurav Sen` — why copies diverge, leader assignment, cost of 2PC vs eventual — mental bridge into “agree on one value”
- [ ] [Algorithms You Should Know Before System Design Interviews](https://www.youtube.com/watch?v=xbgzl2maQUU) — `ByteByteGo` — short Raft/Paxos section: elect a leader, replicate state, survive minority failures (etcd/Kafka-class uses)
- [ ] [EP197: 12 Architectural Concepts… → 5 Leader Election Algorithms](https://blog.bytebytego.com/p/ep197-12-architectural-concepts-developers) — `ByteByteGo` — free refresher: Bully / Ring / Paxos / Raft / ZK ephemeral-sequential; deeper paid twin: [Top Leader Election Algorithms…](https://blog.bytebytego.com/p/top-leader-election-algorithms-in) (skip if paywalled)
- [ ] [The Raft Consensus Algorithm](https://raft.github.io/) — `Raft site` — official explainer + viz; then walk [The Secret Lives of Data (Raft)](https://thesecretlivesofdata.com/raft/) once end-to-end (election → append → commit)
- [ ] [Distributed Systems 6.2: Raft](https://www.youtube.com/watch?v=uXEYuDwm7e4) — `DDIA` author (Martin Kleppmann) — interview-depth walkthrough of follower/candidate/leader, terms, majority votes (~38 min). Optional primary-source talk: [Designing for Understandability: The Raft Consensus Algorithm](https://www.youtube.com/watch?v=vYp4LYbnnW8) (Diego Ongaro)
- [ ] [In Search of an Understandable Consensus Algorithm (Raft PDF)](https://raft.github.io/raft.pdf) — `Raft paper` — **skim** §§1–5 only (election, log replication, safety); do **not** memorize membership-change proofs for interviews
- [ ] [Paxos Made Simple (PDF)](https://lamport.azurewebsites.net/pubs/paxos-simple.pdf) — `Lamport` — prepare/accept idea + majority quorum; enough to say “Paxos = hard to implement; Raft = same job, clearer decomposition”. Mirror listing: [Microsoft Research](https://www.microsoft.com/en-us/research/publication/paxos-made-simple/)
- [ ] [ZooKeeper Deep Dive](https://www.hellointerview.com/learn/system-design/deep-dives/zookeeper) — `Hello Interview` — when to name ZK: config, discovery, locks, leader election, ZAB (may be premium — use official docs below if blocked)
- [ ] [ZooKeeper Overview](https://zookeeper.apache.org/doc/current/zookeeperOver.html) — `ZooKeeper docs` — ensemble, znodes, watches, sessions; then [Recipes — Leader Election](https://zookeeper.apache.org/doc/current/recipes.html) (ephemeral + sequential; watch predecessor to avoid herd)
- [ ] [ZooKeeper Internals](https://zookeeper.apache.org/doc/current/zookeeperInternals.html) — `ZooKeeper docs` — skim: FastLeaderElection, quorum of followers, zxid ordering (ZAB mental model — not a Raft clone)
- [ ] [etcd API guarantees](https://etcd.io/docs/v3.5/learning/api_guarantees/) — `etcd docs` — linearizable writes via Raft quorum; why K8s control plane sits on etcd. Pair [Why etcd](https://etcd.io/docs/v3.5/learning/why/) and [Operating etcd for Kubernetes](https://kubernetes.io/docs/tasks/administer-cluster/configure-upgrade-etcd/)
- [ ] [Consul — Consensus Protocol](https://developer.hashicorp.com/consul/docs/concept/consensus) — `HashiCorp` — production Raft knobs in plain English (quorum size, leader, what happens on partition)
- [ ] [How to do distributed locking](https://martin.kleppmann.com/2016/02/08/how-to-do-distributed-locking.html) — `DDIA` author — **fencing tokens**; why “Redis `SETNX` lock” without fencing is unsafe under GC pauses / slow holders
- [ ] *Designing Data-Intensive Applications* ch.9 (Consistency and Consensus) — `DDIA ch.9` — linearizability, total-order broadcast, fault-tolerant consensus, ZK/etcd as coordination services ([book site](https://dataintensive.net/); [free notes 9-1](https://timilearning.com/posts/ddia/part-two/chapter-9-1/) / [9-2](https://timilearning.com/posts/ddia/part-two/chapter-9-2/))
- [ ] [InterviewReady — Distributed consensus](https://github.com/InterviewReady/system-design-resources#distributed-consensus) — `InterviewReady` — short link dump (Paxos explainer + raft.github.io). Optional history: [Chubby (OSDI’06 PDF)](https://static.googleusercontent.com/media/research.google.com/en//archive/chubby-osdi06.pdf) — Google lock service that inspired ZK

## Core concepts to master
- **Consensus (interview definition):** several nodes agree on **one value / one order of values** despite crashes and message loss. Safety: never decide two different values. Liveness: eventually decide if a majority is up (timeouts break FLP in practice).
- **Why you need it:** leader election, replicated config, unique IDs, “who owns this shard,” metadata that must not split-brain. **Not** for bulk user data — put that in your DB/queue; put **coordination** in ZK/etcd/Consul-sized stores.
- **Quorum / majority:** with `N = 2f+1` nodes, need `f+1` votes to elect or commit → tolerate `f` failures. Any two majorities **intersect** → a committed value cannot be lost when leadership changes. Prefer odd sizes (3, 5); even wastes a vote.
- **Leader election:** pick **at most one** active leader for a term/epoch. Goals: safety (no dual writers) + recovery when the leader dies. Naive “highest ID wins” (Bully) is teaching folklore; production uses **quorum voting** (Raft) or **coordination service** recipes (ZK).
- **Raft idea (three parts):** (1) **election** — randomized timeouts → candidate → majority `RequestVote`; (2) **log replication** — leader appends, followers ACK, commit when majority durable; (3) **safety** — only elect leaders whose log is at least as up-to-date; terms act as logical clocks. Powers etcd, Consul, Cockroach/TiKV-style ranges.
- **Paxos idea (one line):** proposers/acceptors; a value is chosen only after a **majority** accepts; Multi-Paxos ≈ stable leader for a stream of decisions. Same power as Raft; harder to implement correctly — say that and move on unless asked.
- **ZooKeeper:** small in-memory hierarchical **znodes**, **watches**, sessions. Ensemble runs **ZAB** (atomic broadcast), not Raft. Client recipes: ephemeral sequential nodes for **leader election** / locks; delete on session loss → failover. Use for coordination, **not** as a general DB.
- **etcd vs ZooKeeper:** both CP-style coordination KVs. etcd ≈ Raft + gRPC/JSON, K8s default; ZK ≈ ZAB + znodes/watches, classic Hadoop/Kafka-ZK era (Kafka moving to KRaft). Interview answer: “small strongly consistent store for metadata/locks/election.”
- **Split-brain:** two nodes both think they are leader → divergent writes. Prevention = **quorum** (minority cannot elect/commit) + **leases/epochs** + **fencing tokens** so a stale leader’s writes are rejected downstream.
- **Tradeoff:** consensus is **CP under partition** — minority side goes unavailable for writes. Single-leader Raft also concentrates write throughput on one node; scale by sharding ranges, not by “add more Raft peers for QPS.”

## Practice — how it's asked & how to attack it
Self-test drills (≤2 min aloud each):

1. **Quorum math:** Cluster of 5. How many failures can you survive? Can a 2-node partition accept writes? Why prefer 5 over 4?
2. **Raft story:** Leader dies mid-heartbeat. Narrate follower timeout → candidate → term bump → votes → new leader → uncommitted vs committed entries. What property stops the new leader from wiping committed data?
3. **Paxos one-liner vs Raft:** Interviewer: “Isn’t Paxos enough?” Answer with prepare/accept + majority, then why industry mostly ships Raft (understandability / explicit leader / log).
4. **ZK leader election recipe:** Sketch ephemeral sequential children under `/election`, lowest sequence = leader, watch next-lower node (no herd). What happens when the leader process GC-pauses but session is still alive?
5. **Where to put consensus:** Design “multi-writer config service” vs “user photo store.” Which uses etcd/ZK? Which uses object store + DB? What breaks if you store photo blobs in ZK?
6. **Fencing drill:** Old primary paused 30s, new primary elected, old wakes and writes to shared storage. How does a monotonically increasing fencing token (ZK zxid / lease generation) stop corruption?

## Common follow-ups / gotchas
- Drawing “ZooKeeper” or “Raft” without saying **majority quorum** and **what happens on partition** — interviewers expect CP behavior (minority refuses writes).
- Treating Raft/Paxos as something you **implement in the interview** — discuss at box+tradeoff level; leave proofs and joint-consensus membership changes unless senior infra loop.
- Confusing **app-level leader** (your service’s primary) with **consensus cluster** (etcd/ZK ensemble that helps elect it).
- “Redis lock = distributed lock” without **fencing** — Kleppmann’s blog is the classic trap; always mention token/epoch checks on the resource.
- Using ZK/etcd as a **high-throughput data plane** — they are coordination stores (small keys, watch fans, limited write QPS).
- Assuming two leaders are “briefly OK” for money/inventory/metadata — that’s split-brain; say how quorum + fencing prevent it.
- Odd vs even cluster size: even `N` does not improve fault tolerance vs `N-1` and makes majority harder — stick to 3 or 5.

## Where it appears
- **Campus / new-grad HLD:** light touch — “primary + failover,” “need majority,” maybe name ZooKeeper/etcd for Kafka/K8s-flavored designs; deep Raft walkthrough uncommon.
- **Experienced (2+ YOE) / infra-leaning:** leader election, split-brain, quorum sizing, ZK recipes vs etcd/Raft, fencing tokens — Meta, Google, Amazon, Uber, Atlassian, Flipkart infra, etc.
- **Frequency:** medium as a named topic; high as a **follow-up** whenever you claim strong consistency, single-leader replication, or a coordination dependency. Full “design Raft” is rare outside specialized distributed-systems rounds.
