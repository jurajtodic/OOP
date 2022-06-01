#include<iostream>
using namespace std;


// bazna klasa za staticki alocirano polje ili dinamicki alocirano polje
template <typename T, size_t S>
class Container {
protected:
    // kod nasljeđene klase vraca
    // pokazivač na prvi element polja
    virtual T* first() = 0;
    
    // kod nasljeđene klase vraća
    // pokazivač na konstantni prvi element polja
    virtual const T* first() const = 0;
public:
    Container() = default;
    virtual ~Container() = default;

    // vrati pokazivač na prvi element polja
    T* begin() { return first(); }

    // vrati pokazivač na zadnji element polja
    T* end() { return first() + S; } // jedan element nakon zadnjeg

    // vrati pokazivač na konstantni prvi element polja
    const T* begin() const { return first(); }

    // vrati pokazivač na konstantni zadnji element polja
    const T* end() const { return first() + S; }


    // preopterećeni operator dohvaćanja
    T& operator[](int i) { return *(first() + i); } //first() daje pointer pa ga moramo dereferencirati
    
    // konstantni preopterećeni operator dohvaćanja
    const T& operator[](int i) const { return *(first() + i); }

    friend ostream& operator<<(ostream& os, const Container& c) {
        c.print(os);  // pozvat ce print koji ce biti definiran u izvedenim klasama
    }

    virtual void print(ostream& os) const = 0;
};

template <typename T, size_t S>
class StaticContainer: private Container<T,S> {
private:
    T container[S]; // staticki alociran container duljine S, mogli smo odmah inicijalizirati T container[S] {} ali je "cleaner" u konstruktoru
protected:
    T* first() { return &container[0]; } // vratimo adresu prvog elementa polja
    const T* first() const { return &container[0]; }

public:
    StaticContainer(): container{} {}
    ~StaticContainer() {} // staticki alocirano polje pa nemoramo brinuti o dealokaciji memorije

    void print(ostream& os) const {
        for (const T& el : *this)
            os << el << "\t";
        os << "\n";
    }

    friend int main ();
};


template <typename T, size_t S>
class DynamicContainer: private Container<T,S> {
private:
    T* container; //mogli smo tu alocirati -> T* container{new T[S]}, int* container = new int[] ali smo u konstruktoru
protected:
    T* first() { return &container[0]; }
    const T* first() const { return &container[0]; }
public:
    DynamicContainer(): container{new T[S]} {}
    ~DynamicContainer() { delete [] container; } // dinamicki alocirano polje moramo dealocirati 

    void print(ostream& os) const {
        for (const T& el : *this)
            os << el << "\t";
        os << "\n";
    }

    friend int main();
};


int main ()
{
    DynamicContainer<int, 10> dcs[5]; // 5 static containera intova duljine 10 u polju dcs
    StaticContainer<int, 10> scs[5]; // 5 dynamic containera intova duljine 10 u polju scs

    int i = 0;
    int j = 0;

    for (DynamicContainer<int,10>& dc : dcs)
        for (int& el : dc) {
            el = i*10 + j;
            i++;
            j++;
        }
            
    i = 0;
    j = 0;

    for (StaticContainer<int,10>& sc : scs)
        for (int& el : sc) {
            el = i*10 + j;
            i++;
            j++;
        };

    // Container<int,10> znaci da je size pojedinog containera 10, ne da ima 10 containera u listi
    Container<int, 10>* containers[10]; // sve ih strpamo u jedno polje



    /*  u sljedecim for petljama radimo ovo: 
        containers[i] = &dc1
        containers[i] = &dc2 
        ...
    */
    int k = 0;
    for(DynamicContainer<int, 10>& dc : dcs) 
        containers[k++] = &dc;

    /*
        containers[i] = &sc1
        containers[i] = &sc2
        ...
    */ 
    for(StaticContainer<int, 10>& sc : scs)
        containers[k++] = &sc;


    //sumiramo sve containere sa svojim elementima u containers
    int s = 0;
    for(Container<int, 10>* container : containers)
        for(int& el : *container) //pointer na container pa ga moramo dereferencirati
            s += el;

    cout << s << endl;
    

    return 0;
}