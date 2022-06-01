#include <iostream>
#include<list>
using namespace std;

template <typename K, typename V>
struct MinPriorityQueue {

    list <pair<K,V>> container;

    void insert(const pair<K, V>& el) {
        auto it{container.begin()}; 
        while (it != container.end() && el.first > it->first) 
            it++; // sljedeca adresa
        
        container.insert(it, el); // unesemo taj element na mjesto iteratora
    }

    V extractMin() { 
        V value = container.front().second;
        container.pop_front();
        return value;
    }

    // pronalazimo element s kljucem key, te ga postavljamo
    // na odgovarajuće mjesto s obzirom na njegov novi kljuc newKey
    void decreaseKey(const K& key, const K& newKey) {

        auto it{container.begin()}; 
        while (it != container.end() &&  it->first != key) //iteriramo dok ne dodemo do zeljenog kljuca
            it++;
        
        if (it == container.end()) return; //ako nije nasao kljuc return
        
        pair<K,V> el = *it; 
        el.first = newKey; 

        container.erase(it); 
            
        // unosimo element na odgovarajuce mjesto
        auto it2{container.begin()};
        while (it2 != container.end() &&  it2->first < newKey)
            it2++;
        container.insert(it2, el); 
    }

};

template <typename K, typename V>
ostream& operator<<(ostream& os, const pair<K,V> p) {
    return os << "K: " << p.first << ", V: " << p.second << ";\t"; 
}

template <typename K, typename V>
ostream& operator<<(ostream& os, const MinPriorityQueue<K,V>& mpq) {
    for (auto it{mpq.container.begin()}; it != mpq.container.end(); it++)
        os << *it;
    return os << "\n\n";
}


int main ()
{
    MinPriorityQueue<int,string> lista{};
    
    lista.insert({1,"osoba4"});
    lista.insert({2,"osoba7"});
    lista.insert({7,"osoba5"});
    lista.insert({8,"osoba1"});
    lista.insert({5,"osoba6"});
    cout<<lista;

    lista.insert({6,"osoba9"});
    cout << lista;

    cout << lista.extractMin() << "\n";
    cout << lista;

    lista.decreaseKey(6,4);
    cout << lista;

    return 0;
}