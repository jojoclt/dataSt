#ifndef UID_HPP
#define UID_HPP

class uID {
   public:
    int type;
    int bikeNo;
    int timeSt;
    uID() : type(-1) {}
    void Rent(int bt, int no, int time) {
        type = bt;
        bikeNo = no;
        timeSt = time;
    }
};

static uID userID[100000];
#endif