#include "status.hpp"
std::string outputRes(Status c) {
    if (c == Accept) return "\naccept\n";
    if (c == Discount) return "\ndiscount ";
    if (c == Wait) return "\nwait\n";
    return "\nreject\n";
}