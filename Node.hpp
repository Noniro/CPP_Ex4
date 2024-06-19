#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

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

#endif