#include <iostream>
#include "CustomInt.h"

int main() {
  std::string in{"0:0:0:8"};
  CustomInt m1{in};
  std::cout << m1;

  //CustomInt m2{"0:0:0:12"};
  //CustomInt m2{std::numeric_limits<unsigned int>::max()};
  //std::cout << m2 << std::endl;

  //std::cout << m1.twos();

  CustomInt m3{m1*m1};
  std::cout << m3;
//  try {
//    CustomInt m3{m2 + m2};
//    std::cout << m3;
//  } catch (const std::runtime_error &ex) {
//    std::cout << ex.what() << std::endl;
//  }

  return 0;
}
