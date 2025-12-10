/*
 * File: HuffmanNode.h
 * Location: backend/include/HuffmanNode.h
 * Description: Node structure for Huffman Tree
 */

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

class HuffmanNode {
public:
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    // Constructor for leaf node
    HuffmanNode(char ch, int freq);
    
    // Constructor for internal node
    HuffmanNode(int freq, HuffmanNode* l, HuffmanNode* r);
    
    // Check if node is a leaf
    bool isLeaf() const;
    
    // Destructor
    ~HuffmanNode();
};

#endif