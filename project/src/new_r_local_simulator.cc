/**
 * @file local_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/new_r_local_simulator.h"

#include <vector>
#include <list>

#include "src/bus.h"
#include "src/stop.h"
#include "src/route.h"
#include "src/rtest_passenger_generator.h"
#include "src/concreteBus_factory.h"

bool newrLocalSimulator::Start() {
  simulation_time_elapsed_ = 0;  // init, but also allows restart

  // int num_round_trips = 10;
  int num_round_trips = 1;
  for (int i = 0; i < num_round_trips; i++) {
    time_since_last_bus_generation_.push_back(0);
  }

  Stop ** EB_shortcut_stops = new Stop *[5];
  Stop ** WB_shortcut_stops = new Stop *[6];
  std::list<Stop *> EB_shortcut_stops_list;
  std::list<Stop *> WB_shortcut_stops_list;

  // Staticly defined objects get destroyed at end of Start()!
  // Must be dynamic...

  // CC Eastbound shortcut stops
  // West bank station
  Stop * stop_EBSC_1 = new Stop(0, 44.972392, -93.243774);
  // student union station
  Stop * stop_EBSC_2 = new Stop(1, 44.973580, -93.235071);

  Stop * stop_EBSC_3 = new Stop(3, 44.975837, -93.222174);  // before transit
  // Stop * stop_CC_EB_5 = new Stop(4, 44.980753, -93.180669);  // tway
  Stop * stop_EBSC_4 = new Stop(5, 44.983375, -93.178810);  // Fairgrounds

  Stop * stop_EBSC_5 = new Stop(7, 44.984630, -93.186352);  // SPSC

  // CC Westbound shortcut stops
  Stop * stop_WBSC_1 = new Stop(8, 44.984630, -93.186352);  // SPSC
  Stop * stop_WBSC_2 = new Stop(9, 44.984482, -93.181657);  // Buford & Gartner
  // Stop * stop_CC_WB_3 = new Stop(10, 44.983703, -93.178846);  // Fairgrounds
  Stop * stop_WBSC_3 = new Stop(11, 44.980663, -93.180808);  // Tway

  Stop * stop_WBSC_4 = new Stop(13, 44.978058, -93.229176);  // Ridder
  // Stop * stop_CC_WB_7 = new Stop(14, 44.978366, -93.236038);  // Jones-Eddy
  Stop * stop_WBSC_5 = new Stop(15, 44.974549, -93.236927);  // Bruininks
  Stop * stop_WBSC_6 = new Stop(16, 44.972638, -93.243591);  // Blegen

  EB_shortcut_stops_list.push_back(stop_EBSC_1);
  EB_shortcut_stops[0] = stop_EBSC_1;
  EB_shortcut_stops_list.push_back(stop_EBSC_2);
  EB_shortcut_stops[1] = stop_EBSC_2;
  EB_shortcut_stops_list.push_back(stop_EBSC_3);
  EB_shortcut_stops[2] = stop_EBSC_3;
  EB_shortcut_stops_list.push_back(stop_EBSC_4);
  EB_shortcut_stops[3] = stop_EBSC_4;
  EB_shortcut_stops_list.push_back(stop_EBSC_5);
  EB_shortcut_stops[4] = stop_EBSC_5;


  WB_shortcut_stops_list.push_back(stop_WBSC_1);
  WB_shortcut_stops[0] = stop_WBSC_1;
  WB_shortcut_stops_list.push_back(stop_WBSC_2);
  WB_shortcut_stops[1] = stop_WBSC_2;
  WB_shortcut_stops_list.push_back(stop_WBSC_3);
  WB_shortcut_stops[2] = stop_WBSC_3;
  WB_shortcut_stops_list.push_back(stop_WBSC_4);
  WB_shortcut_stops[3] = stop_WBSC_4;
  WB_shortcut_stops_list.push_back(stop_WBSC_5);
  WB_shortcut_stops[4] = stop_WBSC_5;
  WB_shortcut_stops_list.push_back(stop_WBSC_6);
  WB_shortcut_stops[5] = stop_WBSC_6;

  double * EB_shortcut_distances = new double[4];
  double * WB_shortcut_distances = new double[5];
  EB_shortcut_distances[0] = 4;
  EB_shortcut_distances[1] = 4;
  EB_shortcut_distances[2] = 19;
  EB_shortcut_distances[3] = 1;

  WB_shortcut_distances[0] = 2;
  WB_shortcut_distances[1] = 1;
  WB_shortcut_distances[2] = 2;
  WB_shortcut_distances[3] = 19;
  WB_shortcut_distances[4] = 3;


  std::list<double> EB_shortcut_probs;  // realistic .15, .3, .025, .05, .05, 0
  EB_shortcut_probs.push_back(.15);  // WB
  EB_shortcut_probs.push_back(.3);  // CMU
  // EB_shortcut_probs.push_back(.025); // O&W
  EB_shortcut_probs.push_back(.05);  // Pre-transit
  // EB_shortcut_probs.push_back(.05);  // post-transit
  EB_shortcut_probs.push_back(.01);  // State fair
  // EB_shortcut_probs.push_back(.01);  // Buford
  EB_shortcut_probs.push_back(0);  // SPSC - MUST BE 0
  //  is this always true?
  // If so, we may want to reduce the length of probs to_char_type
  //        remove possibility of generating passengers with nowhere to go

  std::list<double> WB_shortcut_probs;  // realistic .35, .05, .01, .01, .2, 0
  WB_shortcut_probs.push_back(.35);  // SPSC
  WB_shortcut_probs.push_back(.05);  // Buford
  // WB_shortcut_probs.push_back(.01);  // State fair
  WB_shortcut_probs.push_back(.01);  // post-transit
  // WB_shortcut_probs.push_back(.025);  // pre-transit
  WB_shortcut_probs.push_back(.05);  // Ridder
  // WB_shortcut_probs.push_back(.1);  // Jones-Eddy
  WB_shortcut_probs.push_back(.3);  // Bruininks
  WB_shortcut_probs.push_back(0);  // Blegen

  // Staticly defined objects get destroyed at end of Start()!
  // Must be dynamic...
  // RandomPassengerGenerator CC_EB_generator(CC_EB_probs, CC_EB_stops_list);
  // RandomPassengerGenerator CC_WB_generator(CC_WB_probs, CC_WB_stops_list);

  RtestPassengerGenerator * EB_shortcut_generator =
  new RtestPassengerGenerator (EB_shortcut_probs, EB_shortcut_stops_list);
  RtestPassengerGenerator * WB_shortcut_generator =
  new RtestPassengerGenerator (WB_shortcut_probs, WB_shortcut_stops_list);

  // Test to ensure generators are working
  // Helpful for debugging
  // CC_EB_generator.GeneratePassengers();
  // CC_WB_generator.GeneratePassengers();

  Route * EBSC = new Route("Campus Connector - Eastbound",
  EB_shortcut_stops, EB_shortcut_distances, 5, EB_shortcut_generator);
  Route * WBSC = new Route("Campus Connector - Westbound",
  WB_shortcut_stops, WB_shortcut_distances, 6, WB_shortcut_generator);

  prototype_routes_.push_back(EBSC);
  prototype_routes_.push_back(WBSC);

  prototype_routes_[0]->Report(std::cout);
  prototype_routes_[1]->Report(std::cout);

  bus_counters_.push_back(10000);

  // This will eventually be replaced by configuration/command line argument
  bus_start_timings_.push_back(10);

  // Do we want a bus on start? Or let the update handle this?
  // active_buses_.push_back(new Bus(std::to_string(bus_counters_[0]),
  //   prototype_routes[0].Clone(), prototype_routes[1].Clone(), 60, 1));
  // bus_counters_[0]++;

  return true;
}

bool newrLocalSimulator::Update() {
  // increase time
  simulation_time_elapsed_++;
  std::cout << "~~~~~~~~~~~~~ The time is now " << simulation_time_elapsed_;
  std::cout << " ~~~~~~~~~~~~~" << std::endl;

  // various route-indexed list iterators
  std::vector<int>::iterator bus_gen_timing_iter = bus_start_timings_.begin();
  std::vector<int>::iterator bus_counter_iter = bus_counters_.begin();
  std::vector<Route *>::iterator prototype_route_iter =
                                                     prototype_routes_.begin();

  // increase each time since last bus
  // various iterators parallel the time_since_last iterator
  for (std::vector<int>::iterator it = time_since_last_bus_generation_.begin();
      it != time_since_last_bus_generation_.end();
      it++, bus_gen_timing_iter++, bus_counter_iter++) {
    (*it)++;

    // if time since last [index] == bus gen timing[index]
    if (0 >= (*bus_gen_timing_iter)) {
      // create a new bus! routes are:
      // prototype_routes_[index * 2] & prototype_routes_[index * 2 + 1]
      Route * outbound = (*prototype_route_iter);
      prototype_route_iter++;
      Route * inbound = (*prototype_route_iter);
      prototype_route_iter++;
      // Eric
      ConcreteBusFactory tmp;
      active_buses_.push_back(tmp.ConcreteBusFactory::GenerateBus(
        std::to_string((*bus_counter_iter)),
        outbound->Clone(), inbound->Clone(), 1));
      (*bus_counter_iter)++;
      (*bus_gen_timing_iter) = 10;
    } else {
      prototype_route_iter++;
      prototype_route_iter++;
      (*bus_gen_timing_iter)--;
    }
  }

  // for each bus
  for (std::list<Bus *>::iterator bus_iter = active_buses_.begin();
      bus_iter != active_buses_.end(); bus_iter++) {
    // update bus
    (*bus_iter)->Update();
    // bus report
    (*bus_iter)->Report(std::cout);

    // REQUIRES USE OF IsTripComplete, which was not required
    // Buses which are "done" will just keep having Update() called
    //  Students MAY need to deal with this, not sure yet...
    // remove bus if trip is complete
    // if ((*bus_iter)->IsTripComplete()) {
    //  bus_iter = active_buses_.erase(bus_iter);
    //  bus_iter--;
    //}
  }

  // for each stop
  for (std::vector<Route *>::iterator route_iter = prototype_routes_.begin();
      route_iter != prototype_routes_.end(); route_iter++) {
    // update stop
    (*route_iter)->Update();
    (*route_iter)->Report(std::cout);
  }

  return true;
}
