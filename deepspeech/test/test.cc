#include <stdlib.h>
#include <stdio.h>

#include <assert.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sstream>
#include <string>

#include "deepspeech.h"

int main()
{

  printf("Test\n");
  ModelState* aCtx = NULL;
      StreamingState* ctx;
    int status = DS_CreateStream(aCtx, &ctx);
    if (status != DS_ERR_OK) {
      printf("error\n");
      return 1;
    }

  return 0;
}