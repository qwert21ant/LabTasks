#include "Vector.h"

Vector::Vector() {
  data_ = nullptr;
  capacity_ = 0;
  size_ = 0;
}

Vector::Vector(size_t size) {
  data_ = new int[size];
  memset(data_, 0, sizeof(int) * size);
  capacity_ = size;
  size_ = size;
}

Vector::Vector(size_t size, int value) {
  data_ = new int[size];
  for (int i = 0; i < size; i++)
    data_[i] = value;
  capacity_ = size;
  size_ = size;
}

Vector::Vector(const std::initializer_list<int>& list) {
  data_ = new int[list.size()];
  capacity_ = list.size();
  size_ = list.size();

  size_t ind = 0;
  for (const int value : list)
    data_[ind++] = value;
}

Vector::Vector(const Vector& vec) {
  capacity_ = vec.capacity_;
  size_ = vec.size_;

  data_ = new int[size_];
  memcpy(data_, vec.data_, sizeof(int) * size_);
}

Vector& Vector::operator =(const Vector& vec) {
  if (this == &vec)
    return *this;

  this->~Vector();

  capacity_ = vec.capacity_;
  size_ = vec.size_;

  data_ = new int[size_];
  memcpy(data_, vec.data_, sizeof(int) * size_);

  return *this;
}

Vector::Vector(Vector&& vec) {
  data_ = vec.data_;
  capacity_ = vec.capacity_;
  size_ = vec.size_;

  vec.data_ = nullptr;
  vec.capacity_ = 0;
  vec.size_ = 0;
}

Vector& Vector::operator =(Vector&& vec) {
  this->~Vector();

  data_ = vec.data_;
  capacity_ = vec.capacity_;
  size_ = vec.size_;

  vec.data_ = nullptr;
  vec.capacity_ = 0;
  vec.size_ = 0;

  return *this;
}

size_t Vector::size() const {
  return size_;
}

size_t Vector::capacity() const {
  return capacity_;
}

void Vector::reserve(size_t capacity) {
  if (capacity <= capacity_)
    return;

  int* buf = new int[capacity];
  memcpy(buf, data_, sizeof(int) * size_);
  if (data_)
    delete[] data_;

  data_ = buf;
  capacity_ = capacity;
}

void Vector::resize(size_t size) {
  if (size <= capacity_) {
    size_ = size;
    return;
  }

  reserve(size);
  memset(data_ + size, 0, sizeof(int) * (size - size_));

  size_ = size;
}

void Vector::push_back(int value) {
  if (size_ == capacity_)
    reserve(capacity_ * 2 + 1);

  data_[size_++] = value;
}

void Vector::pop_back() {
  --size_;
}

void Vector::random(int max_val) {
  for (int i = 0; i < size_; i++)
    data_[i] = rand() % max_val;
}

int& Vector::operator [](size_t ind) {
  if (ind >= size_)
    throw std::out_of_range("");
  return data_[ind];
}

const int& Vector::operator [](size_t ind) const {
  if (ind >= size_)
    throw std::out_of_range("");
  return data_[ind];
}

std::ostream& operator <<(std::ostream& out, const Vector& vec) {
  for (int i = 0; i < vec.size(); i++)
    out << vec[i] << " ";
  return out;
}

Vector::~Vector() {
  if (data_)
    delete[] data_;
}