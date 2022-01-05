#ifndef STATUS_HPP
#define STATUS_HPP
#include <string>
enum Status { Accept,
              Reject,
              Discount,
              Wait };
std::string outputRes(Status c);

#endif /* STATUS_HPP */