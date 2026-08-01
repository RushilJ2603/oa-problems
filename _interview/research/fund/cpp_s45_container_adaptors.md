# Container Adaptors

In C++, a **container adaptor** is not a new container in itself. Instead, it wraps an existing sequence container (like `std::deque` or `std::vector`) and restricts its interface to provide a specific, specialised behaviour. 

::: keypoint
Container adaptors intentionally expose **no iterators**. You cannot traverse them, use range-based `for` loops, or access elements by index. You can only manipulate elements according to the strict rules of the adaptor.
:::

There are three standard container adaptors: `std::stack`, `std::queue`, and `std::priority_queue`.

::: definition
An **adaptor** takes an existing **underlying container** (which means the real storage that holds the elements) and publishes only a narrow API — LIFO, FIFO, or priority-ordered access — so the caller cannot misuse the structure as a general sequence.
:::

::: keypoint
All three adaptors are thin wrappers: they forward to members of the underlying container and (for `priority_queue`) to the heap algorithms in `<algorithm>`. Choosing the underlying container changes performance characteristics; it does not change the public adaptor API.
:::

## `std::stack` (LIFO)

A `std::stack` implements a Last-In, First-Out (LIFO) data structure. Elements are pushed onto the top of the stack and popped from the top.

### Template signature and underlying container

```cpp
template<
    class T,
    class Container = std::deque<T>
> class stack;
```

By default, a `std::stack` is backed by a `std::deque`. You can change the underlying container to any sequence container that supports `push_back()`, `pop_back()`, and `back()` (such as `std::vector` or `std::list`).

```cpp
#include <stack>
#include <vector>
#include <list>

std::stack<int> defaultStack;                           // Backed by std::deque<int>
std::stack<int, std::vector<int>> vectorBackedStack;    // Backed by std::vector<int>
std::stack<int, std::list<int>> listBackedStack;        // Backed by std::list<int>
```

::: keypoint
`std::deque` is the default because it grows efficiently at both ends without the occasional large reallocations of `std::vector`, while still giving amortised O(1) `push_back` / `pop_back` / `back`. Prefer `std::vector` only when you know the stack will stay small or cache locality matters more than growth behaviour.
:::

### Interface and example

The restricted interface exposes only:
- `void push(const T& value)` / `void push(T&& value)`: Adds an element to the top.
- `void pop()`: Removes the top element.
- `T& top()`: Returns a reference to the top element.
- `bool empty() const`: Returns `true` if the stack has no elements.
- `size_t size() const`: Returns the number of elements.

Full member list with signatures, complexity, and behaviour (all forwarded to the underlying container’s back end):

| Member | Signature (conceptually) | Does | Complexity |
|--------|--------------------------|------|------------|
| `push` | `void push(const T&)` / `void push(T&&)` | Insert at top (`c.push_back`) | Amortised O(1) |
| `emplace` | `void emplace(Args&&...)` | Construct in place at top (`c.emplace_back`) | Amortised O(1) |
| `pop` | `void pop()` | Remove top (`c.pop_back`); **does not return** the value | Amortised O(1) |
| `top` | `T& top()` / `const T& top() const` | Reference to top (`c.back`) | O(1) |
| `empty` | `bool empty() const` | `c.empty()` | O(1) |
| `size` | `size_type size() const` | `c.size()` | O(1) |

::: trap
`pop()` returns `void`. Always read with `top()` first, then `pop()`. Calling `top()` or `pop()` on an empty stack is undefined behaviour.
:::

```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> s;
    
    s.push(10);
    s.push(20);
    s.push(30);
    
    std::cout << "Size: " << s.size() << "\n"; // Outputs: Size: 3
    
    while (!s.empty()) {
        std::cout << s.top() << " "; // Read the top element
        s.pop();                     // Remove the top element
    }
    // Outputs: 30 20 10
    
    return 0;
}
```

### No iteration

A stack has **no** `begin()` / `end()`, no iterators, and no indexed access. The only legal way to inspect contents is repeatedly `top()` + `pop()` (which destroys the stack) or to keep a parallel structure yourself.

```cpp
#include <stack>
#include <vector>

// If you need to dump without destroying, copy first (or use the underlying
// container type directly if you need random access).
std::stack<int> s;
s.push(1); s.push(2); s.push(3);

std::stack<int> copy = s;
std::vector<int> dumped;
while (!copy.empty()) {
    dumped.push_back(copy.top());
    copy.pop();
}
// dumped == {3, 2, 1}; original s unchanged
```

::: interview
Classic uses: matching brackets, DFS with an explicit stack, undo/redo, evaluating postfix expressions. Interviewers often ask why `std::stack` has no iterators — answer: the adaptor’s contract is LIFO-only; exposing iteration would break that abstraction.
:::

## `std::queue` (FIFO)

A `std::queue` implements a First-In, First-Out (FIFO) data structure, much like a physical queue of people waiting in line. Elements are added to the back and removed from the front.

### Template signature and underlying container

```cpp
template<
    class T,
    class Container = std::deque<T>
> class queue;
```

Like `std::stack`, `std::queue` is backed by `std::deque` by default. It can be backed by any sequence container that supports `push_back()`, `pop_front()`, `front()`, and `back()` (such as `std::list`). Notably, you **cannot** use `std::vector`, because it lacks an efficient `pop_front()`.

```cpp
#include <queue>
#include <deque>
#include <list>

std::queue<int> q1;                              // deque
std::queue<int, std::list<int>> q2;              // list — OK
// std::queue<int, std::vector<int>> q3;         // ill-formed / useless: no pop_front
```

### Interface and example

The restricted interface exposes only:
- `void push(const T& value)` / `void push(T&& value)`: Adds an element to the back.
- `void pop()`: Removes the front element.
- `T& front()`: Returns a reference to the first element.
- `T& back()`: Returns a reference to the last element.
- `bool empty() const`: Returns `true` if empty.
- `size_t size() const`: Returns the number of elements.

Full member list:

| Member | Signature (conceptually) | Does | Complexity |
|--------|--------------------------|------|------------|
| `push` | `void push(const T&)` / `void push(T&&)` | Enqueue at back (`c.push_back`) | Amortised O(1) |
| `emplace` | `void emplace(Args&&...)` | Construct at back (`c.emplace_back`) | Amortised O(1) |
| `pop` | `void pop()` | Dequeue front (`c.pop_front`); returns `void` | Amortised O(1) |
| `front` | `T& front()` / `const T& front() const` | Oldest element (`c.front`) | O(1) |
| `back` | `T& back()` / `const T& back() const` | Newest element (`c.back`) | O(1) |
| `empty` | `bool empty() const` | Whether empty | O(1) |
| `size` | `size_type size() const` | Element count | O(1) |

::: trap
Same as stack: `pop()` does not return the removed value. Use `front()` then `pop()`. `front()` / `back()` / `pop()` on an empty queue is undefined behaviour.
:::

```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;
    
    q.push(1); // Back: 1, Front: 1
    q.push(2); // Back: 2, Front: 1
    q.push(3); // Back: 3, Front: 1
    
    std::cout << "Front: " << q.front() << ", Back: " << q.back() << "\n";
    // Outputs: Front: 1, Back: 3
    
    while (!q.empty()) {
        std::cout << q.front() << " "; // Read the front element
        q.pop();                       // Remove the front element
    }
    // Outputs: 1 2 3
    
    return 0;
}
```

::: interview
Queues power BFS, sliding-window problems, and producer–consumer buffering. Contrast with `std::stack`: queue needs efficient ops at **both** ends, which is why `deque` (or `list`) is required and `vector` is not a valid underlying container.
:::

## `std::priority_queue` (Heaps)

A `std::priority_queue` provides constant time lookup of the "largest" (by default) element, at the expense of logarithmic insertion and extraction. 

::: heavy
Dense section — slow down. `priority_queue` is the adaptor you will use most in competitive programming and interviews: template parameters, max- vs min-heap, custom comparators, and the binary-heap layout underneath all come up constantly.
:::

### Template signature and underlying container

```cpp
template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class priority_queue;
```

The three template parameters are:

1. **`T`** — element type stored in the heap.
2. **`Container`** — underlying random-access sequence; default `std::vector<T>`. Must support random access, `front()`, `push_back()`, `pop_back()`, and the iterators used by `std::make_heap` / `std::push_heap` / `std::pop_heap`.
3. **`Compare`** — strict weak ordering comparator; default `std::less<T>`, which yields a **max-heap**.

Under the hood, `std::priority_queue` is implemented as a **binary heap**. Its default underlying container is `std::vector`, which provides the random access necessary for heap algorithms. 

The default comparator is `std::less`, which results in a **max-heap** (the largest element surfaces to the top). 

```cpp
#include <queue>
#include <vector>
#include <deque>

std::priority_queue<int> pq;                                    // max-heap, vector
std::priority_queue<int, std::deque<int>> pq_deque;             // still max-heap
std::priority_queue<int, std::vector<int>, std::greater<int>>   // min-heap
    min_pq;
```

The complexity of operations reflects this binary heap implementation:
- `push()`: O(log n)
- `pop()`: O(log n)
- `top()`: O(1)

### Interface 

The interface is similar to a stack, but elements are ordered by priority:
- `void push(const T& value)` / `void push(T&& value)`: Inserts the element and reorders the heap.
- `void pop()`: Removes the top (highest priority) element.
- `const T& top() const`: Returns a reference to the top element.
- `bool empty() const`: Returns `true` if empty.
- `size_t size() const`: Returns the number of elements.

Complete member list (what each does, complexity):

| Member | Signature | Does | Complexity |
|--------|-----------|------|------------|
| `push` | `void push(const T&)` / `void push(T&&)` | Append then sift-up via `std::push_heap` | O(log n) |
| `emplace` | `void emplace(Args&&...)` | Construct in place at end, then sift-up | O(log n) |
| `pop` | `void pop()` | Move top to end via `std::pop_heap`, then `pop_back`; returns `void` | O(log n) |
| `top` | `const T& top() const` | Element at root (`c.front()`) — **always const** | O(1) |
| `empty` | `bool empty() const` | Whether the heap is empty | O(1) |
| `size` | `size_type size() const` | Number of elements | O(1) |

::: trap
`top()` returns `const T&` only — you cannot mutate the top element through the adaptor (that would break the heap invariant). `pop()` again returns `void`: read `top()` first.
:::

::: keypoint
**No iteration** and **no decrease-key**. There is no way to walk the heap in priority order, find an arbitrary element, or lower/raise an existing key in place. The public API is deliberately only push / pop / top / size / empty.
:::

### No decrease-key — workarounds

A true decrease-key would need a handle into the heap so a node can be sifted after its priority changes. `std::priority_queue` does not expose handles. In competitive programming the usual workaround is **push duplicates + lazy deletion**:

1. When a node’s distance improves, **push a new** `(dist, node)` pair; leave the stale entry in the heap.
2. When you `pop` / `top`, **skip** entries whose distance is worse than the best known distance for that node.

```cpp
#include <queue>
#include <vector>
#include <limits>

// Dijkstra sketch: lazy deletion instead of decrease-key
void dijkstra_lazy(int n, int src,
                   const std::vector<std::vector<std::pair<int,int>>>& adj) {
    const int INF = std::numeric_limits<int>::max() / 4;
    std::vector<int> dist(n, INF);
    dist[src] = 0;

    using Node = std::pair<int, int>; // {distance, vertex}
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue; // stale duplicate — skip

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v}); // push new; old entry becomes stale
            }
        }
    }
}
```

Complexity stays O((V + E) log V) with a larger constant because of extra heap entries; for contest graphs this is almost always acceptable.

### Min-heaps and custom comparators

To create a **min-heap**, you must override the default `Compare` parameter with `std::greater`. Because `Compare` is the third template parameter, you must also explicitly specify the second parameter (`std::vector<T>`).

For custom objects, you can provide a custom comparator using either a functor (a struct with an overloaded `operator()`) or a lambda expression.

::: definition
The comparator returns `true` when its first argument has **lower priority** than its second — i.e. `comp(a, b) == true` means “`a` is ordered before `b` in the *less-than* sense,” so **`b` is considered greater**. The **top** is therefore the element that is greatest under that order. With `std::less`, larger values win (max-heap); with `std::greater`, smaller values win (min-heap).
:::

::: trap
The comparator intuition feels **inverted**. People write `return a.priority > b.priority` expecting a max-heap of priority and get the opposite. Remember: return `true` when `a` has **lower** priority than `b`. `std::greater<T>` makes a **min-heap**; `std::less<T>` (default) makes a **max-heap**.
:::

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <functional> // For std::greater

struct Task {
    int priority;
    std::string name;
};

// Functor for custom comparison
struct CompareTask {
    bool operator()(const Task& a, const Task& b) const {
        return a.priority < b.priority; // Less-than means max-heap for priority
    }
};

int main() {
    // 1. Max-heap (Default)
    std::priority_queue<int> maxHeap;
    maxHeap.push(10); maxHeap.push(30); maxHeap.push(20);
    // maxHeap.top() is 30
    
    // 2. Min-heap (Requires std::greater)
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    minHeap.push(10); minHeap.push(30); minHeap.push(20);
    // minHeap.top() is 10
    
    // 3. Custom comparator using a functor
    std::priority_queue<Task, std::vector<Task>, CompareTask> taskQueue1;
    taskQueue1.push({2, "Medium task"});
    taskQueue1.push({5, "Urgent task"});
    
    // 4. Custom comparator using a lambda and decltype
    auto cmp = [](const Task& a, const Task& b) {
        return a.priority < b.priority; 
    };
    std::priority_queue<Task, std::vector<Task>, decltype(cmp)> taskQueue2(cmp);
    taskQueue2.push({1, "Low task"});
    
    std::cout << "Highest priority task: " << taskQueue1.top().name << "\n";
    // Outputs: Highest priority task: Urgent task
    
    return 0;
}
```

### Custom comparators — three ways (full examples)

#### (a) Functor / struct with `operator()`

A named **functor** (which means a type that overloads `operator()` so instances are callable) is the cleanest reusable comparator.

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Person {
    std::string name;
    int age;
};

// Max-heap by age: return true when a has LOWER priority than b
struct ByAgeDesc {
    bool operator()(const Person& a, const Person& b) const {
        return a.age < b.age; // younger = lower priority → oldest on top
    }
};

// Min-heap by age
struct ByAgeAsc {
    bool operator()(const Person& a, const Person& b) const {
        return a.age > b.age; // older = lower priority → youngest on top
    }
};

int main() {
    std::priority_queue<Person, std::vector<Person>, ByAgeDesc> oldest_first;
    oldest_first.push({"Ada", 36});
    oldest_first.push({"Bob", 22});
    oldest_first.push({"Cyd", 41});
    std::cout << oldest_first.top().name << "\n"; // Cyd

    std::priority_queue<Person, std::vector<Person>, ByAgeAsc> youngest_first;
    youngest_first.push({"Ada", 36});
    youngest_first.push({"Bob", 22});
    youngest_first.push({"Cyd", 41});
    std::cout << youngest_first.top().name << "\n"; // Bob
}
```

#### (b) Lambda + `decltype` passed to the constructor

Lambdas have unique closure types. Capture that type with `decltype(cmp)` as the third template argument, and **pass the lambda object** to the constructor:

```cpp
#include <iostream>
#include <queue>
#include <vector>

int main() {
    auto cmp = [](int a, int b) {
        return a > b; // true when a is "less" → min-heap of ints
    };
    // Exact syntax interviewers expect:
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

    pq.push(5);
    pq.push(1);
    pq.push(9);
    std::cout << pq.top() << "\n"; // 1
}
```

::: trap
Writing `priority_queue<T, vector<T>, decltype(cmp)> pq;` **without** `pq(cmp)` default-constructs the comparator. That works only if the lambda is **stateless** (no captures). With captures, you must pass `cmp` to the constructor or compilation fails / behaviour is wrong.
:::

#### (c) Pairs, tuples, and structs

`std::pair` and `std::tuple` already define `operator<` lexicographically, so `std::less` / `std::greater` work out of the box. For structs, either overload `operator<` or supply an explicit comparator (prefer an explicit comparator so ordering stays local to the heap).

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <string>

struct Edge {
    int to;
    int weight;
};

struct EdgeMinWeight {
    bool operator()(const Edge& a, const Edge& b) const {
        return a.weight > b.weight; // min-heap by weight
    }
};

int main() {
    // pair: first then second — min-heap of (dist, node)
    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> by_dist;
    by_dist.push({5, 2});
    by_dist.push({1, 0});
    by_dist.push({1, 3});
    // top is {1, 0} (smaller first; then smaller second)
    std::cout << by_dist.top().first << "," << by_dist.top().second << "\n";

    // tuple: lexicographic min-heap
    using T = std::tuple<int, int, std::string>;
    std::priority_queue<T, std::vector<T>, std::greater<T>> events;
    events.emplace(10, 1, "B");
    events.emplace(5, 0, "A");
    auto [t, id, name] = events.top();
    std::cout << t << " " << name << "\n"; // 5 A

    // struct + functor
    std::priority_queue<Edge, std::vector<Edge>, EdgeMinWeight> edges;
    edges.push({3, 10});
    edges.push({1, 4});
    std::cout << edges.top().to << " w=" << edges.top().weight << "\n"; // 1 w=4
}
```

### Worked example: Dijkstra-style min-heap of `pair<dist, node>`

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <utility>

// Compact BFS-on-weights fragment: always expand the smallest distance first.
int main() {
    // Graph: 0 --1--> 1 --2--> 2 ; 0 --4--> 2
    std::vector<std::vector<std::pair<int,int>>> adj(3);
    adj[0].push_back({1, 1});
    adj[0].push_back({2, 4});
    adj[1].push_back({2, 2});

    std::vector<int> dist(3, 1e9);
    dist[0] = 0;

    using P = std::pair<int, int>; // {dist, node}
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue; // lazy skip of stale entries

        for (auto [v, w] : adj[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    std::cout << dist[0] << " " << dist[1] << " " << dist[2] << "\n";
    // Outputs: 0 1 3
}
```

### Under the hood: binary heap in a `std::vector`

Analogy: think of a tournament bracket flattened into a single row of seats — every parent sits earlier in the row than its children, and you can jump to a child or parent with arithmetic on the seat number. No pointers between nodes are stored; the tree shape is **implied** by array indices.

![A `priority_queue` is a binary heap embedded in a vector; the children of index i sit at 2i+1 and 2i+2.](assets/s45_heap_array.png)

::: definition
A **binary heap** stored in a `std::vector` is a complete binary tree embedded in contiguous memory: for the element at index `i` (0-based), its **left child** is at `2*i + 1`, its **right child** at `2*i + 2`, and its **parent** at `(i - 1) / 2`. The **max-heap property** requires every parent to be **greater than or equal to** both children (under the comparator’s notion of “greater”).
:::

Plain-English rule: the largest (by the comparator) element always sits at index `0`. Insertions append at the end and bubble upward; removals replace the root with the last leaf and bubble downward. Index arithmetic replaces tree pointers.

Technical statement: `priority_queue` keeps its container in heap order via `std::make_heap` (construction from a range), `std::push_heap` (after `push_back`), and `std::pop_heap` (before `pop_back`). The adaptor never exposes those indices, so clients cannot iterate in heap order or patch a key in the middle.

#### Array embedding

```
Index:   0   1   2   3   4   5   6
Value:  50  30  40  10  20  35  25

              50                 ← index 0 (root / top)
            /    \
          30      40             ← 1, 2
         /  \    /  \
       10   20  35   25          ← 3, 4, 5, 6
```

- Children of `i`: `2*i+1`, `2*i+2`
- Parent of `i` (`i > 0`): `(i-1)/2`
- `top()` is always `c.front()` — element at index `0` — **O(1)**

This embedding is exactly why there is **no heap-order iteration** (walking the array is level-order storage, not sorted order) and **no decrease-key** (you would need the index of a specific logical element, which the adaptor does not track).

#### `push` = append + sift-up — O(log n)

1. `c.push_back(value)` — place the new element at the next leaf position.
2. **Sift-up** (`std::push_heap`): while the node is larger than its parent (max-heap), swap with the parent; repeat. Height is ⌊log₂ n⌋, so **O(log n)**.

```cpp
// Conceptual — what push does (do not call this yourself on a priority_queue):
// c.push_back(x);
// std::push_heap(c.begin(), c.end(), comp);
```

#### `pop` = move last to root + sift-down — O(log n)

1. `std::pop_heap` swaps the root with the last element, then **sifts down** the new root: repeatedly swap with the larger child until the heap property holds.
2. `c.pop_back()` removes the old root (now at the end).
3. Overall **O(log n)**.

```cpp
// Conceptual:
// std::pop_heap(c.begin(), c.end(), comp); // largest now at back
// c.pop_back();
```

#### `top` = element 0 — O(1)

```cpp
const T& top() const { return c.front(); } // index 0
```

```cpp
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::priority_queue<int> pq;
    for (int x : {10, 50, 30, 20, 40})
        pq.push(x);           // each push: O(log n) sift-up

    std::cout << pq.top() << "\n"; // 50 — O(1)
    pq.pop();                      // O(log n) sift-down; next top is 40
    std::cout << pq.top() << "\n"; // 40
}
```

::: interview
How do you make a **min-heap**? `priority_queue<T, vector<T>, greater<T>>`. How do you heap a **custom struct**? Functor with `operator()`, or lambda with `decltype(cmp)` and `pq(cmp)`, remembering the reversed comparator rule. How is a heap **stored**? Complete binary tree in a `vector`: children `2i+1` / `2i+2`, parent `(i-1)/2`; push sift-up, pop sift-down, top at index 0. Default of `priority_queue` is a **max-heap**; defaults for adaptors: `deque` for `stack`/`queue`, `vector` for `priority_queue`.
:::

::: interview
A frequent interview question asks how `std::priority_queue` is implemented. You should answer that it is a **binary heap** built over a sequence container (usually `std::vector`). Remember that its default is a **max-heap**, and to get a min-heap you must supply `std::greater`. Also, be prepared to list the default backing containers: `std::deque` for `stack` and `queue`, and `std::vector` for `priority_queue`.
:::

::: keypoint
In Python, you simulate a stack using a standard `list` (with `append()` and `pop()`), and a queue using `collections.deque`. For a priority queue, Python provides the `heapq` module, which modifies a list in-place and defaults to a **min-heap** (unlike C++'s max-heap default).
:::

## Choosing an adaptor and underlying container

| Adaptor | Default container | Also valid | Not valid / poor fit | Access pattern |
|---------|-------------------|------------|----------------------|----------------|
| `stack` | `deque` | `vector`, `list` | — | LIFO: back only |
| `queue` | `deque` | `list` | `vector` (no `pop_front`) | FIFO: front + back |
| `priority_queue` | `vector` | `deque` | `list` (no random access) | Heap: top only |

::: keypoint
Reach for `stack` / `queue` when the algorithm’s discipline is the point (DFS, BFS). Reach for `priority_queue` when you always need the current best key (Dijkstra, Huffman, “top K”, event simulation). If you need decrease-key, arbitrary deletes, or sorted iteration, use `std::set` / `std::multiset` or a policy-based / hand-rolled heap instead.
:::

## Quick reference — complexities

| Operation | `stack` | `queue` | `priority_queue` |
|-----------|---------|---------|------------------|
| `push` / `emplace` | Amortised O(1) | Amortised O(1) | O(log n) |
| `pop` | Amortised O(1) | Amortised O(1) | O(log n) |
| `top` / `front` | O(1) | O(1) (`front`/`back`) | O(1) (`top`) |
| `size` / `empty` | O(1) | O(1) | O(1) |
| Iterate / find / decrease-key | Impossible | Impossible | Impossible |
