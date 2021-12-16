#include <fstream>
#include <iostream>
#include <string>

#include "./include/station.hpp"

using namespace std;

// g++ -g *.cpp ./include/*.cpp -o 109006243_proj -std=c++11
int map[105][105];
Station *station[105];
int bikeRate[3][2];
string bikeType[] = {"electric", "lady", "road"};
int waitFee, reduceRate, rateofTransfer;
// elec lady road - disc/reg price

int main() {
    ifstream input;

    input.open("./test_case/map.txt");
    if (!input.is_open()) cout << "<<MAP NOT OPENED>>", exit(0);

    while (input) {
        int s1, s2, dist;
        input >> s1 >> s2 >> dist;
        map[s1][s2] = map[s2][s1] = dist;
    }
    input.close();

    input.open("./test_case/station.txt");
    if (!input.is_open()) cout << "<<STATION NOT OPENED>>", exit(0);

    while (input) {
        int ID, elecAmt, ladyAmt, roadAmt;
        input >> ID >> elecAmt >> ladyAmt >> roadAmt;
        station[ID] = new Station(elecAmt, ladyAmt, roadAmt);
    }
    input.close();

    input.open("./test_case/fee.txt");
    if (!input.is_open()) cout << "<<FEE NOT OPENED>>", exit(0);

    while (input) {
        string type;
        int rate[2];
        for (int i = 0; i < 3; i++) {
            input >> type >> rate[0] >> rate[1];
            for (int j = 0; j < 3; j++) {
                if (type == bikeType[j]) bikeRate[j][0] = rate[0], bikeRate[j][1] = rate[1];
            }
        }
        input >> waitFee >> reduceRate >> rateofTransfer;
    }
    input.close();

    input.open("./test_case/user.txt");
    if (!input.is_open()) cout << "<<USER NOT OPENED>>", exit(0);

    while (input) {
        string type;
        input >> type;
        if (type == "rent") {
            // stationIdRent bikeType userId timeRent
        } else if (type == "return") {
            // stationIdReturn userId timeReturn
        }
    }
}