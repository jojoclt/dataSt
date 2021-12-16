#ifndef STATION_H
#define STATION_H
class Station {
   public:
    int elecAmt, ladyAmt, roadAmt;
    int *elecID, *ladyID, *roadID;
    Station();
    Station(int elec, int lady, int road);
    // Station(const Station &s);
    // Station &operator=(const Station &s);
};
#endif