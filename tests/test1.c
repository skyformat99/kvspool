#include <stdio.h>
#include "kvset.h"

int main() {
  kvset *kv;

  kv = kvset_new();
  kvset_free(kv);

  return 0;
}
