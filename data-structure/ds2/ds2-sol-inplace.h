#ifndef __STUDENT_H_
#define __STUDENT_H_

#include "ds2-queue.h"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <vector>

// constraint other.mSize <= 0.5 this.mSize
// if not, we would have to separate case where push front and push back
template <typename T> void CP::queue<T>::merge_greater(CP::queue<T> &other) {
  if (this == &other) return;
  size_t move_count = 0;                      // size_t overlap_size = std::min(mSize, other.mSize) // (actual);
  size_t overlap_size = other.mSize;          // simply use other.mSize given the constraint
  for (size_t i = 0; i < overlap_size; i++) { // pre-count O(min(this_size, other_size)) -> O(n)
    if (other.mData[(other.mFront + i) % other.mCap] > mData[(mFront + i) % mCap]) move_count++;
  }
  ensureCapacity(move_count + mSize);
  mFront = mCap == 0 ? 0 : (mFront - move_count + mCap) % mCap;

  // orig = logical index in original mData and other.mData
  size_t self_out = 0;                                 // logical index to write to mData (+ mFront)
  size_t other_out = 0;                                // logical index to write to other.mData (+ mFront)
  for (size_t orig = 0; orig < overlap_size; orig++) { // O(min(this_size, other_size)) -> O(n)
    if (other.mData[(other.mFront + orig) % other.mCap] > mData[(mFront + move_count + orig) % mCap]) {
      mData[(mFront + self_out) % mCap] = mData[(mFront + move_count + orig) % mCap];
      mData[(mFront + self_out + 1) % mCap] = other.mData[(other.mFront + orig) % other.mCap];
      self_out += 2;
    } else {
      mData[(mFront + self_out) % mCap] = mData[(mFront + move_count + orig) % mCap];
      other.mData[(other.mFront + other_out) % other.mCap] = other.mData[(other.mFront + orig) % other.mCap];
      other_out++;
      self_out++;
    }
  }
  mSize += move_count;
  other.mSize -= move_count;
}

#endif