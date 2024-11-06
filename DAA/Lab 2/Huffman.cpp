#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Node {
public:
    int val;
    string symbol;
    string huffman;
    Node* left;
    Node* right;

    Node(int val, string symbol) : val(val), symbol(symbol), huffman(""), left(nullptr), right(nullptr) {}
};

// Comparator function to be used with priority_queue
struct CompareNodes {
    bool operator()(Node* a, Node* b) {
        return a->val > b->val;
    }
};

Node* buildHuffmanTree(const vector<string>& characters, const vector<int>& frequencies) {
    // Using the comparator with priority_queue
    priority_queue<Node*, vector<Node*>, CompareNodes> nodes;

    for (size_t i = 0; i < characters.size(); ++i) {
        nodes.push(new Node(frequencies[i], characters[i]));
    }

    while (nodes.size() > 1) {
        Node* left = nodes.top();
        nodes.pop();
        Node* right = nodes.top();
        nodes.pop();

        left->huffman = "0";
        right->huffman = "1";
        
        Node* newNode = new Node(left->val + right->val, left->symbol + right->symbol);
        newNode->left = left;
        newNode->right = right;
        nodes.push(newNode);
    }

    return nodes.top();
}

void traverse(Node* node, const string& currentCode, unordered_map<string, int>& huffmanDecimal) {
    if (!node->left && !node->right) {
        huffmanDecimal[node->symbol] = stoi(currentCode, nullptr, 2);
    } else {
        if (node->left) {
            traverse(node->left, currentCode + node->left->huffman, huffmanDecimal);
        }
        if (node->right) {
            traverse(node->right, currentCode + node->right->huffman, huffmanDecimal);
        }
    }
}

void printHuffmanCodes(Node* root) {
    unordered_map<string, int> huffmanDecimal;
    traverse(root, "", huffmanDecimal);
    cout << "Huffman Codes (Decimal):" << endl;
    for (const auto& entry : huffmanDecimal) {
        cout << entry.first << " -> " << entry.second << endl;
    }
}

int main() {
    cout << "Enter characters (separated by space): ";
    string inputChars;
    getline(cin, inputChars);
    vector<string> characters;
    size_t pos = 0;
    while ((pos = inputChars.find(" ")) != string::npos) {
        characters.push_back(inputChars.substr(0, pos));
        inputChars.erase(0, pos + 1);
    }
    characters.push_back(inputChars);  // Last character

    cout << "Enter corresponding frequencies (separated by space): ";
    string inputFreqs;
    getline(cin, inputFreqs);
    vector<int> frequencies;
    size_t pos2 = 0;
    while ((pos2 = inputFreqs.find(" ")) != string::npos) {
        frequencies.push_back(stoi(inputFreqs.substr(0, pos2)));
        inputFreqs.erase(0, pos2 + 1);
    }
    frequencies.push_back(stoi(inputFreqs));  // Last frequency

    Node* root = buildHuffmanTree(characters, frequencies);
    printHuffmanCodes(root);

    return 0;
}
