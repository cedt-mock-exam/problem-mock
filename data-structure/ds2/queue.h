#ifndef _CP_QUEUE_INCLUDED_
#define _CP_QUEUE_INCLUDED_

#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
// #pragma once

namespace CP {

template <typename T> class queue {
protected:
  T *mData;
  size_t mCap;
  size_t mSize;
  size_t mFront;
  static const std::vector<int> default_indices;

  void expand(size_t capacity) {
    T *arr = new T[capacity]();
    for (size_t i = 0; i < mSize; i++) {
      arr[i] = mData[(mFront + i) % mCap];
    }
    delete[] mData;
    mData = arr;
    mCap = capacity;
    mFront = 0;
  }

  void ensureCapacity(size_t capacity) {
    if (capacity > mCap) {
      size_t s = (capacity > 2 * mCap) ? capacity : 2 * mCap;
      expand(s);
    }
  }

public:
  //-------------- constructor ----------

  // copy constructor
  queue(const queue<T> &a) : mData(new T[a.mCap]()), mCap(a.mCap), mSize(a.mSize), mFront(a.mFront) {
    for (size_t i = 0; i < a.mCap; i++) {
      mData[i] = a.mData[i];
    }
  }

  // default constructor
  queue() : mData(new T[1]()), mCap(1), mSize(0), mFront(0) {}

  // copy assignment operator
  queue<T> &operator=(queue<T> other) {
    using std::swap;
    swap(mSize, other.mSize);
    swap(mCap, other.mCap);
    swap(mData, other.mData);
    swap(mFront, other.mFront);
    return *this;
  }

  ~queue() { delete[] mData; }

  //------------- capacity function -------------------
  bool empty() const { return mSize == 0; }

  size_t size() const { return mSize; }

  //----------------- access -----------------
  const T &front() const {
    if (size() == 0) throw std::out_of_range("index of out range");
    return mData[mFront];
  }
  const T &back() const {
    if (size() == 0) throw std::out_of_range("index of out range");
    return mData[(mFront + mSize - 1) % mCap];
  }

  //----------------- modifier -------------
  void push(const T &element) {
    ensureCapacity(mSize + 1);
    mData[(mFront + mSize) % mCap] = element;
    mSize++;
  }

  void pop() {
    if (size() == 0) throw std::out_of_range("index of out range");
    mFront = (mFront + 1) % mCap;
    mSize--;
  }

  void print_check() { std::printf("%zu %s %s\n", mSize, std::to_string(this->front()).c_str(), std::to_string(this->back()).c_str()); }

  //-------------- For student.h --------------
  void merge_greater(CP::queue<T> &other);

  //-------------- For runner and genin ------
  queue(size_t capacity) : mData(new T[capacity]()), mCap(capacity), mSize(0), mFront(0) {}

  // [deprecated] construct with vector and denote initial capacity
  queue(const std::vector<T> &initial, double cap_factor = 2) {
    cap_factor = std::max(cap_factor, 1.0);
    mCap = (size_t)(initial.size() * cap_factor);
    mData = new T[mCap];
    for (size_t i = 0; i < initial.size(); i++) {
      mData[i] = initial[i];
    }
    mSize = initial.size();
    mFront = 0;
  }

  void *mData_addr() { return &mData; }

  // loosely allow maximum this.mSize + other mSize, not actual merge amount
  bool should_expand_from_merge(CP::queue<T> &other) { return mSize + other.mSize > mCap; }

  // works for int indices - good enough
  void print(const std::vector<int> &indices = default_indices) {
    std::printf("%zu: ", mSize);
    for (auto &i : indices) {
      if (i >= (int)mSize || i < -(int)mSize) continue;
      if (i < 0) std::printf("%s ", std::to_string(mData[(mFront + mSize + i) % mCap]).c_str());
      else std::printf("%s ", std::to_string(mData[(mFront + i) % mCap]).c_str());
    }
    std::printf("\n");
  }

  T &at(const int &index) {
    if (index >= (int)mSize || index < -(int)mSize) throw std::out_of_range("index of out range");
    if (index < 0) return mData[(mFront + mSize + index) % mCap];
    else return mData[(mFront + index) % mCap];
  }

  // For genin only

  size_t merge_mask_size(CP::queue<T> &other) {
    size_t move_count = 0;
    for (int i = 0; i < other.size(); i++) {
      if (other.mData[(other.mFront + i) % other.mCap] > mData[(mFront + i) % mCap]) move_count++;
    }
    return move_count;
  }

  void clean(size_t size, size_t capacity) {
    T *arr = new T[capacity]();
    delete[] mData;
    mData = arr;
    mCap = capacity;
    mSize = size;
    mFront = 0;
  }

  T &operator[](const int &index) {
    if (index >= (int)mSize || index < -(int)mSize) throw std::out_of_range("index of out range");
    if (index < 0) return mData[(mFront + mSize + index) % mCap];
    else return mData[(mFront + index) % mCap];
  }

  const T &operator[](const int &index) const {
    if (index >= (int)mSize || index < -(int)mSize) throw std::out_of_range("index of out range");
    if (index < 0) return mData[(mFront + mSize + index) % mCap];
    else return mData[(mFront + index) % mCap];
  }
};

template <typename T> const std::vector<int> queue<T>::default_indices = {0, -1};

} // namespace CP

#endif
