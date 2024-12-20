#include "bigint.h"
#include <cstring>
#include <iostream>

namespace {
/*!
 * \brief printBits вывод бит числа
 * \param value - число представленное в двоичной системе (10 = 1010)
 * \param size - размер байт выделенное под число
 * \value число выводится в привычном виде слева направо старшие биты и байты
 * (00000000 00000000 00000000 00001010), но хранится по другому Число хранится
 * в системе little-endian (00001010 00000000 00000000 00000000) Старший бит
 * слева младший справа ( 00001010 ) --> левый ноль(первый) старший бит, крайний
 * правый 0 младший бит
 */
void printBits(const char *value, unsigned int size) {
  for (int i = size - 1; i >= 0; --i) {
    unsigned char tmp = value[i];
    for (int j = 7; j >= 0; --j) {
      std::cout << ((tmp >> j) & 0x1);
    }
    std::cout << '\t';
  }
  std::cout << std::endl;
}

void invertBits(char *value, unsigned int size) {
  for (int i = size - 1; i >= 0; --i) {
    value[i] = ~value[i];
  }
}

} // namespace

BigInt::BigInt() {
  capacity = size = 1;
  value = new char[capacity];
  value[0] = 0;
}

BigInt::BigInt(const BigInt &other) {}

BigInt::BigInt(BigInt &&other) {}

BigInt::BigInt(int val) {
  capacity = size = sizeof(int);
  value = new char[capacity];
  sign = (val > 0) ? true : false;

  //! берем число по модулю
  val = std::abs(val);

  std::memcpy(value, &val, capacity);
  ::printBits(value, capacity);
  resize();
}

BigInt::BigInt(const char *val) {
  if (!val || std::strlen(value) == 0) {
    throw std::invalid_argument("empty string");
  }
  //! TODO
}

BigInt::~BigInt() { delete[] value; }

void BigInt::resize() {
  for (int i = size - 1; i >= 0; --i) {
    if (static_cast<int>(value[i]) == 0x0) {
      --size;
    } else
      break;
  }
}

BigInt BigInt::operator+(const BigInt &other) {
  //! max size
  auto ms = std::max(size, other.size);
  char *result = new char[ms + 1];
  int carry = 0;
  for (unsigned i = 0; i < ms; ++i) {
    int byte1 = (i < size) ? static_cast<unsigned char>(value[i]) : 0;
    int byte2 =
        (i < other.size) ? static_cast<unsigned char>(other.value[i]) : 0;
    auto sum = byte1 + byte2 + carry;
    std::memcpy(&result[i], &sum, 1);
    carry = (sum >> 8) & 0x1;
  }
  BigInt res;
  if (carry > 0) {
    std::memcpy(&result[ms], &carry, 1);
  }
  ::printBits(result, ms + 1);
  res.sign = true;
  res.value = result;
  res.capacity = res.size = ms + 1;
  res.resize();
  return res;
}

BigInt &BigInt::operator+=(const BigInt &other) {}

BigInt BigInt::operator-(const BigInt &other) {}

BigInt BigInt::operator-=(const BigInt &other) {}

BigInt BigInt::operator*(const BigInt &other) {}

BigInt BigInt::operator*=(const BigInt &other) {}

BigInt BigInt::operator/(const BigInt &other) {}

BigInt BigInt::operator/=(const BigInt &other) {}

BigInt &BigInt::operator=(const BigInt &other) {}

bool BigInt::operator==(const BigInt &other) const {
  if (size != other.size || sign != other.sign)
    return false;
  for (unsigned int i = 0; i < size; ++i) {
    if (value[i] != other.value[i])
      return false;
  }
  return true;
}

bool BigInt::operator!=(const BigInt &other) const { return !(*this == other); }

bool BigInt::operator<(const BigInt &other) const {
  if (size != other.size)
    return size < other.size;
  //! TODO
}

bool BigInt::operator<=(const BigInt &other) const {
  return *this < other || *this == other;
}

bool BigInt::operator>(const BigInt &other) const { return !(*this <= other); }

bool BigInt::operator>=(const BigInt &other) const { return !(*this < other); }
