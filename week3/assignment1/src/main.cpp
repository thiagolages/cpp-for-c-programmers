#include "Graph.hpp"
#include "DijkstraAlgorithm.hpp"
#include <gtest/gtest.h> // for unit testing

using namespace std;

TEST(GraphTest, GraphIsDisconnected){
    Graph g(1, 0.1);
    ASSERT_EQ(g.list.size(), 1);
}

int main (int argc, char** argv){

    // quick test
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    // Implementation of Dijkstra's Shortest Path Algorithm

    cout << endl << endl; // clear view

    // Step 1 - Graph creation
    int numNodes   = 10; // number of nodes in the graph
    float edgeProb = 0.5; // probability of having an edge between two nodes
    
    // Graph *graph                    = new Graph(numNodes, edgeProb);
    Graph *graph                    = new Graph(true); // Test Graph
    DijkstraAlgorithm *dijkstra     = new DijkstraAlgorithm(graph);
    int result                      = -1; // used to check for errors in the algorithm return

    graph->print();

    // indexes between 0 and graph->getSize() -1
    int startIdx    = rand() % graph->getSize();
    int endIdx      = rand() % graph->getSize();

    // just to make sure start and end indexes are different
    while (endIdx == startIdx){
         endIdx = rand() % graph->getSize();
    }


    

    result = dijkstra->compute(startIdx, endIdx);
    cout << "The shortest path found was "<< dijkstra->getShortestPath() << endl;

    cout << "----------------------------------" << endl;

    delete graph;
    delete dijkstra;

    if (result != 0){
        cout << "Wrong computation of Dijkstra's Algorithm ! " << endl;
        return -1;
    }

    return 0;
}