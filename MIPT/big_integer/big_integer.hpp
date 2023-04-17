#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class BigInt {
 public:
  BigInt();
  BigInt(const std::string&);
  BigInt(int64_t);

  void Swap(BigInt&);
  BigInt(const BigInt&);
  BigInt& operator=(BigInt);
  ~BigInt();

  BigInt& operator+=(const BigInt&);
  BigInt& operator-=(const BigInt&);
  BigInt& operator*=(const BigInt&);
  BigInt& operator/=(const BigInt&);
  BigInt& operator%=(const BigInt&);

  friend BigInt operator+(BigInt, const BigInt&);
  friend BigInt operator-(BigInt, const BigInt&);
  friend BigInt operator*(BigInt, const BigInt&);
  friend BigInt operator/(BigInt, const BigInt&);
  friend BigInt operator%(BigInt, const BigInt&);

  BigInt& operator++();
  BigInt& operator--();

  BigInt operator++(int);
  BigInt operator--(int);

  BigInt operator-() const;

  bool operator==(const BigInt&) const;
  bool operator!=(const BigInt&) const;
  bool operator<(const BigInt&) const;
  bool operator>(const BigInt&) const;
  bool operator<=(const BigInt&) const;
  bool operator>=(const BigInt&) const;

  friend std::ostream& operator<<(std::ostream&, const BigInt&);
  friend std::istream& operator>>(std::istream&, BigInt&);

  static const int kNums = 6;
  static const int kBase = 1'000'000;

 private:
  std::vector<int> data_;
  bool neg_ = false;

 public:
  void Clean();
  void ShiftRight(size_t);
  void ShiftLeft(size_t);

  bool LessAbs(const BigInt&) const;
  bool MoreAbs(const BigInt&) const;
};