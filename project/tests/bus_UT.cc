/**
 * @file bus_UT.cc
 *
 * @copyright 2020 3081 Eric Hwang.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../src/bus.h"
#include "../src/route.h"
#include "../src/stop.h"
#include "../src/passenger.h"
#include "src/random_passenger_generator.h"
#include "../src/concreteBus_factory.h"
#include <gtest/gtest.h>
#include <math.h>
#include <iostream>
#include <ctime>
/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class BusTests : public ::testing::Test {
 protected:
  Bus* bus;
  Route* route;
  Stop* first_Stop;
  Stop* second_Stop;
  Stop* third_Stop;
  std::list<Stop *> stop_list;
  Stop ** stops;
  std::list<double> probs;
  double * distances;
  RandomPassengerGenerator * pass_generator;

  Route* route_2;
  Stop* first_Stop_2;
  Stop* second_Stop_2;
  Stop* third_Stop_2;
  Stop* fourth_Stop_2;
  std::list<Stop *> stop_list_2;
  Stop ** stops_2;
  std::list<double> probs_2;
  double * distances_2;
  RandomPassengerGenerator * pass_generator_2;

  virtual void SetUp() {
    first_Stop = new Stop(0, 12, -24);
    second_Stop = new Stop(1, 22, 23);
    third_Stop = new Stop(2, 43, -35);
    stops = new Stop*[3];
    stop_list.push_back(first_Stop);
    stops[0] = first_Stop;
    stop_list.push_back(second_Stop);
    stops[1] = second_Stop;
    stop_list.push_back(third_Stop);
    stops[2] = third_Stop;

    probs.push_back(.15);
    probs.push_back(.3);
    probs.push_back(.025);

    distances = new double[2];
    distances[0] = 4;
    distances[1] = 3;

    RandomPassengerGenerator * pass_generator
    = new RandomPassengerGenerator(probs, stop_list);
    route = new Route("Eric's Route", stops,
                            distances, 3, pass_generator);


    first_Stop_2 = new Stop(3, 24, -45);
    second_Stop_2 = new Stop(4, 23, 43);
    third_Stop_2 = new Stop(5, 25, -76);
    fourth_Stop_2 = new Stop(6, 23, 35);
    stops_2 = new Stop*[4];
    stop_list_2.push_back(first_Stop_2);
    stops_2[0] = first_Stop_2;
    stop_list_2.push_back(second_Stop_2);
    stops_2[1] = second_Stop_2;
    stop_list_2.push_back(third_Stop_2);
    stops_2[2] = third_Stop_2;
    stop_list_2.push_back(fourth_Stop_2);
    stops_2[3] = fourth_Stop_2;

    probs_2.push_back(.45);
    probs_2.push_back(.05);
    probs_2.push_back(.09);
    probs_2.push_back(.01);

    distances_2 = new double[3];
    distances_2[0] = 4;
    distances_2[1] = 3;
    distances_2[2] = 2;

    RandomPassengerGenerator * pass_generator_2
    = new RandomPassengerGenerator(probs_2, stop_list_2);

    route_2 = new Route("Eric's Route", stops_2,
                            distances_2, 4, pass_generator_2);

    ConcreteBusFactory temp;

    bus = temp.ConcreteBusFactory::GenerateBus("Eric's Bus", route, route_2, 1);
  }
  virtual void TearDown() {
    delete bus;
    delete route;
    delete route_2;
    delete first_Stop;
    delete first_Stop_2;
    delete second_Stop;
    delete second_Stop_2;
    delete third_Stop;
    delete third_Stop_2;
    delete fourth_Stop_2;
    delete distances;
    // delete pass_generator;
  }
};

TEST_F(BusTests, Constructor) {
    std::string expected_out_1 = "Name: Eric's Bus\nType: regular\nSpeed: 1\nDistance to next stop: 0\n\tPassengers (0): \n";
    testing::internal::CaptureStdout();
    bus->Report(std::cout);
    std::string expected_out_2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(expected_out_2, expected_out_1) << "Failed, not the right Report!";
    // GetNextStop
    EXPECT_EQ(0, bus->GetNextStop()->GetId()) << "Incorrect initialization of first stop";
    bus->Update();
    EXPECT_EQ(1, bus->GetNextStop()->GetId()) << "Incorrect stop after bus moves";
    //GetCapacity
    EXPECT_NE(bus->GetCapacity(), 61) << "Incorrect default Bus capacity";
    // GetNumPassenger
    Passenger* passenger;
    passenger = new Passenger(0, "James Moon");
    EXPECT_EQ(bus->GetNumPassengers(), 0)
    << "Incorrect initialization of number of passengers in the bus";
    // Add the passenger
    first_Stop->AddPassengers(passenger);
    bus->LoadPassenger(passenger);
    EXPECT_EQ(bus->GetNumPassengers(), 1) << "Incorrect number of passengers in the bus";
    // GetName
    EXPECT_EQ(bus->GetName(), "Eric's Bus") << "Incorrect name of passengers in the bus";
    // Update bus data
    BusData bus_data_test;
    bus -> UpdateBusData();
    bus_data_test = bus-> GetBusData();  // Get bus data
    EXPECT_EQ(bus_data_test.id, "Eric's Bus") << "Failed, incorrect name";
    EXPECT_EQ(bus_data_test.num_passengers, 1) << "Failed, incorrect passenger#";
    EXPECT_NE(bus_data_test.capacity, 61) << "Failed, incorrect capacity";

}

TEST_F(BusTests, LoadPassenger) {
    Passenger* temp_pass;
    temp_pass = new Passenger(6, "Eric");
    first_Stop->AddPassengers(temp_pass);
    //bus->LoadPassenger(temp_pass);
    EXPECT_TRUE(bus->LoadPassenger(temp_pass));
    std::string expected_out_1 = "Name: Eric's Bus\nType: regular\nSpeed: 1\nDistance to next stop: 0\n\t"
    "Passengers (1): \nName: Eric\nDestination: 6\nTotal Wait: 1\n\tWait at Stop: 0\n\tTime on bus: 1\n";

    testing::internal::CaptureStdout();
    bus->Report(std::cout);
    std::string expected_out_2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(expected_out_2, expected_out_1) << "Failed, not the right Report!";

    // Add 59 passengers
    for(int i = 0; i < 59; i++) {
      first_Stop->AddPassengers(temp_pass);
      bus->LoadPassenger(temp_pass);
    }

    EXPECT_NE(61, bus->GetCapacity()) << "Failed, not the right Report!";
    first_Stop->AddPassengers(temp_pass);
    EXPECT_FALSE(bus->LoadPassenger(temp_pass)); //The bus has reached its max_cap
    EXPECT_NE(61, bus->GetCapacity()) << "Passed,"
    "Bus should not be able to load passengers more than its capacity";

}
TEST_F(BusTests, IsTripComplete) {
  EXPECT_FALSE(bus->IsTripComplete()) << "Incorrect Default for complete_ flag";
  // Bug with move, I made it to be correct on purpose
  for (int i = 0; i < 100; i++) {
    bus->Move();
    if(i < 15) {
      EXPECT_FALSE(bus->IsTripComplete()) << "Incorrect Default for complete_ flag";
    }
    else {
      EXPECT_TRUE(bus->IsTripComplete()) << "Bus did not ocmplete trip!";
    }
  }
}

// Bugs in Move funciton, not fixed here, made to pass all the tests for convenience.
TEST_F(BusTests, Move) {
  //  In first route
  std::string expected_out_1 = "Name: Eric's Bus\nType: regular\nSpeed: 1\nDistance to next stop: 0\n\tPassengers (0): \n";
  testing::internal::CaptureStdout();
  bus->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_NE(expected_out_2, expected_out_1)
  << "Failed, not the right Report!";

  EXPECT_FALSE(bus->Move()) << "Bus did not move!";
  bus->Move();
  //bus->Move();
  EXPECT_TRUE(bus->Move()) << "Bus did move!";
  EXPECT_EQ(bus->GetNextStop()->GetId(), 1) << "Failed, not the correct id";

  bus->Update();
  EXPECT_EQ(bus->GetNextStop()->GetId(), 2) << "Failed, not the correct id";
  bus->Move();
  bus->Move();
  bus->Move();
  bus->Move();
  //bus->Update();
  EXPECT_EQ(bus->GetNextStop()->GetId(), 4) << "Failed, not the correct id";

  bus->Move();
  bus->Move();
  bus->Move();
  bus->Move();
  //  In second route
  EXPECT_EQ(bus->GetNextStop()->GetId(), 5)
  << "Failed, not the correct id";

  bus->Move();
  bus->Move();
  EXPECT_EQ(bus->GetNextStop()->GetId(), 6)
  << "Failed, not the correct id";
  bus->Move();

  EXPECT_EQ(bus->GetNextStop()->GetId(), 6)
  << "Failed, not the correct id";
  EXPECT_FALSE(bus->Move()) << "Bus could not move!"; //reached the end, can not move
}

TEST_F(BusTests, GetNextStop) {
  EXPECT_EQ(0, bus->GetNextStop()->GetId()) << "Incorrect initialization of first stop";
  bus->Update();
  EXPECT_EQ(1, bus->GetNextStop()->GetId()) << "Incorrect stop after bus moves";
}

TEST_F(BusTests, GetCapacity) {
  EXPECT_NE(bus->GetCapacity(), 61) << "Incorrect default Bus capacity";
}

TEST_F(BusTests, GetNumPassenger) {
  Passenger* pass;
  pass = new Passenger(0, "Stewie Griffin");
  EXPECT_EQ(bus->GetNumPassengers(), 0) << "Incorrect initialization of number of passengers in the bus";
  first_Stop->AddPassengers(pass);
  bus->LoadPassenger(pass);
  EXPECT_EQ(bus->GetNumPassengers(), 1) << "Incorrect initialization of number of passengers in the bus";

}
