#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;

const int INF = numeric_limits<int>::max();
const int MAX_N = 100;  

void floydWarshall(int n, int dist[MAX_N][MAX_N], int next[MAX_N][MAX_N]) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void printDistanceMatrix(int n, int dist[MAX_N][MAX_N]) {
    cout << "Distance Matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) cout << setw(4) << "INF";
            else cout << setw(4) << dist[i][j];
        }
        cout << endl;
    }
}

void printPath(int u, int v, int next[MAX_N][MAX_N]) {
    if (next[u][v] == -1) {
        cout << "No path exists from " << u + 1 << " to " << v + 1 << endl;
        return;
    }
    cout << "Shortest path: ";
    for (int at = u; at != v; at = next[at][v]) {
        cout << (at + 1) << " ";
    }
    cout << (v + 1) << endl;
}

int main() {
    ifstream inputFile("in.txt");
    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    int n, m;
    inputFile >> n >> m;

    int dist[MAX_N][MAX_N], next[MAX_N][MAX_N];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = (i == j) ? 0 : INF;
            next[i][j] = (i == j) ? i : -1;
        }
    }

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        inputFile >> u >> v >> w;
        u--; v--;
        dist[u][v] = w;
        next[u][v] = v;
    }

    floydWarshall(n, dist, next);
    printDistanceMatrix(n, dist);

    char choice;
    do {
        int start, end;
        cout << "\nEnter start vertex: ";
        cin >> start;
        cout << "Enter end vertex: ";
        cin >> end;
        start--; end--;

        if (start >= 0 && start < n && end >= 0 && end < n) {
            cout << "Shortest distance from " << start + 1 << " to " << end + 1 << " is: ";
            if (dist[start][end] == INF) cout << "INF\n";
            else cout << dist[start][end] << endl;
            printPath(start, end, next);
        }
        else {
            cout << "Invalid vertices.\n";
        }

        cout << "Do you want to find another path? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
