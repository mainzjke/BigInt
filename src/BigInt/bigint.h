#pragma once

class BigInt
{
public:
    BigInt();
    BigInt(const BigInt& other);
    BigInt(BigInt&& other);
    BigInt(int val);
    BigInt(const char *val);
    ~BigInt();

    BigInt operator +(const BigInt& other);
    BigInt& operator +=(const BigInt& other);

    BigInt operator -(const BigInt& other);
    BigInt operator -=(const BigInt& other);

    BigInt operator *(const BigInt& other);
    BigInt operator *=(const BigInt& other);

    BigInt operator /(const BigInt& other);
    BigInt operator /=(const BigInt& other);

    BigInt& operator =(const BigInt& other);


    bool operator ==(const BigInt& other) const;
    bool operator !=(const BigInt& other) const;
    bool operator <(const BigInt& other) const;
    bool operator <=(const BigInt& other) const;

    bool operator >(const BigInt& other) const;
    bool operator >=(const BigInt& other) const;

private:
    char *value;
    unsigned int size;
};
