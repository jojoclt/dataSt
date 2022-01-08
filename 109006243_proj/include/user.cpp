#include "user.hpp"

User user[100000];
void User::operator=(const User &u) {
    type = u.type;
    bikeNo = u.bikeNo;
    timeSt = u.timeSt, timeEnd = u.timeEnd;
    sIn = u.sIn, sOut = u.sOut;
    discount = u.discount;
    waitTime = u.waitTime;
    isRent = u.isRent;
}
void User::Rent(int bt, int no, int time, int stat, int disc, int wait) {
    type = bt;
    bikeNo = no;
    timeSt = time;
    sOut = stat;
    discount = disc;
    waitTime = wait;
    isRent = true;
}
int User::Return(int time2, int _sIn) {
    sIn = _sIn, timeEnd = time2;
    int dt = time2 - timeSt;
    int t;
    if (dt <= map[sOut][_sIn]) {
        t = (bikeRate[type].first * dt);
    } else {
        t = (bikeRate[type].second * dt);
    }
    isRent = false;
    return t;
}