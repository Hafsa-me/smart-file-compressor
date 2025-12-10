/*
 * File: HuffmanNode.cpp
 * Location: backend/src/HuffmanNode.cpp
 * Description: Implementation of HuffmanNode class
 */

#include "HuffmanNode.h"

// Constructor for leaf node
HuffmanNode::HuffmanNode(char ch, int freq)
    : character(ch), frequency(freq), left(nullptr), right(nullptr) {}

// Constructor for internal node
HuffmanNode::HuffmanNode(int freq, HuffmanNode* l, HuffmanNode* r)
    : character('\0'), frequency(freq), left(l), right(r) {}

// Check if node is a leaf
bool HuffmanNode::isLeaf() const {
    return (left == nullptr && right == nullptr);
}

// Destructor
HuffmanNode::~HuffmanNode() {}