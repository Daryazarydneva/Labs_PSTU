#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "node.h"
#include <vector>

// Forward declaration
class Node;

class BinaryTree
{
private:
    Node* root;
    Node* insertRec(Node* node, int key, Node* parent);
    Node* findMin(Node* node);
    Node* removeRec(Node* node, int key);
    void inorderRec(Node* node, std::vector<int>& result);
    void preorderRec(Node* node, std::vector<int>& result);
    void postorderRec(Node* node, std::vector<int>& result);
    bool searchRec(Node* node, int key);

public:
    BinaryTree();
    ~BinaryTree();
    void insert(int key);
    void remove(int key);
    bool search(int key);
    std::vector<int> inorder();
    std::vector<int> preorder();
    std::vector<int> postorder();
    Node* getRoot() const;
    void clear(Node* node);
};

#endif // BINARYTREE_H
