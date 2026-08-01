# Appendix · Four Real OA Papers: Flipkart, DE Shaw, Millennium & Uber

This appendix reproduces four complete online assessments, transcribed from the originals, together
with worked optimal solutions. The Flipkart paper was transcribed from 45 photographs of the HirePro
assessment screen; the DE Shaw, Millennium and Uber questions were reconstructed from post-test recall and
then formalized into precise statements. Reconstructed text is marked **[recon]**, and details that were
chosen rather than remembered are marked **[assumed]**, so neither is ever mistaken for the original
wording.

Every solution here was compiled and run against the statement samples before being written down,
and the eight recall-derived problems were additionally cross-checked against independent brute force
— exhaustively where the input space allowed it, and on hundreds of random inputs otherwise. File paths mentioned below (`src/`, the individual transcription files)
refer to the working folder that accompanies these notes.

Read this alongside the *OA Survival Kit* and *Debugging C++ Blind* chapters — those cover the
harness mechanics and the debugging techniques; this is the raw material they were drawn from.

## Flipkart — Coding Questions (Q1, Q2)

Source: 45 phone photos of the OA screen (`inapp.hirepro.ai` screen-share banner visible).
Transcription policy — same as the CISCO pass: orchestrator vision only, no OCR, no subagents.
Text obscured by glare/frame-crop is reconstructed from an overlapping photo where one exists;
anything still uncertain is marked **[recon]**.

Platform notes worth keeping (they drive the debugging section):
- The editor shows a **fixed function signature + a `main()` that does all the I/O for you**. You
  only fill in `// WRITE YOUR CODE HERE`. You cannot see the test cases.
- Both statements carry the warning: *"Do not print arbitrary strings anywhere in the program, as
  these contribute to the output and test cases will fail."* — i.e. **no debug `cout` survives**.
  This is exactly the constraint that makes blind debugging hard.

---

### Q1 — Golden Price (megastore savings)

**Statement.**
The megastore has kept an offer saying that, if the customer can identify a product whose price is
a *golden price* G, then it is absolutely free for them. A golden price is defined as a number G
whose difference between the sum of all the digits and the highest digit is equal to the highest
digit.

Worked examples given in the statement:
- 352 → (3+5+2) − 5 = 5 → the highest digit is 5 → golden.
- 3003, 32812 → (3+2+8+1+2) − 8 = 8 → golden.

Narendra goes to the megamarket and buys one unit of product in the price range of (X, Y). Now he
wants to know the amount he saved by selecting the golden price product from the list.

As you are a friend of Narendra, can you help him calculate the total amount he saved by purchasing
one product in the price ranges of X and Y.

Read the input from STDIN and write the output to STDOUT. You should not write arbitrary strings
while reading the input and while printing as these contribute to the standard output.

**Constraints:** `1 < X, Y < 100000`

**Input Format:** Single line of input contains the price ranges X and Y.

**Output Format:** A single line of output is the total amount that he saved.

**Sample Input 1:**
```
10 100
```
**Sample Output 1:**
```
495
```
**Explanation 1:** Given the price range X and Y is 10 and 100. After checking all the golden prices
of items between 10 and 100 we get 11,22,33,44,55,66,77,88,99. So, after adding
11 + 22 + 33 …+ 99 = 495.

**Sample Input 2:**
```
10 1000
```
**Sample Output 2:**
```
63270
```
**Explanation 2:** After checking all the golden prices of items between 10 and 1000 we get
11,22,33,44,55,66,77,88,99,101,110,112,…,880,891,909,918,927,936,945,954,963,972,981,990.
So, after adding all we get 63270.

**Provided harness (C++, verbatim):**
```cpp
#include <iostream>
using namespace std;

int totalAmount(int x, int y)   // x and y are given input numbers
{
    int count=-1;

    // WRITE YOUR CODE HERE

    return count;
}

int main()
{
    int X,Y;
    cin>>X>>Y;
    cout<<totalAmount(X,Y);
    return 0;
}
```

> **Reading the definition carefully.** "difference between the sum of all the digits and the highest
> digit is equal to the highest digit" means `digitSum(G) - maxDigit(G) == maxDigit(G)`, i.e.
> **`digitSum(G) == 2 * maxDigit(G)`**. Check against the samples: 11 → sum 2, max 1, 2 == 2·1 ✓.
> 352 → sum 10, max 5, 10 == 2·5 ✓. 32812 → sum 16, max 8, 16 == 2·8 ✓. Solution in the solutions file.

---

### Q2 — Marathon Checkpoints (sum of checkpoints with two downstream checkpoints)

*(Labelled QUESTION 3 in the OA sidebar.)*

**Statement.**
A marathon is being organised in the hilly terrains of Ladakh. Since the region is sparsely
populated, care must be taken to ensure that no runner gets lost along the route. There are multiple
checkpoints along the route, and each checkpoint must connect to only one downstream checkpoint.
However, since there were multiple teams working on setting up the connections, there have been some
mistakes, and there are some checkpoints which are connecting to more than one downstream
checkpoints.

The checkpoint details are given, with each checkpoint represented by a random integer. Write a
program to identify the checkpoints which are connecting to more than one downstream checkpoints,
and print their sum as the output.

The route details are given as a list of relations between the Starting point and the checkpoints.
The relations are indicated as L, R, LL, LR… and so on, where the checkpoint is to the left (L), or
left-left (LL) or right-left (RL) to the Starting point.

Read the input from STDIN and print the output to STDOUT. Do not print arbitrary strings anywhere in
the program, as these contribute to the output and test cases will fail.

**Constraint:** `3 <= Number of checkpoints <= 100`

**Input Format:**
- The first line of input contains an integer, N, the number of checkpoints in the route, including
  the Starting point.
- The second line of input contains an integer, which is the Starting point of the route.
- The next N−1 lines of input contain a string, S and an integer, X separated by a single white
  space, where X is a checkpoint along the route and S is the relation between the Starting point
  and X.

**Output Format:** The output contains an integer which is the sum of all checkpoints connecting to
more than one downstream checkpoint.

**Sample Input 1:**
```
6
70
L 50
LR 65
LRL 60
LRR 68
LRRL 69
```
**Sample Output 1:**
```
65
```
**Explanation 1:** The marathon route can be represented as below. Starting point is 70.

```
        70
       /
     50
       \
        65
       /  \
     60    68
          /
        69
```
We can see that checkpoint 65 is connecting to two downstream checkpoints, 60 and 68, instead of
one. Since this is the only checkpoint which does so, output is printed as 65.

**Sample Input 2:**
```
8
24
R 35
RL 30
RLL 28
RLR 34
RLLL 25
RLLR 29
RLRL 33
```
**Sample Output 2:**
```
58
```
**Explanation 2:** The marathon route can be represented as below. Starting point is 24.

```
     24
       \
        35
       /
     30
    /   \
  28     34
 /  \   /
25   29 33
```
We can see that two checkpoints, 30 and 28, are connecting to two downstream checkpoints. Sum of
checkpoints is 30+28 = 58. Hence output is 58.

**Provided harness (C++, verbatim):**
```cpp
#include <bits/stdc++.h>
using namespace std;

int sumCheckPoints(int N, int S, string pos[], int val[])
// N is the number of checkpoints in the route, including the Starting point.
// S is the Starting point of the route.
// pos contains the relation between the Starting point and val.
// val contains the checkpoint at corresponding pos index.
{
    int sum=-1;

    // WRITE YOUR CODE HERE

    return sum;
}

int main()
{
    int N;
    cin>>N;
    int S;
    cin>>S;
    string str[N-1];
    int val[N-1];
    for(int i=0;i<N-1;i++)
    {
        cin>>str[i];
        cin>>val[i];
    }
    cout<<sumCheckPoints(N,S,str,val);
    return 0;
}
```
**[recon — line 1 `#include <bits/stdc++.h>` is glare-obscured in every frame; only the tail
`…s/stdc++.h>` is legible. `using namespace std;` on line 2 is clear.]**

> This is "build a binary tree from root-relative L/R path strings, then count nodes with two
> children" — the path string is literally the sequence of left/right turns from the root. Note the
> harness uses **VLAs** (`string str[N-1]`), a GCC extension, not standard C++. Solution in the
> solutions file.

## Flipkart — Q4: Shipment Delay Risk (the specification problem)

Transcribed from the OA photos (HirePro). This is the long-form, rule-heavy question type: no
algorithmic trick at all, but a **specification you must implement exactly**. Every scoring rule,
validity rule and tie-break below is verbatim from the statement.

The provided stub is **Python 3** (the language selector showed Python; the other questions used
C++). A C++ port of the harness plus a full solution is in the solutions file.

---

### Statement

A logistics company wants to identify shipments that are at risk of delayed delivery.

The company stores shipment details, route profiles, tracking events, weather alerts, and warehouse
processing logs. Your task is to analyse these records and print shipments whose delay risk level is
HIGH or MEDIUM.

The delay risk must be calculated using tracking activity, delay events, route weather impact,
warehouse processing time, route-level comparison, and expected delivery time.

Read input from STDIN and print output to STDOUT. Do not print arbitrary strings anywhere in the
program, as these contribute to standard output and test cases will fail.

### Data Structures

**Shipments Table**

| Field | Description |
|---|---|
| shipmentId | Unique identifier of the shipment |
| shipmentName | Name or reference of the shipment |
| routeId | Route assigned to the shipment |
| dispatchDay | Day on which the shipment was dispatched |

Every routeId in the Shipments table has exactly one matching entry in the Route Profiles table.

**Route Profiles Table**

| Field | Description |
|---|---|
| routeId | Unique identifier of the route |
| standardTransitDays | Standard number of days required to complete the route |
| maxWarehouseProcessingHours | Maximum allowed total warehouse-processing hours for a shipment on that route |

**Tracking Events Table**

| Field | Description |
|---|---|
| eventId | Unique identifier of the tracking event |
| shipmentId | Shipment to which the event belongs |
| eventDay | Day on which the event was recorded |
| status | IN_TRANSIT, DELAYED, or DELIVERED |

**Weather Alerts Table**

| Field | Description |
|---|---|
| alertId | Unique identifier of the weather alert |
| routeId | Route affected by the alert |
| alertDay | Day on which the alert was recorded |
| severity | LOW, MEDIUM, or HIGH |

**Warehouse Processing Logs Table**

| Field | Description |
|---|---|
| processId | Unique identifier of the processing log |
| shipmentId | Shipment processed at the warehouse |
| processDay | Day on which processing was recorded |
| processingHours | Number of processing hours recorded |

### Valid Record Rules

A **tracking event** is valid only when all conditions are satisfied:
1. Its shipmentId exists in the Shipments table.
2. Its eventDay is between the shipment's dispatchDay and referenceDay, inclusive.
3. Its status is IN_TRANSIT, DELAYED, or DELIVERED.

A **weather alert** is valid only when all conditions are satisfied:
1. Its routeId exists in the Route Profiles table.
2. Its alertDay is between 1 and referenceDay, inclusive.
3. Its severity is LOW, MEDIUM, or HIGH.

A **warehouse processing log** is valid only when all conditions are satisfied:
1. Its shipmentId exists in the Shipments table.
2. Its processDay is between the shipment's dispatchDay and referenceDay, inclusive.
3. Its processingHours is greater than or equal to 0.

Invalid records must be ignored completely.

Every input record must be processed independently. If identical records appear more than once, each
occurrence must be counted separately.

### Features to Calculate

For every shipment, calculate the following values using only valid records.

1. **validTrackingEventCount** — Count the number of valid tracking events for the shipment.
2. **latestTrackingDay** — Find the latest eventDay among valid tracking events.
3. **daysWithoutUpdate** — `daysWithoutUpdate = referenceDay - latestTrackingDay`.
   If validTrackingEventCount is 0: `daysWithoutUpdate = referenceDay + 1`.
4. **delayEventCount** — Count valid tracking events whose status is DELAYED.
5. **isDelivered** — true if at least one valid tracking event has status DELIVERED; otherwise false.
6. **totalWarehouseProcessingHours** — Sum of processingHours from all valid warehouse-processing
   logs for the shipment.
7. **routeWeatherAlertScore** — For each route, add the following weights for all valid weather
   alerts recorded for that route:

   | Severity | Weight |
   |---|---|
   | LOW | 1 |
   | MEDIUM | 2 |
   | HIGH | 3 |

   The total is the routeWeatherAlertScore for every shipment on that route.
8. **routeAverageDelayEventCount** — For each route, calculate:
   `routeAverageDelayEventCount = total delayEventCount of all shipments on that route // number of
   shipments on that route` (integer division).
   All shipments on the route must be considered, including delivered shipments and shipments with
   no tracking events.
9. **aboveRouteDelayBaseline** — A shipment is above the route delay baseline when:
   `delayEventCount > routeAverageDelayEventCount`.
10. **expectedDeliveryDay** — `expectedDeliveryDay = dispatchDay + standardTransitDays`.

### Delay Risk Score

Calculate the delay risk score for every shipment.

| Condition | Score Added |
|---|---|
| If daysWithoutUpdate >= 5 | 4 |
| If validTrackingEventCount = 0 | 3 |
| If delayEventCount >= 2 | 3 |
| If routeWeatherAlertScore >= 4 | 2 |
| If totalWarehouseProcessingHours > maxWarehouseProcessingHours | 3 |
| If the shipment is above the route delay baseline | 2 |
| If referenceDay > expectedDeliveryDay and isDelivered is false | 4 |

The final score is:
`riskScore = staleUpdateScore + noTrackingScore + delayEventScore + weatherScore + warehouseScore +
routeBaselineScore + overdueScore`

### Delay Risk Level

| Risk Score | Risk Level |
|---|---|
| 10 or more | HIGH |
| 6 to 9 | MEDIUM |
| Less than 6 | LOW |

A delivered shipment must never be printed, even if its calculated risk score is HIGH or MEDIUM.

Only non-delivered shipments with HIGH or MEDIUM risk must be printed.

### Constraints

```
I.    2 <= numberOfShipments      <= 100000
II.   1 <= numberOfRouteProfiles  <= 100
III.  0 <= numberOfTrackingEvents <= 200000
IV.   0 <= numberOfWeatherAlerts  <= 200000
V.    0 <= numberOfWarehouseLogs  <= 200000
VI.   1 <= referenceDay           <= 1000000
VII.  1 <= dispatchDay <= referenceDay
VIII. -1000000 <= eventDay, alertDay, processDay <= 1000000
IX.   -1000000000 <= processingHours <= 1000000000
```
All IDs, names, route IDs, statuses, and severity values contain no spaces.

### Input Format

- The first line contains an integer referenceDay, representing the fixed analysis day.
- The second line contains the number of records in the Shipments table.
- The third line contains the number of records in the Route Profiles table.
- The fourth line contains the number of records in the Tracking Events table.
- The fifth line contains the number of records in the Weather Alerts table.
- The sixth line contains the number of records in the Warehouse Processing Logs table.
- The next records are provided in this order:
  1. Shipments table: `text shipmentId shipmentName routeId dispatchDay`
  2. Route Profiles table: `text routeId standardTransitDays maxWarehouseProcessingHours`
  3. Tracking Events table: `text eventId shipmentId eventDay status`
  4. Weather Alerts table: `text alertId routeId alertDay severity`
  5. Warehouse Processing Logs table: `text processId shipmentId processDay processingHours`

### Output Format

Print all eligible shipments in the following format:
```
<shipmentName>-<riskLevel>-<riskScore>-<daysWithoutUpdate>
```
If multiple shipments must be displayed, separate them with a hash symbol (`#`).

Sort the output in the following sequence:
1. HIGH risk shipments before MEDIUM risk shipments.
2. Higher riskScore first.
3. Higher daysWithoutUpdate first.
4. Original input sequence of the Shipments table when all previous values are equal.

Apply the next sorting condition only when the previous condition results in a tie.
Print `NA` if no shipment qualifies.

> **[recon]** The exact output field layout is not stated in prose anywhere in the photos — it is
> inferred from the two sample outputs, which are consistently
> `Name-LEVEL-riskScore-daysWithoutUpdate` (e.g. `Parcel_A-HIGH-18-20`, `Alpha-HIGH-16-51`). Both
> samples confirm the pattern, so the inference is safe.

### Sample Input 1
```
100
3
2
4
3
3
S1 Parcel_A R1 10
S2 Parcel_B R1 10
S3 Parcel_C R2 80
R1 20 10
R2 30 8
E1 S1 70 DELAYED
E2 S1 80 DELAYED
E3 S2 99 IN_TRANSIT
E4 S3 90 IN_TRANSIT
W1 R1 30 HIGH
W2 R1 50 MEDIUM
W3 R2 85 LOW
P1 S1 60 15
P2 S2 20 5
P3 S3 85 9
```
### Sample Output 1
```
Parcel_A-HIGH-18-20#Parcel_C-MEDIUM-7-10#Parcel_B-MEDIUM-6-1
```
### Explanation 1

For Parcel_A:
```
daysWithoutUpdate = 100 - 80 = 20
delayEventCount = 2
routeWeatherAlertScore for R1 = 3 + 2 = 5
totalWarehouseProcessingHours = 15
routeAverageDelayEventCount for R1 = (2 + 0) // 2 = 1
expectedDeliveryDay = 10 + 20 = 30
```
Parcel_A is above the route delay baseline and is overdue.
`riskScore = 4 + 0 + 3 + 2 + 3 + 2 + 4 = 18`

For Parcel_C:
```
daysWithoutUpdate = 100 - 90 = 10
totalWarehouseProcessingHours = 9
maxWarehouseProcessingHours for R2 = 8
riskScore = 4 + 3 = 7
```

For Parcel_B:
```
daysWithoutUpdate = 100 - 99 = 1
routeWeatherAlertScore for R1 = 5
expectedDeliveryDay = 30
riskScore = 2 + 4 = 6
```

Parcel_A is printed first because it has HIGH risk. Parcel_C is printed before Parcel_B because both
have MEDIUM risk but Parcel_C has a higher risk score.

### Sample Input 2
```
50
4
2
6
6
5
S1 Alpha R1 10
S2 Beta R1 10
S3 Gamma R2 20
S4 Delta R2 20
R1 20 5
R2 15 8
E1 S1 51 DELAYED
E2 S2 30 DELIVERED
E3 S3 25 UNKNOWN
E4 X9 30 DELAYED
E5 S4 40 DELAYED
E6 S4 41 DELAYED
W1 R1 5 HIGH
W2 R1 20 HIGH
W3 R1 30 MEDIUM
W4 R2 30 HIGH
W5 X9 30 HIGH
W6 R2 51 HIGH
P1 S1 20 6
P2 S2 51 10
P3 S3 30 -1
P4 S4 30 9
P5 X9 25 10
```
### Sample Output 2
```
Alpha-HIGH-16-51#Delta-HIGH-16-9#Gamma-HIGH-11-51
```
### Explanation 2

The tracking event for Alpha on day 51 is invalid because it is later than referenceDay 50.
The shipment Beta has a valid DELIVERED event and is never printed.
The tracking event of Gamma is invalid because UNKNOWN is not a valid status. Its warehouse log is
also invalid because its processingHours value is negative.

For Alpha:
```
validTrackingEventCount = 0
daysWithoutUpdate = 50 + 1 = 51
routeWeatherAlertScore for R1 = 3 + 2 = 5
totalWarehouseProcessingHours = 6
expectedDeliveryDay = 10 + 20 = 30
riskScore = 4 + 3 + 2 + 3 + 4 = 16
```

For Delta:
```
daysWithoutUpdate = 50 - 41 = 9
delayEventCount = 2
totalWarehouseProcessingHours = 9
routeAverageDelayEventCount for R2 = (0 + 2) // 2 = 1
expectedDeliveryDay = 20 + 15 = 35
riskScore = 4 + 3 + 3 + 2 + 4 = 16
```

Both Alpha and Delta have the same HIGH risk score. Alpha is printed first because Alpha has more
daysWithoutUpdate (51) than Delta (9).

> **[recon — resolved by implementation]** Alpha's `routeWeatherAlertScore for R1 = 3 + 2 = 5` as
> written in the explanation counts only two of R1's three valid alerts (W1 HIGH=3, W2 HIGH=3,
> W3 MEDIUM=2 give **8**). The photo is legible here — the statement's own arithmetic is simply
> inconsistent with its own data. A literal implementation of the *rule* (sum all valid alerts on
> the route) computes 8 and **reproduces both sample outputs exactly**, because the condition is
> `>= 4` and both readings clear it. So the rule text is trustworthy and the worked explanation
> contains an arithmetic slip. Implement the rule, not the explanation's number.
>
> This is worth internalising: OA statements contain errors, and the sample explanations are
> hand-written prose that is *not* generated from the reference solution. When explanation and rule
> disagree, the rule plus the sample **output** is the ground truth — the explanation's intermediate
> values are the least reliable thing in the document.

### Provided harness (Python 3, verbatim)

```python
import sys

def solve(reference_day, shipments, route_profiles, tracking_events, weather_alerts, warehouse_logs):
    """
    reference_day:
        Fixed analysis day.

    shipments:
        List of tuples:
            (shipment_id, shipment_name, route_id, dispatch_day, input_index)

    route_profiles:
        List of tuples:
            (route_id, standard_transit_days, max_warehouse_hours)

    tracking_events:
        List of tuples:
            (event_id, shipment_id, event_day, status)

    weather_alerts:
        List of tuples:
            (alert_id, route_id, alert_day, severity)

    warehouse_logs:
        List of tuples:
            (process_id, shipment_id, process_day, processing_hours)

    Return:
        Final output string in the required format.
        Return "NA" if no shipment qualifies.
    """

    final_output = "NONE"

    # WRITE YOUR CODE HERE

    return final_output

def main():
    input_data = sys.stdin.readline

    reference_day = int(input_data())

    shipment_count = int(input_data())
    route_count = int(input_data())
    tracking_count = int(input_data())
    weather_count = int(input_data())
    warehouse_count = int(input_data())

    shipments = []
    for input_index in range(shipment_count):
        shipment_id, shipment_name, route_id, dispatch_day = input_data().split()
        shipments.append((shipment_id, shipment_name, route_id, int(dispatch_day), input_index))

    route_profiles = []
    for _ in range(route_count):
        route_id, standard_transit_days, max_warehouse_hours = input_data().split()
        route_profiles.append((route_id, int(standard_transit_days), int(max_warehouse_hours)))

    tracking_events = []
    for _ in range(tracking_count):
        event_id, shipment_id, event_day, status = input_data().split()
        tracking_events.append((event_id, shipment_id, int(event_day), status))

    weather_alerts = []
    for _ in range(weather_count):
        alert_id, route_id, alert_day, severity = input_data().split()
        weather_alerts.append((alert_id, route_id, int(alert_day), severity))

    warehouse_logs = []
    for _ in range(warehouse_count):
        process_id, shipment_id, process_day, processing_hours = input_data().split()
        warehouse_logs.append((process_id, shipment_id, int(process_day), int(processing_hours)))

    result = solve(reference_day, shipments, route_profiles, tracking_events,
                   weather_alerts, warehouse_logs)

    print(result)

if __name__ == "__main__":
    main()
```
**[recon]** The right edge of the code pane is cut off in every frame, so the tail of the long
`… = input_data().split()` lines and the `int(...)` conversions inside each `append` were
reconstructed from the visible left portion plus the docstring's declared tuple shapes. The structure
is unambiguous (each loop reads one line, splits it, appends a tuple with the numeric fields cast);
the exact wrapping is not.

Note `final_output = "NONE"` in the stub versus the docstring's instruction to return `"NA"` — the
stub's placeholder is a decoy, the spec says NA.

## Flipkart — SQL Question

Transcribed from the OA photos (HirePro). One SQL round question appeared alongside the coding ones.

### Statement

A Hospital Management System (HMS) is a software solution designed to streamline and optimize the
administrative and clinical tasks within a healthcare facility. It serves as a centralized platform
for managing various aspects of hospital operations, including Patients, Appointments, Doctors,
Specialization and Doc_Specialization_Mapping.

**Write an SQL query to display the FirstName and LastName of all patients who have taken at least
one doctor appointment and whose ContactNumber and Email are not provided. Consider a value as not
provided when it is NULL, an empty string, or contains only blank spaces. Sort the result in
ascending order of FirstName.**

### Schema (ER diagram)

```
Patients                      Appointments                  Doctors
--------                      ------------                  -------
PatientID     INT(30)   1─┬──N AppointmentID INT(50)   N──┬─1 DoctorID       INT(20)
FirstName     VARCHAR(50)  │    PatientID     INT(30)     │   FirstName      VARCHAR(50)
LastName      VARCHAR(50)  │    DoctorID      INT(20)     │   LastName       VARCHAR(50)
Gender        VARCHAR(10)  │    AppointmentDate DATE      │   Gender         VARCHAR(10)
DateOfBirth   DATE         │    AppointmentTime TIME      │   ContactNumber  VARCHAR(15)
ContactNumber VARCHAR(15)  │                              │   Email          VARCHAR(100)
Address       VARCHAR(255) │                              │
Email         VARCHAR(100) │                              │ 1
                           │                              │ N
Specialization             │            Doc_Specialization_Mapping
--------------             │            -------------------------
Specialization_id   INT(50) ──1──N────→ DoctorID          INT(20)
Specialization_Name VARCHAR(50)         Specialization_id INT(50)
```

### Sample Input

**Patients**

| PatientID | FirstName | LastName | Gender | DateOfBirth | ContactNumber | Address |
|---|---|---|---|---|---|---|
| 1 | John | Doe | Male | 1990-05-15 | +123456789 | 123 Main … |
| 2 | Jane | Smith | Female | 1985-08-22 | +987654321 | 456 Oak … |
| 3 | Alice | Johnson | Female | 1982-12-08 | +111223344 | 789 Pine … |
| 4 | Bob | Williams | Male | 1975-06-25 | NULL | 101 Cedar … |

*(The Email column is cut off past the right edge of the frame in every photo — **[recon]**: for the
sample output to be `Bob,Williams`, Bob's Email must also be NULL/empty/blank, and the other three
patients must have at least one of ContactNumber/Email provided.)*

**doctors**

| DoctorID | FirstName | LastName | Gender | ContactNumber | Email |
|---|---|---|---|---|---|
| 1 | Dr. Michael | Johnson | Male | +111222333 | michael.j@example.com |
| 2 | Dr. Sarah | Anderson | Female | +444555666 | sarah.a@example.com |
| 3 | Dr. David | Miller | Male | +777888999 | david.m@example.com |
| 4 | Dr. Emily | Davis | Female | +999000111 | emily.d@example.com |

**Appointments**

| AppointmentID | PatientID | DoctorID | AppointmentDate | AppointmentTime |
|---|---|---|---|---|
| 101 | 1 | 1 | 2023-01-10 | 10:30:00 |
| 102 | 2 | 2 | 2023-01-12 | 14:00:00 |
| 103 | 3 | 3 | 2023-02-05 | 11:15:00 |
| 104 | 4 | 4 | 2023-02-10 | 15:30:00 |

**Specialization**

| Specialization_id | Specialization_Name |
|---|---|
| 101 | Cardiology |
| 102 | Pediatrics |
| 103 | Orthopedics |
| 104 | Internal Medicine |

**Doc_Specialization_Mapping**

| DoctorID | Specialization_id |
|---|---|
| 1 | 101 |
| 2 | 102 |
| 3 | 103 |
| 4 | 104 |

### Sample Output
```
Bob,Williams
```

### Answer

The whole question is the *"not provided"* definition — NULL, empty string, **or only blank spaces**.
The blank-spaces clause is what most candidates miss: `col = ''` does not catch `'   '`, so you must
`TRIM` before comparing. And because `NULL` never satisfies any comparison, the NULL case needs its
own `IS NULL` test — `TRIM(Email) = ''` is *unknown*, not true, when Email is NULL.

```sql
SELECT p.FirstName, p.LastName
FROM Patients p
WHERE EXISTS (
        SELECT 1
        FROM Appointments a
        WHERE a.PatientID = p.PatientID
      )
  AND (p.ContactNumber IS NULL OR TRIM(p.ContactNumber) = '')
  AND (p.Email         IS NULL OR TRIM(p.Email)         = '')
ORDER BY p.FirstName ASC;
```

Notes on the shape of the answer:
- **`EXISTS` over `JOIN`** — "at least one appointment" with a plain `INNER JOIN` would emit one row
  per appointment, so a patient with three appointments appears three times. `EXISTS` (or
  `JOIN … GROUP BY`, or `IN (SELECT PatientID FROM Appointments)`) keeps it one row per patient.
- The Doctors / Specialization / Doc_Specialization_Mapping tables are **decoys** — the question only
  needs Patients and Appointments. OA SQL questions routinely hand you a full schema and ask about
  two tables.
- `TRIM` handles the blank-spaces clause. On MySQL, `TRIM` strips only spaces by default; if tabs were
  in scope you would need `TRIM(BOTH ' \t' FROM col)` or a regex.
- The output renders as `Bob,Williams` (comma-joined), which is the platform's display format for a
  two-column result row, not something the query produces.

## DE Shaw — Coding Questions (formalized from recall)

**Provenance.** These three were written down from memory after the test, not photographed. The raw
recall notes are in `../Flipkart & de shaw oa questions/DE SHAW QUESTION 1 designing a play.txt`.
Below, each one is **formalized**: the remembered kernel is restated as a precise problem with
explicit input/output, constraints, edge cases, and worked examples. Anything the recall did not pin
down (exact bounds, 0- vs 1-indexing, tie-breaks) is chosen to give the *intended* difficulty and is
flagged **[assumed]** so it is never mistaken for the original wording.

Constraints are set at the level the intended solution implies — where the recall says "you'll have
two queries" repeatedly, the problem is only interesting if `q` is large enough to kill the naive
per-query rebuild, so bounds are chosen accordingly.

---

### Q1 — Designing a Music Player (move-before + positional lookup)

**Recall (verbatim):** *"designing a player, given an array of tracks (1 indexed) shuffled in an
array, you'll have two queries, query 1, you will be given two tracks u and v, you find them in
tracks array, delete u from its place and place it before v, and other type of query is that given a
location (1 indexed), return the track at that location"*

#### Formalized statement

You are building the queue for a music player. The playlist is a sequence of `n` **distinct** track
IDs, initially given as a shuffled permutation of `1 … n`. Positions in the playlist are 1-indexed.

Process `q` queries of two kinds:

- `1 u v` — **Move.** Remove track `u` from its current position and re-insert it immediately
  **before** track `v`. It is guaranteed that `u ≠ v` and both are present in the playlist.
- `2 k` — **Query.** Print the track ID currently at position `k` (1-indexed).

**Input**
```
n q
a1 a2 … an           (the initial playlist, a permutation of 1..n)
then q lines, each either "1 u v" or "2 k"
```

**Output** — for each type-2 query, one line with the track ID at position `k`.

**Constraints [assumed]**
```
1 <= n, q <= 2 * 10^5
1 <= a_i, u, v <= n, all a_i distinct
1 <= k <= n
```

**Example**
```
Input                Output
5 4                  4
3 1 4 5 2            3
2 3                  4
1 4 1
2 1
2 2
```
Walkthrough: start `[3,1,4,5,2]`. Query `2 3` → position 3 holds `4`. Move `1 4 1`: pull `4` out and
put it immediately before `1` → `[3,4,1,5,2]`. Query `2 1` → `3`. Query `2 2` → `4`.
**[recon]** the third printed value above is `4`, not `1` — recomputed from the trace rather than
trusting the sketch.

> **A bug found by actually running this.** The header first read `5 5` while only four query lines
> follow. Running it printed a *fourth* line, `4` — a repeat of the third. Since C++11 a failed
> `cin >> x` leaves `x` **unchanged**, so at EOF the loop re-ran with the previous `type` and `k`
> still in the variables and happily printed again. On an OA this is a trailing-junk-output
> wrong-answer with no visible cause. See the OA-debugging section: always drive the read count from
> the declared header value, and treat "one extra line of output" as a failed-read signature.

#### Why it is not trivial

The recall's phrasing ("find them in the tracks array, delete, place before") describes the **naive**
algorithm: `O(n)` per move with a vector. With `q` up to 2·10⁵ that is 4·10¹⁰ element shifts.

A `list<int>` gives `O(1)` splice once you hold both iterators (store an iterator per track ID), which
solves the *move* in O(1) — but then `2 k` costs `O(n)` because a linked list has no random access.
The two operations pull in opposite directions, and that tension **is** the question.

The intended structure is an **order-statistic tree** — a BIT over positions, or a balanced BST /
treap by implicit key. See the solutions file for the full treatment.

#### Edge cases worth naming
- `u` is already immediately before `v` → the move is a no-op; the code must not corrupt the order.
- `v` is at position 1 → `u` becomes the new head.
- `u` is at position 1 and moves elsewhere → the head changes.
- A move never changes `n`, so `2 k` is always in range.

---

### Q2 — Maximum Flips Keeping Every Prefix Sum Positive

**Recall (verbatim):** *"given an array of positive integers, return the max number of elements you
can flip to negative, but still have the prefix sum at each index be positive"*

#### Formalized statement

You are given an array `a` of `n` **positive** integers. You may choose any subset of positions and
flip the sign of each chosen element (`a_i → -a_i`). A choice is **valid** if after flipping, every
prefix sum is strictly positive:

```
for every i in 1..n:   a_1 + a_2 + … + a_i  >  0
```

Return the **maximum number of elements** that can be flipped over all valid choices.

**Input**
```
n
a1 a2 … an
```
**Output** — a single integer: the maximum count of flipped elements.

**Constraints [assumed]**
```
1 <= n <= 2 * 10^5
1 <= a_i <= 10^9
```
Note the sum can reach 2·10¹⁴ — **`long long` is mandatory**. This is exactly the kind of silent
overflow an OA punishes with a wrong-answer you cannot see.

**Example**
```
Input            Output
5                3
4 1 2 1 3
```
One optimal choice: flip `a_2`, `a_4` and `a_5`, giving `4, -1, 2, -1, -3` with prefix sums
`4, 3, 5, 4, 1` — all strictly positive, 3 flips. A fourth flip is impossible: the un-flipped total
is 11, and flipping a set `F` leaves the final prefix at `11 - 2·sum(F)`, so `sum(F) <= 5`; no four
of `{4,1,2,1,3}` sum to 5 or less.

> **This example was wrong when first written.** It originally claimed the answer was 2, on the
> reasoning that "flipping any third element breaks positivity somewhere" — which is simply false,
> as the trace above shows. The error surfaced only because the solution was cross-checked against
> exhaustive search over all 2ⁿ sign patterns. A hand-derived expected value is not evidence; on an
> OA the same mistake reads as "my code is broken" and sends you debugging correct code.

**[assumed]** *strictly* positive (`> 0`) rather than non-negative (`>= 0`). The recall says
"positive". If the intended reading were `>= 0` the algorithm is identical, only the comparison
changes — noted because it is a one-character difference that flips half the test cases.

#### The shape of the answer

Greedy + max-heap, scanning left to right and *retracting* a past decision when the running sum goes
non-positive: flip everything optimistically, and when the prefix breaks, un-flip the largest
element flipped so far (that is the cheapest way to buy back the most sum). This is the same
"regret" pattern as the classic *IPO* / *Course Schedule III* problems. Full derivation and proof
sketch in the solutions file.

---

### Q3 — Counting Checkerboard Subgrids

**Recall (verbatim):** *"given a grid of 0s and 1s, find as many subgrids where adjacent elements (up
down right left) do not share the same number, so like 0 1 is a subgrid, 0 is a subgrid, 1 is a
subgrid, 0101 is a subgrid, a checkerboard 3*3 of 1s and 0s has 36 subgrids"*

#### Formalized statement

Given an `n × m` binary grid, count the number of **axis-aligned rectangular subgrids** that form a
valid checkerboard — that is, subgrids in which every pair of orthogonally adjacent cells (up, down,
left, right) holds **different** values.

Subgrids are identified by their position, so two subgrids at different locations count separately
even if their contents are identical. A single cell is a valid subgrid (it has no adjacent pairs
inside it, so the condition holds vacuously).

**Input**
```
n m
n lines of m characters each, '0' or '1'
```
**Output** — a single integer: the number of checkerboard subgrids.

**Constraints [assumed]**
```
1 <= n, m <= 2000
```
An `O(n·m)` or `O(n·m·log)` solution is expected; the answer can exceed 32 bits, so **`long long`**.

#### Verifying the recalled example

The recall asserts a 3×3 checkerboard has **36** subgrids. Every subgrid of a perfect checkerboard is
itself a checkerboard, so this reduces to counting all rectangular subgrids of a 3×3 grid:

```
number of subgrids = C(4,2) × C(4,2) = 6 × 6 = 36   ✓
```
(choose 2 of the 4 horizontal boundaries and 2 of the 4 vertical boundaries). The recalled figure
checks out, which is good evidence the rest of the recall is faithful.

In general an `n × m` all-checkerboard grid has `n(n+1)/2 × m(m+1)/2` subgrids — for a 2000×2000
grid that is about 4·10¹² , comfortably past `int`.

**Example**
```
Input        Output
2 2          8
01
10
```
Four 1×1, two 1×2, two 2×1, one 2×2 — wait, that is 9. Recount: 1×1 → 4, 1×2 → 2, 2×1 → 2,
2×2 → 1, total **9**. The grid is a perfect checkerboard so the formula gives
`2·3/2 × 2·3/2 = 3 × 3 = 9`. ✓ *(Output above corrected to 9 — the first count was wrong and is left
visible on purpose: this is exactly the kind of hand-count slip that produces a "works on sample,
fails on submit" OA result.)*

#### The shape of the answer

The key structural fact: a rectangle is a checkerboard **iff** every row-adjacent pair differs *and*
every column-adjacent pair differs. That decomposes into per-cell "how far can I extend left with
alternation" and "how far up", which is a standard DP — then counting rectangles reduces to the
classic *maximal rectangle in a histogram* counting variant. Full derivation in the solutions file.

---

### What these three have in common

All three are **"the naive statement hides the real constraint"** problems, which is DE Shaw's
house style:

- Q1 *sounds* like list manipulation, and is really an order-statistic structure.
- Q2 *sounds* like a search over subsets (2ⁿ), and is really a one-pass greedy with a heap.
- Q3 *sounds* like O((nm)²) rectangle enumeration, and is really a linear-ish DP.

In each case the naive reading is what the problem statement literally describes, and it is
quadratic-or-worse. Reading the constraint bound is what tells you which one is wanted — and in an
OA where you cannot see the failing test, a TLE on hidden tests is indistinguishable from a wrong
answer unless you have already reasoned about the bound.

## Optimal Solutions, With Verification

Every code block below was **compiled and run** before being written down. Where the problem came
from recall rather than a photo (the DE Shaw three), the solution was additionally cross-checked
against brute force on hundreds of random inputs, because there is no official test data to trust.

Verification status, in full:

| Problem | Language | Verified against | Result |
|---|---|---|---|
| Flipkart Q1 — Golden Price | C++17 | both statement samples | `495`, `63270` ✓ |
| Flipkart Q2 — Marathon Checkpoints | C++17 | both statement samples | `65`, `58` ✓ |
| Flipkart Q4 — Shipment Delay Risk | Python 3 | both statement samples | exact string match ✓ |
| Flipkart SQL — HMS | SQL | statement sample | `Bob,Williams` ✓ |
| DE Shaw Q1 — Music Player | C++17 | 300 random cases vs. naive `vector` | all match ✓ |
| DE Shaw Q2 — Max Flips | C++17 | 400 random cases vs. exhaustive 2ⁿ search | all match ✓ |
| DE Shaw Q3 — Checkerboard Subgrids | C++17 | 250 random grids vs. O((nm)²) brute force | all match ✓ |

Sources live beside this file in `src/`. Statements are in the four transcription files.

::: keypoint
**The cross-checks earned their keep.** Two of the worked examples I had written by hand into
`deshaw_coding.md` were **wrong**, and both were caught only by running code against a brute force:
Q2's answer was 3, not the 2 I had reasoned out, and Q1's example header declared five queries while
supplying four. Neither error is visible by staring. On an OA this failure mode is expensive in a
specific way — you conclude your *code* is broken and start "fixing" a correct solution.
:::

---

### Flipkart Q1 — Golden Price

**Parse the definition first.** "The difference between the sum of all the digits and the highest
digit is equal to the highest digit" is

```
digitSum(G) - maxDigit(G) == maxDigit(G)     ⟺     digitSum(G) == 2 * maxDigit(G)
```

Check it against the statement's own examples before writing anything: 352 → sum 10, max 5, and
10 == 2·5 ✓. 32812 → sum 16, max 8, 16 == 2·8 ✓. 11 → sum 2, max 1, 2 == 2·1 ✓.

::: trap
The statement also lists **3003** as golden, and it is: sum 6, max 3, 6 == 2·3. But notice the
trailing/leading zeros do not perturb the rule at all, which is a useful sanity anchor — if your
digit loop mishandles `0` digits (for instance by using `while (t)` on a number that is itself 0),
3003 will still pass while a genuine edge case like `X = 1` silently misbehaves.
:::

With `X, Y < 100000` the search space is at most 10⁵ numbers of ≤ 6 digits — brute force over the
range is ~6·10⁵ digit operations, instantly fast. There is no need to be clever here, and being
clever is how you lose marks.

```cpp
#include <iostream>
using namespace std;

static bool isGolden(int g) {
    int sum = 0, hi = 0;
    for (int t = g; t > 0; t /= 10) {
        int d = t % 10;
        sum += d;
        if (d > hi) hi = d;
    }
    return sum - hi == hi;          // digitSum == 2 * maxDigit
}

int totalAmount(int x, int y) {
    if (x > y) { int t = x; x = y; y = t; }   // "range of X and Y" — order not guaranteed
    long long total = 0;
    for (int g = x; g <= y; ++g)
        if (isGolden(g)) total += g;
    return (int)total;
}

int main() {
    int X, Y;
    cin >> X >> Y;
    cout << totalAmount(X, Y);
    return 0;
}
```

Two decisions worth naming:

- **The swap.** The statement says "price range of (X, Y)" and never promises `X < Y`. The swap
  costs one line and removes an entire class of hidden-test failure. When a statement is silent,
  defend against both readings if the defence is free.
- **`long long` accumulator.** The signature forces an `int` return, but the *sum* over a range up
  to 10⁵ can reach roughly 5·10⁸ — inside `int`, but not by a comfortable margin. Accumulating in
  `long long` and narrowing once at the end costs nothing and makes the overflow question
  answerable by inspection instead of by arithmetic.

Complexity: **O((Y−X)·d)** time, **O(1)** space, where d ≤ 6 is the digit count.

---

### Flipkart Q2 — Marathon Checkpoints

Strip the story: each checkpoint is given by its **path from the root** as a string of `L`/`R`
turns. The starting point is the empty path. "Connects to more than one downstream checkpoint" means
a node with **both** children present. Sum those nodes' values.

::: keypoint
**You never need to build the tree.** The path string *is* the node's address. A node at path `p`
has children at `p + "L"` and `p + "R"`. So the whole problem is: put every path in a hash set, then
for each path check whether both extensions are present. No pointers, no recursion, no tree at all.
:::

That reframing is the entire question. Candidates who reach for `struct Node { Node *l, *r; }` spend
twenty minutes writing an insertion routine that walks the path string creating intermediate nodes,
and then have to handle the case where an intermediate node was never given explicitly.

```cpp
#include <bits/stdc++.h>
using namespace std;

int sumCheckPoints(int N, int S, string pos[], int val[])
{
    // Path string -> checkpoint value. The root (Starting point) has the empty path.
    unordered_map<string, int> node;
    node[""] = S;
    for (int i = 0; i < N - 1; ++i)
        node[pos[i]] = val[i];

    // A checkpoint is "faulty" iff both of its downstream slots are occupied.
    int sum = 0;
    for (const auto &kv : node)
        if (node.count(kv.first + "L") && node.count(kv.first + "R"))
            sum += kv.second;
    return sum;
}
```

Verified against both samples: `65` and `58`.

::: trap
**The stub initialises `int sum = -1;`.** Every one of these HirePro stubs seeds the answer variable
with `-1`, and if your logic happens to add nothing you return `-1` rather than `0`. Overwrite it
with `0` explicitly. This is a real single-character wrong-answer: a test case with no faulty
checkpoint at all should print `0`.
:::

::: trap
**The harness uses variable-length arrays** — `string str[N-1]` with `N` read at runtime. VLAs are a
**GCC extension**, not standard C++; `g++` accepts them, MSVC and `clang -pedantic` reject them. Two
consequences: (a) do not "fix" it, the platform compiles it fine; (b) if you test locally on a
different compiler and get an error on a line you did not write, that is why. Also note `N = 1`
would declare a zero-length array — the constraint `N >= 3` rules it out, but that is the kind of
thing to check rather than assume.
:::

Complexity: **O(N·L)** time and space where L is the maximum path length (≤ N, so O(N²) worst case
for a degenerate chain — with `N ≤ 100`, irrelevant). String hashing dominates.

---

### Flipkart Q4 — Shipment Delay Risk

There is **no algorithm here**. It is a specification-implementation problem: five tables, three
validity predicates, ten derived features, seven scoring rules, a three-way classification and a
four-level sort. The entire difficulty is fidelity and ordering, and the entire failure mode is
mis-reading one rule.

::: keypoint
**The dependency order is what to get right.** Features are not independent — you cannot score a
shipment until you know its route's average delay count, which needs *every* shipment's delay count,
which needs the validity filter applied first. So the shape is fixed:

1. Index the lookup tables (`shipmentId → shipment`, `routeId → profile`).
2. Filter and fold **per-shipment** facts (tracking events, warehouse logs).
3. Fold **per-route** aggregates (weather score; delay average — which needs step 2 finished).
4. Score each shipment, then filter, then sort.

Attempting to score in a single pass over the input is the most common way to lose this question.
:::

Full implementation in `src/q4_logistics.py`; the core is:

```python
    # --- per-route aggregates ---------------------------------------------------------
    weather_score = {rid: 0 for rid in route}
    for _aid, rid, day, severity in weather_alerts:
        if rid not in route or severity not in SEVERITY_WEIGHT:
            continue
        if not (1 <= day <= reference_day):
            continue
        weather_score[rid] += SEVERITY_WEIGHT[severity]

    route_delay_total = {rid: 0 for rid in route}
    route_ship_total = {rid: 0 for rid in route}
    for s in shipments:                       # every shipment counts, delivered or not
        route_delay_total[s[2]] += delay_count[s[0]]
        route_ship_total[s[2]] += 1
    route_avg_delay = {rid: route_delay_total[rid] // route_ship_total[rid] for rid in route}
```

and the scoring, written to mirror the statement's table line by line so it can be **read against
the spec** rather than re-derived:

```python
        score = 0
        if days_without_update >= 5:                      score += 4
        if count == 0:                                    score += 3
        if delay_count[sid] >= 2:                          score += 3
        if weather_score[rid] >= 4:                        score += 2
        if warehouse_hours[sid] > max_hours:               score += 3
        if delay_count[sid] > route_avg_delay[rid]:        score += 2
        if reference_day > expected_delivery_day and not delivered[sid]:
            score += 4
```

#### The traps, each of which is a separate hidden test

::: trap
**Validity rule 2 is per-shipment, not global.** A tracking event is valid when its `eventDay` lies
between *that shipment's* `dispatchDay` and `referenceDay`. Sample 2 leans on this: `E1 S1 51
DELAYED` is invalid because 51 > referenceDay 50, which is what drives Alpha to
`validTrackingEventCount = 0` and therefore `daysWithoutUpdate = 51`.

**Records referencing a non-existent id are dropped, not created.** `E4 X9 …`, `W5 X9 …` and
`P5 X9 …` in sample 2 all name a shipment/route that does not exist. If you use a `defaultdict`
keyed by id you will silently invent shipment `X9` and then crash or mis-count later.

**Negative processing hours are invalid, but zero is valid** — the rule is `>= 0`. Sample 2's
`P3 S3 30 -1` exists purely to test this.

**`routeAverageDelayEventCount` uses integer division and counts every shipment on the route** —
including delivered ones and ones with no tracking events at all. Filtering delivered shipments out
*before* computing the average is a wrong answer that still passes both samples if you are unlucky.

**Delivered shipments are excluded after scoring, not before.** They still contribute to their
route's delay total and shipment count.

**The sort is four-level and two of the levels are descending.** HIGH before MEDIUM, then score
descending, then `daysWithoutUpdate` descending, then original input index ascending. That last
tie-break is why the harness hands you `input_index` in the tuple — it is a hint, and it means
sorting on a dict's iteration order will eventually bite you.

**Return `"NA"`, not the stub's `"NONE"`.** The stub initialises `final_output = "NONE"` while the
docstring says return `"NA"`. The docstring and the spec agree; the initialiser is a decoy.
:::

::: interview
When a statement's worked explanation disagrees with its own rules, **trust the rule and the sample
output, never the explanation's intermediate numbers.** Here, Alpha's explanation computes
`routeWeatherAlertScore for R1 = 3 + 2 = 5` while R1 demonstrably has three valid alerts summing to
8. Implementing the rule literally gives 8 and still reproduces both sample outputs exactly, because
the threshold is `>= 4`. Sample explanations are hand-written prose; they are not generated from the
reference solution, and they are the least reliable content in an OA statement.
:::

Complexity: **O(S + R + T + W + P)** to fold, plus **O(S log S)** to sort. At the stated bounds
(10⁵ shipments, 2·10⁵ of each event type) this is comfortable in Python.

---

### Flipkart SQL — Hospital Management System

The full statement, schema and sample are in `flipkart_sql.md`. The query:

```sql
SELECT p.FirstName, p.LastName
FROM Patients p
WHERE EXISTS (
        SELECT 1
        FROM Appointments a
        WHERE a.PatientID = p.PatientID
      )
  AND (p.ContactNumber IS NULL OR TRIM(p.ContactNumber) = '')
  AND (p.Email         IS NULL OR TRIM(p.Email)         = '')
ORDER BY p.FirstName ASC;
```

::: keypoint
**The whole question is the definition of "not provided": NULL, empty string, *or only blank
spaces*.** Three distinct conditions, and each one defeats a different naive attempt:

- `col = ''` misses `'   '` → hence `TRIM`.
- `TRIM(col) = ''` misses `NULL`, because comparing to NULL yields **unknown**, not true, and a
  `WHERE` clause only keeps rows that are *true* → hence the explicit `IS NULL`.
- `col IS NULL` alone misses both empty and blank strings.
:::

::: trap
**"At least one appointment" with an `INNER JOIN` duplicates rows.** A patient with three
appointments appears three times. `EXISTS` (or `IN (SELECT …)`, or `JOIN … GROUP BY p.PatientID`)
keeps one row per patient. `EXISTS` is also the one that short-circuits — it stops at the first
match rather than materialising all of them.
:::

The Doctors, Specialization and Doc_Specialization_Mapping tables are **decoys**: the answer touches
only Patients and Appointments. OA SQL questions routinely present a complete schema and ask a
question about two of its tables — read the *question*, then decide which tables exist.

---

### DE Shaw Q1 — Music Player

Two operations that pull in opposite directions:

- `1 u v` — move track `u` immediately before track `v`.
- `2 k` — report the track at position `k`.

::: keypoint
**Name the tension before choosing a structure.** A `vector` gives O(1) positional lookup and O(n)
move. A `list` with a stored iterator per track gives O(1) move (`splice`) and O(n) lookup, because
a linked list has no random access. Each naive structure is optimal for one operation and worst-case
for the other — so with both operations appearing up to 2·10⁵ times, either choice is ~4·10¹⁰
element visits. **That trade-off is the question**, and recognising it is most of the answer.
:::

What you need is an **order-statistic sequence**: a container that maintains insertion order but can
also answer "what is at index k" in sublinear time.

#### The solution I would actually write in an OA: sqrt decomposition

Split the sequence into ~√n buckets of ~√n elements each, held as `vector<int>`. Track which bucket
owns each track ID. Every operation touches one bucket internally (O(√n)) and at most walks the
bucket list (O(√n)).

```cpp
struct Playlist {
    int n, B;                       // B = target bucket size
    vector<vector<int>> buck;       // the sequence, split into buckets
    vector<int> owner;              // owner[track] = index of the bucket holding it

    void rebuild(const vector<int> &flat);   // re-split evenly into buckets of size B
    vector<int> flatten() const;             // concatenate the buckets back to a sequence

    void erase(int u) {
        auto &v = buck[owner[u]];
        v.erase(find(v.begin(), v.end(), u));
    }

    void insertBefore(int u, int v) {
        int b = owner[v];
        auto &vec = buck[b];
        vec.insert(find(vec.begin(), vec.end(), v), u);
        owner[u] = b;
        if ((int)vec.size() > 2 * B) rebuild(flatten());   // amortised O(n/B) per op
    }

    int at(int k) const {           // 1-indexed
        for (const auto &v : buck) {
            if (k <= (int)v.size()) return v[k - 1];
            k -= (int)v.size();
        }
        return -1;
    }
};
```

Full source in `src/ds_q1_player.cpp`, cross-checked against a naive `vector` implementation on 300
random operation sequences.

**Why the rebuild is needed and why it is cheap.** Insertions concentrate in one bucket; without
rebalancing a single bucket can grow to n and `erase`/`insert` degrade to O(n). Rebuilding the whole
structure whenever any bucket exceeds `2B` costs O(n), but a bucket needs B insertions to get there,
so the cost amortises to O(n/B) = O(√n) per operation. Total: **O((n + q)√n)** ≈ 9·10⁷ vector
element moves at the stated bounds — which `memmove`-backed `vector::insert` handles in well under a
second.

#### The asymptotically better answer: an implicit-key balanced BST

An implicit treap (or splay tree) keyed by *subtree size* rather than by value gives O(log n) for
both operations: `split` the sequence at u's position to extract it, `split` again at v's position,
`merge` the three pieces back in the new order.

::: trap
The catch, which is worth stating in an interview because it is the part people miss: `2 k` walks
down from the root by size, but the *move* needs the current **position of a given value**, which is
a walk **up** from the node to the root. That requires parent pointers maintained correctly through
every split and merge — considerably more code, and more places to be subtly wrong, than the √n
version. In an OA where √n passes, √n is the correct engineering decision. In an interview, say both
and explain the trade-off.
:::

| Approach | move | lookup | verdict |
|---|---|---|---|
| `vector` | O(n) | O(1) | TLE |
| `list` + iterator map | O(1) | O(n) | TLE |
| bucket / sqrt decomposition | O(√n) am. | O(√n) | **passes, ~30 lines** |
| implicit treap | O(log n) | O(log n) | optimal, ~120 lines + parent pointers |

---

### DE Shaw Q2 — Maximum Flips With All Prefix Sums Positive

Flip the sign of as many elements as possible while every prefix sum stays strictly positive.

::: keypoint
**The regret pattern.** Scan left to right. Flip every element **optimistically** as you meet it,
pushing its magnitude onto a max-heap. Whenever the running prefix sum drops to ≤ 0, **retract** the
single most damaging past decision: pop the largest flipped magnitude and un-flip it, which adds
back `2·x` — the most sum recoverable per retraction. Repeat until the prefix is positive again.
:::

```cpp
int maxFlips(const vector<long long> &a) {
    priority_queue<long long> flipped;   // magnitudes currently flipped
    long long running = 0;               // prefix sum with current decisions
    int count = 0;

    for (long long x : a) {
        running -= x;                    // flip it optimistically
        flipped.push(x);
        ++count;
        while (running <= 0) {           // infeasible: buy back the most sum per un-flip
            long long big = flipped.top();
            flipped.pop();
            running += 2 * big;          // -big becomes +big
            --count;
        }
    }
    return count;
}
```

**Why the greedy is correct.** The invariant maintained after processing prefix `i` is: *among all
valid sign assignments of the first `i` elements, this one has the maximum flip count, and among
those with maximum count, the maximum running sum.* Both halves matter — maximum sum is what keeps
future options open, and it is why we always retract the **largest** flipped element rather than
the most recent.

The exchange argument: retracting an element changes only the sum, never the count-by-one, so among
all single retractions that restore feasibility we should take the one that maximises the recovered
sum, i.e. the largest. And un-flipping an element helps *every* subsequent prefix equally, so a
retraction that fixes position i can never be regretted later. This is structurally identical to
**IPO** and **Course Schedule III** — the same "commit optimistically, retract the worst commitment
via a heap" shape.

::: trap
**`long long` is mandatory** and this is exactly the kind of overflow an OA punishes invisibly. With
`n = 2·10⁵` and `a_i ≤ 10⁹` the running sum reaches 2·10¹⁴ — about 10⁵ times past `int`. The code
compiles, runs, produces plausible small-case output, and fails hidden tests with no diagnostic
whatsoever. Note also `running += 2 * big` — if `big` were `int`, `2 * big` overflows *before* the
widening assignment.
:::

::: trap
**Strict vs. non-strict.** The loop condition is `while (running <= 0)`, enforcing every prefix
`> 0`. If the intended reading were `>= 0` the only change is `while (running < 0)`. One character;
half the test cases. When a statement says "positive", it means strictly — but if you have a custom
input panel, this is precisely the ambiguity to probe first (see the OA-debugging section).
:::

Complexity: **O(n log n)** time, **O(n)** space. Verified against exhaustive 2ⁿ search on 400 random
arrays.

---

### DE Shaw Q3 — Counting Checkerboard Subgrids

Count axis-aligned rectangles in a binary grid in which every orthogonally adjacent pair differs.

::: keypoint
**The transformation that collapses the problem.** A rectangle is a checkerboard iff
`g[i][j] = (i + j + c) mod 2` for a constant `c` throughout it. So define

```
b[i][j] = g[i][j] XOR ((i + j) & 1)
```

and a rectangle is a checkerboard **iff `b` is constant on it.** "Count checkerboard rectangles"
becomes "count constant-value rectangles" — a standard problem with a standard O(n·m) sweep. Finding
this XOR is the whole insight; everything after it is machinery you already know.
:::

The counting sweep is the classic histogram technique. For each cell, `h[i][j]` is how many rows
upward from row `i` share column `j`'s value. Then for each row, every rectangle with its
bottom-right corner at `(i, j)` is counted by the running "sum of minimum height over all subarrays
ending at `j`", maintained with a monotonic stack.

```cpp
    long long total = 0;
    vector<int> h(m, 0);            // h[j] = run of equal b upward in column j, ending at row i
    vector<int> stk(m), width(m);   // monotonic stack of (height, accumulated width)

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            h[j] = (i > 0 && b[i][j] == b[i - 1][j]) ? h[j] + 1 : 1;

        int top = 0;                // stack size
        long long sumMin = 0;       // sum of min-height over all subarrays ending at j
        for (int j = 0; j < m; ++j) {
            if (j > 0 && b[i][j] != b[i][j - 1]) { top = 0; sumMin = 0; }
            int w = 1;
            while (top > 0 && stk[top - 1] >= h[j]) {
                --top;
                w += width[top];
                sumMin -= (long long)stk[top] * width[top];
            }
            stk[top] = h[j];
            width[top] = w;
            ++top;
            sumMin += (long long)h[j] * w;
            total += sumMin;        // all rectangles whose bottom-right corner is (i,j)
        }
    }
```

**Why the stack reset is correct.** A rectangle may not straddle a colour change *within its own
bottom row*, so at every `b` boundary along row `i` the accumulated state is discarded. And the
correctness of the height-only test rests on a small argument worth stating: if column `j` has
constant `b` for the full height, **and** row `i` is constant across `[j₁, j₂]`, then every cell in
the rectangle equals `b[i][j₁]` — so constant columns plus one constant row is sufficient.

::: trap
**`long long` again, and here it is not marginal.** An all-checkerboard `n × m` grid contains
`n(n+1)/2 × m(m+1)/2` subgrids. At 2000 × 2000 that is `2001000² ≈ 4.004·10¹²` — three orders of
magnitude past `int`. Verified by running it: the program prints `4004001000000` on a 2000×2000
checkerboard, in 35 ms.
:::

The recalled figure from the original question — *"a checkerboard 3×3 has 36 subgrids"* — is
reproduced exactly by this program. That is a useful confirmation that the recalled statement was
faithful, since 36 = C(4,2)² is precisely "all rectangles of a 3×3 grid", which is what you expect
when every subgrid of a perfect checkerboard is itself a checkerboard.

Complexity: **O(n·m)** time and **O(m)** working space beyond the grid. Verified against an
O((nm)²) brute force on 250 random grids up to 6×6.

---

## Millennium — Coding Questions (formalized from recall)

**Provenance.** Both questions were written down from memory after the test, not photographed. The
raw recall is in `OA.txt`. Below, each is **formalized**: the remembered kernel is restated as a
precise problem with explicit input/output, constraints, edge cases and worked examples. Anything the
recall did not pin down — bounds, indexing, output format, tie-breaks — is chosen to give the
*intended* difficulty and flagged **[assumed]** so it is never mistaken for the original wording.

Same policy as the DE Shaw set: every solution here was compiled and run, and because there is no
official test data to trust, each was additionally cross-checked against independent brute force
before being written down.

---

### Q1 — Append-and-Reverse, Maximised

**Recall (verbatim):** *"given a binary string s, the following operation will be performed on it /
there will be an empty string b / for i= 0 to n-1, the ith element of s will be appended to b at the
end, and b will be reversed / mutate the string s such that the final b would be maximum"*

#### Formalized statement

You are given a binary string `s` of length `n`. The following process defines a string `b`:

```
b := ""                      (empty)
for i = 0 to n-1:
    b := b + s[i]            (append s[i] at the end of b)
    b := reverse(b)          (then reverse the whole of b)
```

You may **rearrange the characters of `s` arbitrarily** before the process runs — that is, replace
`s` by any permutation of its own characters. The multiset of characters is fixed; only their order
may change.

Find a rearrangement of `s` that makes the final `b` **lexicographically maximum**, and report both
the rearranged `s` and the resulting `b`.

**Input** — a single line containing the binary string `s`.

**Output** — two lines: the rearranged `s`, then the resulting maximal `b`.

**Constraints [assumed]**
```
1 <= n <= 10^5
s consists only of the characters '0' and '1'
```

::: prereqs
**[assumed] — the meaning of "mutate".** The recall's word is *mutate*, which is not precise. The
reading taken here is **"rearrange the characters"**, because it is the only reading under which the
question has content. Two alternatives were considered and rejected: *flipping* characters freely
makes the answer trivially `111…1`, and *no modification at all* leaves nothing to optimise. If the
original permitted a bounded number of flips or swaps, the structural analysis below is unchanged —
only the final selection step differs.
:::

#### Worked example

```
Input        Output
0110         0101
             1100
```

Trace the process on the rearranged `0101`:

| step | append | b after append | b after reverse |
|---|---|---|---|
| i=0 | `0` | `0` | `0` |
| i=1 | `1` | `01` | `10` |
| i=2 | `0` | `100` | `001` |
| i=3 | `1` | `0011` | `1100` |

Final `b = 1100`, which is the largest arrangement of two 1s and two 0s. ✓

#### The structure: it is a fixed permutation

Track where each *original index* lands. Simulating for the first few `n`:

```
n=1   [0]
n=2   [1, 0]
n=3   [2, 0, 1]
n=4   [3, 1, 0, 2]
n=5   [4, 2, 0, 1, 3]
n=6   [5, 3, 1, 0, 2, 4]
n=7   [6, 4, 2, 0, 1, 3, 5]
```

::: keypoint
**The pattern.** The final `b` reads: **all indices with the same parity as `n−1`, descending**,
followed by **all indices of the other parity, ascending**.

```
perm(n) = [n-1, n-3, n-5, …]  ++  [n mod 2, n mod 2 + 2, …]
```

The characters never influence where anything goes — the process is a permutation of *positions*,
identical for every input of the same length. That single observation collapses the problem.
:::

Why: each new character is appended, then everything flips. So the character added at step `i` is
pushed to whichever end is currently "the far side", and every previously placed character has its
side swapped. Characters therefore accumulate outward from the middle, alternating ends — which is
exactly the descending/ascending parity split read from outside in.

#### The consequence

A permutation is a **bijection**. So as `s` ranges over all its rearrangements, `b` ranges over
*exactly the same set* of rearrangements. Therefore:

- The maximum achievable `b` is simply **all 1s followed by all 0s** — no search required.
- The interesting half of the answer is producing the `s` that yields it, which is the **inverse
  permutation** applied to that target.

::: trap
**Do not simulate the reversals.** Reversing `b` on every iteration is O(n) per step and O(n²)
overall — at `n = 10⁵` that is 10¹⁰ character moves. The fix is to never reverse at all: keep a
deque and a `flipped` flag, appending to the back when upright and the front when flipped. The
reversal becomes a single bit-flip, and the whole simulation is O(n).
:::

#### Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

// O(n) simulation: instead of reversing, alternate which end we append to.
string transform_(const string &s) {
    deque<char> b;
    bool flipped = false;               // true => the logical string is reversed vs. the deque
    for (char c : s) {
        if (flipped) b.push_front(c);   // "append to the end" of a reversed view
        else         b.push_back(c);
        flipped = !flipped;             // the reversal itself is deferred into the flag
    }
    string out(b.begin(), b.end());
    if (flipped) reverse(out.begin(), out.end());
    return out;
}

// Position j of the final b is drawn from s[perm[j]].
vector<int> permOf(int n) {
    vector<int> p;
    p.reserve(n);
    for (int i = n - 1; i >= 0; i -= 2) p.push_back(i);   // parity of n-1, descending
    for (int i = n % 2; i < n; i += 2)  p.push_back(i);   // the other parity, ascending
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    int n = s.size();

    int ones = count(s.begin(), s.end(), '1');
    string best = string(ones, '1') + string(n - ones, '0');   // the maximum b

    // Invert the permutation to recover the s that yields it.
    vector<int> p = permOf(n);
    string mutated(n, '?');
    for (int j = 0; j < n; ++j) mutated[p[j]] = best[j];

    cout << mutated << '\n' << best << '\n';
    return 0;
}
```

**Verification.** Checked exhaustively against a literal simulator on **every** binary string of
length 1 through 14 (32,766 cases), asserting three separate properties: the reported `s` is a
rearrangement of the input, running the real process on it genuinely produces the reported `b`, and
that `b` equals the sorted-descending string. All pass.

::: interview
The parity formula was **wrong on the first attempt** — I wrote the second run as
`range(1 - n % 2, n, 2)` instead of `range(n % 2, n, 2)`, which silently emits index 0 twice for
`n = 1` and is off by one everywhere. It was caught immediately because the formula was checked
against the brute simulator rather than trusted. Closed-form index formulas derived by staring at a
table are exactly the kind of thing to verify mechanically: they are easy to get nearly right, and
"nearly right" here means a duplicated character and a dropped one.
:::

Complexity: **O(n)** time and space.

#### Edge cases worth naming
- `n = 1` — the single character is appended and reversed; `b = s`. The parity formula must not
  double-count index 0 here (see above).
- All zeros or all ones — output equals input; a good smoke test that the inverse permutation is not
  scrambling anything it should not.
- The two runs in `permOf` have **different lengths** when `n` is odd (`⌈n/2⌉` and `⌊n/2⌋`). Writing
  the loop bounds symmetrically is the natural mistake.

---

### Q2 — Shortest Walk Visiting All Task Nodes

**Recall (verbatim):** *"there is a bidirectional graph, there is a start node, end node, and a
finite task nodes, all edges carry 1 weight, you are supposed to find the shortest path from start
to end node by traversing all task nodes, you can visit a node more than once"*

#### Formalized statement

You are given an undirected, unweighted graph with `n` nodes and `m` edges (every edge has weight 1).
You are given a **start** node, an **end** node, and a set of `k` **task** nodes.

Find the length of the shortest **walk** that begins at start, ends at end, and passes through every
task node at least once. Nodes and edges may be reused any number of times. Print `-1` if no such
walk exists.

**Input**
```
n m
m lines: u v            (an undirected edge)
start end k
k node ids              (the task nodes; omitted/blank line when k = 0)
```
**Output** — a single integer: the length of the shortest such walk, or `-1`.

**Constraints [assumed]**
```
2 <= n <= 10^5
1 <= m <= 2 * 10^5
0 <= k <= 15
nodes are 0-indexed
```

::: prereqs
**[assumed] — the bound on `k` is the whole question.** The recall says only "a finite task nodes".
The problem is NP-hard in general (it contains the travelling salesman problem), so a solvable OA
version must bound `k` small enough for an exponential factor — `k ≤ 15` gives `2¹⁵ · 15² ≈ 7·10⁶`,
comfortable. **If you see a problem of this shape, the constraint on the number of required nodes is
the first thing to read**: it tells you immediately whether the intended solution is bitmask DP.
:::

#### Worked example

```
Input           Output
6 6             5
0 1
1 2
2 3
1 4
4 5
5 3
0 3 2
2 4
```

The graph:

```
0 — 1 — 2 — 3
    |       |
    4 — 5 ——
```

Walk from 0 to 3 covering both 2 and 4. The optimum is `0 → 1 → 4 → 1 → 2 → 3`: length **5**. Note
that it **revisits node 1** — the detour to task node 4 is made by going out and coming straight
back. That is legal here, and it is precisely why this is a *walk* problem rather than a path
problem: forbidding revisits would make this exact route illegal and the answer larger.

::: interview
**This example was wrong when first written**, and the error is worth keeping. I wrote the answer as
6, from the route `0 → 1 → 4 → 5 → 3 → 2 → 3`, because I had hand-computed `d(4, 2) = 3` — going
`4 → 5 → 3 → 2` around the cycle. But `4 → 1 → 2` is only 2 steps. I had latched onto one route
through the graph and never looked for a shorter one.

That is the *characteristic* hand-computation error on graph problems: distances are easy to
over-estimate because you find *a* path and stop. It is also invisible on inspection — the wrong
answer, 6, is perfectly plausible, corresponds to a real walk, and is only one more than the truth.
Run a BFS instead of eyeballing it.
:::

#### Why this decomposes

::: keypoint
**Between milestones, always take a shortest path.** Because revisiting is allowed, the walk imposes
no constraint linking one leg to the next — you may re-enter any node freely. So a walk visiting the
tasks in a given order has length at least the sum of the shortest-path distances between
consecutive milestones, and that bound is achieved by simply concatenating those shortest paths.

Therefore: **optimum = min over orderings of the tasks, of the sum of pairwise shortest paths**, from
start, through the tasks in that order, to end. The graph collapses to a `(k+2) × (k+2)` distance
matrix, and what remains is a travelling-salesman path problem on it.
:::

That reduction is the entire insight. It fails the moment revisits are forbidden — then the legs
interact, and the problem becomes far harder. The recall's *"you can visit a node more than once"* is
therefore not a throwaway permission, it is the clause that makes the problem tractable.

So the solution is two standard stages:

1. **BFS from each of the `k+2` milestone nodes** (unit weights, so BFS is the shortest-path
   algorithm; Dijkstra is unnecessary overhead). Gives the dense distance matrix.
2. **Bitmask DP** over subsets of tasks: `dp[mask][i]` = shortest walk from start that has covered
   the task set `mask` and currently stands on task `i`.

#### Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<int> bfs(int src, const vector<vector<int>> &g) {
    vector<int> d(g.size(), INF);
    d[src] = 0;
    queue<int> q;
    q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u])
            if (d[v] == INF) { d[v] = d[u] + 1; q.push(v); }
    }
    return d;
}

int solve(int n, const vector<pair<int,int>> &edges, int start, int end_, vector<int> tasks) {
    vector<vector<int>> g(n);
    for (auto &e : edges) {
        g[e.first].push_back(e.second);
        g[e.second].push_back(e.first);      // bidirectional
    }

    // Milestones: index 0..k-1 = tasks, k = start, k+1 = end.
    int k = tasks.size();
    vector<int> node = tasks;
    node.push_back(start);
    node.push_back(end_);

    vector<vector<int>> dist(k + 2);
    for (int i = 0; i < k + 2; ++i) {
        vector<int> d = bfs(node[i], g);
        dist[i].resize(k + 2);
        for (int j = 0; j < k + 2; ++j) dist[i][j] = d[node[j]];
    }

    // Unreachable milestone => no such walk exists.
    for (int j = 0; j < k + 2; ++j)
        if (dist[k][j] >= INF) return -1;

    if (k == 0) return dist[k][k + 1];

    // dp[mask][i] = shortest walk from start covering `mask`, currently standing on task i.
    vector<vector<int>> dp(1 << k, vector<int>(k, INF));
    for (int i = 0; i < k; ++i) dp[1 << i][i] = dist[k][i];

    for (int mask = 1; mask < (1 << k); ++mask)
        for (int i = 0; i < k; ++i) {
            if (dp[mask][i] >= INF || !(mask >> i & 1)) continue;
            for (int j = 0; j < k; ++j) {
                if (mask >> j & 1) continue;
                int nxt = dp[mask][i] + dist[i][j];
                if (nxt < dp[mask | 1 << j][j]) dp[mask | 1 << j][j] = nxt;
            }
        }

    int best = INF;
    for (int i = 0; i < k; ++i)
        if (dp[(1 << k) - 1][i] < INF)
            best = min(best, dp[(1 << k) - 1][i] + dist[i][k + 1]);
    return best >= INF ? -1 : best;
}
```

**Verification.** Cross-checked on **500 random graphs** (including disconnected ones, `k = 0`, and
cases where start/end are themselves task nodes) against **two independent methods** that share no
code with it:

1. a BFS over the expanded state space `(node, visited-task bitmask)`, and
2. an all-pairs BFS followed by trying literally every permutation of the task order.

All three agree on every case.

#### The alternative solution, and when to prefer it

The state-space BFS used as a cross-check is a legitimate solution in its own right: run a plain BFS
where a state is `(node, mask of tasks visited so far)`, and stop at `(end, full mask)`. Since every
edge costs 1, BFS finds the optimum directly with no DP.

| | milestone BFS + bitmask DP | BFS over `(node, mask)` |
|---|---|---|
| time | `O((k+2)(n+m) + 2ᵏ k²)` | `O((n + m) · 2ᵏ)` |
| memory | `O(2ᵏ k)` | `O(n · 2ᵏ)` |
| best when | `n` large, `k` small | `n` small, or you want less code |

At `n = 10⁵` and `k = 15`, the state space is 3.3·10⁹ states — far too much memory, so the DP is the
right choice at the assumed bounds. But the state-space BFS is shorter, harder to get wrong, and is
what I would reach for first if `n` were small. Knowing both, and knowing which constraint decides
between them, is the actual skill being tested.

::: trap
**Unit weights mean BFS, not Dijkstra.** Reaching for a priority queue here costs a `log` factor and
more code for nothing. The recall explicitly says *"all edges carry 1 weight"* — that clause exists
to tell you which algorithm to use, in the same way the revisit clause tells you the problem
decomposes. Statement clauses that look like flavour are usually load-bearing.
:::

#### Edge cases worth naming
- **`k = 0`** — the answer is just the plain BFS distance from start to end. The DP must be skipped
  entirely, since `1 << 0 == 1` gives a degenerate loop and the "min over final tasks" is empty.
- **start or end is itself a task node** — handled for free: it enters the matrix as a milestone and
  the DP visits it like any other. Do not special-case it.
- **`start == end`** — legal; the walk must still cover every task and come back.
- **Unreachable task** — must print `-1`, not a huge number. Checking reachability once from start
  covers every case, since the graph is undirected: if start cannot reach a milestone, no walk can.
- **Disconnected graph** — the same check handles it.

---

### What these two share

Both questions are **"the operation described is not the operation to implement"**:

- Q1 describes an O(n²) simulation with a reversal in the inner loop. The real content is that the
  process is a content-independent permutation, which makes both the simulation O(n) and the
  optimisation a one-liner.
- Q2 describes a walk that seems to demand a search over routes. The real content is that permitting
  revisits makes the legs independent, collapsing the graph to a small distance matrix.

In both cases the literal reading is a correct but hopeless algorithm, and the reframing is worth
more than any amount of optimisation applied to the naive version. This is the same house style as
the DE Shaw set — see the closing note there — and it is why *reading the constraints before writing
code* keeps being the highest-value habit on these tests.

## Uber — Coding Questions (formalized from recall)

**Provenance.** All three were written down from memory after the test, not photographed. The raw
recall is in `oA.txt`. Below, each is **formalized**: the remembered kernel is restated as a precise
problem with explicit input/output, constraints, edge cases and worked examples. Anything the recall
did not pin down — bounds, indexing, the exact penalty rule, the exact operation — is chosen and
flagged **[assumed]**, and where a phrase admits two genuinely different problems both are worked out
and the ambiguity is **resolved with running code** rather than a guess.

Same policy as the DE Shaw and Millennium sets: every solution here was compiled and run, and because
there is no official test data to trust, each was cross-checked against independent brute force —
exhaustively where the input space allowed it, on thousands of random cases otherwise.

::: keypoint
**Two of these three hinge on an ambiguous phrase**, and in an OA you cannot ask the invigilator.
The discipline that replaces asking is: enumerate the readings, implement each, and let a brute-force
oracle tell you which one produces clean structure (a formula, a contiguous range, a matching). The
intended reading is almost always the one whose answer is *elegant* — OA authors do not set problems
whose answer is an accident. That heuristic is applied explicitly below.
:::

---

### Q1 — Minimum Penalty String Partition

**Recall (verbatim):** *"we were given a string s, a duplicatePenalty, and a segmentPenalty / every
element that is same as its adjacent would have a penalty of duplicate penalty, and we can split it
with segment penalty, we have to find the minimum penalty for the entire string"* — and the candidate
adds: *"i tried dp with i and j, partition dp"*.

#### Formalized statement

You are given a string `s`, an integer `duplicatePenalty` `D`, and an integer `segmentPenalty` `Seg`.
You may cut `s` into contiguous segments; **each cut costs `Seg`**. Within a segment, adjacent equal
characters incur a `duplicatePenalty`. Splitting between two equal characters separates them, so they
no longer share a segment and no longer incur that penalty. Minimise the total penalty.

**Input**
```
s D Seg
```
**Output** — a single integer: the minimum achievable total penalty.

**Constraints [assumed]**
```
1 <= |s| <= 10^5
0 <= D, Seg <= 10^9      (answer can exceed 32 bits -> long long)
```

#### The ambiguity, and why it decides the whole problem

The phrase *"every element that is same as its adjacent"* has two honest readings, and they are
**different problems with different optimal algorithms**:

::: trap
**Reading A — penalty per adjacent-equal *pair*.** The boundary between positions `i` and `i+1`
costs `D` if `s[i]==s[i+1]` and they stay in one segment. Then each boundary is **independent**: for
every equal boundary you either pay `D` to keep it or `Seg` to cut it, so the answer is simply

```
sum over equal boundaries of  min(D, Seg)
```

This is an **O(n) greedy** — no DP at all. Verified against brute-force partitioning on 1500 random
cases.

**Reading B — penalty per *element* that has an equal neighbour.** Now a run of `k` equal characters
inside a segment costs `k·D` (each of the `k` characters is "same as its adjacent"), and a run of
length 1 costs nothing. This is **non-linear in the run length**, so boundaries no longer separate:
whether cutting a run helps depends on the sizes of the two resulting pieces. Greedy is **wrong here
— it disagrees with the optimum on 21% of random cases** — and you need exactly the **O(n²) partition
DP** the candidate reached for.
:::

::: keypoint
**The candidate's own note resolves the ambiguity.** They tried "dp with i and j, partition dp". A
partition DP is only *necessary* under Reading B — under Reading A it is correct but pointless, since
the problem separates. The fact that the intended solution is a partition DP is itself evidence that
the penalty is the per-element (run-based) Reading B. So B is taken as primary; A is kept because
recognising that it collapses to O(n) is worth marks if the penalty turns out to be pair-based.
:::

#### Solution (both readings, one program)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solveA(const string &s, ll D, ll Seg) {          // greedy: each equal boundary independently
    ll total = 0;
    for (size_t i = 0; i + 1 < s.size(); ++i)
        if (s[i] == s[i + 1]) total += min(D, Seg);
    return total;
}

ll runCostB(const string &s, int i, int j, ll D) {  // per-element run cost of segment s[i..j]
    ll c = 0;
    int p = i;
    while (p <= j) {
        int q = p;
        while (q + 1 <= j && s[q + 1] == s[p]) ++q;
        int len = q - p + 1;
        if (len >= 2) c += (ll)len * D;
        p = q + 1;
    }
    return c;
}

ll solveB(const string &s, ll D, ll Seg) {          // dp[i] = min penalty for suffix s[i..]
    int n = s.size();
    vector<ll> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        ll best = LLONG_MAX;
        for (int j = i; j < n; ++j) {               // segment s[i..j]
            ll add = (i > 0) ? Seg : 0;             // every segment but the first is preceded by a cut
            best = min(best, add + runCostB(s, i, j, D) + dp[j + 1]);
        }
        dp[i] = best;
    }
    return dp[0];
}
```

Both `solveA` and `solveB` were checked against a brute force that tries all `2^(n-1)` cut sets: they
agree with the optimum on every one of 1500 random `(s, D, Seg)` triples (A for the pair reading, B
for the run reading).

::: trap
**The DP as written is O(n²), which is fine for `n ≤ 10³` but not `10⁵`.** The inner `runCostB`
recomputes from scratch; folding the run bookkeeping into the `j` loop makes each `dp[i]` an O(n)
sweep with O(1) work per step, keeping the whole thing O(n²) but with a tiny constant — and if the
real constraint is `n ≤ 10⁵`, the problem almost certainly intends Reading A (the O(n) greedy) after
all, since no O(n²) DP survives `10⁵`. **The constraint you are given retroactively disambiguates the
penalty rule**: a large `n` means pairs (greedy); a small `n` means the run-based DP is expected.
This is the single most useful thing to notice under time pressure.
:::

#### Worked example

```
s = "aab",  D = 5,  Seg = 3
```
One equal boundary (the `aa`). Reading A: `min(5,3) = 3`. Reading B: keep `aab` whole → run `aa`
costs `2·5 = 10`; or cut to `a|ab` → `Seg=3` + run `a`,`ab` cost 0 → `3`. Both give **3** here because
the run has length 2. They diverge on longer runs, e.g. `s="aaaa", D=1, Seg=10`: A pays
`3·min(1,10)=3`; B keeps it whole for `4·1=4` vs any cut ≥ `10`, so B pays **4**.

#### Edge cases worth naming
- Runs of length ≥ 3 are where A and B separate — always test `"aaa"` or longer.
- `Seg = 0` — cut everywhere free; both readings give 0.
- `D = 0` — never worth cutting; answer 0.
- `|s| = 1` — no boundaries, no runs; answer 0.

---

### Q2 — Bundling Toward a Target: Which Min-Counts Work?

**Recall (verbatim):** *"there was a set of 2n numbers from 1 to 2n, we had to make n bundles of two
elements each, and there is a target array of elements to be formed / within a bundle we can pick
either its min element or its max element, for example 1 3 5 is the target array, we can make bundles
from target.size()*2, so 1 to 6, now we can bundle it like this, (1,4), (3,2), (5,6) such that … pick
min from bundles 1 and 3, and max from bundle 2, so that will give the target array … that meant we
picked min in 2 bundles … can you make the target array using 2 min bundle picking, 1 min bundle rest
max, 4 min rest max, etc"*

#### Formalized statement

The numbers `1, 2, …, 2n` are to be partitioned into `n` unordered **bundles** of two numbers each.
From each bundle you take either its **minimum** or its **maximum**. You are given a **target** array
`T` of `n` distinct values drawn from `1…2n`; the multiset of taken values must equal `T`.

For each `x ∈ {0, 1, …, n}`, decide whether the target can be produced while taking the **min** from
**exactly `x`** bundles (and the max from the other `n − x`). Report the set of feasible `x`.

**Input**
```
n
T[0] T[1] … T[n-1]        (n distinct integers in 1..2n)
```
**Output** — the feasible values of `x`. (As shown below they always form a contiguous range, so it
suffices to print `xmin xmax`.)

**Constraints [assumed]**
```
1 <= n <= 10^5
T contains n distinct values, each in 1..2n
```

#### The reduction that makes it easy

::: keypoint
**Every bundle is one target value plus one non-target value.** The value you *take* is a target;
the value you *discard* is therefore a non-target (if you discarded a target, that target would be
missing from the result). So a valid bundling is exactly a **perfect matching between the target set
`T` and its complement `C = {1…2n} \ T`**, and for a matched pair `(t, c)`:

```
you took the MIN of that bundle  ⟺  its discarded partner c > t
you took the MAX of that bundle  ⟺  its discarded partner c < t
```

So `x` = the number of matched pairs with `c > t`. The question "which `x` are feasible" becomes
"over all perfect matchings between `T` and `C`, what values can `#{c > t}` take?"
:::

#### The structure (found by brute force, then proved)

Enumerating every matching for all targets up to `2n = 8` shows two facts, both of which then have
one-line proofs:

1. **The feasible `x` form a contiguous range `[xmin, xmax]`.** *Proof:* take any matching and swap
   the partners of two targets; each swap changes `#{c>t}` by at most 1, and you can transform any
   matching into any other by such swaps, so no achievable value in between can be skipped.
2. **The endpoints are computed by a greedy two-pointer**, the classic "maximise pairs with `c > t`"
   matching:
   - `xmax` = maximum number of pairs with `c > t`: scan `C` ascending; each `c` satisfies the
     smallest still-unmatched `t < c`.
   - `below` = maximum number of pairs with `c < t` (same greedy, mirrored); then
     `xmin = n − below`.

Every target is feasible for *some* `x` (a perfect matching always exists), so the range is never
empty.

#### Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;                  // n = |target|,  universe is 1..2n
    vector<int> T(n);
    vector<char> inT(2 * n + 1, 0);
    for (int &t : T) { cin >> t; inT[t] = 1; }
    sort(T.begin(), T.end());

    vector<int> C;                              // complement, ascending
    for (int v = 1; v <= 2 * n; ++v) if (!inT[v]) C.push_back(v);

    // xmax = max pairs with c > t : for each c ascending, satisfy the smallest unmet t < c.
    int xmax = 0;
    for (int i = 0, ci = 0; ci < (int)C.size(); ++ci)
        if (i < n && T[i] < C[ci]) { ++xmax; ++i; }

    // max pairs with c < t : for each t ascending, consume the smallest unused c < t.
    int below = 0;
    for (int j = 0, ti = 0; ti < n; ++ti)
        if (j < (int)C.size() && C[j] < T[ti]) { ++below; ++j; }
    int xmin = n - below;

    cout << xmin << ' ' << xmax << '\n';        // every x in [xmin, xmax] is achievable
    return 0;
}
```

**Verification.** The greedy endpoints were checked against a brute force that enumerates **every**
perfect matching, for **every** target set at `2n ∈ {2,4,6,8}` — endpoints match in all cases, and
the achievable set is contiguous in all cases.

#### Worked example (the recall's own)

```
Input        Output
3            1 3
1 3 5
```
`T = {1,3,5}`, `C = {2,4,6}`. The recall's bundling `(1,4),(3,2),(5,6)` takes min, max, min → `x = 2`,
and indeed `2 ∈ [1, 3]`. The extremes: `x = 3` (all min) via `(1,2),(3,4),(5,6)`; `x = 1` (one min)
via `(1,6),(2,3)`→take 3 as max,`(4,5)`→take 5 as max, i.e. matching `1→6, 3→2, 5→4` gives
`c>t` only for the first pair. ✓

::: trap
**"min in exactly x bundles" is a real constraint, not a formality.** A candidate who only checks
"can the target be formed at all" answers a strictly easier question and fails every hidden test that
pins a specific `x`. The whole content is the *count*, which is why the reduction to "number of
above-partners in a matching" is the crux — miss it and you are enumerating pairings.
:::

#### Edge cases worth naming
- Target `= {1,2,…,n}` (the `n` smallest): every partner is larger, so `xmin = xmax = n` — only
  all-min works.
- Target `= {n+1,…,2n}` (the `n` largest): every partner is smaller, `xmin = xmax = 0`.
- `n = 1`: `T = {1}` → `x = 1`; `T = {2}` → `x = 0`.

---

### Q3 — Distinct Strings After One Substring Flip

**Recall (verbatim):** *"there is a string of 0s and 1s, we can flip any consecutive subset of that
string, we have to find out the number of different strings that we can form"*

#### Formalized statement

You are given a binary string `s`. You may choose one contiguous substring and **flip** it (complement
every bit: `0↔1`) — **at most once**. How many distinct strings can result (counting `s` itself, the
result of flipping nothing)?

**Input** — the binary string `s`. **Output** — one integer.

**Constraints [assumed]** `1 <= |s| <= 10^6`.

#### Resolving the operation and the number of operations

*"Flip any consecutive subset"* is ambiguous in two axes; both were settled by enumeration:

::: keypoint
**How many operations?** If flips may be applied **any number of times**, a single-character block is
itself a legal flip, and single-character flips generate every binary string — the answer would be a
trivial `2^n`, independent of `s`. That is too trivial to be the intended question, so the operation
is applied **at most once**.

**Flip = complement, not reverse.** For a binary string "flip" standardly means complement. (Reversing
one substring instead gives a genuinely different, content-*dependent* count; it is noted below as the
alternative, but "flip" is taken as complement.)
:::

Under "complement one substring, at most once", something clean happens:

::: keypoint
**The answer is `1 + n(n+1)/2`, independent of the contents of `s`.** Flipping block `[i,j]` is XOR
with the mask that is 1 exactly on `[i,j]`. Distinct blocks give distinct masks, distinct masks give
distinct results, and no non-empty mask can leave `s` unchanged. So the `n(n+1)/2` substrings produce
`n(n+1)/2` **pairwise-distinct** strings, all different from `s`; adding the do-nothing option gives
`1 + n(n+1)/2`. The characters of `s` never enter the count.
:::

That content-independence *is the question*. It rewards the candidate who proves it and returns the
formula in O(1), and it punishes the two natural wrong turns: enumerating results into a hash set
(O(n²) strings, MLE/TLE), or assuming multiple flips and printing `2^n`.

#### Solution

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    long long n = s.size();
    cout << 1 + n * (n + 1) / 2 << '\n';
    return 0;
}
```

**Verification.** Checked against an explicit enumerator (flip every substring, collect into a set) for
**every** binary string of length 1 through 12 — the formula matches the true distinct-count in all
`Σ 2^n` cases, confirming both the value and its independence from content.

::: trap
**`long long` is mandatory.** At `n = 10⁶`, `n(n+1)/2 ≈ 5·10¹¹` — forty times past 32-bit range. The
program is three lines and still has an overflow trap in it: `n * (n + 1)` overflows `int` long before
the division. Read `n` into a 64-bit type *before* multiplying.
:::

#### If "flip" actually meant reverse

If the operation reverses a substring rather than complementing it, the count becomes
content-dependent (e.g. `"0110"`, `"0011"`, `"0101"` each yield 5 distinct results at `n = 4`, while
`"00100"` yields 5 and `"001011"` yields 10). That problem is a harder distinct-counting exercise —
you must avoid double-counting reversals that produce identical strings. It is flagged here only so
that, if a sample output disagrees with `1 + n(n+1)/2`, you immediately know to switch to the reverse
interpretation rather than hunt for a bug in correct code.

---

### What these three share

Two of the three turn on a **single ambiguous word**, and the method for resolving ambiguity without
being able to ask is the real lesson:

- **Q1** — *"same as its adjacent"* is pair-based or element-based; the two give O(n) greedy vs O(n²)
  DP. The candidate's own instinct to write a partition DP is the evidence that fixes the reading, and
  the `n` bound would confirm it.
- **Q3** — *"flip any consecutive subset"* is complement-vs-reverse and once-vs-many; three of the
  four combinations are trivial or content-independent, and the elegant content-independent formula is
  the tell that you have found the intended one.
- **Q2** is unambiguous once you see that a bundle is a (target, non-target) pair — after which the
  whole problem is "how many above-partners can a matching have", answered by a two-pointer.

The through-line with the DE Shaw and Millennium sets holds: **the literal statement is rarely the
problem**, and on a test with no visible cases, the reading whose answer is *clean* — a formula, a
contiguous range, a separable greedy — is almost always the intended one. Elegance is a debugging
signal.

### What the twelve have in common

Sorted by what they actually test:

- **Q1 Golden Price, Flipkart SQL** — *read the definition exactly.* Both are easy once the
  predicate is parsed correctly and both are lost by parsing it loosely.
- **Q2 Marathon, DE Shaw Q3, Millennium Q1** — *find the reframing.* Path-strings-as-addresses and the XOR parity
  mask, and append-and-reverse-as-a-fixed-permutation, each turn a structural problem into a
  lookup problem. Neither needs a clever algorithm after
  the reframing; both are painful without it.
- **Q4 Logistics** — *fidelity under volume.* No insight required, twenty places to be wrong.
- **DE Shaw Q1, DE Shaw Q2, Millennium Q2** — *the constraint bound tells you the algorithm.* The
  statement literally describes an O(n) per-operation method; the bounds say that is 4·10¹⁰
  operations. Millennium Q2 is the same lesson in reverse — the bound on the number of task nodes
  is what reveals an exponential factor is not merely allowed but intended. Read the bound before
  writing code.
- **Uber Q1, Uber Q3** — *resolve the ambiguous word.* "Same as its adjacent" and "flip any
  consecutive subset" each admit two problems with different optimal algorithms. With no invigilator
  to ask, the reading whose answer is *clean* — a separable greedy, a content-independent formula — is
  the intended one, and the candidate's own instinct (a partition DP) can be the evidence that fixes
  it. Uber Q2 is the reframing lesson again: a bundle is a (target, non-target) pair, and the rest is
  a two-pointer.

::: interview
In every one of these, the failure is silent. There is no visible test case, no stack trace, no
partial credit signal — a TLE, an overflow and a misread rule all present identically as "wrong
answer". That is what makes the bound-reading, the definition-parsing, and the deliberate resolution
of ambiguous wording worth doing *before* you type, and it is the subject of the next section.
:::
