/*
 * File: HuffmanTree.h
 * Location: backend/include/HuffmanTree.h
 * Description: Huffman Tree class for encoding and decoding
 */

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "HuffmanNode.h"
#include "PriorityQueueMin.h"
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

class HuffmanTree {
private:
    HuffmanNode* m_root;
    unordered_map<char, string> m_huffmanCodes;
    
    // Helper functions
    void deleteTree(HuffmanNode* node);
    void generateCodes(HuffmanNode* node, string code);
    void serializeTree(HuffmanNode* node, ofstream& outFile);
    HuffmanNode* deserializeTree(ifstream& inFile);
    
public:
    // Constructor
    HuffmanTree();
    
    // Build tree from frequency map
    void buildTree(const unordered_map<char, int>& frequencies);
    
    // Generate Huffman codes for all characters
    void generateHuffmanCodes();
    
    // Encode text to binary string
    string encode(const string& text);
    
    // Decode binary string to text
    string decode(const string& encodedText);
    
    // Save tree structure to file
    bool saveTreeToFile(const string& filename);
    
    // Load tree structure from file
    bool loadTreeFromFile(const string& filename);
    
    // Get generated Huffman codes
    unordered_map<char, string> getCodes() const;
    
    // Destructor
    ~HuffmanTree();
};

#endif