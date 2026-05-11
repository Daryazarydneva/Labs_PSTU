#ifndef TREEVISUALIZER_H
#define TREEVISUALIZER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

// Forward declarations (объявления классов, которые будут определены позже)
class BinaryTree;
class Node;

class TreeVisualizer : public QMainWindow
{
    Q_OBJECT

private:
    BinaryTree* tree;  // Используем указатель вместо объекта
    QGraphicsScene* scene;
    QGraphicsView* view;
    QLineEdit* inputEdit;
    QLabel* inorderLabel;
    QLabel* preorderLabel;
    QLabel* postorderLabel;

    void drawNode(Node* node, int x, int y, int xOffset);
    void updateTree();

private slots:
    void onInsertClicked();
    void onRemoveClicked();
    void onSearchClicked();

public:
    TreeVisualizer(QWidget* parent = nullptr);
    ~TreeVisualizer();  // Добавим деструктор
};

#endif // TREEVISUALIZER_H
