/**
 * @file bus.h
 *
 * @copyright 2020 3081 Eric Hwang, All rights reserved.
 */
#ifndef SRC_IOBSERVABLE_H_
#define SRC_IOBSERVABLE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>
#include "src/data_structs.h"
#include "src/IObserver.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class of the  IObservable class.
 *
 * This is the subject which maintains an IObservers which is list of
 * registered observers.
 */
class IObservable{
 private:
  std::vector<IObserver*> observe_;  // list of observers
  BusData info;  // bus data
 public:
   /**
  *  @brief The following function add the observer to the list
  *  @param[in] IObserver* observer
  */
  void RegisterObserver(IObserver* observer);
   /**
  *  @brief The following function clear the observer list
  */
  void ClearObservers();
   /**
  *  @brief The following function is called when the data is changed and
  * the observers need to be supplied with new data
  *  @param[in] BusData* info
  */
  void NotifyObservers(BusData* info);
};

#endif  // SRC_IOBSERVABLE_H_
