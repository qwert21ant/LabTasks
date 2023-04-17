#include "big_integer.hpp"

BigInt::BigInt() {
  neg_ = false;
  data_.push_back(0);
}

BigInt::BigInt(const std::string& str) {
  neg_ = false;

  if (str.empty()) {
    data_.push_back(0);
    return;
  }

  int offset = 0;

  if (str[0] == '-') {
    neg_ = true;
    offset = 1;
  }

  for (int i = str.size(); i >= offset; i -= kNums) {
    if (i + offset > kNums) {
      data_.push_back(atoi(str.substr(i - kNums, kNums).c_str()));
    } else {
      data_.push_back(atoi(str.substr(offset, i - offset).c_str()));
    }
  }

  Clean();
}

BigInt::BigInt(int64_t num) {
  neg_ = false;

  if (num < 0) {
    neg_ = true;
  }

  int koef = neg_ ? -1 : 1;

  do {
    data_.push_back((num % kBase) * koef);
  } while ((num /= kBase) != 0);
}

void BigInt::Swap(BigInt& other) {
  std::swap(data_, other.data_);
  std::swap(neg_, other.neg_);
}

BigInt::BigInt(const BigInt& other) {
  neg_ = other.neg_;
  data_ = other.data_;
}

BigInt& BigInt::operator=(BigInt other) {
  Swap(other);

  return *this;
}

BigInt::~BigInt() {}

BigInt& BigInt::operator+=(const BigInt& num) {
  if (neg_) {
    neg_ = !neg_;
    *this -= num;
    neg_ = !neg_;
    Clean();
    return *this;
  }
  if (num.neg_) {
    return *this -= -num;
  }

  int carry = 0;
  for (size_t i = 0; i < std::max(data_.size(), num.data_.size()) || carry != 0;
       ++i) {
    if (i == data_.size()) {
      data_.push_back(0);
    }

    data_[i] += carry + (i < num.data_.size() ? num.data_[i] : 0);
    carry = data_[i] >= kBase ? 1 : 0;
    data_[i] %= kBase;
  }
  Clean();
  return *this;
}

BigInt& BigInt::operator-=(const BigInt& num) {
  if (neg_) {
    neg_ = !neg_;
    *this += num;
    neg_ = !neg_;
    Clean();
    return *this;
  }
  if (num.neg_) {
    return *this += -num;
  }
  if (*this < num) {
    BigInt tmp(num);
    tmp -= *this;
    tmp.neg_ = !tmp.neg_;
    Swap(tmp);
    Clean();
    return *this;
  }
  int carry = 0;
  for (size_t i = 0; i < num.data_.size() || carry != 0; ++i) {
    data_[i] -= carry + (i < num.data_.size() ? num.data_[i] : 0);
    carry = data_[i] < 0 ? 1 : 0;
    if (carry != 0) {
      data_[i] += kBase;
    }
  }
  Clean();
  return *this;
}

BigInt& BigInt::operator*=(const BigInt& num) {
  neg_ = neg_ != num.neg_;
  std::vector<int> res(data_.size() + num.data_.size());

  for (size_t i = 0; i < data_.size(); ++i) {
    int carry = 0;
    for (size_t j = 0; j < num.data_.size() || carry != 0; ++j) {
      long long prod =
          1LL * data_[i] * (j < num.data_.size() ? num.data_[j] : 0);
      long long cur = res[i + j] + prod + carry;
      res[i + j] = cur % kBase;
      carry = cur / kBase;
    }
  }

  swap(data_, res);
  Clean();

  return *this;
}

BigInt& BigInt::operator/=(const BigInt& num) {
  neg_ = neg_ != num.neg_;
  std::vector<int> res = {0};
  BigInt tmp(*this);
  tmp.ShiftRight(data_.size() - num.data_.size() + 1);

  for (int i = data_.size() - num.data_.size(); i >= 0; --i) {
    tmp.ShiftLeft(1);
    tmp.data_[0] = data_[i];

    int val = 0;
    int left = 0;
    int right = kBase;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (!(num * mid).MoreAbs(tmp)) {
        val = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    res.insert(res.begin(), val);
    tmp = tmp - num * val;
  }
  swap(data_, res);
  Clean();
  return *this;
}

BigInt& BigInt::operator%=(const BigInt& num) {
  bool flg = neg_;
  neg_ = false;
  BigInt tmp(*this);
  tmp.ShiftRight(data_.size() - num.data_.size() + 1);

  for (int i = data_.size() - num.data_.size(); i >= 0; --i) {
    tmp.ShiftLeft(1);
    tmp.data_[0] = data_[i];
    int val = 0;
    int left = 0;
    int right = kBase;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (!(num * mid).MoreAbs(tmp)) {
        val = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    tmp = tmp - num * val;
  }
  Swap(tmp);
  neg_ = flg;
  Clean();
  return *this;
}

BigInt operator+(BigInt lhs, const BigInt& rhs) { return lhs += rhs; }
BigInt operator-(BigInt lhs, const BigInt& rhs) { return lhs -= rhs; }
BigInt operator*(BigInt lhs, const BigInt& rhs) { return lhs *= rhs; }
BigInt operator/(BigInt lhs, const BigInt& rhs) { return lhs /= rhs; }
BigInt operator%(BigInt lhs, const BigInt& rhs) { return lhs %= rhs; }

BigInt& BigInt::operator++() { return *this += 1; }
BigInt& BigInt::operator--() { return *this -= 1; }

BigInt BigInt::operator++(int) {
  BigInt res(*this);
  ++*this;
  return res;
}

BigInt BigInt::operator--(int) {
  BigInt res(*this);
  --*this;
  return res;
}

BigInt BigInt::operator-() const {
  BigInt res(*this);
  res.neg_ = !neg_;
  res.Clean();
  return res;
}

bool BigInt::operator==(const BigInt& num) const {
  if (neg_ != num.neg_) {
    return false;
  }

  if (data_.size() != num.data_.size()) {
    return false;
  }

  return std::equal(data_.begin(), data_.end(), num.data_.begin());
}

bool BigInt::operator!=(const BigInt& num) const { return !(*this == num); }

bool BigInt::LessAbs(const BigInt& num) const {
  if (data_.size() != num.data_.size()) {
    return data_.size() < num.data_.size();
  }

  for (int i = data_.size() - 1; i >= 0; --i) {
    if (data_[i] == num.data_[i]) {
      continue;
    }

    return data_[i] < num.data_[i];
  }

  return false;
}

bool BigInt::operator<(const BigInt& num) const {
  if (neg_ != num.neg_) {
    return neg_;
  }

  if (neg_) {
    return MoreAbs(num);
  }

  return LessAbs(num);
}

bool BigInt::MoreAbs(const BigInt& num) const {
  if (data_.size() != num.data_.size()) {
    return data_.size() > num.data_.size();
  }

  for (int i = data_.size() - 1; i >= 0; --i) {
    if (data_[i] == num.data_[i]) {
      continue;
    }

    return data_[i] > num.data_[i];
  }

  return false;
}

bool BigInt::operator>(const BigInt& num) const {
  if (neg_ != num.neg_) {
    return !neg_;
  }

  if (neg_) {
    return LessAbs(num);
  }

  return MoreAbs(num);
}

bool BigInt::operator<=(const BigInt& num) const { return !(*this > num); }
bool BigInt::operator>=(const BigInt& num) const { return !(*this < num); }

void BigInt::Clean() {
  while (data_.size() > 1 && data_.back() == 0) {
    data_.pop_back();
  }

  if (data_.size() == 1 && data_.back() == 0) {
    neg_ = false;
  }
}

void BigInt::ShiftRight(size_t num) {
  if (num == 0) {
    return;
  }

  if (num >= data_.size()) {
    data_.resize(1);
    data_[0] = 0;
    neg_ = false;
    return;
  }

  for (uint64_t i = 0; i < data_.size() - num; ++i) {
    data_[i] = data_[i + num];
  }

  data_.resize(data_.size() - num);
  Clean();
}

void BigInt::ShiftLeft(size_t num) {
  if (num == 0) {
    return;
  }

  data_.resize(data_.size() + num);

  for (size_t i = data_.size() - 1; i >= num; --i) {
    data_[i] = data_[i - num];
  }

  for (size_t i = 0; i < num; ++i) {
    data_[i] = 0;
  }

  Clean();
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
  if (num.neg_) {
    out << "-";
  }

  out << num.data_.back();

  for (int i = num.data_.size() - 2; i >= 0; --i) {
    out << std::setfill('0') << std::setw(BigInt::kNums) << num.data_[i];
  }

  return out;
}

std::istream& operator>>(std::istream& sin, BigInt& num) {
  std::string str;
  sin >> str;

  num = BigInt(str);

  return sin;
}