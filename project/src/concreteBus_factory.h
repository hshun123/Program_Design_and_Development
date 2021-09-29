/**
 * @file concreteBus_factory.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */
#ifndef SRC_CONCRETEBUS_FACTORY_H_
#define SRC_CONCRETEBUS_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <iostream>
#include <list>
#include <string>

#include "src/bus.h"
#include "src/smallBus.h"
#include "src/regularBus.h"
#include "src/largeBus.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the Concrete Bus Factory.
 *
 * A concrete bus factory has name, outgoing routes, in going routes,
 * which bus type is generates and the capcacity for each type of bus.
 * Bus depot is implemeted so that different type of bus are created depends
 * on the current local time.
 * The concrete bus factory helps when creating instances of derived classes,
 * which are small, regular and large.
 */

class ConcreteBusFactory {
 public:
   /**
  * @brief Generate instance of bus depending on the bus type give.
  *
  * This function will be used for generating bus depending on bus type.
  *
  * @param[in] string name
  * @param[in] Route * out
  * @param[in] Route * in
  * @param[in] int busType
  * @param[in] double speed
  * @return the instance of bus according to the bus type.
  */
  Bus* GenerateBus(std::string name, Route * out, Route * in, double speed);

  // static variables for 3 strategies states
  static int stt1_state;
  static int stt2_state;
  static int stt3_state;

 private:
  std::string name_;
  double speed_;  // could also be called "distance travelled in one time step"
  Route * outgoing_route_;
  Route * incoming_route_;
  int smallCapacity;  // small capacity, used to set capacity for small buses
  int regularCapacity;  // the capacity, used to set capacity for regular buses
  int largeCapacity;  // the capacity, used to set capacity for large buses
  // int busType_;  // the bus type, used to figure the type of bus
  time_t rawtime_;  // tiem used to check the current local time
  int strategy;  // the strategy for bus depot.
};

#endif  // SRC_CONCRETEBUS_FACTORY_H_
