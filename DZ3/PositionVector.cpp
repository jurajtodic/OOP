#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

struct PositionVector {
    double x, y;

    PositionVector(){
        x = 0.0;
        y = 0.0;
    }
    PositionVector(double a, double b){
        x = a;
        y = b;
    }
    PositionVector(const PositionVector& v){
        x = v.x;
        y = v.y;
    }

    double norm() const{
        return sqrt(pow(x,2.0) + pow(y,2.0));
    }

    void print() const{
        cout << "(x,y) : (" << x << ") (" << y << "); Norm:" << norm() << endl;  
    }
};

bool comp (const PositionVector& a, const PositionVector& b){
    return (a.norm()>b.norm());
}

int main ()
{
    PositionVector vecs[5] = {PositionVector (2.5, 3.6), PositionVector (5.5, 3.6), PositionVector (4.4, 4.4), PositionVector (10.0, 0.1), PositionVector (0.0, 0.0)};
    for (auto& vec : vecs) // (const PositionVector& vec : vecs)
        vec.print();

    sort(vecs, vecs+5, comp); // vecs-pointer na prvi positionVector, vecs+5-pointer na element iza zadnjeg elementa positionVector

    cout << "Vektori nakon sortiranja normi:" << endl;
    for(auto& vec : vecs)
        vec.print();
    return 0;
}