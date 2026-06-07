#ifndef INSTALL_H
#define INSTALL_H

typedef enum INSTALL_ERR {
  INS_NULLPKG,
  INS_PKGNOTFOUND,
  INS_CONN,
  INS_GIT
} INSTALL_ERR;

int install(const char *pkgName);

#endif // INSTALL_H
