#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "graph.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddVertex();
    void onRemoveVertex();
    void onAddEdge();
    void onRemoveEdge();
    void onEditWeight();
    void onRunDFS();
    void onRunBFS();
    void onRunDijkstra();
    void onRunFloyd();
    void onLoadVariant9();
    void onEditMatrix();

private:
    void updateVisualization();
    void updateMatrixDisplay();
    void updateVertexCombo();
    void logMessage(const QString& msg);

    Graph graph;
    QGraphicsScene* scene;
    QTableWidget* matrixTable;
    QComboBox* vertexCombo;
    QTextEdit* logText;
    QMap<QString, QPair<int, int>> vertexPositions;
};

#endif // MAINWINDOW_H
