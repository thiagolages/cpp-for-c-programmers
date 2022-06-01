#include <Graph.hpp>
#include <DijkstraAlgorithm.hpp>

#include <gtest/gtest.h> // for unit testing

/* GRAPH TEST */

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
    //  ASSERT_GT instead of EXPECT_GT because it makes no sense to have a graph smaller than 2 nodes
    ASSERT_GT(graph0->list.size(), 1)  << "Graph doesn't have more than 1 node";
    ASSERT_GT(graph1->list.size(), 1)  << "Graph doesn't have more than 1 node";
    ASSERT_GT(graph2->list.size(), 1)  << "Graph doesn't have more than 1 node";
}

TEST_F(GraphTest, GraphIsDisconnected){
    // to be implemented
}

/* DIJKSTRA'S ALGORITHM TEST */

class DijkstraTest : public ::testing::Test {

protected:

    Graph *graph;
    DijkstraAlgorithm *dk;
    
    DijkstraTest(){
        graph = new Graph(true); // Test graph (know graph)
    }
    ~DijkstraTest(){
        delete graph;
        delete dk;
    } 

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).

        // // indexes between 0 and graph->getSize() -1
        // dk->setStartIdx (rand() % dk->getGraph()->getSize());
        // dk->setEndIdx   (rand() % dk->getGraph()->getSize());

        // // just to make sure start and end indexes are different
        // while (dk->getEndIdx() == dk->getStartIdx()){
        //     dk->setEndIdx(rand() % dk->getGraph()->getSize());
        // }
    }

    void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
    }
};

TEST_F(DijkstraTest, GraphIsNotDisconnected){
    // to be implemented
}

TEST_F(DijkstraTest, StartAndEndIndexesAreDifferent){
    dk = new DijkstraAlgorithm(graph, 0, 1);
    ASSERT_NE(dk->getStartIdx(), dk->getEndIdx())  << "startIdx and endIdx should not be the same"; 
}

TEST_F(DijkstraTest, GraphSizeIsBiggerThanOne){
    dk = new DijkstraAlgorithm(graph, 0, 1);
    ASSERT_GT(dk->getGraph()->getSize(), 1)  << "Dijkstra's Algorithm member 'graph' has size <= 1."; 
}

TEST_F(DijkstraTest, DijkstraShortestPathExample01){
    
    // Path from A to B (idx 0 to idx 1)
    dk = new DijkstraAlgorithm(graph, 0, 1);

    stringstream ss; // for debugging if we happen to fail the final test
    
    float expectedShortestPath = dk->getGraph()->matrix[0][1];

    ss << "expectedShortestPath = " << expectedShortestPath << endl;
    ss << "start index = " << dk->getStartIdx() << endl;
    ss << "end index = "   << dk->getEndIdx()   << endl;

    // Step 0) Check if the start and end indexes are different
    ASSERT_NE(dk->getStartIdx(), dk->getEndIdx())  << "startIdx and endIdx should not be the same"; 
    // Step 1) Check if we don't have a graph with 1 or less nodes
    ASSERT_GT(dk->getGraph()->getSize(), 1)  << "Dijkstra's Algorithm member 'graph' has size <= 1."; 

    int nodeIdx     = dk->getStartIdx();    // current node index
    float weight    = 0.0;  // auxiliary to get weights
    float currSum   = 0.0;  // current sum of weights

    // Step 1) Add the initial graph node to the closed set, and its distance to the start node (which is itself, so it's zero.)
    dk->closedSet.push_back(GraphNode(nodeIdx, currSum));

    // Step 2) Add to the openSet all the nodes it connects to (since this is the first node and openSet is empty)
    ASSERT_NE(dk->getGraph()->list.at(nodeIdx).size(), 0) << "Node " << nodeIdx << " is not connected to any nodes, so this is not a connected graph." << endl;

    ss << "openSet size before = " << dk->openSet.size() << endl;

    //  First we have to fill the openSet with the elements
    for (int i = 0; i < dk->getGraph()->list.at(nodeIdx).size(); i++){
        dk->openSet.push_back(GraphNode(dk->getGraph()->list.at(nodeIdx).at(i).first, dk->getGraph()->list.at(nodeIdx).at(i).second));
        ss << "pushing (" << dk->getGraph()->list.at(nodeIdx).at(i).first << "," << dk->getGraph()->list.at(nodeIdx).at(i).second << ")" << endl;
    }
    
    ss << "openSet size after = " << dk->openSet.size() << endl;

    ss << "Done !" << endl; 

    // ss << "openSet = " << dk->openSet;

    // Step 2.5) We have to sort our openSet based on weights so we pick the minimum distance
    sort(dk->openSet.rbegin(), dk->openSet.rend(), dk->sortByWeight);

    // ss << "openSet after sort by weight (second index) = " << dk->openSet;
    int count = 0;

    while(dk->openSet.size() != 0){

        ss << "inside while() for the " << ++count << " time" << endl;

        // get the first element on the openSet and put it in the closedSet
        nodeIdx = dk->openSet.back().index;            // update the node index, which is the node with shortest distance
        weight  = dk->openSet.back().weight + currSum; // getting the current cost to get to the new node

        ss << "nodeIdx = " << nodeIdx << endl;
        ss << "weight = "  << weight  << endl;

        // if we found the last node 
        if (nodeIdx == dk->getEndIdx()){
            ss << "nodeIdx = " << nodeIdx << " is equal to endIdx = " << dk->getEndIdx() << endl;
            ss << "currSum before = " << currSum << endl;
            currSum += weight;
            ss << "currSum after = " << currSum << endl;
            
            ss << "current shortest path = " << dk->getShortestPath() << endl;
            dk->setShortestPath(currSum); // assigning to the shortestPath variable
            ss << "new shortest path = " << dk->getShortestPath() << endl;
            break;
        }

        dk->openSet.pop_back();
    }

    ss << "Shortest path from A to B is " << dk->getShortestPath() << " and should be " << expectedShortestPath;

    ASSERT_EQ(dk->getShortestPath(), expectedShortestPath) << ss.str();
}

TEST_F(DijkstraTest, DijkstraShortestPathExample02){
    
    // Path from B to C (idx 1 to idx 2)
    dk = new DijkstraAlgorithm(graph, 1, 2);

    stringstream ss; // for debugging if we happen to fail the final test    

    float expectedShortestPath = dk->getGraph()->matrix[1][2];

    ss << "expectedShortestPath = " << expectedShortestPath << endl;
    ss << "start index = " << dk->getStartIdx() << endl;
    ss << "end index = "   << dk->getEndIdx()   << endl;

    // Step 0) Check if the start and end indexes are different
    ASSERT_NE(dk->getStartIdx(), dk->getEndIdx())  << "startIdx and endIdx should not be the same"; 
    // Step 1) Check if we don't have a graph with 1 or less nodes
    ASSERT_GT(dk->getGraph()->getSize(), 1)  << "Dijkstra's Algorithm member 'graph' has size <= 1."; 

    int nodeIdx     = dk->getStartIdx();    // current node index
    float weight    = 0.0;  // auxiliary to get weights
    float currSum   = 0.0;  // current sum of weights

    // Step 1) Add the initial graph node to the closed set, and its distance to the start node (which is itself, so it's zero.)
    dk->closedSet.push_back(GraphNode(nodeIdx, currSum));

    // Step 2) Add to the openSet all the nodes it connects to (since this is the first node and openSet is empty)
    ASSERT_NE(dk->getGraph()->list.at(nodeIdx).size(), 0) << "Node " << nodeIdx << " is not connected to any nodes, so this is not a connected graph." << endl;

    ss << "openSet size before = " << dk->openSet.size() << endl;

    //  First we have to fill the openSet with the elements
    for (int i = 0; i < dk->getGraph()->list.at(nodeIdx).size(); i++){
        dk->openSet.push_back(GraphNode(dk->getGraph()->list.at(nodeIdx).at(i).first, dk->getGraph()->list.at(nodeIdx).at(i).second));
        ss << "pushing (" << dk->getGraph()->list.at(nodeIdx).at(i).first << "," << dk->getGraph()->list.at(nodeIdx).at(i).second << ")" << endl;
    }
    
    ss << "openSet size after = " << dk->openSet.size() << endl;

    ss << "Done !" << endl; 

    // ss << "openSet = " << dk->openSet;

    // Step 2.5) We have to sort our openSet based on weights so we pick the minimum distance
    // descending order so we can pop from the back
    sort(dk->openSet.rbegin(), dk->openSet.rend(), dk->sortByWeight);

    // ss << "openSet after sort by weight (second index) = " << dk->openSet;
    int count = 0;

    while(dk->openSet.size() != 0){

        ss << "inside while() for the " << ++count << " time" << endl;

        // get the last element on the openSet and put it in the closedSet
        nodeIdx = dk->openSet.back().index;            // update the node index, which is the node with shortest distance
        weight  = dk->openSet.back().weight + currSum; // getting the current cost to get to the new node

        ss << "nodeIdx = " << nodeIdx << endl;
        ss << "weight = "  << weight  << endl;

        // if we found the last node 
        if (nodeIdx == dk->getEndIdx()){
            ss << "nodeIdx = " << nodeIdx << " is equal to endIdx = " << dk->getEndIdx() << endl;
            ss << "currSum before = " << currSum << endl;
            currSum += weight;
            ss << "currSum after = " << currSum << endl;
            
            ss << "current shortest path = " << dk->getShortestPath() << endl;
            dk->setShortestPath(currSum); // assigning to the shortestPath variable
            ss << "new shortest path = " << dk->getShortestPath() << endl;
            break;
        }

        dk->openSet.pop_back();
    }

    ss << "Shortest path from B to C is " << dk->getShortestPath() << " and should be " << expectedShortestPath;

    ASSERT_EQ(dk->getShortestPath(), expectedShortestPath) << ss.str();
}

TEST_F(DijkstraTest, DijkstraShortestPathExample03){

        // Path from B to C (idx 0 to idx 2)
    dk = new DijkstraAlgorithm(graph, 0, 2);

    stringstream ss; // for debugging if we happen to fail the final test

    float expectedShortestPath = dk->getGraph()->matrix[0][1] + dk->getGraph()->matrix[1][2];

    ss << "expectedShortestPath = " << expectedShortestPath << endl;
    ss << "start index = " << dk->getStartIdx() << endl;
    ss << "end index = "   << dk->getEndIdx()   << endl;

    // Step 0) Check if the start and end indexes are different
    ASSERT_NE(dk->getStartIdx(), dk->getEndIdx())  << "startIdx and endIdx should not be the same"; 
    // Step 1) Check if we don't have a graph with 1 or less nodes
    ASSERT_GT(dk->getGraph()->getSize(), 1)  << "Dijkstra's Algorithm member 'graph' has size <= 1."; 

    int nodeIdx     = dk->getStartIdx();    // current node index
    float weight    = 0.0;  // auxiliary to get weights
    float currSum   = 0.0;  // current sum of weights

    // Step 1) Add the initial graph node to the closed set, and its distance to the start node (which is itself, so it's zero.)
    dk->closedSet.push_back(GraphNode(nodeIdx, currSum));

    // Step 2) Add to the openSet all the nodes it connects to (since this is the first node and openSet is empty)
    ASSERT_NE(dk->getGraph()->list.at(nodeIdx).size(), 0) << "Node " << nodeIdx << " is not connected to any nodes, so this is not a connected graph." << endl;

    ss << "openSet size before = " << dk->openSet.size() << endl;

    //  First we have to fill the openSet with the elements
    for (int i = 0; i < dk->getGraph()->list.at(nodeIdx).size(); i++){
        dk->openSet.push_back(GraphNode(dk->getGraph()->list.at(nodeIdx).at(i).first, dk->getGraph()->list.at(nodeIdx).at(i).second));
        ss << "pushing (" << dk->getGraph()->list.at(nodeIdx).at(i).first << "," << dk->getGraph()->list.at(nodeIdx).at(i).second << ")" << endl;
    }
    
    ss << "openSet size after = " << dk->openSet.size() << endl;

    ss << "Done !" << endl; 

    // ss << "openSet = " << dk->openSet;

    // Step 2.5) We have to sort our openSet based on weights so we pick the minimum distance
    // descending order so we can pop from the back
    sort(dk->openSet.rbegin(), dk->openSet.rend(), dk->sortByWeight);

    // ss << "openSet after sort by weight (second index) = " << dk->openSet;
    int count = 0;

    while(dk->openSet.size() != 0){

        ss << "inside while() for the " << ++count << " time" << endl;

        // get the last element on the openSet and put it in the closedSet
        nodeIdx = dk->openSet.back().index;            // update the node index, which is the node with shortest distance
        weight  = dk->openSet.back().weight + currSum; // getting the current cost to get to the new node

        ss << "nodeIdx = " << nodeIdx << endl;
        ss << "weight = "  << weight  << endl;

        // if we found the last node 
        if (nodeIdx == dk->getEndIdx()){
            ss << "nodeIdx = " << nodeIdx << " is equal to endIdx = " << dk->getEndIdx() << endl;
            ss << "currSum before = " << currSum << endl;
            currSum += weight;
            ss << "currSum after = " << currSum << endl;
            
            ss << "current shortest path = " << dk->getShortestPath() << endl;
            dk->setShortestPath(currSum); // assigning to the shortestPath variable
            ss << "new shortest path = " << dk->getShortestPath() << endl;
            break;
        }

        dk->openSet.pop_back();
    }


    ASSERT_EQ(dk->getShortestPath(), expectedShortestPath) << ss.str();
}