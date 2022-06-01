#include<iostream>
#include<list>
#include<algorithm>

using namespace std;

double sum (list<double> a){
    double s = 0.0;
    for (auto el : a)
        s = s+el;
    return s;
}

double prod (list<double> a){
    double p = 1.0;
    for (auto el : a)
        p = p*el;
    return p;
}

int main ()
{
    list<double> L = {59.9, 13.7, 10.0, 98.44, 16.7, 20.269, 1.5};
    cout << "Lista : ";
    for(auto el : L)
        cout << el << "  ";
    cout << endl;

    cout << "Suma elemenata je: " << sum(L) << endl;
    cout << "Umnozak elemenata je: " << prod(L) << endl;
    L.sort();
    cout << "Najmanji element je: " << L.front() << endl;
    cout << "Najveci element je: " << L.back() << endl;

    return 0;
}