#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

#include "user.hpp"

template <typename T>
class Vector {
   public:
    T* arr;
    int curr, cap;

   public:
    friend std::ostream& operator<<(std::ostream& os, Vector<T>& v) {
        for (int i = 0; i < v.size(); i++) os << v[i] << " ";
        os << "\n";
        return os;
    }
    Vector() {
        arr = new T[1];
        cap = 1, curr = 0;
    }

    Vector(const Vector<T>& obj) {
        curr = obj.curr;
        cap = obj.cap;
        arr = new T[cap];
        for (int i = 0; i < curr; i++) push_back(obj[i]);
    }
    Vector<T>& operator=(const Vector<T>& obj) {
        curr = obj.curr;
        cap = obj.cap;
        arr = new T[cap];
        for (int i = 0; i < curr; i++) push_back(obj[i]);
        return *this;
    }

    T& operator[](const int pos) const { return arr[pos]; }

    void push_back(T x) {
        if (curr == cap) {
            T* temp = new T[2 * cap];
            for (int i = 0; i < cap; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            cap *= 2;
            arr = temp;
        }

        arr[curr] = x;
        curr++;
    }

    int size() const { return curr; }
    int capacity() const { return cap; }
    void pop_back() { curr--; }
};

#endif