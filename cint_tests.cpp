//
// Created by angelos on 30/12/2019.
//

#include "CustomInt.h"
#include "gtest/gtest.h"

TEST(equal, test_operators) {
  CustomInt m1{"0:0:0:a"};
  CustomInt m2{"0:0:0:a"};

  EXPECT_EQ(m1 == m2, true);
}

TEST(addition, test_operators) {
  CustomInt m1{"0:0:0:a"};
  CustomInt m2{"0:0:0:5"};

  CustomInt res{"0:0:0:f"};

  EXPECT_EQ((m1 + m2) == res, true);
}

TEST(subtraction, test_operators) {
  CustomInt m1{"0:0:0:a"};
  CustomInt m2{"0:0:0:f"};

  CustomInt res{"0:0:0:5"};

  EXPECT_EQ((m2 - m1) == res, true);
}

TEST(multiplication, test_operators) {
  CustomInt m1{"0:0:0:3"};
  CustomInt m2{"0:0:0:5"};

  CustomInt res{"0:0:0:f"};

  EXPECT_EQ((m1 * m2) == res, true);
}

TEST(division, test_operators) {
  CustomInt m1{"0:0:0:a"};
  CustomInt m2{"0:0:0:5"};

  CustomInt res{"0:0:0:2"};

  EXPECT_EQ((m1 / m2) == res, true);
}

TEST(modulo, test_operators) {
  CustomInt m1{"0:0:0:a"};
  CustomInt m2{"0:0:0:5"};

  CustomInt res{"0:0:0:0"};

  EXPECT_EQ((m1 % m2) == res, true);
}