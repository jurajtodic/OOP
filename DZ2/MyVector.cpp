#include<iostream>
using namespace std;

class MyVector{
protected:
    unsigned int _size, _capacity;
    int* P;
public:
    MyVector(){
        _capacity = 1;
        _size = 0;
        P = new int[_capacity];
    }
    MyVector(const MyVector& v){
        P = new int [v.getCapacity()];
        if (v.getSize()!=0){
            for (int i = 0; i < v.getSize(); i++){
                P[i] = v.P[i];
            }
        }
        _size = v.getSize();
        _capacity = v.getCapacity();
    }
    ~MyVector() {
        delete [] P;
    }

    void pushBack(int x) { 
        if (_size == _capacity) { 
            int* T = new int[2 * _capacity]; 
            //copying old array elements to new array  
            for (int i = 0; i < _capacity; i++)  
                T[i] = P[i];   

            delete[] P; 
            _capacity = 2*_capacity; 
            P = T; 
        } 
        // ovaj dio se uvijek izvede
        P[_size] = x; 
        _size++; 
    } 

    int popBack(){
        if (_size*2==_capacity) {
            int* T = new int[_capacity/2];
            //copying old array elements to new array  
            for (int i = 0; i < _size; i++)  
                T[i] = P[i];    
            delete[] P; 
            _capacity = _capacity/2; 
            P = T; 
        }
        return _size--; // tu je return samo zato sto je kodomena int
    }

    unsigned int getSize() const {return _size;}
    unsigned int getCapacity() const {return _capacity;}

    void print() {
        for (int i=0; i<_size; i++)
            cout << P[i] << " ";
        cout << endl;
    }

    bool empty() const { return (_size == 0); }
    bool full() const { return (_size == _capacity); }

    int& at(unsigned int pos){
        return (P[pos-1]);
    }

    int& front(){
        return P[0];
    }
    int& back() {
        return P[_size-1];
    }
};

int main ()
{
    MyVector *vektor1 = new MyVector;
    for (int i = 1; i<11;i++)
        vektor1->pushBack(i);
    cout << "Prvi vektor:" ;
    vektor1->print();
    cout << endl;

    MyVector *vektor2 = new MyVector (*vektor1);
    cout << "Drugi vektor:";
    vektor2->print();
    cout << endl;
    for (int i = 10; i>0; i--) {
        vektor2->popBack();
        vektor2->print();
    }
    return 0;
}