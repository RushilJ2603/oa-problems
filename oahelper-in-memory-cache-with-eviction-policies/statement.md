# In-Memory Cache with Eviction Policies

Design and implement a generic in-memory cache system with pluggable eviction policies.

### Requirements

#### Part 1: Core Cache Interface
Implement a Cache interface/protocol with the following operations:
- `get(key)` - Retrieve a value by key. Returns `"None"` if not found.
- `put(key, value)` - Store a key-value pair. If cache is full, evict based on policy.
- `delete(key)` - Remove a key-value pair.
- `size()` - Return current number of items in cache (does not affect the returned result array).
- `clear()` - Remove all items from cache.

#### Part 2: Eviction Policies
Implement two eviction policies:
1. **LRU (Least Recently Used):** Evict the item that was accessed (get/put) longest ago.
2. **LFU (Least Frequently Used):** Evict the item that was accessed the fewest times. If there's a tie, evict the least recently used among them.

#### Part 3: Return
Complete the `run_cache_operations` function. The function should process each command and return a list of strings containing ONLY the results of all `get` operations.

**Constraints**
- 1 <= capacity <= 10000
- Keys are strings with length 1-100
- Values are integers
- Total operations: up to 100,000

**Example**
Input:
```
3
LRU
6
put a 1
put b 2
put c 3
get a
put d 4
get b
```
Output:
```
1
None
```
Explanation:
After putting a, b, c, capacity is full. We get 'a', making it the most recently used. Then we put 'd', which evicts 'b' (least recently used). So getting 'b' returns None.
