/**
 * @file bus.h
 *
 * @copyright 2020 3081 Eric Hwang, All rights reserved.
 */
#ifndef SRC_IOBSERVER_H_
#define SRC_IOBSERVER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include "src/data_structs.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief The main class for the  Observer.
 *
 * An observer interface which has a member function UpdateObserver
 * deifines the action to be taken when the bus provides data
 */
// The Observer (Abstract) Interface Class
class IObserver{
 public:
  /**
  * @brief pure virtual method for BusWebObserver
  *
  * @param[in] Busdata* info
  */
  virtual void UpdateObserver(BusData* info) = 0;
};

#endif  // SRC_IOBSERVER_H_
