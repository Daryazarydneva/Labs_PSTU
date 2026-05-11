#include "node.h"

Node::Node(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr) {}

int Node::getKey() const { return key; }

void Node::setLeft(Node* node) {
    left = node;
    if (node) node->setParent(this);
}

void Node::setRight(Node* node) {
    right = node;
    if (node) node->setParent(this);
}

Node* Node::getLeft() const { return left; }
Node* Node::getRight() const { return right; }
Node* Node::getParent() const { return parent; }
void Node::setParent(Node* node) { parent = node; }
