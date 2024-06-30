#  K-ary Tree with Iterators and GUI using Qt5

## Description
This project is a K-ary tree implementation with iterators and a GUI using Qt5. The tree is implemented using a vector of pointers to the children of each node. The iterators are implemented using a stack of pointers to the nodes. The GUI is implemented using Qt5 and allows the user display the tree.
also added for fun display of a complex number patterns like Julia and Mandelbrot sets.

## Features 
* K-ary tree implementation: Create trees with any branching factor (k).
* Iterators: Includes six types of iterators for various tree traversal  techniques:
* Depth-First Search (DFS)
* Breadth-First Search (BFS)
* Heap
* Inorder
* Postorder
* Preorder
* Binary Tree DFS: For k=2, performs DFS traversal.
* GUI: Display the tree using a GUI implemented using Qt5.
* Complex Numbers: Support for complex numbers to create and display patterns like the Mandelbrot set.

## Usage

To build the project use this simple commands:
```bash
make tree 
make tree1 # integer tree.
make tree2 # string tree.
make tree3 # complex numbers tree.
make complex # exmples of the mandelbrot set.
```
build your own tree and display it using the GUI:
```cpp
 Node<std::string> root_node("BB");
        Node<std::string> n2("gantz");
        Node<std::string> n3("lapid");
        Node<std::string> n4("noam");
        Node<std::string> n5("yosi");
        Node<std::string> n6("avner");
        Node<std::string> n7("iztik");
        Tree<std::string> tree(4); //default 'tree()' for binary tree.
        tree.add_root(root_node);
        tree.add_sub_node(*tree.get_root(), n2);
        tree.add_sub_node(*tree.get_root(), n3);
        tree.add_sub_node(*tree.get_root(), n4);
        tree.add_sub_node(*tree.get_root(), n5);
        tree.add_sub_node(n2, n6);
        tree.add_sub_node(n2, n7);
```
gui display:
```cpp
    QApplication a(argc, argv);
    QMainWindow w;
    TreeWidget<std::string>* treeWidget = new TreeWidget<std::string>(tree);
    window.setCentralWidget(treeWidget);
    window.resize(800, 600);
    window.show();
    return app.exec();
```

## GUI prints 
tree2: 

![Screenshot_36](https://github.com/Noniro/CPP_Ex4/assets/118755760/bb0c17cf-387c-463c-9632-e67e03b57cd5)


## classes
* Node: Represents a node in the tree.
* Tree: Represents the tree - includes the root node and the tree iterators classes. tree default is binary tree.
* iterator classes:
- dfs_iterator: Depth-First Search iterator.
- bfs_iterator: Breadth-First Search iterator.
- min_heap_iterator: well, min heap iterator. ¯\_(ツ)_/¯
- in_order_iterator.
- post_order_iterator.
- pre_order_iterator.

* TreeWidget: A Qt5 widget that displays the tree.

## Tests: 
to run tests: 
```bash
make test
```



