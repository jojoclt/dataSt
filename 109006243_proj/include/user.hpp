#ifndef USER_HPP
#define USER_HPP
#include <iostream>

#include "pricing.hpp"

extern int money;
extern int map[105][105];
extern pii bikeRate[3];
class User {
   protected:
    int type;
    int bikeNo;
    int timeSt;
    int sOut;

   public:
    friend class Station;
    User() : type(-1), timeSt(-1000) {}
    void Rent(int bt, int no, int time, int stat) {
        type = bt;
        bikeNo = no;
        timeSt = time;
        sOut = stat;
    }
    void Return(int time2, int sIn) {
        int dt = time2 - timeSt;
        if (dt <= map[sOut][sIn]) {
            money += bikeRate[type].first * dt;
        } else {
            money += bikeRate[type].second * dt;
        }
        type = -1;
    }
};

#endif