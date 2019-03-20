#include "config.h"

#include <cstring>
#include <cerrno>
#include <cstdio>

constexpr int MAX_BUFFER = 1048576;  // 1 MB
char buf[MAX_BUFFER];

size_t removeComment(char *content, const size_t filesize) {
  size_t length = 0;
  for (size_t r=0, s=0; r < filesize; ++r) {
    if (s) {
      if (content[r] == '\n')
        s = 0;
    } else if (content[r] == '#') {
      s = 1;
    } else if (content[r] != '\r') {  // ignore '\r'
      content[length] = content[r];
      ++length;
    }
  }
  content[length] = '\0';
  return length;
}

int splitLines(char *content, const size_t length, char ***line_p) {
  int lines = 0, cur = 0;
  for (size_t i = 0; i < length; ++i)
    lines += content[i] == '\n';

  char **line = static_cast<char**>(malloc(sizeof(char*) * (lines + 1)));
  *line_p = line;

  line[0] = content + 0;
  for (size_t i = 0; i < length; ++i)
    if (content[i] == '\n') {
      content[i] = '\0';
      if (i + 1 < length)
        line[++cur] = content + i + 1;
    }
  line[lines] = content + length;  // 0x00
  return lines;
}

int parseStructureList(char const* const *line, const int start,
                       MapInfo *info) {
  static char tmp[1024];
  int cnt = 0;
  for (int i = start; strcmp(line[i], ""); ++i)
    ++cnt;

  StructureInfo *si = static_cast<StructureInfo*>(
    malloc(sizeof(StructureInfo) * cnt));
  for (int i = 0; i < cnt; ++i) {
    sscanf(line[i + start], "  %s %d %d", tmp, &si[i].x, &si[i].y);
    si[i].type = StructureInfo::UNSET;
    for (int j = 0; structure_type_reverse[j].text[0] != '\0'; ++j)
      if (!strcmp(structure_type_reverse[j].text, tmp)) {
        si[i].type = static_cast<StructureInfo::TYPE>(
          structure_type_reverse[j].value);
        break;
      }
    if (si[i].type == StructureInfo::UNSET)
      fprintf(stderr, "[WARNING] Unknown biome type: %s\n", tmp);
  }

  info->structure = si;
  info->structure_count = cnt;
  return cnt;
}

int parseBiomeList(char const* const *line, const int start, MapInfo *info) {
  static char tmp[1024];
  int cnt = 0;
  for (int i = start; strcmp(line[i], ""); ++i)
    ++cnt;

  BiomeInfo *bi = static_cast<BiomeInfo*>(malloc(sizeof(BiomeInfo) * cnt));
  for (int i = 0; i < cnt; ++i) {
    sscanf(line[i + start], "  %s %d %d", tmp, &bi[i].x, &bi[i].y);
    bi[i].type = -1;
    for (int j = 0; biome_type_reverse[j].text[0] != '\0'; ++j)
      if (!strcmp(biome_type_reverse[j].text, tmp)) {
        bi[i].type = biome_type_reverse[j].value;
        break;
      }
    if (bi[i].type == -1)
      fprintf(stderr, "[WARNING] Unknown biome type: %s\n", tmp);
  }

  info->biome = bi;
  info->biome_count = cnt;
  return cnt;
}

MapInfo parseConfig(const char *filename) {
  MapInfo info;
  info.valid = false;
  FILE *f = fopen(filename, "r");

  if (!f) {
    fprintf(stderr, "Could not open \"%s\": %s\n", filename, strerror(errno));
    return info;
  }

  size_t filesize, length;
  filesize = fread(buf, sizeof(char), MAX_BUFFER, f);
  length = removeComment(buf, filesize);

  char **line = NULL;
  int lines = splitLines(buf, length, &line);

  for (int i = 0; i < lines; ++i) {
    if (!strcmp(line[i], "Structures:")) {
      i += parseStructureList(line, i + 1, &info) + 1;
    } else if (!strcmp(line[i], "Biomes:")) {
      i += parseBiomeList(line, i + 1, &info) + 1;
    }
  }
  info.valid = true;

  return info;
}
