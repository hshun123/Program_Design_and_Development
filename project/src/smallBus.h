/**
 * @file smallBus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_SMALLBUS_H_
#define SRC_SMALLBUS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <iostream>
#include <list>
#include <string>

#include "src/bus.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for small bus.
 *
 * Declares functions used for large bus. A small bus has a capacity of 30.
 * Member function of the class provide the informaiton of bus name, type,
 * speed, distance to next stop and the information of its passegers.
 *
 */
class SmallBus : public Bus{
 public:
   /**
  *  @brief This is the constructor of the Regular Bus.
  *  @param[in] string name
  *  @param[in] Route * out
  *  @param[in] Route * in
  *  @param[in] int capacity
  *  @param[in] double speed
  *  @param[in] int strategy
  */
  SmallBus(std::string name, Route * out, Route * in, int capacity = 30,
    double speed = 1, int strategy = 0):
    Bus(name, out, in, capacity, speed, strategy) {}
    /**
   *  @brief The following function would show the current status of the Bus
   *  @param[in] std::ostream & out
   */
  void Report(std::ostream&) override;
};

#endif  // SRC_SMALLBUS_H_
