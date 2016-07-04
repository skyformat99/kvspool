#include <stdio.h>
#include "kvset.h"

int main() {
  kvset *set;
  int l;

  set = kvset_new();

  l = kvset_len(set);
  printf("set has %d items\n", l);

  printf("adding two items to set\n");
  kvset_add(set, "k1", 3, "v1", 3, 1);
  kvset_add(set, "k2", 3, "v2", 3, 2);

  l = kvset_len(set);
  printf("set has %d items\n", l);

  kvset_dump(set, stdout);
  printf("clearing set\n");
  kvset_clear(set);

  l = kvset_len(set);
  printf("set has %d items\n", l);

  printf("adding two items to set\n");
  kvset_add(set, "k3", 3, "v3", 3, 3);
  kvset_add(set, "k4", 3, "v4", 3, 4);

  l = kvset_len(set);
  printf("set has %d items\n", l);

  kvset_dump(set, stdout);
  kvset_free(set);

  return 0;
}
