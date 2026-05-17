#ifndef TREE_VISUALS_H
#define TREE_VISUALS_H

// ============================================================
//  CDSIAS — Tree Visualizations
//  src/core/trees/tree_visuals.h
//
//  Shared visualization helpers for BT, BST, AVL.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include "tree_node.h"
#include "../../analysis/visual.h"

using namespace std;

// --------------------------------------------------------
// Get tree height helper
// --------------------------------------------------------
inline int getTreeHeight(TreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + max(getTreeHeight(node->left), getTreeHeight(node->right));
}

// --------------------------------------------------------
// Print Tree (Vertical ASCII)
// --------------------------------------------------------
inline void printTree(TreeNode* root, TreeNode* activeNode = nullptr) {
    if (root == nullptr) {
        cout << "[ empty ]\n";
        return;
    }

    int height = getTreeHeight(root);
    // If the tree is too tall, a vertical print might break formatting.
    // For CDSIAS, typical educational trees are small (height <= 5).
    
    // We will do a level-order traversal to build the lines
    vector<TreeNode*> currentLevel;
    currentLevel.push_back(root);
    
    int level = 1;
    while (!currentLevel.empty() && level <= height) {
        vector<TreeNode*> nextLevel;
        bool hasNodes = false;
        
        // Calculate spacing
        int spaceBetween = pow(2, height - level + 1) * 2;
        int initialSpace = spaceBetween / 2;
        
        // Print leading space
        for (int i = 0; i < initialSpace; i++) cout << " ";
        
        // Print nodes
        for (size_t i = 0; i < currentLevel.size(); i++) {
            TreeNode* node = currentLevel[i];
            
            if (node != nullptr) {
                if (node == activeNode) {
                    cout << highlight(to_string(node->data));
                } else {
                    cout << node->data;
                }
                
                nextLevel.push_back(node->left);
                nextLevel.push_back(node->right);
                if (node->left != nullptr || node->right != nullptr) hasNodes = true;
            } else {
                cout << "  "; // Empty node placeholder
                nextLevel.push_back(nullptr);
                nextLevel.push_back(nullptr);
            }
            
            // Print space between nodes
            for (int s = 0; s < spaceBetween - 2; s++) cout << " ";
        }
        cout << "\n";
        
        // Print branches if not the last level
        if (level < height) {
            // Print leading space for branches
            for (int i = 0; i < initialSpace - 1; i++) cout << " ";
            
            for (size_t i = 0; i < currentLevel.size(); i++) {
                TreeNode* node = currentLevel[i];
                if (node != nullptr) {
                    if (node->left) cout << "/"; else cout << " ";
                    cout << "  ";
                    if (node->right) cout << "\\"; else cout << " ";
                } else {
                    cout << "    ";
                }
                // Print space between branches
                for (int s = 0; s < spaceBetween - 4; s++) cout << " ";
            }
            cout << "\n";
        }
        
        currentLevel = nextLevel;
        level++;
        if (!hasNodes) break;
    }
}

#endif
