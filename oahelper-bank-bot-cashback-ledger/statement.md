# Bank Bot Cashback Ledger

A regional bank is rolling out an automated request bot. You have been asked to implement the ledger that processes a stream of deposit and withdrawal requests and keeps every account balance correct.

Every request carries a **timestamp in seconds**. Requests arrive in order: timestamps are **strictly increasing**.

There are two request types:

- `deposit <timestamp> <holder_id> <amount>` — credit `amount` to account `holder_id`.
- `withdraw <timestamp> <holder_id> <amount>` — debit `amount` from account `holder_id`. As a bonus, the bank returns a cashback of **2%** of the withdrawn amount, **rounded down to the nearest integer**, credited back to the **same** account exactly **86400 seconds** (24 hours) after the withdrawal timestamp.

**Cashback tie-break:** if a cashback is due at the same timestamp as a deposit or withdrawal, the cashback is applied **first**. Equivalently: before handling a request at time `t`, credit every pending cashback whose due time is `<= t`.

Cashback must be computed with integer arithmetic only:

\[
\text{cashback} = \lfloor \text{amount} \times 2 / 100 \rfloor = (\text{amount} \times 2) \mathbin{//} 100
\]

Do **not** use floating-point multiplication by `0.02`.

### Invalid requests

Two kinds of request are invalid:

1. **Invalid account** — `holder_id` is not in `[1, n]`.
2. **Overdraft** — a withdrawal whose `amount` is strictly greater than the account's balance **at the moment the withdrawal is evaluated** (after any cashbacks due at or before that timestamp have already been credited).

On the first invalid request (1-based index `k`), stop immediately and report `-k`. Later requests are not processed.

### End-of-stream cashbacks

After the last request is processed, any cashbacks whose due time is **strictly after** the timestamp of that last request are **ignored** (they are never credited).

Return the balances immediately after the last request has been processed (with only the cashbacks due on or before that timestamp applied), or `-k` on the first invalid request.

### Input format

- The first line contains an integer `n` — the number of accounts.
- The second line contains `n` space-separated integers, where the `i`-th value is the balance of account `i` (accounts are numbered from `1`).
- The third line contains an integer `m` — the number of requests.
- Each of the next `m` lines contains one request in the format `<type> <timestamp> <holder_id> <amount>`, where `<type>` is either `deposit` or `withdraw`.

### Output format

If every request is valid, print the final balances as `n` space-separated integers on a single line. Otherwise print the single integer `-k`, where `k` is the 1-based index of the first invalid request.

### Constraints

- `1 <= n <= 100`
- `0 <= balances[i] <= 10^5`
- `1 <= m <= 100`
- `0 <= timestamp <= 2 * 10^9`, strictly increasing across requests
- `0 <= amount <= 10^5`

### Example 1

**Input:**
```
2
1000 1500
5
withdraw 1613327630 2 480
withdraw 1613327644 2 800
withdraw 1614105244 1 100
deposit 1614108844 2 200
withdraw 1614108845 2 150
```

**Output:**
```
900 295
```

**Explanation:** After the first two withdrawals the balances are `[1000, 220]`. At `1613414030` account 2 receives cashback `(480 * 2) // 100 = 9`, and at `1613414044` it receives `(800 * 2) // 100 = 16`, giving `[1000, 245]`. The last three requests then give `[900, 245]`, `[900, 445]` and finally `[900, 295]`. The cashbacks for the last two withdrawals are due at `1614191644` and `1614195245`, which is after the final request timestamp, so they are ignored.

### Example 2

**Input:**
```
5
20 1000 500 40 90
4
deposit 1613327630 3 400
withdraw 1613327635 1 20
withdraw 1613327651 1 50
deposit 1613327655 1 50
```

**Output:**
```
-3
```

**Explanation:** After the first two requests the balances are `[0, 1000, 900, 40, 90]`. The third request tries to withdraw `50` from account 1, which holds only `0`, so it is invalid and the answer is `-3`.
