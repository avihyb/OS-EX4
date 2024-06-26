#include "Graph.hpp"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;


int main(int argc, char* argv[]) {
    int v, e, seed;
    int opt;

    // Parse optional command-line options
    while ((opt = getopt(argc, argv, "v:e:s:")) != -1) {
        switch (opt) {
            case 'v':
                v = stoi(optarg);
                break;
            case 'e':
                e = stoi(optarg);
                break;
            case 's':
                seed = stoi(optarg);
                break;
        }
    }

    

    // Create the graph and perform operations
    Graph g(v, e, seed);
    g.printGraphInfo();
    g.printEulerCircuit();

    return 0;
}
