#include "genericCompleteBT.h"
#include<limits>

template<typename K, typename V>
class MinPriorityQueue {
public:
    CompleteBinaryTree<K, V> tree;

    MinPriorityQueue();
    MinPriorityQueue(const MinPriorityQueue&);

    //spusta neki cvor dolje dok god je to moguce po pravilima heapa
    void downHeap(Node i);
    //podize neki cvor dolje dok god je to moguce po pravilima heapa
    void upHeap(Node i);

    // s obzirom na prosljeđeni vektor, izgrađujemo prioritetni red
    // (pretpostavljamo da je prioritetni red prazan, ili pregazimo
    // sve dosad pohranjene parove)
    void buildMinHeap(const vector<pair<K, V>>& L);

    inline V minimum() const { return tree.N.front().second; } //tree.N = vector<pair<K,V>>.front().second -> minimalna vrijednost 
    V extractMin();
    // pronalazimo element s indeksom i, te ga postavljamo
    // na odgovarajuće mjesto s obzirom na njegov novi kljuc
    // newKey
    void decreaseKey(Node i, K newKey);
    void insert(const pair<K, V>& v);

};

template<typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue(): tree{} {}

template<typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue(const MinPriorityQueue& bt): tree{bt.tree.N} {} //kopira sadrzaj vector<pair<K,V>>

template<typename K, typename V>
void MinPriorityQueue<K, V>::downHeap(Node i) {
    Node l = tree.left(i);
    Node r = tree.right(i);

    Node smallest{};

    if (l < tree.getSize() && tree[l].first < tree[i].first) //provjeravamo lijevu stranu
        smallest = l;
    else 
        smallest = i;

    if (r < tree.getSize() && tree[r].first < tree[smallest].first) //provjeravamo desnu stranu
        smallest = r;

    if (smallest != i) {
        tree.swapNodes(i, smallest); //swapamo i, najmanji
        downHeap(smallest);
    }
}

template<typename K, typename V>
V MinPriorityQueue<K, V>::extractMin() {
    if (tree.empty())
        0;
    else {
        V value = minimum();
        tree[0] = tree[tree.getSize()-1]; //0-ti element tree-a ce biti zadnji element tree-a
        //pobrinemo se oko tehnickih detalja
        tree.setSize(tree.getSize() - 1); //smanjimo velicinu za 1
        tree.N.pop_back(); // remove last element
        downHeap(0); // radimo downheap pocevsi od 0-tog elementa
        return value;
    }
}

template<typename K, typename V>
void MinPriorityQueue<K, V>::upHeap(Node i) {
    if (i == 0)
        return;
    
    while (i>0 && tree[tree.parent(i)].first > tree[i].first) {
        tree.swapNodes(tree.parent(i), i);
        i = tree.parent(i);
    }
}

template<typename K, typename V>
void MinPriorityQueue<K, V>::decreaseKey(Node i, K key) {
    if (i >= tree.getSize() || key > tree[i].first) //ne postoji ili ne mozemo nista decreasat
        return;
    
    tree[i].first = key; // novi key = key
    upHeap(i);
}

template<typename K, typename V>
void MinPriorityQueue<K, V>:: insert(const pair<K, V>& v) {
    tree.setSize(tree.getSize() + 1);
    tree.N.push_back({ numeric_limits<K>::max(), v.second }); //dodamo na kraj novi element koji ima ogroman key(najveci od svih mogucih K)
    decreaseKey(tree.getSize() - 1, v.first);
}

template<typename K, typename V>
void MinPriorityQueue<K, V>:: buildMinHeap(const vector<pair<K,V>>& L) {
    tree.N = L;
    tree.setSize(L.size());

    for(unsigned int i{tree.getSize() / 2 - 1}; i >= 0; i--) // idemo po svim ne-listovima i radimo downHeap()
        downHeap(i);    
}

template <typename K, typename V>
ostream& operator<<(ostream& os, const pair<K,V> p) {
    return os << "K: " << p.first << ", V: " << p.second << ";\t"; 
}

template <typename K, typename V>
ostream& operator<<(ostream& os, const MinPriorityQueue<K,V>& mpq) {
    os << "Priority queue: " << endl;
    MinPriorityQueue<K, V> mpq2{mpq};
    
    while (!mpq2.tree.empty())
        os << mpq2.extractMin() << "\t";
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

    return 0;
}