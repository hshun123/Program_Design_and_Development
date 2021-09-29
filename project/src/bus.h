/**
 * @file bus.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/


#include <stdio.h>
#include <time.h>
#include <iostream>
#include <list>
#include <string>


#include "src/data_structs.h"

#include "src/passenger.h"
#include "src/passenger_loader.h"
#include "src/passenger_unloader.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/IObservable.h"

class PassengerUnloader;
class PassengerLoader;
class Route;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the Bus.
 *
 * A bus factory has name, outgoing routes, in going routes, speed,
 * and the remaining distance to next stop. Member functions provide
 * neccessary information about the bus.
 */

class Bus : public IObservable {
 public:
   /**
  *  @brief This is the constructor of Bus.
  *  @param[in] string name
  *  @param[in] Route * out
  *  @param[in] Route * in
  *  @param[in] int capacity
  *  @param[in] double speed
  *  @param[in] int strategy
  */
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                        double speed = 1, int strategy = 0);
  bool IsTripComplete();
  bool LoadPassenger(Passenger *);  // returning revenue delta
  /**
   *  @brief The following function would move the Bus
   *  @return bool to indicate if Bus has arrived at a
   * Stop or has to continue moving.
   */
  bool Move();
  void Update();
  // set virtual, Report function override for factory
  virtual void Report(std::ostream&) = 0;

  // Vis Getters
  void UpdateBusData();
  BusData GetBusData() const;
  std::string GetName() const { return name_; }
  Stop * GetNextStop() const { return next_stop_; }
  size_t GetNumPassengers() const { return passengers_.size(); }
  int GetCapacity() const { return passenger_max_capacity_; }

 protected:  // changed for factory
  int UnloadPassengers();  // returning revenue delta
  // bool Refuel();
  PassengerUnloader * unloader_;
  PassengerLoader * loader_;
  std::list<Passenger *> passengers_;
  int passenger_max_capacity_;
  // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
  std::string name_;
  double speed_;  // could also be called "distance travelled in one time step"
  Route * outgoing_route_;
  Route * incoming_route_;
  double distance_remaining_;  // when negative?, unload/load procedure occurs
                              // AND next stop set
  Stop * next_stop_;
  // bool trip_complete_;  // [DERIVED data] when BOTH routes are at end, trip
  // is complete
  // Vis data for bus
  BusData bus_data_;
  // iteration2
  int strategy_;
  time_t rawtime_;
};
#endif  // SRC_BUS_H_
