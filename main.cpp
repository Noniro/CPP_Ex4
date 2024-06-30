#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include "Tree.hpp"  
#include "Node.hpp"  
#include <cmath>
#include "Complex.hpp"
#include "TreeWidget.hpp"


int main(int argc, char* argv[]) {
    cout<<"just some tests:"<<endl;
    Tree<int> tree(2);
    Node<int> root(1);
    tree.add_root(root);

    Node<int> child1(2);
    Node<int> child2(3);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    Node<int> child3(4);
    Node<int> child4(5);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    std::cout<<"pre_order"<<std::endl;
    for(auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it){
        std::cout << it->value << std::endl;
    }
    std::cout<<"post_order"<<std::endl;
    for(auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it){
        std::cout << it->value << std::endl;
    }
    std::cout<<"in_order"<<std::endl;
    for(auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it){
        std::cout << it->value << std::endl;
    }
    std::cout<<"DFS"<<std::endl;
    for(auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it){
        std::cout << it->value << std::endl;
    }
    std::cout<<"BFS"<<std::endl;
    for(auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it){
        std::cout << it->value << std::endl;
    }
    std::cout<<"MinHeap"<<std::endl;
    for(auto it = tree.begin_heap(); it != tree.end_heap(); ++it){
        std::cout << it->value << std::endl;
    }

    QApplication app(argc, argv);
    QMainWindow window;
    
    if(argc <= 1 || std::string(argv[1]) == "tree"){  // a default binary tree (k = 2)
        Node<int> n2(2);
        Node<int> n3(3);
        Node<int> n4(4);
        Node<int> root_node(1);
        Node<int> n5(5);
        Tree<int> tree;
        tree.add_root(root_node);
        tree.add_sub_node(*tree.get_root(), n2);
        tree.add_sub_node(*tree.get_root(), n3);
        tree.add_sub_node(n2, n4);
        tree.add_sub_node(n2, n5);

        TreeWidget<int>* treeWidget = new TreeWidget<int>(tree);
        window.setCentralWidget(treeWidget);
        window.resize(800, 600);
        window.show();

        return app.exec();

    } else if(argc > 1 && std::string(argv[1]) == "tree1"){  // a ternary tree (k = 3)
        Tree<int> tree(3);
        Node<int> root_node(1);
        tree.add_root(root_node);
        Node<int> n2(2);
        Node<int> n3(3);
        Node<int> n4(4);
        Node<int> n5(5);
        Node<int> n6(6);
        Node<int> n7(7);
        tree.add_sub_node(*tree.get_root(), n2);
        tree.add_sub_node(*tree.get_root(), n3);
        tree.add_sub_node(*tree.get_root(), n4);
        tree.add_sub_node(n2, n5);
        tree.add_sub_node(n2, n6);
        tree.add_sub_node(n2, n7);

        TreeWidget<int>* treeWidget = new TreeWidget<int>(tree);
        window.setCentralWidget(treeWidget);
        window.resize(800, 600);
        window.show();

        return app.exec();

    }else if(argc > 1 && std::string(argv[1]) == "tree2"){  // a quaternary tree (k = 4) with strings
        Node<std::string> root_node("BB");
        Node<std::string> n2("gantz");
        Node<std::string> n3("lapid");
        Node<std::string> n4("noam");
        Node<std::string> n5("yosi");
        Node<std::string> n6("avner");
        Node<std::string> n7("iztik");
        Tree<std::string> tree(4);
        tree.add_root(root_node);
        tree.add_sub_node(*tree.get_root(), n2);
        tree.add_sub_node(*tree.get_root(), n3);
        tree.add_sub_node(*tree.get_root(), n4);
        tree.add_sub_node(*tree.get_root(), n5);
        tree.add_sub_node(n2, n6);
        tree.add_sub_node(n2, n7);

        TreeWidget<std::string>* treeWidget = new TreeWidget<std::string>(tree);
        window.setCentralWidget(treeWidget);
        window.resize(800, 600);
        window.show();

        return app.exec();
        
    }else if(argc > 1 && std::string(argv[1]) == "tree3"){  // a quaternary tree (k = 4) with complex numbers
        Node<Complex> root_node(Complex(1, 2));
        Node<Complex> n2(Complex(3, 4));
        Node<Complex> n3(Complex(5, 6));
        Node<Complex> n4(Complex(7, 8));
        Node<Complex> n5(Complex(9, 10));
        Node<Complex> n6(Complex(11, 12));
        Node<Complex> n7(Complex(13, 14));
        Tree<Complex> tree(4);
        tree.add_root(root_node);
        tree.add_sub_node(*tree.get_root(), n2);
        tree.add_sub_node(*tree.get_root(), n3);
        tree.add_sub_node(*tree.get_root(), n4);
        tree.add_sub_node(*tree.get_root(), n5);
        tree.add_sub_node(n2, n6);
        tree.add_sub_node(n2, n7);

        TreeWidget<Complex>* treeWidget = new TreeWidget<Complex>(tree);
        window.setCentralWidget(treeWidget);
        window.resize(800, 600);
        window.show();

        return app.exec();

    }else if(argc > 1 && std::string(argv[1]) == "complex"){
        FractalWidget* fractalWidget = new FractalWidget();
        window.setCentralWidget(fractalWidget);
        window.resize(800, 800);
        window.show();

        return app.exec();
    } else {
        std::cerr << "Usage: " << argv[0] << " [tree1|tree2|tree3|complex]" << std::endl;
        return 1;
    }

    return 0;
}

// #include <QApplication>
// #include <QGraphicsScene>
// #include <QGraphicsView>
// #include <QPointF>
// #include <QLineF>
// #include <cmath>

// class RecursiveTree : public QGraphicsView {
// public:
//     RecursiveTree(QWidget *parent = nullptr) : QGraphicsView(parent) {
//         setScene(new QGraphicsScene(this));
//         setRenderHint(QPainter::Antialiasing);

//         drawTree(8, 200, QPointF(250, 400), -90, 20);
        
//         setFixedSize(500, 500);
//     }

//     void drawTree(int depth, qreal length, const QPointF &pos, qreal angle, qreal angleDelta) {
//         if (depth == 0)
//             return;

//         qreal x2 = pos.x() + length * cos(angle * M_PI / 180.0);
//         qreal y2 = pos.y() + length * sin(angle * M_PI / 180.0);
//         QPointF end(x2, y2);

//         scene()->addLine(QLineF(pos, end));

//         drawTree(depth - 1, length * 0.7, end, angle - angleDelta, angleDelta);
//         drawTree(depth - 1, length * 0.7, end, angle + angleDelta, angleDelta);
//     }
// };

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);

//     RecursiveTree tree;
//     tree.show();

//     return app.exec();
// }



