#ifndef USER_HPP
#define USER_HPP

#include "pii.hpp"
class User {
   protected:
    int type;
    // first is station, second is #bike
    pii bikeNo;
    int timeSt;

   public:
    friend class Station;
    User() : type(-1) {}
    void Rent(int bt, pii no, int time) {
        type = bt;
        bikeNo = no;
        timeSt = time;
    }
    int Return() {
        type = -1;
        return timeSt;
    }
};

static User user[100000];
#endif