//
// Created by angelos on 27/12/2019.
//

#include "CustomInt.h"

// default constructor
CustomInt::CustomInt() : bytes{new uint8_t[num_of_bytes]} {
  for (int i{num_of_bytes - 1}; i >= 0; i--)
    bytes[i] = 0x00;
}

// constructor a
CustomInt::CustomInt(const std::string &in) : bytes{new uint8_t[num_of_bytes]} {
  char char_temp{};
  int int_temp{};
  std::istringstream iss{in};

  for (int i{3}; i >= 0; i--) {
    iss >> std::hex >> int_temp;
    bytes[i] = int_temp % 0x100;
    iss >> char_temp;
  }
}

// constructor b
CustomInt::CustomInt(unsigned int in) : bytes{new uint8_t[4]} {
  /*bytes[3] = (in >> 24u) & 0xFFu;
  bytes[2] = (in >> 16u) & 0xFFu;
  bytes[1] = (in >> 8u) & 0xFFu;
  bytes[0] = in & 0xFFu;*/

  unsigned char mask(0xff);

  for (size_t i{}; i < num_of_bytes; i++)
    bytes[i] = (in >> i * CHAR_BIT) & mask;
}

// destructor
CustomInt::~CustomInt() { delete[] bytes; }

// copy constructor
CustomInt::CustomInt(const CustomInt &other)
    : bytes{new uint8_t[num_of_bytes]} {
  std::memcpy(bytes, other.bytes, num_of_bytes);
}

// copy assignment operator
CustomInt &CustomInt::operator=(const CustomInt &other) {
  if (this == &other)
    return *this;
  delete[] bytes;
  bytes = new uint8_t[num_of_bytes];
  std::memcpy(bytes, other.bytes, num_of_bytes);
  return *this;
}

// move constructor
CustomInt::CustomInt(CustomInt &&other) noexcept : bytes{other.bytes} {
  other.bytes = nullptr;
}

// move assignment operator
CustomInt &CustomInt::operator=(CustomInt &&other) noexcept {
  if (this == &other)
    return *this;
  delete[] bytes;
  bytes = new uint8_t[num_of_bytes];
  std::memcpy(bytes, other.bytes, num_of_bytes);
  return *this;
}

// + operator overload
CustomInt &CustomInt::operator+(const CustomInt &other) {

  std::bitset<num_of_bits> a = bytesToBitset();
  std::bitset<num_of_bits> b = other.bytesToBitset();
  std::bitset<num_of_bits> result;

  result = add(a, b);

  BitsetToBytes(result, bytes);

  return *this;
}

// - operator overload
CustomInt &CustomInt::operator-(CustomInt &other) {
  return *this + other.twos();
}

// * operator overload
CustomInt &CustomInt::operator*(CustomInt &other) {

  std::bitset<num_of_bits> a = bytesToBitset();
  std::bitset<num_of_bits> b = other.bytesToBitset();
  std::bitset<num_of_bits> result{}; // initialize result

  // While second number doesn't become 1
  while (b != 0) {
    // If second number becomes odd, add the first number to result
    if (b[0] == 1)
      result = add(result, a);

    // Double the first number and halve the second number
    a = a << 1;
    b = b >> 1;
  }

  BitsetToBytes(result, bytes);

  return *this;
}

// the 2nd complement
CustomInt &CustomInt::twos() {
  std::bitset<num_of_bits> num = bytesToBitset();

  size_t num_zero{};
  for (int i{num_of_bits}; i >= 0; i--) {
    if (num[i]) {
      num_zero = i;
      break;
    }
  }

  for (size_t i{}; i <= num_zero; i++)
    num.flip(i);

  // std::cout << "1's complement: " << num << std::endl;

  //  for two's complement go from right to left in
  //  ones complement and if we get 1 make, we make
  //  them 0 and keep going left when we get first
  //  0, make that 1 and go out of loop
  int i{};
  for (; i < num_of_bits; i++) {
    if (num[i] == 1)
      num.reset(i);
    else {
      num.set(i);
      break;
    }
  }

  // If No break : all are 1  as in 111  or  11111;
  // in such case, add extra 1 at beginning
  if (i == num_of_bits)
    throw std::runtime_error{"overflow error"};

  // std::cout << "1's complement: " << num << std::endl;
  // std::cout << "2's complement: " << num << std::endl;
  BitsetToBytes(num, bytes);
  return *this;
}

[[nodiscard]] std::bitset<CustomInt::num_of_bits>
CustomInt::bytesToBitset() const {

  std::bitset<num_of_bits> bits;

  for (size_t i{}; i < num_of_bytes; i++) {
    uint8_t cur = bytes[i];
    size_t offset = i * CHAR_BIT;

    for (size_t bit{}; bit < CHAR_BIT; bit++) {
      bits[offset] = cur & 1u;
      ++offset;   // Move to next bit in bits
      cur >>= 1u; // Move to next bit in array
    }
  }

  return bits;
}

void CustomInt::BitsetToBytes(std::bitset<num_of_bits> bits,
                              uint8_t bytes[num_of_bytes]) {

  std::bitset<num_of_bits> mask(0xff);

  for (int i = 0; i < num_of_bytes; ++i) {
    bytes[i] =
        static_cast<uint8_t>(((bits >> (CHAR_BIT * i)) & mask).to_ulong());
    // std::cout << std::hex << static_cast<int>(bytes[i]) << " ";
  }
  // std::cout << std::endl;
}

std::bitset<CustomInt::num_of_bits>
CustomInt::add(const std::bitset<num_of_bits> &a,
               const std::bitset<num_of_bits> &b) {

  std::bitset<num_of_bits> result;

  bool carry{}; // Initialize carry

  // Add all bits one by one
  for (size_t i{}; i < num_of_bits; i++) {

    // boolean expression for sum of 3 bits
    bool sum = a[i] ^ b[i] ^ carry;

    result[i] = sum;

    // boolean expression for 3-bit addition
    carry = (a[i] & b[i]) | (b[i] & carry) | (a[i] & carry);
  }

  // if overflow, then add a leading 1
  if (carry)
    // result = '1' + result;
    throw std::runtime_error{"overflow error"};

  return result;
}

std::ostream &operator<<(std::ostream &stream, const CustomInt &customInt) {
  for (size_t i{}; i < CustomInt::num_of_bytes; i++) {
    stream << std::showbase << std::setw(CustomInt::num_of_bytes) << std::hex
           << static_cast<int>(customInt.bytes[i]) << " ";
  }
  stream << std::endl;
  stream << customInt.bytesToBitset() << std::endl;

  return stream;
}