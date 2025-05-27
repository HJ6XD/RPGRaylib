#pragma once
#include "HeapNode.h"
#include <vector>
#include <iostream>
template<class T>
class Heap
{
	std::vector<HeapNode<&T>*> heap;

	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * i + 2; }

    void heapify_up(int i) {
        while (i > 0 && heap[i] > heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapify_down(int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (l < heap.size() && heap[l] > heap[largest]) largest = l;
        if (r < heap.size() && heap[r] > heap[largest]) largest = r;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify_down(largest);
        }
    }

public: 
    void insert(HeapNode<&T>* element) {
        heap.push_back(element);
        heapify_up(heap.size() - 1);
    }

    int extract() {
        if (heap.empty()) {
            std::count << "heap esta vacía" << std::endl;
            return nullptr;
        }
        int top = heap[0]->GetValue();
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
        return top;
    }

    int peek() const {
        if (heap.empty()) {
            std::count<<"heap esta vacía" << std::endl;
            return nullptr;
        }
        return heap[0];
    }

    bool is_empty() const {
        return heap.empty();
    }
};

