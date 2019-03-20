#ifndef MINECRAFTSEED_GENERATOR_H_
#define MINECRAFTSEED_GENERATOR_H_

#include <cstdint>

void setMyWorldSeed(const int64_t seed);

bool checkSpawnEndCity(const int cx, const int cz);
bool checkSpawnMansion(const int cx, const int cz);
bool checkSpawnNetherFortress(const int cx, const int cz);
bool checkSpawnOceanMonument(const int cx, const int cz);
bool checkSpawnTemple(const int cx, const int cz);
bool checkSpawnVillage(const int cx, const int cz);
bool checkSpawnVillageWeak(const int cx, const int cz);

#endif  // MINECRAFTSEED_GENERATOR_H_
