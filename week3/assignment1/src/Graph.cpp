#include "Graph.hpp"

// Default constructor
Graph::Graph(): size(10), prob(0.2){
    createGraph(); 
    // cout << "Graph(): Graph object created !"<<endl;
}

Graph::Graph(int size, float prob): size(size), prob(prob){
    createGraph(); 
    // cout << "Graph(): Graph object created !"<<endl;
}

// Constructor for tests
Graph::Graph(bool test){
    this->size = 6;
    this->prob = 0.0; // not being used
    
    allocateMatrix();
    
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            this->matrix[i][j] = 0.0;
        }
    }

    // Matrix
    this->matrix[0][1] = this->matrix[1][0] = 3.0; // A-B, B-A
    this->matrix[0][3] = this->matrix[3][0] = 4.0; // A-D, D-A
    this->matrix[1][2] = this->matrix[2][1] = 5.0; // B-C, C-B
    this->matrix[1][4] = this->matrix[4][1] = 7.0; // B-E, E-B
    this->matrix[2][4] = this->matrix[4][2] = 3.0; // C-E, E-C
    this->matrix[2][5] = this->matrix[5][2] = 2.0; // C-F, F-C
    this->matrix[3][4] = this->matrix[4][3] = 2.0; // D-E, E-D
    this->matrix[4][5] = this->matrix[5][4] = 3.0; // E-F, F-E

    allocateList();

    // List
    this->list.at(0).insert(list.at(0).end(), {make_pair(1, 3.0), make_pair(3, 4.0)});                                          // A
    this->list.at(1).insert(list.at(1).end(), {make_pair(2, 5.0), make_pair(4, 7.0), make_pair(0, 3.0)});                       // B
    this->list.at(2).insert(list.at(2).end(), {make_pair(4, 3.0), make_pair(5, 2.0), make_pair(1, 5.0)});                       // C
    this->list.at(3).insert(list.at(3).end(), {make_pair(4, 2.0), make_pair(5, 9.0), make_pair(0, 4.0)});                       // D
    this->list.at(4).insert(list.at(4).end(), {make_pair(1, 7.0), make_pair(2, 3.0), make_pair(4, 2.0), make_pair(5, 3.0)});    // E
    this->list.at(5).insert(list.at(5).end(), {make_pair(2, 2.0), make_pair(3, 9.0), make_pair(4, 3.0)});                       // F
    
    
    // cout << "Graph(): Graph object created !"<<endl;
}

Graph::~Graph(){    
    // both matrix[i] and matrix[] are arrays, so we should use delete[] for both
    for (int i = 0; i < size; i++){
        delete[] this->matrix[i];
    }
    delete[] this->matrix;

    // cout << "~Graph(): Graph object destroyed !"<<endl;
}

void Graph::allocateMatrix(){
    this->matrix = new float*[this->size];
    for (int i = 0; i < this->size; i++){
        this->matrix[i] = new float[this->size];
    }
}

void Graph::allocateList(){
    this->list.resize(this->size);
}

int Graph::getSize(){return this->size;}

void Graph::print(){ 

    cout << endl;
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

    cout << setprecision (1) << fixed; // set fixed precision for all outputs to come
    srand(time(0)); // seeding the pseudo-random generator
    
    // Allocating memory for the graph matrix
    allocateMatrix();

    // Allocating memory for the graph list
    allocateList();
    
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
}

