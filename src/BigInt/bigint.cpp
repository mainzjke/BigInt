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

char *invertBits(const char *value, unsigned int size) {
  char *r = new char[size];
  for (int i = size - 1; i >= 0; --i) {
    r[i] = ~value[i];
  }
  return r;
}

char *makeNegative(const char *value, unsigned int size) {
  char *r = invertBits(value, size);
  int carry = 1;
  for (unsigned i = 0; i < size; ++i) {
    int byte = static_cast<unsigned char>(r[i]);
    auto sum = byte + carry;
    r[i] = sum & 0xFF;
    carry = (sum >> 8) & 0x1;
    if (carry == 0x0)
      break;
  }
  return r;
}

} // namespace

BigInt::BigInt() {
  m_capacity = m_size = 1;
  m_value = new char[m_capacity];
  m_value[0] = 0;
}

BigInt::BigInt(const BigInt &other) {
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_value = new char[m_capacity];
  std::memcpy(m_value, other.m_value, m_capacity);
}

BigInt::BigInt(BigInt &&other) {
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_value = std::move(other.m_value);
  other.m_value = nullptr;
  other.m_capacity = 0;
  other.m_size = 0;
  other.m_sign = false;
}

BigInt::BigInt(int value) {
  m_capacity = m_size = sizeof(int);
  m_value = new char[m_capacity];
  m_sign = (value > 0) ? true : false;

  //! берем число по модулю
  value = std::abs(value);

  std::memcpy(m_value, &value, m_capacity);
  ::printBits(m_value, m_capacity);
  resize();
}

BigInt::BigInt(const char *value) {
  if (!value || std::strlen(value) == 0) {
    throw std::invalid_argument("empty string");
  }
  //! TODO
}

BigInt::BigInt(char *value, unsigned int capacity, bool sign) {
  m_value = value;
  m_capacity = m_size = capacity;
  m_sign = sign;
  resize();
}

BigInt::~BigInt() { delete[] m_value; }

void BigInt::resize() {
  while (m_size > 1 && m_value[m_size - 1] == 0x0) {
    --m_size;
  }
}

BigInt BigInt::operator+(const BigInt &other) {
  //! max size
  auto ms = std::max(m_size, other.m_size);
  char *result = new char[ms + 1];
  int carry = 0;
  for (unsigned i = 0; i < ms; ++i) {
    int byte1 = (i < m_size) ? static_cast<unsigned char>(m_value[i]) : 0;
    int byte2 =
        (i < other.m_size) ? static_cast<unsigned char>(other.m_value[i]) : 0;
    auto sum = byte1 + byte2 + carry;
    result[i] = sum & 0xFF;
    carry = (sum >> 8) & 0x1;
  }

  if (carry > 0) {
    result[ms] = carry & 0xFF;
  }
  ::printBits(result, ms + 1);
  return BigInt(result, ms + 1, true);
}

BigInt &BigInt::operator+=(const BigInt &other) {}

BigInt BigInt::operator-(const BigInt &other) {}

BigInt BigInt::operator-=(const BigInt &other) {}

BigInt BigInt::operator-() const {
  BigInt result(*this);
  result.m_sign = !m_sign;
  return result;
}

BigInt BigInt::operator*(const BigInt &other) {}

BigInt BigInt::operator*=(const BigInt &other) {}

BigInt BigInt::operator/(const BigInt &other) {}

BigInt BigInt::operator/=(const BigInt &other) {}

BigInt &BigInt::operator=(const BigInt &other) {
  if (*this == other)
    return *this;
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_sign = other.m_sign;
  m_value = new char[m_capacity];
  std::memcpy(m_value, other.m_value, m_capacity);
}

BigInt &BigInt::operator=(BigInt &&other) {
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_sign = other.m_sign;
  m_value = other.m_value;

  other.m_value = nullptr;
  other.m_size = 0;
  other.m_capacity = 0;
  other.m_sign = false;
}

bool BigInt::operator==(const BigInt &other) const {
  if (m_size != other.m_size || m_sign != other.m_sign)
    return false;
  for (unsigned int i = 0; i < m_size; ++i) {
    if (m_value[i] != other.m_value[i])
      return false;
  }
  return true;
}

bool BigInt::operator!=(const BigInt &other) const { return !(*this == other); }

bool BigInt::operator<(const BigInt &other) const {
  if (m_size != other.m_size)
    return m_size < other.m_size;
  //! TODO
}

bool BigInt::operator<=(const BigInt &other) const {
  return *this < other || *this == other;
}

bool BigInt::operator>(const BigInt &other) const { return !(*this <= other); }

bool BigInt::operator>=(const BigInt &other) const { return !(*this < other); }
