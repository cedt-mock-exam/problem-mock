#include "queue.h"
#include "student.h"
#include <cstdio>
#include <ios>
#include <iostream>
#include <string>

typedef int test_type;
inline const bool print_std = false;
inline const bool heap_guard = false;
inline const double cap_factor = 1.5;

// guard: override global new allocator (only for this thread)
static thread_local bool guard_enabled = false;
void *operator new(std::size_t size) {
  if (heap_guard && guard_enabled) throw std::bad_alloc();
  if (void *p = std::malloc(size)) return p;
  throw std::bad_alloc();
}
void *operator new[](std::size_t size) {
  if (heap_guard && guard_enabled) throw std::bad_alloc();
  if (void *p = std::malloc(size)) return p;
  throw std::bad_alloc();
}
void operator delete(void *p) noexcept { std::free(p); }
void operator delete[](void *p) noexcept { std::free(p); }

struct HeapGuard {
  bool prev;
  HeapGuard() : prev(guard_enabled) { guard_enabled = true; }
  ~HeapGuard() { guard_enabled = prev; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int A_count, B_count;
  std::cin >> A_count >> B_count;
  CP::queue<test_type> A(std::min(A_count * cap_factor, (double) 1));
  CP::queue<test_type> B(std::min(B_count * cap_factor, (double) 1));
  for (int j = 0; j < A_count; j++) {
    test_type a;
    std::cin >> a;
    A.push(a);
  }
  for (int j = 0; j < B_count; j++) {
    test_type b;
    std::cin >> b;
    B.push(b);
  }
  std::string cmd;
  while (true) {
    std::cin >> cmd;
    char self, other;
    if (cmd == "q") break;
    std::cin >> self;
    auto self_ref = (self == 'A') ? &A : &B;
    if (cmd == "p") {
      if (print_std) {
        std::cout << self_ref->size() << ' ' << self_ref->at(0) << ' ' << self_ref->at(-1) << '\n';
      } else {
        int count, idx;
        std::cout << self_ref->size() << ": ";
        std::cin >> count;
        while (count--) {
          std::cin >> idx;
          std::cout << self_ref->at(idx) << ' ';
        }
        std::cout << '\n';
      }
    } else if (cmd == "d") self_ref->pop();
    else {
      if (cmd == "e") {
        test_type k;
        std::cin >> k;
        self_ref->push(k);
      } else if (cmd == "g") {
        std::cin >> other;
        auto *other_ref = (other == 'A') ? &A : &B;
        void *m_mData = self_ref->mData_addr();
        void *k_mData = other_ref->mData_addr();
        bool should_expand = self_ref->should_expand_from_merge(*other_ref);
        if (!should_expand) {
          HeapGuard guard; // scope bounded

          self_ref->merge_greater(*other_ref);
        } else {
          self_ref->merge_greater(*other_ref);
        }
        if (other_ref->mData_addr() != k_mData) return 1;
        if (!should_expand && self_ref->mData_addr() != m_mData) return 1;
      }
    }
  }
  std::cout << "OK: SVDIsTheDiamondInTheLandOfLinearAlgebra :)";
  return 0;
}