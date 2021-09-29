/**
 * @file route_UT.cc
 *
 * @copyright 2020 3081 Eric Hwang.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/data_structs.h"
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/route.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class RouteTests : public ::testing::Test {
protected:
  Route* route;
  Stop* first_Stop;
  Stop* second_Stop;
  Stop* third_Stop;
  std::list<Stop *> stop_list;
  Stop ** stops;
  std::list<double> probs;
  double * distances;
  PassengerGenerator *pass_generator;

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
    probs.push_back(.4);
    probs.push_back(.015);

    distances = new double[2];
    distances[0] = 100;
    distances[1] = 230;

    pass_generator = new RandomPassengerGenerator(probs, stop_list);
    route = new Route("Eric's route", stops, distances, 3, pass_generator);
  }

  virtual void TearDown() {
    delete route;
    delete first_Stop;
    delete second_Stop;
    delete third_Stop;
    delete distances;

    route = NULL;
    first_Stop = NULL;
    second_Stop = NULL;
    third_Stop = NULL;
    distances = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(RouteTests, Constructor) {
    std::string expected_output1 = "Eric's route";
    //Getters
    EXPECT_EQ(expected_output1, route-> GetName()) << "Incorrect name";
    EXPECT_EQ(stop_list, route-> GetStops()) << "Incorrect stop list";
    EXPECT_EQ(330, route-> GetTotalRouteDistance()) << "Incorrect TotalRouteDistance";
    EXPECT_EQ(0, route-> GetNextStopDistance()) << "Incorrect NextStopDistance";
    EXPECT_EQ(stops[0], route-> GetDestinationStop()) << "Incorrect DestinationStop";
    route->ToNextStop();
    EXPECT_EQ(100, route-> GetNextStopDistance()) << "Incorrect";
    EXPECT_EQ(stops[1], route-> GetDestinationStop()) << "Incorrect";
    // UpdateRouteData
    RouteData rtdata_test;
    route->UpdateRouteData();
    rtdata_test = route->GetRouteData();  // GetRouteData
    EXPECT_EQ(route->GetName(), rtdata_test.id);

    EXPECT_EQ((*rtdata_test.stops.begin()).id, std::to_string(stops[0]->GetId()));
};

TEST_F(RouteTests, IsAtEnd) {
  EXPECT_FALSE(route-> IsAtEnd()) << "It is not at the end"; // begining
  // There are 3 stops
  route -> ToNextStop();
  EXPECT_FALSE(route-> IsAtEnd()) << "It is not at the end";
  route -> ToNextStop();
  EXPECT_FALSE(route-> IsAtEnd()) << "It is not at the end";
  route -> ToNextStop();  // Reaches the end
  EXPECT_TRUE(route-> IsAtEnd()) << "It is at the end";
}

TEST_F(RouteTests, GetDestinationStop) {

  EXPECT_EQ(0, (route->GetDestinationStop())->GetId()) <<
  "Incorrect Destination Stop";

  route->ToNextStop();
  EXPECT_EQ(1, (route->GetDestinationStop())->GetId()) << "Incorrect Destination Stop";

  route->ToNextStop();
  EXPECT_EQ(2, (route->GetDestinationStop())->GetId()) << "Incorrect Destination Stop";

  EXPECT_NE(0, (route->GetDestinationStop())->GetId()) <<
  "Destination stop should have been changed";
}

TEST_F(RouteTests, GetTotalRouteDistance) {

  EXPECT_NE(0, route->GetTotalRouteDistance()) << "Incorrect initialization for Distance between";
  EXPECT_EQ(330, route->GetTotalRouteDistance()) << "Incorrect Distance between after moving to next distance between";

}

TEST_F(RouteTests, GetNextStopDistance) {
  EXPECT_EQ(0, route->GetNextStopDistance()) << "Incorrect Distance";
  route->ToNextStop();
  EXPECT_EQ(100, route->GetNextStopDistance()) << "Incorrect Distance after move";
  route->ToNextStop();
  EXPECT_EQ(230, route->GetNextStopDistance()) << "Incorrect Distance after move";

}
