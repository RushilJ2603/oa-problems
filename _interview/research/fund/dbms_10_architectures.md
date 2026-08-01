# 10. SQL vs. NoSQL & NewSQL Architectures

To ace a senior system design interview, you must know when *not* to use a traditional relational database. The choice between relational and non-relational databases fundamentally boils down to how they handle distributed data over a network.

## 10.1 The Scale-Up vs Scale-Out Dilemma

- **SQL (Relational):** Historically scales *vertically* (Scale-Up). When you need more performance, you buy a bigger server with more RAM, CPU, and faster NVMe drives. This is because enforcing strict relational rules (joining data, locking rows, ensuring consistency) across a network of 100 separate servers is incredibly slow due to network latency.
- **NoSQL (Non-Relational):** Designed to scale *horizontally* (Scale-Out). You buy 100 cheap commodity servers and distribute the data across them. To achieve this speed across a network, NoSQL databases (like MongoDB, Cassandra, or DynamoDB) abandon strict relational schemas, lack traditional joins, and often relax data consistency.

## 10.2 The CAP Theorem

When you distribute data across multiple servers (a distributed system), you are bound by a fundamental mathematical constraint.

::: heavy
**Heavy Concept: The CAP Theorem**
**Analogy:** You are managing a bank with two branches (Node A and Node B), connected by a phone line. 

**Concrete Example:** A storm knocks out the phone line. The branches can no longer talk to each other. This is a **Partition (P)**. Now, a customer walks into Branch A to deposit $100. Because you cannot communicate with Branch B to update its ledger, you have a forced choice:

- **Choice 1 (Availability):** You accept the deposit. The system is Available. But now, Branch A says the balance is $100, and Branch B says it's $0. You have lost Consistency. This is an **AP** system.
- **Choice 2 (Consistency):** You refuse the deposit until the phone line is fixed, ensuring both branches always have the exact same balance. You have maintained Consistency, but the customer was rejected. You lost Availability. This is a **CP** system.

**Plain English:** The CAP theorem states you can only guarantee two out of three: **C**onsistency (every read receives the most recent write or an error), **A**vailability (every request receives a non-error response), and **P**artition Tolerance (the system continues to operate despite an arbitrary number of messages being dropped by the network). 

**Technical:** Because network partitions (P) are unavoidable in distributed systems (switches fail, cables are cut), database engineers cannot actually choose CA. They must choose between **CP** (Consistency over Availability during a partition) and **AP** (Availability over Consistency during a partition).

**The Trap:** Thinking a traditional single-node PostgreSQL database is "CA". While a single node provides Consistency and Availability, it is not a distributed system, so the theorem doesn't apply. The moment you distribute PostgreSQL (e.g., via synchronous replication across datacenters), it becomes a **CP** system: it will block writes if the network fails, preferring to go offline rather than corrupting consistency.
:::

## 10.3 ACID vs. BASE Semantics

Because NoSQL databases often choose Availability over Consistency (AP), they operate on **BASE** semantics instead of the strict **ACID** properties you learned for relational databases.

- **B**asically **A**vailable: The database guarantees a response to any request (success or failure), even if the data returned is slightly stale because a recent update hasn't propagated to all nodes yet.
- **S**oft State: The state of the system can change over time without any new input, simply due to background syncing between nodes.
- **E**ventually Consistent: If no new updates are made to a given piece of data, eventually all nodes will synchronize and return the exact same value. 
  - *Example:* When you "like" a post on a global social network, the counter updates instantly for you, but your friend in another country might see the old count for a few seconds. For social media, this eventual consistency is fine; for a banking ledger, it is unacceptable.

## 10.4 The Rise of NewSQL and Distributed PostgreSQL

For decades, engineers faced a stark binary choice: use SQL for strict ACID transactions but hit a vertical scaling ceiling, or use NoSQL for infinite horizontal scale but lose transactions and joins. 

**NewSQL** (also known as Distributed SQL) is a class of modern databases that attempts to solve this, providing the horizontal scalability and geographical distribution of NoSQL while maintaining strict ACID compliance and a standard SQL interface.

- **Purpose-built Distributed SQL:** Databases like Google Cloud Spanner and CockroachDB were built from the ground up for this. They achieve global consistency using advanced consensus protocols (like Raft) and specialized hardware (Spanner uses atomic clocks and GPS receivers to definitively order transactions globally).
- **PostgreSQL as Distributed SQL:** The PostgreSQL ecosystem has evolved to bridge this gap. Extensions like **Citus** transform a standard PostgreSQL database into a distributed database, automatically sharding tables and routing queries across a cluster of Postgres nodes while maintaining SQL semantics. This allows teams to scale horizontally without leaving the PostgreSQL dialect or ecosystem.

### References
1. High Availability, Load Balancing, and Replication - PostgreSQL Documentation - https://www.postgresql.org/docs/current/high-availability.html
2. CAP Theorem - IBM - https://www.ibm.com/topics/cap-theorem
3. ACID vs BASE - Medium - https://medium.com/swlh/acid-vs-base-in-databases-324c4dc8c1e7
4. Citus Data (Distributed PostgreSQL) - https://www.citusdata.com/
