#include "user.hpp"

User user[100000];
void User::operator=(const User &u) {
    type = u.type;
    bikeNo = u.bikeNo;
    timeSt = u.timeSt, timeEnd = u.timeEnd;
    sIn = u.sIn, sOut = u.sOut;
    discount = u.discount;
    isRent = u.isRent;
    waitTime = u.waitTime;
}
void User::Rent(int bt, int no, int time, int stat, bool disc, int wait) {
    type = bt;
    bikeNo = no;
    timeSt = time;
    sOut = stat;
    discount = disc;
    isRent = true;
    waitTime = wait;
}
int User::Return(int time2, int _sIn) {
    sIn = _sIn, timeEnd = time2;
    int dt = timeEnd - timeSt;
    int t;
    if (dt <= map[sOut][sIn]) {
        t = (bikeRate[type].first * dt);
    } else {
        t = (bikeRate[type].second * dt);
    }
    isRent = false;
    if (discount) return round(reduceRate * t);
    if (waitTime) return t - (waitTime * waitFee);
    return t;
}