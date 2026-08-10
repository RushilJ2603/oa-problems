# Escape Room Capacity

Emma manages the escape room for a series of game shows. The room holds at most `capacity` people at
any one time.

Each game show is described by a start time, an end time and a number of attendees. A show's
attendees are inside the room for the interval `[start_time, end_time)` — they arrive at
`start_time` and they are **gone by** `end_time`, so a show that ends at time `t` and a show that
starts at time `t` never share the room.

Every show must run, all of them on the same room. Decide whether the room is ever over capacity.

Print `True` if the number of people in the room never exceeds `capacity` at any moment, and `False`
otherwise.

## Input

- The first line contains a single integer `capacity` — the maximum number of attendees the room can
  hold.
- The second line contains a single integer `N` — the number of shows.
- Each of the next `N` lines contains three integers `start_time`, `end_time` and `attendees`.

## Output

A single line: `True` or `False`.

## Constraints

- `1 <= N <= 10^5`
- `0 <= capacity <= 10^9`
- `0 <= start_time <= end_time <= 10^9`
- `0 <= attendees <= 10^9`

Note that `N · attendees` can reach `10^14`, which does not fit in a 32-bit integer.

A show with `start_time == end_time` occupies the room for no time at all, and therefore never
contributes to the count.

## Example 1

**Input**
```
3
2
1 5 2
2 6 1
```

**Output**
```
True
```

**Explanation:**

| interval | who is inside | people |
|---|---|---|
| `[1, 2)` | show 1 | `2` |
| `[2, 5)` | shows 1 and 2 | `3` |
| `[5, 6)` | show 2 | `1` |

The peak is `3`, and `3 <= 3`, so every show fits.

## Example 2

**Input**
```
7
3
1 4 4
2 6 10
1 5 7
```

**Output**
```
False
```

**Explanation:** shows 1 and 3 both start at time `1`, putting `4 + 7 = 11` people in the room
straight away — already more than the capacity of `7`.

## Example 3

**Input**
```
5
2
1 5 5
5 9 5
```

**Output**
```
True
```

**Explanation:** the first show's attendees leave at time `5`, which is exactly when the second
show's attendees arrive. The two never overlap, so the peak is `5` rather than `10`.
