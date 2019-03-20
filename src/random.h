#ifndef MINECRAFTSEED_RANDOM_H_
#define MINECRAFTSEED_RANDOM_H_

#include <cstdint>

void setSeed(const int64_t new_seed);
int next(const int bits);
int nextInt(const int bound);

#endif  // MINECRAFTSEED_RANDOM_H_
