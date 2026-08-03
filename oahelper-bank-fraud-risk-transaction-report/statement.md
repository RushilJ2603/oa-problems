Flipkart's risk engine flags successful payments that look suspicious. You are given five tables — accounts, transactions, merchants, device activity, and location risk — and must report every valid successful transaction whose fraud risk level is HIGH or MEDIUM.

### Validity

A transaction is valid only if all of the following hold:

1. `accountId` exists in Accounts
2. `merchantId` exists in Merchant Profiles
3. `location` exists in Location Risk
4. `1 ≤ transactionDay ≤ referenceDay`
5. `amount > 0`
6. `status` is `SUCCESS` or `FAILED`

Only valid **SUCCESS** transactions are scored. Invalid rows are ignored. Duplicate identical transaction rows each count separately toward averages, same-day counts, and output.

A device-activity row is valid only if its `accountId` exists and `firstUsedDay ≥ 1`. If several valid rows share the same `(accountId, deviceId)`, keep the earliest `firstUsedDay`.

### Features (per valid SUCCESS transaction)

1. `accountAverageAmount` = (sum of that account's successful amounts) // (count) — integer division
2. `sameDayTransactionCount` = number of valid SUCCESS transactions of the same account on the same day (including itself)
3. `isUnknownDevice` — no valid device-activity record for `(accountId, deviceId)`
4. `isFutureDevice` — device exists but earliest `firstUsedDay > transactionDay`
5. `merchantRiskTier` — LOW / MEDIUM / HIGH
6. `locationRiskScore`
7. `isOutsideHomeLocation` — transaction location ≠ account home location

### Scoring

| Condition | Points |
| --- | --- |
| amount > 2 × accountAverageAmount | +4 |
| sameDayTransactionCount ≥ 3 | +3 |
| isUnknownDevice | +4 |
| isFutureDevice | +3 |
| merchantRiskTier HIGH | +3 |
| merchantRiskTier MEDIUM | +1 |
| locationRiskScore ≥ 4 | +3 |
| isOutsideHomeLocation | +2 |

Unknown and future device points are mutually exclusive.

### Risk level

- score ≥ 10 → HIGH
- 6 ≤ score ≤ 9 → MEDIUM
- otherwise LOW (omit from output)

### Output

Print `TransactionId-AccountHolder-RiskLevel-RiskScore` for every HIGH/MEDIUM transaction, joined by `#`. Sort by:

1. HIGH before MEDIUM
2. higher riskScore first
3. higher amount first
4. earlier original input order

Print `NA` if none qualify.

## Input Format

1. `referenceDay`
2. counts: `nAccounts`, `nTransactions`, `nMerchants`, `nDeviceActivities`, `nLocations`
3. Accounts: `accountId accountHolder accountType homeLocation`
4. Transactions: `transactionId accountId merchantId deviceId location transactionDay amount status`
5. Merchants: `merchantId category riskTier`
6. Device activity: `activityId accountId deviceId firstUsedDay`
7. Locations: `location riskScore`

All tokens contain no spaces.

## Output Format

One line as described above.

## Constraints

- `2 ≤ nAccounts ≤ 100000`
- `0 ≤ nTransactions ≤ 200000`
- `1 ≤ nMerchants ≤ 100000`
- `0 ≤ nDeviceActivities ≤ 200000`
- `1 ≤ nLocations ≤ 100000`
- `1 ≤ referenceDay ≤ 1000000`
- `-1000000 ≤ transactionDay, firstUsedDay ≤ 1000000`
- `-1000000000 ≤ amount ≤ 1000000000`

## Examples

### Example 1

**Input**
```
200
3
7
3
3
4
A1 Rahul SAVINGS BLR
A2 Priya CURRENT MUM
A3 Kiran SAVINGS DEL
T1 A1 M1 D1 BLR 100 1000 SUCCESS
T2 A1 M2 D9 DEL 110 7000 SUCCESS
T3 A1 M1 D1 BLR 120 1000 SUCCESS
T4 A2 M3 D2 MUM 130 2000 SUCCESS
T5 A2 M3 D8 HYD 130 2500 SUCCESS
T6 A2 M3 D2 MUM 130 3000 SUCCESS
T7 A3 M1 D3 DEL 140 500 FAILED
M1 GROCERY LOW
M2 ELECTRONICS HIGH
M3 TRAVEL MEDIUM
DLOG1 A1 D1 10
DLOG2 A2 D2 20
DLOG3 A3 D3 30
BLR 1
DEL 4
MUM 1
HYD 4
```

**Output**
```
T2-Rahul-HIGH-16#T5-Priya-HIGH-13
```

### Example 2

**Input**
```
100
3
9
3
3
3
A1 Anita SAVINGS BLR
A2 Bala SAVINGS DEL
A3 Charu CURRENT MUM
T1 A1 M1 D1 BLR 90 1000 SUCCESS
T2 A1 M2 D9 DEL 91 6000 SUCCESS
T3 A2 M3 D2 DEL 101 5000 SUCCESS
T4 A2 M3 D2 DEL 80 -100 SUCCESS
T5 A3 M9 D3 MUM 80 1000 SUCCESS
T6 X9 M1 D1 BLR 80 1000 SUCCESS
T7 A3 M3 D3 XXX 80 1000 SUCCESS
T8 A2 M3 D2 DEL 80 1000 PENDING
T9 A2 M3 D2 DEL 80 1000 FAILED
M1 GROCERY LOW
M2 JEWELLERY HIGH
M3 TRAVEL MEDIUM
D1 A1 D1 1
D2 A2 D2 1
D3 A3 D3 1
BLR 1
DEL 4
MUM 1
```

**Output**
```
T2-Anita-HIGH-12
```

### Example 3

**Input**
```
10
2
0
1
0
1
A1 Ram SAVINGS BLR
A2 Sita CURRENT DEL
M1 GROCERY LOW
BLR 1
```

**Output**
```
NA
```
