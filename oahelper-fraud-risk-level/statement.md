# Fraud Risk Level

A payments platform wants to flag successful transfers that look risky. You are given five tables — accounts, transactions, merchant profiles, device activity, and location risk — and a reference day. Score every valid successful transaction and print those whose risk level is HIGH or MEDIUM.

## Validity

A transaction is valid only when all of the following hold:

1. `accountId` exists in Accounts.
2. `merchantId` exists in Merchant Profiles.
3. `location` exists in Location Risk.
4. `1 <= transactionDay <= referenceDay`.
5. `amount > 0`.
6. `status` is exactly `SUCCESS` or `FAILED`.

Only valid **SUCCESS** transactions are scored. A device-activity row is valid when its account exists and `firstUsedDay >= 1`. If several valid device rows share the same `(accountId, deviceId)`, keep the earliest `firstUsedDay`. Invalid rows are ignored. Duplicate identical transaction rows each contribute separately to statistics and may each appear in the output. Account, merchant, and location identifiers are unique within their tables.

## Features (per valid SUCCESS transaction)

1. **accountAverageAmount** — sum of that account's valid SUCCESS amounts, integer-divided by their count.
2. **sameDayTransactionCount** — number of valid SUCCESS transactions of the same account on the same day (including itself).
3. **isUnknownDevice** — no valid device-activity row for `(accountId, deviceId)`.
4. **isFutureDevice** — a valid device row exists, but earliest `firstUsedDay > transactionDay`.
5. **merchantRiskTier** — the merchant's risk tier.
6. **locationRiskScore** — risk score of the transaction location.
7. **isOutsideHomeLocation** — transaction location differs from the account's home location.

Unknown and future device flags are mutually exclusive.

## Risk score

| Condition | Points |
| --- | --- |
| `amount > 2 * accountAverageAmount` | +4 |
| `sameDayTransactionCount >= 3` | +3 |
| unknown device | +4 |
| future device | +3 |
| merchant tier HIGH | +3 |
| merchant tier MEDIUM | +1 |
| `locationRiskScore >= 4` | +3 |
| outside home location | +2 |

| Score | Level |
| --- | --- |
| ≥ 10 | HIGH |
| 6–9 | MEDIUM |
| < 6 | LOW |

Print only HIGH and MEDIUM transactions.

## Input

- Line 1: `referenceDay`
- Line 2: number of Accounts
- Line 3: number of Transactions
- Line 4: number of Merchant Profiles
- Line 5: number of Device Activity rows
- Line 6: number of Location Risk rows

Then, in order:

1. Accounts: `accountId accountHolder accountType homeLocation`
2. Transactions: `transactionId accountId merchantId deviceId location transactionDay amount status`
3. Merchants: `merchantId category riskTier`
4. Devices: `activityId accountId deviceId firstUsedDay`
5. Locations: `location riskScore`

All tokens contain no spaces.

## Output

Print eligible rows as `TransactionId-AccountHolder-RiskLevel-RiskScore`, joined by `#` on one line.

Sort by:

1. HIGH before MEDIUM
2. higher risk score first
3. higher amount first
4. earlier original transaction index

Print `NA` if nothing qualifies.

## Constraints

- `2 ≤ numberOfAccounts ≤ 5000`
- `0 ≤ numberOfTransactions ≤ 10000`
- `1 ≤ numberOfMerchants ≤ 2000`
- `0 ≤ numberOfDeviceActivities ≤ 5000`
- `1 ≤ numberOfLocations ≤ 2000`
- `1 ≤ referenceDay ≤ 1000000`
- `-1000000 ≤ transactionDay, firstUsedDay ≤ 1000000`
- `-1000000000 ≤ amount ≤ 1000000000`

## Examples

### Example 1

Input:
```
200
3
7
3
3
4
A1 Alice SAVINGS L1
A2 Bob CURRENT L2
A3 Charu SAVINGS L1
T1 A1 M1 D1 L1 10 100 SUCCESS
T2 A1 M2 D1 L3 10 900 SUCCESS
T3 A1 M1 D9 L1 10 200 SUCCESS
T4 A2 M3 D2 L2 20 500 FAILED
T5 A2 M2 D2 L3 20 4000 SUCCESS
T6 A3 M1 D3 L1 250 100 SUCCESS
T7 A9 M1 D1 L1 5 50 SUCCESS
M1 FOOD LOW
M2 CRYPTO HIGH
M3 RETAIL MEDIUM
V1 A1 D1 5
V2 A2 D2 900
V3 A3 D3 1
L1 1
L2 2
L3 7
L4 0
```

Output:
```
T2-Alice-HIGH-15#T5-Bob-HIGH-11#T3-Alice-MEDIUM-7
```

### Example 2

Input:
```
5
2
2
1
2
1
A1 Alice SAVINGS L1
A2 Bob SAVINGS L1
T1 A1 M1 D1 L1 1 100 SUCCESS
T2 A2 M1 D2 L1 2 100 FAILED
M1 FOOD LOW
V1 A1 D1 1
V2 A2 D2 1
L1 0
```

Output:
```
NA
```
