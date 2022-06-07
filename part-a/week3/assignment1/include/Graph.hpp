#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct GraphNode{ 
    int index;
    float distFromPrevNode;
    int prevIndex;
    GraphNode(int index, float distFromPrevNode=-1, int prevIndex = -1): index(index), distFromPrevNode(distFromPrevNode), prevIndex(prevIndex){}
    GraphNode(const GraphNode& node): index(node.index), distFromPrevNode(node.distFromPrevNode), prevIndex(node.prevIndex){}
    GraphNode& operator=(const GraphNode& node){
        index           = node.index;
        distFromPrevNode= node.distFromPrevNode;
        prevIndex       = node.prevIndex;
        return *this;
    }
    bool operator<(const GraphNode& node) const {
        return (distFromPrevNode < node.distFromPrevNode);
    }
}GraphNode;

class Graph {
    public:
        float** matrix;                   // representation of the graph in a matrix format
        vector<vector<pair<int, float>>> list;  // list representation of the graph. list of pairs, containing the node it connects to, and the weight of the edge
        vector<GraphNode> nodes;

    private:
        int size;                               // number of nodes in the graph
        float prob;                             // probability of existing an edge between two nodes

    public:
        Graph(); // Default constructor. Uses a default size and prob
        Graph(int size, float prob); // User defined size and prob
        Graph(bool test); // Constructor used for testing
        ~Graph();

        int getSize();
        void print(bool printMatrix);

    private:
        void createGraph();
        void allocateMatrix();
        void allocateList();
};

#endif