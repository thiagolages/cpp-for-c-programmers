// Program in C++
// change to C++ io - OK
// change to one line comments - OK
// change defines of constants to const - OK
// change array to vector<> - OK
// inline any short function - OK


#include <iostream>
#include <vector>

using namespace std;

const int arrSize = 40;

// Sums the whole array
inline void sum(int &accum, vector<int> data){
    accum = 0;
    for(int i = 0; i < data.size(); ++i){
        accum += data[i];
    }
}

int main() {

    int accum = 0;
    vector<int> data(arrSize);

    for(int i = 0; i < arrSize; ++i){
        data[i] = i;
    }

    sum(accum, data);
    cout << "sum is " << accum << endl;

    return 0;
}