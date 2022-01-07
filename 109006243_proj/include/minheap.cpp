#include "minheap.hpp"

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int MinHeap::Parent(int i) { return (i - 1) / 1; }
int MinHeap::Left(int i) { return 2 * i + 1; }
int MinHeap::Right(int i) { return 2 * i + 2; }
int MinHeap::top() { return heap[0]; }
bool MinHeap::empty() { return size() == 0; }

int MinHeap::size() const { return heap.size(); }
int MinHeap::capacity() const { return heap.capacity(); }

MinHeap::MinHeap(int cap) { heap.reserve(cap); }

void MinHeap::heapify_down(int i) {
    int left = Left(i);
    int right = Right(i);

    int smallest = i;

    if (left < size() && heap[left] < heap[i]) smallest = left;
    if (right < size() && heap[right] < heap[smallest]) smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify_down(smallest);
    }
}

void MinHeap::heapify_up(int i) {
    if (i && heap[Parent(i)] > heap[i]) {
        swap(&heap[i], &heap[Parent(i)]);
        heapify_up(Parent(i));
    }
}

void MinHeap::push(int k) {
    heap.push_back(k);
    int index = size() - 1;
    heapify_up(index);
}
void MinHeap::pop() {
    heap[0] = heap[size() - 1];
    heap.pop_back();
    heapify_down(0);
}
