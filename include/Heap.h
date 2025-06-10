#pragma once
#include "HeapNode.h"
#include <vector>
#include <iostream>
//#include <>
template<class T>
class Heap
{
	std::vector<HeapNode<T>> heap;

	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * i + 2; }

    void heapify_up(int i) {
       //while (i > 0 && heap[i].GetValue() > heap[parent(i)].GetValue()) {
            //std::swap(heap[i], heap[parent(i)]);
            //i = parent(i);
        //}
    }

    void heapify_down(int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (l < heap.size() && heap[l].GetValue() > heap[largest].GetValue()) largest = l; 
        if (r < heap.size() && heap[r].GetValue() > heap[largest].GetValue()) largest = r;

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapify_down(largest);
        }
    }



public: 
    Heap() {
        //heap = new std::vector<HeapNode<T> >();
    }

    void insert(T element, int val) {
        HeapNode<T>* hn = new HeapNode<T>(&element, val);
        heap.push_back(*hn);
        heapify_up(heap.size() - 1);
    }

    T extract() {
        std::cout << "extrayendo" << std::endl;

        if (heap.empty()) {
            std::cout << "heap esta vacía" << std::endl;
            return T();
        }
        T* top = heap.at(0).GetData();
        
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
        return *top;
    }

    int peek() const {
        if (heap.empty()) {
            std::count<<"heap esta vacía" << std::endl;
            return nullptr;
        }
        return heap.at(0);
    }

    bool is_empty() const {
        return heap.empty();
    }
};

