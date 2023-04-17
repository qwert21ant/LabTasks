#pragma once

#include <cstddef>

class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity)
      : capacity_(capacity), data_(new int[capacity_]), pos_(0), size_(0) {}

  ~RingBuffer() { delete[] data_; }

  size_t Size() const { return size_; }

  bool Empty() const { return size_ == 0; }

  bool TryPush(int element) {
    if (size_ == capacity_) {
      return false;
    }

    data_[(pos_ + size_++) % capacity_] = element;

    return true;
  }

  bool TryPop(int* element) {
    if (size_ == 0) {
      return false;
    }

    *element = data_[pos_++];
    size_--;
    if (pos_ >= capacity_) {
      pos_ -= capacity_;
    }

    return true;
  }

 private:
  size_t capacity_;
  int* data_;

  size_t pos_;
  size_t size_;
};