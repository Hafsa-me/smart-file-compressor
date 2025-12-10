/*
 * File: PriorityQueueMin.h
 * Location: backend/include/PriorityQueueMin.h
 * Description: Priority Queue implementation using linked list
 */

#ifndef PRIORITY_QUEUE_MIN_H
#define PRIORITY_QUEUE_MIN_H

#include "HuffmanNode.h"

class PriorityQueueMin {
private:
    // Node structure for priority queue linked list
    struct PQNode {
        HuffmanNode* data;
        PQNode* next;
        
        PQNode(HuffmanNode* node);
    };
    
    PQNode* m_front;
    int m_size;
    
public:
    // Constructor
    PriorityQueueMin();
    
    // Insert node into priority queue
    void insert(HuffmanNode* node);
    
    // Extract minimum frequency node
    HuffmanNode* extractMin();
    
    // Get size
    int size() const;
    
    // Check if empty
    bool isEmpty() const;
    
    // Destructor
    ~PriorityQueueMin();
};

#endif