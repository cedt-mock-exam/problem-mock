/**
  written by @enderpalm, expect bugs >_<
  edited for mock-exam (to be used with testlib)
  won't work without testlib.h - make sure this file is
  in the same directory as testlib.h file
*/

#ifndef GENTOOLS
#define GENTOOLS

#include "testlib.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sys/types.h>

/**
 * @brief Generate test cases and write them to separate files
 *
 * @param tc Number of test cases to generate
 * @param generator Function that generates a test case (takes index and
 * testlib's rnd generator as parameter)
 * @param seed seed to testlib's rnd
 */

inline void
useGenIn(int tc,
         std::function<void(int, random_t *, std::ofstream *)> generator,
         int argc, char **argv, unsigned long seed = 0) {
  registerGen(argc, argv, 1); // use in-code parameter instead
  rnd.setSeed(seed == 0 ? time(0) : seed);
  for (int i = 1; i <= tc; ++i) {
    std::string filename = "testcase/" + std::to_string(i) + ".in";
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
      std::cerr << "Failed to open file: " << filename << std::endl;
      continue;
    }
    generator(i, &rnd, &outFile);
    outFile.close();
    std::cout << "Generated: " + std::to_string(i) + ".in\n";
  }
}

// Use testlib's functions instead

/* inline int randInt(int lower, int upper, std::mt19937_64 &gen) {
  std::uniform_int_distribution<> dis(lower, upper);
  gen.discard(1);
  return dis(gen);
}

inline double randDouble(double lower, double upper, std::mt19937_64 &gen,
double precision = 1e6) { std::uniform_real_distribution<> dis(lower, upper);
  gen.discard(1);
  return round(dis(gen) * precision) / precision;
}

inline bool randBool(std::mt19937_64 &gen, double percent_true = 0.5) {
  std::uniform_real_distribution<> dis(0, 1);
  gen.discard(1);
  return dis(gen) <= percent_true;
}

template <typename T>
inline const T &randVec(std::vector<T> &vec, std::mt19937_64 &gen) {
  int index = randInt(0, vec.size() - 1, gen);
  return vec[index];
} */

#endif
