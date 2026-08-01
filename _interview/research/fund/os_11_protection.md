# Protection and security

**Protection** controls the access of *processes and users* to the resources of a computer system —
an internal mechanism. **Security** defends the system against *external and internal threats* —
attackers, malware, and misuse. Protection provides the mechanisms; security sets the policy and
guards the boundary.

## Goals and principles

The goal of protection is to ensure that each object (memory, files, devices, CPU) is accessed
**correctly, and only by processes that are allowed to** — enforcing a well-defined set of
operations per object.

> **Key point — principle of least privilege.** Every program and user should be given **just the
> privileges needed** to do its job, and no more. This limits the damage when a component has a bug
> or is compromised, and is the guiding rule behind protection design.

## Domains and the access matrix

A **protection domain** is a set of **access rights**, each an `<object, {allowed operations}>`
pair; a process runs within a domain and may only perform the operations its domain grants.

The **access matrix** formalizes this: **rows are domains**, **columns are objects**, and entry
$(i, j)$ is the set of operations a process in domain $i$ may invoke on object $j$. It is a clean
model of who-can-do-what; real systems implement it compactly as **access-control lists** (by
column — per object, who may access it) or **capabilities** (by row — per domain, what it may
touch).

## Security violations

Attacks are categorized by what they compromise — the classic **CIA** triad and two more:

- **Breach of confidentiality** — unauthorized *reading* of data.
- **Breach of integrity** — unauthorized *modification* of data.
- **Breach of availability** — unauthorized *destruction* of data.
- **Theft of service** — unauthorized *use* of resources.
- **Denial of service (DoS)** — preventing legitimate *use* of the system.

Common **methods** of attack: **masquerading** (pretending to be another identity to gain
privileges), **replay** (re-sending captured messages, possibly modified), **man-in-the-middle**
(sitting in the data flow, impersonating each end to the other), and **session hijacking**
(intercepting an already-authenticated session).

## Threats

**Program threats** — malicious code:

- **Trojan horse** — a program that looks legitimate but hides a destructive payload; it does *not*
  self-replicate.
- **Virus** — a code fragment embedded in a legitimate program; it is **self-replicating** and
  spreads when the host program runs (often via email or shared files).
- **Worm** — a **self-replicating** program that spreads across systems **on its own**, without a
  host program or user action, consuming resources as it multiplies.
- **Spyware** — covertly collects information about the user; **trap door / backdoor** — a hidden
  entry point that bypasses normal authentication.

> **Trap.** *Malware* is the umbrella term. The distinctions interviewers probe: a **virus** needs a
> host and an execution to spread; a **worm** needs neither; a **trojan** neither self-replicates
> nor needs a host — it relies on the user running it willingly.

**System and network threats** — **port scanning** (probing for open services to exploit), **denial
of service** and its distributed form **DDoS** (flooding a target from many sources), and
connection-flood tricks such as the **SYN** attack against the TCP handshake.

## Defenses

- **Cryptography** — protect confidentiality and authenticity of messages using keys, so that only
  the intended recipient can read them and the sender can be verified.
- **Firewalls** — place a barrier between trusted and untrusted networks, limiting and inspecting
  traffic across the boundary (packet-filter, application-proxy, and system-call firewalls).
- **Defense in depth** — security must be enforced at **four levels** to be effective: **physical**
  (data centers, terminals), **human** (avoiding social engineering and phishing), **operating
  system** (protection mechanisms, patching), and **network** (guarding communications). Security is
  only as strong as the weakest link.

---
