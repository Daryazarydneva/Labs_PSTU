#include "graph.h"
#include <QDebug>
#include <cstdlib>

Graph::Graph(int size) : maxSize(size) {
    adjMatrix.resize(maxSize);
    for (int i = 0; i < maxSize; ++i) {
        adjMatrix[i].fill(0, maxSize);
    }
}

Graph::~Graph() {}

bool Graph::isEmpty() const {
    return vertices.isEmpty();
}

bool Graph::isFull() const {
    return vertices.size() == maxSize;
}

int Graph::getVertCount() const {
    return vertices.size();
}

int Graph::getEdgeCount() const {
    int count = 0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjMatrix[i][j] != 0) count++;
        }
    }
    return count;
}

int Graph::getVertexPos(const QString& vertex) const {
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == vertex) return i;
    }
    return -1;
}

int Graph::getWeight(const QString& v1, const QString& v2) const {
    int pos1 = getVertexPos(v1);
    int pos2 = getVertexPos(v2);
    if (pos1 != -1 && pos2 != -1) return adjMatrix[pos1][pos2];
    return 0;
}

void Graph::setWeight(const QString& v1, const QString& v2, int weight) {
    int pos1 = getVertexPos(v1);
    int pos2 = getVertexPos(v2);
    if (pos1 != -1 && pos2 != -1 && weight >= 0) {
        adjMatrix[pos1][pos2] = weight;
        adjMatrix[pos2][pos1] = weight;
    }
}

bool Graph::addVertex(const QString& vertex) {
    if (isFull() || getVertexPos(vertex) != -1) return false;
    vertices.push_back(vertex);
    return true;
}

bool Graph::removeVertex(const QString& vertex) {
    int pos = getVertexPos(vertex);
    if (pos == -1) return false;

    vertices.removeAt(pos);

    for (int i = pos; i < vertices.size(); ++i) {
        adjMatrix[i] = adjMatrix[i + 1];
    }
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = pos; j < vertices.size(); ++j) {
            adjMatrix[i][j] = adjMatrix[i][j + 1];
        }
    }
    for (int i = 0; i < maxSize; ++i) {
        adjMatrix[vertices.size()][i] = 0;
        adjMatrix[i][vertices.size()] = 0;
    }

    positions.remove(vertex);
    return true;
}

bool Graph::addEdge(const QString& v1, const QString& v2, int weight) {
    if (weight <= 0) return false;
    int pos1 = getVertexPos(v1);
    int pos2 = getVertexPos(v2);
    if (pos1 == -1 || pos2 == -1 || adjMatrix[pos1][pos2] != 0) return false;
    adjMatrix[pos1][pos2] = weight;
    adjMatrix[pos2][pos1] = weight;
    return true;
}

bool Graph::removeEdge(const QString& v1, const QString& v2) {
    int pos1 = getVertexPos(v1);
    int pos2 = getVertexPos(v2);
    if (pos1 == -1 || pos2 == -1 || adjMatrix[pos1][pos2] == 0) return false;
    adjMatrix[pos1][pos2] = 0;
    adjMatrix[pos2][pos1] = 0;
    return true;
}

bool Graph::editWeight(const QString& v1, const QString& v2, int newWeight) {
    if (newWeight <= 0) return false;
    int pos1 = getVertexPos(v1);
    int pos2 = getVertexPos(v2);
    if (pos1 == -1 || pos2 == -1 || adjMatrix[pos1][pos2] == 0) return false;
    adjMatrix[pos1][pos2] = newWeight;
    adjMatrix[pos2][pos1] = newWeight;
    return true;
}

QVector<QString> Graph::getNeighbors(const QString& vertex) const {
    QVector<QString> neighbors;
    int pos = getVertexPos(vertex);
    if (pos != -1) {
        for (int i = 0; i < vertices.size(); ++i) {
            if (adjMatrix[pos][i] != 0) neighbors.append(vertices[i]);
        }
    }
    return neighbors;
}

void Graph::DFSUtil(const QString& vertex, QSet<QString>& visited, QVector<QString>& result) {
    visited.insert(vertex);
    result.append(vertex);
    QVector<QString> neighbors = getNeighbors(vertex);
    for (const QString& neighbor : neighbors) {
        if (!visited.contains(neighbor)) {
            DFSUtil(neighbor, visited, result);
        }
    }
}

QVector<QString> Graph::DFS(const QString& startVertex) {
    QVector<QString> result;
    QSet<QString> visited;
    if (getVertexPos(startVertex) != -1) {
        DFSUtil(startVertex, visited, result);
    }
    return result;
}

QVector<QString> Graph::BFS(const QString& startVertex) {
    QVector<QString> result;
    QSet<QString> visited;
    QQueue<QString> queue;

    if (getVertexPos(startVertex) == -1) return result;

    visited.insert(startVertex);
    queue.enqueue(startVertex);

    while (!queue.isEmpty()) {
        QString current = queue.dequeue();
        result.append(current);
        QVector<QString> neighbors = getNeighbors(current);
        for (const QString& neighbor : neighbors) {
            if (!visited.contains(neighbor)) {
                visited.insert(neighbor);
                queue.enqueue(neighbor);
            }
        }
    }
    return result;
}

QMap<QString, int> Graph::dijkstra(const QString& startVertex) {
    QMap<QString, int> distances;
    QSet<QString> visited;

    for (const QString& v : vertices) distances[v] = INF;
    distances[startVertex] = 0;

    for (int count = 0; count < vertices.size(); ++count) {
        QString minVertex;
        int minDist = INF;

        for (const QString& v : vertices) {
            if (!visited.contains(v) && distances[v] < minDist) {
                minDist = distances[v];
                minVertex = v;
            }
        }

        if (minVertex.isEmpty()) break;
        visited.insert(minVertex);

        QVector<QString> neighbors = getNeighbors(minVertex);
        for (const QString& neighbor : neighbors) {
            if (!visited.contains(neighbor)) {
                int weight = getWeight(minVertex, neighbor);
                if (distances[minVertex] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[minVertex] + weight;
                }
            }
        }
    }
    return distances;
}

QVector<QVector<int>> Graph::floydWarshall() {
    int n = vertices.size();
    QVector<QVector<int>> dist(n, QVector<int>(n, INF));

    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != 0) dist[i][j] = adjMatrix[i][j];
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

void Graph::printMatrix() const {
    qDebug() << "Матрица смежности:";
    int n = vertices.size();
    QString line;
    for (int i = 0; i < n; ++i) {
        line = vertices[i] + ": ";
        for (int j = 0; j < n; ++j) {
            line += QString::number(adjMatrix[i][j]) + " ";
        }
        qDebug() << line;
    }
}

void Graph::printGraphVisual() const {
    qDebug() << "\n=== ВИЗУАЛИЗАЦИЯ ГРАФА (Вариант 9) ===";
    qDebug() << "              (2)";
    qDebug() << "              /|\\";
    qDebug() << "            5/ | \\7";
    qDebug() << "            / 2|  \\";
    qDebug() << "          (1)--(3)--(4)";
    qDebug() << "            \\3 / \\4 /8";
    qDebug() << "             \\/   \\/";
    qDebug() << "             (5)  6";
    qDebug() << "\nРёбра с весами:";
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = i + 1; j < vertices.size(); ++j) {
            if (adjMatrix[i][j] != 0) {
                qDebug() << "  " << vertices[i] << "--" << adjMatrix[i][j] << "--" << vertices[j];
            }
        }
    }
}

void Graph::loadVariant9() {
    vertices.clear();
    for (int i = 0; i < maxSize; ++i) {
        adjMatrix[i].fill(0, maxSize);
    }

    vertices = {"1", "2", "3", "4", "5"};
    addEdge("1", "2", 5);
    addEdge("1", "3", 3);
    addEdge("2", "3", 2);
    addEdge("2", "4", 7);
    addEdge("3", "4", 4);
    addEdge("3", "5", 6);
    addEdge("4", "5", 8);

    positions["1"] = {100, 100};
    positions["2"] = {300, 50};
    positions["3"] = {250, 200};
    positions["4"] = {150, 250};
    positions["5"] = {350, 200};

    qDebug() << "Загружен вариант 9";
}
