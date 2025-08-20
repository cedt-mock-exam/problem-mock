/**
  written by @enderpalm, expect bugs >_<
*/

#ifndef GENTOOLS
#define GENTOOLS

#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <sys/types.h>

/**
 * @brief Generate test cases and write them to separate files
 *
 * @param tc Number of test cases to generate
 * @param generator Function that generates a test case (takes index and mt19937
 * generator as parameter)
 * @param seed seed to mt19937 rng
 */

inline void useGenIn(int tc,
                     std::function<void(int, std::mt19937_64)> generator,
                     unsigned long seed = 0) {
  std::streambuf *coutBuffer = std::cout.rdbuf();
  std::random_device rd;
  ulong actualSeed = seed == 0 ? rd() : seed;
  std::mt19937_64 gen(actualSeed);
  std::cout << "Using seed: " << actualSeed << '\n';

  for (int i = 0; i < tc; ++i) {
    std::string filename = "testcase/" + std::to_string(i + 1) + ".in";
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
      std::cerr << "Failed to open file: " << filename << std::endl;
      continue;
    }
    std::cout.rdbuf(outFile.rdbuf());
    gen.discard(1);
    generator(i, gen);
    std::cout.rdbuf(coutBuffer);
    outFile.close();
    std::cout << "Generated: " + std::to_string(i + 1) + ".in\n";
  }

  std::cout.rdbuf(coutBuffer);
}

inline int randInt(int lower, int upper, std::mt19937_64 &gen) {
  std::uniform_int_distribution<> dis(lower, upper);
  gen.discard(1);
  return dis(gen);
}

inline double randDouble(double lower, double upper, std::mt19937_64 &gen, double precision = 1e6) {
  std::uniform_real_distribution<> dis(lower, upper);
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
}

#endif
