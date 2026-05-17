#ifndef TREE_NODE_H
#define TREE_NODE_H

// ============================================================
//  CDSIAS — Tree Node Shared Definition
//  src/core/trees/tree_node.h
//
//  Shared node structure for BT, BST, and AVL trees.
// ============================================================

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    int height; // Primarily used for AVL tree, default 1

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

#endif
