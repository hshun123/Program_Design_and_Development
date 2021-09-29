/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/


#include <iostream>
#include <string>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the passenger.
 *
 * A passenger has name, destination stop id, which stop does he wait on,
 * time on bus, and his id. Member functions of the class provides the
 * information of where does the passenger get on the bus, wati and if
 * he is on the bus or not. It also update the status of the passenger.
 *
 */
class Passenger {   // : public Reporter {
 public:
  explicit Passenger(int = -1, std::string = "Nobody");
  void Update();
  void GetOnBus();
  /**
   * @brief Get the total number of waits of a passenger.
   *
   * This function will be used for wait counting purposes.
   *
   * @return the number of total waits of the passenger.
   */
  int GetTotalWait() const;
  bool IsOnBus() const;
  int GetDestination() const;
  void Report() const;
 private:
  std::string name_;
  int destination_stop_id_;
  int wait_at_stop_;
  int time_on_bus_;
  int id_;
  static int count_;  // global count, used to set ID for new instances
};
#endif  // SRC_PASSENGER_H_
