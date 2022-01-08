#ifndef PRICING_HPP
#define PRICING_HPP

#include <string.h>

#include "minheap.hpp"
#include "pii.hpp"
#include "station.hpp"
#include "vector.hpp"
// elec lady road - disc/reg price
extern int maxStation;
extern int costForDisc;
extern Station *station;
void initMap(int c);
void calcDist();
// void maxTransferOp();
// int getTransferMaxStation(int bt);
// pii getShortestTransfer(int from, int type, int minTran);
// void Transfer(int from, int to, int type, int amo);
#endif