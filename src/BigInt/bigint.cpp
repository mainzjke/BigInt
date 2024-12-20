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
} // namespace

BigInt::BigInt() {
  size = 1;
  value = new char[size];
  value[0] = 0;
}

BigInt::BigInt(const BigInt &other) {}

BigInt::BigInt(BigInt &&other) {}

BigInt::BigInt(int val) {
  size = sizeof(val);
  value = new char[size];
  std::memcpy(value, &val, size);
  ::printBits(value, size);
}

BigInt::BigInt(const char *val) {
  if (!val || std::strlen(value) == 0) {
    throw std::invalid_argument("empty string");
  }
  //! TODO
}

BigInt::~BigInt() { delete[] value; }

BigInt BigInt::operator+(const BigInt &other) {}

BigInt &BigInt::operator+=(const BigInt &other) {}

BigInt BigInt::operator-(const BigInt &other) {}

BigInt BigInt::operator-=(const BigInt &other) {}

BigInt BigInt::operator*(const BigInt &other) {}

BigInt BigInt::operator*=(const BigInt &other) {}

BigInt BigInt::operator/(const BigInt &other) {}

BigInt BigInt::operator/=(const BigInt &other) {}

BigInt &BigInt::operator=(const BigInt &other) {}

bool BigInt::operator==(const BigInt &other) const {
  if (size != other.size)
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
