#ifndef MINHEAP_HPP
#define MINHEAP_HPP
#include <climits>
#include <iostream>

#include "vector.hpp"
using namespace std;

template <typename T>
class MinHeap {
   public:
    Vector<T> heap;
    void push(T k);
    void pop();
    T top();
    int size() const;
    int capacity() const;
    bool empty();

   private:
    int Parent(int i);
    int Left(int i);
    int Right(int i);
    void heapify_down(int);
    void heapify_up(int);
};

#endif