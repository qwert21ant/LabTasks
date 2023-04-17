#pragma once

#include <iterator>
#include <type_traits>

template <class T, class Alloc = std::allocator<T>>
class List {
 private:
  struct Node;

  template <bool IsConst>
  class Iterator;

  using alloc_traits = std::allocator_traits<Alloc>;

  using node_alloc = typename alloc_traits::template rebind_alloc<Node>;
  using node_alloc_traits = typename alloc_traits::template rebind_traits<Node>;

 public:
  using value_type = T;
  using allocator_type = Alloc;

  List(const Alloc& alloc = Alloc()) : size_(0), alloc_(alloc) {
    begin_ = node_alloc_traits::allocate(alloc_, 1);
    end_ = node_alloc_traits::allocate(alloc_, 1);

    begin_->prev = nullptr;
    begin_->next = end_;

    end_->prev = begin_;
    end_->next = nullptr;
  };

  List(size_t count, const T& value, const Alloc& alloc = Alloc())
      : List(alloc) {
    try {
      while (count-- != 0) {
        push_back(value);
      }
    } catch (...) {
      this->~List();

      throw;
    }
  }

  List(std::initializer_list<T> init, const Alloc& alloc = Alloc())
      : List(alloc) {
    try {
      for (const T& item : init) {
        push_back(item);
      }
    } catch (...) {
      this->~List();

      throw;
    }
  }

  explicit List(size_t count, const Alloc& alloc = Alloc()) : List(alloc) {
    try {
      while (count-- != 0) {
        push_back();
      }
    } catch (...) {
      this->~List();

      throw;
    }
  }

  List(const List& list)
      : List(alloc_traits::select_on_container_copy_construction(list.alloc_)) {
    try {
      Node* this_prev = begin_;
      Node* list_cur = list.begin_->next;
      auto list_end = list.end_;
      while (list_cur != list_end) {
        push_back(list_cur->value);

        list_cur = list_cur->next;
      }
    } catch (...) {
      this->~List();

      throw;
    }
  };

  List& operator=(const List& list) {
    if (this == &list) {
      return *this;
    }

    try {
      List tmp(list);

      {
        Node* cur = begin_->next;
        while (cur != end_) {
          Node* next = cur->next;
          my_delete(cur);
          cur = next;
        }

        node_alloc_traits::deallocate(alloc_, begin_, 1);
        node_alloc_traits::deallocate(alloc_, end_, 1);

        begin_ = nullptr;
        end_ = nullptr;
      }

      begin_ = tmp.begin_;
      end_ = tmp.end_;
      size_ = tmp.size_;
      if (alloc_traits::propagate_on_container_copy_assignment::value) {
        alloc_ = list.alloc_;
      }

      tmp.begin_ = nullptr;
      tmp.end_ = nullptr;
      tmp.size_ = 0;

    } catch (...) {
      throw;
    }

    return *this;
  };

  List(List&& list) : size_(list.size_), alloc_(std::move(list.alloc_)) {
    begin_ = list.begin_;
    end_ = list.end_;

    list.begin_ = nullptr;
    list.end_ = nullptr;
    list.size_ = 0;
  };

  List& operator=(List&& list) noexcept {
    std::swap(begin_, list.begin_);
    std::swap(end_, list.end_);
    std::swap(alloc_, list.alloc_);
    std::swap(size_, list.size_);

    return *this;
  };

  void push_front(const T& value) {
    Node* next = begin_->next;
    begin_->next = my_new(std::move(value), begin_, next);
    next->prev = begin_->next;

    size_++;
  };

  void push_front(T&& value) {
    Node* next = begin_->next;
    begin_->next = my_new(std::move(value), begin_, next);
    next->prev = begin_->next;

    size_++;
  };

  void pop_front() noexcept {
    Node* tmp = begin_->next;
    begin_->next = tmp->next;
    tmp->next->prev = begin_;
    my_delete(tmp);

    size_--;
  };

  void push_back(const T& value) {
    Node* prev = end_->prev;
    end_->prev = my_new(value, prev, end_);
    prev->next = end_->prev;

    size_++;
  };

  void push_back(T&& value) {
    Node* prev = end_->prev;
    end_->prev = my_new(std::move(value), prev, end_);
    prev->next = end_->prev;

    size_++;
  };

  void pop_back() noexcept {
    Node* tmp = end_->prev;
    end_->prev = tmp->prev;
    tmp->prev->next = end_;
    my_delete(tmp);

    size_--;
  };

  T& front() { return begin_->next->value; }
  const T& front() const { return begin_->next->value; }

  T& back() { return end_->prev->value; }
  const T& back() const { return end_->prev->value; }

  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }

  node_alloc get_allocator() { return alloc_; }

  ~List() noexcept {
    if (!begin_ || !end_) {
      return;
    }

    Node* cur = begin_->next;
    while (cur != end_) {
      Node* next = cur->next;
      my_delete(cur);
      cur = next;
    }

    node_alloc_traits::deallocate(alloc_, begin_, 1);
    node_alloc_traits::deallocate(alloc_, end_, 1);

    begin_ = nullptr;
    end_ = nullptr;
  };

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;

  iterator begin() { return iterator(begin_->next); }
  iterator end() { return iterator(end_); }

  const_iterator begin() const { return const_iterator(begin_->next); }
  const_iterator end() const { return const_iterator(end_); }

  const_iterator cbegin() { return const_iterator(begin_->next); }
  const_iterator cend() { return const_iterator(end_); }

  reverse_iterator rbegin() { return reverse_iterator(end_->prev); }
  reverse_iterator rend() { return reverse_iterator(begin_); }

 private:
  void push_back() {
    Node* prev = end_->prev;
    end_->prev = my_new();
    end_->prev->prev = prev;
    end_->prev->next = end_;
    prev->next = end_->prev;

    size_++;
  };

  template <class... Args>
  Node* my_new(Args&&... args) {
    Node* res = node_alloc_traits::allocate(alloc_, 1);
    try {
      node_alloc_traits::construct(alloc_, res, std::forward<Args>(args)...);
    } catch (...) {
      node_alloc_traits::deallocate(alloc_, res, 1);
      throw;
    }
    return res;
  }

  void my_delete(Node* node) noexcept {
    node_alloc_traits::destroy(alloc_, node);
    node_alloc_traits::deallocate(alloc_, node, 1);
  }

  struct Node {
    Node() = default;
    Node(const T& value, Node* prev, Node* next)
        : value(value), prev(prev), next(next){};
    Node(T&& value, Node* prev, Node* next)
        : value(std::move(value)), prev(prev), next(next){};

    ~Node(){};

    T value;
    Node* prev;
    Node* next;
  };

  template <bool IsConst>
  class Iterator {
   public:
    friend class List;

    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::conditional_t<IsConst, const T, T>;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;

    Iterator(const Iterator&) = default;
    Iterator(Iterator&&) = default;

    ~Iterator() = default;

    Iterator& operator=(const Iterator&) = default;
    Iterator& operator=(Iterator&&) = default;

    Iterator& operator++() {
      node_ = node_->next;
      return *this;
    }

    Iterator operator++(int) {
      Iterator iter(*this);

      node_ = node_->next;
      return iter;
    }

    Iterator& operator--() {
      node_ = node_->prev;
      return *this;
    }

    Iterator operator--(int) {
      Iterator iter(*this);

      node_ = node_->prev;
      return iter;
    }

    bool operator==(const Iterator& iter) const { return node_ == iter.node_; }
    bool operator!=(const Iterator& iter) const { return !(*this == iter); }

    reference operator*() { return node_->value; }
    pointer operator->() { return &(node_->value); }

   private:
    Iterator(Node* node) : node_(node){};

    Node* node_;
  };

  Node* begin_;
  Node* end_;

  size_t size_;

  node_alloc alloc_;
};