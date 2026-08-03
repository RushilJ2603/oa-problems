A manufacturing company wants to identify machines that may require urgent maintenance.

The company records machine details, machine-type operating limits, sensor readings, maintenance logs and fault events. Your task is to analyse the available data and print machines whose maintenance risk level is `HIGH` or `MEDIUM`.

### Data Structures

**Machines Table**: `machineId` (unique identifier), `machineName`, `machineType` (such as PRESS, CUTTER, WELDER or PACKER).

**Machine Type Profiles Table**: `machineType`, `maxTemperature`, `maxVibration`. Every `machineType` present in the Machines table has exactly one matching record here.

**Sensor Readings Table**: `readingId`, `machineId`, `readingDay`, `temperature`, `vibration`.

**Maintenance Logs Table**: `maintenanceId`, `machineId`, `maintenanceDay`, `maintenanceType` (PREVENTIVE or CORRECTIVE).

**Fault Events Table**: `eventId`, `machineId`, `eventDay`, `severity` (LOW, MEDIUM or HIGH).

### Valid Record Rules

A **sensor reading** is valid only when all of the following hold:

1. Its `machineId` exists in the Machines table.
2. Its `readingDay` is between `1` and `referenceDay`, inclusive.
3. Its `temperature` is greater than or equal to `0`.
4. Its `vibration` is greater than or equal to `0`.

A **maintenance log** is valid only when all of the following hold:

1. Its `machineId` exists in the Machines table.
2. Its `maintenanceType` is `PREVENTIVE` or `CORRECTIVE`.
3. Its `maintenanceDay` is between `1` and `referenceDay`, inclusive.

A **fault event** is valid only when all of the following hold:

1. Its `machineId` exists in the Machines table.
2. Its `severity` is `LOW`, `MEDIUM` or `HIGH`.
3. Its `eventDay` is between `1` and `referenceDay`, inclusive.

Invalid records must be ignored completely. Every input record must be processed independently: if identical records appear more than once, each occurrence must be counted separately.

### Features to Calculate

For every machine, calculate the following using only valid records. `//` denotes integer (floor) division.

1. **validReadingCount**: the number of valid sensor readings for the machine.
2. **averageTemperature** = total valid temperature values `//` validReadingCount. If `validReadingCount` is `0`, it is `0`.
3. **averageVibration** = total valid vibration values `//` validReadingCount. If `validReadingCount` is `0`, it is `0`.
4. **temperatureBreachCount**: valid readings for which `temperature > maxTemperature`.
5. **vibrationBreachCount**: valid readings for which `vibration > maxVibration`.
6. **latestMaintenanceDay**: the latest `maintenanceDay` among valid maintenance logs.
7. **daysSinceMaintenance** = `referenceDay - latestMaintenanceDay`. If there is no valid maintenance log, `daysSinceMaintenance = referenceDay + 1`.
8. **highSeverityFaultCount**: valid fault events whose severity is `HIGH`.
9. **machineTypeAverageTemperature** = total temperature of all valid readings of that machine type `//` total valid reading count of that machine type. This uses individual valid readings, not an average of machine averages. If a machine type has no valid readings, it is `0`.
10. A machine is **above the temperature baseline** when `validReadingCount > 0` AND `averageTemperature > machineTypeAverageTemperature`.

### Maintenance Risk Score

| Condition | Score Added |
| --- | --- |
| daysSinceMaintenance >= 90 | 4 |
| There is no valid maintenance log | 3 |
| temperatureBreachCount >= 2 | 3 |
| vibrationBreachCount >= 2 | 3 |
| highSeverityFaultCount >= 1 | 3 |
| The machine is above the temperature baseline | 2 |
| validReadingCount > 0 and averageVibration > maxVibration | 2 |

The final score is the sum of all conditions that apply.

### Maintenance Risk Level

| Risk Score | Risk Level |
| --- | --- |
| 10 or more | HIGH |
| 6 to 9 | MEDIUM |
| Less than 6 | LOW |

Only machines with `HIGH` or `MEDIUM` risk must be printed.

### Input Format

The first line contains an integer `referenceDay`, the fixed day on which maintenance risk is analysed. The second line contains the number of records in the Machines table, the third the number in the Machine Type Profiles table, the fourth the number in the Sensor Readings table, the fifth the number in the Maintenance Logs table, and the sixth the number in the Fault Events table. The records then follow in this order:

1. Machines table: `machineId machineName machineType`
2. Machine Type Profiles table: `machineType maxTemperature maxVibration`
3. Sensor Readings table: `readingId machineId readingDay temperature vibration`
4. Maintenance Logs table: `maintenanceId machineId maintenanceDay maintenanceType`
5. Fault Events table: `eventId machineId eventDay severity`

### Output Format

Print all eligible machines in the format `MachineName-RiskLevel-RiskScore-DaysSinceMaintenance`. If multiple machines must be displayed, separate their details using a hash symbol (`#`).

Sort the output using the following sequence, applying the next condition only when the previous one ties:

1. `HIGH` risk machines before `MEDIUM` risk machines.
2. Higher `riskScore` first.
3. Higher `daysSinceMaintenance` first.
4. Original input sequence of the Machines table.

Print `NA` if no machine has `HIGH` or `MEDIUM` risk.

### Constraints

- `2 <= numberOfMachines <= 100000`
- `1 <= numberOfMachineTypeProfiles <= 100`
- `0 <= numberOfSensorReadings <= 200000`
- `0 <= numberOfMaintenanceLogs <= 200000`
- `0 <= numberOfFaultEvents <= 200000`
- `1 <= referenceDay <= 1000000`
- `-1000000 <= readingDay, maintenanceDay, eventDay <= 1000000`
- `-1000000000 <= temperature, vibration <= 1000000000`
- All IDs, names, machine types, maintenance types and severity values contain no spaces.

### Example 1

Input:
```
200
3
2
4
2
1
M1 Press_A PRESS
M2 Press_B PRESS
M3 Cutter_A CUTTER
PRESS 80 50
CUTTER 70 40
R1 M1 150 85 55
R2 M1 160 90 60
R3 M2 190 70 40
R4 M3 150 75 35
MT1 M1 100 PREVENTIVE
MT2 M2 195 PREVENTIVE
F1 M1 170 HIGH
```

Output:
```
Press_A-HIGH-17-100#Cutter_A-MEDIUM-7-201
```

For *Press_A*: temperatureBreachCount = 2, vibrationBreachCount = 2, daysSinceMaintenance = 200 - 100 = 100, highSeverityFaultCount = 1, averageTemperature = (85 + 90) // 2 = 87, machineTypeAverageTemperature for PRESS = (85 + 90 + 70) // 3 = 81, averageVibration = (55 + 60) // 2 = 57. Press_A is above its machine-type temperature baseline, so riskScore = 4 + 3 + 3 + 3 + 2 + 2 = 17.

For *Cutter_A* there is no valid maintenance log, so daysSinceMaintenance = 200 + 1 = 201 and riskScore = 4 + 3 = 7. Press_A is printed before Cutter_A because HIGH risk machines come before MEDIUM risk machines.

### Example 2

Input:
```
120
4
2
6
4
4
M1 Alpha_PRESS PRESS
M2 Beta_PRESS PRESS
M3 Gamma_WELDER WELDER
M4 Delta_WELDER WELDER
PRESS 80 50
WELDER 90 60
R1 M1 110 70 40
R2 M2 121 95 70
R3 M3 50 -1 20
R4 X9 50 100 70
R5 M4 100 85 55
R6 M4 101 95 65
MT1 M1 115 PREVENTIVE
MT2 M2 121 PREVENTIVE
MT3 M3 40 REPAIR
MT4 M4 20 CORRECTIVE
F1 M2 100 HIGH
F2 M3 121 HIGH
F3 X9 100 HIGH
F4 M4 110 HIGH
```

Output:
```
Beta_PRESS-HIGH-10-121#Gamma_WELDER-MEDIUM-7-121#Delta_WELDER-MEDIUM-7-100
```

The sensor reading of Beta_PRESS on day 121 is invalid because it is later than referenceDay 120. The sensor reading of Gamma_WELDER is invalid because its temperature is negative. The fault event for Gamma_WELDER is invalid because its event day is later than referenceDay. The maintenance record for Gamma_WELDER is invalid because REPAIR is not a valid maintenance type. Gamma_WELDER is printed before Delta_WELDER because both are MEDIUM with the same score, but Gamma_WELDER has more days since maintenance.
