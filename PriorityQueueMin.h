

#ifndef PRIORITY_QUEUE_MIN_H
#define PRIORITY_QUEUE_MIN_H

#include "HuffmanNode.h"

class PriorityQueueMin {
private:
    struct PQNode {
        HuffmanNode* data;
        PQNode* next;
        
        PQNode(HuffmanNode* node);
    };
    
    PQNode* m_front;
    int m_size;
    
public:
    
    PriorityQueueMin();
    
    void insert(HuffmanNode* node);
    
    HuffmanNode* extractMin();
    
    int size() const;
    
    bool isEmpty() const;
    
    ~PriorityQueueMin();
};

#endif