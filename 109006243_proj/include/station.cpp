#include "station.hpp"

#include <iostream>
Station::Station() {
}
Station::Station(int elec, int lady, int road) {
    elecAmt = elec;
    ladyAmt = lady;
    roadAmt = road;
    elecID = new int[elecAmt];
    ladyID = new int[ladyAmt];
    roadID = new int[roadAmt];
}
// Station::Station(const Station &s) {
//     elecAmt = s.elecAmt;
//     ladyAmt = s.ladyAmt;
//     roadAmt = s.roadAmt;
//     elecID = s.elecID;
//     ladyID = s.ladyID;
//     roadID = s.roadID;
// }
// Station &Station::operator=(const Station &s) {
//     elecAmt = s.elecAmt;
//     ladyAmt = s.ladyAmt;
//     roadAmt = s.roadAmt;
//     elecID = s.elecID;
//     ladyID = s.ladyID;
//     roadID = s.roadID;
//     return *this;
// }