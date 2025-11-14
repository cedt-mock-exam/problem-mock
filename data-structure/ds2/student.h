#ifndef __STUDENT_H_
#define __STUDENT_H_

#include "queue.h"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <vector>

// naive ver: O(n) space & time
template <typename T> void CP::queue<T>::merge_greater(CP::queue<T> &other) {
  if (this == &other) return;
  std::vector<T> new_self;
  std::vector<T> new_other;
  new_self.reserve(mSize + other.mSize); // should reserve
  new_other.reserve(other.mSize);
  for (int i = 0; i < other.mSize; i++) {
    T self_data = mData[(mFront + i) % mCap];
    T other_data = other.mData[(other.mFront + i) % other.mCap];
    if (other_data > self_data) { // should use > not >=
      new_self.push_back(self_data);
      new_self.push_back(other_data);
    } else {
      new_self.push_back(self_data);
      new_other.push_back(other_data);
    }
  }
  for (int i = other.mSize; i < mSize; i++) { // remaining element
    new_self.push_back(mData[(mFront + i) % mCap]);
  }
  ensureCapacity(mSize + other.mSize); // have to ensureCapacity
  for (int i = 0; i < new_self.size(); i++)
    mData[(mFront + i) % mCap] = new_self[i];
  for (int i = 0; i < new_other.size(); i++)
    other.mData[(other.mFront + i) % other.mCap] = new_other[i];

  mSize = new_self.size();
  other.mSize = new_other.size();
}

#endif