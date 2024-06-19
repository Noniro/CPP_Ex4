#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include "Tree.hpp"  
#include "Node.hpp"  
#include <cmath>
#include "Complex.hpp"

template <typename T>
class TreeWidget : public QGraphicsView {
public:
    TreeWidget(const Tree<T>& tree, QWidget* parent = nullptr) : QGraphicsView(parent) {
        QGraphicsScene* scene = new QGraphicsScene(this);
        setScene(scene);
        display_tree(tree.get_root(), scene, width() / 2, 0, 80);
    }

    void display_tree(Node<T>* node, QGraphicsScene* scene, int x, int y, int dx) {
        if (!node) return;
        int radius = 30;  // Half of the circle's diameter
        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(x, y, 2*radius, 2*radius);
        circle->setBrush(Qt::magenta);
        circle->setPen(QPen(Qt::black));
        scene->addItem(circle);

        QString nodeValue = QString::fromStdString(to_string(node->value));
        QGraphicsTextItem* text = new QGraphicsTextItem(nodeValue);
        QFont font = text->font();
        QFontMetrics fm(font);
        int textWidth = fm.width(nodeValue);
        while (textWidth > 2 * radius) {
            font.setPointSize(font.pointSize() - 1);
            text->setFont(font);
            fm = QFontMetrics(font);
            textWidth = fm.width(nodeValue);
        }
        text->setPos(x + radius - textWidth / 2, y + radius - fm.height() / 2);
        text->setZValue(1);  // Set the Z-value of the text to be higher than the ellipse
        scene->addItem(text);

        int child_y = y + 100;
        int new_dx = std::max(50, dx - 5); // Decrease the horizontal spacing between nodes
        for (int i = 0; i < node->children.size(); ++i) {
            if (node->children[i]) {
                int child_x = x + (i - node->children.size() / 2) * new_dx;

                QPointF circle_center = circle->boundingRect().center();
                QPointF child_circle_center(child_x + radius, child_y + radius);
                QLineF line(circle_center, child_circle_center);

                // Adjust the line's start and end points
                double angle = line.angle() * M_PI / 180;  // Convert to radians
                line.setP1(circle_center + QPointF(radius * cos(angle), -radius * sin(angle)));
                line.setP2(child_circle_center - QPointF(radius * cos(angle), -radius * sin(angle)));

                scene->addLine(line, QPen(Qt::black));
                display_tree(node->children[i], scene, child_x, child_y, new_dx);
            }
        }
    }

private:
    std::string to_string(const T& value) {
        if constexpr (std::is_same<T, std::string>::value) {
            return value;
        } else {
            return std::to_string(value);
        }
    }
};

class FractalWidget : public QGraphicsView {
public:
    FractalWidget(QWidget* parent = nullptr) : QGraphicsView(parent) {
        scene = new QGraphicsScene(this);
        setScene(scene);
        drawMandelbrot();
    }

    void drawMandelbrot(int width = 800, int height = 800, int maxIter = 1000) {
        QImage image(width, height, QImage::Format_RGB32);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double zx = 1.5 * (x - width / 2) / (0.5 * width);
                double zy = (y - height / 2) / (0.5 * height);
                Complex z(0, 0);
                Complex c(zx, zy);
                int iter;
                for (iter = 0; iter < maxIter; ++iter) {
                    if (z.magnitudeSquared() > 4) break;
                    z = z * z + c;
                }
                int color = (iter == maxIter) ? 0 : (255 * iter) / maxIter;
                image.setPixel(x, y, qRgb(color, color, color));
            }
        }
        scene->addPixmap(QPixmap::fromImage(image));
        setSceneRect(0, 0, width, height);
    }

private:
    QGraphicsScene* scene;
};



int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QMainWindow window;
    

    if(argc > 1 && std::string(argv[1]) == "tree1"){  // a default binary tree (k = 2)
        Tree<int> tree;
        Node<int> root_node(1);
        tree.add_root(root_node);
        Node<int> n2(2);
        Node<int> n3(3);
        Node<int> n4(4);
        Node<int> n5(5);
        tree.add_sub_node(*tree.get_root(), n2);
        tree.add_sub_node(*tree.get_root(), n3);
        tree.add_sub_node(n2, n4);
        tree.add_sub_node(n2, n5);

        TreeWidget<int>* treeWidget = new TreeWidget<int>(tree);
        window.setCentralWidget(treeWidget);
        window.resize(800, 600);
        window.show();

        return app.exec();

    } else if(argc > 1 && std::string(argv[1]) == "tree2"){  // a ternary tree (k = 3)
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

    }else if(argc > 1 && std::string(argv[1]) == "tree3"){  // a quaternary tree (k = 4) with strings
        Tree<std::string> tree(4);
        Node<std::string> root_node("BB");
        tree.add_root(root_node);
        Node<std::string> n2("gantz");
        Node<std::string> n3("lapid");
        Node<std::string> n4("noam");
        Node<std::string> n5("yosi");
        Node<std::string> n6("avner");
        Node<std::string> n7("iztik");
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
        
    } else if(argc > 1 && std::string(argv[1]) == "complex"){
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



