#include "Graph.hpp"
#include "DijkstraAlgorithm.hpp"
#include <gtest/gtest.h> // for unit testing

using namespace std;

int main (int argc, char** argv){   

    // Implementation of Dijkstra's Shortest Path Algorithm

    cout << endl << endl; // clear view

    // Step 1 - Graph creation
    int numNodes   = 10; // number of nodes in the graph
    float edgeProb = 0.5; // probability of having an edge between two nodes

    Graph *graph0                   = new Graph(numNodes, edgeProb);
    Graph *graph                    = new Graph(true); // Test Graph

     // indexes between 0 and graph->getSize() -1
    // int startIdx= rand() % graph->getSize();
    // int endIdx  = rand() % graph->getSize();
    if (argc < 2){
        cout << "ERROR: need start and end index nodes!" << endl;
        cout << "Usage: ./dijkstraalgorithm startIdx endIdx" << endl;
        return -1;
    }

    int startIdx= stoi(argv[1]);
    int endIdx  = stoi(argv[2]);

    if (startIdx > graph->getSize() || 
        endIdx > graph->getSize() ||
        startIdx < 0 ||
        endIdx < 0 ||
        startIdx == endIdx){
            cout << "Check indexes limits, they shall not be equal to one another, and lie between 0 <= idx <= graph-getSize() = " << graph->getSize() << endl;
            return -1;
        }

    // // just to make sure start and end indexes are different
    // while (endIdx == startIdx){
    //     endIdx = rand() % graph->getSize();
    // }

    DijkstraAlgorithm *dk           = new DijkstraAlgorithm(graph, startIdx, endIdx);
    int result                      = -1; // used to check for errors in the algorithm return

    graph->print();

    result = dk->compute();
    dk->printShortestPath();

    cout << "----------------------------------" << endl;

    delete graph; delete graph0;
    delete dk;

    if (result != 0){
        cout << "Wrong computation of Dijkstra's Algorithm ! " << endl;
        return -1;
    }

    return 0;
}