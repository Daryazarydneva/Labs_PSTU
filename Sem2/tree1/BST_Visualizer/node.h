#ifndef NODE_H
#define NODE_H

class Node
{
public:
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int key);
    int getKey() const;
    void setLeft(Node* node);
    void setRight(Node* node);
    Node* getLeft() const;
    Node* getRight() const;
    Node* getParent() const;
    void setParent(Node* node);
};

#endif // NODE_H
