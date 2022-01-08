#ifndef INPUT_HPP
#define INPUT_HPP
#include <fstream>
#include <iostream>
#include <string>

#include "pricing.hpp"
#include "station.hpp"
extern int **map;
extern int waitFee, reduceRate, rateofTransfer;
extern pii bikeRate[3];
extern Station *station;
extern int maxStation;

int toBike(std::string b) {
    if (b == "electric") return 0;
    if (b == "lady") return 1;
    if (b == "road") return 2;
    return 0;
}
std::string toName(int i) {
    if (i == 0) return "electric";
    if (i == 1) return "lady";
    if (i == 2) return "road";
    return "BAD";
}
void inputMap(std::ifstream &os, std::string path) {
    os.open(path + "/map.txt");
    if (!os.is_open()) std::cout << "<<MAP NOT OPENED>>", exit(0);

    initMap(maxStation);
    while (os) {
        int s1, s2, dist;
        os >> s1 >> s2 >> dist;
        map[s1][s2] = map[s2][s1] = dist;
    }
    os.close();
    calcDist();
}

void inputStation(std::ifstream &os, std::string path) {
    os.open(path + "/station.txt");
    while (os) {
        int ID, elecAmt, ladyAmt, roadAmt;
        os >> ID >> elecAmt >> ladyAmt >> roadAmt;
        // station[ID] = Station(ID, elecAmt, ladyAmt, roadAmt);
        maxStation = max(ID, maxStation);
    }
    os.close();
    station = new Station[maxStation + 1];
    os.open(path + "/station.txt");
    while (os) {
        int ID, elecAmt, ladyAmt, roadAmt;
        os >> ID >> elecAmt >> ladyAmt >> roadAmt;
        station[ID] = Station(ID, elecAmt, ladyAmt, roadAmt);
        // maxStation = max(ID, maxStation);
    }
    os.close();
}

void inputFee(std::ifstream &os, std::string path) {
    os.open(path + "/fee.txt");
    while (os) {
        std::string type;
        pii rate;
        for (int i = 0; i < 3; i++) {
            os >> type >> rate.first >> rate.second;
            bikeRate[toBike(type)] = rate;
            costForDisc = std::min(costForDisc, rate.first);
        }
        os >> waitFee >> reduceRate >> rateofTransfer;
    }
    os.close();
}
#endif