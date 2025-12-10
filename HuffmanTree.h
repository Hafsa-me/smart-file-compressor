

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
    
    void deleteTree(HuffmanNode* node);
    void generateCodes(HuffmanNode* node, string code);
    void serializeTree(HuffmanNode* node, ofstream& outFile);
    HuffmanNode* deserializeTree(ifstream& inFile);
    
public:
    HuffmanTree();
    
    void buildTree(const unordered_map<char, int>& frequencies);
    
    void generateHuffmanCodes();
    
    string encode(const string& text);
    
    string decode(const string& encodedText);
    
    bool saveTreeToFile(const string& filename);
    
    bool loadTreeFromFile(const string& filename);
    
    unordered_map<char, string> getCodes() const;
    
    ~HuffmanTree();
};

#endif