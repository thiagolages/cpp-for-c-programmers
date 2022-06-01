#include "Graph.hpp"

using namespace std;

typedef struct MSTNode{ // Minimum Spanning Tree Node
    int previousNodeIdx;
    float distFromSrcNode;
    bool hasBeenVisited;
    MSTNode(int previousNodeIdx=-1,  float distFromSrcNode=INFINITY, bool hasBeenVisited=false):distFromSrcNode(distFromSrcNode), previousNodeIdx(previousNodeIdx), hasBeenVisited(hasBeenVisited){}
    MSTNode& operator= (const GraphNode& node){
        previousNodeIdx = node.index;
        distFromSrcNode = node.distFromPrevNode;
        return *this;
    }

}MSTNode;

class DijkstraAlgorithm{

    public:
    vector<GraphNode> closedSet, openSet;
    vector<MSTNode> MST; // Minimum Spanning Tree

    private:
        Graph *graph = new Graph();       // graph in which we want to calculate the shortest path
        float shortestPath=0.0; // value of the shortest path
        vector<int> path;   // contains the shortest path. index in the first position is the start and index N-1 is the end node
        int startIdx=0, endIdx=1;

    public:
        DijkstraAlgorithm(Graph *graph, int startIdx, int endIdx);
        ~DijkstraAlgorithm();
        // 'friend' will allow a function/other class get access to private/protected variables/functions of this class
        friend ostream& operator<< (const ostream& out, const vector<pair<int, float>>& vec);
        friend ostream& operator<< (ostream& out, const vector<MSTNode>& MST);
        friend ostream& operator<< (ostream& out, const MSTNode& node);
        
        int     compute();
        void    setShortestPath(float shortestPath);
        float   getShortestPath();
        void printShortestPath();
        Graph*  getGraph();

        int getStartIdx();
        int getEndIdx();

        static bool sortByDist(const GraphNode &a, const GraphNode &b);

};