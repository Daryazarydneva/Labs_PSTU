#include "treevisualizer.h"
#include "binarytree.h"  // Теперь подключаем после forward declaration
#include "node.h"
#include <QMessageBox>
#include <sstream>

TreeVisualizer::TreeVisualizer(QWidget* parent) : QMainWindow(parent)
{
    // Создаём дерево в куче
    tree = new BinaryTree();

    // Создаём центральный виджет
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    // Создаём сцену для рисования
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, 900, 600);
    view->setBackgroundBrush(Qt::white);

    // Создаём элементы управления
    inputEdit = new QLineEdit(this);
    inputEdit->setPlaceholderText("Введите число...");

    QPushButton* insertBtn = new QPushButton("Вставить", this);
    QPushButton* removeBtn = new QPushButton("Удалить", this);
    QPushButton* searchBtn = new QPushButton("Поиск", this);

    // Метки для отображения обходов
    inorderLabel = new QLabel("Inorder: ", this);
    preorderLabel = new QLabel("Preorder: ", this);
    postorderLabel = new QLabel("Postorder: ", this);

    // Настраиваем цвета кнопок
    insertBtn->setStyleSheet("background-color: #4CAF50; color: white; font-size: 14px; padding: 8px;");
    removeBtn->setStyleSheet("background-color: #f44336; color: white; font-size: 14px; padding: 8px;");
    searchBtn->setStyleSheet("background-color: #2196F3; color: white; font-size: 14px; padding: 8px;");
    inputEdit->setStyleSheet("font-size: 14px; padding: 8px;");

    // Подключаем сигналы
    connect(insertBtn, &QPushButton::clicked, this, &TreeVisualizer::onInsertClicked);
    connect(removeBtn, &QPushButton::clicked, this, &TreeVisualizer::onRemoveClicked);
    connect(searchBtn, &QPushButton::clicked, this, &TreeVisualizer::onSearchClicked);

    // Располагаем элементы в панели управления
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(inputEdit);
    buttonLayout->addWidget(insertBtn);
    buttonLayout->addWidget(removeBtn);
    buttonLayout->addWidget(searchBtn);

    // Располагаем метки обходов
    QVBoxLayout* labelsLayout = new QVBoxLayout;
    labelsLayout->addWidget(inorderLabel);
    labelsLayout->addWidget(preorderLabel);
    labelsLayout->addWidget(postorderLabel);

    // Главный вертикальный layout
    QVBoxLayout* mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(view);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(labelsLayout);

    // Настройки окна
    setWindowTitle("Binary Search Tree Visualizer");
    resize(1000, 700);
}

TreeVisualizer::~TreeVisualizer()
{
    delete tree;  // Очищаем память
}

void TreeVisualizer::drawNode(Node* node, int x, int y, int xOffset)
{
    if (!node) return;

    // Рисуем узел (круг)
    QBrush brush(Qt::lightGray);
    QPen pen(Qt::black);
    pen.setWidth(2);
    scene->addEllipse(x, y, 40, 40, pen, brush);

    // Рисуем текст (ключ)
    QGraphicsTextItem* text = scene->addText(QString::number(node->getKey()));
    text->setPos(x + 12, y + 10);
    text->setFont(QFont("Arial", 12, QFont::Bold));

    // Рисуем линии к детям
    if (node->getLeft()) {
        int childX = x - xOffset;
        int childY = y + 70;
        scene->addLine(x + 20, y + 40, childX + 20, childY, QPen(Qt::red, 2));
        drawNode(node->getLeft(), childX, childY, xOffset / 2);
    }
    if (node->getRight()) {
        int childX = x + xOffset;
        int childY = y + 70;
        scene->addLine(x + 20, y + 40, childX + 20, childY, QPen(Qt::blue, 2));
        drawNode(node->getRight(), childX, childY, xOffset / 2);
    }
}

void TreeVisualizer::updateTree()
{
    scene->clear();

    if (tree->getRoot()) {
        drawNode(tree->getRoot(), 460, 30, 200);  // tree-> вместо tree.
    }

    // Обновляем отображение обходов
    std::vector<int> inorderVec = tree->inorder();
    std::vector<int> preorderVec = tree->preorder();
    std::vector<int> postorderVec = tree->postorder();

    std::stringstream inorderSS, preorderSS, postorderSS;
    for (int v : inorderVec) inorderSS << v << " ";
    for (int v : preorderVec) preorderSS << v << " ";
    for (int v : postorderVec) postorderSS << v << " ";

    inorderLabel->setText(QString::fromStdString("Inorder (Л-К-П): " + inorderSS.str()));
    preorderLabel->setText(QString::fromStdString("Preorder (К-Л-П): " + preorderSS.str()));
    postorderLabel->setText(QString::fromStdString("Postorder (Л-П-К): " + postorderSS.str()));
}

void TreeVisualizer::onInsertClicked()
{
    bool ok;
    int key = inputEdit->text().toInt(&ok);
    if (ok) {
        tree->insert(key);  // tree-> вместо tree.
        updateTree();
        inputEdit->clear();
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите целое число!");
    }
}

void TreeVisualizer::onRemoveClicked()
{
    bool ok;
    int key = inputEdit->text().toInt(&ok);
    if (ok) {
        if (tree->search(key)) {  // tree-> вместо tree.
            tree->remove(key);     // tree-> вместо tree.
            updateTree();
        } else {
            QMessageBox::information(this, "Результат", "Узел " + QString::number(key) + " не найден");
        }
        inputEdit->clear();
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите целое число!");
    }
}

void TreeVisualizer::onSearchClicked()
{
    bool ok;
    int key = inputEdit->text().toInt(&ok);
    if (ok) {
        if (tree->search(key)) {  // tree-> вместо tree.
            QMessageBox::information(this, "Результат", "Узел " + QString::number(key) + " найден в дереве");
        } else {
            QMessageBox::information(this, "Результат", "Узел " + QString::number(key) + " не найден");
        }
        inputEdit->clear();
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите целое число!");
    }
}
