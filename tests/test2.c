#include <stdio.h>
#include "kvset.h"

int main() {
  kvset *set;

  set = kvset_new();

  kvset_add(set, "k1", 3, "v1", 3, 0);
  kvset_add(set, "k2", 3, "v2", 3, 0);

  int i = 0, kl, vl, t;
  char *k, *v;
  while( (i = kvset_next(set, i, &k, &kl, &v, &vl, &t)) > 0) {
    printf("%.*s -> %.*s (%d)\n", kl, k, vl, v, t);
  }

  kvset_free(set);

  return 0;
}
