#pragma once
#include "HeapNode.h"
#include <vector>
#include <iostream>
//#include <>
//macro to print pointers in hex format
#define PRINT_POINTER(p) std::showbase << std::hex << reinterpret_cast<uintptr_t>(p) << std::dec

template<class T>
class Heap
{
    std::vector<HeapNode<T>> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapify_up(int i) {
        while (i > 0 && heap[parent(i)].GetValue() < heap[i].GetValue()) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
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
        //inicializar heap
        heap.reserve(10);
        std::cout << "Heap creado: " << heap.size() << std::endl;
    }

    void insert(T element, int val) {
        HeapNode<T>* hn = new HeapNode<T>(element, val);
        std::cout << "insertando " << PRINT_POINTER(hn) << std::endl;
        std::cout << "data: " << PRINT_POINTER(hn->GetData()) << std::endl;
        heap.push_back(*hn);
        heapify_up(heap.size() - 1);
    }

    T extract() {
        std::cout << "extrayendo" << std::endl;

        if (heap.empty()) {
            std::cout << "heap esta vacía" << std::endl;
            return T();
        }
        const T* top = heap.at(0).GetData();

        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
        return *top;
    }

    const T* peek() const {
        if (heap.empty()) {
            return nullptr;
        }
        return heap.at(0).GetData();
    }

    bool is_empty() const {
        return heap.empty();
    }

    //itera en todos los elementos del heap, para debuggear
    void print() const {
        std::cout << "Heap contiene: " << heap.size() << "elementos" << std::endl;
        if (heap.empty())return;

        std::cout << "|INDEX\t" << "|NODEDATA\t" << "|NODEVAL\t" << "|ADDRESS\t" << std::endl;
        for (size_t i = 0; i < heap.size(); i++)
        {
            const T* data = heap[i].GetData();
            std::cout
                << i << "\t|"
                << *data << "\t\t|"
                << heap[i].GetValue() << "\t\t|"
                << std::showbase << std::hex << reinterpret_cast<uintptr_t>(data) << std::dec
                << std::endl;
        }
    }
};

