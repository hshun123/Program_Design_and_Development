#include "gtest/gtest.h"

#include <iostream>
#include <math.h>
#include <ctime>

#include "date.h"


class DateTest : public ::testing::Test {
 public:
  void SetUp( ) {
    // code here will execute just before the test ensues
	first_day = Date(2018, 9, 4);
	last_day = Date(2018, 12, 11);
  }
 protected:
  Date first_day;          // first day of classes
  Date last_day;           // last day of classes0
};



TEST_F(DateTest, PrintDateTests) {
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween

  Date birthday(1994,2,24);
  Date epo1(20800320);
  Date epo2(190011);
  Date m1 (1991,12,4);
  Date d1 (1991,1,20);

  std::string expected_out_1 = "1999-12-31\n";
  std::string expected_out_2 = "1776-07-04\n";
  std::string expected_out_3 = "2018-10-31\n";

  std::string expected_out_4 = "1994-02-24\n";
  std::string expected_out_5 = "1970-08-29\n";
  std::string expected_out_6 = "1970-01-03\n";
  std::string expected_out_7 = "1991-12-04\n";
  std::string expected_out_8 = "1991-01-20\n";

  testing::internal::CaptureStdout();
  y2k.PrintDate(true);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  ind_day.PrintDate(true);
  std::string output2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  best_holiday.PrintDate(true);
  std::string output3 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  std:: cout << birthday.GetDate() << std::endl;
  std::string output4 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  epo1.PrintDate(true);
  std::string output5 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  epo2.PrintDate(true);
  std::string output6 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  m1.PrintDate(true);
  std::string output7 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  d1.PrintDate(true);
  std::string output8 = testing::internal::GetCapturedStdout();



  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);

  EXPECT_EQ(output4, expected_out_4);
  EXPECT_EQ(output5, expected_out_5);
  EXPECT_EQ(output6, expected_out_6);
  EXPECT_EQ(output7, expected_out_7);
  EXPECT_EQ(output8, expected_out_8);
}

TEST_F(DateTest, PrintDateTestsWithoutNewline) {
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween

  Date epo(208074);
  Date epo1(00000000);

  std::string expected_out_1 = "1999-12-31";
  std::string expected_out_2 = "1776-07-04";
  std::string expected_out_3 = "2018-10-31";

  std::string expected_out_4 = "1970-01-03";
  std::string expected_out_5 = "1970-01-01";

  testing::internal::CaptureStdout();
  y2k.PrintDate(false);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ind_day.PrintDate(false);
  std::string output2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  best_holiday.PrintDate(false);
  std::string output3 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  epo.PrintDate(false);
  std::string output4 = testing::internal::GetCapturedStdout();


  testing::internal::CaptureStdout();
  epo1.PrintDate(false);
  std::string output5 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);
  EXPECT_EQ(output4, expected_out_4);
  EXPECT_EQ(output5, expected_out_5);
}

TEST_F(DateTest, PrintUsDateTests){
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween
  Date epo(208074);

  std::string expected_out_1 = "12-31-1999\n";
  std::string expected_out_2 = "07-04-1776\n";
  std::string expected_out_3 = "10-31-2018\n";
  std::string expected_out_4 = "01-03-1970\n";

  testing::internal::CaptureStdout();
  y2k.PrintUsDate(true);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ind_day.PrintUsDate(true);
  std::string output2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  best_holiday.PrintUsDate(true);
  std::string output3 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  epo.PrintUsDate(true);
  std::string output4 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);
  EXPECT_EQ(output4, expected_out_4);
}

TEST_F(DateTest, PrintUsDateTestsWithoutLine){
  Date y2k(1999, 12, 31);              // y2k
  Date ind_day(1776, 7, 4);            // US Independence
  Date best_holiday(2018, 10, 31);     // Halloween
  Date epo(208074);

  std::string expected_out_1 = "12-31-1999";
  std::string expected_out_2 = "07-04-1776";
  std::string expected_out_3 = "10-31-2018";
  std::string expected_out_4 = "01-03-1970";

  testing::internal::CaptureStdout();
  y2k.PrintUsDate(false);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ind_day.PrintUsDate(false);
  std::string output2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  best_holiday.PrintUsDate(false);
  std::string output3 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  epo.PrintUsDate(false);
  std::string output4 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output1, expected_out_1);
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(output3, expected_out_3);
  EXPECT_EQ(output4, expected_out_4);
}

/**
  *
  * Note, this is the only provided test case which actually uses our test fixture
  *
  * However, it is illegal to mix TEST() and TEST_F() in the same test case (file).
  *
  */

TEST_F(DateTest, DaysBetweenTests) {
  Date inde_day(1776, 7, 25);
  Date birthday(1994,2,24);
  Date ndate(2020,1,30);
  Date tmr(2020,1,31);
  Date test1(2016,1,1);
  Date test2(2016,3,1);
  Date test3(2016,1,1);

  EXPECT_EQ(inde_day.GetUsDate(), "07-25-1776") << "indepedent day";

  EXPECT_EQ(first_day.GetUsDate(), "09-04-2018") << "First day of class not setup properly";
  EXPECT_EQ(last_day.GetUsDate(), "12-11-2018") << "Last day of class not setup properly";
  EXPECT_EQ(last_day.GetDate(), "2018-12-11") << "Last day of class not setup properly";
  std::string s = birthday.GetUsDate();
  EXPECT_NE(birthday.GetDate(),s) << "Formatting is not correct";

  EXPECT_EQ(first_day.DaysBetween(last_day), 98) << "Days between is not calculated properly";
  EXPECT_EQ(ndate.DaysBetween(tmr), 1) << "Days between is not calculated properly";
  EXPECT_EQ(test1.DaysBetween(test2), 60) << "Days between is not calculated properly";
  EXPECT_EQ(test1.DaysBetween(test3), 0) << "Same date";
}

TEST_F(DateTest,CurrentTimeTest){
    std::time_t t = std::time(NULL);
    std:: tm * now = std::localtime(&t);
    std:: tm * now1 = std::localtime(&t);
    char s[100];
    sprintf(s, "%d-%02d-%02d", now->tm_year + 1900, now->tm_mon+1, now->tm_mday);
    EXPECT_EQ(Date().GetDate(), std::string(s));

    char test[100];
    sprintf(test,"%02d-%02d-%d", now1->tm_mon+1, now1->tm_mday,  now1->tm_year + 1900);

    EXPECT_EQ(Date().GetUsDate(), std::string(test));
}

TEST_F(DateTest,SubtractionTest){
  Date test1 (2016,2,27);
  Date test2 (2016,3,1);
  Date test3 (2015,6,15);
  Date test4 (2020,8,31);

  EXPECT_EQ((test1 - 2).GetDate(),"2016-02-25") << "- operation checking";
  EXPECT_EQ ((test2 - 2).GetDate(), "2016-02-28") << "- operation checking";
  EXPECT_EQ ((test3 - 5).GetDate(), "2015-06-10") << "- operation checking";
  EXPECT_EQ ((test4 - 30).GetUsDate(), "08-01-2020") << "- operation checking";
}

TEST_F(DateTest, AdditionTest){
  Date test1 (2016,2,27);
  Date test2 (2015,6,15);
  Date test3 (2020,8,31);
  EXPECT_EQ((test1 + 2).GetDate(),"2016-02-29") << "+ operation checking";
  EXPECT_EQ((test2 + 5).GetDate(), "2015-06-20") << "+ operation checking";
  EXPECT_EQ((test3 + 31).GetUsDate(), "10-01-2020") << "+ operation checking";


}


/**
  *
  * NOPE!  Can't test PRIVATE methods
  *
  */
/*
TEST(DateTest, ConvertFromDays) {
	Date convert_first_day = ConvertToDays(2458365);
	EXPECT_STREQ(convert_first_day.GetUsDate(), "09-04-2018");
}
*/
