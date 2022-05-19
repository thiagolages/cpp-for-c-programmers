#include <iostream>
#include <random>
#include <ctime>
#include <vector>

using namespace std;

class Graph {
    private:
        int size;           // number of nodes in the graph
        float prob;         // probability of existing an edge between two nodes
        bool** matrix;      // representation of the graph in a matrix format
        vector<float> nodes;// actual nodes of the graph - not necessary for this, but let's keep it for now

    public:
        Graph(): size(20), prob(0.2){createGraph();} // Default constructor
        Graph(int size, float prob): size(size), prob(prob){createGraph();}

    
    private:
        void createGraph(){
            srand(time(0)); // seeding the pseudo-random generator
            
            // Allocating memory for the graph
            this->matrix = new bool*[size];
            for (int i = 0; i < size; i++){
                this->matrix[i] = new bool[size];
            }
            
            // Filling the graph with edges, based on a probability
            for (int i=0; i < size; i++){
                for (int j=0; j < size; j++){
                    if(i == j) {
                        this->matrix[i][j] = 0; // No loops, so no edge between the element with itself
                    }else{
                        this->matrix[i][j] = this->matrix[j][i] = (rand() < prob); // symmetrical matrix
                    }
                }
            }
        }
};

int main (int argc, char** argv){

    // Implementation of Dijkstra's Shortest Path Algorithm

    // Step 1 - Graph creation
    int n   = 10; // number of size in the graph
    float p = 0.1; // probability of having an edge between two size
    
    Graph *g = new Graph(n, p);

    // We need:
    /*  1) an open set
        2) a closed set
        3) termination conditions:
            - if the closed set size == graph size
            OR
            - if there are no more items in the open set
    */


    return 0;
}