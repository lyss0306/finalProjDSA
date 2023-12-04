#ifndef UNTITLED2_MAXHEAP_H
#define UNTITLED2_MAXHEAP_H



#include <iostream>
#include <vector>

#include "readcsv.h"


class MaxHeap {
private:
    std::vector<GameNode> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].similarity > heap[parent].similarity) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heap.size() && heap[leftChild].similarity > heap[largest].similarity) {
            largest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild].similarity > heap[largest].similarity) {
            largest = rightChild;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void push(const GameNode& node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    void pushVector(const std::vector<GameNode>& nodes) {
        for (const auto& node : nodes) {
            push(node);
        }
    }

    void pop() {
        if (!heap.empty()) {
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);
        }
    }

    const GameNode& top() const {

        return heap[0];

    }
};



#endif //UNTITLED2_MAXHEAP_H
