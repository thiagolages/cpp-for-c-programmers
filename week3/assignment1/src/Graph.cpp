#include "Graph.hpp"

Graph::Graph(): size(10), prob(0.2){createGraph(); } // Default constructor

Graph::Graph(int size, float prob): size(size), prob(prob){createGraph();}

Graph::~Graph(){
    // both matrix[i] and matrix[] are arrays, so we should use delete[] for both
    for (int i = 0; i < size; i++){
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
}

int Graph::getSize(){return this->size;}

void Graph::print(){ 

    cout << "Matrix Representation: " << endl << endl;
    cout << "  X | ";
    for (int i=0; i < this->size; i++){cout << i << ".0 | ";}
    cout << endl;
    for (int i=0; i < this->size*7; i++) cout << "_";
    cout << endl;

    for (int i = 0; i < this->size; i++){
        cout << i << ".0";
        for (int j = 0; j < this->size; j++){
            cout << " | " << this->matrix[i][j];
        }
        cout << " | " << endl;
        for (int k=0; k < (this->size)*7; k++) cout << "_";
        cout << endl;
    }

    cout << endl;
    cout << "List Representation: " << endl << endl;
    for (int i = 0; i < this->list.size(); i++){
        cout << i << " -> ";
        for (int j = 0; j < this->list.at(i).size(); j++){
            cout << "(" << this->list.at(i).at(j).first << "," << this->list.at(i).at(j).second << "), "; 
        }
        cout << endl;
    }
}

void Graph::createGraph(){
    cout << setprecision (1) << fixed;
    cout << "Creating graph.." << endl;
    srand(time(0)); // seeding the pseudo-random generator
    
    // Allocating memory for the graph matrix
    this->matrix = new float*[this->size];
    for (int i = 0; i < this->size; i++){
        this->matrix[i] = new float[this->size];
    }

    // Allocating memory for the graph list
    this->list.resize(this->size);
    
    // Filling the graph with edges, based on a probability
    float weight = 0.0; // auxiliary to fill values of weights
    for (int i = 0; i < this->size; i++){
        for (int j = 0; j < this->size; j++){
            if(i == j) {
                this->matrix[i][j] = 0.0; // No loops, so no edge between the element with itself
            }
            // REALLY IMPORTANT: since we're filling a symmetrical matrix, we have to make sure i < j, otherwise values will be
            // overwritten in the matrix and it won't be symmetrical anymore
            else if (i < j){                
                
                // will create an integer between 1-9 for the edge weight, if the probability is met

                if (rand()%10 < prob*10.0 && i <= j){
                    weight = rand()%9 + 1; // 1 to 9
                    this->matrix[i][j] = weight; // fill in the matrix
                    this->matrix[j][i] = weight;
                    this->list.at(i).push_back(make_pair(j, weight)); // fill in the list
                    this->list.at(j).push_back(make_pair(i, weight)); // fill in the list
                }
            }
        }
    }
    cout << "Done creating graph !" << endl;
}

