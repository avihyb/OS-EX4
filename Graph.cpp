#include "Graph.hpp"
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Graph::Graph(int v, int e) : v(v), e(e), seed(0) {
//     adj = new list<int>[v];
//     in = new int[v];
//     for (int i = 0; i < v; i++){
//         in[i] = 0;
//     }
//     cout << "Graph with " << v << " vertices and " << e << " edges created\n";
//     addEdges();
// }

Graph::Graph(int V) : v(V), e(0), seed(0) {
    adj = new list<int>[V];
    in = new int[V];
    for (int i = 0; i < V; i++){
        in[i] = 0;
    }
}

Graph::Graph(int v, int e, int seed) : v(v), e(e), seed(seed) {
    adj = new list<int>[v];
    in = new int[v];
    for (int i = 0; i < v; i++){
        in[i] = 0;
    }
    cout << "Graph with " << v << " vertices and " << e << " edges created\n";
    addRandomEdges();
}

Graph::~Graph() {
    delete[] adj;
    delete[] in;
}

// void Graph::addEdges() {
//     int src, dest;
//     for (int i = 0; i < e; i++) {
//         cin >> src >> dest;
//         adj[src].push_back(dest);
//         in[dest]++;
//         cout << src << "->" << dest << " edge added\n";
//     }
//     cout << "All edges added\n";
// }

bool Graph::isDirected() {
    for (int i = 0; i < v; ++i) {
        for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
            if (find(adj[*it].begin(), adj[*it].end(), i) == adj[*it].end()) {
                return true;
            }
        }
    }
    return false;
}

void Graph::DFSUtil(int v, bool visited[]) {
    visited[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
        if (!visited[*it])
            DFSUtil(*it, visited);
}

Graph Graph::getTranspose() {
    Graph g(v);
    for (int i = 0; i < v; i++) {
        for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
            g.adj[*it].push_back(i);
            g.in[i]++;
        }
    }
    return g;
}

bool Graph::isSC() {
    bool visited[v];
    fill(visited, visited + v, false);
    int n;
    for (n = 0; n < v; n++)
        if (adj[n].size() > 0)
            break;
    if (n == v)
        return true;
    DFSUtil(n, visited);
    for (int i = 0; i < v; i++)
        if (adj[i].size() > 0 && !visited[i])
            return false;
    Graph gr = getTranspose();
    fill(visited, visited + v, false);
    gr.DFSUtil(n, visited);
    for (int i = 0; i < v; i++)
        if (adj[i].size() > 0 && !visited[i])
            return false;
    return true;
}

bool Graph::isThereEulerCircle() {
    if (isDirected()) {
        if (!isSC()) {
            cout << "Graph is not Eulerian!\n";
            cout << "Directed Graph: All non-zero degree vertices are not strongly-connected\n";
            return false;
        }
        for (int i = 0; i < v; i++) {
            if (adj[i].size() != in[i]) {
                cout << "Graph is not Eulerian!\n";
                cout << "Directed Graph: In degree and out degree of " << i << " is not same\n";
                return false;
            }
        }
        return true;
    } else {
        if (!isConnected()) {
            cout << "Graph is not Eulerian!\n";
            cout << "Undirected Graph: Graph is not connected\n";
            return false;
        }
        int odd = 0;
        for (int i = 0; i < v; i++)
            if (adj[i].size() % 2 != 0)
                odd++;
        if (odd > 2)
            return false;
        return odd == 0;
    }
}

// bool Graph::evenDegree() {
//     for (int i = 0; i < v; ++i)
//         if (adj[i].size() % 2 != 0)
//             return false;
//     return true;
// }

void Graph::printEulerCircuit() {
    if (!isThereEulerCircle()) {
        cout << "There is no Euler Circuit\n";
        return;
    }
    cout << "Found Euler Circuit: ";
    stack<int> currPath;
    vector<int> circuit;
    int currV = 0;
    for (int i = 0; i < v; i++)
        if (adj[i].size() > 0) {
            currV = i;
            break;
        }
    currPath.push(currV);
    while (!currPath.empty()) {
        if (!adj[currV].empty()) {
            currPath.push(currV);
            int nextV = adj[currV].front();
            adj[currV].pop_front();
            currV = nextV;
        } else {
            circuit.push_back(currV);
            currV = currPath.top();
            currPath.pop();
        }
    }
    for (int i = circuit.size() - 1; i >= 0; i--) {
        cout << circuit[i];
        if (i > 0) cout << " -> ";
    }
    cout << "\n";
}

bool Graph::isConnected() {
    if (!isDirected()) {
        if (v == 0)
            return true;
        vector<bool> visited(v, false);
        queue<int> queue;
        queue.push(0);
        visited[0] = true;
        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            for (auto it = adj[current].begin(); it != adj[current].end(); ++it)
                if (!visited[*it]) {
                    visited[*it] = true;
                    queue.push(*it);
                }
        }
        for (int i = 0; i < v; ++i)
            if (!visited[i])
                return false;
        return true;
    } else {
        for (int i = 0; i < v; ++i) {
            vector<bool> visited(v, false);
            queue<int> queue;
            queue.push(i);
            visited[i] = true;
            while (!queue.empty()) {
                int current = queue.front();
                queue.pop();
                for (auto it = adj[current].begin(); it != adj[current].end(); ++it)
                    if (!visited[*it]) {
                        visited[*it] = true;
                        queue.push(*it);
                    }
            }
            for (int j = 0; j < v; ++j)
                if (!visited[j])
                    return false;
        }
        return true;
    }
}

void Graph::addRandomEdges() {
    std::random_device rd;
    std::mt19937 gen(seed == 0 ? rd() : seed);
    std::uniform_int_distribution<> dist(0, v - 1);
    for (int i = 0; i < e; i++) {
        int src = dist(gen);
        int dest = dist(gen);
        adj[src].push_back(dest);
        in[dest]++;
    }
    cout << "All edges added\n";
}

void Graph::printGraphInfo() {
    cout << "====================================\n";
    cout << "Graph Directed: " << isDirected() << "\n";
    cout << "Graph Connected: " << isConnected() << "\n";
 //   cout << "Graph has even degree: " << evenDegree() << "\n";
    cout << "isSC: " << isSC() << "\n";
    cout << "====================================\n";
    for (int i = 0; i < v; i++) {
        cout << "V" << i << ": ";
        for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
            cout << *it << " ";
        }
        cout << "\n";
    }
}
