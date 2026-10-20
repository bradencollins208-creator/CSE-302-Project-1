#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Passenger
{
    int PassengerId;
    int Survived;
    int Class;
    string LastName;
    string Gender;
    int Age;
    double Fare;
};

struct TNode
{
public:
    Passenger item;
    TNode* left;
    TNode* right;
};

class BST 
{
public:
    BST();

    // Added to release dynamically allocated nodes.
    ~BST();

    int GetItem(Passenger gitem);
    void PutItem(Passenger newitem);
    void PrintTree();

private:
    TNode* root;

    void Insert(TNode*& curnode, Passenger newitem);
    int FindItem(TNode* curnode, Passenger gitem);
    void PrintNode(TNode*& curnode);

    // Additional helper for the destructor.
    void DestroyTree(TNode* curnode);
};

BST::BST()
{
    root = nullptr;
}

int BST::GetItem(Passenger gitem)
{
    return FindItem(root, gitem);
}

void BST::PutItem(Passenger newitem)
{
    Insert(root, newitem);
}

void BST::PrintTree()
{
    PrintNode(root);
}

int BST::FindItem(TNode* curnode, Passenger gitem)
{
    if (curnode == nullptr) 
        return -1;  
    else if (gitem.PassengerId == curnode->item.PassengerId) 
        return curnode->item.PassengerId;
    else if (gitem.PassengerId < curnode->item.PassengerId) 
        return FindItem(curnode->left, gitem);
    else
        return FindItem(curnode->right, gitem);
}

void BST::Insert(TNode*& curnode, Passenger newitem)
{
    if (curnode == nullptr) {
        curnode = new TNode;
        curnode->item = newitem;
        curnode->left = nullptr;
        curnode->right = nullptr;
    }
    else if (newitem.PassengerId < curnode->item.PassengerId) {
        Insert(curnode->left, newitem);
    }
    else if (newitem.PassengerId > curnode->item.PassengerId) {
        Insert(curnode->right, newitem);
    }

    // else: newitem == curnode->item, do nothing.
}

void BST::PrintNode(TNode*& curnode)
{
    if (curnode != nullptr) {
        PrintNode(curnode->left);
        cout << curnode->item.PassengerId << ", ";
        PrintNode(curnode->right);
    }
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

int main()
{
    BST tree;

    // int count = 0; 
    // const int MAX_PASSENGERS = 1000;
    // Passenger passengers[MAX_PASSENGERS];
    Passenger passenger;
    string line, field;

    // open titanic.csv as an input file string called "infile"
    ifstream infile("titanic.csv");
    if (!infile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    getline(infile, line);

    while (getline(infile, line) /*&& count < MAX_PASSENGERS*/) 
    {
        stringstream ss(line);

        getline(ss, field, ',');
        passenger.PassengerId = stoi(field);
        getline(ss, field, ',');
        passenger.Survived = stoi(field);
        getline(ss, field, ',');
        passenger.Class = stoi(field);
        getline(ss, passenger.LastName, ',');
        getline(ss, passenger.Gender, ',');
        getline(ss, field, ',');
        passenger.Age = stoi(field);
        getline(ss, field, ',');
        passenger.Fare = stod(field);

        tree.PutItem(passenger);

        //count++;
    }

    infile.close();

    //tree.PrintTree();
    
    // Passenger search;
    // search.PassengerId = 1000;
    // cout << tree.GetItem(search) << endl;

    return 0;
}