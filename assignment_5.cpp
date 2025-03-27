#include<bits/stdc++.h>
using namespace std;

struct Node{
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq){
        this->ch = ch;
        this->freq = freq;
        left = right = nullptr;
    }
};

struct Compare{
    bool operator()(Node* a, Node* b){
        return a->freq > b->freq;
    }
};


Node* build_huffman_tree(unordered_map<char, int>& freqmap){
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for(auto pair:freqmap){
        pq.push(new Node(pair.first, pair.second));
    }

    while(pq.size() > 1){
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    return pq.top();
}


void generate_code(Node* root, string code, unordered_map<char, string>& huffmancode){
    if(!root) return;

    if(!root->left && !root->right){
        huffmancode[root->ch] = code;
    }

    generate_code(root->left, code + "0", huffmancode);
    generate_code(root->right, code + "1", huffmancode);
}

string encodeString(string text, unordered_map<char, string>& huffmancode){
    string encodedString = "";
    for(char ch:text){
        encodedString += huffmancode[ch];
    }
    return encodedString;
}
