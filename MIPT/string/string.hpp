#pragma once

#include <cstring>
#include <iostream>
#include <vector>

class String {
 public:
  String();
  explicit String(size_t, char);
  String(const char*);

  String(const String&);
  void Swap(String&);
  String& operator=(String);
  ~String();

  void Clear();
  void PushBack(char);
  void PopBack();

  void Resize(size_t, char = '\0');
  void Reserve(size_t);
  void ShrinkToFit();

  char& operator[](size_t);
  const char& operator[](size_t) const;

  char& Front();
  const char& Front() const;

  char& Back();
  const char& Back() const;

  bool Empty() const;
  size_t Size() const;
  size_t Capacity() const;
  const char* Data() const;

  bool operator==(const String&) const;
  bool operator!=(const String&) const;
  bool operator<(const String&) const;
  bool operator>(const String&) const;
  bool operator<=(const String&) const;
  bool operator>=(const String&) const;

  String& operator+=(const String&);
  String& operator*=(int);

  friend String operator+(String, const String&);
  friend String operator*(String, int);

  friend std::ostream& operator<<(std::ostream&, const String&);
  friend std::istream& operator>>(std::istream&, String&);

  size_t Find(const String&, size_t = 0) const;
  String Substr(size_t, size_t) const;
  String Substr(size_t) const;

  std::vector<String> Split(const String& = " ") const;
  String Join(const std::vector<String>&) const;

 private:
  size_t capacity_;
  size_t size_;
  char* data_;
};