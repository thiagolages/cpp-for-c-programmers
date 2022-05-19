#include <iostream>

using namespace std;

// test00
void test00();
// without 'inline', it took ~1.403s to print 1milions numbers in the screen
template <class T>
void display(T x){
    cout << x;
}

// without 'inline', it took ~1.189s to print 1milions numbers in the screen (~15% faster)
// template <class T>
// void display(T x){
//     cout << x;
// }

// test01
void test01();

// test02
void test02();
typedef enum days{SUN, MON, TUE, WED, THU, FRI, SAT} days;
inline days operator++ (days &d){
    return d = static_cast<days>((static_cast<int>(d) + 1) % 7);
}
// shown in the class notes:
//days operator++(days &d)
//    { return d  = static_cast<int>d + 1 % 7; } 

ostream& operator<< (ostream& out, const days& d){
    switch (d) {
        case SUN: out << "SUN"; break;
        case MON: out << "MON"; break;
        case TUE: out << "TUE"; break;
        case WED: out << "WED"; break;
        case THU: out << "THU"; break;
        case FRI: out << "FRI"; break;
        case SAT: out << "SAT"; break;
        default:
            break;
    }

    return out;
}

int main (int argc, char** argv){

    if (argc < 2){
        cout << "Usage: ./test <Test Number>" << endl;
        return 0;
    }

    int testNum = stoi(argv[1]);

    switch (testNum)
    {
    case 0: // inline speed when printing 1 milion numbers
        test00(); break;
    case 1: // enum assignment 
        test01(); break;
    case 2: // enum operations overloading
        test02(); break;

    default:
        break;
    }
    
    cout << "Done !" << endl;
    return 0;
}

void test00(){
    for (int i=0; i < 1000000; i++){
        display(i);
    }
}
void test01(){
    enum colors{RED, WHITE, GREEN};
    cout << "With the definition 'enum colors{RED, WHITE, GREEN};', we get:" << endl;
    cout << RED << "," << WHITE << "," << GREEN << endl;
    
    enum colors2{RED2, WHITE2=3, GREEN2};
    cout << "With the definition 'enum colors{RED, WHITE=3, GREEN};', we get:" << endl;
    cout << RED2 << "," << WHITE2 << "," << GREEN2 << endl;
}
void test02(){
    days d = MON, e;
    e = ++d;
    cout << d << '\t' << e << endl;
}