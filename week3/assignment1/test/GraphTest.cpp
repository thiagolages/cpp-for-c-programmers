#include <Graph.hpp>
#include <gtest/gtest.h> // for unit testing

class GraphTest : public ::testing::Test {

protected:

    Graph *graph0, *graph1, *graph2;
    
    GraphTest(){
        graph0 = new Graph(); // Default constructor
        graph1 = new Graph(20, 0.2); // User defined size and probability
        graph2 = new Graph(true); // Test graph (know graph)
    }
    ~GraphTest(){
        delete graph0;
        delete graph1;
        delete graph2;
    }  
  
};


TEST_F(GraphTest, GraphContainsMoreThanTwoNodes) {
  EXPECT_GT(graph0->list.size(), 2)  << "Graph doesn't have more than 2 nodes";
  EXPECT_GT(graph1->list.size(), 2)  << "Graph doesn't have more than 2 nodes";
  EXPECT_GT(graph2->list.size(), 2)  << "Graph doesn't have more than 2 nodes";
}

TEST_F(GraphTest, GraphIsDisconnected){
    // to be implemented
}