#include "generator.h"

#include "random.h"

int64_t current_seed;

void setMyWorldSeed(const int64_t seed) {
  current_seed = seed;
}

inline void setRandomSeed(const int a, const int b, const int c) {
  setSeed(a * 341873128712LL + b * 132897987541LL + current_seed + c);
}

bool checkSpawnVillageWeak(const int cx, const int cz) {
  const int distance = 32;

  int x = cx, z = cz;

  if (x < 0) x -= distance - 1;
  if (z < 0) z -= distance - 1;

  setRandomSeed(x / distance, z / distance, 10387312);
  x = nextInt(distance - 8) % 8;
  z = nextInt(distance - 8) % 8;

  return static_cast<unsigned>(cx) % 8 == static_cast<unsigned>(x)
      && static_cast<unsigned>(cz) % 8 == static_cast<unsigned>(z);
}

bool checkSpawnVillage(const int cx, const int cz) {
  const int distance = 32;

  int x = cx, z = cz;

  if (x < 0) x -= distance - 1;
  if (z < 0) z -= distance - 1;

  x /= distance;
  z /= distance;
  setRandomSeed(x, z, 10387312);
  x *= distance;
  z *= distance;
  x += nextInt(distance - 8);
  z += nextInt(distance - 8);

  return cx == x && cz == z;
}

bool checkSpawnNetherFortress(const int cx, const int cz) {
  int x = cx >> 4, z = cz >> 4;
  setSeed(static_cast<int64_t>(x ^ z << 4) ^ current_seed);
  next(32);

  if (nextInt(3))
    return false;
  return cx == (x << 4) + 4 + nextInt(8)
      && cz == (z << 4) + 4 + nextInt(8);
}

bool checkSpawnTemple(const int cx, const int cz) {
  const int max_distance = 32;

  int x = cx, z = cz;

  if (x < 0) x -= max_distance - 1;
  if (z < 0) z -= max_distance - 1;

  x /= max_distance;
  z /= max_distance;
  setRandomSeed(x, z, 14357617);
  x *= max_distance;
  z *= max_distance;
  x += nextInt(max_distance - 8);
  z += nextInt(max_distance - 8);

  return cx == x && cz == z;
}

bool checkSpawnOceanMonument(const int cx, const int cz) {
  const int spacing = 32;
  const int separation = 5;

  int x = cx, z = cz;

  if (x < 0) x -= spacing - 1;
  if (z < 0) z -= spacing - 1;

  x /= spacing;
  z /= spacing;
  setRandomSeed(x, z, 10387313);
  x *= spacing;
  z *= spacing;
  x += (nextInt(spacing - separation) + nextInt(spacing - separation)) >> 1;
  z += (nextInt(spacing - separation) + nextInt(spacing - separation)) >> 1;

  return cx == x && cz == z;
}

bool checkSpawnMansion(const int cx, const int cz) {
  const int spacing = 80;
  const int separation = 20;

  int x = cx, z = cz;

  if (x < 0) x -= spacing - 1;
  if (z < 0) z -= spacing - 1;

  x /= spacing;
  z /= spacing;
  setRandomSeed(x, z, 10387319);
  x *= spacing;
  z *= spacing;
  x += (nextInt(spacing - separation) + nextInt(spacing - separation)) >> 1;
  z += (nextInt(spacing - separation) + nextInt(spacing - separation)) >> 1;

  return cx == x && cz == z;
}

bool checkSpawnEndCity(const int cx, const int cz) {
  const int spacing = 20;
  const int separation = 11;

  int x = cx, z = cz;

  if (x < 0) x -= spacing - 1;
  if (z < 0) z -= spacing - 1;

  x /= spacing;
  z /= spacing;
  setRandomSeed(x, z, 10387313);
  x *= spacing;
  z *= spacing;
  x += (nextInt(spacing - separation) + nextInt(spacing - separation)) >> 1;
  z += (nextInt(spacing - separation) + nextInt(spacing - separation)) >> 1;

  return cx == x && cz == z;
}
