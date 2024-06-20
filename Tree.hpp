#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "Node.hpp"

template <typename T>
class Tree {
private:
    Node<T>* root;
    int k;

public:
    Tree(int k = 2) : root(nullptr), k(k) {}

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
            throw std::runtime_error("Exceeded maximum number of children");
        }
    }

    class dfs_iterator{ 
    protected:
        Node<T>* current;
        std::stack<Node<T>*> stack;

    public:
        dfs_iterator(Node<T>* current) : current(current) {
            if (current) {
                stack.push(current);
            }
        }

        virtual dfs_iterator& operator++() {
            std::cout<<"dfs_iterator++\n";
            if (!stack.empty()) {
                Node<T>* node = stack.top();
                stack.pop();
                current = nullptr;  // Clear current

                for (int i = node->children.size() - 1; i >= 0; --i) {
                    if (node->children[i]) {
                        stack.push(node->children[i]);
                    }
                }

                if (!stack.empty()) {
                    current = stack.top();
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
    class pre_order_iterator : public dfs_iterator{
    private:
        std::stack<Node<T>*> stack;

    public:
        pre_order_iterator(Node<T>* root) : dfs_iterator(root){
            if (root) stack.push(root);
        }

       pre_order_iterator& operator++() override {
            if (!this->stack.empty()) {
                Node<T>* node = this->stack.top();
                this->stack.pop();

                for (int i = node->children.size() - 1; i >= 0; --i) {
                    if (node->children[i]) {
                        this->stack.push(node->children[i]);
                    }
                }

                if (!this->stack.empty()) {
                    this->current = this->stack.top();
                } else {
                    this->current = nullptr;
                }
            }
            return *this;
        }


        Node<T>& operator*() const {
            return *stack.top();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

        bool operator!=(const pre_order_iterator& other) const {
            return !(*this == other);
        }

        bool operator==(const pre_order_iterator& other) const {
            return stack.empty() == other.stack.empty();
        }
    };

    dfs_iterator begin_pre_order() {
        if(k != 2){
            std::cout<<"printing k!=2\n";
            return dfs_iterator(root);
        }
        std::cout<<"printing pre order k=2\n";
        return pre_order_iterator(root);
    }

    dfs_iterator end_pre_order() {
        if(k != 2){
            return dfs_iterator(nullptr);
        }
        return pre_order_iterator(nullptr);
    }


    class in_order_iterator : public dfs_iterator{
    private:
        std::stack<Node<T>*> stack;
        Node<T>* current;

        void push_left(Node<T>* node) {
            while (node) {
                stack.push(node);
                if (!node->children.empty()) {
                    node = node->children[0];
                } else {
                    node = nullptr;
                }
            }
        }

    public:
        in_order_iterator(Node<T>* root) : dfs_iterator(root) {
            push_left(root);
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
        }

        in_order_iterator& operator++() override {
            if (this->current) {
                if (this->current->children.size() > 1) {
                    push_left(this->current->children[1]);  // push the right child and its left descendants
                }
                if (!this->stack.empty()) {
                    this->current = this->stack.top();
                    this->stack.pop();
                } else {
                    this->current = nullptr;
                }
            }
            return *this;
        }
            

        T& operator*() {
            return current->value;
        }

        T* operator->() {
            return &(current->value);
        }

        bool operator!=(const in_order_iterator& other) const {
            return current != other.current;
        }
        
        bool operator==(const in_order_iterator& other) const {
            return current == other.current;
        }
    };

    dfs_iterator begin_in_order() {
        if(k!=2){
            std::cout<<"printing in order k!=2\n";
            return dfs_iterator(root);
        }
        std::cout<<"printing in order k=2\n";
        return in_order_iterator(root);
    }

    dfs_iterator end_in_order() {
        if(k != 2){
            return dfs_iterator(nullptr);
        }
        return in_order_iterator(nullptr);
    }

    class post_order_iterator : public dfs_iterator{
    private:
        std::stack<Node<T>*> stack;
        Node<T>* current;

        void push_left(Node<T>* node) {
            while (node) {
                stack.push(node);
                if (!node->children.empty()) {
                    node = node->children[0];
                } else {
                    node = nullptr;
                }
            }
        }

    public:

        post_order_iterator(Node<T>* root) : dfs_iterator(root) {
            push_left(root);
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
        }

        post_order_iterator& operator++() override {
            if (current) {
                if (!current->children.empty()) {
                    push_left(current->children[1]);
                }
                if (!stack.empty()) {
                    current = stack.top();
                    stack.pop();
                } else {
                    current = nullptr;
                }
            }
            return *this;
        }

        T& operator*() {
            return current->value;
        }

        T* operator->() {
            return &(current->value);
        }

        bool operator!=(const post_order_iterator& other) const {
            return current != other.current;
        }
        bool operator==(const post_order_iterator& other) const {
            return current == other.current;
        }
    };

    dfs_iterator begin_post_order() {
        if(k !=2){
            std::cout<<"printing post order k!=2\n";
            return dfs_iterator(root);
        }
        std::cout<<"printing post order k=2\n";
        return post_order_iterator(root);
    }

    dfs_iterator end_post_order() {
        if(k !=2){
            return dfs_iterator(nullptr);
        }

        return post_order_iterator(nullptr);
    }

    class bfs_iterator : public dfs_iterator{
    private:
        std::queue<Node<T>*> queue;

    public:

        bfs_iterator(Node<T>* root) : dfs_iterator(root) {
            if (root) queue.push(root);
        }

        bfs_iterator& operator++() override {
            if (!queue.empty()) {
                Node<T>* node = queue.front();
                queue.pop();
                for (auto child : node->children) {
                    if (child) queue.push(child);
                }
            }
            return *this;
        }

        Node<T>& operator*() {
            return *queue.front();
        }

        Node<T>* operator->() {
            return queue.front();
        }

        bool operator!=(const bfs_iterator& other) const {
            return !(*this == other);
        }

        bool operator==(const bfs_iterator& other) const {
            return queue.empty() == other.queue.empty();
        }
    };


};

#endif
