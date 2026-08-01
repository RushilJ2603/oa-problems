# Graphs

::: heavy
A **graph** is a collection of **vertices** (nodes) and **edges** connecting them. Edges can be **directed** (one-way) or **undirected** (two-way), and they can be **weighted** (having a cost or distance) or unweighted. A sequence of edges forming a loop is a **cycle**. A graph might not be fully connected; it can consist of multiple disjoint **connected components**.

There are two primary ways to represent a graph:
1. **Adjacency Matrix**: A 2D array `adj[V][V]` where `adj[i][j]` is 1 (or the weight) if there is an edge from $i$ to $j$, and 0 otherwise.
2. **Adjacency List**: An array of lists `vector<vector<int>> adj` where `adj[i]` contains all neighbors of vertex $i$.

| Representation | Space | Edge Lookup | Edge Insertion | Iterating Neighbors of $u$ |
| --- | --- | --- | --- | --- |
| Adjacency Matrix | $O(V^2)$ | $O(1)$ | $O(1)$ | $O(V)$ |
| Adjacency List | $O(V + E)$ | $O(\text{degree}(u))$ | $O(1)$ | $O(\text{degree}(u))$ |

Because graphs can be disconnected, real code often uses an outer loop over all vertices to launch traversals, ensuring all connected components are visited.
:::

::: keypoint
Breadth-First Search (BFS) uses a **queue** to find the shortest path in unit-weight graphs. Depth-First Search (DFS) uses a **stack** (or recursion) to explore paths deeply.
:::

## Traversals & Grid Problems

### Graph Representation in C++
Building a graph from a list of edges is the first step in most problems. We represent an unweighted graph using an adjacency list. 

The input is typically the number of vertices $V$ and a list of pairs `(u, v)`. For an undirected graph, we add $v$ to $u$'s list and $u$ to $v$'s list.

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int V = 5;
    vector<pair<int, int>> edges = {{0, 1}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}};
    
    // Create an adjacency list for V vertices (0-indexed)
    vector<vector<int>> adj(V);
    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adj[u].push_back(v);
        adj[v].push_back(u); // Omit this line for a directed graph
    }
    
    // Print the graph
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (int neighbor : adj[i]) {
            cout << neighbor << " ";
        }
        cout << "\n";
    }
    return 0;
}
```
**Complexity**: Time $O(V + E)$ to build the list, Space $O(V + E)$ to store it.
**Practice:** https://practice.geeksforgeeks.org/problems/print-adjacency-list-1587115620/1

### BFS Traversal
Breadth-First Search visits nodes level by level, radiating outward from a starting node.

![Breadth-first search explores a graph level by level using a queue.](../assets/fig_bfs.png)

::: keypoint
BFS always requires a queue to track the frontier and a boolean array (or set) to track visited nodes. Always mark a node visited the moment it is pushed to the queue to avoid duplicate processing.
:::

We enqueue the starting node and mark it visited. While the queue is not empty, we dequeue a node, process it, and enqueue all its unvisited neighbors.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int start, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& result) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

int main() {
    int V = 5;
    vector<vector<int>> adj = {{1, 2}, {0, 3, 4}, {0, 4}, {1}, {1, 2}};
    
    vector<bool> visited(V, false);
    vector<int> result;
    
    // Loop covers disconnected components
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            bfs(i, adj, visited, result);
        }
    }
    
    for (int node : result) cout << node << " ";
    cout << "\n";
    return 0;
}
```
**Complexity**: Time $O(V + E)$ as each node and edge is processed once. Space $O(V)$ for the queue and visited array.
**Practice:** https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1

### DFS Traversal
Depth-First Search plunges as deeply as possible along each branch before backtracking.

![Depth-first search on an example graph.](../assets/fig_graph_dfs_example.png)

We use recursion (the call stack) to track our path. When we visit a node, we mark it visited, then recursively call DFS on all its unvisited neighbors.

```cpp
#include <iostream>
#include <vector>

using namespace std;

void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& result) {
    visited[node] = true;
    result.push_back(node);

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, result);
        }
    }
}

int main() {
    int V = 5;
    vector<vector<int>> adj = {{1, 2}, {0, 3, 4}, {0, 4}, {1}, {1, 2}};
    
    vector<bool> visited(V, false);
    vector<int> result;
    
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited, result);
        }
    }
    
    for (int node : result) cout << node << " ";
    cout << "\n";
    return 0;
}
```
**Complexity**: Time $O(V + E)$ since each node is visited once and each edge is inspected. Space $O(V)$ for the recursion stack and visited array.
**Practice:** https://practice.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1

### Number of Provinces
Given an $n \times n$ matrix `isConnected` where `isConnected[i][j] = 1` if city $i$ and city $j$ are directly connected, return the total number of provinces (connected components).

A province is a group of directly or indirectly connected cities. We simply need to count how many times we initiate a new BFS or DFS from our outer loop. Each time we find an unvisited node, it represents a new connected component.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void dfs(int node, const vector<vector<int>>& isConnected, vector<bool>& visited) {
        visited[node] = true;
        for (int i = 0; i < isConnected.size(); ++i) {
            if (isConnected[node][i] == 1 && !visited[i]) {
                dfs(i, isConnected, visited);
            }
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;
        
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                provinces++;
                dfs(i, isConnected, visited);
            }
        }
        return provinces;
    }
};

int main() {
    vector<vector<int>> isConnected = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    Solution sol;
    cout << sol.findCircleNum(isConnected) << "\n";
    return 0;
}
```
**Complexity**: Time $O(V^2)$ because we traverse the $V \times V$ adjacency matrix. Space $O(V)$ for the visited array and recursion stack.
**Practice:** https://leetcode.com/problems/number-of-provinces/

### Number of Islands
Given an $m \times n$ 2D binary grid where `'1'` represents land and `'0'` represents water, return the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.

This is fundamentally the same as Number of Provinces, but on an implicit grid graph where each cell is a vertex and shares edges with its 4 cardinal neighbors. When we find an unvisited `'1'`, we increment our island count and launch a DFS/BFS to mark the entire island as visited.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void dfs(int r, int c, vector<vector<char>>& grid) {
        if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == '0') {
            return;
        }
        
        grid[r][c] = '0'; // Mark as visited by mutating the grid
        
        dfs(r + 1, c, grid);
        dfs(r - 1, c, grid);
        dfs(r, c + 1, grid);
        dfs(r, c - 1, grid);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int islands = 0;
        
        for (int r = 0; r < grid.size(); ++r) {
            for (int c = 0; c < grid[0].size(); ++c) {
                if (grid[r][c] == '1') {
                    islands++;
                    dfs(r, c, grid);
                }
            }
        }
        return islands;
    }
};

int main() {
    vector<vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    Solution sol;
    cout << sol.numIslands(grid) << "\n";
    return 0;
}
```
**Complexity**: Time $O(m \times n)$ since each cell is visited a constant number of times. Space $O(m \times n)$ for the recursion stack in the worst case (a grid full of '1's).
**Practice:** https://leetcode.com/problems/number-of-islands/

### Flood Fill
Given an image represented by an $m \times n$ integer grid, a starting pixel `(sr, sc)`, and a `color`, perform a flood fill on the starting pixel.

We start at `(sr, sc)`, record its original color, and change its color to the new `color`. Then we recursively do the same for its 4-directionally adjacent neighbors that share the original color.

::: trap
If the new color is the same as the original color, the DFS will loop infinitely. Always check `if (initialColor == color)` and return early.
:::

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void dfs(int r, int c, int initialColor, int newColor, vector<vector<int>>& image) {
        if (r < 0 || c < 0 || r >= image.size() || c >= image[0].size() || image[r][c] != initialColor) {
            return;
        }
        
        image[r][c] = newColor;
        
        dfs(r + 1, c, initialColor, newColor, image);
        dfs(r - 1, c, initialColor, newColor, image);
        dfs(r, c + 1, initialColor, newColor, image);
        dfs(r, c - 1, initialColor, newColor, image);
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int initialColor = image[sr][sc];
        if (initialColor != color) {
            dfs(sr, sc, initialColor, color, image);
        }
        return image;
    }
};

int main() {
    vector<vector<int>> image = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    Solution sol;
    vector<vector<int>> res = sol.floodFill(image, 1, 1, 2);
    for (const auto& row : res) {
        for (int pixel : row) cout << pixel << " ";
        cout << "\n";
    }
    return 0;
}
```
**Complexity**: Time $O(m \times n)$ to visit each pixel. Space $O(m \times n)$ for the recursion stack.
**Practice:** https://leetcode.com/problems/flood-fill/

### Rotten Oranges
Given an $m \times n$ grid where `0` is empty, `1` is a fresh orange, and `2` is a rotten orange. Every minute, any fresh orange 4-directionally adjacent to a rotten orange becomes rotten. Return the minimum number of minutes until no cell has a fresh orange, or `-1` if impossible.

Because the rotting spreads outward from *all* rotten oranges simultaneously at a rate of one step per minute, this is a **multi-source shortest path** problem.

::: keypoint
Whenever we need to process multiple starting nodes spreading simultaneously level-by-level, we use a **multi-source BFS**. We enqueue all starting nodes at level 0 before beginning the loop.
:::

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 2) {
                    q.push({r, c});
                } else if (grid[r][c] == 1) {
                    fresh++;
                }
            }
        }
        
        if (fresh == 0) return 0;
        
        int minutes = 0;
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        while (!q.empty()) {
            int levelSize = q.size();
            bool rottedAny = false;
            
            for (int i = 0; i < levelSize; ++i) {
                auto [r, c] = q.front();
                q.pop();
                
                for (auto [dr, dc] : dirs) {
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;
                        fresh--;
                        q.push({nr, nc});
                        rottedAny = true;
                    }
                }
            }
            if (rottedAny) minutes++;
        }
        
        return fresh == 0 ? minutes : -1;
    }
};

int main() {
    vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    Solution sol;
    cout << sol.orangesRotting(grid) << "\n";
    return 0;
}
```
**Complexity**: Time $O(m \times n)$ as every cell is enqueued at most once. Space $O(m \times n)$ if the grid is filled with rotten oranges.
**Practice:** https://leetcode.com/problems/rotting-oranges/

### Detect a Cycle in an Undirected Graph
Given an undirected graph, return true if it contains a cycle.

A cycle exists if, during our traversal, we encounter a node that is already visited AND is not the immediate parent we came from. We can detect this using either BFS or DFS.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool dfsCheck(int node, int parent, const vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfsCheck(neighbor, node, adj, visited)) return true;
            } else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }

public:
    bool isCycle(int V, vector<vector<int>>& adj) {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                if (dfsCheck(i, -1, adj, visited)) return true;
            }
        }
        return false;
    }
};

int main() {
    int V = 5;
    vector<vector<int>> adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}};
    Solution sol;
    cout << (sol.isCycle(V, adj) ? "Cycle" : "No Cycle") << "\n";
    return 0;
}
```
**Complexity**: Time $O(V + E)$ since we visit each vertex and edge once. Space $O(V)$ for the recursion stack (DFS) and visited array.
**Practice:** https://practice.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1

### Distance of Nearest Cell Having 1
Given an $m \times n$ binary grid, return the distance of the nearest `1` for each cell. The distance between two adjacent cells is 1.

Rather than searching outward from every `0` to find a `1` (which would be inefficient), we reverse the logic. We treat all `1`s as multiple sources, enqueue them all at distance 0, and run a multi-source BFS outward to the `0`s.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 1) {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }
        
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            for (auto [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        return dist;
    }
};

int main() {
    vector<vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
    Solution sol;
    vector<vector<int>> res = sol.updateMatrix(mat);
    for (const auto& row : res) {
        for (int cell : row) cout << cell << " ";
        cout << "\n";
    }
    return 0;
}
```
**Complexity**: Time $O(m \times n)$ to process every cell once. Space $O(m \times n)$ for the output matrix and queue.
**Practice:** https://leetcode.com/problems/01-matrix/

### Surrounded Regions / Replace O with X
Given an $m \times n$ matrix containing `'X'` and `'O'`, capture all regions that are 4-directionally surrounded by `'X'`. A region is not surrounded if it touches the boundary of the board.

Any `'O'` connected to the boundary cannot be captured. We perform a boundary DFS: traverse the perimeter of the board, run DFS from any `'O'`, and mark all connected `'O'`s as safe (e.g., `'S'`). Afterwards, flip the remaining `'O'`s to `'X'`, and revert `'S'` back to `'O'`.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void dfs(int r, int c, vector<vector<char>>& board) {
        if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] != 'O') {
            return;
        }
        board[r][c] = 'S'; // Mark as safe
        dfs(r + 1, c, board);
        dfs(r - 1, c, board);
        dfs(r, c + 1, board);
        dfs(r, c - 1, board);
    }
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        if (m == 0) return;
        int n = board[0].size();
        
        // Traverse first and last rows
        for (int j = 0; j < n; ++j) {
            if (board[0][j] == 'O') dfs(0, j, board);
            if (board[m - 1][j] == 'O') dfs(m - 1, j, board);
        }
        // Traverse first and last columns
        for (int i = 0; i < m; ++i) {
            if (board[i][0] == 'O') dfs(i, 0, board);
            if (board[i][n - 1] == 'O') dfs(i, n - 1, board);
        }
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                else if (board[i][j] == 'S') board[i][j] = 'O';
            }
        }
    }
};

int main() {
    vector<vector<char>> board = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };
    Solution sol;
    sol.solve(board);
    for (const auto& row : board) {
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
    return 0;
}
```
**Complexity**: Time $O(m \times n)$ to visit and check each cell. Space $O(m \times n)$ for the recursion stack in the worst case.
**Practice:** https://leetcode.com/problems/surrounded-regions/

### Number of Enclaves
Given an $m \times n$ binary grid where `1` represents land and `0` represents water, count the number of land cells that cannot be walked off the boundary of the grid.

This is identical to Surrounded Regions. We run a boundary DFS from all perimeter `1`s to mark them as reachable (by sinking them to `0`). Then, we count the remaining `1`s in the grid.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void dfs(int r, int c, vector<vector<int>>& grid) {
        if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == 0) {
            return;
        }
        grid[r][c] = 0; // Sink the land
        dfs(r + 1, c, grid);
        dfs(r - 1, c, grid);
        dfs(r, c + 1, grid);
        dfs(r, c - 1, grid);
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 1) dfs(i, 0, grid);
            if (grid[i][n - 1] == 1) dfs(i, n - 1, grid);
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 1) dfs(0, j, grid);
            if (grid[m - 1][j] == 1) dfs(m - 1, j, grid);
        }
        
        int enclaves = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    enclaves++;
                }
            }
        }
        return enclaves;
    }
};

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    Solution sol;
    cout << sol.numEnclaves(grid) << "\n";
    return 0;
}
```
**Complexity**: Time $O(m \times n)$ to process the grid. Space $O(m \times n)$ for the recursion stack.
**Practice:** https://leetcode.com/problems/number-of-enclaves/

### Number of Distinct Islands
Given an $m \times n$ binary grid, count the number of distinct islands. Two islands are the same if they can be translated (not rotated or reflected) to match each other.

To uniquely identify the shape of an island regardless of its absolute coordinates, we record the path relative to the starting cell `(r0, c0)`. Every cell's relative coordinate is `(r - r0, c - c0)`. We insert the list of relative coordinates into a hash set to weed out duplicates.

```cpp
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
    void dfs(int r, int c, int r0, int c0, vector<vector<int>>& grid, vector<pair<int, int>>& shape) {
        if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == 0) {
            return;
        }
        grid[r][c] = 0; // Mark visited
        shape.push_back({r - r0, c - c0});
        
        dfs(r + 1, c, r0, c0, grid, shape);
        dfs(r - 1, c, r0, c0, grid, shape);
        dfs(r, c + 1, r0, c0, grid, shape);
        dfs(r, c - 1, r0, c0, grid, shape);
    }
public:
    int countDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        
        set<vector<pair<int, int>>> uniqueIslands;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    vector<pair<int, int>> shape;
                    dfs(i, j, i, j, grid, shape);
                    uniqueIslands.insert(shape);
                }
            }
        }
        return uniqueIslands.size();
    }
};

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {1, 1, 0, 1, 0}
    };
    Solution sol;
    cout << sol.countDistinctIslands(grid) << "\n";
    return 0;
}
```
**Complexity**: Time $O(m \times n \log(\text{unique shapes}))$ due to set insertion (which compares vectors). Space $O(m \times n)$ for the set and recursion stack.
**Practice:** https://practice.geeksforgeeks.org/problems/number-of-distinct-islands/1

### Bipartite Graph Check
A graph is bipartite if its vertices can be partitioned into two independent sets such that every edge connects a vertex in the first set to one in the second. Equivalently, it is bipartite if it can be colored using exactly 2 colors with no two adjacent vertices sharing a color.

::: keypoint
A graph is bipartite if and only if it has **no odd-length cycles**. We can check this by performing a BFS or DFS and attempting to 2-color the graph.
:::

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
    bool bfsCheck(int start, const vector<vector<int>>& graph, vector<int>& color) {
        queue<int> q;
        q.push(start);
        color[start] = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : graph[node]) {
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[node]; // Flip color 0 <-> 1
                    q.push(neighbor);
                } else if (color[neighbor] == color[node]) {
                    return false; // Found adjacent nodes with the same color
                }
            }
        }
        return true;
    }
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int V = graph.size();
        vector<int> color(V, -1);
        
        for (int i = 0; i < V; ++i) {
            if (color[i] == -1) {
                if (!bfsCheck(i, graph, color)) return false;
            }
        }
        return true;
    }
};

int main() {
    vector<vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    Solution sol;
    cout << (sol.isBipartite(graph) ? "Bipartite" : "Not Bipartite") << "\n";
    return 0;
}
```
**Complexity**: Time $O(V + E)$ to traverse all nodes and edges. Space $O(V)$ for the colors array and queue.
**Practice:** https://leetcode.com/problems/is-graph-bipartite/

### Detect a Cycle in a Directed Graph
Given a directed graph, check if it contains a cycle.

Unlike undirected graphs, crossing an already visited node doesn't necessarily mean a cycle exists (it could just be two paths converging at a node). A cycle exists ONLY if we reach a node that is currently in the active recursion stack for this path.

::: trap
A simple `visited` boolean array fails for directed graphs. You must track two states: globally visited, and currently active in the path stack.
:::

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool dfsCheck(int node, const vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& pathVisited) {
        visited[node] = true;
        pathVisited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfsCheck(neighbor, adj, visited, pathVisited)) return true;
            } else if (pathVisited[neighbor]) {
                // If it's visited AND in the current path, it's a cycle
                return true;
            }
        }
        
        pathVisited[node] = false; // Remove from current path when backtracking
        return false;
    }
public:
    bool isCyclic(int V, vector<vector<int>>& adj) {
        vector<bool> visited(V, false);
        vector<bool> pathVisited(V, false);
        
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                if (dfsCheck(i, adj, visited, pathVisited)) return true;
            }
        }
        return false;
    }
};

int main() {
    int V = 4;
    vector<vector<int>> adj = {{1}, {2}, {3}, {1}}; // 1 -> 2 -> 3 -> 1
    Solution sol;
    cout << (sol.isCyclic(V, adj) ? "Cycle" : "No Cycle") << "\n";
    return 0;
}
```
**Complexity**: Time $O(V + E)$ since every node is processed once. Space $O(V)$ for the arrays and recursion stack.
**Practice:** https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1

## Topological Sort & Directed Graphs

### Topological Sort (DFS)

A **topological sort** or topological ordering of a directed graph is a linear ordering of its vertices such that for every directed edge $u \to v$ from vertex $u$ to vertex $v$, $u$ comes before $v$ in the ordering. It is only possible if the graph is a Directed Acyclic Graph (DAG). 

**Intuition / approach:**
We can use Depth-First Search (DFS) to find a topological sort. When we perform DFS on a DAG, a vertex will finish exploring all of its adjacent descendants before it finishes its own exploration. If we push a vertex onto a stack right before its recursive DFS call returns, the stack will ultimately hold the vertices in topologically sorted order (from top to bottom). The strategy is to maintain a visited array, initiate a DFS for every unvisited vertex, and upon finishing the DFS for a vertex, push it onto a stack. Popping all elements from the stack yields the valid ordering.

::: keypoint
Topological sort is strictly defined for Directed Acyclic Graphs (DAGs). A graph with a cycle cannot be topologically sorted.
:::

```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, st);
        }
    }
    st.push(node);
}

vector<int> topologicalSortDFS(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    stack<int> st;

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited, st);
        }
    }

    vector<int> result;
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    return result;
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);
    
    vector<int> topo = topologicalSortDFS(V, adj);
    for (int node : topo) {
        cout << node << " ";
    }
    cout << "\n";
    return 0;
}
```

**Complexity:**
Time: $O(V + E)$ where $V$ is the number of vertices and $E$ is the number of edges, as every vertex and edge is explored exactly once during the DFS.
Space: $O(V)$ for the visited array, the recursion stack depth, and the explicit stack used to store the result.

**Practice:** https://practice.geeksforgeeks.org/problems/topological-sort/1

### Kahn's Algorithm — Topological Sort

**Intuition / approach:**
Kahn's Algorithm iteratively constructs a topological sort by repeatedly removing nodes with an indegree of zero. The **indegree** of a node is the number of incoming edges. A node with an indegree of zero has no dependencies and can thus be placed next in the topological ordering.
We first compute the indegree for every vertex. Vertices with an indegree of $0$ are added to a queue. While the queue is not empty, we dequeue a vertex, add it to our topological sort result, and conceptually remove it from the graph by decreasing the indegree of all its adjacent neighbors by $1$. If any neighbor's indegree becomes $0$, it is pushed into the queue.

::: keypoint
Kahn's Algorithm naturally adapts to cycle detection: if the graph contains a cycle, the vertices in the cycle will never reach an indegree of $0$, meaning they will never be added to the queue. The final sorted array will contain fewer than $V$ vertices.
:::

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> topologicalSortKahn(int V, const vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    for (int i = 0; i < V; ++i) {
        for (int neighbor : adj[i]) {
            indegree[neighbor]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    return topo;
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);
    
    vector<int> topo = topologicalSortKahn(V, adj);
    for (int node : topo) {
        cout << node << " ";
    }
    cout << "\n";
    return 0;
}
```

**Complexity:**
Time: $O(V + E)$ since initializing indegrees and BFS traversal processes each vertex and each edge exactly once.
Space: $O(V)$ for the indegree array and the queue.

**Practice:** https://practice.geeksforgeeks.org/problems/topological-sort/1

### Detect a Cycle in a Directed Graph using Kahn's Algorithm

**Intuition / approach:**
Building directly on Kahn's Algorithm, we can determine whether a directed graph contains a cycle. In a DAG, Kahn's Algorithm will successfully process and extract all $V$ vertices. If there is a cycle, the cyclic dependencies mean that the vertices within the cycle (and any vertices reachable from them) will never have their indegrees drop to $0$. Consequently, they will never enter the queue. By counting the number of vertices appended to our topological ordering (or simply comparing the result size to $V$), we can detect a cycle: if the count is equal to $V$, it is a DAG (no cycle); if the count is less than $V$, a cycle exists.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isCyclic(int V, const vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    for (int i = 0; i < V; ++i) {
        for (int neighbor : adj[i]) {
            indegree[neighbor]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    // If we processed all V nodes, there is no cycle.
    return count != V;
}

int main() {
    int V = 4;
    vector<vector<int>> adj(V);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(3);
    adj[3].push_back(1); // Cycle here
    
    if (isCyclic(V, adj)) {
        cout << "Cycle detected.\n";
    } else {
        cout << "No cycle detected.\n";
    }
    return 0;
}
```

**Complexity:**
Time: $O(V + E)$ to traverse the graph and compute indegrees, and to process nodes in the queue.
Space: $O(V)$ for the indegree array and queue memory.

**Practice:** https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1

### Course Schedule I

Given a total number of courses `numCourses` and a list of prerequisite pairs `[course, prerequisite]`, determine if it is possible to finish all courses. 

**Intuition / approach:**
This is a direct application of cycle detection in a directed graph. Each prerequisite pair `[u, v]` represents a directed edge from `v` to `u` (since course `v` must be taken before course `u`). If there is a cycle in the resulting graph, it is impossible to complete the courses involved in the cycle. We can build the adjacency list and apply Kahn's Algorithm to check if a topological sort of all `numCourses` nodes is possible. If we can process all nodes, then all courses can be completed.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool canFinish(int numCourses, const vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);
    
    for (const auto& pre : prerequisites) {
        int course = pre[0];
        int prereq = pre[1];
        adj[prereq].push_back(course);
        indegree[course]++;
    }
    
    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;
        
        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    return count == numCourses;
}

int main() {
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1, 0}, {0, 1}};
    
    if (canFinish(numCourses, prerequisites)) {
        cout << "Can finish all courses.\n";
    } else {
        cout << "Cannot finish all courses.\n";
    }
    return 0;
}
```

**Complexity:**
Time: $O(V + E)$ where $V$ is `numCourses` and $E$ is the number of prerequisites, to construct the graph and perform Kahn's Algorithm.
Space: $O(V + E)$ to store the adjacency list representation, plus $O(V)$ for the indegree array and queue.

**Practice:** https://leetcode.com/problems/course-schedule/

### Course Schedule II

Given the number of courses and their prerequisites, return the ordering of courses to take to finish all courses. If there are multiple valid answers, return any of them. If it is impossible, return an empty array.

**Intuition / approach:**
Instead of just returning a boolean indicating if it is possible to finish the courses (like in Course Schedule I), we must return the actual topological order. We use Kahn's Algorithm. As we dequeue a node with a zero indegree, we append it to our result array. If at the end, our result array size does not equal `numCourses` (indicating a cycle), we return an empty array. Otherwise, the result array contains a valid course sequence.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> findOrder(int numCourses, const vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);
    
    for (const auto& pre : prerequisites) {
        int course = pre[0];
        int prereq = pre[1];
        adj[prereq].push_back(course);
        indegree[course]++;
    }
    
    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> order;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);
        
        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    if (order.size() == numCourses) {
        return order;
    }
    return {};
}

int main() {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    
    vector<int> order = findOrder(numCourses, prerequisites);
    for (int course : order) {
        cout << course << " ";
    }
    cout << "\n";
    return 0;
}
```

**Complexity:**
Time: $O(V + E)$ where $V$ is `numCourses` and $E$ is the number of prerequisite relations.
Space: $O(V + E)$ to create the graph structures, plus $O(V)$ for the indegree array and queue.

**Practice:** https://leetcode.com/problems/course-schedule-ii/

### Find Eventual Safe States

Given a directed graph, find all eventual safe nodes. A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node). Return the safe nodes sorted in ascending order.

**Intuition / approach:**
A node is unsafe if it is part of a cycle, or if there is a path from it to a cycle. A node is safe if all paths emanating from it terminate without getting trapped in a cycle. We can reverse the direction of all edges in the graph. In the reversed graph, the terminal nodes of the original graph will now have an indegree of $0$. By applying Kahn's Algorithm on this reversed graph, we start from terminal nodes and work backwards. Any node that gets added to our topological order (queue) is a safe node. The nodes left with a non-zero indegree after Kahn's algorithm finishes are those involved in, or pointing to, a cycle. Finally, we sort the safe nodes to satisfy the problem requirements.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> eventualSafeNodes(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> reversedGraph(V);
    vector<int> indegree(V, 0);

    for (int i = 0; i < V; ++i) {
        for (int neighbor : graph[i]) {
            reversedGraph[neighbor].push_back(i);
            indegree[i]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> safeNodes;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        safeNodes.push_back(node);

        for (int neighbor : reversedGraph[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    sort(safeNodes.begin(), safeNodes.end());
    return safeNodes;
}

int main() {
    vector<vector<int>> graph = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    vector<int> safe = eventualSafeNodes(graph);
    for (int node : safe) {
        cout << node << " ";
    }
    cout << "\n";
    return 0;
}
```

**Complexity:**
Time: $O(V + E \log V)$. Finding safe states takes $O(V + E)$ where $V$ and $E$ are nodes and edges. Sorting the resulting safe nodes takes $O(V \log V)$ in the worst case (where all nodes are safe).
Space: $O(V + E)$ for constructing the reversed graph and keeping track of indegrees.

**Practice:** https://leetcode.com/problems/find-eventual-safe-states/

### Alien Dictionary

Given a sorted dictionary of an alien language with an unknown alphabet order, find the order of characters in the alien language.

::: heavy
This problem requires synthesizing information to derive rules. The core realization is that the sorted words dictate relative orderings of individual characters. If "apple" comes before "ape", the first differing character implies 'p' must come before 'e' in their alphabet.
:::

**Intuition / approach:**
We compare adjacent words in the sorted dictionary to uncover character dependencies. For a pair of adjacent words `word1` and `word2`, we find the first index `j` where `word1[j] != word2[j]`. This difference creates a directed edge `word1[j] -> word2[j]`, implying that `word1[j]` appears before `word2[j]` in the alien alphabet.
Once all such edges are extracted, this becomes a topological sorting problem on the characters. We can use Kahn's Algorithm to find the topological sort of these characters. If we detect a cycle, or if a longer word precedes a shorter word which is a prefix of it (e.g., "abcd" before "abc"), the dictionary is invalid, and no ordering exists.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

string findAlienOrder(int K, const vector<string>& dict) {
    vector<vector<int>> adj(K);
    vector<int> indegree(K, 0);

    for (int i = 0; i < dict.size() - 1; i++) {
        string word1 = dict[i];
        string word2 = dict[i + 1];
        
        // Edge case: word1 is larger but word2 is a prefix of word1
        if (word1.length() > word2.length() && word1.substr(0, word2.length()) == word2) {
            return "";
        }

        int minLen = min(word1.length(), word2.length());
        for (int j = 0; j < minLen; j++) {
            if (word1[j] != word2[j]) {
                adj[word1[j] - 'a'].push_back(word2[j] - 'a');
                indegree[word2[j] - 'a']++;
                break;
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < K; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    string order = "";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order += (char)(node + 'a');

        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (order.length() != K) {
        return "";
    }
    return order;
}

int main() {
    int K = 4;
    vector<string> dict = {"baa", "abcd", "abca", "cab", "cad"};
    string order = findAlienOrder(K, dict);
    cout << order << "\n";
    return 0;
}
```

**Complexity:**
Time: $O(C + K + E)$ where $C$ is the total length of all words in the dictionary (for building the graph), $K$ is the number of alphabets, and $E$ is the number of relations (at most $N-1$ where $N$ is the number of words).
Space: $O(K + E)$ for the adjacency list and indegree array, tracking up to $K$ characters and their $E$ relationships.

**Practice:** https://practice.geeksforgeeks.org/problems/alien-dictionary/1

## Shortest-Path Algorithms

::: keypoint
Mapping the problem to the right shortest-path algorithm is crucial:
- **Unit weights / unweighted:** Breadth-First Search (BFS).
- **Directed Acyclic Graph (DAG):** Topological Sort + Relaxation.
- **Non-negative weights (single source):** Dijkstra's Algorithm.
- **Negative edges / negative cycle detection (single source):** Bellman-Ford Algorithm.
- **All-pairs shortest path:** Floyd-Warshall Algorithm.
:::

### Shortest Path in an Undirected Graph with Unit Weights
Find the shortest path from a source vertex to all other vertices in an undirected graph where every edge has a weight of $1$.

**Intuition:** Since all edge weights are $1$, the distance to any node is simply the number of edges traversed. BFS explores nodes level by level, ensuring that the first time we visit a node, we have found the shortest path to it. We use a standard queue and an array to keep track of distances, initialized to infinity.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> shortestPath(vector<vector<int>>& adj, int src, int n) {
    vector<int> dist(n, 1e9);
    queue<int> q;
    
    dist[src] = 0;
    q.push(src);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbor : adj[node]) {
            if (dist[node] + 1 < dist[neighbor]) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (dist[i] == 1e9) {
            dist[i] = -1; // Unreachable
        }
    }
    return dist;
}

int main() {
    int n = 4;
    vector<vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[1].push_back(2); adj[2].push_back(1);
    adj[2].push_back(3); adj[3].push_back(2);
    adj[0].push_back(3); adj[3].push_back(0);
    
    vector<int> dist = shortestPath(adj, 0, n);
    for (int d : dist) cout << d << " ";
    return 0;
}
```

**Complexity:**
- **Time:** $O(V + E)$, as it is a standard BFS traversal.
- **Space:** $O(V)$ for the queue and distance array.

**Practice:** https://practice.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1

### Shortest Path in a DAG
Find the shortest path from a source vertex to all other vertices in a Directed Acyclic Graph (DAG) with weighted edges.

**Intuition:** In a DAG, there are no cycles, which means we can process the vertices in topological order. By processing nodes such that all incoming edges to a node are relaxed before the node itself is processed, we guarantee the shortest path to each node in a single pass. This avoids the overhead of Dijkstra's algorithm.

```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void topoSort(int node, vector<vector<pair<int, int>>>& adj, vector<bool>& vis, stack<int>& st) {
    vis[node] = true;
    for (auto& edge : adj[node]) {
        int v = edge.first;
        if (!vis[v]) {
            topoSort(v, adj, vis, st);
        }
    }
    st.push(node);
}

vector<int> shortestPathDAG(int n, int m, vector<vector<int>>& edges, int src) {
    vector<vector<pair<int, int>>> adj(n);
    for (auto& edge : edges) {
        adj[edge[0]].push_back({edge[1], edge[2]});
    }
    
    vector<bool> vis(n, false);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            topoSort(i, adj, vis, st);
        }
    }
    
    vector<int> dist(n, 1e9);
    dist[src] = 0;
    
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        
        if (dist[node] != 1e9) {
            for (auto& edge : adj[node]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[node] + weight < dist[v]) {
                    dist[v] = dist[node] + weight;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (dist[i] == 1e9) dist[i] = -1;
    }
    return dist;
}

int main() {
    int n = 6, m = 7;
    vector<vector<int>> edges = {{0,1,2}, {0,4,1}, {4,5,4}, {4,2,2}, {1,2,3}, {2,3,6}, {5,3,1}};
    vector<int> dist = shortestPathDAG(n, m, edges, 0);
    for (int d : dist) cout << d << " ";
    return 0;
}
```

**Complexity:**
- **Time:** $O(V + E)$ to find the topological sort and $O(V + E)$ to relax edges, totaling $O(V + E)$.
- **Space:** $O(V + E)$ to build the adjacency list and $O(V)$ for the stack, visited, and distance arrays.

**Practice:** https://practice.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1

### Dijkstra's Algorithm using a Priority Queue

::: heavy
Dijkstra's Algorithm finds the shortest paths from a single source to all other nodes in a graph with non-negative edge weights. It is a greedy algorithm that always explores the closest unvisited node.
:::

**Intuition:** We use a min-heap (priority queue) to repeatedly extract the node with the minimum known distance from the source. When a node is extracted, we relax all its outgoing edges. If a shorter path to a neighbor is found, we push the updated distance and neighbor into the priority queue. Since all weights are non-negative, the first time a node is extracted from the heap, its shortest path is permanently finalized.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(V, 1e9);
    
    dist[src] = 0;
    pq.push({0, src}); // {distance, node}
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        
        // If we found a shorter path to the node before processing this popped pair, skip it
        if (d > dist[node]) continue;
        
        for (auto& edge : adj[node]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (dist[node] + weight < dist[v]) {
                dist[v] = dist[node] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

int main() {
    int V = 3;
    vector<vector<pair<int, int>>> adj(V);
    adj[0].push_back({1, 1});
    adj[0].push_back({2, 6});
    adj[1].push_back({2, 3});
    adj[1].push_back({0, 1});
    adj[2].push_back({1, 3});
    adj[2].push_back({0, 6});
    
    vector<int> dist = dijkstra(V, adj, 2);
    for (int d : dist) cout << d << " ";
    return 0;
}
```

**Complexity:**
- **Time:** $O(E \log V)$, because each edge can cause an insertion into the priority queue, and the queue contains at most $V$ elements (with lazy deletion/skipping it can be $E$, but $O(E \log V)$ is the standard loose bound).
- **Space:** $O(V)$ for the distance array and the priority queue.

**Practice:** https://practice.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1

### Dijkstra's Algorithm using a Set
Find the shortest paths from a single source to all other nodes in a graph with non-negative edge weights, this time using a `set` instead of a `priority_queue`.

**Intuition:** A `set` in C++ stores unique elements in sorted order. Like a min-heap, `set.begin()` gives the minimum distance node. The advantage of a `set` over a `priority_queue` is that we can easily erase an existing worse distance before inserting a better one, thus keeping the set size strictly $\le V$. This saves space and unnecessary iterations, though the asymptotic time complexity remains the same due to tree rebalancing.

```cpp
#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> dijkstraSet(int V, vector<vector<pair<int, int>>>& adj, int src) {
    set<pair<int, int>> st;
    vector<int> dist(V, 1e9);
    
    dist[src] = 0;
    st.insert({0, src});
    
    while (!st.empty()) {
        auto it = *(st.begin());
        int d = it.first;
        int node = it.second;
        st.erase(st.begin());
        
        for (auto& edge : adj[node]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (dist[node] + weight < dist[v]) {
                // If a path already exists, erase it to avoid redundancy
                if (dist[v] != 1e9) {
                    st.erase({dist[v], v});
                }
                
                dist[v] = dist[node] + weight;
                st.insert({dist[v], v});
            }
        }
    }
    
    return dist;
}

int main() {
    int V = 3;
    vector<vector<pair<int, int>>> adj(V);
    adj[0].push_back({1, 1});
    adj[0].push_back({2, 6});
    adj[1].push_back({2, 3});
    adj[1].push_back({0, 1});
    adj[2].push_back({1, 3});
    adj[2].push_back({0, 6});
    
    vector<int> dist = dijkstraSet(V, adj, 2);
    for (int d : dist) cout << d << " ";
    return 0;
}
```

**Complexity:**
- **Time:** $O(E \log V)$.
- **Space:** $O(V)$ for the set and distance array. The set never exceeds $V$ elements.

**Practice:** https://practice.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1

### Print the Shortest Path
Given a weighted, undirected graph and a source and destination, return the shortest path (the sequence of vertices) from $1$ to $n$.

**Intuition:** While computing Dijkstra's algorithm, whenever we relax an edge and update the shortest distance to node $v$ from $u$, it implies that $u$ is the optimal predecessor to $v$. We maintain a `parent` array to store this predecessor. After reaching the destination, we backtrack using the `parent` array to reconstruct the full path, then reverse it.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> printShortestPath(int n, int m, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto& edge : edges) {
        adj[edge[0]].push_back({edge[1], edge[2]});
        adj[edge[1]].push_back({edge[0], edge[2]});
    }
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n + 1, 1e9);
    vector<int> parent(n + 1);
    
    for (int i = 1; i <= n; i++) parent[i] = i;
    
    dist[1] = 0;
    pq.push({0, 1});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        
        if (d > dist[node]) continue;
        
        for (auto& edge : adj[node]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (dist[node] + weight < dist[v]) {
                dist[v] = dist[node] + weight;
                pq.push({dist[v], v});
                parent[v] = node;
            }
        }
    }
    
    if (dist[n] == 1e9) return {-1};
    
    vector<int> path;
    int node = n;
    while (parent[node] != node) {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(1);
    reverse(path.begin(), path.end());
    
    return path;
}

int main() {
    int n = 5, m = 6;
    vector<vector<int>> edges = {{1,2,2}, {2,5,5}, {2,3,4}, {1,4,1}, {4,3,3}, {3,5,1}};
    vector<int> path = printShortestPath(n, m, edges);
    for (int node : path) cout << node << " ";
    return 0;
}
```

**Complexity:**
- **Time:** $O(E \log V)$ for Dijkstra's, plus $O(V)$ to reconstruct and reverse the path. Overall $O(E \log V)$.
- **Space:** $O(V + E)$ for the adjacency list and $O(V)$ for the priority queue, distance array, and parent array.

**Practice:** https://practice.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1

### Shortest Path in a Binary Maze
Given an $N \times M$ grid containing only $0$s and $1$s, find the length of the shortest path from a source cell to a destination cell. You can move in 4 directions, only on cells with $1$.

**Intuition:** Since every step to an adjacent cell counts as a unit distance (weight $1$), BFS is optimal. We don't need the overhead of Dijkstra's algorithm. We push the source into a queue and do a standard level-order exploration. The first time we hit the destination, that path is guaranteed to be the shortest.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int shortestPathBinaryMatrix(vector<vector<int>>& grid, pair<int, int> source, pair<int, int> destination) {
    if (grid[source.first][source.second] == 0 || grid[destination.first][destination.second] == 0) return -1;
    if (source.first == destination.first && source.second == destination.second) return 0;
    
    int n = grid.size();
    int m = grid[0].size();
    
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[source.first][source.second] = 0;
    
    queue<pair<int, pair<int, int>>> q; // {distance, {row, col}}
    q.push({0, {source.first, source.second}});
    
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    
    while (!q.empty()) {
        auto it = q.front();
        q.pop();
        int d = it.first;
        int r = it.second.first;
        int c = it.second.second;
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1 && d + 1 < dist[nr][nc]) {
                dist[nr][nc] = d + 1;
                if (nr == destination.first && nc == destination.second) return d + 1;
                q.push({d + 1, {nr, nc}});
            }
        }
    }
    return -1;
}

int main() {
    vector<vector<int>> grid = {{1, 1, 1, 1},
                                {1, 1, 0, 1},
                                {1, 1, 1, 1},
                                {1, 1, 0, 0},
                                {1, 0, 0, 1}};
    cout << shortestPathBinaryMatrix(grid, {0, 1}, {2, 2}) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(V) = O(N \times M)$ because every cell is visited at most once.
- **Space:** $O(V) = O(N \times M)$ for the distance matrix and queue.

**Practice:** https://leetcode.com/problems/shortest-path-in-binary-matrix/ (Note: LeetCode uses 8 directions and considers distance differently, adjust rules accordingly.)

### Path With Minimum Effort
Find a path from the top-left to the bottom-right cell of a grid such that the maximum absolute difference in heights between consecutive cells on the path (the "effort") is minimized.

**Intuition:** This is a variant of the shortest path problem. Instead of minimizing the sum of edge weights, we want to minimize the maximum edge weight on the path. We use Dijkstra's algorithm. The distance to a cell becomes the maximum effort required to reach it. When relaxing an edge, the new effort to a neighbor is the maximum of the effort to the current cell and the height difference to the neighbor.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int minimumEffortPath(vector<vector<int>>& heights) {
    int n = heights.size();
    int m = heights[0].size();
    
    priority_queue<pair<int, pair<int, int>>, 
                   vector<pair<int, pair<int, int>>>, 
                   greater<pair<int, pair<int, int>>>> pq;
                   
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[0][0] = 0;
    pq.push({0, {0, 0}});
    
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    
    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();
        int diff = it.first;
        int r = it.second.first;
        int c = it.second.second;
        
        if (r == n - 1 && c == m - 1) return diff;
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                int newEffort = max(diff, abs(heights[r][c] - heights[nr][nc]));
                if (newEffort < dist[nr][nc]) {
                    dist[nr][nc] = newEffort;
                    pq.push({newEffort, {nr, nc}});
                }
            }
        }
    }
    return 0; 
}

int main() {
    vector<vector<int>> heights = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
    cout << minimumEffortPath(heights) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(E \log V) = O(N \times M \log (N \times M))$ because each of the $4$ neighbors is relaxed using a priority queue.
- **Space:** $O(N \times M)$ for the distance array and priority queue.

**Practice:** https://leetcode.com/problems/path-with-minimum-effort/

### Cheapest Flights Within K Stops

::: keypoint
Using Dijkstra's algorithm blindly prioritizing by cost fails here because a path with a smaller cost might consume more stops. We must prioritize by the number of stops, which naturally maps to a level-by-level BFS using a standard queue.
:::

Find the cheapest flight from `src` to `dst` with at most `K` stops.

**Intuition:** We need to find the minimum cost, but the path is constrained by stops. If we use a priority queue based on cost, we might reach a node optimally by cost but exhaust our allowed stops, missing a slightly costlier path that uses fewer stops. Instead, we use a simple queue storing `{stops, {node, cost}}`. By exploring strictly in increasing order of stops, we can safely update distances without needing a priority queue.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int, int>>> adj(n);
    for (auto& flight : flights) {
        adj[flight[0]].push_back({flight[1], flight[2]});
    }
    
    // queue stores {stops, {node, cost}}
    queue<pair<int, pair<int, int>>> q;
    q.push({0, {src, 0}});
    
    vector<int> dist(n, 1e9);
    dist[src] = 0;
    
    while (!q.empty()) {
        auto it = q.front();
        q.pop();
        
        int stops = it.first;
        int node = it.second.first;
        int cost = it.second.second;
        
        if (stops > k) continue;
        
        for (auto& edge : adj[node]) {
            int adjNode = edge.first;
            int edgeWeight = edge.second;
            
            if (cost + edgeWeight < dist[adjNode]) {
                dist[adjNode] = cost + edgeWeight;
                q.push({stops + 1, {adjNode, cost + edgeWeight}});
            }
        }
    }
    
    if (dist[dst] == 1e9) return -1;
    return dist[dst];
}

int main() {
    int n = 4;
    vector<vector<int>> flights = {{0,1,100}, {1,2,100}, {2,0,100}, {1,3,600}, {2,3,200}};
    cout << findCheapestPrice(n, flights, 0, 3, 1) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(V + E)$ because each node is processed strictly by steps; within $K$ steps we do a bounded BFS traversal.
- **Space:** $O(V + E)$ for the adjacency list and $O(V)$ for the queue and distance array.

**Practice:** https://leetcode.com/problems/cheapest-flights-within-k-stops/

### Network Delay Time
Given a network of $N$ nodes labeled $1$ to $N$, with directed weighted edges representing signal travel times, find how long it takes for a signal sent from a given source node to reach all other nodes.

**Intuition:** This is a classic single-source shortest path problem on a directed graph with non-negative edge weights. We use Dijkstra's algorithm to compute the shortest time from the source to all nodes. The total time required to reach all nodes is simply the maximum of these shortest times. If any node is unreachable, the distance remains infinity, and we return `-1`.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto& time : times) {
        adj[time[0]].push_back({time[1], time[2]});
    }
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n + 1, 1e9);
    
    dist[k] = 0;
    pq.push({0, k});
    
    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();
        
        int time = it.first;
        int node = it.second;
        
        if (time > dist[node]) continue;
        
        for (auto& edge : adj[node]) {
            int adjNode = edge.first;
            int waitTime = edge.second;
            
            if (time + waitTime < dist[adjNode]) {
                dist[adjNode] = time + waitTime;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }
    
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == 1e9) return -1;
        mx = max(mx, dist[i]);
    }
    return mx;
}

int main() {
    vector<vector<int>> times = {{2,1,1}, {2,3,1}, {3,4,1}};
    cout << networkDelayTime(times, 4, 2) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(E \log V)$ for standard Dijkstra's algorithm.
- **Space:** $O(V + E)$ to store the graph and $O(V)$ for the priority queue and distance array.

**Practice:** https://leetcode.com/problems/network-delay-time/

### Number of Ways to Arrive at Destination
Find the number of ways to travel from node $0$ to node $N-1$ in the shortest possible time.

**Intuition:** We run Dijkstra's algorithm. Along with the standard `dist` array, we maintain a `ways` array initialized to $0$ (and `ways[src] = 1`). During relaxation, if we find a *strictly shorter* path to an adjacent node, we update `dist` and reset its `ways` to the current node's `ways`. If we find a path that is *exactly equal* to the known shortest distance, we add the current node's `ways` to the adjacent node's `ways`. Because weights can be large, we must use `long long` for distances and take results modulo $10^9+7$.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int countPaths(int n, vector<vector<int>>& roads) {
    vector<vector<pair<int, int>>> adj(n);
    for (auto& road : roads) {
        adj[road[0]].push_back({road[1], road[2]});
        adj[road[1]].push_back({road[0], road[2]});
    }
    
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    vector<long long> dist(n, 1e18);
    vector<long long> ways(n, 0);
    
    int mod = 1e9 + 7;
    dist[0] = 0;
    ways[0] = 1;
    pq.push({0, 0});
    
    while (!pq.empty()) {
        long long d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        
        if (d > dist[node]) continue;
        
        for (auto& edge : adj[node]) {
            int adjNode = edge.first;
            long long edgeWeight = edge.second;
            
            if (d + edgeWeight < dist[adjNode]) {
                dist[adjNode] = d + edgeWeight;
                pq.push({dist[adjNode], adjNode});
                ways[adjNode] = ways[node];
            } else if (d + edgeWeight == dist[adjNode]) {
                ways[adjNode] = (ways[adjNode] + ways[node]) % mod;
            }
        }
    }
    
    return ways[n - 1];
}

int main() {
    int n = 7;
    vector<vector<int>> roads = {{0,6,7}, {0,1,2}, {1,2,3}, {1,3,3}, {6,3,3}, {3,5,1}, {6,5,1}, {2,5,1}, {0,4,5}, {4,6,2}};
    cout << countPaths(n, roads) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(E \log V)$ for Dijkstra's algorithm.
- **Space:** $O(V + E)$ for adjacency list and $O(V)$ for auxiliary structures.

**Practice:** https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/

### Bellman-Ford Algorithm

::: keypoint
Dijkstra's algorithm can fail on graphs with negative edge weights and will infinitely loop on negative cycles. Bellman-Ford can handle negative weights and is the standard algorithm to detect negative weight cycles.
:::

Find the shortest paths from a single source to all vertices, and detect if a negative weight cycle exists.

**Intuition:** The shortest path in a graph with $V$ vertices can have at most $V-1$ edges. Bellman-Ford relaxes all edges $V-1$ times. By the end of these iterations, the shortest distances are guaranteed to be correct if there is no negative cycle. If we relax all edges one more time (the $V$-th iteration) and any distance updates, it implies there is a cycle whose total weight is strictly negative.

```cpp
#include <iostream>
#include <vector>

using namespace std;

vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
    vector<int> dist(V, 1e8); // Problem constraint usually specifies 1e8 for infinity
    dist[S] = 0;
    
    // Relax edges V - 1 times
    for (int i = 0; i < V - 1; i++) {
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            
            if (dist[u] != 1e8 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // N-th relaxation to detect negative cycle
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];
        
        if (dist[u] != 1e8 && dist[u] + weight < dist[v]) {
            return {-1}; // Returns {-1} if a negative cycle is detected
        }
    }
    
    return dist;
}

int main() {
    int V = 3;
    vector<vector<int>> edges = {{0,1,5}, {1,0,3}, {1,2,-1}, {2,0,1}};
    vector<int> dist = bellman_ford(V, edges, 2);
    for (int d : dist) cout << d << " ";
    return 0;
}
```

**Complexity:**
- **Time:** $O(V \times E)$ because we iterate over all $E$ edges $V$ times.
- **Space:** $O(V)$ for the distance array.

**Practice:** https://practice.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1

### Floyd-Warshall Algorithm

::: keypoint
While Dijkstra and Bellman-Ford are Single-Source Shortest Path algorithms, Floyd-Warshall is a Multi-Source (All-Pairs) Shortest Path algorithm. It calculates the shortest path between every pair of vertices in $O(V^3)$ time using dynamic programming.
:::

Find the shortest distance between all pairs of vertices in an edge-weighted directed graph.

**Intuition:** For every pair of nodes $(i, j)$, we try to see if going through an intermediate node $k$ gives a shorter path than the direct edge. We test every possible intermediate node $k$ from $0$ to $V-1$. The DP state transition is $matrix[i][j] = \min(matrix[i][j], matrix[i][k] + matrix[k][j])$. A negative cycle is detected if any $matrix[i][i] < 0$.

```cpp
#include <iostream>
#include <vector>

using namespace std;

void shortest_distance(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    // Replace -1 with infinity for calculation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == -1) {
                matrix[i][j] = 1e9;
            }
            if (i == j) matrix[i][j] = 0;
        }
    }
    
    // Try all possible intermediate nodes k
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][k] != 1e9 && matrix[k][j] != 1e9) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }
    }
    
    // Revert infinity to -1 for unreachable nodes
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1e9) {
                matrix[i][j] = -1;
            }
        }
    }
}

int main() {
    vector<vector<int>> matrix = {{0, 25}, {-1, 0}};
    shortest_distance(matrix);
    for (auto& row : matrix) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }
    return 0;
}
```

**Complexity:**
- **Time:** $O(V^3)$ because of the three nested loops over vertices.
- **Space:** $O(V^2)$ to store the distance matrix (often given in-place).

**Practice:** https://practice.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1

### Find the City With the Smallest Number of Neighbours at a Threshold Distance
Given $N$ cities and edges representing weights, find the city which has the smallest number of reachable cities within a `distanceThreshold`. If there is a tie, return the city with the greatest number.

**Intuition:** We need the shortest path from every node to every other node to count reachable neighbors within the threshold. This makes it a perfect candidate for the Floyd-Warshall algorithm. After building the shortest path matrix, we just iterate through each city to count its valid neighbors and select the optimal one.

```cpp
#include <iostream>
#include <vector>

using namespace std;

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> dist(n, vector<int>(n, 1e9));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    
    for (auto& edge : edges) {
        dist[edge[0]][edge[1]] = edge[2];
        dist[edge[1]][edge[0]] = edge[2];
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != 1e9 && dist[k][j] != 1e9) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    int minReachable = n;
    int cityNo = -1;
    
    for (int i = 0; i < n; i++) {
        int reachableCount = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] <= distanceThreshold) {
                reachableCount++;
            }
        }
        
        if (reachableCount <= minReachable) {
            minReachable = reachableCount;
            cityNo = i;
        }
    }
    
    return cityNo;
}

int main() {
    int n = 4, distanceThreshold = 4;
    vector<vector<int>> edges = {{0,1,3}, {1,2,1}, {1,3,4}, {2,3,1}};
    cout << findTheCity(n, edges, distanceThreshold) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(V^3)$ due to the Floyd-Warshall DP.
- **Space:** $O(V^2)$ to store the shortest paths matrix.

**Practice:** https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/

## Minimum Spanning Tree, Disjoint Set & SCC

### 1. Minimum Spanning Tree

::: definition
A **Minimum Spanning Tree (MST)** is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles, and with the minimum possible total edge weight.
:::

A spanning tree of a graph with $V$ vertices always has exactly $V - 1$ edges. If a graph is not connected, it has a Minimum Spanning Forest.

#### What an MST does *not* give you

Two properties are assumed far more often than they are true, and both misconceptions cost interview answers.

::: trap
**An MST does not contain the shortest path between two nodes.** An MST minimises the **global total weight** needed to connect every vertex. It carries no obligation whatsoever to optimise the **distance between any specific pair**. For pairwise shortest paths you need a shortest-path tree — Dijkstra or Bellman-Ford from a source — which is a different tree built to a different objective.

The smallest counterexample is a triangle on $\{A, B, C\}$ with

```
A—B = 2,   B—C = 2,   A—C = 3
```

The MST takes $A\!-\!B$ and $B\!-\!C$ for a total weight of 4, dropping the $A\!-\!C$ edge as the most expensive. So the only $A \to C$ route **in the MST** is $A \to B \to C$, of length **4** — while the original graph has a direct $A \to C$ edge of length **3**. The MST made the path between $A$ and $C$ longer, in exchange for keeping the spanning weight as low as possible. That trade is the entire point of an MST, and it is why the two objectives cannot be served by one tree.
:::

::: keypoint
**There is exactly one path between any two nodes in an MST**, and this one *is* guaranteed — by definition rather than by algorithm. An MST is a spanning **tree**, and the defining property of a tree is that it is connected and acyclic. If two distinct paths existed between some pair of nodes, their union would contain a cycle, contradicting acyclicity. So the path is unique — it is simply not necessarily the shortest one in the original graph.
:::

#### The directed case: arborescences

Prim's and Kruskal's both assume an **undirected** graph. The directed analogue is a different problem with a different name and a different algorithm, and reaching for Kruskal's on a directed graph is a classic error.

::: definition
A **Minimum Weight Arborescence** (also called a Directed Minimum Spanning Tree, DMST) is the directed equivalent of an MST: given a root $r$, it is the minimum-weight set of edges such that every other vertex is reachable from $r$ by exactly one directed path.
:::

The structural requirements are stricter than in the undirected case:

1. You must pick a **root**. Unlike an MST, the answer depends on which vertex it is.
2. Every non-root vertex must have **in-degree exactly one**.
3. The root must have **in-degree zero**.

::: trap
**Why Prim's and Kruskal's fail on directed graphs.** Kruskal's sorts edges by weight and adds any edge that does not form a cycle — but in a directed graph "does not form a cycle" is not sufficient, because a set of edges can be acyclic and still leave a vertex with two incoming edges or a vertex unreachable from the root. Prim's grows from a start vertex by repeatedly taking the cheapest edge leaving the current set, which in a directed graph can commit to a cheap outgoing edge and then find that some vertex can only be reached expensively — or not at all. Both are greedy on the wrong invariant.

Note also that the answer genuinely changes with the root: change the start vertex and you may get a completely different arborescence, or find that none exists at all if some vertex is unreachable.
:::

The algorithm is **Edmonds' algorithm** (also called Chu–Liu/Edmonds). The idea in outline:

1. For every vertex except the root, greedily select its cheapest **incoming** edge.
2. If that selection contains no cycle, it is already the answer — every non-root vertex has in-degree 1 and the structure is a valid arborescence.
3. If it does contain a cycle, **contract** the cycle into a single super-node, adjust the weights of edges entering and leaving the contracted cycle to account for the edge that would be displaced, and recurse on the smaller graph. Expanding the contractions back out yields the arborescence.

This is well outside the range of a typical OA, but knowing that the directed problem *is different*, has a name, and is not solved by Kruskal's is a realistic interview discriminator.

### 2. Prim's Algorithm

Given a weighted, undirected graph, find the sum of weights of the edges of the Minimum Spanning Tree.

**Intuition**:
Prim's algorithm is a greedy approach. It starts from an arbitrary node and grows the MST one edge at a time. It maintains a priority queue of edges that connect the tree vertices to the non-tree vertices. In each step, it selects the minimum weight edge from the priority queue that connects a tree vertex to a non-tree vertex, adds it to the MST, and marks the new vertex as visited.

::: keypoint
Prim's algorithm uses a priority queue (min-heap) to always pick the smallest edge that expands the current spanning tree.
:::

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int spanningTree(int V, vector<vector<int>> adj[]) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> vis(V, 0);
        
        // {weight, node}
        pq.push({0, 0});
        int sum = 0;
        
        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            
            int wt = it.first;
            int node = it.second;
            
            if (vis[node] == 1) continue;
            
            // Add to MST
            vis[node] = 1;
            sum += wt;
            
            for (auto it : adj[node]) {
                int adjNode = it[0];
                int edW = it[1];
                if (!vis[adjNode]) {
                    pq.push({edW, adjNode});
                }
            }
        }
        return sum;
    }
};

int main() {
    int V = 5;
    vector<vector<int>> adj[V];
    adj[0].push_back({1, 2}); adj[1].push_back({0, 2});
    adj[1].push_back({2, 3}); adj[2].push_back({1, 3});
    adj[0].push_back({3, 6}); adj[3].push_back({0, 6});
    adj[1].push_back({3, 8}); adj[3].push_back({1, 8});
    adj[1].push_back({4, 5}); adj[4].push_back({1, 5});
    adj[2].push_back({4, 7}); adj[4].push_back({2, 7});
    
    Solution obj;
    cout << "Sum of MST: " << obj.spanningTree(V, adj) << "\n";
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(E \log E)$ where $E$ is the number of edges. In the worst case, all edges can be pushed to the priority queue.
- Space Complexity: $O(E + V)$ for the priority queue and visited array.

**Practice:** https://practice.geeksforgeeks.org/problems/minimum-spanning-tree/1

### 3. Disjoint Set Union

::: heavy
The Disjoint Set Union (DSU) or Union-Find data structure tracks a set of elements partitioned into a number of disjoint (non-overlapping) subsets. It provides near-constant time operations to add new sets, to merge existing sets, and to determine whether elements are in the same set.
:::

**Intuition**:
DSU maintains a forest of trees. Each tree represents a set, and the root of the tree is the representative element of the set. 
- **Find** traverses the parent pointers to reach the root. Path compression flattens the tree structure by making every visited node point directly to the root, drastically speeding up future operations.
- **Union** merges two sets. Union by rank (or size) ensures that the smaller tree is attached to the root of the larger tree, preventing the tree from becoming a long chain.

::: keypoint
**The DSU is a sidecar, not a view of your graph.** This is the misconception that makes path compression feel alarming the first time you meet it. The `parent[]` array is a **separate data structure** maintained alongside your adjacency list — it is not a representation of the graph, and mutating it does not touch a single edge of the original.

The two structures interpret an edge $(u, v)$ completely differently:

- Your **adjacency list** treats it as a *traversal path*: "you can physically walk from $u$ to $v$." Structure is preserved exactly as given.
- Your **DSU** treats it as an *identity claim*: "$u$ and $v$ are in the same component, so I will keep one representative for both."

So when path compression re-points a node directly at its root, it is not flattening your graph — it is flattening the DSU's private bookkeeping about *which component each node belongs to*. That bookkeeping is allowed to become a shallow "forest of stars" that looks nothing like the graph's real shape, because the only question it ever has to answer is *"are these two in the same component?"*. Discarding path information is not a loss; path information was never its job.
:::

That trade is what buys the complexity. Because the DSU is free to reshape itself, path compression combined with union by rank gives an amortised $O(\alpha(V))$ per operation, where $\alpha$ is the inverse Ackermann function. $\alpha$ grows so slowly that for any $V$ that could physically be stored — past the number of atoms in the observable universe — it is at most 4. It is not literally $O(1)$, and the distinction matters in a theory discussion, but no practical input separates them.

```cpp
#include <vector>

using namespace std;

class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]); // Path compression
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

int main() {
    DisjointSet ds(7);
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);
    
    // Check if 3 and 7 are in the same component
    if (ds.findUPar(3) == ds.findUPar(7)) {
        // They are not initially
    }
    
    ds.unionBySize(3, 7);
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(\alpha(V))$ per operation, where $\alpha$ is the inverse Ackermann function, effectively a constant $O(1)$.
- Space Complexity: $O(V)$ for the parent, rank, and size arrays.

### 4. Kruskal's Algorithm

Given a weighted, undirected graph, find the sum of weights of the edges of the Minimum Spanning Tree using Kruskal's algorithm.

**Intuition**:
Sort all edges in non-decreasing order of their weight. Iterate through the sorted edges, and for each edge, check if its endpoints belong to different sets using DSU. If they do, include the edge in the MST and union the two sets. If they are in the same set, including the edge would form a cycle, so ignore it.

::: keypoint
Kruskal's algorithm relies on sorting all edges by weight and using a Disjoint Set to greedily pick edges that do not form cycles.
:::

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DisjointSet {
    vector<int> parent, size;
public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    int spanningTree(int V, vector<vector<int>> adj[]) {
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                int adjNode = it[0];
                int wt = it[1];
                int node = i;
                // Add only one direction to avoid duplicates, though DSU handles it gracefully
                if (node < adjNode) {
                    edges.push_back({wt, {node, adjNode}});
                }
            }
        }
        
        DisjointSet ds(V);
        sort(edges.begin(), edges.end());
        int mstWt = 0;
        
        for (auto it : edges) {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;
            
            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWt += wt;
                ds.unionBySize(u, v);
            }
        }
        
        return mstWt;
    }
};

int main() {
    int V = 5;
    vector<vector<int>> adj[V];
    adj[0].push_back({1, 2}); adj[1].push_back({0, 2});
    adj[1].push_back({2, 3}); adj[2].push_back({1, 3});
    adj[0].push_back({3, 6}); adj[3].push_back({0, 6});
    adj[1].push_back({3, 8}); adj[3].push_back({1, 8});
    adj[1].push_back({4, 5}); adj[4].push_back({1, 5});
    adj[2].push_back({4, 7}); adj[4].push_back({2, 7});
    
    Solution obj;
    cout << "Sum of MST: " << obj.spanningTree(V, adj) << "\n";
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(E \log E)$ for sorting the edges, plus $O(E \cdot \alpha(V))$ for the DSU operations.
- Space Complexity: $O(E + V)$ to store the edges and the DSU arrays.

**Practice:** https://practice.geeksforgeeks.org/problems/minimum-spanning-tree/1

### 5. Number of Operations to Make a Network Connected

There are $n$ computers numbered from $0$ to $n-1$ connected by ethernet cables forming a network. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected. Return the minimum number of times you need to do this in order to make all the computers connected. If it's not possible, return -1.

**Intuition**:
To connect $n$ components into a single component, we need exactly $n - 1$ edges. Thus, if the total number of edges provided is less than $n - 1$, it is impossible. Otherwise, it is always possible. We can use DSU to count how many "extra" edges exist (edges that connect two nodes already in the same component, creating a cycle) and count the number of connected components. The answer is the number of connected components minus one, provided we have at least that many extra edges.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class DisjointSet {
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) return -1;
        
        DisjointSet ds(n);
        int extraEdges = 0;
        
        for (auto it : connections) {
            int u = it[0];
            int v = it[1];
            if (ds.findUPar(u) == ds.findUPar(v)) {
                extraEdges++;
            } else {
                ds.unionBySize(u, v);
            }
        }
        
        int componentsC = 0;
        for (int i = 0; i < n; i++) {
            if (ds.parent[i] == i) componentsC++;
        }
        
        int ans = componentsC - 1;
        if (extraEdges >= ans) return ans;
        return -1;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> connections = {{0, 1}, {0, 2}, {1, 2}};
    Solution obj;
    cout << "Operations needed: " << obj.makeConnected(n, connections) << "\n";
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(E \cdot \alpha(V) + V)$ where $E$ is the number of edges. We process all edges and then iterate over all nodes to count components.
- Space Complexity: $O(V)$ for the DSU structures.

**Practice:** https://leetcode.com/problems/number-of-operations-to-make-network-connected/

### 6. Most Stones Removed With Same Row or Column

Given a 2D plane with stones placed at integer coordinates, a stone can be removed if it shares either the same row or the same column as another stone that has not been removed. Return the maximum number of stones that can be removed.

**Intuition**:
Treat this as a graph problem where each stone is a vertex. An edge exists between two stones if they share the same row or column. All stones within a single connected component can be removed one by one until exactly one stone remains. Therefore, if there are $k$ connected components, we can leave $k$ stones and remove all others. The answer is the total number of stones minus the number of connected components. To uniquely map rows and columns into the DSU, we can offset the column index by a large number, such as the maximum possible row index.

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class DisjointSet {
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int maxRow = 0;
        int maxCol = 0;
        for (auto it : stones) {
            maxRow = max(maxRow, it[0]);
            maxCol = max(maxCol, it[1]);
        }
        
        DisjointSet ds(maxRow + maxCol + 2);
        unordered_map<int, int> stoneNodes;
        for (auto it : stones) {
            int nodeRow = it[0];
            int nodeCol = it[1] + maxRow + 1; // Offset for columns
            ds.unionBySize(nodeRow, nodeCol);
            stoneNodes[nodeRow] = 1;
            stoneNodes[nodeCol] = 1;
        }
        
        int cnt = 0;
        for (auto it : stoneNodes) {
            if (ds.findUPar(it.first) == it.first) {
                cnt++;
            }
        }
        return stones.size() - cnt;
    }
};

int main() {
    vector<vector<int>> stones = {{0,0}, {0,1}, {1,0}, {1,2}, {2,1}, {2,2}};
    Solution obj;
    cout << "Max stones removed: " << obj.removeStones(stones) << "\n";
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(N \cdot \alpha(R + C))$ where $N$ is the number of stones, and $R$ and $C$ are the maximum row and column indices.
- Space Complexity: $O(R + C)$ for the DSU arrays and hash map.

**Practice:** https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/

### 7. Accounts Merge

Given a list of accounts where each element is a list of strings, with the first element being a name, and the rest being emails representing emails of the account. Merge accounts that share at least one email, and return the accounts in the same format with emails sorted in lexicographical order.

**Intuition**:
If two accounts share an email, they belong to the same person. We can use a Disjoint Set to group emails. We iterate over the accounts and union all emails within the same account to the first email in that account. A map from email to account index helps keep track of nodes. Finally, we group emails by their ultimate parent component and attach the associated name.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class DisjointSet {
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DisjointSet ds(n);
        unordered_map<string, int> mapMailNode;
        
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string mail = accounts[i][j];
                if (mapMailNode.find(mail) == mapMailNode.end()) {
                    mapMailNode[mail] = i;
                } else {
                    ds.unionBySize(i, mapMailNode[mail]);
                }
            }
        }
        
        vector<vector<string>> mergedMail(n);
        for (auto it : mapMailNode) {
            string mail = it.first;
            int node = ds.findUPar(it.second);
            mergedMail[node].push_back(mail);
        }
        
        vector<vector<string>> ans;
        for (int i = 0; i < n; i++) {
            if (mergedMail[i].size() == 0) continue;
            sort(mergedMail[i].begin(), mergedMail[i].end());
            vector<string> temp;
            temp.push_back(accounts[i][0]);
            for (auto it : mergedMail[i]) {
                temp.push_back(it);
            }
            ans.push_back(temp);
        }
        return ans;
    }
};

int main() {
    vector<vector<string>> accounts = {
        {"John","johnsmith@mail.com","john_newyork@mail.com"},
        {"John","johnsmith@mail.com","john00@mail.com"},
        {"Mary","mary@mail.com"},
        {"John","johnnybravo@mail.com"}
    };
    Solution obj;
    vector<vector<string>> res = obj.accountsMerge(accounts);
    for (auto acc : res) {
        for (string s : acc) cout << s << " ";
        cout << "\n";
    }
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(M \log M + N \cdot K \cdot \alpha(N))$ where $N$ is the number of accounts, $K$ is the maximum number of emails per account, and $M$ is the total number of unique emails (sorting the strings dominates).
- Space Complexity: $O(M)$ to store the map of emails to node indices.

**Practice:** https://leetcode.com/problems/accounts-merge/

### 8. Number of Islands II

Given an $m \times n$ grid initially filled with water ($0$), and a list of positions where land ($1$) is sequentially added, return the number of islands after each operation. 

**Intuition**:
This is a dynamic connectivity problem on a grid. We can flatten the 2D grid into a 1D array of size $m \times n$ for the DSU. As each land cell is added, we increase the island count by 1. We then check its up to 4 orthogonal neighbors. If a neighbor is also land, and it belongs to a different component, we union the two components and decrease the island count by 1. This gives an online, efficient update for each operation.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class DisjointSet {
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        DisjointSet ds(m * n);
        vector<vector<int>> vis(m, vector<int>(n, 0));
        int cnt = 0;
        vector<int> ans;
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        for (auto it : positions) {
            int row = it[0];
            int col = it[1];
            
            if (vis[row][col] == 1) {
                ans.push_back(cnt);
                continue;
            }
            
            vis[row][col] = 1;
            cnt++;
            int nodeNo = row * n + col;
            
            for (int ind = 0; ind < 4; ind++) {
                int adjRow = row + dr[ind];
                int adjCol = col + dc[ind];
                
                if (adjRow >= 0 && adjRow < m && adjCol >= 0 && adjCol < n) {
                    if (vis[adjRow][adjCol] == 1) {
                        int adjNodeNo = adjRow * n + adjCol;
                        if (ds.findUPar(nodeNo) != ds.findUPar(adjNodeNo)) {
                            cnt--;
                            ds.unionBySize(nodeNo, adjNodeNo);
                        }
                    }
                }
            }
            ans.push_back(cnt);
        }
        return ans;
    }
};

int main() {
    int m = 3, n = 3;
    vector<vector<int>> positions = {{0,0}, {0,1}, {1,2}, {2,1}};
    Solution obj;
    vector<int> res = obj.numIslands2(m, n, positions);
    for (int count : res) cout << count << " ";
    cout << "\n";
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(Q \cdot \alpha(m \times n))$ where $Q$ is the number of operations (length of `positions`).
- Space Complexity: $O(m \times n)$ for the DSU arrays and the visited grid.

**Practice:** https://leetcode.com/problems/number-of-islands-ii/

### 9. Making a Large Island

You are given an $n \times n$ binary matrix. You are allowed to change at most one $0$ to be a $1$. Return the size of the largest island in grid after applying this operation.

**Intuition**:
First, process all $1$s in the grid using DSU to group connected cells into islands and record their sizes. Then, iterate through every $0$ in the grid. For each $0$, changing it to a $1$ potentially connects up to 4 neighboring islands. We sum the sizes of the uniquely identifiable neighboring components (using a hash set of their DSU roots) and add 1 for the changed cell itself. We keep track of the maximum size encountered.

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class DisjointSet {
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        DisjointSet ds(n * n);
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Step 1: Connect matching 1s
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (grid[row][col] == 0) continue;
                int nodeNo = row * n + col;
                for (int i = 0; i < 4; i++) {
                    int adjRow = row + dr[i];
                    int adjCol = col + dc[i];
                    if (adjRow >= 0 && adjRow < n && adjCol >= 0 && adjCol < n && grid[adjRow][adjCol] == 1) {
                        int adjNodeNo = adjRow * n + adjCol;
                        ds.unionBySize(nodeNo, adjNodeNo);
                    }
                }
            }
        }
        
        // Step 2: Try converting each 0
        int mx = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (grid[row][col] == 1) continue;
                unordered_set<int> components;
                for (int i = 0; i < 4; i++) {
                    int adjRow = row + dr[i];
                    int adjCol = col + dc[i];
                    if (adjRow >= 0 && adjRow < n && adjCol >= 0 && adjCol < n && grid[adjRow][adjCol] == 1) {
                        components.insert(ds.findUPar(adjRow * n + adjCol));
                    }
                }
                int sizeTotal = 1;
                for (auto it : components) {
                    sizeTotal += ds.size[it];
                }
                mx = max(mx, sizeTotal);
            }
        }
        
        // Edge case: what if there are no 0s?
        for (int cellNo = 0; cellNo < n * n; cellNo++) {
            mx = max(mx, ds.size[ds.findUPar(cellNo)]);
        }
        
        return mx;
    }
};

int main() {
    vector<vector<int>> grid = {{1, 0}, {0, 1}};
    Solution obj;
    cout << "Largest Island: " << obj.largestIsland(grid) << "\n";
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(V \cdot \alpha(V))$ where $V = n^2$. Each cell and its 4 neighbors are examined a constant number of times.
- Space Complexity: $O(V)$ for the DSU arrays.

**Practice:** https://leetcode.com/problems/making-a-large-island/

### 10. Bridges in a Graph

A bridge (or cut-edge) is an edge whose removal increases the number of connected components. Find all bridges in a graph.

::: heavy
Tarjan's algorithm finds bridges in a single DFS traversal by keeping track of the discovery time (`tin`) of each node and the lowest discovery time reachable (`low`) from a node. If the lowest reachable time from a child is strictly greater than the discovery time of its parent, the edge between them is a bridge.
:::

**Intuition**:
We perform a DFS traversal. The `tin` array records the exact step counter when a node is first visited. The `low` array initially equals `tin`. During the DFS traversal, when exploring neighbors (excluding the parent the DFS just came from), we update the `low` of the current node using the `low` of its visited neighbors. If we find a neighbor whose `low` is greater than the current node's `tin`, it implies that the neighbor has no back-edge to an ancestor of the current node, making the edge connecting them a bridge.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int timer = 1;
    void dfs(int node, int parent, vector<int> &vis, vector<vector<int>> &adj,
             vector<int> &tin, vector<int> &low, vector<vector<int>> &bridges) {
        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer++;
        
        for (auto it : adj[node]) {
            if (it == parent) continue;
            
            if (vis[it] == 0) {
                dfs(it, node, vis, adj, tin, low, bridges);
                low[node] = min(low[node], low[it]);
                
                // Condition for bridge
                if (low[it] > tin[node]) {
                    bridges.push_back({node, it});
                }
            } else {
                // Back-edge
                low[node] = min(low[node], tin[it]);
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for (auto it : connections) {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        
        vector<int> vis(n, 0);
        vector<int> tin(n, 0);
        vector<int> low(n, 0);
        vector<vector<int>> bridges;
        
        dfs(0, -1, vis, adj, tin, low, bridges);
        return bridges;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> connections = {{0,1}, {1,2}, {2,0}, {1,3}};
    Solution obj;
    vector<vector<int>> res = obj.criticalConnections(n, connections);
    for (auto it : res) {
        cout << "[" << it[0] << ", " << it[1] << "] ";
    }
    cout << "\n";
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(V + E)$ where $V$ is the number of vertices and $E$ is the number of edges. It requires a single DFS pass.
- Space Complexity: $O(V + E)$ for the adjacency list and $O(V)$ for auxiliary arrays `vis`, `tin`, `low`, and recursion stack.

**Practice:** https://leetcode.com/problems/critical-connections-in-a-network/

### 11. Articulation Points

An articulation point (or cut-vertex) is a vertex whose removal increases the number of connected components in the graph.

**Intuition**:
Similar to finding bridges, we maintain `tin` and `low`. For a node `u` and its neighbor `v` in the DFS tree, if `low[v] >= tin[u]` and `u` is not the root of the DFS tree, then `u` is an articulation point (removing `u` disconnects `v` from ancestors). The root of the DFS tree is a special case: it is an articulation point if and only if it has more than one child in the DFS tree.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int timer = 1;
    void dfs(int node, int parent, vector<int> &vis, vector<int> &tin, vector<int> &low,
             vector<int> &mark, vector<int> adj[]) {
        vis[node] = 1;
        tin[node] = low[node] = timer++;
        int child = 0;
        
        for (auto it : adj[node]) {
            if (it == parent) continue;
            
            if (!vis[it]) {
                dfs(it, node, vis, tin, low, mark, adj);
                low[node] = min(low[node], low[it]);
                
                // Condition for articulation point
                if (low[it] >= tin[node] && parent != -1) {
                    mark[node] = 1;
                }
                child++;
            } else {
                low[node] = min(low[node], tin[it]);
            }
        }
        if (parent == -1 && child > 1) {
            mark[node] = 1;
        }
    }
public:
    vector<int> articulationPoints(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        vector<int> tin(V, 0);
        vector<int> low(V, 0);
        vector<int> mark(V, 0);
        
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, -1, vis, tin, low, mark, adj);
            }
        }
        
        vector<int> ans;
        for (int i = 0; i < V; i++) {
            if (mark[i] == 1) {
                ans.push_back(i);
            }
        }
        if (ans.size() == 0) return {-1};
        return ans;
    }
};

int main() {
    int V = 5;
    vector<int> adj[V];
    adj[0].push_back(1); adj[1].push_back(0);
    adj[1].push_back(4); adj[4].push_back(1);
    adj[2].push_back(4); adj[4].push_back(2);
    adj[2].push_back(3); adj[3].push_back(2);
    adj[3].push_back(4); adj[4].push_back(3);
    
    Solution obj;
    vector<int> res = obj.articulationPoints(V, adj);
    for (int it : res) cout << it << " ";
    cout << "\n";
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(V + E)$ where $V$ is vertices and $E$ is edges, derived from the DFS traversal.
- Space Complexity: $O(V)$ for auxiliary arrays and recursion stack space.

**Practice:** https://practice.geeksforgeeks.org/problems/articulation-point-1/1

### 12. Kosaraju's Algorithm — Strongly Connected Components

A Strongly Connected Component (SCC) is a maximal subgraph of a directed graph such that for every pair of vertices $u$ and $v$ in the subgraph, there is a directed path from $u$ to $v$ and a directed path from $v$ to $u$.

::: heavy
Kosaraju's algorithm finds all SCCs in $O(V + E)$ time using three steps:
1. Sort all nodes in order of decreasing finishing times (using DFS to populate a stack).
2. Transpose (reverse) all edges of the graph.
3. Perform a second DFS in the order of the stack. Each DFS invocation extracts one SCC.
:::

**Intuition**:
By sorting nodes by finishing time, we ensure that if there is an edge from SCC $A$ to SCC $B$, nodes in $A$ finish after nodes in $B$. When the graph is transposed, the edge between them points from $B$ to $A$. Thus, by running DFS in decreasing order of finishing time, we visit $A$ first, and the transposed edge prevents DFS from leaking into $B$. Each DFS call thus captures exactly one SCC.

```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
private:
    void dfsSort(int node, vector<int> &vis, vector<vector<int>> &adj, stack<int> &st) {
        vis[node] = 1;
        for (auto it : adj[node]) {
            if (!vis[it]) {
                dfsSort(it, vis, adj, st);
            }
        }
        st.push(node);
    }

    void dfsSCC(int node, vector<int> &vis, vector<vector<int>> &adjT) {
        vis[node] = 1;
        for (auto it : adjT[node]) {
            if (!vis[it]) {
                dfsSCC(it, vis, adjT);
            }
        }
    }
public:
    int kosaraju(int V, vector<vector<int>>& adj) {
        vector<int> vis(V, 0);
        stack<int> st;
        // Step 1: Sort by finishing time
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfsSort(i, vis, adj, st);
            }
        }
        
        // Step 2: Transpose graph
        vector<vector<int>> adjT(V);
        for (int i = 0; i < V; i++) {
            vis[i] = 0; // reuse visited array
            for (auto it : adj[i]) {
                adjT[it].push_back(i);
            }
        }
        
        // Step 3: DFS according to stack order
        int sccCount = 0;
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            
            if (!vis[node]) {
                sccCount++;
                dfsSCC(node, vis, adjT);
            }
        }
        return sccCount;
    }
};

int main() {
    int V = 5;
    vector<vector<int>> adj(V);
    adj[0].push_back(2);
    adj[2].push_back(1);
    adj[1].push_back(0);
    adj[0].push_back(3);
    adj[3].push_back(4);
    
    Solution obj;
    cout << "Number of SCCs: " << obj.kosaraju(V, adj) << "\n";
    return 0;
}
```

**Complexity**:
- Time Complexity: $O(V + E)$ where $V$ is vertices and $E$ is edges. Three passes (DFS, Transpose, DFS) all take linear time.
- Space Complexity: $O(V + E)$ for the transposed adjacency list `adjT` and $O(V)$ for auxiliary data structures like `vis` and `st`.

**Practice:** https://practice.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1

::: interview
When approaching graph problems in an interview, explicitly state how you model the problem as a graph first (nodes, edges, weights, directed vs undirected).
- Need the shortest path in an **unweighted** graph? Use BFS.
- Weighted but **no negative** edges? Use Dijkstra.
- **Negative edges** involved? Reach for Bellman-Ford.
- Need shortest path between **all pairs**? Floyd-Warshall.
- Dependencies or "must come before"? Topo sort.
- Dynamic connectivity (grouping items, finding connected components online)? DSU is your best friend.
:::
