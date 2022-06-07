#include <iostream>
#include <vector>
#include <array>

#include "../week3/assignment1/include/Graph.hpp"

using namespace std;

#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

typedef pair<int, int> Edge;

typedef struct MST{
    vector<GraphNode> nodes;
    vector<Edge> edges;
}MST;

ostream& operator << (ostream& out, const vector<GraphNode>& vec){
    for (auto v : vec){
        // out << "idx = " << v.index << ", dist = " << v.distFromPrevNode << endl;
        out << "(" << v.index << "," << v.distFromPrevNode << "," << v.prevIndex << ")\t";
    }
    return out;
}

ostream& operator << (ostream& out, const vector<Edge> vec){
    for (auto v : vec){
        // out << "idx = " << v.index << ", dist = " << v.distFromPrevNode << endl;
        out << "(" << v.first << "," << v.second << ")\t";
    }
    return out;
}

int main (int argc, char** argv){

    Graph graph(true); // test Graph
    MST mst;
    vector<GraphNode> tmpNodes;
    const size_t graphSize = graph.getSize(); // more readable
    bool isPartOfMST[graphSize];

    // initialize nodes as not been visited yet
    for (int i = 0; i < graphSize; i++){
        isPartOfMST[i] = false;
    }

    int firstIdx = 0;
    int currNodeIdx = 0;
    isPartOfMST[firstIdx] = true;
    mst.nodes.push_back(GraphNode(firstIdx, 0.0, 0.0));
    mst.edges.push_back(make_pair(0,0));
    // since we're adding one extra node to the MST (firstIdx, 0.0), we're checking for !- graphSize and not (graphSize-1)
    while (mst.nodes.size() != graphSize){ 

        tmpNodes.clear(); // clear all temp nodes, if any

        // 1) Get all distances to other nodes
        for (auto node : mst.nodes){
            currNodeIdx = node.index;
            
            if (graph.list[currNodeIdx].size() == 0){
                cout << "Node "<< currNodeIdx << " is not connected to any other node. Exiting.." << endl;
                return -1;
            }
            for (int j = 0; j < graph.list[currNodeIdx].size(); j++){
                int adjNodeIdx = graph.list[currNodeIdx].at(j).first; // adjacent node indexes
                DEBUG_MSG("currNodeIdx = " << currNodeIdx << ", adjNodeIdx = " << adjNodeIdx << endl);
                // if adjNodeIdx is NOT in MST (checking for loops)
                if ( !isPartOfMST[adjNodeIdx] ){ 
                    DEBUG_MSG(adjNodeIdx << " is not part of MST, adding it to tmpNodes" << endl);
                    float distToNextNode = graph.list[currNodeIdx].at(j).second;
                    cout << "adding " << adjNodeIdx << "," << distToNextNode << "," << currNodeIdx << endl;
                    tmpNodes.push_back(GraphNode(adjNodeIdx, distToNextNode, currNodeIdx));
                }
            }
        }

        if (tmpNodes.size() == 0){
            cout << "No more nodes to visit, and the MST does not contain the right size. Exiting.." << endl;
            return -1;
        }

        // 2) Choose the smallest one
        DEBUG_MSG("tmpNodes normal: " << tmpNodes << endl);
        sort(tmpNodes.begin(), tmpNodes.end()); // 'operator<' is defined for type GraphNode
        DEBUG_MSG("tmpNodes sorted: " << tmpNodes << endl);
        DEBUG_MSG("MST nodes so far: " << mst.nodes << endl);
        DEBUG_MSG("MST edges so far: " << mst.edges << endl);
        int newNodeIdx = tmpNodes.front().index;

        while (isPartOfMST[newNodeIdx]){
            DEBUG_MSG(newNodeIdx << " is part of MST" << endl);
            tmpNodes.erase(tmpNodes.begin()); // remove first element
            if (tmpNodes.size() == 0){
                cout << "No more new nodes to visit and MST is not the ideal size. Exiting.. "<<endl;
                return -1;
            }         
            newNodeIdx = tmpNodes.front().index;
        } // while isPartOfMST[newNodeIdx]

        // 3) Check for loops
        if ( !isPartOfMST[newNodeIdx] ){
            DEBUG_MSG(newNodeIdx << " is NOT part of MST, adding it to MST" << endl);
            DEBUG_MSG("(nodes)adding "<<tmpNodes.front().index<<","<<tmpNodes.front().distFromPrevNode<<","<<tmpNodes.front().prevIndex<<endl);
            // 4) If no loops, add it to the MST
            mst.nodes.push_back(tmpNodes.front());
            mst.edges.push_back(make_pair(tmpNodes.front().index, tmpNodes.front().prevIndex));
            isPartOfMST[newNodeIdx] = true;
        }
    } // while MST.size() != graphSize - 1

    float minDist = 0.0;
    
    mst.nodes.erase(mst.nodes.begin()); // removing first element (0,0) that we added just for logic purposes
    mst.edges.erase(mst.edges.begin()); // removing first element (0,0) that we added just for logic purposes

    DEBUG_MSG("Final MST nodes: " << mst.nodes << endl);
    DEBUG_MSG("Final MST edges: " << mst.edges << endl);

    DEBUG_MSG("My graph is: " << endl);
    graph.print();

    cout << "My MST is composed of: " << endl;
    for (auto node : mst.nodes){
        cout << node.index << ", weight " << node.distFromPrevNode << endl;
        minDist += node.distFromPrevNode;
    }

    cout << "Min dist = " << minDist << endl;

    return 0;

} // main