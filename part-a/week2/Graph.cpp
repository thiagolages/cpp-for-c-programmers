#include "Graph.hpp"

using namespace std;

class Graph{
    public:
        double value;
        vector<double> edges;
    
    Graph(){
        this->value = 0.0;
    }
    Graph(double& value){
        this->value = value;
    }
    Graph(double& value, vector<double>& edges){
        this->value = value;
        this->edges = edges;
    }

};