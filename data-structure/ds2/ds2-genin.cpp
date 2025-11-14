#include "gentools.hpp"
#include "queue.h"
#include "student.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <list>
#include <string>
#include <vector>

inline const double cap_factor = 1.5;

// mutable queues
CP::queue<int> A;
CP::queue<int> B;
int overlap_size = 0;

// for outputting to file
std::vector<int> print_A;
std::vector<int> print_B;
std::vector<std::string> actions;

void gen_queue_pair(random_t *rnd, int a_count, int b_count, double merge_prob) {
  b_count = std::min(b_count, a_count / 2);
  A.clean(a_count, std::max(a_count * cap_factor, (double)1));
  B.clean(b_count, std::max(b_count * cap_factor, (double)1));
  print_A.resize(a_count);
  print_B.resize(b_count);
  for (int i = 0; i < a_count; i++) {
    print_A[i] = A.at(i) = rnd->next(-5e8, 5e8);
  }
  for (int i = 0; i < b_count; i++) {
    if (rnd->next() < merge_prob) B.at(i) = rnd->next(A.at(i) + 1, (int)1e9);
    else B.at(i) = rnd->next((int)-1e9, A.at(i));
    print_B[i] = B.at(i);
  }
}

void merge(char self, char other) {
  auto &self_ptr = (self == 'A') ? A : B;
  auto &other_ptr = (other == 'A') ? A : B;
  if (other_ptr.size() > self_ptr.size() / 2 && self != other) return;
  self_ptr.merge_greater(other_ptr);
  actions.push_back(format("g %c %c", self, other));
  overlap_size = other_ptr.size();
}

const inline double overlap_ratio = 0.6;

void print(random_t *rnd, char self, int count = 1, int power = 4) {
  auto &queue_ptr = (self == 'A') ? A : B;
  int sz = queue_ptr.size();
  if (sz == 0 || count <= 0) return;
  count = std::min(count, sz);
  std::vector<int> indices;
  indices.reserve(count);
  for (int i = 0; i < count; i++) {
    int idx;
    do {
      double raw = rnd->next();
      raw = std::pow(raw, power); // bias towards front
      if (overlap_size > 0 && i < overlap_size && rnd->next() < overlap_ratio) {
        idx = raw * std::min(overlap_size - 1, sz - 1);
      } else {
        idx = raw * sz;
      }
    } while (std::find(indices.begin(), indices.end(), idx) != indices.end());
    indices.push_back(idx);
  }
  std::sort(indices.begin(), indices.end());
  std::string action = format("p %c %d", self, count);
  for (int idx : indices) {
    action += format(" %d", idx);
  }
  actions.push_back(action);
}

void push(char self, int value) {
  auto &self_ptr = (self == 'A') ? A : B;
  self_ptr.push(value);
  actions.push_back(format("e %c %d", self, value));
}

void pop(char self) {
  auto &self_ptr = (self == 'A') ? A : B;
  self_ptr.pop();
  actions.push_back(format("d %c", self));
}

int main(int argc, char **argv) {
  useGenIn(
      1, 20,
      [](int tc, random_t *rnd, std::ofstream *out) {
        actions.clear();
        if (tc == 1) { // self merge return
          gen_queue_pair(rnd, 500000, 1, 1);
          for (int i = 0; i < 50000; i++)
            merge('A', 'A');
          print(rnd, 'A', 100, 100);
          print(rnd, 'B');
          push('B', rnd->next((int)-1e9, (int)A[1]));
          merge('A', 'B');
          print(rnd, 'B', 1);
          print(rnd, 'A', 10, 1e5);
          pop('A');
          print(rnd, 'A', 5);

        } else if (tc <= 3) { // empty other
          gen_queue_pair(rnd, 100, 0, 0.3);
          print(rnd, 'A', 50);
          merge('A', 'B');
          push('B', rnd->next((int)-1e9, A[0]));
          push('B', rnd->next(A[1] + 1, (int)1e9));
          push('B', rnd->next((int)-1e9, A[2]));
          print(rnd, 'B', 3);
          merge('A', 'B');
          print(rnd, 'A', 20, 100);
          print(rnd, 'B', 2, 100);

        } else if (tc <= 5) { // empty both
          gen_queue_pair(rnd, 0, 0, 0);
          merge('A', 'B');
          for (int i = 0; i < 3; i++) {
            push('A', rnd->next((int)-1e9, (int)1e9));
            push('B', i == 1 ? rnd->next((int)-1e9, A[i]) : rnd->next(A[i] + 1, (int)1e9));
          }
          for (int i = 0; i < rnd->next(3, 5); i++) {
            push('A', rnd->next((int)-1e9, (int)1e9));
          }
          print(rnd, 'A', 3);
          print(rnd, 'B', 3);
          merge('A', 'B');
          print(rnd, 'A', 5, 1);
          print(rnd, 'B', 1, 1);

        } else if (tc <= 8) { // ensureCapacity
          int a_size = rnd->next(500, 1000);
          gen_queue_pair(rnd, a_size, a_size / 2, 0.9);
          int target_size = a_size * 1.25;
          for (int i = a_size; i < target_size; i++) {
            push('A', rnd->next((int)-1e9, (int)1e9));
          }
          print(rnd, 'A', 0.5 * a_size, 20);
          merge('A', 'B');
          print(rnd, 'A', 250, 50);
          print(rnd, 'B', 100, 50);

        } else if (tc <= 13) { // mCap
          int a_size = rnd->next(50, 100);
          gen_queue_pair(rnd, a_size, a_size / 2, 1);
          int target_mFront = a_size * cap_factor - 1;
          for (int i = 0; i < target_mFront; i++) {
            pop('A');
            push('A', rnd->next((int)-1e9, (int)0));
          }
          print(rnd, 'A', 40, 50);
          merge('A', 'B');
          print(rnd, 'A', 40, 100);
          print(rnd, 'B', 5, 10);
        }

        else if (tc <= 20) { // stress test
          int a_size = rnd->next(450000, 500000);
          gen_queue_pair(rnd, a_size, a_size / 8, 0.8);
          int round = 125;
          for (int i = 0; i < round; i++) {
            if (rnd->next() < 0.2 && A.size() > 0) pop('A');
            if (rnd->next() < 0.2 && B.size() > 0) pop('B');
            merge('A', 'B');
            if (rnd->next() < 0.2) print(rnd, 'A', 50, 200);
            if (rnd->next() < 0.2) print(rnd, 'B', 20, 200);
            int j = A.merge_mask_size(B);
            while (j <= 0) {
              push('A', rnd->next((int)-1e9, (int)1e9));
              j++;
            }
          }
          print(rnd, 'A', 100, 10);
          print(rnd, 'B', 100, 10);
        }

        *out << print_A.size() << ' ' << print_B.size() << '\n';
        for (auto &a : print_A)
          *out << a << ' ';
        if (!print_A.empty()) *out << '\n';
        for (auto &b : print_B)
          *out << b << ' ';
        if (!print_B.empty()) *out << '\n';
        for (auto &act : actions)
          *out << act << '\n';
        *out << 'q';
      },
      argc, argv, 1762937775);
  return 0;
}