#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

template <typename T>
class Deque {
 public:
  Deque() : startInd_(0), endInd_(0), startBlockInd_(0), endBlockInd_(0) {
    data_.push_back((T*)new char[kBlockSize * sizeof(T)]);
  };

  Deque(size_t count) : data_((count + kBlockSize - 1) / kBlockSize) {
    startInd_ = 0;
    endInd_ = count % kBlockSize;
    startBlockInd_ = 0;
    endBlockInd_ = count / kBlockSize;

    for (auto& ptr : data_) {
      ptr = (T*)new char[kBlockSize * sizeof(T)];
      memset(ptr, 0, kBlockSize * sizeof(T));
    }

    if (endInd_ == kBlockSize) {
      endInd_ = 0;
      ++endBlockInd_;
      data_.push_back((T*)new char[kBlockSize * sizeof(T)]);
      memset(data_.back(), 0, kBlockSize * sizeof(T));
    }
  };

  Deque(size_t count, const T& value) : Deque(count) {
    int block_ind = 0;
    int ind = 0;

    try {
      while ((count--) != 0) {
        new (&(data_[block_ind][ind])) T(value);
        ++ind;
        if (ind == kBlockSize) {
          ++block_ind;
          ind = 0;
        }
      }
    } catch (...) {
      throw;
    }
  };

  Deque(const Deque& deque)
      : data_(deque.data_.size(), nullptr),
        startInd_(deque.startInd_),
        endInd_(deque.endInd_),
        startBlockInd_(deque.startBlockInd_),
        endBlockInd_(deque.endBlockInd_) {
    for (size_t i = 0; i < (size_t)deque.data_.size(); ++i) {
      data_[i] = (T*)new char[kBlockSize * sizeof(T)];
      memcpy(data_[i], deque.data_[i], sizeof(T) * kBlockSize);
    }
  };

  Deque& operator=(const Deque& deque) {
    for (auto ptr : data_) {
      delete[] (char*)ptr;
    }

    startInd_ = deque.startInd_;
    endInd_ = deque.endInd_;
    startBlockInd_ = deque.startBlockInd_;
    endBlockInd_ = deque.endBlockInd_;

    data_.resize(deque.data_.size());
    for (size_t i = 0; i < (size_t)data_.size(); ++i) {
      data_[i] = (T*)new char[kBlockSize * sizeof(T)];
      memcpy(data_[i], deque.data_[i], sizeof(T) * kBlockSize);
    }

    return *this;
  };

  ~Deque() noexcept {
    for (auto ptr : data_) {
      delete[] (char*)ptr;
    }
  };

  size_t size() const noexcept {
    if (startBlockInd_ == endBlockInd_) {
      return endInd_ - startInd_;
    }

    size_t res = 0;
    res += kBlockSize * (endBlockInd_ - startBlockInd_ - 1);
    res += kBlockSize - startInd_;
    res += endInd_;
    return res;
  };

  bool empty() const noexcept {
    return startBlockInd_ == endBlockInd_ && startInd_ == endInd_;
  };

  T& operator[](size_t ind) {
    size_t cur_block_ind = startBlockInd_ + ind / kBlockSize;
    size_t cur_ind = startInd_ + ind % kBlockSize;

    cur_block_ind += cur_ind / kBlockSize;
    cur_ind %= kBlockSize;

    return data_[cur_block_ind][cur_ind];
  };

  const T& operator[](size_t ind) const {
    size_t cur_block_ind = startBlockInd_ + ind / kBlockSize;
    size_t cur_ind = startInd_ + ind % kBlockSize;

    cur_block_ind += cur_ind / kBlockSize;
    cur_ind %= kBlockSize;

    return data_[cur_block_ind][cur_ind];
  };

  T& at(size_t ind) {
    iterator iter = begin() + ind;

    if (ind >= size()) {
      throw std::out_of_range("");
    }

    return *iter;
  };

  const T& at(size_t ind) const {
    iterator iter = begin() + ind;

    if (ind >= size()) {
      throw std::out_of_range("");
    }

    return *iter;
  };

  void push_back(const T& value) {
    try {
      new (&(data_[endBlockInd_][endInd_])) T(value);
    } catch (...) {
      throw;
    }
    ++endInd_;
    if (endInd_ == kBlockSize) {
      endInd_ = 0;
      ++endBlockInd_;
      if ((int64_t)data_.size() == endBlockInd_) {
        data_.push_back((T*)new char[kBlockSize * sizeof(T)]);
      }
    }
  };

  void pop_back() {
    if (endInd_ == 0) {
      endInd_ = kBlockSize - 1;
      --endBlockInd_;
    } else {
      --endInd_;
    }
  }

  void push_front(const T& value) {
    if (startInd_ == 0) {
      if (startBlockInd_ == 0) {
        data_.insert(data_.begin(), (T*)new char[kBlockSize * sizeof(T)]);
        ++endBlockInd_;
      } else {
        --startBlockInd_;
      }

      startInd_ = kBlockSize - 1;
    } else {
      --startInd_;
    }

    try {
      new (&(data_[startBlockInd_][startInd_])) T(value);
    } catch (...) {
      pop_front();
      throw;
    }
  }

  void pop_front() {
    ++startInd_;
    if (startInd_ == kBlockSize) {
      ++startBlockInd_;
      startInd_ = 0;
    }
  };

  template <bool IsConst>
  class RawIterator;

  template <class Iter>
  class ReverseIterator;

  using iterator = RawIterator<false>;
  using const_iterator = RawIterator<true>;
  using reverse_iterator = ReverseIterator<iterator>;
  using const_reverse_iterator = ReverseIterator<const_iterator>;

  void insert(iterator iter, const T& value) {
    int64_t dist_start = iter - begin();
    int64_t dist_end = end() - iter;

    if (dist_start > dist_end) {
      push_back(*(end() - 1));
      shift_right(iter, end() - 1);
    } else {
      push_front(*begin());
      if (begin().ind_ == kBlockSize - 1) {
        ++iter.blockInd_;
      }
      shift_left(begin(), iter);
      --iter;
    }
    *iter = value;
  };

  void erase(iterator iter) {
    int64_t dist_start = iter - begin();
    int64_t dist_end = end() - iter;

    if (dist_start > dist_end) {
      shift_left(iter, end());
      pop_back();
    } else {
      shift_right(begin() - 1, iter);
      pop_front();
    }
  };

  iterator begin() { return iterator(&data_, startBlockInd_, startInd_); };

  const_iterator begin() const {
    return const_iterator(&data_, startBlockInd_, startInd_);
  };

  iterator end() { return iterator(&data_, endBlockInd_, endInd_); };

  const_iterator end() const {
    return const_iterator(&data_, endBlockInd_, endInd_);
  };

  const_iterator cbegin() const {
    return const_iterator(&data_, startBlockInd_, startInd_);
  };

  const_iterator cend() const {
    return const_iterator(&data_, endBlockInd_, endInd_);
  };

  reverse_iterator rbegin() { return reverse_iterator(end() - 1); };

  reverse_iterator rend() { return reverse_iterator(begin() - 1); };

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(cend() - 1);
  };

  const_reverse_iterator crend() const {
    return const_reverse_iterator(cbegin() - 1);
  };

 private:
  std::vector<T*> data_;
  int64_t startInd_;
  int64_t endInd_;
  int64_t startBlockInd_;
  int64_t endBlockInd_;

  static const int64_t kBlockSize = 1000;

  void shift_right(iterator left, iterator right) {
    if (left == right) {
      return;
    }

    iterator prev = right--;
    while (left != right) {
      *prev = *right;
      --right;
      --prev;
    }
  }

  void shift_left(iterator left, iterator right) {
    if (left == right) {
      return;
    }

    iterator prev = left++;
    while (left != right) {
      *prev = *left;
      ++left;
      ++prev;
    }
  }
};

template <typename T>
template <bool IsConst>
class Deque<T>::RawIterator {
 public:
  friend class Deque<T>;

  using iterator_category = std::random_access_iterator_tag;
  using value_type = std::conditional_t<IsConst, const T, T>;
  using difference_type = ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  using vector_type =
      std::conditional_t<IsConst, const std::vector<T*>, std::vector<T*>>;

  RawIterator(vector_type* data, int64_t block_ind, int64_t ind)
      : data_(data), blockInd_(block_ind), ind_(ind){};
  RawIterator(const RawIterator& iter) = default;
  RawIterator& operator=(const RawIterator& iter) = default;
  ~RawIterator() = default;

  RawIterator& operator++() {
    ++ind_;
    if (ind_ == kBlockSize) {
      ++blockInd_;
      ind_ = 0;
    }
    return *this;
  };

  RawIterator operator++(int) {
    RawIterator tmp = *this;
    ++(*this);
    return tmp;
  };

  RawIterator& operator--() {
    if (ind_ == 0) {
      --blockInd_;
      ind_ = kBlockSize - 1;
    } else {
      --ind_;
    }
    return *this;
  };

  RawIterator operator--(int) {
    RawIterator tmp = *this;
    --(*this);
    return tmp;
  };

  RawIterator operator+(int64_t value) const {
    if (value < 0) {
      return *this - (-value);
    }

    int64_t cur_block_ind = blockInd_ + value / kBlockSize;
    int64_t cur_ind = ind_ + value % kBlockSize;

    cur_block_ind += cur_ind / kBlockSize;
    cur_ind %= kBlockSize;

    return RawIterator(data_, cur_block_ind, cur_ind);
  };

  RawIterator& operator+=(int64_t value) {
    if (value < 0) {
      return *this -= (-value);
    }

    int64_t cur_block_ind = blockInd_ + value / kBlockSize;
    int64_t cur_ind = ind_ + value % kBlockSize;

    cur_block_ind += cur_ind / kBlockSize;
    cur_ind %= kBlockSize;

    blockInd_ = cur_block_ind;
    ind_ = cur_ind;
    return *this;
  };

  RawIterator operator-(int64_t value) const {
    if (value < 0) {
      return *this + (-value);
    }

    int64_t cur_block_ind = blockInd_ - value / kBlockSize;
    int64_t cur_ind = ind_;

    if (value % kBlockSize > cur_ind) {
      --cur_block_ind;
      cur_ind = kBlockSize - (value % kBlockSize - cur_ind);
    } else {
      cur_ind -= value % kBlockSize;
    }

    return RawIterator(data_, cur_block_ind, cur_ind);
  };

  RawIterator& operator-=(int64_t value) {
    if (value < 0) {
      return *this += (-value);
    }

    int64_t cur_block_ind = blockInd_ - value / kBlockSize;
    int64_t cur_ind = ind_;

    if (value % kBlockSize > cur_ind) {
      --cur_block_ind;
      cur_ind = kBlockSize - (value % kBlockSize - cur_ind);
    } else {
      cur_ind -= value % kBlockSize;
    }

    blockInd_ = cur_block_ind;
    ind_ = cur_ind;
    return *this;
  };

  bool operator==(const RawIterator& iter) const {
    return blockInd_ == iter.blockInd_ && ind_ == iter.ind_;
  };
  bool operator!=(const RawIterator& iter) const { return !(*this == iter); };
  bool operator<(const RawIterator& iter) const {
    if (blockInd_ > iter.blockInd_) {
      return false;
    }
    if (blockInd_ < iter.blockInd_) {
      return true;
    }
    return ind_ < iter.ind_;
  };
  bool operator>(const RawIterator& iter) const { return iter < *this; };
  bool operator>=(const RawIterator& iter) const { return !(*this < iter); };
  bool operator<=(const RawIterator& iter) const { return !(iter < *this); };

  difference_type operator-(const RawIterator& iter) const {
    if (*this == iter) {
      return 0;
    }
    if (*this < iter) {
      return -(iter - *this);
    }

    if (blockInd_ == iter.blockInd_) {
      return ind_ - iter.ind_;
    }

    difference_type res = (blockInd_ - iter.blockInd_ - 1) * kBlockSize;
    res += kBlockSize - iter.ind_;
    res += ind_;
    return res;
  };

  reference operator*() { return (*data_)[blockInd_][ind_]; };
  const T& operator*() const { return (*data_)[blockInd_][ind_]; };

  pointer operator->() { return &((*data_)[blockInd_][ind_]); };
  const T* operator->() const { return &((*data_)[blockInd_][ind_]); };

 private:
  vector_type* data_;
  int64_t blockInd_;
  int64_t ind_;
};

template <typename T>
template <class Iter>
class Deque<T>::ReverseIterator {
 public:
  friend class Deque<T>;

  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename Iter::value_type;
  using difference_type = typename Iter::difference_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;

  ReverseIterator(Iter iter) : base_(iter){};
  ReverseIterator(const ReverseIterator& iter) = default;
  ReverseIterator& operator=(const ReverseIterator& iter) = default;
  ~ReverseIterator() = default;

  ReverseIterator& operator++() {
    --base_;
    return *this;
  };

  ReverseIterator operator++(int) {
    ReverseIterator tmp = *this;
    ++(*this);
    return tmp;
  };

  ReverseIterator& operator--() {
    ++base_;
    return *this;
  };

  ReverseIterator operator--(int) {
    ReverseIterator tmp = *this;
    --(*this);
    return tmp;
  };

  ReverseIterator operator+(int value) const {
    return ReverseIterator(base_ - value);
  };

  ReverseIterator& operator+=(int value) {
    base_ -= value;
    return *this;
  };

  ReverseIterator operator-(int value) const {
    return ReverseIterator(base_ + value);
  };

  ReverseIterator& operator-=(int value) {
    base_ += value;
    return *this;
  };

  bool operator==(const ReverseIterator& iter) const {
    return base_ == iter.base_;
  };
  bool operator!=(const ReverseIterator& iter) const {
    return !(*this == iter);
  };
  bool operator<(const ReverseIterator& iter) const {
    return base_ > iter.base_;
  };
  bool operator>(const ReverseIterator& iter) const { return iter < *this; };
  bool operator>=(const ReverseIterator& iter) const {
    return !(*this < iter);
  };
  bool operator<=(const ReverseIterator& iter) const {
    return !(iter < *this);
  };

  difference_type operator-(const ReverseIterator& iter) const {
    return iter.base_ - base_;
  };

  reference operator*() { return *base_; };
  const T& operator*() const { return *base_; };

  pointer operator->() { return &(*base_); };
  const T* operator->() const { return &(*base_); };

 private:
  Iter base_;
};