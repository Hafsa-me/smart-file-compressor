
#include "HuffmanTree.h"

HuffmanTree::HuffmanTree() : m_root(nullptr) {}

void HuffmanTree::buildTree(const unordered_map<char, int>& frequencies) {
    PriorityQueueMin priorityQueue;
    
    for (const auto& pair : frequencies) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        priorityQueue.insert(node);
    }
    
    while (priorityQueue.size() > 1) {
        HuffmanNode* left = priorityQueue.extractMin();
        HuffmanNode* right = priorityQueue.extractMin();
        
        int combinedFreq = left->frequency + right->frequency;
        HuffmanNode* internalNode = new HuffmanNode(combinedFreq, left, right);
        
        priorityQueue.insert(internalNode);
    }
    
    m_root = priorityQueue.extractMin();
}

void HuffmanTree::generateHuffmanCodes() {
    m_huffmanCodes.clear();
    
    if (m_root != nullptr) {
        if (m_root->isLeaf()) {
            m_huffmanCodes[m_root->character] = "0";
        } else {
            generateCodes(m_root, "");
        }
    }
}

void HuffmanTree::generateCodes(HuffmanNode* node, string code) {
    if (node == nullptr) return;
    
    if (node->isLeaf()) {
        m_huffmanCodes[node->character] = code.empty() ? "0" : code;
        return;
    }
    
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

string HuffmanTree::encode(const string& text) {
    string encodedText = "";
    
    for (int i=0; i<text.length(); i++ ) {
        char ch = text[i];
        if (m_huffmanCodes.find(ch) != m_huffmanCodes.end()) {
            encodedText += m_huffmanCodes[ch];
        }
    }
    
    return encodedText;
}

string HuffmanTree::decode(const string& encodedText) {
    string decodedText = "";
    HuffmanNode* current = m_root;
    
    if (m_root == nullptr) {
        return decodedText;
    }
    
    if (m_root->isLeaf()) {
        for (size_t i = 0; i < encodedText.length(); i++) {
            decodedText += m_root->character;
        }
        return decodedText;
    }
    
    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }
        
        if (current && current->isLeaf()) {
            decodedText += current->character;
            current = m_root;
        }
    }
    
    return decodedText;
}

void HuffmanTree::serializeTree(HuffmanNode* node, ofstream& outFile) {
    if (node == nullptr) {
        char marker = '#';
        outFile.write(&marker, sizeof(char));
        return;
    }
    
    if (node->isLeaf()) {
        char marker = 'L';
        outFile.write(&marker, sizeof(char));
        outFile.write(&node->character, sizeof(char));
        outFile.write(reinterpret_cast<const char*>(&node->frequency), sizeof(int));
    } else {
        char marker = 'I';
        outFile.write(&marker, sizeof(char));
        outFile.write(reinterpret_cast<const char*>(&node->frequency), sizeof(int));
        serializeTree(node->left, outFile);
        serializeTree(node->right, outFile);
    }
}

HuffmanNode* HuffmanTree::deserializeTree(ifstream& inFile) {
    char marker;
    inFile.read(&marker, sizeof(char));
    
    if (marker == '#') {
        return nullptr;
    }
    
    if (marker == 'L') {
        char character;
        int frequency;
        inFile.read(&character, sizeof(char));
        inFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));
        return new HuffmanNode(character, frequency);
    } else {
        int frequency;
        inFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));
        HuffmanNode* left = deserializeTree(inFile);
        HuffmanNode* right = deserializeTree(inFile);
        return new HuffmanNode(frequency, left, right);
    }
}

bool HuffmanTree::saveTreeToFile(const string& filename) {
    ofstream outFile(filename, ios::binary);
    
    if (!outFile.is_open()) {
        return false;
    }
    
    serializeTree(m_root, outFile);
    outFile.close();
    return true;
}

bool HuffmanTree::loadTreeFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    
    if (!inFile.is_open()) {
        return false;
    }
    
    deleteTree(m_root);
    
    m_root = deserializeTree(inFile);
    inFile.close();
    
    generateHuffmanCodes();
    return true;
}

// Get generated Huffman codes
unordered_map<char, string> HuffmanTree::getCodes() const {
    return m_huffmanCodes;
}

// Recursively delete tree
void HuffmanTree::deleteTree(HuffmanNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Destructor
HuffmanTree::~HuffmanTree() {
    deleteTree(m_root);
    m_root = nullptr;
}