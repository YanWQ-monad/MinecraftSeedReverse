#ifndef MINECRAFTSEED_WRAP_H_
#define MINECRAFTSEED_WRAP_H_

#include "list.h"
#include <cstdint>

extern "C" {
#include "../cubiomes/layers.h"
}

struct StructureInfo {
  enum TYPE {
    UNSET,
    VILLAGE,
    OCEAN_MONUMENT,
    NETHER_FORTRESS,
    TEMPLE,  // include Desert Temple, Jungle Temple, Witch Hut, Igloo
    MANSION,
    END_CITY,
  };

  // The center(chunk) of the structure:
  //   Village: the well
  //   Ocean Monument: the top roof of the monument
  //   Nether Fortress: some crossroad (difficult to determine)
  //   Temple: The center of the temple
  //   Mansion: The center of the gate
  //   End City: The center of the first floor

  int x, y;
  TYPE type;
  StructureInfo(const int xp, const int yp, const TYPE type_p)
      : x(xp), y(yp), type(type_p) {}
};

struct BiomeInfo {
  int x, y, type;
  BiomeInfo(const int xp, const int yp, const int type_p)
      : x(xp), y(yp), type(type_p) {}
};

struct ReverseLookup {
  const char *text;
  int value;
  ReverseLookup(const char *text_p, const int value_p)
      : text(text_p), value(value_p) {}
};

extern const ReverseLookup structure_type_reverse[];
extern const ReverseLookup biome_type_reverse[];

bool checkLow20(const int64_t seed, const List &structures);
bool checkLow48(const int64_t seed, const List &structures);
bool checkBiome(const int64_t seed, const List &biomes);
void filterSeedLow20(const List &structures, List *out);
void filterSeedLow48(const List &structures, const List &low20, List *out);
void filterSeedAll(const List &biomes, const List &low48, List *out);

#endif  // MINECRAFTSEED_WRAP_H_
