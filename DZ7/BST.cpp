#include<iostream>
#include<vector>
using namespace std;


template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node *parent, *left, *right;

    friend ostream& operator<<(ostream& os, const Node& n) {
    os << "Node at: " << &n << ";parent at: " << n.parent << ";left at: " << n.left << ";right at: " << n.right << "\n" << "Key: " << n.key << ";value:" << n.value;
    return os;
    }

};


template <typename K, typename V>
struct BST {
    Node<K, V> *root;

    BST();

    // copy konstruktor (pripaziti na shallow-copy)
    BST(const BST& bst);

    ~BST();

    // pretrazuj podstablo s korijenom x dok ne pronadeš čvor
    // s vrijednoscu key (u suprotnom vrati nullptr)
    Node<K, V>* search(Node<K, V>* x, K key);

    // vrati pokazivač na čvor koji ima minimalnu vrijednost
    // kljuca u podstablu čiji je korijen x
    Node<K, V>* minimum(Node<K, V>* x);

    // vrati pokazivač na čvor koji ima maksimalnu vrijednost
    // kljuca u podstablu čiji je korijen x
    Node<K, V>* maximum(Node<K, V>* x);

    // vrati sljedbenika čvora x po vrijednosti key unutar stabla
    Node<K, V>* successor(Node<K, V>* x);

    // vrati prethodnika čvora x po vrijednosti key unutar stabla
    Node<K, V>* predecessor(Node<K, V>* x);

    // unesi novi čvor brinuvši se o definiciji binary search tree-a
    void insert(const K& key, const V& value);

    // zamijeni podstabla s korijenima u i v
    void transplant(Node<K, V>* u, Node<K, V>* v);

    // obriši čvor x brinuvši se o definiciji binary search tree-a
    void remove(Node<K, V>* x);

    // napravi inorder obilazak, vrijednosti redom pohrani u vektor nodes
    void inorderWalk(Node<K, V>* x, vector<Node<K, V>*>& nodes) const;

    // copy pridruživanje (pripaziti na shallow-copy)
    BST& operator=(const BST& bst);

    friend ostream& operator<<(ostream& os, const BST& bst) {
        vector<Node<K,V>*> nodes{};
        bst.inorderWalk(bst.root, nodes);
        os << "--------------------------------------" << endl;
        os << "Binary search tree with root at: " << bst.root << endl;
        os << "Nodes: " << endl;
        for(Node<K,V>* nodePtr: nodes)
            os << *nodePtr << endl;
        os << "--------------------------------------" << endl;
        return os;
    }
};


template <typename K, typename V>
BST<K, V>::BST(): root{nullptr} {}

template <typename K, typename V>
BST<K, V>::BST(const BST& bst) {
    vector<Node<K,V>*> nodes{};
    bst.inorderWalk(bst.root, nodes); //krece od bst.root i prolazi inorder algoritmom i sprema vrijednost u vector nodes
    for (Node<K, V>* nodePtr : nodes) // dodajemo u BST elemente iz vectora nodes
        insert(nodePtr->key, nodePtr->value);
}


template <typename K, typename V>
BST<K, V>& BST<K,V>::operator=(const BST& bst) {
    this->~BST();
    root = nullptr;

    vector<Node<K,V>*> nodes{};
    bst.inorderWalk(bst.root, nodes);
    for (Node<K, V>* nodePtr : nodes)
        insert(nodePtr->key, nodePtr->value);
    //return *this;
}


template <typename K, typename V>
BST<K, V>::~BST() {
    vector<Node<K,V>*> nodes{};
    inorderWalk(root, nodes);
    for (Node<K, V>* nodePtr : nodes)
        delete nodePtr;
}

// pretrazuj podstablo s korijenom x dok ne pronadeš čvor
// s vrijednoscu key (u suprotnom vrati nullptr)
template <typename K, typename V>
Node<K, V>* BST<K, V> :: search(Node<K, V>* x, K key) {
    if (x == nullptr || x->key == key)
        return x;
    
    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);   
}


template <typename K, typename V>
Node<K, V>* BST<K,V>:: minimum(Node<K, V>* x) {
    while(x->left != nullptr)
        x = x->left;
    return x;
}


template <typename K, typename V>
Node<K, V>* BST<K,V>:: maximum(Node<K, V>* x) {
    while(x->right != nullptr)
        x = x->right;
    return x;
}

// vrati sljedbenika čvora x po vrijednosti key unutar stabla (INORDER SUCCESOR)
template <typename K, typename V>
Node<K, V>* BST<K,V> :: successor(Node<K, V>* x) {
    if (x->right != nullptr)
        return minimum(x->right);
    
    Node<K,V>* y = x->parent;
    while (y != nullptr && y->right == x) {
        x = y;
        y = y->parent;
    }
    return y;
}


template <typename K, typename V>
Node<K, V>* BST<K,V> :: predecessor(Node<K, V>* x) {
    if (x->left != nullptr)
        return maximum(x->right);

    Node<K,V>* y = x->parent;
    while (y != nullptr && y->left == x) {
        x = y;
        y = y->parent;
    }
    return y;
}



// unesi novi čvor brinuvši se o definiciji binary search tree-a
template <typename K, typename V>
void BST<K,V>:: insert(const K& key, const V& value) {
    Node<K,V>* z = new Node<K,V> {key, value, nullptr, nullptr, nullptr}; 
    Node<K, V>* y{nullptr}; //y ce biti parent od x dok se spustamo
    Node<K, V>* x{root};

    while (x != nullptr) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}


// zamijeni podstabla s korijenima u i v
template <typename K, typename V>
void BST<K,V>:: transplant(Node<K, V>* u, Node<K, V>* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left) // ako je u lijevo dijete svog roditelja
        u->parent->left = v; // postavljamo lijevo dijete tog roditelja (u) na v
    else 
        u->parent->right = v; // ako je u desno dijete svog roditelja postavljamo desno dijete tog roditelja na v
    
    if (v != nullptr) v->parent = u->parent;
}
     

// obriši čvor x brinuvši se o definiciji binary search tree-a
template <typename K, typename V>
void BST<K,V>:: remove(Node<K, V>* x) {
    if (x->left == nullptr)
        transplant(x, x->right);
    else if (x->right == nullptr)
        transplant(x, x->left);
    else
    {
        Node<K,V>* y = minimum(x->right); // y = sljedbenik od x->right
        if (y->parent != x) {
            transplant(y, y->right);
            y->right = x->right;
            y->right->parent = y;
        }

        transplant(x,y);
        y->left = x->left;
        y->left->parent = y;        
    }
    delete x;
}


// napravi inorder obilazak, vrijednosti redom pohrani u vektor nodes
template <typename K, typename V>
void BST<K,V>:: inorderWalk(Node<K, V>* x, vector<Node<K, V>*>& nodes) const {
    if (x != nullptr) {
        inorderWalk(x->left, nodes);
        nodes.push_back(x);
        inorderWalk(x->right, nodes);
    }
}


int main ()
{
    BST<int, string> v{};

    v.insert(20, "Korisnik1");
    v.insert(25, "Korisnik2");
    v.insert(15, "Korisnik3");
    v.insert(17, "Korisnik4");

    cout << v;

    v.remove(v.root);

    cout << v;
  
    return 0;
}