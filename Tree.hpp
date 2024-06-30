#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "Node.hpp"
#include "Complex.hpp"

using namespace std;

template <typename T>
class Tree {
private:
    Node<T>* root;
    size_t k;

public:
    Tree(size_t k = 2) : root(nullptr), k(k) {}

    ~Tree() {
        cout<<"destructor 😈"<<endl;
    auto bfs_start = begin_bfs();
    auto bfs_end = end_bfs();
    auto prev = bfs_start;
    while (bfs_start != bfs_end) {
        prev = bfs_start;
        ++bfs_start;
        prev->children.clear();
    }
}

    void add_root(Node<T>& node) {
        if (root) {
            root->value = node.value;
        } else {
            root = &node;
        }
    }

    Node<T>* get_root() const {
        return root;
    }

    void add_sub_node(Node<T>& parent, Node<T>& child) {
        if (parent.children.size() < k) {
            parent.add_child(&child);
        } else {
            throw runtime_error("Exceeded maximum number of children");
        }
    }

    class dfs_iterator {
    protected:
        Node<T>* current;
        stack<Node<T>*> Nodestack;

    public:
        dfs_iterator(Node<T>* current) : current(current) {
            if (current) {
                Nodestack.push(current);
            }
        }

        dfs_iterator& operator++() {
            if (!Nodestack.empty()) {
                Node<T>* node = Nodestack.top();
                Nodestack.pop();
                current = nullptr;

                for (int i = node->children.size() - 1; i >= 0; --i) {
                    if (node->children[i]) {
                        Nodestack.push(node->children[i]);
                    }
                }

                if (!Nodestack.empty()) {
                    current = Nodestack.top();
                }
            }
            return *this;
        }

        bool operator!=(const dfs_iterator& other) const {
            return current != other.current;
        }

        bool operator==(const dfs_iterator& other) const {
            return current == other.current;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }
    };

    dfs_iterator begin_dfs() {
        return dfs_iterator(root);
    }

    dfs_iterator end_dfs() {
        return dfs_iterator(nullptr);
    }

    // Pre-order iterator
    class pre_order_iterator {
    private:
        stack<Node<T>*> Nodestack;
        Node<T>* current;
        size_t k;

    public:
        pre_order_iterator(Node<T>* root, size_t k) : current(nullptr), k(k) {
            if (root) {
                Nodestack.push(root);
                current = root;
            }
        }

        pre_order_iterator& operator++() {
            if (!Nodestack.empty()) {
                Node<T>* node = Nodestack.top();
                Nodestack.pop();
                if (k != 2) {
                    // Custom DFS logic
                    for (int i = node->children.size() - 1; i >= 0; --i) {
                        if (node->children[i]) {
                            Nodestack.push(node->children[i]);
                        }
                    }
                } else {
                    // Pre-order traversal for k=2
                    for (int i = node->children.size() - 1; i >= 0; --i) {
                        Nodestack.push(node->children[i]);
                    }
                }
                current = Nodestack.empty() ? nullptr : Nodestack.top();
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }

        bool operator!=(const pre_order_iterator& other) const {
            return current != other.current;
        }

        bool operator==(const pre_order_iterator& other) const {
            return current == other.current;
        }
    };

    pre_order_iterator begin_pre_order() {
        return pre_order_iterator(root, this->k);
    }

    pre_order_iterator end_pre_order() {
        return pre_order_iterator(nullptr, this->k);
    }

    // In-order iterator
    class in_order_iterator {
    private:
        stack<Node<T>*> Nodestack;
        Node<T>* current;
        size_t k;

        void push_left(Node<T>* node) {
            while (node) {
                Nodestack.push(node);
                if (k == 2 && !node->children.empty()) {
                    node = node->children[0];
                } else {
                    break;
                }
            }
        }

    public:
        in_order_iterator(Node<T>* root, size_t k = 2) : current(nullptr), k(k) {
            if (k != 2) {
                if (root) {
                    Nodestack.push(root);
                    current = root;
                }
            } else {
                if (root) {
                    push_left(root);
                    if (!Nodestack.empty()) {
                        current = Nodestack.top();
                        Nodestack.pop();
                    }
                }
            }
        }

        in_order_iterator& operator++() {
            if (current && k == 2) {
                if (!current->children.empty() && current->children.size() > 1) {
                    push_left(current->children[1]);
                }
                if (!Nodestack.empty()) {
                    current = Nodestack.top();
                    Nodestack.pop();
                } else {
                    current = nullptr;
                }
            } else {
                if (!Nodestack.empty()) {
                    Node<T>* node = Nodestack.top();
                    Nodestack.pop();
                    for (int i = node->children.size() - 1; i >= 0; --i) {
                        Nodestack.push(node->children[i]);
                    }
                    current = Nodestack.empty() ? nullptr : Nodestack.top();
                } else {
                    current = nullptr;
                }
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }

        bool operator!=(const in_order_iterator& other) const {
            return current != other.current;
        }

        bool operator==(const in_order_iterator& other) const {
            return current == other.current;
        }
    };

    in_order_iterator begin_in_order() {
        return in_order_iterator(root, this->k);
    }

    in_order_iterator end_in_order() {
        return in_order_iterator(nullptr, this->k);
    }


    // Post-order iterator
    class post_order_iterator {
    private:
        stack<Node<T>*> nodeStack;
        stack<bool> visitStack;
        Node<T>* current;
        size_t k;

        void push_left(Node<T>* node) {
            while (node) {
                nodeStack.push(node);
                visitStack.push(false);
                if (k == 2 && !node->children.empty()) {
                    node = node->children[0];
                } else {
                    break;
                }
            }
        }

    public:
        post_order_iterator(Node<T>* root = nullptr, size_t k = 2) : current(nullptr), k(k) {
            if (k != 2) {
                if (root) {
                    nodeStack.push(root);
                    current = root;
                }
            } else {
                if (root) {
                    push_left(root);
                    while (!nodeStack.empty()) {
                        Node<T>* node = nodeStack.top();
                        if (node->children.size() > 1) {
                            push_left(node->children[1]);
                        } else {
                            current = nodeStack.top();
                            nodeStack.pop();
                            visitStack.pop();
                            break;
                        }
                    }
                }
            }
        }

        post_order_iterator& operator++() {
            if (k == 2) {
                while (!nodeStack.empty()) {
                    Node<T>* node = nodeStack.top();
                    if (visitStack.top()) {
                        nodeStack.pop();
                        visitStack.pop();
                        current = node;
                        return *this;
                    } else {
                        visitStack.top() = true;
                        if (node->children.size() > 1) {
                            push_left(node->children[1]);
                        }
                    }
                }
                current = nullptr;
            } else {
                if (!nodeStack.empty()) {
                    Node<T>* node = nodeStack.top();
                    nodeStack.pop();
                    for (int i = node->children.size() - 1; i >= 0; --i) {
                        nodeStack.push(node->children[i]);
                    }
                    current = nodeStack.empty() ? nullptr : nodeStack.top();
                } else {
                    current = nullptr;
                }
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }

        bool operator!=(const post_order_iterator& other) const {
            return current != other.current;
        }

        bool operator==(const post_order_iterator& other) const {
            return current == other.current;
        }
    };

    post_order_iterator begin_post_order() {
        return post_order_iterator(root, k);
    }

    post_order_iterator end_post_order() {
        return post_order_iterator();
    }


    // BFS iterator
    class bfs_iterator {
    private:
        queue<Node<T>*> nodeQueue;

    public:
        bfs_iterator(Node<T>* root) {
            if (root) nodeQueue.push(root);
        }

        bfs_iterator& operator++() {
            if (!nodeQueue.empty()) {
                Node<T>* node = nodeQueue.front();
                nodeQueue.pop();
                for (auto child : node->children) {
                    if (child) nodeQueue.push(child);
                }
            }
            return *this;
        }

        Node<T>& operator*() {
            return *nodeQueue.front();
        }

        Node<T>* operator->() {
            return nodeQueue.front();
        }

        bool operator!=(const bfs_iterator& other) const {
            return !(*this == other);
        }

        bool operator==(const bfs_iterator& other) const {
            return nodeQueue.empty() == other.nodeQueue.empty();
        }
    };

    bfs_iterator begin_bfs() {
        return bfs_iterator(root);
    }

    bfs_iterator end_bfs() {
        return bfs_iterator(nullptr);
    }



    class min_heap_iterator {
    private:
        priority_queue<Node<T>*, vector<Node<T>*>, NodeCompare<T>> nodeHeap;
        Node<T>* current;

        void push_children(Node<T>* node) {
            for (auto child : node->children) {
                nodeHeap.push(child);
            }
        }

    public:
        min_heap_iterator(Node<T>* root = nullptr) : current(nullptr) {
            if (root) {
                nodeHeap.push(root);
                advance();
            }
        }

        void advance() {
            if (!nodeHeap.empty()) {
                current = nodeHeap.top();
                nodeHeap.pop();
                push_children(current);
            } else {
                current = nullptr;
            }
        }

        min_heap_iterator& operator++() {
            advance();
            return *this;
        }

        Node<T>& operator*() const {
            return *current;
        }

        Node<T>* operator->() const {
            return current;
        }

        bool operator!=(const min_heap_iterator& other) const {
            return current != other.current;
        }

        bool operator==(const min_heap_iterator& other) const {
            return current == other.current;
        }
    };

    min_heap_iterator begin_heap() {
        return min_heap_iterator(root);
    }

    min_heap_iterator end_heap() {
        return min_heap_iterator();
    }

};

#endif
