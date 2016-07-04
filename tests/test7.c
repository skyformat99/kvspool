#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "kvspool.h"

char file[100];
size_t sz = 1024;

int main() {
  int rc = -1;
  kvsp *sp;

  snprintf(file, sizeof(file), "/tmp/test.spool.%d", (int)getpid());

  if (kvsp_init(file, sz, 0) < 0) goto done;

  sp = kvsp_open(file);
  if (sp) printf("opened\n");
  if (sp) kvsp_close(sp);

  rc = 0;

 done:
  unlink(file);
  return rc;
}
