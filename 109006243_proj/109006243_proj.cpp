#include <fstream>
#include <iostream>
#include <string>

#include "./include/input.hpp"
#include "./include/pricing.hpp"
#include "./include/station.hpp"
#include "./include/status.hpp"
#include "./include/user.hpp"

using namespace std;

int costForDisc = 123456;
int DEBUG = 0;
int case2 = 1;
int DEBUG3 = 1;
int maxStation = 0;
extern User user[100000];
extern Vector<pii> transferList[2];
/*
g++ -g *.cpp ./include/*.cpp -o 109006243_proj -std=c++11
./109006243_proj
*/
Station *station;
Vector<int> Rej;
bool rejectedUser[100000];
bool firstTime = true;

void stockAtTime();
void outputUserTest();
void RejectOut();
void MaxTransDisc();
void mapPrint();
void waitListPrint();
void expectCost();
// string path = "./test_case/DS_testcase/open_basic3";
string path = "./test_case";
int main() {
    money = 0;
    ifstream input;
    ofstream output;
    inputStation(input, path);
    inputMap(input, path);
    inputFee(input, path);

    input.open(path + "/user.txt");
    output.open("part1_response.txt");

    while (input) {
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
            if (DEBUG && x == Accept)
                station[ID].stockAtTime[time][toBike(type)]--;
            if (x == Reject) {
                Rej.push_back(userID);
                rejectedUser[userID] = true;
            }

        } else if (t == "return") {
            // stationIdReturn userId timeReturn0-1440
            input >> ID >> userID >> time;
            output << ID << " " << std::setfill('0') << std::setw(5) << userID
                   << " " << time << "\n";
            bool x = station[ID].Return(userID, time);
            if (DEBUG && x == true)
                station[ID].stockAtTime[time][user[userID].type]++;
        }
    }
    // PUSH BACK THE USER DATA TO WAITLIST
    for (int i = 0; i < Rej.size(); i++) {
        User t = user[Rej[i]];
        station[t.sOut].waitList[t.type].push(
            pii(-(t.timeEnd - t.timeSt), Rej[i]));
        station[t.sOut].costExpected[t.type] += t.Return(t.timeEnd, t.sIn);
        // station[t.sOut].costExpected[t.type][1] +=
        //     round(costForDisc * (t.timeEnd - t.timeSt));
    }
    if (DEBUG) {
        expectCost();
        // waitListPrint();
        // RejectOut();
        // stockAtTime();
        MaxTransDisc();
        mapPrint();
        // outputUserTest();
    }
    input.close();
    output.close();

    output.open("part1_status.txt");
    for (int i = 0; i <= maxStation; i++) station[i].printStation_1(output);
    output << money;
    output.close();
    // for part 2
    if (case2) {
        firstTime = false;
        // MaxTransDisc();
        money = 0;

        output.open("part2_response.txt");
        maxTransferOp();

        inputStation(input, path);
        for (int i = 0; i < transferList[0].size(); i++) {
            int from = transferList[0][i].first, to = transferList[0][i].second;
            int bt = transferList[1][i].first;
            int &need = transferList[1][i].second;
            station[to].transferedTime[bt] = map[from][to];
            output << "transfer " << from << " " << to << " " << toName(bt)
                   << " " << need << " 0\n";
            // cout << from << " " << to << " " << type << " " << need << "\n ";
            while (need--) {
                station[to].bikeID[bt].push(station[from].bikeID[bt].top());
                station[from].bikeID[bt].pop();
            }
        }

        input.open(path + "/user.txt");
        while (input) {
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
                       << std::setw(5) << userID << " " << time;
                if (x == Reject) {
                    // check maxTrans stock
                    int i;
                    for (i = 2; i >= 0; i--) {
                        if (station[ID].maxTransfer[i]) {
                            x = station[ID].Rent(i, userID, time, true);
                            output << outputRes(x) << toName(i) << "\n";
                            station[ID].maxTransfer[i]--;
                            break;
                        }
                    }
                    if (i == -1) output << outputRes(x);
                    // TODO CAN WE WAIT OR DISCOUNT ELSE REJECT
                } else
                    output << outputRes(x);

                // 1. discount
                // TODO actually to know what to offer need to know
                // the start and the end transfer or discount wait
                // is hard offer discount on ppl accept is hard

            } else if (t == "return") {
                // stationIdReturn userId timeReturn0-1440
                input >> ID >> userID >> time;
                output << ID << " " << std::setfill('0') << std::setw(5)
                       << userID << " " << time << "\n";
                bool x = station[ID].Return(userID, time);
            }
        }
        // MaxTransDisc();
        output.close();
        output.open("part2_status.txt");
        for (int i = 0; i <= maxStation; i++) station[i].printStation_1(output);
        output << money;
        output.close();
    }
}
void stockAtTime() {
    int t[3];
    ofstream out;
    out.open("stockTime.txt");
    for (int i = 0; i <= maxStation; i++) {
        if (station[i].sID != -1) {
            for (int j = 0; j < 3; j++) {
                for (int k = 1; k <= 1441; k++) {
                    station[i].stockAtTime[k][j] +=
                        station[i].stockAtTime[k - 1][j];
                    station[i].stockAtTime[k - 1][j] += station[i].size[j];
                }
            }
            for (int j = 0; j <= 1440; j++) {
                if (j && t[0] == station[i].stockAtTime[j][0] &&
                    t[1] == station[i].stockAtTime[j][1] &&
                    t[2] == station[i].stockAtTime[j][2])
                    continue;
                out << i << "@" << j << ": ";
                for (int k = 0; k < 3; k++) {
                    t[k] = station[i].stockAtTime[j][k];
                    out << t[k] << " ";
                }
                out << "\n";
            }
        }
    }
}
void outputUserTest() {
    ofstream out;
    out.open("TEST.txt");
    for (int i = 0; i < 100000; i++) {
        if (user[i].type != -1) {
            out << "User: " << i << " " << toName(user[i].type)
                << " Time: " << user[i].timeSt << "-" << user[i].timeEnd
                << " sOut-sIn: " << user[i].sOut << "->" << user[i].sIn << "\n";
        }
    }
    out.close();
}
void MaxTransDisc() {
    ofstream out;
    out.open("maxTrans.txt");
    for (int i = 0; i <= maxStation; i++) {
        if (station[i].sID != -1) {
            out << i << " ";
            for (int j = 0; j < 3; j++) out << station[i].maxTransfer[j] << " ";
            out << "\n";
        }
    }
    out.close();
}
void RejectOut() {
    ofstream outw;
    outw.open("Rejected.txt");
    for (int i = 0; i < Rej.size(); i++) {
        User t = user[Rej[i]];
        outw << "FROM: " << t.sOut << "->" << t.sIn << " TIME: " << t.timeSt
             << "->" << t.timeEnd << " DIFF: " << t.timeEnd - t.timeSt << " "
             << toName(t.type) << " ID: " << Rej[i] << "\n";
    }
    outw.close();
}
void mapPrint() {
    ofstream out;
    out.open("mapPrint.txt");
    for (int i = 1; i <= maxStation; i++) {
        for (int j = 1; j <= maxStation; j++) out << map[i][j] << " ";
        out << "\n";
    }
    out.close();
}
void waitListPrint() {
    ofstream out;
    out.open("waitPrint.txt");
    for (int i = 1; i <= maxStation; i++) {
        out << i << ":\n";
        for (int j = 0; j < 3; j++) {
            bool x = station[i].waitList[j].size();
            if (x) out << "Type " << j << ": ";
            int k;
            if (x) out << "(" << station[i].waitList[j].size() << ")";
            while (!station[i].waitList[j].empty()) {
                out << -station[i].waitList[j].top().first << ","
                    << station[i].waitList[j].top().second << " ";
                station[i].waitList[j].pop();
            }
            if (x) out << "\n";
        }
    }
    out.close();
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