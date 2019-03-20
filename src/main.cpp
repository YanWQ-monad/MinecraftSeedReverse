#include <cstdio>

#include "generator.h"
#include "wrap.h"
#include "../cubiomes/layers.h"
#include "config.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: reverse_seed [information file]\n");
    return 1;
  }
  MapInfo info = parseConfig(argv[1]);

  if (!info.valid)
    return 1;

  List out1 = List::AllocBuffer<int64_t>(128);
  List out2 = List::AllocBuffer<int64_t>(128);
  List out3 = List::AllocBuffer<int64_t>(128);
  List structures = List::FromArray<StructureInfo>(
    info.structure, info.structure_count);
  List biome = List::FromArray<BiomeInfo>(info.biome, info.biome_count);

  filterSeedLow20(structures, &out1);
  puts("Debug low 20 bit list:");
  for (int i = 0; i < out1.end; ++i)
    printf("  %ld\n", out1.get<int64_t>(i));

  filterSeedLow48(structures, out1, &out2);
  puts("Debug low 48 bit list:");
  for (int i = 0; i < out2.end; ++i)
    printf("  %ld\n", out2.get<int64_t>(i));

  filterSeedAll(biome, out2, &out3);
  puts("Possible seeds:");
  for (int i = 0; i < out3.end; ++i)
    printf("  %ld\n", out3.get<int64_t>(i));

  return 0;
}
