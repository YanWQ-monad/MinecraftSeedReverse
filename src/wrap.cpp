#include "wrap.h"

#include <cstdio>
#include "generator.h"
#include "progress.h"

extern "C" {
#include "../cubiomes/generator.h"
#include "../cubiomes/finders.h"
}

const ReverseLookup structure_type_reverse[] = {
  ReverseLookup("Village", StructureInfo::VILLAGE),
  ReverseLookup("OceanMonument", StructureInfo::OCEAN_MONUMENT),
  ReverseLookup("NetherFortress", StructureInfo::NETHER_FORTRESS),
  ReverseLookup("Temple", StructureInfo::TEMPLE),
  ReverseLookup("Mansion", StructureInfo::MANSION),
  ReverseLookup("EndCity", StructureInfo::END_CITY),
  ReverseLookup("", -1),
};

const ReverseLookup biome_type_reverse[] = {
  ReverseLookup("Ocean", ocean),
  ReverseLookup("Plains", plains),
  ReverseLookup("Desert", desert),
  ReverseLookup("Mountains", extremeHills),
  ReverseLookup("Forest", forest),
  ReverseLookup("Taiga", taiga),
  ReverseLookup("Swamp", swampland),
  ReverseLookup("River", river),
  ReverseLookup("Nether", hell),
  ReverseLookup("TheEnd", sky),
  ReverseLookup("FrozenOcean", frozenOcean),
  ReverseLookup("FrozenRiver", frozenRiver),
  ReverseLookup("SnowyTundra", icePlains),
  ReverseLookup("SnowyMountains", iceMountains),
  ReverseLookup("MushroomFields", mushroomIsland),
  ReverseLookup("MushroomFieldShore", mushroomIslandShore),
  ReverseLookup("Beach", beach),
  ReverseLookup("DesertHills", desertHills),
  ReverseLookup("WoodedHills", forestHills),
  ReverseLookup("TaigaHills", taigaHills),
  ReverseLookup("MountainEdge", extremeHillsEdge),
  ReverseLookup("Jungle", jungle),
  ReverseLookup("JungleHills", jungleHills),
  ReverseLookup("JungleEdge", jungleEdge),
  ReverseLookup("DeepOcean", deepOcean),
  ReverseLookup("StoneShore", stoneBeach),
  ReverseLookup("SnowyBeach", coldBeach),
  ReverseLookup("BirchForest", birchForest),
  ReverseLookup("BirchForestHills", birchForestHills),
  ReverseLookup("DarkForest", roofedForest),
  ReverseLookup("SnowyTaiga", coldTaiga),
  ReverseLookup("SnowyTaigaHills", coldTaigaHills),
  ReverseLookup("GiantTreeTaiga", megaTaiga),
  ReverseLookup("GiantTreeTaigaHills", megaTaigaHills),
  ReverseLookup("WoodedMountains", extremeHillsPlus),
  ReverseLookup("Savanna", savanna),
  ReverseLookup("SavannaPlateau", savannaPlateau),
  ReverseLookup("Badlands", mesa),
  ReverseLookup("WoodedBadlandsPlateau", mesaPlateau_F),
  ReverseLookup("BadlandsPlateau", mesaPlateau),
  ReverseLookup("SmallEndIslands", skyIslandLow),
  ReverseLookup("EndMidlands", skyIslandMedium),
  ReverseLookup("EndHighlands", skyIslandHigh),
  ReverseLookup("EndBarrens", skyIslandBarren),
  ReverseLookup("WarmOcean", warmOcean),
  ReverseLookup("LukewarmOcean", lukewarmOcean),
  ReverseLookup("ColdOcean", coldOcean),
  ReverseLookup("DeepWarmOcean", warmDeepOcean),
  ReverseLookup("DeepLukewarmOcean", lukewarmDeepOcean),
  ReverseLookup("DeepColdOcean", coldDeepOcean),
  ReverseLookup("DeepFrozenOcean", frozenDeepOcean),
  ReverseLookup("TheVoid", 127),
  ReverseLookup("SunflowerPlains", plains + 128),
  ReverseLookup("DesertLakes", desert + 128),
  ReverseLookup("GravellyMountains", extremeHills + 128),
  ReverseLookup("FlowerForest", forest + 128),
  ReverseLookup("TaigaMountains", taiga + 128),
  ReverseLookup("SwampHills", swampland + 128),
  ReverseLookup("IceSpikes", icePlains + 128),
  ReverseLookup("ModifiedJungle", jungle + 128),
  ReverseLookup("ModifiedJungleEdge", jungleEdge + 128),
  ReverseLookup("TallBirchForest", birchForest + 128),
  ReverseLookup("TallBirchHills", birchForestHills + 128),
  ReverseLookup("DarkForestHills", roofedForest + 128),
  ReverseLookup("SnowyTaigaMountains", coldTaiga + 128),
  ReverseLookup("GiantSpruceTaiga", megaTaiga + 128),
  ReverseLookup("GiantSpruceTaigaHills", megaTaigaHills + 128),
  ReverseLookup("ModifiedGravellyMountains", extremeHillsPlus + 128),
  ReverseLookup("ShatteredSavanna", savanna + 128),
  ReverseLookup("ShatteredSavannaPlateau", savannaPlateau + 128),
  ReverseLookup("ErodedBadlands", mesa + 128),
  ReverseLookup("ModifiedWoodedBadlandsPlateau", mesaPlateau_F + 128),
  ReverseLookup("ModifiedBadlandsPlateau", mesaPlateau + 128),
  ReverseLookup("", -1),
};

LayerStack getStack() {
  initBiomes();
  return setupGenerator(MC_1_9);
}

LayerStack stack = getStack();

bool checkStructures(const StructureInfo &structure, const bool weak) {
  switch (structure.type) {
    case StructureInfo::UNSET:
      return true;
    case StructureInfo::VILLAGE:
      return weak ? checkSpawnVillageWeak(structure.x, structure.y)
                  : checkSpawnVillage(structure.x, structure.y);
    case StructureInfo::OCEAN_MONUMENT:
      return weak ? true : checkSpawnOceanMonument(structure.x, structure.y);
    case StructureInfo::NETHER_FORTRESS:
      return weak ? true : checkSpawnNetherFortress(structure.x, structure.y);
    case StructureInfo::TEMPLE:
      return weak ? true : checkSpawnTemple(structure.x, structure.y);
    case StructureInfo::MANSION:
      return weak ? true : checkSpawnMansion(structure.x, structure.y);
    case StructureInfo::END_CITY:
      return weak ? true : checkSpawnEndCity(structure.x, structure.y);
    default:
      fprintf(stderr, "[WARNING] Unknown structure type: %d\n", structure.type);
      return true;
  }
}

bool checkBiome(const int64_t seed, const List &biomes) {
  applySeed(&stack, seed);
  for (int i = 0; i < biomes.end; ++i) {
    BiomeInfo biome = biomes.get<BiomeInfo>(i);
    if (getBiomeAtPos(stack, (Pos){ biome.x, biome.y }) != biome.type)
      return false;
  }
  return true;
}

bool checkLow20(const int64_t seed, const List &structures) {
  setMyWorldSeed(seed);
  for (int i = 0; i < structures.end; ++i)
    if (!checkStructures(structures.get<StructureInfo>(i), true))
      return false;
  return true;
}

bool checkLow48(const int64_t seed, const List &structures) {
  setMyWorldSeed(seed);
  for (int i = 0; i < structures.end; ++i)
    if (!checkStructures(structures.get<StructureInfo>(i), false))
      return false;
  return true;
}

void filterSeedLow20(const List &structures, List *out) {
  const char *title = "Filtering low 20 bits";

  for (int64_t s = 0; s < (1 << 20); ++s) {
    if (checkLow20(s, structures))
      out->put<int64_t>(s);
    if (!(s & ((1 << 13) - 1)))
      print_progress(title, s * 100 / (1LL << 20));
  }

  print_progress(title, 100);
  puts("");
}

void filterSeedLow48(const List &structures, const List &low20, List *out) {
  const char *title = "Filtering low 48 bits";
  const int64_t total = static_cast<int64_t>(low20.end) * (1 << 28);
  int64_t s20, seed, s;

  for (int i = 0; i < low20.end; ++i) {
    s20 = low20.get<int64_t>(i);
    for (s = 0; s < (1 << 28); ++s) {
      seed = s << 20 | s20;
      if (checkLow48(seed, structures))
        out->put<int64_t>(seed);

      if (!(s & ((1 << 20) - 1)))
        print_progress(title, (i * (1LL << 28) + s) * 100 / total);
    }
  }

  print_progress(title, 100);
  puts("");
}

void filterSeedAll(const List &biomes, const List &low48, List *out) {
  const char *title = "Filtering high 16 bits";
  const int64_t total = static_cast<int64_t>(low48.end) * (1 << 16);
  int64_t s48, s, seed;

  for (int i = 0; i < low48.end; ++i) {
    s48 = low48.get<int64_t>(i);
    for (s = 0; s < (1 << 16); ++s) {
      seed = s << 48 | s48;
      if (checkBiome(seed, biomes))
        out->put<int64_t>(seed);

      if (!(s & ((1 << 8) - 1)))
        print_progress(title, (i * (1LL << 16) + s) * 100 / total);
    }
  }

  print_progress(title, 100);
  puts("");
}
