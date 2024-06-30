#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "Complex.hpp"

template <typename T>
class Node {
public:
    T value;
    std::vector<Node*> children;

    Node(T val) : value(val) {}

    void add_child(Node* child) {
        children.push_back(child);
    }
};

//functor for comparing nodes
template <typename T>
struct NodeCompare {
    bool operator()(const Node<T>* lhs, const Node<T>* rhs) const {
        return lhs->value > rhs->value;
    }
};


#endif