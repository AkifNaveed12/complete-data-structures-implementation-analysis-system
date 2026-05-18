// ============================================================
//  CDSIAS — Binary Tree Implementation
//  src/core/trees/bt.cpp
//
//  No STL allowed in core implementations.
//  Performance tracked for traversal and insertion.
// ============================================================

#include <iostream>
#include <string>
#include "bt.h"
#include "tree_visuals.h"
#include "../../analysis/visual.h"
#include "../../analysis/performance.h"

using namespace std;

// --------------------------------------------------------
// Internal helper: Simple Queue for TreeNode* (No STL)
// --------------------------------------------------------
struct TQNode {
    TreeNode* treeNode;
    TQNode*   next;
    TQNode(TreeNode* tn) : treeNode(tn), next(nullptr) {}
};

class TreeQueue {
private:
    TQNode* front;
    TQNode* rear;
public:
    TreeQueue() : front(nullptr), rear(nullptr) {}
    ~TreeQueue() {
        while (front != nullptr) {
            TQNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
    void enqueue(TreeNode* node) {
        TQNode* newNode = new TQNode(node);
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }
    TreeNode* dequeue() {
        if (front == nullptr) return nullptr;
        TQNode* temp = front;
        TreeNode* res = temp->treeNode;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return res;
    }
    bool isEmpty() {
        return front == nullptr;
    }
};

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
BinaryTree::BinaryTree() {
    root = nullptr;
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
void BinaryTree::deleteTree(TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

BinaryTree::~BinaryTree() {
    deleteTree(root);
}

// --------------------------------------------------------
// Display
// --------------------------------------------------------
void BinaryTree::display() {
    printTree(root);
}

// --------------------------------------------------------
// Insert (Level-Order)
// --------------------------------------------------------
void BinaryTree::insert(int value) {
    printHeader("BinaryTree", "Insert: " + to_string(value));

    printStep(1, "BEFORE:");
    printTree(root);
    sleep_ms(500);

    TreeNode* newNode = new TreeNode(value);
    printStep(2, "Creating new node " + highlight(value));
    sleep_ms(300);

    int steps = 2;
    int comparisons = 0;

    if (root == nullptr) {
        root = newNode;
        printStep(steps++, "Tree is empty. Inserting at root.");
        printTree(root, root);
        sleep_ms(500);
    } else {
        printStep(steps++, "Performing level-order traversal to find first empty position...");
        TreeQueue q;
        q.enqueue(root);
        
        while (!q.isEmpty()) {
            TreeNode* temp = q.dequeue();
            comparisons++;
            
            if (temp->left == nullptr) {
                temp->left = newNode;
                printStep(steps++, "Inserted as left child of " + to_string(temp->data));
                break;
            } else {
                q.enqueue(temp->left);
            }
            
            comparisons++;
            if (temp->right == nullptr) {
                temp->right = newNode;
                printStep(steps++, "Inserted as right child of " + to_string(temp->data));
                break;
            } else {
                q.enqueue(temp->right);
            }
        }
        sleep_ms(500);
    }

    printResult("AFTER: " + to_string(value) + " inserted");
    printTree(root);
    
    Performance::log("BinaryTree", "Insert", steps, comparisons);
}

// --------------------------------------------------------
// Traversals Helper
// --------------------------------------------------------
void BinaryTree::inorderHelper(TreeNode* node, int& steps, string& res) {
    if (node == nullptr) return;
    inorderHelper(node->left, steps, res);
    res += to_string(node->data) + " ";
    printStep(steps++, "Visiting node " + highlight(node->data));
    sleep_ms(300);
    inorderHelper(node->right, steps, res);
}

void BinaryTree::preorderHelper(TreeNode* node, int& steps, string& res) {
    if (node == nullptr) return;
    res += to_string(node->data) + " ";
    printStep(steps++, "Visiting node " + highlight(node->data));
    sleep_ms(300);
    preorderHelper(node->left, steps, res);
    preorderHelper(node->right, steps, res);
}

void BinaryTree::postorderHelper(TreeNode* node, int& steps, string& res) {
    if (node == nullptr) return;
    postorderHelper(node->left, steps, res);
    postorderHelper(node->right, steps, res);
    res += to_string(node->data) + " ";
    printStep(steps++, "Visiting node " + highlight(node->data));
    sleep_ms(300);
}

// --------------------------------------------------------
// Traversals
// --------------------------------------------------------
void BinaryTree::inorder() {
    printHeader("BinaryTree", "In-order Traversal (Left, Root, Right)");
    if (root == nullptr) {
        printError("Tree is empty");
        Performance::log("BinaryTree", "Inorder", 0, 0);
        return;
    }
    
    int steps = 1;
    string res = "";
    inorderHelper(root, steps, res);
    printResult("Traversal complete: " + res);
    Performance::log("BinaryTree", "Inorder", steps, 0);
}

void BinaryTree::preorder() {
    printHeader("BinaryTree", "Pre-order Traversal (Root, Left, Right)");
    if (root == nullptr) {
        printError("Tree is empty");
        Performance::log("BinaryTree", "Preorder", 0, 0);
        return;
    }
    
    int steps = 1;
    string res = "";
    preorderHelper(root, steps, res);
    printResult("Traversal complete: " + res);
    Performance::log("BinaryTree", "Preorder", steps, 0);
}

void BinaryTree::postorder() {
    printHeader("BinaryTree", "Post-order Traversal (Left, Right, Root)");
    if (root == nullptr) {
        printError("Tree is empty");
        Performance::log("BinaryTree", "Postorder", 0, 0);
        return;
    }
    
    int steps = 1;
    string res = "";
    postorderHelper(root, steps, res);
    printResult("Traversal complete: " + res);
    Performance::log("BinaryTree", "Postorder", steps, 0);
}
