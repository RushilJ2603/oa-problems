#include <bits/stdc++.h>
using namespace std;

struct Step {
    long long ready;
    int id;
    bool operator>(const Step& other) const {
        if (ready != other.ready) return ready > other.ready;
        return id > other.id;
    }
};

struct Event {
    long long time;
    int type; // 1 = FINISH, 2 = WAKEUP
    int id;
    bool operator>(const Event& other) const {
        if (time != other.time) return time > other.time;
        if (type != other.type) return type > other.type;
        return id > other.id;
    }
};

vector<long long> solve(int N, int S, vector<int>& station, vector<int>& duration, vector<vector<int>>& adj, vector<int>& indegree) {
    vector<long long> ready(N + 1, 0);
    vector<long long> finish(N + 1, 0);
    
    vector<priority_queue<Step, vector<Step>, greater<Step>>> station_pq(S + 1);
    vector<bool> station_busy(S + 1, false);
    
    priority_queue<Event, vector<Event>, greater<Event>> ev_pq;
    vector<int> dirty_stations;
    vector<bool> in_dirty(S + 1, false);
    
    auto add_dirty = [&](int s) {
        if (!in_dirty[s]) {
            in_dirty[s] = true;
            dirty_stations.push_back(s);
        }
    };
    
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) {
            ready[i] = 0;
            station_pq[station[i]].push({0LL, i});
            add_dirty(station[i]);
        }
    }
    
    long long T = 0;
    while (!ev_pq.empty() || !dirty_stations.empty()) {
        if (!dirty_stations.empty()) {
            vector<int> current_dirty = dirty_stations;
            dirty_stations.clear();
            for (int s : current_dirty) in_dirty[s] = false;
            
            for (int s : current_dirty) {
                if (!station_busy[s] && !station_pq[s].empty()) {
                    Step top = station_pq[s].top();
                    if (top.ready <= T) {
                        station_pq[s].pop();
                        station_busy[s] = true;
                        long long ft = T + duration[top.id];
                        finish[top.id] = ft;
                        ev_pq.push({ft, 1, top.id});
                    } else {
                        ev_pq.push({top.ready, 2, s});
                    }
                }
            }
            if (!dirty_stations.empty()) continue; 
        }
        
        if (ev_pq.empty()) break;
        
        T = ev_pq.top().time;
        while (!ev_pq.empty() && ev_pq.top().time == T) {
            Event e = ev_pq.top();
            ev_pq.pop();
            
            if (e.type == 1) {
                int step = e.id;
                int s = station[step];
                station_busy[s] = false;
                add_dirty(s);
                
                for (int v : adj[step]) {
                    ready[v] = max(ready[v], T);
                    if (--indegree[v] == 0) {
                        station_pq[station[v]].push({ready[v], v});
                        add_dirty(station[v]);
                    }
                }
            } else {
                int s = e.id;
                add_dirty(s);
            }
        }
    }
    
    return finish;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, S;
    if (!(cin >> N >> S)) return 0;
    
    vector<int> station(N + 1), duration(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> station[i] >> duration[i];
    }
    
    int M;
    cin >> M;
    vector<vector<int>> adj(N + 1);
    vector<int> indegree(N + 1, 0);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }
    
    vector<long long> finish = solve(N, S, station, duration, adj, indegree);
    
    long long makespan = 0;
    for (int i = 1; i <= N; i++) {
        cout << finish[i] << (i == N ? "" : " ");
        makespan = max(makespan, finish[i]);
    }
    cout << "\n" << makespan << "\n";
    return 0;
}
