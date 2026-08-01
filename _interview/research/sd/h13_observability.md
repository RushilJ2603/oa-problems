# H13 — Observability (logging, metrics, distributed tracing, alerting, SLO/SLA)

**Interview relevance:** High — almost every HLD ends with "how do you know it's healthy / on fire?"; interviewers probe golden signals, p99 vs avg, structured logs + trace IDs, and SLI/SLO/SLA vs error budget. Full "design Datadog/Prometheus" is common in mid/senior loops.
**Type:** HLD-foundation
**Prereqs:** h01_networking, h02_load_balancing; helpful: h08_message_queues (async span propagation), h06_consistency_cap (eventual metrics vs alert freshness)

## Read / watch (curated, in order)
- [ ] [Logging, Tracing, and Metrics](https://bytebytego.com/guides/logging-tracing-metrics/) — `ByteByteGo` — three pillars in one diagram: ELK for logs, OpenTelemetry path for traces, Prometheus→Grafana/Alertmanager for metrics
- [ ] [Observability primer](https://opentelemetry.io/docs/concepts/observability-primer/) — `OpenTelemetry` — observability vs monitoring; logs / spans / traces; SLI/SLO vocabulary tied to user-visible reliability
- [ ] [What is OpenTelemetry?](https://opentelemetry.io/docs/what-is-opentelemetry/) — `OpenTelemetry` — vendor-neutral instrumentation (not a backend); pair with [Collector](https://opentelemetry.io/docs/collector/) (receive → process → export)
- [ ] [Monitoring Distributed Systems — Four Golden Signals](https://sre.google/sre-book/monitoring-distributed-systems/) — `Google SRE book` — **latency, traffic, errors, saturation**; white-box vs black-box; pages vs tickets vs logs
- [ ] [EP67: Top 9 Microservice Best Practices](https://blog.bytebytego.com/p/ep67-top-9-microservice-best-practices) — `ByteByteGo` — skim Shopify section: golden signals + **structured logging**; full write-up: [Building resilient payment systems](https://shopify.engineering/building-resilient-payment-systems)
- [ ] [SLA vs SLO vs SLI (in EP212)](https://blog.bytebytego.com/p/ep212-data-warehouse-vs-data-lake) — `ByteByteGo` — scroll to **SLA vs SLO vs SLI**: indicator → internal target → contractual promise (SLO tighter than SLA)
- [ ] [Service Level Objectives](https://sre.google/sre-book/service-level-objectives/) — `Google SRE book` — SLI / SLO / SLA definitions; why 100% is the wrong target; error budget as the release throttle
- [ ] [Implementing SLOs](https://sre.google/workbook/implementing-slos/) — `Google SRE workbook` — pick user-centric SLIs, set targets, compute budget (e.g. 99.9% → 0.1% bad events)
- [ ] [Alerting on SLOs](https://sre.google/workbook/alerting-on-slos/) — `Google SRE workbook` — page on **error-budget burn rate**, not raw CPU; multi-window multi-burn-rate alerts
- [ ] [Example Error Budget Policy](https://sre.google/workbook/error-budget-policy/) — `Google SRE workbook` — what happens when budget is spent (freeze features, reliability work)
- [ ] [Prometheus overview](https://prometheus.io/docs/introduction/overview/) — `Prometheus` — pull model, labels, PromQL, Alertmanager; when it fits / when not (not for exact billing)
- [ ] [Prometheus data model](https://prometheus.io/docs/concepts/data_model/) — `Prometheus` — metric name + labels = time series; cardinality warning implicit in label design
- [ ] [Alerting best practices](https://prometheus.io/docs/practices/alerting/) + [Alertmanager](https://prometheus.io/docs/alerting/latest/alertmanager/) — `Prometheus` — symptom-based alerts, grouping/inhibition/silences so pages are actionable
- [ ] [The USE Method](https://www.brendangregg.com/usemethod.html) — `Brendan Gregg` — for every **resource**: Utilization, Saturation, Errors (host/infra checklist)
- [ ] [The RED Method](https://thenewstack.io/monitoring-microservices-red-method/) — `Tom Wilkie / The New Stack` — for every **service**: Rate, Errors, Duration (request-path checklist; pairs with golden signals)
- [ ] [Design a Metrics Monitoring Platform](https://www.hellointerview.com/learn/system-design/problem-breakdowns/metrics-monitoring) — `Hello Interview` — Datadog-style interview: ingest → TSDB → dashboards → alerts; cardinality & scale traps
- [ ] [Scaling AWS — monitoring section](https://github.com/donnemartin/system-design-primer/tree/master/solutions/system_design/scaling_aws) — `primer` — host vs aggregate vs logs vs external probes; CloudWatch / PagerDuty / Sentry mental model as you grow
- [ ] [Evolving Distributed Tracing at Uber (Jaeger)](https://www.uber.com/us/en/blog/distributed-tracing/) — `Uber Eng` — why metrics+logs aren't enough across microservices; Jaeger origin story
- [ ] [Jaeger architecture](https://www.jaegertracing.io/docs/latest/architecture/) — `Jaeger` — client → agent/collector → storage → UI; modern default instrumentation is often OTel → Jaeger/Tempo/etc.
- [ ] [Dapper (Google tracing paper)](https://research.google.com/pubs/pub36356.html) — `Google Research` — classic sampling + library-level RPC instrumentation; PDF: [36356.pdf](https://static.googleusercontent.com/media/research.google.com/en//pubs/archive/36356.pdf)
- [ ] [OpenTelemetry traces](https://opentelemetry.io/docs/concepts/signals/traces/) — `OpenTelemetry` — trace / span / context propagation — the words you use on the whiteboard
- [ ] [From 0 to Millions — Monitoring and Observability](https://blog.bytebytego.com/p/from-0-to-millions-a-guide-to-scaling-47a) — `ByteByteGo` — which app + DB metrics to watch before traffic melts you (p95 latency, error rate, connections, slow queries)
- [ ] [Observability for Beginners: Logs, Metrics, Traces](https://blog.bytebytego.com/p/observability-for-beginners-logs) — `ByteByteGo` — deeper narrative on events → logs/metrics/traces, cardinality, sampling, correlation (paid beyond intro; free guide above covers the interview core)
- [ ] [The Tech Stack Powering Wise — Unified Observability](https://blog.bytebytego.com/p/the-tech-stack-powering-wise) — `ByteByteGo` — optional case study: LGTM (Loki/Grafana/Tempo/Mimir) and why **correlation** beats three disconnected tools
- [ ] *Designing Data-Intensive Applications* ch.1 (Reliability / Operability / percentiles) — `DDIA ch.1` — telemetry for human error; prefer **p50/p95/p99** over averages — [book site](https://dataintensive.net/); free notes: [ch.1](https://timilearning.com/posts/ddia/part-one/chapter-1/)
- [ ] [InterviewReady — Distributed Logging](https://github.com/InterviewReady/system-design-resources#distributed-logging) — `InterviewReady` (Gaurav Sen) — curated eng posts (Uber tracing, logging agents); pair with [Alerts and Anomaly Detection](https://github.com/InterviewReady/system-design-resources#alerts-and-anomaly-detection)

## Core concepts to master
- **Observability vs monitoring:** monitoring asks known questions ("is error rate > 1%?"). Observability lets you ask **new** ones from telemetry ("why is *this* checkout slow for *this* user?") via correlated logs, metrics, and traces.
- **Three pillars:** **Logs** = discrete events (high volume, richest context). **Metrics** = aggregatable numbers over time (cheap to store/alert). **Traces** = one request's path across services as a tree of **spans**. Interview default stack story: structured logs + Prometheus-style metrics + OTel/Jaeger traces, linked by `trace_id`.
- **Four golden signals (user-facing):** **latency** (separate success vs failure), **traffic** (QPS / bytes), **errors** (explicit + wrong answers), **saturation** (how full — queues, CPU, memory, connections).
- **RED vs USE:** **RED** (Rate, Errors, Duration) for services/APIs; **USE** (Utilization, Saturation, Errors) for resources (CPU, disk, NIC). Use both layers in an incident.
- **Percentiles > averages:** avg latency hides the tail. Track **p50 / p95 / p99**; "p99 > SLO" is a common alert and interview answer.
- **SLI / SLO / SLA:** **SLI** = measured indicator (e.g. successful requests / valid requests). **SLO** = internal target over a window (e.g. 99.9% over 28 days). **SLA** = customer contract, usually **looser** than SLO, with credits on breach. Never set SLA = SLO with no buffer.
- **Error budget:** `1 − SLO`. 99.9% → ~43 min downtime / month (or equivalent bad events). Budget buys **change velocity**; exhausted budget → reliability work / launch freeze (SRE policy).
- **Alerting that doesn't page you to death:** alert on **user symptoms** and **budget burn**, not every CPU blip. Pages = human action *now*; everything else is ticket/dashboard. Use grouping, inhibition, runbooks.
- **Structured logging:** JSON (or equivalent) with level, service, timestamp, `request_id`/`trace_id`, user/order ids — searchable in ELK/Loki; printf spaghetti doesn't scale.
- **Distributed tracing:** propagate context (W3C / OTel) across HTTP/RPC/queue boundaries; waterfall shows which downstream ate the latency. **Sample** aggressively (head or tail-based) — 100% traces at scale is usually unaffordable.
- **Cardinality:** each unique label combo is a time series. `user_id` / unbounded URL paths as labels → **metric explosion** / OOM Prometheus. High-cardinality identity belongs in logs/traces, not metric labels.
- **Black-box vs white-box:** black-box = probe like a user (uptime checks); white-box = internals (queue depth, saturation). You need both — white-box explains *why*, black-box catches "DNS is fine but cert expired."

## Practice — how it's asked & how to attack it
Self-test drills (say answers out loud in ≤2 min each):

1. **Close the design:** You just designed Instagram/URL shortener/chat. Name the golden signals + 2 SLIs (availability, latency) + one SLO sentence + where logs/metrics/traces plug into the diagram.
2. **SLI/SLO/SLA drill:** Login API. Pick SLI, give a 99.9% SLO over 30 days, a looser SLA, and compute the monthly error budget in failed requests if QPS ≈ 100.
3. **Incident path:** Alert: p99 checkout latency spiked. Walk metrics → traces (find slow span) → logs (`trace_id`) → fix. What do you *not* page on?
4. **Cardinality trap:** Someone adds `user_id` as a Prometheus label on `http_requests_total`. What breaks, and where should user identity live instead?
5. **Kafka / async drill:** Order service publishes `OrderPlaced`; payment consumer is slow. How does a trace continue across the queue? What metric shows consumer lag vs what a trace shows?
6. **Design Datadog (senior):** Sketch ingest agents → buffer (Kafka) → TSDB → query/alert path. Call out write amplification, downsampling/retention tiers, and alert freshness vs dashboard eventual consistency.

## Common follow-ups / gotchas
- Quoting "five nines" without knowing **~5 min downtime/year** — or confusing **durability** (S3 11 nines) with **availability** SLO.
- Alerting on CPU alone while user-facing error rate is fine (or the reverse: ignoring saturation until OOM).
- Logging PII / secrets; or unstructured logs with no `trace_id` so you can't jump pillars.
- Claiming "exactly once metrics" or using Prometheus for **billing** — Prometheus optimizes for reliable *enough* ops data, not perfect accounting.
- 100% trace sampling "for correctness" at high QPS — cost and collector meltdown; sample + always-keep errors/slow requests.
- Setting SLA == SLO with zero buffer — first SLO miss is already a contract breach.
- Drawing three tools with no correlation story — interviewer wants shared IDs / one investigation path.

## Where it appears
- **Campus / intern / new-grad HLD:** light but expected — mention monitoring, key metrics (latency/errors/QPS), maybe centralized logs. SLO vocabulary is a plus; deep burn-rate alerting is rare.
- **Experienced / mid-level (1–4 YOE):** SLO/error budget, p99, cardinality, tracing across microservices, "design metrics platform" — common at Meta, Google, Uber, Amazon, Stripe, Atlassian, Flipkart, etc.
- **Frequency:** near-universal as a **closing** reliability discussion on any design; standalone "design Datadog / CloudWatch / Prometheus" is a frequent senior/infra question. Depth = tradeoffs and incident workflow — not building a TSDB from scratch.
