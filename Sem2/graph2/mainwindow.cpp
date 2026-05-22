#include "mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QBrush>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)) {

    setWindowTitle("Теория графов - Лабораторная работа №2 (Вариант 9)");
    setMinimumSize(900, 700);

    // Центральный виджет
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // ========== ЛЕВАЯ ПАНЕЛЬ (управление) ==========
    QWidget* controlPanel = new QWidget();
    QVBoxLayout* controlLayout = new QVBoxLayout(controlPanel);

    // Группа редактирования графа
    QPushButton* btnAddVertex = new QPushButton("Добавить вершину");
    QPushButton* btnRemoveVertex = new QPushButton("Удалить вершину");
    QPushButton* btnAddEdge = new QPushButton("Добавить ребро");
    QPushButton* btnRemoveEdge = new QPushButton("Удалить ребро");
    QPushButton* btnEditWeight = new QPushButton("Редактировать вес");
    QPushButton* btnEditMatrix = new QPushButton("Редактировать матрицу");
    QPushButton* btnLoadVariant9 = new QPushButton("Загрузить вариант 9");

    controlLayout->addWidget(btnAddVertex);
    controlLayout->addWidget(btnRemoveVertex);
    controlLayout->addWidget(btnAddEdge);
    controlLayout->addWidget(btnRemoveEdge);
    controlLayout->addWidget(btnEditWeight);
    controlLayout->addWidget(btnEditMatrix);
    controlLayout->addWidget(btnLoadVariant9);
    controlLayout->addSpacing(20);

    // Группа алгоритмов
    QPushButton* btnDFS = new QPushButton("Обход в глубину (DFS)");
    QPushButton* btnBFS = new QPushButton("Обход в ширину (BFS)");
    QPushButton* btnDijkstra = new QPushButton("Алгоритм Дейкстры");
    QPushButton* btnFloyd = new QPushButton("Алгоритм Флойда-Уоршелла");

    controlLayout->addWidget(btnDFS);
    controlLayout->addWidget(btnBFS);
    controlLayout->addWidget(btnDijkstra);
    controlLayout->addWidget(btnFloyd);
    controlLayout->addSpacing(20);

    // Выбор вершины
    QLabel* lblVertex = new QLabel("Выберите вершину:");
    vertexCombo = new QComboBox();
    controlLayout->addWidget(lblVertex);
    controlLayout->addWidget(vertexCombo);
    controlLayout->addSpacing(20);

    // Лог сообщений
    QLabel* lblLog = new QLabel("Лог:");
    logText = new QTextEdit();
    logText->setReadOnly(true);
    logText->setMaximumHeight(150);
    controlLayout->addWidget(lblLog);
    controlLayout->addWidget(logText);

    controlLayout->addStretch();

    // ========== ПРАВАЯ ПАНЕЛЬ (визуализация) ==========
    QWidget* rightPanel = new QWidget();
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    // Графическая сцена
    QGraphicsView* view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(500, 400);
    view->setBackgroundBrush(Qt::white);
    rightLayout->addWidget(view);

    // Таблица матрицы смежности
    matrixTable = new QTableWidget();
    rightLayout->addWidget(matrixTable);

    mainLayout->addWidget(controlPanel, 1);
    mainLayout->addWidget(rightPanel, 2);

    // Подключение сигналов
    connect(btnAddVertex, &QPushButton::clicked, this, &MainWindow::onAddVertex);
    connect(btnRemoveVertex, &QPushButton::clicked, this, &MainWindow::onRemoveVertex);
    connect(btnAddEdge, &QPushButton::clicked, this, &MainWindow::onAddEdge);
    connect(btnRemoveEdge, &QPushButton::clicked, this, &MainWindow::onRemoveEdge);
    connect(btnEditWeight, &QPushButton::clicked, this, &MainWindow::onEditWeight);
    connect(btnEditMatrix, &QPushButton::clicked, this, &MainWindow::onEditMatrix);
    connect(btnLoadVariant9, &QPushButton::clicked, this, &MainWindow::onLoadVariant9);
    connect(btnDFS, &QPushButton::clicked, this, &MainWindow::onRunDFS);
    connect(btnBFS, &QPushButton::clicked, this, &MainWindow::onRunBFS);
    connect(btnDijkstra, &QPushButton::clicked, this, &MainWindow::onRunDijkstra);
    connect(btnFloyd, &QPushButton::clicked, this, &MainWindow::onRunFloyd);

    // Загружаем вариант 9 по умолчанию
    onLoadVariant9();
}

MainWindow::~MainWindow() {}

void MainWindow::onLoadVariant9() {
    graph.loadVariant9();
    vertexPositions = graph.getPositions();
    updateVisualization();
    updateMatrixDisplay();
    updateVertexCombo();
    logMessage("Загружен граф для варианта 9");
    graph.printGraphVisual();
}

void MainWindow::updateVisualization() {
    scene->clear();

    QPen edgePen(Qt::black, 2);
    QFont weightFont("Arial", 10);
    QBrush vertexBrush(Qt::lightGray);
    QPen vertexPen(Qt::black, 2);
    QFont vertexFont("Arial", 12, QFont::Bold);

    QVector<QString> vertices = graph.getVertices();
    QVector<QVector<int>> adjMatrix = graph.getAdjMatrix();
    int n = vertices.size();

    // Рисуем рёбра
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjMatrix[i][j] != 0) {
                QString v1 = vertices[i];
                QString v2 = vertices[j];
                int weight = adjMatrix[i][j];

                if (vertexPositions.contains(v1) && vertexPositions.contains(v2)) {
                    QPointF p1(vertexPositions[v1].first, vertexPositions[v1].second);
                    QPointF p2(vertexPositions[v2].first, vertexPositions[v2].second);

                    scene->addLine(p1.x(), p1.y(), p2.x(), p2.y(), edgePen);

                    QPointF mid = (p1 + p2) / 2;
                    QGraphicsTextItem* weightText = scene->addText(QString::number(weight), weightFont);
                    weightText->setDefaultTextColor(Qt::darkBlue);
                    weightText->setPos(mid.x() - 10, mid.y() - 10);
                }
            }
        }
    }

    // Рисуем вершины
    for (const QString& v : vertices) {
        if (vertexPositions.contains(v)) {
            qreal x = vertexPositions[v].first;
            qreal y = vertexPositions[v].second;

            scene->addEllipse(x - 20, y - 20, 40, 40, vertexPen, vertexBrush);

            QGraphicsTextItem* label = scene->addText(v, vertexFont);
            label->setDefaultTextColor(Qt::black);
            label->setPos(x - 8, y - 12);
        }
    }
}

void MainWindow::updateMatrixDisplay() {
    int n = graph.getVertCount();
    QVector<QString> vertices = graph.getVertices();
    QVector<QVector<int>> adjMatrix = graph.getAdjMatrix();

    matrixTable->clear();
    matrixTable->setRowCount(n);
    matrixTable->setColumnCount(n);

    QStringList headers;
    for (const QString& v : vertices) {
        headers << v;
    }
    matrixTable->setHorizontalHeaderLabels(headers);
    matrixTable->setVerticalHeaderLabels(headers);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(adjMatrix[i][j]));
            item->setTextAlignment(Qt::AlignCenter);
            if (i == j) {
                item->setBackground(Qt::lightGray);
            }
            matrixTable->setItem(i, j, item);
        }
    }
    matrixTable->resizeColumnsToContents();
}

void MainWindow::updateVertexCombo() {
    vertexCombo->clear();
    for (const QString& v : graph.getVertices()) {
        vertexCombo->addItem(v);
    }
}

void MainWindow::logMessage(const QString& msg) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    logText->append(timestamp + ": " + msg);
    qDebug() << timestamp << ": " << msg;
}

void MainWindow::onAddVertex() {
    bool ok;
    QString vertex = QInputDialog::getText(this, "Добавить вершину",
                                           "Введите название вершины:",
                                           QLineEdit::Normal, "", &ok);
    if (ok && !vertex.isEmpty()) {
        if (graph.addVertex(vertex)) {
            vertexPositions[vertex] = {400, 300};
            graph.setPositions(vertexPositions);
            updateVisualization();
            updateMatrixDisplay();
            updateVertexCombo();
            logMessage("Добавлена вершина: " + vertex);
        } else {
            logMessage("Ошибка: не удалось добавить вершину " + vertex);
        }
    }
}

void MainWindow::onRemoveVertex() {
    QString vertex = vertexCombo->currentText();
    if (!vertex.isEmpty()) {
        if (graph.removeVertex(vertex)) {
            vertexPositions.remove(vertex);
            graph.setPositions(vertexPositions);
            updateVisualization();
            updateMatrixDisplay();
            updateVertexCombo();
            logMessage("Удалена вершина: " + vertex);
        } else {
            logMessage("Ошибка: не удалось удалить вершину " + vertex);
        }
    }
}

void MainWindow::onAddEdge() {
    QString v1 = vertexCombo->currentText();

    bool ok;
    QString v2 = QInputDialog::getText(this, "Добавить ребро",
                                       "Введите вторую вершину:",
                                       QLineEdit::Normal, "", &ok);
    if (!ok) return;

    int weight = QInputDialog::getInt(this, "Добавить ребро",
                                      "Введите вес ребра:", 1, 1, 100, 1, &ok);
    if (!ok) return;

    if (graph.addEdge(v1, v2, weight)) {
        updateVisualization();
        updateMatrixDisplay();
        logMessage(QString("Добавлено ребро %1-%2 весом %3").arg(v1, v2).arg(weight));
    } else {
        logMessage("Ошибка: не удалось добавить ребро");
    }
}

void MainWindow::onRemoveEdge() {
    QString v1 = vertexCombo->currentText();

    bool ok;
    QString v2 = QInputDialog::getText(this, "Удалить ребро",
                                       "Введите вторую вершину:",
                                       QLineEdit::Normal, "", &ok);
    if (!ok) return;

    if (graph.removeEdge(v1, v2)) {
        updateVisualization();
        updateMatrixDisplay();
        logMessage(QString("Удалено ребро %1-%2").arg(v1, v2));
    } else {
        logMessage("Ошибка: не удалось удалить ребро");
    }
}

void MainWindow::onEditWeight() {
    QString v1 = vertexCombo->currentText();

    bool ok;
    QString v2 = QInputDialog::getText(this, "Редактировать вес",
                                       "Введите вторую вершину:",
                                       QLineEdit::Normal, "", &ok);
    if (!ok) return;

    int currentWeight = graph.getWeight(v1, v2);
    int newWeight = QInputDialog::getInt(this, "Редактировать вес",
                                         "Введите новый вес:",
                                         currentWeight, 1, 100, 1, &ok);
    if (!ok) return;

    if (graph.editWeight(v1, v2, newWeight)) {
        updateVisualization();
        updateMatrixDisplay();
        logMessage(QString("Изменён вес ребра %1-%2: %3 -> %4")
                   .arg(v1, v2).arg(currentWeight).arg(newWeight));
    } else {
        logMessage("Ошибка: не удалось изменить вес");
    }
}

void MainWindow::onRunDFS() {
    QString start = vertexCombo->currentText();
    if (start.isEmpty()) {
        logMessage("Ошибка: выберите начальную вершину");
        return;
    }

    QVector<QString> order = graph.DFS(start);
    QString result = "DFS (обход в глубину) от вершины " + start + ": ";
    for (int i = 0; i < order.size(); ++i) {
        result += order[i];
        if (i < order.size() - 1) result += " → ";
    }
    logMessage(result);
    QMessageBox::information(this, "DFS - Обход в глубину", result);
}

void MainWindow::onRunBFS() {
    QString start = vertexCombo->currentText();
    if (start.isEmpty()) {
        logMessage("Ошибка: выберите начальную вершину");
        return;
    }

    QVector<QString> order = graph.BFS(start);
    QString result = "BFS (обход в ширину) от вершины " + start + ": ";
    for (int i = 0; i < order.size(); ++i) {
        result += order[i];
        if (i < order.size() - 1) result += " → ";
    }
    logMessage(result);
    QMessageBox::information(this, "BFS - Обход в ширину", result);
}

void MainWindow::onRunDijkstra() {
    QString start = vertexCombo->currentText();
    if (start.isEmpty()) {
        logMessage("Ошибка: выберите начальную вершину");
        return;
    }

    QMap<QString, int> distances = graph.dijkstra(start);

    QString result = "Кратчайшие расстояния от вершины " + start + ":\n\n";
    for (auto it = distances.begin(); it != distances.end(); ++it) {
        if (it.value() >= INF) {
            result += QString("  до %1: недостижима\n").arg(it.key());
        } else {
            result += QString("  до %1: %2\n").arg(it.key()).arg(it.value());
        }
    }

    logMessage("Выполнен алгоритм Дейкстры от вершины " + start);
    QMessageBox::information(this, "Алгоритм Дейкстры", result);
}

void MainWindow::onRunFloyd() {
    QVector<QVector<int>> dist = graph.floydWarshall();
    QVector<QString> vertices = graph.getVertices();
    int n = vertices.size();

    QString result = "Матрица кратчайших расстояний (Флойд-Уоршелл):\n\n";
    result += "      ";
    for (int i = 0; i < n; ++i) {
        result += QString("%1   ").arg(vertices[i]);
    }
    result += "\n      ";
    for (int i = 0; i < n; ++i) {
        result += "----";
    }
    result += "\n";

    for (int i = 0; i < n; ++i) {
        result += QString("  %1 | ").arg(vertices[i]);
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] >= INF / 2) {
                result += "∞   ";
            } else {
                result += QString("%1   ").arg(dist[i][j]);
            }
        }
        result += "\n";
    }

    logMessage("Выполнен алгоритм Флойда-Уоршелла");
    QMessageBox::information(this, "Алгоритм Флойда-Уоршелла", result);
}

void MainWindow::onEditMatrix() {
    int n = graph.getVertCount();
    QVector<QString> vertices = graph.getVertices();

    QString result = "Текущая матрица смежности:\n\n";
    result += "     ";
    for (int i = 0; i < n; ++i) {
        result += QString("%1   ").arg(vertices[i]);
    }
    result += "\n";

    QVector<QVector<int>> adjMatrix = graph.getAdjMatrix();
    for (int i = 0; i < n; ++i) {
        result += QString("%1 | ").arg(vertices[i]);
        for (int j = 0; j < n; ++j) {
            result += QString("%1   ").arg(adjMatrix[i][j]);
        }
        result += "\n";
    }

    logMessage("Просмотр матрицы смежности");
    QMessageBox::information(this, "Матрица смежности", result);
}
