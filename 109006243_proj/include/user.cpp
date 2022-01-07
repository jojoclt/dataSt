#include "user.hpp"

User user[100000];
extern int waitFee;
void User::Rent(int bt, int no, int time, int stat, int disc, int wait) {
    type = bt;
    bikeNo = no;
    timeSt = time;
    sOut = stat;
    discount = disc;
    waitTime = wait;
    isRent = true;
}
void User::Return(int time2, int _sIn) {
    sIn = _sIn, timeEnd = time2;
    int dt = time2 - timeSt;
    if (dt <= map[sOut][_sIn]) {
        money += (bikeRate[type].first * dt) * discount + (waitTime * waitFee);
    } else {
        money += (bikeRate[type].second * dt) * discount + (waitTime * waitFee);
    }
    isRent = false;
}