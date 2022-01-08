#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

#include "user.hpp"

template <typename T>
class Vector {
   private:
    T *first, *curr, *last;

   public:
    friend std::ostream& operator<<(std::ostream& os, Vector<T>& v) {
        for (int i = 0; i < v.size(); i++) os << v[i] << " ";
        os << "\n";
        return os;
    }
    Vector();
    ~Vector();
    Vector(int s);

    Vector(const Vector<T>&);

    T& operator[](const int pos) const { return first[pos]; }
    Vector<T>& operator=(const Vector<T>&);
    void push_back(T x);
    void insert(int pos, T val);
    void reserve(int new_capacity);
    // Filling num
    void resize(int new_size);
    int size() const { return curr - first; }
    int capacity() const { return last - first; }
    void pop_back();
};

#endif