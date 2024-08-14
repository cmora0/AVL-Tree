#include "AVL.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


// Helper function to insert a Node into the AVL Tree
Node* AVLTree::InsertHelper(Node* node, const string& name, const string& ufid) {
    // Base case: If the current node is null, creates a new node with the given data
    if (node == nullptr)
        return new Node(name, ufid);

    // Inserts data according to BST property
    if (ufid < node->getUFID())
        node->setLeft(InsertHelper(node->getLeft(), name, ufid));
    else if (ufid > node->getUFID())
        node->setRight(InsertHelper(node->getRight(), name, ufid));
    else
        return node;

    // Updates the height of the current node
    node->setHeight(node->getHeight());

    // Calculates the balance factor for the current node
    int balance = balanceFactor(node);

    // Performs rotations if necessary to maintain AVL balance
    // Left-Left case: Performs right rotation
    if (balance > 1 && ufid < node->getLeft()->getUFID())
        return rotateRight(node);

    // Right-Right case: Performs left rotation
    if (balance < -1 && ufid > node->getRight()->getUFID())
        return rotateLeft(node);

    // Left-Right case: Performs left-right rotation
    if (balance > 1 && ufid > node->getLeft()->getUFID()) {
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }

    // Right-Left case: Performs right-left rotation
    if (balance < -1 && ufid < node->getRight()->getUFID()) {
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }

    // If not rotation is needed returns the node.
    return node;
};

// Helper function to remove a Node with a given ufid
Node* AVLTree::removeIDHelper(Node* node, const string& ufid) {
    // Base case
    if (node == nullptr) {
        return nullptr;
    }

    // Traverses AVL Tree recursively to remove Node
    if (ufid < node->getUFID()) {
        node->setLeft(removeIDHelper(node->getLeft(), ufid));
    } else if (ufid > node->getUFID()) {
        node->setRight(removeIDHelper(node->getRight(), ufid));
    } else {
        // Once the Node is found, performs the removal
        if (node->getLeft() == nullptr) {
            Node* temp = node->getRight();
            delete node;
            // Updates the node pointer
            return temp;

        } else if (node->getRight() == nullptr) {
            Node* temp = node->getLeft();
            delete node;
            // Updates the node pointer
            return temp;
        } else {
            // If the Node has two children, finds the inorder successor
            Node* parent = node;
            Node* successor = node->getRight();
            while (successor->getLeft() != nullptr) {
                parent = successor;
                successor = successor->getLeft();
            }
            // Copies data from successor to node
            node->setName(successor->getName());
            node->setUFID(successor->getUFID());
            // Recursively removes the successor node
            if (parent == node) {
                parent->setRight(successor->getRight());
            } else {
                parent->setLeft(successor->getRight());
            }
            delete successor;
        }
    }

    // Updates height of the current node
    node->setHeight(node->getHeight());

    return node;
};

// Helper function to find a Node with a given ufid
Node* AVLTree::searchIDHelper(Node* node, const string& ufid) {
    if (node == nullptr) {
        return nullptr;
    }

    // Base case
    if (node->getUFID() == ufid) {
        return node;
    // Recursively traverses AVL Tree to find node
    } else if (ufid < node->getUFID()) {
        return searchIDHelper(node->getLeft(), ufid);
    } else {
        return searchIDHelper(node->getRight(), ufid);
    }
};

// Helper function to find a Node with a given name
void AVLTree::searchNameHelper(Node* node, const string& name, bool& found) {
    if (node == nullptr) {
        return;
    }

    if (node->getName() == name) {
        cout << node->getUFID() << endl;
        found = true;
    }

    searchNameHelper(node->getLeft(), name, found);
    searchNameHelper(node->getRight(), name, found);
};

// Function to check if a subtree is balanced
bool isAVL(Node* root) {
    if (root == nullptr)
        return true;

    int leftHeight = root->getLeft() ? root->getLeft()->getHeight() : 0;
    int rightHeight = root->getRight() ? root->getRight()->getHeight() : 0;

    if (abs(leftHeight - rightHeight) <= 1 && isAVL(root->getLeft()) && isAVL(root->getRight()))
        return true;

    return false;
};

// Main function
int main() {
    // Creating an AVLTree object
    AVLTree t;

    // Initializing input into numCommands
    int numCommands;
    cin >> numCommands;
    // Ignores the newline character
    cin.ignore();

    // Reads in the entire input
    for (int i = 0; i < numCommands; ++i) {
        string line;
        getline(cin, line);

        // Converts an input line into a variable.
        istringstream in(line);
        string command;
        in >> command;

        // Inserts a node
        if (command == "insert") {
            string name, ufid;
            char quote;
            // Reads the opening quotation mark
            in >> quote;

            // Reads in the name and ufid and prints whether successful or not
            getline(in, name, '"');
            in >> ufid;

            // Checks if the ufid has exactly 8 digits
            if (ufid.length() != 8 || ufid.find_first_not_of("0123456789") != string::npos) {
                cout << "unsuccessful" << endl;
                continue;
            }

            // Inserts if ufid is valid
            t.Insert(name, ufid);
            cout << "successful" << endl;

        // Prints AVLTree inorder    
        } else if (command == "printInorder") {
            t.printInorder(t.root);
            cout << endl;

        // Prints AVLTree preorder    
        } else if (command == "printPreorder") {
            t.printPreorder(t.root);
            cout << endl;

        // Prints AVLTree postorder   
        } else if (command == "printPostorder") {
            t.printPostorder(t.root);
            cout << endl;

        // Removes a particular node given a ufid
        } else if (command == "remove") {
            string ufid;
            in >> ufid;
            t.removeID(ufid);

        // Removes the nth node inorder
        } else if (command == "removeInorder") {
            int n;
            in >> n;
            t.removeInorder(n);
        }
    }

    return 0;
}