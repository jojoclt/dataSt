#include "vector.hpp"

#include <iostream>

template <typename T>
Vector<T>::Vector() {
    first = new T[0];
    last = curr = first;
}

template <typename T>
Vector<T>::~Vector() {
    if (first != nullptr) delete[] first;
}
template <typename T>
Vector<T>::Vector(int s) {
    first = new T[0];
    last = curr = first;
    reserve(s);
}
template <typename T>
Vector<T>::Vector(const Vector<T>& obj) {
    if (first != nullptr) delete[] first;
    first = curr = last = nullptr;
    reserve(obj.size());
    for (int i = 0; i < obj.size(); i++) push_back(obj[i]);
}
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& obj) {
    if (first != nullptr) delete[] first;
    first = curr = last = nullptr;
    reserve(obj.size());
    for (int i = 0; i < obj.size(); i++) push_back(obj[i]);
    return *this;
}
template <typename T>
void Vector<T>::push_back(T val) {
    int old_capacity = capacity();
    int new_capacity = std::max(old_capacity + 1, old_capacity * 3);
    if (size() == old_capacity) {
        reserve(new_capacity);
        push_back(val);
    } else {
        (*curr) = val;
        curr++;
    };
}
template <typename T>
void Vector<T>::insert(int pos, T val) {
    int old_size = size();
    int old_capacity = capacity();
    if (pos > old_size) return;
    if (curr == last) {
        int new_capacity =
            std::max(old_capacity * 3, old_capacity + 1);
        reserve(new_capacity);
    }
    curr++;
    // resize(old_size + 1);
    for (int i = old_size; i > pos; i--) first[i] = first[i - 1];

    first[pos] = val;
}

template <typename T>
void Vector<T>::reserve(int new_capacity) {
    int old_capacity = capacity();
    int old_size = size();
    if (new_capacity <= old_capacity) return;

    T* new_first = new T[new_capacity];
    for (int i = 0; i < old_size; i++) {
        new_first[i] = first[i];
    }
    if (first != nullptr) delete[] first;
    first = new_first;
    curr = &first[old_size];
    last = &first[new_capacity];
}

template <typename T>
void Vector<T>::resize(int new_size) {
    int old_size = size();
    if (new_size > old_size) {
        reserve(new_size);
        T x;
        for (int i = old_size; i < new_size; i++) push_back(x);
    } else if (new_size < old_size) {
        for (int i = old_size; i > new_size; i--) pop_back();
    }
}
template <typename T>
void Vector<T>::pop_back() {
    if (size() > 0) {
        curr--;
    }
}
template class Vector<int>;
