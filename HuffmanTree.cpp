/*
 * File: HuffmanTree.cpp
 * Location: backend/src/HuffmanTree.cpp
 * Description: Implementation of Huffman Tree
 */

#include "HuffmanTree.h"

// Constructor
HuffmanTree::HuffmanTree() : m_root(nullptr) {}

// Build Huffman tree from character frequencies
void HuffmanTree::buildTree(const unordered_map<char, int>& frequencies) {
    PriorityQueueMin priorityQueue;
    
    // Create leaf nodes for each character and insert into priority queue
    for (const auto& pair : frequencies) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        priorityQueue.insert(node);
    }
    
    // Build tree by repeatedly combining two minimum frequency nodes
    while (priorityQueue.size() > 1) {
        HuffmanNode* left = priorityQueue.extractMin();
        HuffmanNode* right = priorityQueue.extractMin();
        
        // Create internal node with combined frequency
        int combinedFreq = left->frequency + right->frequency;
        HuffmanNode* internalNode = new HuffmanNode(combinedFreq, left, right);
        
        priorityQueue.insert(internalNode);
    }
    
    // The last remaining node is the root
    m_root = priorityQueue.extractMin();
}

// Generate Huffman codes for all characters
void HuffmanTree::generateHuffmanCodes() {
    m_huffmanCodes.clear();
    
    if (m_root != nullptr) {
        // Special case: single character (assign code "0")
        if (m_root->isLeaf()) {
            m_huffmanCodes[m_root->character] = "0";
        } else {
            generateCodes(m_root, "");
        }
    }
}

// Recursive helper to generate codes
void HuffmanTree::generateCodes(HuffmanNode* node, string code) {
    if (node == nullptr) return;
    
    // If leaf node, store the code
    if (node->isLeaf()) {
        m_huffmanCodes[node->character] = code.empty() ? "0" : code;
        return;
    }
    
    // Traverse left with '0' and right with '1'
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

// Encode text using generated Huffman codes
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

// Decode binary string using Huffman tree
string HuffmanTree::decode(const string& encodedText) {
    string decodedText = "";
    HuffmanNode* current = m_root;
    
    if (m_root == nullptr) {
        return decodedText;
    }
    
    // Special case: single character
    if (m_root->isLeaf()) {
        for (size_t i = 0; i < encodedText.length(); i++) {
            decodedText += m_root->character;
        }
        return decodedText;
    }
    
    // Traverse tree based on bits
    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }
        
        // If reached leaf, add character and reset to root
        if (current && current->isLeaf()) {
            decodedText += current->character;
            current = m_root;
        }
    }
    
    return decodedText;
}

// Serialize tree structure to file (pre-order traversal)
void HuffmanTree::serializeTree(HuffmanNode* node, ofstream& outFile) {
    if (node == nullptr) {
        // Write marker for null node
        char marker = '#';
        outFile.write(&marker, sizeof(char));
        return;
    }
    
    if (node->isLeaf()) {
        // Write marker for leaf node + character + frequency
        char marker = 'L';
        outFile.write(&marker, sizeof(char));
        outFile.write(&node->character, sizeof(char));
        outFile.write(reinterpret_cast<const char*>(&node->frequency), sizeof(int));
    } else {
        // Write marker for internal node + frequency, then recurse
        char marker = 'I';
        outFile.write(&marker, sizeof(char));
        outFile.write(reinterpret_cast<const char*>(&node->frequency), sizeof(int));
        serializeTree(node->left, outFile);
        serializeTree(node->right, outFile);
    }
}

// Deserialize tree structure from file
HuffmanNode* HuffmanTree::deserializeTree(ifstream& inFile) {
    char marker;
    inFile.read(&marker, sizeof(char));
    
    if (marker == '#') {
        return nullptr;
    }
    
    if (marker == 'L') {
        // Read leaf node data
        char character;
        int frequency;
        inFile.read(&character, sizeof(char));
        inFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));
        return new HuffmanNode(character, frequency);
    } else {
        // Read internal node and recurse for children
        int frequency;
        inFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));
        HuffmanNode* left = deserializeTree(inFile);
        HuffmanNode* right = deserializeTree(inFile);
        return new HuffmanNode(frequency, left, right);
    }
}

// Save tree to binary file
bool HuffmanTree::saveTreeToFile(const string& filename) {
    ofstream outFile(filename, ios::binary);
    
    if (!outFile.is_open()) {
        return false;
    }
    
    serializeTree(m_root, outFile);
    outFile.close();
    return true;
}

// Load tree from binary file
bool HuffmanTree::loadTreeFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    
    if (!inFile.is_open()) {
        return false;
    }
    
    // Delete existing tree
    deleteTree(m_root);
    
    // Deserialize tree from file
    m_root = deserializeTree(inFile);
    inFile.close();
    
    // Regenerate codes from loaded tree
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