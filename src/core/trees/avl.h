#ifndef AVL_H
#define AVL_H

// ============================================================
//  CDSIAS — AVL Tree Header
//  src/core/trees/avl.h
// ============================================================

#include "tree_node.h"

class AVLTree {
private:
    TreeNode* root;

    int height(TreeNode* node);
    int getBalance(TreeNode* node);
    void updateHeight(TreeNode* node);

    TreeNode* rightRotate(TreeNode* y, int& steps);
    TreeNode* leftRotate(TreeNode* x, int& steps);

    TreeNode* insertHelper(TreeNode* node, int value, int& steps, int& comparisons);
    void deleteTree(TreeNode* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(int value);
    void display();
    TreeNode* getRoot() const { return root; } // GUI helper
};

#endif
