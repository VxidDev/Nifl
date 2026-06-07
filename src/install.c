#include "../include/install.h"
#include "../include/nifl.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * using system() here is not the best thing, but I'll keep it for basic MVP,
 * also this code is not cross-platform, so I might have to update it later...
*/ 

int install(const char *pkgName) {
  if (!pkgName) return INS_NULLPKG;

  system("rm -rf ./tmp"); // cleanup, it's temp code T-T

  char buf[4096];

  snprintf(buf, sizeof(buf), "mkdir -p %s", ARC_LIB_DIR);

  int code = system(buf);

  if (code != 0) {
    return code;
  }

  snprintf(buf, sizeof(buf), 
    "git clone --no-checkout %s tmp",
    NIFL_GIT_SOURCE
  );

  code = system(buf);

  if (code != 0) {
    return code;
  }
  
  snprintf(buf, sizeof(buf),
    "cd tmp && git sparse-checkout init --cone"
  );

  code = system(buf);
  
  if (code != 0) {
    return code;
  }

  snprintf(buf, sizeof(buf),
    "cd tmp && git cat-file -e HEAD:%s",
    pkgName 
  );

  code = system(buf);

  if (code != 0) {
    return code;
  }
  
  snprintf(buf, sizeof(buf),
    "cd tmp && git sparse-checkout set %s", 
    pkgName 
  );

  code = system(buf);

  if (code != 0) {
    return code;
  }

  snprintf(buf, sizeof(buf),
    "cd tmp && git checkout HEAD"
  );

  code = system(buf);

  if (code != 0) {
    return code;
  }

  snprintf(buf, sizeof(buf),
    "cp -r tmp/%s %s/%s",
    pkgName, ARC_LIB_DIR, pkgName 
  );

  code = system(buf);

  if (code != 0) {
    return code;
  }

  return 0;
}
