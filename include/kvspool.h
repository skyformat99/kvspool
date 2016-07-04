/* kvspool: an API for streaming sets of key-value pairs */

#ifndef _KVSPOOL_H_
#define _KVSPOOL_H_

#include <time.h> // time_t
#include "kvset.h"

#if defined __cplusplus
extern "C" {
#endif

/* opaque data structure */
struct kvsp;
typedef struct kvsp kvsp;

int kvsp_init(const char *file, size_t sz, int flags, ...);

kvsp *kvsp_open(const char *file);
int kvsp_read(kvsp *sp, kvset *set, int blocking);
int kvsp_write(kvsp *sp, kvset *set);
void kvsp_close(kvsp*);

typedef struct { int pct_consumed; time_t last_write; off_t spool_sz;} kv_stat_t;
int kv_stat(const char *file, kv_stat_t *stats);
void kv_rewind(const char *file);

#if defined __cplusplus
}
#endif

#endif
