#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP
#include <climits>
#include <iostream>

#include "vector.hpp"
using namespace std;

class MaxHeap {
   public:
    Vector<int> heap;
    MaxHeap(int capacity = 100);

    void heapify(int);

    int parent(int i);
    int left(int i);
    int right(int i);
    int top();
    int extractMax();

    void insert(int k);

    void printArray();
    int size() const;
    int capacity() const;
};

#endif