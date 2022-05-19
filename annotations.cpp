#include <iostream>

// templates
// example: swap function

inline void swap(int& x, int& y){
    int temp = x;
    x = y;
    y = temp;
}

template<class T>  // just add this one line
inline void swap(T& x, T& y){
    T temp = x;
    x = y;
    y = temp;
}

// Module 3.2 - Point and its constructor
class Point{
    private:
        double x, y;
        const double specialVariable;
    public:
        // Default constructor (does not contain arguments, it's called 'void signature')
        Point(): x(0.0), y(0.0), specialVariable(0.0) {} // x = 0.0; y = 0.0; specialVariable = 0.0;

        // INITIALIZER LIST SYNTAX: 'x(x), y(y)' -> assigns variables right after the constructor
        
        // Syntax: ClassName(T1 arg1, T2, arg2): classAttribute1(arg1), classAttribute1(arg2)
        // after the colon(:), we use the attribute of the class - classAttribute1 - followed by 
        // some expression, which can be the argument (arg1) for example, so we have: classAttribute1(arg1)
        // IN THIS CASE, we can use the same name for the argument and the variable, like variableName1(variableName1)

        // There's "nothing" inside the constructor itself. The assignments were made using the 'initializer list syntax'
        // IMPORTANT NOTE: this is INITIALIZATION, not ASSIGNMENT, meaning if we have a 
        // private const int specialVariable;
        //  declaration for example, the following is INVALID if using assignments:
        /* Point (double x, double y, double special){
            this->x = x;
            this->y = y;                       
            this->specialVariable = special; // INVALID, since its a const
        }
        */
        // HOWEVER, the following is VALID:
        /* Point (double x, double y, double special): x(x), y(y), specialVariable(special){}
        */

        Point(double x=0.0, double y=0.0, double specialVariable=0.0): x(x), y(y), specialVariable(specialVariable) {} 
        
        // If we didn't have the 'specialVariable' as a const, this declaration:
        /*Point(double x=0.0, double y=0.0,double specialVariable=0.0): x(x), y(y),specialVariable(specialVariable) {} */
        // Would be equivalent to the following:
        /* Point(double x=0.0, double y=0.0, double specialVariable=0.0) {
            this->x = x;
            this->y = y;
            // this->specialVariable = specialVariable; // this doesnt work in fact because specialVariable is a const
        }*/

        double getx(){return x;}
        void setx(double value){this->x = value;}

};

int main(int argc, char** argv){

    


    return 0;
}