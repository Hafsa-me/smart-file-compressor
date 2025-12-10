/*
 * File: PriorityQueueMin.cpp
 * Location: backend/src/PriorityQueueMin.cpp
 * Description: Implementation of Priority Queue using linked list
 */

#include "PriorityQueueMin.h"

// PQNode constructor
PriorityQueueMin::PQNode::PQNode(HuffmanNode* node) 
    : data(node), next(nullptr) {}

// PriorityQueueMin constructor
PriorityQueueMin::PriorityQueueMin() 
    : m_front(nullptr), m_size(0) {}

// Insert node maintaining sorted order (ascending by frequency)
void PriorityQueueMin::insert(HuffmanNode* node) {
    PQNode* newNode = new PQNode(node);
    
    // Insert at front if empty or new node has smallest frequency
    if (m_front == nullptr || node->frequency < m_front->data->frequency) {
        newNode->next = m_front;
        m_front = newNode;
    } else {
        // Find correct position to maintain sorted order
        PQNode* current = m_front;
        
        while (current->next != nullptr && 
               current->next->data->frequency < node->frequency) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
    }
    
    m_size++;
}

// Extract and return node with minimum frequency
HuffmanNode* PriorityQueueMin::extractMin() {
    if (isEmpty()) {
        return nullptr;
    }
    
    PQNode* temp = m_front;
    HuffmanNode* minNode = m_front->data;
    
    m_front = m_front->next;
    delete temp;
    m_size--;
    
    return minNode;
}

// Get current size of priority queue
int PriorityQueueMin::size() const {
    return m_size;
}

// Check if priority queue is empty
bool PriorityQueueMin::isEmpty() const {
    return m_front == nullptr;
}

// Destructor - clean up all nodes
PriorityQueueMin::~PriorityQueueMin() {
    while (!isEmpty()) {
        PQNode* temp = m_front;
        m_front = m_front->next;
        delete temp;
    }
}