#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Node structure for Binary Search Tree (BST) and Threaded Binary Tree (TBT)
class BSTNode {
public:
    int data;
    BSTNode *left, *right;
    bool isLeftThread, isRightThread;
    
    BSTNode(int value) {
        data = value;
        left = right = nullptr;
        isLeftThread = isRightThread = true;
    }
};

// Function to insert a node into BST
void insertBST(BSTNode *&root, int value) {
    BSTNode *newNode = new BSTNode(value);
    if (!root) {
        root = newNode;
        return;
    }
    BSTNode *current = root;
    while (true) {
        if (value < current->data) {
            if (!current->left) {
                current->left = newNode;
                break;
            }
            current = current->left;
        } else {
            if (!current->right) {
                current->right = newNode;
                break;
            }
            current = current->right;
        }
    }
}

// Function to create BST from user input
BSTNode* createBST() {
    BSTNode *root = nullptr;
    int value;
    cout << "Enter numbers to insert into BST (-1 to stop): ";
    while (cin >> value && value != -1) {
        insertBST(root, value);
    }
    return root;
}

// Function to get inorder traversal of BST as a vector
vector<BSTNode*> getInorder(BSTNode *root) {
    vector<BSTNode*> inorderList;
    stack<BSTNode*> s;
    BSTNode *current = root;
    
    while (!s.empty() || current) {
        while (current) {
            s.push(current);
            current = current->left;
        }
        current = s.top(); s.pop();
        inorderList.push_back(current);
        current = current->right;
    }
    return inorderList;
}

// Function to convert BST to Threaded Binary Tree (TBT)
BSTNode* convertToTBT(BSTNode *&root, vector<BSTNode*> &inorderList) {
    BSTNode *dummy = new BSTNode(1000);
    dummy->left = root;
    dummy->isRightThread = false;
    dummy->right = dummy;

    // Adjust left and right pointers for threads
    inorderList[0]->left = dummy;
    inorderList[0]->isLeftThread = false;
    inorderList.back()->right = dummy;
    inorderList.back()->isRightThread = false;
    
    for (size_t i = 1; i < inorderList.size(); i++) {
        if (!inorderList[i]->left) {
            inorderList[i]->left = inorderList[i - 1];
            inorderList[i]->isLeftThread = false;
        }
        if (!inorderList[i - 1]->right) {
            inorderList[i - 1]->right = inorderList[i];
            inorderList[i - 1]->isRightThread = false;
        }
    }
    return dummy;
}

// Inorder traversal of TBT
void inorderTBT(BSTNode *dummy) {
    BSTNode *current = dummy->left;
    while (current != dummy) {
        while (current->isLeftThread)
            current = current->left;
        cout << current->data << " ";
        while (!current->isRightThread) {
            current = current->right;
            if (current == dummy) return;
            cout << current->data << " ";
        }
        current = current->right;
    }
    cout << endl;
}

// Preorder traversal of TBT
void preorderTBT(BSTNode *dummy) {
    BSTNode *current = dummy->left;
    while (current != dummy) {
        while (current->isLeftThread) {
            cout << current->data << " ";
            current = current->left;
        }
        cout << current->data << " ";
        while (!current->isRightThread) {
            current = current->right;
            if (current == dummy) return;
        }
        current = current->right;
    }
    cout << endl;
}

// Main function with menu
int main() {
    BSTNode *root = nullptr, *dummy = nullptr;
    vector<BSTNode*> inorderList;
    int choice;
    
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Create BST\n2. Convert BST to TBT\n3. Inorder traversal of TBT\n";
        cout << "4. Preorder traversal of TBT\n5. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                root = createBST();
                inorderList = getInorder(root);
                break;
            case 2:
                dummy = convertToTBT(root, inorderList);
                cout << "BST converted to TBT.\n";
                break;
            case 3:
                cout << "Inorder Traversal of TBT: ";
                inorderTBT(dummy);
                break;
            case 4:
                cout << "Preorder Traversal of TBT: ";
                preorderTBT(dummy);
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
