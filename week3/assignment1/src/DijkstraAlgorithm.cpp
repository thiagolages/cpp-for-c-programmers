#include "Graph.hpp"
#include "DijkstraAlgorithm.hpp"

DijkstraAlgorithm::DijkstraAlgorithm(Graph *graph): graph(graph){cout << "DijkstraAlgorithm(): DijkstraAlgorithm object created !"<<endl;}

DijkstraAlgorithm::~DijkstraAlgorithm(){cout << "~DijkstraAlgorithm(): DijkstraAlgorithm object destroyed !"<<endl;}

int DijkstraAlgorithm::compute(int startIdx, int endIdx){
    
    // Step 0) Check if we don't have a graph with 1 or less nodes
    if (graph->getSize() <= 1){
        cout << "Graph should have size > 1 !" << endl;
        this->shortestPath = -1;
        this->path.push_back(-1);
        return -1;
    }

    int nodeIdx     = 0;    // current node index
    float weight    = 0.0;  // auxiliary to get weights
    float currSum   = 0.0;  // current sum of weights

    // Step 1) Add the initial graph node to the closed set, and its distance to the start node (which is itself, so it's zero.)
    closedSet.push_back(make_pair(nodeIdx, currSum));

    // Step 2) Add to the openSet all the nodes it connects to
    //  First we have to fill the openSet with the elements
    for (int i = 0; i < graph->list.at(nodeIdx).size(); i++){
        cout << "i = "<<i<<endl;
        openSet.push_back(graph->list.at(nodeIdx).at(i)); 
    }

    // Step 2.5) We have to sort our openSet based on weights so we pick the minimum distance
    sort(openSet.begin(), openSet.end(), this->sortByWeight);

    return 0; // temporary

    // while(openSet.size() != 0){

    //     // get the first element on the openSet and put it in the closedSet
    //     nodeIdx = openSet.front().first;            // update the node index, which is the node with shortest distance
    //     weight  = openSet.front().second + currSum; // getting the current cost to get to the new node

    //     // Step 3) Check a few conditions:
        
    //     // 3.1) Checks if the node index is found within the closedSet
    //     // 'it' returns 'closedSet.end()' if nothing is found
    //     auto it = find_if( closedSet.begin(), closedSet.end(), 
    //     [&nodeIdx](const pair<int, float>& element){ return nodeIdx == element.first;} );
        
    //     // determine the index of the 'closedSet' vector in which the new node was found.
    //     // if this index is out of range of the vector size, means we haven't found anything
    //     int pos = it - closedSet.begin(); 
        
    //     if ( pos < closedSet.size()){ // if it is found, just skip to the next iteration
            
    //         continue;
    //     }

    //     // 3.2) Checks if the node index is found within the openSet
    //     it = find_if( openSet.begin(), openSet.end(), 
    //     [&nodeIdx](const pair<int, float>& element){ return nodeIdx == element.first;} );

    //     int aux = it - openSet.begin(); // determine if the element was found or not
    //     if ( aux < openSet.size()){ // if it is found, check if we can make any improvements on the minimum distance
            
    //     }


    //     closedSet.push_back(make_pair(nodeIdx, weight));
    //     // remove it from the openSet
    //     openSet.clear(openSet.front());

        
    //     getEdges(nodeIdx, currSum);

    // }
    


    // // Step 1) While there are items in the openSet and we haven't moved our destination to the closedSet, we continue
    // while(openSet.size() != 0){

    //     // Step 2) Add the initial graph node to the closed set, and its distance to the start node (which is itself, so it's zero.)
    //     closedSet.push_back(make_pair(nodeIdx, weight));

    //     // Step 3) Add to the openSet all the nodes it connects to
    //     //  First we have to fill the openSet with the elements
    //     for (int i = 0; i < graph->list.at(nodeIdx).size(); i++){
    //         openSet.push_back(graph->list.at(nodeIdx).at(i)); 
    //     }

    //     // Step 3.5) We have to sort our openSet based on weights so we pick the minimum distance
    //     sort(openSet.begin(), openSet.end(), this->sortByWeight);

    //     // get the first element on the openSet and put it in the closedSet
    //     nodeIdx = openSet.front().first;            // update the node index, which is the node with shortest distance
    //     weight  = openSet.front().second + currSum; // getting the current cost to get to the new node
    //     closedSet.push_back(make_pair(nodeIdx, weight));
    //     // remove it from the openSet
    //     openSet.clear(openSet.front());

        
    //     getEdges(nodeIdx, currSum);


    // } // end while
                

    return 0; // everything worked fine

} // end of 'compute'

// sort by second element (weight) in a vector<pair<int, float>>
bool DijkstraAlgorithm::sortByWeight(const pair<int,float> &a, const pair<int,float> &b){
    return (a.second < b.second);
}

// void DijkstraAlgorithm::getEdges(int nodeIdx, float currSum){
//     if (graph->list.at(nodeIdx).size() == 0){
//         // nothing to do, 'set' keeps the same
//         return;
//     }
//     // Step 4) We have to check if the item to be fetched is:
//     // 4.1) already in the closed set
//     // 4.2) already in the open set
//     // 4.3) not in the open nor closed sets

//     // Now we check some conditions
//     for (int i = 0; i < graph->list.at(nodeIdx).size(); i++){
        
//         int adjNodeIdx      = openSet.front().first;
//         int adjNodeWeight   = openSet.front().second;

//         // 4.1) check if it's in the closed set. If it is, remove it from the openSet and go to the next iteration 
//         for (int i = 0 ; i < openSet.size(); i++){
            
//             int nodeIdx     = openSet.at(i).first;
//             float nodeWeight= openSet.at(i).second;

//             if (count(closedSet.begin(), closedSet.end(), adjNodeIdx)){
//                 openSet.erase(openSet.begin()); // erase it from the openSet
//                 continue;
//             }else
//             // 4.2) check if it needs to be updated in the openSet
//             if (count(openSet.begin(), openSet.end(), adjNodeIdx)){
//                 openSet.erase(openSet.begin()); // erase it from the openSet
//                 continue;
//             }else // 4.3) not in the open nor closed set
//             {
//                 // was already added to the openSet so no need to do anything here
//             }
//         }
        
//     }

        
// }

