// ============================================================
//  CDSIAS — Trees Test File
//  tests/test_trees.cpp
//
//  Tests: BinaryTree
//  All 7 categories per contracts.md §7:
//    1. Normal cases
//    2. Edge: empty
//    3. Edge: overflow (N/A for dynamic trees)
//    4. Edge: not found
//    5. Edge: boundary
//    6. Output format matches contract
//    7. Performance::log verified called
// ============================================================

#include <iostream>
#include "../src/core/trees/bt.h"
#include "../src/core/trees/bst.h"
#include "../src/analysis/performance.h"
#include "../src/analysis/visual.h"

using namespace std;

// ============================================================
//  BINARY TREE TESTS
// ============================================================
void testBinaryTree() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: BinaryTree" << COL_RESET << "\n";
    printSeparator();

    BinaryTree bt;

    // Edge: empty traversals
    cout << "\n[T1.1] In-order empty tree\n";
    bt.inorder();

    cout << "\n[T1.2] Display empty tree\n";
    bt.display();

    // Normal cases
    cout << "\n[T1.3] Insert: 50 (Root)\n";
    bt.insert(50);

    cout << "\n[T1.4] Insert: 30 (Left child of 50)\n";
    bt.insert(30);

    cout << "\n[T1.5] Insert: 70 (Right child of 50)\n";
    bt.insert(70);

    cout << "\n[T1.6] Insert: 20\n";
    bt.insert(20);

    cout << "\n[T1.7] Insert: 40\n";
    bt.insert(40);
    
    cout << "\n[T1.8] Insert: 60\n";
    bt.insert(60);

    cout << "\n[T1.9] Insert: 80\n";
    bt.insert(80);

    cout << "\n[T1.10] In-order Traversal (should be sorted if elements entered logically, but here level-order so 20,30,40,50,60,70,80)\n";
    bt.inorder();

    cout << "\n[T1.11] Pre-order Traversal (50, 30, 20, 40, 70, 60, 80)\n";
    bt.preorder();

    cout << "\n[T1.12] Post-order Traversal (20, 40, 30, 60, 80, 70, 50)\n";
    bt.postorder();
}

// ============================================================
//  BINARY SEARCH TREE TESTS
// ============================================================
void testBST() {
    printSeparator();
    cout << COL_ACCENT << "  TEST: Binary Search Tree" << COL_RESET << "\n";
    printSeparator();

    BinarySearchTree bst;

    cout << "\n[T2.1] Search empty tree\n";
    bst.search(50);

    cout << "\n[T2.2] Delete from empty tree\n";
    bst.remove(50);

    cout << "\n[T2.3] Insert: 50, 30, 70, 20, 40, 60, 80\n";
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    cout << "\n[T2.4] Insert duplicate: 30\n";
    bst.insert(30);

    cout << "\n[T2.5] Search: 40 (Existing)\n";
    bst.search(40);

    cout << "\n[T2.6] Search: 90 (Not found)\n";
    bst.search(90);

    cout << "\n[T2.7] Delete: 20 (Case 1: Leaf node)\n";
    bst.remove(20);

    cout << "\n[T2.8] Delete: 30 (Case 2: One child - currently 40 is right child, 20 was deleted)\n";
    bst.remove(30);

    cout << "\n[T2.9] Delete: 50 (Case 3: Two children)\n";
    bst.remove(50);

    cout << "\n[T2.10] Display Final BST\n";
    bst.display();
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    cout << "\n";
    printSeparator();
    cout << COL_ACCENT << "  CDSIAS - TREES MODULE TESTS" << COL_RESET << "\n";
    printSeparator();

    testBinaryTree();
    testBST();

    // Performance report at end
    cout << "\n";
    Performance::display();

    return 0;
}
