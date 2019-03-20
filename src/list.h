#ifndef MINECRAFTSEED_LIST_H_
#define MINECRAFTSEED_LIST_H_

#include <cassert>
#include <cstdlib>
#include <utility>
#include <cstdio>

struct List {
  void *data;
  int end, blocksize, maxsize;
  bool owned;

  template <typename T>
  static List AllocBuffer(const int size) {
    void *data = malloc(sizeof(T) * size);
    return List(data, 0, sizeof(T), size, true);
  }

  template <typename T>
  static List FromArray(T *data, const int len, const int maxsize = -1,
                        const bool exclusive = false) {
    return List(data, len, sizeof(T), maxsize == -1 ? len : maxsize, exclusive);
  }

  List(void *data_p, const int end_p, const int bs_p,
       const int msize_p, const bool own_p)
      : data(data_p), end(end_p), blocksize(bs_p),
        maxsize(msize_p), owned(own_p) {}

  ~List() {
    if (owned && data)
      free(data);
  }

  List operator=(const List &other) = delete;
  List(const List &other) = delete;

  List(List &&old)
      : data(old.data), end(old.end), blocksize(old.blocksize),
        maxsize(old.maxsize), owned(old.owned) {
    old.owned = false;
  }

  template <typename T>
  const T& get(const int pos) const {
    assert(sizeof(T) == blocksize && "Blocksize must be equal to the data\'s");
    return *(reinterpret_cast<T*>(data) + pos);
  }

  template <typename T>
  T& get(const int pos) {
    assert(sizeof(T) == blocksize && "Blocksize must be equal to the data\'s");
    return *(reinterpret_cast<T*>(data) + pos);
  }

  template <typename T>
  bool put(T obj) {
    assert(sizeof(T) == blocksize && "Blocksize must be equal to the data\'s");
    if (end >= maxsize) {
      fprintf(stderr, "List overflow: too much item saved\n");
      exit(1);
    }
    *(reinterpret_cast<T*>(data) + end) = obj;
    ++end;
    return true;
  }

  void* transform() {
    owned = false;
    return data;
  }
};

#endif  // MINECRAFTSEED_LIST_H_
