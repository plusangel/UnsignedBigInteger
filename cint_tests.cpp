//
// Created by angelos on 30/12/2019.
//

#include "CustomInt.h"
#include "gtest/gtest.h"

TEST(addition, operators) {
  CustomInt m1{"0:0:0:a"};
  CustomInt m2{"0:0:0:5"};

  CustomInt res{"0:0:0:f"};

  EXPECT_EQ((m1 + m2) == res, true);
}
