#include <fstream>
#include <iostream>
#include <string>

#include "./include/station.hpp"

using namespace std;

// g++ -g *.cpp ./include/*.cpp -o 109006243_proj -std=c++11
int map[105][105];
Station *station[105];
int main() {
    ifstream input;

    input.open("./test_case/map.txt");
    if (!input.is_open()) {
        cout << "<<MAP NOT OPENED>>";
    }
    while (input) {
        int s1, s2, dist;
        input >> s1 >> s2 >> dist;
        map[s1][s2] = map[s2][s1] = dist;
    }
    input.close();
    input.open("./test_case/station.txt");
    if (!input.is_open()) {
        cout << "<<STATION NOT OPENED>>";
    }
    while (input) {
        int ID, elecAmt, ladyAmt, roadAmt;
        input >> ID >> elecAmt >> ladyAmt >> roadAmt;
        station[ID] = new Station(elecAmt, ladyAmt, roadAmt);
    }
    input.close();
    input.open("./test_case/fee.txt");
    if (!input.is_open()) {
        cout << "<<FEE NOT OPENED>>";
    }
    // while (input) {
    // }
}