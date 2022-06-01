#include <iostream>
using namespace std;

struct Node {
    double value;
    Node* next;

    Node();
    Node(double value);
    Node(const Node& n);
    ~Node();
    void print() const;
};

Node :: Node() : next(nullptr), value{} {}
Node :: Node (double value) : next(nullptr), value(value) {}
Node :: Node (const Node& n) : Node{n.value} { next = n.next; }
Node :: ~Node() { cout << "Delete node at: " << this <<endl; }
void Node :: print() const {
    cout << "Node at" << this /* adresa */ << "; value = " << value << " next at " << next << endl;
}

class CSLL {
protected:
    Node* tail;
public:
    CSLL();
    CSLL(const CSLL& c);
    ~CSLL();

    bool empty() const;
    void prepend(double value); // umetanje elementa na pocetak
    void append(double value); // umetanje na kraj

    double removeFromHead(); // vraca vrijednost onog sto smo obrisali

    void print() const;
};

CSLL :: CSLL() : tail(nullptr) {}

CSLL :: CSLL(const CSLL& c) : CSLL() { // pozivamo pretpostavljeni konstruktor umjesto da smo inicijalizirali tail
    if (!c.empty()) {
        Node* it = c.tail->next; // ovdje smo umjesto heada koristili c.tail->next
        do {
            append(it->value);
            it = it->next;
        }
        while (it != c.tail->next);
    }
}

CSLL :: ~CSLL() {
    while (!empty())
        removeFromHead();
}

bool CSLL :: empty() const { return tail == nullptr; }

void CSLL :: prepend(double value) {
    Node* n = new Node (value); //instanciramo novi cvor s vrijednoscu value, ne moramo ga brisati zazto sto desktruktor vec brise sve elemente
    if (empty()) {
        tail = n;    
        n->next = n;
    }
    else { // trapamo nesto na pocetak
        n->next = tail->next; 
        tail->next = n;
    }
}

void CSLL :: append(double value) {
    prepend(value); 
    tail = tail->next;
}

void CSLL :: print () const {
    cout << "--------------------------------------------------------" << endl;
    cout << "Tail at: " << tail << endl;
    
    if (!empty()) {
        cout << "--------------------------------------------------------" << endl;
        Node* it = tail->next;
        do {
            it -> print();
            it = it->next;
        } while (it != tail->next);
    }
    cout << "--------------------------------------------------------" << endl;
}

double CSLL :: removeFromHead() {
    if (!empty()) {
        double v = tail->next->value; // pohranjujemo vrijednost onog cvora kojeg zelimo obrisati
        Node* toDelete = tail->next; // kako ne bi doslo do MemoryLeaka njegovu adresu cemo spremiti sa strane u pokazivac toDelete
        
        if (tail->next == tail)
            tail = nullptr;
        else 
            tail->next = tail->next->next;

        delete toDelete;
        return v;
    }
}



/*---------------------------------------------------------------------------ZADATAK 4---------------------------------------------------------------------------*/

class DynamicQueue {
protected:
    CSLL container;
public:
    DynamicQueue();
    DynamicQueue(const DynamicQueue& q);
    ~DynamicQueue();

    bool empty() const;
    void enqueue(double x);
    double dequeue();

    void print() const;
};

DynamicQueue :: DynamicQueue(): container{} {} // triggerat ce se defaultni konstrunktor is CSLL-a
DynamicQueue :: DynamicQueue(const DynamicQueue& q) : container(q.container) {}
DynamicQueue :: ~DynamicQueue() = default; // vec definirano u CSLL-u

bool DynamicQueue :: empty() const {
    return container.empty();
}

void DynamicQueue :: enqueue(double x) {
    container.append(x);
}

double DynamicQueue :: dequeue() {
    if (!empty())
        return container.removeFromHead();
}

void DynamicQueue :: print() const {
    container.print();
}


int main () {

    CSLL* csll = new CSLL {};
    csll->print();

    double values[] = {59.9, 13.7, 10.0, 98.44, 16.7, 20.269, 1.5};
    for (const auto& value : values)
        csll->append(value);
    csll->print();

    CSLL* csll2 = new CSLL (*csll);
    csll2->print();

    delete csll;
    delete csll2;

// ZADATAK 4 DIO

    cout << endl;
    cout << "ZADATAK 4: " << endl;

    DynamicQueue* queue1 = new DynamicQueue {};
    queue1->print();

    double values2[] = {59.9, 13.7, 10.0, 98.44, 16.7, 20.269, 1.5};
    for (const auto& value : values2)
        queue1->enqueue(value);
    queue1->print();

    DynamicQueue* queue2 = new DynamicQueue (*queue1);
    queue2->print();

    delete queue1;
    delete queue2;
    return 0;
}
