#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Tree.hpp"
#include "Node.hpp"
#include <iostream>
#include "Complex.hpp"

// Define a helper function to compare trees (for testing purposes)
template <typename T>
bool trees_are_equal(Node<T>* node1, Node<T>* node2) {
    if (!node1 && !node2) return true;
    if ((node1 && !node2) || (!node1 && node2)) return false;
    if (node1->value != node2->value) return false;
    if (node1->children.size() != node2->children.size()) return false;
    for (size_t i = 0; i < node1->children.size(); ++i) {
        if (!trees_are_equal(node1->children[i], node2->children[i])) return false;
    }
    return true;
}

TEST_CASE("Tree - add_root and get_root") {
    Node<int> root(1);
    Tree<int> tree(2);
    tree.add_root(root);

    REQUIRE(tree.get_root() != nullptr);
    CHECK(tree.get_root()->value == 1);
}

TEST_CASE("Tree - add_sub_node") {
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Tree<int> tree(2);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    REQUIRE(tree.get_root()->children.size() == 2);
    CHECK(tree.get_root()->children[0]->value == 2);
    CHECK(tree.get_root()->children[1]->value == 3);

    Node<int> child3(4);
    CHECK_THROWS_AS(tree.add_sub_node(root, child3), std::runtime_error);
}

TEST_CASE("Tree - Iterators") {
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Tree<int> tree(2);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    SUBCASE("DFS"){
    auto it = tree.begin_dfs();
    CHECK(it->value == 1);
    ++it;
    CHECK(it->value == 2);
    ++it;
    CHECK(it->value == 4);
    ++it;
    CHECK(it->value == 5);
    ++it;
    CHECK(it->value == 3);
    ++it;
    CHECK(it == tree.end_dfs());
    }


SUBCASE("Tree - BFS iterator") {
    auto it = tree.begin_dfs();
    CHECK(it->value == 1);
    ++it;
    CHECK(it->value == 2);
    ++it;
    CHECK(it->value == 4);
    ++it;
    CHECK(it->value == 5);
    ++it;
    CHECK(it->value == 3);
    ++it;
    CHECK(it == tree.end_dfs());
}

SUBCASE("Tree - Pre-order iterator") {
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Tree<int> tree(2);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    

    auto it = tree.begin_pre_order();
    std::cout << it->value << std::endl;
    CHECK(it->value == 1);
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 2);
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 4);
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 5);
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 3);
    ++it;
    CHECK(it == tree.end_pre_order());
}

SUBCASE("Tree - In-order iterator") {
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Tree<int> tree(2);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    auto it = tree.begin_in_order();
    std::cout << it->value << std::endl;
    CHECK(it->value == 2); // Assuming leftmost child is visited first
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 1);
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 3);
    ++it;
    // std::cout << it->value << std::endl;
    CHECK(it == tree.end_in_order());
}

SUBCASE("Tree - Post-order iterator") {

    std::cout<<"post order check"<<std::endl;
    auto it = tree.begin_post_order();
    std::cout << it->value << std::endl;
    CHECK(it->value == 4);
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 5);
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 2);
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 3);
    ++it;
    std::cout << it->value << std::endl;
    CHECK(it->value == 1);
    ++it;
    CHECK(it == tree.end_post_order());

}
}

TEST_CASE("Tree is non-binary - i.e DFS"){
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Node<int> child5(6);
    Tree<int> tree(3);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(root, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child4, child5);

SUBCASE("inorder"){
    cout<<"inorder"<<endl;
    auto it = tree.begin_in_order();
    CHECK(it->value == 1);
    ++it;
    CHECK(it->value == 2);
    ++it;
    CHECK(it->value == 5);
    ++it;
    CHECK(it->value == 6);
    ++it;
    CHECK(it->value == 3);
    ++it;
    CHECK(it->value == 4);
    ++it;
    CHECK(it == tree.end_in_order());
}

    SUBCASE("postorder"){
    cout<<"postorder"<<endl;
    auto it = tree.begin_post_order(); 
    CHECK(it->value == 1);
    ++it;
    CHECK(it->value == 2);
    ++it;
    CHECK(it->value == 5);
    ++it;
    CHECK(it->value == 6);
    ++it;
    CHECK(it->value == 3);
    ++it;
    CHECK(it->value == 4);
    ++it;
    CHECK(it == tree.end_post_order());

}

    SUBCASE("preorder"){
    cout<<"preorder"<<endl;
    auto it = tree.begin_pre_order();
    CHECK(it->value == 1);
    ++it;
    CHECK(it->value == 2);
    ++it;
    CHECK(it->value == 5);
    ++it;
    CHECK(it->value == 6);
    ++it;
    CHECK(it->value == 3);
    ++it;
    CHECK(it->value == 4);
    ++it;
    CHECK(it == tree.end_pre_order());
}

}

TEST_CASE("Tree - copy constructor") {
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Tree<int> tree(2);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    Tree<int> tree_copy(tree);

    CHECK(trees_are_equal(tree.get_root(), tree_copy.get_root()));
}

TEST_CASE("Tree heap iterator") {
    Node<int> root(1);
    Node<int> child1(2);
    Tree<int> tree(2);
    Node<int> child2(3);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    auto it = tree.begin_heap();
    cout<<it->value<<endl;
    CHECK(it->value == 1);
    ++it;
    cout<<it->value<<endl;
    CHECK(it->value == 2);
    ++it;
    cout<<it->value<<endl;
    CHECK(it->value == 3);
    ++it;
    CHECK(it == tree.end_heap());
}

TEST_CASE("min heap with complex numbers"){
    Node<Complex> root(Complex(0, 0));
    Node<Complex> child1(Complex(4, 4));
    Node<Complex> child2(Complex(3, 3));
    Node<Complex> child3(Complex(2, 2));
    Node<Complex> child4(Complex(1, 1));
    Node<Complex> child5(Complex(5, 5));
    Node<Complex> child6(Complex(-10, -3));
    Node<Complex> child7(Complex(-2.5, -50.5));
    Node<Complex> child8(Complex(-3.5, -3));
    Tree<Complex> tree(4);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(root, child3);
    tree.add_sub_node(root, child4);
    tree.add_sub_node(child1, child5);
    tree.add_sub_node(child1, child6);
    tree.add_sub_node(child2, child7);
    tree.add_sub_node(child2, child8);

    auto it = tree.begin_heap();
    CHECK(it->value == Complex(0, 0));
    ++it;
    CHECK(it->value == Complex(1, 1));
    ++it;
    CHECK(it->value == Complex(2, 2));
    ++it;
    CHECK(it->value == Complex(3, 3));
    ++it;
    CHECK(it->value == Complex(-3.5, -3));
    ++it;
    CHECK(it->value == Complex(4, 4));
    ++it;
    CHECK(it->value == Complex(5, 5));
    ++it;
    CHECK(it->value == Complex(-10, -3));
    ++it;
    CHECK(it->value == Complex(-2.5, -50.5));
    ++it;
    CHECK(it == tree.end_heap());

}
 
TEST_CASE("Iterators"){
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Node<int> child5(6);
    Node<int> child6(7);
    Node<int> child7(8);
    Tree<int> tree(2);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child2, child5);
    tree.add_sub_node(child2, child6);
    tree.add_sub_node(child5, child7);
    //        1
    //      /   \ 
    //     2     3
    //    / \   / \     
    //   4   5 6   7
    //        /
    //       8
    int pre_order[] = {1, 2, 4, 5, 3, 6, 8, 7};
    int post_order[] = {4, 5, 2, 8, 6, 7, 3, 1};
    int in_order[] = {4, 2, 5, 1, 8, 6, 3, 7};
    int dfs[] = {1, 2, 4, 5, 3, 6, 8, 7};
    int bfs[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int heap[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int i = 0;
    SUBCASE("preorder"){
    for(auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it){
        CHECK(it->value == pre_order[i]);
        i++;
    }
    }
    SUBCASE("postorder"){
    i = 0;
    for(auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it){
        CHECK(it->value == post_order[i]);
        i++;
    }
    }
    SUBCASE("inorder"){
    i = 0;
    for(auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it){
        CHECK(it->value == in_order[i]);
        i++;
    }
    }
    SUBCASE("DFS"){
    i = 0;
    for(auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it){
        CHECK(it->value == dfs[i]);
        i++;
    }
    }
    SUBCASE("BFS"){
    i = 0;
    for(auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it){
        CHECK(it->value == bfs[i]);
        i++;
    }
    }
    SUBCASE("heap"){
    i = 0;
    for(auto it = tree.begin_heap(); it != tree.end_heap(); ++it){
        CHECK(it->value == heap[i]);
        i++;
    }
    }

}

TEST_CASE("empty tree"){
    Tree<int> tree(2);
    CHECK(tree.get_root() == nullptr);
    CHECK(tree.begin_pre_order() == tree.end_pre_order());
    CHECK(tree.begin_post_order() == tree.end_post_order());
    CHECK(tree.begin_in_order() == tree.end_in_order());
    CHECK(tree.begin_dfs() == tree.end_dfs());
    CHECK(tree.begin_bfs() == tree.end_bfs());
    CHECK(tree.begin_heap() == tree.end_heap());
}

