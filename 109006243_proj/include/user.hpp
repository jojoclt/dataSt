#ifndef USER_HPP
#define USER_HPP
#include <iostream>

#include "pricing.hpp"
#define MAXN 505
extern int money;
extern int map[MAXN][MAXN];
extern pii bikeRate[3];
class User {
   public:
    int type;
    int bikeNo;
    int timeSt, timeEnd;
    int sIn, sOut;
    int discount;
    int waitTime;
    bool isRent;

   public:
    friend class Station;
    User() : isRent(false), discount(1), waitTime(0), type(-1) {}

    void Rent(int bt, int no, int time, int stat, int disc = 1, int wait = 0);

    void Return(int time2, int _sIn);
};

#endif