// ============================================================
//  CDSIAS — Binary Search Tree Implementation
//  src/core/trees/bst.cpp
// ============================================================

#include <iostream>
#include <string>
#include "bst.h"
#include "tree_visuals.h"
#include "../../analysis/visual.h"
#include "../../analysis/performance.h"

using namespace std;

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
void BinarySearchTree::deleteTree(TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

BinarySearchTree::~BinarySearchTree() {
    deleteTree(root);
}

// --------------------------------------------------------
// Display
// --------------------------------------------------------
void BinarySearchTree::display() {
    printTree(root);
}

// --------------------------------------------------------
// Insert
// --------------------------------------------------------
TreeNode* BinarySearchTree::insertHelper(TreeNode* node, int value, int& steps, int& comparisons) {
    if (node == nullptr) {
        printStep(steps++, "Found empty position. Inserting " + highlight(value));
        return new TreeNode(value);
    }

    comparisons++;
    if (value < node->data) {
        printStep(steps++, "Checking " + to_string(node->data) + " -> Going left...");
        printTree(root, node);
        sleep_ms(300);
        node->left = insertHelper(node->left, value, steps, comparisons);
    } else if (value > node->data) {
        printStep(steps++, "Checking " + to_string(node->data) + " -> Going right...");
        printTree(root, node);
        sleep_ms(300);
        node->right = insertHelper(node->right, value, steps, comparisons);
    } else {
        printStep(steps++, "Value " + to_string(value) + " already exists. Duplicate ignored.");
    }
    return node;
}

void BinarySearchTree::insert(int value) {
    printHeader("BST", "Insert: " + to_string(value));

    printStep(1, "BEFORE:");
    printTree(root);
    sleep_ms(500);

    int steps = 2;
    int comparisons = 0;

    root = insertHelper(root, value, steps, comparisons);

    printResult("AFTER: " + to_string(value) + " inserted");
    printTree(root);

    Performance::log("BST", "Insert", steps, comparisons);
}

// --------------------------------------------------------
// Search
// --------------------------------------------------------
TreeNode* BinarySearchTree::searchHelper(TreeNode* node, int value, int& steps, int& comparisons) {
    if (node == nullptr) {
        comparisons++;
        printError("Value " + to_string(value) + " not found in tree.");
        return nullptr;
    }

    comparisons++;
    if (node->data == value) {
        printStep(steps++, "Found " + highlight(value) + "!");
        printTree(root, node);
        sleep_ms(300);
        return node;
    }

    comparisons++;
    if (value < node->data) {
        printStep(steps++, "Checking " + to_string(node->data) + " -> Going left...");
        printTree(root, node);
        sleep_ms(300);
        return searchHelper(node->left, value, steps, comparisons);
    } else {
        printStep(steps++, "Checking " + to_string(node->data) + " -> Going right...");
        printTree(root, node);
        sleep_ms(300);
        return searchHelper(node->right, value, steps, comparisons);
    }
}

void BinarySearchTree::search(int value) {
    printHeader("BST", "Search: " + to_string(value));

    if (root == nullptr) {
        printError("Tree is empty");
        Performance::log("BST", "Search", 0, 0);
        return;
    }

    printStep(1, "Starting search from root...");
    int steps = 2;
    int comparisons = 0;

    TreeNode* foundNode = searchHelper(root, value, steps, comparisons);

    if (foundNode) {
        printResult("Search complete. Value found.");
    } else {
        printResult("Search complete. Value not found.");
    }

    Performance::log("BST", "Search", steps, comparisons);
}

// --------------------------------------------------------
// Delete
// --------------------------------------------------------
TreeNode* BinarySearchTree::getMinNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

TreeNode* BinarySearchTree::deleteHelper(TreeNode* node, int value, int& steps, int& comparisons) {
    if (node == nullptr) {
        comparisons++;
        printStep(steps++, "Value " + to_string(value) + " not found.");
        return nullptr;
    }

    comparisons++;
    if (value < node->data) {
        printStep(steps++, "Checking " + to_string(node->data) + " -> Going left...");
        printTree(root, node);
        sleep_ms(300);
        node->left = deleteHelper(node->left, value, steps, comparisons);
    } else if (value > node->data) {
        comparisons++;
        printStep(steps++, "Checking " + to_string(node->data) + " -> Going right...");
        printTree(root, node);
        sleep_ms(300);
        node->right = deleteHelper(node->right, value, steps, comparisons);
    } else {
        comparisons++; // node->data == value
        printStep(steps++, "Found node to delete: " + highlight(node->data));
        printTree(root, node);
        sleep_ms(500);

        // Case 1: Leaf node (no children)
        if (node->left == nullptr && node->right == nullptr) {
            printStep(steps++, "Case 1: Leaf node. Deleting directly.");
            delete node;
            return nullptr;
        }
        // Case 2: One child (right only)
        else if (node->left == nullptr) {
            printStep(steps++, "Case 2: One child (right). Replacing node with its right child.");
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        // Case 2: One child (left only)
        else if (node->right == nullptr) {
            printStep(steps++, "Case 2: One child (left). Replacing node with its left child.");
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        // Case 3: Two children
        else {
            printStep(steps++, "Case 3: Two children. Finding inorder successor (min in right subtree)...");
            TreeNode* temp = getMinNode(node->right);
            printStep(steps++, "Inorder successor found: " + highlight(temp->data));
            
            node->data = temp->data;
            printStep(steps++, "Replaced node's value with successor's value.");
            printTree(root, node);
            sleep_ms(300);

            printStep(steps++, "Deleting original inorder successor...");
            node->right = deleteHelper(node->right, temp->data, steps, comparisons);
        }
    }
    return node;
}

void BinarySearchTree::remove(int value) {
    printHeader("BST", "Delete: " + to_string(value));

    if (root == nullptr) {
        printError("Tree is empty");
        Performance::log("BST", "Delete", 0, 0);
        return;
    }

    printStep(1, "BEFORE:");
    printTree(root);
    sleep_ms(500);

    int steps = 2;
    int comparisons = 0;

    root = deleteHelper(root, value, steps, comparisons);

    printResult("AFTER: " + to_string(value) + " deleted (if it existed)");
    printTree(root);

    Performance::log("BST", "Delete", steps, comparisons);
}
