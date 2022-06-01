#include<iostream>
#include<vector>
using namespace std;

class DynamicStack {
protected:
    vector<int> container;
public:
    DynamicStack() {};
    DynamicStack(const DynamicStack& S){
         container = S.container;
    }

    bool empty() const{
        return (container.empty());
    }

    void push(int x){
        container.push_back(x);
    }
    int pop(){
        container.pop_back();
    }

    void print(){
        for (int i=0; i<container.size(); i++) 
            cout <<  container.at(i) << " ";
        cout << endl;  
    }
};

int main ()
{
    DynamicStack *vec1 = new DynamicStack;
    for(int i = 1; i<11; i++)
        vec1->push(i);
    cout<<"Prvi vektor: ";
    vec1->print();

    DynamicStack *vec2= new DynamicStack(*vec1);
    cout<< "Drugi vektor: ";
    vec2->print();
    for(int i = 11; i>1; i--){
        vec2->pop();
        vec2->print();
    }
    return 0;
}