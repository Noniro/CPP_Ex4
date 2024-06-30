#ifndef TREEWIDGET_HPP
#define TREEWIDGET_HPP

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include "Tree.hpp"
#include "Node.hpp"
#include <cmath>
#include <QString>
#include <QFont>
#include <QFontMetrics>
#include <QPointF>
#include <QLineF>

template <typename T>
class TreeWidget : public QGraphicsView {
public:
    TreeWidget(const Tree<T>& tree, QWidget* parent = nullptr);
    void display_tree(Node<T>* node, QGraphicsScene* scene, int x, int y, int dx);

private:
    std::string to_string(const T& value);
};

class FractalWidget : public QGraphicsView {
public:
    FractalWidget(QWidget* parent = nullptr);
    void drawMandelbrot(int width = 800, int height = 800, int maxIter = 1000);

private:
    QGraphicsScene* scene;
};

#endif // TREEWIDGET_HPP
