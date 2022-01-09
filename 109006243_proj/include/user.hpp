#ifndef USER_HPP
#define USER_HPP
#include <cmath>
#include <iostream>

#include "pricing.hpp"
extern int money;
extern int **map;
extern pii bikeRate[3];
extern int waitFee;
class User {
   public:
    int type;
    int bikeNo;
    int timeSt, timeEnd;
    int sIn, sOut;
    bool discount;
    int waitTime;
    bool isRent;

   public:
    friend class Station;
    User() : isRent(false), discount(false), waitTime(0), type(-1) {}
    void operator=(const User &u);
    void Rent(int bt, int no, int time, int stat, bool disc = false,
              int wait = 0);

    int Return(int time2, int _sIn);
};

#endif