#include "progress.h"

#include <cstdio>

void print_progress(const char *title, const int percentage, const int length) {
  printf("%s: ", title);
  print_progress(percentage, length);
}

void print_progress(const int percentage, const int length) {
  const int width = 100 / length;
  printf("%3d%% [", percentage);
  int full = percentage / width;
  for (int i = 0; i < full; ++i)
    printf("█");

  int leak = percentage - full * width;
  leak = leak * 8 / width;

  switch (leak) {
    case 0: break;
    case 1: printf("▏"); break;
    case 2: printf("▎"); break;
    case 3: printf("▍"); break;
    case 4: printf("▌"); break;
    case 5: printf("▋"); break;
    case 6: printf("▊"); break;
    case 7: printf("▉"); break;
    default: printf("??");
  }

  for (int i = full + !!leak; i < length; ++i)
    printf("  ");

  printf("]\r");
  fflush(stdout);
}
