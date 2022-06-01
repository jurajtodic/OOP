#include <iostream>
using namespace std;

struct Node {
    Node* prev;
    Node* next;
    double value;

    Node();
    Node(double value);
    Node(const Node& n);
    // prilikom ciscenja ispraznjujemo adresu
    ~Node();

    // swap premjesta sadrzaj izmedu dva cvora 
    void swap (Node& n);
    // ispisujemo adresu, adresu prethodnog, adresu sljedeceg te vrijednost
    void print() const;
};

Node :: Node() : prev{nullptr}, next{nullptr}, value{} {}

Node :: Node (double value) : prev{nullptr}, next{nullptr}, value{value} {}

Node :: Node (const Node& n) {
    value = n.value;
    prev = n.prev;
    next = n.next;
}

Node :: ~Node() {
    cout << "Delete node at: " << this << endl;
}


void Node :: swap(Node& n) {
        value += n.value;
        n.value = value - n.value;
        value -= n.value;
}


void Node :: print () const {
    cout << "Node at: " << this << "; prev at: " << prev << ";next at: " << next << "; value:" << value << endl;
}

class CDLL {
protected:
    Node* head;
    Node* tail;
public:
    CDLL();
    CDLL (const CDLL& c);
    ~CDLL();

    bool empty() const;
    // postavi vrijednost na pocetak
    void prepend(double value);
    // postavi vrijednost na kraj
    void append (double value);
    // uklkoni cvor sa pocetka i vrati njegovu vrijednost
    double removeFromHead();
    // ukloni cvor sa kraja i vrati njevu vrijednost
    double removeFromTail();
    // ispisujemo adresu head+a, taila+a te sve cvorove
    void print() const;
    void sort();    
};

CDLL :: CDLL() : head{nullptr}, tail{nullptr} {}

CDLL :: CDLL(const CDLL& c) : CDLL{} {
    Node* it = c.head;
    do {
        append(it->value);
        it = it-> next;
    } while(it != c.head);
}

CDLL :: ~ CDLL() {
    while(!empty())
        removeFromHead();
}

bool CDLL :: empty() const { return head == nullptr;}

void CDLL :: prepend (double value) {
    Node* n = new Node (value);
    if (empty()) {
        n->next = n->prev = head = tail = n;
    } else {
        n->next = head; // n je prije heada
        head->prev = n;
        n->prev = tail; // n je poslije taila
        tail->next = n;
        head = n;
    }
    
}
void CDLL :: append(double value) {
    prepend(value); // dodati na kraj je isto kao i dodati na pocetak i HEAD I TAIL pomaknuti za jedan udesno
    head = head->next;
    tail = tail->next;
}

double CDLL :: removeFromHead() {
    if (!empty()) {
        double v = head->value; 
        Node* toDelete = head; 

        if (head==tail) // ako lista ima samo jedan element
            head = tail = nullptr;
        else {
            tail->next = head->next;
            head->next->prev = tail;
            head = head->next;
        }
        
        delete toDelete;
        return v;
    }
}

double CDLL :: removeFromTail() {
    if (!empty()) {
    head = head->prev;
    tail = tail->prev;
    return removeFromHead();
    }
}

void CDLL :: print() const {
    cout << "--------------------------------------------------------" << endl;
    cout << "Head at: " << head << "; tail at: " << tail << endl;

    if (!empty()) {
        cout << "--------------------------------------------------------" << endl;
        Node* it = head;
        do {
            it -> print();
            it = it->next;
        } while (it != head);
    }
    cout << "--------------------------------------------------------" << endl;
}

void CDLL :: sort() {
    for (Node* j = head->next; j!= head; j = j->next) {
        double key = j-> value;
        Node* i = j->prev;
        while (i != tail && i->value > key) {
            i->next->swap(*i);
            i = i->prev;
        }
        i->next->value = key;
    }
}

int main ()
{
    CDLL* lista = new CDLL ();

    double l[] = {59.9, 13.7, 10.0, 98.44, 16.7, 20.269, 1.5};

    for (int i = 0; i<7; i++)
        lista->append(l[i]);
    lista->print();

    CDLL* lista2 = new CDLL (*lista);
    lista2->sort();
    lista2->print();

    delete lista;
    delete lista2;

    return 0;
}
