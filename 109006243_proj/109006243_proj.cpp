#include <fstream>
#include <iostream>
#include <string>

#include "./include/input.hpp"
#include "./include/pricing.hpp"
#include "./include/station.hpp"
#include "./include/status.hpp"
#include "./include/user.hpp"

using namespace std;

int costForDisc = 12345678;
int DEBUG = 0;
int case2 = 1;
int DEBUG3 = 1;
int maxStation = 0;
extern User user[100000];
extern Vector<pii> transferList[2];
Vector<int> addtoReturn;
// a wait list for waiters
Vector<int> addtoRent;
Vector<int> arr[505];
Vector<int> arrTime;
int timeCount = 0;
int rentCount = 0, returnCount = 0;
void expectCost();
void transfer(int time);
/*
g++ -g *.cpp ./include/*.cpp -o 109006243_proj -std=c++11
./109006243_proj
*/
Station *station;
bool rejectedUser[100000];
bool firstTime = true;

string path = "./test_case/DS_testcase/open_basic2/test_case";
// string path = "./test_case";
int main() {
    money = 0;
    ifstream input;
    ofstream output;
    inputStation(input, path);
    inputMap(input, path);
    inputFee(input, path);

    input.open(path + "/user.txt");
    output.open("part1_response.txt");

    // part1
    while (input.good()) {
        string t;
        input >> t;
        output << t << " ";
        int ID, userID, time;
        string type;
        if (t == "rent") {
            // stationIdRent bikeType userId(5digit) timeRent
            input >> ID >> type >> userID >> time;
            Status x = station[ID].Rent(toBike(type), userID, time);
            output << ID << " " << type << " " << std::setfill('0')
                   << std::setw(5) << userID << " " << time << outputRes(x);

            if (x == Reject) {
                rejectedUser[userID] = true;
            }

        } else if (t == "return") {
            // stationIdReturn userId timeReturn0-1440
            input >> ID >> userID >> time;
            output << ID << " " << std::setfill('0') << std::setw(5) << userID
                   << " " << time << "\n";
            bool x = station[ID].Return(userID, time);
        }
    }
    // PUSH BACK THE USER DATA TO WAITLIST
    for (int i = 0; i < 100000; i++) {
        if (!rejectedUser[i]) continue;
        User t = user[i];
        station[t.sOut].waitCount[t.type]++;
        station[t.sOut].costExpected[t.type] += t.Return(t.timeEnd, t.sIn);
    }

    // expectCost();
    input.close();
    output.close();

    output.open("part1_status.txt");
    for (int i = 0; i <= maxStation; i++) station[i].printStation_1(output);
    output << money << "\n";
    output.close();

    // for part 2

    firstTime = false;

    money = 0;

    output.open("part2_response.txt");
    maxTransferOp();

    inputStation(input, path);
    for (int i = 0; i < transferList[0].size(); i++) {
        int from = transferList[0][i].first, to = transferList[0][i].second;
        int bt = transferList[1][i].first;
        int &need = transferList[1][i].second;
        station[to].transferedTime[bt] = map[from][to];
        output << "transfer " << from << " " << to << " " << toName(bt) << " "
               << need << " 0\n";
        // cout << from << " " << to << " " << type << " " << need << "\n ";

        while (need--) {
            // u cant push now!

            arr[i].push_back(station[from].bikeID[bt].top());
            station[from].bikeID[bt].pop();
        }
        arrTime.push_back(map[from][to]);
    }
    // debugger

    input.open(path + "/user.txt");
    while (input.good()) {
        string t;
        input >> t;
        output << t << " ";
        int ID, userID, time;
        string type;
        if (t == "rent") {
            input >> ID >> type >> userID >> time;
            transfer(time);
            // waitlist for waiters
            // while (rentCount < addtoRent.size()) {
            //     User u = user[addtoRent[rentCount]];
            //     if (u.waitTime + u.timeSt > time) break;
            //     station[u.sOut].Rent(u.type, addtoRent[rentCount], u.timeSt,
            //                          false, u.waitTime);
            //     rentCount++;
            // }
            // // stationIdRent bikeType userId(5digit) timeRent
            // // check IF TIME IS MORE THAN TOADD LIST
            // while (returnCount < addtoReturn.size()) {
            //     User t = user[addtoReturn[returnCount]];
            //     if (time >= t.timeEnd + t.waitTime &&
            //         t.timeEnd + t.waitTime <= 1440) {
            //         station[ID].Return(addtoReturn[returnCount], t.timeEnd);
            //         returnCount++;
            //     } else
            //         break;
            // }

            Status x = station[ID].Rent(toBike(type), userID, time);
            output << ID << " " << type << " " << std::setfill('0')
                   << std::setw(5) << userID << " " << time;
            if (x == Reject) {
                // check maxTrans stock
                // compare between wait and discount

                // DISCOUNT
                int moneyDisc = -1e9, moneyWait = -1e9;
                int maxI;
                int t;
                int dt = user[userID].timeEnd - user[userID].timeSt;

                for (int i = 0; i < 3; i++) {
                    if (station[ID].maxTransfer[i]) {
                        if (map[user[userID].sOut][user[userID].sIn] <= dt)
                            t = round(reduceRate * dt * bikeRate[i].first);
                        else
                            t = round(reduceRate * dt * bikeRate[i].second);
                        if (moneyDisc < t) {
                            moneyDisc = t;
                            maxI = i;
                        }
                    }
                }

                // WAIT

                dt = station[ID].transferedTime[toBike(type)] - time;
                if (time < station[ID].transferedTime[toBike(type)])
                    moneyWait = user[userID].Return(user[userID].timeEnd,
                                                    user[userID].sIn) -
                                (waitFee * dt);
                moneyWait = -1;
                if (moneyDisc <= 0 && moneyWait <= 0) {
                    output << outputRes(x);
                } else {
                    // cout << moneyWait << " " << moneyDisc << endl;
                    if (moneyWait >= moneyDisc) {
                        if (dt + user[userID].timeEnd > 1440)
                            output << outputRes(x);
                        else {
                            output << "\nwait\n";
                            // YOU CANT RENT YET! YOU NEED TO GET THE BIKE AT
                            // TIME
                            // always prioritize wait! rent return implement
                            addtoRent.push_back(userID);
                            user[userID].waitTime = dt;
                            // station[ID].Rent(toBike(type), userID, time,
                            // false,
                            //                  dt);
                        }
                    } else {
                        output << "\ndiscount " << toName(maxI) << "\n";
                        station[ID].Rent(maxI, userID, time, true);
                        station[ID].maxTransfer[maxI]--;
                    }
                }
            } else
                output << outputRes(x);

        } else if (t == "return") {
            // TIME TO RETURN GOR BUAK PAI
            // stationIdReturn userId timeReturn0-1440
            input >> ID >> userID >> time;
            transfer(time);
            // for waiter renters
            // while (rentCount < addtoRent.size()) {
            //     User u = user[addtoRent[rentCount]];
            //     if (time < u.waitTime + u.timeSt) break;
            //     station[u.sOut].Rent(u.type, addtoRent[rentCount], u.timeSt,
            //                          false, u.waitTime);
            //     rentCount++;
            // }
            // while (returnCount < addtoReturn.size()) {
            //     User t = user[addtoReturn[returnCount]];
            //     if (time >= t.timeEnd + t.waitTime &&
            //         t.timeEnd + t.waitTime <= 1440) {
            //         station[ID].Return(addtoReturn[returnCount], t.timeEnd);
            //         returnCount++;
            //     } else
            //         break;
            // }
            output << ID << " " << std::setfill('0') << std::setw(5) << userID
                   << " " << time << "\n";
            if (user[ID].waitTime) {
                // ADD TO LIST OF ADDERS // ALSO USER TIME
                addtoReturn.push_back(userID);
            } else
                bool x = station[ID].Return(userID, time);
        }
    }
    // MaxTransDisc();
    output.close();
    output.open("part2_status.txt");
    for (int i = 0; i <= maxStation; i++) station[i].printStation_1(output);
    output << money << "\n";
    output.close();
}

void expectCost() {
    ofstream out;
    out.open("costExpect.txt");
    for (int i = 1; i <= maxStation; i++) {
        out << i << ":\n";
        for (int j = 0; j < 3; j++) {
            out << "TRANSFER:" << station[i].costExpected[j] << "\n";
        }
        out << "\n";
    }
    out.close();
}

void transfer(int time) {
    for (int i = 0; i < arrTime.size(); i++) {
        if (arrTime[i] != -1 && time >= arrTime[i]) {
            // startTransfer
            int to = transferList[0][i].second, bt = transferList[1][i].first;
            for (int j = 0; j < arr[i].size(); j++) {
                station[to].bikeID[bt].push(arr[i][j]);
            }
            arrTime[i] = -1;
        }
    }
}