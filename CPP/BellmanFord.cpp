#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int source, destination, weight;
};

void bellmanFord(int V, int E, const vector<Edge>& edges, int start) {
    vector<int> distance(V, INF);
    distance[start] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i < V; i++) {
        for (const auto& edge : edges) {
            if (distance[edge.source] != INF && distance[edge.source] + edge.weight < distance[edge.destination]) {
                distance[edge.destination] = distance[edge.source] + edge.weight;
            }
        }
    }

    // Check for negative weight cycles
    for (const auto& edge : edges) {
        if (distance[edge.source] != INF && distance[edge.source] + edge.weight < distance[edge.destination]) {
            cout << "Graph contains a negative weight cycle." << endl;
            return;
        }
    }

    // Print distances from the source vertex
    cout << "Vertex Distance from Source (" << start << "):" << endl;
    for (int i = 0; i < V; i++) {
        if (distance[i] == INF) {
            cout << "Vertex " << i << ": Unreachable" << endl;
        } else {
            cout << "Vertex " << i << ": " << distance[i] << endl;
        }
    }
}

int main() {
    int V = 5; // Number of vertices
    int E = 8; // Number of edges
    vector<Edge> edges = {
        {0, 1, -1}, // Edge from 0 to 1 with weight -1
        {0, 2, 4},  // Edge from 0 to 2 with weight 4
        {1, 2, 3},  // Edge from 1 to 2 with weight 3
        {1, 3, 2},  // Edge from 1 to 3 with weight 2
        {1, 4, 2},  // Edge from 1 to 4 with weight 2
        {3, 2, 5},  // Edge from 3 to 2 with weight 5
        {3, 1, 1},  // Edge from 3 to 1 with weight 1
        {4, 3, -3}  // Edge from 4 to 3 with weight -3
    };

    bellmanFord(V, E, edges, 0); // Start from vertex 0

    return 0;
}
