#ifndef BST_H
#define BST_H

// ============================================================
//  CDSIAS — Binary Search Tree Header
//  src/core/trees/bst.h
// ============================================================

#include "tree_node.h"

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insertHelper(TreeNode* node, int value, int& steps, int& comparisons);
    TreeNode* searchHelper(TreeNode* node, int value, int& steps, int& comparisons);
    TreeNode* deleteHelper(TreeNode* node, int value, int& steps, int& comparisons);
    TreeNode* getMinNode(TreeNode* node);
    void deleteTree(TreeNode* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int value);
    void remove(int value);
    void search(int value);
    void display();
    TreeNode* getRoot() const { return root; }
};

#endif
