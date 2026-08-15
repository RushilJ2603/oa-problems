A railway company operates multiple train lines across the United States.

Each train line has:
- a unique line name, and
- an ordered list of cities that the train visits.

A passenger may:
- Travel between adjacent cities on the same train line in either direction.
- Transfer from one train line to another only at a city that appears in both train lines.
- Make any number of transfers.

You are given a list of available train lines. You are also given multiple travel queries. Each query consists of a source city and a destination city.

For every query, determine whether it is possible to travel from the source city to the destination city using the available train lines. Return an array of booleans where the i-th element is `true` if the i-th query is possible, and `false` otherwise.

### Input Format
The first line contains an integer `L`, the number of train lines.
The next `L` lines describe the train lines. Each line starts with a string representing the `lineName`, followed by an integer `K` (the number of stations on this line), and then `K` strings representing the names of the stations in order.
The next line contains an integer `Q`, the number of queries.
The next `Q` lines each contain two strings, representing the source city and the destination city for that query.

### Output Format
Output `Q` space-separated strings, each either `true` or `false`, representing the answer to each query.

### Constraints
- $1 \le \text{number of train lines} \le 10^4$
- $1 \le \text{number of stations per line} \le 10^3$
- The total number of station occurrences across all train lines does not exceed $2 \times 10^5$.
- $1 \le \text{number of queries} \le 2 \times 10^5$
- Every train line has a unique name.
- Station names are case-sensitive strings consisting of English letters and underscores.
- A city may belong to multiple train lines.
- A query may contain cities that do not appear in any train line.

### Example 1
**Input**
```
3
Northeast_Corridor 5 Boston Providence New_York Philadelphia Washington_DC
Capitol_Limited 4 Washington_DC Pittsburgh Cleveland Chicago
Pacific_Surfliner 4 San_Diego Los_Angeles Santa_Barbara San_Luis_Obispo
4
Boston Chicago
Boston Los_Angeles
San_Diego Santa_Barbara
Chicago Philadelphia
```
**Output**
```
true false true true
```
**Explanation**
- Boston to Chicago: Reachable by transferring at Washington DC.
- Boston to Los Angeles: No train line connects the eastern and western networks.
- San Diego to Santa Barbara: Both cities are on the Pacific Surfliner.
- Chicago to Philadelphia: Travel via Capitol Limited to Washington DC, then transfer to Northeast Corridor.

### Example 2
**Input**
```
3
Empire_Builder 4 Seattle Spokane Minneapolis Chicago
Lake_Shore_Limited 4 Chicago Cleveland Buffalo New_York
Silver_Service 4 New_York Philadelphia Washington_DC Miami
3
Seattle Miami
Seattle Boston
Buffalo Washington_DC
```
**Output**
```
true false true
```
**Explanation**
- Seattle to Miami: Transfer at Chicago and New York.
- Seattle to Boston: Boston is not reachable from the network (in fact, it's not even in the network for this example).
- Buffalo to Washington DC: Reachable via New York.
