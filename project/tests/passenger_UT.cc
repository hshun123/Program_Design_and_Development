/*
 * Students: Use this file as a guide to writing your own unit tests.
 * See the project instructions for more information on which classes
 * and methods must be tested.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/passenger_loader.h"
#include "../src/passenger_unloader.h"
#include "../src/passenger.h"
#include "../src/stop.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class PassengerTests : public ::testing::Test {
protected:
  PassengerLoader* pass_loader;
  PassengerUnloader* pass_unloader;
  Passenger *passenger, *passenger1, *passenger2;

  virtual void SetUp() {
    pass_loader = new PassengerLoader();
    pass_unloader = new PassengerUnloader();
  }

  virtual void TearDown() {
    delete pass_loader;
    delete pass_unloader;
    delete passenger;
    passenger = NULL;
    pass_loader = NULL;
    pass_unloader = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(PassengerTests, Constructor) {
  passenger = new Passenger();
  EXPECT_EQ(passenger->IsOnBus(), false);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true);
};

//Eric
TEST_F(PassengerTests, NameCheck) {
  passenger1 = new Passenger(12, "Jone Doe");
  passenger2 = new Passenger(12, "Apple Bee");
  std::string expectedouput1 = "Name: Jone Doe";
  std::string expectedouput2 = "Name: Apple Bee";

  testing::internal::CaptureStdout();
  passenger1 -> Report(std :: cout);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  passenger2 -> Report(std :: cout);
  std::string output2 = testing::internal::GetCapturedStdout();

  int p1 = output1.find(expectedouput1);
  int p2 = output2.find(expectedouput2);

  EXPECT_GE (p1, 0);
  EXPECT_GE (p2, 0);
};

TEST_F(PassengerTests, TimeOnBus){
  passenger = new Passenger(12 , "Jone Doe");
  passenger -> GetOnBus();
  for(int i = 0; i < 5; i++){
    passenger-> Update();
  }

  EXPECT_EQ (passenger->GetTotalWait(), 6);
};


// Try
TEST_F(PassengerTests, Constructors) {
  passenger = new Passenger();
  std::string expected_out_1 = "Name: Nobody\nDestination: -1\nTotal Wait:"
  " 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, not the correct Report!";
  EXPECT_EQ(passenger->IsOnBus(), false) << "Failed, not on the bus";
  EXPECT_EQ(passenger->GetDestination(), -1)
            << "Failed, not the correct destination";
  EXPECT_EQ(passenger->GetTotalWait(), 0) << "Failed, not the correct # waits";

  passenger1 = new Passenger(100);
  std::string expected_out_3 = "Name: Nobody\nDestination: 100\nTotal Wait: 0"
  "\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger1->Report(std::cout);
  std::string expected_out_4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(passenger1->IsOnBus(), false) << "Failed, invalid ";
  EXPECT_EQ(passenger1->GetDestination(), 100)
            << "Failed, not the right destination for Default!";
  EXPECT_EQ(passenger1->GetTotalWait(), 0) << "Failed, not the right "
  "amount of wait for Default!";
  EXPECT_EQ(expected_out_4, expected_out_3) << "Failed for incorrect "
  "Default when only destination_id is passed";

  passenger2 = new Passenger(98, "");
  std::string expected_out_5 = "Name: Nobody\nDestination: 98\nTotal Wait: 0"
  "\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger2->Report(std::cout);
  std::string expected_out_6 = testing::internal::GetCapturedStdout();
  EXPECT_NE(expected_out_6, expected_out_5) << "Failed for incorrect "
  "Default when only destination_id and empty string is passed";

  Passenger* passenger3;
  passenger3 = new Passenger(99, "Eric");
  std::string expected_out_7 = "Name: Eric\nDestination: 99\nTotal Wait: 0"
  "\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger3->Report(std::cout);
  std::string expected_out_8 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_8, expected_out_7) << "Failed to Report";

}

TEST_F(PassengerTests, Update) {
  passenger = new Passenger(5, "Eric");
  EXPECT_EQ(passenger->IsOnBus(), false);
  std::string expected_out_1 = "Name: Eric\nDestination: "
  "5\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, incorrect report";
  passenger->Update();
  EXPECT_EQ(passenger->IsOnBus(), false) << "Failed, not on the bus";
  passenger->GetOnBus();  // get on the bus
  // update 10 times after get on the bus
  for (int i = 0; i < 10; i++) {
    passenger->Update();
  }
  EXPECT_EQ(passenger->GetTotalWait(), 12) << "Failed, not correct total wait";
}

TEST_F(PassengerTests, GetOnBusTest) {

  passenger = new Passenger(3081, "Professor Dan");
  EXPECT_EQ(passenger->IsOnBus(), false);
  std::string expected_out_1 = "Name: Professor Dan\nDestination: "
  "3081\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, incorrect report";
  passenger->Update();
  EXPECT_EQ(passenger->IsOnBus(), false) << "Failed, not on the bus";
  passenger->GetOnBus();  // get on the bus
  EXPECT_EQ(passenger->IsOnBus(), true);
  std::string expected_out_3 = "Name: Professor Dan\nDestination: "
  "3081\nTotal Wait: 2\n\tWait at Stop: 1\n\tTime on bus: 1\n";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string expected_out_4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_4, expected_out_3) << "Failed, not correct report";
}

TEST_F(PassengerTests, GetTotalWaitTest) {

  passenger = new Passenger(1207, "Eric Hwang");
  std::string expected_out_1 = "Name: Eric Hwang\nDestination: 1207"
  "\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, incorrect report";
  EXPECT_EQ(passenger->GetTotalWait(), 0) << "Failed, not correct total wait";
  passenger->Update();
  EXPECT_EQ(passenger->GetTotalWait(), 1) << "Failed, not correct total wait";
  passenger->Update();
  passenger->GetOnBus();
  std::string expected_out_5 = "Name: Eric Hwang\nDestination: 1207"
  "\nTotal Wait: 3\n\tWait at Stop: 2\n\tTime on bus: 1\n";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string expected_out_6 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_6, expected_out_5) << "Failed, incorrect report";

  EXPECT_EQ(passenger->GetTotalWait(), 3) << "Failed, not correct tital wait";
}

TEST_F(PassengerTests, IsOnBusTest) {
  passenger = new Passenger(15, "Ann Marie");
  EXPECT_EQ(passenger->IsOnBus(), false) << "Failed, is not on bus";
  std::string expected_out_1 = "Name: Ann Marie\nDestination: 15\n"
  "Total Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, incorrect report";
  passenger->Update();
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true) << "Failed, is on the bus";
  std::string expected_out_3 = "Name: Ann Marie\nDestination: 15\n"
  "Total Wait: 2\n\tWait at Stop: 1\n\tTime on bus: 1\n";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string expected_out_4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_4, expected_out_3) << "Failed, incorrect report";
}

TEST_F(PassengerTests, GetDestinationTest) {

  passenger = new Passenger(15, "Mark");
  std::string expected_out_1 = "Name: Mark\nDestination: 15"
  "\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed Report in "
  "GetDestinationTest() Test, not the right Report!";
  passenger1 = new Passenger(-100, "James");
  std::string expected_out_3 = "Name: James\nDestination: -100"
  "\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger1->Report(std::cout);
  std::string expected_out_4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_4, expected_out_3) << "Failed, incorrect report";
  EXPECT_EQ(passenger->GetDestination(), 15) << "Failed, "
  "Destination id does not match!";
  EXPECT_EQ(passenger1->GetDestination(), -100) << "Failed, "
  "Destination id does not match!";

}
TEST_F(PassengerTests, ReportTest) {
  passenger1 = new Passenger(94, "BTS");
  std::string expected_out_1 = "Name: BTS\nDestination: 94\n"
  "Total Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  passenger1->Report(std::cout);
  std::string expected_out_2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out_2, expected_out_1) << "Failed, incorrect report";

}
