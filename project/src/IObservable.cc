/**
 * @file bus.cc
 *
 * @copyright 2019 3081 Eric Hwang, All rights reserved.
 */
 /*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/IObservable.h"
#include "src/bus.h"
using std::vector;
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// This function add observers to the IObserver list
void IObservable::RegisterObserver(IObserver* observer) {
  observe_.push_back(observer);
}

// This function clears the IObserver list
void IObservable::ClearObservers() {
  observe_.clear();
}

// This funciton is called when the data is changed and
// the observers need to be supplied with new data
void IObservable::NotifyObservers(BusData* info) {
  std::cout << "--------------notify observers------------------"<< std::endl;
  for (vector<IObserver*>::const_iterator iter = observe_.begin();
    iter != observe_.end(); ++iter) {
      if (*iter != 0) {
          (*iter)->UpdateObserver(info);  // UpdateObserver is called
      }
  }
}
