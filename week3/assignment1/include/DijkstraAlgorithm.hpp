#include "Graph.hpp"

using namespace std;

class DijkstraAlgorithm{

    private:
        Graph *graph = new Graph();       // graph in which we want to calculate the shortest path
        float shortestPath; // value of the shortest path
        vector<int> path;   // contains the shortest path. index in the first position is the start and index N-1 is the end node
        vector<pair<int, float>> closedSet, openSet;

    public:
        DijkstraAlgorithm(Graph *graph);
        ~DijkstraAlgorithm();
        int compute(int startIdx, int endIdx);

    private:
        // sort by second element (weight) in a vector<pair<int, float>>
        static bool sortByWeight(const pair<int,float> &a, const pair<int,float> &b);

};