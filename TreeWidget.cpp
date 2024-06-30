#include "TreeWidget.hpp"
#include "Complex.hpp"

template class TreeWidget<int>;
template class TreeWidget<std::string>;
template class TreeWidget<Complex>;

template <typename T>
TreeWidget<T>::TreeWidget(const Tree<T>& tree, QWidget* parent) : QGraphicsView(parent) {
    QGraphicsScene* scene = new QGraphicsScene(this);
    setScene(scene);
    display_tree(tree.get_root(), scene, width() / 2, 0, 80);
}

template <typename T>
void TreeWidget<T>::display_tree(Node<T>* node, QGraphicsScene* scene, int x, int y, int dx) {
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
    int textWidth = fm.horizontalAdvance(nodeValue);
    while (textWidth > 2 * radius) {
        font.setPointSize(font.pointSize() - 1);
        text->setFont(font);
        fm = QFontMetrics(font);
        textWidth = fm.horizontalAdvance(nodeValue);
    }
    text->setPos(x + radius - textWidth / 2, y + radius - fm.height() / 2);
    text->setZValue(1);  // Set the Z-value of the text to be higher than the ellipse
    scene->addItem(text);

    int child_y = y + 100;
    int new_dx = std::max(50, dx - 5); // Decrease the horizontal spacing between nodes
    for (size_t i = 0; i < node->children.size(); ++i) {
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

template <typename T>
std::string TreeWidget<T>::to_string(const T& value) {
    if constexpr (std::is_same<T, std::string>::value) {
        return value;
    } else if constexpr (std::is_same<T, Complex>::value) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2); // Set fixed-point notation and precision
        oss << "(" << value.real << ", " << value.imag << "i)";
        return oss.str();
    } else {
        return std::to_string(value);
    }
}

FractalWidget::FractalWidget(QWidget* parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    drawMandelbrot();
}

void FractalWidget::drawMandelbrot(int width, int height, int maxIter) {
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

