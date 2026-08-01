# 9. Database Administration Basics

Even as a software engineer, you will be expected to understand the operational side of databases. Interviewers ask these questions to see if you understand how to keep data safe, highly available, and secure at scale.

## 9.1 Backups and Recovery

A backup strategy is dictated by two business metrics: **RPO** (Recovery Point Objective — how much data can we lose?) and **RTO** (Recovery Time Objective — how fast must we be back online?).

::: heavy
**Heavy Concept: Point-in-Time Recovery (PITR)**
**Analogy:** Imagine writing a book. A **full backup** is photocopying the entire manuscript every midnight. If you spill coffee on it at 4:00 PM, you lose 16 hours of work. But what if you set up a camera that records every single keystroke as you type? That is the **Write-Ahead Log (WAL)**.

**Concrete Example:** At 2:15 PM, a developer accidentally drops the `users` table. You don't restore last night's full backup and accept the data loss. Instead, you restore midnight's full backup into a fresh server, and then "play back" the WAL keystroke-by-keystroke, stopping exactly at 2:14:59 PM.

**Plain English:** PostgreSQL (like all major relational databases) writes every change to a sequential log *before* writing it to the actual data files. By combining a periodic snapshot (a base backup) with an unbroken archive of these logs, you can reconstruct the database state at any arbitrary microsecond. 

**Technical:** In PostgreSQL, you take a base backup using `pg_basebackup`. As the database runs, it archives its WAL segments. To recover, you configure recovery settings with `recovery_target_time = '2026-06-30 14:14:59'`, and PostgreSQL will automatically replay transactions up to that exact timestamp and halt.

**The Trap:** Thinking a daily `pg_dump` is a sufficient backup strategy for a production application. `pg_dump` produces a logical backup (SQL statements), which is slow to restore and does not support PITR. For true disaster recovery, you need physical backups (`pg_basebackup`) combined with WAL archiving.
:::

## 9.2 Scaling the Database (Replication & Sharding)

When a single database server maxes out its CPU or disk I/O, you must scale it.

::: heavy
**Heavy Concept: Replication vs Sharding**
**Analogy:** Your pizza restaurant is overwhelmed with orders. 

- **Replication** is hiring an assistant who perfectly copies your recipe book and handles all the customers asking "What are the ingredients?" (Reads), leaving you to handle the actual cooking (Writes).
- **Sharding** is opening a second restaurant across town. You take half the menu, they take the other half. You both handle Reads and Writes, but only for your specific pizzas.

**Concrete Example (Replication):** Your analytics team runs massive `SELECT` queries that slow down the database for regular users. You set up a Replica. The analytics team points their queries at the Replica, while the main application continues writing to the Primary.

**Plain English - Replication:** One server (Primary) accepts all writes. It continuously streams its transaction logs to one or more Read Replicas. This scales *Read* performance and provides failover redundancy. PostgreSQL supports **Streaming Replication** (copying raw bytes) and **Logical Replication** (copying specific tables or changes). Replication can be **Asynchronous** (Primary acknowledges the write immediately, Replica catches up later) or **Synchronous** (Primary waits for the Replica to confirm it saved the data, slowing down writes but guaranteeing zero data loss if the Primary dies).

**Plain English - Sharding:** Partitioning the actual data horizontally across multiple servers (e.g., Server A holds users A-M, Server B holds users N-Z). This scales *Write* performance because no single server handles all inserts. 

**The Trap:** Sharding a relational database manually. If you shard, queries that cross shards (like joining a user on Server A to an order on Server B) become incredibly slow and complex because the database must fetch data over the network. 
:::

## 9.3 Database Security

Security is implemented in layers, adhering to the Principle of Least Privilege.

- **Connection Security (`pg_hba.conf`):** PostgreSQL controls exactly who can connect, from which IP addresses, and using which authentication method via the Host-Based Authentication file. 
- **Role-Based Access Control (RBAC):** Users should never connect to the database as the `postgres` superuser. The application should connect using a role (a PostgreSQL concept that encompasses both users and groups) that only has `SELECT`, `INSERT`, `UPDATE` permissions on specific tables, with no `DROP` privileges.
- **Row-Level Security (RLS):** A powerful PostgreSQL feature where you can restrict which *rows* a role can see. For example, `CREATE POLICY user_policy ON accounts USING (tenant_id = current_setting('app.current_tenant'));` ensures a user can only ever select rows belonging to their tenant, even if they run `SELECT * FROM accounts`.
- **Encryption at Rest:** Protecting the physical files on the hard drive. If a hacker steals the hard drive, they cannot read the files. (Note: PostgreSQL relies on filesystem-level encryption like LUKS or third-party extensions for transparent data encryption).
- **Encryption in Transit:** Protecting the data as it travels over the network from the database server to the application server using SSL/TLS.

### References
1. Continuous Archiving and Point-in-Time Recovery (PITR) - PostgreSQL Documentation - https://www.postgresql.org/docs/current/continuous-archiving.html
2. High Availability, Load Balancing, and Replication - PostgreSQL Documentation - https://www.postgresql.org/docs/current/high-availability.html
3. Row Security Policies - PostgreSQL Documentation - https://www.postgresql.org/docs/current/ddl-rowsecurity.html
