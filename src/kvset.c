#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "kvset.h"
#include "libut.h"

struct kvset {
  UT_vector /* of UT_string */ keys;
  UT_vector /* of UT_string */ vals;
  UT_vector /* of int       */ types;
};

static void oom_exit(void) {
  fprintf(stderr, "out of memory\n");
  abort();
}

kvset* kvset_new(void) {
  struct kvset *set;
  if ( (set = malloc(sizeof(kvset))) == NULL) oom_exit();
  memset(set,0,sizeof(*set));
  utvector_init(&set->keys,  utmm_utstring);
  utvector_init(&set->vals,  utmm_utstring);
  utvector_init(&set->types, utmm_int);
  return set;
}

void kvset_clear(struct kvset *set) {
  utvector_clear(&set->keys);
  utvector_clear(&set->vals);
  utvector_clear(&set->types);
}

void kvset_dump(struct kvset *set, FILE *out) {
  char *k, *v;
  int kl, vl;

  int i=0, t;
  while ( (i=kvset_next(set, i, &k, &kl, &v, &vl, &t)) > 0) {
    /* TODO interpret t and print value appropriately */
    fprintf(out, " %.*s -> (%d) %.*s\n", kl, k, t, vl, v);
  }
}

void kvset_free(kvset *set) {
  utvector_fini(&set->keys);
  utvector_fini(&set->vals);
  utvector_fini(&set->types);
  free(set);
}

int kvset_next(kvset *set, int i, char **key, int *klen, char **val, int *vlen, 
   int *vtype) {

  int l = utvector_len(&set->keys);
  if (i >= l) return -1;
  UT_string *k = utvector_elt(&set->keys, i);
  UT_string *v = utvector_elt(&set->vals, i);
  *vtype = *(int*)utvector_elt(&set->types, i);
  *key = utstring_body(k);
  *klen = utstring_len(k);
  *val = utstring_body(v);
  *vlen = utstring_len(v);
  return i+1;
}

void kvset_add(kvset *set, const char *key, int klen, const char *val, int vlen,
   int vtype) { 

  /* TODO check if we're replacing an existing key */
  UT_string *k = utvector_extend(&set->keys);
  UT_string *v = utvector_extend(&set->vals);
  int *t = utvector_extend(&set->types);

  utstring_bincpy(k, key, klen);
  utstring_bincpy(v, val, vlen);
  *t = vtype;
}

int kvset_len(kvset *set) {
  int l = utvector_len(&set->keys);
  return l;
}

