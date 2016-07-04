#ifndef _KVSET_H_
#define _KVSET_H_

#if defined __cplusplus
extern "C" {
#endif

/******************************************************************************
 * key-value set API 
 *****************************************************************************/

/* the structure is opaque */
struct kvset;
typedef struct kvset kvset;

/******************************************************************************
 * kvset API 
 *****************************************************************************/
kvset* kvset_new(void);
void kvset_free(kvset*);
void kvset_clear(kvset*);
void kvset_dump(kvset *set,FILE *out);
void kvset_add(kvset*set, const char *key, int klen, const char *val, int vlen,
  int vtype); 
#define kvset_adds(set, key, val) kv_add(set,key,strlen(key),val,strlen(val),0)
int kvset_len(kvset*set);
int kvset_next(kvset*set, int idx, char **key, int *klen, char **val, int *vlen,
  int *vtype);

#if defined __cplusplus
}
#endif

#endif
