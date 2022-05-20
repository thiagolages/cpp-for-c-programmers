#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
    public:
        float** matrix;                           // representation of the graph in a matrix format
        vector<vector<pair<int, float>>> list;  // list representation of the graph. list of pairs, containing the node it connects to, and the weight of the edge

    private:
        int size;                               // number of nodes in the graph
        float prob;                             // probability of existing an edge between two nodes

    public:
        Graph(); // Default constructor
        Graph(int size, float prob);
        ~Graph();

        int getSize();
        void print();

    private:
        void createGraph();
};

#endif