#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

// Parts of the Node class are sourced from "AVL Project Breakdown/Q&A Session"
// https://www.youtube.com/watch?v=BjH_Pdu_2W4

// The Node class represent one node in the AVL Tree
class Node {
    // Defining data types to be stored in the Node
    string name;
    string ufid;
    int height;
    Node* left;
    Node* right;

public:
    // Node constructor
    Node(string name, string ufid) : name(name), ufid(ufid), left(nullptr), right(nullptr) {}

    // Getters and setters
    string getName() const {return name;}
    string getUFID() const {return ufid;}
    Node* getLeft() const {return left;}
    Node* getRight() const {return right;}

    int getHeight() const {
        return 1 + max((left ? left->getHeight() : 0), (right ? right->getHeight() : 0));
    }
    int getBalanceFactor() const {
        return (left ? left->getHeight() : 0) - (right ? right->getHeight() : 0);
    }

    void setName(const string& newName) {name = newName;}
    void setUFID(const string& newUFID) {ufid = newUFID;}
    void setLeft(Node* newLeft) {left = newLeft;}
    void setRight(Node* newRight) {right = newRight;}
    void setHeight(int newHeight) {height = newHeight;}



    // Operator overloading for comparison
    bool operator<(const Node& other) const {
        int thisUFID = stoi(ufid);
        int otherUFID = stoi(other.ufid);
        return thisUFID < otherUFID;
    }

    bool operator>(const Node& other) const {
        int thisUFID = stoi(ufid);
        int otherUFID = stoi(other.ufid);
        return thisUFID > otherUFID;
    }

    bool operator==(const Node& other) const {
        int thisUFID = stoi(ufid);
        int otherUFID = stoi(other.ufid);
        return thisUFID == otherUFID;
    }
};

// The AVL Tree is made up of Nodes
class AVLTree {
private:
    // Defining data types and functions for the AVL Tree
    int height(Node* node);
    int balanceFactor(Node* node);
    Node* InsertHelper(Node* node, const string& name, const string& ufid);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);

    // Helper function to remove a Node with the specified ID
    Node* removeIDHelper(Node* node, const string& ufid);

    // Helper function to search for a Node with the specified ID
    Node* searchIDHelper(Node* node, const string& ufid);

    // Helper function to search for a Node with the specified name
    void searchNameHelper(Node* node, const string& name, bool& found);

public:
    // Constructs a Node as the root of the AVL Tree, default as nullptr
    Node* root;
    AVLTree() : root(nullptr) {}

    // Inserts a Node into the AVL Tree
    void Insert(const string& name, const string& ufid) {
        this->root = InsertHelper(this->root, name, ufid);
    }

    // Removes a Node with the specified ufid
    void removeID(const string& ufid) {
        root = removeIDHelper(root, ufid);
        if (root != nullptr) {
            cout << "successful" << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    // Searches the AVL Tree for a Node with the specified ufid
    void searchID(const string& ufid) {
        Node* result = searchIDHelper(root, ufid);
        if (result != nullptr) {
            cout << result->getName() << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    // Searches the AVL Tree for a Node with the specified name
    void searchName(const string& name) {
        bool found = false;
        searchNameHelper(root, name, found);
        if (!found) {
            cout << "unsuccessful" << endl;
        }
    }

    // Prints the AVL Tree Node by Node, inorder
    void printInorder(Node* node) {
        if (node == nullptr) return;
        printInorder(node->getLeft());
        cout << node->getName() << ",";
        printInorder(node->getRight());
    }

    // Prints the AVL Tree Node by Node, preorder
    void printPreorder(Node* node) {
        if (node == nullptr) return;
        cout << node->getName() << ",";
        printPreorder(node->getLeft());
        printPreorder(node->getRight());
    }

    // Prints the AVL Tree Node by Node, postorder
    void printPostorder(Node* node) {
        if (node == nullptr) return;
        printPostorder(node->getLeft());
        printPostorder(node->getRight());
        cout << node->getName() << ",";
    }

    // Prints the number of levels that exist in the AVL Tree
    void printLevelCount(Node* root) {
        // If the tree is empty, print 0 levels
        if (root == nullptr) {
            cout << "0" << endl;
            return;
        }

        // Creates a queue to perform the level-order traversal, and initializes levels to 0
        queue<Node*> q;
        q.push(root);
        int levels = 0;

        // Performs level-order traversal to count levels
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                Node* current = q.front();
                q.pop();
                if (current->getLeft()) q.push(current->getLeft());
                if (current->getRight()) q.push(current->getRight());
            }
            levels++;
        }

        cout << levels << endl;
    }

    // Removes the nth Node of the AVL Tree inorder
    bool removeNthInorder(Node* node, int& count, int n) {
        if (node == nullptr) return false;
        if (removeNthInorder(node->getLeft(), count, n)) return true;
        if (count == n) {
            // Remove the current node
            // Implement your removal logic here
            count++;
            return true;
        }
        count++;
        return removeNthInorder(node->getRight(), count, n);
    }

    // Wrapper for removeNthInorder
    void removeInorder(int n) {
        int count = 0;
        if (removeNthInorder(root, count, n)) {
            cout << "successful" << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }
};