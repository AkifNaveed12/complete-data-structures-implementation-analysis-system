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
    void remove(int value); // Changed from 'delete' because 'delete' is a C++ keyword
    void search(int value);
    void display();
};

#endif
