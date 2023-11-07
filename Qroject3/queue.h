#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdexcept>
#include <cstdint>

using namespace std;

const uint32_t
    QUEUE_SIZE = 16;

template <typename QueueType>
class Queue {
public:
    Queue() {
        data = new QueueType[QUEUE_SIZE];
        capacity = QUEUE_SIZE;
        count = tail = 0;
        head = QUEUE_SIZE - 1;
    }
  
    ~Queue() { delete[] data; }
  
    void clear() { count = tail = 0; head = QUEUE_SIZE - 1; }
  
    uint32_t size() { return count; }
    bool isEmpty() { return count == 0; }

    void enqueue(const QueueType &d) {

        // out of space? make more space!
        // NOTE: STACK_SIZE is now capacity 
        if (count == capacity) {
            int
                tmpCap = 2 * capacity;
            QueueType
                *tmpData = new QueueType[tmpCap];
                
            // this shouldn't happen in practice 
            if (tmpData == nullptr)
                throw std::overflow_error("Stack is full");

            // copy data from old array into new array 
            for (int i = 0; i < capacity; i++)
                tmpData[i] = data[(head + i + 1) % capacity];
            
            head = tmpCap - 1;
            tail = capacity;
                
            // toss the old array
            delete[] data;

            // remember the new array and its capacity 
            data = tmpData;
            capacity = tmpCap;
        }

        data[tail] = d;
        tail = ++tail % capacity;
        count++;
    }

    QueueType dequeue() {
  
        if (count == 0)
            throw underflow_error("Queue is empty");

        head = ++head % capacity;

        count--;

        return data[head];
    }

private:
    QueueType
        *data;
    
    uint32_t
        head,tail,
        count, capacity;
};

#endif
