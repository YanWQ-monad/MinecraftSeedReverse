#ifndef MINECRAFTSEED_PROGRESS_H_
#define MINECRAFTSEED_PROGRESS_H_

void print_progress(const char *title, const int percentage,
                    const int len = 20);
void print_progress(const int percentage, const int len = 20);
void ends_progress();

#endif  // MINECRAFTSEED_PROGRESS_H_
