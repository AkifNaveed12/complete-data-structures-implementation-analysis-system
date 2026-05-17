#ifndef BT_H
#define BT_H

// ============================================================
//  CDSIAS — Binary Tree Header
//  src/core/trees/bt.h
// ============================================================

#include "tree_node.h"

class BinaryTree {
private:
    TreeNode* root;

    void inorderHelper(TreeNode* node, int& steps);
    void preorderHelper(TreeNode* node, int& steps);
    void postorderHelper(TreeNode* node, int& steps);
    void deleteTree(TreeNode* node);

public:
    BinaryTree();
    ~BinaryTree();

    void insert(int value);
    void inorder();
    void preorder();
    void postorder();
    void display();
};

#endif
