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

    int CountPassengers();
    int CountSurvivors();
    void PrintSurvivors();
    void PrintClass(int pclass);
    int Depth(int pid);
    int Height();
    double AverageDepth();

private:
    TNode* root;

    void Insert(TNode*& curnode, Passenger newitem);
    int FindItem(TNode* curnode, Passenger gitem);
    void PrintNode(TNode*& curnode);

    // Additional helper for the destructor.
    void DestroyTree(TNode* curnode);

    int PassengerCount(TNode*& curnode);
    int SurvivorCount(TNode*& curnode);
    void ClassPrint(TNode*& curnode, int pclass);
    int TreeDepth(TNode*& curnode, int pid);
    int TreeHeight(TNode*& curnode);
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

int BST::CountPassengers()
{
    return PassengerCount(root);
}

int BST::PassengerCount(TNode*& curnode)
{
    int count = 0;

    if (curnode != nullptr) {
        count++;
        count += PassengerCount(curnode->left);
        count += PassengerCount(curnode->right);
    }
    return count;
}

int BST::CountSurvivors()
{
    return SurvivorCount(root);
}

int BST::SurvivorCount(TNode*& curnode)
{
    int count = 0;
    if (curnode != nullptr) {
        count += SurvivorCount(curnode->left);
        count += SurvivorCount(curnode->right);
        if (curnode->item.Survived == 1) {
            count++;
        }
    }
    return count;
}

void BST::PrintClass(int pclass)
{
    ClassPrint(root, pclass);
}

void BST::ClassPrint(TNode*& curnode, int pclass)
{
    if (curnode != nullptr) {
        ClassPrint(curnode->left, pclass);
        ClassPrint(curnode->right, pclass);
        if (curnode->item.Class == pclass) {
            cout << curnode->item.PassengerId << endl;
        }
    }
}

int BST::Depth(int pid)
{
    return TreeDepth(root, pid);
}

int BST::TreeDepth(TNode*& curnode, int pid)
{
    int depth = 0;

    if (curnode != nullptr) {
        if (curnode->item.PassengerId != pid) {
            if (pid < curnode->item.PassengerId) {
                depth = TreeDepth(curnode->left, pid);
            }
            else {
                depth = TreeDepth(curnode->right, pid);
            }
        }
        else {
            return 0;
        }
    }
    else {
        return -1;
    }
    if (depth == -1) {
        return -1;
    }
    return depth + 1;
}

int BST::Height()
{
    return TreeHeight(root);
}

int BST::TreeHeight(TNode*& curnode)
{
    int height = 0;
    int lHeight;
    int rHeight;
    int max;

    if (curnode != nullptr) {
        lHeight = TreeHeight(curnode->left);
        rHeight = TreeHeight(curnode->right);
    }
    else {
        return -1;
    }
    
    if (lHeight > rHeight) {
        max = lHeight;
    }
    else if (rHeight > lHeight) {
        max = rHeight;
    }
    else {
        max = lHeight;
    }
    return 1 + max;
}

// we use this to nicely format a passenger info
// make use of the iomanip library with setw to set width
void PrintPassenger(Passenger p) {
    cout << left
         << setw(12) << p.PassengerId
         << setw(10) << p.Survived
         << setw(8) << p.Class
         << setw(25) << p.LastName.substr(0, 24)
         << setw(8) << p.Gender.substr(0, 6)
         << right
         << setw(5) << p.Age
         << setw(12) << fixed << setprecision(2) << p.Fare
         << endl;
}

// header with passenger data columns labels
void PrintPassengerHeader() {
    cout << left
        << setw(12) << "PassengerId"
        << setw(10) << "Survived"
        << setw(8) << "Class"
        << setw(25) << "LastName"
        << setw(8) << "Gender"
        << right
        << setw(5) << "Age"
        << setw(12) << "Fare"
        << endl;
    // divider line of dashes
    cout << string(80, '-') << endl;
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

    // tree.PrintTree();
    
    // Passenger search;
    // search.PassengerId = 1000;
    // cout << tree.GetItem(search) << endl;

    // cout << tree.CountPassengers() << endl;

    // cout << tree.CountSurvivors() << endl;

    // tree.PrintClass(3);

    // cout << tree.Depth(846) << endl;
    // cout << tree.Depth(280) << endl;
    // cout << tree.Depth(747) << endl;
    // cout << tree.Depth(309) << endl;
    // cout << tree.Depth(41) << endl;

    cout << tree.Height() << endl;

    return 0;
}