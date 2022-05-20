#include "Graph.hpp"
#include "DijkstraAlgorithm.hpp"

using namespace std;

int main (int argc, char** argv){

    // Implementation of Dijkstra's Shortest Path Algorithm

    // Step 1 - Graph creation
    int n   = 10; // number of nodes in the graph
    float p = 0.5; // probability of having an edge between two nodes
    
    Graph *graph                    = new Graph(n, p);
    // DijkstraAlgorithm *dijkstra     = new DijkstraAlgorithm(graph);
    int result                      = 0; // used to check for errors in the algorithm return

    graph->print();
    

    return 0; //temporary

    // // making sure we have more than one node, otherwise start and end indexes would be equal to each other
    // // indexes between 0 and graph->getSize() -1
    // int startIdx    = rand() % graph->getSize();
    // int endIdx      = rand() % graph->getSize();

    // // just to make sure start and end indexes are different
    // while (endIdx == startIdx){
    //      endIdx = rand() % graph->getSize();
    // }

    // result = dijkstra->compute(startIdx, endIdx);

    // if (result != 0){
    //     cout << "Wrong computation of Dijkstra's Algorithm ! " << endl;
    //     return -1;
    // }

    // return 0;
}