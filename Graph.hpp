#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <list>

class Graph {
    public:
        Graph(int v, int e);
        Graph(int v);
        Graph(int v, int e, int seed);
        ~Graph();
        void addEdges();
        bool isDirected();
        bool isSC();
        void DFSUtil(int v, bool visited[]);
        Graph getTranspose();
        bool isThereEulerCircle();
        bool evenDegree();
        void printEulerCircuit();
        bool isConnected();
        void addRandomEdges();
        void printGraphInfo();
    
    private:
        int v;
        int e;
        std::list<int> *adj;
        int* in;
        int seed;
};

#endif