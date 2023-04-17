#include "string.hpp"

String::String() {
  capacity_ = 0;
  size_ = 0;
  data_ = nullptr;
}

String::String(size_t size, char character) {
  capacity_ = size_ = size;
  data_ = new char[capacity_ + 1];

  memset(data_, character, size_);
  data_[size_] = 0;
}

String::String(const char* str) {
  capacity_ = size_ = strlen(str);
  data_ = new char[capacity_ + 1];

  memcpy(data_, str, size_);
  data_[size_] = 0;
}

String::String(const String& other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  data_ = new char[capacity_ + 1];

  memcpy(data_, other.data_, size_);
  data_[size_] = 0;
}

void String::Swap(String& other) {
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
  std::swap(data_, other.data_);
}

String& String::operator=(String other) {
  Swap(other);

  return *this;
}

String::~String() { delete[] data_; }

void String::Clear() {
  size_ = 0;
  data_[0] = 0;
}

void String::PushBack(char character) {
  Resize(size_ + 1);
  data_[size_ - 1] = character;
}

void String::PopBack() {
  if (size_ > 0) {
    data_[--size_] = 0;
  }
}

void String::Resize(size_t new_size, char character) {
  if (new_size > capacity_) {
    capacity_ = std::max(2 * capacity_, new_size);
    char* tmp = new char[capacity_ + 1];
    if (size_ > 0) {
      memcpy(tmp, data_, size_);
    }

    delete[] data_;
    data_ = tmp;
  }

  if (new_size > size_) {
    memset(data_ + size_, character, new_size - size_);
  }
  size_ = new_size;
  if (data_ != nullptr) {
    data_[size_] = 0;
  }
}

void String::Reserve(size_t new_capacity) {
  if (capacity_ >= new_capacity) {
    return;
  }

  char* tmp = new char[new_capacity + 1];
  delete[] data_;
  data_ = tmp;
  capacity_ = new_capacity;
}

void String::ShrinkToFit() {
  if (capacity_ == size_) {
    return;
  }

  char* tmp = new char[size_ + 1];
  memcpy(tmp, data_, size_);
  tmp[size_] = 0;

  delete[] data_;
  data_ = tmp;
  capacity_ = size_;
}

char& String::operator[](size_t ind) { return data_[ind]; }
const char& String::operator[](size_t ind) const { return data_[ind]; }

char& String::Front() { return data_[0]; }
const char& String::Front() const { return data_[0]; }

char& String::Back() { return data_[size_ - 1]; }
const char& String::Back() const { return data_[size_ - 1]; }

bool String::Empty() const { return size_ == 0; }
size_t String::Size() const { return size_; }
size_t String::Capacity() const { return capacity_; }
const char* String::Data() const { return data_; }

bool String::operator==(const String& other) const {
  if (size_ != other.size_) {
    return false;
  }

  return memcmp(data_, other.data_, size_) == 0;
}

bool String::operator!=(const String& other) const { return !(*this == other); }

bool String::operator<(const String& other) const {
  int res = memcmp(data_, other.data_, std::min(size_, other.size_));

  if (res < 0) {
    return true;
  }
  if (res == 0) {
    return size_ < other.size_;
  }
  return false;
}

bool String::operator>(const String& other) const {
  int res = memcmp(data_, other.data_, std::min(size_, other.size_));

  if (res > 0) {
    return true;
  }
  if (res == 0) {
    return size_ > other.size_;
  }
  return false;
}

bool String::operator<=(const String& other) const { return !(*this > other); }
bool String::operator>=(const String& other) const { return !(*this < other); }

String& String::operator+=(const String& other) {
  size_t prev_size = size_;

  Resize(size_ + other.size_);
  memcpy(data_ + prev_size, other.data_, other.size_);

  return *this;
}

String& String::operator*=(int num) {
  size_t prev_size = size_;

  Resize(size_ * num);
  for (int i = 1; i < num; ++i) {
    memcpy(data_ + prev_size * i, data_, prev_size);
  }

  return *this;
}

String operator+(String lhs, const String& rhs) { return lhs += rhs; }
String operator*(String str, int num) { return str *= num; }

std::ostream& operator<<(std::ostream& out, const String& str) {
  return out << str.data_;
}

std::istream& operator>>(std::istream& in, String& str) {
  char ch;
  while (in.get(ch)) {
    str.PushBack(ch);
  }

  return in;
}

size_t String::Find(const String& str, size_t pos) const {
  for (size_t i = pos; i < size_; ++i) {
    bool equal = true;
    for (size_t j = 0; i + j < size_ && j < str.size_; ++j) {
      if (data_[i + j] != str.data_[j]) {
        equal = false;
        break;
      }
    }

    if (!equal) {
      continue;
    }

    if (i + str.size_ <= size_) {
      return i;
    }
  }

  return size_;
}

String String::Substr(size_t pos, size_t num) const {
  size_t new_size = std::min(num, size_ - pos);
  String res;
  res.Resize(new_size);

  memcpy(res.data_, data_ + pos, new_size);

  return res;
}

String String::Substr(size_t pos) const { return Substr(pos, size_ - pos); }

std::vector<String> String::Split(const String& delim) const {
  std::vector<String> res;

  for (size_t word_left = 0; word_left <= size_;) {
    size_t delim_left = Find(delim, word_left);

    if (delim_left == size_) {
      res.push_back(Substr(word_left));
      break;
    }

    res.push_back(Substr(word_left, delim_left - word_left));
    word_left = delim_left + delim.size_;
  }

  return res;
}

String String::Join(const std::vector<String>& strings) const {
  String res;

  size_t new_size = (strings.size() - 1) * size_;
  for (const String& str : strings) {
    new_size += str.size_;
  }

  res.Reserve(new_size);

  for (size_t i = 0; i < strings.size(); ++i) {
    res += strings[i];
    if (i != strings.size() - 1) {
      res += *this;
    }
  }

  return res;
}