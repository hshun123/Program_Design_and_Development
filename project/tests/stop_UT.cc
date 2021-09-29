/**
 * @file stop_UT.cc
 *
 * @copyright 2020 3081 Eric Hwang.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../src/stop.h"
#include <gtest/gtest.h>
#include <math.h>
#include <iostream>
#include <ctime>
/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class StopTests : public ::testing::Test {
 protected:
  Stop* stop;
  virtual void SetUp() {
  stop = new Stop(0);
  }
  virtual void TearDown() {
    delete stop;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(StopTests, Constructor) {
    std::string expected_out_1 = "ID: 0\nPassengers waiting: 0\n";
    testing::internal::CaptureStdout();
    stop->Report(std::cout);
    std::string expected_out_2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, not the right Report!";

    EXPECT_EQ(stop->GetId(), 0) << "Failed, not the correct ID";
    EXPECT_EQ(stop->GetLongitude(), 44.973723) << "Failed, not the correct Longitude!";
    EXPECT_EQ(stop->GetLatitude(), -93.235365) << "Failed, not the correct Latitude!";
    EXPECT_EQ(stop->GetNumPassengersPresent(), 0) << "Failed, not the correct number of passenger!";

    Stop* stop2;
    stop2 = new Stop(1, 23.11, -87.234);
    std::string expected_out_3 = "ID: 1\nPassengers waiting: 0\n";
    testing::internal::CaptureStdout();
    stop2->Report(std::cout);
    std::string expected_out_4 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expected_out_3, expected_out_4) << "Failed, not the right Report!";

    EXPECT_EQ(stop2->GetId(), 1) << "Failed, not the correct ID";
    EXPECT_EQ(stop2->GetLongitude(), 23.11) << "Failed, not the correct Longitude!";
    EXPECT_EQ(stop2->GetLatitude(), -87.234) << "Failed, not the correct Latitude!";
    EXPECT_EQ(stop2->GetNumPassengersPresent(), 0) << "Failed, not the correct number of passenger!";
}

TEST_F(StopTests, AddPassengers){
    std::string expected_out_1 = "ID: 0\nPassengers waiting: 1\nName: Nobody\nDestination: -1\nTotal Wait:"
    " 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
    Passenger* passenger;
    passenger = new Passenger();
    stop->AddPassengers(passenger);
    testing::internal::CaptureStdout();
    stop->Report(std::cout);
    std::string expected_out_2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, not the correct Report!";

    EXPECT_EQ(stop->GetNumPassengersPresent(), 1) << "Failed, not the correct number of passenger!";

    Passenger* passenger1;
    passenger1 = new Passenger();
    stop->AddPassengers(passenger1);
    EXPECT_EQ(stop->GetNumPassengersPresent(), 2) << "Failed, not the correct number of passenger!";
}

TEST_F(StopTests, GetStopID) {
    EXPECT_EQ(stop->GetId(), 0);

    Stop * stop2;
    stop2 = new Stop(1, 23.11, -87.234);
    EXPECT_EQ(1, stop2->GetId()) << "Failed, not the correct ID!";

    Stop * stop3;
    stop3 = new Stop(-100);
    EXPECT_EQ(-100, stop3->GetId()) << "Failed, not the correct ID!";
}

TEST_F(StopTests, GetLongitudeLatitude) {
    Stop * temp_Stop;
    temp_Stop = new Stop(1, 45.99, -90.99);
    double expected_out_1 = 45.99;
    double expected_out_2 = -90.99;
    EXPECT_EQ(expected_out_1, temp_Stop->GetLongitude()) << "Failed, not the correct Longitude!";
    EXPECT_EQ(expected_out_2, temp_Stop->GetLatitude()) << "Failed, not the correct Latitude!";
}

TEST_F(StopTests, Update) {
  Passenger* passenger;
  passenger = new Passenger();
  stop->AddPassengers(passenger);
  stop->Update();
  std::string expected_out_1 = "ID: 0\nPassengers waiting: 1\nName: Nobody\nDestination: -1\nTotal Wait:"
  " 1\n\tWait at Stop: 1\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  stop->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, did not update properly!";

  for(int i = 0; i < 10; i++) {
    stop->Update();
  }
  std::string expected_out_3 = "ID: 0\nPassengers waiting: 1\nName: Nobody\nDestination: -1\nTotal Wait:"
  " 11\n\tWait at Stop: 11\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  stop->Report(std::cout);
  std::string expected_out_4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_4, expected_out_3) << "Failed, did not update properly!";
}

TEST_F(StopTests, GetNumPassengersPresent) {

  std::string expected_out_1 = "ID: 0\nPassengers waiting: 5\n"
  "Name: Nobody\nDestination: -1\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n"
  "Name: Nobody\nDestination: -1\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n"
  "Name: Nobody\nDestination: -1\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n"
  "Name: Nobody\nDestination: -1\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n"
  "Name: Nobody\nDestination: -1\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";

  Passenger* temp_pass;
  temp_pass = new Passenger();
  for(int i = 0; i < 5; i++) {
    stop->AddPassengers(temp_pass);
  }

  testing::internal::CaptureStdout();
  stop->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, not a correct report";
  EXPECT_EQ(stop->GetNumPassengersPresent(), 5) << "Failed, not the correct number of passenger!";
}

TEST_F(StopTests, Report) {
  Stop* stop3 = new Stop(10, 72.3, 38.75);

  std::string expected_out_1 = "ID: 10\nPassengers waiting: 0\n";
  testing::internal::CaptureStdout();
  stop3->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, not a correct report!";

  Passenger* passenger = new Passenger(10, "Eric Hwang");
  stop3->AddPassengers(passenger);
  std::string expected_out_3 = "ID: 10\nPassengers waiting: 1\n"
  "Name: Eric Hwang\nDestination: 10\nTotal Wait:"
  " 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  stop3->Report(std::cout);
  std::string expected_out_4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_4, expected_out_3) << "Failed, not a correct report!";

  for (int i = 0; i < 50; i++) {
    stop3->Update();
  }
  std::string expected_out_5 = "ID: 10\nPassengers waiting: 1\nName: Eric Hwang\nDestination: 10\nTotal Wait:"
  " 50\n\tWait at Stop: 50\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  stop3->Report(std::cout);
  std::string expected_out_6 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_6, expected_out_5) << "Failed, not a correct report!";
}
