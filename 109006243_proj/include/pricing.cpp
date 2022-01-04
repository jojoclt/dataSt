#include "pricing.hpp"

#include <iostream>
int money = 0;
int map[105][105];
int waitFee, reduceRate, rateofTransfer;
pii bikeRate[3];
void initMap() {
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++) map[i][j] = 123456;
    for (int i = 0; i <= 100; i++) map[i][i] = 0;
}

void calcDist() {
    for (int k = 0; k <= 100; k++)
        for (int i = 0; i <= 100; i++)
            for (int j = 0; j <= 100; j++)
                if (map[i][j] > map[i][k] + map[k][j])
                    map[i][j] = map[i][k] + map[k][j];
}