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

TEST(narrowing, test_casting) {
  CustomInt m1{"0:1:0:0"};

  try {
    auto i = static_cast<uint16_t>(m1);
  } catch (const std::exception &e) {
    EXPECT_EQ(e.what(), std::string("narrowing error"));
  }
}