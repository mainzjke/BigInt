#pragma once

class BigInt {
public:
  BigInt();
  BigInt(const BigInt &other);
  BigInt(BigInt &&other);
  BigInt(int val);
  BigInt(const char *val);
  ~BigInt();

  char *value;
  BigInt operator+(const BigInt &other);
  BigInt &operator+=(const BigInt &other);

  BigInt operator-(const BigInt &other);
  BigInt operator-=(const BigInt &other);

  BigInt operator*(const BigInt &other);
  BigInt operator*=(const BigInt &other);

  BigInt operator/(const BigInt &other);
  BigInt operator/=(const BigInt &other);

  BigInt &operator=(const BigInt &other);

  bool operator==(const BigInt &other) const;
  bool operator!=(const BigInt &other) const;
  bool operator<(const BigInt &other) const;
  bool operator<=(const BigInt &other) const;

  bool operator>(const BigInt &other) const;
  bool operator>=(const BigInt &other) const;

private:
  void resize();

private:
  unsigned int size;
  unsigned int capacity;
  bool sign;
};
