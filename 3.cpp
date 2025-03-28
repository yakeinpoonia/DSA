#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function prototypes
TreeNode* insert(TreeNode* root, int value);
void deleteTree(TreeNode* root);
TreeNode* clone(TreeNode* root);
void mirror(TreeNode* root);
TreeNode* buildTreeHelper(vector<int>& preorder, vector<int>& inorder, int& preIndex, int inStart, int inEnd);
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);
TreeNode* deleteNode(TreeNode* root, int key);
bool isEqual(TreeNode* root1, TreeNode* root2);

// Recursive traversals
void preOrderRecursive(TreeNode* root) {
    if (!root) return;
    cout << root->data << " ";
    preOrderRecursive(root->left);
    preOrderRecursive(root->right);
}

void inOrderRecursive(TreeNode* root) {
    if (!root) return;
    inOrderRecursive(root->left);
    cout << root->data << " ";
    inOrderRecursive(root->right);
}

void postOrderRecursive(TreeNode* root) {
    if (!root) return;
    postOrderRecursive(root->left);
    postOrderRecursive(root->right);
    cout << root->data << " ";
}

// Iterative traversals
void preOrderIterative(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* curr = st.top();
        st.pop();
        cout << curr->data << " ";
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
}

void inOrderIterative(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top();
        st.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

void postOrderIterative(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        TreeNode* curr = st1.top();
        st1.pop();
        st2.push(curr);
        if (curr->left) st1.push(curr->left);
        if (curr->right) st1.push(curr->right);
    }
    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// Tree operations
int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

TreeNode* insert(TreeNode* root, int value) {
    if (!root) return new TreeNode(value);
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

TreeNode* clone(TreeNode* root) {
    if (!root) return nullptr;
    TreeNode* newRoot = new TreeNode(root->data);
    newRoot->left = clone(root->left);
    newRoot->right = clone(root->right);
    return newRoot;
}

void mirror(TreeNode* root) {
    if (!root) return;
    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
}

int findIndex(vector<int>& inorder, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) return i;
    }
    return -1;
}

TreeNode* buildTreeHelper(vector<int>& preorder, vector<int>& inorder, int& preIndex, int inStart, int inEnd) {
    if (inStart > inEnd) return nullptr;
    TreeNode* root = new TreeNode(preorder[preIndex++]);
    if (inStart == inEnd) return root;
    
    int inIndex = findIndex(inorder, inStart, inEnd, root->data);
    root->left = buildTreeHelper(preorder, inorder, preIndex, inStart, inIndex-1);
    root->right = buildTreeHelper(preorder, inorder, preIndex, inIndex+1, inEnd);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int preIndex = 0;
    return buildTreeHelper(preorder, inorder, preIndex, 0, inorder.size()-1);
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        
        TreeNode* temp = root->right;
        while (temp->left) temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

bool isEqual(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) return true;
    if (!root1 || !root2) return false;
    return (root1->data == root2->data) && 
           isEqual(root1->left, root2->left) && 
           isEqual(root1->right, root2->right);
}

int main() {
    TreeNode* root = nullptr;
    int n;
    
    cout << "Enter number of nodes for initial tree: ";
    cin >> n;
    cout << "Enter " << n << " values: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        root = insert(root, val);
    }

    int choice;
    do {
        cout << "\nMenu:\n"
             << "1. Insert node\n"
             << "2. All traversals\n"
             << "3. Find height\n"
             << "4. Clone tree & erase original\n"
             << "5. Mirror image\n"
             << "6. Construct from pre/in order\n"
             << "7. Delete node\n"
             << "8. Check equality\n"
             << "0. Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "Enter value: ";
                cin >> val;
                root = insert(root, val);
                break;
            }
            case 2: {
                cout << "\nRecursive Traversals:\n";
                cout << "Pre-order:  "; preOrderRecursive(root);
                cout << "\nIn-order:   "; inOrderRecursive(root);
                cout << "\nPost-order: "; postOrderRecursive(root);
                
                cout << "\n\nIterative Traversals:\n";
                cout << "Pre-order:  "; preOrderIterative(root);
                cout << "\nIn-order:   "; inOrderIterative(root);
                cout << "\nPost-order: "; postOrderIterative(root);
                cout << endl;
                break;
            }
            case 3:
                cout << "Tree height: " << height(root) << endl;
                break;
            case 4: {
                TreeNode* cloned = clone(root);
                deleteTree(root);
                root = cloned;
                cout << "Tree cloned and original erased!" << endl;
                break;
            }
            case 5:
                mirror(root);
                cout << "Tree mirrored!" << endl;
                break;
            case 6: {
                int size;
                cout << "Enter number of nodes: ";
                cin >> size;
                vector<int> pre(size), in(size);
                cout << "Enter pre-order: ";
                for (int i = 0; i < size; i++) cin >> pre[i];
                cout << "Enter in-order: ";
                for (int i = 0; i < size; i++) cin >> in[i];
                TreeNode* newRoot = buildTree(pre, in);
                deleteTree(root);
                root = newRoot;
                cout << "New tree constructed!" << endl;
                break;
            }
            case 7: {
                int val;
                cout << "Enter value to delete: ";
                cin >> val;
                root = deleteNode(root, val);
                break;
            }
            case 8: {
                cout << "Create comparison tree:\n";
                TreeNode* root2 = nullptr;
                int n2;
                cout << "Enter node count: ";
                cin >> n2;
                cout << "Enter values: ";
                for (int i = 0; i < n2; i++) {
                    int val;
                    cin >> val;
                    root2 = insert(root2, val);
                }
                cout << (isEqual(root, root2) ? "Trees are equal" : "Trees differ") << endl;
                deleteTree(root2);
                break;
            }
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    deleteTree(root);
    return 0;
}