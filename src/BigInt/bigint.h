#pragma once

class BigInt {
public:
  BigInt();
  BigInt(const BigInt &other);
  BigInt(BigInt &&other);
  BigInt(int value);
  BigInt(const char *value);
  ~BigInt();
  BigInt operator+(const BigInt &other);
  BigInt &operator+=(const BigInt &other);

  BigInt operator-(const BigInt &other);
  BigInt operator-=(const BigInt &other);
  BigInt operator-() const;

  BigInt operator*(const BigInt &other);
  BigInt operator*=(const BigInt &other);

  BigInt operator/(const BigInt &other);
  BigInt operator/=(const BigInt &other);

  BigInt &operator=(const BigInt &other);
  BigInt &operator=(BigInt &&other);

  bool operator==(const BigInt &other) const;

  bool operator!=(const BigInt &other) const;
  bool operator<(const BigInt &other) const;
  bool operator<=(const BigInt &other) const;

  bool operator>(const BigInt &other) const;
  bool operator>=(const BigInt &other) const;

private:
  BigInt(char *value, unsigned int capacity, bool sign);
  void resize();

private:
  char *m_value;
  unsigned int m_size;
  unsigned int m_capacity;
  bool m_sign;
};
