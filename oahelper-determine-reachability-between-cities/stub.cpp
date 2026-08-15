#include <bits/stdc++.h>
using namespace std;

struct TrainLine {
    string lineName;
    vector<string> stations;
};

vector<bool> canTravel(vector<TrainLine>& trainLines, vector<vector<string>>& queries) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numLines;
    if (!(cin >> numLines)) return 0;

    vector<TrainLine> trainLines(numLines);
    for (int i = 0; i < numLines; i++) {
        cin >> trainLines[i].lineName;
        int numStations;
        cin >> numStations;
        trainLines[i].stations.resize(numStations);
        for (int j = 0; j < numStations; j++) {
            cin >> trainLines[i].stations[j];
        }
    }

    int numQueries;
    if (!(cin >> numQueries)) return 0;
    vector<vector<string>> queries(numQueries, vector<string>(2));
    for (int i = 0; i < numQueries; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }

    vector<bool> results = canTravel(trainLines, queries);
    for (size_t i = 0; i < results.size(); i++) {
        cout << (results[i] ? "true" : "false");
        if (i + 1 < results.size()) cout << " ";
    }
    cout << "\n";
    return 0;
}
