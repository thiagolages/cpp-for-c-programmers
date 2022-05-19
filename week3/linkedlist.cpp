#include <iostream>

using namespace std;

typedef struct slistelem {
    int data; 
    slistelem* next;
} slistelem;

class Slist{
    private:
        slistelem* head;
        slistelem* cursor;
    public:
        Slist():head(nullptr), cursor(nullptr){}
        Slist(const int* data, int size){
            
            if (size == 0 || data == nullptr){
                this->head = nullptr;
                this->cursor = nullptr;
            }else{

                int i = 0;
                slistelem *lastElement;
                slistelem *newElement = new slistelem;
                
                this->head = newElement;
                newElement->data = data[0];
                newElement->next = nullptr;
                lastElement = newElement;
                i++;

                while (i < size){
                    newElement = new slistelem;
                    newElement->data = data[i];
                    lastElement->next = newElement;
                    lastElement = newElement;
                    
                    i++;

                } // end 'while'            
            } // end 'else'
        }
        Slist(const Slist& list){ // Deep copy constructor
            if(list.head == nullptr){ // if there are no elements
                this->head  = nullptr;
                this->cursor= nullptr;
            }else{

            // This would be inside of the 'set up' as seen on module 3.10 - https://www.coursera.org/learn/c-plus-plus-a/lecture/tB8n3/3-10-deep-vs-shallow-copy
                slistelem* lastElement  = nullptr; // will always point to the last element on the new list
                slistelem* newElement   = new slistelem;
                
                newElement->data        = list.head->data;
                this->cursor            = list.head;
                this->head              = newElement;
                lastElement             = newElement;
                this->cursor            = this->cursor->next;
            // 'set up' ends here
            
                while(this->cursor != nullptr){
                    newElement = new slistelem;
                    newElement->data = this->cursor->data;
                    newElement->next = nullptr; // redundant, but just to illustrate

                    lastElement->next = newElement; // making the connection between the previously created 'newElement' to this current newElement
                    lastElement = newElement;       // making our pointer actually point to the last Element created
                    this->cursor = this->cursor->next; // updating the cursor
                }
                
                lastElement = nullptr; // Important ! making this auxiliary pointer point to nullptr before deleting it, otherwise would delete the actual last node
                delete lastElement;
            }
            this->cursor = this->head; // reset cursor to head
        }
        ~Slist(){release(head);}

    private:
        void release(slistelem* node_ptr){
            if(node_ptr->next == nullptr){
                delete node_ptr;
                return;
            }
            release(node_ptr->next);
        } 
    
    public:
        void prepend(int d){
            
            slistelem* elem = new slistelem;
            elem->data = d;
            elem->next = nullptr;

            if(this->head == nullptr){ // if there are no elements
                this->head = elem;
            }else{ // if there are already elements in the list, other than the nullptr head
                elem->next = this->head;
                this->head = elem;
            }
        }

        void print(){
            this->cursor = this->head; //making sure cursor points to the head
            while(this->cursor != nullptr){
                cout << this->cursor->data << ", ";
                this->cursor = this->cursor->next;
            }
            cout << "###" << endl;
            this->cursor = this->head;
        }

        inline bool operator==(const Slist& list){
            this->cursor = this->head;
            slistelem* aux = new slistelem;
            aux = list.head;
            while(this->cursor != nullptr && aux != nullptr){
                if (this->cursor->data != aux->data){
                    return false;
                }
                this->cursor = this->cursor->next;
                aux = aux->next;
            }
            return true;
        }
};


int main(int argc, char** argv){
    Slist a, b;
    int data[10] = {3, 4, 6, 7, -3, 5};
    Slist d(data, 6);
    Slist e(data, 10);
    a.prepend(9); a.prepend(8);
    cout << "List A: ";
    a.print();
    for (int i = 0; i < 40 ; i++){
        b.prepend(i*i);
    }
    cout << "List B: ";
    b.print();

    Slist c(b);
    Slist f(a);
    cout << "List C: ";
    c.print();
    cout << "List D: ";
    d.print();
    cout << "List E: ";
    e.print();
     cout << "List F: ";
    f.print();

    cout << "Is A == B ? " << (a == b ? "YES" : "NO") << endl;
    cout << "Is C == B ? " << (c == b ? "YES" : "NO") << endl;

    cout << "Is F == A ? " << (f == a ? "YES" : "NO") << endl;
}