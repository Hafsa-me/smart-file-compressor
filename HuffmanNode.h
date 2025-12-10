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
    
    HuffmanNode(char ch, int freq);
    
    HuffmanNode(int freq, HuffmanNode* l, HuffmanNode* r);
    
    bool isLeaf() const;
    
    ~HuffmanNode();
};

#endif