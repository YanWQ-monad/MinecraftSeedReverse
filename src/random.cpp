#include "random.h"

const int64_t multiplier = 0x5DEECE66DLL;
const int64_t addend = 0xBL;
const int64_t mask = (1LL << 48) - 1;

int64_t seed;

void setSeed(const int64_t new_seed) {
  seed = (new_seed ^ multiplier) & mask;
}

int next(const int bits) {
  seed = (seed * multiplier + addend) & mask;
  return static_cast<int>(seed >> (48 - bits));
}

int nextInt(const int bound) {
  if ((bound & (bound - 1)) == 0) {
    return static_cast<int>((bound * (int64_t)next(31)) >> 31);
  } else {
    return next(31) % bound;
  }
}
