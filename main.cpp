#include <iostream>
#include "CustomInt.h"

int main() {
  std::string in{"0:0:0:a"};
  CustomInt m1{in};
  std::cout << m1;

  CustomInt m2{"0:0:0:5"};
  // CustomInt m2{std::numeric_limits<unsigned int>::max()};
  std::cout << m2;

  // std::cout << m1.twos();

  CustomInt m3{"0:0:0:f"};
  std::cout << m3;

  if ((m1 + m2) == m3)
    std::cout << "Pass" << std::endl;

  if (m1 == m2)
    std::cout << "Pass" << std::endl;

  //  try {
  //    CustomInt m3{m2 + m2};
  //    std::cout << m3;
  //  } catch (const std::runtime_error &ex) {
  //    std::cout << ex.what() << std::endl;
  //  }

  return 0;
}
