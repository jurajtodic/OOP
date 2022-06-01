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
            // deleting previous array 
            delete[] P; 
            _capacity = 2*_capacity; 
            P = T; //P[_capacity*2] = T[_capacity*2]
            // P[_size] = x; 
            // _size++; 
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
            // deleting previous array 
            delete[] P; 
            _capacity = _capacity/2; 
            P = T; //P[_capacity/2] = T[_capacity/2]
        }
        return _size--;
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

    // operator pridruzivanja
    MyVector& operator=(const MyVector&);

    /*
    Povećaj element na itom mjestu za vrijednost
    koja se nalazi na itom mjestu vektora
    prosljeđenog po referenci
    */
    MyVector& operator+=(const MyVector&);
    
    //zbroj vektora
    MyVector operator+(const MyVector&) const;

    //skalarni produkt vektora
    int operator*(const MyVector&) const;

    //provjera jesu li dva vektora jednaki po elementima
    bool operator==(const MyVector&) const;

    //provjera jesu li dva vektora različiti po elementima
    bool operator!=(const MyVector&) const;

    //operatori dohvaćanja
    const int& operator[](int) const;
    int& operator[](int);

    //početak i kraj vektora (obratite pažnju što treba vraćati end)
    int* begin() const;
    int* end() const;
};

const int& MyVector :: operator[](int i) const {
    return P[i];
}

int& MyVector :: operator[](int i) {
    return P[i];
}

MyVector& MyVector :: operator=(const MyVector& c) {
    if (_size != 0) delete [] P;
    _capacity = c._capacity;
    _size = c._size;
    P = new int [_capacity];
    for(int i = 0; i < _size; i++)
        P[i] = c.P[i];

    return *this;
}

MyVector& MyVector :: operator+=(const MyVector& c) {
    for(int i = 0; i<_size; i++)
        P[i] += c.P[i];
    return *this;
}

MyVector MyVector :: operator+(const MyVector& c ) const {
    MyVector w{*this};
    return w += c;
}

int MyVector :: operator*(const MyVector& c) const {
    int s=0;
    for(int i = 0; i < _size; i++){
        s = s + P[i]*c.P[i];
    }
    return s;
}

bool MyVector :: operator==(const MyVector& c) const{
    int s = 0;
    for (int i = 0; i<_size; i++){
        if (P[i]!=c.P[i])
            s++;
    }
    return (s==0);
}

bool MyVector :: operator!=(const MyVector& c) const{
    int s = 0;
    for (int i = 0; i<_size; i++){
        if (P[i]!=c.P[i])
            s++;
    }
    return (s!=0);
}

int* MyVector :: begin() const {
    return &P[0];
}

int* MyVector :: end() const {
    return &P[_size-1];
}


int main ()
{
    MyVector *vektor1 = new MyVector;
    for (int i = 1; i<5;i++)
        vektor1->pushBack(i);
    cout << "Prvi vektor:" ;
    vektor1->print();
    cout << endl;

    MyVector *vektor2 = new MyVector;
    for (int i = 5; i<9;i++)
        vektor2->pushBack(i);
    cout << "Drugi vektor:" ;
    vektor2->print();
    cout << endl;

    *vektor1+=*vektor2;
    cout << "vektor1+=vektor2 : ";
    vektor1->print();
    cout << endl;

    return 0;
}