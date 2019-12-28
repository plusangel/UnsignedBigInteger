//
// Created by angelos on 27/12/2019.
//

#ifndef CUSTOMINT_H
#define CUSTOMINT_H

#include <algorithm>
#include <bitset>
#include <climits>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

struct CustomInt {

  // default constructor
  CustomInt();

  // constructor a
  explicit CustomInt(const std::string &in);

  // constructor b
  explicit CustomInt(unsigned int in);

  // destructor
  ~CustomInt();

  // copy constructor
  CustomInt(const CustomInt &other);

  // copy assignment operator
  CustomInt &operator=(const CustomInt &other);

  // move constructor
  CustomInt(CustomInt &&other) noexcept;

  // move assignment operator
  CustomInt &operator=(CustomInt &&other) noexcept;

  // + operator overload
  CustomInt &operator+(const CustomInt &other);

  // - operator overload
  CustomInt &operator-(CustomInt &other);

  // * operator overload
  CustomInt &operator*(CustomInt &other);

  friend std::ostream &operator<<(std::ostream &stream,
                                  const CustomInt &customInt);

private:
  uint8_t *bytes;
  static const size_t num_of_bytes = 4;
  static constexpr size_t num_of_bits = num_of_bytes * CHAR_BIT;

  [[nodiscard]] std::bitset<num_of_bits> bytesToBitset() const;

  static void BitsetToBytes(std::bitset<num_of_bits> bits,
                            uint8_t bytes[num_of_bytes]);

  // the 2nd complement
  CustomInt &twos();

  // add to bitsets
  static std::bitset<CustomInt::num_of_bits>
  add(const std::bitset<num_of_bits> &a, const std::bitset<num_of_bits> &b);
};

#endif // CUSTOMINT_H
