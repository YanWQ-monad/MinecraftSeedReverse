#ifndef MINECRAFTSEED_CONFIG_H_
#define MINECRAFTSEED_CONFIG_H_

#include "wrap.h"

struct MapInfo {
  bool valid;
  StructureInfo *structure;
  BiomeInfo *biome;
  int structure_count, biome_count;
};

MapInfo parseConfig(const char *filename);


#endif  // MINECRAFTSEED_CONFIG_H_
