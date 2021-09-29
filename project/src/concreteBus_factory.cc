/**
 * @file concreteBus_factory.cc
 *
 * @copyright 2019 3081 Eric Hwang, All rights reserved.
 */

#include <string>

#include "src/bus.h"
#include "src/concreteBus_factory.h"

// the state for each strategy is set to 0
int ConcreteBusFactory::stt1_state = 0;
int ConcreteBusFactory::stt2_state = 0;
int ConcreteBusFactory::stt3_state = 0;

// Generate instance of bus depending on the bus type give
Bus* ConcreteBusFactory::GenerateBus(std::string name, Route * out, Route * in,
 double speed) {
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  speed_ = speed;

  smallCapacity = 30;  // the capacity for small bus is 30
  regularCapacity = 60;  // the capacity for regular bus is 60
  largeCapacity = 90;  // the capacity for large bus is 60

  // if the bustype passed is 1, small bus is generated with the capacity of 30
  // else if the bustype is 2, regular bus is generated with the capacity of 60
  // otherwise, large bus is generated with the capacity of 90

  // priority 3 bus depot refactoring pattern
  // below code are provided by instructor

  struct tm timeinfo;
  char buf[50];
  rawtime_ = time(&rawtime_);
  localtime_r(&rawtime_, &timeinfo);
  int currenthour = timeinfo.tm_hour;

  // If the current local time is: 6am or later but before 8 am
  // Deploy the bus using strategy 1
  // 8am or later but before 3pm
  // Deploy the bus using strategy 2
  // 3pm or later but before 8pm
  // Deploy the bus using strategy 3
  // Otherwise
  // Deploy a small bus

  if ((6 <= currenthour) && (currenthour < 8)) {
    strategy = 1;
    stt1_state++;  // state for the strategy increases
  } else if ((8 <= currenthour) && (currenthour < 15)) {
    strategy = 2;
    stt2_state++;  // state became to 1
  } else if ((15 <= currenthour) && (currenthour < 20)) {
    strategy = 3;
    stt3_state++;
  } else {
    strategy = 0;
  }

  // switch statemet to check which strategy to use depending on the current
  // local time
  switch (strategy) {
    case 1:
      if (stt1_state % 2 == 0) {  // state is odd number regular bus deployed
        return new RegularBus(name_, outgoing_route_, incoming_route_,
          regularCapacity, speed_, strategy);
      } else {
        return new SmallBus(name_, outgoing_route_, incoming_route_,
          smallCapacity, speed_, strategy);
      }
      break;
    case 2:
      if (stt2_state % 2 == 0) {  // state is odd num large bus deployed
        return new LargeBus(name_, outgoing_route_, incoming_route_,
          regularCapacity, speed_, strategy);
      } else {
        return new RegularBus(name_, outgoing_route_, incoming_route_,
          largeCapacity, speed_, strategy);
      }
      break;
    case 3:
      if (stt3_state % 3 == 1) {  // when the state is 1*n small bus deployed
        std::cout << "#########state: " << stt3_state << std::endl;
        return new SmallBus(name_, outgoing_route_, incoming_route_,
          smallCapacity, speed_, strategy);
      } else if (stt3_state % 3 == 2) {  // state is 2*n regular bus deployed
        std::cout << "#########state: " << stt3_state << std::endl;
        return new RegularBus(name_, outgoing_route_, incoming_route_,
          regularCapacity, speed_, strategy);
      } else {   // when the state is 2*n large bus deployed
        std::cout << "#########state: " << stt3_state << std::endl;
        return new LargeBus(name_, outgoing_route_, incoming_route_,
          largeCapacity, speed_, strategy);
      }
      break;
    default:  // small bus deployed by default
      return new SmallBus(name_, outgoing_route_, incoming_route_,
        smallCapacity, speed_, strategy);
  }
}
