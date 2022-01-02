#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

template <typename T>
class Vector {
   private:
    T *first, *curr, *last;

   public:
    friend std::ostream& operator<<(std::ostream& os, Vector<T>& v)
    {
        for (int i = 0; i < v.size(); i++) os << v[i] << " ";
        os << "\n";
        return os;
    }
    Vector()
    {
        first = new T[0];
        last = curr = first;
    }
    Vector(int s)
    {
        first = new T[s];
        curr = first;
        last = first + s * sizeof(T);
    }
    Vector(const Vector<T>& obj)
    {
        first = obj.first;
        curr = obj.curr;
        last = obj.last;
    }
    ~Vector() {}
    T& operator[](int pos) { return first[pos]; }
    Vector<T>& operator=(const Vector<T>& p)
    {
        first = p.first;
        curr = p.curr;
        last = p.last;
        return *this;
    }
    void push_back(T x);
    void insert(int pos, T val);
    void reserve(int new_capacity);
    // Filling num
    void resize(int new_size);
    int size() { return curr - first; }
    int capacity() { return last - first; }
    void pop_back()
    {
        if (size() > 0) {
            curr--;
        }
    }
};

#endif