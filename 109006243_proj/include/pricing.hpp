#ifndef PRICING_HPP
#define PRICING_HPP

#include <string.h>

#include "pii.hpp"
// elec lady road - disc/reg price
extern int maxStation;
void initMap();
void calcDist();
pii getShortestTransfer(int from, int type);
#endif