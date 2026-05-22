#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QString>
#include <QQueue>
#include <QStack>
#include <QSet>
#include <QMap>
#include <QPair>
#include <limits>

const int INF = std::numeric_limits<int>::max() / 2;

class Graph {
private:
    QVector<QString> vertices;
    QVector<QVector<int>> adjMatrix;
    int maxSize;
    QMap<QString, QPair<int, int>> positions;

    void DFSUtil(const QString& vertex, QSet<QString>& visited, QVector<QString>& result);

public:
    Graph(int size = 20);
    ~Graph();

    bool isEmpty() const;
    bool isFull() const;
    int getVertCount() const;
    int getEdgeCount() const;
    int getVertexPos(const QString& vertex) const;
    int getWeight(const QString& v1, const QString& v2) const;
    void setWeight(const QString& v1, const QString& v2, int weight);

    bool addVertex(const QString& vertex);
    bool removeVertex(const QString& vertex);
    bool addEdge(const QString& v1, const QString& v2, int weight);
    bool removeEdge(const QString& v1, const QString& v2);
    bool editWeight(const QString& v1, const QString& v2, int newWeight);

    QVector<QString> getNeighbors(const QString& vertex) const;
    QVector<QString> DFS(const QString& startVertex);
    QVector<QString> BFS(const QString& startVertex);
    QMap<QString, int> dijkstra(const QString& startVertex);
    QVector<QVector<int>> floydWarshall();

    void printMatrix() const;
    void printGraphVisual() const;
    void loadVariant9();

    QVector<QString> getVertices() const { return vertices; }
    QVector<QVector<int>> getAdjMatrix() const { return adjMatrix; }
    QMap<QString, QPair<int, int>> getPositions() const { return positions; }
    void setPositions(const QMap<QString, QPair<int, int>>& pos) { positions = pos; }
};

#endif // GRAPH_H
