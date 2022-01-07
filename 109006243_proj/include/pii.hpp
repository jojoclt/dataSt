#ifndef PII_HPP
#define PII_HPP
struct pii {
    int first, second;
    pii() { first = second = 0; }
    pii(int x, int y) { first = x, second = y; }
    pii& operator=(const pii& p) {
        first = p.first;
        second = p.second;
        return *this;
    }
    bool operator<(pii p) const {
        return (first < p.first) || (first == p.first && second < p.second);
    }
    bool operator>(pii p) const {
        return (first > p.first) || (first == p.first && second > p.second);
    }
    bool operator==(const pii& p) {
        return p.first == first && p.second == second;
    }
};

#endif