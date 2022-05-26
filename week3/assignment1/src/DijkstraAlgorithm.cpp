#include "Graph.hpp"
#include "DijkstraAlgorithm.hpp"

DijkstraAlgorithm::DijkstraAlgorithm(Graph *graph, int startIdx=0, int endIdx=1): graph(graph), startIdx(startIdx), endIdx(endIdx){
    
    MST.reserve(graph->getSize());

    for (int i = 0; i < graph->getSize(); i++){
        MST.push_back(MSTNode());
    }
    // cout << "DijkstraAlgorithm(): DijkstraAlgorithm object created !"<<endl;
}

DijkstraAlgorithm::~DijkstraAlgorithm(){
    // cout << "~DijkstraAlgorithm(): DijkstraAlgorithm object destroyed !"<<endl;
}

ostream& operator<< (ostream& out, const vector<GraphNode>& vec){
    for (int i = 0; i < vec.size(); i++){
        out << "(" << vec.at(i).index << "," << vec.at(i).distFromPrevNode << "),";
    }
    out << endl;
    return out;
}

ostream& operator<< (ostream& out, const vector<MSTNode>& MST){
    out << endl;
    for (int i = 0; i < MST.size(); i++){
        out << "(" << MST.at(i).previousNodeIdx << "," << MST.at(i).distFromSrcNode << ")" << endl;
    }
    return out;
}

ostream& operator<< (ostream& out, const MSTNode& node){
        out << "previousNodeIdx = " << node.previousNodeIdx << endl;
        out << "distFromSrcNode = " << node.distFromSrcNode << endl;
        out << "hasBeenVisited  = " << node.hasBeenVisited << endl;
        return out;
}

void  DijkstraAlgorithm::setShortestPath(float shortestPath){this->shortestPath = shortestPath;}

float DijkstraAlgorithm::getShortestPath(){return this->shortestPath;}

void DijkstraAlgorithm::printShortestPath(){
    
    int oldIdx = endIdx;
    int newIdx = MST.at(endIdx).previousNodeIdx;
    
    cout << "shortest path from " << startIdx << " to " << endIdx << " = " << shortestPath << endl;
    cout << endIdx << "<-" << newIdx;
    while(newIdx!= startIdx){
        oldIdx = newIdx;
        newIdx = MST.at(oldIdx).previousNodeIdx;
        cout << "<-" << newIdx;
    }
    cout << endl;

}

// void DijkstraAlgorithm::setStartIdx(int startIdx){this->startIdx = startIdx;};

// void DijkstraAlgorithm::setEndIdx  (int endIdx  ){this->endIdx   = endIdx  ;};

int  DijkstraAlgorithm::getStartIdx(){return this->startIdx;};

int  DijkstraAlgorithm::getEndIdx  (){return this->endIdx  ;};

Graph* DijkstraAlgorithm::getGraph(){return this->graph;}

int DijkstraAlgorithm::compute(){

    if (startIdx == endIdx){
        cout << "Initital and Final nodes are the same." << endl;
        return 0; //all OK
    }
    
    // Step 0)
    if (graph->getSize() <= 1){
        cout << "Graph should have size > 1 !" << endl;
        shortestPath = -1;
        path.push_back(-1);
        return -1;
    }

    int   currNodeIdx          = startIdx; // current node index
    float currNodeDistFromPrev = 0.0;

    // Step 1) Add the initial graph node to the closed set, and its distance to the start node (which is itself, so it's zero.)
    closedSet.push_back(GraphNode(startIdx, 0.0));
    MST.at(startIdx)  = GraphNode(startIdx, 0.0);

    // Step 2) Add to the openSet all the nodes it connects to (since this is the first node and openSet is empty)
    //  First we have to fill the openSet with the elements
    if(graph->list.at(startIdx).size() == 0){
        cerr << "Node "<<currNodeIdx<< " is not connected to any nodes, so this is not a connected graph." << endl;
        return -1;
    }


    for (int i = 0; i < graph->list.at(startIdx).size(); i++){
        int auxIdx      = graph->list.at(startIdx).at(i).first;
        float auxWeight = graph->list.at(startIdx).at(i).second;
        openSet.push_back(GraphNode(auxIdx, auxWeight)); // e.g. (1, 3) and (4, 4) for the test graph
        MST.at(auxIdx) =  MSTNode(currNodeIdx, auxWeight);
    }
    
    cout << endl; 
    cout << "startIdx = "<< startIdx << endl;
    cout << "openSet = " << openSet << endl;
    cout << "MST     = " << MST << endl;
    cout << "openSet.size() = " << openSet.size() << endl;

    while(openSet.size() != 0){

        // Step 2.5) We have to sort our openSet based on weights so we pick the minimum distance
        sort(openSet.begin(), openSet.end(), sortByDist);
        cout << "openSet sorted = " << openSet << endl;

        currNodeIdx          = openSet.front().index;
        currNodeDistFromPrev = openSet.front().distFromPrevNode;

        cout << "currNodeIdx = " << currNodeIdx << "  ";
        cout << "currNodeDistFromPrev = " << currNodeDistFromPrev << endl;

        // remove from openSet
        openSet.erase(openSet.begin());

        cout << "openSet.size() = " << openSet.size() << endl;
        cout << "openSet = " << openSet << endl;

        MST.at(currNodeIdx).hasBeenVisited = true;

        // Step 3) Add all nodes this node connects to
        for (auto& node: graph->list.at(currNodeIdx)){
            cout << "inside for auto& node: graph->list.at("<<currNodeIdx<<")" << endl;
            int newNodeIdx                  = node.first;
            int distFromCurrNodeToNewNode   = node.second;
            
            cout << "newNodeIdx = " << newNodeIdx << endl;
            cout << "distFromCurrNodeToNewNode = " << distFromCurrNodeToNewNode << endl;

            float oldDistance = MST.at(newNodeIdx).distFromSrcNode; // current  assigned distance from  i to source node
            float newDistance = MST.at(currNodeIdx).distFromSrcNode + distFromCurrNodeToNewNode; // new calculated distance - distance so far + distance from currNode to i

            cout << "oldDistance = " << oldDistance << endl;
            cout << "newDistance = " << newDistance << endl;

            cout << "MST.at("<<newNodeIdx<<") = " << MST.at(newNodeIdx) <<endl;

            if ( !MST.at(newNodeIdx).hasBeenVisited &&
                  MST.at(currNodeIdx).distFromSrcNode != INFINITY &&
                  newDistance < oldDistance){
                    cout << "in" <<endl;
                    
                    MST.at(newNodeIdx).distFromSrcNode = newDistance;
                    MST.at(newNodeIdx).hasBeenVisited  = true;
                    MST.at(newNodeIdx).previousNodeIdx = currNodeIdx;

                    cout << "MST.at("<<newNodeIdx<<") = " << MST.at(newNodeIdx) <<endl;

                    for (auto& newNodeAdj: graph->list.at(newNodeIdx)){
                        // adding only if node was not visited already
                        if (!MST.at(newNodeAdj.first).hasBeenVisited){
                            openSet.push_back(GraphNode(newNodeAdj.first,   newNodeAdj.second));
                            cout << "adding node ("<<newNodeAdj.first<<","<<newNodeAdj.second<<") to openSet"<<endl;
                        }
                        
                    }

                    cout << "out" << endl;
                }
        }


    }

    float shortestPath = MST.at(endIdx).distFromSrcNode;
    setShortestPath(shortestPath);
    printShortestPath();

    return 0; // everything worked fine

} // end of 'compute'

// sort by second element (weight) in a vector<pair<int, float>>
bool DijkstraAlgorithm::sortByDist(const GraphNode &a, const GraphNode &b){
    return (a.distFromPrevNode < b.distFromPrevNode);
}