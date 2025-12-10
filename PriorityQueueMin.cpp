
#include "PriorityQueueMin.h"

PriorityQueueMin::PQNode::PQNode(HuffmanNode* node) 
    : data(node), next(nullptr) {}

PriorityQueueMin::PriorityQueueMin() 
    : m_front(nullptr), m_size(0) {}

void PriorityQueueMin::insert(HuffmanNode* node) {
    PQNode* newNode = new PQNode(node);
    
    if (m_front == nullptr || node->frequency < m_front->data->frequency) {
        newNode->next = m_front;
        m_front = newNode;
    } else {
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

int PriorityQueueMin::size() const {
    return m_size;
}

bool PriorityQueueMin::isEmpty() const {
    return m_front == nullptr;
}

PriorityQueueMin::~PriorityQueueMin() {
    while (!isEmpty()) {
        PQNode* temp = m_front;
        m_front = m_front->next;
        delete temp;
    }
}