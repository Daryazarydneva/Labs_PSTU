#include "binarytree.h"
#include "node.h"
BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    clear(root);
}

void BinaryTree::clear(Node* node) {
    if (!node) return;
    clear(node->getLeft());
    clear(node->getRight());
    delete node;
}

Node* BinaryTree::insertRec(Node* node, int key, Node* parent) {
    if (!node) {
        Node* newNode = new Node(key);
        newNode->setParent(parent);
        return newNode;
    }
    if (key < node->getKey())
        node->setLeft(insertRec(node->getLeft(), key, node));
    else if (key > node->getKey())
        node->setRight(insertRec(node->getRight(), key, node));
    return node;
}

void BinaryTree::insert(int key) {
    root = insertRec(root, key, nullptr);
}

bool BinaryTree::searchRec(Node* node, int key) {
    if (!node) return false;
    if (node->getKey() == key) return true;
    if (key < node->getKey()) return searchRec(node->getLeft(), key);
    return searchRec(node->getRight(), key);
}

bool BinaryTree::search(int key) {
    return searchRec(root, key);
}

Node* BinaryTree::findMin(Node* node) {
    while (node && node->getLeft())
        node = node->getLeft();
    return node;
}

Node* BinaryTree::removeRec(Node* node, int key) {
    if (!node) return nullptr;

    if (key < node->getKey())
        node->setLeft(removeRec(node->getLeft(), key));
    else if (key > node->getKey())
        node->setRight(removeRec(node->getRight(), key));
    else {
        // Узел найден
        if (!node->getLeft()) {
            Node* rightChild = node->getRight();
            delete node;
            return rightChild;
        }
        else if (!node->getRight()) {
            Node* leftChild = node->getLeft();
            delete node;
            return leftChild;
        }
        else {
            Node* minNode = findMin(node->getRight());
            node->key = minNode->getKey();
            node->setRight(removeRec(node->getRight(), minNode->getKey()));
        }
    }
    return node;
}

void BinaryTree::remove(int key) {
    root = removeRec(root, key);
}

void BinaryTree::inorderRec(Node* node, std::vector<int>& result) {
    if (!node) return;
    inorderRec(node->getLeft(), result);
    result.push_back(node->getKey());
    inorderRec(node->getRight(), result);
}

std::vector<int> BinaryTree::inorder() {
    std::vector<int> result;
    inorderRec(root, result);
    return result;
}

void BinaryTree::preorderRec(Node* node, std::vector<int>& result) {
    if (!node) return;
    result.push_back(node->getKey());
    preorderRec(node->getLeft(), result);
    preorderRec(node->getRight(), result);
}

std::vector<int> BinaryTree::preorder() {
    std::vector<int> result;
    preorderRec(root, result);
    return result;
}

void BinaryTree::postorderRec(Node* node, std::vector<int>& result) {
    if (!node) return;
    postorderRec(node->getLeft(), result);
    postorderRec(node->getRight(), result);
    result.push_back(node->getKey());
}

std::vector<int> BinaryTree::postorder() {
    std::vector<int> result;
    postorderRec(root, result);
    return result;
}

Node* BinaryTree::getRoot() const {
    return root;
}
