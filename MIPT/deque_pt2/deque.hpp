#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

template <typename T, typename Alloc = std::allocator<T>>
class Deque {
 private:
  using alloc_traits = std::allocator_traits<Alloc>;

 public:
  using value_type = T;
  using allocator_type = Alloc;

  Deque(const Alloc& alloc = Alloc())
      : alloc_(alloc),
        startInd_(0),
        endInd_(0),
        startBlockInd_(0),
        endBlockInd_(0) {
    data_.push_back(allocate_block());
  }

  Deque(size_t count, const Alloc& alloc = Alloc())
      : alloc_(alloc), data_(count / kBlockSize + 1) {
    startInd_ = 0;
    endInd_ = count % kBlockSize;
    startBlockInd_ = 0;
    endBlockInd_ = count / kBlockSize;

    int block_ind = 0;
    int ind = 0;

    try {
      for (block_ind = 0; block_ind < endBlockInd_; ++block_ind) {
        data_[block_ind] = allocate_block();

        for (ind = 0; ind < kBlockSize; ++ind) {
          construct_element(&data_[block_ind][ind]);
        }
      }

      data_[block_ind] = allocate_block();

      for (ind = 0; ind < endInd_; ++ind) {
        construct_element(&data_[block_ind][ind]);
      }
    } catch (...) {
      endInd_ = ind;
      endBlockInd_ = block_ind;

      destroy();

      throw;
    }
  }

  Deque(size_t count, const T& value, const Alloc& alloc = Alloc())
      : alloc_(alloc), data_(count / kBlockSize + 1) {
    startInd_ = 0;
    endInd_ = count % kBlockSize;
    startBlockInd_ = 0;
    endBlockInd_ = count / kBlockSize;

    int block_ind = 0;
    int ind = 0;

    try {
      for (block_ind = 0; block_ind < endBlockInd_; ++block_ind) {
        data_[block_ind] = allocate_block();

        for (ind = 0; ind < kBlockSize; ++ind) {
          construct_element(&data_[block_ind][ind], value);
        }
      }

      data_[block_ind] = allocate_block();

      for (ind = 0; ind < endInd_; ++ind) {
        construct_element(&data_[block_ind][ind], value);
      }
    } catch (...) {
      endInd_ = ind;
      endBlockInd_ = block_ind;

      destroy();

      throw;
    }
  }

  Deque(std::initializer_list<T> init, const Alloc& alloc = Alloc())
      : alloc_(alloc), data_(init.size() / kBlockSize + 1) {
    startInd_ = 0;
    endInd_ = init.size() % kBlockSize;
    startBlockInd_ = 0;
    endBlockInd_ = init.size() / kBlockSize;

    int block_ind = 0;
    int ind = 0;

    auto cur = init.begin();

    try {
      for (block_ind = 0; block_ind < endBlockInd_; ++block_ind) {
        data_[block_ind] = allocate_block();

        for (ind = 0; ind < kBlockSize; ++ind) {
          construct_element(&data_[block_ind][ind], *cur++);
        }
      }

      data_[block_ind] = allocate_block();

      for (ind = 0; ind < endInd_; ++ind) {
        construct_element(&data_[block_ind][ind], *cur++);
      }
    } catch (...) {
      endInd_ = ind;
      endBlockInd_ = block_ind;

      destroy();

      throw;
    }
  }

  Deque(Deque&& deque) noexcept
      : alloc_(std::move(deque.alloc_)),
        data_(std::move(deque.data_)),
        startInd_(deque.startInd_),
        endInd_(deque.endInd_),
        startBlockInd_(deque.startBlockInd_),
        endBlockInd_(deque.endBlockInd_) {
    deque.startInd_ = 0;
    deque.endInd_ = 0;
    deque.startBlockInd_ = 0;
    deque.endBlockInd_ = 0;
  }

  Deque& operator=(Deque&& deque) noexcept {
    if (this == &deque) {
      return *this;
    }

    destroy();
    alloc_ = std::move(deque.alloc_);
    data_ = std::move(deque.data_);
    startInd_ = deque.startInd_;
    endInd_ = deque.endInd_;
    startBlockInd_ = deque.startBlockInd_;
    endBlockInd_ = deque.endBlockInd_;

    deque.startInd_ = 0;
    deque.endInd_ = 0;
    deque.startBlockInd_ = 0;
    deque.endBlockInd_ = 0;

    return *this;
  }

  Deque(const Deque& deque)
      : alloc_(
            alloc_traits::select_on_container_copy_construction(deque.alloc_)),
        data_(deque.size() / kBlockSize + 1) {
    startInd_ = 0;
    endInd_ = deque.size() % kBlockSize;
    startBlockInd_ = 0;
    endBlockInd_ = deque.size() / kBlockSize;

    int block_ind = 0;
    int ind = 0;

    auto cur = deque.begin();

    try {
      for (block_ind = 0; block_ind < endBlockInd_; ++block_ind) {
        data_[block_ind] = allocate_block();

        for (ind = 0; ind < kBlockSize; ++ind) {
          construct_element(&data_[block_ind][ind], *cur++);
        }
      }

      data_[block_ind] = allocate_block();

      for (ind = 0; ind < endInd_; ++ind) {
        construct_element(&data_[block_ind][ind], *cur++);
      }
    } catch (...) {
      endInd_ = ind;
      endBlockInd_ = block_ind;

      destroy();

      throw;
    }
  }

  Deque& operator=(const Deque& deque) {
    if (this == &deque) {
      return *this;
    }

    Deque tmp = deque;
    *this = std::move(tmp);

    if (alloc_traits::propagate_on_container_copy_assignment::value) {
      alloc_ = deque.alloc_;
    }

    return *this;
  }

  ~Deque() noexcept { destroy(); }

  Alloc get_allocator() { return alloc_; }

  size_t size() const noexcept {
    if (startBlockInd_ == endBlockInd_) {
      return endInd_ - startInd_;
    }

    size_t res = 0;
    res += kBlockSize * (endBlockInd_ - startBlockInd_ - 1);
    res += kBlockSize - startInd_;
    res += endInd_;
    return res;
  }

  bool empty() const noexcept {
    return startBlockInd_ == endBlockInd_ && startInd_ == endInd_;
  }

  T& operator[](size_t ind) {
    size_t cur_block_ind = startBlockInd_ + ind / kBlockSize;
    size_t cur_ind = startInd_ + ind % kBlockSize;

    cur_block_ind += cur_ind / kBlockSize;
    cur_ind %= kBlockSize;

    return data_[cur_block_ind][cur_ind];
  }

  const T& operator[](size_t ind) const {
    size_t cur_block_ind = startBlockInd_ + ind / kBlockSize;
    size_t cur_ind = startInd_ + ind % kBlockSize;

    cur_block_ind += cur_ind / kBlockSize;
    cur_ind %= kBlockSize;

    return data_[cur_block_ind][cur_ind];
  }

  T& at(size_t ind) {
    iterator iter = begin() + ind;

    if (ind >= size()) {
      throw std::out_of_range("");
    }

    return *iter;
  }

  const T& at(size_t ind) const {
    iterator iter = begin() + ind;

    if (ind >= size()) {
      throw std::out_of_range("");
    }

    return *iter;
  }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    construct_element(&data_[endBlockInd_][endInd_],
                      std::forward<Args>(args)...);

    expand_back();
  }

  void push_back(const T& value) {
    construct_element(&data_[endBlockInd_][endInd_], value);

    expand_back();
  }

  void push_back(T&& value) {
    construct_element(&data_[endBlockInd_][endInd_], std::move(value));

    expand_back();
  }

  void pop_back() {
    if (endInd_ == 0) {
      endInd_ = kBlockSize - 1;
      --endBlockInd_;
    } else {
      --endInd_;
    }

    destroy_element(&data_[endBlockInd_][endInd_]);
  }

  template <typename... Args>
  void emplace_front(Args&&... args) {
    expand_front();

    try {
      construct_element(&data_[startBlockInd_][startInd_],
                        std::forward<Args>(args)...);
    } catch (...) {
      ++startInd_;
      if (startInd_ == kBlockSize) {
        ++startBlockInd_;
        startInd_ = 0;
      }

      throw;
    }
  }

  void push_front(const T& value) {
    expand_front();

    try {
      construct_element(&data_[startBlockInd_][startInd_], value);
    } catch (...) {
      ++startInd_;
      if (startInd_ == kBlockSize) {
        ++startBlockInd_;
        startInd_ = 0;
      }

      throw;
    }
  }

  void push_front(T&& value) {
    expand_front();

    try {
      construct_element(&data_[startBlockInd_][startInd_], std::move(value));
    } catch (...) {
      ++startInd_;
      if (startInd_ == kBlockSize) {
        ++startBlockInd_;
        startInd_ = 0;
      }

      throw;
    }
  }

  void pop_front() {
    destroy_element(&data_[startBlockInd_][startInd_]);

    ++startInd_;
    if (startInd_ == kBlockSize) {
      ++startBlockInd_;
      startInd_ = 0;
    }
  };

  template <bool IsConst>
  class Iterator;

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  void insert(iterator iter, const T& value) {
    int64_t dist_start = iter - begin();
    int64_t dist_end = end() - iter;

    T* tmp = allocate_block(1);

    try {
      construct_element(tmp, value);
    } catch (...) {
      deallocate_block(tmp);

      throw;
    }

    if (dist_start > dist_end) {
      expand_back();
      shift_right(iter, end() - 1);
    } else {
      expand_front();
      if (begin().ind_ == kBlockSize - 1) {
        ++iter.blockInd_;
      }
      shift_left(begin(), iter);
      --iter;
    }

    move_element(*iter, *tmp);
    deallocate_block(tmp, 1);
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

  reverse_iterator rbegin() { return reverse_iterator(end()); };

  reverse_iterator rend() { return reverse_iterator(begin()); };

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(cend() - 1);
  };

  const_reverse_iterator crend() const {
    return const_reverse_iterator(cbegin() - 1);
  };

 private:
  Alloc alloc_;

  std::vector<T*> data_;
  int64_t startInd_;
  int64_t endInd_;
  int64_t startBlockInd_;
  int64_t endBlockInd_;

  static const int64_t kBlockSize = 1000;

  inline T* allocate_block(int cnt = kBlockSize) {
    return alloc_traits::allocate(alloc_, cnt);
  }
  template <typename... Args>
  inline void construct_element(Args&&... args) {
    alloc_traits::construct(alloc_, std::forward<Args>(args)...);
  }
  inline void deallocate_block(T* block, int cnt = kBlockSize) {
    alloc_traits::deallocate(alloc_, block, cnt);
  }
  inline void destroy_element(T* value) {
    alloc_traits::destroy(alloc_, value);
  }

  static inline void move_element(T& dst, T& src) noexcept {
    memcpy(&dst, &src, sizeof(T));
  }

  void destroy() noexcept {
    for (auto& elem : *this) {
      destroy_element(&elem);
    }

    for (auto& ptr : data_) {
      deallocate_block(ptr);
    }
  }

  void expand_back() {
    ++endInd_;
    if (endInd_ == kBlockSize) {
      endInd_ = 0;
      ++endBlockInd_;
      if ((int64_t)data_.size() == endBlockInd_) {
        data_.push_back(allocate_block());
      }
    }
  }

  void expand_front() {
    if (startInd_ == 0) {
      if (startBlockInd_ == 0) {
        data_.insert(data_.begin(), allocate_block());
        ++endBlockInd_;
      } else {
        --startBlockInd_;
      }

      startInd_ = kBlockSize - 1;
    } else {
      --startInd_;
    }
  }

  void shift_right(iterator left, iterator right) noexcept {
    if (left == right) {
      return;
    }

    iterator prev = right--;
    while (left != right) {
      move_element(*prev, *right);
      --right;
      --prev;
    }
  }

  void shift_left(iterator left, iterator right) noexcept {
    if (left == right) {
      return;
    }

    iterator prev = left++;
    while (left != right) {
      move_element(*prev, *left);
      ++left;
      ++prev;
    }
  }
};

template <typename T, typename Alloc>
template <bool IsConst>
class Deque<T, Alloc>::Iterator {
 public:
  friend class Deque<T>;

  using iterator_category = std::random_access_iterator_tag;
  using value_type = std::conditional_t<IsConst, const T, T>;
  using difference_type = ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  using vector_type =
      std::conditional_t<IsConst, const std::vector<T*>, std::vector<T*>>;

  Iterator(vector_type* data, int64_t block_ind, int64_t ind)
      : data_(data), blockInd_(block_ind), ind_(ind){};
  Iterator(const Iterator& iter) = default;
  Iterator& operator=(const Iterator& iter) = default;
  ~Iterator() = default;

  Iterator& operator++() {
    ++ind_;
    if (ind_ == kBlockSize) {
      ++blockInd_;
      ind_ = 0;
    }
    return *this;
  };

  Iterator operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  };

  Iterator& operator--() {
    if (ind_ == 0) {
      --blockInd_;
      ind_ = kBlockSize - 1;
    } else {
      --ind_;
    }
    return *this;
  };

  Iterator operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
  };

  Iterator operator+(int64_t value) const {
    if (value < 0) {
      return *this - (-value);
    }

    int64_t cur_block_ind = blockInd_ + value / kBlockSize;
    int64_t cur_ind = ind_ + value % kBlockSize;

    cur_block_ind += cur_ind / kBlockSize;
    cur_ind %= kBlockSize;

    return Iterator(data_, cur_block_ind, cur_ind);
  };

  Iterator& operator+=(int64_t value) {
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

  Iterator operator-(int64_t value) const {
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

    return Iterator(data_, cur_block_ind, cur_ind);
  };

  Iterator& operator-=(int64_t value) {
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

  bool operator==(const Iterator& iter) const {
    return blockInd_ == iter.blockInd_ && ind_ == iter.ind_;
  };
  bool operator!=(const Iterator& iter) const { return !(*this == iter); };
  bool operator<(const Iterator& iter) const {
    if (blockInd_ > iter.blockInd_) {
      return false;
    }
    if (blockInd_ < iter.blockInd_) {
      return true;
    }
    return ind_ < iter.ind_;
  };
  bool operator>(const Iterator& iter) const { return iter < *this; };
  bool operator>=(const Iterator& iter) const { return !(*this < iter); };
  bool operator<=(const Iterator& iter) const { return !(iter < *this); };

  difference_type operator-(const Iterator& iter) const {
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

  reference operator*() const { return (*data_)[blockInd_][ind_]; };
  pointer operator->() const { return &((*data_)[blockInd_][ind_]); };

 private:
  vector_type* data_;
  int64_t blockInd_;
  int64_t ind_;
};