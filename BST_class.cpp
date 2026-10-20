#include <iostream>
using namespace std;

struct TNode {
public:
    int item;
    TNode* left;
    TNode* right;
};

class BST {
public:
    BST();

    // Added to release dynamically allocated nodes.
    ~BST();

    int GetItem(int gitem);
    void PutItem(int newitem);
    void DeleteItem(int ditem);
    void PrintTree();

private:
    TNode* root;

    void Insert(TNode*& curnode, int newitem);
    int FindItem(TNode* curnode, int gitem);
    void Delete(TNode*& curnode, int ditem);
    void DeleteNode(TNode*& curnode);
    void PrintNode(TNode*& curnode);

    // Additional helper for the destructor.
    void DestroyTree(TNode* curnode);
};

BST::BST()
{
    root = nullptr;
}

int BST::GetItem(int gitem)
{
    return FindItem(root, gitem);
}

void BST::PutItem(int newitem)
{
    Insert(root, newitem);
}

void BST::DeleteItem(int ditem)
{
    Delete(root, ditem);
}

void BST::PrintTree()
{
    // to do
}

int BST::FindItem(TNode* curnode, int gitem)
{
    if (curnode == nullptr) 
        return -1;  
    else if (gitem == curnode->item) 
        return curnode->item;
    else if (gitem < curnode->item) 
        return FindItem(curnode->left, gitem);
    else
        return FindItem(curnode->right, gitem);
}

void BST::Insert(TNode*& curnode, int newitem)
{
    if (curnode == nullptr) {
        curnode = new TNode;
        curnode->item = newitem;
        curnode->left = nullptr;
        curnode->right = nullptr;
    }
    else if (newitem < curnode->item) {
        Insert(curnode->left, newitem);
    }
    else if (newitem > curnode->item) {
        Insert(curnode->right, newitem);
    }

    // else: newitem == curnode->item, do nothing.
}

void BST::Delete(TNode*& curnode, int ditem)
{
    if (curnode == nullptr) 
        return;  // Item not found
    else if (ditem < curnode->item) 
        Delete(curnode->left, ditem);
    else if (ditem > curnode->item) 
        Delete(curnode->right, ditem);
    else 
        // Found the node to delete.
        DeleteNode(curnode);
}

void BST::DeleteNode(TNode*& curnode)
{
    TNode* temp;

    // Case 1: Leaf node (no children).
    if (curnode->left == nullptr &&
        curnode->right == nullptr) {

        delete curnode;
        curnode = nullptr;
    }

    // Case 2a: Only a right child.
    else if (curnode->left == nullptr) {
        temp = curnode;
        curnode = curnode->right;
        delete temp;
    }

    // Case 2b: Only a left child.
    else if (curnode->right == nullptr) {
        temp = curnode;
        curnode = curnode->left;
        delete temp;
    }

    // Case 3: Two children.
    // Replace with the in-order predecessor:
    // the largest item in the left subtree.
    else {
        TNode* pred = curnode->left;

        while (pred->right != nullptr) {
            pred = pred->right;
        }

        int predecessorItem = pred->item;

        curnode->item = predecessorItem;

        // Remove the original predecessor node.
        // It has no right child, but may have a left child.
        Delete(curnode->left, predecessorItem);
    }
}

void BST::PrintNode(TNode*& curnode)
{
    // to do
}

BST::~BST()
{
    DestroyTree(root);
}

void BST::DestroyTree(TNode* curnode)
{
    if (curnode != nullptr) {
        DestroyTree(curnode->left);
        DestroyTree(curnode->right);
        delete curnode;
    }
}

// Simple demonstration
int main()
{
    BST tree;

    tree.PutItem(50);
    tree.PutItem(30);
    tree.PutItem(70);
    tree.PutItem(20);
    tree.PutItem(40);
    tree.PutItem(60);
    tree.PutItem(80);

    cout << "GetItem(40): " << tree.GetItem(40) << endl;
    cout << "GetItem(90): " << tree.GetItem(90) << endl;

    // Delete a leaf.
    tree.DeleteItem(20);

    // Delete a node with one child (60 after 70 is removed).
    tree.DeleteItem(70);

    // Delete a node with two children.
    tree.DeleteItem(50);

    cout << "GetItem(50): " << tree.GetItem(50) << endl;
    cout << "GetItem(40): " << tree.GetItem(40) << endl;

    return 0;
}