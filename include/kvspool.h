#ifndef _KVSPOOL_H_
#define _KVSPOOL_H_

#include <stdio.h>
#include "uthash.h"

/* kvspool: an API for streaming sets of key-value pairs */

/******************************************************************************
 * key-value set API 
 *****************************************************************************/
typedef struct {
  char *key;
  int klen;
  char *val;
  int vtype;
  int vlen;
  UT_hash_handle hh; /* internal */
} kv_t;


#if defined __cplusplus
extern "C" {
#endif

/******************************************************************************
 * kvset API 
 *****************************************************************************/
kvset* kv_set_new(void);
void kv_set_free(kvset*);
void kv_set_clear(kvset*);
void kv_set_dump(kvset *set,FILE *out);
void kv_add(kvset*set, const char *key, int klen, const char *val, int vlen);
kv_t *kv_get(kvset*set, char *key);
#define kv_adds(set, key, val) kv_add(set,key,strlen(key),val,strlen(val))
int kv_len(kvset*set);
kv_t *kv_next(kvset*set,kv_t *kv);

/******************************************************************************
 * spooling API 
 *****************************************************************************/
kvsp *kv_spoolreader_new(const char *dir);
int kv_spool_read(kvsp*sp, kvset *set, int blocking);
void kv_spoolreader_free(kvsp*);

kvsp *kv_spoolwriter_new(const char *dir);
int kv_spool_write(kvsp*sp, kvset *set);
void kv_spoolwriter_free(kvsp*);
void sp_attrition(char *dir);

/******************************************************************************
 * special purpose API 
 *****************************************************************************/
typedef struct { int pct_consumed; time_t last_write; off_t spool_sz;} kv_stat_t;
int kv_stat(const char *dir, kv_stat_t *stats);
void sp_rewind(const char *dir);

#if defined __cplusplus
}
#endif

#endif
