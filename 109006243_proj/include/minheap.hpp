#ifndef MINHEAP_HPP
#define MINHEAP_HPP
#include <climits>
#include <iostream>

#include "vector.hpp"
using namespace std;

class MinHeap {
   public:
    Vector<int> heap;
    MinHeap(int capacity = 100);
    void push(int k);
    void pop();
    int top();
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