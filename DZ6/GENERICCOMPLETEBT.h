#ifndef GENERIC_COMPLETE_BT_H
#define GENERIC_COMPLETE_BT_H

#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

typedef unsigned int Node;

template <typename K, typename V>
struct CompleteBinaryTree {

    vector<pair<K,V>> N;
    unsigned int size;

    CompleteBinaryTree(): N{}, size{0} {};
    CompleteBinaryTree(const vector<pair<K, V>>& L): N{L}, size{L.size()} {}

    //getters
    Node left(Node i) const {return 2*i+1;}
    Node right(Node i) const {return 2*i+2;}
    Node parent(Node i) const {return (i-1)/2;}

    pair<K, V>& element(Node i) {return N[i];}
    const pair<K,V>& element(Node i) const {return N[i];}

    // setters
    void updateLeft(Node i, const pair<K,V>& e) { N[left(i)] = e; }
    void updateRight(Node i, const pair<K,V>& e) { N[right(i)] = e; }
    void updateParent(Node i, const pair<K,V>& e) { N[parent(i)] = e; }

    bool isLeaf(Node i) const { return left(i) > size; }

    unsigned int getSize() const { return size; }
    void setSize(unsigned int newSize) { size = newSize; }
    bool empty() const { return size == 0; }

    void preorderPrint(Node);
    void postorderPrint(Node);
    
    void swapNodes(Node i, Node j) { swap(N[i], N[j]); } //swap iz algorithm

    const pair<K, V>& operator[](int i) const { return N.at(i); }
    pair<K, V>& operator[](int i) { return N.at(i); }
};

template <typename K, typename V>
void CompleteBinaryTree<K, V>::preorderPrint(Node i) {
    if (i > size)
        return;
    cout <<  N[i] << "  "; 
    preorderPrint(left(i));
    preorderPrint(right(i));  
}

template <typename K, typename V>
void CompleteBinaryTree<K, V>::postorderPrint(Node i) {
    if (i > size)
        return;
    postorderPrint(left(i));
    postorderPrint(right(i));
    cout <<  N[i] << "  ";
}

#endif