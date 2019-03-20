#include "progress.h"

#include <cstdio>

void print_progress(const char *title, const int percentage, const int length) {
  fprintf(stderr, "%s: ", title);
  print_progress(percentage, length);
}

void print_progress(const int percentage, const int length) {
  const int width = 100 / length;
  fprintf(stderr, "%3d%% [", percentage);
  int full = percentage / width;
  for (int i = 0; i < full; ++i)
    fprintf(stderr, "█");

  int leak = percentage - full * width;
  leak = leak * 8 / width;

  switch (leak) {
    case 0: break;
    case 1: fprintf(stderr, "▏"); break;
    case 2: fprintf(stderr, "▎"); break;
    case 3: fprintf(stderr, "▍"); break;
    case 4: fprintf(stderr, "▌"); break;
    case 5: fprintf(stderr, "▋"); break;
    case 6: fprintf(stderr, "▊"); break;
    case 7: fprintf(stderr, "▉"); break;
    default: fprintf(stderr, "??");
  }

  for (int i = full + !!leak; i < length; ++i)
    fprintf(stderr, "  ");

  fprintf(stderr, "]\r");
  fflush(stdout);
}

void ends_progress() {
  fprintf(stderr, "\n");
}
