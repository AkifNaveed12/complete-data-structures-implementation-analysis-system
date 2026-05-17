// ============================================================
//  CDSIAS — AVL Tree Implementation
//  src/core/trees/avl.cpp
// ============================================================

#include <iostream>
#include <string>
#include "avl.h"
#include "tree_visuals.h"
#include "../../analysis/visual.h"
#include "../../analysis/performance.h"

using namespace std;

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
AVLTree::AVLTree() {
    root = nullptr;
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
void AVLTree::deleteTree(TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

AVLTree::~AVLTree() {
    deleteTree(root);
}

// --------------------------------------------------------
// Display
// --------------------------------------------------------
void AVLTree::display() {
    printTree(root);
}

// --------------------------------------------------------
// Helper Methods
// --------------------------------------------------------
int AVLTree::height(TreeNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int AVLTree::getBalance(TreeNode* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

void AVLTree::updateHeight(TreeNode* node) {
    if (node != nullptr) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
}

// --------------------------------------------------------
// Rotations
// --------------------------------------------------------
TreeNode* AVLTree::rightRotate(TreeNode* y, int& steps) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

TreeNode* AVLTree::leftRotate(TreeNode* x, int& steps) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// --------------------------------------------------------
// Insert
// --------------------------------------------------------
TreeNode* AVLTree::insertHelper(TreeNode* node, int value, int& steps, int& comparisons) {
    // 1. Perform standard BST insertion
    if (node == nullptr) {
        printStep(steps++, "Found empty position. Inserting " + highlight(value));
        return new TreeNode(value);
    }

    comparisons++;
    if (value < node->data) {
        node->left = insertHelper(node->left, value, steps, comparisons);
    } else if (value > node->data) {
        node->right = insertHelper(node->right, value, steps, comparisons);
    } else {
        printStep(steps++, "Value " + to_string(value) + " already exists. Duplicate ignored.");
        return node;
    }

    // 2. Update height of this ancestor node
    updateHeight(node);

    // 3. Get the balance factor
    int balance = getBalance(node);
    
    // Print balance factor if unbalanced
    if (balance > 1 || balance < -1) {
        printStep(steps++, "Node " + highlight(node->data) + " is UNBALANCED (Balance Factor: " + to_string(balance) + ")");
        printTree(root, node);
        sleep_ms(400);

        // If this node becomes unbalanced, then there are 4 cases
        comparisons++;
        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            printStep(steps++, "LL Imbalance detected. Performing LL Rotation (Right Rotate)...");
            sleep_ms(400);
            return rightRotate(node, steps);
        }
        
        comparisons++;
        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            printStep(steps++, "RR Imbalance detected. Performing RR Rotation (Left Rotate)...");
            sleep_ms(400);
            return leftRotate(node, steps);
        }
        
        comparisons++;
        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            printStep(steps++, "LR Imbalance detected. Performing LR Rotation...");
            printStep(steps++, "Step 1: Left Rotate child " + to_string(node->left->data));
            node->left = leftRotate(node->left, steps);
            printTree(root);
            sleep_ms(400);
            printStep(steps++, "Step 2: Right Rotate parent " + to_string(node->data));
            sleep_ms(400);
            return rightRotate(node, steps);
        }
        
        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            printStep(steps++, "RL Imbalance detected. Performing RL Rotation...");
            printStep(steps++, "Step 1: Right Rotate child " + to_string(node->right->data));
            node->right = rightRotate(node->right, steps);
            printTree(root);
            sleep_ms(400);
            printStep(steps++, "Step 2: Left Rotate parent " + to_string(node->data));
            sleep_ms(400);
            return leftRotate(node, steps);
        }
    }

    return node;
}

// --------------------------------------------------------
// Print all balance factors helper
// --------------------------------------------------------
static void printBalanceFactors(TreeNode* node) {
    if (node == nullptr) return;
    printBalanceFactors(node->left);
    int bf = 0;
    if (node) {
        int hl = (node->left) ? node->left->height : 0;
        int hr = (node->right) ? node->right->height : 0;
        bf = hl - hr;
    }
    cout << "  Node " << node->data << " -> BF: " << bf << "\n";
    printBalanceFactors(node->right);
}

void AVLTree::insert(int value) {
    printHeader("AVL Tree", "Insert: " + to_string(value));

    printStep(1, "BEFORE:");
    printTree(root);
    sleep_ms(500);

    int steps = 2;
    int comparisons = 0;

    root = insertHelper(root, value, steps, comparisons);

    printResult("AFTER: " + to_string(value) + " inserted");
    printTree(root);
    
    cout << "\n  Balance Factors:\n";
    printBalanceFactors(root);

    Performance::log("AVL Tree", "Insert", steps, comparisons);
}
