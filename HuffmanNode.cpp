

#include "HuffmanNode.h"

HuffmanNode::HuffmanNode(char ch, int freq)
    : character(ch), frequency(freq), left(nullptr), right(nullptr) {}

HuffmanNode::HuffmanNode(int freq, HuffmanNode* l, HuffmanNode* r)
    : character('\0'), frequency(freq), left(l), right(r) {}

bool HuffmanNode::isLeaf() const {
    return (left == nullptr && right == nullptr);
}

HuffmanNode::~HuffmanNode() {}