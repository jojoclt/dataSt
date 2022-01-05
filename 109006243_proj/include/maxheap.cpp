#include "maxheap.hpp"

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
int MaxHeap::parent(int i) { return (i - 1) >> 1; }
int MaxHeap::left(int i) { return (i + 1) << 1; }
int MaxHeap::right(int i) { return (i + 2) << 1; }
int MaxHeap::top() { return heap[0]; }

int MaxHeap::size() const { return heap.size(); }
int MaxHeap::capacity() const { return heap.capacity(); }

MaxHeap::MaxHeap(int cap) {
    heap.reserve(cap);
}

void MaxHeap::insert(int k) {
    heap.push_back(k);
    int size = heap.size();
    for (int i = size >> 1 - 1; i >= 0; i--)
        heapify(i);
}
int MaxHeap::extractMax() {
    int size = heap.size();
    if (size <= 0)
        return 123456;
    if (size == 1) {
        heap.pop_back();
        return heap[0];
    }
    int val = heap[0];
    heap[0] = heap[size - 1];
    heap.pop_back();
    heapify(0);
    return val;
}

void MaxHeap::printArray() {
    for (int i = 0; i < heap.size(); i++)
        cout << heap[i] << " ";
    cout << endl;
}

void MaxHeap::heapify(int i) {
    int size = heap.size();
    int largest = i;
    int l = left(i);
    int r = right(i);
    if (l < size && heap[l] > heap[largest])
        largest = l;
    if (r < size && heap[r] > heap[largest])
        largest = r;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(largest);
    }
}
