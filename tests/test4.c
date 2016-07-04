#include <stdio.h>
#include "kvset.h"

int main() {
  kvset *set;
  int l;

  set = kvset_new();

  l = kvset_len(set);
  printf("set has %d items\n", l);

  printf("adding two items to set\n");
  kvset_add(set, "k1", 3, "v1", 3, 0);
  kvset_add(set, "k2", 3, "v2", 3, 0);

  l = kvset_len(set);
  printf("set has %d items\n", l);

  int i = 0, kl, vl, t;
  char *k, *v;
  while( (i = kvset_next(set, i, &k, &kl, &v, &vl, &t)) > 0) {
    printf("%.*s -> %.*s (%d)\n", kl, k, vl, v, t);
  }

  printf("clearing set\n");
  kvset_clear(set);

  l = kvset_len(set);
  printf("set has %d items\n", l);

  printf("adding two items to set\n");
  kvset_add(set, "k3", 3, "v3", 3, 0);
  kvset_add(set, "k4", 3, "v4", 3, 0);

  l = kvset_len(set);
  printf("set has %d items\n", l);

  i = 0;
  while( (i = kvset_next(set, i, &k, &kl, &v, &vl, &t)) > 0) {
    printf("%.*s -> %.*s (%d)\n", kl, k, vl, v, t);
  }

  kvset_free(set);

  return 0;
}
