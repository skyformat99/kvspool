#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include "kvspool.h"
#include "libut.h"

struct kvsp {
  char *name;    /* file name */
  struct stat s; /* file stat */
  int fd;        /* descriptor */
  char *buf;     /* mmap'd area */
};

static void oom_exit(void) {
  fprintf(stderr, "out of memory\n");
  abort();
}

/*******************************************************************************
* kvspool API 
*******************************************************************************/
int kvsp_init(const char *file, size_t sz, int flags, ...) {
  int rc = -1;

  /* TODO flags choose must-create, permit-existing, resize? */

  int fd = open(file, O_RDWR|O_CREAT|O_EXCL, 0644);
  if (fd == -1) {
    fprintf(stderr,"open %s: %s\n", file, strerror(errno));
    goto done;
  }

  if (ftruncate(fd, sz) < 0) {
    fprintf(stderr,"ftruncate %s: %s\n", file, strerror(errno));
    goto done;
  }

  rc = 0;

 done:
  if (fd != -1) close(fd);
  return rc;
}

struct kvsp *kvsp_open(const char *file) {
  int rc = -1;

  struct kvsp *kvsp = malloc( sizeof(struct kvsp) );
  if (kvsp == NULL) oom_exit();
  memset(kvsp, 0, sizeof(*kvsp));

  kvsp->name = strdup(file);
  kvsp->fd = open(file, O_RDWR);
  if (kvsp->fd == -1) {
    fprintf(stderr,"open %s: %s\n", file, strerror(errno));
    goto done;
  }

  if (fstat(kvsp->fd, &kvsp->s) == -1) {
    fprintf(stderr,"stat %s: %s\n", file, strerror(errno));
    goto done;
  }

  kvsp->buf = mmap(0, kvsp->s.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, kvsp->fd, 0);
  if (kvsp->buf == MAP_FAILED) {
    fprintf(stderr, "mmap %s: %s\n", file, strerror(errno));
    goto done;
  }

  /* TODO validate */

  rc = 0;

 done:
  if (rc < 0) {
    if (kvsp->name) free(kvsp->name);
    if (kvsp->fd != -1) close(kvsp->fd);
    if (kvsp->buf && (kvsp->buf != MAP_FAILED)) munmap(kvsp->buf, kvsp->s.st_size);
    free(kvsp);
    kvsp = NULL;
  }
  return kvsp;
}

int kvsp_write(struct kvsp *kvsp, kvset *set) {
  int rc = -1;
  return rc;
}

int kvsp_read(struct kvsp *kvsp, kvset *set, int blocking) {
  kvset_clear(set);
}

void kvsp_close(struct kvsp *kvsp) {
  if (kvsp->name) free(kvsp->name);
  if (kvsp->fd != -1) close(kvsp->fd);
  if (kvsp->buf && (kvsp->buf != MAP_FAILED)) munmap(kvsp->buf, kvsp->s.st_size);
  free(kvsp);
}

/*******************************************************************************
* MISC API 
*******************************************************************************/
int kv_stat(const char *dir, kv_stat_t *stats) {
}

void kv_rewind(const char *file) {
}
