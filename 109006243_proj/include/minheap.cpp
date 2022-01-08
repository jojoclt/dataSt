#include "minheap.hpp"
template <typename T>
int MinHeap<T>::Parent(int i) {
    return (i - 1) / 1;
}
template <typename T>
int MinHeap<T>::Left(int i) {
    return 2 * i + 1;
}
template <typename T>
int MinHeap<T>::Right(int i) {
    return 2 * i + 2;
}
template <typename T>
T MinHeap<T>::top() {
    return heap[0];
}
template <typename T>
bool MinHeap<T>::empty() {
    return size() == 0;
}
template <typename T>
int MinHeap<T>::size() const {
    return heap.size();
}
template <typename T>
int MinHeap<T>::capacity() const {
    return heap.capacity();
}
template <typename T>
MinHeap<T>::MinHeap(int cap) {
    heap.reserve(cap);
}
template <typename T>
void MinHeap<T>::heapify_down(int i) {
    int left = Left(i);
    int right = Right(i);

    int smallest = i;

    if (left < size() && heap[left] < heap[i]) smallest = left;
    if (right < size() && heap[right] < heap[smallest]) smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapify_down(smallest);
    }
}
template <typename T>
void MinHeap<T>::heapify_up(int i) {
    if (i && heap[Parent(i)] > heap[i]) {
        swap(heap[i], heap[Parent(i)]);
        heapify_up(Parent(i));
    }
}
template <typename T>
void MinHeap<T>::push(T k) {
    heap.push_back(k);
    int index = size() - 1;
    heapify_up(index);
}
template <typename T>
void MinHeap<T>::pop() {
    heap[0] = heap[size() - 1];
    heap.pop_back();
    heapify_down(0);
}
template class MinHeap<pii>;
template class MinHeap<int>;