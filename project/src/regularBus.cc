/**
 * @file regularBus.cc
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */
#include "src/regularBus.h"
#include "src/bus.h"

//  This functions provide the informaiton of bus name, type,
// speed, distance to next stop and the information of its passegers.
void RegularBus::Report(std::ostream& out) {
  // iteration2 provided by instsructor
  struct tm timeinfo;
  char buf[50];
  rawtime_ = time(&rawtime_);
  localtime_r(&rawtime_, &timeinfo);

  out << "Name: " << name_ << std::endl;
  out << "Type: regular" << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Distance to next stop: " << distance_remaining_ << std::endl;
  out << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  // iteration2 additional requirement
  out << "Type: Regular" << std::endl;
  out << "Strategy: " << strategy_ << std::endl;
  out << "Time: " << asctime_r(&timeinfo, buf) << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
                                        it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}
