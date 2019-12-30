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
CustomInt &CustomInt::operator-(const CustomInt &other) {

  std::bitset<num_of_bits> a = bytesToBitset();
  std::bitset<num_of_bits> b = other.bytesToBitset();
  std::bitset<num_of_bits> result{};

  result = subtract(a, b);
  BitsetToBytes(result, bytes);

  return *this;
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

template <size_t N> int top_bit_set(const std::bitset<N> &a) {
  int i;
  for (i = N - 1; i >= 0; i--)
    if (a.test(i))
      break;
  return i;
}

// / operator overload
CustomInt &CustomInt::operator/(CustomInt &other) {
  std::bitset<num_of_bits> dividend = bytesToBitset();
  std::bitset<num_of_bits> divisor = other.bytesToBitset();
  std::bitset<num_of_bits> quotient{};

  int divisor_size = top_bit_set<num_of_bits>(divisor);

  if (divisor_size < 0)
    throw std::logic_error{"divide by zero"};

  int bit;
  while ((bit = top_bit_set<num_of_bits>(dividend)) >= divisor_size) {
    quotient.set(bit - divisor_size);
    dividend ^= divisor << (bit - divisor_size);
  }

  BitsetToBytes(quotient, bytes);

  return *this;
}

// % operator overload
CustomInt &CustomInt::operator%(CustomInt &other) {
  std::bitset<num_of_bits> dividend = bytesToBitset();
  std::bitset<num_of_bits> divisor = other.bytesToBitset();
  std::bitset<num_of_bits> quotient{};

  int divisor_size = top_bit_set<num_of_bits>(divisor);

  if (divisor_size < 0)
    throw std::logic_error{"divide by zero"};

  int bit;
  while ((bit = top_bit_set<num_of_bits>(dividend)) >= divisor_size) {
    quotient.set(bit - divisor_size);
    dividend ^= divisor << (bit - divisor_size);
  }

  BitsetToBytes(dividend, bytes);

  return *this;
}

bool CustomInt::operator==(const CustomInt &other) const {
  for (size_t i{}; i < num_of_bytes; i++) {
    return bytes[i] == other.bytes[i];
  }
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

std::bitset<CustomInt::num_of_bits>
CustomInt::subtract(const std::bitset<num_of_bits> &a,
                    const std::bitset<num_of_bits> &b) {

  std::bitset<num_of_bits> result;

  bool borrow{}; // Initialize borrow

  // Add all bits one by one
  for (size_t i{}; i < num_of_bits; i++) {

    // boolean expression for sum of 3 bits
    bool dif = a[i] ^ b[i] ^ borrow;

    result[i] = dif;

    // boolean expression for 3-bit addition
    borrow = (!a[i] & borrow) | (!a[i] & b[i]) | (b[i] & borrow);
  }

  // if overflow, then add a leading 1
  if (borrow)
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