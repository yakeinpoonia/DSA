#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// Huffman Tree Node
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Custom comparator for priority queue (Min-Heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;  // Min-heap based on frequency
    }
};

// Function to generate Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    // Leaf node - store the code
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    // Traverse left (add '0') and right (add '1')
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Function to build Huffman Tree and return root
Node* buildHuffmanTree(unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Insert all characters into the priority queue
    for (auto pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build the tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // Merge two nodes
        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    return pq.top();  // Root of Huffman tree
}

// Function to encode a string
string encodeString(string text, unordered_map<char, string>& huffmanCode) {
    string encodedString = "";
    for (char ch : text) {
        encodedString += huffmanCode[ch];
    }
    return encodedString;
}

// Function to decode a bit sequence using the Huffman tree
string decodeString(Node* root, string encodedText) {
    string decodedString = "";
    Node* current = root;
    
    for (char bit : encodedText) {
        current = (bit == '0') ? current->left : current->right;

        // If a leaf node is reached, append the character and reset to root
        if (!current->left && !current->right) {
            decodedString += current->ch;
            current = root;
        }
    }

    return decodedString;
}

// Main Function
int main() {
    unordered_map<char, int> freqMap;
    int n;

    // Input character frequencies
    cout << "Enter the number of unique characters: ";
    cin >> n;
    
    cout << "Enter character and its frequency:\n";
    for (int i = 0; i < n; i++) {
        char ch;
        int freq;
        cin >> ch >> freq;
        freqMap[ch] = freq;
    }

    // Build Huffman Tree
    Node* root = buildHuffmanTree(freqMap);

    // Generate Huffman codes
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Display Huffman codes
    cout << "\nHuffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Encoding
    cout << "\nEnter a string to encode: ";
    string text;
    cin >> text;
    
    string encodedText = encodeString(text, huffmanCode);
    cout << "Encoded String: " << encodedText << endl;

    // Decoding
    cout << "\nEnter a binary sequence to decode: ";
    string encodedInput;
    cin >> encodedInput;

    string decodedText = decodeString(root, encodedInput);
    cout << "Decoded String: " << decodedText << endl;

    return 0;
}
